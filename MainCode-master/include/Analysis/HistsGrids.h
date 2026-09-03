#ifndef HistsGrids_h
#define HistsGrids_h

#include "Analysis/makeHists.h"

class HistsGrids : public makeHists
{
 public:

 TGraph* CSS_L0[200][200];
 TGraph* CSS_A3[200][200];

 TGraph* ASY_L0[200][200];
 TGraph* ASY_A3[200][200];

 TGraph* Singular_L0[200][200];
 TGraph* Singular_A3[200][200];

 TGraph* Pert_L0[200][200];
 TGraph* Pert_A3[200][200];
 TGraph* Pert_A1[200][200];
 TGraph* Pert_A2[200][200];
 TGraph* Pert_A4[200][200];
 TGraph* Pert_A0[200][200];

 TGraph* Match_CSS[200][200];
 TGraph* Match_CSSPlusY[200][200];
 TGraph* Match_Pert[200][200];
 TGraph* Match_CSSPlusY_MatchToPert[200][200];

 int CSS_L0_Count = 0;
 int CSS_A3_Count = 0;

 int ASY_L0_Count = 0;
 int ASY_A3_Count = 0;

 int Singular_L0_Count = 0;
 int Singular_A3_Count = 0;

 int Pert_L0_Count = 0;
 int Pert_A3_Count = 0;
 int Pert_A1_Count = 0;
 int Pert_A2_Count = 0;
 int Pert_A4_Count = 0;
 int Pert_A0_Count = 0;

 double myQ;
 double myY;

 double PtMin = -999.0;
 double PtMax = 100000.0;

 bool isOutput = false;

 virtual void bookHists(const char* TypeName, int QID, int YID, double myQ, double myY);
 virtual void SetPoint(const char* TypeName, int QID, int YID, vector<double> XPoint, vector<double> YPoint);
 virtual void PtCut(double min, double max);
 virtual void Output(){isOutput = true;}
};
#endif
