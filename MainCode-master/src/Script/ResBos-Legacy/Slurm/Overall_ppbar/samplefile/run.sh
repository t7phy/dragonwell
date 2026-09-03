#!/bin/bash
WORKDIR=$PWD
Process=$1
GridDIR=/lustre/AtlUser/yfu/pku_resbos/gridfile
multicore=1
localrun=1
WConfig=2   ###1: w321  2: w432  0: delsig  -1: asy
YConfig=2   ###1: y1    2: y2    0: onlyW   -1: asy  ##For NLO calculation, please usage WConfig=0 YConfig=0, and then WConfig=-1 YConfig=-1, and hadd the result.
isResBos2=1
isLegacy=0
isKinCorr=0
KinCorr=1
UseLatestPara=0

source ../overall.sh

SeparateQuark=0

PseudoData=0
STWINPUT=0.2315
#onlyCentral=0
TryOld=0
NTemplate=40
isRotation=0

SCALECHOICE=_${SCALECHOICE}
NonPertFormat=_${NonPertFormat}

#PDFNumber=7
ECM=8TeV
# PDFNumber = 1: CT14HEAR2NNLO
# PDFNumber = 2: CT14nnlo
# PDFNumber = 3: MMHT2014nnlo68cl
######################Initialize the PDF Name###############################
source ~/pku_resbos/FrameWork/script/PDFInformation.sh $PDFNumber
source ~/pku_resbos/FrameWork/script/ResBosConfig.sh $WConfig $YConfig 1
if [ $onlyCentral -eq 1 -o $PseudoData -eq 1 ]; then
    NumberOfPDFSet=0
fi
############################################################################
NJobs=1

Process=$1
if [ $Process -eq 1 ]; then
    echo Running scale variation.
    NProcess=135
    InitialProcess=121
elif [ $Process -eq 2 ]; then
    echo Running PDF uncertainty.
    NProcess=${NumberOfPDFSet}
    InitialProcess=0
elif [ $Process -eq 3 ]; then
    echo Generating stw template.
    NProcess=${NTemplate}
    InitialProcess=1
    PseudoData=0
fi

#NBosons=2
if [ $SeparateQuark -eq 1 ]; then
    NBosons=34
fi

IsReweight=$2
if [ $IsReweight -eq 1 ]; then
    IWGT=-1
    if [ $Process -eq 1 ]; then
        NProcess=${InitialProcess}
        InitialProcess=${InitialProcess}
    elif [ $Process -eq 2 ]; then
        NProcess=0
        InitialProcess=0
    fi
elif [ $IsReweight -eq 2 ]; then
    IWGT=-2
    if [ $Process -eq 1 ]; then
        InitialProcess=$[${InitialProcess}+1]
    elif [ $Process -eq 2 ]; then
        InitialProcess=1
    fi
elif [ $IsReweight -eq 0 ]; then
    IWGT=0
fi

if [ $PseudoData -eq 1 ]; then
    export SINT2W=${STWINPUT}
    WHICHPDF=PseudoData_${SINT2W}_${MYPDF}
fi

#if [ $TryOld -eq 1 ]; then
#    WHICHPDF=${WHICHPDF}_TryOld
#fi

#if [ $Process -eq 3 ]; then
#    WHICHPDF=Template_${WHICHPDF}
#fi

WHICHPDF=${WHICHPDF}${SCALECHOICE}
cd $WORKDIR
if [ ! -d "$WHICHPDF/" ]; then
    mkdir $WHICHPDF
fi

for((Boson=${InitialBoson};Boson<=$NBosons;Boson++)); do
########Set Boson Type############
if [ $SeparateQuark -eq 0 ]; then

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

