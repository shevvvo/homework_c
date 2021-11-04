cmake_minimum_required(VERSION 3.20)
project(hw_c C CXX)

set(CMAKE_C_STANDARD 11)
set(CMAKE_CXX_STANDARD 17)

set(CMAKE_C_FLAGS  "${CMAKE_C_FLAGS} ${GCC_COVERAGE_COMPILE_FLAGS} -Wall -Wpedantic -Werror --coverage -fsanitize=thread -g -O1
    -fsanitize=address -fno-optimize-sibling-calls -fsanitize-address-use-after-scope -fno-omit-frame-pointer -g -O1
    -fsanitize=memory -fno-optimize-sibling-calls -fsanitize-memory-track-origins=2 -fno-omit-frame-pointer -g -O2
    -fsanitize=undefined")
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
find_package(GTest REQUIRED)

add_executable(hw_c src/main.c)

add_executable(test_dynamic tests/lib_test.cpp)
target_link_libraries(test_dynamic GTest::gtest dynamic input gcov)

add_executable(test_static tests/lib_test.cpp)
target_link_libraries(test_static GTest::gtest static_work input gcov)

if(dynamic)
    message("dynamic")
    target_link_libraries(hw_c Threads::Threads dynamic gcov)
else()
    message("static_work")
    target_link_libraries(hw_c static_work gcov)
endif(dynamic)


add_executable(test_input tests/input_test.cpp)
target_link_libraries(test_input GTest::gtest input gcov)

enable_testing()

add_test(NAME test_input
        COMMAND test_input
        WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/data)
add_test(NAME test_static
         COMMAND test_static
         WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/data)
add_test(NAME test_dynamic
         COMMAND test_dynamic
         WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/data)
