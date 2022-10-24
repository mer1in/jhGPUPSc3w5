# CUDA at Scale Independent Project

This is the week 5 project of the [Course 3 of 4 in the GPU Programming Specialization by Johns Hopkins University](https://www.coursera.org/learn/cuda-at-scale-for-the-enterprise/home/info)

## Description

Video Stabilization Using Minimal difference of consequent frames

## Quick run

`git clone https://github.com/mer1in/jhGPUPSc3w5.git && cd jhGPUPSc3w5 && ./init.sh`

## Dependencies / third party components

- [ffmpeg](https://www.ffmpeg.org/) included as submodule
  - `cd ffmpeg && ./configure --disable-x86asm --prefix=`pwd` && make && make install && make examples`
  - make sure you can link proj with ffmpeg: ```gcc doc/examples/decode_video.c -Llib -lavcodec -lavdevice -lavfilter -lavformat -lavutil -lpostproc -lswresample -lswscale -lpthread -lz -llzma -lm```
- video/\* samples were taken from <a target="_blank" href="http://www.videezy.com/">Free Stock Videos by Videezy</a>  and downscaled with ```for f in `ls|grep mp4`; do ffmpeg -i $f -vf scale=480:-1 video/$f ; done```

## Steps/lib calls to use
1. substract two images
1. summ all pixels in the diff image

TODO:
- [ ] ffmpeg
  - [x] read mp4
  - [ ] write mp4
  - [ ] Hello world: convert to grayscale
- [ ] Open stream, calc array of shifts in a movie, get borders
- [ ] Reopen stream, transfer frames with corresponding shifts
