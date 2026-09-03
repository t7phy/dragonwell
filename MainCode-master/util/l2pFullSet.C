#include <iostream>
#include <fstream>
#include "RootCommon.h"
#include "CTEQHelper/pdsReader.h"
#include "CTEQHelper/HoppetInterface.h"

using namespace std;

int main(int argc, char** argv)
{
 if(argc != 3){
   cout<<"usage: ./l2pFullSet LHAPDFName nSet"<<endl;
   return 0;
 }

 HoppetInterface* hoppet = new HoppetInterface();

 pdsReader* pdf = new pdsReader();
 pdf->InputxQVector(hoppet->xVector, hoppet->QVector);
 pdf->l2pFullSet(argv[1], stoi(argv[2]));

 return 1;
}
