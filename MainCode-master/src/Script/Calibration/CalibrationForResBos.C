#ifndef CalibrationForResBos_cxx
#define CalibrationForResBos_cxx

#include "Analysis/Common.h"
#include "Calibration/Calibration.h"

Control process;

HistsResBos* myhists;

void RunResBosCalibration(Control run, HistsResBos* hists)
{
 process = run;

 myhists = hists;

}

void CalibrationForResBos(Int_t &npbar, Double_t *gin, Double_t &f, Double_t *par, Int_t iflag)
{
     myhists->ResetHists();

     double Chi2;

     bool OneFilePerJob = process.OneFilePerJob;
     int TotalThread = process.TotalThread;

     pthread_t thread[TotalThread];

     loopResBos *Run[TotalThread];
     TreeForResBos *ResBosTree[TotalThread];

     for(int j = 0; j < TotalThread; j++){
       ResBosTree[j] = new TreeForResBos();
       if(process.isReweight) ResBosTree[j]->Reweight();
       if(process.isFSR) ResBosTree[j]->TurnOnFSR();
       ResBosTree[j]->InputFile(process.RootNames);

       Run[j] = new loopResBos(process.RootType);
       Run[j]->InputHist(myhists);
       Run[j]->InputThreadInfo(TotalThread, j + 1);
       Run[j]->ConfigCut(process.CutFile);
       Run[j]->InputECM(process.ECM);
       Run[j]->InputScaleAndSmear(par[0], par[1]);
       if(process.isTest) Run[j]->Test();
cout<<"par 0: "<<par[0]<<" par 1: "<<par[1]<<endl;
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

     Chi2 = CalculateChi2(myhists->ZMass->at(0), myhists->DataHist);
     f = Chi2;

     if(f < Min_Chi2) Min_Chi2 = f;

     cout<<"Min Chi2 = "<<Min_Chi2<<endl;

}

#endif
