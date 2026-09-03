#include <iostream>
#include "Tools/Tools.h"

using namespace std;

int main(int argc, char** argv)
{
 if(argc != 3){
   cout<<"usage: ./GetPValue chi2 Npt"<<endl;
   return 0;
 }

 double Chi2 = stod(argv[1]);
 double Npt = stoi(argv[2]);
 double PValue = TranslateChi2ToPValue(Chi2, Npt);
 double Spartyness = TranslateChi2ToSpartyness(Chi2, Npt);

 cout<<"P-Value: "<<PValue<<" Spartyness: "<<Spartyness<<endl;

 return 1;
}
