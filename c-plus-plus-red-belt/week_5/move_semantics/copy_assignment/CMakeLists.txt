cmake_minimum_required(VERSION 3.5)

project(copy_assignment LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(copy_assignment main.cpp profile.h simple_vector.h test_runner.h)
