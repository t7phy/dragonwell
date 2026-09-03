#include "CTEQHelper/dtaReader.h"
#include "CTEQHelper/pdsReader.h"

using namespace std;

int main(int argc, char** argv)
{
 if(argc != 2){
   cout<<"usage: ReadFittingData filename"<<endl;
   return 0;
 }

 dtaReader data(argv[1]);
 data.openFile("saveFittingData.root");
 data.ReadFile();
 data.SaveFile();
 cout<<data.GetSumOfChi2()<<endl;

/*
 pdsReader pdf;
 pdf.Initialize(argv[1]);

 vector<double> XVector;

 for(int i = 0; i < 100; i++){
   XVector.push_back(pow(10, (5.0 / 3.0) * log10((i + 1) / 100.0)));
 }

 for(int i = 0; i < XVector.size(); i++){
   cout<<*right<<setw(10)<<fixed<<setprecision(6)<<"x: "<<XVector.at(i);
   cout<<*right<<setw(10)<<fixed<<setprecision(6)<<" c:"<<pdf.Getf(4, XVector.at(i), 100.0);
   cout<<*right<<setw(10)<<fixed<<setprecision(6)<<" cbar:"<<pdf.Getf(-4, XVector.at(i), 100.0);
   cout<<*right<<setw(10)<<fixed<<setprecision(6)<<" s:"<<pdf.Getf(3, XVector.at(i), 100.0);
   cout<<*right<<setw(10)<<fixed<<setprecision(6)<<" sbar:"<<pdf.Getf(-3, XVector.at(i), 100.0);
   cout<<endl;
 }
*/

 return 1;
}
