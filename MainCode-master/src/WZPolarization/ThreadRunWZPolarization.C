#ifndef ThreadRunWZPolarization_cxx
#define ThreadRunWZPolarization_cxx

#include "Analysis/Common.h"

void ThreadRunWZPolarization(Control process, HistsWZPolarization* myhists)
{
     bool OneFilePerJob = process.OneFilePerJob;
     int TotalThread = process.TotalThread;

     pthread_t thread[TotalThread];

     loopWZPolarization *Run[TotalThread];
     TreeForWZPolarization *WZPolarizationTree[TotalThread];

     for(int j = 0; j < TotalThread; j++){
       WZPolarizationTree[j] = new TreeForWZPolarization();
       WZPolarizationTree[j]->InputFile(process.RootNames);
       WZPolarizationTree[j]->LinkHist(myhists);
       if(process.ErrorType != "") WZPolarizationTree[j]->RunPDFAndQCDUnc(process.ErrorType, process.ErrorSet);

       Run[j] = new loopWZPolarization(process.RootType);
       if(process.isRunAllSystematic) Run[j]->RunAllSystematic();
       Run[j]->InputHist(myhists);
       Run[j]->InputThreadInfo(TotalThread, j + 1);
       Run[j]->ConfigCut(process.CutFile);
       if(process.doFakeRate) Run[j]->GetFullFakeMatrix();
       if(process.PreRunReweightingFactor) Run[j]->PreRunReweightingFactor();
       if(process.isTest) Run[j]->Test();
       Run[j]->LinkLog(process.myLog);
     }

     for(int iround = 0; iround < process.TotalRound; iround++){
       int ifile = 0;

       if(process.TotalRound > 1){
         cout<<"The "<<iround + 1<<" time for submit thread job."<<endl;
         cout<<endl;
       }

       for(int j = 0; j < TotalThread; j++){
         if(!OneFilePerJob) WZPolarizationTree[j]->ConfigFile(process.NFilePerJob, iround);

         if(OneFilePerJob){
           ifile = iround * TotalThread + j;
           if((iround == process.TotalRound - 1) && ifile >= process.TotalFileNumber) continue;
           WZPolarizationTree[j]->ConfigFile(ifile);
         }

         Run[j]->InputTree(WZPolarizationTree[j]);
         if(process.isBDT) Run[j]->InitialTMVA(process.BDTFile);
         if(process.isBDTSR){
           if(process.isOnlyDecSR)
             Run[j]->InitialTMVASR_OnlyDec(process.BDTFileSR);
           else if(process.isNoPtVSR)
             Run[j]->InitialTMVASR_NoPtV(process.BDTFileSR);
           else
             Run[j]->InitialTMVASR(process.BDTFileSR);
         }
         if(process.isBDTSR100){
           if(process.isOnlyDecSR100)
             Run[j]->InitialTMVASR100_OnlyDec(process.BDTFileSR100);
           else if(process.isNoPtVSR100)
             Run[j]->InitialTMVASR100_NoPtV(process.BDTFileSR100);
           else
             Run[j]->InitialTMVASR100(process.BDTFileSR100);
         }
         cout<<"Thread No."<<j + 1<<": Initialize the rootfile finish"<<endl;
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

}

void ThreadRunPreWZPolarization(Control process, HistsWZPolarization* myhists)
{
     bool OneFilePerJob = process.OneFilePerJob;
     int TotalThread = process.TotalThread;

     pthread_t thread[TotalThread];

     loopWZPolarization *Run[TotalThread];
     TreeForPreWZPolarization *WZPolarizationTree[TotalThread];

     SumOfWeightHelper *mySumOfWeight = new SumOfWeightHelper(process.SumOfWeightList);
     mySumOfWeight->GetSumOfWeight();
     cout<<"Get Sum of Weight finished."<<endl;

     for(int j = 0; j < TotalThread; j++){
       WZPolarizationTree[j] = new TreeForPreWZPolarization();
       WZPolarizationTree[j]->InputFile(process.RootNames);
       WZPolarizationTree[j]->InputSumOfWeight(mySumOfWeight->SumOfWeightsMap);
       WZPolarizationTree[j]->InputLuminosity(mySumOfWeight->Lumi1516, mySumOfWeight->Lumi17, mySumOfWeight->Lumi18);
       if(process.doPDFAndQCDUnc) WZPolarizationTree[j]->SavePDFAndQCDUnc();
       if(!process.NtupleName.Contains("root")) WZPolarizationTree[j]->BkgSelection(process.NtupleName);
       WZPolarizationTree[j]->YearSelection(process.Year);
       if(process.doTruthSelection) WZPolarizationTree[j]->DoTruthSelection();

       Run[j] = new loopWZPolarization(process.RootType);
       Run[j]->ProcessOption(process.ProcessOption);
       if(process.isRunAllSystematic) Run[j]->RunAllSystematic();
       Run[j]->InputNtupleName(process.NtupleName);
       Run[j]->InputHist(myhists);
       Run[j]->InputThreadInfo(TotalThread, j + 1);
       Run[j]->ConfigCut(process.CutFile);
       if(process.doFakeRate) Run[j]->GetFullFakeMatrix();
       if(process.PreRunReweightingFactor) Run[j]->PreRunReweightingFactor();
       if(process.isLWTNNNuPz) Run[j]->InitialLWTNNNuPz(process.NuPzEven, process.NuPzOdd);
       if(process.isLWTNNPolClassifier) Run[j]->InitialLWTNNPolClassifier(process.PolClassifierEven, process.PolClassifierOdd);
       if(process.isLWTNNNLOPol) Run[j]->InitialLWTNNNLOPol(process.DNNLLFile, process.DNNLTFile, process.DNNTLFile, process.DNNTTFile);
       if(process.isTest) Run[j]->Test();
       Run[j]->LinkLog(process.myLog);
     }

     if(process.TotalFileNumber != (WZPolarizationTree[0]->RootNames).size()){
       process.TotalFileNumber = (WZPolarizationTree[0]->RootNames).size();
       process.GetRunningType(1);
     }

     for(int iround = 0; iround < process.TotalRound; iround++){
       int ifile = 0;

       if(process.TotalRound > 1){
         cout<<"The "<<iround + 1<<" time for submit thread job."<<endl;
         cout<<endl;
       }

       for(int j = 0; j < TotalThread; j++){
         if(!process.OneFilePerJob) WZPolarizationTree[j]->ConfigFile(process.NFilePerJob, iround);

         if(process.OneFilePerJob){
           ifile = iround * TotalThread + j;
           if((iround == process.TotalRound - 1) && ifile >= process.TotalFileNumber) continue;
           WZPolarizationTree[j]->ConfigFile(ifile);
         }

         //finish the initialization, the tree can be input to LoopMicro now;
         Run[j]->InputTree(WZPolarizationTree[j]);
         cout<<"Thread No."<<j + 1<<": Initialize the rootfile finish"<<endl;
       }

       Run[0]->OutputFileInfo();

       for(int j = 0; j < TotalThread; j++){
         ifile = iround * TotalThread + j;
         if(process.OneFilePerJob && (iround == process.TotalRound - 1) && ifile >= process.TotalFileNumber) continue;

         pthread_create(&thread[j], NULL, StartThread, Run[j]);
         cout<<"Thread No."<<j + 1<<" has created."<<endl;
         sleep(1);
       }

       for(int j = 0; j < TotalThread; j++){
         ifile = iround * TotalThread + j;
         if(process.OneFilePerJob && (iround == process.TotalRound - 1) && ifile >= process.TotalFileNumber) continue;

         pthread_join(thread[j], NULL);
         cout<<"Thread No."<<j + 1<<" has finished."<<endl;
       }

     }

}

void CondorRunWZPolarization(Control process, HistsWZPolarization* myhists)
{
     loopWZPolarization *Run;
     TreeForWZPolarization *WZPolarizationTree;

     WZPolarizationTree = new TreeForWZPolarization();
     WZPolarizationTree->InputFile(process.RootNames);
     WZPolarizationTree->LinkHist(myhists);
     if(process.ErrorType != "") WZPolarizationTree->RunPDFAndQCDUnc(process.ErrorType, process.ErrorSet);

     WZPolarizationTree->ConfigFile(process.NFilePerJob, 0);

     Run = new loopWZPolarization(process.RootType);
     if(process.isRunAllSystematic) Run->RunAllSystematic();
     Run->InputHist(myhists);
     Run->InputTree(WZPolarizationTree);
     Run->ConfigCut(process.CutFile);
     Run->iThread = 1;
     if(process.doFakeRate) Run->GetFullFakeMatrix();
     if(process.PreRunReweightingFactor) Run->PreRunReweightingFactor();
     if(process.isBDT) Run->InitialTMVA(process.BDTFile);
     if(process.isBDTSR){
       if(process.isOnlyDecSR)
         Run->InitialTMVASR_OnlyDec(process.BDTFileSR);
       else if(process.isNoPtVSR)
         Run->InitialTMVASR_NoPtV(process.BDTFileSR);
       else
         Run->InitialTMVASR(process.BDTFileSR);
     }
     if(process.isBDTSR100){
       if(process.isOnlyDecSR100)
         Run->InitialTMVASR100_OnlyDec(process.BDTFileSR100);
       else if(process.isNoPtVSR100)
         Run->InitialTMVASR100_NoPtV(process.BDTFileSR100);
       else
         Run->InitialTMVASR100(process.BDTFileSR100);
     }
     if(process.isTest) Run->Test();
     Run->LinkLog(process.myLog);
     cout<<"Initialize the rootfile finish"<<endl;

     for(int ifile = 0; ifile < Run->RootNames.size(); ifile++){
       Run->InitialSys(ifile);
       Run->ReadTree(ifile);
       Run->End(ifile);
     }
     Run->Finish();

}

void CondorRunPreWZPolarization(Control process, HistsWZPolarization* myhists)
{
     loopWZPolarization *Run;
     TreeForPreWZPolarization *WZPolarizationTree;

     SumOfWeightHelper *mySumOfWeight = new SumOfWeightHelper(process.SumOfWeightList);
     mySumOfWeight->GetSumOfWeight();
     cout<<"Get Sum of Weight finished."<<endl;

     WZPolarizationTree = new TreeForPreWZPolarization();
     WZPolarizationTree->InputFile(process.RootNames);
     WZPolarizationTree->InputSumOfWeight(mySumOfWeight->SumOfWeightsMap);
     WZPolarizationTree->InputLuminosity(mySumOfWeight->Lumi1516, mySumOfWeight->Lumi17, mySumOfWeight->Lumi18);
     if(process.doPDFAndQCDUnc) WZPolarizationTree->SavePDFAndQCDUnc();
     if(!process.NtupleName.Contains("root")) WZPolarizationTree->BkgSelection(process.NtupleName);
     WZPolarizationTree->YearSelection(process.Year);
     if(process.doTruthSelection) WZPolarizationTree->DoTruthSelection();
     WZPolarizationTree->ConfigFile(process.NFilePerJob, 0);

     Run = new loopWZPolarization(process.RootType);
     Run->ProcessOption(process.ProcessOption);
     if(process.isRunAllSystematic) Run->RunAllSystematic();
     Run->InputNtupleName(process.NtupleName);
     Run->InputHist(myhists);
     Run->InputTree(WZPolarizationTree);
     Run->ConfigCut(process.CutFile);
     Run->iThread = 1;
     if(process.doFakeRate) Run->GetFullFakeMatrix();
     if(process.PreRunReweightingFactor) Run->PreRunReweightingFactor();
     if(process.isLWTNNNuPz) Run->InitialLWTNNNuPz(process.NuPzEven, process.NuPzOdd);
     if(process.isLWTNNPolClassifier) Run->InitialLWTNNPolClassifier(process.PolClassifierEven, process.PolClassifierOdd);
     if(process.isLWTNNNLOPol) Run->InitialLWTNNNLOPol(process.DNNLLFile, process.DNNLTFile, process.DNNTLFile, process.DNNTTFile);
     if(process.isTest) Run->Test();
     Run->LinkLog(process.myLog);
     cout<<"Initialize the rootfile finish"<<endl;

     Run->OutputFileInfo();

     for(int ifile = 0; ifile < Run->RootNames.size(); ifile++){
       Run->Initial(ifile);
       Run->PreLoop(ifile);
       Run->End(ifile);
     }
     Run->Finish();

}

#endif
