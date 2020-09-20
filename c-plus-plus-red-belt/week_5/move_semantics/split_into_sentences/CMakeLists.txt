cmake_minimum_required(VERSION 3.5)

project(split_into_sentences LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(split_into_sentences main.cpp profile.h test_runner.h)
