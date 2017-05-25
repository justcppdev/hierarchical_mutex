cmake_minimum_required(VERSION 3.0)
project(hierarchical_mutex)
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
add_library(hierarchical_mutex STATIC ${CMAKE_CURRENT_SOURCE_DIR}/sources/hierarchical_mutex.cpp)
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/include)

add_executable(example01 ${CMAKE_CURRENT_SOURCE_DIR}/examples/example01.cpp)
target_link_libraries(example01 hierarchical_mutex)
