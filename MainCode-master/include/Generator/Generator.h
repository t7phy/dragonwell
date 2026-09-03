#ifndef Generator_Generator_h
#define Generator_Generator_h

#include <iostream>
#include "RootCommon.h"
#include "Generator/VegasSimple.h"

using namespace std;

class Generator : public VegasSimple
{
 public:

 TFile* file;
 TTree* tree;

 double testX;
 double testY;

 double Weight;

 vector<double> fY;

 Generator();
 Generator(int it1, int ncall1, int it2, int ncall2, int RandomSeed, int Ndim);
 Generator(int it1, int ncall1, int it2, int ncall2, int RandomSeed, int Ndim, vector<double> lower, vector<double> upper);

 virtual double ConstantFunction(vector<double> Y, double WGT){this->fY = Y; return sin(Y.at(0));};
 virtual double Constant2DFunction(vector<double> Y, double WGT){
   this->fY = Y;
//   Weight = Y.at(0) * Y.at(0) + Y.at(1) * Y.at(1);
   double F = sin(Y.at(0));
   Weight = F * WGT;
   if(!isFirstCall) MakeEvent();
   return F;
 }



 virtual void Initial(const char* fout, const char* ftree);
 virtual void DefineTree();
 virtual void MakeEvent();
 virtual void Close(){file->Write(); file->Close();};

};
#endif
