#ifndef PIGS_ON_THE_MOON_SPG_H
#define PIGS_ON_THE_MOON_SPG_H
#include "vehicle.h"

class Spg : public Vehicle {
public:
    explicit Spg (int playerId) : Vehicle(playerId, 1, 1) {};

    bool IsAvailableForShoot(Vehicle *enemy) override;

    Action PriorityAction() const override {return Action::SHOOT;}
};


#endif//PIGS_ON_THE_MOON_SPG_H