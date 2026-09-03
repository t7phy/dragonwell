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
cd /mnt/home/fuyao3/Work/MainCode/run/FixedTarget_pp830a016
GetFixed e605
GetFixed e866ppxf
GetFixed e866f_pp
GetFixed e866f_pd
GetFixed e906aF_pp
GetFixed e906aF_pd
