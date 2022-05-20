cmake_minimum_required(VERSION 3.5)

project(Upper_project)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=gnu++0x")

set(lab2_src_files Application.cpp Application.h Block.cpp Block.h BlockProcessing.cpp BlockProcessing.h definitions.h Executor.cpp Executor.h Keywords.cpp Keywords.h Parser.cpp Parser.h Validator.h WorkerBase.h Workers.cpp Workers.h)

add_library(lab2_src ${lab2_src_files})