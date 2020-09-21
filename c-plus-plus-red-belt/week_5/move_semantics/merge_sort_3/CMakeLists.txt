cmake_minimum_required(VERSION 3.5)

project(merge_sort_3 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(merge_sort_3 main.cpp profile.h test_runner.h)
