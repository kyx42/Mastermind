cmake_minimum_required(VERSION 3.8)
project(untitled)

set(CMAKE_CXX_STANDARD 11)
SET( CMAKE_CXX_FLAGS  "-g3")
set(SOURCE_FILES main.cpp)
add_executable(untitled ${SOURCE_FILES})