elif [ $SeparateQuark -eq 1 ]; then

    if [ $Boson -eq 1 ]; then
    WHICHBOSON=ZU
    myBOSON=zu_uubar
    export ZUZDFLAG=1
    elif [ $Boson -eq 2 ]; then
    WHICHBOSON=ZD
    myBOSON=zd_ddbar
    export ZUZDFLAG=2
    elif [ $Boson -eq 3 ]; then
    WHICHBOSON=ZD
    myBOSON=zd_ssbar
    export ZUZDFLAG=3
    elif [ $Boson -eq 4 ]; then
    WHICHBOSON=ZU
    myBOSON=zu_ccbar
    export ZUZDFLAG=4
    elif [ $Boson -eq 5 ]; then
    WHICHBOSON=ZD
    myBOSON=zd_bbbar
    export ZUZDFLAG=5
    elif [ $Boson -eq 6 ]; then
    WHICHBOSON=ZU
    myBOSON=zu_ubaru
    export ZUZDFLAG=-1
    elif [ $Boson -eq 7 ]; then
    WHICHBOSON=ZD
    myBOSON=zd_dbard
    export ZUZDFLAG=-2
    elif [ $Boson -eq 8 ]; then
    WHICHBOSON=ZD
    myBOSON=zd_sbars
    export ZUZDFLAG=-3
    elif [ $Boson -eq 9 ]; then
    WHICHBOSON=ZU
    myBOSON=zu_cbarc
    export ZUZDFLAG=-4
    elif [ $Boson -eq 10 ]; then
    WHICHBOSON=ZD
    myBOSON=zd_bbarb
    export ZUZDFLAG=-5
    elif [ $Boson -eq 11 ]; then
    WHICHBOSON=W+
    myBOSON=wp_udbar
    export ZUZDFLAG=12
    elif [ $Boson -eq 12 ]; then
    WHICHBOSON=W+
    myBOSON=wp_usbar
    export ZUZDFLAG=13
    elif [ $Boson -eq 13 ]; then
    WHICHBOSON=W+
    myBOSON=wp_ubbar
    export ZUZDFLAG=15
    elif [ $Boson -eq 14 ]; then
    WHICHBOSON=W+
    myBOSON=wp_cdbar
    export ZUZDFLAG=42
    elif [ $Boson -eq 15 ]; then
    WHICHBOSON=W+
    myBOSON=wp_csbar
    export ZUZDFLAG=43
    elif [ $Boson -eq 16 ]; then
    WHICHBOSON=W+
    myBOSON=wp_cbbar
    export ZUZDFLAG=45
    elif [ $Boson -eq 17 ]; then
    WHICHBOSON=W-
    myBOSON=wm_dubar
    export ZUZDFLAG=12
    elif [ $Boson -eq 18 ]; then
    WHICHBOSON=W-
    myBOSON=wm_subar
    export ZUZDFLAG=13
    elif [ $Boson -eq 19 ]; then
    WHICHBOSON=W-
    myBOSON=wm_bubar
    export ZUZDFLAG=15
    elif [ $Boson -eq 20 ]; then
    WHICHBOSON=W-
    myBOSON=wm_dcbar
    export ZUZDFLAG=42
    elif [ $Boson -eq 21 ]; then
    WHICHBOSON=W-
    myBOSON=wm_scbar
    export ZUZDFLAG=43
    elif [ $Boson -eq 22 ]; then
    WHICHBOSON=W-
    myBOSON=wm_bcbar
    export ZUZDFLAG=45
    elif [ $Boson -eq 23 ]; then
    WHICHBOSON=W+
    myBOSON=wp_dbaru
    export ZUZDFLAG=-12
    elif [ $Boson -eq 24 ]; then
    WHICHBOSON=W+
    myBOSON=wp_sbaru
    export ZUZDFLAG=-13
    elif [ $Boson -eq 25 ]; then
    WHICHBOSON=W+
    myBOSON=wp_bbaru
    export ZUZDFLAG=-15
    elif [ $Boson -eq 26 ]; then
    WHICHBOSON=W+
    myBOSON=wp_dbarc
    export ZUZDFLAG=-42
    elif [ $Boson -eq 27 ]; then
    WHICHBOSON=W+
    myBOSON=wp_sbarc
    export ZUZDFLAG=-43
    elif [ $Boson -eq 28 ]; then
    WHICHBOSON=W+
    myBOSON=wp_bbarc
    export ZUZDFLAG=-45
    elif [ $Boson -eq 29 ]; then
    WHICHBOSON=W-
    myBOSON=wm_ubard
    export ZUZDFLAG=-12
    elif [ $Boson -eq 30 ]; then
    WHICHBOSON=W-
    myBOSON=wm_ubars
    export ZUZDFLAG=-13
    elif [ $Boson -eq 31 ]; then
    WHICHBOSON=W-
    myBOSON=wm_ubarb
    export ZUZDFLAG=-15
    elif [ $Boson -eq 32 ]; then
    WHICHBOSON=W-
    myBOSON=wm_cbard
    export ZUZDFLAG=-42
    elif [ $Boson -eq 33 ]; then
    WHICHBOSON=W-
    myBOSON=wm_cbars
    export ZUZDFLAG=-43
    elif [ $Boson -eq 34 ]; then
    WHICHBOSON=W-
    myBOSON=wm_cbarb
    export ZUZDFLAG=-45
    fi

