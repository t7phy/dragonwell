#include "Analysis/HistsFlavorAsym.h"

using namespace std;

void HistsFlavorAsym::bookHists(int TotalThread)
{
// int CMS_mass_bin = 14;
// double RangeCMSMass[15] = {40.0, 50.0, 60.0, 76.0, 86.0, 96.0, 106.0, 120.0, 133.0, 150.0, 171.0, 200.0, 320.0, 500.0, 2000.0};
// int CMS_mass_bin = 7;
// double RangeCMSMass[8] = {60.0, 76.0, 86.0, 96.0, 106.0, 120.0, 133.0, 150.0};
 int CMS_mass_bin = 35;
 double RangeCMSMass[36] = {60.0, 62.0, 64.0, 66.0, 68.0, 70.0, 72.0, 74.0, 76.0, 78.0, 80.0, 82.0, 84.0, 86.0, 88.0, 90.0,
                           92.0, 94.0, 96.0, 98.0, 100.0, 102.0, 104.0, 106.0, 108.0, 110.0, 112.0, 114.0, 116.0, 118.0, 120.0,
                           122.0, 124.0, 126.0, 128.0, 130.0};

 int CMS_ZPt_bin = 1;
 double RangeCMSZPt[2] = {0.0, 10000.0};
// int CMS_ZPt_Fine_bin = 17;
// double RangeCMSFineZPt[18] = {0.0, 5.0, 10.0, 15.0, 20.0, 25.0, 30.0, 35.0, 40.0, 45.0, 50.0, 60.0, 80.0, 100.0, 300.0, 500.0, 1000.0, 10000.0};
 int CMS_ZPt_Fine_bin = 1;
 double RangeCMSFineZPt[17] = {0.0, 10000.0};

// int CMS_ZY_bin = 4;
// double RangeCMSZY[5] = {0.0, 1.0, 1.25, 1.5, 2.4};
 int CMS_ZY_bin = 1;
 double RangeCMSZY[2] = {2.2, 2.5};

 this->TotalThread = TotalThread;

 BookHist(ZRapidity, "ZRapidity", "ZRapidity", 20, -5, 5);
 BookHist(ChangePDF_ZRapidity, "ChangePDF_ZRapidity", "ChangePDF_ZRapidity", 20, -5, 5);

 Book3DHist(FZMass_ZY_QT, "FZMass_ZY_QT", "FZMass_ZY_QT", CMS_mass_bin, RangeCMSMass, CMS_ZY_bin, RangeCMSZY, CMS_ZPt_bin, RangeCMSZPt);
 Book3DHist(BZMass_ZY_QT, "BZMass_ZY_QT", "BZMass_ZY_QT", CMS_mass_bin, RangeCMSMass, CMS_ZY_bin, RangeCMSZY, CMS_ZPt_bin, RangeCMSZPt);

 Book3DHist(ZMass_ZY_QT, "ZMass_ZY_QT", "ZMass_ZY_QT", CMS_mass_bin, RangeCMSMass, CMS_ZY_bin, RangeCMSZY, CMS_ZPt_Fine_bin, RangeCMSFineZPt);
 Book3DHist(ChangePDF_ZMass_ZY_QT, "ChangePDF_ZMass_ZY_QT", "ChangePDF_ZMass_ZY_QT", CMS_mass_bin, RangeCMSMass, CMS_ZY_bin, RangeCMSZY, CMS_ZPt_Fine_bin, RangeCMSFineZPt);

 Book3DHist(FZMass_ZY_QT_uu, "FZMass_ZY_QT_uu", "FZMass_ZY_QT_uu", CMS_mass_bin, RangeCMSMass, CMS_ZY_bin, RangeCMSZY, CMS_ZPt_Fine_bin, RangeCMSFineZPt);
 Book3DHist(BZMass_ZY_QT_uu, "BZMass_ZY_QT_uu", "BZMass_ZY_QT_uu", CMS_mass_bin, RangeCMSMass, CMS_ZY_bin, RangeCMSZY, CMS_ZPt_Fine_bin, RangeCMSFineZPt);
 Book3DHist(FZMass_ZY_QT_dd, "FZMass_ZY_QT_dd", "FZMass_ZY_QT_dd", CMS_mass_bin, RangeCMSMass, CMS_ZY_bin, RangeCMSZY, CMS_ZPt_Fine_bin, RangeCMSFineZPt);
 Book3DHist(BZMass_ZY_QT_dd, "BZMass_ZY_QT_dd", "BZMass_ZY_QT_dd", CMS_mass_bin, RangeCMSMass, CMS_ZY_bin, RangeCMSZY, CMS_ZPt_Fine_bin, RangeCMSFineZPt);

 Book3DHist(ChangePDF_FZMass_ZY_QT_uu, "ChangePDF_FZMass_ZY_QT_uu", "ChangePDF_FZMass_ZY_QT_uu", CMS_mass_bin, RangeCMSMass, CMS_ZY_bin, RangeCMSZY, CMS_ZPt_Fine_bin, RangeCMSFineZPt);
 Book3DHist(ChangePDF_BZMass_ZY_QT_uu, "ChangePDF_BZMass_ZY_QT_uu", "ChangePDF_BZMass_ZY_QT_uu", CMS_mass_bin, RangeCMSMass, CMS_ZY_bin, RangeCMSZY, CMS_ZPt_Fine_bin, RangeCMSFineZPt);
 Book3DHist(ChangePDF_FZMass_ZY_QT_dd, "ChangePDF_FZMass_ZY_QT_dd", "ChangePDF_FZMass_ZY_QT_dd", CMS_mass_bin, RangeCMSMass, CMS_ZY_bin, RangeCMSZY, CMS_ZPt_Fine_bin, RangeCMSFineZPt);
 Book3DHist(ChangePDF_BZMass_ZY_QT_dd, "ChangePDF_BZMass_ZY_QT_dd", "ChangePDF_BZMass_ZY_QT_dd", CMS_mass_bin, RangeCMSMass, CMS_ZY_bin, RangeCMSZY, CMS_ZPt_Fine_bin, RangeCMSFineZPt);


 Book3DHist(ZMass_ZY_QT_uu, "ZMass_ZY_QT_uu", "ZMass_ZY_QT_uu", CMS_mass_bin, RangeCMSMass, CMS_ZY_bin, RangeCMSZY, CMS_ZPt_Fine_bin, RangeCMSFineZPt);
 Book3DHist(ZMass_ZY_QT_dd, "ZMass_ZY_QT_dd", "ZMass_ZY_QT_dd", CMS_mass_bin, RangeCMSMass, CMS_ZY_bin, RangeCMSZY, CMS_ZPt_Fine_bin, RangeCMSFineZPt);
 Book3DHist(ZMass_ZY_QT_ss, "ZMass_ZY_QT_ss", "ZMass_ZY_QT_ss", CMS_mass_bin, RangeCMSMass, CMS_ZY_bin, RangeCMSZY, CMS_ZPt_Fine_bin, RangeCMSFineZPt);
 Book3DHist(ZMass_ZY_QT_cc, "ZMass_ZY_QT_cc", "ZMass_ZY_QT_cc", CMS_mass_bin, RangeCMSMass, CMS_ZY_bin, RangeCMSZY, CMS_ZPt_Fine_bin, RangeCMSFineZPt);
 Book3DHist(ZMass_ZY_QT_bb, "ZMass_ZY_QT_bb", "ZMass_ZY_QT_bb", CMS_mass_bin, RangeCMSMass, CMS_ZY_bin, RangeCMSZY, CMS_ZPt_Fine_bin, RangeCMSFineZPt);

 Book3DHist(ZMass_ZY_QT_uu_total, "ZMass_ZY_QT_uu_total", "ZMass_ZY_QT_uu_total", CMS_mass_bin, RangeCMSMass, CMS_ZY_bin, RangeCMSZY, CMS_ZPt_Fine_bin, RangeCMSFineZPt);
 Book3DHist(ZMass_ZY_QT_uu_wrong, "ZMass_ZY_QT_uu_wrong", "ZMass_ZY_QT_uu_wrong", CMS_mass_bin, RangeCMSMass, CMS_ZY_bin, RangeCMSZY, CMS_ZPt_Fine_bin, RangeCMSFineZPt);
 Book3DHist(ZMass_ZY_QT_dd_total, "ZMass_ZY_QT_dd_total", "ZMass_ZY_QT_dd_total", CMS_mass_bin, RangeCMSMass, CMS_ZY_bin, RangeCMSZY, CMS_ZPt_Fine_bin, RangeCMSFineZPt);
 Book3DHist(ZMass_ZY_QT_dd_wrong, "ZMass_ZY_QT_dd_wrong", "ZMass_ZY_QT_dd_wrong", CMS_mass_bin, RangeCMSMass, CMS_ZY_bin, RangeCMSZY, CMS_ZPt_Fine_bin, RangeCMSFineZPt);

 Book3DHist(ChangePDF_ZMass_ZY_QT_uu_total, "ChangePDF_ZMass_ZY_QT_uu_total", "ChangePDF_ZMass_ZY_QT_uu_total", CMS_mass_bin, RangeCMSMass, CMS_ZY_bin, RangeCMSZY, CMS_ZPt_Fine_bin, RangeCMSFineZPt);
 Book3DHist(ChangePDF_ZMass_ZY_QT_uu_wrong, "ChangePDF_ZMass_ZY_QT_uu_wrong", "ChangePDF_ZMass_ZY_QT_uu_wrong", CMS_mass_bin, RangeCMSMass, CMS_ZY_bin, RangeCMSZY, CMS_ZPt_Fine_bin, RangeCMSFineZPt);
 Book3DHist(ChangePDF_ZMass_ZY_QT_dd_total, "ChangePDF_ZMass_ZY_QT_dd_total", "ChangePDF_ZMass_ZY_QT_dd_total", CMS_mass_bin, RangeCMSMass, CMS_ZY_bin, RangeCMSZY, CMS_ZPt_Fine_bin, RangeCMSFineZPt);
 Book3DHist(ChangePDF_ZMass_ZY_QT_dd_wrong, "ChangePDF_ZMass_ZY_QT_dd_wrong", "ChangePDF_ZMass_ZY_QT_dd_wrong", CMS_mass_bin, RangeCMSMass, CMS_ZY_bin, RangeCMSZY, CMS_ZPt_Fine_bin, RangeCMSFineZPt);

//////////////////////////////////////////////////////////////////////////////////////////////////////////

 BookHist(ZY_ssbar, "ZY_ssbar", "ZY_ssbar", 40, -5, 5);
 BookHist(ZY_sbars, "ZY_sbars", "ZY_sbars", 40, -5, 5);

 BookHist(ZPositiveLeptonEta_uu, "ZPositiveLeptonEta_uu", "ZPositiveLeptonEta_uu", 40, -5, 5);
 BookHist(ZNegativeLeptonEta_uu, "ZNegativeLeptonEta_uu", "ZNegativeLeptonEta_uu", 40, -5, 5);
 BookHist(ZPositiveLeptonEta_dd, "ZPositiveLeptonEta_dd", "ZPositiveLeptonEta_dd", 40, -5, 5);
 BookHist(ZNegativeLeptonEta_dd, "ZNegativeLeptonEta_dd", "ZNegativeLeptonEta_dd", 40, -5, 5);
 BookHist(ZPositiveLeptonEta_ss, "ZPositiveLeptonEta_ss", "ZPositiveLeptonEta_ss", 40, -5, 5);
 BookHist(ZNegativeLeptonEta_ss, "ZNegativeLeptonEta_ss", "ZNegativeLeptonEta_ss", 40, -5, 5);

 BookHist(ZMass_ForwardEtaPlus, "ZMass_ForwardEtaPlus", "ZMass_ForwardEtaPlus", 30, 60, 120);
 BookHist(ZMass_CentralEtaPlus, "ZMass_CentralEtaPlus", "ZMass_CentralEtaPlus", 30, 60, 120);
 BookHist(ZMass_ForwardEtaMinus, "ZMass_ForwardEtaMinus", "ZMass_ForwardEtaMinus", 30, 60, 120);
 BookHist(ZMass_CentralEtaMinus, "ZMass_CentralEtaMinus", "ZMass_CentralEtaMinus", 30, 60, 120);

 BookHist(ZMass_ForwardEtaPlus_uu, "ZMass_ForwardEtaPlus_uu", "ZMass_ForwardEtaPlus_uu", 30, 60, 120);
 BookHist(ZMass_CentralEtaPlus_uu, "ZMass_CentralEtaPlus_uu", "ZMass_CentralEtaPlus_uu", 30, 60, 120);
 BookHist(ZMass_ForwardEtaMinus_uu, "ZMass_ForwardEtaMinus_uu", "ZMass_ForwardEtaMinus_uu", 30, 60, 120);
 BookHist(ZMass_CentralEtaMinus_uu, "ZMass_CentralEtaMinus_uu", "ZMass_CentralEtaMinus_uu", 30, 60, 120);

 BookHist(ZMass_ForwardEtaPlus_dd, "ZMass_ForwardEtaPlus_dd", "ZMass_ForwardEtaPlus_dd", 30, 60, 120);
 BookHist(ZMass_CentralEtaPlus_dd, "ZMass_CentralEtaPlus_dd", "ZMass_CentralEtaPlus_dd", 30, 60, 120);
 BookHist(ZMass_ForwardEtaMinus_dd, "ZMass_ForwardEtaMinus_dd", "ZMass_ForwardEtaMinus_dd", 30, 60, 120);
 BookHist(ZMass_CentralEtaMinus_dd, "ZMass_CentralEtaMinus_dd", "ZMass_CentralEtaMinus_dd", 30, 60, 120);

 BookHist(ZMass_ForwardEtaPlus_ss, "ZMass_ForwardEtaPlus_ss", "ZMass_ForwardEtaPlus_ss", 30, 60, 120);
 BookHist(ZMass_CentralEtaPlus_ss, "ZMass_CentralEtaPlus_ss", "ZMass_CentralEtaPlus_ss", 30, 60, 120);
 BookHist(ZMass_ForwardEtaMinus_ss, "ZMass_ForwardEtaMinus_ss", "ZMass_ForwardEtaMinus_ss", 30, 60, 120);
 BookHist(ZMass_CentralEtaMinus_ss, "ZMass_CentralEtaMinus_ss", "ZMass_CentralEtaMinus_ss", 30, 60, 120);

 BookHist(ZMass_ForwardEtaPlus_other, "ZMass_ForwardEtaPlus_other", "ZMass_ForwardEtaPlus_other", 30, 60, 120);
 BookHist(ZMass_CentralEtaPlus_other, "ZMass_CentralEtaPlus_other", "ZMass_CentralEtaPlus_other", 30, 60, 120);
 BookHist(ZMass_ForwardEtaMinus_other, "ZMass_ForwardEtaMinus_other", "ZMass_ForwardEtaMinus_other", 30, 60, 120);
 BookHist(ZMass_CentralEtaMinus_other, "ZMass_CentralEtaMinus_other", "ZMass_CentralEtaMinus_other", 30, 60, 120);

 BookHist(ZMass_uu, "ZMass_uu", "ZMass_uu", 30, 60, 120);
 BookHist(ZMass_dd, "ZMass_dd", "ZMass_dd", 30, 60, 120);
 BookHist(ZMass_ss, "ZMass_ss", "ZMass_ss", 30, 60, 120);
 BookHist(ZMass_other, "ZMass_other", "ZMass_other", 30, 60, 120);
 BookHist(ZMass_total, "ZMass_total", "ZMass_total", 30, 60, 120);

 BookHist(ZMassAddEta, "ZMassAddEta", "ZMassAddEta", 80, 70, 400);

 /*************************/
 /*  W related histogram  */
 /*************************/
 BookHist(WY_udbar, "WY_udbar", "WY_udbar", 40, -5, 5);
 BookHist(WY_usbar, "WY_usbar", "WY_usbar", 40, -5, 5);
 BookHist(WY_ubbar, "WY_ubbar", "WY_ubbar", 40, -5, 5);
 BookHist(WY_cdbar, "WY_cdbar", "WY_cdbar", 40, -5, 5);
 BookHist(WY_csbar, "WY_csbar", "WY_csbar", 40, -5, 5);
 BookHist(WY_cbbar, "WY_cbbar", "WY_cbbar", 40, -5, 5);
 BookHist(WY_dbaru, "WY_dbaru", "WY_dbaru", 40, -5, 5);
 BookHist(WY_sbaru, "WY_sbaru", "WY_sbaru", 40, -5, 5);
 BookHist(WY_bbaru, "WY_bbaru", "WY_bbaru", 40, -5, 5);
 BookHist(WY_dbarc, "WY_dbarc", "WY_dbarc", 40, -5, 5);
 BookHist(WY_sbarc, "WY_sbarc", "WY_sbarc", 40, -5, 5);
 BookHist(WY_bbarc, "WY_bbarc", "WY_bbarc", 40, -5, 5);
 BookHist(WY_dubar, "WY_dubar", "WY_dubar", 40, -5, 5);
 BookHist(WY_subar, "WY_subar", "WY_subar", 40, -5, 5);
 BookHist(WY_bubar, "WY_bubar", "WY_bubar", 40, -5, 5);
 BookHist(WY_dcbar, "WY_dcbar", "WY_dcbar", 40, -5, 5);
 BookHist(WY_scbar, "WY_scbar", "WY_scbar", 40, -5, 5);
 BookHist(WY_bcbar, "WY_bcbar", "WY_bcbar", 40, -5, 5);
 BookHist(WY_ubard, "WY_ubard", "WY_ubard", 40, -5, 5);
 BookHist(WY_ubars, "WY_ubars", "WY_ubars", 40, -5, 5);
 BookHist(WY_ubarb, "WY_ubarb", "WY_ubarb", 40, -5, 5);
 BookHist(WY_cbard, "WY_cbard", "WY_cbard", 40, -5, 5);
 BookHist(WY_cbars, "WY_cbars", "WY_cbars", 40, -5, 5);
 BookHist(WY_cbarb, "WY_cbarb", "WY_cbarb", 40, -5, 5);

 BookHist(LeptonPt, "LeptonPt", "LeptonPt", 22, 33, 44);
 BookHist(LeptonPt_WMinus, "LeptonPt_WMinus", "LeptonPt_WMinus", 22, 33, 44);
 BookHist(LeptonPt_d, "LeptonPt_d", "LeptonPt_d", 22, 33, 44);
 BookHist(LeptonPt_s, "LeptonPt_s", "LeptonPt_s", 22, 33, 44);
 BookHist(LeptonPt_udbar, "LeptonPt_udbar", "LeptonPt_udbar", 22, 33, 44);
 BookHist(LeptonPt_usbar, "LeptonPt_usbar", "LeptonPt_usbar", 22, 33, 44);
 BookHist(LeptonPt_ubbar, "LeptonPt_ubbar", "LeptonPt_ubbar", 22, 33, 44);
 BookHist(LeptonPt_cdbar, "LeptonPt_cdbar", "LeptonPt_cdbar", 22, 33, 44);
 BookHist(LeptonPt_csbar, "LeptonPt_csbar", "LeptonPt_csbar", 22, 33, 44);
 BookHist(LeptonPt_cbbar, "LeptonPt_cbbar", "LeptonPt_cbbar", 22, 33, 44);
 BookHist(LeptonPt_dbaru, "LeptonPt_dbaru", "LeptonPt_dbaru", 22, 33, 44);
 BookHist(LeptonPt_sbaru, "LeptonPt_sbaru", "LeptonPt_sbaru", 22, 33, 44);
 BookHist(LeptonPt_bbaru, "LeptonPt_bbaru", "LeptonPt_bbaru", 22, 33, 44);
 BookHist(LeptonPt_dbarc, "LeptonPt_dbarc", "LeptonPt_dbarc", 22, 33, 44);
 BookHist(LeptonPt_sbarc, "LeptonPt_sbarc", "LeptonPt_sbarc", 22, 33, 44);
 BookHist(LeptonPt_bbarc, "LeptonPt_bbarc", "LeptonPt_bbarc", 22, 33, 44);
 BookHist(LeptonPt_dubar, "LeptonPt_dubar", "LeptonPt_dubar", 22, 33, 44);
 BookHist(LeptonPt_subar, "LeptonPt_subar", "LeptonPt_subar", 22, 33, 44);
 BookHist(LeptonPt_bubar, "LeptonPt_bubar", "LeptonPt_bubar", 22, 33, 44);
 BookHist(LeptonPt_dcbar, "LeptonPt_dcbar", "LeptonPt_dcbar", 22, 33, 44);
 BookHist(LeptonPt_scbar, "LeptonPt_scbar", "LeptonPt_scbar", 22, 33, 44);
 BookHist(LeptonPt_bcbar, "LeptonPt_bcbar", "LeptonPt_bcbar", 22, 33, 44);
 BookHist(LeptonPt_ubard, "LeptonPt_ubard", "LeptonPt_ubard", 22, 33, 44);
 BookHist(LeptonPt_ubars, "LeptonPt_ubars", "LeptonPt_ubars", 22, 33, 44);
 BookHist(LeptonPt_ubarb, "LeptonPt_ubarb", "LeptonPt_ubarb", 22, 33, 44);
 BookHist(LeptonPt_cbard, "LeptonPt_cbard", "LeptonPt_cbard", 22, 33, 44);
 BookHist(LeptonPt_cbars, "LeptonPt_cbars", "LeptonPt_cbars", 22, 33, 44);
 BookHist(LeptonPt_cbarb, "LeptonPt_cbarb", "LeptonPt_cbarb", 22, 33, 44);

 BookHist(PositiveLeptonEta_udbar, "PositiveLeptonEta_udbar", "PositiveLeptonEta_udbar", 40, -5, 5);
 BookHist(PositiveLeptonEta_csbar, "PositiveLeptonEta_csbar", "PositiveLeptonEta_csbar", 40, -5, 5);
 BookHist(PositiveLeptonEta_dbaru, "PositiveLeptonEta_dbaru", "PositiveLeptonEta_dbaru", 40, -5, 5);
 BookHist(PositiveLeptonEta_sbarc, "PositiveLeptonEta_sbarc", "PositiveLeptonEta_sbarc", 40, -5, 5);
 BookHist(PositiveLeptonEta_other, "PositiveLeptonEta_other", "PositiveLeptonEta_other", 40, -5, 5);

 BookHist(PositiveLeptonEta_ud, "PositiveLeptonEta_ud", "PositiveLeptonEta_ud", 40, -5, 5);
 BookHist(PositiveLeptonEta_cs, "PositiveLeptonEta_cs", "PositiveLeptonEta_cs", 40, -5, 5);

 BookHist(NegativeLeptonEta_dubar, "NegativeLeptonEta_dubar", "NegativeLeptonEta_dubar", 40, -5, 5);
 BookHist(NegativeLeptonEta_scbar, "NegativeLeptonEta_scbar", "NegativeLeptonEta_scbar", 40, -5, 5);
 BookHist(NegativeLeptonEta_ubard, "NegativeLeptonEta_ubard", "NegativeLeptonEta_ubard", 40, -5, 5);
 BookHist(NegativeLeptonEta_cbars, "NegativeLeptonEta_cbars", "NegativeLeptonEta_cbars", 40, -5, 5);
 BookHist(NegativeLeptonEta_other, "NegativeLeptonEta_other", "NegativeLeptonEta_other", 40, -5, 5);

 BookHist(NegativeLeptonEta_ud, "NegativeLeptonEta_ud", "NegativeLeptonEta_ud", 40, -5, 5);
 BookHist(NegativeLeptonEta_cs, "NegativeLeptonEta_cs", "NegativeLeptonEta_cs", 40, -5, 5);

 Book2DHist(PositiveLeptonEtaMT_udbar, "PositiveLeptonEtaMT_udbar", "PositiveLeptonEtaMT_udbar", 40, -5, 5, 3, 60, 105);
 Book2DHist(PositiveLeptonEtaMT_csbar, "PositiveLeptonEtaMT_csbar", "PositiveLeptonEtaMT_csbar", 40, -5, 5, 3, 60, 105);
 Book2DHist(PositiveLeptonEtaMT_dbaru, "PositiveLeptonEtaMT_dbaru", "PositiveLeptonEtaMT_dbaru", 40, -5, 5, 3, 60, 105);
 Book2DHist(PositiveLeptonEtaMT_sbarc, "PositiveLeptonEtaMT_sbarc", "PositiveLeptonEtaMT_sbarc", 40, -5, 5, 3, 60, 105);
 Book2DHist(PositiveLeptonEtaMT_other, "PositiveLeptonEtaMT_other", "PositiveLeptonEtaMT_other", 40, -5, 5, 3, 60, 105);

 Book2DHist(PositiveLeptonEtaMT_ud, "PositiveLeptonEtaMT_ud", "PositiveLeptonEtaMT_ud", 40, -5, 5, 3, 60, 105);
 Book2DHist(PositiveLeptonEtaMT_cs, "PositiveLeptonEtaMT_cs", "PositiveLeptonEtaMT_cs", 40, -5, 5, 3, 60, 105);

 Book2DHist(NegativeLeptonEtaMT_dubar, "NegativeLeptonEtaMT_dubar", "NegativeLeptonEtaMT_dubar", 40, -5, 5, 3, 60, 105);
 Book2DHist(NegativeLeptonEtaMT_scbar, "NegativeLeptonEtaMT_scbar", "NegativeLeptonEtaMT_scbar", 40, -5, 5, 3, 60, 105);
 Book2DHist(NegativeLeptonEtaMT_ubard, "NegativeLeptonEtaMT_ubard", "NegativeLeptonEtaMT_ubard", 40, -5, 5, 3, 60, 105);
 Book2DHist(NegativeLeptonEtaMT_cbars, "NegativeLeptonEtaMT_cbars", "NegativeLeptonEtaMT_cbars", 40, -5, 5, 3, 60, 105);
 Book2DHist(NegativeLeptonEtaMT_other, "NegativeLeptonEtaMT_other", "NegativeLeptonEtaMT_other", 40, -5, 5, 3, 60, 105);

 Book2DHist(NegativeLeptonEtaMT_ud, "NegativeLeptonEtaMT_ud", "NegativeLeptonEtaMT_ud", 40, -5, 5, 3, 60, 105);
 Book2DHist(NegativeLeptonEtaMT_cs, "NegativeLeptonEtaMT_cs", "NegativeLeptonEtaMT_cs", 40, -5, 5, 3, 60, 105);

 BookHist(PositiveNeutrinoEta_udbar, "PositiveNeutrinoEta_udbar", "PositiveNeutrinoEta_udbar", 40, -5, 5);
 BookHist(PositiveNeutrinoEta_csbar, "PositiveNeutrinoEta_csbar", "PositiveNeutrinoEta_csbar", 40, -5, 5);
 BookHist(PositiveNeutrinoEta_dbaru, "PositiveNeutrinoEta_dbaru", "PositiveNeutrinoEta_dbaru", 40, -5, 5);
 BookHist(PositiveNeutrinoEta_sbarc, "PositiveNeutrinoEta_sbarc", "PositiveNeutrinoEta_sbarc", 40, -5, 5);
 BookHist(PositiveNeutrinoEta_other, "PositiveNeutrinoEta_other", "PositiveNeutrinoEta_other", 40, -5, 5);

 BookHist(PositiveNeutrinoEta_ud, "PositiveNeutrinoEta_ud", "PositiveNeutrinoEta_ud", 40, -5, 5);
 BookHist(PositiveNeutrinoEta_cs, "PositiveNeutrinoEta_cs", "PositiveNeutrinoEta_cs", 40, -5, 5);

 BookHist(NegativeNeutrinoEta_dubar, "NegativeNeutrinoEta_dubar", "NegativeNeutrinoEta_dubar", 40, -5, 5);
 BookHist(NegativeNeutrinoEta_scbar, "NegativeNeutrinoEta_scbar", "NegativeNeutrinoEta_scbar", 40, -5, 5);
 BookHist(NegativeNeutrinoEta_ubard, "NegativeNeutrinoEta_ubard", "NegativeNeutrinoEta_ubard", 40, -5, 5);
 BookHist(NegativeNeutrinoEta_cbars, "NegativeNeutrinoEta_cbars", "NegativeNeutrinoEta_cbars", 40, -5, 5);
 BookHist(NegativeNeutrinoEta_other, "NegativeNeutrinoEta_other", "NegativeNeutrinoEta_other", 40, -5, 5);

 BookHist(NegativeNeutrinoEta_ud, "NegativeNeutrinoEta_ud", "NegativeNeutrinoEta_ud", 40, -5, 5);
 BookHist(NegativeNeutrinoEta_cs, "NegativeNeutrinoEta_cs", "NegativeNeutrinoEta_cs", 40, -5, 5);

 Book2DHist(PositiveNeutrinoEtaMT_udbar, "PositiveNeutrinoEtaMT_udbar", "PositiveNeutrinoEtaMT_udbar", 40, -5, 5, 3, 60, 105);
 Book2DHist(PositiveNeutrinoEtaMT_csbar, "PositiveNeutrinoEtaMT_csbar", "PositiveNeutrinoEtaMT_csbar", 40, -5, 5, 3, 60, 105);
 Book2DHist(PositiveNeutrinoEtaMT_dbaru, "PositiveNeutrinoEtaMT_dbaru", "PositiveNeutrinoEtaMT_dbaru", 40, -5, 5, 3, 60, 105);
 Book2DHist(PositiveNeutrinoEtaMT_sbarc, "PositiveNeutrinoEtaMT_sbarc", "PositiveNeutrinoEtaMT_sbarc", 40, -5, 5, 3, 60, 105);
 Book2DHist(PositiveNeutrinoEtaMT_other, "PositiveNeutrinoEtaMT_other", "PositiveNeutrinoEtaMT_other", 40, -5, 5, 3, 60, 105);

 Book2DHist(PositiveNeutrinoEtaMT_ud, "PositiveNeutrinoEtaMT_ud", "PositiveNeutrinoEtaMT_ud", 40, -5, 5, 3, 60, 105);
 Book2DHist(PositiveNeutrinoEtaMT_cs, "PositiveNeutrinoEtaMT_cs", "PositiveNeutrinoEtaMT_cs", 40, -5, 5, 3, 60, 105);

 Book2DHist(NegativeNeutrinoEtaMT_dubar, "NegativeNeutrinoEtaMT_dubar", "NegativeNeutrinoEtaMT_dubar", 40, -5, 5, 3, 60, 105);
 Book2DHist(NegativeNeutrinoEtaMT_scbar, "NegativeNeutrinoEtaMT_scbar", "NegativeNeutrinoEtaMT_scbar", 40, -5, 5, 3, 60, 105);
 Book2DHist(NegativeNeutrinoEtaMT_ubard, "NegativeNeutrinoEtaMT_ubard", "NegativeNeutrinoEtaMT_ubard", 40, -5, 5, 3, 60, 105);
 Book2DHist(NegativeNeutrinoEtaMT_cbars, "NegativeNeutrinoEtaMT_cbars", "NegativeNeutrinoEtaMT_cbars", 40, -5, 5, 3, 60, 105);
 Book2DHist(NegativeNeutrinoEtaMT_other, "NegativeNeutrinoEtaMT_other", "NegativeNeutrinoEtaMT_other", 40, -5, 5, 3, 60, 105);

 Book2DHist(NegativeNeutrinoEtaMT_ud, "NegativeNeutrinoEtaMT_ud", "NegativeNeutrinoEtaMT_ud", 40, -5, 5, 3, 60, 105);
 Book2DHist(NegativeNeutrinoEtaMT_cs, "NegativeNeutrinoEtaMT_cs", "NegativeNeutrinoEtaMT_cs", 40, -5, 5, 3, 60, 105);

 BookHist(WY_udbar_total, "WY_udbar_total", "WY_udbar_total", 40, -5, 5);
 BookHist(WY_csbar_total, "WY_csbar_total", "WY_csbar_total", 40, -5, 5);
 BookHist(WY_dubar_total, "WY_dubar_total", "WY_dubar_total", 40, -5, 5);
 BookHist(WY_scbar_total, "WY_scbar_total", "WY_scbar_total", 40, -5, 5);

 BookHist(WPlusY, "WPlusY", "WPlusY", 40, -5, 5);
 BookHist(WMinusY, "WMinusY", "WMinusY", 40, -5, 5);

 BookHist(LeptonEta, "LeptonEta", "LeptonEta", 20, 0, 5);
 BookHist(AntiLeptonEta, "AntiLeptonEta", "AntiLeptonEta", 20, 0, 5);
 BookHist(ChangePDF_LeptonEta, "ChangePDF_LeptonEta", "ChangePDF_LeptonEta", 20, 0, 5);
 BookHist(ChangePDF_AntiLeptonEta, "ChangePDF_AntiLeptonEta", "AntiLeptonEta", 20, 0, 5);

 BookHist(FWPlusY, "FWPlusY", "FWPlusY", 20, -5, 5);
 BookHist(BWPlusY, "BWPlusY", "BWPlusY", 20, -5, 5);
 BookHist(FWMinusY, "FWMinusY", "FWMinusY", 20, -5, 5);
 BookHist(BWMinusY, "BWMinusY", "BWMinusY", 20, -5, 5);
 BookHist(FWPlusY_reco_80385, "FWPlusY_reco_80385", "FWPlusY_reco_80385", 20, -5, 5);
 BookHist(BWPlusY_reco_80385, "BWPlusY_reco_80385", "BWPlusY_reco_80385", 20, -5, 5);
 BookHist(FWMinusY_reco_80385, "FWMinusY_reco_80385", "FWMinusY_reco_80385", 20, -5, 5);
 BookHist(BWMinusY_reco_80385, "BWMinusY_reco_80385", "BWMinusY_reco_80385", 20, -5, 5);
 BookHist(FWPlusY_reco_80395, "FWPlusY_reco_80395", "FWPlusY_reco_80395", 20, -5, 5);
 BookHist(BWPlusY_reco_80395, "BWPlusY_reco_80395", "BWPlusY_reco_80395", 20, -5, 5);
 BookHist(FWMinusY_reco_80395, "FWMinusY_reco_80395", "FWMinusY_reco_80395", 20, -5, 5);
 BookHist(BWMinusY_reco_80395, "BWMinusY_reco_80395", "BWMinusY_reco_80395", 20, -5, 5);
 BookHist(FWPlusY_reco_80375, "FWPlusY_reco_80375", "FWPlusY_reco_80375", 20, -5, 5);
 BookHist(BWPlusY_reco_80375, "BWPlusY_reco_80375", "BWPlusY_reco_80375", 20, -5, 5);
 BookHist(FWMinusY_reco_80375, "FWMinusY_reco_80375", "FWMinusY_reco_80375", 20, -5, 5);
 BookHist(BWMinusY_reco_80375, "BWMinusY_reco_80375", "BWMinusY_reco_80375", 20, -5, 5);
 BookHist(FWPlusMass, "FWPlusMass", "FWPlusMass", 30, 60, 120);
 BookHist(BWPlusMass, "BWPlusMass", "BWPlusMass", 30, 60, 120);
 BookHist(FWMinusMass, "FWMinusMass", "FWMinusMass", 30, 60, 120);
 BookHist(BWMinusMass, "BWMinusMass", "BWMinusMass", 30, 60, 120);

 BookHist(WPlusY_wrong, "WPlusY_wrong", "WPlusY_wrong", 20, -5, 5);
 BookHist(WPlusY_total, "WPlusY_total", "WPlusY_total", 20, -5, 5);
 BookHist(WMinusY_wrong, "WMinusY_wrong", "WMinusY_wrong", 20, -5, 5);
 BookHist(WMinusY_total, "WMinusY_total", "WMinusY_total", 20, -5, 5);

 BookHist(WPlusForwardMT_quark, "WPlusForwardMT_quark", "WPlusForwardMT_quark", 100, 0, 200);
 BookHist(WPlusBackwardMT_quark, "WPlusBackwardMT_quark", "WPlusBackwardMT_quark", 100, 0, 200);
 BookHist(WMinusForwardMT_quark, "WMinusForwardMT_quark", "WMinusForwardMT_quark", 100, 0, 200);
 BookHist(WMinusBackwardMT_quark, "WMinusBackwardMT_quark", "WMinusBackwardMT_quark", 100, 0, 200);

 BookHist(WPlusMT_ForwardEta, "WPlusMT_ForwardEta", "WPlusMT_ForwardEta", 40, 60, 100);
 BookHist(WPlusMT_CentralEta, "WPlusMT_CentralEta", "WPlusMT_CentralEta", 40, 60, 100);
 BookHist(WMinusMT_ForwardEta, "WMinusMT_ForwardEta", "WMinusMT_ForwardEta", 40, 60, 100);
 BookHist(WMinusMT_CentralEta, "WMinusMT_CentralEta", "WMinusMT_CentralEta", 40, 60, 100);

 BookHist(WPlusMT_ForwardEta_ud, "WPlusMT_ForwardEta_ud", "WPlusMT_ForwardEta_ud", 40, 60, 100);
 BookHist(WPlusMT_CentralEta_ud, "WPlusMT_CentralEta_ud", "WPlusMT_CentralEta_ud", 40, 60, 100);
 BookHist(WMinusMT_ForwardEta_ud, "WMinusMT_ForwardEta_ud", "WMinusMT_ForwardEta_ud", 40, 60, 100);
 BookHist(WMinusMT_CentralEta_ud, "WMinusMT_CentralEta_ud", "WMinusMT_CentralEta_ud", 40, 60, 100);

 BookHist(WPlusMT_ForwardEta_cs, "WPlusMT_ForwardEta_cs", "WPlusMT_ForwardEta_cs", 40, 60, 100);
 BookHist(WPlusMT_CentralEta_cs, "WPlusMT_CentralEta_cs", "WPlusMT_CentralEta_cs", 40, 60, 100);
 BookHist(WMinusMT_ForwardEta_cs, "WMinusMT_ForwardEta_cs", "WMinusMT_ForwardEta_cs", 40, 60, 100);
 BookHist(WMinusMT_CentralEta_cs, "WMinusMT_CentralEta_cs", "WMinusMT_CentralEta_cs", 40, 60, 100);

 BookHist(WPlusMT_ForwardEta_other, "WPlusMT_ForwardEta_other", "WPlusMT_ForwardEta_other", 40, 60, 100);
 BookHist(WPlusMT_CentralEta_other, "WPlusMT_CentralEta_other", "WPlusMT_CentralEta_other", 40, 60, 100);
 BookHist(WMinusMT_ForwardEta_other, "WMinusMT_ForwardEta_other", "WMinusMT_ForwardEta_other", 40, 60, 100);
 BookHist(WMinusMT_CentralEta_other, "WMinusMT_CentralEta_other", "WMinusMT_CentralEta_other", 40, 60, 100);

 BookHist(WPlusMT_ud, "WPlusMT_ud", "WPlusMT_ud", 40, 60, 100);
 BookHist(WMinusMT_ud, "WMinusMT_ud", "WMinusMT_ud", 40, 60, 100);
 BookHist(WPlusMT_cs, "WPlusMT_cs", "WPlusMT_cs", 40, 60, 100);
 BookHist(WMinusMT_cs, "WMinusMT_cs", "WMinusMT_cs", 40, 60, 100);
 BookHist(WPlusMT_other, "WPlusMT_other", "WPlusMT_other", 40, 60, 100);
 BookHist(WMinusMT_other, "WMinusMT_other", "WMinusMT_other", 40, 60, 100);
 BookHist(WPlusMT_total, "WPlusMT_total", "WPlusMT_total", 40, 60, 100);
 BookHist(WMinusMT_total, "WMinusMT_total", "WMinusMT_total", 40, 60, 100);

 AFB_Mass_ZY_ZPt = (TH3D *)FZMass_ZY_QT->at(0)->Clone("AFB_ZMass_ZY_QT");
 AFB_Mass_ZY_ZPt->Reset();

 AFB_Mass_ZY_ZPt_uu = (TH3D *)FZMass_ZY_QT_uu->at(0)->Clone("AFB_ZMass_ZY_QT_uu");
 AFB_Mass_ZY_ZPt_uu->Reset();
 AFB_Mass_ZY_ZPt_dd = (TH3D *)FZMass_ZY_QT_dd->at(0)->Clone("AFB_ZMass_ZY_QT_dd");
 AFB_Mass_ZY_ZPt_dd->Reset();

 AFB_ChangePDF_Mass_ZY_ZPt_uu = (TH3D *)ChangePDF_FZMass_ZY_QT_uu->at(0)->Clone("AFB_ChangePDF_ZMass_ZY_QT_uu");
 AFB_ChangePDF_Mass_ZY_ZPt_uu->Reset();
 AFB_ChangePDF_Mass_ZY_ZPt_dd = (TH3D *)ChangePDF_FZMass_ZY_QT_dd->at(0)->Clone("AFB_ChangePDF_ZMass_ZY_QT_dd");
 AFB_ChangePDF_Mass_ZY_ZPt_dd->Reset();

 Wasymmetry = (TH1D *)LeptonEta->at(0)->Clone("Wasymmetry");
 Wasymmetry->Reset();
 ChangePDF_Wasymmetry = (TH1D *)ChangePDF_LeptonEta->at(0)->Clone("ChangePDF_Wasymmetry");
 ChangePDF_Wasymmetry->Reset();

 AFB_WPlusY = (TH1D *)FWPlusY->at(0)->Clone("AFB_WPlusY");
 AFB_WPlusY->Reset();
 AFB_WMinusY = (TH1D *)FWMinusY->at(0)->Clone("AFB_WMinusY");
 AFB_WMinusY->Reset();
 AFB_WPlusY_reco_80385 = (TH1D *)FWPlusY_reco_80385->at(0)->Clone("AFB_WPlusY_reco_80385");
 AFB_WPlusY_reco_80385->Reset();
 AFB_WMinusY_reco_80385 = (TH1D *)FWMinusY_reco_80385->at(0)->Clone("AFB_WMinusY_reco_80385");
 AFB_WMinusY_reco_80385->Reset();
 AFB_WPlusY_reco_80395 = (TH1D *)FWPlusY_reco_80395->at(0)->Clone("AFB_WPlusY_reco_80395");
 AFB_WPlusY_reco_80395->Reset();
 AFB_WMinusY_reco_80395 = (TH1D *)FWMinusY_reco_80395->at(0)->Clone("AFB_WMinusY_reco_80395");
 AFB_WMinusY_reco_80395->Reset();
 AFB_WPlusY_reco_80375 = (TH1D *)FWPlusY_reco_80375->at(0)->Clone("AFB_WPlusY_reco_80375");
 AFB_WPlusY_reco_80375->Reset();
 AFB_WMinusY_reco_80375 = (TH1D *)FWMinusY_reco_80375->at(0)->Clone("AFB_WMinusY_reco_80375");
 AFB_WMinusY_reco_80375->Reset();

 AFB_WPlusMass = (TH1D *)FWPlusMass->at(0)->Clone("AFB_WPlusMass");
 AFB_WPlusMass->Reset();
 AFB_WMinusMass = (TH1D *)FWMinusMass->at(0)->Clone("AFB_WMinusMass");
 AFB_WMinusMass->Reset();

}

