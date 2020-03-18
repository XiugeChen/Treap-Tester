cmake_minimum_required(VERSION 3.15)
project(TreapTester)

include_directories(
    include
)

set(CMAKE_CXX_STANDARD 14)

add_executable(TreapTester
    src/main.cpp
    src/data_generator.cpp
)