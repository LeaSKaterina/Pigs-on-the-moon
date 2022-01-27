//
// Created by Alex on 27.01.2022.
//

#include "game_client.h"

bool GameClient::initGame(const string &name, const string &password, const string &game_name, int num_turns,
                          int num_players, bool is_observer)  {
    auto answer = client->Login(name, password, game_name, num_turns, num_players, is_observer);
    if (answer.result != Result::OKEY)
        return false;

    int id = answer.answer.value("idx", -1);
    game->InitPlayer(id, name, password);

    answer = client->Map();
    if (answer.result != Result::OKEY)
        return false;
    int size = answer.answer.value("size", -1);
    game->InitMap(size);

    return true;
}
