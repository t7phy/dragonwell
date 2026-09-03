#!/bin/bash
#setupATLAS
lsetup rucio
voms-proxy-init -voms atlas --valid 72:00
localSetupPandaClient --noAthenaCheck
