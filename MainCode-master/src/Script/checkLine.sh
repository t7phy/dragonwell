#/bin/bash
NFile=`ls *.data |wc -l`
for((k=1;k<=${NFile};k++)); do
FileName[${k}]=`ls *.data|head -${k}|tail -1`
FileName[${k}]=${FileName[${k}]%.data}
done

for((k=1;k<=${NFile};k++)); do
NData=`cat ${FileName[${k}]}.data |wc -l`
NData=`echo "$NData*59-4*59+2" |bc`
NTheory=`cat ${FileName[${k}]}.theory |wc -l`
if [[ $NData == $NTheory ]]; then
echo ${FileName[${k}]} check lines ok
else
echo ${FileName[${k}]} mismatch
fi
done
