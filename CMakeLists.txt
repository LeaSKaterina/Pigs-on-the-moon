cmake_minimum_required(VERSION 3.20)
project(Pigs_on_the_moon)

set(CMAKE_CXX_STANDARD 17)


set(SOURCES modules/actors/player.cpp modules/actors/vehicle.cpp modules/constructions/base.cpp modules/constructions/construction.cpp modules/map/hex.cpp modules/map/map.cpp modules/game.cpp)

add_executable(Pigs_on_the_moon main.cpp ${SOURCES})
