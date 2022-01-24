#pragma once
#include "vehicle.hpp"
#include <string>
#include <vector>

class Player {
public:
    Player(int _id, std::string _name, std::string pass)
        : id(_id), 
        name(_name),
        password(pass) {}

    int get_id() const {
        return id;
    }
    
private:
    std::string name;
    std::string password;
    int id;
    // std::vector<Vehicle*>& tanks;
    int capture;
    int kill;
};