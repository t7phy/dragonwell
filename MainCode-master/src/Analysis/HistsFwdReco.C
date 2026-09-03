#include "Analysis/HistsFwdReco.h"

using namespace std;

void HistsFwdReco::bookHists(int TotalThread)
{
 this->TotalThread = TotalThread;

 BookHist(FwdElectronPt, "FwdElectronPt", "FwdElectronPt", 20, 0, 100000);
// BookHist(FwdElectronEta, "FwdElectronEta", "FwdElectronEta", 10, 2.5, 5);
 BookHist(FwdElectronEta, "FwdElectronEta", "FwdElectronEta", 20, -5, 5);
 BookHist(FwdElectronPhi, "FwdElectronPhi", "FwdElectronPhi", 20, -3.14, 3.14);
 BookHist(FwdElectronEt, "FwdElectronEt", "FwdElectronEt", 20, 0, 100000);

 BookHist(TruthElectronPt, "TruthElectronPt", "TruthElectronPt", 20, 0, 100000);
 BookHist(TruthElectronEta, "TruthElectronEta", "TruthElectronEta", 20, -5, 5);
 BookHist(TruthElectronPhi, "TruthElectronPhi", "TruthElectronPhi", 20, -3.14, 3.14);
 BookHist(TruthElectronEt, "TruthElectronEt", "TruthElectronEt", 20, 0, 100000);
 BookHist(TruthElectronEtaAbs, "TruthElectronEtaAbs", "TruthElectronEtaAbs", 25, 2.5, 5);

 BookHist(MatchedElectronPt, "MatchedElectronPt", "MatchedElectronPt", 20, 0, 100000);
 BookHist(MatchedElectronEta, "MatchedElectronEta", "MatchedElectronEta", 20, -5, 5);
 BookHist(MatchedElectronPhi, "MatchedElectronPhi", "MatchedElectronPhi", 20, -3.14, 3.14);
 BookHist(MatchedElectronEt, "MatchedElectronEt", "MatchedElectronEt", 20, 0, 100000);
 BookHist(MatchedElectronEtaAbs, "MatchedElectronEtaAbs", "MatchedElectronEtaAbs", 25, 2.5, 5);

 BookHist(AverageMu, "AverageMu", "AverageMu", 20, 0, 100);
 BookHist(TruthSize, "TruthSize", "TruthSize", 10, 0, 10);
 BookHist(RecoSize, "RecoSize", "RecoSize", 20, 0, 20);

 Book2DHist(TruthElectronEtEta, "TruthElectronEtEta", "TruthElectronEtEta", 20, 0, 100000, 20, -5, 5);
 Book2DHist(TruthElectronEtaPhi, "TruthElectronEtaPhi", "TruthElectronEtaPhi", 20, -5, 5, 20, -3.14, 3.14);

 Book2DHist(MatchedElectronEtEta, "MatchedElectronEtEta", "MatchedElectronEtEta", 20, 0, 100000, 20, -5, 5);
 Book2DHist(MatchedElectronEtaPhi, "MatchedElectronEtaPhi", "MatchedElectronEtaPhi", 20, -5, 5, 20, -3.14, 3.14);

 BookResolutionHist(EResolutionEta, "E_Resolution", "RMS", 25, 2.5, 5);
 BookResolutionHist(PtResolutionEta, "Pt_Resolution", "RMS", 25, 2.5, 5);
 BookResolutionHist(EtResolutionEta, "Et_Resolution", "RMS", 25, 2.5, 5);
 BookResolutionHist(PtResolutionEta_LowMu, "Pt_Resolution_LowMu", "RMS", 25, 2.5, 5);
 BookResolutionHist(PtResolutionEta_HighMu, "Pt_Resolution_HighMu", "RMS", 25, 2.5, 5);
 BookResolutionHist(PtResolutionPt, "Pt_ResolutionPt", "RMS", 20, 0, 100000);


}
