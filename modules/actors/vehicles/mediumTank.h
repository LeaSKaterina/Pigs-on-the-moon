#pragma once

#include "vehicle.h"

class MediumTank : public Vehicle {
public:
    MediumTank(int playerId) : Vehicle(playerId, 2, 2){};

    bool IsAvailableForShoot(Vehicle *enemy) override;

    Action PriorityAction() const override { return Action::MOVE; }
};
