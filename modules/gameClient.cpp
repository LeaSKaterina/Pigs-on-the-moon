#include "gameClient.h"

bool GameClient::Login(const string &name, const string &password, const string &gameName, int numTurns,
                 int numPlayers, bool isObserver) {
    // Login
    auto answer = client->Login(name, password, gameName, numTurns, numPlayers, isObserver);
    if (answer.result != Result::OKEY)
        return false;

    int id = answer.answer.value("idx", -1);
    this->game->InitPlayer(id, name, password);

    // Always init game for _3_ players
    game->InitVariables();
    return true;
}

bool GameClient::InitGame(const string &name, const string &password, const string &gameName, int numTurns,
                          int numPlayers, bool isObserver) {
    if (!Login(name, password, gameName, numTurns, numPlayers, isObserver))
        return false;
    InitMap();
    return true;
}

GameClient::~GameClient() {
    client->Logout();
    delete game;
    delete client;
}

void GameClient::UpdateGameState() {
    auto answer = client->GameState();

    // attack matrix
    UpdateAttackMatrix(answer.answer.value("attack_matrix", nlohmann::ordered_json("")));

    // current turn | player | finished
    game->UpdateState(
            answer.answer.value("current_turn", -1),
            answer.answer.value("current_player_idx", -1),
            answer.answer.value("finished", 0));

    // vehicles
    UpdateVehicles(answer.answer.value("vehicles", nlohmann::ordered_json("")));

    // win_points
    UpdateWinPoints(answer.answer.value("win_points", nlohmann::ordered_json("")));
}

bool GameClient::SendTurn() const {
    auto answer = client->Turn();
    return answer.result == Result::OKEY;
}

void GameClient::SendAction() const {
    auto actions = game->Play();
    for (auto &act : actions) {
        auto &[actionType, vehicleId, coordinate] = act;
        auto &[x, y, z] = coordinate->GetCoordinates();
        // TODO? Is there any check needed? as Hex* == nullptr
        switch (actionType) {
            case Action::MOVE:
                client->Move(vehicleId, x, y, z);
                // TODO make other move/shoot in Client private
                break;
            case Action::SHOOT:
                client->Shoot(vehicleId, x, y, z);
                break;
            default:
                //                cerr << "DEFAULT ACTIVE" << endl;
                break;
        }
    }
}


void GameClient::InitIds() {
    auto answer = client->GameState();

    // players id
    InitPlayersIds(answer.answer.value("attack_matrix", nlohmann::ordered_json("")));

    // vehicle id
    InitVehiclesIds(answer.answer.value("vehicles", nlohmann::ordered_json("")));
}

tuple<int, int, int> GameClient::MakePosTuple(const nlohmann::json&& coordinate) {
    return make_tuple(
            coordinate.value("x", -1),
            coordinate.value("y", -1),
            coordinate.value("z", -1));
}


void GameClient::InitMap() {
    // Map
    nlohmann::ordered_json mapInfo = client->Map().answer;
    int size = mapInfo.value("size", -1);
    game->InitMap(size);

    #ifdef _DEBUG
        cout << "Map request:\n"
             << mapInfo << "\n:Map request" << endl;
    #endif

    auto spawnInfo = mapInfo.value("spawn_points", nlohmann::ordered_json(""));
    int index = 0;

    for (auto& player : spawnInfo.items()) {
        for(int i = 0; i < VehiclesTypes::TypesNum; i++) {
            const auto& type = VehiclesTypes::s_types[i];
            auto spawns = player.value().value(type, nlohmann::ordered_json(""));
            for (auto& spawn : spawns.items()) {
                auto &point = spawn.value();
                #ifdef _DEBUG
                    cout << "SPAWNS:\n" << spawns << "\n:SPAWNS" << endl;
                    cout << "POINT:\n" << point << "\n:POINTS" << endl;
                #endif
                game->AddVehicle(index,
                                 VehiclesTypes::Type(i),
                                 MakePosTuple(point));
                //                std::cerr << "POINT1: " << typeid(point).name() << std::endl;
            }
        }
        index++;
    }

    auto contentInfo = mapInfo.value("content", nlohmann::ordered_json(""));
    auto baseInfo = contentInfo.value("base", nlohmann::ordered_json(""));
    vector<tuple<int, int, int>> basePoints;
    for (auto &point : baseInfo) {
        basePoints.emplace_back(MakePosTuple(point));
        //        std::cerr << "POINT2: " << typeid(point).name() << std::endl;
    }
    game->AddBase(basePoints);
}


void GameClient::UpdateVehicles(const nlohmann::json &&vehicles) {
    for (auto &v : vehicles.items()) {
        auto &vehicleInfo = v.value();

        auto pos = MakePosTuple(
                vehicleInfo.value("position", nlohmann::ordered_json("")));
        auto spawnPos = MakePosTuple(
                vehicleInfo.value("spawn_position", nlohmann::ordered_json("")));
        game->UpdateVehicleState(
                vehicleInfo.value("player_id", -1),
                spawnPos,
                pos,
                vehicleInfo.value("health", -1),
                vehicleInfo.value("capture_points", -1));
        // TODO? mb ref in uvs;
    }
}


void GameClient::UpdateAttackMatrix(const nlohmann::json &&am) {
    //    const int vector_size = game->GetNumPlayers();
    for (auto &pm : am.items()) {
        // player id = pm.key, vector of attacks = pm.value
        // to upd : is there a way to do vector without a loop ?

        vector<int> vAttacked;
        //        auto& arr_attacked = pm.value();
        for (int i : pm.value()) {
            vAttacked.push_back(i);
        }
        game->UpdateAttackMatrix(stoi(pm.key()), vAttacked);
    }
}


void GameClient::UpdateWinPoints(const nlohmann::json &&winPoints) {
    cerr << "DEBUG: " << winPoints << endl;
    for (auto &player : winPoints.items()) {
        auto &winPointsInfo = player.value();
        game->UpdateWinPoints(
                stoi(player.key()),
                winPointsInfo.value("capture", 0),
                winPointsInfo.value("kill", 0));
    }
}


void GameClient::InitPlayersIds(const nlohmann::json &&am) {
    vector<int> realIds;
    for (auto &pm : am.items()) {
        realIds.push_back(stoi(pm.key()));
    }
    game->InitPlayersId(realIds);
}


void GameClient::InitVehiclesIds(const nlohmann::json &&vehicles) {
    // TODO! recode
    vector<int> vehiclesIds;
    int currentPlayerId = -1;
    for (auto &v : vehicles.items()) {
        auto &vehicleInfo = v.value();
        int playerId = vehicleInfo.value("player_id", -1);
        int vehicleId = stoi(v.key());
        if (currentPlayerId == -1)
            currentPlayerId = playerId;
        if (currentPlayerId != playerId) {
            game->InitVehiclesIds(currentPlayerId, vehiclesIds);
            vehiclesIds.clear();
            currentPlayerId = playerId;
        }
        vehiclesIds.push_back(vehicleId);
    }
    if (!vehiclesIds.empty())
        game->InitVehiclesIds(currentPlayerId, vehiclesIds);
}
