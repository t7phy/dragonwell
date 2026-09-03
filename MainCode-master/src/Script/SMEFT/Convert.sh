#!/bin/bash
gzip -d $1/unweighted_events.lhe.gz
../ExRootAnalysis/ExRootLHEFConverter $1/unweighted_events.lhe $2
