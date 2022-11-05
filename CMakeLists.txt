cmake_minimum_required (VERSION 3.16)

set(project VideoHideFaces)
project($project})

include(common)
add_sources(*.cpp *.h)
ADD_EXECUTABLE(${this_target} ${SOURCES})



# tbd: nvpp
#set(CUDAToolkit_ROOT "${CMAKE_BINARY_DIR}/extracted/cuda")
#find_package(CUDAToolkit)
