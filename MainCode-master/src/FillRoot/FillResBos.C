#include "FillRoot/FillResBos.h"

using namespace std;

void FillResBos::DefineTree()
{
 tree->Branch("Px_d2", &Px_d2, "Px_d2/F");
 tree->Branch("Py_d2", &Py_d2, "Py_d2/F");
 tree->Branch("Pz_d2", &Pz_d2, "Pz_d2/F");
 tree->Branch("E_d2", &E_d2, "E_d2/F");
 tree->Branch("Px_d1", &Px_d1, "Px_d1/F");
 tree->Branch("Py_d1", &Py_d1, "Py_d1/F");
 tree->Branch("Pz_d1", &Pz_d1, "Pz_d1/F");
 tree->Branch("E_d1", &E_d1, "E_d1/F");

 tree->Branch("Px_V", &Px_V, "Px_V/F");
 tree->Branch("Py_V", &Py_V, "Py_V/F");
 tree->Branch("Pz_V", &Pz_V, "Pz_V/F");
 tree->Branch("E_V", &E_V, "E_V/F");

 tree->Branch("WT00", &WT00, "WT00/F");

 tree->Branch("Px_g2", &Px_g2, "Px_g2/F");
 tree->Branch("Py_g2", &Py_g2, "Py_g2/F");
 tree->Branch("Pz_g2", &Pz_g2, "Pz_g2/F");
 tree->Branch("E_g2", &E_g2, "E_g2/F");
 tree->Branch("Px_g1", &Px_g1, "Px_g1/F");
 tree->Branch("Py_g1", &Py_g1, "Py_g1/F");
 tree->Branch("Pz_g1", &Pz_g1, "Pz_g1/F");
 tree->Branch("E_g1", &E_g1, "E_g1/F");

}

void FillResBos::FillIn()
{
 int count = 0;
 while(infile>>evt){
   count++;
   if(count % 1000000 == 0) cout<<"Finish event: "<<count<<endl;

   infile >> WT00;

   infile >> skip >> skip >> skip;

   infile >> skip;
   if(skip == 90) infile >> Px_V >> Py_V >> Pz_V >> E_V >> skip >> skip;
   infile >> skip;
   if(skip == 12) infile >> Px_d1 >> Py_d1 >> Pz_d1 >> E_d1 >> skip >> skip;
   infile >> skip;
   if(skip == -12) infile >> Px_d2 >> Py_d2 >> Pz_d2 >> E_d2 >> skip >> skip;

   infile >> skip;
   if(skip > 9){
     if(skip == 10) infile >> Px_g1 >> Py_g1 >> Pz_g1 >> E_g1 >> skip >> skip;
     infile >> skip;
     if(skip > 9){
       if(skip == 10) infile >> Px_g2 >> Py_g2 >> Pz_g2 >> E_g2 >> skip >> skip;
       infile >> skip;
     }
     else{
       Px_g2 = 0;
       Py_g2 = 0;
       Pz_g2 = 0;
       E_g2 = 0;
     }
   }
   else{
     Px_g1 = 0;
     Py_g1 = 0;
     Pz_g1 = 0;
     E_g1 = 0;
     Px_g2 = 0;
     Py_g2 = 0;
     Pz_g2 = 0;
     E_g2 = 0;
   }

   tree->Fill();

   if(isTest){
     cout<<evt<<"  "<<WT00<<endl;
     cout<<Px_V<<"  "<<Py_V<<"  "<<Pz_V<<"  "<<E_V<<" "<<endl;
     cout<<Px_d1<<"  "<<Py_d1<<"  "<<Pz_d1<<"  "<<E_d1<<"  "<<endl;
     cout<<Px_d2<<"  "<<Py_d2<<"  "<<Pz_d2<<"  "<<E_d2<<"  "<<endl;
     cout<<Px_g1<<"  "<<Py_g1<<"  "<<Pz_g1<<"  "<<E_g1<<"  "<<endl;
     cout<<Px_g2<<"  "<<Py_g2<<"  "<<Pz_g2<<"  "<<E_g2<<"  "<<endl;
     cout<<endl;
   }
   if(isTest && count == 10) break;
 }

 file->Write();
}
