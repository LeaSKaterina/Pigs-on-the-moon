#ifndef PIGS_ON_THE_MOON_HEAVYTANK_H
#define PIGS_ON_THE_MOON_HEAVYTANK_H

#include "vehicle.h"

class HeavyTank : public Vehicle {
    virtual std::vector<Point> GetAvailableMovePoints() override;

    virtual std::vector<Point> GetAvailableShootPoints() override;
};


#endif//PIGS_ON_THE_MOON_HEAVYTANK_H
