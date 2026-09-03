#!/bin/bash

module purge
module load GCC/13.2.0
module load GCCcore/13.2.0
module load libtool/2.4.7-GCCcore-13.2.0
module load GMP/6.3.0-GCCcore-13.2.0
module load zlib/1.2.13-GCCcore-13.2.0
module load OpenBLAS/0.3.24-GCC-13.2.0
module load libpng/1.6.40-GCCcore-13.2.0
module load CMake/3.27.6-GCCcore-13.2.0
module load binutils/2.40-GCCcore-13.2.0
module load OpenMPI/4.1.6-GCC-13.2.0
module load Python/3.11.5-GCCcore-13.2.0
module load Bison/3.8.2-GCCcore-13.2.0
module load GSL/2.7-GCC-13.2.0

source /mnt/home/fuyao3/ROOT_6_30_02/bin/thisroot.sh

#LHAPDF
export LHAPDF_ROOT_DIR=/mnt/home/fuyao3/GCC13/LHAPDF/
export LHAPDF_PDF_DIR=${LHAPDF_ROOT_DIR}/share/LHAPDF
export PATH=$PATH:${LHAPDF_ROOT_DIR}/bin
export LD_LIBRARY_PATH=${LD_LIBRARY_PATH}:${LHAPDF_ROOT_DIR}/lib

#Hoppet
export Hoppet_ROOT_DIR=/mnt/home/fuyao3/GCC13/HOPPET/
export PATH=$PATH:${Hoppet_ROOT_DIR}/bin
export LD_LIBRARY_PATH=${LD_LIBRARY_PATH}:${Hoppet_ROOT_DIR}/lib

#ApplGrid
export APPLGRID_ROOT_DIR=/mnt/home/fuyao3/GCC13/APPLGRID/
export PATH=$PATH:${APPLGRID_ROOT_DIR}/bin
export LD_LIBRARY_PATH=${LD_LIBRARY_PATH}:${APPLGRID_ROOT_DIR}/lib
export PDFPATH=`applgrid-config --share`

#Fast NLO
export FASTNLO_ROOT_DIR=/mnt/home/fuyao3/GCC13/FASTNLO/
export LD_LIBRARY_PATH=${FASTNLO_ROOT_DIR}/lib:${LD_LIBRARY_PATH}
export PATH=${FASTNLO_ROOT_DIR}/bin:${PATH}

#yaml
export YAML_ROOT_DIR=/mnt/home/fuyao3/GCC13/yaml-cpp-0.8.0/build
export LD_LIBRARY_PATH=/mnt/home/fuyao3/GCC13/yaml-cpp-0.8.0/build/lib64:${LD_LIBRARY_PATH}

#BAT
export BAT_ROOT_DIR=/mnt/home/fuyao3/GCC13/BAT/
export PATH=$PATH:${BAT_ROOT_DIR}/bin
export LD_LIBRARY_PATH=${LD_LIBRARY_PATH}:${BAT_ROOT_DIR}/lib

#apfel APFELgrid swig
export apfelxx_ROOT_DIR=/mnt/home/fuyao3/GCC13/apfelxx/build/
export PATH=${apfelxx_ROOT_DIR}/bin:$PATH
export LD_LIBRARY_PATH=${apfelxx_ROOT_DIR}/lib:${LD_LIBRARY_PATH}
export PATH=/mnt/home/fuyao3/GCC13/apfel/build/bin:$PATH
export LD_LIBRARY_PATH=/mnt/home/fuyao3/GCC13/apfel/build/lib:${LD_LIBRARY_PATH}
export PATH=/mnt/home/fuyao3/GCC13/SWIG/bin:$PATH

#Cuba (For HELLx grids)
export CUBA_PATH=/mnt/home/fuyao3/GCC13/CUBA/
export PATH=$PATH:${CUBA_PATH}/bin
export LD_LIBRARY_PATH=${LD_LIBRARY_PATH}:${CUBA_PATH}/lib

#json
export json_ROOT_DIR=/mnt/home/fuyao3/json/build

#Main Code
export PATH=${PATH}:/mnt/home/fuyao3/Work/MainCode/build/bin
export LD_LIBRARY_PATH=${LD_LIBRARY_PATH}:/mnt/home/fuyao3/Work/MainCode/build/lib
export PYTHONPATH=$PYTHONPATH:/mnt/home/fuyao3/Work/MainCode/build/src/Calculation

#python3 -m pip install --upgrade pip
#python3 -m pip install --user numpy
#python3 -m pip install --user matplotlib
#python3 -m pip install --user pycairo
#python3 -m pip install --user uproot
#python3 -m pip install --user "hist[plot]"
#python3 -m pip install --user pandas
#python3 -m pip install --user pyyaml
#python3 -m pip install --user scipy
#python3 -m pip install --user tensorflow
#python3 -m pip install --user tensorflow-probability[tf]

