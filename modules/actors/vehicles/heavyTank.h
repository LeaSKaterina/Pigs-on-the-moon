#pragma once

#include "vehicle.h"

class HeavyTank : public Vehicle {
public:
    explicit HeavyTank(Hex *spawn, int playerId) : Vehicle(spawn, playerId, 3, 1){};

    bool IsAvailableToShoot(const Point3D &point3D) override;

    [[nodiscard]] Action PriorityAction() const override { return Action::MOVE; }

    [[nodiscard]] VehiclesTypes::Type GetType() const override { return VehiclesTypes::HEAVY_TANK; }
};
