#include "gameClient.h"

using namespace std;

GameClient::GameClient(const string &name, const string &password, const string &gameName,
                       int numTurns, int numPlayers, bool isObserver) {
    client = new Client();
    CreateConnection(name, password, gameName, numTurns, numPlayers, isObserver);
}

GameClient::~GameClient() {
    //we don't use logout because, otherwise reconnection brings throw game is full,
    //but logically we should do this
    //    client->Logout();
    delete game;
    delete client;
}

// Init methods

int GameClient::Login(const string &name, const string &password, const string &gameName, int numTurns,
                      int numPlayers, bool isObserver) {
    // Login
    auto answer = client->Login(name, password, gameName, numTurns, numPlayers, isObserver);
#ifdef _DEBUG
    std::cerr << (int) answer.result << " " << answer.answer << std::endl;
#endif
    if (answer.result != Result::OKEY)
        return false;

    return answer.answer.value("idx", -1);
}


bool GameClient::CreateConnection(const string &name, const string &password, const string &gameName, int numTurns,
                                  int numPlayers, bool isObserver) {
    int id = Login(name, password, gameName, numTurns, numPlayers, isObserver);
    if (id == -1)
        return false;
    game = new Game(id, name, password, isObserver, numPlayers, client->Map().answer);
    return true;
}


void GameClient::ConnectPlayer() {
    auto state = client->GameState();
    while (state.answer.value("players", nlohmann::ordered_json("")).size() != game->GetNumPlayers()) {
        client->Turn();
        state = client->GameState();
    }
    std::cout << state.answer.value("players", nlohmann::ordered_json("")) << '\n';
#ifdef _DEBUG
    cerr << "Attack Matrix: "
         << state.answer.value("attack_matrix", nlohmann::ordered_json(""))
         << " :Attack Matrix" << endl;
    cerr << "Vehicles: "
         << state.answer.value("vehicles", nlohmann::ordered_json(""))
         << " :Vehicles" << endl;
#endif
    game->InitIds(state.answer);
}

// Game process methods

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
