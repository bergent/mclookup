cmake_minimum_required(VERSION 3.20)
project(mclookup
        VERSION 1.0
        LANGUAGES CXX)


set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++20 -Wall -Wextra")
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED On)

file(GLOB MCLOOKUP_SOURCES "${CMAKE_SOURCE_DIR}/src/**/*.cpp")
file(GLOB MCLOOKUP_MAIN "${CMAKE_SOURCE_DIR}/src/main.cpp")

include_directories(include/)

add_executable(${PROJECT_NAME} ${MCLOOKUP_MAIN} ${MCLOOKUP_SOURCES})

