#!/bin/bash
#MC16a=`rucio list-dids mc16_13TeV.5070*recon.AOD.e8312_e7400_s3126_r9364 |grep 5070 |awk '{print $2}'`
#MC16d=`rucio list-dids mc16_13TeV.5070*recon.AOD.e8312_e7400_s3126_r10201 |grep 5070 |awk '{print $2}'`
#MC16e=`rucio list-dids mc16_13TeV.5070*recon.AOD.e8312_e7400_s3126_r10724 |grep 5070 |awk '{print $2}'`

MC16a=`rucio list-dids mc16_13TeV.5070*.DAOD_STDM5.e8312_e7400_s3126_r9364_r9315_p4097 |grep 5070 |awk '{print $2}'`
MC16d=`rucio list-dids mc16_13TeV.5070*.DAOD_STDM5.e8312_e7400_s3126_r10201_r10210_p4097 |grep 5070 |awk '{print $2}'`
MC16e=`rucio list-dids mc16_13TeV.5070*.DAOD_STDM5.e8312_e7400_s3126_r10724_r10726_p4097 |grep 5070 |awk '{print $2}'`

for((i=0;i<=15;i++)); do
dids=$[${i}+507019]
echo "$MC16a" |grep $dids |awk '{print $1}'
done

echo ""

for((i=0;i<=15;i++)); do
dids=$[${i}+507019]
echo "$MC16d" |grep $dids |awk '{print $1}'
done

echo ""

for((i=0;i<=15;i++)); do
dids=$[${i}+507019]
echo "$MC16e" |grep $dids |awk '{print $1}'
done

