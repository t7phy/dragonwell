#include "FillRoot/FillHepMC.h"

using namespace std;

void FillHepMC::DefineTree()
{
 tree->Branch("GammaPx",&GammaPx,"GammaPx[10]/D");
 tree->Branch("GammaPy",&GammaPy,"GammaPy[10]/D");
 tree->Branch("GammaPz",&GammaPz,"GammaPz[10]/D");
 tree->Branch("GammaE",&GammaE,"Gamma[10]/D");
 tree->Branch("GammaMother",&GammaMother,"GammaMother[10]/I");
 tree->Branch("GammaNumber",&GammaNumber,"GammaNumber/I");

 tree->Branch("ElectronPx",&ElectronPx,"ElectronPx/D");
 tree->Branch("ElectronPy",&ElectronPy,"ElectronPy/D");
 tree->Branch("ElectronPz",&ElectronPz,"ElectronPz/D");
 tree->Branch("ElectronE",&ElectronE,"ElectronE/D");
 tree->Branch("ElectronFlavor",&ElectronFlavor,"ElectronFlavor/I");

 tree->Branch("eNeutrinoPx",&eNeutrinoPx,"eNeutrinoPx/D");
 tree->Branch("eNeutrinoPy",&eNeutrinoPy,"eNeutrinoPy/D");
 tree->Branch("eNeutrinoPz",&eNeutrinoPz,"eNeutrinoPz/D");
 tree->Branch("eNeutrinoE",&eNeutrinoE,"eNeutrinoE/D");

 tree->Branch("MuonPx",&MuonPx,"MuonPx/D");
 tree->Branch("MuonPy",&MuonPy,"MuonPy/D");
 tree->Branch("MuonPz",&MuonPz,"MuonPz/D");
 tree->Branch("MuonE",&MuonE,"MuonE/D");
 tree->Branch("MuonFlavor",&MuonFlavor,"MuonFlavor/I");

 tree->Branch("mNeutrinoPx",&mNeutrinoPx,"mNeutrinoPx/D");
 tree->Branch("mNeutrinoPy",&mNeutrinoPy,"mNeutrinoPy/D");
 tree->Branch("mNeutrinoPz",&mNeutrinoPz,"mNeutrinoPz/D");
 tree->Branch("mNeutrinoE",&mNeutrinoE,"mNeutrinoE/D");

 tree->Branch("quark_flavour",&quark_flavour,"quark_flavour[2]/I");
 tree->Branch("QuarkPx",&QuarkPx,"QuarkPx[2]/D");
 tree->Branch("QuarkPy",&QuarkPy,"QuarkPy[2]/D");
 tree->Branch("QuarkPz",&QuarkPz,"QuarkPz[2]/D");
 tree->Branch("QuarkE",&QuarkE,"QuarkE[2]/D");

 tree->Branch("x1",&x1,"x1/D");
 tree->Branch("x2",&x2,"x2/D");

 //tree->Branch("WeightNames", "vector<string>", &WeightNames);
 tree->Branch("Weights", "vector<float>", &Weights);

 DefineMetaTree();
}

void FillHepMC::DefineMetaTree()
{
 metaTree = new TTree("metaTree", "metaTree");
 metaTree->SetDirectory(file);
 metaTree->Branch("WeightNames", "vector<string>", &WeightNames);
}

void FillHepMC::FillIn()
{
 for(int i = 0; i < 3; i++){
   getline(infile, FileLine);
   cout<<FileLine<<endl;
 }

 int count = 0;

 TString Symbol;
 infile >> Symbol;

 while(1){
   count++;
   ResetEvent();
   if(count % 10000 == 0) cout<<"Finish event: "<<count<<endl;

   FillE();
   infile >> Symbol;
   FillN();
   infile >> Symbol;
   FillU();
   infile >> Symbol;
   FillC();
   infile >> Symbol;
   FillF();

   while(1){
     infile >> Symbol;
     if(Symbol == "P"){
       FillP();
     }
     if(Symbol == "V"){
       FillV();
     }
     if(Symbol != "P" && Symbol != "V") break;
   }

   if(isTest){
     cout<<quark_flavour[0]<<endl;
     cout<<ElectronPx<<" "<<ElectronPy<<" "<<ElectronPz<<" "<<ElectronE<<endl;
     cout<<eNeutrinoPx<<" "<<eNeutrinoPy<<" "<<eNeutrinoPz<<" "<<eNeutrinoE<<endl;
     cout<<MuonPx<<" "<<MuonPy<<" "<<MuonPz<<" "<<MuonE<<" "<<endl;
     cout<<mNeutrinoPx<<" "<<mNeutrinoPy<<" "<<mNeutrinoPz<<" "<<mNeutrinoE<<endl;
   }
   if(isTest && count == 10) break;

   if(isTest) cout<<"Fill one event..."<<endl;
   tree->Fill();
   if(count == 1) metaTree->Fill();

   if(Symbol != "E") break;
 }

 file->Write();
 file->Close();
}

