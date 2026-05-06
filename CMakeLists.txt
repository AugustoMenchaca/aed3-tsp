cmake_minimum_required(VERSION 3.16)
project(aed3-tsp CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE Release)
endif()

add_compile_options(-Wall -Wextra)

add_executable(tsp
    src/main.cpp
    src/BruteForce.cpp
    src/Prim.cpp
    src/DFS.cpp
)
