#ifndef Calculation_mDisPac_h
#define Calculation_mDisPac_h

#include "RootCommon.h"

#include "Calculation/EwkSet.h"
#include "Calculation/QCDSet.h"

using namespace std;

class mDisPac : public EwkSet, public QCDSet
{
 public:

 bool DisSet = false;
 double CF = 4.0 / 3.0, CG = 3.0, TR = 0.5, Pi = 3.141592653589793238462643383279502884197, Tf = 0.5;
 double CA = 3.0;
 double XsGv2pb = 0.389379323 * 1e9;
 double Gf = 1.16637 * 1e-5;
 double aErr = 1e-16, rErr = 1e-6;

 FortranArray2D<int> iBsn{1, 2, -1, 5};      // Structure Function level: Virtual Forward Compton Amplitude 
                                             // incoming Boson=iBsn(1) and outgoing boson=iBsn(2);
                                             // iBsn = 1/2/3/4/  for photon/W+/W-/Z;
                  // iCmptn = 1/2/3/4 for the diagonal processes; and 5 for photon-Z interference
                  //          in addition, -1, 0 for W+ -/+ W- .

 FortranArray1D<double> g2Bn{-1, 5};
 FortranArray2D<double> g2Lp{-2, 2, 1, 5};
 FortranArray2D<double> g2Lm{-2, 2, 1, 5};
 FortranArray3D<double> g2p{-6, 6, 1, 5, -6, 6};       // parity conserving combination   g_V g_V+g_A g_A=g_L g_L + g_R g_R
 FortranArray3D<double> g2m{-6, 6, 1, 5, -6, 6};       // parity violating  combination   g_V g_A+g_A g_V=g_L g_L - g_R g_R
 FortranArray3D<double> g2x{-6, 6, 1, 5, -6, 6};       // chirality violating combination g_V g_V-g_A g_A=g_L g_R + g_R g_L
 FortranArray4D<double> g2q{0, 3, -6, 6, -1, 5, -6, 6};  // All above combined; 0th element = Sum Abs
 FortranArray3D<double> g2Qpc{-6, 6, 1, 5, 1, 6};     // Accumulated parity conserving combination for quark partons
 FortranArray3D<double> g2Qpv{-6, 6, 1, 5, 1, 6};     // Accumulated parity violating  combination for quark partons
 FortranArray3D<double> g2Gpc{1, 6, 1, 5, 1, 6};     // Accumulated parity conserving combination for gluon parton
 FortranArray3D<double> g2Gpv{1, 6, 1, 5, 1, 6};     // Accumulated parity violating  combination for gluon parton

 FortranArray1D<double> AA{1, 3};
 FortranArray1D<double> AB{-1, 1};


 mDisPac();
 virtual void mSetDis();

 // QCD

 // Electroweak parameters
};
#endif
