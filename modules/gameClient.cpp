#include "gameClient.h"

using namespace std;


bool GameClient::Login(const string &name, const string &password, const string &gameName, int numTurns,
                       int numPlayers, bool isObserver) {
    // Login
    auto answer = client->Login(name, password, gameName, numTurns, numPlayers, isObserver);
#ifdef _DEBUG
    std::cerr << (int) answer.result << " " << answer.answer << std::endl;
#endif
    if (answer.result != Result::OKEY)
        return false;

    int id = answer.answer.value("idx", -1);

    // Always init game for _3_ players
    game = new Game(id, name, password, numPlayers,
                    client->Map().answer, client->GameState().answer);

    return true;
}


bool GameClient::InitGame(const string &name, const string &password, const string &gameName, int numTurns,
                          int numPlayers, bool isObserver) {
    if (!Login(name, password, gameName, numTurns, numPlayers, isObserver))
        return false;

    return true;
}

GameClient::~GameClient() {
    //we don't use logout because, otherwise reconnection brings throw game is full
    //but logically we should do this
    //    client->Logout();
    delete game;
    delete client;
}

void GameClient::UpdateGameState() {
    auto state = client->GameState();
    game->UpdateGameState(state.answer);
}

bool GameClient::SendTurn() const {
    auto answer = client->Turn();
    return answer.result == Result::OKEY;
}

void GameClient::SendAction(const std::vector<std::tuple<Action, int, Point3D>> &actions) const {
    for (auto &act : actions) {
        auto &[actionType, vehicleId, coordinate] = act;
        auto &[x, y, z] = coordinate;
        Response resp = client->SendTankAction(actionType, vehicleId, x, y, z);
#ifdef _DEBUG
        std::cerr << (int) resp.result << " " << resp.answer << std::endl;
#endif
    }
}

void GameClient::InitIds() {
    auto answer = client->GameState();
    while (answer.answer.value("players", nlohmann::ordered_json("")).size() != game->GetNumPlayers()) {
        client->Turn();
        answer = client->GameState();
    }
    std::cout << answer.answer.value("players", nlohmann::ordered_json(""));
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

void GameClient::InitPlayersIds(const nlohmann::ordered_json &am) {
    vector<int> realIds;
    for (auto &pm : am.items()) {
        realIds.push_back(stoi(pm.key()));
    }
    game->InitPlayersId(realIds);
}

void GameClient::InitVehiclesIds(const nlohmann::ordered_json &vehicles) {
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


void GameClient::StartAI() {
    InitIds();
    while (!GameIsFinished()) {
        UpdateGameState();
        if (IsPlayTime())// play only our turn
                         //             SendAction();

#ifdef _DEBUG
            std::cerr << "\n---------------------------------------\n";
#endif
        SendTurn();
    }
}

GameClient::GameClient(const string &name, const string &password, const string &gameName,
                       int numTurns, int numPlayers, bool isObserver) {
    client = new Client();
    InitGame(name, password, gameName, numTurns, numPlayers, isObserver);
//    InitIds();
}
