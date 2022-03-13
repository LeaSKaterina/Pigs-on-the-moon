#pragma once

#include "vehicle.h"

class LightTank : public Vehicle {
public:
    explicit LightTank(Hex *spawn, int playerId) : Vehicle(spawn, playerId, 1, 3){};

    bool IsAvailableForShoot(Vehicle *enemy) override;

    [[nodiscard]] Action PriorityAction() const override { return Action::SHOOT; }

    [[nodiscard]] VehiclesTypes::Type GetType() const override { return VehiclesTypes::Type::LIGHT_TANK; }
};
