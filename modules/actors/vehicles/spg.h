#ifndef PIGS_ON_THE_MOON_SPG_H
#define PIGS_ON_THE_MOON_SPG_H
#include "vehicle.h"

class Spg : public Vehicle {
public:
    Spg (int playerId) : Vehicle(playerId, 1, 1) {};

    std::vector<Point> GetAvailableMovePoints(Point target, int r = 0) override;

    bool IsAvailableForShoot(Vehicle *enemy) override;
};


#endif//PIGS_ON_THE_MOON_SPG_H