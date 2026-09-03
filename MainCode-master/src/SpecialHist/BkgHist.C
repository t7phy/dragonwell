#include "SpecialHist/BkgHist.h"

using namespace std;

BkgHist::BkgHist(TString ProcessName)
{
 this->ProcessName = ProcessName;

 DefineBkgName(ProcessName);
 GetRequiredList(ProcessName);
}

void BkgHist::DefineHist(TString name, TString title, int nbin, double left, double right, int iflag)
{
 if(iflag == 0){
   NoBkgHist = true;
   return;
 }

 this->HistName = name;

 for(int ibkg = 0; ibkg < bkgName.size(); ibkg++){
   myHist[ibkg] = new TH1D(name + "_" + bkgName.at(ibkg), title + "_" + bkgName.at(ibkg), nbin, left, right);
   myHist[ibkg]->Sumw2();

   BkgHist_1d.push_back(myHist[ibkg]);
 }

 DefineAdditionalHist(name, title, nbin, left, right);

 Dimension = 1;
}

void BkgHist::DefineHist(TString name, TString title, int nbin, double* xbins, int iflag)
{
 if(iflag == 0){
   NoBkgHist = true;
   return;
 }

 this->HistName = name;

 for(int ibkg = 0; ibkg < bkgName.size(); ibkg++){
   myHist[ibkg] = new TH1D(name + "_" + bkgName.at(ibkg), title + "_" + bkgName.at(ibkg), nbin, xbins);
   myHist[ibkg]->Sumw2();

   BkgHist_1d.push_back(myHist[ibkg]);
 }

 DefineAdditionalHist(name, title, nbin, xbins);

 Dimension = 1;
}

void BkgHist::DefineHist(TString name, TString title, int nbinx, double leftx, double rightx, int nbiny, double lefty, double righty, int iflag)
{
 if(iflag == 0){
   NoBkgHist = true;
   return;
 }

 this->HistName = name;

 for(int ibkg = 0; ibkg < bkgName.size(); ibkg++){
   myHist2D[ibkg] = new TH2D(name + "_" + bkgName.at(ibkg), title + "_" + bkgName.at(ibkg), nbinx, leftx, rightx, nbiny, lefty, righty);
   myHist2D[ibkg]->Sumw2();

   BkgHist_2d.push_back(myHist2D[ibkg]);
 }

 DefineAdditionalHist(name, title, nbinx, leftx, rightx, nbiny, lefty, righty);

 Dimension = 2;
}

void BkgHist::DefineHist(TString name, TString title, int nbinx, double* xbins, int nbiny, double* ybins, int iflag)
{
 if(iflag == 0){
   NoBkgHist = true;
   return;
 }

 this->HistName = name;

 for(int ibkg = 0; ibkg < bkgName.size(); ibkg++){
   myHist2D[ibkg] = new TH2D(name + "_" + bkgName.at(ibkg), title + "_" + bkgName.at(ibkg), nbinx, xbins, nbiny, ybins);
   myHist2D[ibkg]->Sumw2();

   BkgHist_2d.push_back(myHist2D[ibkg]);
 }

 DefineAdditionalHist(name, title, nbinx, xbins, nbiny, ybins);

 Dimension = 2;
}

