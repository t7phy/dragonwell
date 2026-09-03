#!/bin/bash
WORKDIR=$PWD
CONVDIR=/mnt/scratch/fuyao3/pku_resbos/RHIC/ResBos2
multicore=0
localrun=0
RunNonPertFit=0
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
WHICHBOSON=WPlus
myBOSON=wp
elif [ $Boson -eq 4 ]; then
WHICHBOSON=WMinus
myBOSON=wm
fi

echo " "
echo ${myBOSON} production:
echo " "

##########Define Scale and PDF name####################
for((k=${InitialProcess};k<=$NProcess;k++)); do
if [ $k -lt 10 ]; then
PDFDIR=${PDFFile}0${k}_${myBOSON}_${NonPertFormat}
NonPertDIR=${PDFFile}0${k}_NonPertFit_${NonPertFormat}
SETNUMBER=${k}
else
PDFDIR=${PDFFile}${k}_${myBOSON}_${NonPertFormat}
NonPertDIR=${PDFFile}${k}_NonPertFit_${NonPertFormat}
SETNUMBER=${k}
fi
ScaleVari=$[900+${k}]
ScaleDIR=Scale${ScaleVari}

##########build directory##############################
if [ $Process -eq 1 ]; then
cd $WORKDIR
PDFDIR=${PDFFile}00_${myBOSON}_${NonPertFormat}
NonPertDIR=${PDFFile}00_NonPertFit_${NonPertFormat}
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

echo "This Job is for $PDFDIR $ScaleDIR"

if [ $RunNonPertFit -eq 1 ]; then

cd $WORKDIR/${WHICHPDF}/${NonPertDIR}/$ScaleDIR
source ~/pku_resbos/FrameWork/script/getNonPertParAndErr.sh 1

else

#NonPertFormat=BLNY
#G1NUMBER=0.21
#G2NUMBER=0.68
#G3NUMBER=-0.126
#G4NUMBER=0.0
#G5NUMBER=0.0
#G6NUMBER=0.0
NonPertFormat=IY6
G1NUMBER=1.034
G2NUMBER=0.053
G3NUMBER=0.0
G4NUMBER=-0.143
G5NUMBER=13.45
G6NUMBER=1.468

if [ $UseLatestPara -eq 1 -a $AORDER -eq 4 ]; then
NonPertFormat=BLNY
G1NUMBER=0.34483
G2NUMBER=0.49333
G3NUMBER=-0.1858
fi

fi

##################################
source ~/pku_resbos/FrameWork/script/ScaleConfig.sh $ScaleVari
##################################

for((n=1;n<=$NJobs;n++)); do
cd $WORKDIR
QVALUE=`cat inp/q_grid_0.inp|head -${n}|tail -1`
echo "Q is " $QVALUE
if [ ! -d "$WORKDIR/$WHICHPDF/$PDFDIR/$ScaleDIR/JOB$n/" ]; then
    mkdir $WORKDIR/$WHICHPDF/$PDFDIR/$ScaleDIR/JOB$n
fi

cp 00resbos.config $WORKDIR/$WHICHPDF/$PDFDIR/$ScaleDIR/JOB$n

cd $WORKDIR/$WHICHPDF/$PDFDIR/$ScaleDIR/JOB$n

sed -i "s/INPUTECM/$INPUTECM/g" 00resbos.config
sed -i "s/MYPDF/$MYPDF/g" 00resbos.config
sed -i "s/SETNUMBER/$SETNUMBER/g" 00resbos.config
sed -i "s/AORDER/$AORDER/g" 00resbos.config
sed -i "s/BORDER/$BORDER/g" 00resbos.config
sed -i "s/CORDER/$CORDER/g" 00resbos.config
sed -i "s/C1SCALE/$C1SCALE/g" 00resbos.config
sed -i "s/C2SCALE/$C2SCALE/g" 00resbos.config
sed -i "s/C3SCALE/$C3SCALE/g" 00resbos.config
sed -i "s/MUFSCALE/$MUFSCALE/g" 00resbos.config
sed -i "s/MURSCALE/$MURSCALE/g" 00resbos.config
sed -i "s/SCALECHOICE/$SCALECHOICE/g" 00resbos.config
sed -i "s/WHICHBOSON/$WHICHBOSON/g" 00resbos.config
sed -i "s/QVALUE/$QVALUE/g" 00resbos.config
sed -i "s/G1NUMBER/$G1NUMBER/g" 00resbos.config
sed -i "s/G2NUMBER/$G2NUMBER/g" 00resbos.config
sed -i "s/G3NUMBER/$G3NUMBER/g" 00resbos.config
sed -i "s/G4NUMBER/$G4NUMBER/g" 00resbos.config
sed -i "s/G5NUMBER/$G5NUMBER/g" 00resbos.config
sed -i "s/G6NUMBER/$G6NUMBER/g" 00resbos.config
sed -i "s/NonPertFormat/$NonPertFormat/g" 00resbos.config
cat 00resbos.config > resbos.config

if [ ! -d "ConvGrids/" ]; then
    mkdir ConvGrids
fi
if [ ! -d "Grids/" ]; then
    mkdir Grids
fi

cd ConvGrids

if [ -f "${CONVDIR}/ConvGrids/${MYPDF}_${SETNUMBER}_Conv_C1.out" ]; then
    ln -s ${CONVDIR}/ConvGrids/${MYPDF}_${SETNUMBER}_Conv_C1.out ${MYPDF}_${SETNUMBER}_Conv_C1.out
fi

if [ -f "${CONVDIR}/ConvGrids/${MYPDF}_${SETNUMBER}_Conv_C1P1.out" ]; then
    ln -s ${CONVDIR}/ConvGrids/${MYPDF}_${SETNUMBER}_Conv_C1P1.out ${MYPDF}_${SETNUMBER}_Conv_C1P1.out
