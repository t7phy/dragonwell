#!/bin/bash
WORKDIR=$PWD
CONVDIR=/lustre/AtlUser/yfu/pku_resbos/ScaleUncertainty/resbos2_mmht
multicore=0
localrun=0
#PDFNumber=7

source ../overall.sh

#onlyCentral=0
# PDFNumber = 1: CT14HEAR2NNLO
# PDFNumber = 2: CT14nnlo
# PDFNumber = 3: MMHT2014nnlo68cl
######################Initialize the PDF Name###############################
source ~/pku_resbos/FrameWork/script/PDFInformation.sh $PDFNumber
############################################################################
if [ $onlyCentral -eq 1 ]; then
    NumberOfPDFSet=0
fi

Process=$1
if [ $Process -eq 1 ]; then
echo Running scale variation.
NProcess=15
InitialProcess=1
elif [ $Process -eq 2 ]; then
echo Running PDF uncertainty.
NProcess=${NumberOfPDFSet}
InitialProcess=0
fi

AORDER=4
BORDER=3
CORDER=2
#SCALECHOICE=MT
#NonPertFormat=BLNY

WHICHPDF=${MYPDF}_${SCALECHOICE}_pds
if [ ! -d "${WHICHPDF}_YPiece" ]; then
    mkdir ${WHICHPDF}_YPiece
fi

NJobs=`cat inp/q_grid_0.inp |wc -l`
#NBosons=4

cd $WORKDIR

for((Boson=${InitialBoson};Boson<=$NBosons;Boson++)); do
########Set Boson Type############
if [ $Boson -eq 1 ]; then
WHICHBOSON=ZU
myBOSON=zu
elif [ $Boson -eq 2 ]; then
WHICHBOSON=ZD
myBOSON=zd
elif [ $Boson -eq 3 ]; then
WHICHBOSON=W+
myBOSON=wp
elif [ $Boson -eq 4 ]; then
WHICHBOSON=W-
myBOSON=wm
fi

echo " "
echo ${myBOSON} production:
echo " "

##########Define Scale and PDF name####################
for((k=${InitialProcess};k<=$NProcess;k++)); do
if [ $k -lt 10 ]; then
PDFDIR=${PDFFile}0${k}_${myBOSON}_${NonPertFormat}
SETNUMBER=${k}
else
PDFDIR=${PDFFile}${k}_${myBOSON}_${NonPertFormat}
SETNUMBER=${k}
fi
ScaleVari=$[900+${k}]
ScaleDIR=Scale${ScaleVari}

##########build directory##############################
if [ $Process -eq 1 ]; then
cd $WORKDIR
PDFDIR=${PDFFile}00_${myBOSON}_${NonPertFormat}
SETNUMBER=0
elif [ $Process -eq 2 ]; then
cd $WORKDIR
ScaleVari=908
ScaleDIR=Scale908
fi

#move path
cp $WORKDIR/${WHICHPDF}/${PDFDIR}/${ScaleDIR}/JOB1/legacy.out $WORKDIR/${WHICHPDF}_YPiece/${PDFDIR}_${ScaleDIR}.out

echo $PDFDIR $ScaleDIR has been generated.

done ##done process

done ##done boson

cd $WORKDIR
