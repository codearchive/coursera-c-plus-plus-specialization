cmake_minimum_required(VERSION 3.5)

project(text_editor LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(text_editor editor.h editor.cpp main.cpp profile.h test_runner.h)
