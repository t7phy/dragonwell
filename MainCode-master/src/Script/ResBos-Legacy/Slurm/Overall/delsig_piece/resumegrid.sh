#!/bin/bash
WORKDIR=$PWD
multicore=0
localrun=0
#onlyCentral=0
UseLatestPara=0

isRotation=0
if [ $isRotation -eq 1 ]; then
ObservableName=AFB_Full_60_130_2GeV
TotalEigenVector=56
fi

source ../overall.sh

#PDFNumber=7
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
NProcess=135
InitialProcess=121
elif [ $Process -eq 2 ]; then
echo Running PDF uncertainty.
NProcess=${NumberOfPDFSet}
InitialProcess=0
fi

WORY=3  ###  0:W-piece 3:Y-piece

AORDER=4
BORDER=3
CORDER=2
#ScaleChoice1=1
#NonPertFormat=IY6

if [ $ScaleChoice1 -eq 1 ]; then
SCALECHOICE=MT
elif [ $ScaleChoice1 -eq 0 ]; then
SCALECHOICE=Q
fi

WHICHPDF=${MYPDF}_${SCALECHOICE}_pds

if [ $isRotation -eq 1 ]; then
    NProcess=${TotalEigenVector}
    WHICHPDF=${MYPDF}_rotated
fi

NJobs=`cat inp/q_grid_0.inp |wc -l`
#NBosons=2

cd $WORKDIR
if [ ! -d "$WHICHPDF/" ]; then
    mkdir $WHICHPDF
fi

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
PDFNAME=${PDFFile}0${k}.pds
PDFDIR=${PDFFile}0${k}_${myBOSON}_${NonPertFormat}
else
PDFNAME=${PDFFile}${k}.pds
PDFDIR=${PDFFile}${k}_${myBOSON}_${NonPertFormat}
fi
ScaleVari=$[900+${k}]
ScaleDIR=Scale${ScaleVari}

##########build directory##############################
if [ $Process -eq 1 ]; then
cd $WORKDIR
PDFNAME=${PDFFile}00.pds
PDFDIR=${PDFFile}00_${myBOSON}_${NonPertFormat}
elif [ $Process -eq 2 ]; then
cd $WORKDIR
ScaleVari=908
ScaleDIR=Scale908
if [ $UseLatestPara -eq 1 ]; then
ScaleVari=977
ScaleDIR=Scale977
fi
fi

if [ ! -d "$WORKDIR/${WHICHPDF}/$PDFDIR/" ]; then
    mkdir $WORKDIR/${WHICHPDF}/$PDFDIR
fi
if [ ! -d "$WORKDIR/${WHICHPDF}/$PDFDIR/$ScaleDIR/" ]; then
    mkdir $WORKDIR/${WHICHPDF}/$PDFDIR/$ScaleDIR
fi
if [ ! -d "$WORKDIR/${WHICHPDF}/$PDFDIR/$ScaleDIR/JOB1" ]; then
    mkdir $WORKDIR/${WHICHPDF}/$PDFDIR/$ScaleDIR/JOB1
fi

cp ../GridFiles/${WHICHPDF}_DelSig/${PDFDIR}_${ScaleDIR}.out $WORKDIR/$WHICHPDF/$PDFDIR/$ScaleDIR/JOB1/legacy.out

echo $PDFDIR $ScaleDIR has been generated.

done ##done process

done ##done boson

cd $WORKDIR
