cmake_minimum_required(VERSION 3.20)
project(Pigs_on_the_moon)

set(CMAKE_CXX_STANDARD 17)

#Debug
#set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -D_DEBUG")
#!Debug

link_libraries(ws2_32)
set(ACTORS modules/actors/player.cpp modules/actors/vehicle.cpp)
set(CLIENT modules/client/client.cpp)
set(CONSTRUCTIONS modules/constructions/construction.cpp modules/constructions/base.cpp)
set(GAMECLIENT modules/gameClient.h modules/gameClient.cpp modules/enums/vehicle_types.h modules/enums/vehicle_types.cpp)
set(GAME modules/game/game.cpp modules/game/actionController.cpp)
set(MAP modules/map/map.cpp modules/map/hex.cpp)

include_directories(libs/json-3.10.5/include)

add_executable(Pigs_on_the_moon main.cpp ${CLIENT} ${ACTORS} ${CONSTRUCTIONS} ${MAP} ${GAME} ${GAMECLIENT})