void HistsFlavorAsym::outputInformation()
{
 PositiveAFC = (TH1D *)ZMass_ForwardEtaPlus->at(0)->Clone("PositiveAFC");
 PositiveAFC->Reset();
 AFBFunction(ZMass_CentralEtaPlus->at(0), ZMass_ForwardEtaPlus->at(0), PositiveAFC);

 NegativeAFC = (TH1D *)ZMass_ForwardEtaMinus->at(0)->Clone("NegativeAFC");
 NegativeAFC->Reset();
 AFBFunction(ZMass_CentralEtaMinus->at(0), ZMass_ForwardEtaMinus->at(0), NegativeAFC);

 PositiveAFC_uu = (TH1D *)ZMass_ForwardEtaPlus_uu->at(0)->Clone("PositiveAFC_uu");
 PositiveAFC_uu->Reset();
 AFBFunction(ZMass_CentralEtaPlus_uu->at(0), ZMass_ForwardEtaPlus_uu->at(0), PositiveAFC_uu);

 NegativeAFC_uu = (TH1D *)ZMass_ForwardEtaMinus_uu->at(0)->Clone("NegativeAFC_uu");
 NegativeAFC_uu->Reset();
 AFBFunction(ZMass_CentralEtaMinus_uu->at(0), ZMass_ForwardEtaMinus_uu->at(0), NegativeAFC_uu);

 PositiveAFC_dd = (TH1D *)ZMass_ForwardEtaPlus_dd->at(0)->Clone("PositiveAFC_dd");
 PositiveAFC_dd->Reset();
 AFBFunction(ZMass_CentralEtaPlus_dd->at(0), ZMass_ForwardEtaPlus_dd->at(0), PositiveAFC_dd);

 NegativeAFC_dd = (TH1D *)ZMass_ForwardEtaMinus_dd->at(0)->Clone("NegativeAFC_dd");
 NegativeAFC_dd->Reset();
 AFBFunction(ZMass_CentralEtaMinus_dd->at(0), ZMass_ForwardEtaMinus_dd->at(0), NegativeAFC_dd);

 PositiveAFC_ss = (TH1D *)ZMass_ForwardEtaPlus_ss->at(0)->Clone("PositiveAFC_ss");
 PositiveAFC_ss->Reset();
 AFBFunction(ZMass_CentralEtaPlus_ss->at(0), ZMass_ForwardEtaPlus_ss->at(0), PositiveAFC_ss);

 NegativeAFC_ss = (TH1D *)ZMass_ForwardEtaMinus_ss->at(0)->Clone("NegativeAFC_ss");
 NegativeAFC_ss->Reset();
 AFBFunction(ZMass_CentralEtaMinus_ss->at(0), ZMass_ForwardEtaMinus_ss->at(0), NegativeAFC_ss);

 PositiveAFC_other = (TH1D *)ZMass_ForwardEtaPlus_other->at(0)->Clone("PositiveAFC_other");
 PositiveAFC_other->Reset();
 AFBFunction(ZMass_CentralEtaPlus_other->at(0), ZMass_ForwardEtaPlus_other->at(0), PositiveAFC_other);

 NegativeAFC_other = (TH1D *)ZMass_ForwardEtaMinus_other->at(0)->Clone("NegativeAFC_other");
 NegativeAFC_other->Reset();
 AFBFunction(ZMass_CentralEtaMinus_other->at(0), ZMass_ForwardEtaMinus_other->at(0), NegativeAFC_other);

 PositiveAFC->Write();
 NegativeAFC->Write();
 PositiveAFC_uu->Write();
 NegativeAFC_uu->Write();
 PositiveAFC_dd->Write();
 NegativeAFC_dd->Write();
 PositiveAFC_ss->Write();
 NegativeAFC_ss->Write();
 PositiveAFC_other->Write();
 NegativeAFC_other->Write();

 GetDilutionAverage(PositiveAFC_uu, PositiveAFC_uu_Average, PositiveAFC_uu_Residual);
 GetDilutionAverage(NegativeAFC_uu, NegativeAFC_uu_Average, NegativeAFC_uu_Residual);
 GetDilutionAverage(PositiveAFC_dd, PositiveAFC_dd_Average, PositiveAFC_dd_Residual);
 GetDilutionAverage(NegativeAFC_dd, NegativeAFC_dd_Average, NegativeAFC_dd_Residual);
 GetDilutionAverage(PositiveAFC_ss, PositiveAFC_ss_Average, PositiveAFC_ss_Residual);
 GetDilutionAverage(NegativeAFC_ss, NegativeAFC_ss_Average, NegativeAFC_ss_Residual);

 PositiveAFC_uu_Average->Write();
 NegativeAFC_uu_Average->Write();
 PositiveAFC_uu_Residual->Write();
 NegativeAFC_uu_Residual->Write();
 PositiveAFC_dd_Average->Write();
 NegativeAFC_dd_Average->Write();
 PositiveAFC_dd_Residual->Write();
 NegativeAFC_dd_Residual->Write();
 PositiveAFC_ss_Average->Write();
 NegativeAFC_ss_Average->Write();
 PositiveAFC_ss_Residual->Write();
 NegativeAFC_ss_Residual->Write();


 RelativeXsec_uu = (TH1D *)ZMass_uu->at(0)->Clone("RelativeXsec_uu");
 RelativeXsec_uu->Divide(ZMass_total->at(0));
 RelativeXsec_dd = (TH1D *)ZMass_dd->at(0)->Clone("RelativeXsec_dd");
 RelativeXsec_dd->Divide(ZMass_total->at(0));
 RelativeXsec_ss = (TH1D *)ZMass_ss->at(0)->Clone("RelativeXsec_ss");
 RelativeXsec_ss->Divide(ZMass_total->at(0));
 RelativeXsec_other = (TH1D *)ZMass_other->at(0)->Clone("RelativeXsec_other");
 RelativeXsec_other->Divide(ZMass_total->at(0));

 RelativeXsec_uu->Write();
 RelativeXsec_dd->Write();
 RelativeXsec_ss->Write();
 RelativeXsec_other->Write();

 AFCDiff = (TH1D *)PositiveAFC->Clone("AFCDiff");
 AFCDiff->Add(NegativeAFC, -1);

 AFCDiff_uu = (TH1D *)PositiveAFC_uu->Clone("AFCDiff_uu");
 AFCDiff_uu->Add(NegativeAFC_uu, -1);

 AFCDiff_dd = (TH1D *)PositiveAFC_dd->Clone("AFCDiff_dd");
 AFCDiff_dd->Add(NegativeAFC_dd, -1);

 AFCDiff_ss = (TH1D *)PositiveAFC_ss->Clone("AFCDiff_ss");
 AFCDiff_ss->Add(NegativeAFC_ss, -1);

 GetDilutionAverage(AFCDiff_uu, AFCDiff_uu_Average, AFCDiff_uu_Residual);
 GetDilutionAverage(AFCDiff_dd, AFCDiff_dd_Average, AFCDiff_dd_Residual);
 GetDilutionAverage(AFCDiff_ss, AFCDiff_ss_Average, AFCDiff_ss_Residual);

 AFCDiff->Write();
 AFCDiff_uu->Write();
 AFCDiff_dd->Write();
 AFCDiff_ss->Write();
 AFCDiff_uu_Average->Write();
 AFCDiff_dd_Average->Write();
 AFCDiff_ss_Average->Write();
 AFCDiff_uu_Residual->Write();
 AFCDiff_dd_Residual->Write();
 AFCDiff_ss_Residual->Write();


///////////////////////////////////////////////////////////////////////////////////////////////////////////

 WPlusAFB_quark = (TH1D *)WPlusForwardMT_quark->at(0)->Clone("WPlusAFB_quark");
 WPlusAFB_quark->Reset();
 AFBFunction(WPlusForwardMT_quark->at(0), WPlusBackwardMT_quark->at(0), WPlusAFB_quark);

 WMinusAFB_quark = (TH1D *)WMinusForwardMT_quark->at(0)->Clone("WMinusAFB_quark");
 WMinusAFB_quark->Reset();
 AFBFunction(WMinusForwardMT_quark->at(0), WMinusBackwardMT_quark->at(0), WMinusAFB_quark);

 WPlusAFB_quark->Write();
 WMinusAFB_quark->Write();

///////////////////////////////////////////////////////////////////////////////////////////////////////////

 WPlusAFC_MT = (TH1D *)WPlusMT_ForwardEta->at(0)->Clone("WPlusAFC_MT");
 WPlusAFC_MT->Reset();
 AFBFunction(WPlusMT_CentralEta->at(0), WPlusMT_ForwardEta->at(0), WPlusAFC_MT);

 WMinusAFC_MT = (TH1D *)WMinusMT_ForwardEta->at(0)->Clone("WMinusAFC_MT");
 WMinusAFC_MT->Reset();
 AFBFunction(WMinusMT_CentralEta->at(0), WMinusMT_ForwardEta->at(0), WMinusAFC_MT);

 WPlusAFC_MT_ud = (TH1D *)WPlusMT_ForwardEta_ud->at(0)->Clone("WPlusAFC_MT_ud");
 WPlusAFC_MT_ud->Reset();
 AFBFunction(WPlusMT_CentralEta_ud->at(0), WPlusMT_ForwardEta_ud->at(0), WPlusAFC_MT_ud);

 WMinusAFC_MT_ud = (TH1D *)WMinusMT_ForwardEta_ud->at(0)->Clone("WMinusAFC_MT_ud");
 WMinusAFC_MT_ud->Reset();
 AFBFunction(WMinusMT_CentralEta_ud->at(0), WMinusMT_ForwardEta_ud->at(0), WMinusAFC_MT_ud);

 WPlusAFC_MT_cs = (TH1D *)WPlusMT_ForwardEta_cs->at(0)->Clone("WPlusAFC_MT_cs");
 WPlusAFC_MT_cs->Reset();
 AFBFunction(WPlusMT_CentralEta_cs->at(0), WPlusMT_ForwardEta_cs->at(0), WPlusAFC_MT_cs);

 WMinusAFC_MT_cs = (TH1D *)WMinusMT_ForwardEta_cs->at(0)->Clone("WMinusAFC_MT_cs");
 WMinusAFC_MT_cs->Reset();
 AFBFunction(WMinusMT_CentralEta_cs->at(0), WMinusMT_ForwardEta_cs->at(0), WMinusAFC_MT_cs);

 WPlusAFC_MT_other = (TH1D *)WPlusMT_ForwardEta_other->at(0)->Clone("WPlusAFC_MT_other");
 WPlusAFC_MT_other->Reset();
 AFBFunction(WPlusMT_CentralEta_other->at(0), WPlusMT_ForwardEta_other->at(0), WPlusAFC_MT_other);

 WMinusAFC_MT_other = (TH1D *)WMinusMT_ForwardEta_other->at(0)->Clone("WMinusAFC_MT_other");
 WMinusAFC_MT_other->Reset();
 AFBFunction(WMinusMT_CentralEta_other->at(0), WMinusMT_ForwardEta_other->at(0), WMinusAFC_MT_other);

 WPlusAFC_MT->Write();
 WMinusAFC_MT->Write();
 WPlusAFC_MT_ud->Write();
 WMinusAFC_MT_ud->Write();
 WPlusAFC_MT_cs->Write();
 WMinusAFC_MT_cs->Write();
 WPlusAFC_MT_other->Write();
 WMinusAFC_MT_other->Write();

 GetDilutionAverage(WPlusAFC_MT_ud, WPlusAFC_MT_ud_Average, WPlusAFC_MT_ud_Residual);
 GetDilutionAverage(WMinusAFC_MT_ud, WMinusAFC_MT_ud_Average, WMinusAFC_MT_ud_Residual);
 GetDilutionAverage(WPlusAFC_MT_cs, WPlusAFC_MT_cs_Average, WPlusAFC_MT_cs_Residual);
 GetDilutionAverage(WMinusAFC_MT_cs, WMinusAFC_MT_cs_Average, WMinusAFC_MT_cs_Residual);

 WPlusAFC_MT_ud_Average->Write();
 WMinusAFC_MT_ud_Average->Write();
 WPlusAFC_MT_cs_Average->Write();
 WMinusAFC_MT_cs_Average->Write();

 WPlusAFC_MT_ud_Residual->Write();
 WMinusAFC_MT_ud_Residual->Write();
 WPlusAFC_MT_cs_Residual->Write();
 WMinusAFC_MT_cs_Residual->Write();

 WPlusRelativeXsec_MT_ud = (TH1D *)WPlusMT_ud->at(0)->Clone("WPlusRelativeXsec_MT_ud");
 WPlusRelativeXsec_MT_ud->Divide(WPlusMT_total->at(0));
 WMinusRelativeXsec_MT_ud = (TH1D *)WMinusMT_ud->at(0)->Clone("WMinusRelativeXsec_MT_ud");
 WMinusRelativeXsec_MT_ud->Divide(WMinusMT_total->at(0));

 WPlusRelativeXsec_MT_cs = (TH1D *)WPlusMT_cs->at(0)->Clone("WPlusRelativeXsec_MT_cs");
 WPlusRelativeXsec_MT_cs->Divide(WPlusMT_total->at(0));
 WMinusRelativeXsec_MT_cs = (TH1D *)WMinusMT_cs->at(0)->Clone("WMinusRelativeXsec_MT_cs");
 WMinusRelativeXsec_MT_cs->Divide(WMinusMT_total->at(0));

 WPlusRelativeXsec_MT_other = (TH1D *)WPlusMT_other->at(0)->Clone("WPlusRelativeXsec_MT_other");
 WPlusRelativeXsec_MT_other->Divide(WPlusMT_total->at(0));
 WMinusRelativeXsec_MT_other = (TH1D *)WMinusMT_other->at(0)->Clone("WMinusRelativeXsec_MT_other");
 WMinusRelativeXsec_MT_other->Divide(WMinusMT_total->at(0));

 WPlusRelativeXsec_MT_ud->Write();
 WMinusRelativeXsec_MT_ud->Write();
 WPlusRelativeXsec_MT_cs->Write();
 WMinusRelativeXsec_MT_cs->Write();
 WPlusRelativeXsec_MT_other->Write();
 WMinusRelativeXsec_MT_other->Write();

 //AFB vs Mass ZY ZPt
// AFBFunction(FZMass_ZY_QT->at(0), BZMass_ZY_QT->at(0), AFB_Mass_ZY_ZPt);

 //W asymmetry
// GetWasymmetry(AntiLeptonEta->at(0), LeptonEta->at(0), Wasymmetry);
// GetWasymmetry(ChangePDF_AntiLeptonEta->at(0), ChangePDF_LeptonEta->at(0), ChangePDF_Wasymmetry); 

 if(RootType != "FittingCMSData"){
/*   //quark level AFB vs Mass ZY ZPt
   AFBFunction(FZMass_ZY_QT_uu->at(0), BZMass_ZY_QT_uu->at(0), AFB_Mass_ZY_ZPt_uu);
   AFBFunction(FZMass_ZY_QT_dd->at(0), BZMass_ZY_QT_dd->at(0), AFB_Mass_ZY_ZPt_dd);

   AFBFunction(ChangePDF_FZMass_ZY_QT_uu->at(0), ChangePDF_BZMass_ZY_QT_uu->at(0), AFB_ChangePDF_Mass_ZY_ZPt_uu);
   AFBFunction(ChangePDF_FZMass_ZY_QT_dd->at(0), ChangePDF_BZMass_ZY_QT_dd->at(0), AFB_ChangePDF_Mass_ZY_ZPt_dd);

   //Dilution
   GetCoefficientDilution(ZMass_ZY_QT_uu_wrong->at(0), ZMass_ZY_QT_uu_total->at(0), ZMass_ZY_QT->at(0), CoefficientDilution_ZMass_ZY_QT_uu);
   GetCoefficientDilution(ZMass_ZY_QT_dd_wrong->at(0), ZMass_ZY_QT_dd_total->at(0), ZMass_ZY_QT->at(0), CoefficientDilution_ZMass_ZY_QT_dd);

   GetDilutionAverage(CoefficientDilution_ZMass_ZY_QT_uu, DilutionAverage_ZMass_ZY_QT_uu, ResidualDilution_ZMass_ZY_QT_uu);
   GetDilutionAverage(CoefficientDilution_ZMass_ZY_QT_dd, DilutionAverage_ZMass_ZY_QT_dd, ResidualDilution_ZMass_ZY_QT_dd);

   GetCoefficientDilution(ChangePDF_ZMass_ZY_QT_uu_wrong->at(0), ChangePDF_ZMass_ZY_QT_uu_total->at(0), ChangePDF_ZMass_ZY_QT->at(0), CoefficientDilution_ChangePDF_ZMass_ZY_QT_uu);
   GetCoefficientDilution(ChangePDF_ZMass_ZY_QT_dd_wrong->at(0), ChangePDF_ZMass_ZY_QT_dd_total->at(0), ChangePDF_ZMass_ZY_QT->at(0), CoefficientDilution_ChangePDF_ZMass_ZY_QT_dd);

   GetDilutionAverage(CoefficientDilution_ChangePDF_ZMass_ZY_QT_uu, DilutionAverage_ChangePDF_ZMass_ZY_QT_uu, ResidualDilution_ChangePDF_ZMass_ZY_QT_uu);
   GetDilutionAverage(CoefficientDilution_ChangePDF_ZMass_ZY_QT_dd, DilutionAverage_ChangePDF_ZMass_ZY_QT_dd, ResidualDilution_ChangePDF_ZMass_ZY_QT_dd);

   //W+/W- A4/AFB and Dilution
   AFBFunction(FWPlusY->at(0), BWPlusY->at(0), AFB_WPlusY);
   AFBFunction(FWMinusY->at(0), BWMinusY->at(0), AFB_WMinusY);
   AFBFunction(FWPlusY_reco_80385->at(0), BWPlusY_reco_80385->at(0), AFB_WPlusY_reco_80385);
   AFBFunction(FWMinusY_reco_80385->at(0), BWMinusY_reco_80385->at(0), AFB_WMinusY_reco_80385);
   AFBFunction(FWPlusY_reco_80395->at(0), BWPlusY_reco_80395->at(0), AFB_WPlusY_reco_80395);
   AFBFunction(FWMinusY_reco_80395->at(0), BWMinusY_reco_80395->at(0), AFB_WMinusY_reco_80395);
   AFBFunction(FWPlusY_reco_80375->at(0), BWPlusY_reco_80375->at(0), AFB_WPlusY_reco_80375);
   AFBFunction(FWMinusY_reco_80375->at(0), BWMinusY_reco_80375->at(0), AFB_WMinusY_reco_80375);
   AFBFunction(FWPlusMass->at(0), BWPlusMass->at(0), AFB_WPlusMass);
   AFBFunction(FWMinusMass->at(0), BWMinusMass->at(0), AFB_WMinusMass);

   Dilution_WPlusY = (TH1D *)WPlusY_wrong->at(0)->Clone("Dilution_WPlusY");
   Dilution_WPlusY->Divide(WPlusY_total->at(0));
   Dilution_WMinusY = (TH1D *)WMinusY_wrong->at(0)->Clone("Dilution_WMinusY");
   Dilution_WMinusY->Divide(WMinusY_total->at(0));

   CoefficientDilution_WPlusY = (TH1D *)Dilution_WPlusY->Clone("CoefficientDilution_WPlusY");
   CoefficientDilution_WPlusY->Reset();
   for(int ibin = 1; ibin <= CoefficientDilution_WPlusY->GetNbinsX(); ibin++){
     CoefficientDilution_WPlusY->SetBinContent(ibin, 1.0 - 2.0 * Dilution_WPlusY->GetBinContent(ibin));
     CoefficientDilution_WPlusY->SetBinError(ibin, 2.0 * Dilution_WPlusY->GetBinError(ibin));
   }

   CoefficientDilution_WMinusY = (TH1D *)Dilution_WMinusY->Clone("CoefficientDilution_WMinusY");
   CoefficientDilution_WMinusY->Reset();
   for(int ibin = 1; ibin <= CoefficientDilution_WMinusY->GetNbinsX(); ibin++){
     CoefficientDilution_WMinusY->SetBinContent(ibin, 1.0 - 2.0 * Dilution_WMinusY->GetBinContent(ibin));
     CoefficientDilution_WMinusY->SetBinError(ibin, 2.0 * Dilution_WMinusY->GetBinError(ibin));
   }

   OriginAFB_WPlusY = (TH1D *)AFB_WPlusY->Clone("OriginAFB_WPlusY");
   OriginAFB_WPlusY->Divide(CoefficientDilution_WPlusY);
   OriginAFB_WMinusY = (TH1D *)AFB_WMinusY->Clone("OriginAFB_WMinusY");
   OriginAFB_WMinusY->Divide(CoefficientDilution_WMinusY);
*/

 }

 if(RootType != "FittingCMSData") Save();



}

