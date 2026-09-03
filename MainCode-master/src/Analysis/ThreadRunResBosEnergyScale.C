#ifndef ThreadRunResBosEnergyScale_cxx
#define ThreadRunResBosEnergyScale_cxx

#include "Analysis/Common.h"

void ThreadRunResBosEnergyScale(Control process)
{
     bool OneFilePerJob = process.OneFilePerJob;
     int TotalThread = process.TotalThread;

     pthread_t thread[TotalThread];

     loopResBos *Run[TotalThread];
     TreeForResBos *ResBosTree[TotalThread];
     HistsResBos* myhists;
     myhists = new HistsResBos();
     myhists->openFile(process.SaveName);
     myhists->LinkLog(process.myLog);
     myhists->bookHists(TotalThread);
     myhists->bookCovHists(TotalThread);

     vector<double> RandomList;
     GenGausRandomList(1.001, 0.001, RandomList, 1000);

     for(int j = 0; j < TotalThread; j++){
       ResBosTree[j] = new TreeForResBos();
       if(process.isReweight) ResBosTree[j]->Reweight();
       if(process.isFSR) ResBosTree[j]->TurnOnFSR();
       ResBosTree[j]->InputFile(process.RootNames);

       Run[j] = new loopResBos(process.RootType);
       Run[j]->InputHist(myhists);
       Run[j]->InputThreadInfo(TotalThread, j + 1);
       Run[j]->ConfigCut(process.CutFile);
       Run[j]->ConfigEnergyScale(RandomList);
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

void CondorRunResBosEnergyScale(Control process)
{
     loopResBos *Run;
     TreeForResBos *ResBosTree;
     HistsResBos* myhists;

     myhists = new HistsResBos();
     myhists->openFile(process.SaveName);
     myhists->LinkLog(process.myLog);
     myhists->bookHists(1);
     myhists->bookCovHists(1);

     vector<double> RandomList;
     GenGausRandomList(1.001, 0.001, RandomList, 1000);

     ResBosTree = new TreeForResBos();
     if(process.isReweight) ResBosTree->Reweight();
     if(process.isFSR) ResBosTree->TurnOnFSR();
     ResBosTree->InputFile(process.RootNames);
     ResBosTree->ConfigFile(process.NFilePerJob, 0);

     Run = new loopResBos(process.RootType);
     Run->InputHist(myhists);
     Run->InputTree(ResBosTree);
     Run->ConfigCut(process.CutFile);
     Run->ConfigEnergyScale(RandomList);
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
