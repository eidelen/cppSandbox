cmake_minimum_required(VERSION 3.0)

project(exceptions)

SET(CMAKE_CXX_FLAGS "-Wall")
SET(CMAKE_INCLUDE_CURRENT_DIR ON)

add_executable(exceptions main.cpp )
target_compile_features( exceptions PRIVATE cxx_range_for )
