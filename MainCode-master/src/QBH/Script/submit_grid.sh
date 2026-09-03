#!/bin/bash

subName=250121_tree.root

nList=`ls *.in |wc -l`

for((i=1;i<=${nList};i++));do

ListName=`ls *.in |head -$i |tail -1`

if [[ `echo ${ListName} |grep mc23a` != "" ]]; then
    Period=mc23a
    Process=${ListName%_${Period}.in}
elif [[ `echo ${ListName} |grep mc23d` != "" ]]; then
    Period=mc23d
    Process=${ListName%_${Period}.in}
elif [[ `echo ${ListName} |grep mc23e` != "" ]]; then
    Period=mc23e
    Process=${ListName%_${Period}.in}
elif [[ `echo ${ListName} |grep data22` != "" ]]; then
    Period=data22
    Process=data
elif [[ `echo ${ListName} |grep data23` != "" ]]; then
    Period=data23
    Process=data
elif [[ `echo ${ListName} |grep data24` != "" ]]; then
    Period=data24
    Process=data
fi

echo $ListName $Period ${Process}

if [ -d submitDir_grid ]; then
    rm -r submitDir_grid
fi

xAH_run.py --files ./${ListName} --inputList --inputRucio --config ../../source/LJAlgo/data/config/LJConfig.py --submitDir ./submitDir_grid --extraOptions "--campaign ${Period}" prun --optGridOutputSampleName="user.%nickname%.Run3_${Process}_${Period}.%in:name[2]%.%in:name[6]%.LJNtupleMaker.${subName}"

done


