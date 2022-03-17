#pragma once

#include "behaviortree_cpp_v3/bt_factory.h"
#include "game/game.h"
#include <tuple>

class AIPlayer;
class AIClient;

class AIBehaviorTree {
public:
    explicit AIBehaviorTree(const AIPlayer *p);

    void Init();

    BT::NodeStatus SimpleMoveToTarget(const Point3D &targetPoint);

    BT::NodeStatus SimpleMoveToBase();

    std::vector<Point3D> GetPointsToRun();

    BT::NodeStatus SimpleMoveFromDanger();

    BT::NodeStatus SimpleShoot();

    BT::NodeStatus NeedToRun();

    std::vector<std::tuple<Action, int, Point3D>> GetActionsToServer();

    void ProcessAllTanks();

private:
    AIClient *aiClient;
    const AIPlayer *player;
    const Game *game;
    BT::Tree tree;

    //shared data between tree nodes
    const std::vector<std::unique_ptr<Vehicle>> *playerVehicles;
    Vehicle *currentVehicle;
    int currentVehicleId = 0;
    std::queue<std::tuple<Action, int, Point3D>> actions;// Action = Move | SHOOT, int = tankId, point = point
};
