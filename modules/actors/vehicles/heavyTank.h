#ifndef PIGS_ON_THE_MOON_HEAVYTANK_H
#define PIGS_ON_THE_MOON_HEAVYTANK_H

#include "vehicle.h"

class HeavyTank : public Vehicle {
public:
    explicit HeavyTank(int playerId) : Vehicle(playerId, 3, 1) {};

    bool IsAvailableForShoot(Vehicle *enemy) override;

    Action PriorityAction() const override {return Action::MOVE;}
};


#endif//PIGS_ON_THE_MOON_HEAVYTANK_H
