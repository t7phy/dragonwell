#include <iostream>
#include <fstream>
#include "RootCommon.h"
#include "Tools/Tools.h"

using namespace std;

void ReadTable(TString FileName, TH1D* &h1, TString name, int iColumn)
{
    ifstream datafile(FileName);

    string FileLine;
    vector<double> result;

    int nHead = 3;
    int NCorr;
    double NormErr;
    int NParam;
    vector<int> Param(3);

    for(int i = 0; i < nHead; i++){//first 3(2) comment lines
      getline(datafile, FileLine);
      cout<<FileLine<<endl;
    }

    getline(datafile, FileLine);//fourth line(by default)

    while(FileLine.substr(FileLine.find_first_not_of(" \t\n\r\f\v"), 1) == "*" || FileLine.substr(FileLine.find_first_not_of(" \t\n\r\f\v"), 1) == "#"){//find the rest comment lines
      getline(datafile, FileLine);
    }

    //process fouth line
    stringstream FourthLine(FileLine);
    string SubFourthLine1, SubFourthLine2;
    FourthLine >> SubFourthLine1 >> SubFourthLine2;

    //cout<<SubFourthLine1 <<"  "<< SubFourthLine2<<endl;
    //cout<<isInteger(SubFourthLine1)<<" "<<isFloat(SubFourthLine1)<<" "<<isInteger(SubFourthLine2)<<" "<<isFloat(SubFourthLine2)<<endl;
    if((isInteger(SubFourthLine1) || isFloat(SubFourthLine1)) && (isInteger(SubFourthLine2) || isFloat(SubFourthLine2))){
      NormErr = stod(SubFourthLine1);
      NCorr = stoi(SubFourthLine2);
      cout<<NormErr<<"  "<<NCorr<<endl;
    }
    else{
      NParam = stoi(SubFourthLine1);
      if(NParam > 3) NParam = 3; // force to only read the first 3 parameters
      getline(datafile, FileLine);//read NormErr, # of corr_err
      stringstream LineString(FileLine);
      LineString >> NormErr >> NCorr;
      for(int i = 0; i < NParam; i++){
        LineString >> Param.at(i);
      }
    }

    getline(datafile, FileLine);//Header Information

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

void UpdateKFactor(TString inname, TString outname, TH1D* KFactor1, int KFactorColumn1, TH1D* KFactor2 = 0, int KFactorColumn2 = -1)
{   
    ifstream datafile(inname);
    ofstream upfile(outname);
    
    string FileLine;

    int nHead = 3;
    int NCorr;
    double NormErr;
    int NParam;
    vector<int> Param(3);

    for(int i = 0; i < nHead; i++){//first 3(2) comment lines
      getline(datafile, FileLine);
      cout<<FileLine<<endl;
      upfile<<FileLine<<endl;
    }

    getline(datafile, FileLine);//fourth line(by default)
    upfile<<FileLine<<endl;

    while(FileLine.substr(FileLine.find_first_not_of(" \t\n\r\f\v"), 1) == "*" || FileLine.substr(FileLine.find_first_not_of(" \t\n\r\f\v"), 1) == "#"){//find the rest comment lines
      getline(datafile, FileLine);
      upfile<<FileLine<<endl;
    }

    //process fouth line
    stringstream FourthLine(FileLine);
    string SubFourthLine1, SubFourthLine2;
    FourthLine >> SubFourthLine1 >> SubFourthLine2;

    //cout<<SubFourthLine1 <<"  "<< SubFourthLine2<<endl;
    //cout<<isInteger(SubFourthLine1)<<" "<<isFloat(SubFourthLine1)<<" "<<isInteger(SubFourthLine2)<<" "<<isFloat(SubFourthLine2)<<endl;
    if((isInteger(SubFourthLine1) || isFloat(SubFourthLine1)) && (isInteger(SubFourthLine2) || isFloat(SubFourthLine2))){
      NormErr = stod(SubFourthLine1);
      NCorr = stoi(SubFourthLine2);
      cout<<NormErr<<"  "<<NCorr<<endl;
    }
    else{
      NParam = stoi(SubFourthLine1);
      if(NParam > 3) NParam = 3; // force to only read the first 3 parameters
      getline(datafile, FileLine);//read NormErr, # of corr_err
      upfile<<FileLine<<endl;
      stringstream LineString(FileLine);
      LineString >> NormErr >> NCorr;
      for(int i = 0; i < NParam; i++){
        LineString >> Param.at(i);
      }
    }

    getline(datafile, FileLine);//Header Information
    upfile<<FileLine<<endl;

    vector<double> result;
    
    vector<vector<TString>> FullTable;
    vector<vector<string>> spaces;
    int FirstLine = 1;
    while(getline(datafile, FileLine)){

      string line = FileLine;
      vector<string> space;
      size_t i = 0, n = line.size();
      while (i < n) {
          if (isspace(static_cast<unsigned char>(line[i]))) {
              size_t j = i;
              while (j < n && isspace(static_cast<unsigned char>(line[j]))) ++j;
              space.push_back(line.substr(i, j - i));
              i = j;
          } else {
              while (i < n && !isspace(static_cast<unsigned char>(line[i]))) ++i;
          }
      }

      vector<TString> LineVector;
      string Value;
      stringstream LineStream(FileLine);
      while(LineStream >> Value){
        LineVector.push_back(Value.c_str());
      }
      if(LineVector.size() == 0) break;
      
      FullTable.push_back(LineVector);//FullTable.at(i).at(j) is i row and j column

      //cout<<"Number of space: "<<spaces.size()<<"  Number of numbers: "<<FullTable.at(0).size()<<endl;
      if(space.size() == LineVector.size() - 1){
        space.insert(space.begin(), "");
      }
      spaces.push_back(space);
    }

    for(int i = 0; i < FullTable.size(); i++){
      for(int j = 0; j < FullTable.at(i).size(); j++){
        TString Space = spaces.at(i).at(j).c_str();

        if(j != KFactorColumn1 && j != KFactorColumn2) upfile << Space << FullTable.at(i).at(j);
        else if(j == KFactorColumn1) upfile << Space << fixed << setprecision(15) << KFactor1->GetBinContent(i + 1);
        else if(j == KFactorColumn2) upfile << Space << fixed << setprecision(15) << KFactor2->GetBinContent(i + 1);
      }
      upfile << endl;
    }
}

int main(int argc, char** agrv)
{
 TFile* file = new TFile("save.root", "RECREATE");
 file->cd();

 TH1D* E245_Data;
 TH1D* E246_Data;
 TH1D* E248_Data;
 TH1D* E249_Data;
 TH1D* E250_Data;
 TH1D* E253_Data;
 TH1D* E225_Data;
 TH1D* E227_Data;
 TH1D* E234_Data;
 TH1D* E260_Data;
 TH1D* E261_Data;
 TH1D* E266_Data;
 TH1D* E267_Data;
 TH1D* E281_Data;
 TH1D* E211_Data;
 TH1D* E212_Data;
 TH1D* E218_Data;
 TH1D* E214_Data;
 TH1D* E215_Data;
 TH1D* E217_Data;

 TH1D* E245_NLO;
 TH1D* E246_NLO;
 TH1D* E248_NLO;
 TH1D* E249_NLO;
 TH1D* E250_NLO;
 TH1D* E253_NLO;
 TH1D* E225_NLO;
 TH1D* E227_NLO;
 TH1D* E234_NLO;
 TH1D* E260_NLO;
 TH1D* E261_NLO;
 TH1D* E266_NLO;
 TH1D* E267_NLO;
 TH1D* E281_NLO;
 TH1D* E211_NLO;
 TH1D* E212_NLO;
 TH1D* E218_NLO;
 TH1D* E214_NLO;
 TH1D* E215_NLO;
 TH1D* E217_NLO;

 TH1D* E245_w432;
 TH1D* E246_w432;
 TH1D* E248_w432;
 TH1D* E249_w432;
 TH1D* E250_w432;
 TH1D* E253_w432;
 TH1D* E225_w432;
 TH1D* E227_w432;
 TH1D* E234_w432;
 TH1D* E260_w432;
 TH1D* E261_w432;
 TH1D* E266_w432;
 TH1D* E267_w432;
 TH1D* E281_w432;
 TH1D* E211_w432;
 TH1D* E212_w432;
 TH1D* E218_w432;
 TH1D* E214_w432;
 TH1D* E215_w432;
 TH1D* E217_w432;

 TH1D* E245_w321;
 TH1D* E246_w321;
 TH1D* E248_w321;
 TH1D* E249_w321;
 TH1D* E250_w321;
 TH1D* E253_w321;
 TH1D* E225_w321;
 TH1D* E227_w321;
 TH1D* E234_w321;
 TH1D* E260_w321;
 TH1D* E261_w321;
 TH1D* E266_w321;
 TH1D* E267_w321;
 TH1D* E281_w321;
 TH1D* E211_w321;
 TH1D* E212_w321;
 TH1D* E218_w321;
 TH1D* E214_w321;
 TH1D* E215_w321;
 TH1D* E217_w321;

 TH1D* E225_NLO_tmp;
 TH1D* E227_NLO_tmp;
 TH1D* E234_NLO_tmp;
 TH1D* E266_NLO_tmp;
 TH1D* E267_NLO_tmp;
 TH1D* E281_NLO_tmp;

 TH1D* E225_w432_tmp;
 TH1D* E227_w432_tmp;
 TH1D* E234_w432_tmp;
 TH1D* E266_w432_tmp;
 TH1D* E267_w432_tmp;
 TH1D* E281_w432_tmp;

 TH1D* E225_w321_tmp;
 TH1D* E227_w321_tmp;
 TH1D* E234_w321_tmp;
 TH1D* E266_w321_tmp;
 TH1D* E267_w321_tmp;
 TH1D* E281_w321_tmp;

 TH1D* E245_kfactor;
 TH1D* E246_kfactor;
 TH1D* E248_kfactor;
 TH1D* E249_kfactor;
 TH1D* E250_kfactor;
 TH1D* E253_kfactor;
 TH1D* E225_kfactor;
 TH1D* E227_kfactor;
 TH1D* E234_kfactor;
 TH1D* E260_kfactor;
 TH1D* E261_kfactor;
 TH1D* E266_kfactor;
 TH1D* E267_kfactor;
 TH1D* E281_kfactor;
 TH1D* E211_kfactor;
 TH1D* E212_kfactor;
 TH1D* E218_kfactor;
 TH1D* E214_kfactor;
 TH1D* E215_kfactor;
 TH1D* E217_kfactor;

 TH1D* E214_BinWidth;

 TH1D* E245_oldkfactor;
 TH1D* E246_oldkfactor;
 TH1D* E248_oldkfactor;
 TH1D* E249_oldkfactor;
 TH1D* E250_oldkfactor;
 TH1D* E253_oldkfactor;
 TH1D* E225_oldkfactor;
 TH1D* E227_oldkfactor;
 TH1D* E234_oldkfactor;
 TH1D* E260_oldkfactor;
 TH1D* E261_oldkfactor;
 TH1D* E266_oldkfactor;
 TH1D* E267_oldkfactor;
 TH1D* E281_oldkfactor;
 TH1D* E211_oldkfactor;
 TH1D* E212_oldkfactor;
 TH1D* E218_oldkfactor;
 TH1D* E214_oldkfactor;
 TH1D* E215_oldkfactor;
 TH1D* E217_oldkfactor;

 function<void(TH1D*, TH1D*, TH1D* &)> GetKFactor = [&](TH1D* NLO, TH1D* w432, TH1D* &kfactor){
   TString name = NLO->GetName();
   name.ReplaceAll("_Final", "");
   name = name + "_KFactor";
   kfactor = (TH1D *)w432->Clone(name);
   kfactor->Divide(NLO);
 };

 function<void(TH1D*, TH1D* &, TH1D* &)> SeparateKFactor = [&](TH1D* kfactor, TH1D* &wp, TH1D* &wm){
   int nBin = kfactor->GetNbinsX();
   TString name = kfactor->GetName();
   wp = new TH1D(name + "_wp", name + "_wp", nBin / 2, 0, nBin / 2);
   wm = new TH1D(name + "_wm", name + "_wm", nBin / 2, 0, nBin / 2);

   for(int ibin = 1; ibin <= nBin / 2; ibin++){
     wp->SetBinContent(ibin, kfactor->GetBinContent(ibin));
     wm->SetBinContent(ibin, kfactor->GetBinContent(ibin + nBin / 2));
   }
 };

 function<void(TH1D*, TH1D* &)> GetWasymmetry = [&](TH1D* input, TH1D* &asy){
   int nBin = input->GetNbinsX();
   TString name = input->GetName();

   asy = new TH1D(name + "_asy", name + "_asy", nBin / 2, 0, nBin / 2);

   for(int ibin = 1; ibin <= nBin / 2; ibin++){
     double plus = input->GetBinContent(ibin);
     double minus = input->GetBinContent(ibin + nBin / 2);
     double Value = (plus - minus) / (plus + minus);

     asy->SetBinContent(ibin, Value);
     asy->SetBinError(ibin, 0.0);
   }
 };

 TFile* f_13TeV_NLO = new TFile("13TeV/MC_results_NLO.root");
 TFile* f_13TeV_w432 = new TFile("13TeV_BLNY/MC_results_w432.root");
 TFile* f_13TeV_w321 = new TFile("13TeV_BLNY/MC_results_w321.root");
 TFile* f_7TeV_NLO = new TFile("7TeV/MC_results_NLO.root");
 TFile* f_7TeV_w432 = new TFile("7TeV_BLNY/MC_results_w432.root");
 TFile* f_7TeV_w321 = new TFile("7TeV_BLNY/MC_results_w321.root");
 TFile* f_8TeV_NLO = new TFile("8TeV/MC_results_NLO.root");
 TFile* f_8TeV_w432 = new TFile("8TeV_BLNY/MC_results_w432.root");
 TFile* f_8TeV_w321 = new TFile("8TeV_BLNY/MC_results_w321.root");
 TFile* f_5TeV_NLO = new TFile("5TeV/MC_results_NLO.root");
 TFile* f_5TeV_w432 = new TFile("5TeV_BLNY/MC_results_w432.root");
 TFile* f_5TeV_w321 = new TFile("5TeV_BLNY/MC_results_w321.root");
 TFile* f_1p96TeV_NLO = new TFile("1.96TeV/MC_results_NLO.root");
 TFile* f_1p96TeV_w432 = new TFile("1.96TeV_BLNY/MC_results_w432.root");
 TFile* f_1p96TeV_w321 = new TFile("1.96TeV_BLNY/MC_results_w321.root");
 TFile* f_1p8TeV_NLO = new TFile("1.8TeV/MC_results_NLO.root");
 TFile* f_1p8TeV_w432 = new TFile("1.8TeV_BLNY/MC_results_w432.root");
 TFile* f_1p8TeV_w321 = new TFile("1.8TeV_BLNY/MC_results_w321.root");

 E245_NLO = (TH1D *)f_7TeV_NLO->Get("E245_Final");
 E245_w432 = (TH1D *)f_7TeV_w432->Get("E245_Final");
 E245_w321 = (TH1D *)f_7TeV_w321->Get("E245_Final");

 E246_NLO = (TH1D *)f_8TeV_NLO->Get("E246_Final");
 E246_w432 = (TH1D *)f_8TeV_w432->Get("E246_Final");
 E246_w321 = (TH1D *)f_8TeV_w321->Get("E246_Final");

 E248_NLO = (TH1D *)f_7TeV_NLO->Get("E248_Final");
 E248_w432 = (TH1D *)f_7TeV_w432->Get("E248_Final");
 E248_w321 = (TH1D *)f_7TeV_w321->Get("E248_Final");

 E249_NLO = (TH1D *)f_8TeV_NLO->Get("E249_Final");
 E249_w432 = (TH1D *)f_8TeV_w432->Get("E249_Final");
 E249_w321 = (TH1D *)f_8TeV_w321->Get("E249_Final");

 E250_NLO = (TH1D *)f_8TeV_NLO->Get("E250_Final");
 E250_w432 = (TH1D *)f_8TeV_w432->Get("E250_Final");
 E250_w321 = (TH1D *)f_8TeV_w321->Get("E250_Final");

 E253_NLO = (TH1D *)f_8TeV_NLO->Get("E253_Final");
 E253_w432 = (TH1D *)f_8TeV_w432->Get("E253_Final");
 E253_w321 = (TH1D *)f_8TeV_w321->Get("E253_Final");

 E225_NLO_tmp = (TH1D *)f_1p8TeV_NLO->Get("E225_Final");
 E225_w432_tmp = (TH1D *)f_1p8TeV_w432->Get("E225_Final");
 E225_w321_tmp = (TH1D *)f_1p8TeV_w321->Get("E225_Final");

 E227_NLO_tmp = (TH1D *)f_1p96TeV_NLO->Get("E227_Final");
 E227_w432_tmp = (TH1D *)f_1p96TeV_w432->Get("E227_Final");
 E227_w321_tmp = (TH1D *)f_1p96TeV_w321->Get("E227_Final");

 E234_NLO_tmp = (TH1D *)f_1p96TeV_NLO->Get("E234_Final");
 E234_w432_tmp = (TH1D *)f_1p96TeV_w432->Get("E234_Final");
 E234_w321_tmp = (TH1D *)f_1p96TeV_w321->Get("E234_Final");

 E260_NLO = (TH1D *)f_1p96TeV_NLO->Get("E260_Final");
 E260_w432 = (TH1D *)f_1p96TeV_w432->Get("E260_Final");
 E260_w321 = (TH1D *)f_1p96TeV_w321->Get("E260_Final");

 E261_NLO = (TH1D *)f_1p96TeV_NLO->Get("E261_Final");
 E261_w432 = (TH1D *)f_1p96TeV_w432->Get("E261_Final");
 E261_w321 = (TH1D *)f_1p96TeV_w321->Get("E261_Final");

 E266_NLO_tmp = (TH1D *)f_7TeV_NLO->Get("E266_Final");
 E266_w432_tmp = (TH1D *)f_7TeV_w432->Get("E266_Final");
 E266_w321_tmp = (TH1D *)f_7TeV_w321->Get("E266_Final");

 E267_NLO_tmp = (TH1D *)f_7TeV_NLO->Get("E267_Final");
 E267_w432_tmp = (TH1D *)f_7TeV_w432->Get("E267_Final");
 E267_w321_tmp = (TH1D *)f_7TeV_w321->Get("E267_Final");

 E281_NLO_tmp = (TH1D *)f_1p96TeV_NLO->Get("E281_Final");
 E281_w432_tmp = (TH1D *)f_1p96TeV_w432->Get("E281_Final");
 E281_w321_tmp = (TH1D *)f_1p96TeV_w321->Get("E281_Final");

 E211_NLO = (TH1D *)f_8TeV_NLO->Get("E211_Final");
 E211_w432 = (TH1D *)f_8TeV_w432->Get("E211_Final");
 E211_w321 = (TH1D *)f_8TeV_w321->Get("E211_Final");

 E212_NLO = (TH1D *)f_13TeV_NLO->Get("E212_Final");
 E212_w432 = (TH1D *)f_13TeV_w432->Get("E212_Final");
 E212_w321 = (TH1D *)f_13TeV_w321->Get("E212_Final");

 E218_NLO = (TH1D *)f_13TeV_NLO->Get("E218_Final");
 E218_w432 = (TH1D *)f_13TeV_w432->Get("E218_Final");
 E218_w321 = (TH1D *)f_13TeV_w321->Get("E218_Final");

 E214_NLO = (TH1D *)f_8TeV_NLO->Get("E214_Final");
 E214_w432 = (TH1D *)f_8TeV_w432->Get("E214_Final");
 E214_BinWidth = (TH1D *)f_8TeV_w432->Get("E214_BinWidth");
 E214_w321 = (TH1D *)f_8TeV_w321->Get("E214_Final");

 E215_NLO = (TH1D *)f_5TeV_NLO->Get("E215_Final");
 E215_w432 = (TH1D *)f_5TeV_w432->Get("E215_Final");
 E215_w321 = (TH1D *)f_5TeV_w321->Get("E215_Final");

 E217_NLO = (TH1D *)f_8TeV_NLO->Get("E217_Final");
 E217_w432 = (TH1D *)f_8TeV_w432->Get("E217_Final");
 E217_w321 = (TH1D *)f_8TeV_w321->Get("E217_Final");

 ReadTable("LHCb7ZWrap", E245_Data, "E245_Data", 3);
 ReadTable("LHCb8ZResKF", E246_Data, "E246_Data", 3);
 ReadTable("ATL7ZW", E248_Data, "E248_Data", 3);
 ReadTable("CMS8Wxa", E249_Data, "E249_Data", 3);
 ReadTable("LHCb8WZ", E250_Data, "E250_Data", 3);
 //ReadTable("ATL8ZpT", E253_Data, "E253_Data", 3);
 ReadTable("cdfLasy_up", E225_Data, "E225_Data", 3);
 ReadTable("cdfLasy2_up", E227_Data, "E227_Data", 3);
 ReadTable("d02Masy1_up", E234_Data, "E234_Data", 3);
 ReadTable("ZyD02a_up", E260_Data, "E260_Data", 3);
 ReadTable("ZyCDF2_up", E261_Data, "E261_Data", 3);
 ReadTable("CMS7Masy2_up", E266_Data, "E266_Data", 3);
 ReadTable("CMS7Easy_up", E267_Data, "E267_Data", 3);
 ReadTable("d02Easy5_up", E281_Data, "E281_Data", 3);
 ReadTable("ATL8W_new3_Yao", E211_Data, "E211_Data", 3);
 ReadTable("CMS13Zmu_new2_Yao", E212_Data, "E212_Data", 3);
 ReadTable("LHCb13Zy2_Decom.data_Yao", E218_Data, "E218_Data", 3);
 ReadTable("ATL8Z3d_Yao", E214_Data, "E214_Data", 3);
 ReadTable("ATL5WZunc.data_Yao", E215_Data, "E215_Data", 3);
 ReadTable("LHCb8W_Lastm2.data_Yao", E217_Data, "E217_Data", 3);

 ReadTable("LHCb7ZWrap", E245_oldkfactor,               "E245_oldkfactor", 27);
 ReadTable("LHCb8ZResKF", E246_oldkfactor,              "E246_oldkfactor", 16);
 ReadTable("ATL7ZW", E248_oldkfactor,                   "E248_oldkfactor", 146);
 ReadTable("CMS8Wxa", E249_oldkfactor,                  "E249_oldkfactor", 25);
 ReadTable("LHCb8WZ", E250_oldkfactor,                  "E250_oldkfactor", 26);
 //ReadTable("ATL8ZpT", E253_oldkfactor,                  "E253_oldkfactor", 113);
 ReadTable("cdfLasy_up", E225_oldkfactor,               "E225_oldkfactor", 8);
 ReadTable("cdfLasy2_up", E227_oldkfactor,              "E227_oldkfactor", 8);
 ReadTable("d02Masy1_up", E234_oldkfactor,              "E234_oldkfactor", 8);
 ReadTable("ZyD02a_up", E260_oldkfactor,                "E260_oldkfactor", 9);
 ReadTable("ZyCDF2_up", E261_oldkfactor,                "E261_oldkfactor", 19);
 ReadTable("CMS7Masy2_up", E266_oldkfactor,             "E266_oldkfactor", 20);
 ReadTable("CMS7Easy_up", E267_oldkfactor,              "E267_oldkfactor", 8);
 ReadTable("d02Easy5_up", E281_oldkfactor,              "E281_oldkfactor", 16);
 ReadTable("ATL8W_new3_Yao", E211_oldkfactor,           "E211_oldkfactor", 53);
 ReadTable("CMS13Zmu_new2_Yao", E212_oldkfactor,        "E212_oldkfactor", 20);
 ReadTable("LHCb13Zy2_Decom.data_Yao", E218_oldkfactor, "E218_oldkfactor", 24);
 ReadTable("ATL8Z3d_Yao", E214_oldkfactor,              "E214_oldkfactor", 286);
 ReadTable("ATL5WZunc.data_Yao", E215_oldkfactor,       "E215_oldkfactor", 9);
 ReadTable("LHCb8W_Lastm2.data_Yao", E217_oldkfactor,   "E217_oldkfactor", 10);


 GetKFactor(E245_NLO, E245_w432, E245_kfactor);
 GetKFactor(E246_NLO, E246_w432, E246_kfactor);
 GetKFactor(E248_NLO, E248_w432, E248_kfactor);
 GetKFactor(E249_NLO, E249_w432, E249_kfactor);
 GetKFactor(E250_NLO, E250_w432, E250_kfactor);
 GetKFactor(E253_NLO, E253_w432, E253_kfactor);
 GetKFactor(E225_NLO_tmp, E225_w432_tmp, E225_kfactor);
 GetKFactor(E227_NLO_tmp, E227_w432_tmp, E227_kfactor);
 GetKFactor(E234_NLO_tmp, E234_w432_tmp, E234_kfactor);
 GetKFactor(E260_NLO, E260_w432, E260_kfactor);
 GetKFactor(E261_NLO, E261_w432, E261_kfactor);
 GetKFactor(E266_NLO_tmp, E266_w432_tmp, E266_kfactor);
 GetKFactor(E267_NLO_tmp, E267_w432_tmp, E267_kfactor);
 GetKFactor(E281_NLO_tmp, E281_w432_tmp, E281_kfactor);
 GetKFactor(E211_NLO, E211_w432, E211_kfactor);
 GetKFactor(E212_NLO, E212_w432, E212_kfactor);
 GetKFactor(E218_NLO, E218_w432, E218_kfactor);
 GetKFactor(E214_NLO, E214_w432, E214_kfactor);
 GetKFactor(E215_NLO, E215_w432, E215_kfactor);
 GetKFactor(E217_NLO, E217_w432, E217_kfactor);

 for(int ibin = 1; ibin <= E214_kfactor->GetNbinsX(); ibin++){
   double kfactor = E214_kfactor->GetBinContent(ibin);
   double BinWidth = E214_BinWidth->GetBinContent(ibin);
   E214_kfactor->SetBinContent(ibin, kfactor * BinWidth);
 }

 GetWasymmetry(E225_NLO_tmp, E225_NLO);
 GetWasymmetry(E227_NLO_tmp, E227_NLO);
 GetWasymmetry(E234_NLO_tmp, E234_NLO);
 GetWasymmetry(E266_NLO_tmp, E266_NLO);
 GetWasymmetry(E267_NLO_tmp, E267_NLO);
 GetWasymmetry(E281_NLO_tmp, E281_NLO);
 GetWasymmetry(E225_w432_tmp, E225_w432);
 GetWasymmetry(E227_w432_tmp, E227_w432);
 GetWasymmetry(E234_w432_tmp, E234_w432);
 GetWasymmetry(E266_w432_tmp, E266_w432);
 GetWasymmetry(E267_w432_tmp, E267_w432);
 GetWasymmetry(E281_w432_tmp, E281_w432);
 GetWasymmetry(E225_w321_tmp, E225_w321);
 GetWasymmetry(E227_w321_tmp, E227_w321);
 GetWasymmetry(E234_w321_tmp, E234_w321);
 GetWasymmetry(E266_w321_tmp, E266_w321);
 GetWasymmetry(E267_w321_tmp, E267_w321);
 GetWasymmetry(E281_w321_tmp, E281_w321);

 UpdateKFactor("LHCb7ZWrap", "LHCb7ZWrap_up2025", E245_kfactor, 27);
 UpdateKFactor("LHCb8ZResKF", "LHCb8ZResKF_up2025", E246_kfactor, 16);
 UpdateKFactor("ATL7ZW", "ATL7ZW_up2025", E248_kfactor, 146);
 UpdateKFactor("CMS8Wxa", "CMS8Wxa_up2025", E249_kfactor, 25);
 UpdateKFactor("LHCb8WZ", "LHCb8WZ_up2025", E250_kfactor, 26);
 //UpdateKFactor("ATL8ZpT", "ATL8ZpT_up2025", E253_kfactor, 113);

 TH1D *E225_kfactor_wp, *E225_kfactor_wm;
 SeparateKFactor(E225_kfactor, E225_kfactor_wp, E225_kfactor_wm);
 UpdateKFactor("cdfLasy_up", "cdfLasy_up2025", E225_kfactor_wp, 11, E225_kfactor_wm, 12);

 TH1D *E227_kfactor_wp, *E227_kfactor_wm;
 SeparateKFactor(E227_kfactor, E227_kfactor_wp, E227_kfactor_wm);
 UpdateKFactor("cdfLasy2_up", "cdfLasy2_up2025", E227_kfactor_wp, 11, E227_kfactor_wm, 12);

 TH1D *E234_kfactor_wp, *E234_kfactor_wm;
 SeparateKFactor(E234_kfactor, E234_kfactor_wp, E234_kfactor_wm);
 UpdateKFactor("d02Masy1_up", "d02Masy1_up2025", E234_kfactor_wp, 11, E234_kfactor_wm, 12);

 UpdateKFactor("ZyD02a_up", "ZyD02a_up2025", E260_kfactor, 12);
 UpdateKFactor("ZyCDF2_up", "ZyCDF2_up2025", E261_kfactor, 21);

 TH1D *E266_kfactor_wp, *E266_kfactor_wm;
 SeparateKFactor(E266_kfactor, E266_kfactor_wp, E266_kfactor_wm);
 UpdateKFactor("CMS7Masy2_up", "CMS7Masy2_up2025", E266_kfactor_wp, 23, E266_kfactor_wm, 24);

 TH1D *E267_kfactor_wp, *E267_kfactor_wm;
 SeparateKFactor(E267_kfactor, E267_kfactor_wp, E267_kfactor_wm);
 UpdateKFactor("CMS7Easy_up", "CMS7Easy_up2025", E267_kfactor_wp, 11, E267_kfactor_wm, 12);

 TH1D *E281_kfactor_wp, *E281_kfactor_wm;
 SeparateKFactor(E281_kfactor, E281_kfactor_wp, E281_kfactor_wm);
 UpdateKFactor("d02Easy5_up", "d02Easy5_up2025", E281_kfactor_wp, 19, E281_kfactor_wm, 20);

// for(int ibin = 1; ibin <= E211_kfactor->GetNbinsX(); ibin++) E211_kfactor->SetBinContent(ibin, E211_kfactor->GetBinContent(ibin) * 0.5);
 for(int ibin = 1; ibin <= E211_kfactor->GetNbinsX(); ibin++) E211_kfactor->SetBinContent(ibin, E211_oldkfactor->GetBinContent(ibin) / 0.5);
 UpdateKFactor("ATL8W_new3", "ATL8W_new3_up2025", E211_kfactor, 53);
 UpdateKFactor("ATL8W_new3_Yao", "ATL8W_new3_up2025_Yao", E211_kfactor, 53);

 UpdateKFactor("CMS13Zmu_new2", "CMS13Zmu_new2_up2025", E212_kfactor, 20);
 UpdateKFactor("CMS13Zmu_new2_Yao", "CMS13Zmu_new2_up2025_Yao", E212_kfactor, 20);

 UpdateKFactor("LHCb13Zy2_Decom.data", "LHCb13Zy2_Decom.data_up2025", E218_kfactor, 24);
 UpdateKFactor("LHCb13Zy2_Decom.data_Yao", "LHCb13Zy2_Decom.data_up2025_Yao", E218_kfactor, 24);

 UpdateKFactor("ATL8Z3d", "ATL8Z3d_up2025", E214_kfactor, 286);
 UpdateKFactor("ATL8Z3d_Yao", "ATL8Z3d_up2025_Yao", E214_kfactor, 286);

 for(int ibin = 1; ibin <= E215_kfactor->GetNbinsX(); ibin++) E215_kfactor->SetBinContent(ibin, E215_kfactor->GetBinContent(ibin));// * 0.5);
 UpdateKFactor("ATL5WZunc.data", "ATL5WZunc.data_up2025", E215_kfactor, 9);
 UpdateKFactor("ATL5WZunc.data_Yao", "ATL5WZunc.data_up2025_Yao", E215_kfactor, 9);

 for(int ibin = 1; ibin <= E217_kfactor->GetNbinsX(); ibin++) E217_kfactor->SetBinContent(ibin, E217_kfactor->GetBinContent(ibin));// * 0.25);
 UpdateKFactor("LHCb8W_Lastm2.data", "LHCb8W_Lastm2.data_up2025", E217_kfactor, 10);
 UpdateKFactor("LHCb8W_Lastm2.data_Yao", "LHCb8W_Lastm2.data_up2025_Yao", E217_kfactor, 10);

 file->cd();

 E245_Data->Write();
 E245_NLO->Write("E245_NLO");
 E245_w432->Write("E245_w432");
 E245_w321->Write("E245_w321");
 E245_kfactor->Write();
 E245_oldkfactor->Write();

 E246_Data->Write();
 E246_NLO->Write("E246_NLO");
 E246_w432->Write("E246_w432");
 E246_w321->Write("E246_w321");
 E246_kfactor->Write();
 E246_oldkfactor->Write();

 E248_Data->Write();
 E248_NLO->Write("E248_NLO");
 E248_w432->Write("E248_w432");
 E248_w321->Write("E248_w321");
 E248_kfactor->Write();
 E248_oldkfactor->Write();

 E249_Data->Write();
 E249_NLO->Write("E249_NLO");
 E249_w432->Write("E249_w432");
 E249_w321->Write("E249_w321");
 E249_kfactor->Write();
 E249_oldkfactor->Write();

 E250_Data->Write();
 E250_NLO->Write("E250_NLO");
 E250_w432->Write("E250_w432");
 E250_w321->Write("E250_w321");
 E250_kfactor->Write();
 E250_oldkfactor->Write();

 /*E253_Data->Write();
 E253_NLO->Write("E253_NLO");
 E253_w432->Write("E253_w432");
 E253_kfactor->Write();
 E253_oldkfactor->Write();
 */

 E225_Data->Write();
 E225_NLO->Write("E225_NLO");
 E225_w432->Write("E225_w432");
 E225_w321->Write("E225_w321");
 E225_kfactor->Write();
 E225_oldkfactor->Write();

 E227_Data->Write();
 E227_NLO->Write("E227_NLO");
 E227_w432->Write("E227_w432");
 E227_w321->Write("E227_w321");
 E227_kfactor->Write();
 E227_oldkfactor->Write();

 E234_Data->Write();
 E234_NLO->Write("E234_NLO");
 E234_w432->Write("E234_w432");
 E234_w321->Write("E234_w321");
 E234_kfactor->Write();
 E234_oldkfactor->Write();

 E260_Data->Write();
 E260_NLO->Write("E260_NLO");
 E260_w432->Write("E260_w432");
 E260_w321->Write("E260_w321");
 E260_kfactor->Write();
 E260_oldkfactor->Write();

 E261_Data->Write();
 E261_NLO->Write("E261_NLO");
 E261_w432->Write("E261_w432");
 E261_w321->Write("E261_w321");
 E261_kfactor->Write();
 E261_oldkfactor->Write();

 E266_Data->Write();
 E266_NLO->Write("E266_NLO");
 E266_w432->Write("E266_w432");
 E266_w321->Write("E266_w321");
 E266_kfactor->Write();
 E266_oldkfactor->Write();

 E267_Data->Write();
 E267_NLO->Write("E267_NLO");
 E267_w432->Write("E267_w432");
 E267_w321->Write("E267_w321");
 E267_kfactor->Write();
 E267_oldkfactor->Write();

 E281_Data->Write();
 E281_NLO->Write("E281_NLO");
 E281_w432->Write("E281_w432");
 E281_w321->Write("E281_w321");
 E281_kfactor->Write();
 E281_oldkfactor->Write();

 E211_Data->Write();
 E211_NLO->Write("E211_NLO");
 E211_w432->Write("E211_w432");
 E211_w321->Write("E211_w321");
 E211_kfactor->Write();
 E211_oldkfactor->Write();

 E212_Data->Write();
 E212_NLO->Write("E212_NLO");
 E212_w432->Write("E212_w432");
 E212_w321->Write("E212_w321");
 E212_kfactor->Write();
 E212_oldkfactor->Write();

 E218_Data->Write();
 E218_NLO->Write("E218_NLO");
 E218_w432->Write("E218_w432");
 E218_w321->Write("E218_w321");
 E218_kfactor->Write();
 E218_oldkfactor->Write();

 E214_Data->Write();
 E214_NLO->Write("E214_NLO");
 E214_w432->Write("E214_w432");
 E214_w321->Write("E214_w321");
 E214_kfactor->Write();
 E214_oldkfactor->Write();

 E215_Data->Write();
 E215_NLO->Write("E215_NLO");
 E215_w432->Write("E215_w432");
 E215_w321->Write("E215_w321");
 E215_kfactor->Write();
 E215_oldkfactor->Write();

 E217_Data->Write();
 E217_NLO->Write("E217_NLO");
 E217_w432->Write("E217_w432");
 E217_w321->Write("E217_w321");
 E217_kfactor->Write();
 E217_oldkfactor->Write();

 file->Close();

 return 1;
}
