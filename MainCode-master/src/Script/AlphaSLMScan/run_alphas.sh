#!/bin/bash
WORKDIR=$PWD

BaseName=i2TAn3m248_mDIS

alphas[1]=0.110
alphas[2]=0.111
alphas[3]=0.112
alphas[4]=0.113
alphas[5]=0.114
alphas[6]=0.115
alphas[7]=0.116
alphas[8]=0.117
alphas[9]=0.118
alphas[10]=0.119
alphas[11]=0.120
alphas[12]=0.121
alphas[13]=0.122
alphas[14]=0.123
alphas[15]=0.124
alphas[16]=0.1164
alphas[17]=0.1123
alphas[18]=0.1206
alphas[19]=0.1139
alphas[20]=0.1177
alphas[21]=0.1151

for((i=1;i<=15;i++)); do
cd $WORKDIR
mkdir $WORKDIR/CentralFit_AlphaS_${alphas[${i}]}
cp f06b.x 00${BaseName}.inp $WORKDIR/CentralFit_AlphaS_${alphas[${i}]}

cd $WORKDIR/CentralFit_AlphaS_${alphas[${i}]}
sed -i "s/ALPHAS/${alphas[${i}]}/g" 00${BaseName}.inp
cp 00${BaseName}.inp ${BaseName}.inp

cat >>myANA.sh  <<EOF
#!/bin/bash --login
#SBATCH --job-name=cp18h_12b   # job name
#SBATCH --nodes=1               # total number of nodes
#SBATCH --ntasks-per-node=1     # total number of tasks requested
#SBATCH --cpus-per-task=38       # total number of tasks requested
#SBATCH --threads-per-core=1    # one core each thread
#SBATCH --mem=60G            # job memory limit
#SBATCH --time=30:00:00             # run time (hh:mm:ss) - 3:00:00 hours
#SBATCH --output=%x-%j.out      # queue (partition) 
source ~/setup.sh
cd ${WORKDIR}/CentralFit_AlphaS_${alphas[${i}]}
./f06b.x ${BaseName}.inp > ${BaseName}.con
EOF
chmod +x myANA.sh

sbatch myANA.sh

done
cd $WORKDIR
