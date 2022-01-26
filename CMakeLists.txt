cmake_minimum_required(VERSION 3.20)
project(Pigs_on_the_moon)

set(CMAKE_CXX_STANDARD 17)


link_libraries(ws2_32)

set(CLIENT
        modules/client/Client.cpp)

include_directories(libs/json-3.10.5/include)

add_executable(Pigs_on_the_moon main.cpp ${CLIENT} )
#target_include_directories(Pigs_on_the_moon PUBLIC include/)
