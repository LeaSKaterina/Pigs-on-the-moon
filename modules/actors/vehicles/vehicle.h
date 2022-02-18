#pragma once

#include "enums/action.h"
#include "map/hex.h"
#include <map>
#include <vector>
#include <algorithm>

class Vehicle {
public:
    Vehicle(int ownerId, int hp, int speed, int damage = 1)
        : playerId(ownerId),
          damage(damage),
          health(hp),
          speedPoints(speed),
          destructionPoints(hp) {}

    void InitSpawn(Hex *p);

    virtual ~Vehicle() = default;

    //based on the minimum path form point(Hex) available to move most priority. Consider hex.IsEmpty
    //minPath = currentPosition -> neighbor -> neighbor -> ...
    Hex *GetAvailableMovePoint(const std::vector<Hex *> &minPath);

    virtual bool IsAvailableForShoot(Vehicle *enemy) = 0;

    virtual Point3D Shoot(Vehicle *enemy) { return enemy->GetCurrentPosition(); };

    // getters

    [[nodiscard]] int GetPlayerId() const { return playerId; }

    [[nodiscard]] const Point3D &GetSpawn() const { return spawnPosition->GetCoordinates(); }

    [[nodiscard]] const Point3D &GetCurrentPosition() const { return currentPosition->GetCoordinates(); }

    Hex *GetCurrentHex() const {return currentPosition;}

    [[nodiscard]] int GetHp() const { return health; }

    [[nodiscard]] bool IsAlive() const { return health > 0; }

    [[nodiscard]] virtual Action PriorityAction() const = 0;

    std::vector<Point3D> PriorityMoveTriangle(const Point3D &&target);

    // mods

    void Respawn();

    int GetHit(int damage = 1);

    void IncCapture() { capturePoints++; }

    void DropCapture() { capturePoints = 0; }

    void Update(int health, Hex *newPos, int capture);

    bool Move(Hex *newPos);

private:
    const int playerId;
    int health;
    const int destructionPoints;
    const int speedPoints;
    const int damage;
    int capturePoints = 0;
    Hex *spawnPosition = nullptr;
    Hex *currentPosition = nullptr;

    bool IsEnemy(Vehicle *v) const { return this->playerId != v->playerId; }
    static bool IsBetweenCoo(int coo, int first, int second);
};
