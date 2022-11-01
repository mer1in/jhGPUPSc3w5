#!/bin/bash

cp decode.cpp ffmpeg/
cd ffmpeg
[ -d out ] || mkdir out
[ -d my ] || mkdir my
gcc decode.cpp -lavdevice -lavfilter -lavformat -lavcodec -lavutil -lpostproc -lswresample \
    -lswscale -lpthread -lz -llzma -lm -fpermissive -Llib -L/usr/local/lib/ -D__STDC_CONSTANT_MACROS -o my/decode \
    && echo "decode compiled" && ./my/decode ../video/P1033651.mp4 out/out || echo "Failed to compile decode"

mkdir -p ~/project/boxFilterNPP/out
python3 -m pip install --upgrade pip
python3 -m pip install --upgrade Pillow

for f in `ls out|grep ppm`
do 
    python3 ../ppm2png.py out/$f
done
cp out/*.png ~/project/boxFilterNPP/out/

echo "--- Build openCV ---"
base_directory=$(pwd)

cd ./opencv
mkdir -p build 
cd ./build 
cmake -DCMAKE_BUILD_TYPE=Release \
      -DENABLE_FAST_MATH=ON \
      -DINSTALL_C_EXAMPLES=OFF \
      -DINSTALL_PYTHON_EXAMPLES=OFF \
      -DBUILD_TESTS=OFF \
      -DBUILD_PERF_TESTS=OFF \
      -DBUILD_EXAMPLES=OFF \
      -DBUILD_DOCS=OFF \
      -DOPENCV_EXTRA_MODULES_PATH=${base_directory}/opencv_contrib/modules \
      -DCMAKE_INSTALL_PREFIX=${base_directory} ..
make
echo "--- Install openCV ---"
sudo make install
