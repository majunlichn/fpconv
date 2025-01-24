cmake_minimum_required(VERSION 3.23)

message(STATUS "CMake version: ${CMAKE_VERSION}")

project(fpconv)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)

set(FPCONV_SOURCES
    common.h
    common.cpp
    fp16.cpp
    bf16.cpp
    fp8.cpp
    main.cpp
)

add_executable(fpconv ${FPCONV_SOURCES})
