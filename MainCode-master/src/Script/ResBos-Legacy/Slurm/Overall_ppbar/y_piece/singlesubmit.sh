#!/bin/bash
WORKDIR=$PWD
multicore=0
localrun=0
#onlyCentral=0
RunNonPertFit=0
isKinCorr=0
KinCorr=1
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
#NonPertChoice=5

if [ $ScaleChoice1 -eq 1 ]; then
SCALECHOICE=MT
elif [ $ScaleChoice1 -eq 0 ]; then
SCALECHOICE=Q
fi

if [ $NonPertChoice -eq 4 ]; then
NonPertFormat=BLNY
elif [ $NonPertChoice -eq 5 ]; then
NonPertFormat=IY6
elif [ $NonPertChoice -eq  ]; then
NonPertFormat=SIYY
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

if [ $isRotation -eq 1 ]; then
    if [ ! -d "$WHICHPDF/$ObservableName/" ]; then
        mkdir $WHICHPDF/$ObservableName
    fi
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
NonPertDIR=${PDFFile}0${k}_NonPertFit_${NonPertFormat}
SETNUMBER=$k
else
PDFNAME=${PDFFile}${k}.pds
PDFDIR=${PDFFile}${k}_${myBOSON}_${NonPertFormat}
NonPertDIR=${PDFFile}${k}_NonPertFit_${NonPertFormat}
SETNUMBER=$k
fi
ScaleVari=$[900+${k}]
ScaleDIR=Scale${ScaleVari}

##########build directory##############################
if [ $Process -eq 1 ]; then
cd $WORKDIR
PDFNAME=${PDFFile}00.pds
PDFDIR=${PDFFile}00_${myBOSON}_${NonPertFormat}
NonPertDIR=${PDFFile}00_NonPertFit_${NonPertFormat}
SETNUMBER=0
elif [ $Process -eq 2 ]; then
cd $WORKDIR
ScaleVari=908
ScaleDIR=Scale908
if [ $UseLatestPara -eq 1 ]; then
ScaleVari=977
ScaleDIR=Scale977
fi
fi

if [ $isRotation -ne 1 ]; then
    if [ ! -d "$WORKDIR/${WHICHPDF}/$PDFDIR/" ]; then
        mkdir $WORKDIR/${WHICHPDF}/$PDFDIR
    fi
    if [ ! -d "$WORKDIR/${WHICHPDF}/$PDFDIR/$ScaleDIR/" ]; then
        mkdir $WORKDIR/${WHICHPDF}/$PDFDIR/$ScaleDIR
    fi
elif [ $isRotation -eq 1 ]; then
    if [ ! -d "$WORKDIR/${WHICHPDF}/$ObservableName/$PDFDIR/" ]; then
        mkdir $WORKDIR/${WHICHPDF}/$ObservableName/$PDFDIR
    fi
    if [ ! -d "$WORKDIR/${WHICHPDF}/$ObservableName/$PDFDIR/$ScaleDIR/" ]; then
        mkdir $WORKDIR/${WHICHPDF}/$ObservableName/$PDFDIR/$ScaleDIR
    fi
fi

if [ $RunNonPertFit -eq 1 ]; then

if [ $isKinCorr -eq 1 ]; then
    if [ $KinCorr -eq 1 ]; then
        cd $WORKDIR/../../ResBos2/KinCorrOn/${MYPDF}_${SCALECHOICE}_w${AORDER}${BORDER}${CORDER}_pds/${NonPertDIR}/$ScaleDIR
    else
        cd $WORKDIR/../../ResBos2/KinCorrOff/${MYPDF}_${SCALECHOICE}_w${AORDER}${BORDER}${CORDER}_pds/${NonPertDIR}/$ScaleDIR
    fi
else
    cd $WORKDIR/../ResBos2/${MYPDF}_${SCALECHOICE}_w${AORDER}${BORDER}${CORDER}_pds/${NonPertDIR}/$ScaleDIR
fi

source ~/pku_resbos/FrameWork/script/getNonPertPar.sh 2

else

G1NUMBER=0.21
G2NUMBER=0.68
G3NUMBER=-0.126

if [ $UseLatestPara -eq 1 ]; then
NonPertFormat=BLNY
G1NUMBER=0.34483
G2NUMBER=0.49333
G3NUMBER=-0.1858
fi

fi

##################################
source ~/pku_resbos/FrameWork/script/ScaleConfig.sh $ScaleVari
##################################

