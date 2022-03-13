#pragma once

#include "behaviortree_cpp_v3/bt_factory.h"
#include "game/game.h"
#include <tuple>

class AIClient;

class AIBehaviorTree {
public:
    AIBehaviorTree();

    void Init(AIClient *aiClient);

    BT::NodeStatus SimpleMoveToTarget(const Point3D &targetPoint);

    BT::NodeStatus SimpleMoveToBase();

    std::vector<Point3D> GetPointsToRun();

    BT::NodeStatus SimpleMoveFromDanger();

    BT::NodeStatus SimpleShoot();

    BT::NodeStatus NeedToRun();

    void ProcessAllTanks();

    void SendActionsToServer();

private:
    AIClient *aiClient;
    const Game *game;
    BT::Tree tree;

    //shared data between tree nodes
    const std::vector<Vehicle *> *playerVehicles;
    Vehicle *currentVehicle;
    int currentVehicleId = 0;
    std::queue<std::tuple<Action, int, Point3D>> actions;// Action = Move | SHOOT, int = tankId, point = point
};
