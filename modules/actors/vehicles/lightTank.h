#ifndef PIGS_ON_THE_MOON_LIGHTTANK_H
#define PIGS_ON_THE_MOON_LIGHTTANK_H

#include "vehicle.h"

class LightTank : public Vehicle {

public:
    LightTank(VehiclesTypes::Type type, int playerId) : Vehicle(type, playerId){};

    std::vector<Point> GetAvailableMovePoints() override;

    std::vector<bool> IsAvailableForShoot(const std::vector<Point>& points) override;
};


#endif//PIGS_ON_THE_MOON_LIGHTTANK_H