fi

if [ -f "${CONVDIR}/ConvGrids/${MYPDF}_${SETNUMBER}_Conv_C1P1P1.out" ]; then
    ln -s ${CONVDIR}/ConvGrids/${MYPDF}_${SETNUMBER}_Conv_C1P1P1.out ${MYPDF}_${SETNUMBER}_Conv_C1P1P1.out
fi

if [ -f "${CONVDIR}/ConvGrids/${MYPDF}_${SETNUMBER}_Conv_C1P2.out" ]; then
    ln -s ${CONVDIR}/ConvGrids/${MYPDF}_${SETNUMBER}_Conv_C1P2.out ${MYPDF}_${SETNUMBER}_Conv_C1P2.out
fi

if [ -f "${CONVDIR}/ConvGrids/${MYPDF}_${SETNUMBER}_Conv_C2.out" ]; then
    ln -s ${CONVDIR}/ConvGrids/${MYPDF}_${SETNUMBER}_Conv_C2.out ${MYPDF}_${SETNUMBER}_Conv_C2.out
fi

if [ -f "${CONVDIR}/ConvGrids/${MYPDF}_${SETNUMBER}_Conv_C2P1.out" ]; then
    ln -s ${CONVDIR}/ConvGrids/${MYPDF}_${SETNUMBER}_Conv_C2P1.out ${MYPDF}_${SETNUMBER}_Conv_C2P1.out
fi

if [ -f "${CONVDIR}/ConvGrids/${MYPDF}_${SETNUMBER}_Conv_G1.out" ]; then
    ln -s ${CONVDIR}/ConvGrids/${MYPDF}_${SETNUMBER}_Conv_G1.out ${MYPDF}_${SETNUMBER}_Conv_G1.out
fi

if [ -f "${CONVDIR}/ConvGrids/${MYPDF}_${SETNUMBER}_Conv_G1P1.out" ]; then
    ln -s ${CONVDIR}/ConvGrids/${MYPDF}_${SETNUMBER}_Conv_G1P1.out ${MYPDF}_${SETNUMBER}_Conv_G1P1.out
fi

#ln -s ${CONVDIR}/ConvGrids/${MYPDF}_${SETNUMBER}_Conv_C1P1.out ${MYPDF}_${SETNUMBER}_Conv_C1P1.out
#ln -s ${CONVDIR}/ConvGrids/${MYPDF}_${SETNUMBER}_Conv_C1P1P1.out ${MYPDF}_${SETNUMBER}_Conv_C1P1P1.out
#ln -s ${CONVDIR}/ConvGrids/${MYPDF}_${SETNUMBER}_Conv_C1P2.out ${MYPDF}_${SETNUMBER}_Conv_C1P2.out
#ln -s ${CONVDIR}/ConvGrids/${MYPDF}_${SETNUMBER}_Conv_C2.out ${MYPDF}_${SETNUMBER}_Conv_C2.out
#ln -s ${CONVDIR}/ConvGrids/${MYPDF}_${SETNUMBER}_Conv_C2P1.out ${MYPDF}_${SETNUMBER}_Conv_C2P1.out
#ln -s ${CONVDIR}/ConvGrids/${MYPDF}_${SETNUMBER}_Conv_G1.out ${MYPDF}_${SETNUMBER}_Conv_G1.out
#ln -s ${CONVDIR}/ConvGrids/${MYPDF}_${SETNUMBER}_Conv_G1P1.out ${MYPDF}_${SETNUMBER}_Conv_G1P1.out

cd ..

if [ $localrun -eq 1 ]; then
if [ $multicore -eq 1 ]; then

totalJob=`ps -ef|grep resbos|grep -v grep|awk '{print $1}'|grep ${USER}|wc -l`
while [ $totalJob -gt 90 ]; do
  sleep 5
  totalJob=`ps -ef|grep resbos|grep -v grep|awk '{print $1}'|grep ${USER}|wc -l`
done

nohup ./resbos &

else
./resbos
fi
echo $PDFDIR $ScaleDIR has been generated.

else ###submit condor job

totalJob=`condor_q |grep ${USER}|wc -l`
while [ $totalJob -gt 900 ] ; do
  sleep 30
  totalJob=`condor_q |grep ${USER}|wc -l`
done

cd $WORKDIR/$WHICHPDF/$PDFDIR/$ScaleDIR/JOB$n
cat >>mySUB_ResBos2_${MYPDF}_${myBOSON}_${k}_${n}  <<EOF
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

cd $WORKDIR/$WHICHPDF/$PDFDIR/$ScaleDIR/JOB$n

cat >>myANA.sh  <<EOF
#!/bin/bash --login
#SBATCH --job-name=cp18h_12b   # job name
#SBATCH --nodes=1               # total number of nodes
#SBATCH --ntasks-per-node=1     # total number of tasks requested
#SBATCH --cpus-per-task=1       # total number of tasks requested
#SBATCH --threads-per-core=1    # one core each thread
#SBATCH --mem=10G            # job memory limit
#SBATCH --time=1:00:00             # run time (hh:mm:ss) - 3:00:00 hours
#SBATCH --output=%x-%j.out      # queue (partition) 
ulimit -c 0
source ~/setup.sh
cd $WORKDIR/$WHICHPDF/$PDFDIR/$ScaleDIR/JOB$n
resbos
###############################################
EOF
chmod +x myANA.sh

echo one job has been submitted
sbatch myANA.sh
#condor_submit mySUB_ResBos2_${MYPDF}_${myBOSON}_${k}_${n}

fi

done ##done job

echo $PDFDIR $ScaleDIR has been submitted

done ##done process

done ##done boson

cd $WORKDIR