void HistsFlavorAsym::Save()
{
 hf->cd();

// AFB_Mass_ZY_ZPt->Write();

 if(RootType != "FittingCMSData"){
/*   AFB_Mass_ZY_ZPt_uu->Write();
   AFB_Mass_ZY_ZPt_dd->Write();

   AFB_ChangePDF_Mass_ZY_ZPt_uu->Write();
   AFB_ChangePDF_Mass_ZY_ZPt_dd->Write();

   CoefficientDilution_ZMass_ZY_QT_uu->Write();
   CoefficientDilution_ZMass_ZY_QT_dd->Write();

   DilutionAverage_ZMass_ZY_QT_uu->Write();
   DilutionAverage_ZMass_ZY_QT_dd->Write();

   ResidualDilution_ZMass_ZY_QT_uu->Write();
   ResidualDilution_ZMass_ZY_QT_dd->Write();

   CoefficientDilution_ChangePDF_ZMass_ZY_QT_uu->Write();
   CoefficientDilution_ChangePDF_ZMass_ZY_QT_dd->Write();

   DilutionAverage_ChangePDF_ZMass_ZY_QT_uu->Write();
   DilutionAverage_ChangePDF_ZMass_ZY_QT_dd->Write();

   ResidualDilution_ChangePDF_ZMass_ZY_QT_uu->Write();
   ResidualDilution_ChangePDF_ZMass_ZY_QT_dd->Write();
*/
 }

/*
 Wasymmetry->Write();
 ChangePDF_Wasymmetry->Write();

 AFB_WPlusY->Write();
 AFB_WMinusY->Write();
 AFB_WPlusY_reco_80385->Write();
 AFB_WMinusY_reco_80385->Write();
 AFB_WPlusY_reco_80395->Write();
 AFB_WMinusY_reco_80395->Write();
 AFB_WPlusY_reco_80375->Write();
 AFB_WMinusY_reco_80375->Write();
 AFB_WPlusMass->Write();
 AFB_WMinusMass->Write();
 Dilution_WPlusY->Write();
 Dilution_WMinusY->Write();
 OriginAFB_WPlusY->Write();
 OriginAFB_WMinusY->Write();
*/

}

