#ifndef PIGS_ON_THE_MOON_ATSPG_H
#define PIGS_ON_THE_MOON_ATSPG_H

#include "vehicle.h"

class AtSpg : public Vehicle {
    virtual std::vector<Point> GetAvailableMovePoints() override;

    virtual std::vector<Point> GetAvailableShootPoints() override;
};


#endif//PIGS_ON_THE_MOON_ATSPG_H
