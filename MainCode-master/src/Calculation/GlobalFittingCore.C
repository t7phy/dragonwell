#include "Calculation/GlobalFittingCore.h"

#include <cassert>

double Min_Chi2_Minuit2 = 10000000.0;

GlobalFittingCore::GlobalFittingCore()
{
 cout<<LOG_INFO<<"Start PDF Global Fitting:"<<endl;
 cout<<LOG_INFO<<endl;

}

void GlobalFittingCore::Initialize()
{
// setting.ConfigOrder(22, 3, 0, 0, 3, 3, 5);
 setting.ConfigDis(
  {99, 1, 230},
  {1.0, 0.0, 0.0}
 );
 setting.ConfigVbp(
  {99, 0, 0},
  {0.0, 0.0, 0.0}
 );

 map<tuple<int, int>, double> CPpara = {
   {make_tuple(1, 1), 0.01000}, {make_tuple(2, 1), 0.3}, {make_tuple(3, 1), 0.3}, {make_tuple(4, 1), 0.8}, {make_tuple(5, 1), 1.0}, {make_tuple(6, 1), 0.0},  {make_tuple(7, 1), 0.0},
   {make_tuple(1, 2), 0.00000}, {make_tuple(2, 2), 0.0}, {make_tuple(3, 2), 0.0}, {make_tuple(4, 2), 0.0}, {make_tuple(5, 2), 0.0}, {make_tuple(6, 2), 0.0},  {make_tuple(7, 2), 0.0},
   {make_tuple(1, 3), 0.00000}, {make_tuple(2, 3), 0.0}, {make_tuple(3, 3), 0.0}, {make_tuple(4, 3), 0.0}, {make_tuple(5, 3), 1.0}, {make_tuple(6, 3), 16.0}, {make_tuple(7, 3), 0.9},
   {make_tuple(1, 4), 0.00000}, {make_tuple(2, 4), 0.0}, {make_tuple(3, 4), 0.0}, {make_tuple(4, 4), 0.0}, {make_tuple(5, 4), 0.0}, {make_tuple(6, 4), 0.0},  {make_tuple(7, 4), 0.0},
   {make_tuple(1, 5), 0.00000}, {make_tuple(2, 5), 0.0}, {make_tuple(3, 5), 0.0}, {make_tuple(4, 5), 0.0}, {make_tuple(5, 5), 0.0}, {make_tuple(6, 5), 0.0},  {make_tuple(7, 5), 0.0}
 };

 setting.InputCP(CPpara);

 setting.ParseParameter(InputParaFileName);
 setting.ParseConfig("Config.yml");

 QCDSet* m_qcd = new QCDSet();
 m_qcd->SetNfTotal(setting.Nflv);
 m_qcd->SetPoleMasscbt(setting.mc, setting.mb, setting.mt);
 m_qcd->SetAmhatf();
 setting.Amhat = m_qcd->Amhat;
 delete m_qcd;

 for(int i = 0; i < setting.GetNPar(); i++){
   Input(setting.GetParName(i), setting.GetParCentral(i), setting.GetParStep(i), setting.GetParLeft(i), setting.GetParRight(i));
 }

 m_pdf_Q0 = new PDFEvolve();

 map<TString, double> p = setting.FittingParameter;

 vector<TString> FlavorList = setting.FlavorList;
 vector<int> FlagList = setting.FlagList;

 for(int iflavor = 0; iflavor < FlavorList.size(); iflavor++){
   m_pdf_Q0->SetParameter(FlavorList.at(iflavor), setting.ShapeParameterValue.at(FlavorList.at(iflavor)));
 }

 m_pdf_Q0->SetInitialgluonMomentum(setting.InitialgluonMomentum);
 m_pdf_Q0->SetInitialStrangeB0(setting.InitialStrangeB0);

 m_pdf_Q0->Initialize(setting.IFun, FlavorList, FlagList);
 if(setting.PDFInputType == "None") m_pdf_Q0->ParameterOutput();

 m_hoppet = new HoppetInterface();
 m_hoppet->SetAlphaSQ0(setting.AlphaS, setting.AlphaS_Q0);
 m_hoppet->SetMcbt(setting.Amhat(4), setting.Amhat(5), setting.Amhat(6));
 if(setting.Nflv > 5) m_hoppet->SetNfMax(setting.Nflv);
 m_hoppet->SetEvolveOrder(setting.IorEvl);
 m_hoppet->SetAlphaSOrder(setting.IorQCD);

 if(setting.isEvolveSmallx) m_hoppet->SetEvolveSmallx(); // Just need to be done once. All the other Initialize() call will use the same setting.

 if(setting.PDFInputType == "None"){
   if(setting.EvolveType == "Hoppet"){
     m_hoppet->Initialize(m_pdf_Q0, setting.Qini);
   }
   else if(setting.EvolveType == "APFEL"){
     m_hoppet->InitializeAPFEL(m_pdf_Q0, setting.Qini);
   }
   else if(setting.EvolveType == "APFELxx"){
     m_hoppet->InitializeAPFELxx(m_pdf_Q0, setting.Qini);
   }
  
   m_hoppet->SetQArray();
   m_hoppet->SetXArray();
   pdsReader* pdftable = m_hoppet->PrepareCTEQTable();
  
   setting.ConfigPDF(pdftable);
 }
 else if(setting.PDFInputType == "CTEQ"){
   setting.ConfigPDF(setting.PDFInput);
 }
 else if(setting.PDFInputType == "LHAPDF"){
   setting.ConfigPDF(setting.PDFInput, setting.PDFiSet);
 }

 setting.ParseDataList("DataList.yml");
 AllData.resize(setting.DataList.size());

 for(int idata = 0; idata < setting.DataList.size(); idata++){
   AllData.at(idata) = new Dataset(setting.DataList.at(idata).DataName);
   AllData.at(idata)->SetCut(setting);

   if(setting.DataList.at(idata).Normalization.size() != 0){
     double NormCentral = setting.DataList.at(idata).Normalization.at(0);
     if(setting.FittingParameter.count(setting.DataList.at(idata).NormParName) > 0) NormCentral = setting.FittingParameter.at(setting.DataList.at(idata).NormParName);
     AllData.at(idata)->InputNormalization(NormCentral, setting.DataList.at(idata).Normalization.at(1), setting.DataList.at(idata).Normalization.at(2));
   }

   AllData.at(idata)->ReadFile(setting.DataList.at(idata).DataPath,
                               setting.DataList.at(idata).DataType,
                               setting.DataList.at(idata).CalcMode,
                               setting.DataList.at(idata).Collider,
                               setting.DataList.at(idata).subType);

   AllData.at(idata)->SetDataID(setting.DataList.at(idata).DataID);

   if(setting.DataList.at(idata).ApplGrids.size() != 0){
     AllData.at(idata)->InputGridName(setting.DataList.at(idata).ApplGrids);
   }

   if(setting.DataList.at(idata).ApplRange.size() != 0){
     for(int i = 0; i < setting.DataList.at(idata).ApplRange.size(); i++){
       AllData.at(idata)->InputApplGridRange(setting.DataList.at(idata).ApplRange.at(i).at(0), setting.DataList.at(idata).ApplRange.at(i).at(1), setting.DataList.at(idata).ApplRange.at(i).at(2));
     }
   }

   if(setting.DataList.at(idata).FastNLOGrids.size() != 0){
     AllData.at(idata)->InputFNLOTableName(setting.DataList.at(idata).FastNLOGrids);
   }

   if(setting.DataList.at(idata).PineAPPLGrids.size() != 0){
     AllData.at(idata)->InputPineAPPLGridName(setting.DataList.at(idata).PineAPPLGrids);
     AllData.at(idata)->InputPineAPPLGridMap(setting.DataList.at(idata).PineAPPLGridMap);
   }

   if(setting.DataList.at(idata).SystematicMethod.size() != 0){
     AllData.at(idata)->InputSystematicMethod(setting.DataList.at(idata).SystematicMethodMap);
   }

   if(setting.DataList.at(idata).KFactors.size() != 0){
     AllData.at(idata)->InputKFactorColumns(setting.DataList.at(idata).KFactors);
   }

   if(setting.OtherParameterList.size() > 0){
     if(setting.DataList.at(idata).OtherKFactors.size() != 0){
       vector<double> zVec;
       for(int i = 0; i < setting.DataList.at(idata).OtherKFactors.size(); i++){
         TString name = setting.DataList.at(idata).OtherKFactors.at(i).at(0);
         TString FileName = setting.DataList.at(idata).OtherKFactors.at(i).at(2);
         TString Path = setting.DataGlobalPath + FileName;
         AllData.at(idata)->InputOtherKFactor(Path);

         double central = 0.0;
         if(setting.OtherParameterCentral.count(name) > 0){
           central = setting.OtherParameterCentral.at(name);
         }
         else{
           central = 0.0;
         }
         zVec.push_back(central);
       }
       AllData.at(idata)->ApplyOtherKFactor(zVec);
     }
   }

   if(setting.DataList.at(idata).AdditionalCorrMatrix.size() != 0){
     AllData.at(idata)->InputAdditionalCorrMatrix(setting.DataList.at(idata).AdditionalCorrMatrix);
   }
 }

 m_fcn = new PDFChi2();
 //m_fcn->BookLMPenalty(1, "ratioPDF", vector<int>{1}, vector<double>{10.0, 2.0, 0.2, 1e-8});
 //m_fcn->BookLMPenalty(2, "ratioPDF", vector<int>{1}, vector<double>{10.0, 1.8, 0.4, 1e-5});
 //m_fcn->BookLMPenalty(3, "LargeCoefficient", vector<int>{1}, vector<double>{0.01});
 //m_fcn->BookLMPenalty(4, "SystematicShift", vector<int>{504, 25, 514, 23}, vector<double>{0.5, 0.5});

 for(auto iter = setting.LMPenaltyInput.begin(); iter != setting.LMPenaltyInput.end(); iter++){
   m_fcn->BookLMPenalty(iter->first, get<0>(iter->second), get<1>(iter->second), get<2>(iter->second));
 }

 m_fcn->ThreadSetup(setting.nDISThread, setting.nVBPThread);
 m_fcn->Initialize(AllData, setting);
 m_fcn->GetChi2(true);
 cout<<getTime()<<" Finish calculate chi2 first time. Chi2 = "<<m_fcn->FitChi2<<endl;

 if(setting.PDFInputType == "None"){
   pdsReader* mypdf = m_hoppet->PrepareCTEQTable();
   mypdf->OutputPDF("mypdf_bestfit.pds");
   m_hoppet->OutputLHAPDFTable("mypdf_bestfit", 0);
   setting.OutputNewParameterFile(NewParaFileName);
 }

 if(setting.PDFInputType == "None") setting.OutputParameters();

 m_AllData = &AllData;
 m_setting = &setting;
}

