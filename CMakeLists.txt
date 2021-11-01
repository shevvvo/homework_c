cmake_minimum_required(VERSION 3.20)
project(hw_c C CXX)

set(CMAKE_C_STANDARD 11)
set(CMAKE_CXX_STANDARD 17)

set(CMAKE_C_FLAGS  "${CMAKE_C_FLAGS} ${GCC_COVERAGE_COMPILE_FLAGS} -Wall -Wpedantic -Werror --coverage  ")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wpedantic -Werror  --coverage ")

add_library(input STATIC src/input.c)
target_include_directories(input PUBLIC include)

add_library(static_work STATIC src/static.c)
target_include_directories(static_work PUBLIC include)
target_link_libraries(static_work PUBLIC input)

add_library(dynamic SHARED src/dynamic.c)
target_include_directories(dynamic PUBLIC include)
target_link_libraries(dynamic PUBLIC input)

set(THREADS_PREFER_PTHREAD_FLAG ON)
find_package(Threads REQUIRED)

add_executable(hw_c src/main.c)

if(dynamic)
    message("dynamic")
    target_link_libraries(hw_c Threads::Threads dynamic gcov)
else()
    message("static_work")
    target_link_libraries(hw_c static_work gcov)
endif(dynamic)

find_package(GTest REQUIRED)

add_executable(test_input tests/input_test.cpp)
target_link_libraries(test_input GTest::gtest input gcov)

add_executable(test_static tests/static_test.cpp)
target_link_libraries(test_static GTest::gtest static_work input gcov)

add_executable(test_dynamic tests/dynamic_test.cpp)
target_link_libraries(test_dynamic GTest::gtest dynamic input gcov)