fi

echo " "
echo ${myBOSON} production:
echo " "

##########Define Scale and PDF name####################
for((k=${InitialProcess};k<=${NProcess};k++)); do
if [ $k -lt 10 ]; then
    PDFDIR=${PDFFile}0${k}_${myBOSON}${NonPertFormat}
else
    PDFDIR=${PDFFile}${k}_${myBOSON}${NonPertFormat}
fi
ScaleVari=$[900+${k}]
ScaleDIR=Scale${ScaleVari}

##########build directory##############################
if [ $Process -eq 1 ]; then
    cd $WORKDIR
    PDFDIR=${PDFFile}00_${myBOSON}${NonPertFormat}
elif [ $Process -eq 2 ]; then
    cd $WORKDIR
    ScaleDIR=Scale908
    if [ $UseLatestPara -eq 1 ]; then
        ScaleVari=977
        ScaleDIR=Scale977
    fi
elif [ $Process -eq 3 ]; then
    cd $WORKDIR
    PDFDIR=${PDFFile}00_${myBOSON}${NonPertFormat}
    ScaleDIR=Scale908
    if [ $UseLatestPara -eq 1 ]; then
        ScaleVari=977
        ScaleDIR=Scale977
    fi
    STWINPUT=$[2252+3*$k]
    STWINPUT=0.${STWINPUT}
    echo stw input is $STWINPUT
fi

if [ $Process -ne 3 ]; then
    if [ ! -d "$WORKDIR/${WHICHPDF}/$PDFDIR/" ]; then
        mkdir $WORKDIR/${WHICHPDF}/$PDFDIR
    fi
    if [ ! -d "$WORKDIR/${WHICHPDF}/$PDFDIR/$ScaleDIR/" ]; then
        mkdir $WORKDIR/${WHICHPDF}/$PDFDIR/$ScaleDIR
    fi

    echo " "
    echo $PDFDIR $ScaleDIR
    echo " "

elif [ $Process -eq 3 ]; then
    if [ ! -d "$WORKDIR/${WHICHPDF}/${STWINPUT}/" ]; then
        mkdir $WORKDIR/${WHICHPDF}/${STWINPUT}
    fi
    if [ ! -d "$WORKDIR/${WHICHPDF}/${STWINPUT}/$PDFDIR/" ]; then
        mkdir $WORKDIR/${WHICHPDF}/${STWINPUT}/$PDFDIR
    fi
fi

for((n=1;n<=$NJobs;n++)); do

if [ $Process -ne 3 ]; then

    cd $WORKDIR/$WHICHPDF/$PDFDIR/$ScaleDIR

    if [ ! -d "$WORKDIR/$WHICHPDF/$PDFDIR/$ScaleDIR/JOB${n}/" ]; then
        mkdir $WORKDIR/$WHICHPDF/$PDFDIR/$ScaleDIR/JOB${n}
    fi

    cd $WORKDIR
    cp resbos_root 00resbos.in $WORKDIR/$WHICHPDF/$PDFDIR/$ScaleDIR/JOB${n}
    cd $WORKDIR/$WHICHPDF/$PDFDIR/$ScaleDIR/JOB${n}

