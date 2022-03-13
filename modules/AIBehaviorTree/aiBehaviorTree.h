#pragma once

#include "AI/AIClient.h"
#include "behaviortree_cpp_v3/bt_factory.h"
#include "game/game.h"
#include <tuple>

class AIBehaviorTree {
public:
    AIBehaviorTree() {
        BT::BehaviorTreeFactory factory;

        factory.registerSimpleAction("SimpleShootGripper", std::bind(&AIBehaviorTree::SimpleShoot, this));

        factory.registerSimpleAction("SimpleMoveGripper", std::bind(&AIBehaviorTree::SimpleMove, this));

        tree = factory.createTreeFromFile("./tree.xml");
    }

    void Init(AIClient *aiClient) {
        this->aiClient = aiClient;
        game = aiClient->GetGame();
        playerVehicles = &game->GetVehicles(game->GetAdaptedPlayerId());
    }

    BT::NodeStatus CheckBattery() {
        std::cout << "[ Battery: OK ]" << std::endl;
        return BT::NodeStatus::SUCCESS;
    }

    BT::NodeStatus SimpleMove() {
        Point3D targetPoint{0, 0, 0};
        std::vector<Hex *> oldPath;
        std::vector<Hex *> path;
        std::vector<Hex *> occupiedHexes;
        int minLength = 0;
        int maxAvailableHexIndex;

            path = game->GetMap()->GetShortestWay(*currentVehicle->GetCurrentHex(), *game->GetMap()->GetHexByPoint(targetPoint));
            maxAvailableHexIndex = currentVehicle->GetAvailableMovePoints(path);

            int nextHexIndex = 0;
            for (int i = maxAvailableHexIndex; i > 0; --i) {
                if (path[i]->IsEmpty()) {
                    nextHexIndex = i;
                    break;
                } else {
                    occupiedHexes.push_back(path[i]);
                }
            }



        //        if(!occupiedHexes.empty()){
        oldPath = game->GetMap()->GetShortestWay(*currentVehicle->GetCurrentHex(),
                                                 *game->GetMap()->GetHexByPoint(targetPoint), occupiedHexes);
        //        }

        int availablePathLength2 = currentVehicle->GetAvailableMovePoints(oldPath);
        int nextHexIndex2 = 0;
        for (int i = availablePathLength2; i > 0; --i) {
            if (oldPath[i]->IsEmpty()) {
                nextHexIndex2 = i;
                break;
            } else {
                occupiedHexes.push_back(oldPath[i]);
            }
        }
        if (maxAvailableHexIndex - nextHexIndex > availablePathLength2 - nextHexIndex2) {
            std::swap(path, oldPath);
            nextHexIndex = nextHexIndex2;
        }

        if (nextHexIndex != 0) {
            currentVehicle->GetCurrentHex()->Free();
            actions.push(std::make_tuple(Action::MOVE, game->GetVehicleServerId(currentVehicleId), path[nextHexIndex]->GetCoordinates()));
            std::cout << currentVehicle->GetCurrentPosition().ToString() << " :: " << path[nextHexIndex]->GetCoordinates().ToString() << std::endl;
            path[nextHexIndex]->Occupy();
            return BT::NodeStatus::SUCCESS;
        }

        return BT::NodeStatus::FAILURE;
    }

    BT::NodeStatus SimpleShoot() {
        std::unordered_map<Vehicle *, std::vector<Vehicle *>> priorityShootTargets =
                aiClient->GetAIPlayer()->GetPointsForShoot(game->GetAdaptedPlayerId());
        aiClient->GetAIPlayer()->ProcessAttackPossibility(priorityShootTargets);
        if (!priorityShootTargets[currentVehicle].empty()) {
            // TODO: priority.
            for (auto *vToAttack : priorityShootTargets.at(currentVehicle)) {
                if (vToAttack->IsAlive()) {
                    vToAttack->GetHit();
                    actions.push(std::make_tuple(Action::SHOOT, game->GetVehicleServerId(currentVehicleId), vToAttack->GetCurrentPosition()));
                    return BT::NodeStatus::SUCCESS;
                }
            }
        }
        return BT::NodeStatus::FAILURE;
    }


    void ProcessAllTanks() {
        for (auto vehicle : *playerVehicles) {
            currentVehicle = vehicle;
            this->tree.tickRoot();
            currentVehicleId++;
        }
        SendActionsToServer();
    }

    void SendActionsToServer() {
        std::vector<std::tuple<Action, int, Point3D>> actionsVector;
        while (!actions.empty()) {
            actionsVector.push_back(actions.front());
            actions.pop();
        }

        aiClient->GameClient::SendAction(actionsVector);
        currentVehicleId = 0;
    }

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
