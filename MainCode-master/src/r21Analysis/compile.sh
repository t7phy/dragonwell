#!/bin/bash
WORKDIR=$PWD
cd build
#asetup 21.2.75,AnalysisBase
cmake ../source/
make -j
source x86_64-*/setup.sh
cd $WORKDIR
