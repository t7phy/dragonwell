#!/bin/bash
WORKDIR=$PWD
channel[1]=data15
channel[2]=data16
channel[3]=data17
channel[4]=data18

NDIR=`ls |wc -l`
n=0
for((i=1;i<=NDIR;i++)); do

FileName=`ls |head -$i |tail -1`

if [ -d $FileName ]; then

n=$[$n+1]
FileDIR[$n]=$FileName

fi

done

for((k=1;k<=4;k++)); do
echo "merge the ${channel[$k]}"

for((i=1;i<=n;i++)); do

if [[ `echo ${FileDIR[$i]} |grep ${channel[$k]}` != "" ]]; then
ls-abs $PWD/${FileDIR[$i]} >> data_${channel[$k]}.list
fi

done

if [ -f "data_${channel[$k]}.list" ]; then
#if [ `cat data_${channel[$k]}.list |wc -l` -ne 0 ]; then
hadd ${channel[$k]}_.myOutput.root @data_${channel[$k]}.list
rm data_${channel[$k]}.list
fi

done

cd $WORKDIR

