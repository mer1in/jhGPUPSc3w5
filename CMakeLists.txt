cmake_minimum_required (VERSION 3.16)
set(CMAKE_VERBOSE_MAKEFILE ON)

set(project videoHideFaces)
project($project})

list(APPEND CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/cmake")
include(Common)
add_sources(*.cpp *.hpp)
ADD_EXECUTABLE(${project} ${SOURCES})

set(OpenCV_DIR ${CMAKE_CURRENT_SOURCE_DIR}/libraries/lib/cmake/opencv4/)
set(FFmpeg_DIR ${CMAKE_CURRENT_SOURCE_DIR}/libraries/)
find_package(OpenCV REQUIRED)
find_package(FFmpeg REQUIRED)



#debug
message(STATUS "OpenCV_INCLUDE_DIRS = ${OpenCV_INCLUDE_DIRS}")
message(STATUS "FFMPEG_INCLUDE_DIRS = ${FFMPEG_INCLUDE_DIRS}")

link_directories(${CMAKE_CURRENT_SOURCE_DIR}/libraries/lib)
message(STATUS "CMAKE_CURRENT_SOURCE_DIR = ${CMAKE_CURRENT_SOURCE_DIR}")
target_include_directories(${project} PUBLIC ${OpenCV_INCLUDE_DIRS})
target_include_directories(${project} PUBLIC "/usr/local/cuda-11.3/targets/x86_64-linux/include/")

add_definitions(-fpermissive)
 
target_link_libraries(${project} ${AVDEVICE_LIBRARIES} ${AVFILTER_LIBRARIES}
    ${AVFORMAT_LIBRARIES} ${AVCODEC_LIBRARIES} ${AVUTIL_LIBRARIES}
    ${POSTPROC_LIBRARIES} ${SWRESAMPLE_LIBRARIES} ${SWSCALE_LIBRARIES}
    pthread opencv_core opencv_imgcodecs opencv_dnn
    opencv_imgproc z lzma)

# tbd: nvpp
#set(CUDAToolkit_ROOT "${CMAKE_BINARY_DIR}/extracted/cuda")
#find_package(CUDAToolkit)
