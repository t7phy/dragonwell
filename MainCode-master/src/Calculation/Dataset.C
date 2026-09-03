#include "Calculation/Dataset.h"

Dataset::Dataset()
{

}

Dataset::Dataset(TString name)
{
 m_name = name;
}

void Dataset::ReadFile(TString FileName, TString DataType, TString CalcMode, TString ColliderType, TString subType)
{
    this->DataType = DataType;
    this->CalcMode = CalcMode;
    this->ColliderType = ColliderType;
    this->subType = subType;
   
    cout<<LOG_INFO<<"Open file: "<<FileName<<endl;
    datafile.open(FileName, ios::in);

    int nHead = 3;
    if(subType == "H1FL10") nHead = 2; // Look at how special you are!

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
   
   
    if(DataType == "DrellYan"){
      ReadDYData(subType);
    }
    else if(DataType == "DIS"){
      ReadDISData(subType);
    }
    else if(DataType == "Jet"){
      ReadJetData(subType);
    }
    else{
      cout<<LOG_ERROR<<"Unknown data type!"<<endl;
      return;
    }
   
    NPoints = m_data.size();
    for(int i = 0; i < m_data.size(); i++){
      m_data.at(i).AppliedKFactorColumns = AppliedKFactorColumns;
    }

    isInitialize = true;
}

void Dataset::ReadDYData(TString subType)
{
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
      DataPoint p;

      int Ninfo;
      if(subType == "CommonDY" || subType == "ATL8Z3d"){
        p.data = FullTable.at(i).at(3);
        p.StatErr = FullTable.at(i).at(4);
        p.SysErr = FullTable.at(i).at(6);
        p.UnCorrErr = sqrt(p.StatErr * p.StatErr + p.SysErr * p.SysErr);

        Ninfo = 7;
      }
      if(subType == "ATL8ZpT"){
   
        double Qmax = FullTable.at(i).at(0);
        double QTmin = FullTable.at(i).at(1);
        double QTmax = FullTable.at(i).at(2);
   
        bool RemovePoint = (Qmax > VBPQmaxCut)
                        || (QTmin < VBPQTminCut)
                        || (QTmax > VBPQTmaxCut);
   
        if(RemovePoint) continue;
   
        p.data = FullTable.at(i).at(3);
        p.StatErr = FullTable.at(i).at(4);
        p.SysErr = FullTable.at(i).at(6);
        p.UnCorrErr = sqrt(p.StatErr * p.StatErr + p.SysErr * p.SysErr);

        p.variable1 = FullTable.at(i).at(0);
        p.variable2 = FullTable.at(i).at(1);
        p.variable3 = FullTable.at(i).at(2);
        p.variableTitle = "     Q       Ptmin      Ptmax        ";

        Ninfo = 7;
      }
      if(subType == "LHCb7ZWrap" || subType == "LHCb8Zeer" || subType == "LHCb8ZResKF" || subType == "ATL7ZW"){
        p.data = FullTable.at(i).at(3);
        p.StatErr = FullTable.at(i).at(4);
        p.SysErr = FullTable.at(i).at(6);
        p.UnCorrErr = sqrt(p.StatErr * p.StatErr + p.SysErr * p.SysErr);

        Ninfo = 8;
      }
      if(subType == "CMS8Wxa"){
        p.data = FullTable.at(i).at(3);
        p.StatErr = FullTable.at(i).at(4);
        p.SysErr = FullTable.at(i).at(6);
        p.UnCorrErr = sqrt(p.StatErr * p.StatErr + p.SysErr * p.SysErr);
        p.lob = FullTable.at(i).at(7);
        p.isAsymmetryData = true;

        Ninfo = 8;
      }
      if(subType == "LHCb8WZ"){
        p.data = FullTable.at(i).at(3);
        p.StatErr = FullTable.at(i).at(4);
        p.SysErr = FullTable.at(i).at(6);
        p.UnCorrErr = sqrt(p.StatErr * p.StatErr + p.SysErr * p.SysErr);
        p.lob = FullTable.at(i).at(7);
        p.BarnFactor = 1000.0;

        if(p.lob == 2) continue;

        Ninfo = 8;
      }

      if(subType == "e605"){

        double Qmax = FullTable.at(i).at(1);

        bool RemovePoint = (Qmax > VBPQmaxCut);

        if(RemovePoint) continue;

        p.y = FullTable.at(i).at(0);
        p.Q = FullTable.at(i).at(1);
        p.tau = FullTable.at(i).at(2) * FullTable.at(i).at(2);
        p.data = FullTable.at(i).at(3);
        p.StatErr = FullTable.at(i).at(4);
        p.SysErr = FullTable.at(i).at(6);
        p.UnCorrErr = sqrt(p.StatErr * p.StatErr + p.SysErr * p.SysErr);

        Ninfo = 7;
      }
      if(subType == "e866f" || subType == "e866f_up2025"){

        double Qmax = FullTable.at(i).at(1);

        bool RemovePoint = (Qmax > VBPQmaxCut);

        if(RemovePoint) continue;

        p.y = FullTable.at(i).at(0);
        p.Q = FullTable.at(i).at(1);
        p.xf = FullTable.at(i).at(2);
        p.data = FullTable.at(i).at(3);
        p.StatErr = FullTable.at(i).at(4);
        p.SysErr = FullTable.at(i).at(5);
        p.UnCorrErr = sqrt(p.StatErr * p.StatErr + p.SysErr * p.SysErr);

        Ninfo = 6;

        if(subType == "e866f_up2025"){
          p.noAdditionalKFactor = true;
          p.wp_kfac = FullTable.at(i).at(Ninfo + 1); // neutron kfactor
          p.wm_kfac = FullTable.at(i).at(Ninfo + 3); // proton kfactor
          p.wp_kfac0 = FullTable.at(i).at(Ninfo + 1); // neutron kfactor
          p.wm_kfac0 = FullTable.at(i).at(Ninfo + 3); // proton kfactor
        }
        else{
          p.wp_kfac = 1.0; // neutron kfactor
          p.wm_kfac = 1.0; // proton kfactor
          p.wp_kfac0 = 1.0; // neutron kfactor
          p.wm_kfac0 = 1.0; // proton kfactor
        }
      }
      if(subType == "e866ppxf" || subType == "e906aF" || subType == "e906aF_up2025"){

        double Qmax = FullTable.at(i).at(1);

        bool RemovePoint = (Qmax > VBPQmaxCut);

        if(RemovePoint) continue;

        p.y = FullTable.at(i).at(0);
        p.Q = FullTable.at(i).at(1);
        p.xf = FullTable.at(i).at(2);
        p.data = FullTable.at(i).at(3);
        p.StatErr = FullTable.at(i).at(4);
        p.SysErr = FullTable.at(i).at(6);
        p.UnCorrErr = sqrt(p.StatErr * p.StatErr + p.SysErr * p.SysErr);

        Ninfo = 7;

        if(subType == "e906aF_up2025"){
          p.noAdditionalKFactor = true;
          p.wp_kfac = FullTable.at(i).at(Ninfo + NCorr + 1); // neutron kfactor
          p.wm_kfac = FullTable.at(i).at(Ninfo + NCorr + 3); // proton kfactor
          p.wp_kfac0 = FullTable.at(i).at(Ninfo + NCorr + 1); // neutron kfactor
          p.wm_kfac0 = FullTable.at(i).at(Ninfo + NCorr + 3); // proton kfactor
        }
        else{
          p.wp_kfac = 1.0; // neutron kfactor
          p.wm_kfac = 1.0; // proton kfactor
          p.wp_kfac0 = 1.0; // neutron kfactor
          p.wm_kfac0 = 1.0; // proton kfactor
        }
      }
      if(subType == "cdfLasy" || subType == "cdfLasy2" || subType == "d02Masy1" || subType == "CMS7Easy"){

        p.y = FullTable.at(i).at(0);
        p.Ptmin = FullTable.at(i).at(1);
        p.Ptmax = FullTable.at(i).at(2);
        p.data = FullTable.at(i).at(3);
        p.StatErr = FullTable.at(i).at(4);
        p.SysErr = FullTable.at(i).at(5);
        p.UnCorrErr = sqrt(p.StatErr * p.StatErr + p.SysErr * p.SysErr);

        if(FullTable.at(i).size() == 10){ // original CT18, use CT DY routine
          p.wp_kfac = FullTable.at(i).at(8);
          p.wm_kfac = FullTable.at(i).at(9);
          p.wp_kfac0 = FullTable.at(i).at(8);
          p.wm_kfac0 = FullTable.at(i).at(9);
        }
        else{ // xxx_up, use APPLgrid
          p.wp_kfac = FullTable.at(i).at(11);
          p.wm_kfac = FullTable.at(i).at(12);
          p.wp_kfac0 = FullTable.at(i).at(11);
          p.wm_kfac0 = FullTable.at(i).at(12);
        }

        Ninfo = 10;
      }
      if(subType == "ZyD02a" || subType == "ZyD02a_up" || subType == "ZyCDF2" || subType == "ZyCDF2_up"){

        p.y = FullTable.at(i).at(0);
        p.Q = FullTable.at(i).at(1);
        p.data = FullTable.at(i).at(3);
        p.StatErr = FullTable.at(i).at(4);
        p.SysErr = FullTable.at(i).at(6);
        p.UnCorrErr = sqrt(p.StatErr * p.StatErr + p.SysErr * p.SysErr);

        if(subType == "ZyD02a_up" || subType == "ZyCDF2_up") p.BarnFactor = 1000.0;

        Ninfo = 7;
      }
      if(subType == "CMS7Masy2" || subType == "ATL7_WZ" || subType == "ATL7_WZ_up" || subType == "d02Easy5"){

        p.y = FullTable.at(i).at(0);
        p.Ptmin = FullTable.at(i).at(1);
        p.Ptmax = FullTable.at(i).at(2);
        p.BR = FullTable.at(i).at(2);
        p.data = FullTable.at(i).at(3);
        p.StatErr = FullTable.at(i).at(4);
        p.SysErr = FullTable.at(i).at(6);
        p.lob = FullTable.at(i).at(7);
        p.UnCorrErr = sqrt(p.StatErr * p.StatErr + p.SysErr * p.SysErr);
        Ninfo = 8;

        if(subType == "ATL7_WZ_up" && p.lob != 2) p.BarnFactor = 1000.0;

        if(FullTable.at(i).size() == (Ninfo + NCorr + 3 + 1)){ // original CT18, use CT DY routine
          p.wp_kfac = FullTable.at(i).at(Ninfo + NCorr + 2);
          p.wm_kfac = FullTable.at(i).at(Ninfo + NCorr + 3);
          p.wp_kfac0 = FullTable.at(i).at(Ninfo + NCorr + 2);
          p.wm_kfac0 = FullTable.at(i).at(Ninfo + NCorr + 3);
        }
        else{ // xxx_up, use APPLgrid
          p.wp_kfac = FullTable.at(i).at(Ninfo + NCorr + 5);
          p.wm_kfac = FullTable.at(i).at(Ninfo + NCorr + 6);
          p.wp_kfac0 = FullTable.at(i).at(Ninfo + NCorr + 5);
          p.wm_kfac0 = FullTable.at(i).at(Ninfo + NCorr + 6);
        }

        if(p.lob == 2){// W asymmetry
                       // K Factors for W+/W- have already been saved in wp_kfac and wm_kfac
                       // Reset them to 1.0 for further applying to the prediction (in GetPrediction())

          if(FullTable.at(i).size() == (Ninfo + NCorr + 3 + 1)){ // original CT18, use CT DY routine
            FullTable.at(i).at(Ninfo + NCorr + 2) = 1.0;
            FullTable.at(i).at(Ninfo + NCorr + 3) = 1.0;
          }
          else{ // xxx_up, use APPLgrid
            FullTable.at(i).at(Ninfo + NCorr + 5) = 1.0;
            FullTable.at(i).at(Ninfo + NCorr + 6) = 1.0;
          }
        }
      }

      p.Param = Param;
      p.CorrErrs.resize(NCorr);
      p.KFactors.resize(FullTable.at(i).size() - NCorr - Ninfo);
      p.NKFactor = p.KFactors.size();
   
      for(int j = 0; j < NCorr; j++){
        p.CorrErrs(j) = FullTable.at(i).at(j + Ninfo) / 100.0;
      }
      for(int j = 0; j < p.KFactors.size(); j++){
        p.KFactors(j) = FullTable.at(i).at(j + NCorr + Ninfo);
      }
   
      p.FindInfo(subType);
      p.subType = subType;
      p.DataType = this->DataType;
      p.ColliderType = this->ColliderType;
      p.CalcMode = this->CalcMode;
      p.origindata = p.data;
      if(p.variableTitle == ""){
        p.variable1 = FullTable.at(i).at(0);
        p.variable2 = FullTable.at(i).at(1);
        p.variable3 = Param.at(0);
        p.variableTitle = "     Y         Q         Rs          ";
      }
      if(isNormFit) p.Normalization = Normalization;

      m_data.push_back(p);
    }

}

