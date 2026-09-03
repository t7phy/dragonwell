#include "ReadResBosGrid/ReadResBosGrid.h"

using namespace std;

void ReadResBosGrid::openFile(const char* FileName)
{
 infile.open(FileName, ios::in);
}

void ReadResBosGrid::LinkHist(HistsGrids* GridsHists)
{
 this->myhists = GridsHists;
}

void ReadResBosGrid::LoadPertKFactor(vector<TString> FileList)
{
 double DataPoint = 0.0;
 double BinCenter = 0.0;
 double skip = 0.0;

 vector<double> XVectorSave;

 YVector = {20.0, 66.0, 116.0, 500.0};
 ZVector = {0.2, 0.6, 1.0, 1.4, 1.8, 2.2};

 for(int ifile = 0; ifile < FileList.size(); ifile++){
   ifstream infile;
    infile.open(FileList.at(ifile));

   for(int i = 0; i < 3; i++){
     getline(infile, FileLine);
   }

   int ibin = 0;
   while(infile >> skip){
     infile >> BinCenter >> skip;
     infile >> DataPoint;
     infile >> skip >> skip >> skip >> skip >> skip >> skip >> skip >> skip >> skip >> skip >> skip >> skip >> skip;
     XVectorSave.push_back(BinCenter);

     Points[(vector<int>{ibin, 0, ifile})] = DataPoint;
     Points[(vector<int>{ibin, 1, ifile})] = DataPoint;
     Points[(vector<int>{ibin, 2, ifile})] = DataPoint;
     Points[(vector<int>{ibin, 3, ifile})] = DataPoint;
     ibin++;
   }
   XVector = XVectorSave;
   XVectorSave.clear();
   infile.close();
 }
}

