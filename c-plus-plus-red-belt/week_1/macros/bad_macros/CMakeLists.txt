cmake_minimum_required(VERSION 3.5)

project(bad_macros LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(bad_macros main.cpp test_runner.h)
