#!/bin/bash
WORKDIR=$PWD

SysName[0]=nominal
SysName[1]=Luminosity
SysName[2]=PIVariation
SysName[3]=Di-boson
SysName[4]=LepSF_EL_Reco
SysName[5]=LepSF_EL_Isol
SysName[6]=LepSF_EL_Trigger
SysName[7]=LepSF_EL_ID_1
SysName[8]=LepSF_EL_ID_2
SysName[9]=LepSF_EL_ID_3
SysName[10]=LepSF_EL_ID_4
SysName[11]=LepSF_EL_ID_5
SysName[12]=LepSF_EL_ID_6
SysName[13]=LepSF_EL_ID_7
SysName[14]=LepSF_EL_ID_8
SysName[15]=LepSF_EL_ID_9
SysName[16]=LepSF_EL_ID_10
SysName[17]=LepSF_EL_ID_11
SysName[18]=LepSF_EL_ID_12
SysName[19]=LepSF_EL_ID_13
SysName[20]=LepSF_EL_ID_14
SysName[21]=LepSF_EL_ID_15
SysName[22]=LepSF_EL_ID_16
SysName[23]=LepSF_EL_ID_17
SysName[24]=LepSF_EL_ID_18
SysName[25]=LepSF_EL_ID_19
SysName[26]=LepSF_EL_ID_20
SysName[27]=LepSF_EL_ID_21
SysName[28]=LepSF_EL_ID_22
SysName[29]=LepSF_EL_ID_23
SysName[30]=LepSF_EL_ID_24
SysName[31]=LepSF_EL_ID_25
SysName[32]=LepSF_EL_ID_26
SysName[33]=LepSF_EL_ID_27
SysName[34]=LepSF_EL_ID_28
SysName[35]=LepSF_EL_ID_29
SysName[36]=LepSF_EL_ID_30
SysName[37]=LepSF_EL_ID_31
SysName[38]=LepSF_EL_ID_32
SysName[39]=LepSF_EL_ID_33
SysName[40]=LepSF_EL_ID_34
SysName[41]=LepSF_EL_ChargeMisID_SYST
SysName[42]=LepSF_EL_ChargeMisID_STAT
SysName[43]=HardScatterMCAdNlo
SysName[44]=FragHadModelHerwig7
SysName[45]=ISRVariationNtuple
SysName[46]=TopMassVariation
SysName[47]=EG_RESOLUTION_AF2
SysName[48]=EG_RESOLUTION_MATERIALCALO
SysName[49]=EG_RESOLUTION_MATERIALCRYO
SysName[50]=EG_RESOLUTION_MATERIALGAP
SysName[51]=EG_RESOLUTION_MATERIALIBL
SysName[52]=EG_RESOLUTION_MATERIALPP0
SysName[53]=EG_RESOLUTION_PILEUP
SysName[54]=EG_RESOLUTION_SAMPLINGTERM
SysName[55]=EG_RESOLUTION_ZSMEARING
SysName[56]=EG_SCALE_E4SCINTILLATOR
SysName[57]=EG_SCALE_G4
SysName[58]=EG_SCALE_L1GAIN
SysName[59]=EG_SCALE_L2GAIN
SysName[60]=EG_SCALE_LARCALIB
SysName[61]=EG_SCALE_LARELECCALIB
SysName[62]=EG_SCALE_LARELECUNCONV
SysName[63]=EG_SCALE_LARUNCONVCALIB
SysName[64]=EG_SCALE_MATCALO
SysName[65]=EG_SCALE_MATCRYO
SysName[66]=EG_SCALE_MATID
SysName[67]=EG_SCALE_MATPP0
SysName[68]=EG_SCALE_PEDESTAL
SysName[69]=EG_SCALE_PS_BARREL_B12
SysName[70]=EG_SCALE_TOPOCLUSTER_THRES
SysName[71]=EG_SCALE_WTOTS1
SysName[72]=EG_SCALE_ZEESYST
SysName[73]=EG_SCALE_PS
SysName[74]=EG_SCALE_S12
SysName[75]=LepSF_MU_TTVA
SysName[76]=LepSF_MU_TTVA_STAT
SysName[77]=LepSF_MU_ID_STAT
SysName[78]=LepSF_MU_ID_STAT_LOWPT
SysName[79]=LepSF_MU_ID_SYST
SysName[80]=LepSF_MU_ID_SYST_LOWPT
SysName[81]=LepSF_MU_Trigger
SysName[82]=LepSF_MU_Isol
SysName[83]=LepSF_MU_ID_BAD_MUON_VETO
SysName[84]=MUON_SAGITTA_RESBIAS
SysName[85]=MUON_ID
SysName[86]=MUON_MS
SysName[87]=MUON_SCALE
SysName[88]=MUON_CB
SysName[89]=TopDD_Mass_Stat
SysName[90]=TopDD_Mass_CosTheta_Stat
SysName[91]=TopDD_Mass_Rapidity_Stat
SysName[92]=Fake_Matrix_Electron
SysName[93]=Fake_Matrix_Muon

for((i=89;i<=93;i++)); do
cd $WORKDIR

if [ $i -eq 0 ]; then
NVar=1
else
NVar=2
fi

for((j=1;j<=${NVar};j++)); do
if [ $i -eq 0 ]; then
VarName=
else
    if [ $j -eq 1 ]; then
       VarName=__1up
    else
       VarName=__1down
    fi
fi

FullSysName=${SysName[${i}]}${VarName}
echo $FullSysName

mkdir $WORKDIR/$FullSysName
cp data.list figure.cpp $WORKDIR/$FullSysName
cd $WORKDIR/$FullSysName

cat>>cardfileTop.in <<EOF
Condor                                          *Running method (Thread/Condor)
1                                               *Thread Number
HMDY                                            *Rootfile Type (Wasymmetry/ResBos/ResBosW/....)
data.list                                       *file list
ttbar_DD.root                                   *save rootfile name
0                                               *global cut information
0                                               *is Test(1: test, 0: normal run)
0                                               *run all systematic
${FullSysName}                                     *SystematicName
TopQuark                                        *Bkg Selection
EOF

cat>>cardfile.in <<EOF
Condor                                          *Running method (Thread/Condor)
1                                               *Thread Number
HMDY                                            *Rootfile Type (Wasymmetry/ResBos/ResBosW/....)
data.list                                       *file list
MC_results.root                                 *save rootfile name
0                                               *global cut information
0                                               *is Test(1: test, 0: normal run)
0                                               *run all systematic
${FullSysName}                                     *SystematicName
all                                             *Bkg Selection
ttbar_DD.list                                   *top DD file list
EOF

cat>>ttbar_DD.list <<EOF
ttbar_DD.root TransferFactor_ee TransferFactor_mm
ttbar_DD.root TransferFactor_HighMass_CosTheta_ee TransferFactor_HighMass_CosTheta_mm
ttbar_DD.root TransferFactor_HighMass_Rapidity_ee TransferFactor_HighMass_Rapidity_mm
EOF

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

cd $WORKDIR/$FullSysName
loopMC cardfileTop.in
mv save.log topDD.log
loopMC cardfile.in
root -l -b -q figure.cpp
mv MC_results.root MC_results_${FullSysName}.root
EOF

source ~/script/CondorCommon.sh mySUB_Sys_$i_$j

done

done

cd $WORKDIR

