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

using namespace std;

int main(int argc, char** argv)
{
 Iterate* EV = new Iterate();
 EV->Initialize();
// EV->ReadHessianFortran("i2Tn3.ev");
 EV->IterateHessian();
 EV->ProduceEVSet("newpdf");

 return 1;
}

