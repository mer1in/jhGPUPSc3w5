#!/bin/bash

echo "Fetch submodules"
git submodule update --init --recursive

echo "Build ffmpeg"
#( cd ffmpeg && ./configure --disable-x86asm --prefix=`pwd` && make && make install && make examples )
( cd ffmpeg && ./configure --enable-static --enable-pic --enable-nonfree  --enable-gpl --disable-x86asm --prefix=`pwd` && make && make install && make examples )

echo "Run decoding test"
(
    mkdir -p ~/project/out
    ./ffmpeg/bin/ffmpeg -i ./video/P1033651.mp4 mpeg1.mpeg
    ./ffmpeg/doc/examples/decode_video ./mpeg1.mpeg ~/project/out/frame
    ls -la ~/project/out/
)
