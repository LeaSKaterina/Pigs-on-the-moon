#ifndef PIGS_ON_THE_MOON_LIGHTTANK_H
#define PIGS_ON_THE_MOON_LIGHTTANK_H

#include "vehicle.h"

class LightTank : public Vehicle {

public:
    LightTank(int playerId) : Vehicle(playerId, 1, 3){};

    std::vector<Point> GetAvailableMovePoints(Point target, int r = 0) override;

    bool IsAvailableForShoot(Vehicle *enemy) override;
};


#endif//PIGS_ON_THE_MOON_LIGHTTANK_H