void BkgHist::Initial(int MCType)
{
 this->MCType = MCType;

 if(ProcessName == "WSignal_Electron" || ProcessName == "WSignal_Muon" || ProcessName == "ZSignal_Electron" || ProcessName == "ZSignal_Muon"){
 //For W asymmetry analysis
   if(MCType == 361102 || MCType == 361105 || MCType == 361108){
     iBkg = NameIndex["BkgTau"];
   }
   else if(MCType == 363356 || MCType == 363358 || MCType == 363359 || MCType == 363360 || MCType == 363489){
     iBkg = NameIndex["BkgDiboson"];
   }
   else if(MCType == 364250 || MCType == 364253 || MCType == 364254 || MCType == 364255){
     iBkg = NameIndex["BkgDiboson"];
   }
   else if(MCType == 410013 || MCType == 410014){
     iBkg = NameIndex["BkgWtop"];
   }
   else if(MCType == 410470){
     iBkg = NameIndex["Bkgttbar"];
   }
   else if(MCType == 410642 || MCType == 410643 || MCType == 410644 || MCType == 410645){
     iBkg = NameIndex["BkgSingletop"];
   }
   else if(ProcessName == "WSignal_Electron" && MCType == 361106){
     iBkg = NameIndex["BkgWZ"];
   }
   else if(ProcessName == "WSignal_Muon" && MCType == 361107){
     iBkg = NameIndex["BkgWZ"];
   }
   else if(ProcessName == "ZSignal_Electron" && (MCType == 361100 || MCType == 361103)){
     iBkg = NameIndex["BkgWZ"];
   }
   else if(ProcessName == "ZSignal_Muon" && (MCType == 361101 || MCType == 361104)){
     iBkg = NameIndex["BkgWZ"];
   }
   else{
     iBkg = -1;
   }
 }
 else if(ProcessName == "SignalWZ" || ProcessName == "ZZControlRegion" || ProcessName == "TopControlRegion"){
 //For WZ polarization analysis
   if(MCType == 345705 || MCType == 345706){
     ShortName = "BkgZZ";
     iBkg = NameIndex["BkgZZ"];
   }
   else if(MCType == 361106 || MCType == 361107 || MCType == 361108){
     ShortName = "BkgZjet";
     iBkg = NameIndex["BkgZjet"];
   }
   else if(MCType == 361292 || MCType == 361293){
     ShortName = "Unused";
     iBkg = -1;
   }
   else if(MCType == 364242 || MCType == 364243 || MCType == 364244 || MCType == 364245 || MCType == 364246 || MCType == 364247 || MCType == 364248 || MCType == 364249){
     ShortName = "BkgVVV";
     iBkg = NameIndex["BkgVVV"];
   }
   else if(MCType == 364250){
     ShortName = "BkgZZ";
     iBkg = NameIndex["BkgZZ"];
   }
   else if(MCType == 364253){
     ShortName = "BkgWZQCD";
     iBkg = NameIndex["BkgWZQCD"];
   }
   else if(MCType == 361601){
     ShortName = "BkgWZQCD";
     iBkg = NameIndex["BkgWZQCD"];
   }
   else if(MCType == 364254){
     ShortName = "BkgZZ";
     iBkg = NameIndex["BkgZZ"];
   }
   else if(MCType == 364283){
     ShortName = "BkgZZ";
     iBkg = NameIndex["BkgZZ"];
   }
   else if(MCType == 364284){
     ShortName = "BkgWZEW";
     iBkg = NameIndex["BkgWZEW"];
   }
   else if(MCType == 364739 || MCType == 364740 || MCType == 364741 || MCType == 364742){
     ShortName = "BkgWZEW";
     iBkg = NameIndex["BkgWZEW"];
   }
   else if(MCType == 366140 || MCType == 366141 || MCType == 366142 || MCType == 366143 || MCType == 366144){
     ShortName = "BkgZgamma";
     iBkg = NameIndex["BkgZgamma"];
   }
   else if(MCType == 366145 || MCType == 366146 || MCType == 366147 || MCType == 366148 || MCType == 366149){
     ShortName = "BkgZgamma";
     iBkg = NameIndex["BkgZgamma"];
   }
   else if(MCType == 366150 || MCType == 366151 || MCType == 366152 || MCType == 366153 || MCType == 366154){
     ShortName = "BkgZgamma";
     iBkg = NameIndex["BkgZgamma"];
   }
   else if(MCType == 410155 || MCType == 410218 || MCType == 410219){
     ShortName = "BkgttbarV";
     iBkg = NameIndex["BkgttbarV"];
   }
   else if(MCType == 410470){
     ShortName = "BkgTop";
     iBkg = NameIndex["BkgTop"];
   }
   else if(MCType == 410550){
     ShortName = "BkgtZ";
     iBkg = NameIndex["BkgtZ"];
   }
   else if(MCType == 410644 || MCType == 410645 || MCType == 410646 || MCType == 410647 || MCType == 410648 || MCType == 410649){
     ShortName = "BkgTop";
     iBkg = NameIndex["BkgTop"];
   }
   else if(MCType == 410658 || MCType == 410659){
     ShortName = "BkgTop";
     iBkg = NameIndex["BkgTop"];
   }
   else if(MCType == -1){
     ShortName = "Data";
     iBkg = NameIndex["Data"];
   }
   else{
     ShortName = "Unused";
     iBkg = -1;
   }
 }
 else if(ProcessName == "WZPolarized"){
 //For WZ polarization analysis
   if(MCType == 364253){
     ShortName = "Total";
     iBkg = NameIndex["Total"];
   }
   else if(MCType == 361601){
     ShortName = "Total";
     iBkg = NameIndex["Total"];
   }
   else if(MCType == 364991 || MCType == 501793 || MCType == 501794 || MCType == 500291 || MCType == 500295
                            || MCType == 507019 || MCType == 507020 || MCType == 507027 || MCType == 507028){
     ShortName = "LL";
     iBkg = NameIndex["LL"];
   }
   else if(MCType == 364992 || MCType == 501795 || MCType == 501796 || MCType == 500290 || MCType == 500294
                            || MCType == 507021 || MCType == 507022 || MCType == 507029 || MCType == 507030){
     ShortName = "LT";
     iBkg = NameIndex["LT"];
   }
   else if(MCType == 364993 || MCType == 501797 || MCType == 501798 || MCType == 500292 || MCType == 500296
                            || MCType == 507023 || MCType == 507024 || MCType == 507031 || MCType == 507032){
     ShortName = "TL";
     iBkg = NameIndex["TL"];
   }
   else if(MCType == 364994 || MCType == 501799 || MCType == 501800 || MCType == 500293 || MCType == 500297
                            || MCType == 507025 || MCType == 507026 || MCType == 507033 || MCType == 507034){
     ShortName = "TT";
     iBkg = NameIndex["TT"];
   }
   else{
     ShortName = "Unused";
     iBkg = -1;
   }
 }

 if(ProcessName == RequiredProcessName){
   if(ListFlag[MCType] == 0){
     ShortName = "Unused";
     iBkg = -1;
   }
 }
}

