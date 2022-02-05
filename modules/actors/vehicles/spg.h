#pragma once

#include "vehicle.h"

class Spg : public Vehicle {
public:
    explicit Spg(int playerId) : Vehicle(playerId, 1, 1) {};

    bool IsAvailableForShoot(Vehicle *enemy) override;

    Action PriorityAction() const override { return Action::SHOOT; }
};

