cmake_minimum_required(VERSION 3.20)
project(Pigs_on_the_moon)

set(CMAKE_CXX_STANDARD 17)

set(ConanFolder conanBuild)

include(${CMAKE_CURRENT_SOURCE_DIR}/${ConanFolder}/conanbuildinfo.cmake)
conan_basic_setup()

file(GLOB_RECURSE HEADER_FILES ${CMAKE_CURRENT_SOURCE_DIR}/modules/*.h) #collect all .h files
file(GLOB_RECURSE SOURCE_FILES ${CMAKE_CURRENT_SOURCE_DIR}/modules/*.cpp) #collect all .cpp files

set(SOURCES ${HEADER_FILES} ${SOURCE_FILES})
source_group(TREE ${CMAKE_CURRENT_SOURCE_DIR} FILES ${SOURCES} main.cpp) #save folders tree

add_executable(${PROJECT_NAME} main.cpp ${SOURCES})

target_link_libraries(${PROJECT_NAME} ${CONAN_LIBS})

target_include_directories(${PROJECT_NAME} PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/modules) # need for include project files


#copy dll to bin folder
file(GLOB_RECURSE dlls ${CMAKE_CURRENT_SOURCE_DIR}/${ConanFolder}/bin/*)

configure_file(modules/AIBehaviorTree/tree.xml ${CMAKE_BINARY_DIR}/bin/ COPYONLY)

foreach (dll ${dlls})
    get_filename_component(filename ${dll} NAME)
    configure_file(${dll} ${CMAKE_BINARY_DIR}/bin/${filename} COPYONLY)
endforeach ()

#copy resource files in binary directory (folder with executable file). Save resource path.
file(GLOB_RECURSE resources "modules/gui/resources/*.*")# collect all resources
foreach (resource ${resources})
    get_filename_component(filename ${resource} NAME)
    get_filename_component(dir ${resource} DIRECTORY)
    get_filename_component(dirname ${dir} NAME)

    set(output "")

    while (NOT ${dirname} STREQUAL resources)
        get_filename_component(path_component ${dir} NAME)
        set(output "${path_component}/${output}")
        get_filename_component(dir ${dir} DIRECTORY)
        get_filename_component(dirname ${dir} NAME)
    endwhile ()

    set(output "${CMAKE_CURRENT_BINARY_DIR}/bin/resources/${output}${filename}")
    configure_file(${resource} ${output} COPYONLY)
endforeach ()