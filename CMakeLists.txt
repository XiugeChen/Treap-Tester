cmake_minimum_required(VERSION 3.15)
project(TreapTester)

include_directories(
    include
)

include(cmake/utils.cmake)

if(NOT TARGET spdlog)
    # Stand-alone build
    find_package(spdlog REQUIRED)
endif()

set(CMAKE_CXX_STANDARD 20)

add_executable(TreapTester
    src/main.cpp
    src/data_generator.cpp
    src/dummy.cpp
    src/tester.app.cpp
    src/treap.cpp
)

spdlog_enable_warnings(TreapTester)
target_link_libraries(TreapTester PRIVATE spdlog::spdlog)