double GlobalFittingCore::operator()(const std::vector<double>& par) const
{
 assert(par.size() == m_setting->GetNPar());

 double chi2;

 for(int i = 0; i < m_setting->GetNPar(); i++){
   TString ParName = m_setting->ParameterList.at(i).name;
   int Index = m_setting->ParameterList.at(i).index;
   m_setting->FittingParameter.at(ParName) = par[Index];
 }

 for(int i = 0; i < m_setting->GetNPar(); i++){
   int id = m_setting->ParameterList.at(i).id;
   int Index = m_setting->ParameterList.at(i).index;
   m_setting->IDtoParam.at(id) = par[Index];
 }

 m_setting->RefreshShapeParameter();

 map<TString, double> p = m_setting->FittingParameter;

 vector<TString> FlavorList = m_setting->FlavorList;
 vector<int> FlagList = m_setting->FlagList;

 for(int iflavor = 0; iflavor < FlavorList.size(); iflavor++){
   m_pdf_Q0->SetParameter(FlavorList.at(iflavor), m_setting->ShapeParameterValue.at(FlavorList.at(iflavor)));
 }

 m_pdf_Q0->SetgluonMomentumPar(p.at("gluM"));
 m_pdf_Q0->SetStrangeB0Par(p.at("strM"));

 m_pdf_Q0->Initialize(m_setting->IFun, FlavorList, FlagList);

 if(setting.EvolveType == "Hoppet"){
   m_hoppet->Initialize(m_pdf_Q0, m_setting->Qini);
 }
 else if(setting.EvolveType == "APFEL"){
   m_hoppet->InitializeAPFEL(m_pdf_Q0, m_setting->Qini);
 }
 else if(setting.EvolveType == "APFELxx"){
   m_hoppet->InitializeAPFELxx(m_pdf_Q0, m_setting->Qini);
 }

 pdsReader* pdftable = m_hoppet->PrepareCTEQTable();
 m_setting->ConfigPDF(pdftable);

 m_fcn->InitialPDF(*m_setting);

 for(auto iter = m_setting->NormParDataList.begin(); iter != m_setting->NormParDataList.end(); iter++){
   for(int i = 0; i < iter->second.size(); i++){
     m_fcn->AllData.at(iter->second.at(i))->InputNormalization(p.at(iter->first));
   }
 }

 if(m_setting->OtherParameterList.size() > 0){
   for(int idata = 0; idata < m_setting->DataList.size(); idata++){
     if(m_setting->DataList.at(idata).OtherKFactors.size() != 0){
       vector<double> zVec;
       for(int i = 0; i < m_setting->DataList.at(idata).OtherKFactors.size(); i++){
         TString name = m_setting->DataList.at(idata).OtherKFactors.at(i).at(0);

         double central = 0.0;
         if(p.count(name) > 0 && m_setting->OtherParameter_isFit.at(name)){
           central = p.at(name);
         }
         else{
           if(m_setting->OtherParameterCentral.count(name) > 0){
             central = m_setting->OtherParameterCentral.at(name);
           }
           else{
             central = 0.0;
           }
         }
         zVec.push_back(central);
       }
       m_fcn->AllData.at(idata)->ApplyOtherKFactor(zVec);
     }
   }
   m_fcn->UpdateVBPDataTable();
 }

 chi2 = m_fcn->GetChi2(false);

// if(chi2 < Min_Chi2){
   Min_Chi2_Minuit2 = chi2;

   cout<<getTime()<<endl;
   m_pdf_Q0->ParameterOutput();
   cout<<"gluM = "<<m_pdf_Q0->GetgluonMomentum()<<endl;
   cout<<"strM = "<<m_pdf_Q0->GetStrangeB0()<<endl;
   if(p.count("N71") > 0) cout<<"N71  = "<<p.at("N71")<<endl;
   if(p.count("N72") > 0) cout<<"N72  = "<<p.at("N72")<<endl;
   if(p.count("N73") > 0) cout<<"N73  = "<<p.at("N73")<<endl;
   cout<<endl;

   cout<<"Min Chi2 = "<<Min_Chi2_Minuit2<<" Chi2 (no penalty) = "<<m_fcn->FitChi2NoPenalty<<endl;
// }

 if(chi2 > 100000.0){
   m_fcn->GetChi2(true);
 }

 delete pdftable;

 return chi2;
}

