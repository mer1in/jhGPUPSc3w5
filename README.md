# CUDA at Scale Independent Project

This is the week 5 project of the [Course 3 of 4 in the GPU Programming Specialization by Johns Hopkins University](https://www.coursera.org/learn/cuda-at-scale-for-the-enterprise/home/info)

## Project Description

Blur faces in videostream

| Source Video | Blured Faces Video |
:-------------------------:|:-------------------------:
![src](out/F01-input-12.jpg)  |  ![dst](out/F01-blured-12.jpg)

## Quick start

`git clone https://github.com/mer1in/jhGPUPSc3w5.git && cd jhGPUPSc3w5 && ./init.sh`
`./run.sh`

## Code Organization

### folders

- src - sources
- opencv - openCV Library. Included as a submodule
- opencv_contrib - openCV extra modules, submodule
- ffmpeg - video manipulation framework, submodule
- x264 - libx264 encoder library, submodule
- assets - face detection DNNs
- video - video sources
- out - example results of the program
- cmake - cmake routines required for build

### files

- [CMakeLists.txt](./CMakeLists.txt) - cmake build recipe
- [README.md](./README.md) - this file
- [init.sh](./init.sh) - script to initialize build environment
- [monitor.sh](./monitor.sh) - continuous integration, instantly watches for changes in repo and rebuilds if changed
- [run.sh](./run.sh) - build and run

## Prerequisites

- [npp](https://developer.nvidia.com/npp) - if you're using computer provided by course platform then this dependency is already installed

## Dependencies / third party components / RTFMs

- [ffmpeg](https://www.ffmpeg.org/) included as submodule, this dependency is built by `init.sh` script
  - [hints in building ffmpeg](https://trac.ffmpeg.org/wiki/CompilationGuide/Ubuntu)
- video/\* samples were taken from <a target="_blank" href="http://www.videezy.com/">Free Stock Videos by Videezy</a>  and downscaled with\
 ```for f in `ls|grep mp4`; do ffmpeg -i $f -vf scale=480:-1 video/$f ; done```
- [npp documentation](https://docs.nvidia.com/cuda/npp/index.html)
- [Building a face detector with OpenCV in C++](https://medium.com/analytics-vidhya/building-a-face-detector-with-opencv-in-c-8814cd374ea1)

## Steps/lib calls to use
1. Blur = gauss filter

TODO:
- [x] ffmpeg
  - [x] read mp4
  - [x] write mp4
    - [x] install libx264
  - [ ] ~~Hello world: convert to grayscale~~
- [x] build OpenCV
- [x] get array of ROIs using net from [Building a face detector with OpenCV in C++](https://medium.com/analytics-vidhya/building-a-face-detector-with-opencv-in-c-8814cd374ea1)
- [x] use cmake
- [x] apply blur
  - [x] npp sandbox
    - [ ] ~~install npp~~
- [ ] write stream
  - [x] make it work with global vars
  - [ ] rewrite with classes
- [ ] documentation
