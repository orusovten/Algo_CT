cmake_minimum_required(VERSION 3.16)
set(CMAKE_CXX_STANDARD 14)

add_library(bitset bitset.h bitset.cpp)
add_executable(bitset_test test.cpp)
target_link_libraries(bitset_test bitset)
