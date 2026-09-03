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
#include "TMinuitHelper/TMinuitHelper.h"

using namespace std;

int main(int argc, char** argv)
{
 FittingPDF();

 return 1;
}
