#pragma once

#include "game/game.h"

class AIPlayer {
public:
    explicit AIPlayer(const Game *game) : game(game) {}

    //private
    [[nodiscard]] std::vector<bool> NeutralityRuleCheck(int playerId) const;

    [[nodiscard]] std::unordered_map<Vehicle *, std::vector<Vehicle *>> GetPointsForShoot(int playerId) const;

    static void ProcessAttackPossibility(std::unordered_map<Vehicle *, std::vector<Vehicle *>> &priorityShootTargets);

    int GetPossibleDamageForPoint(const Point3D &point3D);

    bool CanDieOnPoint(const Vehicle &vehicle, const Point3D &point3D);

private:
    const Game *game;
};
