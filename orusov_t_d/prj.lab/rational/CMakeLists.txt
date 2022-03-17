cmake_minimum_required(VERSION 3.16)
set(CMAKE_CXX_STANDARD 14)

add_library(rational rational.h rational.cpp)
add_executable(rational_test test.cpp)
target_link_libraries(rational_test rational)
