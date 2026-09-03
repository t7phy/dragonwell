#ifndef ReadResBosGrid_h
#define ReadResBosGrid_h

#include "RootCommon.h"
#include "Analysis/HistsGrids.h"
#include "Tools/Interpolation.h"

class ReadResBosGrid
{
 public:

 HistsGrids* myhists;

 ifstream infile;

 TString skip;
 string FileLine;
 double para;

 vector<double> XVector;
 vector<double> YVector;
 vector<double> ZVector;
 map<vector<int>, double> Points;

 double Q;
 double QT;
 double Y;
 double CSS_L0;
 double CSS_A3;
 double ASY_L0;
 double ASY_A3;
 double Singular_L0;
 double Singular_A3;
 double Pert_L0;
 double Pert_A3;
 double Pert_A1;
 double Pert_A2;
 double Pert_A4;
 double Pert_A0;
 double Match_CSS;
 double Match_CSSPlusY;
 double Match_Pert;
 double Match_CSSPlusY_MatchToPert;

 double v_Q[200][200];
 double v_Y[200][200];

 vector<double> v_QT[200][200];
 vector<double> v_CSS_L0[200][200];
 vector<double> v_CSS_A3[200][200];
 vector<double> v_ASY_L0[200][200];
 vector<double> v_ASY_A3[200][200];
 vector<double> v_Singular_L0[200][200];
 vector<double> v_Singular_A3[200][200];
 vector<double> v_Pert_L0[200][200];
 vector<double> v_Pert_A3[200][200];
 vector<double> v_Pert_A1[200][200];
 vector<double> v_Pert_A2[200][200];
 vector<double> v_Pert_A4[200][200];
 vector<double> v_Pert_A0[200][200];
 vector<double> v_Match_CSS[200][200];
 vector<double> v_Match_CSSPlusY[200][200];
 vector<double> v_Match_Pert[200][200];
 vector<double> v_Match_CSSPlusY_MatchToPert[200][200];

 int CountQ;
 int CountY;

 bool isOutput = false;

 virtual void openFile(const char* FileName);
 virtual void LinkHist(HistsGrids* GridsHists);
 virtual void LoadPertKFactor(vector<TString> FileList);
 virtual void OutputY(const char* name, ReadResBosGrid* Asym, Interpolation* NNLO, Interpolation* NLO);


 virtual void LoadW(int iformat);
 virtual void LoadY();
 virtual void LoadPert();
 virtual void LoadAsym();
 virtual void LoadMatch();
 virtual void SetPoint(const char* TypeName, double myQ, double myY);
 virtual void Output(){isOutput = true;}
 virtual void SaveW(double myQ, double myY);
 virtual void SaveY(double myQ, double myY);
 virtual void SaveMatch(double myQ, double myY);
};
#endif
