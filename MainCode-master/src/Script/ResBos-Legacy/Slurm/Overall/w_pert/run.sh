#!/bin/bash
WORKDIR=$PWD
multicore=0
localrun=0
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

#ScaleChoice1=1

if [ $ScaleChoice1 -eq 1 ]; then
SCALECHOICE=MT
elif [ $ScaleChoice1 -eq 0 ]; then
SCALECHOICE=Q
fi

WHICHPDF=${MYPDF}_${SCALECHOICE}_pds

#NBosons=2
NJobs=`cat inp/q_grid_0.inp |wc -l`

cd $WORKDIR
if [ ! -d "$WHICHPDF/" ]; then
    mkdir $WHICHPDF
fi

for((Boson=${InitialBoson};Boson<=$NBosons;Boson++)); do
########Set Boson Type############
if [ $Boson -eq 1 ]; then
WHICHBOSON=2
BOSON=ZU
myBOSON=zu
ZTYPE=1
elif [ $Boson -eq 2 ]; then
WHICHBOSON=2
BOSON=ZD
myBOSON=zd
ZTYPE=-1
elif [ $Boson -eq 3 ]; then
WHICHBOSON=1
myBOSON=wp
ZTYPE=0
elif [ $Boson -eq 4 ]; then
WHICHBOSON=-1
myBOSON=wm
ZTYPE=0
fi

echo " "
echo ${myBOSON} production:
echo " "

##########Define Scale and PDF name####################
for((k=${InitialProcess};k<=$NProcess;k++)); do
if [ $k -lt 10 ]; then
PDFNAME=${PDFFile}0${k}.pds
PDFDIR=${PDFFile}0${k}_${myBOSON}
SETNUMBER=$k
else
PDFNAME=${PDFFile}${k}.pds
PDFDIR=${PDFFile}${k}_${myBOSON}
SETNUMBER=$k
fi
ScaleVari=$[900+${k}]
ScaleDIR=Scale${ScaleVari}

##########build directory##############################
if [ $Process -eq 1 ]; then
cd $WORKDIR
PDFNAME=${PDFFile}00.pds
PDFDIR=${PDFFile}00_${myBOSON}
SETNUMBER=0
elif [ $Process -eq 2 ]; then
cd $WORKDIR
ScaleVari=908
ScaleDIR=Scale${ScaleVari}
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

##################################
source ~/pku_resbos/FrameWork/script/ScaleConfig.sh $ScaleVari
##################################

#if [ $localrun -eq 1 ]; then
#cd $WORKDIR
#
#if [ $Boson -lt 3 ]; then
#cp w_pert 00w_pert.in $WORKDIR/$WHICHPDF/$PDFDIR/$ScaleDIR
#else
#cp w_pert 00w_pert.in $WORKDIR/$WHICHPDF/$PDFDIR/$ScaleDIR
#fi
#
#cp -r inp $WORKDIR/$WHICHPDF/$PDFDIR/$ScaleDIR
#cd $WORKDIR/$WHICHPDF/$PDFDIR/$ScaleDIR
#sed -i "s/WHICHBOSON/$WHICHBOSON/g" 00w_pert.in
#sed -i "s/SCALECHOICE/$ScaleChoice1/g" 00w_pert.in
#sed -i "s/MURSCALE/$MURSCALE/g" 00w_pert.in
#sed -i "s/MUFSCALE/$MUFSCALE/g" 00w_pert.in
#sed -i "s/ZTYPE/$ZTYPE/g" 00w_pert.in
#cat 00w_pert.in > w_pert.in
#ln -s /lustre/AtlUser/yfu/LHAPDF/share/LHAPDF/${MYPDF}_pds/$PDFNAME pdf00.pds
#
#if [ $multicore -eq 1 ]; then
#
#totalJob=`ps -ef|grep w_pert|grep -v grep|awk '{print $1}'|grep ${USER}|wc -l`
#while [ $totalJob -gt 15 ]; do
#  sleep 5
#  totalJob=`ps -ef|grep w_pert|grep -v grep|awk '{print $1}'|grep ${USER}|wc -l`
#done
#
#if [ $Boson -lt 3 ]; then
#nohup ./w_pert &
#else
#nohup ./w_pert &
#fi
#
#else
#
#if [ $Boson -lt 3 ]; then
#./w_pert
#else
#./w_pert
#fi
#
#fi
for((n=1;n<=$NJobs;n++)); do

