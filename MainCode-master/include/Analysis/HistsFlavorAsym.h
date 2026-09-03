#ifndef __HistsFlavorAsym_H_
#define __HistsFlavorAsym_H_
#include <iostream>
#include "TH1D.h"
#include "TH2D.h"
#include "TH3D.h"
#include "TH2F.h"
#include "TH3F.h"
#include "TFile.h"
#include "TProfile.h"
#include "TProfile2D.h"
#include "TMath.h"
#include "TTree.h"
#include <vector>
#include "Analysis/makeHists.h"

using namespace std;

class HistsFlavorAsym : public makeHists
{
 public:

 ThreadHist<TH1D *>* ZRapidity;
 ThreadHist<TH1D *>* ChangePDF_ZRapidity;

 //Forward and backward vs Mass ZY QT
 ThreadHist<TH3D *>* FZMass_ZY_QT;
 ThreadHist<TH3D *>* BZMass_ZY_QT;

 //ZMass ZY QT 3D plot
 ThreadHist<TH3D *>* ZMass_ZY_QT;
 ThreadHist<TH3D *>* ChangePDF_ZMass_ZY_QT;
 ThreadHist<TH3D *>* FZMass_ZY_QT_uu;
 ThreadHist<TH3D *>* BZMass_ZY_QT_uu;
 ThreadHist<TH3D *>* FZMass_ZY_QT_dd;
 ThreadHist<TH3D *>* BZMass_ZY_QT_dd;
 ThreadHist<TH3D *>* ChangePDF_FZMass_ZY_QT_uu;
 ThreadHist<TH3D *>* ChangePDF_BZMass_ZY_QT_uu;
 ThreadHist<TH3D *>* ChangePDF_FZMass_ZY_QT_dd;
 ThreadHist<TH3D *>* ChangePDF_BZMass_ZY_QT_dd;
 ThreadHist<TH3D *>* ZMass_ZY_QT_uu;
 ThreadHist<TH3D *>* ZMass_ZY_QT_dd;
 ThreadHist<TH3D *>* ZMass_ZY_QT_ss;
 ThreadHist<TH3D *>* ZMass_ZY_QT_cc;
 ThreadHist<TH3D *>* ZMass_ZY_QT_bb;

 /////////////////////
 //  dilution plot  //
 /////////////////////

 ThreadHist<TH3D *>* ZMass_ZY_QT_uu_wrong;
 ThreadHist<TH3D *>* ZMass_ZY_QT_uu_total;
 TH3D *Dilution_ZMass_ZY_QT_uu;

 ThreadHist<TH3D *>* ZMass_ZY_QT_dd_wrong;
 ThreadHist<TH3D *>* ZMass_ZY_QT_dd_total;
 TH3D *Dilution_ZMass_ZY_QT_dd;

 ThreadHist<TH3D *>* ChangePDF_ZMass_ZY_QT_uu_wrong;
 ThreadHist<TH3D *>* ChangePDF_ZMass_ZY_QT_uu_total;
 TH3D *Dilution_ChangePDF_ZMass_ZY_QT_uu;

 ThreadHist<TH3D *>* ChangePDF_ZMass_ZY_QT_dd_wrong;
 ThreadHist<TH3D *>* ChangePDF_ZMass_ZY_QT_dd_total;
 TH3D *Dilution_ChangePDF_ZMass_ZY_QT_dd;

 ThreadHist<AngularFunction* >* A0_Mass_ZY_QT_uu;
 ThreadHist<AngularFunction* >* A0_Mass_ZY_QT_dd;
 ThreadHist<AngularFunction* >* A0_Mass_ZY_QT_ss;
 ThreadHist<AngularFunction* >* A0_Mass_ZY_QT_cc;
 ThreadHist<AngularFunction* >* A0_Mass_ZY_QT_bb;

 TH3D *AFB_Mass_ZY_ZPt;

