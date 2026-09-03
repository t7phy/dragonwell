#!/bin/bash
echo mc16a:
for((n=1;n<=16;n++));do
Number=`cat run/polar_mc16aSample_new.list |head -$n |tail -1|xargs rucio list-files |grep 'Total events'|awk '{print $4}'`
SampleName=`cat run/polar_mc16aSample_new.list |head -$n |tail -1`
echo $SampleName : $Number
done

echo ""
echo mc16d:
for((n=1;n<=16;n++));do
Number=`cat run/polar_mc16dSample_new.list |head -$n |tail -1|xargs rucio list-files |grep 'Total events'|awk '{print $4}'`
SampleName=`cat run/polar_mc16dSample_new.list |head -$n |tail -1`
echo $SampleName : $Number
done

echo ""
echo "mc16e:"
for((n=1;n<=16;n++));do
Number=`cat run/polar_mc16eSample_new.list |head -$n |tail -1|xargs rucio list-files |grep 'Total events'|awk '{print $4}'`
SampleName=`cat run/polar_mc16eSample_new.list |head -$n |tail -1`
echo $SampleName : $Number
done

