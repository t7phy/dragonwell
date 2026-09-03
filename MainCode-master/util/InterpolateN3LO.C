#include <iostream>
#include "RootCommon.h"
#include "Tools/Tools.h"
#include "Tools/Interpolation.h"
#include "ReadResBosGrid/ReadResBosGrid.h"

using namespace std;

int main(int argc, char** argv)
{
 TString FileName;
 vector<TString> NNLOList;
 vector<TString> NLOList;

 ifstream infile;

 infile.open("NNLO.list");
 while(infile >> FileName){
   NNLOList.push_back(FileName);
 }
 infile.close();

 infile.open("NLO.list");
 while(infile >> FileName){
   NLOList.push_back(FileName);
 }
 infile.close();

 ReadResBosGrid* NNLOGrid = new ReadResBosGrid();
 NNLOGrid->LoadPertKFactor(NNLOList);

 ReadResBosGrid* NLOGrid = new ReadResBosGrid();
 NLOGrid->LoadPertKFactor(NLOList);

 Interpolation* NNLOInterp = new Interpolation();
 NNLOInterp->InitializeThreeD(NNLOGrid->XVector, NNLOGrid->YVector, NNLOGrid->ZVector, NNLOGrid->Points);

 Interpolation* NLOInterp = new Interpolation();
 NLOInterp->InitializeThreeD(NLOGrid->XVector, NLOGrid->YVector, NLOGrid->ZVector, NLOGrid->Points);

 ReadResBosGrid* AsymGrid = new ReadResBosGrid();
 AsymGrid->openFile("Asym3_zu.out");
 AsymGrid->LoadAsym();

 ReadResBosGrid* YGrid = new ReadResBosGrid();
 YGrid->openFile("i2Tn3.00_zu_IY6_Scale1051_yk.out");
 YGrid->LoadY();
 YGrid->OutputY("test_zu.out", AsymGrid, NNLOInterp, NLOInterp);

 ReadResBosGrid* AsymGrid_zd = new ReadResBosGrid();
 AsymGrid_zd->openFile("Asym3_zd.out");
 AsymGrid_zd->LoadAsym();

 ReadResBosGrid* YGrid_zd = new ReadResBosGrid();
 YGrid_zd->openFile("i2Tn3.00_zd_IY6_Scale1051_yk.out");
 YGrid_zd->LoadY();
 YGrid_zd->OutputY("test_zd.out", AsymGrid_zd, NNLOInterp, NLOInterp);

/* cout<<20.0<<" "<<90.0<<" "<<1.0<<" "<<  NNLOInterp->ThreeDInp(2, 2, 2, 20.0, 90.0, 1.0)<<" "<<  NLOInterp->ThreeDInp(2, 2, 2, 20.0, 90.0, 1.0)<<endl;
 cout<<20.0<<" "<<90.0<<" "<<1.1<<" "<<  NNLOInterp->ThreeDInp(2, 2, 2, 20.0, 90.0, 1.1)<<" "<<  NLOInterp->ThreeDInp(2, 2, 2, 20.0, 90.0, 1.1)<<endl;
 cout<<20.0<<" "<<90.0<<" "<<2.0<<" "<<  NNLOInterp->ThreeDInp(2, 2, 2, 20.0, 90.0, 2.0)<<" "<<  NLOInterp->ThreeDInp(2, 2, 2, 20.0, 90.0, 2.0)<<endl;
 cout<<175.0<<" "<<90.0<<" "<<0.2<<" "<< NNLOInterp->ThreeDInp(2, 2, 2, 175.0, 90.0, 0.2)<<" "<< NLOInterp->ThreeDInp(2, 2, 2, 175.0, 90.0, 0.2)<<endl;
 cout<<175.0<<" "<<90.0<<" "<<0.6<<" "<< NNLOInterp->ThreeDInp(2, 2, 2, 175.0, 90.0, 0.6)<<" "<< NLOInterp->ThreeDInp(2, 2, 2, 175.0, 90.0, 0.6)<<endl;
 cout<<175.0<<" "<<90.0<<" "<<1.8<<" "<< NNLOInterp->ThreeDInp(2, 2, 2, 175.0, 90.0, 1.8)<<" "<< NLOInterp->ThreeDInp(2, 2, 2, 175.0, 90.0, 1.8)<<endl;
 cout<<176.0<<" "<<90.0<<" "<<0.2<<" "<< NNLOInterp->ThreeDInp(2, 2, 2, 176.0, 90.0, 0.2)<<" "<< NLOInterp->ThreeDInp(2, 2, 2, 176.0, 90.0, 0.2)<<endl;
 cout<<176.0<<" "<<90.0<<" "<<0.6<<" "<< NNLOInterp->ThreeDInp(2, 2, 2, 176.0, 90.0, 0.6)<<" "<< NLOInterp->ThreeDInp(2, 2, 2, 176.0, 90.0, 0.6)<<endl;
 cout<<176.0<<" "<<90.0<<" "<<1.8<<" "<< NNLOInterp->ThreeDInp(2, 2, 2, 176.0, 90.0, 1.8)<<" "<< NLOInterp->ThreeDInp(2, 2, 2, 176.0, 90.0, 1.8)<<endl;
 cout<<200.0<<" "<<90.0<<" "<<1.0<<" "<< NNLOInterp->ThreeDInp(2, 2, 2, 200.0, 90.0, 1.0)<<" "<< NLOInterp->ThreeDInp(2, 2, 2, 200.0, 90.0, 1.0)<<endl;
 cout<<200.0<<" "<<90.0<<" "<<1.1<<" "<< NNLOInterp->ThreeDInp(2, 2, 2, 200.0, 90.0, 1.1)<<" "<< NLOInterp->ThreeDInp(2, 2, 2, 200.0, 90.0, 1.1)<<endl;
 cout<<200.0<<" "<<90.0<<" "<<2.0<<" "<< NNLOInterp->ThreeDInp(2, 2, 2, 200.0, 90.0, 2.0)<<" "<< NLOInterp->ThreeDInp(2, 2, 2, 200.0, 90.0, 2.0)<<endl;
 cout<<200.0<<" "<<120.0<<" "<<1.0<<" "<<NNLOInterp->ThreeDInp(2, 2, 2, 200.0, 120.0, 1.0)<<" "<<NLOInterp->ThreeDInp(2, 2, 2, 200.0, 120.0, 1.0)<<endl;
 cout<<200.0<<" "<<120.0<<" "<<1.1<<" "<<NNLOInterp->ThreeDInp(2, 2, 2, 200.0, 120.0, 1.1)<<" "<<NLOInterp->ThreeDInp(2, 2, 2, 200.0, 120.0, 1.1)<<endl;
 cout<<200.0<<" "<<120.0<<" "<<2.0<<" "<<NNLOInterp->ThreeDInp(2, 2, 2, 200.0, 120.0, 2.0)<<" "<<NLOInterp->ThreeDInp(2, 2, 2, 200.0, 120.0, 2.0)<<endl;
*/
 return 1;
}

