cmake_minimum_required(VERSION 3.0.0)
project(rpn)

include_directories(
    ../ex_1_1
    ../ex_2_2
)

set(SOURCES
    main.cpp
    rpn_calculator.cpp
    ../ex_1_1/fraction.cpp
)

add_executable(${PROJECT_NAME} ${SOURCES})
