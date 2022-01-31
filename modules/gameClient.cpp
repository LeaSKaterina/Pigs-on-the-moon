#include "gameClient.h"

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
    nlohmann::ordered_json map_info = client->Map().answer;
    int size = map_info.value("size", -1);
    game->InitMap(size);

    auto spawn_info = map_info.value("spawn_points", nlohmann::ordered_json(""));
    int index = 0;
    for (auto& player : spawn_info.items()) {
        auto points = player.value().value("medium_tank", nlohmann::ordered_json(""));
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

    auto content_info = map_info.value("content", nlohmann::ordered_json(""));
    auto base_info = content_info.value("base", nlohmann::ordered_json(""));
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

tuple<int, int, int> GameClient::MakePosTuple(nlohmann::ordered_json coordinate) {
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

GameClient::GameClient(bool debug) {
    game = new Game();
    client = new Client(debug);
}

bool GameClient::GameIsFinished() const {
    return game->IsFinished();
}

void GameClient::CheckGameState() {
    auto answer = client->GameState();

    // attack matrix

    auto am = answer.answer.value("attack_matrix", nlohmann::ordered_json(""));
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

    auto vehicles = answer.answer.value("vehicles", nlohmann::ordered_json(""));
    for(auto& v : vehicles.items()) {
        auto& vehicle_info = v.value();

        auto position = vehicle_info.value("position", nlohmann::ordered_json(""));
        auto spawn_position = vehicle_info.value("spawn_position", nlohmann::ordered_json(""));

        auto pos = MakePosTuple(
                vehicle_info.value("position", nlohmann::ordered_json(""))
                );
        auto spawn_pos = MakePosTuple(
                vehicle_info.value("spawn_position", nlohmann::ordered_json(""))
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

    auto win_points = answer.answer.value("win_points", nlohmann::ordered_json(""));
    cerr <<"DEBUG: " << win_points << endl;
    for(auto& player : win_points.items()) {
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
    auto actions = game->Play();
    for(auto& act : actions) {
        auto& [action_type, vehicle_id, coordinate] = act;
        auto& [x, y, z] = coordinate->GetCoordinates();
        // TODO? Is there any check needed? as Hex* == nullptr
        switch (action_type) {
            case Action::MOVE:
                client->Move(vehicle_id, x, y, z);
                // TODO make other move/shoot in Client private
                break;
            case Action::SHOOT:
                client->Shoot(vehicle_id, x, y, z);
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
    vector<int> real_ids;

    // players id

    auto am = answer.answer.value("attack_matrix", nlohmann::ordered_json(""));
    for(auto& pm : am.items()) {
        real_ids.push_back(stoi(pm.key()));
    }
    game->InitPlayersId(real_ids);

    // vehicle id
    // TODO! recode
    vector<int> vehicles_ids;
    int current_player_id = -1;
    auto vehicles = answer.answer.value("vehicles", nlohmann::ordered_json(""));
    for(auto& v : vehicles.items()) {
        auto& vehicle_info = v.value();
        int player_id = vehicle_info.value("player_id", -1);
        int vehicle_id = stoi(v.key());
        if (current_player_id == -1)
            current_player_id = player_id;
        if(current_player_id != player_id) {
            game->InitVehiclesIds(current_player_id, vehicles_ids);
            vehicles_ids.clear();
            current_player_id = player_id;
        }
        vehicles_ids.push_back(vehicle_id);
    }
    if(!vehicles_ids.empty())
        game->InitVehiclesIds(current_player_id, vehicles_ids);
}

Client *GameClient::getClient() const {
    return client;
}

bool GameClient::isOurTurn() {
    return true;
}


