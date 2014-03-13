cmake_minimum_required(VERSION 2.8)

project(ml2048)

set(CMAKE_C_COMPILER "gcc")
set(CMAKE_CXX_COMPILER "g++")
set(CMAKE_CXX_FLAGS "-std=c++11 ${CMAKE_CXX_FLAGS} -g")

add_executable(ml2048 main.cpp)

target_link_libraries(ml2048)
