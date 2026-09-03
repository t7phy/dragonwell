#include "SpecialHist/AngularFunction.h"

using namespace std;

AngularFunction::AngularFunction(const char* myAngular, int iThread)
{
 this->myAngular = myAngular;
 this->iThread = iThread;

 if((TString)myAngular == "A0") {k = 20.0 / 3.0; b = 2.0 / 3.0;}
 if((TString)myAngular == "A1") {k = 5.0;      b = 0;  }
 if((TString)myAngular == "A2") {k = 20.0;     b = 0;  }
 if((TString)myAngular == "A02") {k = 1.0;     b = 0;  }
 if((TString)myAngular == "A3") {k = 4.0;      b = 0;  }
 if((TString)myAngular == "A4") {k = 4.0;      b = 0;  }
 if((TString)myAngular == "L0") {k = 5.0 / 7.0;      b = 0;  }

 iflag = 0;

 TRandom3 myR(0);
 x = myR.Integer(100000);

 isFill = false;
}

AngularFunction::~AngularFunction()
{
}

void AngularFunction::SetHist(const char* histName, int NbinsX, double xmin, double xmax)
{
 iflag = 1;

 this->NbinsX = NbinsX;
 this->histName = histName;
 this->AngularHist1D = new TH1D(histName, histName, NbinsX, xmin, xmax);
 this->VariableHist1D = new TH1D("h1_" + (TString)histName, "h1_" + (TString)histName, NbinsX, xmin, xmax);

 TString Name = "";

 for(int i = 1; i < NbinsX + 1; i++){
   Name = (TString)histName + (TString)"_Angular_" + (int)i + (TString)"bin";
   if(iThread != 0) Name = (TString)Name + (TString)"_" + (int)iThread;
   h1[i] = new TH1D(Name, Name, 1, -1000000.0, 1000000.0);
   h1[i]->Sumw2();
   hist_1d.push_back(h1[i]);
 }

}

void AngularFunction::SetHist(const char* histName, int NbinsX, double* xbins)
{
 iflag = 1;

 this->NbinsX = NbinsX;
 this->histName = histName;
 this->AngularHist1D = new TH1D(histName, histName, NbinsX, xbins);
 this->VariableHist1D = new TH1D("h1_" + (TString)histName, "h1_" + (TString)histName, NbinsX, xbins);

 TString Name = "";

 for(int i = 1; i < NbinsX + 1; i++){
   Name = (TString)histName + (TString)"_Angular_" + (int)i + (TString)"bin";
   if(iThread != 0) Name = (TString)Name + (TString)"_" + (int)iThread;
   h1[i] = new TH1D(Name, Name, 1, -1000000.0, 1000000.0);
   h1[i]->Sumw2();
   hist_1d.push_back(h1[i]);
 }

}

void AngularFunction::SetHist(const char* histName, int NbinsX, double* xbins, int NbinsY, double* ybins)
{
 iflag = 2;

 this->NbinsX = NbinsX;
 this->NbinsY = NbinsY;
 this->histName = histName;
 this->AngularHist2D = new TH2D(histName, histName, NbinsX, xbins, NbinsY, ybins);
 this->VariableHist2D = new TH2D("h2_" + (TString)histName, "h2_" + (TString)histName, NbinsX, xbins, NbinsY, ybins);

 TString Name = "";

 for(int i = 1; i < NbinsX + 1; i++){
   for(int j = 1; j < NbinsY + 1; j++){
     Name = (TString)histName + (TString)"_Angular_" + (int)i + (TString)"xbin_" + (int)j + (TString)"ybin";
     if(iThread != 0) Name = (TString)Name + (TString)"_" + (int)iThread;
     h2[i][j] = new TH1D(Name, Name, 1, -1000000.0, 1000000.0);
     h2[i][j]->Sumw2();
     hist_1d.push_back(h2[i][j]);
   }
 }

}

