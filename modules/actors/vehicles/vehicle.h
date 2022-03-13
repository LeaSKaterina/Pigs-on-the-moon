#pragma once

#include "enums/action.h"
#include "map/hex.h"
#include <algorithm>
#include <map>
#include <vector>

class Vehicle {
public:
    Vehicle(Hex *spawn, int ownerId, int hp, int speed, int damage = 1)
        : playerId(ownerId),
          damage(damage),
          health(hp),
          speedPoints(speed),
          destructionPoints(hp),
          spawnPosition(spawn),
          currentPosition(spawn) {}

    virtual ~Vehicle() = default;

    //based on the minimum path form point(Hex) available to move most priority.
    //minPath = currentPosition -> neighbor -> neighbor -> ...
    int GetAvailableMovePoints(const std::vector<Hex *> &minPath) const;

    virtual bool IsAvailableToShoot(const Point3D &point3D) = 0;

    virtual Point3D Shoot(Vehicle &enemy);

    // getters

    [[nodiscard]] int GetPlayerId() const { return playerId; }

    [[nodiscard]] const Point3D &GetSpawn() const { return spawnPosition->GetCoordinates(); }

    [[nodiscard]] const Point3D &GetCurrentPosition() const { return currentPosition->GetCoordinates(); }

    [[nodiscard]] Hex *GetCurrentHex() const { return currentPosition; }

    [[nodiscard]] int GetHp() const { return health; }

    [[nodiscard]] bool IsAlive() const { return health > 0; }

    [[nodiscard]] virtual Action PriorityAction() const = 0;

    [[nodiscard]] virtual VehiclesTypes::Type GetType() const = 0;

    // mods

    void Respawn();

    int GetHit(int hp = 1);

    void IncCapture() { capturePoints++; }

    void DropCapture() { capturePoints = 0; }

    void Update(int hp, Hex *newPos, int capture);

    bool Move(Hex *newPos);

    void GiveBonus() { hasABonus = true; }

private:
    const int playerId;
    int health;
    const int destructionPoints;
    const int speedPoints;
    const int damage;
    int capturePoints = 0;
    Hex *spawnPosition;
    Hex *currentPosition;

    bool IsEnemy(Vehicle *v) const { return this->playerId != v->playerId; }

protected:
    bool hasABonus = false;
};
