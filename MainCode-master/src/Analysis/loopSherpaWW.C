#define loopSherpaWW_cxx
#include <iostream>
#include "Analysis/loopSherpaWW.h"

using namespace std;

loopSherpaWW::loopSherpaWW(TString RootType)
{
 this->RootType = RootType;

 Sta_TotalNumber = 0;

 isThread = false;
}

void loopSherpaWW::InputHist(HistsSherpaWW* &myhists)
{
 this->myhists = myhists;

}

void loopSherpaWW::InputTree(TreeForSherpaWW *SherpaWWTree)
{
 this->SherpaWWTree = SherpaWWTree;
 this->RootNames = SherpaWWTree->RootNames;

 this->FirstFile = SherpaWWTree->FirstFile;
 this->EndFile = SherpaWWTree->EndFile;

 this->OneFilePerJob = SherpaWWTree->OneFilePerJob;

 for(int ifile = FirstFile; ifile < EndFile; ifile++){
   TotalEntries[ifile] = SherpaWWTree->TotalEntries[ifile];
 }

}

void loopSherpaWW::ReadTree(int ifile)
{
 for(long iEvent = InitialEntry - 1; iEvent < Nentries; iEvent++){
   Sta_TotalNumber++;
   if(isTest) cout<<"Thread No."<<iThread<<": The No."<<Sta_TotalNumber<<" event."<<endl;

   if(Sta_TotalNumber % 1000000 == 0){
     if(isThread) cout<<"Thread No."<<iThread<<": "<<Sta_TotalNumber<<" events have finished."<<endl;
     if(!isThread) cout<<"Condor No."<<iThread<<": "<<Sta_TotalNumber<<" events have finished."<<endl;
   }

   SherpaWWTree->GetEntry(ifile, iEvent);

   Electron.SetPxPyPzE(SherpaWWTree->ElectronPx, SherpaWWTree->ElectronPy, SherpaWWTree->ElectronPz, SherpaWWTree->ElectronE);
   eNeutrino.SetPxPyPzE(SherpaWWTree->eNeutrinoPx, SherpaWWTree->eNeutrinoPy, SherpaWWTree->eNeutrinoPz, SherpaWWTree->eNeutrinoE);
   Muon.SetPxPyPzE(SherpaWWTree->MuonPx, SherpaWWTree->MuonPy, SherpaWWTree->MuonPz, SherpaWWTree->MuonE);
   mNeutrino.SetPxPyPzE(SherpaWWTree->mNeutrinoPx, SherpaWWTree->mNeutrinoPy, SherpaWWTree->mNeutrinoPz, SherpaWWTree->mNeutrinoE);

   DiNeutrino = eNeutrino + mNeutrino;

   if(SherpaWWTree->ElectronFlavor > 0 && SherpaWWTree->MuonFlavor < 0){
     WPlus = Electron + eNeutrino;
     WMinus = Muon + mNeutrino;
     PositiveLepton = Electron;
     NegativeLepton = Muon;
   }
   if(SherpaWWTree->ElectronFlavor < 0 && SherpaWWTree->MuonFlavor > 0){ 
     WPlus = Muon + mNeutrino;
     WMinus = Electron + eNeutrino;
     PositiveLepton = Muon;
     NegativeLepton = Electron;
   }
   WW = WPlus + WMinus;

   PDFWeights = SherpaWWTree->Weights;
   PDFReweightFactor = PDFWeights->at(PDFErrorSet + 4);

   if(isTest){
     cout<<PDFErrorSet<<endl;
     cout<<"Weights size: "<<PDFWeights->size()<<endl;
     cout<<"PDF reweight factor = "<<PDFReweightFactor<<endl;
     cout<<endl;
   }

   double Weight = 1.0 * PDFReweightFactor;

   bool isZU = false;
   bool isZD = false;
   if(fabs(SherpaWWTree->quark_flavour[0]) == 2 || fabs(SherpaWWTree->quark_flavour[0]) == 4 || fabs(SherpaWWTree->quark_flavour[0]) == 6) isZU = true;
   if(fabs(SherpaWWTree->quark_flavour[0]) == 1 || fabs(SherpaWWTree->quark_flavour[0]) == 3 || fabs(SherpaWWTree->quark_flavour[0]) == 5) isZD = true;

   bool isUUB = false;
   bool isDDB = false;
   bool isSSB = false;
   bool isCCB = false;
   bool isBBB = false;
   bool isGG = false;
   isUUB = (fabs(SherpaWWTree->quark_flavour[0]) == 2);//uu
   isDDB = (fabs(SherpaWWTree->quark_flavour[0]) == 1);//dd
   isSSB = (fabs(SherpaWWTree->quark_flavour[0]) == 3);//ss
   isCCB = (fabs(SherpaWWTree->quark_flavour[0]) == 4);//cc
   isBBB = (fabs(SherpaWWTree->quark_flavour[0]) == 5);//bb
   isGG = (fabs(SherpaWWTree->quark_flavour[0]) == 3 || fabs(SherpaWWTree->quark_flavour[0]) == 4 || fabs(SherpaWWTree->quark_flavour[0]) == 5 || fabs(SherpaWWTree->quark_flavour[0]) == 6);//gg

   bool isWrongW = fabs(WPlus.Rapidity()) < fabs(WMinus.Rapidity());
   bool isRightW = fabs(WPlus.Rapidity()) > fabs(WMinus.Rapidity());

   bool isWrong = fabs(PositiveLepton.Eta()) < fabs(NegativeLepton.Eta());
   bool isRight = fabs(PositiveLepton.Eta()) > fabs(NegativeLepton.Eta());

   bool isWrongWQuark = false;
   bool isRightWQuark = false;

   bool isWrongQuark = false;
   bool isRightQuark = false;

   if(isZU) isWrongWQuark = fabs(WPlus.Rapidity()) < fabs(WMinus.Rapidity());
   if(isZD) isWrongWQuark = fabs(WPlus.Rapidity()) > fabs(WMinus.Rapidity());

   if(isZU) isRightWQuark = fabs(WPlus.Rapidity()) > fabs(WMinus.Rapidity());
   if(isZD) isRightWQuark = fabs(WPlus.Rapidity()) < fabs(WMinus.Rapidity());

   isWrongWQuark = isWrongW;
   isRightWQuark = isRightW;

   if(isZU) isWrongQuark = fabs(PositiveLepton.Eta()) < fabs(NegativeLepton.Eta());
   if(isZD) isWrongQuark = fabs(PositiveLepton.Eta()) > fabs(NegativeLepton.Eta());

   if(isZU) isRightQuark = fabs(PositiveLepton.Eta()) > fabs(NegativeLepton.Eta());
   if(isZD) isRightQuark = fabs(PositiveLepton.Eta()) < fabs(NegativeLepton.Eta());

   isWrongQuark = isWrong;
   isRightQuark = isRight;

   double WYDiff = fabs(fabs(WPlus.Rapidity()) - fabs(WMinus.Rapidity()));
   double EtaDiff = fabs(fabs(PositiveLepton.Eta()) - fabs(NegativeLepton.Eta()));

   double CosThetaPlusDiff = cos(WPlus.Vect().Angle(PositiveLepton.Vect()));
   double CosThetaMinusDiff = cos(WMinus.Vect().Angle(NegativeLepton.Vect()));

   //if(PositiveLepton.Pt() < 25 || NegativeLepton.Pt() < 25) continue;
   //if(DiNeutrino.Pt() < 25) continue;
   //if(WW.M() < 160 || WW.M() > 400) continue;

   myhists->Wrong_uu->at(iThread - 1)->Fill(fabs(EtaDiff), Weight * isWrongQuark * isUUB);
   myhists->Right_uu->at(iThread - 1)->Fill(fabs(EtaDiff), Weight * isRightQuark * isUUB);
   myhists->Total_uu->at(iThread - 1)->Fill(fabs(EtaDiff), Weight * isUUB);

   myhists->Wrong_dd->at(iThread - 1)->Fill(fabs(EtaDiff), Weight * isWrongQuark * isDDB);
   myhists->Right_dd->at(iThread - 1)->Fill(fabs(EtaDiff), Weight * isRightQuark * isDDB);
   myhists->Total_dd->at(iThread - 1)->Fill(fabs(EtaDiff), Weight * isDDB);

   myhists->Wrong_ss->at(iThread - 1)->Fill(fabs(EtaDiff), Weight * isWrongQuark * isSSB);
   myhists->Right_ss->at(iThread - 1)->Fill(fabs(EtaDiff), Weight * isRightQuark * isSSB);
   myhists->Total_ss->at(iThread - 1)->Fill(fabs(EtaDiff), Weight * isSSB);

   myhists->Wrong_cc->at(iThread - 1)->Fill(fabs(EtaDiff), Weight * isWrongQuark * isCCB);
   myhists->Right_cc->at(iThread - 1)->Fill(fabs(EtaDiff), Weight * isRightQuark * isCCB);
   myhists->Total_cc->at(iThread - 1)->Fill(fabs(EtaDiff), Weight * isCCB);

   myhists->Wrong_bb->at(iThread - 1)->Fill(fabs(EtaDiff), Weight * isWrongQuark * isBBB);
   myhists->Right_bb->at(iThread - 1)->Fill(fabs(EtaDiff), Weight * isRightQuark * isBBB);
   myhists->Total_bb->at(iThread - 1)->Fill(fabs(EtaDiff), Weight * isBBB);

   myhists->Wrong_AllFlavor->at(iThread - 1)->Fill(fabs(EtaDiff), Weight * isWrong);
   myhists->Right_AllFlavor->at(iThread - 1)->Fill(fabs(EtaDiff), Weight * isRight);
   myhists->Total_AllFlavor->at(iThread - 1)->Fill(fabs(EtaDiff), Weight);

   myhists->WrongW_uu->at(iThread - 1)->Fill(fabs(WYDiff), Weight * isWrongWQuark * isUUB);
   myhists->RightW_uu->at(iThread - 1)->Fill(fabs(WYDiff), Weight * isRightWQuark * isUUB);
   myhists->TotalW_uu->at(iThread - 1)->Fill(fabs(WYDiff), Weight * isUUB);

   myhists->WrongW_dd->at(iThread - 1)->Fill(fabs(WYDiff), Weight * isWrongWQuark * isDDB);
   myhists->RightW_dd->at(iThread - 1)->Fill(fabs(WYDiff), Weight * isRightWQuark * isDDB);
   myhists->TotalW_dd->at(iThread - 1)->Fill(fabs(WYDiff), Weight * isDDB);

   myhists->WrongW_ss->at(iThread - 1)->Fill(fabs(WYDiff), Weight * isWrongWQuark * isSSB);
   myhists->RightW_ss->at(iThread - 1)->Fill(fabs(WYDiff), Weight * isRightWQuark * isSSB);
   myhists->TotalW_ss->at(iThread - 1)->Fill(fabs(WYDiff), Weight * isSSB);

   myhists->WrongW_cc->at(iThread - 1)->Fill(fabs(WYDiff), Weight * isWrongWQuark * isCCB);
   myhists->RightW_cc->at(iThread - 1)->Fill(fabs(WYDiff), Weight * isRightWQuark * isCCB);
   myhists->TotalW_cc->at(iThread - 1)->Fill(fabs(WYDiff), Weight * isCCB);

   myhists->WrongW_bb->at(iThread - 1)->Fill(fabs(WYDiff), Weight * isWrongWQuark * isBBB);
   myhists->RightW_bb->at(iThread - 1)->Fill(fabs(WYDiff), Weight * isRightWQuark * isBBB);
   myhists->TotalW_bb->at(iThread - 1)->Fill(fabs(WYDiff), Weight * isBBB);

   myhists->WrongW_AllFlavor->at(iThread - 1)->Fill(fabs(WYDiff), Weight * isWrongW);
   myhists->RightW_AllFlavor->at(iThread - 1)->Fill(fabs(WYDiff), Weight * isRightW);
   myhists->TotalW_AllFlavor->at(iThread - 1)->Fill(fabs(WYDiff), Weight);

   myhists->LeptonEta->at(iThread - 1)->Fill(NegativeLepton.Eta(), Weight);
   myhists->AntiLeptonEta->at(iThread - 1)->Fill(PositiveLepton.Eta(), Weight);

   myhists->WPlusRapidity->at(iThread - 1)->Fill(WPlus.Rapidity(), Weight);
   myhists->WMinusRapidity->at(iThread - 1)->Fill(WMinus.Rapidity(), Weight);

   myhists->WWMass->at(iThread - 1)->Fill(WW.M(), Weight);
   myhists->WWMass_uu->at(iThread - 1)->Fill(WW.M(), Weight * isUUB);
   myhists->WWMass_dd->at(iThread - 1)->Fill(WW.M(), Weight * isDDB);
   myhists->EtaDiff_uu->at(iThread - 1)->Fill(fabs(EtaDiff), Weight * isUUB);
   myhists->EtaDiff_dd->at(iThread - 1)->Fill(fabs(EtaDiff), Weight * isDDB);
   myhists->CosThetaPlusDiff->at(iThread - 1)->Fill(CosThetaPlusDiff, Weight);
   myhists->CosThetaMinusDiff->at(iThread - 1)->Fill(CosThetaMinusDiff, Weight);
 }

}

void loopSherpaWW::End(int RootNumber)
{
 cout<<"Thread No."<<this->iThread<<": **Running: Free Rootfile: "<<RootNumber + 1<<endl;

 if(!SherpaWWTree->fChain[RootNumber])
  {
   cout<<"XXXXX**Runing: BIG ERROR!!! No File loadead!"<<endl;
   return;
  }
 delete SherpaWWTree->fChain[RootNumber]->GetCurrentFile();
}

void loopSherpaWW::Finish()
{
 cout<<"Thread No."<<this->iThread<<": **Total Event Number: "<<this->Sta_TotalNumber<<endl;

 if(EndFile == RootNames.size()) delete SherpaWWTree;

}

loopSherpaWW::~loopSherpaWW()
{
}