void ReadResBosGrid::OutputY(const char* name, ReadResBosGrid* Asym, Interpolation* NNLO, Interpolation* NLO)
{
 ofstream outfile;
  outfile.open(name);

 for(int i = 0; i < 17; i++){
   outfile<<endl;
 }

 for(int i = 0; i <= CountQ; i++){
   for(int j = 0; j <= CountY; j++){
     for(int k = 0; k < v_QT[i][j].size(); k++){
       outfile<<setw(8)<<fixed<<setprecision(2)<<v_Q[i][j];
       outfile<<setw(14)<<fixed<<setprecision(4)<<v_QT[i][j].at(k);
       outfile<<setw(14)<<fixed<<setprecision(4)<<v_Y[i][j]<<endl;

       if(v_QT[i][j].at(k) > 20.0){
         if(fabs(Asym->v_ASY_L0[i][j].at(k)) < 1.0) outfile<<setw(20)<<scientific<<setprecision(5)<<Asym->v_ASY_L0[i][j].at(k);
         if(fabs(Asym->v_ASY_L0[i][j].at(k)) >= 1.0) outfile<<setw(20)<<fixed<<setprecision(5)<<Asym->v_ASY_L0[i][j].at(k);
         if(fabs(Asym->v_ASY_A3[i][j].at(k)) < 1.0) outfile<<setw(20)<<scientific<<setprecision(5)<<Asym->v_ASY_A3[i][j].at(k);
         if(fabs(Asym->v_ASY_A3[i][j].at(k)) >= 1.0) outfile<<setw(20)<<fixed<<setprecision(5)<<Asym->v_ASY_A3[i][j].at(k);
       }
       else{
         if(fabs(v_Singular_L0[i][j].at(k)) < 1.0) outfile<<setw(20)<<scientific<<setprecision(5)<<v_Singular_L0[i][j].at(k);
         if(fabs(v_Singular_L0[i][j].at(k)) >= 1.0) outfile<<setw(20)<<fixed<<setprecision(5)<<v_Singular_L0[i][j].at(k);
         if(fabs(v_Singular_A3[i][j].at(k)) < 1.0) outfile<<setw(20)<<scientific<<setprecision(5)<<v_Singular_A3[i][j].at(k);
         if(fabs(v_Singular_A3[i][j].at(k)) >= 1.0) outfile<<setw(20)<<fixed<<setprecision(5)<<v_Singular_A3[i][j].at(k);
       }

       double Pert_L0 = v_Pert_L0[i][j].at(k);
       if(v_QT[i][j].at(k) > 20.0) Pert_L0 = v_Pert_L0[i][j].at(k) * NNLO->ThreeDInp(2, 2, 2, v_QT[i][j].at(k), v_Q[i][j], v_Y[i][j]) / NLO->ThreeDInp(2, 2, 2, v_QT[i][j].at(k), v_Q[i][j], v_Y[i][j]);
       //if(fabs(v_Pert_L0[i][j].at(k)) < 1.0) outfile<<setw(20)<<scientific<<setprecision(5)<<v_Pert_L0[i][j].at(k);
       //if(fabs(v_Pert_L0[i][j].at(k)) >= 1.0) outfile<<setw(20)<<fixed<<setprecision(5)<<v_Pert_L0[i][j].at(k);
       if(fabs(Pert_L0) < 1.0) outfile<<setw(20)<<scientific<<setprecision(5)<<Pert_L0;
       if(fabs(Pert_L0) >= 1.0) outfile<<setw(20)<<fixed<<setprecision(5)<<Pert_L0;

       double Pert_A3 = v_Pert_A3[i][j].at(k);
       if(v_QT[i][j].at(k) > 20.0) Pert_A3 = v_Pert_A3[i][j].at(k) * NNLO->ThreeDInp(2, 2, 2, v_QT[i][j].at(k), v_Q[i][j], v_Y[i][j]) / NLO->ThreeDInp(2, 2, 2, v_QT[i][j].at(k), v_Q[i][j], v_Y[i][j]);

       //if(fabs(v_Pert_A3[i][j].at(k)) < 1.0) outfile<<setw(20)<<scientific<<setprecision(5)<<v_Pert_A3[i][j].at(k)<<endl;
       //if(fabs(v_Pert_A3[i][j].at(k)) >= 1.0) outfile<<setw(20)<<fixed<<setprecision(5)<<v_Pert_A3[i][j].at(k)<<endl;
       if(fabs(Pert_A3) < 1.0) outfile<<setw(20)<<scientific<<setprecision(5)<<Pert_A3<<endl;
       if(fabs(Pert_A3) >= 1.0) outfile<<setw(20)<<fixed<<setprecision(5)<<Pert_A3<<endl;

       if(fabs(v_Pert_A1[i][j].at(k)) < 1.0) outfile<<setw(20)<<scientific<<setprecision(5)<<v_Pert_A1[i][j].at(k);
       if(fabs(v_Pert_A1[i][j].at(k)) >= 1.0) outfile<<setw(20)<<fixed<<setprecision(5)<<v_Pert_A1[i][j].at(k);
       if(fabs(v_Pert_A2[i][j].at(k)) < 1.0) outfile<<setw(20)<<scientific<<setprecision(5)<<v_Pert_A2[i][j].at(k);
       if(fabs(v_Pert_A2[i][j].at(k)) >= 1.0) outfile<<setw(20)<<fixed<<setprecision(5)<<v_Pert_A2[i][j].at(k);
       if(fabs(v_Pert_A4[i][j].at(k)) < 1.0) outfile<<setw(20)<<scientific<<setprecision(5)<<v_Pert_A4[i][j].at(k);
       if(fabs(v_Pert_A4[i][j].at(k)) >= 1.0) outfile<<setw(20)<<fixed<<setprecision(5)<<v_Pert_A4[i][j].at(k);
       if(fabs(v_Pert_A0[i][j].at(k)) < 1.0) outfile<<setw(20)<<scientific<<setprecision(5)<<v_Pert_A0[i][j].at(k)<<endl;
       if(fabs(v_Pert_A0[i][j].at(k)) >= 1.0) outfile<<setw(20)<<fixed<<setprecision(5)<<v_Pert_A0[i][j].at(k)<<endl;
     }
   }
 }
}

void ReadResBosGrid::LoadW(int iformat)
{
 for(int i = 0; i < 15; i++){
   getline(infile, FileLine);
   if(isOutput) cout<<FileLine<<endl;
 }

 CountQ = 0;
 CountY = 0;
 while(infile>>Q){
   if(iformat == 1) infile >> QT >> Y >> CSS_L0 >> CSS_A3 >> ASY_L0 >> ASY_A3;
   if(iformat == 2) infile >> QT >> Y >> CSS_L0 >> CSS_A3;

   v_Q[0][0] = 0;
   v_Y[0][0] = 0;
   if(fabs(v_Q[CountQ][CountY] - Q) > 0.0000001){
     CountQ++;
     CountY = 0;
   }
   if(fabs(v_Y[CountQ][CountY] - Y) > 0.0000001) CountY++;

   v_Q[CountQ][CountY] = Q;
   v_Y[CountQ][CountY] = Y;

   v_QT[CountQ][CountY].push_back(QT);
   v_CSS_L0[CountQ][CountY].push_back(CSS_L0);
   v_CSS_A3[CountQ][CountY].push_back(CSS_A3);
   v_ASY_L0[CountQ][CountY].push_back(ASY_L0);
   v_ASY_A3[CountQ][CountY].push_back(ASY_A3);


 }
 cout<<"Load ResBos W-grid finished."<<endl;
}