void AngularFunction::SetHist(const char* histName, int NbinsX, double* xbins, int NbinsY, double* ybins, int NbinsZ, double* zbins)
{
 iflag = 3;

 this->NbinsX = NbinsX;
 this->NbinsY = NbinsY;
 this->NbinsZ = NbinsZ;
 this->histName = histName;
 this->AngularHist3D = new TH3D(histName, histName, NbinsX, xbins, NbinsY, ybins, NbinsZ, zbins);
 this->VariableHist3D = new TH3D("h3_" + (TString)histName, "h3_" + (TString)histName, NbinsX, xbins, NbinsY, ybins, NbinsZ, zbins);

 TString Name = "";

 for(int i = 1; i < NbinsX + 1; i++){
   for(int j = 1; j < NbinsY + 1; j++){
     for(int z = 1; z < NbinsZ + 1; z++){
       Name = (TString)histName + (TString)"_Angular_" + (int)i + (TString)"xbin_" + (int)j + (TString)"ybin_" + (int)z + (TString)"zbin";
       if(iThread != 0) Name = (TString)Name + (TString)"_" + (int)iThread;
       h3[i][j][z] = new TH1D(Name, Name, 1, -1000000, 1000000);
       h3[i][j][z]->Sumw2();
       hist_1d.push_back(h3[i][j][z]);
     }
   }
 }

}

void AngularFunction::Fill(double myVariable, double weight)
{
 isFill = true;

 double sin_theta = sqrt(1.0 - cos_theta * cos_theta);

 this->weight = weight;
 int bin = VariableHist1D->Fill(myVariable, weight);
 if(bin > 0){
   if(myAngular == "A0") {h1[bin]->Fill((1.0 - 3.0 * cos_theta * cos_theta) / 2.0, weight);}
   if(myAngular == "A1") {h1[bin]->Fill(2.0 * sin_theta * cos_theta * cos(phi), weight);}
   if(myAngular == "A2") {h1[bin]->Fill((sin_theta * sin_theta * cos(2.0 * phi)) / 2.0, weight);}
   if(myAngular == "A02") {h1[bin]->Fill((20.0 / 3.0) * ((1.0 - 3.0 * cos_theta * cos_theta) / 2.0) + 2.0 / 3.0 - 20.0 * (sin_theta * sin_theta * cos(2.0 * phi)) / 2.0, weight);}
   if(myAngular == "A3") {h1[bin]->Fill(sin_theta * cos(phi), weight);}
   if(myAngular == "A4") {h1[bin]->Fill(cos_theta, weight);}
   if(myAngular == "L0") {h1[bin]->Fill(1.0 + cos_theta * cos_theta, weight);}
 }
}

void AngularFunction::Fill(double myVariable1, double myVariable2, double weight)
{
 isFill = true;

 double sin_theta = sqrt(1.0 - cos_theta * cos_theta);

 this->weight = weight;
 int bin = VariableHist2D->Fill(myVariable1, myVariable2, weight);
 if(bin > 0){
   if(myAngular == "A0") {h2[bin % (NbinsX + 2)][bin / (NbinsX + 2)]->Fill((1.0 - 3.0 * cos_theta * cos_theta) / 2.0, weight);}
   if(myAngular == "A1") {h2[bin % (NbinsX + 2)][bin / (NbinsX + 2)]->Fill(2.0 * sin_theta * cos_theta * cos(phi), weight);}
   if(myAngular == "A2") {h2[bin % (NbinsX + 2)][bin / (NbinsX + 2)]->Fill((sin_theta * sin_theta * cos(2.0 * phi)) / 2.0, weight);}
   if(myAngular == "A02") {h2[bin % (NbinsX + 2)][bin / (NbinsX + 2)]->Fill((20.0 / 3.0) * ((1.0 - 3.0 * cos_theta * cos_theta) / 2.0) + 2.0 / 3.0 - 20.0 * (sin_theta * sin_theta * cos(2.0 * phi)) / 2.0, weight);}
   if(myAngular == "A3") {h2[bin % (NbinsX + 2)][bin / (NbinsX + 2)]->Fill(sin_theta * cos(phi), weight);}
   if(myAngular == "A4") {h2[bin % (NbinsX + 2)][bin / (NbinsX + 2)]->Fill(cos_theta, weight);}
   if(myAngular == "L0") {h2[bin % (NbinsX + 2)][bin / (NbinsX + 2)]->Fill(1.0 + cos_theta * cos_theta, weight);}
 }

}

