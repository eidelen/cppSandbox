cmake_minimum_required(VERSION 2.8.11)

project(codewars)

SET(CMAKE_INCLUDE_CURRENT_DIR ON)

add_executable(triangle color_triangle.cpp)
target_compile_features(triangle PRIVATE cxx_range_for)
