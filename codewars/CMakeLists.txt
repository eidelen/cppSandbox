cmake_minimum_required(VERSION 2.8.11)

project(codewars)

SET(CMAKE_INCLUDE_CURRENT_DIR ON)

add_executable(triangle color_triangle.cpp)
target_compile_features(triangle PRIVATE cxx_range_for)

add_executable(divstr div_str.cpp)
target_compile_features(divstr PRIVATE cxx_range_for)

add_executable(mulstr mult_str.cpp)
target_compile_features(mulstr PRIVATE cxx_range_for)

add_executable(nextbigger nextbigger.cpp)
target_compile_features(nextbigger PRIVATE cxx_range_for)
