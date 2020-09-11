cmake_minimum_required(VERSION 3.5)

project(web_server LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(web_server http_request.h main.cpp stats.h stats.cpp profile.h test_runner.h)
