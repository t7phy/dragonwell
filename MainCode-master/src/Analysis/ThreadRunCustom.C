#ifndef ThreadRunCustom_cxx
#define ThreadRunCustom_cxx

#include "Analysis/Common.h"

void ThreadRunCustom(Control process)
{
     bool OneFilePerJob = process.OneFilePerJob;
     int TotalThread = process.TotalThread;

     pthread_t thread[TotalThread];

     loopCustom *Run[TotalThread];
     TreeForCustom *CustomTree[TotalThread];
     HistsCustom* myhists;

     myhists = new HistsCustom();
     myhists->openFile(process.SaveName);
     myhists->LinkLog(process.myLog);
     myhists->bookHists(TotalThread);

     for(int j = 0; j < TotalThread; j++){
       CustomTree[j] = new TreeForCustom();
       CustomTree[j]->InputFile(process.RootNames);

       Run[j] = new loopCustom(process.RootType);
       Run[j]->InputHist(myhists);
       Run[j]->InputThreadInfo(TotalThread, j + 1);
       Run[j]->ConfigCut(process.CutFile);
       if(process.isTest) Run[j]->Test();
     }

     for(int iround = 0; iround < process.TotalRound; iround++){
       int ifile = 0;

       if(process.TotalRound > 1){
         cout<<"The "<<iround + 1<<" time for submit thread job."<<endl;
         cout<<endl;
       }

       for(int j = 0; j < TotalThread; j++){
         if(!OneFilePerJob) CustomTree[j]->ConfigFile(process.NFilePerJob, iround);

         if(OneFilePerJob){
           ifile = iround * TotalThread + j;
           if((iround == process.TotalRound - 1) && ifile >= process.TotalFileNumber) continue;
           CustomTree[j]->ConfigFile(ifile);
         }

         Run[j]->InputTree(CustomTree[j]);
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

void CondorRunCustom(Control process)
{
     loopCustom *Run;
     TreeForCustom *CustomTree;
     HistsCustom* myhists;

     myhists = new HistsCustom();
     myhists->openFile(process.SaveName);
     myhists->LinkLog(process.myLog);
     myhists->bookHists(1);

     CustomTree = new TreeForCustom();
     CustomTree->InputFile(process.RootNames);
     CustomTree->ConfigFile(process.NFilePerJob, 0);

     Run = new loopCustom(process.RootType);
     Run->InputHist(myhists);
     Run->InputTree(CustomTree);
     Run->ConfigCut(process.CutFile);
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
