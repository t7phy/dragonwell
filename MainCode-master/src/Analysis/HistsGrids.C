#include "Analysis/HistsGrids.h"

using namespace std;

void HistsGrids::bookHists(const char* TypeName, int QID, int YID, double myQ, double myY)
{
 hf->cd();

 this->myQ = myQ;
 this->myY = myY;

 string ystring;
 stringstream s_ystring;
 s_ystring<<fixed<<setprecision(1)<<myY;
 ystring = s_ystring.str();

 if((TString)TypeName == "CSS_L0"){
   CSS_L0[QID][YID] = new TGraph();
   cout<<"book CSS L0 graph"<<endl;
 }
 if((TString)TypeName == "CSS_A3"){
   CSS_A3[QID][YID] = new TGraph();
   cout<<"book CSS A3 graph"<<endl;
 }
 if((TString)TypeName == "Singular_L0"){
   Singular_L0[QID][YID] = new TGraph();
   cout<<"book Singular L0 graph"<<endl;
 }
 if((TString)TypeName == "Singular_A3"){
   Singular_A3[QID][YID] = new TGraph();
   cout<<"book Singular A3 graph"<<endl;
 }
 if((TString)TypeName == "Pert_L0"){
   Pert_L0[QID][YID] = new TGraph();
   cout<<"book Pert L0 graph"<<endl;
 }
 if((TString)TypeName == "Pert_A3"){
   Pert_A3[QID][YID] = new TGraph();
   cout<<"book Pert A3 graph"<<endl;
 }
 if((TString)TypeName == "Pert_A1"){
   Pert_A1[QID][YID] = new TGraph();
   cout<<"book Pert A1 graph"<<endl;
 }
 if((TString)TypeName == "Pert_A2"){
   Pert_A2[QID][YID] = new TGraph();
   cout<<"book Pert A2 graph"<<endl;
 }
 if((TString)TypeName == "Pert_A4"){
   Pert_A4[QID][YID] = new TGraph();
   cout<<"book Pert A4 graph"<<endl;
 }
 if((TString)TypeName == "Pert_A0"){
   Pert_A0[QID][YID] = new TGraph();
   cout<<"book Pert A0 graph"<<endl;
 }
 if((TString)TypeName == "Match_CSS"){
   Match_CSS[QID][YID] = new TGraph();
   cout<<"book Match CSS graph"<<endl;
 }
 if((TString)TypeName == "Match_CSS+Y"){
   Match_CSSPlusY[QID][YID] = new TGraph();
   cout<<"book Match CSS+Y graph"<<endl;
 }
 if((TString)TypeName == "Match_Pert"){
   Match_Pert[QID][YID] = new TGraph();
   cout<<"book Match Pert graph"<<endl;
 }
 if((TString)TypeName == "Match_CSS+Y_MatchToPert"){
   Match_CSSPlusY_MatchToPert[QID][YID] = new TGraph();
   cout<<"book Match CSS+Y MatchToPert graph"<<endl;
 }

}