void ReadResBosGrid::LoadY()
{
 for(int i = 0; i < 17; i++){
   getline(infile, FileLine);
   if(isOutput) cout<<FileLine<<endl;
 }

 CountQ = 0;
 CountY = 0;
 while(infile>>Q){ 
   infile >> QT >> Y >> Singular_L0 >> Singular_A3 >> Pert_L0 >> Pert_A3 >> Pert_A1 >> Pert_A2 >> Pert_A4 >> Pert_A0;
   
   v_Q[0][0] = 0;
   v_Y[0][0] = 0;
   if(fabs(v_Q[CountQ][CountY] - Q) > 0.0000001){
     CountQ++;
     CountY = 0;
   }
   if(fabs(v_Y[CountQ][CountY] - Y) > 0.0000001) CountY++;
   
   v_Q[CountQ][CountY] = Q;
   v_Y[CountQ][CountY] = Y;
   
   v_QT[CountQ][CountY].push_back(QT);
   v_Singular_L0[CountQ][CountY].push_back(Singular_L0);
   v_Singular_A3[CountQ][CountY].push_back(Singular_A3);
   v_Pert_L0[CountQ][CountY].push_back(Pert_L0);
   v_Pert_A3[CountQ][CountY].push_back(Pert_A3);
   v_Pert_A1[CountQ][CountY].push_back(Pert_A1);
   v_Pert_A2[CountQ][CountY].push_back(Pert_A2);
   v_Pert_A4[CountQ][CountY].push_back(Pert_A4);
   v_Pert_A0[CountQ][CountY].push_back(Pert_A0);

 
 }
 cout<<"Load ResBos Y-grid finished."<<endl;

}

void ReadResBosGrid::LoadPert()
{

}

void ReadResBosGrid::LoadAsym()
{
 for(int i = 0; i < 12; i++){
   getline(infile, FileLine);
   if(isOutput) cout<<FileLine<<endl;
 }

 CountQ = 0;
 CountY = 0;
 while(infile>>Q){
   infile >> QT >> Y >> ASY_L0 >> ASY_A3;

   v_Q[0][0] = 0;
   v_Y[0][0] = 0;
   if(fabs(v_Q[CountQ][CountY] - Q) > 0.0000001){
     CountQ++;
     CountY = 0;
   }
   if(fabs(v_Y[CountQ][CountY] - Y) > 0.0000001) CountY++;

   v_Q[CountQ][CountY] = Q;
   v_Y[CountQ][CountY] = Y;

   v_QT[CountQ][CountY].push_back(QT);
   v_ASY_L0[CountQ][CountY].push_back(ASY_L0);
   v_ASY_A3[CountQ][CountY].push_back(ASY_A3);
 }
 cout<<"Load ResBos Asym-grid finished."<<endl;

}

void ReadResBosGrid::LoadMatch()
{
 double skip;

 for(int i = 0; i < 15; i++){
   getline(infile, FileLine);
   if(isOutput) cout<<FileLine<<endl;
 }
 
 CountQ = 0;
 CountY = 0;
 while(infile>>Q){ 
   infile >> QT >> Y >> Match_CSS >> Match_CSSPlusY >> Match_Pert >> Match_CSSPlusY_MatchToPert >> skip >> skip;
   
   v_Q[0][0] = 0;
   v_Y[0][0] = 0;
   if(fabs(v_Q[CountQ][CountY] - Q) > 0.0000001){
     CountQ++;
     CountY = 0;
   }
   if(fabs(v_Y[CountQ][CountY] - Y) > 0.0000001) CountY++;
   
   v_Q[CountQ][CountY] = Q;
   v_Y[CountQ][CountY] = Y;
   
   v_QT[CountQ][CountY].push_back(QT);
   v_Match_CSS[CountQ][CountY].push_back(Match_CSS);
   v_Match_CSSPlusY[CountQ][CountY].push_back(Match_CSSPlusY);
   v_Match_Pert[CountQ][CountY].push_back(Match_Pert);
   v_Match_CSSPlusY_MatchToPert[CountQ][CountY].push_back(Match_CSSPlusY_MatchToPert);

 
 }
 cout<<"Load ResBos Matched-grid finished."<<endl;

}

