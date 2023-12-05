cmake_minimum_required(VERSION 3.23)
project(Zybooks_13_23)

set(CMAKE_CXX_STANDARD 17)

add_subdirectory(gtest)

add_executable(Zybooks_13_23 main.cpp MinHeap.h)