void Dataset::ReadDISData(TString subType)
{
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
      DataPoint p;

      int Ninfo;
      if(subType == "HERAIpII"){

        p.x = FullTable.at(i).at(0);
        p.Q2 = FullTable.at(i).at(1);
        p.y = FullTable.at(i).at(2);

        double Q = sqrt(p.Q2);
        double W = sqrt(p.Q2 * (-1.0) + 1.0 + p.Q2 / p.x);

        bool RemovePoint = (Q >= DISQmaxCut)
                        || (Q <= DISQminCut)
                        || (W <= DISWCut);

        if(RemovePoint) continue;

        p.data = FullTable.at(i).at(3);
        p.StatErr = FullTable.at(i).at(4);
        p.SysErr = FullTable.at(i).at(6);
        p.lob = FullTable.at(i).at(7);
        p.UnCorrErr = sqrt(p.StatErr * p.StatErr + p.SysErr * p.SysErr);

        Ninfo = 8;
      }

      if(subType == "BcdF2pCor" || subType == "BcdF2dCor" || subType == "NmcRatCor" || subType == "ccfrf2.mi" || subType == "NuTvNuChXN" || subType == "NuTvNbChXN"
      || subType == "CcfrNuChXN" || subType == "CcfrNbChXN" || subType == "Hn+9900x0b" || subType == "Hn1X0c" || subType == "H1FL10" || subType == "Hn1X0ccom" || subType == "Hn1X0bcom"
      || subType == "CommonF2" || subType == "CommonFL"){
        p.x = FullTable.at(i).at(0);
        p.Q2 = FullTable.at(i).at(1);

        if(subType == "NuTvNuChXN" || subType == "NuTvNbChXN" || subType == "CcfrNuChXN" || subType == "CcfrNbChXN" || subType == "Hn+9900x0b" || subType == "Hn1X0c"
        || subType == "Hn1X0ccom" || subType == "Hn1X0bcom"){
          p.y = FullTable.at(i).at(2);
        }

        double Q = sqrt(p.Q2);
        double W = sqrt(p.Q2 * (-1.0) + 1.0 + p.Q2 / p.x);

        bool RemovePoint = (Q >= DISQmaxCut)
                        || (Q <= DISQminCut)
                        || (W <= DISWCut);

        if(RemovePoint) continue;

        p.data = FullTable.at(i).at(3);
        p.StatErr = FullTable.at(i).at(4);
        p.SysErr = FullTable.at(i).at(6);
        p.UnCorrErr = sqrt(p.StatErr * p.StatErr + p.SysErr * p.SysErr);

        Ninfo = 7;
      }

      if(subType == "cdhswf2" || subType == "cdhswf3" || subType == "ccfrf3.md"){
        p.x = FullTable.at(i).at(0);
        p.Q2 = FullTable.at(i).at(1);

        double Q = sqrt(p.Q2);
        double W = sqrt(p.Q2 * (-1.0) + 1.0 + p.Q2 / p.x);

        bool RemovePoint = (Q >= DISQmaxCut)
                        || (Q <= DISQminCut)
                        || (W <= DISWCut);

        if(RemovePoint) continue;

        p.data = FullTable.at(i).at(3);
        p.StatErr = FullTable.at(i).at(4);
        p.UnCorrErr = sqrt(p.StatErr * p.StatErr + p.SysErr * p.SysErr);

        Ninfo = 6;
      }

      p.Param = Param;
      p.CorrErrs.resize(NCorr);
      p.KFactors.resize(FullTable.at(i).size() - NCorr - Ninfo);
      p.NKFactor = p.KFactors.size();

      for(int j = 0; j < NCorr; j++){
        p.CorrErrs(j) = FullTable.at(i).at(j + Ninfo) / 100.0;
      }
      for(int j = 0; j < p.KFactors.size(); j++){
        p.KFactors(j) = FullTable.at(i).at(j + NCorr + Ninfo);
      }

      p.FindInfo(subType);
      p.subType = subType;
      p.DataType = this->DataType;
      p.ColliderType = this->ColliderType;
      p.CalcMode = this->CalcMode;
      p.origindata = p.data;
      p.variable1 = sqrt(p.Q2);
      p.variable2 = p.x;
      p.variable3 = p.y;
      p.variableTitle = "     Q          x         y          ";
      if(isNormFit) p.Normalization = Normalization;

      m_data.push_back(p);
    }

}

