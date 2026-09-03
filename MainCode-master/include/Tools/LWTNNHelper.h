#ifndef LWTNNHelper_h
#define LWTNNHelper_h

#include <fstream>
#include <map>
#include <string>
#include "RootCommon.h"
#include "Tools/Tools.h"

#ifdef USE_LWTNN
#include "lwtnn/LightweightGraph.hh"
#include "lwtnn/parse_json.hh"
#endif

class LWTNNHelper
{
 public:

#ifdef USE_LWTNN
 lwt::LightweightGraph *nn_pnu_even;
 lwt::LightweightGraph *nn_pnu_odd;

 lwt::LightweightGraph *m_nn_polclassifier_mg_even;
 lwt::LightweightGraph *m_nn_polclassifier_mg_odd;

 lwt::LightweightGraph *m_nn_polrw_w0z0;
 lwt::LightweightGraph *m_nn_polrw_w0zT;
 lwt::LightweightGraph *m_nn_polrw_wTz0;
 lwt::LightweightGraph *m_nn_polrw_wTzT;

#endif

 float nn_pLL;
 float nn_pLT;
 float nn_pTL;
 float nn_pTT;

 virtual void Initialize(TString EvenFile, TString OddFile);
 virtual double GetNuPz(TLorentzVector wlep, TLorentzVector wnu, int eventNumber, double WMass);
 virtual double plNu(TLorentzVector wlep, TLorentzVector wnu, double MW);

 virtual void InitializePolClassifier(TString EvenFile, TString OddFile);
 virtual void ReadPolClassifier(TLorentzVector m_ZLepton1, TLorentzVector m_ZLepton2, TLorentzVector m_WLepton, TLorentzVector m_WNeutrino, int eventNumber);
 virtual void GetFraction(float &pLL, float &pLT, float &pTL, float &pTT);

 virtual void InitializeNLOPol(TString LLFile, TString LTFile, TString TLFile, TString TTFile);
 virtual double GetNLOWeight(TString type, TLorentzVector ZLepton1, TLorentzVector ZLepton2, TLorentzVector WLepton, TLorentzVector Neutrino);

};
#endif
