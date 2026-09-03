#!/bin/bash
#setupATLAS
WORKDIR=$PWD
cd build
asetup --restore
source x86_64-*/setup.sh
cd $WORKDIR
export PATHONPATH=${PATHONPATH}:/lustre/AtlUser/yfu/Repository/WZPolarization/source/NtupleMaker/share
