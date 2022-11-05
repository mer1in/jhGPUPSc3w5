cmake_minimum_required (VERSION 3.16)

set(project VideoHideFaces)
project($project})

list(APPEND CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/cmake")
include(Common)
add_sources(*.cpp *.hpp)
ADD_EXECUTABLE(${project} ${SOURCES})

set(OPENCV_ROOT ${SOURCES}/libraries/lib/cmake/opencv4/)
find_package(OpenCV REQUIRED PATHS ${OPENCV_ROOT} NO_DEFAULT_PATH)
target_include_directories(${project} PUBLIC ${OPENCV_INCLUDE_DIRS})




# tbd: nvpp
#set(CUDAToolkit_ROOT "${CMAKE_BINARY_DIR}/extracted/cuda")
#find_package(CUDAToolkit)
