#include "Analysis/Common.h"

using namespace std;

Control process;

HistsResBosCMS* myhists;

TH3D* global_AFB;

double Min_Chi2 = 1000000.0;

void OpenDataFile()
{
 TFile* file = new TFile("CMSData.root");

 global_AFB = (TH3D *)file->Get("CMS_AFB_3D");
}

void FittingCMSDataForResBos(Int_t &npbar, Double_t *gin, Double_t &f, Double_t *par, Int_t iflag)
{
     myhists->ResetHists();
     myhists->Reset();

     double Chi2;

     bool OneFilePerJob = process.OneFilePerJob;
     int TotalThread = process.TotalThread;

     pthread_t thread[TotalThread];

     loopResBosCMS *Run[TotalThread];
     TreeForResBosCMS *ResBosCMSTree[TotalThread];

     for(int j = 0; j < TotalThread; j++){
       ResBosCMSTree[j] = new TreeForResBosCMS();
       if(process.isReweight) ResBosCMSTree[j]->Reweight();
       if(process.isFSR) ResBosCMSTree[j]->TurnOnFSR();
       if(process.isDilution) ResBosCMSTree[j]->TurnOnDilution();
       ResBosCMSTree[j]->InputFile(process.RootNames);

       Run[j] = new loopResBosCMS(process.RootType);
       Run[j]->InputHist(myhists);
       Run[j]->InputThreadInfo(TotalThread, j + 1);
       Run[j]->ConfigCut(process.CutFile);
       Run[j]->InputECM(process.ECM);
       Run[j]->InputP0STW(par[1], par[2], par[0]);
       if(process.isTest) Run[j]->Test();
     }

     for(int iround = 0; iround < process.TotalRound; iround++){
       int ifile = 0;

       if(process.TotalRound > 1){
         cout<<"The "<<iround + 1<<" time for submit thread job."<<endl;
         cout<<endl;
       }

       for(int j = 0; j < TotalThread; j++){
         if(!OneFilePerJob) ResBosCMSTree[j]->ConfigFile(process.NFilePerJob, iround);

         if(OneFilePerJob){
           ifile = iround * TotalThread + j;
           if((iround == process.TotalRound - 1) && ifile >= process.TotalFileNumber) continue;
           ResBosCMSTree[j]->ConfigFile(ifile);
         }

         Run[j]->InitialReweight();
         Run[j]->InputTree(ResBosCMSTree[j]);
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
     myhists->outputInformation();

     Chi2 = CalculateChi2(global_AFB, myhists->AFB_Mass_ZY_ZPt, 4, 4, 1, 17);

     f = Chi2;

     if(f < Min_Chi2) Min_Chi2 = f;

     cout<<"Min Chi2 = "<<Min_Chi2<<endl;

}

int main(int argc, char** argv)
{
 if(argc != 2){
   cout<<"usage ./FittingCMSData cardfile"<<endl;
   return 0;
 }

 cout<<"// ----------------------------- //"<<endl;
 cout<<"//       Loop Events Begin       //"<<endl;
 cout<<"// ----------------------------- //"<<endl;

 ofstream outputfile;
 Logstream myLog;
 outputfile.open("save.log");
 myLog.Initial(cout, outputfile);

 myLog<<LOG_INFO<<"// ----------------------------- //"<<endl;
 myLog<<LOG_INFO<<"//       Loop Events Begin       //"<<endl;
 myLog<<LOG_INFO<<"// ----------------------------- //"<<endl;

 process.LinkLog(myLog);

 process.ReadFile(argv[1]);

 OpenDataFile();

 bool isReweight = process.isReweight;
 bool isTest = process.isTest;

 if(process.RunType != "Thread" && process.RunType != "Condor"){
    cout<<"For RunType, Please use \"Thread\" or \"Condor\""<<endl;
    return 0;
 }

 if(process.RootType != "FittingCMSData"){

    cout<<"For RootType, Please use \"FittingCMSData\""<<endl;

    return 0;
 }

 if(process.RunType == "Thread"){
   cout<<"Thread: Start Time: "<<getTime()<<endl;

   process.GetRunningType();

   TString RootType = process.RootType;

   if(RootType == "FittingCMSData"){
     myhists = new HistsResBosCMS(RootType);
     myhists->openFile(process.SaveName);
     myhists->bookHists(process.TotalThread);
     myhists->outputInformation();

     TMinuitHelper *myMinuit = new TMinuitHelper(3);
     myMinuit->SetFCN(FittingCMSDataForResBos);
     myMinuit->Input(0, "stw", 0.23, 0.01, 0.22, 0.24);
     myMinuit->Input(1, "P0u", 0.45, 0.2, 0.0, 0.7);
     myMinuit->Input(2, "P0d", 0.25, 0.2, 0.0, 0.7);
     myMinuit->Exec("SIMPLEX", 100000, 1);//tolerance*0.001
     myMinuit->Exec("MIGRAD", 100000, 0.001);
     double* SPar = new double[3];
     double* SParError = new double[3];
     myMinuit->GetParametersAndError(SPar, SParError);
     cout<<"Fitted Stw: "<<SPar[0]<<" +- "<<SParError[0]<<endl;
     cout<<"Fitted Pu: "<<SPar[1]<<" +- "<<SParError[1]<<endl;
     cout<<"Fitted Pd: "<<SPar[2]<<" +- "<<SParError[2]<<endl;

     myhists->Save();
     myhists->saveHists();
     delete myhists;

   }

   cout<<"Thread: End Time:   "<<getTime()<<endl;
 }

 cout<<"Master thread is end."<<endl;
 return 1;
}
