#!/bin/bash

cp decode.cpp ffmpeg/
cd ffmpeg
gcc decode.cpp -Llib -lavcodec -lavdevice -lavfilter -lavformat -lavutil -lpostproc -lswresample \
    -lswscale -lpthread -lz -llzma -lm

./a.out
