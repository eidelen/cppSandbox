cmake_minimum_required(VERSION 2.8.11)

project(search_and_sort)

SET(CMAKE_CXX_FLAGS "-pthread -msse4 -Wall")
SET(CMAKE_INCLUDE_CURRENT_DIR ON)

SET( general_src_files
        listOperations.cpp listOperations.h
        myMath.cpp myMath.h
        myBinaryTree.cpp myBinaryTree.h)

add_executable(sort ${general_src_files} sort.cpp )
target_compile_features( sort PRIVATE cxx_range_for )

add_executable(search ${general_src_files} search.cpp )
target_compile_features( search PRIVATE cxx_range_for )