void ReadResBosGrid::SetPoint(const char* TypeName, double myQ, double myY)
{
 int QID = 0;
 int YID = 0;
 for(int i = 0; i < CountQ; i++){
   if(fabs(v_Q[i][1] - myQ) < 0.00000001) QID = i;
 }
 for(int i = 0; i < CountY; i++){
   if(fabs(v_Y[1][i] - myY) < 0.00000001) YID = i;
 }

 cout<<v_Q[QID][1]<<"  "<<v_Y[1][YID]<<endl;
 if(isOutput) myhists->Output();

 myhists->bookHists(TypeName, QID, YID, myQ, myY);
 if((TString)TypeName == "CSS_L0") myhists->SetPoint(TypeName, QID, YID, v_QT[QID][YID], v_CSS_L0[QID][YID]);
 if((TString)TypeName == "CSS_A3") myhists->SetPoint(TypeName, QID, YID, v_QT[QID][YID], v_CSS_A3[QID][YID]);
 if((TString)TypeName == "Singular_L0") myhists->SetPoint(TypeName, QID, YID, v_QT[QID][YID], v_Singular_L0[QID][YID]);
 if((TString)TypeName == "Singular_A3") myhists->SetPoint(TypeName, QID, YID, v_QT[QID][YID], v_Singular_A3[QID][YID]);
 if((TString)TypeName == "Pert_L0") myhists->SetPoint(TypeName, QID, YID, v_QT[QID][YID], v_Pert_L0[QID][YID]);
 if((TString)TypeName == "Pert_A3") myhists->SetPoint(TypeName, QID, YID, v_QT[QID][YID], v_Pert_A3[QID][YID]);
 if((TString)TypeName == "Pert_A1") myhists->SetPoint(TypeName, QID, YID, v_QT[QID][YID], v_Pert_A1[QID][YID]);
 if((TString)TypeName == "Pert_A2") myhists->SetPoint(TypeName, QID, YID, v_QT[QID][YID], v_Pert_A2[QID][YID]);
 if((TString)TypeName == "Pert_A4") myhists->SetPoint(TypeName, QID, YID, v_QT[QID][YID], v_Pert_A4[QID][YID]);
 if((TString)TypeName == "Pert_A0") myhists->SetPoint(TypeName, QID, YID, v_QT[QID][YID], v_Pert_A0[QID][YID]);
 if((TString)TypeName == "Match_CSS") myhists->SetPoint(TypeName, QID, YID, v_QT[QID][YID], v_Match_CSS[QID][YID]);
 if((TString)TypeName == "Match_CSS+Y") myhists->SetPoint(TypeName, QID, YID, v_QT[QID][YID], v_Match_CSSPlusY[QID][YID]);
 if((TString)TypeName == "Match_Pert") myhists->SetPoint(TypeName, QID, YID, v_QT[QID][YID], v_Match_Pert[QID][YID]);
 if((TString)TypeName == "Match_CSS+Y_MatchToPert") myhists->SetPoint(TypeName, QID, YID, v_QT[QID][YID], v_Match_CSSPlusY_MatchToPert[QID][YID]);

}

void ReadResBosGrid::SaveW(double myQ, double myY)
{
 SetPoint("CSS_L0", myQ, myY);
 SetPoint("CSS_A3", myQ, myY);
}

void ReadResBosGrid::SaveY(double myQ, double myY)
{
 SetPoint("Singular_L0", myQ, myY);
 SetPoint("Singular_A3", myQ, myY);
 SetPoint("Pert_L0", myQ, myY);
 SetPoint("Pert_A3", myQ, myY);
 SetPoint("Pert_A1", myQ, myY);
 SetPoint("Pert_A2", myQ, myY);
 SetPoint("Pert_A4", myQ, myY);
 SetPoint("Pert_A0", myQ, myY);
}

void ReadResBosGrid::SaveMatch(double myQ, double myY)
{
 SetPoint("Match_CSS", myQ, myY);
 SetPoint("Match_CSS+Y", myQ, myY);
 SetPoint("Match_Pert", myQ, myY);
 SetPoint("Match_CSS+Y_MatchToPert", myQ, myY);
}


