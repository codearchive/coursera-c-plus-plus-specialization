cmake_minimum_required(VERSION 3.5)

project(final_project_1 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(final_project_1 iterator_range.h main.cpp parse.cpp parse.h
    profile.h search_server.cpp search_server.h test_runner.h)
