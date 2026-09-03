#!/bin/bash
nLine=119
for((i=1;i<=${nLine};i++));do
cp JOB${i}/legacy.out JOB${i}/legacy_tmp.out
sed -i "1,15d" JOB${i}/legacy_tmp.out
cat JOB${i}/legacy_tmp.out >> e605_LO.txt
done
