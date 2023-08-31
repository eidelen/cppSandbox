cmake_minimum_required(VERSION 2.8.11)

project(codewars)

SET(CMAKE_INCLUDE_CURRENT_DIR ON)

add_executable(mulstr mult_str.cpp)
target_compile_features(mulstr PRIVATE cxx_range_for)
