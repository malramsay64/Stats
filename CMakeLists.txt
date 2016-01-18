cmake_minimum_required(VERSION 2.8)
project(stats)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

add_subdirectory(googletest/googletest)
include_directories(googletest/googletest/include)

link_libraries(gtest pthread)

set(SOURCE_FILES
        Stats.cpp
        Stats.h
        )
add_executable(runTests runTests.cpp ${SOURCE_FILES})
add_library(stats SHARED ${SOURCE_FILES})