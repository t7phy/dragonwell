#include "SpecialHist/FakeHist.h"

FakeHist::FakeHist()
{
 FakeObjects = 3;
}

void FakeHist::DefineHist(TString name, TString title, int nbin, double left, double right)
{
 this->HistName = name;

 myHist["ZElFakeRate"] = new TH1D(name + "_ZElFakeRate", title + "_ZElFakeRate", nbin, left, right);
 myHist["ZElFakeRate"]->Sumw2();
 FakeHist_1d.push_back(myHist["ZElFakeRate"]);
 myHist["LTTCount"] = new TH1D(name + "_LTTCount", title + "_LTTCount", nbin, left, right);
 myHist["LTTCount"]->Sumw2();
 FakeHist_1d.push_back(myHist["LTTCount"]);

 myHist["TTT"] = new TH1D(name + "_TTT", title + "_TTT", nbin, left, right);
 myHist["TTT"]->Sumw2();
 FakeHist_1d.push_back(myHist["TTT"]);
 myHist["TTL"] = new TH1D(name + "_TTL", title + "_TTL", nbin, left, right);
 myHist["TTL"]->Sumw2();
 FakeHist_1d.push_back(myHist["TTL"]);
 myHist["TLT"] = new TH1D(name + "_TLT", title + "_TLT", nbin, left, right);
 myHist["TLT"]->Sumw2();
 FakeHist_1d.push_back(myHist["TLT"]);
 myHist["LTT"] = new TH1D(name + "_LTT", title + "_LTT", nbin, left, right);
 myHist["LTT"]->Sumw2();
 FakeHist_1d.push_back(myHist["LTT"]);
 myHist["TLL"] = new TH1D(name + "_TLL", title + "_TLL", nbin, left, right);
 myHist["TLL"]->Sumw2();
 FakeHist_1d.push_back(myHist["TLL"]);
 myHist["LTL"] = new TH1D(name + "_LTL", title + "_LTL", nbin, left, right);
 myHist["LTL"]->Sumw2();
 FakeHist_1d.push_back(myHist["LTL"]);
 myHist["LLT"] = new TH1D(name + "_LLT", title + "_LLT", nbin, left, right);
 myHist["LLT"]->Sumw2();
 FakeHist_1d.push_back(myHist["LLT"]);

 myHist_RRR = new TH1D(name + "_RRR", title + "_RRR", nbin, left, right);
 myHist_RRR->Sumw2();
 FakeHist_1d.push_back(myHist_RRR);
 myHist_RRF = new TH1D(name + "_RRF", title + "_RRF", nbin, left, right);
 myHist_RRF->Sumw2();
 FakeHist_1d.push_back(myHist_RRF);
 myHist_RFR = new TH1D(name + "_RFR", title + "_RFR", nbin, left, right);
 myHist_RFR->Sumw2();
 FakeHist_1d.push_back(myHist_RFR);
 myHist_FRR = new TH1D(name + "_FRR", title + "_FRR", nbin, left, right);
 myHist_FRR->Sumw2();
 FakeHist_1d.push_back(myHist_FRR);
 myHist_RFF = new TH1D(name + "_RFF", title + "_RFF", nbin, left, right);
 myHist_RFF->Sumw2();
 FakeHist_1d.push_back(myHist_RFF);
 myHist_FRF = new TH1D(name + "_FRF", title + "_FRF", nbin, left, right);
 myHist_FRF->Sumw2();
 FakeHist_1d.push_back(myHist_FRF);
 myHist_FFR = new TH1D(name + "_FFR", title + "_FFR", nbin, left, right);
 myHist_FFR->Sumw2();
 FakeHist_1d.push_back(myHist_FFR);

}