 TH3D *AFB_Mass_ZY_ZPt_uu;
 TH3D *AFB_Mass_ZY_ZPt_dd;
 TH3D *CoefficientDilution_ZMass_ZY_QT_uu;
 TH3D *CoefficientDilution_ZMass_ZY_QT_dd;
 TH3D *ResidualDilution_ZMass_ZY_QT_uu;
 TH3D *ResidualDilution_ZMass_ZY_QT_dd;
 TH3D *DilutionAverage_ZMass_ZY_QT_uu;
 TH3D *DilutionAverage_ZMass_ZY_QT_dd;

 TH3D *AFB_ChangePDF_Mass_ZY_ZPt_uu;
 TH3D *AFB_ChangePDF_Mass_ZY_ZPt_dd;
 TH3D *CoefficientDilution_ChangePDF_ZMass_ZY_QT_uu;
 TH3D *CoefficientDilution_ChangePDF_ZMass_ZY_QT_dd;
 TH3D *ResidualDilution_ChangePDF_ZMass_ZY_QT_uu;
 TH3D *ResidualDilution_ChangePDF_ZMass_ZY_QT_dd;
 TH3D *DilutionAverage_ChangePDF_ZMass_ZY_QT_uu;
 TH3D *DilutionAverage_ChangePDF_ZMass_ZY_QT_dd;

////////////////////////////////////////////////////////////////////////////

 ThreadHist<TH1D *>* ZY_ssbar;
 ThreadHist<TH1D *>* ZY_sbars;

 ThreadHist<TH1D *>* ZPositiveLeptonEta_uu;
 ThreadHist<TH1D *>* ZNegativeLeptonEta_uu;
 ThreadHist<TH1D *>* ZPositiveLeptonEta_dd;
 ThreadHist<TH1D *>* ZNegativeLeptonEta_dd;
 ThreadHist<TH1D *>* ZPositiveLeptonEta_ss;
 ThreadHist<TH1D *>* ZNegativeLeptonEta_ss;

 ThreadHist<TH1D *>* ZMass_ForwardEtaPlus;
 ThreadHist<TH1D *>* ZMass_CentralEtaPlus;
 ThreadHist<TH1D *>* ZMass_ForwardEtaMinus;
 ThreadHist<TH1D *>* ZMass_CentralEtaMinus;

 ThreadHist<TH1D *>* ZMass_ForwardEtaPlus_uu;
 ThreadHist<TH1D *>* ZMass_CentralEtaPlus_uu;
 ThreadHist<TH1D *>* ZMass_ForwardEtaMinus_uu;
 ThreadHist<TH1D *>* ZMass_CentralEtaMinus_uu;

 ThreadHist<TH1D *>* ZMass_ForwardEtaPlus_dd;
 ThreadHist<TH1D *>* ZMass_CentralEtaPlus_dd;
 ThreadHist<TH1D *>* ZMass_ForwardEtaMinus_dd;
 ThreadHist<TH1D *>* ZMass_CentralEtaMinus_dd;

 ThreadHist<TH1D *>* ZMass_ForwardEtaPlus_ss;
 ThreadHist<TH1D *>* ZMass_CentralEtaPlus_ss;
 ThreadHist<TH1D *>* ZMass_ForwardEtaMinus_ss;
 ThreadHist<TH1D *>* ZMass_CentralEtaMinus_ss;

 ThreadHist<TH1D *>* ZMass_ForwardEtaPlus_other;
 ThreadHist<TH1D *>* ZMass_CentralEtaPlus_other;
 ThreadHist<TH1D *>* ZMass_ForwardEtaMinus_other;
 ThreadHist<TH1D *>* ZMass_CentralEtaMinus_other;

 ThreadHist<TH1D *>* ZMass_uu;
 ThreadHist<TH1D *>* ZMass_dd;
 ThreadHist<TH1D *>* ZMass_ss;
 ThreadHist<TH1D *>* ZMass_other;
 ThreadHist<TH1D *>* ZMass_total;

 ThreadHist<TH1D *>* ZMassAddEta;

 TH1D* PositiveAFC;
 TH1D* NegativeAFC;

 TH1D* PositiveAFC_uu;
 TH1D* NegativeAFC_uu;

 TH1D* PositiveAFC_dd;
 TH1D* NegativeAFC_dd;

 TH1D* PositiveAFC_ss;
 TH1D* NegativeAFC_ss;

