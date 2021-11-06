cmake_minimum_required(VERSION 3.20)
project(hw_c C CXX)

set(CMAKE_C_STANDARD 11)
set(CMAKE_CXX_STANDARD 17)

set(CMAKE_C_FLAGS  "${CMAKE_C_FLAGS} ${GCC_COVERAGE_COMPILE_FLAGS} -Wall -Wpedantic -Werror --coverage")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wpedantic -Werror  --coverage")

if (address)
    message("address")
    add_compile_options(-fsanitize=address)
    add_link_options(-fsanitize=address)
elseif(memory)
    message("memory")
    add_compile_options(-fsanitize=leak)
    add_link_options(-fsanitize=leak)
elseif(undefined)
    message("undefined")
    add_compile_options(-fsanitize=undefined)
    add_link_options(-fsanitize=undefined)
elseif(thread)
    message("thread")
    add_compile_options(-fsanitize=thread)
    add_link_options(-fsanitize=thread)
endif()


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
