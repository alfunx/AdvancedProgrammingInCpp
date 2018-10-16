cmake_minimum_required(VERSION 3.0.0)
project(traits)

include_directories(
    ../ex_1_1
)

set(SOURCES
    main.cpp
    ../ex_1_1/fraction.cpp
)

add_executable(${PROJECT_NAME} ${SOURCES})
