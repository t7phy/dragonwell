#include "Calculation/PDFChi2.h"
#include "Calculation/ThreadChi2.h"

PDFChi2::PDFChi2()
{
 ROOT::EnableThreadSafety();
 TDirectory::AddDirectory(kFALSE);
 TH1::AddDirectory(kFALSE);
}

void PDFChi2::Initialize(vector<Dataset *> AllData, Config setting)
{
 if(isInitial) return;

 this->setting = setting;

 PDFType = setting.PDFType;

 cout<<getTime()<<" Starting Initialization:"<<endl;

 this->AllData = AllData;
 this->AllChi2.resize(AllData.size());
 this->AllBestFitChi2.resize(AllData.size());
 this->AllNPoints.resize(AllData.size());
 for(int i = 0; i < AllData.size(); i++){
   IDtoIndex[AllData.at(i)->m_data[0].ID] = i;
   NametoIndex[AllData.at(i)->m_name] = i;

   AllNPoints.at(i) = AllData.at(i)->NPoints;
 }

 // n Data -> TotalThread Data
 TotalThread = 40;
// nDISThread = 55;
// nVBPThread = 15;
// nDISThread = 7;
// nVBPThread = 7;

 // Reorganize DIS data
 for(int idata = 0; idata < AllData.size(); idata++){
   if(AllData.at(idata)->DataType == "DIS"){
     for(int ipoint = 0; ipoint < AllData.at(idata)->NPoints; ipoint++){
       DISDataVector.push_back(AllData.at(idata)->GetDataPoint(ipoint));
     }
   }
 }

 if(nDISThread > DISDataVector.size() && DISDataVector.size() != 0) nDISThread = DISDataVector.size();

 nDISPointsPerThread = DISDataVector.size() / nDISThread;

 int iThread = 0;
 for(int ipoint = 0; ipoint < DISDataVector.size(); ipoint++){
   if(ipoint % nDISPointsPerThread == 0 && iThread != nDISThread) iThread++;
   ThreadDataDIS[iThread].push_back(DISDataVector.at(ipoint));
 }

 // Reorganize VBP data
 for(int idata = 0; idata < AllData.size(); idata++){
   if(AllData.at(idata)->DataType == "DrellYan" && AllData.at(idata)->CalcMode == "CTEQ_DY"){
     for(int ipoint = 0; ipoint < AllData.at(idata)->NPoints; ipoint++){
       VBPDataVector.push_back(AllData.at(idata)->GetDataPoint(ipoint));
     }
   }
 }

 if(nVBPThread > VBPDataVector.size() && VBPDataVector.size() != 0) nVBPThread = VBPDataVector.size();

 nVBPPointsPerThread = VBPDataVector.size() / nVBPThread;

 iThread = 0;
 for(int ipoint = 0; ipoint < VBPDataVector.size(); ipoint++){
   if(ipoint % nVBPPointsPerThread == 0 && iThread != nVBPThread) iThread++;
   ThreadDataVBP[iThread].push_back(VBPDataVector.at(ipoint));
 }

 // Initialize ApplGrid Jobs
 for(int idata = 0; idata < AllData.size(); idata++){
   if(AllData.at(idata)->CalcMode != "ApplGrid") continue;
   AllData.at(idata)->InitialPrediction(setting);
 }

 // Initialize FastNLO Jobs
 for(int idata = 0; idata < AllData.size(); idata++){
   if(AllData.at(idata)->CalcMode != "FastNLO") continue;
   AllData.at(idata)->InitialPrediction(setting);
 }

 // Initialize PineAPPL Jobs
 for(int idata = 0; idata < AllData.size(); idata++){
   if(AllData.at(idata)->CalcMode != "PineAPPL") continue;
   AllData.at(idata)->InitialPrediction(setting);
 }

 // Initialize DIS Thread Jobs
 for(int i = 1; i <= nDISThread; i++){
   ThreadRunDIS[i] = new Dataset();
   ThreadRunDIS[i]->SetDataTable(ThreadDataDIS[i]);
   ThreadRunDIS[i]->InitialPrediction(setting);
 }

 // Initialize VBP Thread Jobs
 for(int i = 1; i <= nVBPThread; i++){
   ThreadRunVBP[i] = new Dataset();
   ThreadRunVBP[i]->SetDataTable(ThreadDataVBP[i]);
   ThreadRunVBP[i]->InitialPrediction(setting);
 }

 isInitial = true;

 cout<<getTime()<<" Initialize Data finish"<<endl;
}

