#ifndef PIGS_ON_THE_MOON_HEAVYTANK_H
#define PIGS_ON_THE_MOON_HEAVYTANK_H

#include "vehicle.h"

class HeavyTank : public Vehicle {
public:
    HeavyTank(int playerId) : Vehicle(playerId, 3, 1) {};

    std::vector<Point> GetAvailableMovePoints(Point target, int r = 0) override;

    bool IsAvailableForShoot(Vehicle *enemy) override;
};


#endif//PIGS_ON_THE_MOON_HEAVYTANK_H
