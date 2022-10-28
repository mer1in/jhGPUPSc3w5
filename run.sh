#!/bin/bash

cp decode.cpp ffmpeg/
cd ffmpeg
gcc decode.cpp -Llib -lavcodec -lavdevice -lavfilter -lavformat -lavutil -lpostproc -lswresample \
    -lswscale -lpthread -lz -llzma -lm \
    && echo "decode compiled" || echo "Failed to compile decode"
mkdir out
./a.out ../video/P1033651.mp4 out/out
