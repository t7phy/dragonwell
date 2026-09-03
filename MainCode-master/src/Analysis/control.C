#include "control.h"

using namespace std;

void Control::ReadFile(const char* FileName)
{
 myLog<<LOG_INFO<<endl;
 myLog<<LOG_INFO<<"Start to read the card file: "<<FileName<<endl;
 myLog<<LOG_INFO<<endl;

 ifstream infile;
   infile.open(FileName, ios::in);
 string FileLine;

 TString skip;
 int config;
 double config_double;

/********cardfile.in format********/
/*

////Common Block////

Thread                                          *Running method (Thread/Condor)
4                                               *Thread Number
ResBosW                                         *Rootfile Type (Wasymmetry/ResBos/ResBosW/....)
data_lowmu.list                                         *file list
MC_results_lowmu.root                           *save rootfile name
cuts.in                                         *global cut information
0                                               *is Test(1: test, 0: normal run)
1                                               *run all systematic(1: yes, 0: only run nominal)

////////////////////

*****************************************************************************************************

////   Pythia   ////
1                                               *Prerun reweighting factor
1                                               *Fitting
13000                                           *ECM
0                                               *is PPbar
NNPDF31_nnlo_as_0118_1000   0                   *old PDF Name, old PDF set(optional)
NNPDF31_nnlo_as_0118_1000   1                   *new PDF Name, new PDF set(optional)
////////////////////

////   PythiaWW   ////
NNPDF31_nnlo_as_0118_1000   0                   *old PDF Name, old PDF set(optional)
NNPDF31_nnlo_as_0118_1000   1                   *new PDF Name, new PDF set(optional)
////////////////////

////   ResBos   ////
0                                               *reweight flag (0: not reweight, 1: reweight)
0                                               *turn on FSR(0: turn off, 1: turn on)
13000                      			*ECM
1                                               *include dilution
NNPDF31_nnlo_as_0118_1000   0                   *old PDF Name, old PDF set(optional)
NNPDF31_nnlo_as_0118_1000   1                   *new PDF Name, new PDF set(optional)
////////////////////

////   ResBosWTev   ////
DataList.list                                   *DataList
////////////////////////

///WZPolarization///
1 						*run bkg
1                                               *run control region
1                                               *run fake rate
nominal                                         *Systematic name(0: nominal, all: Run All Systematic(not recommended), other names...)
1                  				*Prerun reweighting factor
1                           			*Fitting
BDTfile                                         *BDTFile list
QCD    1                                        *Error Type(QCD or PDF), Error set
///////////////////

///PreWZPolarization///
1 						*run bkg
1 						*run control region
1 						*run fake rate
1                               		*ProcessOption(1: Just Generate Tree, 2: Finish All Process)
sherpa.364253.inclusive.root           		*Ntuple name or Bkg name
1718          					*Year
1 						*do truth selection
SumOfWeightFile.list                            *file list for calculating the sum of weight
1                                               *do save PDF and QCD uncertainty
1                                               *Prerun reweighting factor
1                                               *Fitting
LWTNNfile                                       *Neural network file list
///////////////////////

///  CalibrationForResBos  ///
fitting.list                                  	*fitting data information
//////////////////////////////

to be added....

*/
/**********************************/

//running method
 infile>>skip;
 getline(infile, FileLine);
 myLog<<LOG_INFO<<skip<<FileLine<<endl;
 RunType = skip;

//total thread
 infile>>config;
 getline(infile, FileLine);
 myLog<<LOG_INFO<<config<<FileLine<<endl;
 TotalThread = config;
 if(RunType == "Condor") TotalThread = 1;

//root type
 infile>>skip;
 getline(infile, FileLine);
 myLog<<LOG_INFO<<skip<<FileLine<<endl;
 RootType = skip;

//file list
 infile>>skip;
 getline(infile, FileLine);
 myLog<<LOG_INFO<<skip<<FileLine<<endl;
 FileList = skip;

 if(FileList != ""){
   ifstream myfile;
     myfile.open(FileList, ios::in);
   while(myfile>>RootName){
     RootNames.push_back(RootName);
   }
   TotalFileNumber = RootNames.size();
   NFilePerJob = TotalFileNumber;
 }

//save name
 infile>>skip;
 getline(infile, FileLine);
 myLog<<LOG_INFO<<skip<<FileLine<<endl;
 SaveName = skip;

//cut info
 infile>>skip;
 getline(infile, FileLine);
 myLog<<LOG_INFO<<skip<<FileLine<<endl;
 CutFile = skip;

//isTest
 infile>>config;
 getline(infile, FileLine);
 myLog<<LOG_INFO<<config<<FileLine<<endl;
 isTest = config;

//isRunAllSystematic
 infile>>config;
 getline(infile, FileLine);
 myLog<<LOG_INFO<<config<<FileLine<<endl;
 isRunAllSystematic = config;

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

 if(RootType == "Pythia"){
//Add reweighting factor
   infile>>config;
   getline(infile, FileLine);
   myLog<<LOG_INFO<<config<<FileLine<<endl;
   PreRunReweightingFactor = config;

//Fitting
   infile>>config;
   getline(infile, FileLine);
   myLog<<LOG_INFO<<config<<FileLine<<endl;
   Fitting = config;

//input ECM
   infile>>config_double;
   getline(infile, FileLine);
   myLog<<LOG_INFO<<config_double<<FileLine<<endl;
   ECM = config_double;

//isPPbar
   infile>>config;
   getline(infile, FileLine);
   myLog<<LOG_INFO<<config<<FileLine<<endl;
   isPPbar = config;

   //PDF reweight
   if(infile>>skip>>config){
     getline(infile, FileLine);
     myLog<<LOG_INFO<<skip<<" "<<config<<FileLine<<endl;
     oldPDFName = skip;
     oldPDFset = config;

     infile>>skip>>config;
     getline(infile, FileLine);
     myLog<<LOG_INFO<<skip<<" "<<config<<FileLine<<endl;
     newPDFName = skip;
     newPDFset = config;
   }

 }

 if(RootType == "PythiaWW"){

   //PDF reweight
   if(infile>>skip>>config){
     getline(infile, FileLine);
     myLog<<LOG_INFO<<skip<<" "<<config<<FileLine<<endl;
     oldPDFName = skip;
     oldPDFset = config;

     infile>>skip>>config;
     getline(infile, FileLine);
     myLog<<LOG_INFO<<skip<<" "<<config<<FileLine<<endl;
     newPDFName = skip;
     newPDFset = config;
   }

 }

 if(RootType == "SherpaWW"){
   //PDF Error set
   infile>>config;
   getline(infile, FileLine);
   myLog<<LOG_INFO<<config<<FileLine<<endl;
   ErrorSet = config;
 }

 if(RootType == "ResBos" || RootType == "ResBosW" || RootType == "ResBosWTev" || RootType == "CalibrationForResBos" ||
    RootType == "ResBosCMS" || RootType == "FittingCMSData" || RootType == "FlavorAsym" || RootType == "FittingCDFSmear" ||
    RootType == "ResBosHighMassZ" || RootType == "ResBosD0"){
//reweight flag
   infile>>config;
   getline(infile, FileLine);
   myLog<<LOG_INFO<<config<<FileLine<<endl;
   isReweight = config;

//turn on FSR
   infile>>config;
   getline(infile, FileLine);
   myLog<<LOG_INFO<<config<<FileLine<<endl;
   isFSR = config;

//input ECM
   infile>>config_double;
   getline(infile, FileLine);
   myLog<<LOG_INFO<<config_double<<FileLine<<endl;
   ECM = config_double;

//is dilution
   infile>>config;
   getline(infile, FileLine);
   myLog<<LOG_INFO<<config<<FileLine<<endl;
   isDilution = config;

   if(RootType == "ResBos" || RootType == "ResBosHighMassZ"){
     //PDF reweight
     if(infile>>skip>>config){
       getline(infile, FileLine);
       myLog<<LOG_INFO<<skip<<" "<<config<<FileLine<<endl;
       oldPDFName = skip;
       oldPDFset = config;

       infile>>skip>>config;
       getline(infile, FileLine);
       myLog<<LOG_INFO<<skip<<" "<<config<<FileLine<<endl;
       newPDFName = skip;
       newPDFset = config;
     }
   }
 }

 if(RootType == "FlavorAsym"){
   if(infile>>skip>>config){
     getline(infile, FileLine);
     myLog<<LOG_INFO<<skip<<" "<<config<<FileLine<<endl;
     oldPDFName = skip;
     oldPDFset = config;

     infile>>skip>>config;
     getline(infile, FileLine);
     myLog<<LOG_INFO<<skip<<" "<<config<<FileLine<<endl;
     newPDFName = skip;
     newPDFset = config;
   }
 }

 if(RootType == "ResBosCMS"){
//Data list
   if(infile>>skip){
     getline(infile, FileLine);
     myLog<<LOG_INFO<<skip<<FileLine<<endl;
     DataListFile = skip;

     ifstream infile_data;
      infile_data.open(DataListFile, ios::in);
     while(infile_data>>skip){
       DataList.push_back(skip);
     }
   }
 }

 if(RootType == "ResBosWTev" || RootType == "FittingCDFSmear"){
//Data list
   if(infile>>skip){
     getline(infile, FileLine);
     myLog<<LOG_INFO<<skip<<FileLine<<endl;
     DataListFile = skip;

     ifstream infile_data;
      infile_data.open(DataListFile, ios::in);
     while(infile_data>>skip){
       DataList.push_back(skip);
     }
   }
//WMass reweighting
   infile>>config_double;
   OriginWMass = config_double;
   infile>>config_double;
   NewWMass = config_double;
   infile>>config_double;
   WWidth = config_double;
   getline(infile, FileLine);
   myLog<<LOG_INFO<<OriginWMass<<" "<<NewWMass<<" "<<WWidth<<FileLine<<endl;

   //temporary
   //infile>>LeptonPtMin>>LeptonPtMiddle>>LeptonPtMax;
   //getline(infile, FileLine);
   //myLog<<LOG_INFO<<LeptonPtMin<<" "<<LeptonPtMiddle<<" "<<LeptonPtMax<<" "<<FileLine<<endl;

//pT(W)/pT(Z) scale reweighting
   if(infile>>config_double){
     ScaleSlope = config_double;
     getline(infile, FileLine);
     myLog<<LOG_INFO<<ScaleSlope<<FileLine<<endl;
   }

   if(RootType == "FittingCDFSmear"){
     if(infile>>skip){
       getline(infile, FileLine);
       myLog<<LOG_INFO<<skip<<FileLine<<endl;
       CalibrationOption = skip;
     }
   }
 }

 if(RootType == "WZPolarization"){
//run bkg
   infile>>config;
   getline(infile, FileLine);
   myLog<<LOG_INFO<<config<<FileLine<<endl;
   doBkg = config;

//run control region
   infile>>config;
   getline(infile, FileLine);
   myLog<<LOG_INFO<<config<<FileLine<<endl;
   doControlRegion = config;

//run fake rate
   infile>>config;
   getline(infile, FileLine);
   myLog<<LOG_INFO<<config<<FileLine<<endl;
   doFakeRate = config;

//Systematic name
   infile>>skip;
   getline(infile, FileLine);
   myLog<<LOG_INFO<<skip<<FileLine<<endl;
   SystematicName = skip;
   if(SystematicName == "0"){
     SystematicName = "nominal";
     isRunAllSystematic = 0;
   }
   else if(SystematicName == "all"){
     SystematicName = "";
     isRunAllSystematic = 1;
   }

//Add reweighting factor
   infile>>config;
   getline(infile, FileLine);
   myLog<<LOG_INFO<<config<<FileLine<<endl;
   PreRunReweightingFactor = config;

//Fitting
   infile>>config;
   getline(infile, FileLine);
   myLog<<LOG_INFO<<config<<FileLine<<endl;
   Fitting = config;

//BDTFile list
   infile>>skip;
   getline(infile, FileLine);
   myLog<<LOG_INFO<<skip<<FileLine<<endl;
   BDTFileList = skip;
   if(BDTFileList == "0"){
     isBDT = false;
   }
   else{
     isBDT = true;
     ifstream myBDTFile;
       myBDTFile.open(BDTFileList);
       myBDTFile>>BDTFile;
       myBDTFile>>BDTFileSR;
       myBDTFile>>BDTFileSR100;
       if(BDTFileSR != ""){
         isBDTSR = true;
	 if(BDTFileSR.Contains("OnlyDec")){
           isOnlyDecSR = true;
         }
         if(BDTFileSR.Contains("NoPtV")){
           isNoPtVSR = true;
         }
       }
       if(BDTFileSR100 != ""){
         isBDTSR100 = true;
	 if(BDTFileSR100.Contains("OnlyDec")){
           isOnlyDecSR100 = true;
         }
         if(BDTFileSR100.Contains("NoPtV")){
           isNoPtVSR100 = true;
         }
       }
   }

//Error Type, Error set
   if(infile>>skip>>config){
     getline(infile, FileLine);
     myLog<<LOG_INFO<<skip<<" "<<config<<FileLine<<endl;
     ErrorType = skip;
     ErrorSet = config;
   }

   if(isBDT){
     myLog<<LOG_INFO<<endl;
     myLog<<LOG_INFO<<"BDT file:"<<endl;
     myLog<<LOG_INFO<<BDTFile<<endl;
   }
   if(isBDTSR){
     myLog<<LOG_INFO<<"BDT SR file:"<<endl;
     myLog<<LOG_INFO<<BDTFileSR<<endl;
   }
   if(isBDTSR100){
     myLog<<LOG_INFO<<"BDT SR100 file:"<<endl;
     myLog<<LOG_INFO<<BDTFileSR100<<endl;
   }
 }

 if(RootType == "PreWZPolarization"){
//run bkg
   infile>>config;
   getline(infile, FileLine);
   myLog<<LOG_INFO<<config<<FileLine<<endl;
   doBkg = config;

//run control region
   infile>>config;
   getline(infile, FileLine);
   myLog<<LOG_INFO<<config<<FileLine<<endl;
   doControlRegion = config;

//run fake rate
   infile>>config;
   getline(infile, FileLine);
   myLog<<LOG_INFO<<config<<FileLine<<endl;
   doFakeRate = config;

//Process Option
   infile>>config; 
   getline(infile, FileLine);
   myLog<<LOG_INFO<<config<<FileLine<<endl;
   ProcessOption = config;

   if(ProcessOption == 1){//Generate Tree cannot use multi-thread.
     RunType = "Condor";
     TotalThread = 1;
   }

//Ntuple Name
   infile>>skip;
   getline(infile, FileLine);
   myLog<<LOG_INFO<<skip<<FileLine<<endl;
   NtupleName = skip;

//Year
   infile>>config;
   getline(infile, FileLine);
   myLog<<LOG_INFO<<config<<FileLine<<endl;
   Year = config;

//do truth selection
   infile>>config;
   getline(infile, FileLine);
   myLog<<LOG_INFO<<config<<FileLine<<endl;
   doTruthSelection = config;

//SumOfWeight File List
   infile>>skip;
   getline(infile, FileLine);
   myLog<<LOG_INFO<<skip<<FileLine<<endl;
   SumOfWeightList = skip;

//do save PDF and QCD uncertainty
   infile>>config;
   getline(infile, FileLine);
   myLog<<LOG_INFO<<config<<FileLine<<endl;
   doPDFAndQCDUnc = config;

//Add reweighting factor
   infile>>config;
   getline(infile, FileLine);
   myLog<<LOG_INFO<<config<<FileLine<<endl;
   PreRunReweightingFactor = config;

//Fitting
   infile>>config;
   getline(infile, FileLine);
   myLog<<LOG_INFO<<config<<FileLine<<endl;
   Fitting = config;

//LWTNNFile list
   infile>>skip;
   getline(infile, FileLine);
   myLog<<LOG_INFO<<skip<<FileLine<<endl;
   LWTNNFileList = skip;
   if(LWTNNFileList == "0"){
     isLWTNNNuPz = false;
     isLWTNNPolClassifier = false;
   }
   else{
     myLog<<LOG_INFO<<endl;
     myLog<<LOG_INFO<<"Reading LWTNN files:"<<endl;
     ifstream myLWTNNFile;
       myLWTNNFile.open(LWTNNFileList);
       TString LWTNNType;
       while(myLWTNNFile >> LWTNNType){
         if(LWTNNType == "NuPz"){
           isLWTNNNuPz = true;
           myLWTNNFile>>NuPzEven;
           myLWTNNFile>>NuPzOdd;
           myLog<<LOG_INFO<<LWTNNType<<":"<<endl;
           myLog<<LOG_INFO<<"Even: "<<NuPzEven<<endl;
           myLog<<LOG_INFO<<"Odd:  "<<NuPzOdd<<endl;
         }
         else if(LWTNNType == "PolClassifier"){
           isLWTNNPolClassifier = true;
           myLWTNNFile>>PolClassifierEven;
           myLWTNNFile>>PolClassifierOdd;
           myLog<<LOG_INFO<<LWTNNType<<":"<<endl;
           myLog<<LOG_INFO<<"Even: "<<PolClassifierEven<<endl;
           myLog<<LOG_INFO<<"Odd:  "<<PolClassifierOdd<<endl;
         }
         else if(LWTNNType == "NLOPol"){
           isLWTNNNLOPol = true;
           myLWTNNFile>>DNNLLFile;
           myLWTNNFile>>DNNLTFile;
           myLWTNNFile>>DNNTLFile;
           myLWTNNFile>>DNNTTFile;
           myLog<<LOG_INFO<<LWTNNType<<":"<<endl;
           myLog<<LOG_INFO<<"DNN LL: "<<DNNLLFile<<endl;
           myLog<<LOG_INFO<<"DNN LT: "<<DNNLTFile<<endl;
           myLog<<LOG_INFO<<"DNN TL: "<<DNNTLFile<<endl;
           myLog<<LOG_INFO<<"DNN TT: "<<DNNTTFile<<endl;
         }
       }
   }
 }

//Fitting Data Information
 if(RootType == "CalibrationForResBos"){
   infile>>skip;
   getline(infile, FileLine);
   myLog<<LOG_INFO<<skip<<FileLine<<endl;
   FittingData = skip;

   if(FittingData != ""){
     ifstream myFittingInfo;
       myFittingInfo.open(FittingData, ios::in);
     myFittingInfo>>FittingFile;
     myFittingInfo>>FittingHist;
   }
 }


 if(RootType == "PreQBH"){
//run fake rate
   infile>>config;
   getline(infile, FileLine);
   myLog<<LOG_INFO<<config<<FileLine<<endl;
   doFakeRate = config;

//Process Option
   infile>>config;
   getline(infile, FileLine);
   myLog<<LOG_INFO<<config<<FileLine<<endl;
   ProcessOption = config;

   if(ProcessOption == 1){//Generate Tree cannot use multi-thread.
     RunType = "Condor";
     TotalThread = 1;
   }

//Ntuple Name
   infile>>skip;
   getline(infile, FileLine);
   myLog<<LOG_INFO<<skip<<FileLine<<endl;
   NtupleName = skip;

 }

 if(RootType == "HMDY"){
//Systematic name
   infile>>skip;
   getline(infile, FileLine);
   myLog<<LOG_INFO<<skip<<FileLine<<endl;
   SystematicName = skip;

//Ntuple Name
   infile>>skip;
   getline(infile, FileLine);
   myLog<<LOG_INFO<<skip<<FileLine<<endl;
   NtupleName = skip;

//topDD reweighting
   infile>>skip;
   topDDList = skip;
   getline(infile, FileLine);
   myLog<<LOG_INFO<<topDDList<<FileLine<<endl;

   if(topDDList != "0" && topDDList != ""){
     ifstream myTopDDFile;
       myTopDDFile.open(topDDList);
     while(myTopDDFile >> skip){
       topDDFile.push_back(skip);
       myTopDDFile >> skip;
       TransferName_ee.push_back(skip);
       myTopDDFile >> skip;
       TransferName_mm.push_back(skip);
     }
     myLog<<LOG_INFO<<"There are "<<topDDFile.size()<<" input topDD files."<<endl;
     for(int i = 0; i < topDDFile.size(); i++){
       myLog<<LOG_INFO<<topDDFile.at(i)<<"   "<<TransferName_ee.at(i)<<"   "<<TransferName_mm.at(i)<<endl;
     }

     if(topDDFile.size() != 3){
       myLog<<LOG_INFO<<"Warning! we plan to use 3 top DD transfer factor."<<endl;
     }
   }

//Input Fake Efficiency
   if(infile>>skip){
     getline(infile, FileLine);
     myLog<<LOG_INFO<<skip<<FileLine<<endl;
     HMDYFakeEffFile = skip;
   }
 }

 if(RootType == "PreHMDY"){
//SumOfWeight File List
   infile>>skip;
   getline(infile, FileLine);
   myLog<<LOG_INFO<<skip<<FileLine<<endl;
   SumOfWeightList = skip;

//Process Option
   infile>>config;
   getline(infile, FileLine);
   myLog<<LOG_INFO<<config<<FileLine<<endl;
   ProcessOption = config;

   if(ProcessOption == 1){//Generate Tree cannot use multi-thread.
     RunType = "Condor";
     TotalThread = 1;
   }

//Ntuple Name
   infile>>skip;
   getline(infile, FileLine);
   myLog<<LOG_INFO<<skip<<FileLine<<endl;
   NtupleName = skip;

//Tree Name
   if(infile>>skip){
     getline(infile, FileLine);
     myLog<<LOG_INFO<<skip<<FileLine<<endl;
     TreeName = skip;
   }

//Run Type
   if(infile>>skip){
     getline(infile, FileLine);
     myLog<<LOG_INFO<<skip<<FileLine<<endl;
     HMDYisNormalRun = skip;
   }

//Input Fake Efficiency
   if(infile>>skip){
     getline(infile, FileLine);
     myLog<<LOG_INFO<<skip<<FileLine<<endl;
     HMDYFakeEffFile = skip;
   }
 }

 if(RootType == "ZPrime"){
//Systematic name
   infile>>skip;
   getline(infile, FileLine);
   myLog<<LOG_INFO<<skip<<FileLine<<endl;
   SystematicName = skip;

//Ntuple Name
   infile>>skip;
   getline(infile, FileLine);
   myLog<<LOG_INFO<<skip<<FileLine<<endl;
   NtupleName = skip;

//topDD reweighting
   infile>>skip;
   topDDList = skip;
   getline(infile, FileLine);
   myLog<<LOG_INFO<<topDDList<<FileLine<<endl;

   if(topDDList != "0" && topDDList != ""){
     ifstream myTopDDFile;
       myTopDDFile.open(topDDList);
     while(myTopDDFile >> skip){
       topDDFile.push_back(skip);
       myTopDDFile >> skip;
       TransferName_ee.push_back(skip);
       myTopDDFile >> skip;
       TransferName_mm.push_back(skip);
     }
     myLog<<LOG_INFO<<"There are "<<topDDFile.size()<<" input topDD files."<<endl;
     for(int i = 0; i < topDDFile.size(); i++){
       myLog<<LOG_INFO<<topDDFile.at(i)<<"   "<<TransferName_ee.at(i)<<"   "<<TransferName_mm.at(i)<<endl;
     }

     if(topDDFile.size() != 3){
       myLog<<LOG_INFO<<"Warning! we plan to use 3 top DD transfer factor."<<endl;
     }
   }

//Input Fake Efficiency
   if(infile>>skip){
     getline(infile, FileLine);
     myLog<<LOG_INFO<<skip<<FileLine<<endl;
     ZPrimeFakeEffFile = skip;
   }
 }

 if(RootType == "PreZPrime"){
//SumOfWeight File List
   infile>>skip;
   getline(infile, FileLine);
   myLog<<LOG_INFO<<skip<<FileLine<<endl;
   SumOfWeightList = skip;

//Process Option
   infile>>config;
   getline(infile, FileLine);
   myLog<<LOG_INFO<<config<<FileLine<<endl;
   ProcessOption = config;

   if(ProcessOption == 1){//Generate Tree cannot use multi-thread.
     RunType = "Condor";
     TotalThread = 1;
   }

//Ntuple Name
   infile>>skip;
   getline(infile, FileLine);
   myLog<<LOG_INFO<<skip<<FileLine<<endl;
   NtupleName = skip;

//Tree Name
   if(infile>>skip){
     getline(infile, FileLine);
     myLog<<LOG_INFO<<skip<<FileLine<<endl;
     TreeName = skip;
   }

//Run Type
   if(infile>>skip){
     getline(infile, FileLine);
     myLog<<LOG_INFO<<skip<<FileLine<<endl;
     ZPrimeisNormalRun = skip;
   }

//Input Fake Efficiency
   if(infile>>skip){
     getline(infile, FileLine);
     myLog<<LOG_INFO<<skip<<FileLine<<endl;
     if(skip != "0") ZPrimeFakeEffFile = skip;
   }

//Input kfactor
   if(infile>>skip){
     getline(infile, FileLine);
     myLog<<LOG_INFO<<skip<<FileLine<<endl;
     if(skip != "0") ZPrimeKFactorFile = skip;
   }

//Input AngularFile
   if(infile>>skip){
     getline(infile, FileLine);
     myLog<<LOG_INFO<<skip<<FileLine<<endl;
     if(skip != "0") ZPrimeAngularFile = skip;
   }
 }

 if(RootType == "MadGraph"){
   infile>>config;
   getline(infile, FileLine);
   myLog<<LOG_INFO<<config<<FileLine<<endl;
   MadGraphReweightID = config;
 }

 myLog<<LOG_INFO<<endl;


}

