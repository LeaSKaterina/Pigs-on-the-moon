#pragma once

#include "vehicle.h"

class AtSpg : public Vehicle {
public:
    explicit AtSpg(Hex *spawn, int playerId) : Vehicle(spawn, playerId, 2, 1){};

    bool IsAvailableToShoot(const Point3D &point3D) override;

    [[nodiscard]] Action PriorityAction() const override { return Action::SHOOT; }

    [[nodiscard]] VehiclesTypes::Type GetType() const override { return VehiclesTypes::AT_SPG; }

    Point3D Shoot(Vehicle &enemy) override;
};