void Dataset::ReadJetData(TString subType)
{
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
      DataPoint p;

      int Ninfo;
      if(subType == "CommonJet" || subType == "CommonJet1000" || subType == "CommonJet1000NNLO" || subType == "CMS13lj21mtt_HTO2"){
        p.data = FullTable.at(i).at(3);
        p.StatErr = FullTable.at(i).at(4);
        p.SysErr = FullTable.at(i).at(6);
        p.UnCorrErr = sqrt(p.StatErr * p.StatErr + p.SysErr * p.SysErr);

        if(subType == "CMS13lj21mtt_HTO2") p.BarnFactor = 0.2877; // Branching for ttbar->lep+jets

        if(subType == "CommonJet1000" || subType == "CommonJet1000NNLO") p.BarnFactor = 1000.0;

        Ninfo = 7;
      }
      if(subType == "CMS7jtR7y6" || subType == "CMS7jtR7y6_v1" || subType == "CMS8jtR7" || subType == "CMS8jtR7_v1" || subType == "CMS8pTtyt" || subType == "ATL8ttcoma"){
        p.data = FullTable.at(i).at(3);
        p.StatErr = FullTable.at(i).at(4);
        p.SysErr = FullTable.at(i).at(6);
        p.UnCorrErr = sqrt(p.StatErr * p.StatErr + p.SysErr * p.SysErr);

        Ninfo = 7;
      }
      if(subType == "ATL7jtR6u"){
        p.data = FullTable.at(i).at(3);
        p.StatErr = FullTable.at(i).at(4);
        p.SysErr = FullTable.at(i).at(6);
        p.UnCorrErr = sqrt(p.StatErr * p.StatErr + p.SysErr * p.SysErr);
        p.BarnFactor = 1000.0;

        Ninfo = 7;
      }
      if(subType == "cdf2jtCor2" || subType == "d02jtCor2"){
        p.data = FullTable.at(i).at(3);
        p.StatErr = FullTable.at(i).at(4);
        p.SysErr = FullTable.at(i).at(6);
        p.UnCorrErr = sqrt(p.StatErr * p.StatErr + p.SysErr * p.SysErr);
        p.isOldFNLOFormat = true;
        if(subType == "d02jtCor2") p.BarnFactor = 0.001;

        Ninfo = 7;
      }

      p.Param = Param;
      p.CorrErrs.resize(NCorr);
      p.KFactors.resize(FullTable.at(i).size() - NCorr - Ninfo);
      p.NKFactor = p.KFactors.size();

      for(int j = 0; j < NCorr; j++){
        p.CorrErrs(j) = FullTable.at(i).at(j + Ninfo) / 100.0;
      }
      for(int j = 0; j < p.KFactors.size(); j++){
        p.KFactors(j) = FullTable.at(i).at(j + NCorr + Ninfo);
      }

      p.FindInfo(subType);
      p.subType = subType;
      p.DataType = this->DataType;
      p.ColliderType = this->ColliderType;
      p.CalcMode = this->CalcMode;
      p.origindata = p.data;
      if(p.variableTitle == ""){
        p.variable1 = FullTable.at(i).at(0);
        p.variable2 = FullTable.at(i).at(1);
        p.variable3 = FullTable.at(i).at(2);
        p.variableTitle = " variable1    variable2   variable3  ";
      }
      if(isNormFit) p.Normalization = Normalization;

      m_data.push_back(p);
    }

}

void Dataset::InitialPrediction(Config setting)
{
 PDFType = setting.PDFType;

 m_calculation = new Prediction();

 if(CalcMode == "ApplGrid"){
   //m_calculation->ApplGridHelper::InitialPDFbyHand(m_pdf);
   //m_calculation->ApplGridHelper::InitialCTEQPDF("i2Tn3.00.pds");

   m_applgrid.resize(GridNames.size());
   for(int i = 0; i < GridNames.size(); i++){
     m_applgrid.at(i) = new ApplGridHelper();
     m_applgrid.at(i)->SetNfTotal(setting.Nflv);
     m_applgrid.at(i)->SetPoleMasscbt(setting.mc, setting.mb, setting.mt);
     if(subType == "ATL8ZpT") m_applgrid.at(i)->SetCut(setting.VBPQTminCut, setting.VBPQTmaxCut);
     if(subType == "LHCb8WZ"){
       if(GridNames.at(0).Contains("250_1_KP_2018.1010.root")){
         for(int ipoint = 0; ipoint < m_data.size(); ipoint++){
           m_data.at(ipoint).BarnFactor = 250.0;
         }
       }
     }

     m_applgrid.at(i)->ApplGridHelper::InitialGrid(GridNames.at(i));

     if(subType.Contains("NNLO")) m_applgrid.at(i)->SetNNLO();

     if(setting.PDFType == "CTEQ") m_applgrid.at(i)->ApplGridHelper::InitialCTEQPDF(setting.m_cteqpdf);
     if(setting.PDFType == "LHAPDF") m_applgrid.at(i)->ApplGridHelper::InitialPDF(setting.PDFName, setting.iSet);
   }
 }
 else if(CalcMode == "FastNLO"){
   m_fnlo.resize(FNLOTableNames.size());
   if(!m_data.at(0).isOldFNLOFormat){
     for(int i = 0; i < FNLOTableNames.size(); i++){
       m_fnlo.at(i) = new FastNLOHelper(FNLOTableNames.at(i));
       m_fnlo.at(i)->SetNfTotal(setting.Nflv);
       m_fnlo.at(i)->SetPoleMasscbt(setting.mc, setting.mb, setting.mt);
       if(setting.PDFType == "CTEQ") m_fnlo.at(i)->FastNLOHelper::InitialCTEQPDF(setting.m_cteqpdf);
       if(setting.PDFType == "LHAPDF") m_fnlo.at(i)->FastNLOHelper::InitialPDF(setting.PDFName, setting.iSet);
       m_fnlo.at(i)->SetContributionON(fastNLO::kFixedOrder,1,true);
       m_fnlo.at(i)->SetContributionON(fastNLO::kFixedOrder,2,true);
       m_fnlo.at(i)->SetScaleFactorsMuRMuF(1.0, 1.0);
       m_fnlo.at(i)->CalcCrossSection();
       //m_fnlo.at(i)->FastNLOHelper::SetFilename(FNLOTableName);
     }
   }
   else{
     for(int i = 0; i < FNLOTableNames.size(); i++){
       m_fnlo.at(i) = new FastNLOHelper();
       m_fnlo.at(i)->SetNfTotal(setting.Nflv);
       m_fnlo.at(i)->SetPoleMasscbt(setting.mc, setting.mb, setting.mt);
       m_fnlo.at(i)->FT2007RD(FNLOTableNames.at(i));
       if(setting.PDFType == "CTEQ") m_fnlo.at(i)->FastNLOHelper::InitialCTEQPDF(setting.m_cteqpdf);
       if(setting.PDFType == "LHAPDF") m_fnlo.at(i)->FastNLOHelper::InitialPDF(setting.PDFName, setting.iSet);
     }
   }
 }
 else if(CalcMode == "PineAPPL"){
   m_pineappl.resize(PineAPPLGridNames.size());
   for(int i = 0; i < PineAPPLGridNames.size(); i++){
     m_pineappl.at(i) = new PineAPPLHelper();
     m_pineappl.at(i)->SetNfTotal(setting.Nflv);
     m_pineappl.at(i)->SetPoleMasscbt(setting.mc, setting.mb, setting.mt);
     if(setting.PDFType == "CTEQ") m_pineappl.at(i)->InitialCTEQPDF(setting.m_cteqpdf);
     if(setting.PDFType == "LHAPDF") m_pineappl.at(i)->InitialPDF(setting.PDFName, setting.iSet);
     m_pineappl.at(i)->InitialGrid(PineAPPLGridNames.at(i));
   }
 }
 else if(CalcMode == "CTEQ"){
   //m_calculation->CalcDIS::InitialPDFbyHand(m_pdf);
   //m_calculation->CalcDIS::InitialCTEQPDF("i2Tn3.00.pds");
   m_calculation->CalcDIS::SetNfTotal(setting.Nflv);
   m_calculation->CalcDIS::SetPoleMasscbt(setting.mc, setting.mb, setting.mt);
   m_calculation->CalcDIS::SetEvolveOrder(setting.IorEvl);
   m_calculation->CalcDIS::SetAlphaSOrder(setting.IorQCD);
   if(setting.PDFType == "CTEQ") m_calculation->CalcDIS::InitialCTEQPDF(setting.m_cteqpdf);
   if(setting.PDFType == "LHAPDF") m_calculation->CalcDIS::InitialPDF(setting.PDFName, setting.iSet);
   if(m_calculation->doCalcN3LODIS) m_calculation->CalcDIS::InitializeHoppetSF();
   m_calculation->CalcDIS::InitializeData(setting, m_data);
 }
 else if(CalcMode == "CTEQ_DY"){
   //m_calculation->CalcVBP::InitialPDFbyHand(m_pdf);
   //m_calculation->CalcVBP::InitialCTEQPDF("i2Tn3.00.pds");
   m_calculation->CalcVBP::SetNfTotal(setting.Nflv);
   m_calculation->CalcVBP::SetPoleMasscbt(setting.mc, setting.mb, setting.mt);
   if(setting.PDFType == "CTEQ") m_calculation->CalcVBP::InitialCTEQPDF(setting.m_cteqpdf);
   if(setting.PDFType == "LHAPDF") m_calculation->CalcVBP::InitialPDF(setting.PDFName, setting.iSet);
   m_calculation->CalcVBP::InitializeData(setting, m_data);
 }
 else if(CalcMode == "NULL"){
   return;
 }
 else{
   cout<<LOG_ERROR<<"Unknown Calculation Mode!"<<endl;
   return;
 }

 //cout<<"Initialize done."<<endl;
}