Control& Control::operator=(const Control &myClass)
{
 if(this != &myClass){
   this->TotalThread = myClass.TotalThread;
   this->isReweight = myClass.isReweight;
   this->isFSR = myClass.isFSR;
   this->isTest = myClass.isTest;
   this->isRunAllSystematic = myClass.isRunAllSystematic;
   this->RunType = myClass.RunType;
   this->RootType = myClass.RootType;
   this->FileList = myClass.FileList;
   this->SaveName = myClass.SaveName;
   this->CutFile = myClass.CutFile;
   this->SystematicList = myClass.SystematicList;
   this->oldPDFName = myClass.oldPDFName;
   this->oldPDFset = myClass.oldPDFset;
   this->newPDFName = myClass.newPDFName;
   this->newPDFset = myClass.newPDFset;
   this->ECM = myClass.ECM;
   this->isDilution = myClass.isDilution;
   this->PreRunReweightingFactor = myClass.PreRunReweightingFactor;
   this->Fitting = myClass.Fitting;
   this->FittingData = myClass.FittingData;
   this->ProcessOption = myClass.ProcessOption;
   this->doTruthSelection = myClass.doTruthSelection;
   this->NtupleName = myClass.NtupleName;
   this->Year = myClass.Year;
   this->doBkg = myClass.doBkg;
   this->doControlRegion = myClass.doControlRegion;
   this->doFakeRate = myClass.doFakeRate;
   this->SystematicName = myClass.SystematicName;
   this->UpDn = myClass.UpDn;
   this->SumOfWeightList = myClass.SumOfWeightList;
   this->doPDFAndQCDUnc = myClass.doPDFAndQCDUnc;
   this->ErrorType = myClass.ErrorType;
   this->ErrorSet = myClass.ErrorSet;
   this->BDTFileList = myClass.BDTFileList;
   this->LWTNNFileList = myClass.LWTNNFileList;
   this->DataListFile = myClass.DataListFile;
   this->isPPbar = myClass.isPPbar;
   this->OriginWMass = myClass.OriginWMass;
   this->NewWMass = myClass.NewWMass;
   this->WWidth = myClass.WWidth;
   this->ScaleSlope = myClass.ScaleSlope;
   this->CalibrationOption = myClass.CalibrationOption;
   this->LeptonPtMin = myClass.LeptonPtMin;
   this->LeptonPtMiddle = myClass.LeptonPtMiddle;
   this->LeptonPtMax = myClass.LeptonPtMax;
   this->topDDList = myClass.topDDList;
   this->TreeName = myClass.TreeName;
   this->HMDYisNormalRun = myClass.HMDYisNormalRun;
   this->HMDYFakeEffFile = myClass.HMDYFakeEffFile;
   this->ZPrimeisNormalRun = myClass.ZPrimeisNormalRun;
   this->ZPrimeFakeEffFile = myClass.ZPrimeFakeEffFile;
   this->ZPrimeKFactorFile = myClass.ZPrimeKFactorFile;
   this->ZPrimeAngularFile = myClass.ZPrimeAngularFile;
   this->MadGraphReweightID = myClass.MadGraphReweightID;

//not input parameter
   this->RootName = myClass.RootName;
   this->RootNames = myClass.RootNames;
   this->TotalFileNumber = myClass.TotalFileNumber;

   this->NFilePerJob = myClass.NFilePerJob;
   this->TotalRound = myClass.TotalRound;
   this->OneFilePerJob = myClass.OneFilePerJob;

   this->FittingFile = myClass.FittingFile;
   this->FittingHist = myClass.FittingHist;

   this->isBDT = myClass.isBDT;
   this->isBDTSR = myClass.isBDTSR;
   this->isBDTSR100 = myClass.isBDTSR100;
   this->BDTFile = myClass.BDTFile;
   this->BDTFileSR = myClass.BDTFileSR;
   this->BDTFileSR100 = myClass.BDTFileSR100;

   this->isOnlyDecSR = myClass.isOnlyDecSR;
   this->isNoPtVSR = myClass.isNoPtVSR;
   this->isOnlyDecSR100 = myClass.isOnlyDecSR100;
   this->isNoPtVSR100 = myClass.isNoPtVSR100;

   this->isLWTNNNuPz = myClass.isLWTNNNuPz;
   this->isLWTNNPolClassifier = myClass.isLWTNNPolClassifier;
   this->isLWTNNNLOPol = myClass.isLWTNNNLOPol;
   this->DNNLLFile = myClass.DNNLLFile;
   this->DNNLTFile = myClass.DNNLTFile;
   this->DNNTLFile = myClass.DNNTLFile;
   this->DNNTTFile = myClass.DNNTTFile;
   this->NuPzEven = myClass.NuPzEven;
   this->NuPzOdd = myClass.NuPzOdd;
   this->PolClassifierEven = myClass.PolClassifierEven;
   this->PolClassifierOdd = myClass.PolClassifierOdd;

   this->DataList = myClass.DataList;

   this->topDDFile = myClass.topDDFile;
   this->TransferName_ee = myClass.TransferName_ee;
   this->TransferName_mm = myClass.TransferName_mm;

   this->myLog = myClass.myLog;
 }

 return *this;
}

