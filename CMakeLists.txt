cmake_minimum_required(VERSION 3.20)
project(Pigs_on_the_moon)

set(CMAKE_CXX_STANDARD 17)

link_libraries(ws2_32)

set(CLIENT modules/client/Client.cpp)
set(ACTORS modules/actors/player.cpp modules/actors/vehicle.cpp)
set(CONSTRUCTIONS modules/constructions/construction.cpp modules/constructions/base.cpp)
set(MAP modules/map/map.cpp modules/map/hex.cpp)
set(GAME modules/game.cpp)

include_directories(libs/json-3.10.5/include)

add_executable(Pigs_on_the_moon main.cpp ${CLIENT} ${ACTORS} ${CONSTRUCTIONS} ${MAP} ${GAME})