 TH1D* PositiveAFC_other;
 TH1D* NegativeAFC_other;

 TH1D* RelativeXsec_uu;
 TH1D* RelativeXsec_dd;
 TH1D* RelativeXsec_ss;
 TH1D* RelativeXsec_other;

 TH1D* PositiveAFC_uu_Average;
 TH1D* NegativeAFC_uu_Average;
 TH1D* PositiveAFC_uu_Residual;
 TH1D* NegativeAFC_uu_Residual;

 TH1D* PositiveAFC_dd_Average;
 TH1D* NegativeAFC_dd_Average;
 TH1D* PositiveAFC_dd_Residual;
 TH1D* NegativeAFC_dd_Residual;

 TH1D* PositiveAFC_ss_Average;
 TH1D* NegativeAFC_ss_Average;
 TH1D* PositiveAFC_ss_Residual;
 TH1D* NegativeAFC_ss_Residual;

 TH1D* AFCDiff;
 TH1D* AFCDiff_uu;
 TH1D* AFCDiff_dd;
 TH1D* AFCDiff_ss;

 TH1D* AFCDiff_uu_Average;
 TH1D* AFCDiff_dd_Average;
 TH1D* AFCDiff_ss_Average;
 TH1D* AFCDiff_uu_Residual;
 TH1D* AFCDiff_dd_Residual;
 TH1D* AFCDiff_ss_Residual;


   /*************************/
   /*  W related histogram  */
   /*************************/

 ThreadHist<TH1D *>* WY_udbar;
 ThreadHist<TH1D *>* WY_usbar;
 ThreadHist<TH1D *>* WY_ubbar;
 ThreadHist<TH1D *>* WY_cdbar;
 ThreadHist<TH1D *>* WY_csbar;
 ThreadHist<TH1D *>* WY_cbbar;
 ThreadHist<TH1D *>* WY_dbaru;
 ThreadHist<TH1D *>* WY_sbaru;
 ThreadHist<TH1D *>* WY_bbaru;
 ThreadHist<TH1D *>* WY_dbarc;
 ThreadHist<TH1D *>* WY_sbarc;
 ThreadHist<TH1D *>* WY_bbarc;
 ThreadHist<TH1D *>* WY_dubar;
 ThreadHist<TH1D *>* WY_subar;
 ThreadHist<TH1D *>* WY_bubar;
 ThreadHist<TH1D *>* WY_dcbar;
 ThreadHist<TH1D *>* WY_scbar;
 ThreadHist<TH1D *>* WY_bcbar;
 ThreadHist<TH1D *>* WY_ubard;
 ThreadHist<TH1D *>* WY_ubars;
 ThreadHist<TH1D *>* WY_ubarb;
 ThreadHist<TH1D *>* WY_cbard;
 ThreadHist<TH1D *>* WY_cbars;
 ThreadHist<TH1D *>* WY_cbarb;

 ThreadHist<TH1D *>* LeptonPt;
 ThreadHist<TH1D *>* LeptonPt_WMinus;
 ThreadHist<TH1D *>* LeptonPt_d;
 ThreadHist<TH1D *>* LeptonPt_s;
 ThreadHist<TH1D *>* LeptonPt_udbar;
 ThreadHist<TH1D *>* LeptonPt_usbar;
 ThreadHist<TH1D *>* LeptonPt_ubbar;
 ThreadHist<TH1D *>* LeptonPt_cdbar;
 ThreadHist<TH1D *>* LeptonPt_csbar;
 ThreadHist<TH1D *>* LeptonPt_cbbar;
 ThreadHist<TH1D *>* LeptonPt_dbaru;
 ThreadHist<TH1D *>* LeptonPt_sbaru;
 ThreadHist<TH1D *>* LeptonPt_bbaru;
 ThreadHist<TH1D *>* LeptonPt_dbarc;
 ThreadHist<TH1D *>* LeptonPt_sbarc;
 ThreadHist<TH1D *>* LeptonPt_bbarc;
 ThreadHist<TH1D *>* LeptonPt_dubar;
 ThreadHist<TH1D *>* LeptonPt_subar;
 ThreadHist<TH1D *>* LeptonPt_bubar;
 ThreadHist<TH1D *>* LeptonPt_dcbar;
 ThreadHist<TH1D *>* LeptonPt_scbar;
 ThreadHist<TH1D *>* LeptonPt_bcbar;
 ThreadHist<TH1D *>* LeptonPt_ubard;
 ThreadHist<TH1D *>* LeptonPt_ubars;
 ThreadHist<TH1D *>* LeptonPt_ubarb;
 ThreadHist<TH1D *>* LeptonPt_cbard;
 ThreadHist<TH1D *>* LeptonPt_cbars;
 ThreadHist<TH1D *>* LeptonPt_cbarb;

