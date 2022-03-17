cmake_minimum_required(VERSION 3.16)
set(CMAKE_CXX_STANDARD 14)

add_library(m3i m3i.h m3i.cpp)
add_executable(m3i_test test.cpp)
target_link_libraries(m3i_test m3i)
