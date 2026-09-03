#!/bin/bash
WORKDIR=$PWD
CONVDIR=/lustre/AtlUser/yfu/pku_resbos/ScaleUncertainty/resbos2_mmht
multicore=0
localrun=0
#PDFNumber=7
UseLatestPara=0

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
NProcess=165
InitialProcess=151
elif [ $Process -eq 2 ]; then
echo Running PDF uncertainty.
NProcess=${NumberOfPDFSet}
InitialProcess=0
fi

AORDER=4
BORDER=3
CORDER=2
#SCALECHOICE=MT
#NonPertFormat=IY6

WHICHPDF=${MYPDF}_${SCALECHOICE}_w${AORDER}${BORDER}${CORDER}_pds
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
if [ $UseLatestPara -eq 1 -a $AORDER -eq 4 ]; then
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
if [ ! -d "$WORKDIR/$WHICHPDF/$PDFDIR/$ScaleDIR/JOB1/" ]; then
    mkdir $WORKDIR/$WHICHPDF/$PDFDIR/$ScaleDIR/JOB1
fi
if [ ! -d "$WORKDIR/$WHICHPDF/$PDFDIR/$ScaleDIR/JOB1/Grids" ]; then
    mkdir $WORKDIR/$WHICHPDF/$PDFDIR/$ScaleDIR/JOB1/Grids
fi


#combine q grid
cp ../GridFiles/${WHICHPDF}_ResBos2/${PDFDIR}_${ScaleDIR}_w${AORDER}${BORDER}${CORDER}.out $WORKDIR/${WHICHPDF}/${PDFDIR}/${ScaleDIR}/JOB1/Grids/ResBos_GridFile_0.out

echo $PDFDIR $ScaleDIR has been generated.

done ##done process

done ##done boson

cd $WORKDIR
