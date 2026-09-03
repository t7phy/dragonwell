#!/bin/bash
RunTags=WZPol16

FileList=dataSample15.list
NFile=`cat $FileList |wc -l`
for((n=1;n<=$NFile;n++)); do
Name[0]=`cat $FileList |head -$n |tail -1`
Name[1]=${Name[0]:0:6}
Name[2]=${Name[0]:26:8}
rucio erase user.yafu.${RunTags}${Name[1]}.${Name[2]}_physics_Main_hist
rucio erase user.yafu.${RunTags}${Name[1]}.${Name[2]}_physics_Main_myOutput.root
rucio erase user.yafu.${RunTags}${Name[1]}.${Name[2]}_physics_Main.log
done
unset Name

FileList=dataSample16.list
NFile=`cat $FileList |wc -l`
for((n=1;n<=$NFile;n++)); do
Name[0]=`cat $FileList |head -$n |tail -1`
Name[1]=${Name[0]:0:6}
Name[2]=${Name[0]:26:8}
rucio erase user.yafu.${RunTags}${Name[1]}.${Name[2]}_physics_Main_hist
rucio erase user.yafu.${RunTags}${Name[1]}.${Name[2]}_physics_Main_myOutput.root
rucio erase user.yafu.${RunTags}${Name[1]}.${Name[2]}_physics_Main.log
done
unset Name

FileList=dataSample17.list
NFile=`cat $FileList |wc -l`
for((n=1;n<=$NFile;n++)); do
Name[0]=`cat $FileList |head -$n |tail -1`
Name[1]=${Name[0]:0:6}
Name[2]=${Name[0]:26:8}
rucio erase user.yafu.${RunTags}${Name[1]}.${Name[2]}_physics_Main_hist
rucio erase user.yafu.${RunTags}${Name[1]}.${Name[2]}_physics_Main_myOutput.root
rucio erase user.yafu.${RunTags}${Name[1]}.${Name[2]}_physics_Main.log
done
unset Name

FileList=dataSample18.list
NFile=`cat $FileList |wc -l`
for((n=1;n<=$NFile;n++)); do
Name[0]=`cat $FileList |head -$n |tail -1`
Name[1]=${Name[0]:0:6}
Name[2]=${Name[0]:26:8}
rucio erase user.yafu.${RunTags}${Name[1]}.${Name[2]}_physics_Main_hist
rucio erase user.yafu.${RunTags}${Name[1]}.${Name[2]}_physics_Main_myOutput.root
rucio erase user.yafu.${RunTags}${Name[1]}.${Name[2]}_physics_Main.log
done
unset Name

FileList=mc16aSample.list
NFile=`cat $FileList |wc -l`
for((n=1;n<=$NFile;n++)); do
FullName=`cat $FileList |head -$n |tail -1`
Name=(${FullName//./ })
rucio erase user.yafu.${RunTags}MC16a.${Name[1]}_${Name[2]}_hist
rucio erase user.yafu.${RunTags}MC16a.${Name[1]}_${Name[2]}_myOutput.root
rucio erase user.yafu.${RunTags}MC16a.${Name[1]}_${Name[2]}.log
done
unset Name

FileList=polar_mc16aSample_new_new.list
NFile=`cat $FileList |wc -l`
for((n=1;n<=$NFile;n++)); do
FullName=`cat $FileList |head -$n |tail -1`
Name=(${FullName//./ })
rucio erase user.yafu.${RunTags}MC16a.${Name[1]}_${Name[2]}_hist
rucio erase user.yafu.${RunTags}MC16a.${Name[1]}_${Name[2]}_myOutput.root
rucio erase user.yafu.${RunTags}MC16a.${Name[1]}_${Name[2]}.log
done
unset Name

FileList=mc16dSample.list
NFile=`cat $FileList |wc -l`
for((n=1;n<=$NFile;n++)); do
FullName=`cat $FileList |head -$n |tail -1`
Name=(${FullName//./ })
rucio erase user.yafu.${RunTags}MC16d.${Name[1]}_${Name[2]}_hist
rucio erase user.yafu.${RunTags}MC16d.${Name[1]}_${Name[2]}_myOutput.root
rucio erase user.yafu.${RunTags}MC16d.${Name[1]}_${Name[2]}.log
done
unset Name

FileList=polar_mc16dSample_new_new.list
NFile=`cat $FileList |wc -l`
for((n=1;n<=$NFile;n++)); do
FullName=`cat $FileList |head -$n |tail -1`
Name=(${FullName//./ })
rucio erase user.yafu.${RunTags}MC16d.${Name[1]}_${Name[2]}_hist
rucio erase user.yafu.${RunTags}MC16d.${Name[1]}_${Name[2]}_myOutput.root
rucio erase user.yafu.${RunTags}MC16d.${Name[1]}_${Name[2]}.log
done
unset Name

FileList=mc16eSample.list
NFile=`cat $FileList |wc -l`
for((n=1;n<=$NFile;n++)); do
FullName=`cat $FileList |head -$n |tail -1`
Name=(${FullName//./ })
rucio erase user.yafu.${RunTags}MC16e.${Name[1]}_${Name[2]}_hist
rucio erase user.yafu.${RunTags}MC16e.${Name[1]}_${Name[2]}_myOutput.root
rucio erase user.yafu.${RunTags}MC16e.${Name[1]}_${Name[2]}.log
done
unset Name

FileList=polar_mc16eSample_new_new.list
NFile=`cat $FileList |wc -l`
for((n=1;n<=$NFile;n++)); do
FullName=`cat $FileList |head -$n |tail -1`
Name=(${FullName//./ })
rucio erase user.yafu.${RunTags}MC16e.${Name[1]}_${Name[2]}_hist
rucio erase user.yafu.${RunTags}MC16e.${Name[1]}_${Name[2]}_myOutput.root
rucio erase user.yafu.${RunTags}MC16e.${Name[1]}_${Name[2]}.log
done
unset Name

