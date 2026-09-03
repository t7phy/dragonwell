#include <iostream>
#include <fstream>
#include "RootCommon.h"
#include "Tools/Tools.h"
//#include "Calculation/ThreadAppl.h"
#include "Calculation/ThreadChi2.h"
#include "CTEQHelper/pdsReader.h"

using namespace std;

int main(int argc, char** argv)
{
 ROOT::EnableThreadSafety();
 TDirectory::AddDirectory(kFALSE);
 TH1::AddDirectory(kFALSE);

 vector<TString> GridNames;
 GridNames = {
   "/msu/data/t3work12/yaofu/FittingCode/ApplGridtables/250_1.root",
   "/msu/data/t3work12/yaofu/FittingCode/ApplGridtables/250_2.root",
   "/msu/data/t3work12/yaofu/FittingCode/ApplGridtables/250_3.root",
   "/msu/data/t3work12/yaofu/FittingCode/ApplGridtables/253_4.root",
   "/msu/data/t3work12/yaofu/FittingCode/ApplGridtables/253_5.root",
   "/msu/data/t3work12/yaofu/FittingCode/ApplGridtables/253_6.root"
 };
/*
 vector<ThreadAppl *> m_applgrid(GridNames.size());

 pdsReader* pdf = new pdsReader();
 pdf->Initialize("mypdf.pds");

 for(int i = 0; i < m_applgrid.size(); i++){
   m_applgrid.at(i) = new ThreadAppl();
   m_applgrid.at(i)->InitialGrid(GridNames.at(i));
   m_applgrid.at(i)->InitialCTEQPDF(pdf, i + 1);
 }

 map<int, pthread_t> thread;
 for(int i = 0; i < m_applgrid.size(); i++){
   pthread_create(&thread[i], NULL, ThreadRunAppl, m_applgrid.at(i));
   cout<<"Thread No."<<i<<" has created."<<endl;
 }

 for(int i = 0; i < m_applgrid.size(); i++){
   pthread_join(thread.at(i), NULL);
   cout<<"Thread No."<<i<<" has finished."<<endl;
 }
*/

// Convolute(Theory);

/* for(int j = 0; j < TotalThread; j++){
   Data.at(j) = GenPseudodata(1.0, Theory[j]->GetResultPtr(), "_Data");
 }

 double TotalChi2 = 0.0;

 for(int i = 0; i < 10; i++){
   Convolute(Theory);

   for(int j = 0; j < TotalThread; j++){
     TotalChi2 += CalculateChi2(Theory.at(j)->GetResultPtr(), Data.at(j));
   }

   cout<<"Chi2 = "<<TotalChi2<<endl;

   for(int j = 0; j < TotalThread; j++){
     Theory.at(j)->DeleteResult();
   }

   TotalChi2 = 0.0;
 }
*/

 return 1;
}

