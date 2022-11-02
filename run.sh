#!/bin/bash

BASE_DIR=$(pwd)

cp decode.cpp ffmpeg/
(
set -x
cd ffmpeg
[ -d out ] || mkdir out
[ -d my ] || mkdir my
gcc decode.cpp -lavdevice -lavfilter -lavformat -lavcodec -lavutil -lpostproc -lswresample \
    -lswscale -lpthread \
    -l:libopencv_core.so -l:libopencv_imgcodecs.so \
    -lz -llzma -lm -fpermissive -lstdc++ -Llib \
    -L${BASE_DIR}/libraries/lib \
    -L/usr/local/lib/ -D__STDC_CONSTANT_MACROS -o my/decode \
    -I${BASE_DIR}/libraries/include/opencv4 \
    && echo "decode compiled" && LD_LIBRARY_PATH=${BASE_DIR}/libraries/lib ./my/decode ../video/P1033651.mp4 out/out || echo "Failed to compile decode"

#mkdir -p ~/project/boxFilterNPP/out
#python3 -m pip install --upgrade pip
#python3 -m pip install --upgrade Pillow
#
#for f in `ls out|grep ppm`
#do 
#    python3 ../ppm2png.py out/$f
#done
#cp out/*.png ~/project/boxFilterNPP/out/
)

