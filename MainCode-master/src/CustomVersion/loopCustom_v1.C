#define loopCustom_v1_cxx
#include <iostream>
#include "CustomVersion/loopCustom_v1.h"

using namespace std;

loopCustom_v1::loopCustom_v1(TString RootType)
{
 this->RootType = RootType;

 Sta_TotalNumber = 0;

 isThread = false;
}

void loopCustom_v1::InputHist(HistsCustom_v1* &myhists)
{
 this->myhists = myhists;

}

void loopCustom_v1::InputTree(TreeForCustom_v1 *Custom_v1Tree)
{
 this->Custom_v1Tree = Custom_v1Tree;
 this->RootNames = Custom_v1Tree->RootNames;

 this->FirstFile = Custom_v1Tree->FirstFile;
 this->EndFile = Custom_v1Tree->EndFile;

 this->OneFilePerJob = Custom_v1Tree->OneFilePerJob;

 for(int ifile = FirstFile; ifile < EndFile; ifile++){
   TotalEntries[ifile] = Custom_v1Tree->TotalEntries[ifile];
 }

}

void loopCustom_v1::ReadTree(int ifile)
{
 for(long iEvent = InitialEntry - 1; iEvent < Nentries; iEvent++){
   Sta_TotalNumber++;
   if(isTest) cout<<"Thread No."<<iThread<<": The No."<<Sta_TotalNumber<<" event."<<endl;

   if(Sta_TotalNumber % 1000000 == 0){ 
     if(isThread) cout<<"Thread No."<<iThread<<": "<<Sta_TotalNumber<<" events have finished."<<endl;
     if(!isThread) cout<<"Condor No."<<iThread<<": "<<Sta_TotalNumber<<" events have finished."<<endl;
   }
  
   Custom_v1Tree->GetEntry(ifile, iEvent);

   int ieta1=0;
   int ieta2=0;

   Electron.SetPxPyPzE(Custom_v1Tree->ElectronPx, Custom_v1Tree->ElectronPy, Custom_v1Tree->ElectronPz, Custom_v1Tree->ElectronE);
   Positron.SetPxPyPzE(Custom_v1Tree->PositronPx, Custom_v1Tree->PositronPy, Custom_v1Tree->PositronPz, Custom_v1Tree->PositronE);

   ZBoson = Electron + Positron;

   if(isPDFReweight) PDFReweightFactor = myPDFReweight->GetPDFReweightFactor(Custom_v1Tree->quark_flavour[0], Custom_v1Tree->quark_flavour[1], Custom_v1Tree->QuarkE[0] / 6500, Custom_v1Tree->QuarkE[1] / 6500, ZBoson.M());

   if(isTest){
     cout<<Custom_v1Tree->ZPx<<" "<<Custom_v1Tree->ZPy<<" "<<Custom_v1Tree->ZPz<<" "<<Custom_v1Tree->ZE<<endl;
     cout<<Custom_v1Tree->PositronPx<<" "<<Custom_v1Tree->PositronPy<<" "<<Custom_v1Tree->PositronPz<<" "<<Custom_v1Tree->PositronE<<endl;
     cout<<Custom_v1Tree->ElectronPx<<" "<<Custom_v1Tree->ElectronPy<<" "<<Custom_v1Tree->ElectronPz<<" "<<Custom_v1Tree->ElectronE<<endl;
     cout<<"PDF reweight factor = "<<PDFReweightFactor<<endl;
     cout<<endl;
   }

//   if(isTest) cout<<"ZPt = "<<ZBoson.Pt()<<" ZY = "<<ZBoson.Rapidity()<<" ZMass = "<<ZBoson.M()<<endl;

   double ZRapidity=ZBoson.Rapidity();

   double Weight = 1.0 * PDFReweightFactor;

   cos_theta = calculate_theta(ZBoson, Electron, Positron) * ZRapidity / fabs(ZRapidity);
   phi = calculate_phi(Electron, Positron, 13000.0) * ZRapidity / fabs(ZRapidity);
   phi_eta = calculate_phi_eta(Electron, Positron);

   if(cos_theta > 1) cos_theta = 1.0;
   if(cos_theta < -1) cos_theta = -1.0;

   if(Electron.Pt()<25 || Positron.Pt()<25) continue;
   if(fabs(Electron.Eta()) > 2.5 && fabs(Electron.Eta()) < 4.9) ieta1=1;//1F
   if(fabs(Electron.Eta()) < 2.5) ieta1=2;                              //1C
   if(fabs(Positron.Eta()) > 2.5 && fabs(Positron.Eta()) < 4.9) ieta2=3;//2F
   if(fabs(Positron.Eta()) < 2.5) ieta2=4;                              //2C

 }

}

void loopCustom_v1::End(int RootNumber)
{
 cout<<"Thread No."<<this->iThread<<": **Running: Free Rootfile: "<<RootNumber + 1<<endl;

 if(!Custom_v1Tree->fChain[RootNumber])
  {
   cout<<"XXXXX**Runing: BIG ERROR!!! No File loadead!"<<endl;
   return;
  }
 delete Custom_v1Tree->fChain[RootNumber]->GetCurrentFile();
}

void loopCustom_v1::Finish()
{
 cout<<"Thread No."<<this->iThread<<": **Total Event Number: "<<this->Sta_TotalNumber<<endl;

 if(EndFile == RootNames.size()) delete Custom_v1Tree;

}

loopCustom_v1::~loopCustom_v1()
{
}
