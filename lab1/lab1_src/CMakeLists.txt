cmake_minimum_required(VERSION 3.5)

project(Upper_project)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=gnu++0x")
set(lab1_src_files Tritset.cpp Tritset.h TritValue.h TritValue.cpp)

add_library(lab1_src ${lab1_src_files})