cmake_minimum_required (VERSION 3.16)

set(project videoHideFaces)
project($project})

list(APPEND CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/cmake")
include(Common)
add_sources(src/*.cpp src/*.h)
ADD_EXECUTABLE(${project} ${SOURCES})

set(OpenCV_DIR ${CMAKE_CURRENT_SOURCE_DIR}/libraries/lib/cmake/opencv4/)
set(FFmpeg_DIR ${CMAKE_CURRENT_SOURCE_DIR}/libraries/)
find_package(OpenCV REQUIRED)
find_package(FFmpeg REQUIRED)
find_package(CUDA REQUIRED)
find_library(LIBX264 libx264.a HINTS "${CMAKE_CURRENT_SOURCE_DIR}/libraries/lib/")

#debug
message(STATUS "OpenCV_INCLUDE_DIRS = ${OpenCV_INCLUDE_DIRS}")
message(STATUS "FFMPEG_INCLUDE_DIRS = ${FFMPEG_INCLUDE_DIRS}")
message(STATUS "LIBX264 = ${LIBX264}")

link_directories(${CMAKE_CURRENT_SOURCE_DIR}/libraries/lib)
message(STATUS "CMAKE_CURRENT_SOURCE_DIR = ${CMAKE_CURRENT_SOURCE_DIR}")
target_include_directories(${project} PUBLIC ${FFMPEG_INCLUDE_DIRS})
target_include_directories(${project} PUBLIC ${OpenCV_INCLUDE_DIRS})
target_include_directories(${project} PUBLIC ${CUDA_INCLUDE_DIRS})

message(STATUS "CUDA_CUDA_LIBRARY = ${CUDA_CUDA_LIBRARY}")
message(STATUS "CUDA_LIBRARIES = ${CUDA_LIBRARIES}")

add_definitions(-fpermissive)
target_link_libraries(${project} ${AVDEVICE_LIBRARIES} ${AVFILTER_LIBRARIES}
    ${AVFORMAT_LIBRARIES} ${AVCODEC_LIBRARIES} ${AVUTIL_LIBRARIES}
    ${POSTPROC_LIBRARIES} ${SWRESAMPLE_LIBRARIES} ${SWSCALE_LIBRARIES}
    ${CUDA_CUDA_LIBRARY} ${CUDA_LIBRARIES} ${CUDA_nppif_LIBRARY}
    ${LIBX264}
    pthread opencv_core opencv_imgcodecs opencv_dnn
    opencv_imgproc z lzma)

