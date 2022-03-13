#include "game.h"

using namespace std;
using namespace VehiclesTypes;

Game::~Game() {
    delete player;
    delete map;
    for (auto &vehicle : vehicles) {
        for (auto v : vehicle) {
            delete v;
        }
    }
}

Game::Game(int playerId, std::string name, std::string password, bool isObserver, int playersNum,
           const nlohmann::ordered_json &mapInfo) {
    player = new Player(playerId, std::move(name), std::move(password), isObserver);
    InitVariables(playersNum);
    InitMap(mapInfo);
}

// Init methods

void Game::InitVariables(int playersNum) {
    numPlayers = playersNum;

    vehicles.resize(playersNum);
    attackMatrix.resize(playersNum);
    for (auto &v : attackMatrix)
        v.resize(playersNum);
    captures.resize(playersNum);
    kills.resize(playersNum);
    tanksIdAdapter.resize(numPlayerVehicles);
}

void Game::InitMap(const nlohmann::json &mapInfo) {
    // Map
    int size = mapInfo.value("size", -1);
    map = new Map(size);

#ifdef _DEBUG
    cout << "Map request:\n"
         << mapInfo << "\n:Map request" << endl;
#endif

    InitSpawns(mapInfo.value("spawn_points", nlohmann::ordered_json("")));

    InitContent(mapInfo.value("content", nlohmann::ordered_json("")));
}

void Game::InitContent(const nlohmann::ordered_json &contentInfo) {
    for (int i = 0; i < ConstructionsTypes::typesNum; i++) {
        auto cInfo = contentInfo
                             .value(
                                     ConstructionsTypes::sTypes[i],
                                     nlohmann::ordered_json(""));
        vector<Point3D> basePoints;
        for (auto &point : cInfo) {
            basePoints.push_back(MakePosTuple(point));
        }
        map->AddConstruction(ConstructionsTypes::Type(i), basePoints);
    }
}

void Game::InitSpawns(const nlohmann::ordered_json &spawnInfo) {
    int index = 0;
    for (auto &playerInfo : spawnInfo.items()) {
        for (int i = 0; i < VehiclesTypes::typesNum; i++) {
            const auto &type = VehiclesTypes::sTypes[i];
            auto spawns = playerInfo.value().value(type, nlohmann::ordered_json(""));
            for (auto &spawn : spawns.items()) {
                auto &point = spawn.value();
                AddVehicle(index,
                           VehiclesTypes::Type(i),
                           MakePosTuple(point));
            }
        }
        index++;
    }
}

void Game::InitIds(const nlohmann::ordered_json &state) {
    // players id
    InitPlayersIds(state.value("attack_matrix", nlohmann::ordered_json("")));

    // vehicle id
    InitVehiclesIdsTest(state.value("vehicles", nlohmann::ordered_json("")));
}

void Game::InitPlayersIds(const nlohmann::ordered_json &am) {
    // TODO!
    vector<int> realIds;
    for (auto &pm : am.items()) {
        realIds.push_back(stoi(pm.key()));
    }
    InitPlayersId(realIds);
}

void Game::InitPlayersId(const vector<int> &realId) {
    for (int i = 0; i < realId.size(); i++) {
        playersIdAdapter[realId[i]] = i;
    }
}

void Game::InitVehiclesIdsTest(const nlohmann::ordered_json &veh) {
    // observer has no own vehicles
    if (player->IsObserver()) return;

    unordered_map<string, vector<int>> vehiclesIds;
    int counter = 0;
    for (auto &v : veh.items()) {
        auto &vehicleInfo = v.value();
        // search for our player
        int playerId = vehicleInfo.value("player_id", -1);
        if (playerId != player->GetId())
            continue;
        // process only player's vehicles
        int vehicleId = stoi(v.key());
        string vehicleType = vehicleInfo.value("vehicle_type", "unknown");
        vehiclesIds[vehicleType].push_back(vehicleId);
        counter++;

        // when we find all player vehicles, just go out
        if (counter == numPlayerVehicles) break;
    }

    InitVehiclesIdsTest(vehiclesIds);
}

void Game::InitVehiclesIdsTest(const unordered_map<std::string, vector<int>> &realId) {
    int next = 0;
    for (int i = 0; i < VehiclesTypes::typesNum; i++) {
        auto &tanks = realId.at(VehiclesTypes::sTypes[i]);
        for (const auto &id : tanks) {
            tanksIdAdapter[next++] = id;
        }
    }
}

