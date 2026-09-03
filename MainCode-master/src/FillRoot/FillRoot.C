#include "FillRoot/FillRoot.h"

void FillRoot::Initial(const char* fin, const char* fout, const char* ftree)
{
 infile.open(fin, ios::in);
 file = new TFile(fout, "RECREATE");
 tree = new TTree(ftree, ftree);
 tree->SetDirectory(file);
}
