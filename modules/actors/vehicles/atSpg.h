#pragma once

#include "vehicle.h"

class AtSpg : public Vehicle {
public:
    explicit AtSpg(int playerId) : Vehicle(playerId, 2, 1){};

    bool IsAvailableForShoot(Vehicle *enemy) override;

    Action PriorityAction() const override { return Action::SHOOT; }

    Point Shoot(Vehicle *enemy) override;
};