void BkgHist::Initial(TString MCTypeName)
{
 this->MCTypeName = MCTypeName;

 if(ProcessName == "QBH"){
   if(MCTypeName == "ttbar" || MCTypeName == "ttV"){
     ShortName = "ttbar";
     iBkg = NameIndex.at("ttbar");
   }
   else if(MCTypeName == "singletop"){
     ShortName = "singletop";
     iBkg = NameIndex.at("singletop");
   }
   else if(MCTypeName == "Zee" || MCTypeName == "Zmm" || MCTypeName == "Ztt"){
     ShortName = "Zjets";
     iBkg = NameIndex.at("Zjets");
   }
   else if(MCTypeName == "Wenu" || MCTypeName == "Wmnu" || MCTypeName == "Wtnu"){
     ShortName = "Wjets";
     iBkg = NameIndex.at("Wjets");
   }
   else if(MCTypeName == "dijet"){
     ShortName = "dijet";
     iBkg = NameIndex.at("dijet");
   }
   else if(MCTypeName == "diboson"){
     ShortName = "diboson";
     iBkg = NameIndex.at("diboson");
   }
   else if(MCTypeName == "data"){
     ShortName = "data";
     iBkg = NameIndex.at("data");
   }
   else{
     ShortName = "Unused";
     iBkg = -1;
   }
 }

 if(ProcessName == "HMDY" || ProcessName == "HMDY_MuFakes"){
   ShortName = MCTypeName;
   if(NameIndex.count(MCTypeName) > 0) iBkg = NameIndex.at(MCTypeName);
   else iBkg = -1;
 }

 if(ProcessName == "ZPrime" || ProcessName == "ZPrime_MuFakes"){
   ShortName = MCTypeName;
   if(NameIndex.count(MCTypeName) > 0) iBkg = NameIndex.at(MCTypeName);
   else iBkg = -1;
 }

}