void PDFChi2::InitialPDF(Config setting)
{
 this->setting = setting;

 // Change PDF for ApplGrid Jobs
 for(int idata = 0; idata < AllData.size(); idata++){
   if(AllData.at(idata)->CalcMode != "ApplGrid") continue;
   AllData.at(idata)->InitialPDF(setting);
 }

 // Change PDF for FastNLO Jobs
 for(int idata = 0; idata < AllData.size(); idata++){
   if(AllData.at(idata)->CalcMode != "FastNLO") continue;
   AllData.at(idata)->InitialPDF(setting);
 }

 // Change PDF for PineAPPL Jobs
 for(int idata = 0; idata < AllData.size(); idata++){
   if(AllData.at(idata)->CalcMode != "PineAPPL") continue;
   AllData.at(idata)->InitialPDF(setting);
 }

 // Change PDF for DIS Thread Jobs
 for(int i = 1; i <= nDISThread; i++){
   ThreadRunDIS[i]->InitialPDF(setting);
 }

 // Change PDF for VBP Thread Jobs
 for(int i = 1; i <= nVBPThread; i++){
   ThreadRunVBP[i]->InitialPDF(setting);
 }
}

double PDFChi2::GetChi2(bool print, bool isBestFit)
{
 double Result = 0.0;
 BestFitChi2 = 0.0;
 FitChi2NoPenalty = 0.0;

 if(print){
   for(int idata = 0; idata < AllData.size(); idata++){
     AllData.at(idata)->SetPrint();
   }
 }

 //cout<<getTime()<<" ApplGrid submit"<<endl;
 // Submit ApplGrid Jobs
 if(PDFType == "LHAPDF"){
   for(int idata = 0; idata < AllData.size(); idata++){
     if(AllData.at(idata)->CalcMode != "ApplGrid") continue;
     pthread_create(&threadAPPL[idata], NULL, ThreadChi2, AllData[idata]);
     //cout<<"Thread No."<<idata<<" has created."<<endl;
   }
 }
 else if(PDFType == "CTEQ"){
   for(int idata = 0; idata < AllData.size(); idata++){
     if(AllData.at(idata)->CalcMode != "ApplGrid") continue;
     AllData.at(idata)->SubmitApplGridJobs();
   }
 }

 //cout<<getTime()<<" ApplGrid start"<<endl;

 //cout<<getTime()<<" FastNLO submit"<<endl;

 // Submit FastNLO Jobs
 for(int idata = 0; idata < AllData.size(); idata++){
   if(AllData.at(idata)->CalcMode != "FastNLO") continue;
   pthread_create(&threadFNLO[idata], NULL, ThreadChi2, AllData[idata]);
   //cout<<"Thread No."<<idata<<" has created."<<endl;
 }
 //cout<<getTime()<<" FastNLO start"<<endl;

 // Submit PineAPPL Jobs
 if(PDFType == "LHAPDF"){
   for(int idata = 0; idata < AllData.size(); idata++){
     if(AllData.at(idata)->CalcMode != "PineAPPL") continue;
     pthread_create(&threadPineAPPL[idata], NULL, ThreadChi2, AllData[idata]);
     //cout<<"Thread No."<<idata<<" has created."<<endl;
   }
 }
 else if(PDFType == "CTEQ"){
   for(int idata = 0; idata < AllData.size(); idata++){
     if(AllData.at(idata)->CalcMode != "PineAPPL") continue;
     AllData.at(idata)->SubmitPineAPPLJobs();
   }
 }

 // Submit DIS Thread Jobs
 for(int i = 1; i <= nDISThread; i++){
   //cout<<"Run "<<ThreadDataDIS[i].size()<<" Data Points in Thread No."<<i<<endl;
   pthread_create(&threadDIS[i], NULL, ThreadChi2, ThreadRunDIS[i]);
   //cout<<"Thread No."<<i<<" has created."<<endl;
 }

 // Submit VBP Thread Jobs
 for(int i = 1; i <= nVBPThread; i++){
   //cout<<"Run "<<ThreadDataVBP[i].size()<<" Data Points in Thread No."<<i<<endl;
   pthread_create(&threadVBP[i], NULL, ThreadChi2, ThreadRunVBP[i]);
   //cout<<"Thread No."<<i<<" has created."<<endl;
 }

 // Waiting for ApplGrid Jobs finish
 if(PDFType == "LHAPDF"){
   for(auto iter = threadAPPL.begin(); iter != threadAPPL.end(); iter++){
     pthread_join(iter->second, NULL);
   }

   for(int idata = 0; idata < AllData.size(); idata++){
     if(AllData.at(idata)->CalcMode != "ApplGrid") continue;

     // Calculate Chi2 for data-ApplGrid first
     pthread_create(&threadCalcChi2[idata], NULL, ThreadCalcChi2, AllData.at(idata));
   }
 }
 else if(PDFType == "CTEQ"){
   for(int idata = 0; idata < AllData.size(); idata++){
     if(AllData.at(idata)->CalcMode != "ApplGrid") continue;
     AllData.at(idata)->WaitApplGridJobs();
     AllData.at(idata)->GetPrediction();

     // Calculate Chi2 for data-ApplGrid first
     pthread_create(&threadCalcChi2[idata], NULL, ThreadCalcChi2, AllData.at(idata));
   }
 }
 //cout<<getTime()<<" ApplGrid finish"<<endl;

 // Waiting for PineAPPL Jobs finish
 if(PDFType == "LHAPDF"){
   for(auto iter = threadPineAPPL.begin(); iter != threadPineAPPL.end(); iter++){
     pthread_join(iter->second, NULL);
   }

   for(int idata = 0; idata < AllData.size(); idata++){
     if(AllData.at(idata)->CalcMode != "PineAPPL") continue;

     // Calculate Chi2 for data-PineAPPL
     pthread_create(&threadCalcChi2[idata], NULL, ThreadCalcChi2, AllData.at(idata));
   }
 }
 else if(PDFType == "CTEQ"){
   for(int idata = 0; idata < AllData.size(); idata++){
     if(AllData.at(idata)->CalcMode != "PineAPPL") continue;
     AllData.at(idata)->WaitPineAPPLJobs();
     AllData.at(idata)->GetPrediction();

     // Calculate Chi2 for data-PineAPPL
     pthread_create(&threadCalcChi2[idata], NULL, ThreadCalcChi2, AllData.at(idata));
   }
 }
 //cout<<getTime()<<" PineAPPL finish"<<endl;

 // Waiting for FastNLO Jobs finish
 for(auto iter = threadFNLO.begin(); iter != threadFNLO.end(); iter++){
   pthread_join(iter->second, NULL);
 }
 //cout<<getTime()<<" FastNLO finish"<<endl;

 // Waiting for DIS Jobs finish
 for(int i = 1; i <= nDISThread; i++){
   pthread_join(threadDIS[i], NULL);
   //cout<<"Thread No."<<i<<" has finished."<<endl;
 }

 // Waiting for VBP Jobs finish
 for(int i = 1; i <= nVBPThread; i++){
   pthread_join(threadVBP[i], NULL);
   //cout<<"Thread No."<<i<<" has finished."<<endl;
 }

 //cout<<getTime()<<" Reorganize DIS data:"<<endl;

 DISDataVector.clear();
 DISFinalData.clear();
 DISFinalTheory.clear();
 for(int i = 1; i <= nDISThread; i++){
   for(int ipoint = 0; ipoint < ThreadRunDIS[i]->GetTheoryTable().size(); ipoint++){
     //DISDataVector.push_back(ThreadRunDIS[i]->GetDataPoint(ipoint));
     DISFinalData.push_back(ThreadRunDIS[i]->GetFinalData(ipoint));
     DISFinalTheory.push_back(ThreadRunDIS[i]->GetFinalTheory(ipoint));
   }
 }

 int iDISPoint = 0;
 for(int idata = 0; idata < AllData.size(); idata++){
   if(AllData.at(idata)->DataType == "DIS"){
     for(int ipoint = 0; ipoint < AllData.at(idata)->NPoints; ipoint++){
       AllData.at(idata)->PushTheoryPoint(DISFinalTheory.at(iDISPoint));
       AllData.at(idata)->PushDataPoint(DISFinalData.at(iDISPoint));
       iDISPoint++;
     }
   }
 }

/*
 for(int ipoint = 0; ipoint < DISDataVector.size(); ipoint++){
   for(int idata = 0; idata < AllData.size(); idata++){
     if(AllData.at(idata)->subType == DISDataVector.at(ipoint).subType){
       AllData.at(idata)->PushTheoryPoint(DISDataVector.at(ipoint).theory);
       AllData.at(idata)->PushDataPoint(DISDataVector.at(ipoint).data);
     }
   }
 }
*/

 //cout<<getTime()<<" Reorganize VBP data:"<<endl;

 //VBPDataVector.clear();
 VBPFinalData.clear();
 VBPFinalTheory.clear();
 for(int i = 1; i <= nVBPThread; i++){
   for(int ipoint = 0; ipoint < ThreadRunVBP[i]->GetTheoryTable().size(); ipoint++){
     //VBPDataVector.push_back(ThreadRunVBP[i]->GetDataPoint(ipoint));
     VBPFinalData.push_back(ThreadRunVBP[i]->GetFinalData(ipoint));
     VBPFinalTheory.push_back(ThreadRunVBP[i]->GetFinalTheory(ipoint));
   }
 }

 int iVBPPoint = 0;
 for(int idata = 0; idata < AllData.size(); idata++){
   if(AllData.at(idata)->DataType == "DrellYan" && AllData.at(idata)->CalcMode == "CTEQ_DY"){
     for(int ipoint = 0; ipoint < AllData.at(idata)->NPoints; ipoint++){
       AllData.at(idata)->PushTheoryPoint(VBPFinalTheory.at(iVBPPoint));
       AllData.at(idata)->PushDataPoint(VBPFinalData.at(iVBPPoint));
       iVBPPoint++;
     }
   }
 }

/*
 for(int ipoint = 0; ipoint < VBPDataVector.size(); ipoint++){
   for(int idata = 0; idata < AllData.size(); idata++){
     if(AllData.at(idata)->subType == VBPDataVector.at(ipoint).subType){
       AllData.at(idata)->PushTheoryPoint(VBPDataVector.at(ipoint).theory);
       AllData.at(idata)->PushDataPoint(VBPDataVector.at(ipoint).data);
     }
   }
 }
*/

 for(int i = 0; i < AllData.size(); i++){
   if(AllData.at(i)->CalcMode == "ApplGrid") continue;
   if(AllData.at(i)->CalcMode == "PineAPPL") continue;

   //cout<<getTime()<<" Calculate Chi2 for "<<AllData.at(i)->m_name<<endl;

   pthread_create(&threadCalcChi2[i], NULL, ThreadCalcChi2, AllData.at(i));
 }

 for(int i = 0; i < AllData.size(); i++){
   pthread_join(threadCalcChi2[i], NULL);

   AllChi2.at(i) = AllData.at(i)->FinalChi2;
 }

 if(print){
   ofstream dtafile("mypdf_bestfit.dta");
   dtafile << " Data: "<<"mypdf_bestfit"<<".dta"<<endl;
   for(int idata = 0; idata < AllData.size(); idata++){
     dtafile << endl;
     dtafile << AllData.at(idata)->OutputLog();
   }
 }

 for(int i = 0; i < AllData.size(); i++){
   if(isBestFit) AllBestFitChi2.at(i) = AllChi2.at(i);
   if(isBestFit) BestFitChi2 += AllBestFitChi2.at(i);
   Result += AllChi2.at(i);
   FitChi2NoPenalty += AllChi2.at(i);
 }

 for(auto iter = BookedLM.begin(); iter != BookedLM.end(); iter++){
   if(print) cout<<"LMPenalty = "<<LMPenalty(std::get<0>(iter->second), std::get<1>(iter->second), std::get<2>(iter->second))<<endl;
   double penalty = LMPenalty(std::get<0>(iter->second), std::get<1>(iter->second), std::get<2>(iter->second));
   Result += penalty;
   if(isBestFit) BestFitChi2 += penalty;
 }

 if(Irun == 0) InitialChi2 = Result;

 Irun++;

 FitChi2 = Result;

 return Result;
}

