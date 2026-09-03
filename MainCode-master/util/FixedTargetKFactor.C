#include <iostream>
#include <fstream>
#include "RootCommon.h"

using namespace std;

void ReadTable(TString FileName, TH1D* &h1, TString name, int iColumn)
{
    ifstream datafile(FileName);

    string FileLine;
    vector<double> result;

    vector<vector<double>> FullTable;
    while(getline(datafile, FileLine)){
      vector<double> LineVector;
      double Value;
      stringstream LineStream(FileLine);
      while(LineStream >> Value){
        LineVector.push_back(Value);
      }
      if(LineVector.size() == 0) break;

      FullTable.push_back(LineVector);//FullTable.at(i).at(j) is i row and j column
    }

    for(int i = 0; i < FullTable.size(); i++){
      result.push_back(FullTable.at(i).at(iColumn));
    }

    h1 = new TH1D(name, name, result.size(), 0, result.size());
    for(int i = 0; i < result.size(); i++){
      h1->SetBinContent(i + 1, result.at(i));
      h1->SetBinError(i + 1, 0.0);
    }
}

void UpdateKFactor(TString inname, TString outname, TH1D* LO, TH1D* NLO, TH1D* NNLO, int Ninfo, TH1D* LO2 = 0, TH1D* NLO2 = 0, TH1D* NNLO2 = 0)
{
 // LO is LO
 // NLO is NLO/LO
 // NNLO is w432/NLO

    ifstream datafile(inname);
    ofstream upfile(outname);

    string FileLine;

    for(int i = 0; i < 6; i++){
      getline(datafile, FileLine);
      upfile<<FileLine<<endl;
    }

    vector<double> result;

    vector<vector<double>> FullTable;
    while(getline(datafile, FileLine)){
      vector<double> LineVector;
      double Value;
      stringstream LineStream(FileLine);
      while(LineStream >> Value){
        LineVector.push_back(Value);
      }
      if(LineVector.size() == 0) break;

      FullTable.push_back(LineVector);//FullTable.at(i).at(j) is i row and j column
    }

    for(int i = 0; i < FullTable.size(); i++){
      upfile << setw(6) << *right << fixed << setprecision(3) << FullTable.at(i).at(0) << "  ";
      upfile << setw(5) << *right << fixed << setprecision(2) << FullTable.at(i).at(1) << "    ";
      upfile << uppercase << scientific << setprecision(3) << FullTable.at(i).at(2) << " ";
      upfile << uppercase << scientific << setprecision(3) << FullTable.at(i).at(3) << "  ";
      upfile << uppercase << scientific << setprecision(3) << FullTable.at(i).at(4) << "  ";
      upfile << fixed << setprecision(3) << FullTable.at(i).at(5) << "  ";
      if(Ninfo > 6) upfile << fixed << setprecision(3) << FullTable.at(i).at(6) << "  ";
      if(Ninfo > 6) upfile << fixed << setprecision(3) << FullTable.at(i).at(7) << "  ";
      //upfile << fixed << setprecision(5) << NLO->GetBinContent(i + 1) / LO->GetBinContent(i + 1) << "    ";
      //upfile << fixed << setprecision(5) << NNLO->GetBinContent(i + 1) / NLO->GetBinContent(i + 1) << "    ";
      upfile << fixed << setprecision(5) << NLO->GetBinContent(i + 1) << "    ";
      upfile << fixed << setprecision(5) << NNLO->GetBinContent(i + 1) << "    ";
      //if(FixedNLO != 0) upfile << fixed << setprecision(5) << FixedNLO->GetBinContent(i + 1) / LO->GetBinContent(i + 1) << "    ";
      if(LO2 != 0) upfile << fixed << setprecision(5) << NLO2->GetBinContent(i + 1) << "    ";
      if(LO2 != 0) upfile << fixed << setprecision(5) << NNLO2->GetBinContent(i + 1) << "    ";
      upfile << endl;
    }
}

