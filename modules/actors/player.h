#pragma once

#include <string>
//#include <vector>
//#include "vehicle.h"

class Player {
private:
    std::string name;
    std::string password;
    int id;
    // std::vector<Vehicle*>& tanks;
    int capture;
    int kill;

public:
    Player(int id, std::string name, std::string pass);

    int GetId() const;
};

