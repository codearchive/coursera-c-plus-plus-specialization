cmake_minimum_required(VERSION 3.5)

project(airport_counter LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_FLAG -O3)

add_executable(airport_counter airport_counter.h main.cpp profile.h test_runner.h)
