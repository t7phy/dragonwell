#include "Calculation/Config.h"

void Config::ParseDataList(TString filename)
{
 ofstream outfile("DataSetting.config");

 YAML::Node RootNode;
 RootNode = YAML::LoadFile(filename.Data());

 YAML::Node global = RootNode["GlobalPath"];

 DataGlobalPath = global["data"].as<string>().c_str();
 ApplGlobalPath = global["applgrid"].as<string>().c_str();
 FNLOGlobalPath = global["fastnlo"].as<string>().c_str();
 if(global["pineappl"].IsDefined()) PineGlobalPath = global["pineappl"].as<string>().c_str();

 YAML::Node DataNode = RootNode["DataInformation"];
 DataList.resize(DataNode.size());

 int idata = 0;
 for(auto iter = DataNode.begin(); iter != DataNode.end(); iter++){
   string DataName = iter->first.as<string>();
   NametoIndex[DataName] = idata;

   DataList.at(idata).DataName = DataName.c_str();
   DataList.at(idata).DataPath = DataGlobalPath + DataNode[DataName]["Path"].as<string>().c_str();
   DataList.at(idata).DataType = DataNode[DataName]["DataType"].as<string>().c_str();
   DataList.at(idata).CalcMode = DataNode[DataName]["CalcMode"].as<string>().c_str();

   if(DataNode[DataName]["Collider"].IsDefined()){
     if(DataNode[DataName]["Collider"].Type() != YAML::NodeType::Null) DataList.at(idata).Collider = DataNode[DataName]["Collider"].as<string>().c_str();
   }

   DataList.at(idata).subType = DataNode[DataName]["subType"].as<string>().c_str();
   if(DataNode[DataName]["DataID"].IsDefined()) DataList.at(idata).DataID = DataNode[DataName]["DataID"].as<int>();

   if(DataNode[DataName]["ApplGrid"].IsDefined()){
     if(DataNode[DataName]["ApplGrid"].size() != 0){
       DataList.at(idata).ApplGrids.resize(DataNode[DataName]["ApplGrid"].size());
       for(int i = 0; i < DataNode[DataName]["ApplGrid"].size(); i++){
         DataList.at(idata).ApplGrids.at(i) = ApplGlobalPath + DataNode[DataName]["ApplGrid"][i].as<string>().c_str();
       }
     }
   }

   if(DataNode[DataName]["ApplRange"].IsDefined()){
     if(DataNode[DataName]["ApplRange"].size() != 0){
       DataList.at(idata).ApplRange.resize(DataNode[DataName]["ApplRange"].size());
       for(int i = 0; i < DataNode[DataName]["ApplRange"].size(); i++){
         DataList.at(idata).ApplRange.at(i) = DataNode[DataName]["ApplRange"][i].as<vector<int>>();
       }
     }
   }

   if(DataNode[DataName]["FastNLO"].IsDefined()){
     if(DataNode[DataName]["FastNLO"].size() != 0){
       DataList.at(idata).FastNLOGrids.resize(DataNode[DataName]["FastNLO"].size());
       for(int i = 0; i < DataNode[DataName]["FastNLO"].size(); i++){
         DataList.at(idata).FastNLOGrids.at(i) = (FNLOGlobalPath + DataNode[DataName]["FastNLO"][i].as<string>().c_str()).Data();
       }
     }
   }

   if(DataNode[DataName]["PineAPPL"].IsDefined()){
     if(DataNode[DataName]["PineAPPL"].size() != 0){
       //DataList.at(idata).PineAPPLGrids.resize(DataNode[DataName]["PineAPPL"].size());
       DataList.at(idata).PineAPPLGridMap.resize(DataNode[DataName]["PineAPPL"].size());
       for(int i = 0; i < DataNode[DataName]["PineAPPL"].size(); i++){
         //DataList.at(idata).PineAPPLGrids.at(i) = (PineGlobalPath + DataNode[DataName]["PineAPPL"][i].as<string>().c_str()).Data();
         if(DataNode[DataName]["PineAPPL"][i].size() == 1){
           DataList.at(idata).PineAPPLGrids.push_back((PineGlobalPath + DataNode[DataName]["PineAPPL"][i][0].as<string>().c_str()).Data());
           int GridIndex = DataList.at(idata).PineAPPLGrids.size() - 1;
           DataList.at(idata).PineAPPLGridMap.at(i) = make_tuple(vector<int>{GridIndex}, "");
         }
         else if(DataNode[DataName]["PineAPPL"][i].size() == 3){
           DataList.at(idata).PineAPPLGrids.push_back((PineGlobalPath + DataNode[DataName]["PineAPPL"][i][0].as<string>().c_str()).Data());
           DataList.at(idata).PineAPPLGrids.push_back((PineGlobalPath + DataNode[DataName]["PineAPPL"][i][1].as<string>().c_str()).Data());
           int GridIndex1 = DataList.at(idata).PineAPPLGrids.size() - 2;
           int GridIndex2 = DataList.at(idata).PineAPPLGrids.size() - 1;
           TString Operation = DataNode[DataName]["PineAPPL"][i][2].as<string>().c_str();
           DataList.at(idata).PineAPPLGridMap.at(i) = make_tuple(vector<int>{GridIndex1, GridIndex2}, Operation);
         }
         else if(DataNode[DataName]["PineAPPL"][i].size() == 2){
           cout<<LOG_ERROR<<"Please define operation!"<<endl;
           DataList.at(idata).PineAPPLGridMap.at(i) = make_tuple(vector<int>{}, "");
         }
       }
     }
   }

   if(DataNode[DataName]["KFactor"].IsDefined()){
     if(DataNode[DataName]["KFactor"].size() != 0){
       DataList.at(idata).KFactors = DataNode[DataName]["KFactor"].as<vector<int>>();
     }
   }

   if(DataNode[DataName]["OtherKFactor"].IsDefined()){
     if(DataNode[DataName]["OtherKFactor"].size() != 0){
       DataList.at(idata).OtherKFactors.resize(DataNode[DataName]["OtherKFactor"].size());
       for(int i = 0; i < DataNode[DataName]["OtherKFactor"].size(); i++){
         DataList.at(idata).OtherKFactors.at(i).resize(3);
         DataList.at(idata).OtherKFactors.at(i).at(0) = DataNode[DataName]["OtherKFactor"][i][0].as<string>().c_str();
         DataList.at(idata).OtherKFactors.at(i).at(1) = DataNode[DataName]["OtherKFactor"][i][1].as<string>().c_str();
         DataList.at(idata).OtherKFactors.at(i).at(2) = DataNode[DataName]["OtherKFactor"][i][2].as<string>().c_str();
       }
     }
   }

   if(DataNode[DataName]["Systematic"].IsDefined()){
     if(DataNode[DataName]["Systematic"].size() != 0){
       DataList.at(idata).SystematicMethod.resize(DataNode[DataName]["Systematic"].size());
       for(int i = 0; i < DataNode[DataName]["Systematic"].size(); i++){
         DataList.at(idata).SystematicMethod.at(i) = DataNode[DataName]["Systematic"][i].as<vector<int>>();
         DataList.at(idata).SystematicMethodMap[make_tuple(DataList.at(idata).SystematicMethod.at(i).at(0), DataList.at(idata).SystematicMethod.at(i).at(1))] = DataList.at(idata).SystematicMethod.at(i).at(2);
       }
     }
   }

   if(DataNode[DataName]["Normalization"].IsDefined()){
     if(DataNode[DataName]["Normalization"].size() != 0){
       DataList.at(idata).Normalization = DataNode[DataName]["Normalization"][1].as<vector<double>>();
       DataList.at(idata).NormParName = DataNode[DataName]["Normalization"][0][1].as<string>().c_str();
       NormParDataList[DataList.at(idata).NormParName].push_back(idata);
     }
   }

   if(DataNode[DataName]["CorrMatrix"].IsDefined()){
     if(DataNode[DataName]["CorrMatrix"].size() != 0){
       DataList.at(idata).AdditionalCorrMatrix.resize(DataNode[DataName]["CorrMatrix"].size());
       for(int i = 0; i < DataNode[DataName]["CorrMatrix"].size(); i++){
         DataList.at(idata).AdditionalCorrMatrix.at(i) = (DataGlobalPath + DataNode[DataName]["CorrMatrix"][i].as<string>().c_str()).Data();
       }
     }
   }

   outfile<<" AllData.at("<<idata<<") = new Dataset(\""<<DataName<<"\");"<<endl;
   outfile<<" AllData.at("<<idata<<")->SetCut(setting);"<<endl;

   if(DataList.at(idata).Normalization.size() != 0){
     outfile<<" AllData.at("<<idata<<")->InputNormalization(";
     for(int i = 0; i < DataList.at(idata).Normalization.size(); i++){
       if(i == 0) outfile<<fixed<<setprecision(4)<<DataList.at(idata).Normalization.at(i);
       else if(i == 1 || i == 2) outfile<<fixed<<setprecision(1)<<DataList.at(idata).Normalization.at(i);
       if(i != DataList.at(idata).Normalization.size() - 1) outfile<<", ";
     }
     outfile<<");"<<endl;
   }

   outfile<<" AllData.at("<<idata<<")->ReadFile(\""<<DataList.at(idata).DataPath<<"\", \""<<DataList.at(idata).DataType<<"\", \""<<DataList.at(idata).CalcMode<<"\", \""<<DataList.at(idata).Collider<<"\", \""<<DataList.at(idata).subType<<"\");"<<endl;

   outfile<<" AllData.at("<<idata<<")->SetDataID("<<DataList.at(idata).DataID<<");"<<endl;

   if(DataList.at(idata).ApplGrids.size() != 0){
     outfile<<" AllData.at("<<idata<<")->InputGridName(vector<TString>{";
     for(int i = 0; i < DataList.at(idata).ApplGrids.size(); i++){
       outfile<<"\""<<DataList.at(idata).ApplGrids.at(i)<<"\"";
       if(i != DataList.at(idata).ApplGrids.size() - 1) outfile<<", ";
     }
     outfile<<"});"<<endl;
   }

   if(DataList.at(idata).ApplRange.size() != 0){
     for(int i = 0; i < DataList.at(idata).ApplRange.size(); i++){
       outfile<<" AllData.at("<<idata<<")->InputApplGridRange(";
       for(int irange = 0; irange < DataList.at(idata).ApplRange.at(i).size(); irange++){
         outfile<<DataList.at(idata).ApplRange.at(i).at(irange);
         if(irange != DataList.at(idata).ApplRange.at(i).size() - 1) outfile<<", ";
       }
       outfile<<");"<<endl;
     }
   }

   if(DataList.at(idata).FastNLOGrids.size() != 0){
     outfile<<" AllData.at("<<idata<<")->InputFNLOTableName(vector<string>{";
     for(int i = 0; i < DataList.at(idata).FastNLOGrids.size(); i++){
       outfile<<"\""<<DataList.at(idata).FastNLOGrids.at(i)<<"\"";
       if(i != DataList.at(idata).FastNLOGrids.size() - 1) outfile<<", ";
     }
     outfile<<"});"<<endl;
   }

   if(DataList.at(idata).PineAPPLGrids.size() != 0){
     outfile<<" AllData.at("<<idata<<")->InputPineAPPLGridName(vector<string>{";
     for(int i = 0; i < DataList.at(idata).PineAPPLGrids.size(); i++){
       outfile<<"\""<<DataList.at(idata).PineAPPLGrids.at(i)<<"\"";
       if(i != DataList.at(idata).PineAPPLGrids.size() - 1) outfile<<", ";
     }
     outfile<<"});"<<endl;
     outfile<<" AllData.at("<<idata<<")->InputPineAPPLGridMap(vector<tuple<vector<int>, TString>>{";
     for(int i = 0; i < DataList.at(idata).PineAPPLGridMap.size(); i++){
       outfile<<"make_tuple(vector<int>{";
       for(int igrid = 0; igrid < get<0>(DataList.at(idata).PineAPPLGridMap.at(i)).size(); igrid++){
         outfile << get<0>(DataList.at(idata).PineAPPLGridMap.at(i)).at(igrid);
         if(igrid != get<0>(DataList.at(idata).PineAPPLGridMap.at(i)).size() - 1) outfile<<", ";
       }
       outfile << "}, " << "\"" << get<1>(DataList.at(idata).PineAPPLGridMap.at(i)) << "\")";
       if(i != DataList.at(idata).PineAPPLGridMap.size() - 1) outfile<<", ";
     }
     outfile<<"});"<<endl;
   }

   if(DataList.at(idata).SystematicMethod.size() != 0){
     outfile<<" AllData.at("<<idata<<")->InputSystematicMethod(map<tuple<int, int>, int>{";
     for(int i = 0; i < DataList.at(idata).SystematicMethod.size(); i++){
       outfile<<"{make_tuple("<<DataList.at(idata).SystematicMethod.at(i).at(0)<<", "<<DataList.at(idata).SystematicMethod.at(i).at(1)<<"), "<<DataList.at(idata).SystematicMethod.at(i).at(2)<<"}";
       if(i != DataList.at(idata).SystematicMethod.size() - 1) outfile<<", ";
     }
     outfile<<"});"<<endl;
   }

   if(DataList.at(idata).KFactors.size() != 0){
     outfile<<" AllData.at("<<idata<<")->InputKFactorColumns(vector<int>{";
     for(int i = 0; i < DataList.at(idata).KFactors.size(); i++){
       outfile<<DataList.at(idata).KFactors.at(i);
       if(i != DataList.at(idata).KFactors.size() - 1) outfile<<", ";
     }
     outfile<<"});"<<endl;
   }

   if(DataList.at(idata).AdditionalCorrMatrix.size() != 0){
     outfile<<" AllData.at("<<idata<<")->InputAdditionalCorrMatrix(vector<TString>{";
     for(int i = 0; i < DataList.at(idata).AdditionalCorrMatrix.size(); i++){
       outfile<<"\""<<DataList.at(idata).AdditionalCorrMatrix.at(i)<<"\"";
       if(i != DataList.at(idata).AdditionalCorrMatrix.size() - 1) outfile<<", ";
     }
     outfile<<"});"<<endl;
   }

   outfile<<endl;

   idata++;
 }
}