void Dataset::InitialPDF(Config setting)
{
 if(CalcMode == "ApplGrid"){
   for(int i = 0; i < GridNames.size(); i++){
     if(setting.PDFType == "CTEQ") m_applgrid.at(i)->ApplGridHelper::InitialCTEQPDF(setting.m_cteqpdf);
     if(setting.PDFType == "LHAPDF") m_applgrid.at(i)->ApplGridHelper::InitialPDF(setting.PDFName, setting.iSet);
   }
 }
 else if(CalcMode == "FastNLO"){
   for(int i = 0; i < FNLOTableNames.size(); i++){
     if(setting.PDFType == "CTEQ") m_fnlo.at(i)->FastNLOHelper::InitialCTEQPDF(setting.m_cteqpdf);
     if(setting.PDFType == "LHAPDF") m_fnlo.at(i)->FastNLOHelper::InitialPDF(setting.PDFName, setting.iSet);
   }
 }
 else if(CalcMode == "PineAPPL"){
   for(int i = 0; i < PineAPPLGridNames.size(); i++){
     if(setting.PDFType == "CTEQ") m_pineappl.at(i)->InitialCTEQPDF(setting.m_cteqpdf);
     if(setting.PDFType == "LHAPDF") m_pineappl.at(i)->InitialPDF(setting.PDFName, setting.iSet);
   }
 }
 else if(CalcMode == "CTEQ"){
   if(setting.PDFType == "CTEQ") m_calculation->CalcDIS::InitialCTEQPDF(setting.m_cteqpdf);
   if(setting.PDFType == "LHAPDF") m_calculation->CalcDIS::InitialPDF(setting.PDFName, setting.iSet);
 }
 else if(CalcMode == "CTEQ_DY"){
   if(setting.PDFType == "CTEQ") m_calculation->CalcVBP::InitialCTEQPDF(setting.m_cteqpdf);
   if(setting.PDFType == "LHAPDF") m_calculation->CalcVBP::InitialPDF(setting.PDFName, setting.iSet);
 }

}

void Dataset::SubmitApplGridJobs()
{
 if(CalcMode == "ApplGrid"){
   if(ColliderType == "LHC"){
     m_appl_xsec.clear();
     threadAPPL.clear();
     for(int igrid = 0; igrid < GridNames.size(); igrid++){
       pthread_create(&threadAPPL[igrid], NULL, ThreadRunAppl, m_applgrid.at(igrid));
     }
   }
   if(ColliderType == "Tev"){
     m_appl_xsec.clear();
     threadAPPL.clear();
     for(int igrid = 0; igrid < GridNames.size(); igrid++){
       pthread_create(&threadAPPL[igrid], NULL, ThreadRunApplppbar, m_applgrid.at(igrid));
     }
   }
 }
}

void Dataset::WaitApplGridJobs()
{
 if(CalcMode == "ApplGrid"){
   if(ColliderType == "LHC"){
     for(auto iter = m_appl_xsec.begin(); iter != m_appl_xsec.end(); iter++){
       iter->second.clear();
     }
     m_appl_xsec.clear();
     for(int igrid = 0; igrid < GridNames.size(); igrid++){
       pthread_join(threadAPPL[igrid], NULL);
       m_appl_xsec[igrid] = m_applgrid.at(igrid)->appl_xsec;
     }
   }
   if(ColliderType == "Tev"){
     for(auto iter = m_appl_xsec.begin(); iter != m_appl_xsec.end(); iter++){
       iter->second.clear();
     }
     m_appl_xsec.clear();
     for(int igrid = 0; igrid < GridNames.size(); igrid++){
       pthread_join(threadAPPL[igrid], NULL);
       m_appl_xsec[igrid] = m_applgrid.at(igrid)->appl_xsec;
     }
   }
 }
}

void Dataset::SubmitPineAPPLJobs()
{
 if(CalcMode == "PineAPPL"){
   if(ColliderType == "LHC"){
     m_pineappl_xsec.clear();
     threadPineAPPL.clear();
     for(int igrid = 0; igrid < PineAPPLGridNames.size(); igrid++){
       pthread_create(&threadPineAPPL[igrid], NULL, ThreadRunPineAPPL, m_pineappl.at(igrid));
     }
   }
   if(ColliderType == "Tev"){
     m_pineappl_xsec.clear();
     threadPineAPPL.clear();
     for(int igrid = 0; igrid < PineAPPLGridNames.size(); igrid++){
       pthread_create(&threadPineAPPL[igrid], NULL, ThreadRunPineAPPLppbar, m_pineappl.at(igrid));
     }
   }
 }
}

void Dataset::WaitPineAPPLJobs()
{
 if(CalcMode == "PineAPPL"){
   if(ColliderType == "LHC"){
     for(auto iter = m_pineappl_xsec.begin(); iter != m_pineappl_xsec.end(); iter++){
       iter->second.clear();
     }
     m_pineappl_xsec.clear();
     for(int igrid = 0; igrid < PineAPPLGridNames.size(); igrid++){
       pthread_join(threadPineAPPL[igrid], NULL);
       m_pineappl_xsec[igrid] = m_pineappl.at(igrid)->results;
     }
   }
   if(ColliderType == "Tev"){
     for(auto iter = m_pineappl_xsec.begin(); iter != m_pineappl_xsec.end(); iter++){
       iter->second.clear();
     }
     m_pineappl_xsec.clear();
     for(int igrid = 0; igrid < PineAPPLGridNames.size(); igrid++){
       pthread_join(threadPineAPPL[igrid], NULL);
       m_pineappl_xsec[igrid] = m_pineappl.at(igrid)->results;
     }
   }
 }
}

