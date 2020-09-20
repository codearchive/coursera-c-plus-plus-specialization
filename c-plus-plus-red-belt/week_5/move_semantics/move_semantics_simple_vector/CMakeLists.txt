cmake_minimum_required(VERSION 3.5)

project(move_semantics_simple_vector LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(move_semantics_simple_vector main.cpp profile.h simple_vector.h test_runner.h)
