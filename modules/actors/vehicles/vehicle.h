#ifndef PIGS_ON_THE_MOON_VEHICLE_H
#define PIGS_ON_THE_MOON_VEHICLE_H

#pragma once

#include "../../enums/vehicle_types.h"
#include "../../map/hex.h"
#include <vector>

class Vehicle {
public:
    Vehicle(VehiclesTypes::Type type, int playerId);

    bool Move(Hex *newPos);

    virtual std::vector<Point> GetAvailableMovePoints() = 0;

    virtual std::vector<bool> IsAvailableForShoot(const std::vector<Point> &points) = 0;

    int Shoot(Vehicle *v);

    void IncCapture() { capturePoints++; }

    void DropCapture() { capturePoints = 0; }

    void Update(int health, Hex *newPos, int capture);

    int GetPlayerId() const { return playerId; }

    [[nodiscard]] const Point &GetSpawn() const { return spawnPosition->GetCoordinates(); }

    [[nodiscard]] const Point &GetCurrentPosition() const { return currentPosition->GetCoordinates(); }

    void InitSpawn(Hex *p);

    void Respawn();

private:
    int playerId;
    int health;
    int destructionPoints;
    int rangeOfShooting;
    int speedPoints;
    int damage = 1;
    int capturePoints = 0;
    Hex *spawnPosition = nullptr;
    Hex *currentPosition = nullptr;
    VehiclesTypes::Type type;

    int GetHit(int damage = 1);

    bool IsEnemy(Vehicle *v) const { return this->playerId != v->playerId; }
};


#endif//PIGS_ON_THE_MOON_VEHICLE_H
