#ifndef ThreadRunMadGraph_cxx
#define ThreadRunMadGraph_cxx

#include "Analysis/Common.h"

void ThreadRunMadGraph(Control process)
{
     bool OneFilePerJob = process.OneFilePerJob;
     int TotalThread = process.TotalThread;

     pthread_t thread[TotalThread];

     loopMadGraph *Run[TotalThread];
     TreeForMadGraph *MadGraphTree[TotalThread];
     HistsMadGraph* myhists;

     myhists = new HistsMadGraph();
     myhists->openFile(process.SaveName);
     myhists->LinkLog(process.myLog);
     myhists->bookHists(TotalThread);

     for(int j = 0; j < TotalThread; j++){
       MadGraphTree[j] = new TreeForMadGraph();
       MadGraphTree[j]->InputFile(process.RootNames);

       Run[j] = new loopMadGraph(process.RootType);
       if(process.MadGraphReweightID != 0) Run[j]->SetReweightFactor(process.MadGraphReweightID);
       Run[j]->InputHist(myhists);
       Run[j]->InputThreadInfo(TotalThread, j + 1);
       Run[j]->ConfigCut(process.CutFile);
       if(process.newPDFset != -1) Run[j]->InputPDFReweightInfo(process.oldPDFName, process.newPDFName, process.oldPDFset, process.newPDFset);
       if(process.isTest) Run[j]->Test();
     }

     for(int iround = 0; iround < process.TotalRound; iround++){
       int ifile = 0;

       if(process.TotalRound > 1){
         cout<<"The "<<iround + 1<<" time for submit thread job."<<endl;
         cout<<endl;
       }

       for(int j = 0; j < TotalThread; j++){
         if(!OneFilePerJob) MadGraphTree[j]->ConfigFile(process.NFilePerJob, iround);

         if(OneFilePerJob){
           ifile = iround * TotalThread + j;
           if((iround == process.TotalRound - 1) && ifile >= process.TotalFileNumber) continue;
           MadGraphTree[j]->ConfigFile(ifile);
         }

         Run[j]->InputTree(MadGraphTree[j]);
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

void CondorRunMadGraph(Control process)
{
     loopMadGraph *Run;
     TreeForMadGraph *MadGraphTree;
     HistsMadGraph* myhists;

     myhists = new HistsMadGraph();
     myhists->openFile(process.SaveName);
     myhists->LinkLog(process.myLog);
     myhists->bookHists(1);

     MadGraphTree = new TreeForMadGraph();
     MadGraphTree->InputFile(process.RootNames);
     MadGraphTree->ConfigFile(process.NFilePerJob, 0);

     Run = new loopMadGraph(process.RootType);
     if(process.MadGraphReweightID != 0) Run->SetReweightFactor(process.MadGraphReweightID);
     Run->InputHist(myhists);
     Run->InputTree(MadGraphTree);
     Run->ConfigCut(process.CutFile);
     if(process.newPDFset != -1) Run->InputPDFReweightInfo(process.oldPDFName, process.newPDFName, process.oldPDFset, process.newPDFset);
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
