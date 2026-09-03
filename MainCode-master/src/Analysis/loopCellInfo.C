#define loopCellInfo_cxx
#include <iostream>
#include "Analysis/loopCellInfo.h"

using namespace std;

loopCellInfo::loopCellInfo(TString RootType)
{
 this->RootType = RootType;

 Sta_TotalNumber = 0;

 isThread = false;
}

void loopCellInfo::InputHist(HistsCellInfo* &myhists)
{
 this->myhists = myhists;

}

void loopCellInfo::InputTree(TreeForCellInfo *CellInfoTree)
{
 this->CellInfoTree = CellInfoTree;
 this->RootNames = CellInfoTree->RootNames;

 this->FirstFile = CellInfoTree->FirstFile;
 this->EndFile = CellInfoTree->EndFile;

 this->OneFilePerJob = CellInfoTree->OneFilePerJob;

 for(int ifile = FirstFile; ifile < EndFile; ifile++){
   TotalEntries[ifile] = CellInfoTree->TotalEntries[ifile];
 }

}

void loopCellInfo::ReadTree(int ifile)
{
 int TotalCluster = 0;
 map<pair<int, int>, double> CellEnergyMap;

 map<pair<double, double>, double> CellMap;
 set<double> CellEta;
 set<double> CellPhi;

 map<pair<double, double>, double> CellMapXY;
 set<double> CellX;
 set<double> CellY;

 double deta, dphi, dx, dy;

 for(long iEvent = InitialEntry - 1; iEvent < Nentries; iEvent++){
   Sta_TotalNumber++;
   if(isTest) cout<<"Thread No."<<iThread<<": The No."<<Sta_TotalNumber<<" event."<<endl;

   if(Sta_TotalNumber % 1000000 == 0){ 
     if(isThread) cout<<"Thread No."<<iThread<<": "<<Sta_TotalNumber<<" events have finished."<<endl;
     if(!isThread) cout<<"Condor No."<<iThread<<": "<<Sta_TotalNumber<<" events have finished."<<endl;
   }
  
   CellInfoTree->GetEntry(ifile, iEvent);

   for(int iCluster = 0; iCluster < CellInfoTree->tc_cell_eta->size(); iCluster++){
     if(isTest) cout<<"Event: "<<Sta_TotalNumber<<" Cluster: "<<iCluster + 1<<":"<<endl;

     if(CellInfoTree->reco_pt->at(iCluster) > 20000){
       TotalCluster++;
       CellEnergyMap.clear();

       CellMap.clear();
       CellEta.clear();
       CellPhi.clear();

       CellMapXY.clear();
       CellX.clear();
       CellY.clear();

       myhists->ClusterSizeMu->at(iThread - 1)->Fill((CellInfoTree->tc_cell_eta->at(iCluster)).size(), CellInfoTree->mu, 1);

       if(CellInfoTree->mu > 0 && CellInfoTree->mu < 30) myhists->ClusterSizeLowMu->at(iThread - 1)->Fill((CellInfoTree->tc_cell_eta->at(iCluster)).size(), 1);
       if(CellInfoTree->mu > 30 && CellInfoTree->mu < 100) myhists->ClusterSizeHighMu->at(iThread - 1)->Fill((CellInfoTree->tc_cell_eta->at(iCluster)).size(), 1);

//       myhists->bookCellHist(TotalCluster, 20, CellInfoTree->reco_eta->at(iCluster) - 0.5, CellInfoTree->reco_eta->at(iCluster) + 0.5, 20, CellInfoTree->reco_phi->at(iCluster) - 0.3, CellInfoTree->reco_phi->at(iCluster) + 0.3);

       for(int iCell = 0; iCell < (CellInfoTree->tc_cell_eta->at(iCluster)).size(); iCell++){
         if(isTest) cout<<"Cell: "<<iCell + 1<<" eta: "<<(CellInfoTree->tc_cell_eta->at(iCluster)).at(iCell)<<" phi: "<<(CellInfoTree->tc_cell_phi->at(iCluster)).at(iCell)<<" deta: "<<(CellInfoTree->tc_cell_deta->at(iCluster)).at(iCell)<<" dphi: "<<(CellInfoTree->tc_cell_dphi->at(iCluster)).at(iCell)<<" layer: "<<(CellInfoTree->tc_cell_layer->at(iCluster)).at(iCell)<<" energy: "<<(CellInfoTree->tc_cell_energy->at(iCluster)).at(iCell)<<" x: "<<(CellInfoTree->tc_cell_x->at(iCluster)).at(iCell)<<" y: "<<(CellInfoTree->tc_cell_y->at(iCluster)).at(iCell)<<" z: "<<(CellInfoTree->tc_cell_z->at(iCluster)).at(iCell)<<" dx: "<<(CellInfoTree->tc_cell_dx->at(iCluster)).at(iCell)<<" dy: "<<(CellInfoTree->tc_cell_dy->at(iCluster)).at(iCell)<<" dz: "<<(CellInfoTree->tc_cell_dz->at(iCluster)).at(iCell)<<endl;

         if((CellInfoTree->tc_cell_layer->at(iCluster)).at(iCell) == 1) deta = (CellInfoTree->tc_cell_deta->at(iCluster)).at(iCell);
         if((CellInfoTree->tc_cell_layer->at(iCluster)).at(iCell) == 1) dphi = (CellInfoTree->tc_cell_dphi->at(iCluster)).at(iCell);
         if((CellInfoTree->tc_cell_layer->at(iCluster)).at(iCell) == 1) dx = (CellInfoTree->tc_cell_dx->at(iCluster)).at(iCell);
         if((CellInfoTree->tc_cell_layer->at(iCluster)).at(iCell) == 1) dy = (CellInfoTree->tc_cell_dy->at(iCluster)).at(iCell);

         if((CellInfoTree->tc_cell_layer->at(iCluster)).at(iCell) == 1) CellEta.insert((CellInfoTree->tc_cell_eta->at(iCluster)).at(iCell));
         if((CellInfoTree->tc_cell_layer->at(iCluster)).at(iCell) == 1) CellPhi.insert((CellInfoTree->tc_cell_phi->at(iCluster)).at(iCell));

         if((CellInfoTree->tc_cell_layer->at(iCluster)).at(iCell) == 1) CellX.insert((CellInfoTree->tc_cell_x->at(iCluster)).at(iCell));
         if((CellInfoTree->tc_cell_layer->at(iCluster)).at(iCell) == 1) CellY.insert((CellInfoTree->tc_cell_y->at(iCluster)).at(iCell));

         pair<double, double> EtaPhiPair;
         EtaPhiPair = make_pair((CellInfoTree->tc_cell_eta->at(iCluster)).at(iCell), (CellInfoTree->tc_cell_phi->at(iCluster)).at(iCell));
         if((CellInfoTree->tc_cell_layer->at(iCluster)).at(iCell) == 1) CellMap[EtaPhiPair] = (CellInfoTree->tc_cell_energy->at(iCluster)).at(iCell);

         pair<double, double> XYPair;
         XYPair = make_pair((CellInfoTree->tc_cell_x->at(iCluster)).at(iCell), (CellInfoTree->tc_cell_y->at(iCluster)).at(iCell));
         if((CellInfoTree->tc_cell_layer->at(iCluster)).at(iCell) == 1) CellMapXY[XYPair] = (CellInfoTree->tc_cell_energy->at(iCluster)).at(iCell);

       }
       myhists->bookCellHist(TotalCluster, CellEta, CellPhi);
       if(dx < 1e-10) myhists->FindCellBin(TotalCluster, CellEta, CellPhi, deta, dphi, CellMap);
       if(dx > 1e-10) myhists->FindCellBinXY(TotalCluster, CellX, CellY, dx, dy, CellMapXY);


//       myhists->FindCellBin(TotalCluster, CellMap, CellEnergyMap);
//       myhists->FillCellHist(TotalCluster, CellEnergyMap);

//       cout<<"Cluster size: "<<(CellInfoTree->tc_cell_eta->at(iCluster)).size()<<endl;
//       for(map<pair<double, double>, double>::iterator iter = CellMap.begin(); iter != CellMap.end(); iter++){
//         cout<<"eta: "<<(iter->first).first<<" phi: "<<(iter->first).second<<" energy: "<<(iter->second)<<endl;
//       }
//       cout<<endl;
     }
     if(isTest) cout<<endl;
   }

 }

}

void loopCellInfo::End(int RootNumber)
{
 cout<<"Thread No."<<this->iThread<<": **Running: Free Rootfile: "<<RootNumber + 1<<endl;

 if(!CellInfoTree->fChain[RootNumber])
  {
   cout<<"XXXXX**Runing: BIG ERROR!!! No File loadead!"<<endl;
   return;
  }
 delete CellInfoTree->fChain[RootNumber]->GetCurrentFile();
}

void loopCellInfo::Finish()
{
 cout<<"Thread No."<<this->iThread<<": **Total Event Number: "<<this->Sta_TotalNumber<<endl;

 if(EndFile == RootNames.size()) delete CellInfoTree;

}

loopCellInfo::~loopCellInfo()
{
}
