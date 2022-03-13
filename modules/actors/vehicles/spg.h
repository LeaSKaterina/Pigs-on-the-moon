#pragma once

#include "vehicle.h"

class Spg : public Vehicle {
public:
    explicit Spg(Hex *spawn, int playerId) : Vehicle(spawn, playerId, 1, 1){};

    bool IsAvailableToShoot(const Point3D &point3D) override;

    [[nodiscard]] Action PriorityAction() const override { return Action::SHOOT; }

    [[nodiscard]] VehiclesTypes::Type GetType() const override { return VehiclesTypes::Type::SPG; }
};
