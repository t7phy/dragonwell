#!/bin/bash
WORKDIR=$PWD
multicore=0
localrun=0
onlyCentral=1
RunNonPertFit=0
isKinCorr=1
KinCorr=1
UseLatestPara=1

PDFNumber=7
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

ScaleChoice1=1

if [ $ScaleChoice1 -eq 1 ]; then
SCALECHOICE=MT
elif [ $ScaleChoice1 -eq 0 ]; then
SCALECHOICE=Q
fi

WHICHPDF=${MYPDF}_${SCALECHOICE}_pds

NJobs=1

cd $WORKDIR
if [ ! -d "$WHICHPDF/" ]; then
    mkdir $WHICHPDF
fi

if [ ! -d "$WHICHPDF/LO" ]; then
    mkdir $WHICHPDF/LO
fi

if [ ! -d "$WHICHPDF/NLO" ]; then
    mkdir $WHICHPDF/NLO
fi

if [ ! -d "$WHICHPDF/NNLO" ]; then
    mkdir $WHICHPDF/NNLO
fi


##########Define Scale and PDF name####################
for((k=${InitialProcess};k<=$NProcess;k++)); do
if [ $k -lt 10 ]; then
PDFNAME=${PDFFile}0${k}.pds
PDFDIR=${PDFFile}0${k}
SETNUMBER=$k
else
PDFNAME=${PDFFile}${k}.pds
PDFDIR=${PDFFile}${k}
SETNUMBER=$k
fi
ScaleVari=$[900+${k}]
ScaleDIR=Scale${ScaleVari}

##########build directory##############################
if [ $Process -eq 1 ]; then
cd $WORKDIR
PDFNAME=${PDFFile}00.pds
PDFDIR=${PDFFile}00
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

if [ ! -d "$WORKDIR/${WHICHPDF}/LO/$PDFDIR/" ]; then
    mkdir $WORKDIR/${WHICHPDF}/LO/$PDFDIR
fi
if [ ! -d "$WORKDIR/${WHICHPDF}/LO/$PDFDIR/$ScaleDIR/" ]; then
    mkdir $WORKDIR/${WHICHPDF}/LO/$PDFDIR/$ScaleDIR
fi

if [ ! -d "$WORKDIR/${WHICHPDF}/NLO/$PDFDIR/" ]; then
    mkdir $WORKDIR/${WHICHPDF}/NLO/$PDFDIR
fi
if [ ! -d "$WORKDIR/${WHICHPDF}/NLO/$PDFDIR/$ScaleDIR/" ]; then
    mkdir $WORKDIR/${WHICHPDF}/NLO/$PDFDIR/$ScaleDIR
fi

if [ ! -d "$WORKDIR/${WHICHPDF}/NNLO/$PDFDIR/" ]; then
    mkdir $WORKDIR/${WHICHPDF}/NNLO/$PDFDIR
fi
if [ ! -d "$WORKDIR/${WHICHPDF}/NNLO/$PDFDIR/$ScaleDIR/" ]; then
    mkdir $WORKDIR/${WHICHPDF}/NNLO/$PDFDIR/$ScaleDIR
fi


##################################
source ~/pku_resbos/FrameWork/script/ScaleConfig.sh $ScaleVari
##################################

##################################
###LO##

ITMX1=50
NCALL1=2000000
ITMX2=400
NCALL2=20000000
ORDER=lo

RANDOMSEED=$[1000+10*${k}]

cd $WORKDIR
cp 00input.ini mcfm process.DAT $WORKDIR/${WHICHPDF}/LO/$PDFDIR/$ScaleDIR/
cd $WORKDIR/${WHICHPDF}/LO/$PDFDIR/$ScaleDIR/
sed -i "s/MYPDF/$MYPDF/g" 00input.ini
sed -i "s/SETNUMBER/$SETNUMBER/g" 00input.ini
sed -i "s/RANDOMSEED/$RANDOMSEED/g" 00input.ini
sed -i "s/ITMX1/$ITMX1/g" 00input.ini
sed -i "s/NCALL1/$NCALL1/g" 00input.ini
sed -i "s/ITMX2/$ITMX2/g" 00input.ini
sed -i "s/NCALL2/$NCALL2/g" 00input.ini
sed -i "s/ORDER/$ORDER/g" 00input.ini
cat 00input.ini > input.ini

cat >>myANA.sh  <<EOF
#!/bin/bash
#SBATCH --job-name=cp18h_12b   # job name
#SBATCH --nodes=1               # total number of nodes
#SBATCH --ntasks-per-node=1     # total number of tasks requested
#SBATCH --cpus-per-task=96       # total number of tasks requested
#SBATCH --exclusive             # exlusive on nodes
#SBATCH --threads-per-core=1    # one core each thread
#SBATCH --mem=10G            # job memory limit
#SBATCH --time=100:00:00             # run time (hh:mm:ss) - 3:00:00 hours
#SBATCH --output=%x-%j.out      # queue (partition) 
source ~/SetupRoot.sh
cd $WORKDIR/${WHICHPDF}/LO/$PDFDIR/$ScaleDIR
./mcfm input.ini
###############################################
EOF

#sbatch myANA.sh

##################################
##NLO##

for((n=1;n<=$NJobs;n++)); do

