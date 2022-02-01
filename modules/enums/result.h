#pragma once

enum class Result {
    OKEY = 0,
    BAD_COMMAND = 1,
    ACCESS_DENIED = 2,
    INAPPROPRIATE_GAME_STATE = 3,
    TIMEOUT = 4,
    INTERNAL_SERVER_ERROR = 500
};
