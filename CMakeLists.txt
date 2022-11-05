cmake_minimum_required (VERSION 3.16)

set(project VideoHideFaces)
project($project})

list(APPEND CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/cmake")
include(Common)
add_sources(*.cpp *.hpp)
ADD_EXECUTABLE(${project} ${SOURCES})



# tbd: nvpp
#set(CUDAToolkit_ROOT "${CMAKE_BINARY_DIR}/extracted/cuda")
#find_package(CUDAToolkit)
