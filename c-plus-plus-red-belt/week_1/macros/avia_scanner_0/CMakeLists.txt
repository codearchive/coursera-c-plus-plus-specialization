cmake_minimum_required(VERSION 3.5)

project(avia_scanner_0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(avia_scanner_0 main.cpp airline_ticket.h test_runner.h)