void Config::ParseParameter(TString filename)
{
 YAML::Node RootNode;
 RootNode = YAML::LoadFile(filename.Data());

 YAML::Node ParameterNode = RootNode["Parameter"];
 YAML::Node PDFParameterizationNode = RootNode["PDFParameterization"];
 YAML::Node ShapeMatchNode = RootNode["ShapeMatch"];
 YAML::Node CentralValueNode = RootNode["CentralValue"];
 YAML::Node OtherParametersNode = RootNode["OtherParameters"];

 for(int i = 0; i < ParameterNode.size(); i++){
   int id         = ParameterNode[i]["parameter"][0].as<int>();
   TString name   = ParameterNode[i]["parameter"][1].as<string>().c_str();
   double center  = ParameterNode[i]["parameter"][2].as<double>();
   double step    = ParameterNode[i]["parameter"][3].as<double>();
   double left    = ParameterNode[i]["parameter"][4].as<double>();
   double right   = ParameterNode[i]["parameter"][5].as<double>();

   ConfigParameter(i, id, name, center, step, left, right);
 }

 if(PDFParameterizationNode.IsDefined()){
   if(PDFParameterizationNode["IFun"].IsDefined()) IFun = PDFParameterizationNode["IFun"].as<int>();
   else cout<<LOG_INFO<<"Using Default IFun: "<<IFun<<endl;

   cout<<LOG_INFO<<"Use IFun = "<<IFun<<" parameterization."<<endl;
 }
 else{
   cout<<LOG_INFO<<"Using Default PDFParameterization Setting."<<endl;
 }

 FlavorList.clear();
 FlagList.clear();

 MomentumList.clear();
 B0List.clear();

 for(int i = 0; i < ShapeMatchNode.size(); i++){
   TString flavor = ShapeMatchNode[i]["parameter"][0].as<string>().c_str();
   int flag       = ShapeMatchNode[i]["parameter"][1].as<int>();

   cout<<LOG_INFO<<"Book "<<flavor<<" flavor in "<<flag<<" functional form"<<endl;

   FlavorList.push_back(flavor);
   FlagList.push_back(flag);

   ShapeParameter[flavor] = ShapeMatchNode[i]["parameter"][2].as<vector<int>>();

   TString flavor_ValueNode = CentralValueNode[i]["parameter"][0].as<string>().c_str();
   if(flavor == flavor_ValueNode){
     ShapeParameterValue[flavor] = CentralValueNode[i]["parameter"][3].as<vector<double>>();
   }
   else{
     cout<<LOG_ERROR<<"Shape parameter doesn't match!"<<endl;
   }

   // Make the fit starting value is initialized by shape match part
   for(int ipar = 0; ipar < ShapeParameter.at(flavor).size(); ipar++){
     if(ShapeParameter.at(flavor).at(ipar) == 0) continue;
     int index = GetParIndex(ShapeParameter.at(flavor).at(ipar));
     SetParCentral(index, ShapeParameterValue.at(flavor).at(ipar));
   }

   double Momentum = CentralValueNode[i]["parameter"][1].as<double>();
   double B0       = CentralValueNode[i]["parameter"][2].as<double>();

   MomentumList.push_back(Momentum);
   B0List.push_back(B0);

   if(flavor_ValueNode == "gluon"){
     InitialgluonMomentum = CentralValueNode[i]["parameter"][1].as<double>();
   }
   if(flavor_ValueNode == "str"){
     InitialStrangeB0 = CentralValueNode[i]["parameter"][2].as<double>();
   }
 }

 if(OtherParametersNode.IsDefined()){
   OtherParameterList.resize(OtherParametersNode.size());
   for(int i = 0; i < OtherParametersNode.size(); i++){
     OtherParameterList.at(i).id      = OtherParametersNode[i]["parameter"][0].as<int>();
     OtherParameterList.at(i).name    = OtherParametersNode[i]["parameter"][1].as<string>().c_str();
     OtherParameterList.at(i).type    = OtherParametersNode[i]["parameter"][2].as<string>().c_str();
     OtherParameterList.at(i).central = OtherParametersNode[i]["parameter"][3].as<double>();
     OtherParameterList.at(i).isFit   = OtherParametersNode[i]["parameter"][4].as<bool>();

     OtherParameterCentral[OtherParameterList.at(i).name] = OtherParameterList.at(i).central;
     OtherParameterID[OtherParameterList.at(i).name] = i;
     OtherParameter_isFit[OtherParameterList.at(i).name] = OtherParameterList.at(i).isFit;
   }
 }
}

