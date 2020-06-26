cmake_minimum_required(VERSION 3.5)

project(macros_log LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(macros_log main.cpp logger.h logger.cpp test_runner.h)