double GlobalFittingCore::chi2(const std::vector<double>& par)
{
 double chi2;

 chi2 = (*this)(par);

 return chi2;
}

void GlobalFittingCore::Finalize(std::vector<double> pars, std::vector<double> parerrs)
{
 vector<double> Par = pars;
 vector<double> ParErr = parerrs;
 if(Par.size() != setting.GetNPar()){
   cout<<"ERROR! Final best fit parameters don't match with input."<<endl;
 }

 for(int i = 0; i < setting.GetNPar(); i++){
   TString ParName = setting.ParameterList.at(i).name;
   int Index = setting.ParameterList.at(i).index;
   setting.FittingParameter.at(ParName) = Par[Index];
   setting.ParameterList.at(i).central = Par[Index];
   setting.ParameterList.at(i).FittingError = ParErr[Index];
 }

 for(int i = 0; i < setting.GetNPar(); i++){
   int id = setting.ParameterList.at(i).id;
   int Index = setting.ParameterList.at(i).index;
   setting.IDtoParam.at(id) = Par[Index];
 }

 setting.RefreshShapeParameter();

 map<TString, double> p = setting.FittingParameter;

 vector<TString> FlavorList = setting.FlavorList;
 vector<int> FlagList = setting.FlagList;

 for(int iflavor = 0; iflavor < FlavorList.size(); iflavor++){
   m_pdf_Q0->SetParameter(FlavorList.at(iflavor), setting.ShapeParameterValue.at(FlavorList.at(iflavor)));
 }

 m_pdf_Q0->SetgluonMomentumPar(p.at("gluM"));
 m_pdf_Q0->SetStrangeB0Par(p.at("strM"));
 m_pdf_Q0->Initialize(setting.IFun, FlavorList, FlagList);
 if(setting.EvolveType == "Hoppet"){
   m_hoppet->Initialize(m_pdf_Q0, setting.Qini);
 }
 else if(setting.EvolveType == "APFEL"){
   m_hoppet->InitializeAPFEL(m_pdf_Q0, setting.Qini);
 }
 else if(setting.EvolveType == "APFELxx"){
   m_hoppet->InitializeAPFELxx(m_pdf_Q0, setting.Qini);
 }

 setting.MomentumList = m_pdf_Q0->MomentumList;
 setting.B0List = m_pdf_Q0->B0List;

 // gluM and strM parameter will be reset to 0
 // so the updated Initial gluM and strM need to be replaced
 // we replace those values in setting, then update them in UpdateParameterCentral()
 // The reason we don't update them in Finalize() is, in LMScan, we want to keep the initial input being consistent in each scan
 // Only when changing the k-factor, we want to update all parameters and start another new fit
 setting.InitialgluonMomentum = m_pdf_Q0->gluonMomentum;
 setting.InitialStrangeB0 = m_pdf_Q0->StrangeB0;

 pdsReader* mypdf = m_hoppet->PrepareCTEQTable();
 setting.ConfigPDF(mypdf);
 m_fcn->InitialPDF(setting);

 for(auto iter = setting.NormParDataList.begin(); iter != setting.NormParDataList.end(); iter++){
   for(int i = 0; i < iter->second.size(); i++){
     m_fcn->AllData.at(iter->second.at(i))->InputNormalization(p.at(iter->first));
   }
 }

 if(setting.OtherParameterList.size() > 0){
   for(int idata = 0; idata < setting.DataList.size(); idata++){
     if(setting.DataList.at(idata).OtherKFactors.size() != 0){
       vector<double> zVec;
       for(int i = 0; i < setting.DataList.at(idata).OtherKFactors.size(); i++){
         TString name = setting.DataList.at(idata).OtherKFactors.at(i).at(0);

         double central = 0.0;
         if(p.count(name) > 0 && setting.OtherParameter_isFit.at(name)){
           central = p.at(name);
         }
         else{
           if(setting.OtherParameterCentral.count(name) > 0){
             central = setting.OtherParameterCentral.at(name);
           }
           else{
             central = 0.0;
           }
         }
         zVec.push_back(central);
       }
       m_fcn->AllData.at(idata)->ApplyOtherKFactor(zVec);
     }
   }
   m_fcn->UpdateVBPDataTable();
 }

 cout<<"Totally call function "<<m_fcn->Irun<<" times in the fit."<<endl;
 cout<<"Fitting done! Doing calculation again using new parameters."<<endl;

 double FinalChi2 = m_fcn->GetChi2(true);
 m_fcn->FinalChi2 = FinalChi2;
 DeltaChi2 = m_fcn->InitialChi2 - m_fcn->FinalChi2;
 cout<<"Initial Chi2 = "<<m_fcn->InitialChi2<<" Final Chi2 = "<<FinalChi2<<" Delta Chi2 = "<<DeltaChi2<<endl;
 m_pdf_Q0->ParameterOutput();
 cout<<"gluM = "<<m_pdf_Q0->GetgluonMomentum()<<endl;
 cout<<"strM = "<<m_pdf_Q0->GetStrangeB0()<<endl;
 if(m_setting->FittingParameter.count("N71") > 0) cout<<"N71  = "<<m_setting->FittingParameter.at("N71")<<endl;
 if(m_setting->FittingParameter.count("N72") > 0) cout<<"N72  = "<<m_setting->FittingParameter.at("N72")<<endl;
 if(m_setting->FittingParameter.count("N73") > 0) cout<<"N73  = "<<m_setting->FittingParameter.at("N73")<<endl;

 mypdf->OutputPDF("mypdf_bestfit.pds");
 m_hoppet->OutputLHAPDFTable("mypdf_bestfit", 0);

 // The gluon momentum and strange B0 initial value have already been updated
 // Here the gluM and strM should be set to 0.0
 int gluM_index = setting.ParIndex.at("gluM");
 int strM_index = setting.ParIndex.at("strM");
 setting.ParameterList.at(gluM_index).central = 0.0;
 setting.ParameterList.at(strM_index).central = 0.0;

 setting.OutputNewParameterFile(NewParaFileName);
 setting.OutputNewParameterFile("ForIterate.yml");

 if(setting.IFun == 999 || setting.IFun == 99901) m_pdf_Q0->OutputFantoCT18();

 delete mypdf;
}

