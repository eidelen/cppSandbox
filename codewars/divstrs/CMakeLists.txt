cmake_minimum_required(VERSION 2.8.11)

project(divstr)

SET(CMAKE_INCLUDE_CURRENT_DIR ON)

add_executable(divstr div_str.cpp)
target_compile_features(divstr PRIVATE cxx_range_for)
