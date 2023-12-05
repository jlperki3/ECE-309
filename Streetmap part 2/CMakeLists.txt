cmake_minimum_required(VERSION 3.23.2)
project(Project_1_part_2)

set(CMAKE_CXX_STANDARD 17)

add_subdirectory(gtest)
add_executable(ece309_spr23_streetmap main.cpp Node.cpp Way.cpp StreetMap.cpp)
