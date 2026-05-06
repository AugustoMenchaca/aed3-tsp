cmake_minimum_required(VERSION 3.16)

project(aed3-tsp LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(Qt6 REQUIRED COMPONENTS Core)
if(NOT Qt6_FOUND)
    find_package(Qt5 REQUIRED COMPONENTS Core)
endif()

include_directories(include)

set(SOURCES
    src/main.cpp
    src/Prim.cpp
    src/DFS.cpp
    src/BruteForce.cpp
    src/ArquivoManager.cpp
)

add_executable(aed3-tsp ${SOURCES})

if(Qt6_FOUND)
    target_link_libraries(aed3-tsp PRIVATE Qt6::Core)
else()
    target_link_libraries(aed3-tsp PRIVATE Qt5::Core)
endif()

set_target_properties(aed3-tsp PROPERTIES OUTPUT_NAME "main")
