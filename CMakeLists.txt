cmake_minimum_required(VERSION 3.20)
project(Pigs_on_the_moon)

set(CMAKE_CXX_STANDARD 17)

#Debug
#set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -D_DEBUG")
#!Debug

include(./conanBuild/conanbuildinfo.cmake)
conan_basic_setup()
link_libraries(ws2_32)


file(GLOB_RECURSE HEADER_FILES ${CMAKE_CURRENT_SOURCE_DIR}/modules/*.h) #collect all .h files
file(GLOB_RECURSE SOURCE_FILES ${CMAKE_CURRENT_SOURCE_DIR}/modules/*.cpp) #collect all .cpp files

set(SOURCES ${HEADER_FILES} ${SOURCE_FILES})

add_executable(Pigs_on_the_moon main.cpp ${SOURCES})

target_link_libraries(Pigs_on_the_moon ${CONAN_LIBS})