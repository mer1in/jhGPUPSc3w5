#!/bin/bash

echo "Fetch submodules"
git submodule update --init --recursive

(
    cd ffmpeg && ./configure --disable-x86asm --prefix=`pwd` && make && make install && make examples
)
