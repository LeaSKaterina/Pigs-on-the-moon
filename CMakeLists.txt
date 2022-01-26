cmake_minimum_required(VERSION 3.20)
project(Pigs_on_the_moon)

set(CMAKE_CXX_STANDARD 17)


set(SOURCES actors/player.cpp actors/vehicle.cpp constructions/base.cpp constructions/construction.cpp map/hex.cpp map/map.cpp game.cpp)

add_executable(Pigs_on_the_moon main.cpp ${SOURCES})
