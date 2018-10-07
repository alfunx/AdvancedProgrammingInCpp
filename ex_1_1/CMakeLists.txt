cmake_minimum_required(VERSION 3.0.0)
project(fraction)

include_directories(
)

set(SOURCES
    main.cpp
    fraction.cpp
)

add_executable(${PROJECT_NAME} ${SOURCES})
