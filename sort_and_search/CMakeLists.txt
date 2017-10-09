cmake_minimum_required(VERSION 2.8.11)

project(search_and_sort)

SET(CMAKE_CXX_FLAGS "-std=c++0x -pthread -msse4")
SET(CMAKE_INCLUDE_CURRENT_DIR ON)

SET( src_files
        listOperations.cpp listOperations.h
        myMath.cpp myMath.h
        inheritance.cpp inheritance.h
        myBinaryTree.cpp myBinaryTree.h
        sort.cpp )


add_executable(sort ${src_files} )
