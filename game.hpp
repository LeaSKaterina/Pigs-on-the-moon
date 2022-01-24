#pragma once
#include <tuple>
#include <vector>
#include <string>
#include "actors\vehicle.hpp"
#include "map\map.hpp"
#include "actors\player.hpp"
using namespace std;

class Game
{
public:
    Game() {}
    ~Game() {}

    void init_map(int size) {
        map = new Map(size);
    }
    
    void add_vehicle(int player_id, Vehicle::Type type, tuple<int, int, int> spawn) {
        Vehicle* t = new Vehicle(type, player_id);
        t->init_spawn(map->get(spawn));
        vehicles[player_id].push_back(t);
    }

    void add_base(vector<tuple<int, int, int>>& points) {
        map->add_base(points);
    }

    void init_player(int id, string name, string password = "") {
        player = new Player(id, name, password);
    }

    void init_variables(int players_num = 3) {
        num_players = players_num;
        num_turns = num_rounds * num_players;
        current_turn = 0;

        vehicles.resize(players_num + 1);
        attack_matrix.resize(players_num + 1);
        captures.resize(players_num + 1);
        kills.resize(players_num + 1);
    }

    // get state
    void update_state(int curr_turn, int curr_player) {
        current_turn = curr_turn;
        current_player = curr_player; 
    }

    void update_vehicle_state(int parent_id, 
        tuple<int, int, int> spawn, 
        tuple<int, int, int> pos, 
        int health, 
        int capture_points) {
        Vehicle* v = find(parent_id, spawn);
        v->update(health, map->get(pos), capture_points);
    }

    void update_attack_matrics(int player_id, vector<int> attacked) {
        attack_matrix[player_id] = move(attacked);
    }

    void update_win_points(int player_id, int capture, int kill) {
        captures[player_id] = capture;
        kills[player_id] = kill;
    }
    // get action

private:
    vector<int> state;
    vector<vector<Vehicle*>> vehicles;

    vector<int> captures;
    vector<int> kills;

    const int num_rounds = 15;
    int num_turns; 
    int current_turn;
    
    int num_players;
    int current_player;

    vector<vector<int>> attack_matrix; // {"id" : "whom attack"}
    Map* map;

    Player* player;

    Vehicle* find(int parent_id, const tuple<int, int, int>& spawn) const {
        for (auto* p : vehicles[parent_id]) {
            if (p->get_spawn() == spawn)
                return p; 
        }
        return nullptr;
    }
};
