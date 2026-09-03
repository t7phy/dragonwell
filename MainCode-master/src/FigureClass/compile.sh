#!/bin/bash
g++ -std=c++17 -g MakeClassFull.C -I$ROOTSYS/include `root-config --libs` -o MakeClassFull