elif [ $Process -eq 3 ]; then

    cd $WORKDIR/$WHICHPDF/$STWINPUT/$PDFDIR

    if [ ! -d "$WORKDIR/$WHICHPDF/$STWINPUT/$PDFDIR/JOB${n}/" ]; then
        mkdir $WORKDIR/$WHICHPDF/$STWINPUT/$PDFDIR/JOB${n}
    fi

    cd $WORKDIR
    cp resbos_root 00resbos.in $WORKDIR/$WHICHPDF/$STWINPUT/$PDFDIR/JOB${n}
    cd $WORKDIR/$WHICHPDF/$STWINPUT/$PDFDIR/JOB${n}

fi

if [ $IsReweight -eq 0 ]; then
    RANDOMSEED=$[${RANDOM}+1*${k}+10*${n}]
else
    #RANDOMSEED=14640
    RANDOMSEED=$[42100+10*${n}]
fi
sed -i "s/RANDOMSEED/$RANDOMSEED/g" 00resbos.in
sed -i "s/IWGT/$IWGT/g" 00resbos.in
sed -i "s/ISYGRID/$ISYGRID/g" 00resbos.in
cp 00resbos.in resbos.in

if [ $IsReweight -eq 2 ]; then
    if [ $Process -eq 1 ]; then
        ln -s ../../../${PDFFile}00_${myBOSON}${NonPertFormat}/Scale$[900+${InitialProcess}-1]/JOB${n}/weights.dat weights.dat
        cp ../../../${PDFFile}00_${myBOSON}${NonPertFormat}/Scale$[900+${InitialProcess}-1]/JOB${n}/resbos.root resbos.root
    elif [ $Process -eq 2 ]; then
        ln -s ../../../${PDFFile}00_${myBOSON}${NonPertFormat}/Scale908/JOB${n}/weights.dat weights.dat
        cp ../../../${PDFFile}00_${myBOSON}${NonPertFormat}/Scale908/JOB${n}/resbos.root resbos.root
    fi
fi

#sed -i "s/STWINPUT/$STWINPUT/g" resbosm.f

#############refresh the W-piece grid path and Y-piece grid path##############
source ~/pku_resbos/FrameWork/script/ResBosConfig.sh $WConfig $YConfig 0
##############################################################################
#if [ $TryOld -eq 1 ]; then
#    WHICHPDF=${WHICHPDF}_TryOld
#fi

if [ $PDFNumber -eq 1 ]; then

    if [ $TryOld -eq 1 ]; then
        if [ $WConfig -eq 2 ]; then
            echo WARNING!! There is no w432 gridfile in old path structure.
        fi

        ln -s ${GridDIR}/${MYPDF}/${myBOSON}/w321/${PDFDIR}_w321.out legacy_w321.out

        if [ $YConfig -eq 1 ]; then
            ln -s ${GridDIR}/${MYPDF}/${myBOSON}/y/${PDFDIR}_y.out legacy_yk.out
        elif [ $YConfig -eq 2 ]; then
            ln -s ${GridDIR}/${MYPDF}/${myBOSON}/yk/${PDFDIR}_yk.out legacy_yk.out
        fi
    else
        ln -s $WGridPath legacy_w321.out
        ln -s $YGridPath legacy_yk.out
    fi

else
    ln -s $WGridPath legacy_w321.out
    ln -s $YGridPath legacy_yk.out
fi

#ln -s $WORKDIR/../ResBos2/${MYPDF}_pds/${PDFDIR}/$ScaleDIR/y_1/JOB1/Grids/ResBos_GridFile_0.out legacy_w321.out
#ln -s $WORKDIR/../../old_legacy/${MYPDF}_pds/${PDFDIR}/${ScaleDIR}/JOB1/legacy.out legacy_w321.out
#ln -s $WORKDIR/../../get_yk/${PDFDIR}_${ScaleDIR}_yk.out legacy_yk.out

if [ $localrun -eq 1 ]; then

if [ $multicore -eq 1 ]; then
    nohup ./resbos_root &
