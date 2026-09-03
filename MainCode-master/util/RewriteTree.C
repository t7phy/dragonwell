#include <iostream>
#include <fstream>
#include "RootCommon.h"

using namespace std;

int main(int argc, char** argv)
{
 TString FileName = argv[1];
 TFile* infile = new TFile(FileName + ".root");
 TFile* outfile = new TFile(FileName + "_rewrite.root", "RECREATE");

 TTree* tree = (TTree *)infile->Get("LJAlgo/nominal");

 outfile->cd();
 TTree* newtree = (TTree *)tree->CloneTree();
 newtree->Write();

 outfile->Close();

 return 1;
}