void GlobalFittingCore::InitialPDF()
{
 m_pdf_Q0->Initialize(setting.IFun, setting.FlavorList, setting.FlagList);

 if(setting.EvolveType == "Hoppet"){
   m_hoppet->Initialize(m_pdf_Q0, setting.Qini);
 }
 else if(setting.EvolveType == "APFEL"){
   m_hoppet->InitializeAPFEL(m_pdf_Q0, setting.Qini);
 }
 else if(setting.EvolveType == "APFELxx"){
   m_hoppet->InitializeAPFELxx(m_pdf_Q0, setting.Qini);
 }

 pdsReader* pdftable = m_hoppet->PrepareCTEQTable();
 m_setting->ConfigPDF(pdftable);

 m_fcn->InitialPDF(*m_setting);

 // For test
 //m_pdf_Q0->ParameterOutput();
 //cout<<fixed<<setprecision(10)<<"gluM = "<<m_pdf_Q0->GetgluonMomentum()<<endl;
 //cout<<fixed<<setprecision(10)<<"strM = "<<m_pdf_Q0->GetStrangeB0()<<endl;

 delete pdftable;
}

void GlobalFittingCore::UpdateIterateParameters(std::vector<double> pars)
{
 int NPar = setting.IterateParList.size();

 for(int i = 0; i < NPar; i++){
   TString ParName = setting.IterateParList.at(i).name;

   setting.FittingParameter.at(ParName) = pars.at(i);

   setting.ParameterList.at(i).central = pars.at(i);
 }

 for(int i = 0; i < NPar; i++){
   int id = setting.IterateParList.at(i).id;

   setting.IDtoParam.at(id) = pars.at(i);
 }

 setting.RefreshShapeParameter();

 map<TString, double> p = setting.FittingParameter;
 vector<TString> FlavorList = setting.FlavorList;

 for(int iflavor = 0; iflavor < FlavorList.size(); iflavor++){
   m_pdf_Q0->SetParameter(FlavorList.at(iflavor), setting.ShapeParameterValue.at(FlavorList.at(iflavor)));
 }

 m_pdf_Q0->SetgluonMomentumPar(p.at("gluM"));
 m_pdf_Q0->SetStrangeB0Par(p.at("strM"));

 InitialPDF();// calling after SetParameter();

 setting.MomentumList = m_pdf_Q0->MomentumList;
 setting.B0List = m_pdf_Q0->B0List;

 for(auto iter = setting.NormParDataList.begin(); iter != setting.NormParDataList.end(); iter++){
   for(int i = 0; i < iter->second.size(); i++){
     m_fcn->AllData.at(iter->second.at(i))->InputNormalization(p.at(iter->first));
   }
 }

 if(setting.OtherParameterList.size() > 0){
   for(int idata = 0; idata < setting.DataList.size(); idata++){
     if(setting.DataList.at(idata).OtherKFactors.size() != 0){
       vector<double> zVec;
       for(int i = 0; i < setting.DataList.at(idata).OtherKFactors.size(); i++){
         TString name = setting.DataList.at(idata).OtherKFactors.at(i).at(0);

         double central = 0.0;
         if(p.count(name) > 0 && setting.OtherParameter_isFit.at(name)){
           central = p.at(name);
         }
         else{
           if(setting.OtherParameterCentral.count(name) > 0){
             central = setting.OtherParameterCentral.at(name);
           }
           else{
             central = 0.0;
           }
         }
         zVec.push_back(central);
       }
       m_fcn->AllData.at(idata)->ApplyOtherKFactor(zVec);
     }
   }
   m_fcn->UpdateVBPDataTable();
 }

// cout<<getTime()<<endl;
// m_pdf_Q0->ParameterOutput();
// cout<<"gluM = "<<m_pdf_Q0->GetgluonMomentum()<<endl;
// cout<<"strM = "<<m_pdf_Q0->GetStrangeB0()<<endl;
//   if(p.count("N71") > 0) cout<<"N71  = "<<p.at("N71")<<endl;
//   if(p.count("N72") > 0) cout<<"N72  = "<<p.at("N72")<<endl;
//   if(p.count("N73") > 0) cout<<"N73  = "<<p.at("N73")<<endl;
// cout<<endl;

 p.clear();
 FlavorList.clear();
}

