# CUDA at Scale Independent Project

This is the week 5 project of the [Course 3 of 4 in the GPU Programming Specialization by Johns Hopkins University](https://www.coursera.org/learn/cuda-at-scale-for-the-enterprise/home/info)

## Description

Video Stabilization Using Minimal difference of consequent frames

## Dependencies / third party components

- [ffmpeg](https://www.ffmpeg.org/) included as submodule
- video/\* samples were taken from <a target="_blank" href="http://www.videezy.com/">Free Stock Videos by Videezy</a>  and downscaled with ```for f in `ls|grep mp4`; do ffmpeg -i $f -vf scale=480:-1 video/$f ; done```

## Steps/lib calls to use
1. substract two images
1. summ all pixels in the diff image


TODO:
1. Read mp4, write mp4. Hello world: convert to grayscale
1. Open stream, calc array of shifts in a movie, get borders
1. Reopen stream, transfer frames with corresponding shifts
