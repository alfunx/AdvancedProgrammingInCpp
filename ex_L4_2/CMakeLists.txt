cmake_minimum_required(VERSION 3.0.0)
project(count)
set(CMAKE_CXX_STANDARD 17)

include_directories(
)

set(SOURCES
    main.cpp
)

add_executable(${PROJECT_NAME} ${SOURCES})