void Config::CloneParameter(Config setting)
{
 this->MomentumList = setting.MomentumList;
 this->B0List = setting.B0List;
 this->FlavorList = setting.FlavorList;
 this->FlagList = setting.FlagList;
 this->ShapeParameter = setting.ShapeParameter;
 this->ShapeParameterValue = setting.ShapeParameterValue;
 this->IFun = setting.IFun;
 this->ParameterList = setting.ParameterList;
 this->FittingParameter = setting.FittingParameter;
 this->OtherParameterList = setting.OtherParameterList;
 this->OtherParameterCentral = setting.OtherParameterCentral;
 this->OtherParameterID = setting.OtherParameterID;
 this->OtherParameter_isFit = setting.OtherParameter_isFit;
}

void Config::ParseConfig(TString filename)
{
 YAML::Node RootNode;
 RootNode = YAML::LoadFile(filename.Data());

 YAML::Node QCDNode = RootNode["QCDParameter"];
 cout<<LOG_INFO<<endl;
 cout<<LOG_INFO<<"QCD parameters setting:"<<endl;
 if(QCDNode["NFlavor"].IsDefined()) this->Nflv = QCDNode["NFlavor"].as<int>();
 if(QCDNode["EvolveOrder"].IsDefined()) this->IorEvl = QCDNode["EvolveOrder"].as<int>();
 if(QCDNode["HardOrder"].IsDefined()) this->IorHrd = QCDNode["HardOrder"].as<int>();
 if(QCDNode["AlphaSOrder"].IsDefined()) this->IorQCD = QCDNode["AlphaSOrder"].as<int>();
 this->mc = QCDNode["mc"].as<double>();
 this->mb = QCDNode["mb"].as<double>();
 this->mt = QCDNode["mt"].as<double>();
 this->Qini = QCDNode["Qini"].as<double>();
 this->AlphaS = QCDNode["AlphaS"].as<double>();
 this->AlphaS_Q0 = QCDNode["AlphaS_Q0"].as<double>();
 this->EvolveType = QCDNode["Evolution"].as<string>().c_str();
 if(EvolveType == "APFEL"){
   this->EvolveOption = QCDNode["EvolutionOption"].as<string>().c_str();
   if(EvolveOption == "Default"){
     this->isEvolveQED = false;
     this->isEvolveSmallx = false;
   }
   else if(EvolveOption == "QED"){
     this->isEvolveQED = true;
     this->isEvolveSmallx = false;
   }
   else if(EvolveOption == "smallx"){
     this->isEvolveQED = false;
     this->isEvolveSmallx = true;
   }
 }

 if(IorEvl != IorQCD){
   cout<<LOG_ERROR<<"Please make the AlphaSOrder being the same as the EvolveOrder."<<endl;
   cout<<LOG_ERROR<<"Now the EvolveOrder setup will be used for two variables"<<endl;
   IorQCD = IorEvl;
 }

 cout<<LOG_INFO<<"NFlavor = "<<Nflv<<endl;
 cout<<LOG_INFO<<"EvolveOrder, AlphaSOrder, HardOrder = "<<IorEvl<<"  "<<IorQCD<<"  "<<IorHrd<<endl;
 cout<<LOG_INFO<<"Mcbt = "<<mc<<"  "<<mb<<"  "<<mt<<endl;
 cout<<LOG_INFO<<"Qini = "<<Qini<<endl;
 cout<<LOG_INFO<<"PDF evolved by "<<EvolveType<<endl;
 cout<<LOG_INFO<<"Evolve option is "<<EvolveOption<<endl;

 YAML::Node LMPenaltyNode = RootNode["LMPenalty"];
 if(LMPenaltyNode.IsDefined()){
   for(int i = 0; i < LMPenaltyNode.size(); i++){
     int id            = LMPenaltyNode[i]["penalty"][0].as<int>();
     TString name      = LMPenaltyNode[i]["penalty"][1].as<string>().c_str();
     vector<int> LM    = LMPenaltyNode[i]["penalty"][2].as<vector<int>>();
     vector<double> dM = LMPenaltyNode[i]["penalty"][3].as<vector<double>>();
     LMPenaltyInput[id] = make_tuple(name, LM, dM);
     cout<<LOG_INFO<<"Book LM penalty "<<id<<" "<<name<<" {";
     for(int j = 0; j < LM.size(); j++){
       cout<<LM.at(j);
       if(j != LM.size() - 1) cout<<", ";
       if(j == LM.size() - 1) cout<<"}";
     }
     cout<<" {";
     for(int j = 0; j < dM.size(); j++){
       cout<<dM.at(j);
       if(j != dM.size() - 1) cout<<", ";
       if(j == dM.size() - 1) cout<<"}"<<endl;
     }
   }
 }
 else{
   cout<<LOG_INFO<<"No LM penalty are defined."<<endl;
 }

 YAML::Node PDFInputNode = RootNode["PDFInput"];
 if(PDFInputNode.IsDefined()){
   if(PDFInputNode["PDFInputType"].IsDefined()){
     this->PDFInputType = PDFInputNode["PDFInputType"].as<string>().c_str();
  
     if(this->PDFInputType == "CTEQ" || this->PDFInputType == "LHAPDF"){
       cout<<LOG_INFO<<"Run in calculation mode."<<endl;
       if(PDFInputNode["PDFInput"].IsDefined()) this->PDFInput = PDFInputNode["PDFInput"].as<string>().c_str();
       else cout<<LOG_ERROR<<"PDFInput must be specified!"<<endl;
  
       cout<<LOG_INFO<<"The input PDF is "<<this->PDFInput<<endl;
     }
  
     if(this->PDFInputType == "LHAPDF"){
       if(PDFInputNode["PDFiSet"].IsDefined()) this->PDFiSet = PDFInputNode["PDFiSet"].as<int>();
       else cout<<LOG_ERROR<<"PDFiSet must be specified!"<<endl;
  
       cout<<LOG_INFO<<"The PDF set is "<<this->PDFiSet<<endl;
     }
   }
   else{
     this->PDFInputType = "None";
   }
 }
 else{
   this->PDFInputType = "None";
 }

 YAML::Node AlgorithmNode = RootNode["Algorithm"];
 cout<<LOG_INFO<<endl;
 cout<<LOG_INFO<<"Algorithm setting:"<<endl;
 if(AlgorithmNode.IsDefined()){
   if(AlgorithmNode["Name"].IsDefined()) this->AlgorithmName = AlgorithmNode["Name"].as<string>().c_str();
   else cout<<LOG_INFO<<"Using Default Algorithm: "<<AlgorithmName<<endl;

   if(AlgorithmNode["MaxCall"].IsDefined()) this->MaxCall = AlgorithmNode["MaxCall"].as<int>();
   else cout<<LOG_INFO<<"Using Default MaxCall: "<<MaxCall<<endl;

   if(AlgorithmNode["Tolerance"].IsDefined()) this->MinTol = AlgorithmNode["Tolerance"].as<double>();
   else cout<<LOG_INFO<<"Using Default MinTol: "<<MinTol<<endl;

   if(AlgorithmNode["LFit"].IsDefined()) this->LFit = AlgorithmNode["LFit"].as<double>();
   else cout<<LOG_INFO<<"Using Default LFit: "<<LFit<<endl;
 }
 else{
   cout<<LOG_INFO<<"Using Default Algorithm Setting."<<endl;
 }

 YAML::Node ThreadNode = RootNode["Thread"];
 if(ThreadNode.IsDefined()){
   if(ThreadNode["nDISThread"].IsDefined()) this->nDISThread = ThreadNode["nDISThread"].as<int>();
   else cout<<LOG_INFO<<"Using Default nDISThread: "<<nDISThread<<endl;

   if(ThreadNode["nVBPThread"].IsDefined()) this->nVBPThread = ThreadNode["nVBPThread"].as<int>();
   else cout<<LOG_INFO<<"Using Default nVBPThread: "<<nVBPThread<<endl;
 }
 else{
   cout<<LOG_INFO<<"Using Default Thread Setting."<<endl;
 }

 if(this->PDFInputType != "None") this->LFit = 0;

 cout<<LOG_INFO<<AlgorithmName<<" Algorithm is used for minimization. MaxCall = "<<MaxCall<<" MinTol = "<<MinTol<<endl;
 cout<<LOG_INFO<<"nDISThread = "<<nDISThread<<" nVBPThread = "<<nVBPThread<<" will be used for doing calculation."<<endl;

 YAML::Node EVNode = RootNode["ErrorSet"];
 cout<<LOG_INFO<<endl;
 cout<<LOG_INFO<<"ErrorSet setting:"<<endl;
 if(EVNode.IsDefined()){
   if(EVNode["dmeasTol"].IsDefined()) this->dmeasRequirement = EVNode["dmeasTol"].as<double>();
   else cout<<LOG_INFO<<"Using Default dmeas requirement: "<<dmeasRequirement<<endl;

   if(EVNode["Tolerance"].IsDefined()) this->Tolerance = EVNode["Tolerance"].as<double>();
   else cout<<LOG_INFO<<"Using Default Tolerance: "<<Tolerance<<endl;

   if(EVNode["Tier2Type"].IsDefined()) this->Tier2Type = EVNode["Tier2Type"].as<string>().c_str();
   else cout<<LOG_INFO<<"Using Default Tier2Type: "<<Tier2Type<<endl;

   if(EVNode["CalcLevel"].IsDefined()) this->CalcLevel = EVNode["CalcLevel"].as<string>().c_str();
   else cout<<LOG_INFO<<"Using Default CalcLevel: "<<CalcLevel<<endl;

   cout<<LOG_INFO<<"dmeas requirement = "<<dmeasRequirement<<" Tolerance = "<<Tolerance<<" Tier2Type = "<<Tier2Type<<" CalcLevel = "<<CalcLevel<<endl;
 }
 else{
   cout<<LOG_INFO<<"Using Default ErrorSet Setting."<<endl;
 }

 cout<<endl;
}

