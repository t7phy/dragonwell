#include "HistsCellInfo.h"

using namespace std;

void HistsCellInfo::bookCellHist(int iCluster, int nbinx, double leftx, double rightx, int nbiny, double lefty, double righty)
{
 if(!isFillCellHist) return;

 hf->cd();

 if(CellHistMap[iCluster]){
   cout<<"ERROR: Please use another cluster index."<<endl;
   return;
 }

 CellHistMap[iCluster] = new TH2D((TString)"Cluster" + (int)iCluster, (TString)"Cluster" + (int)iCluster, nbinx, leftx, rightx, nbiny, lefty, righty);
}

void HistsCellInfo::bookCellHist(int iCluster, set<double> CellEta, set<double> CellPhi)
{
 if(!isFillCellHist) return;

 hf->cd();

 if(CellHistMap[iCluster]){
   cout<<"ERROR: Please use another cluster index."<<endl;
   return;
 }
 int nEtaBin = CellEta.size() + 2;
 int nPhiBin = CellPhi.size() + 2;
 double EtaRange[nEtaBin];
 double PhiRange[nPhiBin];

 set<double>::iterator etaIter = CellEta.begin();
 set<double>::iterator phiIter = CellPhi.begin();

 EtaRange[0] = (*etaIter) - 0.2;
 etaIter = CellEta.end();
 EtaRange[nEtaBin - 1] = *(--etaIter) + 0.2;

 PhiRange[0] = (*phiIter) - 0.1;
 phiIter = CellPhi.end();
 PhiRange[nPhiBin - 1] = *(--phiIter) + 0.1;

 etaIter = CellEta.begin();
 phiIter = CellPhi.begin();
 for(int i = 1; i < nEtaBin - 1; i++){
   EtaRange[i] = (*etaIter);
   PhiRange[i] = (*phiIter);
   etaIter++;
   phiIter++;
 }

// CellHistMap[iCluster] = new TH2D((TString)"Cluster" + (int)iCluster, (TString)"Cluster" + (int)iCluster, nEtaBin - 1, EtaRange, nPhiBin - 1, PhiRange);

 CellHistMap[iCluster] = new TH2D((TString)"Cluster" + (int)iCluster, (TString)"Cluster" + (int)iCluster, 20, -10, 10, 20, -10, 10);

}

void HistsCellInfo::FillCellHist(int iCluster, map<pair<int, int>, double> CellEnergyMap)
{
 if(!isFillCellHist) return;

 for(map<pair<int, int>, double>::iterator iter = CellEnergyMap.begin(); iter != CellEnergyMap.end(); iter++){

   CellHistMap[iCluster]->SetBinContent((iter->first).first, (iter->first).second, log10(fabs(iter->second)));

 }

}

void HistsCellInfo::FindCellBin(int iCluster, double keyx, double keyy, double Value, map<pair<int, int>, double> &CellEnergyMap)
{
 if(!isFillCellHist) return;

 int ibinx = CellHistMap[iCluster]->FindBin(keyx, keyy) % (CellHistMap[iCluster]->GetNbinsX() + 2);
 int ibiny = CellHistMap[iCluster]->FindBin(keyx, keyy) / (CellHistMap[iCluster]->GetNbinsX() + 2);

 pair<int, int> CellPosition;
 CellPosition = make_pair(ibinx, ibiny);

 if(!CellEnergyMap[CellPosition]){
   CellEnergyMap[CellPosition] = Value;
 }
 else{
   CellEnergyMap[CellPosition] = CellEnergyMap[CellPosition] + Value;
 }
}

void HistsCellInfo::FindCellBin(int iCluster, map<pair<double, double>, double> CellMap, map<pair<int, int>, double> &CellEnergyMap)
{
 if(!isFillCellHist) return;

 for(map<pair<double, double>, double>::iterator iter = CellMap.begin(); iter != CellMap.end(); iter++){

   int ibinx = CellHistMap[iCluster]->FindBin((iter->first).first, (iter->first).second) % (CellHistMap[iCluster]->GetNbinsX() + 2);
   int ibiny = CellHistMap[iCluster]->FindBin((iter->first).first, (iter->first).second) / (CellHistMap[iCluster]->GetNbinsX() + 2);

   pair<int, int> CellPosition;
   CellPosition = make_pair(ibinx, ibiny);

   if(!CellEnergyMap[CellPosition]){
     CellEnergyMap[CellPosition] = iter->second;
   }
   else{
     CellEnergyMap[CellPosition] = CellEnergyMap[CellPosition] + iter->second;
   }
 }

}

