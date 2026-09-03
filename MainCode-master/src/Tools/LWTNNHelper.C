#include "Tools/LWTNNHelper.h"

void LWTNNHelper::Initialize(TString EvenFile, TString OddFile)
{
#ifdef USE_LWTNN
/**************************************************************************************/
// Initialize DNNs only once
/**************************************************************************************/
 if (!nn_pnu_even){
    //path = PathResolverFindCalibFile("regression_pnu_even.json");
	
    // get NN architecture from JSON file
    std::ifstream json(EvenFile);

    // build the network
	nn_pnu_even=new lwt::LightweightGraph(lwt::parse_json_graph(json));
 }


 if (!nn_pnu_odd){
    //path = PathResolverFindCalibFile("regression_pnu_odd.json");
	
    // get NN architecture from JSON file
    std::ifstream json(OddFile);

    // build the network
	nn_pnu_odd=new lwt::LightweightGraph(lwt::parse_json_graph(json));
 }

#endif
}

double LWTNNHelper::GetNuPz(TLorentzVector wlep, TLorentzVector wnu, int eventNumber, double WMass)
{
/**************************************************************************************/
// compute pz nu with DNN (for each event)
/**************************************************************************************/
 float Px = TMath::Cos(wnu.Px()); //nu px in GeV
 float Py = TMath::Cos(wnu.Py()); //nu py in GeV
// double plnu = plNu(); // nu pz reconstructed from w mass constraints (see below)
 double plnu = 0.0;

#ifdef USE_LWTNN
 plnu = CalculateNeutrinoPz(wlep, wnu, WMass);

 float wlep_Pt = wlep.Pt(); //pt of W charged leptong in GeV
 float wlep_Pz = wlep.Pz(); //pz of W charged leptong in GeV
 float cos = TMath::Cos(wlep.Phi()); //cos(phi) W charged lepton
 float sin = TMath::Sin(wlep.Phi()); //sin(phi) W charged lepton

 std::map<std::string, std::map<std::string, double> > nn_inputs;
 nn_inputs["node_0"] = {
 	{"nu_pt_para", (Px*cos + Py*sin)}, 
	{"nu_pt_orto", (-Px*sin + Py*cos)},
	{"nu_pz", plnu},
	{"lep_pt", wlep_Pt}, 
	{"lep_pz", wlep_Pz},
 };

 std::map<std::string, double> nn_outputs = (eventNumber%2==1) ? nn_pnu_odd->compute(nn_inputs) : nn_pnu_even->compute(nn_inputs);

 Px=(nn_outputs.at("nu_pt_para")*cos-nn_outputs.at("nu_pt_orto")*sin);
 Py=(nn_outputs.at("nu_pt_para")*sin+nn_outputs.at("nu_pt_orto")*cos);
 plnu=nn_outputs.at("nu_pz");

#endif

 return plnu;
}

/**************************************************************************************/
// Reconstruct the plNu using the W mass constraints
/**************************************************************************************/
double LWTNNHelper::plNu(TLorentzVector wlep, TLorentzVector wnu, double MW)
{
  // longitudinal transverse momentum of the generated neutrino 
  
//  double MW = 80.385; //This is in GeV
  double plNu = 0;

#ifdef USE_LWTNN 

  double solution1 = 0; 
  double solution2 = 0;
  
  double a = pow(wlep.Pt(),2);
  double b0 = -1 * wlep.Pz();
  double b1 = 2 * (wlep.Px()*wnu.Px()+wlep.Py()*wnu.Py() ) + pow (MW,2);
  double b = b0 * b1 ;
  double c = -1* pow(0.5*b1,2)  + pow (wlep.E()*wnu.Pt(),2);
 
  double delta2= pow(b,2) - 4 * a * c;
 
  plNu = -1*b/(2*a);
  // if delta2>0 there are 2 solutions, take the smallest
  if(delta2 > 0 )
  {
      double delta = sqrt(delta2); 
      solution1 = (-1*b + delta)/(2*a)  ;
      solution2 = (-1*b - delta)/(2*a)  ;
      plNu = solution1;
      if( fabs(solution2) < fabs(solution1) )  plNu = solution2;
  }

#endif

  return plNu;
}


 //----- evaluate NNs
  // //----- fill a map of input nodes
