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
for file_name in F01 F02
do
    ./${PROJ} video/${file_name}.mp4 out/${file_name}.mp4
done

cp -r out/* ~/project/out/
cp out/*.mp4 ~/coursera/
ls -l ~/coursera/
