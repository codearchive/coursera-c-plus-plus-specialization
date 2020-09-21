cmake_minimum_required(VERSION 3.5)

project(priority_collection LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(priority_collection main.cpp profile.h test_runner.h)