void FillHepMC::FillE()
{
 RandomLists.clear();
 Weights.clear();

 infile >> EventNumber >> InterNumber >> EventScale >> alpha_s >> alpha_ew;
 infile >> SignalID >> SignalBarCode >> NVertex >> Beam1BarCode >> Beam2BarCode;
 infile >> NRandomList;
 for(int i = 0; i < NRandomList; i++){
   long Random;
   infile >> Random;
   RandomLists.push_back(Random);
 }
 infile >> NWeight;
 for(int i = 0; i < NWeight; i++){
   float weight;
   infile >> weight;
   Weights.push_back(weight);
 }

}

void FillHepMC::FillN()
{
 WeightNames.clear();

 infile >> NWeightName;
 for(int i = 0; i < NWeightName; i++){
   std::string weightName;
   infile >> weightName;
   WeightNames.push_back(weightName);
 }

}

void FillHepMC::FillU()
{
 infile >> MomentumUnit >> LengthUnit;
}

void FillHepMC::FillC()
{
 infile >> CrossSection >> CrossSectionError;
}

void FillHepMC::FillH()
{
 infile >> NHardScatter >> NProjectile >> NTarget >> NNucleonCollision;
 infile >> NSpectatorNeutron >> NSpectatorProton >> NWoundedCollision >> NWoundedNCollision;
 infile >> NWoundedWounded >> ImpactParameter >> AzimuthalAngle >> Eccentricity >> NucleonNucleonCrossSection;
}

void FillHepMC::FillF()
{
 infile >> Flavor1 >> Flavor2;
 infile >> x1 >> x2 >> PDFScale;
 infile >> xf1 >> xf2 >> partonid1 >> partonid2;

 quark_flavour[0] = Flavor1;
 quark_flavour[1] = Flavor2;
}

void FillHepMC::FillV()
{
 VertexWeights.clear();

 if(!isSpeedUp){
   infile >> VertexBarCode >> VertexID;
   infile >> v_x >> v_y >> v_z >> ctau;
   infile >> Norphan >> NOutgoing >> NVertexWeightList;
   for(int i = 0; i < NVertexWeightList; i++){
     double weight;
     infile >> weight;
     VertexWeights.push_back(weight);
   }
 }
 else{
   getline(infile, FileLine);
 }

}

void FillHepMC::FillP()
{
 FlowCodeIndex.clear();
 FlowCode.clear();

 infile >> BarCode >> pdgID;

 if(pdgID == 11 || pdgID == -12 || pdgID == -13 || pdgID == 14){
   infile >> px >> py >> pz >> energy >> mass;
   infile >> StatusCode >> PolTheta >> PolPhi >> VertexBarCode;
   infile >> NFlowList;
   for(int i = 0; i < NFlowList; i++){
     int index, code;
     infile >> index >> code;
     FlowCodeIndex.push_back(index);
     FlowCode.push_back(code);
   }
 }
 else{
   getline(infile, FileLine);
 }

 if(pdgID == 11 && StatusCode == 11){
   ElectronPx = px;
   ElectronPy = py;
   ElectronPz = pz;
   ElectronE = energy;
   ElectronFlavor = -11;
 }
 if(pdgID == -12 && StatusCode == 11){
   eNeutrinoPx = px;
   eNeutrinoPy = py;
   eNeutrinoPz = pz;
   eNeutrinoE = energy;
 }
 if(pdgID == -13 && StatusCode == 11){
   MuonPx = px;
   MuonPy = py;
   MuonPz = pz;
   MuonE = energy;
   MuonFlavor = 13;
 }
 if(pdgID == 14 && StatusCode == 11){
   mNeutrinoPx = px;
   mNeutrinoPy = py;
   mNeutrinoPz = pz;
   mNeutrinoE = energy;
 }

}

void FillHepMC::ResetEvent()
{
 ElectronPx = 0.0;
 ElectronPy = 0.0;
 ElectronPz = 0.0;
 ElectronE = 0.0;
 ElectronFlavor = 0;

 eNeutrinoPx = 0.0;
 eNeutrinoPy = 0.0;
 eNeutrinoPz = 0.0;
 eNeutrinoE = 0.0;

 MuonPx = 0.0;
 MuonPy = 0.0;
 MuonPz = 0.0;
 MuonE = 0.0;
 MuonFlavor = 0;

 mNeutrinoPx = 0.0;
 mNeutrinoPy = 0.0;
 mNeutrinoPz = 0.0;
 mNeutrinoE = 0.0;

 quark_flavour[0] = 0;
 QuarkPx[0] = 0;
 QuarkPy[0] = 0;
 QuarkPz[0] = 0;
 QuarkE[0] = 0;

 quark_flavour[1] = 0;
 QuarkPx[1] = 0;
 QuarkPy[1] = 0;
 QuarkPz[1] = 0;
 QuarkE[1] = 0;

 GammaNumber = 0;
}