void BkgHist::DefineBkgName(TString ProcessName)
{
 if(ProcessName == "SignalWZ"){
   bkgName.push_back("BkgZZ");
   bkgName.push_back("BkgZjet");
   bkgName.push_back("BkgVVV");
   bkgName.push_back("BkgWZEW");
   bkgName.push_back("BkgZgamma");
   bkgName.push_back("BkgttbarV");
   bkgName.push_back("BkgTop");
   bkgName.push_back("BkgtZ");
   bkgName.push_back("BkgWZQCD");
   bkgName.push_back("Data");
 }

 if(ProcessName == "ZZControlRegion"){
   bkgName.push_back("BkgZZ");
   bkgName.push_back("BkgZjet");
   bkgName.push_back("BkgVVV");
   bkgName.push_back("BkgWZEW");
   bkgName.push_back("BkgZgamma");
   bkgName.push_back("BkgttbarV");
   bkgName.push_back("BkgTop");
   bkgName.push_back("BkgtZ");
   bkgName.push_back("BkgWZQCD");
   bkgName.push_back("Data");
 }

 if(ProcessName == "TopControlRegion"){
   bkgName.push_back("BkgZZ");
   bkgName.push_back("BkgZjet");
   bkgName.push_back("BkgVVV");
   bkgName.push_back("BkgWZEW");
   bkgName.push_back("BkgZgamma");
   bkgName.push_back("BkgttbarV");
   bkgName.push_back("BkgTop");
   bkgName.push_back("BkgtZ");
   bkgName.push_back("BkgWZQCD");
   bkgName.push_back("Data");
 }

 if(ProcessName == "WZPolarized"){
   bkgName.push_back("Total");
   bkgName.push_back("LL");
   bkgName.push_back("LT");
   bkgName.push_back("TL");
   bkgName.push_back("TT");
 }

 if(ProcessName == "QBH"){
   bkgName.push_back("ttbar");
   bkgName.push_back("singletop");
   bkgName.push_back("Zjets");
   bkgName.push_back("Wjets");
   bkgName.push_back("dijet");
   bkgName.push_back("diboson");
   bkgName.push_back("data");
 }

 if(ProcessName == "HMDY"){
   bkgName.push_back("DrellYan");
   bkgName.push_back("PhotonInduced");
   bkgName.push_back("TopQuark");
   bkgName.push_back("Diboson");
   bkgName.push_back("Wjets_DD");
   bkgName.push_back("Ztautau");
   bkgName.push_back("Wjets");
   bkgName.push_back("Data");
 }

 if(ProcessName == "HMDY_MuFakes"){
   bkgName.push_back("DrellYan");
   bkgName.push_back("PhotonInduced");
   bkgName.push_back("TopQuark");
   bkgName.push_back("Diboson");
   bkgName.push_back("Wjets_DD");
   bkgName.push_back("Ztautau");
   bkgName.push_back("Wjets");
   bkgName.push_back("Triboson");
   bkgName.push_back("ttV");
   bkgName.push_back("Data");
 }

 if(ProcessName == "ZPrime"){
   bkgName.push_back("DrellYan");
   bkgName.push_back("TopQuark");
   bkgName.push_back("Diboson");
   bkgName.push_back("Wjets_DD");
   bkgName.push_back("Wjets");
   bkgName.push_back("Data");
 }

 if(ProcessName == "ZPrime_MuFakes"){
   bkgName.push_back("DrellYan");
   bkgName.push_back("TopQuark");
   bkgName.push_back("Diboson");
   bkgName.push_back("Wjets");
   bkgName.push_back("Data");
 }

 for(int i = 0; i < bkgName.size(); i++){
   NameIndex[bkgName.at(i)] = i;
 }

}

