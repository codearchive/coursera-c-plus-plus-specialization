cmake_minimum_required(VERSION 3.5)

project(single_linked_list LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(single_linked_list main.cpp test_runner.h linked_list.h)
