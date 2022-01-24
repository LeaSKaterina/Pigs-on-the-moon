#pragma once
#include "map\hex.hpp"

class Vehicle {
public:
    enum Type {
        MediumTank, LightTank, HeavyTank, AtSpg, Spg
    };

    Vehicle(Type type, int player_id) {
        switch (type) {
            case MediumTank:
                health = 2;
                speed_points = 2;
                break;
            case LightTank:
            case HeavyTank:
            case AtSpg: 
            case Spg:
                break;
        }
        destruction_points = health;
        this->player_id = player_id;
    }

    bool move (Hex* new_pos) {
        if (!new_pos->occupy())
            return false;

        current_position->free();
        current_position = new_pos;
        return true;
    }

    int shoot (Vehicle* v) { // вернет сколько очков заработал
        if (isEnemy(v))
            return v->get_hit(this->damage);
        return 0;
    }

    void inc_capture() {
        capture_points++;
    }

    void drop_capture() {
        capture_points = 0;
    }

    void update(int health, Hex* new_pos, int capture) {
        current_position = new_pos;
        this->health = health;
        capture_points = capture;
    }

    int get_player_id() const {
        return player_id;
    }

    const std::tuple<int, int, int>& get_spawn() const {
        return spawn_position->get_coordinates();
    }

    void init_spawn(Hex* p) {
        spawn_position = p;
        current_position = spawn_position;
    }

    void respawn() {
        move(spawn_position);
        health = destruction_points;
        capture_points = 0;
    }

private:
    int player_id;

    int health;
    int destruction_points;    // Очки за уничтожение
    int speed_points;
    int damage = 1;
    int capture_points;
    Hex* spawn_position;
    Hex* current_position;
    Type type;

    int get_hit (int damage = 1) { 
        this->health -= damage;
        if (health <= 0) 
            return destruction_points;
        return 0;
    }

    bool isEnemy(Vehicle* v) {
        return this->player_id != v->player_id;
    }

};