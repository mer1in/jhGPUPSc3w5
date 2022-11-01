#!/bin/bash

BASE_DIR=$(pwd)

echo "Fetch submodules"
git submodule update --init --recursive

echo "Build ffmpeg"
(
cd ffmpeg && ./configure --enable-static --enable-pic --enable-nonfree \
    --enable-gpl --disable-x86asm --prefix=$BASE_DIR \
    && make && \
    make install && \
    make examples
)

echo "Run decoding test"
(
mkdir -p ~/project/out
./ffmpeg/bin/ffmpeg -i ./video/P1033651.mp4 mpeg1.mpeg
./ffmpeg/doc/examples/decode_video ./mpeg1.mpeg ~/project/out/frame
ls -la ~/project/out/
)

echo "--- Build openCV ---"
(
cd opencv
mkdir -p build 
cd build 
cmake -DCMAKE_BUILD_TYPE=Release \
      -DENABLE_FAST_MATH=ON \
      -DINSTALL_C_EXAMPLES=OFF \
      -DINSTALL_PYTHON_EXAMPLES=OFF \
      -DBUILD_TESTS=OFF \
      -DBUILD_PERF_TESTS=OFF \
      -DBUILD_EXAMPLES=OFF \
      -DBUILD_DOCS=OFF \
      -DOPENCV_EXTRA_MODULES_PATH=${BASE_DIR}/opencv_contrib/modules \
      -DCMAKE_INSTALL_PREFIX=${BASE_DIR}/inst ..

make && make install
)
