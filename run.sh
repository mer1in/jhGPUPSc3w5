#!/bin/bash -x

PROJ=videoHideFaces
rm $PROJ
[ -d out ] || mkdir out
rm out/*

(
[ -d build ] || mkdir build
cd build
cmake .. && make

mv $PROJ ..
)

for file_name in F01 F02
do
    ./${PROJ} video/${file_name}.mp4 out/${file_name}.mp4 --dump-blured --dump-input
done

cp -r out/* ~/project/out/
cp out/*.mp4 ~/coursera/
ls -l ~/coursera/
