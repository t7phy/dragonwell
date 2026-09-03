#ifndef Calculation_PDFChi2_h
#define Calculation_PDFChi2_h

#include "RootCommon.h"
#include "Tools/Tools.h"
#include "Calculation/Dataset.h"
#include "Calculation/Config.h"

class PDFChi2
{
 public:

 Config setting;

 bool isInitial = false;
 TString PDFType = "";

 vector<Dataset *> AllData;
 vector<double> AllChi2;
 vector<double> AllBestFitChi2;
 vector<int> AllNPoints;
 map<int, int> IDtoIndex;
 map<TString, int> NametoIndex;

 double FitChi2 = 0.0;
 double FitChi2NoPenalty = 0.0;
 double BestFitChi2 = 0.0;

 double InitialChi2 = 0.0;
 double FinalChi2 = 0.0;

 int TotalThread = 40;
 int nDISThread = 55;
 int nVBPThread = 15;

 vector<DataPoint> DISDataVector;
 vector<double> DISFinalData;
 vector<double> DISFinalTheory;
 map<int, Dataset *> ThreadRunDIS;
 map<int, vector<DataPoint>> ThreadDataDIS;
 map<int, pthread_t> threadDIS;
 int nDISPointsPerThread;

 vector<DataPoint> VBPDataVector;
 vector<double> VBPFinalData;
 vector<double> VBPFinalTheory;
 map<int, Dataset *> ThreadRunVBP;
 map<int, vector<DataPoint>> ThreadDataVBP;
 map<int, pthread_t> threadVBP;
 int nVBPPointsPerThread;

 map<int, pthread_t> threadAPPL;
 map<int, pthread_t> threadFNLO;
 map<int, pthread_t> threadPineAPPL;
 map<int, pthread_t> threadCalcChi2;

 int Irun = 0;

 PDFChi2();
 virtual void Initialize(vector<Dataset *> AllData, Config setting);
 virtual void InitialPDF(Config setting);
 virtual double GetChi2(bool print, bool isBestFit = false);

 map<int, tuple<TString, vector<int>, vector<double>>> BookedLM;
 virtual void BookLMPenalty(int i, TString LMType, vector<int> LM, vector<double> dM){
   BookedLM[i] = make_tuple(LMType, LM, dM);
 }
 virtual void DeleteLMPenalty(int i){
   BookedLM.erase(i);
 }

 virtual double LMPenalty(TString LMType, vector<int> LM, vector<double> dM);

 virtual void ResetFit(){
   Irun = 0;
   InitialChi2 = 0.0;
   FinalChi2 = 0.0;

   for(auto iter = ThreadRunDIS.begin(); iter != ThreadRunDIS.end(); iter++){
     iter->second->ResetFit();
   }
   for(auto iter = ThreadRunVBP.begin(); iter != ThreadRunVBP.end(); iter++){
     iter->second->ResetFit();
   }

   cout<<getTime()<<" Calculate Chi2 again in complete NNLO."<<endl;
   double Value = GetChi2(true);
   cout<<getTime()<<" Chi2 = "<<Value<<endl;
   cout<<getTime()<<" NNLO/NLO k-factor calculation done."<<endl;
 }

 virtual void ThreadSetup(int DIS, int VBP){this->nDISThread = DIS; this->nVBPThread = VBP;}

 virtual vector<double> GetTheoryPrediction(TString name){
   int Index = NametoIndex.at(name);
   vector<double> theory;
   for(int i = 0; i < AllData.at(Index)->NPoints; i++){
     theory.push_back(AllData.at(Index)->Theory(i));
   }
   return theory;
 }

 virtual void UpdateVBPDataTable(){
   // For updating the wp_kfac and wm_kfac if the additional kfactor is applied
   // Since wp_kfac and wm_kfac are used inside the m_calculation of Dataset, the kfactors are only
   // updated for AllData, which will not be propagated to the ThreadRunVBP automatically.
   // Here we update the corresponding kfactor in VBPDataVector at first, then update the ThreadDataVBP,
   // Finally, call the UpdateDataTable in each ThreadRunVBP objects.

   int ibin = 0;
   for(int idata = 0; idata < AllData.size(); idata++){
     if(AllData.at(idata)->DataType == "DrellYan" && AllData.at(idata)->CalcMode == "CTEQ_DY"){
       for(int ipoint = 0; ipoint < AllData.at(idata)->NPoints; ipoint++){
         VBPDataVector.at(ibin).wp_kfac = AllData.at(idata)->m_data.at(ipoint).wp_kfac;
         VBPDataVector.at(ibin).wm_kfac = AllData.at(idata)->m_data.at(ipoint).wm_kfac;

         ibin++;
       }
     }
   }

   ibin = 0;
   int iThread = 0;
   for(int ipoint = 0; ipoint < VBPDataVector.size(); ipoint++){
     if(ipoint % nVBPPointsPerThread == 0 && iThread != nVBPThread){
       iThread++;
       ibin = 0;
     }
     ThreadDataVBP.at(iThread).at(ibin).wp_kfac = VBPDataVector.at(ipoint).wp_kfac;
     ThreadDataVBP.at(iThread).at(ibin).wm_kfac = VBPDataVector.at(ipoint).wm_kfac;

     ibin++;
   }

   for(int i = 1; i <= nVBPThread; i++){
     ThreadRunVBP[i]->m_calculation->UpdateDataTable(ThreadDataVBP.at(i));
   }
 }

};
#endif
