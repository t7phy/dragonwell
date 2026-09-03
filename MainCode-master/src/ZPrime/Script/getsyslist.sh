#!/bin/bash
WORKDIR=$PWD

ElSysName[0]=nominal
ElSysName[1]=Luminosity
ElSysName[2]=PIVariation
ElSysName[3]=Di-boson
ElSysName[4]=LepSF_EL_Reco
ElSysName[5]=LepSF_EL_Isol
ElSysName[6]=LepSF_EL_Trigger
ElSysName[7]=LepSF_EL_ID_1
ElSysName[8]=LepSF_EL_ID_2
ElSysName[9]=LepSF_EL_ID_3
ElSysName[10]=LepSF_EL_ID_4
ElSysName[11]=LepSF_EL_ID_5
ElSysName[12]=LepSF_EL_ID_6
ElSysName[13]=LepSF_EL_ID_7
ElSysName[14]=LepSF_EL_ID_8
ElSysName[15]=LepSF_EL_ID_9
ElSysName[16]=LepSF_EL_ID_10
ElSysName[17]=LepSF_EL_ID_11
ElSysName[18]=LepSF_EL_ID_12
ElSysName[19]=LepSF_EL_ID_13
ElSysName[20]=LepSF_EL_ID_14
ElSysName[21]=LepSF_EL_ID_15
ElSysName[22]=LepSF_EL_ID_16
ElSysName[23]=LepSF_EL_ID_17
ElSysName[24]=LepSF_EL_ID_18
ElSysName[25]=LepSF_EL_ID_19
ElSysName[26]=LepSF_EL_ID_20
ElSysName[27]=LepSF_EL_ID_21
ElSysName[28]=LepSF_EL_ID_22
ElSysName[29]=LepSF_EL_ID_23
ElSysName[30]=LepSF_EL_ID_24
ElSysName[31]=LepSF_EL_ID_25
ElSysName[32]=LepSF_EL_ID_26
ElSysName[33]=LepSF_EL_ID_27
ElSysName[34]=LepSF_EL_ID_28
ElSysName[35]=LepSF_EL_ID_29
ElSysName[36]=LepSF_EL_ID_30
ElSysName[37]=LepSF_EL_ID_31
ElSysName[38]=LepSF_EL_ID_32
ElSysName[39]=LepSF_EL_ID_33
ElSysName[40]=LepSF_EL_ID_34
ElSysName[41]=LepSF_EL_ChargeMisID_SYST
ElSysName[42]=LepSF_EL_ChargeMisID_STAT
ElSysName[43]=HardScatterMCAdNlo
ElSysName[44]=FragHadModelHerwig7
ElSysName[45]=ISRVariationNtuple
ElSysName[46]=TopMassVariation
ElSysName[47]=EG_RESOLUTION_AF2
ElSysName[48]=EG_RESOLUTION_MATERIALCALO
ElSysName[49]=EG_RESOLUTION_MATERIALCRYO
ElSysName[50]=EG_RESOLUTION_MATERIALGAP
ElSysName[51]=EG_RESOLUTION_MATERIALIBL
ElSysName[52]=EG_RESOLUTION_MATERIALPP0
ElSysName[53]=EG_RESOLUTION_PILEUP
ElSysName[54]=EG_RESOLUTION_SAMPLINGTERM
ElSysName[55]=EG_RESOLUTION_ZSMEARING
ElSysName[56]=EG_SCALE_E4SCINTILLATOR
ElSysName[57]=EG_SCALE_G4
ElSysName[58]=EG_SCALE_L1GAIN
ElSysName[59]=EG_SCALE_L2GAIN
ElSysName[60]=EG_SCALE_LARCALIB
ElSysName[61]=EG_SCALE_LARELECCALIB
ElSysName[62]=EG_SCALE_LARELECUNCONV
ElSysName[63]=EG_SCALE_LARUNCONVCALIB
ElSysName[64]=EG_SCALE_MATCALO
ElSysName[65]=EG_SCALE_MATCRYO
ElSysName[66]=EG_SCALE_MATID
ElSysName[67]=EG_SCALE_MATPP0
ElSysName[68]=EG_SCALE_PEDESTAL
ElSysName[69]=EG_SCALE_PS_BARREL_B12
ElSysName[70]=EG_SCALE_TOPOCLUSTER_THRES
ElSysName[71]=EG_SCALE_WTOTS1
ElSysName[72]=EG_SCALE_ZEESYST
ElSysName[73]=EG_SCALE_PS
ElSysName[74]=EG_SCALE_S12
ElSysName[75]=TopDD_Mass_Stat
ElSysName[76]=TopDD_Mass_CosTheta_Stat
ElSysName[77]=TopDD_Mass_Rapidity_Stat
ElSysName[78]=Fake_Matrix_Electron



MuSysName[0]=nominal
MuSysName[1]=Luminosity
MuSysName[2]=PIVariation
MuSysName[3]=Di-boson
MuSysName[4]=HardScatterMCAdNlo
MuSysName[5]=FragHadModelHerwig7
MuSysName[6]=ISRVariationNtuple
MuSysName[7]=TopMassVariation
MuSysName[8]=LepSF_MU_TTVA
MuSysName[9]=LepSF_MU_TTVA_STAT
MuSysName[10]=LepSF_MU_ID_STAT
MuSysName[11]=LepSF_MU_ID_STAT_LOWPT
MuSysName[12]=LepSF_MU_ID_SYST
MuSysName[13]=LepSF_MU_ID_SYST_LOWPT
MuSysName[14]=LepSF_MU_Trigger
MuSysName[15]=LepSF_MU_Isol
MuSysName[16]=LepSF_MU_ID_BAD_MUON_VETO
MuSysName[17]=MUON_SAGITTA_RESBIAS
MuSysName[18]=MUON_ID
MuSysName[19]=MUON_MS
MuSysName[20]=MUON_SCALE
MuSysName[21]=MUON_CB
MuSysName[22]=TopDD_Mass_Stat
MuSysName[23]=TopDD_Mass_CosTheta_Stat
MuSysName[24]=TopDD_Mass_Rapidity_Stat
MuSysName[25]=Fake_Matrix_Muon

if [ -f "ElSys.list" ]; then
    rm ElSys.list
fi

if [ -f "MuSys.list" ]; then
    rm MuSys.list
fi


for((i=0;i<=78;i++)); do
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

FullSysName=${ElSysName[${i}]}${VarName}
echo $FullSysName/MC_results_${FullSysName}.root >> ElSys.list

done

done

for((i=0;i<=25;i++)); do
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

FullSysName=${MuSysName[${i}]}${VarName}
echo $FullSysName/MC_results_${FullSysName}.root >> MuSys.list

done

done

cd $WORKDIR

