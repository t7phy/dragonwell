#include <iostream>
#include "RootCommon.h"
#include "ReadInRoot/CMSAFB.h"

using namespace std;

int main(int argc, char** argv)
{
 TFile* writefile = new TFile("CMSData.root", "RECREATE");
 writefile->cd();

// int CMS_mass_bin = 12;
// double RangeCMSMass[13] = {40.0, 50.0, 60.0, 76.0, 86.0, 96.0, 106.0, 120.0, 133.0, 150.0, 171.0, 200.0, 320.0};
 int CMS_mass_bin = 7;
 double RangeCMSMass[8] = {60.0, 76.0, 86.0, 96.0, 106.0, 120.0, 133.0, 150.0};

 int CMS_ZPt_bin = 1;
 double RangeCMSZPt[2] = {0.0, 10000.0};

 int CMS_ZY_bin = 4;
 double RangeCMSZY[5] = {0.0, 1.0, 1.25, 1.5, 2.4};

 TH1D* AFB_y1 = new TH1D("AFB_y1", "AFB_y1", CMS_mass_bin, RangeCMSMass);
 TH1D* AFB_y2 = new TH1D("AFB_y2", "AFB_y2", CMS_mass_bin, RangeCMSMass);
 TH1D* AFB_y3 = new TH1D("AFB_y3", "AFB_y3", CMS_mass_bin, RangeCMSMass);
 TH1D* AFB_y4 = new TH1D("AFB_y4", "AFB_y4", CMS_mass_bin, RangeCMSMass);

 CMSAFB* Run_y1 = new CMSAFB();
 CMSAFB* Run_y2 = new CMSAFB();
 CMSAFB* Run_y3 = new CMSAFB();
 CMSAFB* Run_y4 = new CMSAFB();

 Run_y1->openFile("CMS_AFB_y1.csv");
 Run_y1->WriteIn(AFB_y1);
 Run_y2->openFile("CMS_AFB_y2.csv");
 Run_y2->WriteIn(AFB_y2);
 Run_y3->openFile("CMS_AFB_y3.csv");
 Run_y3->WriteIn(AFB_y3);
 Run_y4->openFile("CMS_AFB_y4.csv");
 Run_y4->WriteIn(AFB_y4);

 TH3D* AFB_3D = new TH3D("CMS_AFB_3D", "CMS_AFB_3D", CMS_mass_bin, RangeCMSMass, CMS_ZY_bin, RangeCMSZY, CMS_ZPt_bin, RangeCMSZPt);

 for(int ibinx = 1; ibinx <= AFB_3D->GetNbinsX(); ibinx++){
   AFB_3D->SetBinContent(ibinx, 1, 1, AFB_y1->GetBinContent(ibinx));
   AFB_3D->SetBinError(ibinx, 1, 1, AFB_y1->GetBinError(ibinx));
   AFB_3D->SetBinContent(ibinx, 2, 1, AFB_y2->GetBinContent(ibinx));
   AFB_3D->SetBinError(ibinx, 2, 1, AFB_y2->GetBinError(ibinx));
   AFB_3D->SetBinContent(ibinx, 3, 1, AFB_y3->GetBinContent(ibinx));
   AFB_3D->SetBinError(ibinx, 3, 1, AFB_y3->GetBinError(ibinx));
   AFB_3D->SetBinContent(ibinx, 4, 1, AFB_y4->GetBinContent(ibinx));
   AFB_3D->SetBinError(ibinx, 4, 1, AFB_y4->GetBinError(ibinx));
 }

 writefile->cd();
 writefile->Write();
 writefile->Close();

 return 1;
}
