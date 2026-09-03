#!/bin/bash

alphasCentral=0.1164
alphasUp=0.1151
alphasDown=0.1177

TargetDIR=AlphaSEVSet_T10
BaseName=i2TAn3m248

cp f06b.x ${TargetDIR}

cp CentralFit_AlphaS_${alphasCentral}/${BaseName}.00.inp ${TargetDIR}/${BaseName}.00.inp
cp CentralFit_AlphaS_${alphasCentral}/${BaseName}.00.log ${TargetDIR}/${BaseName}.00.log
cp CentralFit_AlphaS_${alphasCentral}/${BaseName}.00.dta ${TargetDIR}/${BaseName}.00.dta
cp CentralFit_AlphaS_${alphasCentral}/${BaseName}.00.pds ${TargetDIR}/${BaseName}.00.pds
cp CentralFit_AlphaS_${alphasCentral}/${BaseName}.00.sum ${TargetDIR}/${BaseName}.00.sum

cp CentralFit_AlphaS_${alphasUp}/${BaseName}.00.inp ${TargetDIR}/${BaseName}.01.inp
cp CentralFit_AlphaS_${alphasUp}/${BaseName}.00.log ${TargetDIR}/${BaseName}.01.log
cp CentralFit_AlphaS_${alphasUp}/${BaseName}.00.dta ${TargetDIR}/${BaseName}.01.dta
cp CentralFit_AlphaS_${alphasUp}/${BaseName}.00.pds ${TargetDIR}/${BaseName}.01.pds
cp CentralFit_AlphaS_${alphasUp}/${BaseName}.00.sum ${TargetDIR}/${BaseName}.01.sum

cp CentralFit_AlphaS_${alphasDown}/${BaseName}.00.inp ${TargetDIR}/${BaseName}.02.inp
cp CentralFit_AlphaS_${alphasDown}/${BaseName}.00.log ${TargetDIR}/${BaseName}.02.log
cp CentralFit_AlphaS_${alphasDown}/${BaseName}.00.dta ${TargetDIR}/${BaseName}.02.dta
cp CentralFit_AlphaS_${alphasDown}/${BaseName}.00.pds ${TargetDIR}/${BaseName}.02.pds
cp CentralFit_AlphaS_${alphasDown}/${BaseName}.00.sum ${TargetDIR}/${BaseName}.02.sum

sed -i '111a\
 2 48       0  1.0   0\
       1.0000  1.0   0\
 2 11       0  1.0   0\
       1.0000  1.0   0\
 2 12       0  1.0   0\
       1.0000  1.0   0\
 2 18       0  1.0   0\
       1.0000  1.0   0\
 2 14       0  1.0   0\
       1.0000  1.0   0\
 2 15       0  1.0   0\
       1.0000  1.0   0\
 2 17       0  1.0   0\
       1.0000  1.0   0\
 5 21       0  1.0   0\
       1.0000  1.0   0   0.0  111  8.8000E+01  8.8000E+01  8.8000E+01  8.8000E+01  8.8000E+01  8.8000E+01    88  ATL13ytt_HTO2\
 5 28       0  1.0   0\
       1.0000  1.0   0   0.0  111  8.8000E+01  8.8000E+01  8.8000E+01  8.8000E+01  8.8000E+01  8.8000E+01    88  CMS13ytt_HTO2\
 5 87       0  1.0   0\
       1.0000  1.0   0   0.0  111  8.8000E+01  8.8000E+01  8.8000E+01  8.8000E+01  8.8000E+01  8.8000E+01    88  ATL13LepJ_MttYttYBHTtt_HTO2\
 5 81       0  1.0   0\
       1.0000  1.0   0   0.0  111  8.8000E+01  8.8000E+01  8.8000E+01  8.8000E+01  8.8000E+01  8.8000E+01    88  CMS13lj21mtt_HTO2\
 5 53       0  1.0   99 | 5 1*336\
       1.0000  1.0   0   0.0  121  8.8000E+01  8.8000E+01  8.8000E+01  8.8000E+01  8.8000E+01  8.8000E+01    88  ATL8_Inc_pTjDecor\
 5 54       0  1.0   99 | 5 1*342\
       1.0000  1.0   0   0.0  121  8.8000E+01  8.8000E+01  8.8000E+01  8.8000E+01  8.8000E+01  8.8000E+01    88  ATL13_Inc_pTjDecor\
 5 55       0  1.0   99 | 5 1*30\
       1.0000  1.0   0   0.0  121  8.8000E+01  8.8000E+01  8.8000E+01  8.8000E+01  8.8000E+01  8.8000E+01    88  CMS13_Inc_pTj' ${TargetDIR}/${BaseName}.00.inp

