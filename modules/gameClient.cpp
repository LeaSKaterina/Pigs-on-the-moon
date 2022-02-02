#include "gameClient.h"

bool GameClient::InitGame(const string &name, const string &password, const string &gameName, int numTurns,
                          int numPlayers, bool isObserver) {
    // Login
    auto answer = client->Login(name, password, gameName, numTurns, numPlayers, isObserver);
    if (answer.result != Result::OKEY)
        return false;

    int id = answer.answer.value("idx", -1);
    this->game->InitPlayer(id, name, password);

    // Always init game for _3_ players
    game->InitVariables();

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

    for (auto &player : spawnInfo.items()) {
        for (auto &spawn : player.value().items()) {
            auto &points = spawn.value();
            string type = spawn.key();
            for (auto &i : points) {
                game->AddVehicle(index,
                                 type,
                                 make_tuple(
                                         i.value("x", -1),
                                         i.value("y", -1),
                                         i.value("z", -1)));
            }
        }
        index++;
    }

    auto contentInfo = mapInfo.value("content", nlohmann::ordered_json(""));
    auto baseInfo = contentInfo.value("base", nlohmann::ordered_json(""));
    vector<tuple<int, int, int>> basePoints;
    for (auto &point : baseInfo) {
        basePoints.emplace_back(
                make_tuple(
                        point.value("x", -1),
                        point.value("y", -1),
                        point.value("z", -1)));
    }
    game->AddBase(basePoints);
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

    auto am = answer.answer.value("attack_matrix", nlohmann::ordered_json(""));
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

    // current turn | player | finished

    game->UpdateState(
            answer.answer.value("current_turn", -1),
            answer.answer.value("current_player_idx", -1),
            answer.answer.value("finished", 0));

    // vehicles

    auto vehicles = answer.answer.value("vehicles", nlohmann::ordered_json(""));
    for (auto &v : vehicles.items()) {
        auto &vehicleInfo = v.value();

        auto position = vehicleInfo.value("position", nlohmann::ordered_json(""));
        auto spawnPosition = vehicleInfo.value("spawn_position", nlohmann::ordered_json(""));

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

    // win_points

    auto winPoints = answer.answer.value("win_points", nlohmann::ordered_json(""));
    cerr << "DEBUG: " << winPoints << endl;
    for (auto &player : winPoints.items()) {
        auto &winPointsInfo = player.value();
        game->UpdateWinPoints(
                stoi(player.key()),
                winPointsInfo.value("capture", 0),
                winPointsInfo.value("kill", 0));
    }
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

// must be called only when all players are connected
void GameClient::InitPlayersId() {
    auto answer = client->GameState();
    vector<int> realIds;

    // players id

    auto am = answer.answer.value("attack_matrix", nlohmann::ordered_json(""));
    for (auto &pm : am.items()) {
        realIds.push_back(stoi(pm.key()));
    }
    game->InitPlayersId(realIds);

    // vehicle id
    // TODO! recode
    vector<int> vehiclesIds;
    int currentPlayerId = -1;
    auto vehicles = answer.answer.value("vehicles", nlohmann::ordered_json(""));
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

tuple<int, int, int> GameClient::MakePosTuple(const nlohmann::ordered_json &coordinate) {
    return make_tuple(
            coordinate.value("x", -1),
            coordinate.value("y", -1),
            coordinate.value("z", -1));
}
