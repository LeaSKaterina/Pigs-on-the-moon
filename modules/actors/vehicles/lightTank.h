#ifndef PIGS_ON_THE_MOON_LIGHTTANK_H
#define PIGS_ON_THE_MOON_LIGHTTANK_H

#include "vehicle.h"

class LightTank : public Vehicle {

public:
    explicit LightTank(int playerId) : Vehicle(playerId, 1, 3){};

    bool IsAvailableForShoot(Vehicle *enemy) override;

    Action PriorityAction() const override {return Action::SHOOT;}

};


#endif//PIGS_ON_THE_MOON_LIGHTTANK_H
