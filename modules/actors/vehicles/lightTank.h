#pragma once

#include "vehicle.h"

class LightTank : public Vehicle {

public:
    explicit LightTank(int playerId) : Vehicle(playerId, 1, 3) {};

    bool IsAvailableForShoot(Vehicle *enemy) override;

    Action PriorityAction() const override { return Action::SHOOT; }

};

