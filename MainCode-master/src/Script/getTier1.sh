#!/bin/bash
for((i=1;i<=56;i++)); do
if [ $i -lt 10 ]; then
k=0$i
else
k=$i
fi

echo  `grep Chi2F i2Tn3.${k}.log |awk '{print $10}'`-`grep Chi2F i2Tn3.00.log |awk '{print $10}'` |bc
done

