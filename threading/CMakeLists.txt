cmake_minimum_required(VERSION 2.8.11)

project(threading)

SET(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(threading main.cpp )
target_compile_features( threading PRIVATE cxx_range_for )