void Control::Help()
{
 myLog<<"Thread                                          *Running method (Thread/Condor)"<<endl;
 myLog<<"2                                               *Thread Number"<<endl;
 myLog<<"ZEvent                                          *Rootfile Type (Wasymmetry/ResBos/ResBosW/....)"<<endl;
 myLog<<"data.list                                       *file list"<<endl;
 myLog<<"MC_results.root                                 *save rootfile name"<<endl;
 myLog<<"0                                               *global cut information"<<endl;
 myLog<<"0                                               *is Test(1: test, 0: normal run)"<<endl;
 myLog<<"0                                               *run all systematic"<<endl;

}

void Control::GetRunningType(int recall)
{
 int TotalThread = this->TotalThread;
 int TotalRound = 1;
 int NFilePerJob = this->TotalFileNumber;
 int FileMaximum = 1000;

 if(TotalThread * this->TotalFileNumber >= FileMaximum){
//this is the strategy for not too many files but with big thread number running.
   NFilePerJob = FileMaximum / TotalThread;
   TotalRound = this->TotalFileNumber / NFilePerJob + 1;

   this->NFilePerJob = NFilePerJob;
   this->TotalRound = TotalRound;

//this is the strategy for too many files in thread running.
   if(this->TotalFileNumber >= this->TotalThread && this->TotalRound > 1){
     this->OneFilePerJob = true;
     this->TotalRound = this->TotalFileNumber / this->TotalThread + 1;
   }

   if(recall == 0) myLog<<LOG_INFO<<"First call the function to get the running type."<<endl;
   if(recall == 1) myLog<<LOG_INFO<<"The total file number has changed to "<<this->TotalFileNumber<<", recalculate the running type."<<endl;

   if(!this->OneFilePerJob){
     myLog<<LOG_INFO<<endl;
     myLog<<LOG_INFO<<"Number of files are too many, submit thread job for "<<TotalRound<<" times."<<endl;
     myLog<<LOG_INFO<<"Number of files per Job are "<<NFilePerJob<<endl;
     myLog<<LOG_INFO<<endl;
   }
   else{
     myLog<<LOG_INFO<<endl;
     myLog<<LOG_INFO<<"Using the strategy of one file per thread."<<endl;
     myLog<<LOG_INFO<<endl;
   }
 }
 else{
   this->NFilePerJob = NFilePerJob;
   this->TotalRound = TotalRound;
   this->OneFilePerJob = false;

   if(recall == 0) myLog<<LOG_INFO<<"First call the function to get the running type."<<endl;
   if(recall == 1) myLog<<LOG_INFO<<"The total file number has changed to "<<this->TotalFileNumber<<", recalculate the running type."<<endl;
 }

}
