#!/bin/bash
WORKDIR=$PWD
nLine=6
for((i=1;i<=${nLine};i++));do
cd $WORKDIR
mkdir $WORKDIR/JOB$i
Q=`sed -n "${i},${i}p" e906aF |awk '{print $2}'`
y=`sed -n "${i},${i}p" e906aF |awk '{print $1}'`
cp main legacy.in $WORKDIR/JOB$i
cd $WORKDIR/JOB$i
mkdir inp
cp ../inp/qt_grid.inp inp
echo $Q > inp/q_grid_test.inp
echo $y > inp/y_grid.inp
./main
done
cd $WORKDIR
