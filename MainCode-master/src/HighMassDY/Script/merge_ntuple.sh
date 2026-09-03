#!/bin/bash
WORKDIR=$PWD

Channel[1]=Data15
Channel[2]=Data16
Channel[3]=Data17
Channel[4]=Data18
Channel[5]=DrellYan_ee_mc16a
Channel[6]=DrellYan_mm_mc16a
Channel[7]=PI_mc16a
Channel[8]=Diboson_mc16a
Channel[9]=TopQuark_mc16a
Channel[10]=Ztautau_mc16a
Channel[11]=Wjets_mc16a
Channel[12]=DrellYan_ee_mc16d
Channel[13]=DrellYan_mm_mc16d
Channel[14]=PI_mc16d
Channel[15]=Diboson_mc16d
Channel[16]=TopQuark_mc16d
Channel[17]=Ztautau_mc16d
Channel[18]=Wjets_mc16d
Channel[19]=DrellYan_ee_mc16e
Channel[20]=DrellYan_mm_mc16e
Channel[21]=PI_mc16e
Channel[22]=Diboson_mc16e
Channel[23]=TopQuark_mc16e
Channel[24]=Ztautau_mc16e
Channel[25]=Wjets_mc16e

for((i=19;i<=25;i++)); do
cd $WORKDIR
cp $WORKDIR/write.sh $WORKDIR/${Channel[${i}]}
cd $WORKDIR/${Channel[${i}]}
sh write.sh >> data.list
echo ${Channel[${i}]}
hadd output_nominal_Loose_${Channel[${i}]}_nomWeight.root @data.list
done
cd $WORKDIR
