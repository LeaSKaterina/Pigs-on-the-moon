#ifndef PIGS_ON_THE_MOON_GAMECLIENT_H
#define PIGS_ON_THE_MOON_GAMECLIENT_H

//#include "../libs/json-3.10.5/include/nlohmann/json.hpp"
#include "client/client.h"
#include "game/game.h"
#include "enums/vehicle_types.h"


class GameClient {
public:
    explicit GameClient(bool debug = false);

    // must be called once and first.
    bool InitGame(const std::string& name, const std::string& password = "",
                  const std::string& game_name= "", int num_turns = 0, int num_players = 1,
                  bool is_observer = false);

    [[nodiscard]] bool GameIsFinished() const;

    void CheckGameState();

//    void CheckGameAction();  Do we really need this?

    ~GameClient();

    bool SendTurn() const;

    void SendAction() const;
    void InitPlayersId();

    Client *GetClient() const;

    [[nodiscard]] bool IsPlayTime() const;

private:

    // entities
    Game* game;
    Client* client;

    static std::tuple<int, int, int> MakePosTuple(nlohmann::ordered_json coordinate);

};




#endif //PIGS_ON_THE_MOON_GAMECLIENT_H