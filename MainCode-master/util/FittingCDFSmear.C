#include "Analysis/Common.h"

using namespace std;

Control process;

HistsResBosWTev* myhists;

double Min_Chi2 = 1000000.0;

void FittingCDFSmearForResBos(Int_t &npbar, Double_t *gin, Double_t &f, Double_t *par, Int_t iflag)
{
     myhists->ResetHists();

     double Chi2;

     bool OneFilePerJob = process.OneFilePerJob;
     int TotalThread = process.TotalThread;

     pthread_t thread[TotalThread];

     loopResBosWTev *Run[TotalThread];
     TreeForResBos *ResBosTree[TotalThread];

     for(int j = 0; j < TotalThread; j++){
       ResBosTree[j] = new TreeForResBos();
       if(process.isReweight) ResBosTree[j]->Reweight();
       if(process.isFSR) ResBosTree[j]->TurnOnFSR();
       if(process.isDilution) ResBosTree[j]->TurnOnDilution();
       ResBosTree[j]->InputFile(process.RootNames);

       Run[j] = new loopResBosWTev(process.RootType);
       Run[j]->InputHist(myhists);
       Run[j]->InputThreadInfo(TotalThread, j + 1);
       Run[j]->ConfigCut(process.CutFile);
       Run[j]->InputECM(process.ECM);
       Run[j]->InputWMass(process.OriginWMass, process.NewWMass, process.WWidth);

       if(process.CalibrationOption == "LepSmear" || process.CalibrationOption == "NuSmear" || process.CalibrationOption == "AllSmear"){
         Run[j]->InputSmearPara(par[0], par[1], par[2], par[3], par[4], par[5]);
       }
       if(process.CalibrationOption == "LepSmearScale" || process.CalibrationOption == "NuSmearScale" || process.CalibrationOption == "AllSmearScale"){
         Run[j]->InputSmearPara(par[0], par[1], par[2], par[3], par[4], par[5], par[6], par[7]);
       }
       if(process.isTest) Run[j]->Test();
     }

     for(int iround = 0; iround < process.TotalRound; iround++){
       int ifile = 0;

       if(process.TotalRound > 1){
         cout<<"The "<<iround + 1<<" time for submit thread job."<<endl;
         cout<<endl;
       }

       for(int j = 0; j < TotalThread; j++){
         if(!OneFilePerJob) ResBosTree[j]->ConfigFile(process.NFilePerJob, iround);

         if(OneFilePerJob){
           ifile = iround * TotalThread + j;
           if((iround == process.TotalRound - 1) && ifile >= process.TotalFileNumber) continue;
           ResBosTree[j]->ConfigFile(ifile);
         }

         Run[j]->InputTree(ResBosTree[j]);
         cout<<"Initialize the rootfile finish"<<endl;
       }

       for(int j = 0; j < TotalThread; j++){
         ifile = iround * TotalThread + j;
         if(OneFilePerJob && (iround == process.TotalRound - 1) && ifile >= process.TotalFileNumber) continue;

         pthread_create(&thread[j], NULL, StartThread, Run[j]);
         cout<<"Thread No."<<j + 1<<" has created."<<endl;
         sleep(1);
       }


       for(int j = 0; j < TotalThread; j++){
         ifile = iround * TotalThread + j;
         if(OneFilePerJob && (iround == process.TotalRound - 1) && ifile >= process.TotalFileNumber) continue;

         pthread_join(thread[j], NULL);
         cout<<"Thread No."<<j + 1<<" has finished."<<endl;
       }
     }

     myhists->MergeHists();

//     double Chi2_MtW = CalculateNormChi2(myhists->MtW_CDF_Electron, myhists->v_MtW_CDF_Smear.at(0), 11, 50);//70~90
//     double Chi2_LeptonPt = CalculateNormChi2(myhists->LeptonPt_CDF_Electron, myhists->v_LeptonPt_CDF_Smear.at(0), 13, 64);//35~48
//     double Chi2_NuPt = CalculateNormChi2(myhists->NuPt_CDF_Electron, myhists->v_NuPt_CDF_Smear.at(0), 13, 64);//35~48

     double Chi2_MtW = CalculateNormChi2(myhists->MtW_CDF_Electron, myhists->MtW_CDF_Smear->at(0), 19, 50);//70~90
     double Chi2_LeptonPt = CalculateNormChi2(myhists->LeptonPt_CDF_Electron, myhists->LeptonPt_CDF_Smear->at(0), 21, 64);//35~48
     double Chi2_NuPt = CalculateNormChi2(myhists->NuPt_CDF_Electron, myhists->NuPt_CDF_Smear->at(0), 21, 64);//35~48

     if(process.CalibrationOption == "LepSmear" || process.CalibrationOption == "LepSmearScale"){
       Chi2 = Chi2_LeptonPt;
     }
     if(process.CalibrationOption == "NuSmear" || process.CalibrationOption == "NuSmearScale"){
       Chi2 = Chi2_NuPt;
     }
     if(process.CalibrationOption == "AllSmear" || process.CalibrationOption == "AllSmearScale"){
       Chi2 = 0.642 * Chi2_MtW + 0.254 * Chi2_LeptonPt + 0.104 * Chi2_NuPt;
     }

     f = Chi2;

     if(f < Min_Chi2) Min_Chi2 = f;

     cout<<"Min Chi2 = "<<Min_Chi2<<endl;

}

