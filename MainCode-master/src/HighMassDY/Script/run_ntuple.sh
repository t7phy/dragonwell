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

nFile=`cat SumOfWeight_${Channel[${i}]}.list |wc -l`
mkdir $WORKDIR/${Channel[${i}]}
cp SumOfWeight_${Channel[${i}]}.list $WORKDIR/${Channel[${i}]}/SumOfWeight_${Channel[${i}]}.list
cd $WORKDIR/${Channel[${i}]}

for((ifile=1;ifile<=${nFile};ifile++)); do

cd $WORKDIR/${Channel[${i}]}
mkdir $WORKDIR/${Channel[${i}]}/JOB${ifile}
FileName=`cat SumOfWeight_${Channel[${i}]}.list |head -${ifile} |tail -1`
echo $FileName
echo $FileName >> $WORKDIR/${Channel[${i}]}/JOB${ifile}/data.list
cp $WORKDIR/${Channel[${i}]}/SumOfWeight_${Channel[${i}]}.list $WORKDIR/${Channel[${i}]}/JOB${ifile}/SumOfWeight.list
cp $WORKDIR/cardfile.in $WORKDIR/${Channel[${i}]}/JOB${ifile}
cd $WORKDIR/${Channel[${i}]}/JOB${ifile}

cat>>myANA.sh <<EOF
#!/bin/bash
export ATLAS_LOCAL_ROOT_BASE=/cvmfs/atlas.cern.ch/repo/ATLASLocalRootBase
source ${ATLAS_LOCAL_ROOT_BASE}/user/atlasLocalSetup.sh
lsetup "root 6.30.02-x86_64-centos7-gcc11-opt"
lsetup "cmake 3.27.5"
export PATH=${PATH}:/msu/data/t3work12/yaofu/AnalysisOnly/build/bin
export LD_LIBRARY_PATH=${LD_LIBRARY_PATH}:/msu/data/t3work12/yaofu/AnalysisOnly/build/lib
export LHAPDF_ROOT_DIR=/home/yaofu/LHAPDF/
export LHAPDF_PDF_DIR=${LHAPDF_ROOT_DIR}/share/LHAPDF
export PATH=$PATH:${LHAPDF_ROOT_DIR}/bin
export LD_LIBRARY_PATH=${LD_LIBRARY_PATH}:${LHAPDF_ROOT_DIR}/lib

cd $WORKDIR/${Channel[${i}]}/JOB${ifile}
loopMC cardfile.in
EOF

source ~/script/CondorCommon.sh mySUB_Ntuple_$i_$ifile

done

done

cd $WORKDIR
