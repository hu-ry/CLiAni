cmake_minimum_required(VERSION 3.7.2) # cmake 3.7.2 (don't change)
project(cliAnimation)

SET(CMAKE_CXX_STANDARD 14)
SET(CMAKE_INCLUDE_CURRENT_DIR ON)
SET(CMAKE_CXX_FLAGS "-O0 -Wall -pthread -fcheck-new -g ")

SET(CMAKE_CXX_FLAGS  "${CMAKE_CXX_FLAGS} ")
SET(CMAKE_EXE_LINKER_FLAGS  "${CMAKE_EXE_LINKER_FLAGS} ")

# File Globbing
file (GLOB_RECURSE sources src/*.cpp)
file (GLOB_RECURSE includes include/*.h)
file (GLOB_RECURSE tests test/*.cpp)

## Model
file (GLOB_RECURSE model_sources_and_main src/model/*.cpp)
file (GLOB_RECURSE model_includes include/model/*.h)
file (GLOB_RECURSE model_tests test/model/*.cpp)

file (GLOB_RECURSE model_sources src/model/*.cpp)
list (REMOVE_ITEM model_sources
        ${CMAKE_CURRENT_SOURCE_DIR}/src/model/main.cpp)

## View
file (GLOB_RECURSE view_sources_and_main src/view/*.cpp)
file (GLOB_RECURSE view_includes include/view/*.h)
file (GLOB_RECURSE view_tests test/view/*.cpp)

file (GLOB_RECURSE view_sources src/view/*.cpp)
list (REMOVE_ITEM view_sources
        ${CMAKE_CURRENT_SOURCE_DIR}/src/view/main.cpp)

## Controller
SET(controller_sources src/widdershins.cpp)
SET(controller_includes include/widdershins.h)

## Utilz
file (GLOB_RECURSE utilz_sources src/utilz/*.cpp)
file (GLOB_RECURSE utilz_includes include/utilz/*.h)
file (GLOB_RECURSE utilz_tests test/utilz/*.cpp)
    #### No main ####

## Clani
SET(clanimain src/main.cpp)

# Dependencies
## BOOST::TEST
find_package(Boost 1.72 COMPONENTS unit_test_framework REQUIRED)

## Ncurses
find_library(ncurses COMPONENTS menu REQUIRED)

# Finalize Targets

## Model Module
add_executable (model
        ${model_sources_and_main}
        ${utilz_sources}
        )
target_include_directories(model PUBLIC
        include
        include/model
        )
target_link_libraries(model ) # none needed

## View Module
add_executable(view
        ${view_sources_and_main}
        ${utilz_sources}
        )
target_include_directories(view PUBLIC
        include
        include/view
        )
target_link_libraries(view ncurses menu)

## Clani - Full Program
add_executable(clani
        ${clanimain}
        ${model_sources}
        ${view_sources}
        ${controller_sources}
        ${utilz_sources}
        )
target_include_directories(clani PUBLIC
        include
        include/model
        include/view
        include/utilz
        )
target_link_libraries(clani ncurses menu)

# Tests using Boost

## Model Tests
foreach (testsrc ${model_tests})
    get_filename_component(testName ${testsrc} NAME_WE)
    add_executable(${testName} ${testsrc}
            ${model_sources}
            ${utilz_sources})
    target_link_libraries(${testName} ${Boost_LIBRARIES})
    target_include_directories(${testName} PUBLIC
            include
            include/model)
    set_target_properties(${testName} PROPERTIES RUNTIME_OUTPUT_DIRECTORY
            ${CMAKE_CURRENT_BINARY_DIR}/bintest)
    add_test(NAME ${testName}
            WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/bintest
            COMMAND ${CMAKE_CURRENT_BINARY_DIR}/bintest/${testName}
            )
endforeach(testsrc)

## View Tests
foreach (testsrc ${view_tests})
    get_filename_component(testName ${testsrc} NAME_WE)
    add_executable(${testName} ${testsrc}
            ${view_sources}
            ${utilz_sources})
    target_link_libraries(${testName} ${Boost_LIBRARIES} ncurses menu)
    target_include_directories(${testName} PUBLIC
            include
            include/view)
    set_target_properties(${testName} PROPERTIES RUNTIME_OUTPUT_DIRECTORY
            ${CMAKE_CURRENT_BINARY_DIR}/bintest)
    add_test(NAME ${testName}
            WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/bintest
            COMMAND ${CMAKE_CURRENT_BINARY_DIR}/bintest/${testName}
            )
endforeach(testsrc)

## Utilz Tests
foreach (testsrc ${utilz_tests})
    get_filename_component(testName ${testsrc} NAME_WE)
    add_executable(${testName} ${testsrc}
            ${utilz_sources})
    target_link_libraries(${testName} ${Boost_LIBRARIES})
            target_include_directories(${testName} PUBLIC
            include/utilz)
    set_target_properties(${testName} PROPERTIES RUNTIME_OUTPUT_DIRECTORY
            ${CMAKE_CURRENT_BINARY_DIR}/bintest)
    add_test(NAME ${testName}
            WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/bintest
            COMMAND ${CMAKE_CURRENT_BINARY_DIR}/bintest/${testName}
            )
endforeach(testsrc)

enable_testing()
