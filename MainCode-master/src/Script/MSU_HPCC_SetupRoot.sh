#!/bin/bash
SHELL_FOLDER=$(pwd)

export PATH=/opt/software/powertools/bin:/opt/software/MATLAB/2018a:/opt/software/MATLAB/2018a/bin:/opt/software/Java/1.8.0_152:/opt/software/Java/1.8.0_152/bin:/opt/software/Python/3.6.4-foss-2018a/bin:/opt/software/SQLite/3.21.0-GCCcore-6.4.0/bin:/opt/software/Tcl/8.6.8-GCCcore-6.4.0/bin:/opt/software/libreadline/7.0-GCCcore-6.4.0/bin:/opt/software/ncurses/6.0-GCCcore-6.4.0/bin:/opt/software/bzip2/1.0.6-GCCcore-6.4.0/bin:/usr/lib64/qt-3.3/bin:/opt/software/core/lua/lua/bin:/usr/local/bin:/usr/bin:/usr/local/sbin:/usr/sbin:/usr/local/hpcc/bin:/usr/lpp/mmfs/bin:/opt/ibutils/bin:/opt/puppetlabs/bin:/opt/dell/srvadmin/bin

export LD_LIBRARY_PATH=/opt/software/Java/1.8.0_152/lib:/opt/software/Python/3.6.4-foss-2018a/lib:/opt/software/libffi/3.2.1-GCCcore-6.4.0/lib64:/opt/software/libffi/3.2.1-GCCcore-6.4.0/lib:/opt/software/SQLite/3.21.0-GCCcore-6.4.0/lib:/opt/software/Tcl/8.6.8-GCCcore-6.4.0/lib:/opt/software/libreadline/7.0-GCCcore-6.4.0/lib:/opt/software/ncurses/6.0-GCCcore-6.4.0/lib:/opt/software/Boost/1.67.0-foss-2018a/lib:/opt/software/bzip2/1.0.6-GCCcore-6.4.0/lib

export LD_LIBRARY_PATH=/opt/software/GMP/6.1.2-GCCcore-8.3.0/lib:$LD_LIBRARY_PATH
export LD_LIBRARY_PATH=/opt/software/MPFR/4.0.2-GCCcore-8.3.0/lib:$LD_LIBRARY_PATH

export LD_LIBRARY_PATH=/opt/software/zlib/1.2.11-GCCcore-8.3.0/lib:$LD_LIBRARY_PATH

export LD_LIBRARY_PATH=/opt/software/tbb/2020.2-GCCcore-8.3.0/lib:$LD_LIBRARY_PATH
export LD_LIBRARY_PATH=/opt/software/tbb/2020.2-GCCcore-8.3.0/lib64:$LD_LIBRARY_PATH

export PATH=/opt/software/X11/20190717-GCCcore-8.3.0/bin:$PATH
export LD_LIBRARY_PATH=/opt/software/X11/20190717-GCCcore-8.3.0/lib:$LD_LIBRARY_PATH

export PATH=/opt/software/OpenBLAS/0.3.7-GCC-8.3.0/bin:$PATH
export LD_LIBRARY_PATH=/opt/software/OpenBLAS/0.3.7-GCC-8.3.0/lib:$LD_LIBRARY_PATH

export PATH=/opt/software/imkl/2019.1.144-gompi-2019a/bin:$PATH
export LD_LIBRARY_PATH=/opt/software/imkl/2019.1.144-gompi-2019a/lib/intel64:$LD_LIBRARY_PATH
export PATH=/opt/software/imkl/2019.1.144-gompi-2019a/mkl/bin:$PATH
export LD_LIBRARY_PATH=/opt/software/imkl/2019.1.144-gompi-2019a/lib/mkl/intel64:$LD_LIBRARY_PATH

export PATH=/opt/software/FFTW/3.3.8-gompi-2019a/bin:$PATH
export LD_LIBRARY_PATH=/opt/software/FFTW/3.3.8-gompi-2019a/lib:$LD_LIBRARY_PATH

export LD_LIBRARY_PATH=/opt/software/ScaLAPACK/2.0.2-gompi-2019a-OpenBLAS-0.3.5/lib:$LD_LIBRARY_PATH

export PATH=/opt/software/libpng/1.6.37-GCCcore-8.3.0/bin:$PATH
export LD_LIBRARY_PATH=/opt/software/libpng/1.6.37-GCCcore-8.3.0/lib:$LD_LIBRARY_PATH

export PATH=/opt/software/CMake/3.17.1-GCCcore-8.3.0/bin:$PATH

export LD_LIBRARY_PATH=/opt/software/binutils/2.32-GCCcore-8.3.0/lib:$LD_LIBRARY_PATH
export LD_LIBRARY_PATH=/opt/software/GCCcore/8.3.0-new/lib:$LD_LIBRARY_PATH
export LD_LIBRARY_PATH=/opt/software/GCCcore/8.3.0-new/lib64:$LD_LIBRARY_PATH
export LIBRARY_PATH=/opt/software/GCCcore/8.3.0-new/lib64:$LIBRARY_PATH
export LD_LIBRARY_PATH=/opt/software/GCCcore/8.3.0-new/lib/gcc/x86_64-pc-linux-gnu/8.3.0:$LD_LIBRARY_PATH

export PATH=/opt/software/OpenMPI/4.0.1-GCC-8.3.0-2.32/bin:$PATH
export LD_LIBRARY_PATH=/opt/software/OpenMPI/4.0.1-GCC-8.3.0-2.32/lib:$LD_LIBRARY_PATH

export CC=/opt/software/GCCcore/8.3.0-new/bin/gcc
export CXX=/opt/software/GCCcore/8.3.0-new/bin/g++
export PATH=/opt/software/binutils/2.32-GCCcore-8.3.0/bin:$PATH
export PATH=/opt/software/GCCcore/8.3.0-new/bin:$PATH
export FC=/opt/software/GCCcore/8.3.0-new/bin/gfortran

#MCFM-10.3
export OMP_STACKSIZE=100G
export OMP_NUM_THREADS=96

cd /mnt/home/f0104888/ROOT_6_20_06/bin
source thisroot.sh
cd $SHELL_FOLDER

