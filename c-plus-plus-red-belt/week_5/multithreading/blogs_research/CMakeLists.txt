cmake_minimum_required(VERSION 3.5)

project(blogs_research LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(blogs_research main.cpp profile.h test_runner.h)
