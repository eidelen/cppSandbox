cmake_minimum_required(VERSION 3.17)
project(sparsevector)

set(CMAKE_CXX_STANDARD 17)
add_executable(sparsevector main.cpp DotProd.h NaiveDotProduct.h HashDot.h)
