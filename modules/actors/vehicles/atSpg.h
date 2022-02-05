#ifndef PIGS_ON_THE_MOON_ATSPG_H
#define PIGS_ON_THE_MOON_ATSPG_H

#include "vehicle.h"

class AtSpg : public Vehicle {
public:
    AtSpg(int playerId) : Vehicle(playerId, 2, 1) {};

    std::vector<Point> GetAvailableMovePoints() override;

    bool IsAvailableForShoot(Vehicle *enemy) override;
};


#endif//PIGS_ON_THE_MOON_ATSPG_H