void Config::OutputNewParameterFile(TString filename)
{
 ofstream newyml(filename);
 newyml<<"Parameter:"<<endl;
 for(int i = 0; i < ParameterList.size(); i++){
   newyml<<"  - parameter: [";
   newyml<<setw(2)<<*right<<GetParID(i);
   newyml<<",  ";
   newyml<<GetParName(i);
   newyml<<",";
   newyml<<setw(15 - GetParName(i).Length())<<*right<<fixed<<setprecision(5)<<GetParCentral(i);
   newyml<<",";
   if(!filename.Contains("Iterate")){
     newyml<<setw(8)<<*right<<fixed<<setprecision(2)<<GetParStep(i);
   }
   else{
     if(GetParName(i) == "N71" || GetParName(i) == "N72" || GetParName(i) == "N73"
     || OtherParameterCentral.count(GetParName(i)) > 0){
       newyml<<setw(8)<<*right<<scientific<<setprecision(3)<<0.0;

     }
     else{
       newyml<<setw(8)<<*right<<scientific<<setprecision(3)<<GetParError(i);
     }
   }
   newyml<<",";
   newyml<<setw(8)<<*right<<fixed<<setprecision(1)<<GetParLeft(i);
   newyml<<",";
   newyml<<setw(8)<<*right<<fixed<<setprecision(1)<<GetParRight(i);
   newyml<<"]"<<endl;
 }
 newyml<<"PDFParameterization: # IFun = 1(CT18), 2(CT18As)"<<endl;
 newyml<<"  IFun: "<<IFun<<endl;
 newyml<<"ShapeMatch:"<<endl;
 for(int i = 0; i < FlavorList.size(); i++){
   newyml<<"  - parameter: [";
   newyml<<FlavorList.at(i);
   newyml<<",";
   newyml<<setw(9 - FlavorList.at(i).Length())<<*right<<FlagList.at(i);
   newyml<<", [";
   for(int ip = 0; ip < ShapeParameter[FlavorList.at(i)].size(); ip++){
     newyml<<setw(3)<<*right<<ShapeParameter[FlavorList.at(i)].at(ip);
     if(ip != ShapeParameter[FlavorList.at(i)].size() - 1) newyml<<",";
   }
   newyml<<"]]"<<endl;
 }
 newyml<<"CentralValue:"<<endl;
 newyml<<"             # flavor  momentum        B0        shape parameters"<<endl;
 for(int i = 0; i < FlavorList.size(); i++){
   newyml<<"  - parameter: [";
   newyml<<FlavorList.at(i);
   newyml<<",";
   newyml<<setw(15 - FlavorList.at(i).Length())<<*right<<fixed<<setprecision(7)<<MomentumList.at(i);
   newyml<<",";
   newyml<<setw(11)<<*right<<fixed<<setprecision(7)<<B0List.at(i);
   newyml<<",  [";
   for(int ip = 0; ip < ShapeParameterValue[FlavorList.at(i)].size(); ip++){
     newyml<<setw(9)<<*right<<fixed<<setprecision(5)<<ShapeParameterValue[FlavorList.at(i)].at(ip);
     if(ip != ShapeParameterValue[FlavorList.at(i)].size() - 1) newyml<<",";
   }
   newyml<<"]]"<<endl;
 }

 if(OtherParameterList.size() != 0){
   newyml<<"OtherParameters:"<<endl;
   for(int i = 0; i < OtherParameterList.size(); i++){
     newyml<<"  - parameter: [";
     newyml<<OtherParameterList.at(i).id<<", ";
     newyml<<OtherParameterList.at(i).name<<", ";
     newyml<<OtherParameterList.at(i).type<<", ";

     if(OtherParameterList.at(i).isFit) newyml<<fixed<<setprecision(5)<<FittingParameter.at(OtherParameterList.at(i).name)<<", ";
     else newyml<<fixed<<setprecision(5)<<OtherParameterList.at(i).central<<", ";

     if(OtherParameterList.at(i).isFit) newyml<<"true]"<<endl;
     else newyml<<"false]"<<endl;
   }
 }
}