void HistsCellInfo::FindCellBin(int iCluster, set<double> CellEta, set<double> CellPhi, double deta, double dphi, map<pair<double, double>, double> CellMap)
{
 if(!isFillCellHist) return;

 set<double>::iterator CellEtaIter = CellEta.begin();
 set<double>::iterator CellPhiIter = CellPhi.begin();

 double FirstEta = *(CellEtaIter);
 double FirstPhi = *(CellPhiIter);

 CellEtaIter = CellEta.end();
 CellPhiIter = CellPhi.end();

 double EndEta = *(--CellEtaIter);
 double EndPhi = *(--CellPhiIter);

 int nEta = fabs(FirstEta - EndEta) / deta;
 int nPhi = fabs(FirstPhi - EndPhi) / dphi;

 CellEtaBinMap.clear();
 CellPhiBinMap.clear();

 int EtaIndex = - nEta / 2 - 1;
 for(CellEtaIter = CellEta.begin(); CellEtaIter != CellEta.end(); CellEtaIter++){
   CellEtaBinMap[*CellEtaIter] = EtaIndex;
   if(fabs(*(next(CellEtaIter)) - *(CellEtaIter)) > fabs(deta) / 10.0) EtaIndex++;
 }

 int PhiIndex = - nPhi / 2 - 1;
 for(CellPhiIter = CellPhi.begin(); CellPhiIter != CellPhi.end(); CellPhiIter++){
   CellPhiBinMap[*CellPhiIter] = PhiIndex;
   if(fabs(*(next(CellPhiIter)) - *(CellPhiIter)) > fabs(dphi) / 10.0) PhiIndex++;
 }

 for(map<pair<double, double>, double>::iterator iter = CellMap.begin(); iter != CellMap.end(); iter++){

//   cout<<"eta bin: "<<CellEtaBinMap[(iter->first).first]<<" phi bin: "<<CellPhiBinMap[(iter->first).second]<<" log10 energy: "<<log10(fabs(iter->second))<<endl;
   int ibinx = CellHistMap[iCluster]->FindBin(CellEtaBinMap[(iter->first).first], CellPhiBinMap[(iter->first).second]) % (CellHistMap[iCluster]->GetNbinsX() + 2);
   int ibiny = CellHistMap[iCluster]->FindBin(CellEtaBinMap[(iter->first).first], CellPhiBinMap[(iter->first).second]) / (CellHistMap[iCluster]->GetNbinsX() + 2);

   if(log10(fabs(iter->second)) < 0) continue;

   CellHistMap[iCluster]->SetBinContent(ibinx, ibiny, log10(fabs(iter->second)));

 }
 
/* for(map<double, int>::iterator iter = CellEtaBinMap.begin(); iter != CellEtaBinMap.end(); iter++){
   cout<<" eta: "<<iter->first<<" bin: "<<iter->second<<endl;
 }
 for(map<double, int>::iterator iter = CellPhiBinMap.begin(); iter != CellPhiBinMap.end(); iter++){
   cout<<" phi: "<<iter->first<<" bin: "<<iter->second<<endl;
 }
*/

}

void HistsCellInfo::FindCellBinXY(int iCluster, set<double> CellX, set<double> CellY, double dx, double dy, map<pair<double, double>, double> CellMapXY)
{
 if(!isFillCellHist) return;

 set<double>::iterator CellXIter = CellX.begin();
 set<double>::iterator CellYIter = CellY.begin();

 double FirstX = *(CellXIter);
 double FirstY = *(CellYIter);

 CellXIter = CellX.end();
 CellYIter = CellY.end();

 double EndX = *(--CellXIter);
 double EndY = *(--CellYIter);

 int nX = fabs(FirstX - EndX) / dx;
 int nY = fabs(FirstY - EndY) / dy;

 CellXBinMap.clear();
 CellYBinMap.clear();

 int XIndex = - nX / 2 - 1;
 for(CellXIter = CellX.begin(); CellXIter != CellX.end(); CellXIter++){
   CellXBinMap[*CellXIter] = XIndex;
   if(fabs(*(next(CellXIter)) - *(CellXIter)) > fabs(dx) / 10.0) XIndex++;
 }

 int YIndex = - nY / 2 - 1;
 for(CellYIter = CellY.begin(); CellYIter != CellY.end(); CellYIter++){
   CellYBinMap[*CellYIter] = YIndex;
   if(fabs(*(next(CellYIter)) - *(CellYIter)) > fabs(dy) / 10.0) YIndex++;
 }

 for(map<pair<double, double>, double>::iterator iter = CellMapXY.begin(); iter != CellMapXY.end(); iter++){

//   cout<<"x bin: "<<CellXBinMap[(iter->first).first]<<" y bin: "<<CellYBinMap[(iter->first).second]<<" log10 energy: "<<log10(fabs(iter->second))<<endl;
   int ibinx = CellHistMap[iCluster]->FindBin(CellXBinMap[(iter->first).first], CellYBinMap[(iter->first).second]) % (CellHistMap[iCluster]->GetNbinsX() + 2);
   int ibiny = CellHistMap[iCluster]->FindBin(CellXBinMap[(iter->first).first], CellYBinMap[(iter->first).second]) / (CellHistMap[iCluster]->GetNbinsX() + 2);

   if(log10(fabs(iter->second)) < 0) continue;

   CellHistMap[iCluster]->SetBinContent(ibinx, ibiny, log10(fabs(iter->second)));

 }
 
/* for(map<double, int>::iterator iter = CellXBinMap.begin(); iter != CellXBinMap.end(); iter++){
   cout<<" x: "<<iter->first<<" bin: "<<iter->second<<endl;
 }
 for(map<double, int>::iterator iter = CellYBinMap.begin(); iter != CellYBinMap.end(); iter++){
   cout<<" y: "<<iter->first<<" bin: "<<iter->second<<endl;
 }
*/
}

void HistsCellInfo::bookHists(int TotalThread)
{
 double rangeZPt[24] = {0,2.5,5,8,11.4,14.9,18.5,22,25.5,29,32.6,36.4,40.4,44.9,50.2,56.4,63.9,73.4,85.4,105,132,173,253,600};

 this->TotalThread = TotalThread;

 Book2DHist(ClusterSizeMu, "ClusterSize_vs_mu", "ClusterSize_vs_mu", 10, 0, 100, 10, 0, 100);

 BookHist(ClusterSizeLowMu, "ClusterSizeLowMu", "ClusterSizeLowMu", 10, 0, 100);
 BookHist(ClusterSizeMediumMu, "ClusterSizeMediumMu", "ClusterSizeMediumMu", 10, 0, 100);
 BookHist(ClusterSizeHighMu, "ClusterSizeHighMu", "ClusterSizeHighMu", 10, 0, 100);

}

void HistsCellInfo::InitialSysName()
{

}
