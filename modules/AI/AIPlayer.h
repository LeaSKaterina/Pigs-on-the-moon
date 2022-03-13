#pragma once

#include "game/game.h"

class AIPlayer {
public:
    explicit AIPlayer(Game *game) : game(game) {}
    [[nodiscard]] std::vector<std::tuple<Action, int, Point3D>> Play() const;


    //private
    [[nodiscard]] std::vector<bool> NeutralityRuleCheck(int playerId) const;

    [[nodiscard]] std::unordered_map<Vehicle *, std::vector<Vehicle *>> GetPointsForShoot(int playerId) const;

    static void ProcessAttackPossibility(std::unordered_map<Vehicle *, std::vector<Vehicle *>> &priorityShootTargets);

private:
    Game *game;

    // methods

};
