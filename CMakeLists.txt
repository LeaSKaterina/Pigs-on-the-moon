cmake_minimum_required(VERSION 3.20)
project(Pigs_on_the_moon)

set(CMAKE_CXX_STANDARD 17)


link_libraries(ws2_32)

set(CLIENT
        modules/client/Client.cpp)

add_executable(Pigs_on_the_moon main.cpp ${CLIENT})
