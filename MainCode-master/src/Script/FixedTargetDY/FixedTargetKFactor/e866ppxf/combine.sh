#!/bin/bash
nLine=184
for((i=1;i<=${nLine};i++));do
cp JOB${i}/w_pert.out JOB${i}/w_pert_tmp.out
sed -i "1,3d" JOB${i}/w_pert_tmp.out
cat JOB${i}/w_pert_tmp.out >> e866ppxf_pert.txt
done