void FakeHist::DefineHist(TString name, TString title, int nbin, double* xbins)
{
 this->HistName = name;

 myHist["ZElFakeRate"] = new TH1D(name + "_ZElFakeRate", title + "_ZElFakeRate", nbin, xbins);
 myHist["ZElFakeRate"]->Sumw2();
 FakeHist_1d.push_back(myHist["ZElFakeRate"]);
 myHist["LTTCount"] = new TH1D(name + "_LTTCount", title + "_LTTCount", nbin, xbins);
 myHist["LTTCount"]->Sumw2();
 FakeHist_1d.push_back(myHist["LTTCount"]);

 myHist["TTT"] = new TH1D(name + "_TTT", title + "_TTT", nbin, xbins);
 myHist["TTT"]->Sumw2();
 FakeHist_1d.push_back(myHist["TTT"]);
 myHist["TTL"] = new TH1D(name + "_TTL", title + "_TTL", nbin, xbins);
 myHist["TTL"]->Sumw2();
 FakeHist_1d.push_back(myHist["TTL"]);
 myHist["TLT"] = new TH1D(name + "_TLT", title + "_TLT", nbin, xbins);
 myHist["TLT"]->Sumw2();
 FakeHist_1d.push_back(myHist["TLT"]);
 myHist["LTT"] = new TH1D(name + "_LTT", title + "_LTT", nbin, xbins);
 myHist["LTT"]->Sumw2();
 FakeHist_1d.push_back(myHist["LTT"]);
 myHist["TLL"] = new TH1D(name + "_TLL", title + "_TLL", nbin, xbins);
 myHist["TLL"]->Sumw2();
 FakeHist_1d.push_back(myHist["TLL"]);
 myHist["LTL"] = new TH1D(name + "_LTL", title + "_LTL", nbin, xbins);
 myHist["LTL"]->Sumw2();
 FakeHist_1d.push_back(myHist["LTL"]);
 myHist["LLT"] = new TH1D(name + "_LLT", title + "_LLT", nbin, xbins);
 myHist["LLT"]->Sumw2();
 FakeHist_1d.push_back(myHist["LLT"]);

 myHist_RRR = new TH1D(name + "_RRR", title + "_RRR", nbin, xbins);
 myHist_RRR->Sumw2();
 FakeHist_1d.push_back(myHist_RRR);
 myHist_RRF = new TH1D(name + "_RRF", title + "_RRF", nbin, xbins);
 myHist_RRF->Sumw2();
 FakeHist_1d.push_back(myHist_RRF);
 myHist_RFR = new TH1D(name + "_RFR", title + "_RFR", nbin, xbins);
 myHist_RFR->Sumw2();
 FakeHist_1d.push_back(myHist_RFR);
 myHist_FRR = new TH1D(name + "_FRR", title + "_FRR", nbin, xbins);
 myHist_FRR->Sumw2();
 FakeHist_1d.push_back(myHist_FRR);
 myHist_RFF = new TH1D(name + "_RFF", title + "_RFF", nbin, xbins);
 myHist_RFF->Sumw2();
 FakeHist_1d.push_back(myHist_RFF);
 myHist_FRF = new TH1D(name + "_FRF", title + "_FRF", nbin, xbins);
 myHist_FRF->Sumw2();
 FakeHist_1d.push_back(myHist_FRF);
 myHist_FFR = new TH1D(name + "_FFR", title + "_FFR", nbin, xbins);
 myHist_FFR->Sumw2();
 FakeHist_1d.push_back(myHist_FFR);

}

void FakeHist::LinkFakeRate(DataDriven* myFakeRate)
{
 this->myFakeRate = myFakeRate;

 this->doFakeRate = myFakeRate->doFakeRate;
 this->isInputUpSysFakeRate = myFakeRate->isInputUpSysFakeRate;
 this->isInputDownSysFakeRate = myFakeRate->isInputDownSysFakeRate;
}

void FakeHist::Initial(int passTTT, int passTTL, int passTLT, int passLTT, int passTLL, int passLTL, int passLLT)
{
 this->passTTT = passTTT;
 this->passTTL = passTTL;
 this->passTLT = passTLT;
 this->passLTT = passLTT;
 this->passTLL = passTLL;
 this->passLTL = passLTL;
 this->passLLT = passLLT;

 this->passWeight[0] = passTTT;
 this->passWeight[1] = passTTL;
 this->passWeight[2] = passTLT;
 this->passWeight[3] = passLTT;
 this->passWeight[4] = passTLL;
 this->passWeight[5] = passLTL;
 this->passWeight[6] = passLLT;

}

void FakeHist::InitialWeight(double passTTTWeight, double passTTLWeight, double passTLTWeight, double passLTTWeight, double passTLLWeight, double passLTLWeight, double passLLTWeight)
{
 this->passTTTWeight = passTTTWeight;
 this->passTTLWeight = passTTLWeight;
 this->passTLTWeight = passTLTWeight;
 this->passLTTWeight = passLTTWeight;
 this->passTLLWeight = passTLLWeight;
 this->passLTLWeight = passLTLWeight;
 this->passLLTWeight = passLLTWeight;

 this->passWeight[0] = passTTT * passTTTWeight;
 this->passWeight[1] = passTTL * passTTLWeight;
 this->passWeight[2] = passTLT * passTLTWeight;
 this->passWeight[3] = passLTT * passLTTWeight;
 this->passWeight[4] = passTLL * passTLLWeight;
 this->passWeight[5] = passLTL * passLTLWeight;
 this->passWeight[6] = passLLT * passLLTWeight;

}

void FakeHist::Fill(double par, double Weight)
{
 this->doFakeRate = 1;

 if(myFakeRate->isUnknown) return;
 if(myFakeRate->F1 < -900.0) return;

 myHist["TTT"]->Fill(par, Weight * passTTT * passTTTWeight);
 myHist["TTL"]->Fill(par, Weight * passTTL * passTTLWeight * (myFakeRate->F3));
 myHist["TLT"]->Fill(par, Weight * passTLT * passTLTWeight * (myFakeRate->F2));
 myHist["LTT"]->Fill(par, Weight * passLTT * passLTTWeight * (myFakeRate->F1));
 myHist["TLL"]->Fill(par, Weight * passTLL * passTLLWeight * (myFakeRate->F2) * (myFakeRate->F3) * (-1));
 myHist["LTL"]->Fill(par, Weight * passLTL * passLTLWeight * (myFakeRate->F1) * (myFakeRate->F3) * (-1));
 myHist["LLT"]->Fill(par, Weight * passLLT * passLLTWeight * (myFakeRate->F1) * (myFakeRate->F2) * (-1));

}

