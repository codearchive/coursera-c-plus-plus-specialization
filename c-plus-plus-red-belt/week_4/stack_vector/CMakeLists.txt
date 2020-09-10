cmake_minimum_required(VERSION 3.5)

project(stack_vector LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(stack_vector main.cpp profile.h test_runner.h stack_vector.h)
