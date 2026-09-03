#ifndef Calculation_EwkSet_h
#define Calculation_EwkSet_h

#include "RootCommon.h"
#include "Calculation/FortranArray.h"

using namespace std;

class EwkSet
{
 public:

 // Electroweak parameters
 double WMS = 80.39, ZMS = 91.187, ALFE = 7.297353E-3;
 double GMU = 1.16637e-5;
 double SW2_EFF_MZ = 0.23143;
 double SWG2 = 0.23143;
 double ALFA_EM_MZ = 1.0 / 128.937;
 double ALFA_EM_ME = 1.0 / 137.0359895;
 double Pi = 3.1415926535898;

 FortranArray1D<double> AlfEW{1, 4};
 int NSP = 2, NGN = 3, NBN = 4, NPOL = 3;
 int NFL = 6;
 FortranArray2D<int> IP{1, NSP, 1, NGN};

 FortranArray2D<double> VKM{1, NGN, 1, NGN};

 double WCOUPL, ZCOUPL;

 FortranArray1D<double> LeptonCharge{1, 2};
 FortranArray1D<double> QuarkCharge{1, 2};
 FortranArray1D<double> T3{1, 2};
 FortranArray3D<double> GLV{1, NSP, 1, NBN, 1, NSP};
 FortranArray3D<double> GLA{1, NSP, 1, NBN, 1, NSP};
 FortranArray3D<double> GLL{1, NSP, 1, NBN, 1, NSP};
 FortranArray3D<double> GLR{1, NSP, 1, NBN, 1, NSP};
 FortranArray3D<double> GQV{1, NSP, 1, NBN, 1, NSP};
 FortranArray3D<double> GQA{1, NSP, 1, NBN, 1, NSP};
 FortranArray3D<double> GQL{1, NSP, 1, NBN, 1, NSP};
 FortranArray3D<double> GQR{1, NSP, 1, NBN, 1, NSP};
 FortranArray3D<double> HQV{1, NFL, 1, NBN, 1, NFL};
 FortranArray3D<double> HQA{1, NFL, 1, NBN, 1, NFL};
 FortranArray3D<double> HQL{1, NFL, 1, NBN, 1, NFL};
 FortranArray3D<double> HQR{1, NFL, 1, NBN, 1, NFL};

 FortranArray4D<double> GGQV{1, NSP, 1, NGN, 1, NSP, 1, NGN};
 FortranArray4D<double> GGQA{1, NSP, 1, NGN, 1, NSP, 1, NGN};
 FortranArray4D<double> GGQL{1, NSP, 1, NGN, 1, NSP, 1, NGN};
 FortranArray4D<double> GGQR{1, NSP, 1, NGN, 1, NSP, 1, NGN};

 EwkSet();
 virtual double AlfEwk(int iboson);
 virtual double vBnMas(int iboson);
 virtual double gEWlH(int it1, int ibs, int ibh, int it2);
 virtual double gEWqH(int iq1, int ibs, int ibh, int iq2);
 virtual double gEWqT(int iq1, int ibs, int ibt, int iq2);

 FortranArray3D<double> cplanh{-6, 6, 1, NBN, -6, 6};
 FortranArray2D<double> cplsct{-6, 6, 1, NBN};

 bool isSetEWcpl2 = false;
 virtual void SetEWcpl2();
 virtual double EwCpl2An(int jp1, int jbn, int jp2);
 virtual double EwCpl2Cn(int jp, int jbn);

};
#endif