void FakeHist::FillFullMatrix(double par, double Weight)
{
 this->doFakeRate = 2;

 if(myFakeRate->isUnknown) return;
 if(!myFakeRate->InverseFakeMatrix) return;

 for(int iFake = 0; iFake < 7; iFake++){
   double FakeWeight = myFakeRate->InverseFakeMatrix->GetBinContent(1, iFake + 1);
   myHist_RRR->Fill(par, Weight * passWeight[iFake] * FakeWeight);
 }

 for(int iFake = 0; iFake < 7; iFake++){
   double FakeWeight = myFakeRate->InverseFakeMatrix->GetBinContent(2, iFake + 1);
   myHist_RRF->Fill(par, Weight * passWeight[iFake] * FakeWeight);
 }

 for(int iFake = 0; iFake < 7; iFake++){
   double FakeWeight = myFakeRate->InverseFakeMatrix->GetBinContent(3, iFake + 1);
   myHist_RFR->Fill(par, Weight * passWeight[iFake] * FakeWeight);
 }

 for(int iFake = 0; iFake < 7; iFake++){
   double FakeWeight = myFakeRate->InverseFakeMatrix->GetBinContent(4, iFake + 1);
   myHist_FRR->Fill(par, Weight * passWeight[iFake] * FakeWeight);
 }

 for(int iFake = 0; iFake < 7; iFake++){
   double FakeWeight = myFakeRate->InverseFakeMatrix->GetBinContent(5, iFake + 1);
   myHist_RFF->Fill(par, Weight * passWeight[iFake] * FakeWeight);
 }

 for(int iFake = 0; iFake < 7; iFake++){
   double FakeWeight = myFakeRate->InverseFakeMatrix->GetBinContent(6, iFake + 1);
   myHist_FRF->Fill(par, Weight * passWeight[iFake] * FakeWeight);
 }

 for(int iFake = 0; iFake < 7; iFake++){
   double FakeWeight = myFakeRate->InverseFakeMatrix->GetBinContent(7, iFake + 1);
   myHist_FFR->Fill(par, Weight * passWeight[iFake] * FakeWeight);
 }

}

void FakeHist::GetFakeHist()
{
 FinalFakeHist = (TH1D *)myHist["TTT"]->Clone(HistName + "_Fake");
 FinalFakeHist->Reset();

 FinalFakeHist->Add(myHist["TTL"]);
 FinalFakeHist->Add(myHist["TLT"]);
 FinalFakeHist->Add(myHist["LTT"]);
 FinalFakeHist->Add(myHist["TLL"]);
 FinalFakeHist->Add(myHist["LTL"]);
 FinalFakeHist->Add(myHist["LLT"]);

 myHist["TTT"]->Write();
 myHist["TTL"]->Write();
 myHist["TLT"]->Write();
 myHist["LTT"]->Write();
 myHist["TLL"]->Write();
 myHist["LTL"]->Write();
 myHist["LLT"]->Write();

 FinalFakeHist->Write();
}

void FakeHist::GetFakeHistFullMatrix()
{
 myHist["TTT"]->Write();
 myHist["TTL"]->Write();
 myHist["TLT"]->Write();
 myHist["LTT"]->Write();
 myHist["TLL"]->Write();
 myHist["LTL"]->Write();
 myHist["LLT"]->Write();


 FinalFakeHist = (TH1D *)myHist_RRR->Clone(HistName + "_Fake");
 FinalFakeHist->Reset();

 FinalFakeHist->Add(myHist_RRF);
 FinalFakeHist->Add(myHist_RFR);
 FinalFakeHist->Add(myHist_FRR);
 FinalFakeHist->Add(myHist_RFF);
 FinalFakeHist->Add(myHist_FRF);
 FinalFakeHist->Add(myHist_FFR);

 myHist_RRR->Write();
 myHist_RRF->Write();
 myHist_RFR->Write();
 myHist_FRR->Write();
 myHist_RFF->Write();
 myHist_FRF->Write();
 myHist_FFR->Write();
 
 FinalFakeHist->Write();

}

void FakeHist::DeleteHist()
{
 for(int iFake = 0; iFake < FakeHist_1d.size(); iFake++){
   delete FakeHist_1d.at(iFake);
 }

 FakeHist_1d.clear();
}

void FakeHist::Add(FakeHist* hist1)
{
 for(int iFake = 0; iFake < FakeHist_1d.size(); iFake++){
   FakeHist_1d.at(iFake)->Add((hist1->FakeHist_1d).at(iFake));
 }
}

void FakeHist::Reset()
{
 for(int iFake = 0; iFake < FakeHist_1d.size(); iFake++){
   FakeHist_1d.at(iFake)->Reset();
 }
}

void FakeHist::Write()
{
 if(this->doFakeRate == 1) GetFakeHist();
 if(this->doFakeRate == 2) GetFakeHistFullMatrix();
}

