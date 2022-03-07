#pragma once

#include "vehicle.h"

class AtSpg : public Vehicle {
public:
    explicit AtSpg(int playerId) : Vehicle(playerId, 2, 1){};

    bool IsAvailableForShoot(Vehicle *enemy) override;

    [[nodiscard]] Action PriorityAction() const override { return Action::SHOOT; }

    [[nodiscard]] VehiclesTypes::Type GetType() const override {return VehiclesTypes::Type::SPG; }

    Point3D Shoot(Vehicle *enemy) override;
};