void BkgHist::GetRequiredList(TString ProcessName)
{
 UsedList.clear();
 if(ProcessName == "SignalWZ" || ProcessName == "ZZControlRegion" || ProcessName == "TopControlRegion"){
   this->RequiredProcessName = ProcessName;

   UsedList.push_back("364253_Sherpa_222_NNPDF30NNLO_lllv");
   UsedList.push_back("361601_PowhegPy8EG_CT10nloME_AZNLOCTEQ6L1_WZlvll_mll4");
   UsedList.push_back("364739_MGPy8EG_NNPDF30NLO_A14NNPDF23LO_lvlljjEW6_OFMinus");
   UsedList.push_back("364740_MGPy8EG_NNPDF30NLO_A14NNPDF23LO_lvlljjEW6_OFPlus");
   UsedList.push_back("364741_MGPy8EG_NNPDF30NLO_A14NNPDF23LO_lvlljjEW6_SFMinus");
   UsedList.push_back("364742_MGPy8EG_NNPDF30NLO_A14NNPDF23LO_lvlljjEW6_SFPlus");
   UsedList.push_back("345705_Sherpa_222_NNPDF30NNLO_ggllll_0M4l130");
   UsedList.push_back("345706_Sherpa_222_NNPDF30NNLO_ggllll_130M4l");
   UsedList.push_back("364250_Sherpa_222_NNPDF30NNLO_llll");
   UsedList.push_back("364283_Sherpa_222_NNPDF30NNLO_lllljj_EW6");
   UsedList.push_back("364254_Sherpa_222_NNPDF30NNLO_llvv");
   UsedList.push_back("361106_PowhegPythia8EvtGen_AZNLOCTEQ6L1_Zee");
   UsedList.push_back("361107_PowhegPythia8EvtGen_AZNLOCTEQ6L1_Zmumu");
   UsedList.push_back("361108_PowhegPythia8EvtGen_AZNLOCTEQ6L1_Ztautau");
   UsedList.push_back("364242_Sherpa_222_NNPDF30NNLO_WWW_3l3v_EW6");
   UsedList.push_back("364243_Sherpa_222_NNPDF30NNLO_WWZ_4l2v_EW6");
   UsedList.push_back("364244_Sherpa_222_NNPDF30NNLO_WWZ_2l4v_EW6");
   UsedList.push_back("364245_Sherpa_222_NNPDF30NNLO_WZZ_5l1v_EW6");
   UsedList.push_back("364246_Sherpa_222_NNPDF30NNLO_WZZ_3l3v_EW6");
   UsedList.push_back("364247_Sherpa_222_NNPDF30NNLO_ZZZ_6l0v_EW6");
   UsedList.push_back("364248_Sherpa_222_NNPDF30NNLO_ZZZ_4l2v_EW6");
   UsedList.push_back("364249_Sherpa_222_NNPDF30NNLO_ZZZ_2l4v_EW6");
   UsedList.push_back("366140_Sh_224_NN30NNLO_eegamma_LO_pty_7_15");
   UsedList.push_back("366141_Sh_224_NN30NNLO_eegamma_LO_pty_15_35");
   UsedList.push_back("366142_Sh_224_NN30NNLO_eegamma_LO_pty_35_70");
   UsedList.push_back("366143_Sh_224_NN30NNLO_eegamma_LO_pty_70_140");
   UsedList.push_back("366144_Sh_224_NN30NNLO_eegamma_LO_pty_140_E_CMS");
   UsedList.push_back("366145_Sh_224_NN30NNLO_mumugamma_LO_pty_7_15");
   UsedList.push_back("366146_Sh_224_NN30NNLO_mumugamma_LO_pty_15_35");
   UsedList.push_back("366147_Sh_224_NN30NNLO_mumugamma_LO_pty_35_70");
   UsedList.push_back("366148_Sh_224_NN30NNLO_mumugamma_LO_pty_70_140");
   UsedList.push_back("366149_Sh_224_NN30NNLO_mumugamma_LO_pty_140_E_CMS");
   UsedList.push_back("410155_aMcAtNloPythia8EvtGen_MEN30NLO_A14N23LO_ttW");
   UsedList.push_back("410218_aMcAtNloPythia8EvtGen_MEN30NLO_A14N23LO_ttee");
   UsedList.push_back("410219_aMcAtNloPythia8EvtGen_MEN30NLO_A14N23LO_ttmumu");
   UsedList.push_back("410470_PhPy8EG_A14_ttbar_hdamp258p75_nonallhad");
 }

 for(int i = 0; i < UsedList.size(); i++){
   TString ChannelNumber = (TString)UsedList.at(i)(0, 6);
   ListFlag[stoi(ChannelNumber.Data())] = 1;
 }
 ListFlag[-1] = 1;
}

void BkgHist::DefineAdditionalName()
{
 if(ProcessName == "SignalWZ"){
   AdditionalName.push_back("BkgWZ");
   AdditionalName.push_back("BkgFake");
   AdditionalName.push_back("BkgOthers");
 }

 if(ProcessName == "WZPolarized"){
   AdditionalName.push_back("WZMixed");
   AdditionalName.push_back("WZRest");
 }

 if(ProcessName == "HMDY" || ProcessName == "HMDY_MuFakes"){
   //AdditionalName.push_back("FinalData");
   //AdditionalName.push_back("Bkg");
 }

}

