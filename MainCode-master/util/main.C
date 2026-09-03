#include "Analysis/Common.h"

using namespace std;

int main(int argc, char** argv)
{
 if(argc != 2){
   cout<<"usage ./loopMC cardfile"<<endl;
   ofstream outputfile;
   Logstream myLog;
   outputfile.open("save.log");
   myLog.Initial(cout, outputfile);
   Control process;
   process.LinkLog(myLog);
   cout<<"Please construct cardfile as following:"<<endl;
   process.Help();
   return 0;
 }

 ofstream outputfile;
 Logstream myLog;
 outputfile.open("save.log");
 myLog.Initial(cout, outputfile);

 myLog<<LOG_INFO<<"// ----------------------------- //"<<endl;
 myLog<<LOG_INFO<<"//       Loop Events Begin       //"<<endl;
 myLog<<LOG_INFO<<"// ----------------------------- //"<<endl;

 Control process;
 process.LinkLog(myLog);
 process.ReadFile(argv[1]);

 bool isReweight = process.isReweight;
 bool isTest = process.isTest;

 if(process.RunType != "Thread" && process.RunType != "Condor"){
    myLog<<LOG_ERROR<<"For RunType, Please use \"Thread\" or \"Condor\""<<endl;
    myLog<<LOG_ERROR<<"Please construct cardfile as following:"<<endl;
    myLog<<LOG_ERROR<<""<<endl;
    process.Help();
    return 0;
 }

 if(process.RootType != "Wasymmetry" && process.RootType != "ResBos" && process.RootType != "ResBosW" && process.RootType != "Pythia" && process.RootType != "PythiaW"
    && process.RootType != "ResBosWTev" && process.RootType != "ResBosD0"
    && process.RootType != "Herwig"
    && process.RootType != "FwdReco" && process.RootType != "ResBosEnergyScale" && process.RootType != "WZPolarization" && process.RootType != "Custom"
    && process.RootType != "PreWZPolarization" && process.RootType != "CellInfo"
    && process.RootType != "PythiaWW" && process.RootType != "SherpaWW" && process.RootType != "ResBosCMS" && process.RootType != "FlavorAsym"
    && process.RootType != "ResBosHighMassZ" && process.RootType != "MadGraph"
    && process.RootType != "QBH" && process.RootType != "PreQBH"
    && process.RootType != "HMDY" && process.RootType != "PreHMDY"
    && process.RootType != "ZPrime" && process.RootType != "PreZPrime"){

    myLog<<LOG_ERROR<<"For RootType, Please use \"Wasymmetry\" or \"ResBos\" or \"ResBosW\" or \"Pythia\" or \"PythiaW\" or \"Herwig\""<<endl;
    myLog<<LOG_ERROR<<" or \"ResBosWTev\" or \"ResBosD0\" or \"FwdReco\" or \"ResBosEnergyScale\" or \"WZPolarization\" or \"Custom\""<<endl;
    myLog<<LOG_ERROR<<" or \"PreWZPolarization\" or \"CellInfo\" or \"PythiaWW\" or \"SherpaWW\" or \"ResBosCMS\""<<endl;
    myLog<<LOG_ERROR<<" or \"FlavorAsym\" or \"ResBosHighMassZ\" or \"MadGraph\""<<endl;
    myLog<<LOG_ERROR<<" or \"QBH\" or \"PreQBH\" or \"HMDY\" or \"PreHMDY\""<<endl;
    myLog<<LOG_ERROR<<" or \"ZPrime\" or \"PreZPrime\""<<endl;
    myLog<<LOG_ERROR<<"Please construct cardfile as following:"<<endl;
    myLog<<LOG_ERROR<<""<<endl;
    process.Help();

    return 0;
 }

 if(process.RunType == "Thread"){
   myLog<<LOG_INFO<<"Thread: Start Time: "<<getTime()<<endl;

   process.GetRunningType();

   TString RootType = process.RootType;

   if(RootType == "Wasymmetry"){
     ThreadRunWasym(process);
   }

   if(RootType == "ResBos"){
     ThreadRunResBos(process);
   }

   if(RootType == "ResBosW"){
     ThreadRunResBosW(process);
   }

   if(RootType == "ResBosWTev"){
     ThreadRunResBosWTev(process);
   }

   if(RootType == "ResBosCMS"){
     ThreadRunResBosCMS(process);
   }

   if(RootType == "ResBosD0"){
     ThreadRunResBosD0(process);
   }

   if(RootType == "Pythia"){
     HistsPythia* myhists;
     myhists = new HistsPythia();
     myhists->openFile(process.SaveName);
     myhists->LinkLog(process.myLog);
     myhists->bookHists(process.TotalThread);
     if(process.PreRunReweightingFactor) ThreadRunPythia(process, myhists, 1);
     if(process.PreRunReweightingFactor) myhists->MergeHists();
     if(process.PreRunReweightingFactor) myhists->GetReweightFactor();

     if(process.PreRunReweightingFactor) ThreadRunPythia(process, myhists, 2);
     if(!process.PreRunReweightingFactor) ThreadRunPythia(process, myhists, 0);
     myhists->MergeHists();

     if(process.Fitting){
       myhists->LinkClass(myhists);

       TMinuitHelper *myMinuit = new TMinuitHelper(2);
       myMinuit->SetFCN(DilutionFitting);
       myMinuit->Input(0, "k", -0.5, 0.5, -1.0, 0.0);
       myMinuit->Input(1, "b", 0.5, 0.5, 0.0, 1.0);
       myMinuit->Exec("SIMPLEX", 100000, 1);//tolerance*0.001
       myMinuit->Exec("MIGRAD", 100000, 0.001);
       myMinuit->GetParameter();
       double* par = new double[2];
       myMinuit->GetParameters(par);
       myhists->InputParameter(par[0], par[1]);
     }

     myhists->saveHists();
     delete myhists;
   }

   if(RootType == "PythiaW"){
     ThreadRunPythiaW(process);
   }

   if(RootType == "PythiaWW"){
     ThreadRunPythiaWW(process);
   }

   if(RootType == "Herwig"){
     ThreadRunHerwig(process);
   }

   if(RootType == "FwdReco"){
     ThreadRunFwdReco(process);
   }

   if(RootType == "ResBosEnergyScale"){
     ThreadRunResBosEnergyScale(process);
   }

   if(RootType == "WZPolarization"){
     HistsWZPolarization* myhists;
     myhists = new HistsWZPolarization();
     myhists->openFile(process.SaveName);
     myhists->LinkLog(process.myLog);
     myhists->InputSystematicName(process.SystematicName);
     if(process.isRunAllSystematic) myhists->RunAllSystematic();
     if(process.doBkg) myhists->RunBkg();
     if(process.doControlRegion) myhists->RunControlRegion();
     if(process.doFakeRate) myhists->RunFakeRate(process.doFakeRate);
     myhists->bookHists(process.TotalThread);

     if(process.doFakeRate || process.PreRunReweightingFactor) ThreadRunWZPolarization(process, myhists);
     if(process.doFakeRate || process.PreRunReweightingFactor) myhists->MergeHists();
     if(process.doFakeRate) myhists->GetFakeRate();
     if(process.PreRunReweightingFactor) myhists->GetReweightFactor();
     if(process.doFakeRate != 3) myhists->ResetHists();

     if(process.doFakeRate == 3){}
     else{
       ThreadRunWZPolarization(process, myhists);
       myhists->MergeHists();

       if(process.Fitting){
         myhists->LinkClass(myhists);

         TMinuitHelper *myMinuit = new TMinuitHelper(4);
         myMinuit->SetFCN(ScaleFitting);
         myMinuit->Input(0, "LL", 1.0, 0.5, 0.0, 2.0);
         myMinuit->Input(1, "LT", 1.0, 0.5, 0.0, 2.0);
         myMinuit->Input(2, "TL", 1.0, 0.5, 0.0, 2.0);
         myMinuit->Input(3, "TT", 1.0, 0.5, 0.0, 2.0);
         myMinuit->Exec("SIMPLEX", 10000, 1);//tolerance*0.001
         myMinuit->GetParameter();
       }
     }

     myhists->saveHists();
     delete myhists;

   }

   if(RootType == "PreWZPolarization"){
     HistsWZPolarization* myhists;
     myhists = new HistsWZPolarization();
     myhists->openFile(process.SaveName);
     myhists->LinkLog(process.myLog);
     if(process.isRunAllSystematic) myhists->RunAllSystematic();
     if(process.doBkg) myhists->RunBkg();
     if(process.doControlRegion) myhists->RunControlRegion();
     if(process.doFakeRate) myhists->RunFakeRate(process.doFakeRate);
     myhists->bookHists(process.TotalThread);

     if(process.doFakeRate || process.PreRunReweightingFactor) ThreadRunWZPolarization(process, myhists);
     if(process.doFakeRate || process.PreRunReweightingFactor) myhists->MergeHists();
     if(process.doFakeRate) myhists->GetFakeRate();
     if(process.PreRunReweightingFactor) myhists->GetReweightFactor();

     if(process.doFakeRate == 3){}
     else{
       ThreadRunPreWZPolarization(process, myhists);
       myhists->MergeHists();

       if(process.Fitting){
         myhists->LinkClass(myhists);

         TMinuitHelper *myMinuit = new TMinuitHelper(4);
         myMinuit->SetFCN(ScaleFitting);
         myMinuit->Input(0, "LL", 1.0, 0.5, 0.0, 2.0);
         myMinuit->Input(1, "LT", 1.0, 0.5, 0.0, 2.0);
         myMinuit->Input(2, "TL", 1.0, 0.5, 0.0, 2.0);
         myMinuit->Input(3, "TT", 1.0, 0.5, 0.0, 2.0);
         myMinuit->Exec("SIMPLEX", 10000, 1);//tolerance*0.001
         myMinuit->GetParameter();

       }
     }

     myhists->saveHists();
     delete myhists;

   }

   if(RootType == "QBH"){
     HistsQBH* myhists;
     myhists = new HistsQBH();
     myhists->openFile(process.SaveName);
     myhists->LinkLog(process.myLog);
     myhists->InputSystematicName(process.SystematicName);
     myhists->bookHists(process.TotalThread);
     ThreadRunQBH(process, myhists);
     myhists->MergeHists();
     myhists->saveHists();
     delete myhists;
   }

   if(RootType == "PreQBH"){
     HistsQBH* myhists;
     myhists = new HistsQBH();
     myhists->openFile(process.SaveName);
     myhists->LinkLog(process.myLog);
     myhists->InputSystematicName(process.SystematicName);
     myhists->bookHists(process.TotalThread);
     ThreadRunPreQBH(process, myhists);
     myhists->MergeHists();
     myhists->saveHists();
     delete myhists;
   }

   if(RootType == "HMDY"){
     HistsHMDY* myhists;
     myhists = new HistsHMDY();
     myhists->openFile(process.SaveName);
     myhists->LinkLog(process.myLog);
     myhists->InputSystematicName(process.SystematicName);
     myhists->bookHists(process.TotalThread);
     ThreadRunHMDY(process, myhists);
     myhists->MergeHists();
     myhists->GetTransferFactor();
     myhists->saveHists();
     delete myhists;
   }

   if(RootType == "PreHMDY"){
     HistsHMDY* myhists;
     myhists = new HistsHMDY();
     myhists->openFile(process.SaveName);
     myhists->LinkLog(process.myLog);
     myhists->InputSystematicName(process.SystematicName);
     myhists->bookHists(process.TotalThread);
     ThreadRunPreHMDY(process, myhists);
     myhists->MergeHists();
     myhists->saveHists();
     delete myhists;
   }

   if(RootType == "ZPrime"){
     HistsZPrime* myhists;
     myhists = new HistsZPrime();
     myhists->openFile(process.SaveName);
     myhists->LinkLog(process.myLog);
     myhists->InputSystematicName(process.SystematicName);
     myhists->bookHists(process.TotalThread);
     ThreadRunZPrime(process, myhists);
     myhists->MergeHists();
     myhists->GetTransferFactor();
     myhists->saveHists();
     delete myhists;
   }

   if(RootType == "PreZPrime"){
     HistsZPrime* myhists;
     myhists = new HistsZPrime();
     myhists->openFile(process.SaveName);
     myhists->LinkLog(process.myLog);
     myhists->InputSystematicName(process.SystematicName);
     myhists->bookHists(process.TotalThread);
     ThreadRunPreZPrime(process, myhists);
     myhists->MergeHists();
     myhists->saveHists();
     delete myhists;
   }

   if(RootType == "Custom"){
     ThreadRunCustom(process);
   }

   /*if(RootType == "CalibrationForResBos"){
     HistsResBos* myhists = new HistsResBos();
     myhists->openFile(process.SaveName);
     myhists->LinkLog(process.myLog);
     myhists->bookHists(process.TotalThread);
     myhists->InputData(process.FittingFile, process.FittingHist);

     RunResBosCalibration(process, myhists);

     TMinuitHelper *myMinuit = new TMinuitHelper(2);
     myMinuit->SetFCN(CalibrationForResBos);
     myMinuit->Input(0, "Scale", 1.0, 0.02, 0.95, 1.05);
     myMinuit->Input(1, "Smear", 0.01, 0.005, 0.0, 0.002);
     myMinuit->Exec("SIMPLEX", 10000, 1000);//tolerance*0.001
     myMinuit->GetParameter();

     myhists->MergeHists();
     myhists->saveHists();
     delete myhists;

   }*/

   if(RootType == "CellInfo"){
     ThreadRunCellInfo(process);
   }

   if(RootType == "SherpaWW"){
     ThreadRunSherpaWW(process);
   }

   if(RootType == "FlavorAsym"){
     ThreadRunFlavorAsym(process);
   }

   if(RootType == "ResBosHighMassZ"){
     ThreadRunResBosHighMassZ(process);
   }

   if(RootType == "MadGraph"){
     ThreadRunMadGraph(process);
   }

   myLog<<LOG_INFO<<"Thread: End Time:   "<<getTime()<<endl;
 }

 if(process.RunType == "Condor"){
   myLog<<LOG_INFO<<"Condor: Start Time: "<<getTime()<<endl;
   TString RootType = process.RootType;

   if(RootType == "Wasymmetry"){
     CondorRunWasym(process);
   }

   if(RootType == "ResBos"){
     CondorRunResBos(process);
   } 

   if(RootType == "ResBosW"){
     CondorRunResBosW(process);
   } 

   if(RootType == "ResBosWTev"){
     CondorRunResBosWTev(process);
   }

   if(RootType == "ResBosCMS"){
     CondorRunResBosCMS(process);
   }

   if(RootType == "ResBosD0"){
     CondorRunResBosD0(process);
   }

   if(RootType == "Pythia"){
     HistsPythia* myhists;
     myhists = new HistsPythia();
     myhists->openFile(process.SaveName);
     myhists->LinkLog(process.myLog);
     myhists->bookHists(1);
     if(process.PreRunReweightingFactor) CondorRunPythia(process, myhists);
     if(process.PreRunReweightingFactor) myhists->MergeHists();
     if(process.PreRunReweightingFactor) myhists->GetReweightFactor();
     
     if(process.PreRunReweightingFactor) CondorRunPythia(process, myhists);
     if(!process.PreRunReweightingFactor) CondorRunPythia(process, myhists);
     myhists->MergeHists();

     myhists->saveHists();
     delete myhists;
   }

   if(RootType == "PythiaW"){
     CondorRunPythiaW(process);
   }

   if(RootType == "PythiaWW"){
     CondorRunPythiaWW(process);
   }

   if(RootType == "Herwig"){
     CondorRunHerwig(process);
   }

   if(RootType == "FwdReco"){
     CondorRunFwdReco(process);
   }

   if(RootType == "ResBosEnergyScale"){
     CondorRunResBosEnergyScale(process);
   }

   if(RootType == "WZPolarization"){
     HistsWZPolarization* myhists;
     myhists = new HistsWZPolarization();
     myhists->openFile(process.SaveName);
     myhists->LinkLog(process.myLog);
     myhists->InputSystematicName(process.SystematicName);
     if(process.isRunAllSystematic) myhists->RunAllSystematic();
     if(process.doBkg) myhists->RunBkg();
     if(process.doControlRegion) myhists->RunControlRegion();
     if(process.doFakeRate) myhists->RunFakeRate(process.doFakeRate);
     myhists->bookHists(1);

     if(process.doFakeRate || process.PreRunReweightingFactor) CondorRunWZPolarization(process, myhists);
     if(process.doFakeRate || process.PreRunReweightingFactor) myhists->MergeHists();
     if(process.doFakeRate) myhists->GetFakeRate();
     if(process.PreRunReweightingFactor) myhists->GetReweightFactor();
     if(process.doFakeRate != 3) myhists->ResetHists();

     if(process.doFakeRate == 3){}
     else{
       CondorRunWZPolarization(process, myhists);
     }

     myhists->saveHists();
     delete myhists;
   }

   if(RootType == "PreWZPolarization"){
     if(process.ProcessOption == 2){ 
       HistsWZPolarization* myhists;
       myhists = new HistsWZPolarization();
       myhists->openFile(process.SaveName);
       myhists->LinkLog(process.myLog);
       if(process.isRunAllSystematic) myhists->RunAllSystematic();
       if(process.doBkg) myhists->RunBkg();
       if(process.doControlRegion) myhists->RunControlRegion();
       if(process.doFakeRate) myhists->RunFakeRate(process.doFakeRate);
       myhists->bookHists(1);

       if(process.doFakeRate || process.PreRunReweightingFactor) CondorRunWZPolarization(process, myhists);
       if(process.doFakeRate || process.PreRunReweightingFactor) myhists->MergeHists();
       if(process.doFakeRate) myhists->GetFakeRate();
       if(process.PreRunReweightingFactor) myhists->GetReweightFactor();

       if(process.doFakeRate == 3){}
       else{
         CondorRunPreWZPolarization(process, myhists);
       }

       myhists->saveHists();
       delete myhists;
     }
     if(process.ProcessOption == 1){
       HistsWZPolarization* myhists;
       myhists = new HistsWZPolarization();
       if(process.isRunAllSystematic) myhists->RunAllSystematic();
       if(process.doBkg) myhists->RunBkg();
       if(process.doControlRegion) myhists->RunControlRegion();
       if(process.doFakeRate) myhists->RunFakeRate(process.doFakeRate);
       CondorRunPreWZPolarization(process, myhists);
     }
   }

   if(RootType == "QBH"){
     HistsQBH* myhists;
     myhists = new HistsQBH();
     myhists->openFile(process.SaveName);
     myhists->LinkLog(process.myLog);
     myhists->InputSystematicName(process.SystematicName);
     myhists->bookHists(1);
     CondorRunQBH(process, myhists);
     myhists->saveHists();
     delete myhists;
   }

   if(RootType == "PreQBH"){
     HistsQBH* myhists;
     myhists = new HistsQBH();
     CondorRunPreQBH(process, myhists);
   }

   if(RootType == "HMDY"){
     HistsHMDY* myhists;
     myhists = new HistsHMDY();
     myhists->openFile(process.SaveName);
     myhists->LinkLog(process.myLog);
     myhists->InputSystematicName(process.SystematicName);
     myhists->bookHists(1);
     CondorRunHMDY(process, myhists);
     myhists->GetTransferFactor();
     myhists->saveHists();
     delete myhists;
   }

   if(RootType == "PreHMDY"){
     HistsHMDY* myhists;
     myhists = new HistsHMDY();
     CondorRunPreHMDY(process, myhists);
   }

   if(RootType == "ZPrime"){
     HistsZPrime* myhists;
     myhists = new HistsZPrime();
     myhists->openFile(process.SaveName);
     myhists->LinkLog(process.myLog);
     myhists->InputSystematicName(process.SystematicName);
     myhists->bookHists(1);
     CondorRunZPrime(process, myhists);
     myhists->GetTransferFactor();
     myhists->saveHists();
     delete myhists;
   }

   if(RootType == "PreZPrime"){
     HistsZPrime* myhists;
     myhists = new HistsZPrime();
     CondorRunPreZPrime(process, myhists);
   }

   if(RootType == "Custom"){
     CondorRunCustom(process);
   }

   if(RootType == "CellInfo"){
     CondorRunCellInfo(process);
   }

   if(RootType == "SherpaWW"){
     CondorRunSherpaWW(process);
   }

   if(RootType == "FlavorAsym"){
     CondorRunFlavorAsym(process);
   }

   if(RootType == "ResBosHighMassZ"){
     CondorRunResBosHighMassZ(process);
   }

   if(RootType == "MadGraph"){
     CondorRunMadGraph(process);
   }

   myLog<<LOG_INFO<<"Condor: End Time: "<<getTime()<<endl;
 }

 myLog<<LOG_INFO<<"Master thread is end."<<endl;
 return 0;
}
