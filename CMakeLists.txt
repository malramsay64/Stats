cmake_minimum_required(VERSION 2.8)
project(stats)

if (NOT CMAKE_BUILD_TYPE)
    message(STATUS "NO build type selected, default to Release")
    set(CMAKE_BUILD_TYPE "Release")
endif()

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES
        Stats.cpp
        Stats.h
        )

if (NOT CMAKE_BUILD_TYPE STREQUAL "Release")
    add_subdirectory(googletest/googletest)
    include_directories(googletest/googletest/include)

    link_libraries(gtest pthread)
    add_executable(runTests runTests.cpp ${SOURCE_FILES})
endif()

add_library(stats SHARED ${SOURCE_FILES})


SET(CMAKE_INSTALL_PREFIX $ENV{HOME}/.local)

install(TARGETS stats
        CONFIGURATIONS Release
        LIBRARY DESTINATION lib/
        )
install(FILES Stats.h
        CONFIGURATIONS Release
        DESTINATION include/)