else
    ./resbos_root
fi

else ##submit condor job

cat >>mySUB_ResBos_${WConfig}_${YConfig}_${myBOSON}_${k}_${n}  <<EOF
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

if [ $Process -ne 3 ]; then
    cd $WORKDIR/$WHICHPDF/$PDFDIR/$ScaleDIR/JOB${n}
elif [ $Process -eq 3 ]; then
    cd $WORKDIR/$WHICHPDF/$STWINPUT/$PDFDIR/JOB${n}
fi

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
source ~/setup.sh
if [ $PseudoData -eq 1 -o $Process -eq 3 ]; then
export SINT2W=${STWINPUT}
fi
if [ $Process -ne 3 ]; then
    cd $WORKDIR/$WHICHPDF/$PDFDIR/$ScaleDIR/JOB${n}
elif [ $Process -eq 3 ]; then
    cd $WORKDIR/$WHICHPDF/$STWINPUT/$PDFDIR/JOB${n}
fi
if [ $SeparateQuark -eq 1 ]; then
    if [ $Boson -eq 1 ]; then
    export myEventType=uubar
    elif [ $Boson -eq 2 ]; then
    export myEventType=ddbar
    elif [ $Boson -eq 3 ]; then
    export myEventType=ssbar
    elif [ $Boson -eq 4 ]; then
    export myEventType=ccbar
    elif [ $Boson -eq 5 ]; then
    export myEventType=bbbar
    elif [ $Boson -eq 6 ]; then
    export myEventType=ubaru
    elif [ $Boson -eq 7 ]; then
    export myEventType=dbard
    elif [ $Boson -eq 8 ]; then
    export myEventType=sbars
    elif [ $Boson -eq 9 ]; then
    export myEventType=cbarc
    elif [ $Boson -eq 10 ]; then
    export myEventType=bbarb
    elif [ $Boson -eq 11 ]; then
    export myEventType=udbar
    elif [ $Boson -eq 12 ]; then
    export myEventType=usbar
    elif [ $Boson -eq 13 ]; then
    export myEventType=ubbar
    elif [ $Boson -eq 14 ]; then
    export myEventType=cdbar
    elif [ $Boson -eq 15 ]; then
    export myEventType=csbar
    elif [ $Boson -eq 16 ]; then
    export myEventType=cbbar
    elif [ $Boson -eq 17 ]; then
    export myEventType=dubar
    elif [ $Boson -eq 18 ]; then
    export myEventType=subar
    elif [ $Boson -eq 19 ]; then
    export myEventType=bubar
    elif [ $Boson -eq 20 ]; then
    export myEventType=dcbar
    elif [ $Boson -eq 21 ]; then
    export myEventType=scbar
    elif [ $Boson -eq 22 ]; then
    export myEventType=bcbar
    elif [ $Boson -eq 23 ]; then
    export myEventType=dbaru
    elif [ $Boson -eq 24 ]; then
    export myEventType=sbaru
    elif [ $Boson -eq 25 ]; then
    export myEventType=bbaru
    elif [ $Boson -eq 26 ]; then
    export myEventType=dbarc
    elif [ $Boson -eq 27 ]; then
    export myEventType=sbarc
    elif [ $Boson -eq 28 ]; then
    export myEventType=bbarc
    elif [ $Boson -eq 29 ]; then
    export myEventType=ubard
    elif [ $Boson -eq 30 ]; then
    export myEventType=ubars
    elif [ $Boson -eq 31 ]; then
    export myEventType=ubarb
    elif [ $Boson -eq 32 ]; then
    export myEventType=cbard
    elif [ $Boson -eq 33 ]; then
    export myEventType=cbars
    elif [ $Boson -eq 34 ]; then
    export myEventType=cbarb
    fi
fi
#make
./resbos_root
###############################################
EOF
chmod +x myANA.sh

sbatch myANA.sh
#condor_submit mySUB_ResBos_${WConfig}_${YConfig}_${myBOSON}_${k}_${n}

fi

cd $WORKDIR/

done

done ##done process

done ##done boson

cd $WORKDIR/