void BkgHist::DefineAdditionalHist(TString name, TString title, int nbin, double left, double right)
{
 DefineAdditionalName();

 for(int i = 0; i < AdditionalName.size(); i++){
   AdditionalHist[AdditionalName.at(i)] = new TH1D(name + "_" + AdditionalName.at(i), title + "_" + AdditionalName.at(i), nbin, left, right);
   AdditionalHist[AdditionalName.at(i)]->Sumw2();

   BkgHist_1d.push_back(AdditionalHist[AdditionalName.at(i)]);

   NameIndex[AdditionalName.at(i)] = BkgHist_1d.size() - 1;
 }
}

void BkgHist::DefineAdditionalHist(TString name, TString title, int nbin, double* xbins)
{
 DefineAdditionalName();

 for(int i = 0; i < AdditionalName.size(); i++){
   AdditionalHist[AdditionalName.at(i)] = new TH1D(name + "_" + AdditionalName.at(i), title + "_" + AdditionalName.at(i), nbin, xbins);
   AdditionalHist[AdditionalName.at(i)]->Sumw2();

   BkgHist_1d.push_back(AdditionalHist[AdditionalName.at(i)]);

   NameIndex[AdditionalName.at(i)] = BkgHist_1d.size() - 1;
 }
}

void BkgHist::DefineAdditionalHist(TString name, TString title, int nbinx, double leftx, double rightx, int nbiny, double lefty, double righty)
{
 DefineAdditionalName();

 for(int i = 0; i < AdditionalName.size(); i++){
   AdditionalHist2D[AdditionalName.at(i)] = new TH2D(name + "_" + AdditionalName.at(i), title + "_" + AdditionalName.at(i), nbinx, leftx, rightx, nbiny, lefty, righty);
   AdditionalHist2D[AdditionalName.at(i)]->Sumw2();

   BkgHist_2d.push_back(AdditionalHist2D[AdditionalName.at(i)]);

   NameIndex[AdditionalName.at(i)] = BkgHist_2d.size() - 1;
 }
}

void BkgHist::DefineAdditionalHist(TString name, TString title, int nbinx, double* xbins, int nbiny, double* ybins)
{
 DefineAdditionalName();

 for(int i = 0; i < AdditionalName.size(); i++){
   AdditionalHist2D[AdditionalName.at(i)] = new TH2D(name + "_" + AdditionalName.at(i), title + "_" + AdditionalName.at(i), nbinx, xbins, nbiny, ybins);
   AdditionalHist2D[AdditionalName.at(i)]->Sumw2();

   BkgHist_2d.push_back(AdditionalHist2D[AdditionalName.at(i)]);

   NameIndex[AdditionalName.at(i)] = BkgHist_2d.size() - 1;
 }
}

void BkgHist::Fill(double par, double weight)
{
 if(NoBkgHist) return;
 if(iBkg == -1) return;

 if(iBkg != -1) myHist[iBkg]->Fill(par, weight * KFactor);
}

void BkgHist::Fill(double par1, double par2, double weight)
{
 if(NoBkgHist) return;
 if(iBkg == -1) return;

 if(iBkg != -1) myHist2D[iBkg]->Fill(par1, par2, weight * KFactor);
}

void BkgHist::InputKFactor(double KFactor)
{
// this->KFactor = KFactor;

 if(ProcessName == "WZPolarized"){
   if(MCType == 364253) this->KFactor = 1.0;
   else if(MCType == 361601) this->KFactor = 1.0;
   else this->KFactor = KFactor;
 }
}

TH1D* BkgHist::GetHistPtr(TString name)
{
 if(Dimension == 2) cout<<"Please call GetHistPtr2D()"<<endl;
 return BkgHist_1d.at(NameIndex.at(name));
}

TH2D* BkgHist::GetHistPtr2D(TString name)
{
 if(Dimension == 1) cout<<"Please call GetHistPtr()"<<endl;
 return BkgHist_2d.at(NameIndex.at(name));
}

