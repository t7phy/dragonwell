#!/bin/bash
setupATLAS
lsetup "root 6.30.02-x86_64-centos7-gcc11-opt"
lsetup "cmake 3.27.5"

export PATH=${PATH}:/msu/data/t3work12/yaofu/AnalysisOnly/build/bin
export LD_LIBRARY_PATH=${LD_LIBRARY_PATH}:/msu/data/t3work12/yaofu/AnalysisOnly/build/lib

#ResBos2
export LD_LIBRARY_PATH=/msu/data/t3work12/yaofu/pku_resbos/SourceCode/resbos2/build/lib64:${LD_LIBRARY_PATH}
export LD_LIBRARY_PATH=/msu/data/t3work12/yaofu/pku_resbos/SourceCode/resbos2/build/_deps/yaml-cpp-build:${LD_LIBRARY_PATH}
export PATH=/msu/data/t3work12/yaofu/pku_resbos/SourceCode/resbos2/build/bin:${PATH}

#LHAPDF
export LHAPDF_ROOT_DIR=/home/yaofu/LHAPDF/
export LHAPDF_PDF_DIR=${LHAPDF_ROOT_DIR}/share/LHAPDF
export PATH=$PATH:${LHAPDF_ROOT_DIR}/bin
export LD_LIBRARY_PATH=${LD_LIBRARY_PATH}:${LHAPDF_ROOT_DIR}/lib

#Hoppet
#export Hoppet_ROOT_DIR=/home/yaofu/HOPPET/
#export PATH=$PATH:/home/yaofu/HOPPET/bin
#export LD_LIBRARY_PATH=${LD_LIBRARY_PATH}:/home/yaofu/HOPPET/lib

#ApplGrid
#export APPLGRID_ROOT_DIR=/home/yaofu/APPLGRID/
#export PATH=$PATH:/home/yaofu/APPLGRID/bin
#export LD_LIBRARY_PATH=${LD_LIBRARY_PATH}:/home/yaofu/APPLGRID/lib
#export PDFPATH=`applgrid-config --share`

#Fast NLO
#export FASTNLO_ROOT_DIR=/home/yaofu/FASTNLO/
#export LD_LIBRARY_PATH=/home/yaofu/FASTNLO/lib:${LD_LIBRARY_PATH}
#export PATH=/home/yaofu/FASTNLO/bin:${PATH}

#yaml
#export YAML_ROOT_DIR=/home/yaofu/yaml-cpp-0.8.0/build
#export LD_LIBRARY_PATH=/home/yaofu/yaml-cpp-0.8.0/build/lib64:${LD_LIBRARY_PATH}

#BAT
#export BAT_ROOT_DIR=/home/yaofu/BAT/
#export PATH=$PATH:/home/yaofu/BAT/bin
#export LD_LIBRARY_PATH=${LD_LIBRARY_PATH}:/home/yaofu/BAT/lib

#RooUnfold
#export ROOUNFOLD_ROOT_DIR=/home/yaofu/RooUnfold/build
#export PYTHONPATH=${PYTHONPATH}:/home/yaofu/RooUnfold/build
#export LD_LIBRARY_PATH=${LD_LIBRARY_PATH}:/home/yaofu/RooUnfold/build

#CPP
#export PATH=/home/yaofu/gnuplot/bin:${PATH}
#export PATH=/cvmfs/sft.cern.ch/lcg/external/texlive/2016/bin/x86_64-linux:$PATH

#MCFM-10.3
#export OMP_STACKSIZE=100G

#python3 -m pip install --upgrade pip
#python3 -m pip install --user numpy
#python3 -m pip install --user matplotlib
#python3 -m pip install --user pycairo
#python3 -m pip install --user uproot
#python3 -m pip install --user "hist[plot]"
#python3 -m pip install --user pandas
#python3 -m pip install --user pyyaml
#python3 -m pip install --user scipy