int main(int argc, char** agrv)
{
 TFile* file = new TFile("save.root", "RECREATE");
 file->cd();

 TH1D* e605_data;
 TH1D* e605_w321;
 TH1D* e605_w432;
 TH1D* e605_lo;
 TH1D* e605_nlo;
 TH1D* e605_Q;
 TH1D* e605_w321overlo;
 TH1D* e605_w432overw321;
 TH1D* e605_nlooverlo;
 TH1D* e605_nlooverlo_keping;
 TH1D* e605_nnloovernlo_keping;
 TH1D* e605_lo_FittingCode;
 TH1D* e605_nlo_FittingCode;
 TH1D* e605_w432overnlo;

 TH1D* e866ppxf_data;
 TH1D* e866ppxf_w321;
 TH1D* e866ppxf_w432;
 TH1D* e866ppxf_lo;
 TH1D* e866ppxf_Q;
 TH1D* e866ppxf_y;
 TH1D* e866ppxf_lo_FittingCode;
 TH1D* e866ppxf_nlo_FittingCode;
 TH1D* e866ppxf_nlooverlo;
 TH1D* e866ppxf_w432overnlo;

 TH1D* e866f_data;
 TH1D* e866f_pp_w321;
 TH1D* e866f_pd_w321;
 TH1D* e866f_w321;
 TH1D* e866f_pp_w432;
 TH1D* e866f_pd_w432;
 TH1D* e866f_w432;
 TH1D* e866f_pp_lo;
 TH1D* e866f_pd_lo;
 TH1D* e866f_lo;
 TH1D* e866f_Q;
 TH1D* e866f_y;
 TH1D* e866f_proton_lo_FittingCode;
 TH1D* e866f_neutron_lo_FittingCode;
 TH1D* e866f_proton_nlo_FittingCode;
 TH1D* e866f_neutron_nlo_FittingCode;
 TH1D* e866f_proton_w432overnlo;
 TH1D* e866f_neutron_w432overnlo;
 TH1D* e866f_proton_nlooverlo;
 TH1D* e866f_neutron_nlooverlo;

 TH1D* e906aF_data;
 TH1D* e906aF_pp_w321;
 TH1D* e906aF_pd_w321;
 TH1D* e906aF_w321;
 TH1D* e906aF_pp_w432;
 TH1D* e906aF_pd_w432;
 TH1D* e906aF_w432;
 TH1D* e906aF_pp_lo;
 TH1D* e906aF_pd_lo;
 TH1D* e906aF_lo;
 TH1D* e906aF_Q;
 TH1D* e906aF_y;
 TH1D* e906aF_proton_lo_FittingCode;
 TH1D* e906aF_neutron_lo_FittingCode;
 TH1D* e906aF_proton_nlo_FittingCode;
 TH1D* e906aF_neutron_nlo_FittingCode;
 TH1D* e906aF_proton_w432overnlo;
 TH1D* e906aF_neutron_w432overnlo;
 TH1D* e906aF_proton_nlooverlo;
 TH1D* e906aF_neutron_nlooverlo;

 ReadTable("e605_ResBos2_w321.dat", e605_data, "e605_Data", 2);
 ReadTable("e605_ResBos2_w321.dat", e605_w321, "e605_w321", 3);
 ReadTable("e605_ResBos2_w432.dat", e605_w432, "e605_w432", 3);
 ReadTable("e605_LO.txt",   e605_lo,   "e605_LO",   3);
 ReadTable("e605_LO.txt",   e605_Q,    "e605_Qstream",   0);
 //ReadTable("E605_Kfactor_Keping", e605_nlooverlo_keping, "e605_nlooverlo_keping", 6);
 //ReadTable("E605_Kfactor_Keping", e605_nnloovernlo_keping, "e605_nnloovernlo_keping", 7);
 ReadTable("e605_FittingCode.dat", e605_lo_FittingCode, "e605_LO_FittingCode", 2);
 ReadTable("e605_FittingCode.dat", e605_nlo_FittingCode, "e605_NLO_FittingCode", 1);

 ReadTable("e866ppxf_ResBos2_w321.dat", e866ppxf_data, "e866ppxf_Data", 2);
 ReadTable("e866ppxf_ResBos2_w321.dat", e866ppxf_w321, "e866ppxf_w321", 3);
 ReadTable("e866ppxf_ResBos2_w432.dat", e866ppxf_w432, "e866ppxf_w432", 3);
 ReadTable("e866ppxf_LO.txt",   e866ppxf_lo,   "e866ppxf_LO",   3);
 ReadTable("e866ppxf_LO.txt",   e866ppxf_Q,    "e866ppxf_Qstream",   0);
 ReadTable("e866ppxf_LO.txt",   e866ppxf_y,    "e866ppxf_ystream",   2);
 ReadTable("e866ppxf_FittingCode.dat", e866ppxf_lo_FittingCode, "e866ppxf_LO_FittingCode", 2);
 ReadTable("e866ppxf_FittingCode.dat", e866ppxf_nlo_FittingCode, "e866ppxf_NLO_FittingCode", 1);

 ReadTable("e866f_pp_ResBos2_w321.dat", e866f_data,    "e866f_Data", 2);
 ReadTable("e866f_pp_ResBos2_w321.dat", e866f_pp_w321, "e866f_pp_w321", 3);
 ReadTable("e866f_pd_ResBos2_w321.dat", e866f_pd_w321, "e866f_pd_w321", 3);
 ReadTable("e866f_pp_ResBos2_w432.dat", e866f_pp_w432, "e866f_pp_w432", 3);
 ReadTable("e866f_pd_ResBos2_w432.dat", e866f_pd_w432, "e866f_pd_w432", 3);
 ReadTable("e866f_pp_LO.txt",   e866f_pp_lo,   "e866f_pp_LO",   3);
 ReadTable("e866f_pd_LO.txt",   e866f_pd_lo,   "e866f_pd_LO",   3);
 ReadTable("e866f_pp_LO.txt",   e866f_Q,       "e866f_Qstream",   0);
 ReadTable("e866f_pp_LO.txt",   e866f_y,       "e866f_ystream",   2);
 ReadTable("e866f_FittingCode.dat", e866f_proton_lo_FittingCode, "e866f_proton_LO_FittingCode", 2);
 ReadTable("e866f_FittingCode.dat", e866f_neutron_lo_FittingCode, "e866f_neutron_LO_FittingCode", 1);
 ReadTable("e866f_FittingCode.dat", e866f_proton_nlo_FittingCode, "e866f_proton_NLO_FittingCode", 5);
 ReadTable("e866f_FittingCode.dat", e866f_neutron_nlo_FittingCode, "e866f_neutron_NLO_FittingCode", 4);

 ReadTable("e906aF_pp_ResBos2_w321.dat", e906aF_data,    "e906aF_Data", 2);
 ReadTable("e906aF_pp_ResBos2_w321.dat", e906aF_pp_w321, "e906aF_pp_w321", 3);
 ReadTable("e906aF_pd_ResBos2_w321.dat", e906aF_pd_w321, "e906aF_pd_w321", 3);
 ReadTable("e906aF_pp_ResBos2_w432.dat", e906aF_pp_w432, "e906aF_pp_w432", 3);
 ReadTable("e906aF_pd_ResBos2_w432.dat", e906aF_pd_w432, "e906aF_pd_w432", 3);
 ReadTable("e906aF_pp_LO.txt",   e906aF_pp_lo,   "e906aF_pp_LO",   3);
 ReadTable("e906aF_pd_LO.txt",   e906aF_pd_lo,   "e906aF_pd_LO",   3);
 ReadTable("e906aF_pp_LO.txt",   e906aF_Q,       "e906aF_Qstream", 0);
 ReadTable("e906aF_pp_LO.txt",   e906aF_y,       "e906aF_ystream", 2);
 ReadTable("e906aF_FittingCode.dat", e906aF_proton_lo_FittingCode,   "e906aF_proton_LO_FittingCode", 2);
 ReadTable("e906aF_FittingCode.dat", e906aF_neutron_lo_FittingCode,  "e906aF_neutron_LO_FittingCode", 1);
 ReadTable("e906aF_FittingCode.dat", e906aF_proton_nlo_FittingCode,  "e906aF_proton_NLO_FittingCode", 5);
 ReadTable("e906aF_FittingCode.dat", e906aF_neutron_nlo_FittingCode, "e906aF_neutron_NLO_FittingCode", 4);

////////////////////////////////////////////////////////////////////////////////////

 /*TFile* E605_LO_File = new TFile("MC_results_LO.root");
 TFile* E605_NLO_File = new TFile("MC_results_NLO.root");
 vector<double> e605_lo_values;
 vector<double> e605_nlo_values;
 for(int i = 1; i <= 18; i++){
   TH1D* lo = (TH1D *)E605_LO_File->Get((TString)"E605_Q" + (int)i + (TString)"_Final");
   TH1D* nlo = (TH1D *)E605_NLO_File->Get((TString)"E605_Q" + (int)i + (TString)"_Final");
   for(int ibin = 1; ibin <= lo->GetNbinsX(); ibin++){
     e605_lo_values.push_back(lo->GetBinContent(ibin));
     e605_nlo_values.push_back(nlo->GetBinContent(ibin));
   }
 }*/

////////////////////////////////////////////////////////////////////////////////////

 file->cd();
 for(int i = 1; i <= e605_lo->GetNbinsX(); i++){
   e605_lo->SetBinContent(i, e605_lo->GetBinContent(i) * 2.0 * pow(e605_Q->GetBinContent(i), 4) / 1000.0);
   //e605_lo->SetBinContent(i, e605_lo_values.at(i - 1));
 }

 /*e605_nlo = new TH1D("e605_nlo", "e605_nlo", 119, 0, 119);
 for(int i = 1; i <= e605_nlo->GetNbinsX(); i++){
   e605_nlo->SetBinContent(i, e605_nlo_values.at(i - 1));
   e605_nlo->SetBinError(i, 0.0);
 }*/
 e605_w321overlo = new TH1D("e605_w321overlo", "e605_w321overlo", 119, 0, 119);
 e605_w432overw321 = new TH1D("e605_w432overw321", "e605_w432overw321", 119, 0, 119);
 e605_nlooverlo = new TH1D("e605_nlooverlo", "e605_nlooverlo", 119, 0, 119);
 e605_w432overnlo = new TH1D("e605_w432overnlo", "e605_w432overnlo", 119, 0, 119);

 for(int i = 1; i <= e605_w321overlo->GetNbinsX(); i++){
   e605_w321overlo->SetBinContent(i, e605_w321->GetBinContent(i) / e605_lo->GetBinContent(i));
   e605_w321overlo->SetBinError(i, 0.0);
   e605_w432overw321->SetBinContent(i, e605_w432->GetBinContent(i) / e605_w321->GetBinContent(i));
   e605_w432overw321->SetBinError(i, 0.0);
   e605_nlooverlo->SetBinContent(i, e605_nlo_FittingCode->GetBinContent(i) / e605_lo_FittingCode->GetBinContent(i));
   e605_nlooverlo->SetBinError(i, 0.0);
   e605_w432overnlo->SetBinContent(i, (e605_w432->GetBinContent(i) / e605_lo->GetBinContent(i)) / (e605_nlo_FittingCode->GetBinContent(i) / e605_lo_FittingCode->GetBinContent(i)));
   e605_w432overnlo->SetBinError(i, 0.0);
 }

 e866ppxf_nlooverlo = new TH1D("e866ppxf_nlooverlo", "e866ppxf_nlooverlo", 184, 0, 184);
 e866ppxf_w432overnlo = new TH1D("e866ppxf_w432overnlo", "e866ppxf_w432overnlo", 184, 0, 184);

 for(int i = 1; i <= e866ppxf_lo->GetNbinsX(); i++){
   e866ppxf_lo->SetBinContent(i, e866ppxf_lo->GetBinContent(i) * 2.0 * pow(e866ppxf_Q->GetBinContent(i), 4) / 1000.0 * 38.75 / 2.0 / e866ppxf_Q->GetBinContent(i) / cosh(e866ppxf_y->GetBinContent(i)));

   e866ppxf_nlooverlo->SetBinContent(i, e866ppxf_nlo_FittingCode->GetBinContent(i) / e866ppxf_lo_FittingCode->GetBinContent(i));
   e866ppxf_nlooverlo->SetBinError(i, 0.0);
   e866ppxf_w432overnlo->SetBinContent(i, (e866ppxf_w432->GetBinContent(i) / e866ppxf_lo->GetBinContent(i)) / (e866ppxf_nlo_FittingCode->GetBinContent(i) / e866ppxf_lo_FittingCode->GetBinContent(i)));
   e866ppxf_w432overnlo->SetBinError(i, 0.0);

 }

 e866f_w321 = (TH1D *)e866f_pd_w321->Clone("e866f_w321");
 e866f_w321->Divide(e866f_pp_w321);

 e866f_w432 = (TH1D *)e866f_pd_w432->Clone("e866f_w432");
 e866f_w432->Divide(e866f_pp_w432);

 e866f_lo   = (TH1D *)e866f_pd_lo  ->Clone("e866f_LO");
 e866f_lo->Divide(e866f_pp_lo);

 for(int i = 1; i <= e866f_data->GetNbinsX(); i++){
   e866f_w321->SetBinError(i, 0.0);
   e866f_w432->SetBinError(i, 0.0);
   e866f_lo->SetBinError(i, 0.0);
 }

 e906aF_w321 = (TH1D *)e906aF_pd_w321->Clone("e906aF_w321");
 e906aF_w321->Divide(e906aF_pp_w321);

 e906aF_w432 = (TH1D *)e906aF_pd_w432->Clone("e906aF_w432");
 e906aF_w432->Divide(e906aF_pp_w432);

 e906aF_lo   = (TH1D *)e906aF_pd_lo  ->Clone("e906aF_LO");
 e906aF_lo->Divide(e906aF_pp_lo);

 for(int i = 1; i <= e906aF_data->GetNbinsX(); i++){
   e906aF_w321->SetBinError(i, 0.0);
   e906aF_w432->SetBinError(i, 0.0);
   e906aF_lo->SetBinError(i, 0.0);
 }

 e866f_proton_nlooverlo = new TH1D("e866f_proton_nlooverlo", "e866f_proton_nlooverlo", 15, 0, 15);
 e866f_proton_w432overnlo = new TH1D("e866f_proton_w432overnlo", "e866f_proton_w432overnlo", 15, 0, 15);
 e866f_neutron_nlooverlo = new TH1D("e866f_neutron_nlooverlo", "e866f_neutron_nlooverlo", 15, 0, 15);
 e866f_neutron_w432overnlo = new TH1D("e866f_neutron_w432overnlo", "e866f_neutron_w432overnlo", 15, 0, 15);

 for(int i = 1; i <= e866f_proton_nlooverlo->GetNbinsX(); i++){
   e866f_pp_lo->SetBinContent(i, e866f_pp_lo->GetBinContent(i) * 2.0 * pow(e866f_Q->GetBinContent(i), 4) / 1000.0 * 38.76 / 2.0 / e866f_Q->GetBinContent(i) / cosh(e866f_y->GetBinContent(i)));
   e866f_pd_lo->SetBinContent(i, e866f_pd_lo->GetBinContent(i) * 2.0 * pow(e866f_Q->GetBinContent(i), 4) / 1000.0 * 38.76 / 2.0 / e866f_Q->GetBinContent(i) / cosh(e866f_y->GetBinContent(i)));

   double proton_nlo_fittingcode = e866f_proton_nlo_FittingCode->GetBinContent(i);
   double proton_lo_fittingcode = e866f_proton_lo_FittingCode->GetBinContent(i);
   double proton_w432 = e866f_pp_w432->GetBinContent(i);
   double proton_lo = e866f_pp_lo->GetBinContent(i);

   double neutron_nlo_fittingcode = e866f_neutron_nlo_FittingCode->GetBinContent(i);
   double neutron_lo_fittingcode = e866f_neutron_lo_FittingCode->GetBinContent(i);
   double neutron_w432 = 2.0 * (e866f_pd_w432->GetBinContent(i) - e866f_pp_w432->GetBinContent(i) / 2.0);
   double neutron_lo = 2.0 * (e866f_pd_lo->GetBinContent(i) - e866f_pp_lo->GetBinContent(i) / 2.0);

   //cout<<proton_w432<<"  "<<proton_lo<<"  "<<proton_nlo_fittingcode<<"  "<<proton_lo_fittingcode<<endl;

   e866f_proton_nlooverlo->SetBinContent(i, proton_nlo_fittingcode / proton_lo_fittingcode);
   e866f_proton_nlooverlo->SetBinError(i, 0.0);
   e866f_proton_w432overnlo->SetBinContent(i, (proton_w432 / proton_lo) / (proton_nlo_fittingcode / proton_lo_fittingcode));
   e866f_proton_w432overnlo->SetBinError(i, 0.0);
   e866f_neutron_nlooverlo->SetBinContent(i, neutron_nlo_fittingcode / neutron_lo_fittingcode);
   e866f_neutron_nlooverlo->SetBinError(i, 0.0);
   e866f_neutron_w432overnlo->SetBinContent(i, (neutron_w432 / neutron_lo) / (neutron_nlo_fittingcode / neutron_lo_fittingcode));
   e866f_neutron_w432overnlo->SetBinError(i, 0.0);
 }

 e906aF_proton_nlooverlo =    new TH1D("e906aF_proton_nlooverlo",    "e906aF_proton_nlooverlo", 6, 0, 6);
 e906aF_proton_w432overnlo =  new TH1D("e906aF_proton_w432overnlo",  "e906aF_proton_w432overnlo", 6, 0, 6);
 e906aF_neutron_nlooverlo =   new TH1D("e906aF_neutron_nlooverlo",   "e906aF_neutron_nlooverlo", 6, 0, 6);
 e906aF_neutron_w432overnlo = new TH1D("e906aF_neutron_w432overnlo", "e906aF_neutron_w432overnlo", 6, 0, 6);

 for(int i = 1; i <= e906aF_proton_nlooverlo->GetNbinsX(); i++){
   e906aF_pp_lo->SetBinContent(i, e906aF_pp_lo->GetBinContent(i) * 2.0 * pow(e906aF_Q->GetBinContent(i), 4) / 1000.0 * 15.07 / 2.0 / e906aF_Q->GetBinContent(i) / cosh(e906aF_y->GetBinContent(i)));
   e906aF_pd_lo->SetBinContent(i, e906aF_pd_lo->GetBinContent(i) * 2.0 * pow(e906aF_Q->GetBinContent(i), 4) / 1000.0 * 15.07 / 2.0 / e906aF_Q->GetBinContent(i) / cosh(e906aF_y->GetBinContent(i)));

   double proton_nlo_fittingcode = e906aF_proton_nlo_FittingCode->GetBinContent(i);
   double proton_lo_fittingcode = e906aF_proton_lo_FittingCode->GetBinContent(i);
   double proton_w432 = e906aF_pp_w432->GetBinContent(i);
   double proton_lo = e906aF_pp_lo->GetBinContent(i);

   double neutron_nlo_fittingcode = e906aF_neutron_nlo_FittingCode->GetBinContent(i);
   double neutron_lo_fittingcode = e906aF_neutron_lo_FittingCode->GetBinContent(i);
   double neutron_w432 = 2.0 * (e906aF_pd_w432->GetBinContent(i) - e906aF_pp_w432->GetBinContent(i) / 2.0);
   double neutron_lo = 2.0 * (e906aF_pd_lo->GetBinContent(i) - e906aF_pp_lo->GetBinContent(i) / 2.0);

   e906aF_proton_nlooverlo->SetBinContent(i, proton_nlo_fittingcode / proton_lo_fittingcode);
   e906aF_proton_nlooverlo->SetBinError(i, 0.0);
   e906aF_proton_w432overnlo->SetBinContent(i, (proton_w432 / proton_lo) / (proton_nlo_fittingcode / proton_lo_fittingcode));
   e906aF_proton_w432overnlo->SetBinError(i, 0.0);
   e906aF_neutron_nlooverlo->SetBinContent(i, neutron_nlo_fittingcode / neutron_lo_fittingcode);
   e906aF_neutron_nlooverlo->SetBinError(i, 0.0);
   e906aF_neutron_w432overnlo->SetBinContent(i, (neutron_w432 / neutron_lo) / (neutron_nlo_fittingcode / neutron_lo_fittingcode));
   e906aF_neutron_w432overnlo->SetBinError(i, 0.0);
 }

 UpdateKFactor("e605", "e605_up2025", e605_lo, e605_nlooverlo, e605_w432overnlo, 8);
 UpdateKFactor("e866ppxf", "e866ppxf_up2025", e866ppxf_lo, e866ppxf_nlooverlo, e866ppxf_w432overnlo, 8);

 UpdateKFactor("e866f_pp", "e866f_up2025", e866f_neutron_lo_FittingCode, e866f_neutron_nlooverlo, e866f_neutron_w432overnlo, 6, e866f_proton_lo_FittingCode, e866f_proton_nlooverlo, e866f_proton_w432overnlo);
 UpdateKFactor("e906aF_pp", "e906aF_up2025", e906aF_neutron_lo_FittingCode, e906aF_neutron_nlooverlo, e906aF_neutron_w432overnlo, 8, e906aF_proton_lo_FittingCode, e906aF_proton_nlooverlo, e906aF_proton_w432overnlo);

 file->Write();
 file->Close();


/*
 TFile* file = new TFile("save.root", "RECREATE");
 file->cd();

 TH1D *W_Q1_NLO, *WY_Q1_NLO, *P_Q1_NLO, *A_Q1_NLO, *Y_Q1_NLO;
 TH1D *W_Q2_NLO, *WY_Q2_NLO, *P_Q2_NLO, *A_Q2_NLO, *Y_Q2_NLO;

 TH1D *W_Q1_NNLO, *WY_Q1_NNLO, *P_Q1_NNLO, *A_Q1_NNLO, *Y_Q1_NNLO;
 TH1D *W_Q2_NNLO, *WY_Q2_NNLO, *P_Q2_NNLO, *A_Q2_NNLO, *Y_Q2_NNLO;

 TH1D *yk_Q1, *yk_Q2;

 ReadTable("w321_Q1.txt", W_Q1_NLO, "W_Q1_NLO", 1);
 ReadTable("w321_Q1.txt", WY_Q1_NLO, "WY_Q1_NLO", 2);
 ReadTable("w321_Q1.txt", P_Q1_NLO, "P_Q1_NLO", 3);
 ReadTable("w321_Q1.txt", A_Q1_NLO, "A_Q1_NLO", 4);
 ReadTable("w321_Q1.txt", Y_Q1_NLO, "Y_Q1_NLO", 5);

 ReadTable("w321_Q2.txt", W_Q2_NLO, "W_Q2_NLO", 1);
 ReadTable("w321_Q2.txt", WY_Q2_NLO, "WY_Q2_NLO", 2);
 ReadTable("w321_Q2.txt", P_Q2_NLO, "P_Q2_NLO", 3);
 ReadTable("w321_Q2.txt", A_Q2_NLO, "A_Q2_NLO", 4);
 ReadTable("w321_Q2.txt", Y_Q2_NLO, "Y_Q2_NLO", 5);

 ReadTable("w432_y1.txt", W_Q1_NNLO, "W_Q1_NNLO", 1);
 ReadTable("w432_y1.txt", WY_Q1_NNLO, "WY_Q1_NNLO", 2);
 ReadTable("w432_y1.txt", P_Q1_NNLO, "P_Q1_NNLO", 3);
 ReadTable("w432_y1.txt", A_Q1_NNLO, "A_Q1_NNLO", 4);
 ReadTable("w432_y1.txt", Y_Q1_NNLO, "Y_Q1_NNLO", 5);
 ReadTable("w432_y1.txt", yk_Q1,     "yk_Q1",     6);

 ReadTable("w432_y2.txt", W_Q2_NNLO, "W_Q2_NNLO", 1);
 ReadTable("w432_y2.txt", WY_Q2_NNLO, "WY_Q2_NNLO", 2);
 ReadTable("w432_y2.txt", P_Q2_NNLO, "P_Q2_NNLO", 3);
 ReadTable("w432_y2.txt", A_Q2_NNLO, "A_Q2_NNLO", 4);
 ReadTable("w432_y2.txt", Y_Q2_NNLO, "Y_Q2_NNLO", 5);
 ReadTable("w432_y2.txt", yk_Q2,     "yk_Q2",     6);

 TH1D *Pert1_Q1, *Pert2_Q1, *Asym1_Q1, *Asym2_Q1;
 TH1D *Pert1_Q2, *Pert2_Q2, *Asym1_Q2, *Asym2_Q2;

 ReadTable("pert_Q1.txt", Pert1_Q1, "Pert1_Q1", 3);
 ReadTable("pert_Q1.txt", Pert2_Q1, "Pert2_Q1", 4);
 ReadTable("asym_Q1.txt", Asym1_Q1, "Asym1_Q1", 3);
 ReadTable("asym_Q1.txt", Asym2_Q1, "Asym2_Q1", 5);
 ReadTable("pert_Q2.txt", Pert1_Q2, "Pert1_Q2", 3);
 ReadTable("pert_Q2.txt", Pert2_Q2, "Pert2_Q2", 4);
 ReadTable("asym_Q2.txt", Asym1_Q2, "Asym1_Q2", 3);
 ReadTable("asym_Q2.txt", Asym2_Q2, "Asym2_Q2", 5);

 file->Write();
 file->Close();
*/
/*
 for(int i = 1; i <= Pert1_Q1->GetNbinsX(); i++){
   Pert2_Q1->SetBinContent(i, Pert1_Q1->GetBinContent(i) + Pert2_Q1->GetBinContent(i));
   Pert2_Q2->SetBinContent(i, Pert1_Q2->GetBinContent(i) + Pert2_Q2->GetBinContent(i));

   double W = W_Q1_NNLO->GetBinContent(i);
   double P = P_Q1_NNLO->GetBinContent(i) * Pert2_Q1->GetBinContent(i) / Pert1_Q1->GetBinContent(i);
   double A = A_Q1_NNLO->GetBinContent(i) * Asym2_Q1->GetBinContent(i) / Asym1_Q1->GetBinContent(i);
   WY_Q1_NNLO->SetBinContent(i, W + P - A);
   P_Q1_NNLO->SetBinContent(i, P);
   A_Q1_NNLO->SetBinContent(i, A);
   Y_Q1_NNLO->SetBinContent(i, P - A);

   W = W_Q2_NNLO->GetBinContent(i);
   P = P_Q2_NNLO->GetBinContent(i) * Pert2_Q2->GetBinContent(i) / Pert1_Q2->GetBinContent(i);
   A = A_Q2_NNLO->GetBinContent(i) * Asym2_Q2->GetBinContent(i) / Asym1_Q2->GetBinContent(i);
   WY_Q2_NNLO->SetBinContent(i, W + P - A);
   P_Q2_NNLO->SetBinContent(i, P);
   A_Q2_NNLO->SetBinContent(i, A);
   Y_Q2_NNLO->SetBinContent(i, P - A);
 }

 file->Write();
 file->Close();
*/

 return 1;
}
