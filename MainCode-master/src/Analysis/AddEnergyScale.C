#ifndef AddEnergyScale_cxx
#define AddEnergyScale_cxx

#include "Analysis/loopResBos.h"

using namespace std;

void loopResBos::ConfigEnergyScale(vector<double> EnergyScaleList)
{
 isAddEnergyScale = true;

 this->EnergyScaleList = EnergyScaleList;
}

void loopResBos::AddEnergyScale(TLorentzVector Electron_reco, TLorentzVector Positron_reco)
{
 for(int i = 0; i < EnergyScaleList.size(); i++){
   int ieta1=0;
   int ieta2=0;

   Electron_reco = Electron_reco * EnergyScaleList.at(i);
   Positron_reco = Positron_reco * EnergyScaleList.at(i);

   TLorentzVector ZBoson_reco = Electron_reco + Positron_reco;
   double ZRapidity=ZBoson_reco.Rapidity();

   double cos_theta = calculate_theta(ZBoson_reco, Electron_reco, Positron_reco) * ZRapidity / fabs(ZRapidity);

   if(Electron_reco.Pt()<25 || Positron_reco.Pt()<25) continue;
   if(fabs(Electron_reco.Eta()) > 2.5 && fabs(Electron_reco.Eta()) < 4.9) ieta1=1;//1F
   if(fabs(Electron_reco.Eta()) < 2.5) ieta1=2;                              //1C
   if(fabs(Positron_reco.Eta()) > 2.5 && fabs(Positron_reco.Eta()) < 4.9) ieta2=3;//2F
   if(fabs(Positron_reco.Eta()) < 2.5) ieta2=4;                              //2C

//CC
   if(ieta1 * ieta2 == 8){
     if(cos_theta > 0) myhists->FZmass_CC_Cov->at(iThread - 1)->Fill(ZBoson_reco.M(), Weight, i);
     if(cos_theta < 0) myhists->BZmass_CC_Cov->at(iThread - 1)->Fill(ZBoson_reco.M(), Weight, i);
   }
//CF
   if(ieta1 * ieta2 == 4 || ieta1 * ieta2 == 6){
     if(cos_theta > 0) myhists->FZmass_CF_Cov->at(iThread - 1)->Fill(ZBoson_reco.M(), Weight, i);
     if(cos_theta < 0) myhists->BZmass_CF_Cov->at(iThread - 1)->Fill(ZBoson_reco.M(), Weight, i);
   }

 }
}

#endif
