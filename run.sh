#!/bin/bash

cp decode.c ffmpeg/
cd ffmpeg
mkdir out
mkdir my
#gcc decode.cpp -Llib -lavcodec -lavdevice -lavfilter -lavformat -lavutil -lpostproc -lswresample \
#    -lswscale -lpthread -lz -llzma -lm -fpermissive -D__STDC_CONSTANT_MACROS \
#    && echo "decode compiled" && ./a.out ../video/P1033651.mp4 out/out || echo "Failed to compile decode"

cc decode.c -Llib -lavcodec -lavdevice -lavfilter -lavformat -lavutil -lpostproc -lswresample \
    -lswscale -lpthread -lz -llzma -lm -fpermissive -o my/decode \
    && echo "decode compiled" && ./my/decode ../video/P1033651.mp4 out/out || echo "Failed to compile decode"

