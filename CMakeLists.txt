cmake_minimum_required(VERSION 2.8)

project(ml2048)

set(CMAKE_C_COMPILER "gcc")
set(CMAKE_CXX_COMPILER "g++")
set(CMAKE_CXX_FLAGS "-std=c++11 ${CMAKE_CXX_FLAGS} -g")

add_executable(game game.cpp)
add_executable(speed speed.cpp)
add_executable(basic basic.cpp)
add_executable(ga ga.cpp)
add_library(grid utils.cpp grid.cpp)

target_link_libraries(game grid)
target_link_libraries(speed grid)
target_link_libraries(basic grid)
target_link_libraries(ga grid)
