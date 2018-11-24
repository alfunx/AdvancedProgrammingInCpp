cmake_minimum_required(VERSION 3.0.0)
project(rpn)

if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE Debug)
endif()

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_FLAGS "-Wall -Wextra")
set(CMAKE_CXX_FLAGS_DEBUG "-g -O0")
set(CMAKE_CXX_FLAGS_RELEASE "-O3")

include_directories(
    .
    ../ex_1_1
)

set(SOURCES
    main.cpp
    ../ex_1_1/fraction.cpp
)

add_executable(${PROJECT_NAME} ${SOURCES})
