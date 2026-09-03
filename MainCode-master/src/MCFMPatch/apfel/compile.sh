#!/bin/bash
#cmake .. -DCMAKE_INSTALL_PREFIX=. -DAPFEL_Python_SITEARCH=/mnt/home/fuyao3/apfel/build
make -j
chmod -r lib/libAPFEL.so.0.0.0
chmod -r lib/libAPFELevol.so.0.0.0
make install
chmod +r lib/libAPFEL.so.0.0.0
chmod +r lib/libAPFELevol.so.0.0.0

