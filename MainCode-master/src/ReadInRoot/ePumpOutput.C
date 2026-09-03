#include "ReadInRoot/ePumpOutput.h"

ePumpOutput::ePumpOutput()
{
 InitialExperiments();
}

void ePumpOutput::LinkHist(HistsResBos* &myhists)
{
 this->myhists = myhists;
}

void ePumpOutput::WriteIn()
{
 while(getline(infile, FileLine)){
//   if(FileLine.find(((TString)"Delta Chi2 for Data Set: tab.If1363/E101.If1363 with 337 data points (excluding weight factor w[k] = 0.0000)" + ExperimentName).Data()) != std::string::npos){
   if(FileLine.find(((TString)"Original and Updated Delta Chi-Squares").Data()) != std::string::npos){
     cout<<FileLine<<endl;
     break;
   }
 }

 for(int i = 0; i < 3; i++){
   getline(infile, FileLine);
   cout<<FileLine<<endl;
 }

 char* myDataLine;
 const char* split = " ";
 
 int ibin = 0;

 OldSpartynessHist = new TH1D("OldSpartynessHist", "OldSpartynessHist", Experiments.size(), 1, Experiments.size());
 NewSpartynessHist = new TH1D("NewSpartynessHist", "NewSpartynessHist", Experiments.size(), 1, Experiments.size());
 DeltaSpartynessHist = new TH1D("DeltaSpartynessHist", "DeltaSpartynessHist", Experiments.size(), 1, Experiments.size());

 for(auto Experiment : Experiments){
   ibin++;

   while(getline(infile, FileLine)){
     if(FileLine.find(Experiment.Data()) != std::string::npos){
       while(getline(infile, FileLine)){
         if(FileLine.find("Old Spartyness") != std::string::npos){
           myDataLine = (char *)FileLine.c_str();
           char* WholeLine = strtok(myDataLine, split);
           for(int i = 1; i <= 3; i++){
             if(i >= 3) OldSpartyness = stod(WholeLine);
             WholeLine = strtok(NULL, split);
           }
         }
         if(FileLine.find("New Spartyness") != std::string::npos){
           myDataLine = (char *)FileLine.c_str();
           char* WholeLine = strtok(myDataLine, split);
           for(int i = 1; i <= 3; i++){
             if(i >= 3) NewSpartyness = stod(WholeLine);
             WholeLine = strtok(NULL, split);
           }
           break;
         }
       }
       break;
     }
   }

   OldSpartynessHist->SetBinContent(ibin, OldSpartyness);
   OldSpartynessHist->SetBinError(ibin, 0.0);
   NewSpartynessHist->SetBinContent(ibin, NewSpartyness);
   NewSpartynessHist->SetBinError(ibin, 0.0);
   DeltaSpartynessHist->SetBinContent(ibin, NewSpartyness - OldSpartyness);
   DeltaSpartynessHist->SetBinError(ibin, 0.0);

   cout<<Experiment<<": Old Spartyness "<<OldSpartyness<<endl;
   cout<<Experiment<<": New Spartyness "<<NewSpartyness<<endl;
   cout<<endl;
 }


 infile.close();
}

void ePumpOutput::RetrieveHist(TH1D* &Old, TH1D* &New, TH1D* &Delta)
{
 Old = this->OldSpartynessHist;
 New = this->NewSpartynessHist;
 Delta = this->DeltaSpartynessHist;
}

void ePumpOutput::Get2DPlot()
{
}

void ePumpOutput::InitialExperiments()
{
 Experiments.push_back("tab.If1363/E101.If1363");
 Experiments.push_back("tab.If1363/E102.If1363");
 Experiments.push_back("tab.If1363/E104.If1363");
 Experiments.push_back("tab.If1363/E108.If1363");
 Experiments.push_back("tab.If1363/E109.If1363");
 Experiments.push_back("tab.If1363/E110.If1363");
 Experiments.push_back("tab.If1363/E111.If1363");
 Experiments.push_back("tab.If1363/E124.If1363");
 Experiments.push_back("tab.If1363/E125.If1363");
 Experiments.push_back("tab.If1363/E126.If1363");
 Experiments.push_back("tab.If1363/E127.If1363");
 Experiments.push_back("tab.If1363/E145.If1363");
 Experiments.push_back("tab.If1363/E147.If1363");
 Experiments.push_back("tab.If1363/E160.If1363");
 Experiments.push_back("tab.If1363/E169.If1363");
 Experiments.push_back("tab.If1363/E201.If1363");
 Experiments.push_back("tab.If1363/E203.If1363");
 Experiments.push_back("tab.If1363/E204.If1363");
 Experiments.push_back("tab.If1363/E225.If1363");
 Experiments.push_back("tab.If1363/E227.If1363");
 Experiments.push_back("tab.If1363/E234.If1363");
 Experiments.push_back("tab.If1363/E240.If1363");
 Experiments.push_back("tab.If1363/E241.If1363");
 Experiments.push_back("tab.If1363/E260.If1363");
 Experiments.push_back("tab.If1363/E261.If1363");
 Experiments.push_back("tab.If1363/E266.If1363");
 Experiments.push_back("tab.If1363/E267.If1363");
 Experiments.push_back("tab.If1363/E268.If1363");
 Experiments.push_back("tab.If1363/E281.If1363");
 Experiments.push_back("tab.If1363/E504.If1363");
 Experiments.push_back("tab.If1363/E514.If1363");
 Experiments.push_back("tab.If1363/E535.If1363");
 Experiments.push_back("tab.If1363/E538.If1363");

}