void AngularFunction::Fill(double myVariable1, double myVariable2, double myVariable3, double weight)
{
 isFill = true;

 double sin_theta = sqrt(1.0 - cos_theta * cos_theta);

 this->weight = weight;
 int bin = VariableHist3D->Fill(myVariable1, myVariable2, myVariable3, weight);
 if(bin > 0){
   if(myAngular == "A0") {h3[bin % (NbinsX + 2)][(bin / (NbinsX + 2)) % (NbinsY + 2)][(bin / (NbinsX + 2)) / (NbinsY + 2)]->Fill((1.0 - 3.0 * cos_theta * cos_theta) / 2.0, weight);}
   if(myAngular == "A1") {h3[bin % (NbinsX + 2)][(bin / (NbinsX + 2)) % (NbinsY + 2)][(bin / (NbinsX + 2)) / (NbinsY + 2)]->Fill(2.0 * sin_theta * cos_theta * cos(phi), weight);}
   if(myAngular == "A2") {h3[bin % (NbinsX + 2)][(bin / (NbinsX + 2)) % (NbinsY + 2)][(bin / (NbinsX + 2)) / (NbinsY + 2)]->Fill((sin_theta * sin_theta * cos(2.0 * phi)) / 2.0, weight);}
   if(myAngular == "A02") {h3[bin % (NbinsX + 2)][(bin / (NbinsX + 2)) % (NbinsY + 2)][(bin / (NbinsX + 2)) / (NbinsY + 2)]->Fill((20.0 / 3.0) * ((1.0 - 3.0 * cos_theta * cos_theta) / 2.0) + 2.0 / 3.0 - 20.0 * (sin_theta * sin_theta * cos(2.0 * phi)) / 2.0, weight);}
   if(myAngular == "A3") {h3[bin % (NbinsX + 2)][(bin / (NbinsX + 2)) % (NbinsY + 2)][(bin / (NbinsX + 2)) / (NbinsY + 2)]->Fill(sin_theta * cos(phi), weight);}
   if(myAngular == "A4") {h3[bin % (NbinsX + 2)][(bin / (NbinsX + 2)) % (NbinsY + 2)][(bin / (NbinsX + 2)) / (NbinsY + 2)]->Fill(cos_theta, weight);}
   if(myAngular == "L0") {h3[bin % (NbinsX + 2)][(bin / (NbinsX + 2)) % (NbinsY + 2)][(bin / (NbinsX + 2)) / (NbinsY + 2)]->Fill(1.0 + cos_theta * cos_theta, weight);}
 }

}

void AngularFunction::Initial(double cos_theta, double phi)
{
 this->cos_theta = cos_theta;
 this->phi = phi;
}

