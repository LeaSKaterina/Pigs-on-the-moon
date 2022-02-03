#pragma once

#include <string>
//#include <vector>
//#include "vehicle.h"

struct Player {
private:
    const std::string name;
    const std::string password;
    int id;
    // std::vector<Vehicle*>& tanks;
    int capture;
    int kill;

public:
    Player(int id, const std::string &name, const std::string &pass) : id(id), name(name), password(pass), capture(0),
                                                                       kill(0) {}

    int GetId() const { return id; }
};
