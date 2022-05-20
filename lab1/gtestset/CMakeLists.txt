cmake_minimum_required(VERSION 3.5)

project(Upper_project)

find_package(GTest REQUIRED)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=gnu++0x")

add_subdirectory(lib/googletest-master)
include_directories(lib/googletest-maser/googletest/include)
include_directories(lib/googletest-maser/googlemock/include)

include_directories(${GTEST_INCLUDE_DIRS})

set(SOURCE_FILES main.cpp tests/TestForSet.cpp)

add_executable(gtestsetexe ${SOURCE_FILES})
#1
target_link_libraries(gtestsetexe gtest gtest_main lab1_src ${GTEST_LIBRARIES} pthread)