for((n=1;n<=1;n++)); do
cd $WORKDIR
mkdir $WORKDIR/${WHICHPDF}/$ObservableName/$PDFDIR/$ScaleDIR/JOB$n
cp 00legacy.in main $WORKDIR/${WHICHPDF}/$ObservableName/$PDFDIR/$ScaleDIR/JOB$n
cp -r inp $WORKDIR/${WHICHPDF}/$ObservableName/$PDFDIR/$ScaleDIR/JOB$n
cd $WORKDIR/${WHICHPDF}/$ObservableName/$PDFDIR/$ScaleDIR/JOB$n/inp
cp q_grid_0.inp q_grid.inp
cd $WORKDIR/${WHICHPDF}/$ObservableName/$PDFDIR/$ScaleDIR/JOB$n
sed -i "s/INPUTECM/$INPUTECM/g" 00legacy.in
sed -i "s/MYPDF/$MYPDF/g" 00legacy.in
sed -i "s/SETNUMBER/$SETNUMBER/g" 00legacy.in
sed -i "s/C1SCALE/$C1SCALE/g" 00legacy.in
sed -i "s/C2SCALE/$C2SCALE/g" 00legacy.in
sed -i "s/C3SCALE/$C3SCALE/g" 00legacy.in
sed -i "s/MUFSCALE/$MUFSCALE/g" 00legacy.in
sed -i "s/MURSCALE/$MURSCALE/g" 00legacy.in
sed -i "s/WORY/$WORY/g" 00legacy.in
sed -i "s/WHICHBOSON/$WHICHBOSON/g" 00legacy.in
sed -i "s/SCALECHOICE/$ScaleChoice1/g" 00legacy.in
sed -i "s/G1NUMBER/$G1NUMBER/g" 00legacy.in
sed -i "s/G2NUMBER/$G2NUMBER/g" 00legacy.in
sed -i "s/G3NUMBER/$G3NUMBER/g" 00legacy.in
sed -i "s/NonPertChoice/$NonPertChoice/g" 00legacy.in
cat 00legacy.in > legacy.in

#if [ $isRotation -ne 1 ]; then
#    ln -s /lustre/AtlUser/yfu/LHAPDF/share/LHAPDF/${MYPDF}_pds/$PDFNAME pdf00.pds
#elif [ $isRotation -eq 1 ]; then
#    ln -s $WORKDIR/../Rotation/${ObservableName}/$PDFNAME pdf00.pds
#fi

if [ $localrun -eq 1 ]; then
if [ $multicore -eq 1 ]; then

totalJob=`ps -ef|grep main|grep -v grep|awk '{print $1}'|grep ${USER}|wc -l`
#while [ $totalJob -gt 15 ]; do
#  sleep 5
#  totalJob=`ps -ef|grep main|grep -v grep|awk '{print $1}'|grep ${USER}|wc -l`
#done

nohup ./main &

else
./main
fi
echo $PDFDIR $ScaleDIR has been generated.

else ###submit condor job

totalJob=`condor_q |grep ${USER}|wc -l`
while [ $totalJob -gt 900 ] ; do
  sleep 30
  totalJob=`condor_q |grep ${USER}|wc -l`
done

cd $WORKDIR/${WHICHPDF}/$ObservableName/$PDFDIR/$ScaleDIR/JOB$n
cat >>mySUB_y_${MYPDF}_${myBOSON}_${k}_${n}  <<EOF
Universe                          = vanilla 
getenv                            = true
Executable                        = myANA.sh
Input                             = /dev/null
Output                            = JOBINDEX_${k}_${n}.stdout
Error                             = JOBINDEX_${k}_${n}.stderr
Log                               = JOBINDEX_${k}_${n}.condor.log
Concurrency_Limits                = DISK_T3WORK3:30
+IsBypassJob                      = True
Queue
EOF
cd $WORKDIR/${WHICHPDF}/$ObservableName/$PDFDIR/$ScaleDIR/JOB$n
cat >>myANA.sh  <<EOF
#!/bin/bash --login
#SBATCH --job-name=cp18h_12b   # job name
#SBATCH --nodes=1               # total number of nodes
#SBATCH --ntasks-per-node=1     # total number of tasks requested
#SBATCH --cpus-per-task=1       # total number of tasks requested
#SBATCH --threads-per-core=1    # one core each thread
#SBATCH --mem=5G            # job memory limit
#SBATCH --time=10:10:00             # run time (hh:mm:ss) - 3:00:00 hours
#SBATCH --output=%x-%j.out      # queue (partition) 
source ~/setup.sh
cd $WORKDIR/${WHICHPDF}/$ObservableName/$PDFDIR/$ScaleDIR/JOB$n
./main
###############################################
EOF
chmod +x myANA.sh

sbatch myANA.sh
#condor_submit mySUB_y_${MYPDF}_${myBOSON}_${k}_${n}

fi

done ##done job

done ##done process

done ##done boson

cd $WORKDIR
