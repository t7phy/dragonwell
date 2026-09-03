thisdir=`pwd`
cd $thisdir

# cd ../Analysis_Selection/Tools/

python ../Tools/split.py --infile raw/MadeSelection --outfile splited/MadeSelection --m 1000000
cd $thisdir
