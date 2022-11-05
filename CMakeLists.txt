cmake_minimum_required (VERSION 3.16)
set(CMAKE_VERBOSE_MAKEFILE ON)

set(project VideoHideFaces)
project($project})

list(APPEND CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/cmake")
include(Common)
add_sources(*.cpp *.hpp)
ADD_EXECUTABLE(${project} ${SOURCES})

set(OpenCV_DIR ${CMAKE_CURRENT_SOURCE_DIR}/libraries/lib/cmake/opencv4/)
find_package(OpenCV REQUIRED)
find_package(FFmpeg REQUIRED)

#debug
message(STATUS "OpenCV_INCLUDE_DIRS = ${OpenCV_INCLUDE_DIRS}")

link_directories(${CMAKE_CURRENT_SOURCE_DIR}/libraries/lib)
target_include_directories(${project} PUBLIC ${OpenCV_INCLUDE_DIRS})

add_definitions(-fpermissive)
target_link_libraries(${project} avdevice avfilter avformat avcodec avutil postproc swresample swscale pthread opencv_core opencv_imgcodecs opencv_dnn opencv_imgproc z lzma)

# tbd: nvpp
#set(CUDAToolkit_ROOT "${CMAKE_BINARY_DIR}/extracted/cuda")
#find_package(CUDAToolkit)
