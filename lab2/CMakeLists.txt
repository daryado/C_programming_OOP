cmake_minimum_required(VERSION 3.5)

project(Upper_project)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=gnu++0x")

add_subdirectory("${PROJECT_SOURCE_DIR}/lab2_src")
add_subdirectory("${PROJECT_SOURCE_DIR}/gtestset")