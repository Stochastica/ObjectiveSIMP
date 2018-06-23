project(ObjSimp)
cmake_minimum_required(VERSION 3.5)

set(PROJECT_SOURCE_DIR     ${CMAKE_SOURCE_DIR}/src)
set(EXECUTABLE_OUTPUT_PATH ${CMAKE_SOURCE_DIR}/bin)
set(CMAKE_BINARY_DIR       ${CMAKE_SOURCE_DIR}/build)

add_subdirectory(${PROJECT_SOURCE_DIR})