cd $WORKDIR/$WHICHPDF/$PDFDIR/$ScaleDIR
mkdir JOB${n}
cd $WORKDIR

if [ $Boson -lt 3 ]; then
cp w_pert 00w_pert.in $WORKDIR/$WHICHPDF/$PDFDIR/$ScaleDIR/JOB$n
else
cp w_pert 00w_pert.in $WORKDIR/$WHICHPDF/$PDFDIR/$ScaleDIR/JOB$n
fi

cp -r inp $WORKDIR/$WHICHPDF/$PDFDIR/$ScaleDIR/JOB$n
cd $WORKDIR/$WHICHPDF/$PDFDIR/$ScaleDIR/JOB$n
sed -i "s/INPUTECM/$INPUTECM/g" 00w_pert.in
sed -i "s/MYPDF/$MYPDF/g" 00w_pert.in
sed -i "s/SETNUMBER/$SETNUMBER/g" 00w_pert.in
sed -i "s/WHICHBOSON/$WHICHBOSON/g" 00w_pert.in
sed -i "s/SCALECHOICE/$ScaleChoice1/g" 00w_pert.in
sed -i "s/MURSCALE/$MURSCALE/g" 00w_pert.in
sed -i "s/MUFSCALE/$MUFSCALE/g" 00w_pert.in
sed -i "s/ZTYPE/$ZTYPE/g" 00w_pert.in
cat 00w_pert.in > w_pert.in
#ln -s /lustre/AtlUser/yfu/LHAPDF/share/LHAPDF/${MYPDF}_pds/$PDFNAME pdf00.pds
cd $WORKDIR/$WHICHPDF/$PDFDIR/$ScaleDIR/JOB$n/inp
cat q_grid_0.inp|head -${n}|tail -1 > q_grid.inp
cd ..

if [ $localrun -eq 1 ]; then

if [ $multicore -eq 1 ]; then

totalJob=`ps -ef|grep w_pert|grep -v grep|awk '{print $1}'|grep ${USER}|wc -l`
#while [ $totalJob -gt 15 ]; do
#  sleep 5
#  totalJob=`ps -ef|grep w_pert|grep -v grep|awk '{print $1}'|grep ${USER}|wc -l`
#done

nohup ./w_pert &

else
./w_pert
fi
echo $PDFDIR $ScaleDIR has been generated.

else ###submit condor job

totalJob=`condor_q |grep ${USER}|wc -l`
while [ $totalJob -gt 900 ] ; do
  sleep 30
  totalJob=`condor_q |grep ${USER}|wc -l`
done

cd $WORKDIR/$WHICHPDF/$PDFDIR/$ScaleDIR/JOB$n
cat >>mySUB_pert_${MYPDF}_${myBOSON}_${k}_${n}  <<EOF
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
#SBATCH --mem=5G            # job memory limit
#SBATCH --time=00:20:00             # run time (hh:mm:ss) - 3:00:00 hours
#SBATCH --output=%x-%j.out      # queue (partition) 
source ~/setup.sh
cd $WORKDIR/$WHICHPDF/$PDFDIR/$ScaleDIR/JOB$n

Boson=$Boson
if [ $Boson -lt 3 ]; then
./w_pert
else
./w_pert
fi

###############################################
EOF
chmod +x myANA.sh

sbatch myANA.sh
#condor_submit mySUB_pert_${MYPDF}_${myBOSON}_${k}_${n}

fi

done

done

done

cd $WORKDIR
