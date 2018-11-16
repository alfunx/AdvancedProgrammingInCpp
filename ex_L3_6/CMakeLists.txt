cmake_minimum_required(VERSION 3.0.0)
project(mem_fun)

if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE Debug)
endif()

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_FLAGS "-Wall -Wextra")
set(CMAKE_CXX_FLAGS_DEBUG "-g -O0")
set(CMAKE_CXX_FLAGS_RELEASE "-O3")

include_directories(
    .
)

set(SOURCES
    main.cpp
)

add_executable(${PROJECT_NAME} ${SOURCES})
