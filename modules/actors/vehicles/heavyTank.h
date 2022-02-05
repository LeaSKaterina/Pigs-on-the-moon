#pragma once

#include "vehicle.h"

class HeavyTank : public Vehicle {
public:
    explicit HeavyTank(int playerId) : Vehicle(playerId, 3, 1) {};

    bool IsAvailableForShoot(Vehicle *enemy) override;

    Action PriorityAction() const override { return Action::MOVE; }
};