 ThreadHist<TH1D *>* PositiveLeptonEta_udbar;
 ThreadHist<TH1D *>* PositiveLeptonEta_csbar;
 ThreadHist<TH1D *>* PositiveLeptonEta_dbaru;
 ThreadHist<TH1D *>* PositiveLeptonEta_sbarc;
 ThreadHist<TH1D *>* PositiveLeptonEta_other;

 ThreadHist<TH1D *>* PositiveLeptonEta_ud;
 ThreadHist<TH1D *>* PositiveLeptonEta_cs;

 ThreadHist<TH1D *>* NegativeLeptonEta_dubar;
 ThreadHist<TH1D *>* NegativeLeptonEta_scbar;
 ThreadHist<TH1D *>* NegativeLeptonEta_ubard;
 ThreadHist<TH1D *>* NegativeLeptonEta_cbars;
 ThreadHist<TH1D *>* NegativeLeptonEta_other;

 ThreadHist<TH1D *>* NegativeLeptonEta_ud;
 ThreadHist<TH1D *>* NegativeLeptonEta_cs;

 ThreadHist<TH2D *>* PositiveLeptonEtaMT_udbar;
 ThreadHist<TH2D *>* PositiveLeptonEtaMT_csbar;
 ThreadHist<TH2D *>* PositiveLeptonEtaMT_dbaru;
 ThreadHist<TH2D *>* PositiveLeptonEtaMT_sbarc;
 ThreadHist<TH2D *>* PositiveLeptonEtaMT_other;

 ThreadHist<TH2D *>* PositiveLeptonEtaMT_ud;
 ThreadHist<TH2D *>* PositiveLeptonEtaMT_cs;

 ThreadHist<TH2D *>* NegativeLeptonEtaMT_dubar;
 ThreadHist<TH2D *>* NegativeLeptonEtaMT_scbar;
 ThreadHist<TH2D *>* NegativeLeptonEtaMT_ubard;
 ThreadHist<TH2D *>* NegativeLeptonEtaMT_cbars;
 ThreadHist<TH2D *>* NegativeLeptonEtaMT_other;

 ThreadHist<TH2D *>* NegativeLeptonEtaMT_ud;
 ThreadHist<TH2D *>* NegativeLeptonEtaMT_cs;


 ThreadHist<TH1D *>* PositiveNeutrinoEta_udbar;
 ThreadHist<TH1D *>* PositiveNeutrinoEta_csbar;
 ThreadHist<TH1D *>* PositiveNeutrinoEta_dbaru;
 ThreadHist<TH1D *>* PositiveNeutrinoEta_sbarc;
 ThreadHist<TH1D *>* PositiveNeutrinoEta_other;

 ThreadHist<TH1D *>* PositiveNeutrinoEta_ud;
 ThreadHist<TH1D *>* PositiveNeutrinoEta_cs;

 ThreadHist<TH1D *>* NegativeNeutrinoEta_dubar;
 ThreadHist<TH1D *>* NegativeNeutrinoEta_scbar;
 ThreadHist<TH1D *>* NegativeNeutrinoEta_ubard;
 ThreadHist<TH1D *>* NegativeNeutrinoEta_cbars;
 ThreadHist<TH1D *>* NegativeNeutrinoEta_other;

 ThreadHist<TH1D *>* NegativeNeutrinoEta_ud;
 ThreadHist<TH1D *>* NegativeNeutrinoEta_cs;

