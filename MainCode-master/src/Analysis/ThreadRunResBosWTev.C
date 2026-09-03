#ifndef ThreadRunResBosWTev_cxx
#define ThreadRunResBosWTev_cxx

#include "Analysis/Common.h"

void ThreadRunResBosWTev(Control process)
{
     bool OneFilePerJob = process.OneFilePerJob;
     int TotalThread = process.TotalThread;

     pthread_t thread[TotalThread];

     loopResBosWTev *Run[TotalThread];
     TreeForResBos *ResBosTree[TotalThread];
     HistsResBosWTev* myhists;
     myhists = new HistsResBosWTev(process.RootType);
     if(process.LeptonPtMin > 0.0) myhists->InputJacoAsymInput(process.LeptonPtMin, process.LeptonPtMiddle, process.LeptonPtMax);
     myhists->openFile(process.SaveName);
     myhists->LinkLog(process.myLog);
     myhists->bookHists(TotalThread);
     if(process.DataList.size() != 0) myhists->InputData(process.DataList);

     for(int j = 0; j < TotalThread; j++){
       ResBosTree[j] = new TreeForResBos();
       if(process.isReweight) ResBosTree[j]->Reweight();
       if(process.isFSR) ResBosTree[j]->TurnOnFSR();
       ResBosTree[j]->InputFile(process.RootNames);

       Run[j] = new loopResBosWTev(process.RootType);
       Run[j]->InputHist(myhists);
       Run[j]->InputThreadInfo(TotalThread, j + 1);
       Run[j]->ConfigCut(process.CutFile);
       Run[j]->InputECM(process.ECM);
       Run[j]->InputWMass(process.OriginWMass, process.NewWMass, process.WWidth);
       Run[j]->InputScaleSlope(process.ScaleSlope);
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
     myhists->saveHists();
     delete myhists;

}

void CondorRunResBosWTev(Control process)
{
     loopResBosWTev *Run;
     TreeForResBos *ResBosTree;
     HistsResBosWTev* myhists;

     myhists = new HistsResBosWTev(process.RootType);
     if(process.LeptonPtMin > 0.0) myhists->InputJacoAsymInput(process.LeptonPtMin, process.LeptonPtMiddle, process.LeptonPtMax);
     myhists->openFile(process.SaveName);
     myhists->LinkLog(process.myLog);
     myhists->bookHists(1);
     if(process.DataList.size() != 0) myhists->InputData(process.DataList);

     ResBosTree = new TreeForResBos();
     if(process.isReweight) ResBosTree->Reweight();
     if(process.isFSR) ResBosTree->TurnOnFSR();
     ResBosTree->InputFile(process.RootNames);
     ResBosTree->ConfigFile(process.NFilePerJob, 0);

     Run = new loopResBosWTev(process.RootType);
     Run->InputHist(myhists);
     Run->InputTree(ResBosTree);
     Run->ConfigCut(process.CutFile);
     Run->InputECM(process.ECM);
     Run->InputWMass(process.OriginWMass, process.NewWMass, process.WWidth);
     Run->InputScaleSlope(process.ScaleSlope);
     if(process.isTest) Run->Test();
     cout<<"Initialize the rootfile finish"<<endl;

     for(int ifile = 0; ifile < Run->RootNames.size(); ifile++){
       Run->Initial(ifile); 
       Run->ReadTree(ifile);
       Run->End(ifile);
     }
     Run->Finish();
     myhists->saveHists();
     delete myhists;

}
#endif
