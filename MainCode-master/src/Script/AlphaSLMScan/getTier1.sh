#!/bin/bash

BaseName=i2TAn3m248_mDIS

for((i=1;i<=56;i++)); do
if [ $i -lt 10 ]; then
k=0$i
else
k=$i
fi

echo  `grep Chi2F ${BaseName}.${k}.log |awk '{print $10}'`-`grep Chi2F ${BaseName}.00.log |awk '{print $10}'` |bc
done