void LWTNNHelper::InitializePolClassifier(TString EvenFile, TString OddFile)
{
#ifdef USE_LWTNN
/**************************************************************************************/
// Initialize DNNs only once
/**************************************************************************************/
 if (!m_nn_polclassifier_mg_even){
    //path = PathResolverFindCalibFile("regression_pnu_even.json");

    // get NN architecture from JSON file
    std::ifstream json(EvenFile);

    // build the network
        m_nn_polclassifier_mg_even=new lwt::LightweightGraph(lwt::parse_json_graph(json));
 }


 if (!m_nn_polclassifier_mg_odd){
    //path = PathResolverFindCalibFile("regression_pnu_odd.json");

    // get NN architecture from JSON file
    std::ifstream json(OddFile);

    // build the network
        m_nn_polclassifier_mg_odd=new lwt::LightweightGraph(lwt::parse_json_graph(json));
 }

#endif
}

void LWTNNHelper::ReadPolClassifier(TLorentzVector m_ZLepton1, TLorentzVector m_ZLepton2, TLorentzVector m_WLepton, TLorentzVector m_WNeutrino, int eventNumber)
{
#ifdef USE_LWTNN

  TLorentzVector m_ZBoson = m_ZLepton1 + m_ZLepton2;
  TLorentzVector m_WBoson = m_WLepton + m_WNeutrino;
  TLorentzVector WZ = m_ZBoson + m_WBoson;

  std::map<std::string, std::map<std::string, double> > nn_inputs;
  nn_inputs["node_0"] = {
    {"TMath::Abs(WlepZRapidityDiff)", TMath::Abs(m_ZBoson.Rapidity()-m_WLepton.Rapidity())},
    {"WleppT",   m_WLepton.Pt()},
//    {"MET",      m_xAODEvent->m_recMET.Pt()/GeV},
    {"MET",      m_WNeutrino.Pt()},
    {"WlepDPhi", acos(cos(m_WNeutrino.Phi() - m_WLepton.Phi()))},
    {"Zlep1pT",  m_ZLepton1.Pt()},
    {"Zlep2pT",  m_ZLepton2.Pt()},
    {"ZlepDPhi", acos(cos(m_ZLepton1.Phi() - m_ZLepton2.Phi()))},
    {"WZpT_rec", WZ.Pt()},
  };

  std::map<std::string, double> nn_outputs;
  try{
    // DNN MG training
    nn_outputs = ((eventNumber / 100) % 2 == 0) ? m_nn_polclassifier_mg_even->compute(nn_inputs) : m_nn_polclassifier_mg_odd->compute(nn_inputs);
  }
  catch(std::exception& e){
    std::cout<<"Malformed NN input. "<<e.what()<<std::endl;
    throw e;
  }
  this->nn_pLL = nn_outputs["p_WLZL"];
  this->nn_pLT = nn_outputs["p_WLZT"];
  this->nn_pTL = nn_outputs["p_WTZL"];
  this->nn_pTT = nn_outputs["p_WTZT"];

#endif
}

void LWTNNHelper::GetFraction(float &pLL, float &pLT, float &pTL, float &pTT)
{
 pLL = this->nn_pLL;
 pLT = this->nn_pLT;
 pTL = this->nn_pTL;
 pTT = this->nn_pTT;
}

void LWTNNHelper::InitializeNLOPol(TString LLFile, TString LTFile, TString TLFile, TString TTFile)
{
#ifdef USE_LWTNN
 if (!m_nn_polrw_w0z0){

    // get NN architecture from JSON file
    std::ifstream json(LLFile);

    // build the network
        m_nn_polrw_w0z0 = new lwt::LightweightGraph(lwt::parse_json_graph(json));
 }

 if (!m_nn_polrw_w0zT){

    // get NN architecture from JSON file
    std::ifstream json(LTFile);

    // build the network
        m_nn_polrw_w0zT = new lwt::LightweightGraph(lwt::parse_json_graph(json));
 }

 if (!m_nn_polrw_wTz0){

    // get NN architecture from JSON file
    std::ifstream json(TLFile);

    // build the network
        m_nn_polrw_wTz0 = new lwt::LightweightGraph(lwt::parse_json_graph(json));
 }

 if (!m_nn_polrw_wTzT){

    // get NN architecture from JSON file
    std::ifstream json(TTFile);

    // build the network
        m_nn_polrw_wTzT = new lwt::LightweightGraph(lwt::parse_json_graph(json));
 }

#endif
}

