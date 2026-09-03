#define TreeForMadGraph_cxx
#include "Analysis/TreeForMadGraph.h"

using namespace std;

TreeForMadGraph::TreeForMadGraph()
{
 Init();
}

TreeForMadGraph::~TreeForMadGraph()
{

}

void TreeForMadGraph::ConfigFile(int NFilePerJob, int iRound)
{
 FirstFile = iRound * NFilePerJob;
 EndFile = (iRound + 1) * NFilePerJob;

 if(EndFile >= RootNames.size()) EndFile = RootNames.size();

 for(int i = FirstFile; i < EndFile; i++){
   rootfile[i] = new TFile(RootNames.at(i));
   SetBranch(i);
 }
}

void TreeForMadGraph::ConfigFile(int ifile)
{
 OneFilePerJob = true;
 FirstFile = 0;
 EndFile = 1;

 rootfile[0] = new TFile(RootNames.at(ifile));
 SetBranch(0);

}

void TreeForMadGraph::InputFile(vector<TString> RootNames)
{
 this->RootNames = RootNames;

}

void TreeForMadGraph::SetBranch(int ifile)
{
//   fChain[ifile] = (TTree *)rootfile[ifile]->Get("LHEF");
   rootfile[ifile]->GetObject("LHEF", fChain[ifile]);

   fChain[ifile]->SetMakeClass(1);

   // Set branch addresses and branch pointers
   fChain[ifile]->SetBranchAddress("Event", &Event_, &b_Event_);
   fChain[ifile]->SetBranchAddress("Event.fUniqueID", Event_fUniqueID, &b_Event_fUniqueID);
   fChain[ifile]->SetBranchAddress("Event.fBits", Event_fBits, &b_Event_fBits);
   fChain[ifile]->SetBranchAddress("Event.Number", Event_Number, &b_Event_Number);
   fChain[ifile]->SetBranchAddress("Event.Nparticles", Event_Nparticles, &b_Event_Nparticles);
   fChain[ifile]->SetBranchAddress("Event.ProcessID", Event_ProcessID, &b_Event_ProcessID);
   fChain[ifile]->SetBranchAddress("Event.Weight", Event_Weight, &b_Event_Weight);
   fChain[ifile]->SetBranchAddress("Event.ScalePDF", Event_ScalePDF, &b_Event_ScalePDF);
   fChain[ifile]->SetBranchAddress("Event.CouplingQED", Event_CouplingQED, &b_Event_CouplingQED);
   fChain[ifile]->SetBranchAddress("Event.CouplingQCD", Event_CouplingQCD, &b_Event_CouplingQCD);
   fChain[ifile]->SetBranchAddress("Event_size", &Event_size, &b_Event_size);
   fChain[ifile]->SetBranchAddress("Rwgt", &Rwgt_, &b_Rwgt_);
   fChain[ifile]->SetBranchAddress("Rwgt.fUniqueID", Rwgt_fUniqueID, &b_Rwgt_fUniqueID);
   fChain[ifile]->SetBranchAddress("Rwgt.fBits", Rwgt_fBits, &b_Rwgt_fBits);
   fChain[ifile]->SetBranchAddress("Rwgt.Weight", Rwgt_Weight, &b_Rwgt_Weight);
   fChain[ifile]->SetBranchAddress("Rwgt_size", &Rwgt_size, &b_Rwgt_size);
   fChain[ifile]->SetBranchAddress("Particle", &Particle_);
   fChain[ifile]->SetBranchAddress("Particle.fUniqueID", Particle_fUniqueID, &b_Particle_fUniqueID);
   fChain[ifile]->SetBranchAddress("Particle.fBits", Particle_fBits, &b_Particle_fBits);
   fChain[ifile]->SetBranchAddress("Particle.PID", Particle_PID, &b_Particle_PID);
   fChain[ifile]->SetBranchAddress("Particle.Status", Particle_Status, &b_Particle_Status);
   fChain[ifile]->SetBranchAddress("Particle.Mother1", Particle_Mother1, &b_Particle_Mother1);
   fChain[ifile]->SetBranchAddress("Particle.Mother2", Particle_Mother2, &b_Particle_Mother2);
   fChain[ifile]->SetBranchAddress("Particle.ColorLine1", Particle_ColorLine1, &b_Particle_ColorLine1);
   fChain[ifile]->SetBranchAddress("Particle.ColorLine2", Particle_ColorLine2, &b_Particle_ColorLine2);
   fChain[ifile]->SetBranchAddress("Particle.Px", Particle_Px, &b_Particle_Px);
   fChain[ifile]->SetBranchAddress("Particle.Py", Particle_Py, &b_Particle_Py);
   fChain[ifile]->SetBranchAddress("Particle.Pz", Particle_Pz, &b_Particle_Pz);
   fChain[ifile]->SetBranchAddress("Particle.E", Particle_E, &b_Particle_E);
   fChain[ifile]->SetBranchAddress("Particle.M", Particle_M, &b_Particle_M);
   fChain[ifile]->SetBranchAddress("Particle.PT", Particle_PT, &b_Particle_PT);
   fChain[ifile]->SetBranchAddress("Particle.Eta", Particle_Eta, &b_Particle_Eta);
   fChain[ifile]->SetBranchAddress("Particle.Phi", Particle_Phi, &b_Particle_Phi);
   fChain[ifile]->SetBranchAddress("Particle.Rapidity", Particle_Rapidity, &b_Particle_Rapidity);
   fChain[ifile]->SetBranchAddress("Particle.LifeTime", Particle_LifeTime, &b_Particle_LifeTime);
   fChain[ifile]->SetBranchAddress("Particle.Spin", Particle_Spin, &b_Particle_Spin);
   fChain[ifile]->SetBranchAddress("Particle_size", &Particle_size, &b_Particle_size);

   TotalEntries[ifile] = fChain[ifile]->GetEntries();

}

void TreeForMadGraph::GetEntry(int ifile, long i)
{
 Long64_t ientry = fChain[ifile]->LoadTree(i);
 if (ientry < 0) return;
 fChain[ifile]->GetEntry(i);

}