sed -i '111a\
 2 48       0  1.0   0\
       1.0000  1.0   0\
 2 11       0  1.0   0\
       1.0000  1.0   0\
 2 12       0  1.0   0\
       1.0000  1.0   0\
 2 18       0  1.0   0\
       1.0000  1.0   0\
 2 14       0  1.0   0\
       1.0000  1.0   0\
 2 15       0  1.0   0\
       1.0000  1.0   0\
 2 17       0  1.0   0\
       1.0000  1.0   0\
 5 21       0  1.0   0\
       1.0000  1.0   0   0.0  111  8.8000E+01  8.8000E+01  8.8000E+01  8.8000E+01  8.8000E+01  8.8000E+01    88  ATL13ytt_HTO2\
 5 28       0  1.0   0\
       1.0000  1.0   0   0.0  111  8.8000E+01  8.8000E+01  8.8000E+01  8.8000E+01  8.8000E+01  8.8000E+01    88  CMS13ytt_HTO2\
 5 87       0  1.0   0\
       1.0000  1.0   0   0.0  111  8.8000E+01  8.8000E+01  8.8000E+01  8.8000E+01  8.8000E+01  8.8000E+01    88  ATL13LepJ_MttYttYBHTtt_HTO2\
 5 81       0  1.0   0\
       1.0000  1.0   0   0.0  111  8.8000E+01  8.8000E+01  8.8000E+01  8.8000E+01  8.8000E+01  8.8000E+01    88  CMS13lj21mtt_HTO2\
 5 53       0  1.0   99 | 5 1*336\
       1.0000  1.0   0   0.0  121  8.8000E+01  8.8000E+01  8.8000E+01  8.8000E+01  8.8000E+01  8.8000E+01    88  ATL8_Inc_pTjDecor\
 5 54       0  1.0   99 | 5 1*342\
       1.0000  1.0   0   0.0  121  8.8000E+01  8.8000E+01  8.8000E+01  8.8000E+01  8.8000E+01  8.8000E+01    88  ATL13_Inc_pTjDecor\
 5 55       0  1.0   99 | 5 1*30\
       1.0000  1.0   0   0.0  121  8.8000E+01  8.8000E+01  8.8000E+01  8.8000E+01  8.8000E+01  8.8000E+01    88  CMS13_Inc_pTj' ${TargetDIR}/${BaseName}.01.inp

sed -i '111a\
 2 48       0  1.0   0\
       1.0000  1.0   0\
 2 11       0  1.0   0\
       1.0000  1.0   0\
 2 12       0  1.0   0\
       1.0000  1.0   0\
 2 18       0  1.0   0\
       1.0000  1.0   0\
 2 14       0  1.0   0\
       1.0000  1.0   0\
 2 15       0  1.0   0\
       1.0000  1.0   0\
 2 17       0  1.0   0\
       1.0000  1.0   0\
 5 21       0  1.0   0\
       1.0000  1.0   0   0.0  111  8.8000E+01  8.8000E+01  8.8000E+01  8.8000E+01  8.8000E+01  8.8000E+01    88  ATL13ytt_HTO2\
 5 28       0  1.0   0\
       1.0000  1.0   0   0.0  111  8.8000E+01  8.8000E+01  8.8000E+01  8.8000E+01  8.8000E+01  8.8000E+01    88  CMS13ytt_HTO2\
 5 87       0  1.0   0\
       1.0000  1.0   0   0.0  111  8.8000E+01  8.8000E+01  8.8000E+01  8.8000E+01  8.8000E+01  8.8000E+01    88  ATL13LepJ_MttYttYBHTtt_HTO2\
 5 81       0  1.0   0\
       1.0000  1.0   0   0.0  111  8.8000E+01  8.8000E+01  8.8000E+01  8.8000E+01  8.8000E+01  8.8000E+01    88  CMS13lj21mtt_HTO2\
 5 53       0  1.0   99 | 5 1*336\
       1.0000  1.0   0   0.0  121  8.8000E+01  8.8000E+01  8.8000E+01  8.8000E+01  8.8000E+01  8.8000E+01    88  ATL8_Inc_pTjDecor\
 5 54       0  1.0   99 | 5 1*342\
       1.0000  1.0   0   0.0  121  8.8000E+01  8.8000E+01  8.8000E+01  8.8000E+01  8.8000E+01  8.8000E+01    88  ATL13_Inc_pTjDecor\
 5 55       0  1.0   99 | 5 1*30\
       1.0000  1.0   0   0.0  121  8.8000E+01  8.8000E+01  8.8000E+01  8.8000E+01  8.8000E+01  8.8000E+01    88  CMS13_Inc_pTj' ${TargetDIR}/${BaseName}.02.inp

sed -i "3c '1 Run ID:                   :'   '${BaseName}.01'   '${BaseName}.01'" ${TargetDIR}/${BaseName}.01.inp
sed -i "3c '1 Run ID:                   :'   '${BaseName}.02'   '${BaseName}.02'" ${TargetDIR}/${BaseName}.02.inp

sed -i "33c ++ 5:   52    data sets                           Choice of Expt Data Sets ++++++" ${TargetDIR}/${BaseName}.00.inp
sed -i "33c ++ 5:   52    data sets                           Choice of Expt Data Sets ++++++" ${TargetDIR}/${BaseName}.01.inp
sed -i "33c ++ 5:   52    data sets                           Choice of Expt Data Sets ++++++" ${TargetDIR}/${BaseName}.02.inp

cd ${TargetDIR}

nohup ./f06b.x ${BaseName}.00.inp > ${BaseName}.00.con &
nohup ./f06b.x ${BaseName}.01.inp > ${BaseName}.01.con &
nohup ./f06b.x ${BaseName}.02.inp > ${BaseName}.02.con &

cd ..

