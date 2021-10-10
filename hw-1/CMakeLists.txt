cmake_minimum_required(VERSION 3.20)
project(hw_1)

set(CMAKE_C_STANDARD 99)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(LIB_SOURCE_FILES minor_matrix.c)
add_library(minor STATIC ${LIB_SOURCE_FILES})

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -pthread")
add_executable(hw_1 main.c)
target_link_libraries(hw_1 minor)

enable_testing()
find_package(GTest REQUIRED)



include_directories(${GTEST_INCLUDE_DIRS})
add_executable(minor_test minor_matrix_test.cpp)
target_link_libraries(minor_test ${GTEST_LIBRARIES} minor)
