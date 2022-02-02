#ifndef PIGS_ON_THE_MOON_LIGHTTANK_H
#define PIGS_ON_THE_MOON_LIGHTTANK_H

#include "vehicle.h"

class LightTank : public Vehicle {

    virtual std::vector<Point> GetAvailableMovePoints() override;

    virtual std::vector<Point> GetAvailableShootPoints() override;
};


#endif//PIGS_ON_THE_MOON_LIGHTTANK_H
