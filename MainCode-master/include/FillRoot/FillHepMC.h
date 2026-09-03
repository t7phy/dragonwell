#ifndef FillHepMC_h
#define FillHepMC_h

#include "FillRoot/FillRoot.h"

class FillHepMC : public FillRoot
{
 public:

 TTree *metaTree;

 double GammaPx[10] = {0.0};
 double GammaPy[10] = {0.0};
 double GammaPz[10] = {0.0};
 double GammaE[10] = {0.0};
 int GammaMother[10] = {0};//source of gamma the serial number of the event
 int GammaNumber;//take 10 radiational gammas, no more than that 

 double ElectronPx;//e-
 double ElectronPy;
 double ElectronPz;
 double ElectronE;//you'd better follow this paticular order
 int ElectronFlavor;

 double eNeutrinoPx;//e-
 double eNeutrinoPy;
 double eNeutrinoPz;
 double eNeutrinoE;//you'd better follow this paticular order

 double MuonPx;
 double MuonPy;
 double MuonPz;
 double MuonE;
 int MuonFlavor;

 double mNeutrinoPx;//e-
 double mNeutrinoPy;
 double mNeutrinoPz;
 double mNeutrinoE;//you'd better follow this paticular order

 int quark_flavour[2];
 double QuarkPx[2];
 double QuarkPy[2];
 double QuarkPz[2];
 double QuarkE[2];

 std::string FileLine;

 //E
 int EventNumber;
 int InterNumber;
 double EventScale;
 double alpha_s;
 double alpha_ew;
 int SignalID;
 int SignalBarCode;
 int NVertex;
 int Beam1BarCode;
 int Beam2BarCode;
 int NRandomList;
 std::vector<long> RandomLists;
 int NWeight;
 std::vector<float> Weights;

 //N
 int NWeightName;
 std::vector<std::string> WeightNames;

 //U
 std::string MomentumUnit;
 std::string LengthUnit;

 //C
 double CrossSection;
 double CrossSectionError;

 //H
 int NHardScatter;
 int NProjectile;
 int NTarget;
 int NNucleonCollision;
 int NSpectatorNeutron;
 int NSpectatorProton;
 int NWoundedCollision;
 int NWoundedNCollision;
 int NWoundedWounded;
 float ImpactParameter;
 float AzimuthalAngle;
 float Eccentricity;
 float NucleonNucleonCrossSection;

 //F
 int Flavor1;
 int Flavor2;
 double x1, x2;
 double PDFScale;
 double xf1, xf2;
 int partonid1, partonid2;

 //V
 int VertexBarCode;
 int VertexID;
 double v_x, v_y, v_z;
 double ctau;
 int Norphan;
 int NOutgoing;
 int NVertexWeightList;
 std::vector<double> VertexWeights;

 //P
 int BarCode;
 int pdgID;
 double px, py, pz, energy, mass;
 int StatusCode;
 double PolTheta, PolPhi;
 int NFlowList;
 std::vector<int> FlowCodeIndex;
 std::vector<int> FlowCode;

 bool isSpeedUp = true;

 int evt;
 double skip;

 virtual void DefineTree();
 virtual void DefineMetaTree();
 virtual void FillIn();
 virtual void FillE();
 virtual void FillN();
 virtual void FillU();
 virtual void FillC();
 virtual void FillH();
 virtual void FillF();
 virtual void FillV();
 virtual void FillP();
 virtual void ResetEvent();

};
#endif
