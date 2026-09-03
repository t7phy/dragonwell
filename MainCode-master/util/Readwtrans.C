#include <iostream>
#include <fstream>
#include "RootCommon.h"
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
#include "TMinuitHelper/TMinuitHelper.h"
#include "Calculation/Iterate.h"
#include <Eigen/Dense>

using namespace std;

int main(int argc, char** argv)
{
 Eigen::VectorXd xtrans = Eigen::VectorXd(28);
 Eigen::MatrixXd wtrans = Eigen::MatrixXd(28, 28);

 for(int i = 0; i < 28; i++) xtrans(i) = 0.0;

 ifstream infile("wtrans.txt");
 for(int i = 0; i < 28; i++){
   for(int j = 0; j < 28; j++){
     infile >> wtrans(i, j);
   }
 }
 cout<<wtrans<<endl;

 Iterate* EV = new Iterate();
 EV->Initialize();
 EV->wtrans = wtrans;
 EV->xtrans = xtrans;
 EV->ProduceEVSet("newpdf");

 return 1;
}

