#!/bin/bash

cp decode.cpp ffmpeg/
cd ffmpeg
mkdir out
gcc decode.cpp -Llib -lavcodec -lavdevice -lavfilter -lavformat -lavutil -lpostproc -lswresample \
    -lswscale -lpthread -lz -llzma -lm -fpermissive \
    && echo "decode compiled" && ./a.out ../video/P1033651.mp4 out/out || echo "Failed to compile decode"
    
