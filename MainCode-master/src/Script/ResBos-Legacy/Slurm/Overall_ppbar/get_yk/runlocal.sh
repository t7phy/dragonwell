#!/bin/bash
WORKDIR=$PWD
multicore=0
localrun=0
isKinCorr=0
KinCorr=1
#onlyCentral=0
UseLatestPara=0

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

if [ $isKinCorr -eq 1 ]; then
    if [ $KinCorr -eq 1 ]; then
        KinCorrFlag=KinCorrOn
    elif [ $KinCorr -eq 0 ]; then
        KinCorrFlag=KinCorrOff
    fi
else
    KinCorrFlag=
fi

#ScaleChoice1=1
iOrder=2
#NonPertFormat=IY6
RAIName=R_Ai_LHC8TeV_Z.txt

if [ $ScaleChoice1 -eq 1 ]; then
SCALECHOICE=MT
elif [ $ScaleChoice1 -eq 0 ]; then
SCALECHOICE=Q
fi

if [ $iOrder -eq 1 ]; then
YPieceOrder=NLO
elif [ $iOrder -eq 2 ]; then
YPieceOrder=NNLO
fi

WHICHPDF=${MYPDF}_${SCALECHOICE}_pds
#NBosons=2

if [ ! -d "$WORKDIR/$KinCorrFlag/${WHICHPDF}_YPiece/" ]; then
    mkdir $WORKDIR/$KinCorrFlag/${WHICHPDF}_YPiece
fi

for((Boson=${InitialBoson};Boson<=$NBosons;Boson++)); do
########Set Boson Type############
if [ $Boson -eq 1 ]; then
myBOSON=zu
BOSONName=ZU
elif [ $Boson -eq 2 ]; then
myBOSON=zd
BOSONName=ZD
elif [ $Boson -eq 3 ]; then
myBOSON=wp
BOSONName=W+
RAIName=R_Ai_LHC13TeV_WPlus.txt
#RAIName=R_Ai_tev2_wp.txt
elif [ $Boson -eq 4 ]; then
myBOSON=wm
BOSONName=W-
RAIName=R_Ai_LHC13TeV_WMinus.txt
#RAIName=R_Ai_tev2_wp.txt
fi

echo " "
echo ${myBOSON} production:
echo " "

##########Define Scale and PDF name####################
for((k=${InitialProcess};k<=$NProcess;k++)); do
if [ $k -lt 10 ]; then
PDFDIR=${PDFFile}0${k}_${myBOSON}
else
PDFDIR=${PDFFile}${k}_${myBOSON}
fi
ScaleVari=$[900+${k}]
ScaleDIR=Scale${ScaleVari}

##########build directory##############################
if [ $Process -eq 1 ]; then
cd $WORKDIR
PDFDIR=${PDFFile}00_${myBOSON}
elif [ $Process -eq 2 ]; then
cd $WORKDIR
ScaleDIR=Scale908
if [ $UseLatestPara -eq 1 ]; then
ScaleVari=977
ScaleDIR=Scale977
fi
fi

YGRID=$WORKDIR/../y_piece/${KinCorrFlag}/${WHICHPDF}/${PDFDIR}_${NonPertFormat}/$ScaleDIR/JOB1/legacy.out
PERT=$WORKDIR/../w_pert/${KinCorrFlag}/${WHICHPDF}/${PDFDIR}/$ScaleDIR/JOB1/w_pert.out
ASYM=$WORKDIR/../w_asym/${KinCorrFlag}/${WHICHPDF}/${PDFDIR}/$ScaleDIR/JOB1/w_asym.out

if [ $iOrder -eq 1 ]; then
    YKGRID_tmp=legacy_yk.out
    YKGRID=${PDFDIR}_${NonPertFormat}_${ScaleDIR}_y.out
elif [ $iOrder -eq 2 ]; then
    YKGRID_tmp=legacy_yk.out
    YKGRID=${PDFDIR}_${NonPertFormat}_${ScaleDIR}_yk.out
fi

ln -s $YGRID legacy_y.out
ln -s $PERT w_pert.out
ln -s $ASYM w_asym.out
./get_yk_new w_pert.out w_asym.out legacy_y.out ${RAIName} ${YKGRID_tmp} ${BOSONName} ${YPieceOrder} ${PDFFile}00
rm legacy_y.out w_pert.out w_asym.out
mv ${YKGRID_tmp} ${YKGRID}
if [ $isKinCorr -eq 1 ]; then
    mv ${YKGRID} ${KinCorrFlag}/${WHICHPDF}_YPiece
else
    mv ${YKGRID} ${WHICHPDF}_YPiece
fi
echo ${PDFDIR} ${ScaleDIR} has been generated.

done

done