void HistsFlavorAsym::Reset()
{
// AFB_Mass_ZY_ZPt->Reset();

 if(RootType != "FittingCMSData"){
/*   AFB_Mass_ZY_ZPt_uu->Reset();
   AFB_Mass_ZY_ZPt_dd->Reset();

   AFB_ChangePDF_Mass_ZY_ZPt_uu->Reset();
   AFB_ChangePDF_Mass_ZY_ZPt_dd->Reset();

   CoefficientDilution_ZMass_ZY_QT_uu->Reset();
   CoefficientDilution_ZMass_ZY_QT_dd->Reset();

   DilutionAverage_ZMass_ZY_QT_uu->Reset();
   DilutionAverage_ZMass_ZY_QT_dd->Reset();

   ResidualDilution_ZMass_ZY_QT_uu->Reset();
   ResidualDilution_ZMass_ZY_QT_dd->Reset();

   CoefficientDilution_ChangePDF_ZMass_ZY_QT_uu->Reset();
   CoefficientDilution_ChangePDF_ZMass_ZY_QT_dd->Reset();

   DilutionAverage_ChangePDF_ZMass_ZY_QT_uu->Reset();
   DilutionAverage_ChangePDF_ZMass_ZY_QT_dd->Reset();

   ResidualDilution_ChangePDF_ZMass_ZY_QT_uu->Reset();
   ResidualDilution_ChangePDF_ZMass_ZY_QT_dd->Reset();
*/
 }

/*
 Wasymmetry->Reset();
 ChangePDF_Wasymmetry->Reset();

 AFB_WPlusY->Reset();
 AFB_WMinusY->Reset();
 AFB_WPlusY_reco_80385->Reset();
 AFB_WMinusY_reco_80385->Reset();
 AFB_WPlusY_reco_80395->Reset();
 AFB_WMinusY_reco_80395->Reset();
 AFB_WPlusY_reco_80375->Reset();
 AFB_WMinusY_reco_80375->Reset();
 AFB_WPlusMass->Reset();
 AFB_WMinusMass->Reset();
 Dilution_WPlusY->Reset();
 Dilution_WMinusY->Reset();
*/

}

void HistsFlavorAsym::InitialSysName()
{

}