void BkgHist::DeleteHist()
{
 if(NoBkgHist) return;

 for(int ibkg = 0; ibkg < bkgName.size(); ibkg++){
   if(Dimension == 1) delete myHist[ibkg];
   if(Dimension == 2) delete myHist2D[ibkg];
 }

 BkgHist_1d.clear();
 BkgHist_2d.clear();
}

void BkgHist::Add(BkgHist* hist1)
{
 if(Dimension == 1){
   for(int ibkg = 0; ibkg < BkgHist_1d.size(); ibkg++){
     BkgHist_1d.at(ibkg)->Add((hist1->BkgHist_1d).at(ibkg));
   }
 }

 if(Dimension == 2){
   for(int ibkg = 0; ibkg < BkgHist_2d.size(); ibkg++){
     BkgHist_2d.at(ibkg)->Add((hist1->BkgHist_2d).at(ibkg));
   }
 }

}

void BkgHist::Reset()
{
 if(Dimension == 1){
   for(int ibkg = 0; ibkg < bkgName.size(); ibkg++){
     myHist[ibkg]->Reset();
   }

   for(int ibkg = 0; ibkg < AdditionalName.size(); ibkg++){
     AdditionalHist[AdditionalName.at(ibkg)]->Reset();
   }
 }

 if(Dimension == 2){
   for(int ibkg = 0; ibkg < bkgName.size(); ibkg++){
     myHist2D[ibkg]->Reset();
   }

   for(int ibkg = 0; ibkg < AdditionalName.size(); ibkg++){
     AdditionalHist2D[AdditionalName.at(ibkg)]->Reset();
   }
 }
}

