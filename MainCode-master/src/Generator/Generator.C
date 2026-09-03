#include "Generator/Generator.h"

Generator::Generator()
{

}

Generator::Generator(int it1, int ncall1, int it2, int ncall2, int RandomSeed, int Ndim)
{
 this->It1 = it1;
 this->Ncall1 = ncall1;
 this->It2 = it2;
 this->Ncall2 = ncall2;
 this->RandomSeed = RandomSeed;
 this->NDimension = Ndim;

 vector<double> lower;
 vector<double> upper;

 for(int i = 0; i < Ndim; i++){
   lower.push_back(0.0);
   upper.push_back(1.0);
 }

 SetIntegrationRange(lower, upper);

 InitialXi();

}

Generator::Generator(int it1, int ncall1, int it2, int ncall2, int RandomSeed, int Ndim, vector<double> lower, vector<double> upper)
{
 this->It1 = it1;
 this->Ncall1 = ncall1;
 this->It2 = it2;
 this->Ncall2 = ncall2;
 this->RandomSeed = RandomSeed;
 this->NDimension = Ndim;

 SetIntegrationRange(lower, upper);

 InitialXi();

}

void Generator::Initial(const char* fout, const char* ftree)
{
 file = new TFile(fout, "RECREATE");
 tree = new TTree(ftree, ftree);
 tree->SetDirectory(file);
}

void Generator::DefineTree()
{
 tree->Branch("testX", &testX, "testX/D");
// tree->Branch("testY", &testY, "testY/D");
 tree->Branch("Weight", &Weight, "Weight/D");

}

void Generator::MakeEvent()
{
 testX = fY.at(0);
// testY = fY.at(1);

 tree->Fill();
}