int main(int argc, char** argv)
{
 if(argc != 2){
   cout<<"usage ./FittingCDFSmear cardfile"<<endl;
   return 0;
 }

 ofstream outputfile;
 Logstream myLog;
 outputfile.open("save.log");
 myLog.Initial(cout, outputfile);

 myLog<<LOG_INFO<<"// ----------------------------- //"<<endl;
 myLog<<LOG_INFO<<"//       Loop Events Begin       //"<<endl;
 myLog<<LOG_INFO<<"// ----------------------------- //"<<endl;

 process.LinkLog(myLog);

 process.ReadFile(argv[1]);

 bool isReweight = process.isReweight;
 bool isTest = process.isTest;

 if(process.RunType != "Thread" && process.RunType != "Condor"){
    myLog<<LOG_INFO<<"For RunType, Please use \"Thread\" or \"Condor\""<<endl;
    return 0;
 }

 if(process.RootType != "FittingCDFSmear"){

    myLog<<LOG_INFO<<"For RootType, Please use \"FittingCDFSmear\""<<endl;

    return 0;
 }

 if(process.RunType == "Thread"){
   myLog<<LOG_INFO<<"Thread: Start Time: "<<getTime()<<endl;

   process.GetRunningType();

   TString RootType = process.RootType;

   if(RootType == "FittingCDFSmear"){
     myhists = new HistsResBosWTev(RootType);
     myhists->openFile(process.SaveName);
     myhists->bookHists(process.TotalThread);
     if(process.DataList.size() != 0) myhists->InputData(process.DataList);
     myhists->InitialCDFData();

     TMinuitHelper *myMinuit = new TMinuitHelper(8);
     myMinuit->SetFCN(FittingCDFSmearForResBos);

     if(process.CalibrationOption == "LepSmear" || process.CalibrationOption == "LepSmearScale"){
       myMinuit->Input(0, "LepPara1", 0.050088, 0.2, 0.0, 0.5);
       myMinuit->Input(1, "LepPara2", 0.1219, 0.2, 0.0, 0.5);
       myMinuit->Input(2, "LepPara3", 0.0300769, 0.2, 0.0, 0.5);
       myMinuit->Input(3, "NuPara1", 0.0873444, 0.0, 0.0, 0.5);
       myMinuit->Input(4, "NuPara2", 0.000239253, 0.0, 0.0, 0.5);
       myMinuit->Input(5, "NuPara3", 0.00193609, 0.0, 0.0, 0.5);
     }
     if(process.CalibrationOption == "NuSmear" || process.CalibrationOption == "NuSmearScale"){
       myMinuit->Input(0, "LepPara1", 0.050088, 0.0, 0.0, 0.5);
       myMinuit->Input(1, "LepPara2", 0.1219, 0.0, 0.0, 0.5);
       myMinuit->Input(2, "LepPara3", 0.0300769, 0.0, 0.0, 0.5);
       myMinuit->Input(3, "NuPara1", 0.0873444, 0.2, 0.0, 0.5);
       myMinuit->Input(4, "NuPara2", 0.000239253, 0.2, 0.0, 0.5);
       myMinuit->Input(5, "NuPara3", 0.00193609, 0.2, 0.0, 0.5);
     }
     if(process.CalibrationOption == "AllSmear" || process.CalibrationOption == "AllSmearScale"){
       myMinuit->Input(0, "LepPara1", 0.050088, 0.2, 0.0, 0.5);
       myMinuit->Input(1, "LepPara2", 0.1219, 0.2, 0.0, 0.5);
       myMinuit->Input(2, "LepPara3", 0.0300769, 0.2, 0.0, 0.5);
       myMinuit->Input(3, "NuPara1", 0.0873444, 0.2, 0.0, 0.5);
       myMinuit->Input(4, "NuPara2", 0.000239253, 0.2, 0.0, 0.5);
       myMinuit->Input(5, "NuPara3", 0.00193609, 0.2, 0.0, 0.5);
     }
     if(process.CalibrationOption == "LepSmear" || process.CalibrationOption == "NuSmear" || process.CalibrationOption == "AllSmear"){
       myMinuit->Input(6, "LepScale", 1.0, 0.0, 0.9, 1.1);
       myMinuit->Input(7, "NuScale", 1.0, 0.0, 0.9, 1.1);
     }
     if(process.CalibrationOption == "LepSmearScale"){
       myMinuit->Input(6, "LepScale", 1.00072, 0.1, 0.9, 1.1);
       myMinuit->Input(7, "NuScale", 1.0, 0.0, 0.9, 1.1);
     }
     if(process.CalibrationOption == "NuSmearScale"){ 
       myMinuit->Input(6, "LepScale", 1.00072, 0.0, 0.9, 1.1);
       myMinuit->Input(7, "NuScale", 1.0, 0.1, 0.9, 1.1);
     }
     if(process.CalibrationOption == "AllSmearScale"){ 
       myMinuit->Input(6, "LepScale", 1.00072, 0.1, 0.9, 1.1);
       myMinuit->Input(7, "NuScale", 1.0, 0.1, 0.9, 1.1);
     }
     myMinuit->Exec("SIMPLEX", 100000, 1);//tolerance*0.001
     myMinuit->Exec("MIGRAD", 100000, 0.001);
     double* SPar = new double[8];
     double* SParError = new double[8];
     myMinuit->GetParametersAndError(SPar, SParError);
     myLog<<LOG_INFO<<"LepPara1: "<<SPar[0]<<" +- "<<SParError[0]<<endl;
     myLog<<LOG_INFO<<"LepPara2: "<<SPar[1]<<" +- "<<SParError[1]<<endl;
     myLog<<LOG_INFO<<"LepPara3: "<<SPar[2]<<" +- "<<SParError[2]<<endl;
     myLog<<LOG_INFO<<"NuPara1: "<<SPar[3]<<" +- "<<SParError[3]<<endl;
     myLog<<LOG_INFO<<"NuPara2: "<<SPar[4]<<" +- "<<SParError[4]<<endl;
     myLog<<LOG_INFO<<"NuPara3: "<<SPar[5]<<" +- "<<SParError[5]<<endl;
     myLog<<LOG_INFO<<"LepScale: "<<SPar[6]<<" +- "<<SParError[6]<<endl;
     myLog<<LOG_INFO<<"NuScale: "<<SPar[7]<<" +- "<<SParError[7]<<endl;

     myhists->saveHists();
     delete myhists;

   }

   myLog<<LOG_INFO<<"Thread: End Time:   "<<getTime()<<endl;
 }

 myLog<<LOG_INFO<<"Master thread is end."<<endl;
 return 1;
}

