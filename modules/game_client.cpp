#include "game_client.h"

bool GameClient::initGame(const string &name, const string &password, const string &game_name, int num_turns,
                          int num_players, bool is_observer)  {
    // Login
    auto answer = client->Login(name, password, game_name, num_turns, num_players, is_observer);
    if (answer.result != Result::OKEY)
        return false;

    int id = answer.answer.value("idx", -1);
    this->game->InitPlayer(id, name, password);

    // Always init game for _3_ players
    game->InitVariables();

    // Map
    nlohmann::json map_info = client->Map().answer;
    int size = map_info.value("size", -1);
    game->InitMap(size);

    auto spawn_info = map_info.value("spawn_points", nlohmann::json(""));
    int index = 0;
    for (auto& player : spawn_info.items()) {
        auto points = player.value().value("medium_tank", nlohmann::json(""));
        for (auto& i : points){
            game->AddVehicle(index,
                             Vehicle::Type::MediumTank,
                             make_tuple(
                                     i.value("x", -1),
                                     i.value("y", -1),
                                     i.value("z", -1)
                             ));
        }
        index++;
    }

    auto content_info = map_info.value("content", nlohmann::json(""));
    auto base_info = content_info.value("base", nlohmann::json(""));
    vector<tuple<int, int, int>> base_points;
    for (auto& point : base_info) {
        base_points.emplace_back(
                make_tuple(
                        point.value("x", -1),
                        point.value("y", -1),
                        point.value("z",-1)
                        )
                );
    }
    game->AddBase(base_points);
    return true;
}

GameClient::~GameClient() {
    client->Logout();
    delete game;
    delete client;
}

GameClient::GameClient() {
    game = new Game();
    client = new Client();
}

bool GameClient::GameIsFinished() const {
    return gameIsFinished;
}

void GameClient::CheckGameState() {
    // TODO!
    // change gameIsFinished there
    auto answer = client->GameState();
    // attack matrix
    auto am = answer.answer.value("attack_matrix", nlohmann::json(""));

//    for (auto& player : spawn_info.items()) {
//        auto points = player.value().value("medium_tank", nlohmann::json(""));
//        for (auto& i : points){
//            game->AddVehicle(index,
//                             Vehicle::Type::MediumTank,
//                             make_tuple(
//                                     i.value("x", -1),
//                                     i.value("y", -1),
//                                     i.value("z", -1)
//                             ));
//            index++;
//        }
//    }

    // current player_turn
    // finished
    // players -- id!
    // vehicles
    // win_points
}

bool GameClient::SendTurn() const {
    auto answer = client->Turn();
    return answer.result == Result::OKEY;
}

void GameClient::SendAction() const {
    // TODO!
}