double LWTNNHelper::GetNLOWeight(TString type, TLorentzVector ZLepton1, TLorentzVector ZLepton2, TLorentzVector WLepton, TLorentzVector Neutrino)
{
 double Value = 1.0;

#ifdef USE_LWTNN
  TLorentzVector ZBoson = ZLepton1 + ZLepton2;
  TLorentzVector WBoson = WLepton + Neutrino;
  TLorentzVector WZ_lab = ZBoson + WBoson;

  TLorentzVector Wl_WZRF, Zlss_WZRF, W_WZRF, Z_WZRF;

  Wl_WZRF   = WLepton;
  Zlss_WZRF = ZLepton2;
  W_WZRF    = WBoson;
  Z_WZRF    = ZBoson;
  Wl_WZRF.Boost  ( -WZ_lab.BoostVector() );
  Zlss_WZRF.Boost( -WZ_lab.BoostVector() );
  W_WZRF.Boost   ( -WZ_lab.BoostVector() );
  Z_WZRF.Boost   ( -WZ_lab.BoostVector() );

  TLorentzVector Wl_WZtoWRF, Zlss_WZtoZRF;

  Wl_WZtoWRF   = Wl_WZRF;
  Zlss_WZtoZRF = Zlss_WZRF;
  Wl_WZtoWRF.Boost  ( -W_WZRF.BoostVector() );
  Zlss_WZtoZRF.Boost( -Z_WZRF.BoostVector() );

  double DNNweight = 1.0;

  std::map<std::string, std::map<std::string, double> > nn_polrw_inputs;
  nn_polrw_inputs["node_0"] = {
    {"TMath::Abs(WlepZRapidityDiff)", fabs( ZBoson.Rapidity() - WLepton.Rapidity() )},
    {"WleppT",   WLepton.Pt()},
    {"MET",      Neutrino.Pt()},
    {"WlepDPhi", acos(cos(Neutrino.Phi() - WLepton.Phi()))},
    {"Zlep1pT",  ZLepton1.Pt()},
    {"Zlep2pT",  ZLepton2.Pt()},
    {"ZlepDPhi", acos(cos(ZLepton1.Phi() - ZLepton2.Phi()))},
    {"WZpT_rec", WZ_lab.Pt()},
    {"mWZ",      WZ_lab.M()},
    {"cosThetaCM_Zlss", cos( Zlss_WZtoZRF.Angle(Z_WZRF.Vect()))},
    {"cosThetaCM_Wl", cos( Wl_WZtoWRF.Angle(W_WZRF.Vect()))},
    {"cosThetaV", abs( W_WZRF.CosTheta() )},
  };


  std::map<std::string, double> nn_polrw_outputs;
  double p_dnn = -1.;

  lwt::LightweightGraph* nn_polrw;

  if ( type == "00dnn" ) {
    nn_polrw = m_nn_polrw_w0z0;
  }else if ( type == "0Tdnn" ){
    nn_polrw = m_nn_polrw_w0zT;
  }else if ( type == "T0dnn" ){
    nn_polrw = m_nn_polrw_wTz0;
  }else if ( type == "TTdnn" ){
    nn_polrw = m_nn_polrw_wTzT;
  }

  try{
    nn_polrw_outputs = nn_polrw->compute(nn_polrw_inputs);
    p_dnn=nn_polrw_outputs["p"];
  }
  catch(std::exception& e){
    std::cout<<"Malformed NNrw input. "<<e.what()<<std::endl;
    throw e;
  }

  if (p_dnn == 1 or isnan(p_dnn)) {
    std::cerr << "WARNING: would give a NaN DNNweight !" << endl;
    return 1.; //0. ?
  }
  DNNweight = p_dnn/(1-p_dnn);
  if (DNNweight > 50) {
    std::cerr << "WARNING: would give an absurdly high DNNweight !" << endl;
    return 1.; //0. ?
  }

  if ( type == "0Bdnn" ) {
    DNNweight = 1 - DNNweight;
    DNNweight *= (1 - 0.0467);
  }else if ( type == "00dnn" ) {
    DNNweight *= 0.0467;
  }else if ( type == "0Tdnn" ) {
    DNNweight *= 0.1428;
  }else if ( type == "T0dnn" ) {
    DNNweight *= 0.1381;
  }else if ( type == "TTdnn" ) {
    DNNweight *= 0.6725;
  }

  Value = DNNweight;
#endif

 return Value;
}

