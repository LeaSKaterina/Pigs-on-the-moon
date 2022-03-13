#pragma once

#include "vehicle.h"

class MediumTank : public Vehicle {
public:
    explicit MediumTank(Hex *spawn, int playerId) : Vehicle(spawn, playerId, 2, 2){};

    bool IsAvailableToShoot(const Point3D &point3D) override;

    [[nodiscard]] Action PriorityAction() const override { return Action::MOVE; }

    [[nodiscard]] VehiclesTypes::Type GetType() const override { return VehiclesTypes::Type::MEDIUM_TANK; }
};
