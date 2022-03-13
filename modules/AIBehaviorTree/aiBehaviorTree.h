#pragma once

#include "behaviortree_cpp_v3/bt_factory.h"
#include "game/game.h"
#include "AI/AIClient.h"
#include <tuple>

class AIBehaviorTree {
public:
    AIBehaviorTree() {
        BT::BehaviorTreeFactory factory;

        factory.registerSimpleAction("SimpleMoveGripper", std::bind (&AIBehaviorTree::SimpleMove, this));

        factory.registerSimpleAction("SimpleShootGripper", std::bind (&AIBehaviorTree::SimpleShoot, this));

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
        const auto &playerVehicles = game->GetVehicles(game->GetAdaptedPlayerId());
        std::vector<Hex*> path = game->GetMap()->GetShortestWay(*playerVehicles[currentVehicleId]->GetCurrentHex(), *game->GetMap()->GetHexByPoint(targetPoint));
        for (auto hex : path){
            std::cout<<hex->GetCoordinates().ToString()<<", ";
        }
        std::cout<<std::endl;
        auto hex = currentVehicle->GetAvailableMovePoint(path);
        if (hex != nullptr){
            currentVehicle->GetCurrentHex()->Free();
            actions.push(std::make_tuple(Action::MOVE, game->GetPlayer()->GetServerIdForTank(currentVehicleId), hex->GetCoordinates()));
            std::cout<<currentVehicle->GetCurrentPosition().ToString()<<" :: "<<hex->GetCoordinates().ToString()<<std::endl;
            hex->Occupy();
            return BT::NodeStatus::SUCCESS;
        }
        return BT::NodeStatus::FAILURE;
    }

    BT::NodeStatus SimpleShoot(){
        std::unordered_map<Vehicle *, std::vector<Vehicle *>> priorityShootTargets =
                std::move(aiClient->GetAIPlayer()->GetPointsForShoot(game->GetAdaptedPlayerId()));
        if (!priorityShootTargets[currentVehicle].empty()) {
            // TODO: priority.
            for (auto *vToAttack : priorityShootTargets.at(currentVehicle)) {
                if (vToAttack->IsAlive()) {
                    vToAttack->GetHit();
                    actions.push(std::make_tuple(Action::SHOOT, game->GetPlayer()->GetServerIdForTank(currentVehicleId), vToAttack->GetCurrentPosition()));
                    break;
                }
            }
        }
        return BT::NodeStatus::SUCCESS;
    }


    void ProcessAllTanks(){
        for (auto vehicle : *playerVehicles){
            currentVehicle = vehicle;
            this->tree.tickRoot();
            currentVehicleId++;
        }
        SendActionsToServer();
    }

    void SendActionsToServer(){
        std::vector<std::tuple<Action, int, Point3D>> actionsVector;
        while(!actions.empty()){
            actionsVector.push_back(actions.front());
            actions.pop();
        }

        aiClient->GameClient::SendAction(actionsVector);
        currentVehicleId = 0;
    }

private:
    AIClient *aiClient;
    Game *game;
    BT::Tree tree;


    //shared data between tree nodes
    const std::vector<Vehicle *> *playerVehicles;
    Vehicle *currentVehicle;
    int currentVehicleId = 0;
    std::queue<std::tuple<Action, int, Point3D>> actions;// Action = Move | SHOOT, int = tankId, point = point


};

