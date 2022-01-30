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

tuple<int, int, int> GameClient::MakePosTuple(nlohmann::json coordinate) {
    return make_tuple(
            coordinate.value("x", -1),
            coordinate.value("y", -1),
            coordinate.value("z", -1)
    );
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
    return game->IsFinished();
}

void GameClient::CheckGameState() {
    auto answer = client->GameState();

    // attack matrix

    auto am = answer.answer.value("attack_matrix", nlohmann::json(""));
//    const int vector_size = game->GetNumPlayers();
    for(auto& pm : am.items()) {
        // player id = pm.key, vector of attacks = pm.value
        // to upd : is there a way to do vector without a loop ?

        vector<int> v_attacked;
//        auto& arr_attacked = pm.value();
        for(int i : pm.value()) {
            v_attacked.push_back(i);
        }
        game->UpdateAttackMatrix(stoi(pm.key()), v_attacked);
    }

    // current turn | player | finished

    game->UpdateState(
            answer.answer.value("current_turn", -1),
            answer.answer.value("current_player_idx", -1),
            answer.answer.value("finished", 0)
            );

    // vehicles

    auto vehicles = answer.answer.value("vehicles", nlohmann::json(""));
    for(auto& v : vehicles.items()) {
        auto& vehicle_info = v.value();

        auto position = vehicle_info.value("position", nlohmann::json(""));
        auto spawn_position = vehicle_info.value("spawn_position", nlohmann::json(""));

//        cout << "| " << v.key() << " | " << v.value() << " |" << endl;
        auto pos = MakePosTuple(
                vehicle_info.value("position", nlohmann::json(""))
                );
        auto spawn_pos = MakePosTuple(
                vehicle_info.value("position", nlohmann::json(""))
        );
        game->UpdateVehicleState(
                vehicle_info.value("player_id", -1),
                spawn_pos,
                pos,
                vehicle_info.value("health", -1),
                vehicle_info.value("capture_points", -1));
        // TODO? mb ref in uvs;
    }

    // win_points

    auto win_points = answer.answer.value("win_points", nlohmann::json(""));
    for(auto& player : vehicles.items()) {
        auto& win_points_info = player.value();
        game->UpdateWinPoints(
                stoi(player.key()),
                win_points_info.value("capture", 0),
                win_points_info.value("kill", 0)
                );
    }
}

bool GameClient::SendTurn() const {
    auto answer = client->Turn();
    return answer.result == Result::OKEY;
}

void GameClient::SendAction() const {
    // TODO!
}

void GameClient::InitPlayersId() {
    // TODO!
}


