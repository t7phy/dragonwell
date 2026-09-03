#ifndef FillRoot_h
#define FillRoot_h

#include <iostream>
#include <fstream>
#include "TFile.h"
#include "TTree.h"

using namespace std;

class FillRoot
{
 public:

 ifstream infile;
 TFile *file;
 TTree *tree;

 bool isTest = false;

 virtual void Initial(const char* fin, const char* fout, const char* ftree);
 virtual void Test() {isTest = true;}
};
#endif