// Add methods

void Game::AddVehicle(int playerId, Type type, Point3D spawn) {
    // there choose type of tanks
    Vehicle *t;
    switch (type) {
        case MEDIUM_TANK:
            t = new MediumTank(playerId);
            break;
        case LIGHT_TANK:
            t = new LightTank(playerId);
            break;
        case HEAVY_TANK:
            t = new HeavyTank(playerId);
            break;
        case AT_SPG:
            t = new AtSpg(playerId);
            break;
        case SPG:
            t = new Spg(playerId);
    }
    t->InitSpawn(map->GetHexByPoint(spawn));
    vehicles[playerId].push_back(t);// there player id passed from 0 to 2 (GameClient)
}

// Update methods

void Game::UpdateState(int currPlayer, bool finished) {
    currentPlayerId = currPlayer;
    isFinished = finished;
}

void Game::UpdateVehicleState(int parentId, Point3D spawn, Point3D pos, int health,
                              int capturePoints) {
    Vehicle *v = FindVehicle(playersIdAdapter.at(parentId), spawn);
    v->Update(health, map->GetHexByPoint(pos), capturePoints);
}

void Game::UpdateWinPoints(int playerId, int capture, int kill) {
    int adaptedPlayerId = playersIdAdapter.at(playerId);
    captures[adaptedPlayerId] = capture;
    kills[adaptedPlayerId] = kill;
}

void Game::UpdateAttackMatrix(int playerId, const std::vector<int> &attacked) {
    int customId = playersIdAdapter.at(playerId);
    for (int i = 0; i < numPlayers; i++) {
        attackMatrix[customId][i] = false;
    }

    for (const int &i : attacked) {
        attackMatrix[customId][playersIdAdapter.at(i)] = true;
    }
}

void Game::UpdateGameState(const nlohmann::ordered_json &state) {
    // attack matrix
    UpdateAttackMatrix(state.value("attack_matrix", nlohmann::ordered_json("")));

    // current turn | player | finished
    UpdateState(
            state.value("current_player_idx", -1),
            state.value("finished", 0));

    // vehicles
    UpdateVehicles(state.value("vehicles", nlohmann::ordered_json("")));

    // win_points
    UpdateWinPoints(state.value("win_points", nlohmann::ordered_json("")));
}

void Game::UpdateWinPoints(const nlohmann::ordered_json &winPoints) {
    cerr << "DEBUG: " << winPoints << endl;
    for (auto &p : winPoints.items()) {
        auto &winPointsInfo = p.value();
        UpdateWinPoints(
                stoi(p.key()),
                winPointsInfo.value("capture", 0),
                winPointsInfo.value("kill", 0));
    }
}

void Game::UpdateAttackMatrix(const nlohmann::ordered_json &am) {
    for (auto &pm : am.items()) {
        vector<int> vAttacked;
        for (int i : pm.value()) {
            vAttacked.push_back(i);
        }
        UpdateAttackMatrix(stoi(pm.key()), vAttacked);
    }
}

void Game::UpdateVehicles(const nlohmann::ordered_json &veh) {
    for (auto &v : veh.items()) {
        auto &vehicleInfo = v.value();

        auto pos = MakePosTuple(
                vehicleInfo.value("position", nlohmann::ordered_json("")));
        auto spawnPos = MakePosTuple(
                vehicleInfo.value("spawn_position", nlohmann::ordered_json("")));
        UpdateVehicleState(
                vehicleInfo.value("player_id", -1),
                spawnPos,
                pos,
                vehicleInfo.value("health", -1),
                vehicleInfo.value("capture_points", -1));
        // TODO? mb ref in uvs;
    }
}

// Getters

const std::vector<Vehicle *> &Game::GetVehicles(int playerId, bool adapted) const {
    return vehicles[(adapted ? playerId : playersIdAdapter.at(playerId))];
}

Point3D Game::MakePosTuple(const nlohmann::json &coordinate) {
    return {coordinate.value("x", -1),
            coordinate.value("y", -1),
            coordinate.value("z", -1)};
}

Vehicle *Game::FindVehicle(int adaptedPlayerId, const Point3D &spawn) const {
    for (auto *p : vehicles[adaptedPlayerId]) {
        if (p->GetSpawn() == spawn)
            return p;
    }
    return nullptr;
}