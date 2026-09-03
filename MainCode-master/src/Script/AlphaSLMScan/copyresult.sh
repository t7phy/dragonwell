#!/bin/bash

BaseName=i2TAn3m248_mDIS

alphas[1]=0.110
alphas[2]=0.111
alphas[3]=0.112
alphas[4]=0.113
alphas[5]=0.114
alphas[6]=0.115
alphas[7]=0.116
alphas[8]=0.117
alphas[9]=0.118
alphas[10]=0.119
alphas[11]=0.120
alphas[12]=0.121
alphas[13]=0.122
alphas[14]=0.123
alphas[15]=0.124
alphas[16]=0.1164
alphas[17]=0.1123
alphas[18]=0.1206
alphas[19]=0.1139
alphas[20]=0.1177
alphas[21]=0.1151

ResultDIR=LMScan

if [ ! -d $ResultDIR ]; then
    mkdir $ResultDIR
fi

for((i=1;i<=15;i++)); do
cp CentralFit_AlphaS_${alphas[${i}]}/${BaseName}.00.inp $ResultDIR/${BaseName}_${alphas[${i}]}.00.inp
cp CentralFit_AlphaS_${alphas[${i}]}/${BaseName}.00.log $ResultDIR/${BaseName}_${alphas[${i}]}.00.log
cp CentralFit_AlphaS_${alphas[${i}]}/${BaseName}.00.dta $ResultDIR/${BaseName}_${alphas[${i}]}.00.dta
cp CentralFit_AlphaS_${alphas[${i}]}/${BaseName}.00.pds $ResultDIR/${BaseName}_${alphas[${i}]}.00.pds
cp CentralFit_AlphaS_${alphas[${i}]}/${BaseName}.00.sum $ResultDIR/${BaseName}_${alphas[${i}]}.00.sum

done