void GlobalFittingCore::ReadingNewParaFile(TString FileName)
{
     newsetting.ParseParameter(FileName);
     setting.CloneParameter(newsetting);

     map<TString, double> p = setting.FittingParameter;
     vector<TString> FlavorList = setting.FlavorList;

     for(int iflavor = 0; iflavor < FlavorList.size(); iflavor++){
       m_pdf_Q0->SetParameter(FlavorList.at(iflavor), setting.ShapeParameterValue.at(FlavorList.at(iflavor)));
     }

     m_pdf_Q0->SetInitialgluonMomentum(newsetting.InitialgluonMomentum);
     m_pdf_Q0->SetInitialStrangeB0(newsetting.InitialStrangeB0);

     m_pdf_Q0->SetgluonMomentumPar(0.0);
     m_pdf_Q0->SetStrangeB0Par(0.0);

     InitialPDF();// calling after SetParameter();
     m_pdf_Q0->ParameterOutput();

     for(auto iter = setting.NormParDataList.begin(); iter != setting.NormParDataList.end(); iter++){
       for(int idata = 0; idata < iter->second.size(); idata++){
         m_fcn->AllData.at(iter->second.at(idata))->InputNormalization(p.at(iter->first));
       }
     }

     if(setting.OtherParameterList.size() > 0){
       for(int idata = 0; idata < setting.DataList.size(); idata++){
         if(setting.DataList.at(idata).OtherKFactors.size() != 0){
           vector<double> zVec;
           for(int i = 0; i < setting.DataList.at(idata).OtherKFactors.size(); i++){
             TString name = setting.DataList.at(idata).OtherKFactors.at(i).at(0);

             double central = 0.0;
             if(p.count(name) > 0 && setting.OtherParameter_isFit.at(name)){
               central = p.at(name);
             }
             else{
               if(setting.OtherParameterCentral.count(name) > 0){
                 central = setting.OtherParameterCentral.at(name);
               }
               else{
                 central = 0.0;
               }
             }
             zVec.push_back(central);
           }
           m_fcn->AllData.at(idata)->ApplyOtherKFactor(zVec);
         }
       }
       m_fcn->UpdateVBPDataTable();
     }

     for(int i = 0; i < setting.GetNPar(); i++){
       upar.SetValue(newsetting.GetParName(i).Data(), newsetting.GetParCentral(i));
     }
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////

 ////////////////////
 // For PDF LMScan //
 ////////////////////

void GlobalFittingCore::PDFLMScan(int flavor, double x, double Q)
{
 TFile* writefile = new TFile("PDFLMScan.root", "RECREATE");
 writefile->cd();

 //m_fcn->DeleteLMPenalty(1);
 //m_fcn->DeleteLMPenalty(2);

 int nScanPoint = 11;

 vector<double> LambdaSet(nScanPoint);
 vector<double> BestFitSet(nScanPoint);

 map<TString, vector<double>> Chi2Map;
 for(int idata = 0; idata < m_fcn->AllData.size(); idata++){
   Chi2Map[m_fcn->AllData.at(idata)->m_name].resize(nScanPoint);
 }
 Chi2Map[(TString)"Total"].resize(nScanPoint);

 // Get BestFit Chi2
// ROOT::Minuit2::MnMigrad migrad(*this, this->upar);
// ROOT::Minuit2::FunctionMinimum min = migrad(10000);
// FCN.Finalize();
// m_fcn->Chi2(false, true);

 // Scan Lambda
 double PDFUnc = setting.GetPDF(flavor, x, Q) * 0.2;
 double nTimesUnc = 8.0;
 if(flavor == 21) nTimesUnc = 0.5;

 double step = nTimesUnc * 100.0 / PDFUnc / ((double)nScanPoint / 2.0);
 for(int i = 0; i < nScanPoint; i++){
   double lambda = (-1.0) * nTimesUnc * 100.0 / PDFUnc + step * i;
   cout<<"Scan "<<i + 1<<"  lambda = "<<lambda<<"  PDF = "<<setting.GetPDF(flavor, x, Q)<<endl;

   //Quadratic penalty
   double Rs0 = 0.5;
   if(flavor == 21){
     Rs0 = 0.9999 - 0.1 * i;
     lambda = 1.0 / PDFUnc / PDFUnc * 100.0;
   }
   /////////////////////////////////////

   LambdaSet.at(i) = lambda;

   vector<int> LM = {flavor};
   vector<double> dM;

   if(flavor == 21) dM = {lambda, x, Q, Rs0};// only Rs using quadratic penalty
   else dM = {lambda, x, Q};// other PDFs using linear penalty

   TString SavedLMScanResult = (TString)"LMScan_Point" + (i + 1) + (TString)".yml";
   std::filesystem::path file_path = SavedLMScanResult.Data();
   if(!std::filesystem::exists(file_path)){

     m_fcn->BookLMPenalty(500, "PDFLMScan", LM, dM);
  
     NewParaFileName = "Temporary.yml";
     ROOT::Minuit2::FunctionMinimum* min = nullptr;
     for(int ifit = 0; ifit < this->setting.LFit; ifit++){
    
       cout<<"Starting "<<ifit + 1<<" Fit: "<<endl;
       this->ResetFit();
    
       if(this->setting.AlgorithmName == "Simplex"){
         ROOT::Minuit2::MnSimplex migrad(*this, this->upar);
         min = new ROOT::Minuit2::FunctionMinimum(migrad(this->setting.MaxCall));
       }
       else if(this->setting.AlgorithmName == "Migrad"){
         ROOT::Minuit2::MnMigrad migrad(*this, this->upar);
         min = new ROOT::Minuit2::FunctionMinimum(migrad(this->setting.MaxCall));
       }
       else if(this->setting.AlgorithmName == "Minimize"){
         ROOT::Minuit2::MnMinimize migrad(*this, this->upar);
         min = new ROOT::Minuit2::FunctionMinimum(migrad(this->setting.MaxCall));
       }
       else if(this->setting.AlgorithmName == "Fumili"){
         //ROOT::Minuit2::MnFumiliMinimize migrad(*this, this->upar);
         //min = new ROOT::Minuit2::FunctionMinimum(migrad(this->setting.MaxCall));
       }
    
       ROOT::Minuit2::MnUserParameters FinalParam = min->UserParameters();
       vector<double> pars = FinalParam.Params();
       vector<double> parerrs = FinalParam.Errors();
       this->Finalize(pars, parerrs);
    
       this->UpdateParameterCentral();
    
       if(fabs(this->DeltaChi2) < 1.0) break;
     }
  
     ROOT::Minuit2::MnUserParameters FinalParam = min->UserParameters();
     m_fcn->DeleteLMPenalty(500);
     NewParaFileName = (TString)"LMScan_Point" + (int)(i + 1) + ".yml";
     vector<double> pars = FinalParam.Params();
     vector<double> parerrs = FinalParam.Errors();
     this->Finalize(pars, parerrs);
   }
   else{
     cout<<"Reading from "<<SavedLMScanResult<<endl;
     ReadingNewParaFile(SavedLMScanResult);

     this->ResetFit();
   }

   // x-axis
   BestFitSet.at(i) = setting.GetPDF(flavor, x, Q);
   cout<<"PDF after scan = "<<BestFitSet.at(i)<<endl;

   // y-axis
   for(int idata = 0; idata < m_fcn->AllChi2.size(); idata++){
     Chi2Map.at(m_fcn->AllData.at(idata)->m_name).at(i) = m_fcn->AllChi2.at(idata);
   }
   Chi2Map.at((TString)"Total").at(i) = m_fcn->FitChi2;

 }

 double BestFitSolution = Chi2Solution(BestFitSet, Chi2Map.at((TString)"Total"));//find the bestfit of the total chi2

 double xmin = BestFitSet.at(0) - 20.0 * (BestFitSet.at(1) - BestFitSet.at(0));
 double xmax = BestFitSet.at(nScanPoint - 1) + 20.0 * (BestFitSet.at(nScanPoint - 1) - BestFitSet.at(nScanPoint - 2));

 for(auto iter = Chi2Map.begin(); iter != Chi2Map.end(); iter++){

   writefile->cd();

   TString HistName;
   HistName = (TString)"PDFLMScanOriginResult_" + iter->first;
   HistName.ReplaceAll("/", "_");
   HistName.ReplaceAll(".", "_");
   HistName.ReplaceAll("-", "m");

   TString FittingName;
   FittingName = (TString)"PDFLMScanOriginFitting_" + iter->first;
   FittingName.ReplaceAll("/", "_");
   FittingName.ReplaceAll(".", "_");
   FittingName.ReplaceAll("-", "m");

   TString PointName;
   PointName = (TString)"PDFLMScanOriginPoint_" + iter->first;
   PointName.ReplaceAll("/", "_");
   PointName.ReplaceAll(".", "_");
   PointName.ReplaceAll("-", "m");

   PDFLMScanOriginResult[iter->first] = new TGraph(nScanPoint);
   PDFLMScanOriginResult.at(iter->first)->SetName(HistName);
   PDFLMScanOriginResult.at(iter->first)->SetTitle(HistName);

   PDFLMScanOriginPoint[iter->first] = new TGraph(nScanPoint);
   PDFLMScanOriginPoint.at(iter->first)->SetName(PointName);
   PDFLMScanOriginPoint.at(iter->first)->SetTitle(PointName);

   //   a * (x - x0)^2 + b * (x - x0) + c
   // = a * x^2 - (2 * a * x0 - b) * x + (a * x0^2 - b * x0 + c)
   // We move the x point to (x - x0) at first, the x0 is the BestFitSolution of Total Chi2,
   // namely, we fit for a * z^2 + b * z + c, where z = (x - x0)
   // After fit, we set the parameters manually to move back to the original x-axis
   for(int ibin = 1; ibin <= nScanPoint; ibin++){
     PDFLMScanOriginResult.at(iter->first)->SetPointX(ibin, BestFitSet.at(ibin - 1) - BestFitSolution);
     PDFLMScanOriginResult.at(iter->first)->SetPointY(ibin, Chi2Map.at(iter->first).at(ibin - 1));
     PDFLMScanOriginPoint.at(iter->first)->SetPointX(ibin, BestFitSet.at(ibin - 1));
     PDFLMScanOriginPoint.at(iter->first)->SetPointY(ibin, Chi2Map.at(iter->first).at(ibin - 1));
     cout<<"ScanResult for Data "<<iter->first<<": Lambda = "<<LambdaSet.at(ibin - 1)<<" BestFit = "<<BestFitSet.at(ibin - 1)<<" Chi2 = "<<Chi2Map.at(iter->first).at(ibin - 1)<<endl;
   }
   PDFLMScanOriginResult.at(iter->first)->RemovePoint(0);
   PDFLMScanOriginResult.at(iter->first)->SetMarkerSize(0);
   PDFLMScanOriginResult.at(iter->first)->SetMarkerColor(0);
   PDFLMScanOriginResult.at(iter->first)->SetLineWidth(0);
   PDFLMScanOriginResult.at(iter->first)->SetLineColor(0);
   PDFLMScanOriginResult.at(iter->first)->SetLineStyle(1);
   PDFLMScanOriginResult.at(iter->first)->SetMarkerStyle(34);
   PDFLMScanOriginPoint.at(iter->first)->RemovePoint(0);

   PDFLMScanOriginFitting[iter->first] = new TF1(FittingName, "[0]*x*x+[1]*x+[2]", xmin, xmax);
   if(iter->first == "Total") PDFLMScanOriginFitting.at(iter->first)->SetNpx(50000);
   PDFLMScanOriginResult.at(iter->first)->Fit(PDFLMScanOriginFitting.at(iter->first), "W");

   double par1 = PDFLMScanOriginFitting.at(iter->first)->GetParameter(0);
   double par2 = PDFLMScanOriginFitting.at(iter->first)->GetParameter(1);
   double par3 = PDFLMScanOriginFitting.at(iter->first)->GetParameter(2);
   double newpar1 = par1;
   double newpar2 = -1.0 * (2.0 * par1 * BestFitSolution - par2);
   double newpar3 = par1 * BestFitSolution * BestFitSolution - par2 * BestFitSolution + par3;
   PDFLMScanOriginFitting.at(iter->first)->SetParameter(0, newpar1);
   PDFLMScanOriginFitting.at(iter->first)->SetParameter(1, newpar2);
   PDFLMScanOriginFitting.at(iter->first)->SetParameter(2, newpar3);

   ///////////////////////////////////////////////////////////////////////////////////////////////////////
   HistName.ReplaceAll("PDFLMScanOriginResult", "PDFLMScanResult");
   FittingName.ReplaceAll("PDFLMScanOriginFitting", "PDFLMScanFitting");
   PointName.ReplaceAll("PDFLMScanOriginPoint", "PDFLMScanPoint");

   PDFLMScanResult[iter->first] = new TGraph(nScanPoint);
   PDFLMScanResult.at(iter->first)->SetName(HistName);
   PDFLMScanResult.at(iter->first)->SetTitle(HistName);

   PDFLMScanPoint[iter->first] = new TGraph(nScanPoint);
   PDFLMScanPoint.at(iter->first)->SetName(PointName);
   PDFLMScanPoint.at(iter->first)->SetTitle(PointName);

   for(int ibin = 1; ibin <= nScanPoint; ibin++){
     double DataOriginChi2 = PDFLMScanOriginFitting.at(iter->first)->Eval(BestFitSolution);

     PDFLMScanResult.at(iter->first)->SetPointX(ibin, BestFitSet.at(ibin - 1) - BestFitSolution);
     PDFLMScanResult.at(iter->first)->SetPointY(ibin, Chi2Map.at(iter->first).at(ibin - 1) - DataOriginChi2);
     PDFLMScanPoint.at(iter->first)->SetPointX(ibin, BestFitSet.at(ibin - 1));
     PDFLMScanPoint.at(iter->first)->SetPointY(ibin, Chi2Map.at(iter->first).at(ibin - 1) - DataOriginChi2);
     cout<<"ScanResult for Data "<<iter->first<<": Lambda = "<<LambdaSet.at(ibin - 1)<<" BestFit = "<<BestFitSet.at(ibin - 1)<<" Chi2 = "<<Chi2Map.at(iter->first).at(ibin - 1) - DataOriginChi2<<endl;
   }
   PDFLMScanResult.at(iter->first)->RemovePoint(0);
   PDFLMScanResult.at(iter->first)->SetMarkerSize(0);
   PDFLMScanResult.at(iter->first)->SetMarkerColor(0);
   PDFLMScanResult.at(iter->first)->SetLineWidth(0);
   PDFLMScanResult.at(iter->first)->SetLineColor(0);
   PDFLMScanResult.at(iter->first)->SetLineStyle(1);
   PDFLMScanResult.at(iter->first)->SetMarkerStyle(34);
   PDFLMScanPoint.at(iter->first)->RemovePoint(0);

   PDFLMScanFitting[iter->first] = new TF1(FittingName, "[0]*x*x+[1]*x+[2]", xmin, xmax);
   if(iter->first == "Total") PDFLMScanFitting.at(iter->first)->SetNpx(50000);
   PDFLMScanResult.at(iter->first)->Fit(PDFLMScanFitting.at(iter->first), "W");

   par1 = PDFLMScanFitting.at(iter->first)->GetParameter(0);
   par2 = PDFLMScanFitting.at(iter->first)->GetParameter(1);
   par3 = PDFLMScanFitting.at(iter->first)->GetParameter(2);
   newpar1 = par1;
   newpar2 = -1.0 * (2.0 * par1 * BestFitSolution - par2);
   newpar3 = par1 * BestFitSolution * BestFitSolution - par2 * BestFitSolution + par3;
   PDFLMScanFitting.at(iter->first)->SetParameter(0, newpar1);
   PDFLMScanFitting.at(iter->first)->SetParameter(1, newpar2);
   PDFLMScanFitting.at(iter->first)->SetParameter(2, newpar3);

   PDFLMScanOriginResult.at(iter->first)->Write();
   PDFLMScanOriginFitting.at(iter->first)->Write();
   PDFLMScanOriginPoint.at(iter->first)->Write();
   PDFLMScanResult.at(iter->first)->Write();
   PDFLMScanFitting.at(iter->first)->Write();
   PDFLMScanPoint.at(iter->first)->Write();
 }

 DefineCombination();

 TString FigureName;
 FigureName = (TString)"PDFLMScanFitting_" + FlavorNameMap[flavor] + "_x" + TString::Format("%.2f", x) + "_Q" + TString::Format("%.1f", Q) + ".pdf";
 TString XaxisName = TitleMap[flavor] + "(x = " + TString::Format("%.2f", x) + ", Q = " + TString::Format("%.1f", Q) + " GeV)";
 TString YaxisName = "#Delta #chi^{2}";

 map<TString, TString> DataLegend;

 FittingHelper* f = new FittingHelper();
 f->DefineCTEQDataLegend(DataLegend);
 f->DrawLMScanPlot(PDFLMScanFitting, FigureName, XaxisName, YaxisName);

 writefile->Close();
}

void GlobalFittingCore::AlphaSLMScan()
{
 TFile* writefile = new TFile("AlphaSLMScan.root", "RECREATE");
 writefile->cd();

 int nScanPoint = 10;

 vector<double> AlphasSet = {0.113, 0.114, 0.115, 0.116, 0.117, 0.118, 0.119, 0.120, 0.121, 0.122};

 if(nScanPoint != AlphasSet.size()) cout<<"ERROR! Check the AlphasSet input!"<<endl;

 map<TString, vector<double>> Chi2Map;
 for(int idata = 0; idata < m_fcn->AllData.size(); idata++){
   Chi2Map[m_fcn->AllData.at(idata)->m_name].resize(nScanPoint);
 }
 Chi2Map[(TString)"Total"].resize(nScanPoint);

 // Get BestFit Chi2
// ROOT::Minuit2::MnMigrad migrad(*this, this->upar);
// ROOT::Minuit2::FunctionMinimum min = migrad(10000);
// FCN.Finalize();
// m_fcn->Chi2(false, true);

 vector<double> pars = GetInitialParameters();
 vector<double> parerrs;

 // Scan Lambda
 for(int i = 0; i < nScanPoint; i++){
   cout<<"Scan "<<i + 1<<endl;

   TString SavedLMScanResult = (TString)"AlphaS_" + TString::Format("%.3f", AlphasSet.at(i)) + (TString)".yml";
   std::filesystem::path file_path = SavedLMScanResult.Data();
   if(!std::filesystem::exists(file_path)){

     NewParaFileName = "Temporary.yml";
     ROOT::Minuit2::FunctionMinimum* min = nullptr;
     for(int ifit = 0; ifit < this->setting.LFit; ifit++){

       cout<<"Starting "<<ifit + 1<<" Fit: "<<endl;
       setting.AlphaS = AlphasSet.at(i);
       m_hoppet->SetAlphaSQ0(AlphasSet.at(i), setting.AlphaS_Q0);
       this->chi2(pars);
       this->ResetFit();

       if(this->setting.AlgorithmName == "Simplex"){
         ROOT::Minuit2::MnSimplex migrad(*this, this->upar);
         min = new ROOT::Minuit2::FunctionMinimum(migrad(this->setting.MaxCall));
       }
       else if(this->setting.AlgorithmName == "Migrad"){
         ROOT::Minuit2::MnMigrad migrad(*this, this->upar);
         min = new ROOT::Minuit2::FunctionMinimum(migrad(this->setting.MaxCall));
       }
       else if(this->setting.AlgorithmName == "Minimize"){
         ROOT::Minuit2::MnMinimize migrad(*this, this->upar);
         min = new ROOT::Minuit2::FunctionMinimum(migrad(this->setting.MaxCall));
       }
       else if(this->setting.AlgorithmName == "Fumili"){
         //ROOT::Minuit2::MnFumiliMinimize migrad(*this, this->upar);
         //min = new ROOT::Minuit2::FunctionMinimum(migrad(this->setting.MaxCall));
       }

       ROOT::Minuit2::MnUserParameters FinalParam = min->UserParameters();
       pars = FinalParam.Params();
       parerrs = FinalParam.Errors();
       this->Finalize(pars, parerrs);

       this->UpdateParameterCentral();

       if(fabs(this->DeltaChi2) < 1.0) break;
     }

     ROOT::Minuit2::MnUserParameters FinalParam = min->UserParameters();
     NewParaFileName = (TString)"AlphaS_" + TString::Format("%.3f", AlphasSet.at(i)) + (TString)".yml";
     pars = FinalParam.Params();
     parerrs = FinalParam.Errors();
     this->Finalize(pars, parerrs);
   }
   else{
     cout<<"Reading from "<<SavedLMScanResult<<endl;

     setting.AlphaS = AlphasSet.at(i);
     m_hoppet->SetAlphaSQ0(AlphasSet.at(i), setting.AlphaS_Q0);

     ReadingNewParaFile(SavedLMScanResult);

     this->ResetFit();

     pars = newsetting.GetInitialParameters();
   }

   // y-axis
   for(int idata = 0; idata < m_fcn->AllChi2.size(); idata++){
     Chi2Map.at(m_fcn->AllData.at(idata)->m_name).at(i) = m_fcn->AllChi2.at(idata);
   }
   Chi2Map.at((TString)"Total").at(i) = m_fcn->FitChi2;

 }

 double BestFitSolution = Chi2Solution(AlphasSet, Chi2Map.at((TString)"Total"));//find the bestfit of the total chi2

 double xmin = AlphasSet.at(0) - (AlphasSet.at(1) - AlphasSet.at(0));
 double xmax = AlphasSet.at(nScanPoint - 1) + (AlphasSet.at(nScanPoint - 1) - AlphasSet.at(nScanPoint - 2));

 for(auto iter = Chi2Map.begin(); iter != Chi2Map.end(); iter++){

   writefile->cd();

   TString HistName;
   HistName = (TString)"AlphaSLMScanOriginResult_" + iter->first;
   HistName.ReplaceAll("/", "_");
   HistName.ReplaceAll(".", "_");
   HistName.ReplaceAll("-", "m");

   TString FittingName;
   FittingName = (TString)"AlphaSLMScanOriginFitting_" + iter->first;
   FittingName.ReplaceAll("/", "_");
   FittingName.ReplaceAll(".", "_");
   FittingName.ReplaceAll("-", "m");

   TString PointName;
   PointName = (TString)"AlphaSLMScanOriginPoint_" + iter->first;
   PointName.ReplaceAll("/", "_");
   PointName.ReplaceAll(".", "_");
   PointName.ReplaceAll("-", "m");

   AlphaSLMScanOriginResult[iter->first] = new TGraph(nScanPoint);
   AlphaSLMScanOriginResult.at(iter->first)->SetName(HistName);
   AlphaSLMScanOriginResult.at(iter->first)->SetTitle(HistName);

   AlphaSLMScanOriginPoint[iter->first] = new TGraph(nScanPoint);
   AlphaSLMScanOriginPoint.at(iter->first)->SetName(PointName);
   AlphaSLMScanOriginPoint.at(iter->first)->SetTitle(PointName);

   for(int ibin = 1; ibin <= nScanPoint; ibin++){
     AlphaSLMScanOriginResult.at(iter->first)->SetPointX(ibin, AlphasSet.at(ibin - 1));
     AlphaSLMScanOriginResult.at(iter->first)->SetPointY(ibin, Chi2Map.at(iter->first).at(ibin - 1));
     AlphaSLMScanOriginPoint.at(iter->first)->SetPointX(ibin, AlphasSet.at(ibin - 1));
     AlphaSLMScanOriginPoint.at(iter->first)->SetPointY(ibin, Chi2Map.at(iter->first).at(ibin - 1));
     cout<<"ScanResult for Data "<<iter->first<<": AlphaS = "<<AlphasSet.at(ibin - 1)<<" Chi2 = "<<Chi2Map.at(iter->first).at(ibin - 1)<<endl;
   }
   AlphaSLMScanOriginResult.at(iter->first)->RemovePoint(0);
   AlphaSLMScanOriginResult.at(iter->first)->SetMarkerSize(0);
   AlphaSLMScanOriginResult.at(iter->first)->SetMarkerColor(0);
   AlphaSLMScanOriginResult.at(iter->first)->SetLineWidth(0);
   AlphaSLMScanOriginResult.at(iter->first)->SetLineColor(0);
   AlphaSLMScanOriginResult.at(iter->first)->SetLineStyle(1);
   AlphaSLMScanOriginResult.at(iter->first)->SetMarkerStyle(34);
   AlphaSLMScanOriginPoint.at(iter->first)->RemovePoint(0);

   AlphaSLMScanOriginFitting[iter->first] = new TF1(FittingName, "[0]*x*x+[1]*x+[2]", xmin, xmax);
   if(iter->first == "Total") AlphaSLMScanOriginFitting.at(iter->first)->SetNpx(50000);
   AlphaSLMScanOriginResult.at(iter->first)->Fit(AlphaSLMScanOriginFitting.at(iter->first), "W");

   ///////////////////////////////////////////////////////////////////////////////////////////////////////
   HistName.ReplaceAll("AlphaSLMScanOriginResult", "AlphaSLMScanResult");
   FittingName.ReplaceAll("AlphaSLMScanOriginFitting", "AlphaSLMScanFitting");
   PointName.ReplaceAll("AlphaSLMScanOriginPoint", "AlphaSLMScanPoint");

   AlphaSLMScanResult[iter->first] = new TGraph(nScanPoint);
   AlphaSLMScanResult.at(iter->first)->SetName(HistName);
   AlphaSLMScanResult.at(iter->first)->SetTitle(HistName);

   AlphaSLMScanPoint[iter->first] = new TGraph(nScanPoint);
   AlphaSLMScanPoint.at(iter->first)->SetName(PointName);
   AlphaSLMScanPoint.at(iter->first)->SetTitle(PointName);

   for(int ibin = 1; ibin <= nScanPoint; ibin++){
     double DataOriginChi2 = AlphaSLMScanOriginFitting.at(iter->first)->Eval(BestFitSolution);

     AlphaSLMScanResult.at(iter->first)->SetPointX(ibin, AlphasSet.at(ibin - 1));
     AlphaSLMScanResult.at(iter->first)->SetPointY(ibin, Chi2Map.at(iter->first).at(ibin - 1) - DataOriginChi2);
     AlphaSLMScanPoint.at(iter->first)->SetPointX(ibin, AlphasSet.at(ibin - 1));
     AlphaSLMScanPoint.at(iter->first)->SetPointY(ibin, Chi2Map.at(iter->first).at(ibin - 1) - DataOriginChi2);
     cout<<"ScanResult for Data "<<iter->first<<": AlphaS = "<<AlphasSet.at(ibin - 1)<<" Chi2 = "<<Chi2Map.at(iter->first).at(ibin - 1) - DataOriginChi2<<endl;
   }
   AlphaSLMScanResult.at(iter->first)->RemovePoint(0);
   AlphaSLMScanResult.at(iter->first)->SetMarkerSize(0);
   AlphaSLMScanResult.at(iter->first)->SetMarkerColor(0);
   AlphaSLMScanResult.at(iter->first)->SetLineWidth(0);
   AlphaSLMScanResult.at(iter->first)->SetLineColor(0);
   AlphaSLMScanResult.at(iter->first)->SetLineStyle(1);
   AlphaSLMScanResult.at(iter->first)->SetMarkerStyle(34);
   AlphaSLMScanPoint.at(iter->first)->RemovePoint(0);

   AlphaSLMScanFitting[iter->first] = new TF1(FittingName, "[0]*x*x+[1]*x+[2]", xmin, xmax);
   if(iter->first == "Total") AlphaSLMScanFitting.at(iter->first)->SetNpx(50000);
   AlphaSLMScanResult.at(iter->first)->Fit(AlphaSLMScanFitting.at(iter->first), "W");

   AlphaSLMScanOriginResult.at(iter->first)->Write();
   AlphaSLMScanOriginFitting.at(iter->first)->Write();
   AlphaSLMScanOriginPoint.at(iter->first)->Write();
   AlphaSLMScanResult.at(iter->first)->Write();
   AlphaSLMScanFitting.at(iter->first)->Write();
   AlphaSLMScanPoint.at(iter->first)->Write();
 }

 writefile->Close();
}

