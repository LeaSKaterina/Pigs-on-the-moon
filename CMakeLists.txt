cmake_minimum_required(VERSION 3.20)
project(Pigs_on_the_moon)

set(CMAKE_CXX_STANDARD 17)

#Debug
set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -D_DEBUG")
#!Debug

include(${CMAKE_CURRENT_SOURCE_DIR}/conanBuild/conanbuildinfo.cmake)
conan_basic_setup()
link_libraries(ws2_32)

file(GLOB_RECURSE HEADER_FILES ${CMAKE_CURRENT_SOURCE_DIR}/modules/*.h) #collect all .h files
file(GLOB_RECURSE SOURCE_FILES ${CMAKE_CURRENT_SOURCE_DIR}/modules/*.cpp) #collect all .cpp files

set(SOURCES ${HEADER_FILES} ${SOURCE_FILES})
#source_group(TREE ${CMAKE_CURRENT_SOURCE_DIR} FILES ${SOURCES} main.cpp) #save folders tree
source_group(TREE ${CMAKE_CURRENT_SOURCE_DIR} FILES main.cpp) #save folders tree

add_executable(${PROJECT_NAME} main.cpp ${SOURCES})

target_link_libraries(${PROJECT_NAME} ${CONAN_LIBS})

target_include_directories(${PROJECT_NAME} PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/modules) # need for include project files