 ThreadHist<TH2D *>* PositiveNeutrinoEtaMT_udbar;
 ThreadHist<TH2D *>* PositiveNeutrinoEtaMT_csbar;
 ThreadHist<TH2D *>* PositiveNeutrinoEtaMT_dbaru;
 ThreadHist<TH2D *>* PositiveNeutrinoEtaMT_sbarc;
 ThreadHist<TH2D *>* PositiveNeutrinoEtaMT_other;

 ThreadHist<TH2D *>* PositiveNeutrinoEtaMT_ud;
 ThreadHist<TH2D *>* PositiveNeutrinoEtaMT_cs;

 ThreadHist<TH2D *>* NegativeNeutrinoEtaMT_dubar;
 ThreadHist<TH2D *>* NegativeNeutrinoEtaMT_scbar;
 ThreadHist<TH2D *>* NegativeNeutrinoEtaMT_ubard;
 ThreadHist<TH2D *>* NegativeNeutrinoEtaMT_cbars;
 ThreadHist<TH2D *>* NegativeNeutrinoEtaMT_other;

 ThreadHist<TH2D *>* NegativeNeutrinoEtaMT_ud;
 ThreadHist<TH2D *>* NegativeNeutrinoEtaMT_cs;

 ThreadHist<TH1D *>* WPlusForwardMT_quark;
 ThreadHist<TH1D *>* WPlusBackwardMT_quark;
 ThreadHist<TH1D *>* WMinusForwardMT_quark;
 ThreadHist<TH1D *>* WMinusBackwardMT_quark;

 ThreadHist<TH1D *>* WPlusMT_CentralEta;
 ThreadHist<TH1D *>* WPlusMT_ForwardEta;
 ThreadHist<TH1D *>* WMinusMT_CentralEta;
 ThreadHist<TH1D *>* WMinusMT_ForwardEta;

 ThreadHist<TH1D *>* WPlusMT_CentralEta_ud;
 ThreadHist<TH1D *>* WPlusMT_ForwardEta_ud;
 ThreadHist<TH1D *>* WMinusMT_CentralEta_ud;
 ThreadHist<TH1D *>* WMinusMT_ForwardEta_ud;

 ThreadHist<TH1D *>* WPlusMT_CentralEta_cs;
 ThreadHist<TH1D *>* WPlusMT_ForwardEta_cs;
 ThreadHist<TH1D *>* WMinusMT_CentralEta_cs;
 ThreadHist<TH1D *>* WMinusMT_ForwardEta_cs;

 ThreadHist<TH1D *>* WPlusMT_CentralEta_other;
 ThreadHist<TH1D *>* WPlusMT_ForwardEta_other;
 ThreadHist<TH1D *>* WMinusMT_CentralEta_other;
 ThreadHist<TH1D *>* WMinusMT_ForwardEta_other;

 ThreadHist<TH1D *>* WPlusMT_ud;
 ThreadHist<TH1D *>* WMinusMT_ud;

 ThreadHist<TH1D *>* WPlusMT_cs;
 ThreadHist<TH1D *>* WMinusMT_cs;

 ThreadHist<TH1D *>* WPlusMT_other;
 ThreadHist<TH1D *>* WMinusMT_other;

 ThreadHist<TH1D *>* WPlusMT_total;
 ThreadHist<TH1D *>* WMinusMT_total;

 ThreadHist<TH1D *>* WY_udbar_total;
 ThreadHist<TH1D *>* WY_csbar_total;
 ThreadHist<TH1D *>* WY_dubar_total;
 ThreadHist<TH1D *>* WY_scbar_total;

 ThreadHist<TH1D *>* WPlusY;
 ThreadHist<TH1D *>* WMinusY;
 ThreadHist<TH1D *>* LeptonEta;
 ThreadHist<TH1D *>* AntiLeptonEta;
 ThreadHist<TH1D *>* ChangePDF_LeptonEta;
 ThreadHist<TH1D *>* ChangePDF_AntiLeptonEta;

//W+/W- A4(AFB)
 ThreadHist<TH1D *>* FWPlusY;
 ThreadHist<TH1D *>* BWPlusY;
 ThreadHist<TH1D *>* FWMinusY;
 ThreadHist<TH1D *>* BWMinusY;