void Dataset::GetPrediction()
{
 if(CalcMode == "ApplGrid"){
   if(ColliderType == "LHC"){
     m_theory.clear();
     m_corrected_data.clear();
     for(int igrid = 0; igrid < GridNames.size(); igrid++){
       vector<double> xsec;
       if(PDFType == "LHAPDF"){
         m_applgrid.at(igrid)->ApplGridHelper::DefaultConvoluteMacro(GridNames.at(igrid), xsec);
         //cout<<getTime()<<" convolute for "<<GridNames.at(igrid)<<endl;
       }
       else{
         xsec = m_appl_xsec[igrid];
       }

       int FirstBin, LastBin;
       if(ApplGridRange.at(igrid).at(0) < 0) FirstBin = 0;
       else FirstBin = ApplGridRange.at(igrid).at(0) - 1;

       if(ApplGridRange.at(igrid).at(1) < 0) LastBin = xsec.size() - 1;
       else LastBin = ApplGridRange.at(igrid).at(1) - 1;

       if(FirstBin < 0 || LastBin >= xsec.size()){
         cout<<"Range setup is from 1 (out of range). igrid = "<<igrid + 1<<" FirstBin = "<<ApplGridRange.at(igrid).at(0)<<" LastBin = "<<ApplGridRange.at(igrid).at(1)<<" nBins = "<<xsec.size()<<endl;
         return;
       }

       for(int i = FirstBin; i <= LastBin; i++){
         m_theory.push_back(xsec.at(i));
       }
     }

     if(m_data.at(0).isAsymmetryData){
       for(int i = 0; i < m_theory.size() / 2; i++){// For matching data size
         m_theory.push_back(m_theory.at(i));
       }
     }

     if(subType == "CMS7Easy"){
       vector<double> tmp_theory;
       for(int i = 0; i < 7; i++) tmp_theory.push_back(m_theory.at(i));
       for(int i = 8; i < 19; i++) tmp_theory.push_back(m_theory.at(i));
       for(int i = 20; i < 24; i++) tmp_theory.push_back(m_theory.at(i));
       m_theory.clear();
       m_theory = tmp_theory;
     }

     if(subType == "ATL8Z3d"){
       vector<double> tmp_theory;
       for(int i = 2; i < 4; i++) tmp_theory.push_back(m_theory.at(i));
       for(int i = 8; i < 10; i++) tmp_theory.push_back(m_theory.at(i));
       for(int i = 14; i < 16; i++) tmp_theory.push_back(m_theory.at(i));
       for(int i = 20; i < 22; i++) tmp_theory.push_back(m_theory.at(i));
       for(int i = 26; i < 28; i++) tmp_theory.push_back(m_theory.at(i));
       for(int i = 32; i < 34; i++) tmp_theory.push_back(m_theory.at(i));
       for(int i = 38; i < 40; i++) tmp_theory.push_back(m_theory.at(i));
       for(int i = 44; i < 46; i++) tmp_theory.push_back(m_theory.at(i));
       for(int i = 50; i < 52; i++) tmp_theory.push_back(m_theory.at(i));
       for(int i = 73; i < 77; i++) tmp_theory.push_back(m_theory.at(i));
       for(int i = 79; i < 83; i++) tmp_theory.push_back(m_theory.at(i));
       for(int i = 85; i < 89; i++) tmp_theory.push_back(m_theory.at(i));
       for(int i = 91; i < 95; i++) tmp_theory.push_back(m_theory.at(i));
       for(int i = 97; i < 101; i++) tmp_theory.push_back(m_theory.at(i));
       for(int i = 103; i < 107; i++) tmp_theory.push_back(m_theory.at(i));
       for(int i = 109; i < 113; i++) tmp_theory.push_back(m_theory.at(i));
       for(int i = 116; i < 118; i++) tmp_theory.push_back(m_theory.at(i));
       for(int i = 122; i < 124; i++) tmp_theory.push_back(m_theory.at(i));
       for(int i = 128; i < 130; i++) tmp_theory.push_back(m_theory.at(i));
       for(int i = 145; i < 149; i++) tmp_theory.push_back(m_theory.at(i));
       for(int i = 151; i < 155; i++) tmp_theory.push_back(m_theory.at(i));
       for(int i = 157; i < 161; i++) tmp_theory.push_back(m_theory.at(i));
       for(int i = 163; i < 167; i++) tmp_theory.push_back(m_theory.at(i));
       for(int i = 169; i < 173; i++) tmp_theory.push_back(m_theory.at(i));
       for(int i = 175; i < 179; i++) tmp_theory.push_back(m_theory.at(i));
       for(int i = 181; i < 185; i++) tmp_theory.push_back(m_theory.at(i));
       for(int i = 188; i < 190; i++) tmp_theory.push_back(m_theory.at(i));
       for(int i = 194; i < 196; i++) tmp_theory.push_back(m_theory.at(i));
       for(int i = 200; i < 202; i++) tmp_theory.push_back(m_theory.at(i));
       for(int i = 217; i < 221; i++) tmp_theory.push_back(m_theory.at(i));
       for(int i = 223; i < 227; i++) tmp_theory.push_back(m_theory.at(i));
       for(int i = 229; i < 233; i++) tmp_theory.push_back(m_theory.at(i));
       for(int i = 235; i < 239; i++) tmp_theory.push_back(m_theory.at(i));
       for(int i = 241; i < 245; i++) tmp_theory.push_back(m_theory.at(i));
       for(int i = 247; i < 251; i++) tmp_theory.push_back(m_theory.at(i));
       for(int i = 253; i < 257; i++) tmp_theory.push_back(m_theory.at(i));
       for(int i = 260; i < 262; i++) tmp_theory.push_back(m_theory.at(i));
       for(int i = 266; i < 268; i++) tmp_theory.push_back(m_theory.at(i));
       for(int i = 272; i < 274; i++) tmp_theory.push_back(m_theory.at(i));
       for(int i = 289; i < 293; i++) tmp_theory.push_back(m_theory.at(i));
       for(int i = 295; i < 299; i++) tmp_theory.push_back(m_theory.at(i));
       for(int i = 301; i < 305; i++) tmp_theory.push_back(m_theory.at(i));
       for(int i = 307; i < 311; i++) tmp_theory.push_back(m_theory.at(i));
       for(int i = 313; i < 317; i++) tmp_theory.push_back(m_theory.at(i));
       for(int i = 319; i < 323; i++) tmp_theory.push_back(m_theory.at(i));
       for(int i = 325; i < 329; i++) tmp_theory.push_back(m_theory.at(i));
       for(int i = 332; i < 334; i++) tmp_theory.push_back(m_theory.at(i));
       for(int i = 338; i < 340; i++) tmp_theory.push_back(m_theory.at(i));
       for(int i = 344; i < 346; i++) tmp_theory.push_back(m_theory.at(i));
       for(int i = 361; i < 365; i++) tmp_theory.push_back(m_theory.at(i));
       for(int i = 367; i < 371; i++) tmp_theory.push_back(m_theory.at(i));
       for(int i = 373; i < 377; i++) tmp_theory.push_back(m_theory.at(i));
       for(int i = 379; i < 383; i++) tmp_theory.push_back(m_theory.at(i));
       for(int i = 385; i < 389; i++) tmp_theory.push_back(m_theory.at(i));
       for(int i = 391; i < 395; i++) tmp_theory.push_back(m_theory.at(i));
       for(int i = 397; i < 401; i++) tmp_theory.push_back(m_theory.at(i));
       for(int i = 404; i < 406; i++) tmp_theory.push_back(m_theory.at(i));
       for(int i = 410; i < 412; i++) tmp_theory.push_back(m_theory.at(i));
       for(int i = 416; i < 418; i++) tmp_theory.push_back(m_theory.at(i));

       m_theory.clear();
       m_theory = tmp_theory;
     }

     if(subType == "CMS7Masy2" || subType == "CMS7Easy"){
       vector<double> asymmetry;
       int nbin = m_theory.size();
       for(int i = 0; i < m_data.size(); i++){
         double WPlus = m_theory.at(i);
         double WMinus = m_theory.at(nbin / 2 + i);
         WPlus *= m_data.at(i).wp_kfac;
         WMinus *= m_data.at(i).wm_kfac;
         asymmetry.push_back((WPlus - WMinus) / (WPlus + WMinus));
       }
       m_theory.clear();
       m_theory = asymmetry;
     }

     if(subType == "ATL7_WZ_up"){// yfu2025.3.19 Wrong!!!!! We shouldn't include the W asymmetry data to the chi2.
       for(int i = 0; i < 11; i++){
         double WPlus = m_theory.at(19 + i);
         double WMinus = m_theory.at(i);
         WPlus *= m_data.at(i + 30).wp_kfac;
         WMinus *= m_data.at(i + 30).wm_kfac;
         m_theory.push_back((WPlus - WMinus) / (WPlus + WMinus));
       }
     }
   }
   if(ColliderType == "Tev"){
     m_theory.clear();
     m_corrected_data.clear();
     for(int igrid = 0; igrid < GridNames.size(); igrid++){
       vector<double> xsec;
       if(PDFType == "LHAPDF"){
         m_applgrid.at(igrid)->ApplGridHelper::DefaultConvoluteppbarMacro(GridNames.at(igrid), xsec);
         //cout<<getTime()<<" convolute for "<<GridNames.at(igrid)<<endl;
       }
       else{
         xsec = m_appl_xsec[igrid];
       }

       int FirstBin, LastBin;
       if(ApplGridRange.at(igrid).at(0) < 0) FirstBin = 0;
       else FirstBin = ApplGridRange.at(igrid).at(0) - 1;

       if(ApplGridRange.at(igrid).at(1) < 0) LastBin = xsec.size() - 1;
       else LastBin = ApplGridRange.at(igrid).at(1) - 1;

       if(FirstBin < 0 || LastBin >= xsec.size()){
         cout<<"Range setup is from 1 (out of range). igrid = "<<igrid + 1<<" FirstBin = "<<ApplGridRange.at(igrid).at(0)<<" LastBin = "<<ApplGridRange.at(igrid).at(1)<<" nBins = "<<xsec.size()<<endl;
         return;
       }

       for(int i = FirstBin; i <= LastBin; i++){
         m_theory.push_back(xsec.at(i));
       }
     }

     if(m_data.at(0).isAsymmetryData){
       for(int i = 0; i < m_theory.size() / 2; i++){// For matching data size
         m_theory.push_back(m_theory.at(i));
       }
     }

     if(subType == "cdfLasy" || subType == "cdfLasy2" || subType == "d02Masy1"){
       vector<double> asymmetry;
       int nbin = m_theory.size();
       for(int i = 0; i < m_data.size(); i++){
         double WPlus = m_theory.at(nbin / 4 + i);
         double WMinus = m_theory.at(nbin * 3 / 4 + i);
         WPlus *= m_data.at(i).wp_kfac;
         WMinus *= m_data.at(i).wm_kfac;
         asymmetry.push_back((WPlus - WMinus) / (WPlus + WMinus));
       }
       m_theory.clear();
       m_theory = asymmetry;
     }

     if(subType == "d02Easy5"){
       vector<double> asymmetry;
       int nbin = m_theory.size();
       for(int i = 0; i < m_data.size(); i++){
         double WPlus = m_theory.at(i);
         double WMinus = m_theory.at(nbin / 2 + i);
         WPlus *= m_data.at(i).wp_kfac;
         WMinus *= m_data.at(i).wm_kfac;
         asymmetry.push_back((WPlus - WMinus) / (WPlus + WMinus));
       }
       m_theory.clear();
       m_theory = asymmetry;
     }

     //if(subType == "ZyCDF2_up") m_theory.push_back(m_theory.at(m_data.size() - 2)); // yfu2025.3.19 Fix it!!!!!
   }
 }
 else if(CalcMode == "FastNLO"){
   if(ColliderType == "LHC"){
     m_theory.clear();
     m_corrected_data.clear();
     if(!m_data.at(0).isOldFNLOFormat){
       for(int igrid = 0; igrid < FNLOTableNames.size(); igrid++){
         vector<double> xsec;
         m_fnlo.at(igrid)->CalcCrossSection();
         xsec = m_fnlo.at(igrid)->GetCrossSection();
         //cout<<getTime()<<" convolute for "<<FNLOTableNames.at(igrid)<<endl;
         for(int i = 0; i < xsec.size(); i++){
           m_theory.push_back(xsec.at(i));
         }
 
         if(subType == "CMS7jtR7y6_v1") {
           m_theory.clear();
           for(int i = 5; i <= 32; i++) m_theory.push_back(xsec.at(i));
           for(int i = 38; i <= 65; i++) m_theory.push_back(xsec.at(i));
           for(int i = 71; i <= 95; i++) m_theory.push_back(xsec.at(i));
           for(int i = 101; i <= 121; i++) m_theory.push_back(xsec.at(i));
           for(int i = 127; i <= 142; i++) m_theory.push_back(xsec.at(i));
         }

         if(subType == "CMS8jtR7"){
           m_theory.clear();
           for(int i = 9; i <= 45; i++) m_theory.push_back(xsec.at(i));
           for(int i = 55; i <= 91; i++) m_theory.push_back(xsec.at(i));
           for(int i = 101; i <= 136; i++) m_theory.push_back(xsec.at(i));
           for(int i = 146; i <= 177; i++) m_theory.push_back(xsec.at(i));
           for(int i = 187; i <= 211; i++) m_theory.push_back(xsec.at(i));
           for(int i = 221; i <= 238; i++) m_theory.push_back(xsec.at(i));
         }

         if(subType == "CMS8jtR7_v1"){
           vector<double> tmp;
           for(int i = 9; i <= 45; i++) tmp.push_back(xsec.at(i));
           for(int i = 55; i <= 91; i++) tmp.push_back(xsec.at(i));
           for(int i = 101; i <= 136; i++) tmp.push_back(xsec.at(i));
           for(int i = 146; i <= 177; i++) tmp.push_back(xsec.at(i));
           for(int i = 187; i <= 211; i++) tmp.push_back(xsec.at(i));
           for(int i = 221; i <= 238; i++) tmp.push_back(xsec.at(i));

           m_theory.clear();
           for(int i = 0; i <= 34; i++) m_theory.push_back(tmp.at(i));
           for(int i = 37; i <= 70; i++) m_theory.push_back(tmp.at(i));
           for(int i = 76; i <= 106; i++) m_theory.push_back(tmp.at(i));
           for(int i = 110; i <= 137; i++) m_theory.push_back(tmp.at(i));
           for(int i = 142; i <= 161; i++) m_theory.push_back(tmp.at(i));
           for(int i = 167; i <= 182; i++) m_theory.push_back(tmp.at(i));
         }
       }
  
       if(subType == "CMS8pTtyt"){
         double TotalCrossSection = 0.0;
         vector<double> BW1 = {80.0, 70.0, 100.0, 350.0};
         vector<double> BW2 = {0.35, 0.5, 0.6, 1.05};
         for(int i = 0; i < m_theory.size(); i++){
           TotalCrossSection += m_theory.at(i) * BW1.at(i % 4);
         }
         for(int i = 0; i < m_theory.size(); i++){
           m_theory.at(i) /= (TotalCrossSection * BW2.at(i / 4));
         }
       }
     }
     else{
       for(int igrid = 0; igrid < FNLOTableNames.size(); igrid++){
         FortranArray2D<double> xsect{1, m_fnlo.at(igrid)->NBINTOTMAX, 1, 3};
         m_fnlo.at(igrid)->FT2007CC(FNLOTableNames.at(igrid), 1.0, 1.0, 0, xsect, subType);
         for(int i = 0; i < m_fnlo.at(igrid)->nbin; i++){
           m_theory.push_back(xsect(i + 1, 1) + xsect(i + 1, 2));
         }
       }
     }
   }
   if(ColliderType == "Tev"){
     m_theory.clear();
     m_corrected_data.clear();
     if(!m_data.at(0).isOldFNLOFormat){
       for(int igrid = 0; igrid < FNLOTableNames.size(); igrid++){
         vector<double> xsec;
         m_fnlo.at(igrid)->CalcCrossSection();
         xsec = m_fnlo.at(igrid)->GetCrossSection();
         for(int i = 0; i < xsec.size(); i++){
           m_theory.push_back(xsec.at(i));
         }
       }
     }
     else{
       for(int igrid = 0; igrid < FNLOTableNames.size(); igrid++){
         FortranArray2D<double> xsect{1, m_fnlo.at(igrid)->NBINTOTMAX, 1, 3};
         m_fnlo.at(igrid)->FT2007CC(FNLOTableNames.at(igrid), 1.0, 1.0, 0, xsect, subType);
         //cout<<getTime()<<" convolute for "<<FNLOTableNames.at(igrid)<<endl;
         for(int i = 0; i < m_fnlo.at(igrid)->nbin; i++){
           m_theory.push_back(xsect(i + 1, 1) + xsect(i + 1, 2));
         }
       }
     }
   }
 }
 else if(CalcMode == "PineAPPL"){
   if(ColliderType == "LHC"){
     m_theory.clear();
     m_corrected_data.clear();
     vector<vector<double>> xsec_list;
     for(int igrid = 0; igrid < PineAPPLGridNames.size(); igrid++){
       vector<double> xsec;
       if(PDFType == "LHAPDF"){
         xsec = m_pineappl.at(igrid)->Convolute();
         //cout<<getTime()<<" convolute for "<<PineAPPLGridNames.at(igrid)<<endl;
       }
       else{
         xsec = m_pineappl_xsec[igrid];
       }

       xsec_list.push_back(xsec);
       //for(int i = 0; i < xsec.size(); i++){
       //  m_theory.push_back(xsec.at(i));
       //}
     }

     for(int i = 0; i < PineAPPLGridMap.size(); i++){
       tuple<vector<int>, TString> gridblock = PineAPPLGridMap.at(i);

       vector<double> xsec;
       vector<double> xsec1;
       vector<double> xsec2;

       int GridIndex1 = -1;
       int GridIndex2 = -1;

       if(get<0>(gridblock).size() == 1){
         GridIndex1 = get<0>(gridblock).at(0);
         xsec = xsec_list.at(GridIndex1);
       }
       else if(get<0>(gridblock).size() == 2){
         GridIndex1 = get<0>(gridblock).at(0);
         GridIndex2 = get<0>(gridblock).at(1);
         xsec1 = xsec_list.at(GridIndex1);
         xsec2 = xsec_list.at(GridIndex2);
       }

       if(get<1>(gridblock) == "ratio" || get<1>(gridblock) == "Ratio"){
         xsec = xsec1;
         for(int ipoint = 0; ipoint < xsec.size(); ipoint++){
           xsec.at(ipoint) = xsec.at(ipoint) / xsec2.at(0);
         }
       }

       for(int i = 0; i < xsec.size(); i++){
         m_theory.push_back(xsec.at(i));
       }
     }
   }

   if(ColliderType == "Tev"){
     m_theory.clear();
     m_corrected_data.clear();
     vector<vector<double>> xsec_list;
     for(int igrid = 0; igrid < PineAPPLGridNames.size(); igrid++){
       vector<double> xsec;
       if(PDFType == "LHAPDF"){
         xsec = m_pineappl.at(igrid)->Convoluteppbar();
         //cout<<getTime()<<" convolute for "<<PineAPPLGridNames.at(igrid)<<endl;
       }
       else{
         xsec = m_pineappl_xsec[igrid];
       }

       xsec_list.push_back(xsec);
       //for(int i = 0; i < xsec.size(); i++){
       //  m_theory.push_back(xsec.at(i));
       //}
     }

     for(int i = 0; i < PineAPPLGridMap.size(); i++){
       tuple<vector<int>, TString> gridblock = PineAPPLGridMap.at(i);

       vector<double> xsec;
       vector<double> xsec1;
       vector<double> xsec2;

       int GridIndex1 = -1;
       int GridIndex2 = -1;

       if(get<0>(gridblock).size() == 1){
         GridIndex1 = get<0>(gridblock).at(0);
         xsec = xsec_list.at(GridIndex1);
       }
       else if(get<0>(gridblock).size() == 2){
         GridIndex1 = get<0>(gridblock).at(0);
         GridIndex2 = get<0>(gridblock).at(1);
         xsec1 = xsec_list.at(GridIndex1);
         xsec2 = xsec_list.at(GridIndex2);
       }

       if(get<1>(gridblock) == "ratio" || get<1>(gridblock) == "Ratio"){
         xsec = xsec1;
         for(int ipoint = 0; ipoint < xsec.size(); ipoint++){
           xsec.at(ipoint) = xsec.at(ipoint) / xsec2.at(0);
         }
       }

       for(int i = 0; i < xsec.size(); i++){
         m_theory.push_back(xsec.at(i));
       }
     }
   }
 }
 else if(CalcMode == "CTEQ"){
   vector<double> xsec;
   m_calculation->CalcDIS::GetPrediction(xsec);
   m_data = m_calculation->CalcDIS::Output();
   m_theory.clear();
   m_corrected_data.clear();
   for(int i = 0; i < xsec.size(); i++){
     m_theory.push_back(xsec.at(i));
   }
 }
 else if(CalcMode == "CTEQ_DY"){
   vector<double> xsec;
   m_calculation->CalcVBP::GetPrediction(xsec);
   m_data = m_calculation->CalcVBP::Output();
   m_theory.clear();
   m_corrected_data.clear();
   for(int i = 0; i < xsec.size(); i++){
     m_theory.push_back(xsec.at(i));
   }
 }
 else if(CalcMode == "NULL"){
   return;
 }
 else{
   cout<<LOG_ERROR<<"Unknown Calculation Mode!"<<endl;
   return;
 }

 if(!m_data.at(0).isAsymmetryData){
   if(m_data.size() != m_theory.size()){
     cout<<LOG_ERROR<<"in GetPrediction, Calculation doesn't match to data!"<<endl;
     cout<<LOG_ERROR<<"data set: "<<m_name<<endl;
     return;
   }
 }

 m_corrected_data.resize(m_theory.size());
 // Apply KFactor
 // For fixed target Drell-Yan, note that the kfactor for NLO fit is not correct,
 // the dataset should know IorHrd setting from the config, and decide which kfactor should be used.
 for(int i = 0; i < m_data.size(); i++){

   if(!(m_data.at(i).noAdditionalKFactor)){

     for(int icolumn = 0; icolumn < m_data.at(i).AppliedKFactorColumns.size(); icolumn++){
       if(m_data.at(i).AppliedKFactorColumns.at(icolumn) - 1 >= m_data.at(i).NKFactor){
         cout<<LOG_ERROR<<"No such KFactor column, Column = "<<m_data.at(i).AppliedKFactorColumns.at(icolumn)<<" NKFactor = "<<m_data.at(i).NKFactor<<endl;
         return;
       }
       m_theory.at(i) *= m_data.at(i).KFactors(m_data.at(i).AppliedKFactorColumns.at(icolumn) - 1);
     }

   }

   if(OtherKFactorList.size() != 0){
     m_theory.at(i) *= m_data.at(i).OtherKFactor;
   }

   //m_theory.at(i) /= m_data.at(i).Normalization;
   m_theory.at(i) *= m_data.at(i).BarnFactor;
   m_data.at(i).theory = m_theory.at(i);

   m_corrected_data.at(i) = m_data.at(i).data;
 }

 //cout<<"Get prediction done."<<endl;
}

