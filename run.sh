#!/bin/bash -x

PROJ=videoHideFaces

(
# XXX: debug
#rm -fr build ; rm -fr out ; rm videoHideFaces

[ -d build ] || mkdir build
cd build
cmake .. && make

mv $PROJ ..
)

[ -d out ] || mkdir out
./${PROJ} video/F03.mp4 out/out.mp4

cp -r out/* ~/project/out/
cp out/out.mp4 ~/coursera/
ls -l ~/coursera/
