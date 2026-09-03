#!/bin/bash

Channel[1]=301000
Channel[2]=301001
Channel[3]=301002
Channel[4]=301003
Channel[5]=301004
Channel[6]=301005
Channel[7]=301006
Channel[8]=301007
Channel[9]=301008
Channel[10]=301009
Channel[11]=301010
Channel[12]=301011
Channel[13]=301012
Channel[14]=301013
Channel[15]=301014
Channel[16]=301015
Channel[17]=301016
Channel[18]=301017
Channel[19]=301018
Channel[20]=361106

nFile=`cat SumOfWeight.list |wc -l`

for((ifile=1;ifile<=${nFile};ifile++)); do

FileName=`cat SumOfWeight.list |head -${ifile} |tail -1`

for((i=1;i<=20;i++)); do

if echo "$FileName" | awk -v s="${Channel[${i}]}" '{if (index($0, s) != 0) exit 0; else exit 1}'; then
echo ${Channel[${i}]} $FileName
fi

done

done
