cmake_minimum_required(VERSION 3.0.0)
project(rpn)
set(CMAKE_CXX_STANDARD 17)

include_directories(
    ../ex_1_1
    ../ex_4_1
)

set(SOURCES
    main.cpp
    ../ex_1_1/fraction.cpp
)

add_executable(${PROJECT_NAME} ${SOURCES})
