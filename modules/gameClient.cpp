#include "gameClient.h"

using namespace std;


bool GameClient::Login(const string &name, const string &password, const string &gameName, int numTurns,
                       int numPlayers, bool isObserver) {
    // Login
    auto answer = client->Login(name, password, gameName, numTurns, numPlayers, isObserver);
    if (answer.result != Result::OKEY)
        return false;

    int id = answer.answer.value("idx", -1);

    // Always init game for _3_ players
    game = new Game(id, name, password);

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
        auto &[x, y, z] = coordinate;
        // TODO? Is there any check needed? as Hex* == nullptr
        Response resp = client->SendTankAction(actionType, vehicleId, x, y, z);
#ifdef _DEBUG
        std::cerr << (int) resp.result << " " << resp.answer << std::endl;
#endif
    }
}

void GameClient::InitIds() {
    auto answer = client->GameState();
#ifdef _DEBUG
    cerr << "Attack Matrix: "
         << answer.answer.value("attack_matrix", nlohmann::ordered_json(""))
         << " :Attack Matrix" << endl;
    cerr << "Vehicles: "
         << answer.answer.value("vehicles", nlohmann::ordered_json(""))
         << " :Vehicles" << endl;
#endif
    // players id
    InitPlayersIds(answer.answer.value("attack_matrix", nlohmann::ordered_json("")));

    // vehicle id
    InitVehiclesIds(answer.answer.value("vehicles", nlohmann::ordered_json("")));
}


Point GameClient::MakePosTuple(const nlohmann::json &&coordinate) {
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

    InitSpawns(mapInfo.value("spawn_points", nlohmann::ordered_json("")));

    auto contentInfo = mapInfo.value("content", nlohmann::ordered_json(""));
    auto baseInfo = contentInfo.value("base", nlohmann::ordered_json(""));
    vector<tuple<int, int, int>> basePoints;
    for (auto &point : baseInfo) {
        basePoints.emplace_back(MakePosTuple(point));
    }
    game->AddBase(basePoints);
}

void GameClient::InitSpawns(const nlohmann::ordered_json &&spawnInfo) {
#ifdef _DEBUG
    cerr << "Spawn Info: "
         << spawnInfo
         << " :Spawn Info" << endl;
#endif
    int index = 0;
    for (auto &player : spawnInfo.items()) {
        for (int i = 0; i < VehiclesTypes::typesNum; i++) {
            const auto &type = VehiclesTypes::sTypes[i];
            auto spawns = player.value().value(type, nlohmann::ordered_json(""));
            for (auto &spawn : spawns.items()) {
                auto &point = spawn.value();
#ifdef _DEBUG
                cout << "SPAWNS:\n"
                     << spawns << "\n:SPAWNS" << endl;
                cout << "POINT:\n"
                     << point << "\n:POINTS" << endl;
#endif
                game->AddVehicle(index,
                                 VehiclesTypes::Type(i),
                                 MakePosTuple(point));
            }
        }
        index++;
    }
}

void GameClient::InitPlayersIds(const nlohmann::ordered_json &&am) {
    vector<int> realIds;
    for (auto &pm : am.items()) {
        realIds.push_back(stoi(pm.key()));
    }
    game->InitPlayersId(realIds);
}

void GameClient::InitVehiclesIds(const nlohmann::ordered_json &&vehicles) {
    // TODO! do we need all players?
    // copy strings ...
    unordered_map<string, vector<int>> vehiclesIds;
    int currentPlayerId = -1;
    for (auto &v : vehicles.items()) {
        auto &vehicleInfo = v.value();
        int playerId = vehicleInfo.value("player_id", -1);
        string vehicleType = vehicleInfo.value("vehicle_type", "unknown");
        int vehicleId = stoi(v.key());
        if (currentPlayerId == -1)
            currentPlayerId = playerId;
        if (currentPlayerId != playerId) {
            game->InitVehiclesIds(currentPlayerId, vehiclesIds);
            vehiclesIds.clear();
            currentPlayerId = playerId;
        }
        vehiclesIds[vehicleType].push_back(vehicleId);
    }
    if (!vehiclesIds.empty())
        game->InitVehiclesIds(currentPlayerId, vehiclesIds);
}


void GameClient::UpdateVehicles(const nlohmann::ordered_json &&vehicles) {
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

void GameClient::UpdateAttackMatrix(const nlohmann::ordered_json &&am) {
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

void GameClient::UpdateWinPoints(const nlohmann::ordered_json &&winPoints) {
    cerr << "DEBUG: " << winPoints << endl;
    for (auto &player : winPoints.items()) {
        auto &winPointsInfo = player.value();
        game->UpdateWinPoints(
                stoi(player.key()),
                winPointsInfo.value("capture", 0),
                winPointsInfo.value("kill", 0));
    }
}