 ThreadHist<TH1D *>* FWPlusY_reco_80385;
 ThreadHist<TH1D *>* BWPlusY_reco_80385;
 ThreadHist<TH1D *>* FWMinusY_reco_80385;
 ThreadHist<TH1D *>* BWMinusY_reco_80385;

 ThreadHist<TH1D *>* FWPlusY_reco_80395;
 ThreadHist<TH1D *>* BWPlusY_reco_80395;
 ThreadHist<TH1D *>* FWMinusY_reco_80395;
 ThreadHist<TH1D *>* BWMinusY_reco_80395;

 ThreadHist<TH1D *>* FWPlusY_reco_80375;
 ThreadHist<TH1D *>* BWPlusY_reco_80375;
 ThreadHist<TH1D *>* FWMinusY_reco_80375;
 ThreadHist<TH1D *>* BWMinusY_reco_80375;

 ThreadHist<TH1D *>* FWPlusMass;
 ThreadHist<TH1D *>* BWPlusMass;
 ThreadHist<TH1D *>* FWMinusMass;
 ThreadHist<TH1D *>* BWMinusMass;

 ThreadHist<TH1D *>* WPlusY_wrong;
 ThreadHist<TH1D *>* WPlusY_total;
 TH1D *Dilution_WPlusY;
 TH1D *CoefficientDilution_WPlusY;

 ThreadHist<TH1D *>* WMinusY_wrong;
 ThreadHist<TH1D *>* WMinusY_total;
 TH1D *Dilution_WMinusY;
 TH1D *CoefficientDilution_WMinusY;

 TH1D* AFB_WPlusY;
 TH1D* AFB_WMinusY;
 TH1D* AFB_WPlusY_reco_80385;
 TH1D* AFB_WMinusY_reco_80385;
 TH1D* AFB_WPlusY_reco_80395;
 TH1D* AFB_WMinusY_reco_80395;
 TH1D* AFB_WPlusY_reco_80375;
 TH1D* AFB_WMinusY_reco_80375;
 TH1D* AFB_WPlusMass;
 TH1D* AFB_WMinusMass;
 TH1D* OriginAFB_WPlusY;
 TH1D* OriginAFB_WMinusY;

 TH1D* Wasymmetry;
 TH1D* ChangePDF_Wasymmetry;

 TH1D* WPlusAFB_quark;
 TH1D* WMinusAFB_quark;

 TH1D* WPlusAFC_MT;
 TH1D* WMinusAFC_MT;
 TH1D* WPlusAFC_MT_ud;
 TH1D* WMinusAFC_MT_ud;
 TH1D* WPlusAFC_MT_cs;
 TH1D* WMinusAFC_MT_cs;
 TH1D* WPlusAFC_MT_other;
 TH1D* WMinusAFC_MT_other;

 TH1D* WPlusAFC_MT_ud_Residual;
 TH1D* WMinusAFC_MT_ud_Residual;
 TH1D* WPlusAFC_MT_cs_Residual;
 TH1D* WMinusAFC_MT_cs_Residual;

 TH1D* WPlusAFC_MT_ud_Average;
 TH1D* WMinusAFC_MT_ud_Average;
 TH1D* WPlusAFC_MT_cs_Average;
 TH1D* WMinusAFC_MT_cs_Average;

 TH1D* WPlusRelativeXsec_MT_ud;
 TH1D* WMinusRelativeXsec_MT_ud;
 TH1D* WPlusRelativeXsec_MT_cs;
 TH1D* WMinusRelativeXsec_MT_cs;
 TH1D* WPlusRelativeXsec_MT_other;
 TH1D* WMinusRelativeXsec_MT_other;


//member function
 vector<TString> sysName;
 HistsFlavorAsym(){};
 HistsFlavorAsym(TString RootType){this->RootType = RootType;};
 virtual void InitialSysName();
 virtual void bookHists(int TotalThread);
 virtual void outputInformation();
 virtual void Save();
 virtual void Reset();

// template<class T>

};
#endif