void AngularFunction::GetAngular()
{
 if(!isFill){
   if(iflag == 1){
     for(int i = 1; i < NbinsX + 1; i++){
       delete h1[i];
     }
     delete VariableHist1D;
   }
   if(iflag == 2){
     for(int i = 1; i < NbinsX + 1; i++){
       for(int j = 1; j < NbinsX + 1; j++){
         delete h2[i][j];
       }
     }
     delete VariableHist2D;
   }
   if(iflag == 3){
     for(int i = 1; i < NbinsX + 1; i++){
       for(int j = 1; j < NbinsX + 1; j++){
         for(int z = 1; z < NbinsZ + 1; z++){
           delete h3[i][j][z];
         }
       }
     }
     delete VariableHist3D;
   }
   return;
 }

 if(iflag == 1){
   for(int i = 1; i < NbinsX + 1; i++){
     if(fabs(h1[i]->GetBinContent(0)) > 1e-40 || fabs(h1[i]->GetBinContent(2)) > 1e-40){
         cout<<histName<<": There are some events filled into the underflow or over flow bins in the No."<<i<<" bin. Please enlarge the range. underflow: "<<h1[i]->GetBinContent(0)<<" overflow: "<<h1[i]->GetBinContent(2)<<endl;
     }

     AngularHist1D->SetBinContent(i, k * h1[i]->GetMean() + b);
     AngularHist1D->SetBinError(i, k * h1[i]->GetMeanError());

     delete h1[i];
   }
   delete VariableHist1D;
 }

 if(iflag == 2){
   for(int i = 1; i < NbinsX + 1; i++){
     for(int j = 1; j < NbinsY + 1; j++){
       if(fabs(h2[i][j]->GetBinContent(0)) > 1e-40 || fabs(h2[i][j]->GetBinContent(2)) > 1e-40){
         cout<<histName<<": There are some events filled into the underflow or over flow bins in the No."<<i<<" bin. Please enlarge the range. underflow: "<<h2[i][j]->GetBinContent(0)<<" overflow: "<<h2[i][j]->GetBinContent(2)<<endl;
       }

       AngularHist2D->SetBinContent(i, j, k * h2[i][j]->GetMean() + b);
       AngularHist2D->SetBinError(i, j, k * h2[i][j]->GetMeanError());
       delete h2[i][j];
     }
   }
   delete VariableHist2D;
 }

 if(iflag == 3){
   for(int i = 1; i < NbinsX + 1; i++){
     for(int j = 1; j < NbinsY + 1; j++){
       for(int z = 1; z < NbinsZ + 1; z++){
         if(fabs(h3[i][j][z]->GetBinContent(0)) > 1e-40 || fabs(h3[i][j][z]->GetBinContent(2)) > 1e-40){
           cout<<histName<<": There are some events filled into the underflow or over flow bins in the No."<<i<<" bin. Please enlarge the range. underflow: "<<h3[i][j][z]->GetBinContent(0)<<" overflow: "<<h3[i][j][z]->GetBinContent(2)<<endl;
         }

         AngularHist3D->SetBinContent(i, j, z, k * h3[i][j][z]->GetMean() + b);
         AngularHist3D->SetBinError(i, j, z, k * h3[i][j][z]->GetMeanError());
         delete h3[i][j][z];
       }
     }
   }
   delete VariableHist3D;
 }

 cout<<myAngular<<" has been saved."<<endl;
}

void AngularFunction::Add(AngularFunction* angular1)
{
 for(int i = 0; i < hist_1d.size(); i++){
   hist_1d.at(i)->Add((angular1->hist_1d).at(i));
 }
 if(iflag == 1) this->VariableHist1D->Add(angular1->VariableHist1D);
 if(iflag == 2) this->VariableHist2D->Add(angular1->VariableHist2D);
 if(iflag == 3) this->VariableHist3D->Add(angular1->VariableHist3D);

}

void AngularFunction::Reset()
{
 for(int i = 0; i < hist_1d.size(); i++){
   hist_1d.at(i)->Reset();
 }

 if(iflag == 1) VariableHist1D->Reset();
 if(iflag == 2) VariableHist2D->Reset();
 if(iflag == 3) VariableHist3D->Reset();

 if(iflag == 1) AngularHist1D->Reset();
 if(iflag == 2) AngularHist2D->Reset();
 if(iflag == 3) AngularHist3D->Reset();
}

void AngularFunction::Write()
{
 if(iflag == 1) AngularHist1D->Write();
 if(iflag == 2) AngularHist2D->Write();
 if(iflag == 3) AngularHist3D->Write();
}

void AngularFunction::End()
{
}
