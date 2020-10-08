cmake_minimum_required(VERSION 3.5)

project(final_2_sync LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(final_2_sync iterator_range.h main.cpp parse.cpp parse.h
    profile.h search_server.cpp search_server.h synchronized.h test_runner.h tests.h)
