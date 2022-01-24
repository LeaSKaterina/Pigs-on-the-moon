cmake_minimum_required(VERSION 3.20)
project(Pigs_on_the_moon)

set(CMAKE_CXX_STANDARD 17)

add_executable(Pigs_on_the_moon main.cpp)

link_libraries(ws2_32)