void HistsGrids::SetPoint(const char* TypeName, int QID, int YID, vector<double> XPoint, vector<double> YPoint)
{
 hf->cd();

 string ystring;
 stringstream s_ystring;
 s_ystring<<fixed<<setprecision(1)<<myY;
 ystring = s_ystring.str();

 if((TString)TypeName == "CSS_L0"){
   for(int i = 0; i < XPoint.size(); i++){
     if(XPoint.at(i) < PtMin || XPoint.at(i) > PtMax || PtMin < 0.0) continue;
     CSS_L0[QID][YID]->SetPoint(i, XPoint.at(i), YPoint.at(i));
     if(isOutput) cout<<XPoint.at(i)<<"  "<<YPoint.at(i)<<endl;
   }
   CSS_L0[QID][YID]->Write((TString)TypeName + (TString)"_Q" + (double)myQ + (TString)"_Y" + ystring.c_str());
 }

 if((TString)TypeName == "CSS_A3"){
   for(int i = 0; i < XPoint.size(); i++){
     if(XPoint.at(i) < PtMin || XPoint.at(i) > PtMax || PtMin < 0.0) continue;
     CSS_A3[QID][YID]->SetPoint(i, XPoint.at(i), YPoint.at(i));
     if(isOutput) cout<<XPoint.at(i)<<"  "<<YPoint.at(i)<<endl;
   }
   CSS_A3[QID][YID]->Write((TString)TypeName + (TString)"_Q" + (double)myQ + (TString)"_Y" + ystring.c_str());
 }

 if((TString)TypeName == "Singular_L0"){
   for(int i = 0; i < XPoint.size(); i++){
     if(XPoint.at(i) < PtMin || XPoint.at(i) > PtMax || PtMin < 0.0) continue;
     Singular_L0[QID][YID]->SetPoint(i, XPoint.at(i), YPoint.at(i));
     if(isOutput) cout<<XPoint.at(i)<<"  "<<YPoint.at(i)<<endl;
   }
   Singular_L0[QID][YID]->Write((TString)TypeName + (TString)"_Q" + (double)myQ + (TString)"_Y" + ystring.c_str());
 }

 if((TString)TypeName == "Singular_A3"){
   for(int i = 0; i < XPoint.size(); i++){
     if(XPoint.at(i) < PtMin || XPoint.at(i) > PtMax || PtMin < 0.0) continue;
     Singular_A3[QID][YID]->SetPoint(i, XPoint.at(i), YPoint.at(i));
     if(isOutput) cout<<XPoint.at(i)<<"  "<<YPoint.at(i)<<endl;
   }
   Singular_A3[QID][YID]->Write((TString)TypeName + (TString)"_Q" + (double)myQ + (TString)"_Y" + ystring.c_str());
 }

 if((TString)TypeName == "Pert_L0"){
   for(int i = 0; i < XPoint.size(); i++){
     if(XPoint.at(i) < PtMin || XPoint.at(i) > PtMax || PtMin < 0.0) continue;
     Pert_L0[QID][YID]->SetPoint(i, XPoint.at(i), YPoint.at(i));
     if(isOutput) cout<<XPoint.at(i)<<"  "<<YPoint.at(i)<<endl;
   }
   Pert_L0[QID][YID]->Write((TString)TypeName + (TString)"_Q" + (double)myQ + (TString)"_Y" + ystring.c_str());
 }

 if((TString)TypeName == "Pert_A3"){
   for(int i = 0; i < XPoint.size(); i++){
     if(XPoint.at(i) < PtMin || XPoint.at(i) > PtMax || PtMin < 0.0) continue;
     Pert_A3[QID][YID]->SetPoint(i, XPoint.at(i), YPoint.at(i));
     if(isOutput) cout<<XPoint.at(i)<<"  "<<YPoint.at(i)<<endl;
   }
   Pert_A3[QID][YID]->Write((TString)TypeName + (TString)"_Q" + (double)myQ + (TString)"_Y" + ystring.c_str());
 }

 if((TString)TypeName == "Pert_A1"){
   for(int i = 0; i < XPoint.size(); i++){
     if(XPoint.at(i) < PtMin || XPoint.at(i) > PtMax || PtMin < 0.0) continue;
     Pert_A1[QID][YID]->SetPoint(i, XPoint.at(i), YPoint.at(i));
     if(isOutput) cout<<XPoint.at(i)<<"  "<<YPoint.at(i)<<endl;
   } 
   Pert_A1[QID][YID]->Write((TString)TypeName + (TString)"_Q" + (double)myQ + (TString)"_Y" + ystring.c_str());
 } 

 if((TString)TypeName == "Pert_A2"){
   for(int i = 0; i < XPoint.size(); i++){
     if(XPoint.at(i) < PtMin || XPoint.at(i) > PtMax || PtMin < 0.0) continue;
     Pert_A2[QID][YID]->SetPoint(i, XPoint.at(i), YPoint.at(i));
     if(isOutput) cout<<XPoint.at(i)<<"  "<<YPoint.at(i)<<endl;
   }
   Pert_A2[QID][YID]->Write((TString)TypeName + (TString)"_Q" + (double)myQ + (TString)"_Y" + ystring.c_str());
 }

 if((TString)TypeName == "Pert_A4"){
   for(int i = 0; i < XPoint.size(); i++){
     if(XPoint.at(i) < PtMin || XPoint.at(i) > PtMax || PtMin < 0.0) continue;
     Pert_A4[QID][YID]->SetPoint(i, XPoint.at(i), YPoint.at(i));
     if(isOutput) cout<<XPoint.at(i)<<"  "<<YPoint.at(i)<<endl;
   } 
   Pert_A4[QID][YID]->Write((TString)TypeName + (TString)"_Q" + (double)myQ + (TString)"_Y" + ystring.c_str());
 } 

 if((TString)TypeName == "Pert_A0"){
   for(int i = 0; i < XPoint.size(); i++){
     if(XPoint.at(i) < PtMin || XPoint.at(i) > PtMax || PtMin < 0.0) continue;
     Pert_A0[QID][YID]->SetPoint(i, XPoint.at(i), YPoint.at(i));
     if(isOutput) cout<<XPoint.at(i)<<"  "<<YPoint.at(i)<<endl;
   }
   Pert_A0[QID][YID]->Write((TString)TypeName + (TString)"_Q" + (double)myQ + (TString)"_Y" + ystring.c_str());
 }

 if((TString)TypeName == "Match_CSS"){
   for(int i = 0; i < XPoint.size(); i++){
     if(XPoint.at(i) < PtMin || XPoint.at(i) > PtMax || PtMin < 0.0) continue;
     Match_CSS[QID][YID]->SetPoint(i, XPoint.at(i), YPoint.at(i));
     if(isOutput) cout<<XPoint.at(i)<<"  "<<YPoint.at(i)<<endl;
   }
   Match_CSS[QID][YID]->Write((TString)TypeName + (TString)"_Q" + (double)myQ + (TString)"_Y" + ystring.c_str());
 } 

 if((TString)TypeName == "Match_CSS+Y"){
   for(int i = 0; i < XPoint.size(); i++){
     if(XPoint.at(i) < PtMin || XPoint.at(i) > PtMax || PtMin < 0.0) continue;
     Match_CSSPlusY[QID][YID]->SetPoint(i, XPoint.at(i), YPoint.at(i));
     if(isOutput) cout<<XPoint.at(i)<<"  "<<YPoint.at(i)<<endl;
   }
   Match_CSSPlusY[QID][YID]->Write((TString)TypeName + (TString)"_Q" + (double)myQ + (TString)"_Y" + ystring.c_str());
 } 

 if((TString)TypeName == "Match_Pert"){
   for(int i = 0; i < XPoint.size(); i++){
     if(XPoint.at(i) < PtMin || XPoint.at(i) > PtMax || PtMin < 0.0) continue;
     Match_Pert[QID][YID]->SetPoint(i, XPoint.at(i), YPoint.at(i));
     if(isOutput) cout<<XPoint.at(i)<<"  "<<YPoint.at(i)<<endl;
   }
   Match_Pert[QID][YID]->Write((TString)TypeName + (TString)"_Q" + (double)myQ + (TString)"_Y" + ystring.c_str());
 } 

 if((TString)TypeName == "Match_CSS+Y_MatchToPert"){
   for(int i = 0; i < XPoint.size(); i++){
     if(XPoint.at(i) < PtMin || XPoint.at(i) > PtMax || PtMin < 0.0) continue;
     Match_CSSPlusY_MatchToPert[QID][YID]->SetPoint(i, XPoint.at(i), YPoint.at(i));
     if(isOutput) cout<<XPoint.at(i)<<"  "<<YPoint.at(i)<<endl;
   }
   Match_CSSPlusY_MatchToPert[QID][YID]->Write((TString)TypeName + (TString)"_Q" + (double)myQ + (TString)"_Y" + ystring.c_str());
 } 

}

void HistsGrids::PtCut(double min, double max)
{
 this->PtMin = min;
 this->PtMax = max;
}