ITMX1=50
NCALL1=100000
ITMX2=20
NCALL2=1000000
ORDER=nlo

RANDOMSEED=$[2000+10*${k}+1*${n}]
cd $WORKDIR
mkdir $WORKDIR/${WHICHPDF}/NLO/$PDFDIR/$ScaleDIR/JOB$n
cp 00input.ini mcfm process.DAT $WORKDIR/${WHICHPDF}/NLO/$PDFDIR/$ScaleDIR/JOB$n
cd $WORKDIR/${WHICHPDF}/NLO/$PDFDIR/$ScaleDIR/JOB$n
sed -i "s/MYPDF/$MYPDF/g" 00input.ini
sed -i "s/SETNUMBER/$SETNUMBER/g" 00input.ini
sed -i "s/RANDOMSEED/$RANDOMSEED/g" 00input.ini
sed -i "s/ITMX1/$ITMX1/g" 00input.ini
sed -i "s/NCALL1/$NCALL1/g" 00input.ini
sed -i "s/ITMX2/$ITMX2/g" 00input.ini
sed -i "s/NCALL2/$NCALL2/g" 00input.ini
sed -i "s/ORDER/$ORDER/g" 00input.ini
cat 00input.ini > input.ini

if [ $localrun -eq 1 ]; then
if [ $multicore -eq 1 ]; then

totalJob=`ps -ef|grep main|grep -v grep|awk '{print $1}'|grep ${USER}|wc -l`

nohup ./mcfm &

else
./mcfm
fi
echo $PDFDIR $ScaleDIR has been generated.

else ###submit condor job

cd $WORKDIR/${WHICHPDF}/NLO/$PDFDIR/$ScaleDIR/JOB$n
cat >>myANA.sh  <<EOF
#!/bin/bash
#SBATCH --job-name=cp18h_12b   # job name
#SBATCH --nodes=1               # total number of nodes
#SBATCH --ntasks-per-node=1     # total number of tasks requested
#SBATCH --cpus-per-task=96       # total number of tasks requested
#SBATCH --exclusive             # exlusive on nodes
#SBATCH --threads-per-core=1    # one core each thread
#SBATCH --mem=10G            # job memory limit
#SBATCH --time=100:00:00             # run time (hh:mm:ss) - 3:00:00 hours
#SBATCH --output=%x-%j.out      # queue (partition) 
source ~/SetupRoot.sh
cd $WORKDIR/${WHICHPDF}/NLO/$PDFDIR/$ScaleDIR/JOB$n
./mcfm input.ini
###############################################
EOF

sbatch myANA.sh

fi

done ##done job

##################################
##NNLO##

for((n=1;n<=$NJobs;n++)); do

ITMX1=50
NCALL1=100000
ITMX2=20
NCALL2=1000000
ORDER=nnlo

RANDOMSEED=$[2000+10*${k}+1*${n}]
cd $WORKDIR
mkdir $WORKDIR/${WHICHPDF}/NNLO/$PDFDIR/$ScaleDIR/JOB$n
cp 00input.ini mcfm process.DAT $WORKDIR/${WHICHPDF}/NNLO/$PDFDIR/$ScaleDIR/JOB$n
cd $WORKDIR/${WHICHPDF}/NNLO/$PDFDIR/$ScaleDIR/JOB$n
sed -i "s/MYPDF/$MYPDF/g" 00input.ini
sed -i "s/SETNUMBER/$SETNUMBER/g" 00input.ini
sed -i "s/RANDOMSEED/$RANDOMSEED/g" 00input.ini
sed -i "s/ITMX1/$ITMX1/g" 00input.ini
sed -i "s/NCALL1/$NCALL1/g" 00input.ini
sed -i "s/ITMX2/$ITMX2/g" 00input.ini
sed -i "s/NCALL2/$NCALL2/g" 00input.ini
sed -i "s/ORDER/$ORDER/g" 00input.ini
cat 00input.ini > input.ini

if [ $localrun -eq 1 ]; then
if [ $multicore -eq 1 ]; then

totalJob=`ps -ef|grep main|grep -v grep|awk '{print $1}'|grep ${USER}|wc -l`

nohup ./mcfm &

else
./mcfm
fi
echo $PDFDIR $ScaleDIR has been generated.

else ###submit condor job

cd $WORKDIR/${WHICHPDF}/NNLO/$PDFDIR/$ScaleDIR/JOB$n
cat >>myANA.sh  <<EOF
#!/bin/bash
#SBATCH --job-name=cp18h_12b   # job name
#SBATCH --nodes=1               # total number of nodes
#SBATCH --ntasks-per-node=1     # total number of tasks requested
#SBATCH --cpus-per-task=128       # total number of tasks requested
#SBATCH --exclusive             # exlusive on nodes
#SBATCH --threads-per-core=1    # one core each thread
#SBATCH --mem=10G            # job memory limit
#SBATCH --time=150:00:00             # run time (hh:mm:ss) - 3:00:00 hours
#SBATCH --output=%x-%j.out      # queue (partition) 
source ~/SetupRoot.sh
export OMP_NUM_THREADS=128
cd $WORKDIR/${WHICHPDF}/NNLO/$PDFDIR/$ScaleDIR/JOB$n
./mcfm input.ini
###############################################
EOF

sbatch myANA.sh

fi

done ##done job

done ##done process

cd $WORKDIR

