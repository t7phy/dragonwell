#ifndef ThreadRunResBosHighMassZ_cxx
#define ThreadRunResBosHighMassZ_cxx

#include "Analysis/Common.h"

void ThreadRunResBosHighMassZ(Control process)
{
     bool OneFilePerJob = process.OneFilePerJob;
     int TotalThread = process.TotalThread;

     pthread_t thread[TotalThread];

     loopResBosHighMassZ *Run[TotalThread];
     TreeForResBosHighMassZ *ResBosHighMassZTree[TotalThread];
     HistsResBosHighMassZ* myhists;

     myhists = new HistsResBosHighMassZ();
     myhists->openFile(process.SaveName);
     myhists->LinkLog(process.myLog);
     myhists->bookHists(TotalThread);

     for(int j = 0; j < TotalThread; j++){
       ResBosHighMassZTree[j] = new TreeForResBosHighMassZ();
       if(process.isReweight) ResBosHighMassZTree[j]->Reweight();
       if(process.isDilution) ResBosHighMassZTree[j]->TurnOnDilution();
       ResBosHighMassZTree[j]->InputFile(process.RootNames);

       Run[j] = new loopResBosHighMassZ(process.RootType);
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
         if(!OneFilePerJob) ResBosHighMassZTree[j]->ConfigFile(process.NFilePerJob, iround);

         if(OneFilePerJob){
           ifile = iround * TotalThread + j;
           if((iround == process.TotalRound - 1) && ifile >= process.TotalFileNumber) continue;
           ResBosHighMassZTree[j]->ConfigFile(ifile);
         }

         Run[j]->InputTree(ResBosHighMassZTree[j]);
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

void CondorRunResBosHighMassZ(Control process)
{
     loopResBosHighMassZ *Run;
     TreeForResBosHighMassZ *ResBosHighMassZTree;
     HistsResBosHighMassZ* myhists;

     myhists = new HistsResBosHighMassZ();
     myhists->openFile(process.SaveName);
     myhists->LinkLog(process.myLog);
     myhists->bookHists(1);

     ResBosHighMassZTree = new TreeForResBosHighMassZ();
     if(process.isReweight) ResBosHighMassZTree->Reweight();
     if(process.isDilution) ResBosHighMassZTree->TurnOnDilution();
     ResBosHighMassZTree->InputFile(process.RootNames);
     ResBosHighMassZTree->ConfigFile(process.NFilePerJob, 0);

     Run = new loopResBosHighMassZ(process.RootType);
     Run->InputHist(myhists);
     Run->InputTree(ResBosHighMassZTree);
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
