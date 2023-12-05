cmake_minimum_required(VERSION 3.23.2)
project(ece309_spr23_streetmap)

set(CMAKE_CXX_STANDARD 17)

add_subdirectory(gtest)
add_executable(ece309_spr23_streetmap main.cpp Node.cpp Way.cpp StreetMap.cpp HashTable.h Graph.h)
