#!/bin/bash
setupATLAS
lsetup "root 6.20.06-x86_64-centos7-gcc8-opt"
#lsetup "views LCG_94 x86_64-slc6-gcc62-opt"
#lsetup "root 6.14.04-x86_64-slc6-gcc62-opt"
lsetup "cmake 3.14.0"
export LHAPDFSYS=/home/yfu/LHAPDF
export PATH=/home/yfu/LHAPDF/bin:${PATH}
export LD_LIBRARY_PATH=/home/yfu/LHAPDF/lib:${LD_LIBRARY_PATH}
export LD_LIBRARY_PATH=/msu/data/cynisca/yfu/pku_resbos/SourceCode/resbos2/build/lib64:${LD_LIBRARY_PATH}
export LD_LIBRARY_PATH=/home/yfu/HOPPET/lib:${LD_LIBRARY_PATH}
export LD_LIBRARY_PATH=/home/yfu/BAT/lib:${LD_LIBRARY_PATH}
export PATH=/home/yfu/HOPPET/bin:${PATH}
export PATH=/home/yfu/BAT/bin:${PATH}
export LD_LIBRARY_PATH=/msu/data/cynisca/yfu/pku_resbos/SourceCode/resbos2/build/_deps/yaml-cpp-build:${LD_LIBRARY_PATH}

#for analysis code
export PATH=${PATH}:/msu/data/cynisca/yfu/MainCode/build/bin
export LD_LIBRARY_PATH=${LD_LIBRARY_PATH}:/msu/data/cynisca/yfu/MainCode/build/lib


