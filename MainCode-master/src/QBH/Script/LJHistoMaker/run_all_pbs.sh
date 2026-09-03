#!/bin/bash


echo "Submitting nominal jobs"
./steer_systs.py --systs_mode nominal_only --run_condor

echo "Submitting SF jobs"
./steer_systs.py --systs_mode SF --run_condor
echo "======================="
echo "Submitting calib jobs"
./steer_systs.py --systs_mode calib --run_condor
echo "======================="
echo "Submitting MC Sherpa jobs"
./steer_systs.py --systs_mode MC_Sherpa --run_condor
echo "======================="
echo "Submitting MC Top jobs"
./steer_systs.py --systs_mode MC_Top --run_condor
echo "======================="
echo "Submitting fake jobs"
./steer_systs.py --systs_mode fakes --run_condor

