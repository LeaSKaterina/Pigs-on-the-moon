#pragma once

#include "AIBehaviorTree/aiBehaviorTree.h"
#include "game/game.h"

class AIPlayer {
public:
    explicit AIPlayer(const Game *game) : game(game) {
        tree = std::make_unique<AIBehaviorTree>(this);
    }

    //private
    [[nodiscard]] std::vector<bool> NeutralityRuleCheck(int playerId) const;

    [[nodiscard]] std::unordered_map<Vehicle *, std::vector<Vehicle *>> GetPointsForShoot(int playerId) const;

    static void ProcessAttackPossibility(std::unordered_map<Vehicle *, std::vector<Vehicle *>> &priorityShootTargets);

    [[nodiscard]] int GetPossibleDamageForPoint(const Point3D &point3D) const;

    [[nodiscard]] bool CanDieOnPoint(const Vehicle &vehicle, const Point3D &point3D) const;

    auto Play() {
        tree->ProcessAllTanks();
        return tree->GetActionsToServer();
    }

    [[nodiscard]] const Game *GetGame() const { return game; }

private:
    const Game *game;
    std::unique_ptr<AIBehaviorTree> tree;
};
