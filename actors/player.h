#ifndef PIGS_ON_THE_MOON_PLAYER_H
#define PIGS_ON_THE_MOON_PLAYER_H

//#pragma once
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


#endif //PIGS_ON_THE_MOON_PLAYER_H
