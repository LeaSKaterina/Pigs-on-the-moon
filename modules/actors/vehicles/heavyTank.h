#pragma once

#include "vehicle.h"

class HeavyTank : public Vehicle {
public:
    explicit HeavyTank(int playerId) : Vehicle(playerId, 3, 1){};

    bool IsAvailableForShoot(Vehicle *enemy) override;

    [[nodiscard]] Action PriorityAction() const override { return Action::MOVE; }

    [[nodiscard]] VehiclesTypes::Type GetType() const override { return VehiclesTypes::HEAVY_TANK; }
};
