cmake_minimum_required(VERSION 3.10)
project(QuineMcCluskeyMinimizer)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

include_directories(include)

file(GLOB SRC_LIST "src/*.cpp")
add_executable(${PROJECT_NAME} main.cpp ${SRC_LIST})

