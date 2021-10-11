cmake_minimum_required(VERSION 3.20)
project(hw1 C CXX)

set(CMAKE_C_STANDARD 99)
set(CMAKE_CXX_STANDARD 17)

add_compile_options("--coverage")
add_link_options("--coverage")

add_library(minor STATIC project/minor_matrix.c)
target_include_directories(minor PUBLIC project)

add_executable(hw1 project/main.c)
target_link_libraries(hw1 minor)

find_package(GTest REQUIRED)
set(SOURCES tests/minor_matrix_test.cpp)
add_executable(runTests ${SOURCES})
target_link_libraries(runTests GTest::gtest minor)