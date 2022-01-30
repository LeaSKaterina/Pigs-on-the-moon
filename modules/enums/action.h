#ifndef PIGS_ON_THE_MOON_ENUMS_ACTION_H
#define PIGS_ON_THE_MOON_ENUMS_ACTION_H

enum class Action {
    LOGIN = 1,
    LOGOUT = 2,
    MAP = 3,
    GAME_STATE = 4,
    GAME_ACTIONS = 5,
    TURN = 6,

    CHAT = 100,
    MOVE = 101,
    SHOOT = 102
};

#endif //PIGS_ON_THE_MOON_ENUMS_ACTION_H