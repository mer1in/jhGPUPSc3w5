#!/bin/bash

cp decode.cpp ffmpeg/
cd ffmpeg
[ -d out ] || mkdir out
[ -d my ] || mkdir my
gcc decode.cpp  -lavcodec -lavdevice -lavfilter -lavformat -lavutil -lpostproc -lswresample \
    -lswscale -lpthread -lz -llzma -lm -fpermissive -Llib -L/usr/local/lib/ -D__STDC_CONSTANT_MACROS -o my/decode \
    && echo "decode compiled" && ./my/decode ../video/P1033651.mp4 out/out || echo "Failed to compile decode"

#cc decode.c -Llib -lavcodec -lavdevice -lavfilter -lavformat -lavutil -lpostproc -lswresample \
#    -lswscale -lpthread -lz -llzma -lm -o my/decode \
#    && echo "decode compiled" && ./my/decode ../video/P1033651.mp4 out/out || echo "Failed to compile decode"

