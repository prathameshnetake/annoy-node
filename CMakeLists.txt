cmake_minimum_required(VERSION 3.10)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++14")

set(CMAKE_BUILD_TYPE Debug)

project(annoy)

include_directories(annoy/src)
add_definitions(-DANNOYLIB_MULTITHREADED_BUILD)
add_compile_definitions(ANNOYLIB_MULTITHREADED_BUILD)

add_executable(
    annoy
    annoy.cpp
)

target_link_libraries(annoy)
