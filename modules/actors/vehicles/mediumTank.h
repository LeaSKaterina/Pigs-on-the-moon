#pragma once

#include "vehicle.h"

class MediumTank : public Vehicle {
public:
    explicit MediumTank(int playerId) : Vehicle(playerId, 2, 2){};

    bool IsAvailableForShoot(Vehicle *enemy) override;

    [[nodiscard]] Action PriorityAction() const override { return Action::MOVE; }

    [[nodiscard]] VehiclesTypes::Type GetType() const override {return VehiclesTypes::Type::SPG; }
};