void BkgHist::Write()
{
 if(Dimension == 1){
   for(int ibkg = 0; ibkg < bkgName.size(); ibkg++){
     double SumNegativeBins = 0.0;
     for(int ibin = 1; ibin <= myHist[ibkg]->GetNbinsX(); ibin++){
       if(myHist[ibkg]->GetBinContent(ibin) < 0.0){
         SumNegativeBins += myHist[ibkg]->GetBinContent(ibin);
       }
     }

     if(SumNegativeBins < 0.0){
       TH1D* HistOrigin = (TH1D *)myHist[ibkg]->Clone(myHist[ibkg]->GetName() + (TString)"_Origin");
       HistOrigin->Write();
     }

     double ScaleFactor = 1.0;
     if(fabs(myHist[ibkg]->Integral()) > 1e-20){
       ScaleFactor = (myHist[ibkg]->Integral() + SumNegativeBins) / myHist[ibkg]->Integral();
       cout<<myHist[ibkg]->GetName()<<": ScaleFactor = "<<ScaleFactor<<" Integral: "<<myHist[ibkg]->Integral()<<" SumNegativeBins = "<<SumNegativeBins<<endl;
     }

     if(ScaleFactor < 0.0){
       cout<<"Sum of negative bins is greater than the histogram integral in plot "<<myHist[ibkg]->GetName()<<" Integral = "<<myHist[ibkg]->Integral()<<" sum of negative bins = "<<SumNegativeBins<<endl;
       cout<<"Force the scale factor to be 1"<<endl;
       ScaleFactor = 1.0;
     }

     for(int ibin = 1; ibin <= myHist[ibkg]->GetNbinsX(); ibin++){
       if(myHist[ibkg]->GetBinContent(ibin) < 0.0){
         cout<<myHist[ibkg]->GetName()<<": bin "<<ibin<<" is negative, original value is "<<myHist[ibkg]->GetBinContent(ibin)<<", force it to be zero."<<endl;
         myHist[ibkg]->SetBinContent(ibin, 0.0);
         myHist[ibkg]->SetBinError(ibin, 0.0);
       }

       if(fabs(ScaleFactor - 1.0) > 1e-10){
         cout<<myHist[ibkg]->GetName()<<": bin "<<ibin<<" original value is "<<myHist[ibkg]->GetBinContent(ibin)<<", change it to "<<myHist[ibkg]->GetBinContent(ibin) * ScaleFactor<<endl;
       }
       myHist[ibkg]->SetBinContent(ibin, myHist[ibkg]->GetBinContent(ibin) * ScaleFactor);
       myHist[ibkg]->SetBinError(ibin, myHist[ibkg]->GetBinError(ibin) * ScaleFactor);
     }

     myHist[ibkg]->Write();
   }
 }

 if(Dimension == 2){
   for(int ibkg = 0; ibkg < bkgName.size(); ibkg++){
     double SumNegativeBins = 0.0;
     for(int ibinx = 1; ibinx <= myHist2D[ibkg]->GetNbinsX(); ibinx++){
       for(int ibiny = 1; ibiny <= myHist2D[ibkg]->GetNbinsY(); ibiny++){
         if(myHist2D[ibkg]->GetBinContent(ibinx, ibiny) < 0.0){
           SumNegativeBins += myHist2D[ibkg]->GetBinContent(ibinx, ibiny);
         }
       }
     }

     double ScaleFactor = 1.0;
     if(fabs(myHist2D[ibkg]->Integral()) > 1e-20) ScaleFactor = (myHist2D[ibkg]->Integral() + SumNegativeBins) / myHist2D[ibkg]->Integral();
     if(ScaleFactor < 0.0){
       cout<<"Sum of negative bins is greater than the histogram integral in plot "<<myHist2D[ibkg]->GetName()<<" Integral = "<<myHist2D[ibkg]->Integral()<<" sum of negative bins = "<<SumNegativeBins<<endl;
       cout<<"Force the scale factor to be 1"<<endl;
       ScaleFactor = 1.0;
     }

     for(int ibinx = 1; ibinx <= myHist2D[ibkg]->GetNbinsX(); ibinx++){
       for(int ibiny = 1; ibiny <= myHist2D[ibkg]->GetNbinsY(); ibiny++){
         if(myHist2D[ibkg]->GetBinContent(ibinx, ibiny) < 0.0){
           myHist2D[ibkg]->SetBinContent(ibinx, ibiny, 0.0);
           myHist2D[ibkg]->SetBinError(ibinx, ibiny, 0.0);
         }
         myHist2D[ibkg]->SetBinContent(ibinx, ibiny, myHist2D[ibkg]->GetBinContent(ibinx, ibiny) * ScaleFactor);
         myHist2D[ibkg]->SetBinError(ibinx, ibiny, myHist2D[ibkg]->GetBinError(ibinx, ibiny) * ScaleFactor);
       }
     }

     myHist2D[ibkg]->Write();
   }
 }

 if(ProcessName == "HMDY" || ProcessName == "HMDY_MuFakes"){
   if(Dimension == 1){
   }
 }


 if(ProcessName == "SignalWZ"){
   if(Dimension == 1){
     AdditionalHist["BkgWZ"]->Add(myHist[NameIndex["BkgWZQCD"]]);
     AdditionalHist["BkgWZ"]->Add(myHist[NameIndex["BkgWZEW"]]);

     AdditionalHist["BkgFake"]->Add(myHist[NameIndex["BkgZjet"]]);
     AdditionalHist["BkgFake"]->Add(myHist[NameIndex["BkgZgamma"]]);
     AdditionalHist["BkgFake"]->Add(myHist[NameIndex["BkgTop"]]);

     AdditionalHist["BkgOthers"]->Add(myHist[NameIndex["BkgZZ"]]);
     AdditionalHist["BkgOthers"]->Add(myHist[NameIndex["BkgVVV"]]);
     AdditionalHist["BkgOthers"]->Add(myHist[NameIndex["BkgttbarV"]]);

     AdditionalHist["BkgWZ"]->Write();
     AdditionalHist["BkgFake"]->Write();
     AdditionalHist["BkgOthers"]->Write();
   }
 }

 if(ProcessName == "WZPolarized"){
   if(Dimension == 1){
     AdditionalHist["WZMixed"]->Add(myHist[NameIndex["LT"]]);
     AdditionalHist["WZMixed"]->Add(myHist[NameIndex["TL"]]);

     AdditionalHist["WZRest"]->Add(myHist[NameIndex["LT"]]);
     AdditionalHist["WZRest"]->Add(myHist[NameIndex["TL"]]);
     AdditionalHist["WZRest"]->Add(myHist[NameIndex["TT"]]);

     AdditionalHist["WZMixed"]->Write();
     AdditionalHist["WZRest"]->Write();
   }
 }

}

