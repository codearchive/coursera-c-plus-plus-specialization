cmake_minimum_required(VERSION 3.5)

project(template_synchronized LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(template_synchronized main.cpp profile.h test_runner.h)
