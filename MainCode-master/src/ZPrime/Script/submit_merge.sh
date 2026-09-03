#!/bin/bash

WORKDIR=$PWD

SampleDSID[1]=604576
SampleDSID[2]=604577
SampleDSID[3]=604578
SampleDSID[4]=604579
SampleDSID[5]=604580
SampleDSID[6]=604581
SampleDSID[7]=604582
SampleDSID[8]=604583
SampleDSID[9]=604584
SampleDSID[10]=604585
SampleDSID[11]=604586
SampleDSID[12]=604587
SampleDSID[13]=604588
SampleDSID[14]=604589
SampleDSID[15]=604590
SampleDSID[16]=604591
SampleDSID[17]=604592
SampleDSID[18]=604593
SampleDSID[19]=604594
SampleDSID[20]=602648
SampleDSID[21]=602649
SampleDSID[22]=602650
SampleDSID[23]=602651
SampleDSID[24]=602652
SampleDSID[25]=602653
SampleDSID[26]=602654
SampleDSID[27]=602655
SampleDSID[28]=602656
SampleDSID[29]=602657
SampleDSID[30]=602658
SampleDSID[31]=602659
SampleDSID[32]=602660
SampleDSID[33]=602661
SampleDSID[34]=602662
SampleDSID[35]=602663
SampleDSID[36]=602664
SampleDSID[37]=602665
SampleDSID[38]=602666

Campaign[1]=mc23a
Campaign[2]=mc23d
Campaign[3]=mc23e

for((i=1;i<=3;i++)); do

for((j=20;j<=38;j++)); do

cd $WORKDIR
mkdir $WORKDIR/${SampleDSID[${j}]}_${Campaign[${i}]}
cd $WORKDIR/${SampleDSID[${j}]}_${Campaign[${i}]}

if [ -f "merge_${SampleDSID[${j}]}_${Campaign[${i}]}.sh" ]; then
    rm merge_${SampleDSID[${j}]}_${Campaign[${i}]}.sh
fi

if [ -f "Sub_${SampleDSID[${j}]}_${Campaign[${i}]}" ]; then
    rm Sub_${SampleDSID[${j}]}_${Campaign[${i}]}
fi

cat>> merge_${SampleDSID[${j}]}_${Campaign[${i}]}.sh <<EOF
#!/bin/bash
export ATLAS_LOCAL_ROOT_BASE=/cvmfs/atlas.cern.ch/repo/ATLASLocalRootBase
export ALRB_localConfigDir=$HOME/localConfig
source ${ATLAS_LOCAL_ROOT_BASE}/user/atlasLocalSetup.sh
lsetup "root 6.30.02-x86_64-el9-gcc13-opt"
lsetup pyAMI

cd /eos/atlas/atlascerngroupdisk/phys-exotics/lpx/ANA-EXOT-2022-35_dileptonresonance/ntuples/merged_ntuples/v25_2_63_1/download_ntuples
mkdir tmp_${SampleDSID[${j}]}_${Campaign[${i}]}
python /afs/cern.ch/work/y/yafu/public/ZPrimeRepository/Dilepton_v25_2_63_new/source/LJAlgo/scripts/mergeGridOutput.py --downloadDir ./local_ntuples/ --outPath ./merged_ntuples/ --tmpPath ./tmp_${SampleDSID[${j}]}_${Campaign[${i}]}/ --nThreads 1 -isRun3 -skipJET -skipJER --dsid ${SampleDSID[${j}]} -separateDSIDs --mcCampaign ${Campaign[${i}]}
EOF

cat>> Sub_${SampleDSID[${j}]}_${Campaign[${i}]} <<EOF
universe   = vanilla

getenv     = true
executable = merge_${SampleDSID[${j}]}_${Campaign[${i}]}.sh

output = job.\$(ClusterId).out
error  = job.\$(ClusterId).err
log    = job.\$(ClusterId).log

request_cpus   = 1
request_memory = 10GB

+JobFlavour = "tomorrow"

use_x509userproxy = true
x509userproxy = /afs/cern.ch/user/y/yafu/x509proxy

queue
EOF

chmod +x merge_${SampleDSID[${j}]}_${Campaign[${i}]}.sh
condor_submit Sub_${SampleDSID[${j}]}_${Campaign[${i}]}

done

done
cd $WORKDIR
