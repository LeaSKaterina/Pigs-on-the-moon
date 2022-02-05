#ifndef PIGS_ON_THE_MOON_VEHICLE_H
#define PIGS_ON_THE_MOON_VEHICLE_H

#include "../../map/hex.h"
#include "../../enums/action.h"
#include <map>
#include <vector>

class Vehicle {
public:
    Vehicle (int ownerId, int hp, int speed, int damage_ = 1)
        : playerId(ownerId),
          damage(damage_),
          health(hp),
          speedPoints(speed),
          destructionPoints(hp) {}

    bool Move(Hex *newPos);

    std::multimap<int, Point> GetAvailableMovePoints(Point target);

    virtual bool IsAvailableForShoot(Vehicle *enemy) = 0;

    virtual Action PriorityAction() const = 0;

    int Shoot(Vehicle *v);

    void IncCapture() { capturePoints++; }

    void DropCapture() { capturePoints = 0; }

    void Update(int health, Hex *newPos, int capture);

    [[nodiscard]] int GetPlayerId() const { return playerId; }

    [[nodiscard]] const Point &GetSpawn() const { return spawnPosition->GetCoordinates(); }

    [[nodiscard]] const Point &GetCurrentPosition() const { return currentPosition->GetCoordinates(); }

    int GetHp() const { return health; }

    bool IsAlive() const { return health > 0; }

    void InitSpawn(Hex *p);

    void Respawn();

    int GetHit(int damage = 1);

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
};


#endif//PIGS_ON_THE_MOON_VEHICLE_H
