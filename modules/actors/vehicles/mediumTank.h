#ifndef PIGS_ON_THE_MOON_MEDIUMTANK_H
#define PIGS_ON_THE_MOON_MEDIUMTANK_H

#include "vehicle.h"

class MediumTank : public Vehicle {
public:
    MediumTank(VehiclesTypes::Type type, int playerId) : Vehicle(type, playerId) {};

    std::vector<Point> GetAvailableMovePoints() override;

    std::vector<bool> IsAvailableForShoot(const std::vector<Point>& points) override;
};


#endif//PIGS_ON_THE_MOON_MEDIUMTANK_H