void Dataset::PrepareChi2()
{
 Theory = Eigen::VectorXd(m_theory.size());
 for(int i = 0; i < m_theory.size(); i++){
   Theory(i) = m_theory.at(i) / Normalization;

   // For DIS or VBP data, applying the adjustment
   if(isReorganize) m_data[i].data = DataVector.at(i);
 }

 if(isReorganize){
   if(DataVector.size() != NPoints){
     cout<<LOG_ERROR<<"in PrepareChi2, Calculation doesn't match to data!"<<endl;
     cout<<LOG_ERROR<<"data set: "<<m_name<<endl;
     return;
   }
 }

 m_theory.clear();
 DataVector.clear();
}

double Dataset::Chi2(bool print)
{
    if(CalcMode == "NULL"){
      FinalChi2 = 0.0;
      return 0.0;
    }

    if(m_data.at(0).isAsymmetryData){// for calculating W asymmetry
      saved_data.clear();
      saved_data = m_data;

      saved_Theory.resize(0);
      saved_Theory = Theory;

      vector<DataPoint> asymdata(m_data.size() / 3);
      for(int i = 0; i < asymdata.size(); i++){
        asymdata.at(i) = m_data.at(i + asymdata.size() * 2);
        if(fabs(Theory(i) + Theory(i + asymdata.size())) > 1e-20){
          asymdata.at(i).theory = (Theory(i) - Theory(i + asymdata.size())) / (Theory(i) + Theory(i + asymdata.size())) * 100.0;
        }
      }
      m_data.clear();
      m_data = asymdata;
      Theory.resize(0);
      Theory = Eigen::VectorXd(m_data.size());
      for(int i = 0; i < m_data.size(); i++){
        Theory(i) = m_data.at(i).theory;
      }
      NPoints = m_data.size();
    }

    UnCorr = Eigen::VectorXd(m_data.size());
    Data = Eigen::VectorXd(m_data.size());
    for(int i = 0; i < m_data.size(); ++i) {
       UnCorr(i) = m_data[i].UnCorrErr;
       Data(i) = m_data[i].data;
    }

    int NCorrData = m_data[0].CorrErrs.size();

    beta = Eigen::MatrixXd(m_data.size(), NCorrData);
    b = Eigen::MatrixXd(m_data.size(), NCorrData);
    for(size_t k = 0; k < m_data.size(); ++k) {
        for(size_t alpha = 0; alpha < NCorrData; ++alpha) {
            if(kSysMethod.size() == 0){
              beta(k, alpha) = m_data[k].CorrErrs[alpha]*Theory(k);
            }
            else{
              if(kSysMethod[alpha] == 1) beta(k, alpha) = m_data[k].CorrErrs[alpha]*Theory(k);
              if(kSysMethod[alpha] == 0){
                beta(k, alpha) = m_data[k].CorrErrs[alpha]*Data(k);
                //if(Irun == 0) UnCorr(k) = sqrt(UnCorr(k) * UnCorr(k) + beta(k, alpha) * beta(k, alpha));
                UnCorr(k) = sqrt(UnCorr(k) * UnCorr(k) + beta(k, alpha) * beta(k, alpha));
                beta(k, alpha) = 0.0;
              }
            }
            b(k, alpha) = beta(k, alpha) / UnCorr(k);
        }
    }

    /* // This method is slow
    Eigen::MatrixXd S_inv = (UnCorr).array().inverse().matrix().asDiagonal();
    Eigen::MatrixXd b = S_inv*beta;
    Eigen::VectorXd d = S_inv*(Data-Theory);
    Eigen::MatrixXd C_inv = Eigen::MatrixXd::Identity(NPoints, NPoints)-b*(Eigen::MatrixXd::Identity(NCorrData, NCorrData)+b.transpose()*b).inverse()*b.transpose();
    Eigen::VectorXd lambda = b.transpose()*C_inv*d;
    Eigen::VectorXd r = C_inv*d;
    double Result = r.dot(r) + lambda.dot(lambda);
    */

    Eigen::VectorXd d = (Data - Theory);
    Eigen::VectorXd Diff = d; // b^T * d
    for(int ipoint = 0; ipoint < NPoints; ipoint++){
      d(ipoint) = d(ipoint) / UnCorr(ipoint);
      Diff(ipoint) = Diff(ipoint) / UnCorr(ipoint) / UnCorr(ipoint);
    }

    if(isAdditionalCovariance && !isPrepareLLT){
      PrepareLLT();
    }

    if(!isAdditionalCovariance){
      AMatrix = Eigen::MatrixXd::Identity(NCorrData, NCorrData) + b.transpose() * b; // Nlambda by Nlambda
    }
    else{
      AMatrix = Eigen::MatrixXd::Identity(m_data[0].CorrErrs.size(), m_data[0].CorrErrs.size()) + WMatrix.transpose() * WMatrix;
    }

    //Eigen::MatrixXd AMatrix_inv = AMatrix.inverse(); // Nlambda by Nlambda

    if(!isAdditionalCovariance){
      BVector = beta.transpose() * Diff; // Nlambda by Npt * Npt by 1
    }
    else{
      Eigen::VectorXd d_raw = (Data - Theory);
      zVector = LMatrix.triangularView<Eigen::Lower>().solve(d_raw);
      BVector = WMatrix.transpose() * zVector;
    }

    lambda.resize(0);
    //lambda = AMatrix_inv * BVector; // Nlambda by Nlambda * Nlambda by 1
    Eigen::LDLT<Eigen::MatrixXd> A_ldlt(AMatrix);
    lambda = A_ldlt.solve(BVector); // faster

    Eigen::VectorXd r;
    if(!isAdditionalCovariance){
      r = (Data - Theory - beta * lambda);
      for(int ipoint = 0; ipoint < NPoints; ipoint++){
        r(ipoint) = r(ipoint) / UnCorr(ipoint);
      }
    }
    else{
      r = zVector - WMatrix * lambda;
    }

    double Result;

    if(!isAdditionalCovariance){
      Result = d.dot(d) - BVector.dot(lambda);
    }
    else{
      Result = zVector.dot(zVector) - BVector.dot(lambda);
    }

    double OriginalChi2 = Result;
    double ChiNorm = 0.0;
    if(isNormFit){
      ChiNorm = FacNor  * pow((( Normalization - 1.0 )/NormErr), 2.0)
              + FacNor4 * pow((( Normalization - 1.0 )/NormErr), 4.0);     // Quartic norm penalty (jcp 7/11/2013)
      Result += ChiNorm;
    }

    if(print || is_print) {
        cout<<"output data file for "<<m_name<<" Chi2 = "<<OriginalChi2<<"  ";
        if(fabs(ChiNorm) > 1e-20) cout<<"ChiNorm = "<<ChiNorm;
        cout<<endl;

        savedta.str("");
        savedta.clear();
        ofstream singledta;
        singledta.open(m_name + ".dta");
        output.Initial(singledta, savedta);

        double spartyness = TranslateChi2ToSpartyness(OriginalChi2, m_data.size());

        output << " DATA SET " << DataID << " ; NORM Fac = ";
        output << setw(9) << fixed << setprecision(5) << Normalization << " ; # of pts = ";
        output << setw(4) << m_data.size() << " ; chi^2 = ";
        output << setw(12) << fixed << setprecision(6) << OriginalChi2 << " S= ";
        output << setw(10) << fixed << setprecision(5) << spartyness << " chi^2/N = ";
        output << setw(10) << fixed << setprecision(5) << OriginalChi2/m_data.size() << endl;
        output << "R^2, r(k) = ";
        output << setw(7) << fixed << setprecision(3) << lambda.dot(lambda);
        output << setw(7) << fixed << setprecision(3) << lambda.transpose() << endl;
        output << m_data[0].variableTitle << "Exp      Th./Norm     TotErr     EXP/FIT  ERR/FIT    ChiSq  shift    shiftData  UnCorErr  ReducedChi2  lob/lio" << endl;

        //output << "Dataset: " << m_name << endl;
        //output << "Npts = " << m_data.size() << ", chi^2 = " << OriginalChi2 << " chi^2/N = " << OriginalChi2/m_data.size() << endl;
        //output << "Lambda^2 = " << lambda.dot(lambda) << ", lambda_alpha =  " << lambda.transpose() << endl;
        //output << "data           theory       totErr   EXP/FIT  ERR/FIT  ChiSq   shift     shiftData  uncorrErr   reducedChi2 lob" << endl;

        Eigen::VectorXd corr_err = beta*lambda;
        Eigen::VectorXd shifted = Data - corr_err;
        for(size_t i = 0; i < m_data.size(); ++i) {
            double sign = (Data(i)-Theory(i))/std::abs(Data(i)-Theory(i));
            double tot_err;

            if(!isAdditionalCovariance){
              tot_err = sqrt(UnCorr(i)*UnCorr(i) + corr_err(i)*corr_err(i));
            }
            else{
              double diag_V0   = UnCorr(i)*UnCorr(i) + AdditionalCovariance(i, i);// S^2 + C_ii
              double beta2_sum = beta.row(i).squaredNorm();
              tot_err = sqrt(diag_V0 + beta2_sum);
            }

            output << setw(9) << uppercase << scientific << setprecision(3) << m_data[i].variable1;
            output << setw(11) << uppercase << scientific << setprecision(3) << m_data[i].variable2;
            output << setw(11) << uppercase << scientific << setprecision(3) << m_data[i].variable3;
            output << setw(13) << uppercase << scientific << setprecision(5) << m_data[i].data;
            output << setw(13) << uppercase << scientific << setprecision(5) << Theory(i);
            output << setw(11) << uppercase << scientific << setprecision(3) << tot_err;
            output << setw(9) << fixed << setprecision(3) << m_data[i].data / Theory(i);
            output << setw(9) << fixed << setprecision(3) << tot_err / Theory(i);
            output << setw(9) << *right << fixed << setprecision(3) << sign*pow((m_data[i].data-Theory(i))/tot_err, 2);
            output << setw(11) << *right << uppercase << scientific << setprecision(3) << corr_err(i);
            output << setw(11) << uppercase << scientific << setprecision(3) << shifted(i);
            output << setw(11) << uppercase << scientific << setprecision(3) << UnCorr(i);
            output << setw(8) << *right << fixed << setprecision(2) << r(i)*r(i)*r(i)/fabs(r(i));
            output << setw(8) << m_data.at(i).lob << endl;
        }
        //output.close();
        singledta.close();
    }

    if(m_data.at(0).isAsymmetryData){// for calculating W asymmetry
      m_data = saved_data;
      NPoints = m_data.size();

      Theory = saved_Theory;
    }

    Irun++;

    // Set the print to be false, we should set the is_print to true by hand every time.
    is_print = false;

    FinalChi2 = Result;

    return Result;
}


