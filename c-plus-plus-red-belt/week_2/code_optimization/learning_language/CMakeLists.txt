cmake_minimum_required(VERSION 3.5)

project(learning_language LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(learning_language main.cpp test_runner.h profile.h learner.h)
