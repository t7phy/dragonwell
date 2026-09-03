#include <iostream>
#include <fstream>
#include "RootCommon.h"
#include "PDFHelper/PDFHelper.h"
#include "CTEQHelper/HoppetInterface.h"
#include "CTEQHelper/PDFEvolve.h"
#include "Calculation/ApplGridHelper.h"
#include "Calculation/FastNLOHelper.h"
#include "Calculation/Dataset.h"
#include "Calculation/DataPoint.h"
#include "Calculation/Config.h"
#include "Calculation/QCDSet.h"
#include "Calculation/ThreadChi2.h"
#include "Calculation/PDFChi2.h"
#include "Calculation/CalcDIS.h"
#include "Calculation/CalcVBP.h"
#include "Tools/Tools.h"

using namespace std;

int main(int argc, char** argv)
{
 vector<TString> FlavorList = {"dv", "uv", "gluon", "dmu", "dpu", "str"};
 vector<int> FlagList = {981, 981, 848, 219, 218, 220};

 PDFEvolve* pdf = new PDFEvolve();

 pdf->SetParameter("dv",    vector<double>{ 0.76317,  3.03609, 2.61407,  1.82746,  2.72032,  0.00000,  0.00000,  0.00000,  0.00000,  0.00000,  0.00000,  0.00000});
 pdf->SetParameter("uv",    vector<double>{ 0.76317,  3.03609, 1.50192, -0.14666,  1.67108,  0.00000,  0.00000,  0.00000,  0.00000,  0.00000,  0.00000,  0.00000});
 pdf->SetParameter("gluon", vector<double>{ 0.53101,  3.14810, 3.03140, -1.70494,  0.00000,  0.00000,  0.00000,  0.00000,  0.00000,  0.00000,  0.00000,  0.00000});
 pdf->SetParameter("dmu",   vector<double>{-0.02194,  7.73657, 4.00000,  0.29223,  0.64695,  0.47492,  0.74137,  0.61791,  0.19493,  0.87087,  0.26669,  0.73317});
 pdf->SetParameter("dpu",   vector<double>{-0.02194,  7.73657, 4.00000,  0.29223,  0.64695,  0.47492,  0.74137,  0.61791,  0.19493,  0.87087,  0.26669,  0.73317});
 pdf->SetParameter("str",   vector<double>{-0.02194, 10.30986, 4.00000,  0.46599,  0.46599,  0.22525,  0.22525,  1.00000,  0.00000,  0.00000,  0.00000,  0.00000});
 pdf->SetInitialgluonMomentum(0.3846129);
 pdf->SetInitialStrangeB0(0.5146522);

 pdf->Initialize(1, FlavorList, FlagList);

 HoppetInterface* hoppet = new HoppetInterface();
 hoppet->SetAlphaSQ0(0.118, 91.19);
 hoppet->Initialize(pdf, 1.295);

 pdsReader* mypdf = hoppet->PrepareCTEQTable();

 CalcDIS* run = new CalcDIS();
 run->InitialCTEQPDF(mypdf);
 run->mSetDis();
// for(int i = 1; i <= 10000; i++){
//   double Value = run->F2ZMNS2(0.1, 10.0, 10.0, 1, 1, 5);
//   if(i % 1000 == 0) cout<<getTime()<<"  "<<Value<<endl;
// }

 CalcVBP* vbp = new CalcVBP();
 double xmin = 2.2806515270168380e-2;
 double xmax = 6.5381173078592800e-2;
 FortranArray1D<double> xa{1, 24};
 FortranArray1D<double> argp{1, 24};
 FortranArray1D<double> argm{1, 24};
 double ansp = 0.0;
 double ansm = 0.0;
 vbp->gq11(xmin, xmax, 4, xa, argp, ansp);
 for(int i = 1; i <= 24; i++) cout<<xa(i)<<endl;

 return 1;
}

