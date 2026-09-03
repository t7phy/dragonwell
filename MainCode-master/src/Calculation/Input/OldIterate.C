#include "Calculation/Iterate.h"

Iterate::Iterate()
{
 util = new CTUtil();

 Tier2Type = "CTEQ";
}

void Iterate::Initialize()
{
 setting.ConfigOrder(22, 3, 0, 0, 3, 3, 5);
 setting.ConfigDis(
  {99, 1, 230},
  {1.0, 0.0, 0.0}
 );
 setting.ConfigVbp(
  {99, 0, 0},
  {0.0, 0.0, 0.0}
 );

 map<tuple<int, int>, double> CPpara = {
   {make_tuple(1, 1), 0.01000}, {make_tuple(2, 1), 0.3}, {make_tuple(3, 1), 0.3}, {make_tuple(4, 1), 0.8}, {make_tuple(5, 1), 1.0}, {make_tuple(6, 1), 0.0},  {make_tuple(7, 1), 0.0},
   {make_tuple(1, 2), 0.00000}, {make_tuple(2, 2), 0.0}, {make_tuple(3, 2), 0.0}, {make_tuple(4, 2), 0.0}, {make_tuple(5, 2), 0.0}, {make_tuple(6, 2), 0.0},  {make_tuple(7, 2), 0.0},
   {make_tuple(1, 3), 0.00000}, {make_tuple(2, 3), 0.0}, {make_tuple(3, 3), 0.0}, {make_tuple(4, 3), 0.0}, {make_tuple(5, 3), 1.0}, {make_tuple(6, 3), 16.0}, {make_tuple(7, 3), 0.9},
   {make_tuple(1, 4), 0.00000}, {make_tuple(2, 4), 0.0}, {make_tuple(3, 4), 0.0}, {make_tuple(4, 4), 0.0}, {make_tuple(5, 4), 0.0}, {make_tuple(6, 4), 0.0},  {make_tuple(7, 4), 0.0},
   {make_tuple(1, 5), 0.00000}, {make_tuple(2, 5), 0.0}, {make_tuple(3, 5), 0.0}, {make_tuple(4, 5), 0.0}, {make_tuple(5, 5), 0.0}, {make_tuple(6, 5), 0.0},  {make_tuple(7, 5), 0.0}
 };

 setting.InputCP(CPpara);

 setting.ParseParameter("ForIterate.yml");
 setting.ParseConfig("Config.yml");
 Tolerance = setting.Tolerance;
 Tier2Type = setting.Tier2Type;

 QCDSet* m_qcd = new QCDSet();
 m_qcd->SetNfTotal(setting.Nflv);
 m_qcd->SetPoleMasscbt(setting.mc, setting.mb, setting.mt);
 m_qcd->SetAmhatf();
 setting.Amhat = m_qcd->Amhat;
 delete m_qcd;

 m_pdf_Q0 = new PDFEvolve();

 map<TString, double> p = setting.FittingParameter;

 vector<TString> FlavorList = setting.FlavorList;
 vector<int> FlagList = setting.FlagList;

 for(int iflavor = 0; iflavor < FlavorList.size(); iflavor++){
   m_pdf_Q0->SetParameter(FlavorList.at(iflavor), setting.ShapeParameterValue.at(FlavorList.at(iflavor)));
 }

 m_pdf_Q0->SetInitialgluonMomentum(setting.InitialgluonMomentum);
 m_pdf_Q0->SetInitialStrangeB0(setting.InitialStrangeB0);

// m_pdf_Q0->SetgluonMomentumPar(0.0);
// m_pdf_Q0->SetStrangeB0Par(0.0);

 m_pdf_Q0->Initialize(setting.IFun, FlavorList, FlagList);
 m_pdf_Q0->ParameterOutput();

 m_hoppet = new HoppetInterface();
 m_hoppet->SetAlphaSQ0(setting.AlphaS, setting.AlphaS_Q0);
 m_hoppet->SetMcbt(setting.Amhat(4), setting.Amhat(5), setting.Amhat(6));

 if(setting.isEvolveSmallx) m_hoppet->SetEvolveSmallx(); // Just need to be done once. All the other Initialize() call will use the same setting.

 if(setting.EvolveType == "Hoppet"){
   m_hoppet->Initialize(m_pdf_Q0, setting.Qini);
 }
 else if(setting.EvolveType == "APFEL"){
   m_hoppet->InitializeAPFEL(m_pdf_Q0, setting.Qini);
 }
 else if(setting.EvolveType == "APFELxx"){
   m_hoppet->InitializeAPFELxx(m_pdf_Q0, setting.Qini);
 }

 m_hoppet->SetQArray();
 m_hoppet->SetXArray();
 pdsReader* pdftable = m_hoppet->PrepareCTEQTable();

 setting.ConfigPDF(pdftable);

 setting.ParseDataList("DataList.yml");
 AllData.resize(setting.DataList.size());

 for(int idata = 0; idata < setting.DataList.size(); idata++){
   AllData.at(idata) = new Dataset(setting.DataList.at(idata).DataName);
   AllData.at(idata)->SetCut(setting);

   if(setting.DataList.at(idata).Normalization.size() != 0){
     double NormCentral = setting.DataList.at(idata).Normalization.at(0);
     if(setting.FittingParameter.count(setting.DataList.at(idata).NormParName) > 0) NormCentral = setting.FittingParameter.at(setting.DataList.at(idata).NormParName);
     AllData.at(idata)->InputNormalization(NormCentral, setting.DataList.at(idata).Normalization.at(1), setting.DataList.at(idata).Normalization.at(2));
   }

   AllData.at(idata)->ReadFile(setting.DataList.at(idata).DataPath,
                               setting.DataList.at(idata).DataType,
                               setting.DataList.at(idata).CalcMode,
                               setting.DataList.at(idata).Collider,
                               setting.DataList.at(idata).subType);

   if(setting.DataList.at(idata).ApplGrids.size() != 0){
     AllData.at(idata)->InputGridName(setting.DataList.at(idata).ApplGrids);
   }

   if(setting.DataList.at(idata).ApplRange.size() != 0){
     for(int i = 0; i < setting.DataList.at(idata).ApplRange.size(); i++){
       AllData.at(idata)->InputApplGridRange(setting.DataList.at(idata).ApplRange.at(i).at(0), setting.DataList.at(idata).ApplRange.at(i).at(1), setting.DataList.at(idata).ApplRange.at(i).at(2));
     }
   }

   if(setting.DataList.at(idata).FastNLOGrids.size() != 0){
     AllData.at(idata)->InputFNLOTableName(setting.DataList.at(idata).FastNLOGrids);
   }

   if(setting.DataList.at(idata).SystematicMethod.size() != 0){
     AllData.at(idata)->InputSystematicMethod(setting.DataList.at(idata).SystematicMethodMap);
   }

   if(setting.DataList.at(idata).KFactors.size() != 0){
     AllData.at(idata)->InputKFactorColumns(setting.DataList.at(idata).KFactors);
   }
 }

 m_fcn = new PDFChi2();
 m_fcn->BookLMPenalty(1, "ratioPDF", vector<int>{1}, vector<double>{10.0, 2.0, 0.2, 1e-8});
 m_fcn->BookLMPenalty(2, "ratioPDF", vector<int>{1}, vector<double>{10.0, 1.8, 0.4, 1e-5});
 m_fcn->BookLMPenalty(3, "LargeCoefficient", vector<int>{1}, vector<double>{0.01});
 m_fcn->BookLMPenalty(4, "SystematicShift", vector<int>{504, 25, 514, 23}, vector<double>{0.5, 0.5});
 m_fcn->ThreadSetup(setting.nDISThread, setting.nVBPThread);
 m_fcn->Initialize(AllData, setting);
 double Chi2 = m_fcn->GetChi2(true);

 cout<<"Initialize finish. Chi2 = "<<Chi2<<endl;

 NPar = setting.IterateParList.size();
}

/////////////////////////////////////////////////////////////////////////////////////////////////////

 //////////////////////////////
 // For Iterate Procedure    //
 // Method is based on paper //
 //////////////////////////////

void Iterate::IterateHessianBasedPaper()
{
 int irt;

 int maxIter = 100;

 Eigen::MatrixXd PhiMatrix = Eigen::MatrixXd(NPar, NPar);

 // Initialization
 umat = Eigen::MatrixXd::Identity(NPar, NPar);
 tvec = Eigen::VectorXd(NPar);

 evec = Eigen::VectorXd(NPar);

 for(int i = 0; i < NPar; i++){
   tvec(i) = 1.0;
 }

 xtrans = Eigen::VectorXd(NPar);
 for(int i = 0; i < NPar; i++){
   xtrans(i) = 0.0;
 }

 wtrans = Eigen::MatrixXd::Identity(NPar, NPar);

 double BestFitChi2 = m_fcn->GetChi2(false, true);
 cout<<"Starting iterate. Best fit chi2 = "<<BestFitChi2<<endl;

 NewParCentral.resize(NPar);
 ParStep.resize(NPar);

 for(int it = 1; it <= maxIter; it++){

   cout<<getTime()<<"  INFO| Iterate "<<it<<endl;

   // Calculate Phi Matrix

   // Diagonal terms
   for(int ipar = 0; ipar < NPar; ipar++){

     double up = 0.05;
     double step = 0.03 * sqrt(up);
     ParStep.at(ipar) = step;

     CalcNewParOn(ipar, step);
     double F1 = m_fcn->GetChi2(false);

     CalcNewParOn(ipar, step * (-1.0));
     double F2 = m_fcn->GetChi2(false);

     // Adjust the step size if the Delta Chi2 < 0.0009 * up (step = 0.03 * sqrt(up), up = 0.05)
     if(F1 - BestFitChi2 < 0.0009 * up || F2 - BestFitChi2 < 0.0009 * up){

       int nloop = 0;
       double Step1 = step;
       while(F1 - BestFitChi2 < 0.0009 * up){
         Step1 = Step1 * 2.0;
         CalcNewParOn(ipar, Step1);
         F1 = m_fcn->GetChi2(false);
         cout<<"Change the step1 of parameter "<<ipar<<" to "<<Step1<<". Delta Chi2 = "<<F1 - BestFitChi2<<endl;
         nloop++;

         if(nloop > 7){
           cout<<"Try too many times, revert the step to the initial one."<<endl;
           Step1 = 0.03 * sqrt(up);
           break;
         }
       }
       if(F1 - BestFitChi2 > 0.1 * up){
         Step1 = Step1 / sqrt(2.0);
         CalcNewParOn(ipar, Step1);
         F1 = m_fcn->GetChi2(false);
         cout<<"Delta Chi2 is too large for parameter "<<ipar<<", reduce the step to "<<Step1<<endl;
       }

       nloop = 0;
       double Step2 = step;
       while(F2 - BestFitChi2 < 0.0009 * up){
         Step2 = Step2 * 2.0;
         CalcNewParOn(ipar, Step2 * (-1.0));
         F2 = m_fcn->GetChi2(false);
         cout<<"Change the step2 of parameter "<<ipar<<" to "<<Step2<<". Delta Chi2 = "<<F2 - BestFitChi2<<endl;
         nloop++;

         if(nloop > 7){
           cout<<"Try too many times, revert the step to the initial one."<<endl;
           Step2 = 0.03 * sqrt(up);
           break;
         }
       }
       if(F2 - BestFitChi2 > 0.1 * up){
         Step2 = Step2 / sqrt(2.0);
         CalcNewParOn(ipar, Step2 * (-1.0));
         F2 = m_fcn->GetChi2(false);
         cout<<"Delta Chi2 is too large for parameter "<<ipar<<", reduce the step to "<<Step2<<endl;
       }

       if(Step1 > Step2){
         ParStep.at(ipar) = Step1;
         CalcNewParOn(ipar, ParStep.at(ipar) * (-1.0));
         F2 = m_fcn->GetChi2(false);
       }
       else{
         ParStep.at(ipar) = Step2;
         CalcNewParOn(ipar, ParStep.at(ipar));
         F1 = m_fcn->GetChi2(false);
       }

       cout<<"Change to final step for parameter "<<ipar<<" to "<<ParStep.at(ipar)<<". F1 = "<<F1<<" F2 = "<<F2<<endl;
     }


     // Finding new local minimum for parameter if the second derivative is negative
     double Solution = 0.0;
     double PlusSolution = 0.0;
     double MinusSolution = 0.0;
     double PlusChi2 = 0.0;
     double MinusChi2 = 0.0;
     if(F1 < BestFitChi2){
       double left = 0.0;
       double right = ParStep.at(ipar) * 3.0;
       auto FindingZeroDerivative = [&](double x){
         CalcNewParOn(ipar, x + ParStep.at(ipar));
         double F = m_fcn->GetChi2(false);
         CalcNewParOn(ipar, x);
         double F0 = m_fcn->GetChi2(false);
         cout<<"Try x = "<<x<<" F("<<x + ParStep.at(ipar)<<") = "<<F<<" F("<<x<<") = "<<F0<<" First derivative = "<<(F - F0) / ParStep.at(ipar)<<endl;
         return (F - F0) / ParStep.at(ipar);
       };

       PlusSolution = util->zbrnt(FindingZeroDerivative, left, right, 0.0001, irt); 
       CalcNewParOn(ipar, PlusSolution);
       PlusChi2 = m_fcn->GetChi2(false);
       cout<<"Plus direction changed. New solution is "<<PlusSolution<<" New chi2 = "<<PlusChi2<<endl;
     }
     if(F2 < BestFitChi2){
       double left = ParStep.at(ipar) * (-3.0);
       double right = 0.0;
       auto FindingZeroDerivative = [&](double x){
         CalcNewParOn(ipar, x - ParStep.at(ipar));
         double F = m_fcn->GetChi2(false);
         CalcNewParOn(ipar, x);
         double F0 = m_fcn->GetChi2(false);
         cout<<"Try x = "<<x<<" F("<<x<<") = "<<F0<<" F("<<x - ParStep.at(ipar)<<") = "<<F<<" First derivative = "<<(F0 - F) / ParStep.at(ipar)<<endl;
         return (F0 - F) / ParStep.at(ipar);
       };

       MinusSolution = util->zbrnt(FindingZeroDerivative, left, right, 0.0001, irt);   
       CalcNewParOn(ipar, MinusSolution);
       MinusChi2 = m_fcn->GetChi2(false);
       cout<<"Minus direction changed. New solution is "<<MinusSolution<<" New chi2 = "<<MinusChi2<<endl;
     }

     if(PlusSolution != 0.0 && MinusSolution == 0.0){
       Solution = PlusSolution;
     }
     else if(PlusSolution == 0.0 && MinusSolution != 0.0){
       Solution = MinusSolution;
     }
     else if(PlusSolution != 0.0 && MinusSolution != 0.0){
       Solution = PlusChi2 < MinusChi2 ? PlusSolution : MinusSolution;
     }

     if(Solution != 0.0){
       for(int i = 0; i < NPar; i++){
         xtrans(i) = xtrans(i) + wtrans(i, ipar) * Solution;
       }

       CalcNewParOn(ipar, ParStep.at(ipar));
       F1 = m_fcn->GetChi2(false);

       CalcNewParOn(ipar, ParStep.at(ipar) * (-1.0));
       F2 = m_fcn->GetChi2(false);

       CalcNewParOn(ipar, 0.0);
       BestFitChi2 = m_fcn->GetChi2(false, true);

       cout<<"Best fit chi2 is updated. New chi2 = "<<BestFitChi2<<". Central value of parameter z("<<ipar<<") is changed to "<<Solution<<endl;
     }

     double Derivative = (F1 + F2 - 2.0 * BestFitChi2) / (2.0 * ParStep.at(ipar) * ParStep.at(ipar));

     PhiMatrix(ipar, ipar) = Derivative;

     cout<<"Parameter "<<ipar<<": F1 = "<<F1<<" F2 = "<<F2<<" BestFitChi2 = "<<BestFitChi2<<" Derivative = "<<Derivative<<endl;
   }

   // Off-diagonal terms
   for(int ipar = 0; ipar < NPar - 1; ipar++){
     for(int jpar = ipar + 1; jpar < NPar; jpar++){

       double step1 = ParStep.at(ipar) / sqrt(2.0);
       double step2 = ParStep.at(jpar) / sqrt(2.0);

       CalcNewParOff(ipar, jpar, step1, step2);
       double F11 = m_fcn->GetChi2(false);

       CalcNewParOff(ipar, jpar, step1 * (-1.0), step2 * (-1.0));
       double F22 = m_fcn->GetChi2(false);

       CalcNewParOff(ipar, jpar, step1 * (-1.0), step2);
       double F21 = m_fcn->GetChi2(false);

       CalcNewParOff(ipar, jpar, step1, step2 * (-1.0));
       double F12 = m_fcn->GetChi2(false);

       double Derivative = (F11 + F22 - F12 - F21) / (8.0 * step1 * step2);

       PhiMatrix(ipar, jpar) = Derivative;

       cout<<"F11 = "<<F11<<" F22 = "<<F22<<" F12 = "<<F12<<" F21 = "<<F21<<" Derivative = "<<Derivative<<endl;
     }
   }

   for(int ipar = 0; ipar < NPar - 1; ipar++){
     for(int jpar = ipar + 1; jpar < NPar; jpar++){
       PhiMatrix(jpar, ipar) = PhiMatrix(ipar, jpar);
     }
   }

   // Construct Hessian Matrix from tvec(1 / sqrt(Eigen Values)) and umat(Eigen Vectors)
   Hessian = Eigen::MatrixXd(NPar, NPar);
   for(int i = 0; i < NPar; i++){
     for(int j = 0; j < NPar; j++){
       double sum = 0.0;
       for(int m = 0; m < NPar; m++){
         for(int n = 0; n < NPar; n++){
           sum += PhiMatrix(m, n) * umat(i, m) * umat(j, n) / tvec(m) / tvec(n);
         }
       }
       Hessian(i, j) = sum;
     }
   }

   // Get Sorted Eigen Values and Eigen Vectors
   Eigen::EigenSolver<Eigen::MatrixXd> es(Hessian);
   Eigen::MatrixXd D = es.pseudoEigenvalueMatrix();
   Eigen::MatrixXd V = es.pseudoEigenvectors();

   map<double, Eigen::VectorXd> SortEigenValues;
   for(int i = 0; i < NPar; i++){
     V.col(i).normalize();
     SortEigenValues[D(i, i) * (-1.0)] = V.col(i);
   }

   Eigen::MatrixXd SortedD = Eigen::MatrixXd::Identity(NPar, NPar);
   Eigen::MatrixXd SortedV = Eigen::MatrixXd(NPar, NPar);

   int iPar = 0;
   for(auto iter = SortEigenValues.begin(); iter != SortEigenValues.end(); iter++){
     SortedD(iPar, iPar) = iter->first * (-1.0);

     for(int i = 0; i < NPar; i++){
       SortedV(i, iPar) = iter->second(i);
     }
     iPar++;
   }
   SortEigenValues.clear();

   // Force all eigenvalues to be positive
   int Nnegative = 0;
   for(int i = 0; i < NPar; i++){
     if(SortedD(i, i) < 0.0) Nnegative++;
   }

   // Check whether all of negative eigenvalues are in the end of array
   if(Nnegative > 0){
     int inegative = 0;
     int NLastPositive = 0;
     for(int i = NPar - 1; i >= 0; i--){
       if(SortedD(i, i) < 0.0) inegative++;
       if(SortedD(i, i) >= 0.0) NLastPositive++;
       if(inegative == Nnegative) break;
     }
     if(NLastPositive > 0){
       Nnegative = Nnegative + NLastPositive;
       cout<<"Sorting failed! "<<NLastPositive<<" negative eigenvalues are wrongly saved to be positive."<<endl;
       cout<<"Forcing the number of negative eigenvalues to be "<<Nnegative<<endl;
     }
   }

   double EigenValueMin = SortedD(0, 0);

   if(NPar - Nnegative >= 1){
     EigenValueMin = EigenValueMin < 0.1 * SortedD(NPar - Nnegative - 1, NPar - Nnegative - 1) ? EigenValueMin : 0.1 * SortedD(NPar - Nnegative - 1, NPar - Nnegative - 1);
   }

   if(NPar - Nnegative >= 2){ 
     EigenValueMin = EigenValueMin < 0.03 * SortedD(NPar - Nnegative - 2, NPar - Nnegative - 2) ? EigenValueMin : 0.03 * SortedD(NPar - Nnegative - 2, NPar - Nnegative - 2);
   }

   if(NPar - Nnegative >= 3){ 
     EigenValueMin = EigenValueMin < 0.01 * SortedD(NPar - Nnegative - 3, NPar - Nnegative - 3) ? EigenValueMin : 0.01 * SortedD(NPar - Nnegative - 3, NPar - Nnegative - 3);
   }

   if(EigenValueMin > SortedD(NPar - 1, NPar - 1)){
     cout<<"Force all eigenvalues > "<<EigenValueMin<<endl;
     for(int i = 0; i < NPar; i++){
       if(SortedD(i, i) < EigenValueMin) cout<<"The "<<i<<"th eigenvalue has been set to "<<EigenValueMin<<". Original value is "<<SortedD(i, i)<<endl;
       SortedD(i, i) = SortedD(i, i) > EigenValueMin ? SortedD(i, i) : EigenValueMin;
     }
   }

   // Find new local minimum for flattest direction and negative eigen values direction

   int nFlat = Nnegative + 2;

   // Update tvec and umat
   for(int i = 0; i < NPar; i++){
     if(fabs(SortedD(i, i)) < 1e-20){
       cout<<"ERROR! The eigenvalue "<<i<<" equals to 0."<<endl;
       return;
     }
     tvec(i) = 1.0 / sqrt(SortedD(i, i));
   }

   for(int i = 0; i < NPar; i++){
     for(int j = 0; j < NPar; j++){
       umat(i, j) = SortedV(i, j);
     }
   }

   for(int i = 0; i < NPar; i++){
     evec(i) = SortedD(i, i);
   }
   vmat = umat;

   // Calculate dmeas to see if we can stop the iterate
   double dmeas1 = 0.0;
   for(int i = 0; i < NPar; i++){
     dmeas1 = dmeas1 > fabs(PhiMatrix(i, i) - 1.0) ? dmeas1 : fabs(PhiMatrix(i, i) - 1.0);
   }

   double dmeas2 = 0.0;
   for(int i = 1; i < NPar; i++){
     for(int j = 0; j < i; j++){
       dmeas2 = dmeas2 > fabs(PhiMatrix(i, j)) ? dmeas2 : fabs(PhiMatrix(i, j));
     }
   }

   double dmeas = dmeas1 + dmeas2;
   cout<<getTime()<<"  INFO| iter "<<it<<" dmeas = "<<dmeas<<endl;

   if(dmeas < dmeasRequirement){
     cout<<"Final Eigen values: "<<endl;
     cout<<evec<<endl;
     cout<<"Final Eigen vectors: "<<endl;
     cout<<umat<<endl;
     cout<<"Final xtrans: "<<endl;
     cout<<xtrans<<endl;
     cout<<"Final wtrans: "<<endl;
     cout<<wtrans<<endl;
     cout<<"Final PhiMatrix:"<<endl;
     cout<<PhiMatrix<<endl;

     break;
   }

   // Calculate wtrans
   for(int i = 0; i < NPar; i++){
     for(int j = 0; j < NPar; j++){
       wtrans(i, j) = vmat(i, j) / sqrt(evec(j));
     }
   }

   cout<<"Eigen values: "<<endl;
   cout<<evec<<endl;
   cout<<"Eigen vectors: "<<endl;
   cout<<umat<<endl;
   cout<<"xtrans: "<<endl;
   cout<<xtrans<<endl;
   cout<<"wtrans: "<<endl;
   cout<<wtrans<<endl;
   cout<<"PhiMatrix:"<<endl;
   cout<<PhiMatrix<<endl;

   if(it == maxIter){
     cout<<"WARNING! Iterate doesn't converge in "<<maxIter<<" times."<<endl;
   }
 }

 // Construct Hessian Matrix from evec(Eigen Values) and vmat(Eigen Vectors)
 Hessian = Eigen::MatrixXd(NPar, NPar);
 for(int i = 0; i < NPar; i++){
   for(int j = 0; j < NPar; j++){
     double sum = 0.0;
     for(int k = 0; k < NPar; k++){
       sum += evec(k) * vmat(i, k) * vmat(j, k);
     }
     Hessian(i, j) = sum;
   }
 }

 OutputHessianFortran("newpdf.ev");
}

/////////////////////////////////////////////////////////////////////////////////////////////////////

 /////////////////////////////
 // For Iterate Procedure   //
 // Method is based on code //
 /////////////////////////////

void Iterate::IterateHessian()
{
 int irt;

 int maxIter = 100;

 Eigen::MatrixXd PhiMatrix = Eigen::MatrixXd(NPar, NPar);
 Hessian = Eigen::MatrixXd(NPar, NPar);

 // Initialization
 umat = Eigen::MatrixXd::Identity(NPar, NPar);
 tvec = Eigen::VectorXd(NPar);

 evec = Eigen::VectorXd(NPar);

 for(int i = 0; i < NPar; i++){
   tvec(i) = 1.0;
 }

 xtrans = Eigen::VectorXd(NPar);
 for(int i = 0; i < NPar; i++){
   xtrans(i) = 0.0;
 }

 wtrans = Eigen::MatrixXd::Identity(NPar, NPar);

 double BestFitChi2 = m_fcn->GetChi2(false, true);
 cout<<"Starting iterate. Best fit chi2 = "<<BestFitChi2<<endl;

 NewParCentral.resize(NPar);
 ParStep.resize(NPar);

 for(int it = 1; it <= maxIter; it++){

   cout<<getTime()<<"  INFO| Iterate "<<it<<endl;

   // Calculate Phi Matrix

   // Diagonal terms
   for(int ipar = 0; ipar < NPar; ipar++){

     double up = 0.05;
     double step = 0.03 * sqrt(up);
     ParStep.at(ipar) = step;

     CalcNewParOn(ipar, step);
     double F1 = m_fcn->GetChi2(false);

     CalcNewParOn(ipar, step * (-1.0));
     double F2 = m_fcn->GetChi2(false);

     // Adjust the step size if the Delta Chi2 < 0.0009 * up (step = 0.03 * sqrt(up), up = 0.05)
     if(F1 - BestFitChi2 < 0.0009 * up || F2 - BestFitChi2 < 0.0009 * up){

       int nloop = 0;
       double Step1 = step;
       while(F1 - BestFitChi2 < 0.0009 * up){
         Step1 = Step1 * 2.0;
         CalcNewParOn(ipar, Step1);
         F1 = m_fcn->GetChi2(false);
         cout<<"Change the step1 of parameter "<<ipar<<" to "<<Step1<<". Delta Chi2 = "<<F1 - BestFitChi2<<endl;
         nloop++;

         if(nloop > 7){
           cout<<"Try too many times, revert the step to the initial one."<<endl;
           Step1 = 0.03 * sqrt(up);
           break;
         }
       }
       if(F1 - BestFitChi2 > 0.1 * up){
         Step1 = Step1 / sqrt(2.0);
         CalcNewParOn(ipar, Step1);
         F1 = m_fcn->GetChi2(false);
         cout<<"Delta Chi2 is too large for parameter "<<ipar<<", reduce the step to "<<Step1<<endl;
       }

       nloop = 0;
       double Step2 = step;
       while(F2 - BestFitChi2 < 0.0009 * up){
         Step2 = Step2 * 2.0;
         CalcNewParOn(ipar, Step2 * (-1.0));
         F2 = m_fcn->GetChi2(false);
         cout<<"Change the step2 of parameter "<<ipar<<" to "<<Step2<<". Delta Chi2 = "<<F2 - BestFitChi2<<endl;
         nloop++;

         if(nloop > 7){
           cout<<"Try too many times, revert the step to the initial one."<<endl;
           Step2 = 0.03 * sqrt(up);
           break;
         }
       }
       if(F2 - BestFitChi2 > 0.1 * up){
         Step2 = Step2 / sqrt(2.0);
         CalcNewParOn(ipar, Step2 * (-1.0));
         F2 = m_fcn->GetChi2(false);
         cout<<"Delta Chi2 is too large for parameter "<<ipar<<", reduce the step to "<<Step2<<endl;
       }

       if(Step1 > Step2){
         ParStep.at(ipar) = Step1;
         CalcNewParOn(ipar, ParStep.at(ipar) * (-1.0));
         F2 = m_fcn->GetChi2(false);
       }
       else{
         ParStep.at(ipar) = Step2;
         CalcNewParOn(ipar, ParStep.at(ipar));
         F1 = m_fcn->GetChi2(false);
       }

       cout<<"Change to final step for parameter "<<ipar<<" to "<<ParStep.at(ipar)<<". F1 = "<<F1<<" F2 = "<<F2<<endl;
     }


     // Finding new local minimum for parameter if the second derivative is negative
     double Solution = 0.0;
     double PlusSolution = 0.0;
     double MinusSolution = 0.0;
     double PlusChi2 = 0.0;
     double MinusChi2 = 0.0;
     if(F1 < BestFitChi2){
       double left = 0.0;
       double right = ParStep.at(ipar) * 3.0;
       auto FindingZeroDerivative = [&](double x){
         CalcNewParOn(ipar, x + ParStep.at(ipar));
         double F = m_fcn->GetChi2(false);
         CalcNewParOn(ipar, x);
         double F0 = m_fcn->GetChi2(false);
         cout<<"Try x = "<<x<<" F("<<x + ParStep.at(ipar)<<") = "<<F<<" F("<<x<<") = "<<F0<<" First derivative = "<<(F - F0) / ParStep.at(ipar)<<endl;
         return (F - F0) / ParStep.at(ipar);
       };

       PlusSolution = util->zbrnt(FindingZeroDerivative, left, right, 0.0001, irt);
       CalcNewParOn(ipar, PlusSolution);
       PlusChi2 = m_fcn->GetChi2(false);
       cout<<"Plus direction changed. New solution is "<<PlusSolution<<" New chi2 = "<<PlusChi2<<endl;
     }
     if(F2 < BestFitChi2){
       double left = ParStep.at(ipar) * (-3.0);
       double right = 0.0;
       auto FindingZeroDerivative = [&](double x){
         CalcNewParOn(ipar, x - ParStep.at(ipar));
         double F = m_fcn->GetChi2(false);
         CalcNewParOn(ipar, x);
         double F0 = m_fcn->GetChi2(false);
         cout<<"Try x = "<<x<<" F("<<x<<") = "<<F0<<" F("<<x - ParStep.at(ipar)<<") = "<<F<<" First derivative = "<<(F0 - F) / ParStep.at(ipar)<<endl;
         return (F0 - F) / ParStep.at(ipar);
       };

       MinusSolution = util->zbrnt(FindingZeroDerivative, left, right, 0.0001, irt);
       CalcNewParOn(ipar, MinusSolution);
       MinusChi2 = m_fcn->GetChi2(false);
       cout<<"Minus direction changed. New solution is "<<MinusSolution<<" New chi2 = "<<MinusChi2<<endl;
     }

     if(PlusSolution != 0.0 && MinusSolution == 0.0){
       Solution = PlusSolution;
     }
     else if(PlusSolution == 0.0 && MinusSolution != 0.0){
       Solution = MinusSolution;
     }
     else if(PlusSolution != 0.0 && MinusSolution != 0.0){
       Solution = PlusChi2 < MinusChi2 ? PlusSolution : MinusSolution;
     }

     if(Solution != 0.0){
       for(int i = 0; i < NPar; i++){
         xtrans(i) = xtrans(i) + wtrans(i, ipar) * Solution;
       }

       CalcNewParOn(ipar, ParStep.at(ipar));
       F1 = m_fcn->GetChi2(false);

       CalcNewParOn(ipar, ParStep.at(ipar) * (-1.0));
       F2 = m_fcn->GetChi2(false);

       CalcNewParOn(ipar, 0.0);
       BestFitChi2 = m_fcn->GetChi2(false, true);

       cout<<"Best fit chi2 is updated. New chi2 = "<<BestFitChi2<<". Central value of parameter z("<<ipar<<") is changed to "<<Solution<<endl;
     }

     double Derivative = (F1 + F2 - 2.0 * BestFitChi2) / (2.0 * ParStep.at(ipar) * ParStep.at(ipar));

     PhiMatrix(ipar, ipar) = Derivative;

     cout<<"Parameter "<<ipar<<": F1 = "<<F1<<" F2 = "<<F2<<" BestFitChi2 = "<<BestFitChi2<<" Derivative = "<<Derivative<<endl;
   }

   // Off-diagonal terms
   for(int ipar = 0; ipar < NPar - 1; ipar++){
     for(int jpar = ipar + 1; jpar < NPar; jpar++){

       double step1 = ParStep.at(ipar) / sqrt(2.0);
       double step2 = ParStep.at(jpar) / sqrt(2.0);

       CalcNewParOff(ipar, jpar, step1, step2);
       double F11 = m_fcn->GetChi2(false);

       CalcNewParOff(ipar, jpar, step1 * (-1.0), step2 * (-1.0));
       double F22 = m_fcn->GetChi2(false);

       CalcNewParOff(ipar, jpar, step1 * (-1.0), step2);
       double F21 = m_fcn->GetChi2(false);

       CalcNewParOff(ipar, jpar, step1, step2 * (-1.0));
       double F12 = m_fcn->GetChi2(false);

       double Derivative = (F11 + F22 - F12 - F21) / (8.0 * step1 * step2);

       PhiMatrix(ipar, jpar) = Derivative;

       cout<<"F11 = "<<F11<<" F22 = "<<F22<<" F12 = "<<F12<<" F21 = "<<F21<<" Derivative = "<<Derivative<<endl;
     }
   }

   for(int ipar = 0; ipar < NPar - 1; ipar++){
     for(int jpar = ipar + 1; jpar < NPar; jpar++){
       PhiMatrix(jpar, ipar) = PhiMatrix(ipar, jpar);
     }
   }

   // Get Sorted Eigen Values and Eigen Vectors
   Eigen::EigenSolver<Eigen::MatrixXd> es(PhiMatrix);
   Eigen::MatrixXd D = es.pseudoEigenvalueMatrix();
   Eigen::MatrixXd V = es.pseudoEigenvectors();

   map<double, Eigen::VectorXd> SortEigenValues;
   for(int i = 0; i < NPar; i++){
     V.col(i).normalize();
     SortEigenValues[D(i, i) * (-1.0)] = V.col(i);
   }

   Eigen::MatrixXd SortedD = Eigen::MatrixXd::Identity(NPar, NPar);
   Eigen::MatrixXd SortedV = Eigen::MatrixXd(NPar, NPar);

   int iPar = 0;
   for(auto iter = SortEigenValues.begin(); iter != SortEigenValues.end(); iter++){
     SortedD(iPar, iPar) = iter->first * (-1.0);

     for(int i = 0; i < NPar; i++){
       SortedV(i, iPar) = iter->second(i);
     }
     iPar++;
   }
   SortEigenValues.clear();

   // Force all eigenvalues to be positive
   int Nnegative = 0;
   for(int i = 0; i < NPar; i++){
     if(SortedD(i, i) < 0.0) Nnegative++;
   }

   // Check whether all of negative eigenvalues are in the end of array
   if(Nnegative > 0){
     int inegative = 0;
     int NLastPositive = 0;
     for(int i = NPar - 1; i >= 0; i--){
       if(SortedD(i, i) < 0.0) inegative++;
       if(SortedD(i, i) >= 0.0) NLastPositive++;
       if(inegative == Nnegative) break;
     }
     if(NLastPositive > 0){
       Nnegative = Nnegative + NLastPositive;
       cout<<"Sorting failed! "<<NLastPositive<<" negative eigenvalues are wrongly saved to be positive."<<endl;
       cout<<"Forcing the number of negative eigenvalues to be "<<Nnegative<<endl;
     }
   }

   double EigenValueMin = SortedD(0, 0);

   if(NPar - Nnegative >= 1){
     EigenValueMin = EigenValueMin < 0.1 * SortedD(NPar - Nnegative - 1, NPar - Nnegative - 1) ? EigenValueMin : 0.1 * SortedD(NPar - Nnegative - 1, NPar - Nnegative - 1);
   }

   if(NPar - Nnegative >= 2){
     EigenValueMin = EigenValueMin < 0.03 * SortedD(NPar - Nnegative - 2, NPar - Nnegative - 2) ? EigenValueMin : 0.03 * SortedD(NPar - Nnegative - 2, NPar - Nnegative - 2);
   }

   if(NPar - Nnegative >= 3){
     EigenValueMin = EigenValueMin < 0.01 * SortedD(NPar - Nnegative - 3, NPar - Nnegative - 3) ? EigenValueMin : 0.01 * SortedD(NPar - Nnegative - 3, NPar - Nnegative - 3);
   }

   if(EigenValueMin > SortedD(NPar - 1, NPar - 1)){
     cout<<"Force all eigenvalues > "<<EigenValueMin<<endl;
     for(int i = 0; i < NPar; i++){
       if(SortedD(i, i) < EigenValueMin) cout<<"The "<<i<<"th eigenvalue has been set to "<<EigenValueMin<<". Original value is "<<SortedD(i, i)<<endl;
       SortedD(i, i) = SortedD(i, i) > EigenValueMin ? SortedD(i, i) : EigenValueMin;
     }
   }

   // Find new local minimum for flattest direction and negative eigen values direction

   int nFlat = Nnegative + 2;

   // Update tvec and umat
   for(int i = 0; i < NPar; i++){
     if(fabs(SortedD(i, i)) < 1e-20){
       cout<<"ERROR! The eigenvalue "<<i<<" equals to 0."<<endl;
       return;
     }
     tvec(i) = 1.0 / sqrt(SortedD(i, i));
   }

   for(int i = 0; i < NPar; i++){
     for(int j = 0; j < NPar; j++){
       umat(i, j) = SortedV(i, j);
     }
   }

   for(int i = 0; i < NPar; i++){
     evec(i) = SortedD(i, i);
   }
   vmat = umat;

   // Calculate dmeas to see if we can stop the iterate
   double dmeas1 = 0.0;
   for(int i = 0; i < NPar; i++){
     dmeas1 = dmeas1 > fabs(PhiMatrix(i, i) - 1.0) ? dmeas1 : fabs(PhiMatrix(i, i) - 1.0);
   }

   double dmeas2 = 0.0;
   for(int i = 1; i < NPar; i++){
     for(int j = 0; j < i; j++){
       dmeas2 = dmeas2 > fabs(PhiMatrix(i, j)) ? dmeas2 : fabs(PhiMatrix(i, j));
     }
   }

   double dmeas = dmeas1 + dmeas2;
   cout<<getTime()<<"  INFO| iter "<<it<<" dmeas = "<<dmeas<<endl;
   if(dmeas < dmeasRequirement){
     cout<<"Final Eigen values: "<<endl;
     cout<<evec<<endl;
     cout<<"Final Eigen vectors: "<<endl;
     cout<<umat<<endl;
     cout<<"Final xtrans: "<<endl;
     cout<<xtrans<<endl;
     cout<<"Final wtrans: "<<endl;
     cout<<wtrans<<endl;
     cout<<"Final PhiMatrix:"<<endl;
     cout<<PhiMatrix<<endl;
     cout<<"Final Hessian Matrix:"<<endl;
     cout<<Hessian<<endl;

     break;
   }

   if(dmeas < 0.1){
     TString EVName = (TString)"Iter" + it + "_dmeas" + TString::Format("%.5f", dmeas) + ".ev";
     OutputHessianFortran(EVName);
   }

   // Calculate wtrans
   Eigen::MatrixXd wtrans_old = wtrans;
   for(int i = 0; i < NPar; i++){
     for(int j = 0; j < NPar; j++){
       double sum = 0.0;
       for(int k = 0; k < NPar; k++){
         sum += wtrans_old(i, k) * umat(k, j);
       }
       sum = sum / sqrt(evec(j));
       wtrans(i, j) = sum;
     }
   }

   // Calculte Hessian based on wtrans
   Eigen::MatrixXd Hessian_Inverse = Eigen::MatrixXd(NPar, NPar);
   for(int i = 0; i < NPar; i++){
     for(int j = 0; j < NPar; j++){
       double sum = 0.0;
       for(int k = 0; k < NPar; k++){
         sum += wtrans(i, k) * wtrans(j, k);
       }
       Hessian_Inverse(i, j) = sum;
     }
   }
   Hessian = Hessian_Inverse.inverse();

   cout<<"Eigen values: "<<endl;
   cout<<evec<<endl;
   cout<<"Eigen vectors: "<<endl;
   cout<<umat<<endl;
   cout<<"xtrans: "<<endl;
   cout<<xtrans<<endl;
   cout<<"wtrans: "<<endl;
   cout<<wtrans<<endl;
   cout<<"PhiMatrix:"<<endl;
   cout<<PhiMatrix<<endl;
   cout<<"Hessian Matrix:"<<endl;
   cout<<Hessian<<endl;

   if(it == maxIter){
     cout<<"WARNING! Iterate doesn't converge in "<<maxIter<<" times."<<endl;
   }
 }

 // Construct Hessian Matrix from evec(Eigen Values) and vmat(Eigen Vectors)
 Hessian = Eigen::MatrixXd(NPar, NPar);
 for(int i = 0; i < NPar; i++){
   for(int j = 0; j < NPar; j++){
     double sum = 0.0;
     for(int k = 0; k < NPar; k++){
       sum += evec(k) * vmat(i, k) * vmat(j, k);
     }
     Hessian(i, j) = sum;
   }
 }

 OutputHessianFortran("newpdf.ev");
}

/////////////////////////////////////////////////////////////////////////////////////////////////////

 //////////////////////////
 // For Producing EV set //
 //////////////////////////

void Iterate::ProduceEVSet(TString name)
{
 int irt;

 int nSet = 2 * NPar;

 EigenVectorShift(0.0, 0);
 double BestFitChi2 = m_fcn->GetChi2(false, true);
 TString FileName = name + TString::Format(".%02d", 0) + ".pds";
 OutputPDFTable(FileName, 0);
 m_hoppet->OutputLHAPDFTable(name, 0);
 TString ParFileName = name + TString::Format(".%02d", 0) + ".yml";
 setting.OutputNewParameterFile(ParFileName);
 cout<<"Best Fit Chi2 = "<<BestFitChi2<<endl;

 for(int i = 1; i <= nSet; i++){
   TString FileName = name + TString::Format(".%02d", i) + ".pds";
   TString ParFileName = name + TString::Format(".%02d", i) + ".yml";

   auto FindingDistance = [&](double distance){
     EigenVectorShift(distance, (i + 1) / 2 - 1);
     double Chi2 = GetChi2();
     cout<<getTime()<<" Try distance = "<<distance<<" Chi2 = "<<Chi2<<endl;

     return Chi2 - BestFitChi2 - Tolerance;
   };

   double left;
   double right;
   if(i % 2 != 0){
     left = 0.0;
     right = 2.0 * sqrt(Tolerance);
   }
   if(i % 2 == 0){
     left = -2.0 * sqrt(Tolerance);
     right = 0.0;
   }

   std::filesystem::path file_path = ParFileName.Data();
   if(!std::filesystem::exists(file_path)){

     double Solution = util->zbrnt(FindingDistance, left, right, 0.00001, irt);

     EigenVectorShift(Solution, (i + 1) / 2 - 1);
     double Tier1Chi2 = m_fcn->GetChi2(false);
     double Tier2Chi2 = GetTier2(Tier2Type);
     double DeltaChi2 = Tier1Chi2 + Tier2Chi2 - BestFitChi2;
     cout<<getTime()<<"  INFO| EV set "<<i<<": distance = "<<Solution<<" Tier1Chi2 = "<<Tier1Chi2<<" Tier2Chi2 = "<<Tier2Chi2<<" Delta Chi2 = "<<DeltaChi2<<endl;

     setting.OutputNewParameterFile(ParFileName);
   }
   else{
     cout<<"Reading from "<<ParFileName<<endl;
     Config newsetting;
     newsetting.ParseParameter(ParFileName);
     setting.CloneParameter(newsetting);

     map<TString, double> p = setting.FittingParameter;

     vector<TString> FlavorList = setting.FlavorList;
     vector<int> FlagList = setting.FlagList;

     for(int iflavor = 0; iflavor < FlavorList.size(); iflavor++){
       m_pdf_Q0->SetParameter(FlavorList.at(iflavor), setting.ShapeParameterValue.at(FlavorList.at(iflavor)));
     }

     // Here we ignore the parameter of gluM and strM, but read the number directly from the MomentumList and B0List
     // We use newsetting to avoid the InitialgluonMomentum and InitialStrangB0 being modified.
     m_pdf_Q0->SetInitialgluonMomentum(newsetting.InitialgluonMomentum);
     m_pdf_Q0->SetInitialStrangeB0(newsetting.InitialStrangeB0);
     m_pdf_Q0->SetgluonMomentumPar(0.0);
     m_pdf_Q0->SetStrangeB0Par(0.0);

     m_pdf_Q0->Initialize(setting.IFun, FlavorList, FlagList);
     m_pdf_Q0->ParameterOutput();
     if(setting.EvolveType == "Hoppet"){
       m_hoppet->Initialize(m_pdf_Q0, setting.Qini);
     }
     else if(setting.EvolveType == "APFEL"){
       m_hoppet->InitializeAPFEL(m_pdf_Q0, setting.Qini);
     }
     else if(setting.EvolveType == "APFELxx"){
       m_hoppet->InitializeAPFELxx(m_pdf_Q0, setting.Qini);
     }

     pdsReader* pdftable = m_hoppet->PrepareCTEQTable();

     setting.ConfigPDF(pdftable);
     m_fcn->InitialPDF(setting);

     for(auto iter = setting.NormParDataList.begin(); iter != setting.NormParDataList.end(); iter++){
       for(int i = 0; i < iter->second.size(); i++){
         m_fcn->AllData.at(iter->second.at(i))->InputNormalization(p.at(iter->first));
       }
     }
   }

   if(setting.CalcLevel == "Full"){
     double Tier1Chi2 = m_fcn->GetChi2(false);
     double Tier2Chi2 = GetTier2(Tier2Type);
     double DeltaChi2 = Tier1Chi2 + Tier2Chi2 - BestFitChi2;
     cout<<getTime()<<"  INFO| EV set "<<i<<": Tier1Chi2 = "<<Tier1Chi2<<" Tier2Chi2 = "<<Tier2Chi2<<" Delta Chi2 = "<<DeltaChi2<<endl;
   }

   OutputPDFTable(FileName, i);
   m_hoppet->OutputLHAPDFTable(name, i);
 }

}

void Iterate::EigenVectorShift(double distance, int ipar)
{
// ipar is from 0

 NewParCentral.clear();
 NewParCentral.resize(NPar);

 for(int i = 0; i < NPar; i++){
   NewParCentral.at(i) = wtrans(i, ipar) * distance + xtrans(i) + setting.IterateParList.at(i).central;
 }

 UpdateParameters();
}

void Iterate::CalcNewParOn(int ipar, double step)
{
 NewParCentral.clear();
 NewParCentral.resize(NPar);

 vector<double> XiVector(NPar);

 for(int i = 0; i < NPar; i++){
   if(i == ipar) XiVector.at(i) = step;
   else XiVector.at(i) = 0.0;
 }

 cout<<"On-diagonal "<<ipar<<" step "<<step<<endl;
 for(int i = 0; i < NPar; i++){
   double sum = 0.0;
   for(int j = 0; j < NPar; j++){
     sum += wtrans(i, j) * XiVector.at(j);
   }
   NewParCentral.at(i) = sum + setting.IterateParList.at(i).central + xtrans(i);
   //cout<<"Delta "<<sum<<" Initial "<<setting.IterateParList.at(i).central<<" New parameter "<<NewParCentral.at(i)<<endl;
 }
 //cout<<endl;

 UpdateParameters();
}

void Iterate::CalcNewParOff(int ipar, int jpar, double step1, double step2)
{
 NewParCentral.clear();
 NewParCentral.resize(NPar);

 vector<double> XiVector(NPar);

 for(int i = 0; i < NPar; i++){
   if(i == ipar) XiVector.at(i) = step1;
   else if(i == jpar) XiVector.at(i) = step2;
   else XiVector.at(i) = 0.0;
 }

 cout<<"Off-diagonal "<<ipar<<"  "<<jpar<<" step1 "<<step1<<" step2 "<<step2<<endl;
 for(int i = 0; i < NPar; i++){
   double sum = 0.0;
   for(int j = 0; j < NPar; j++){
     sum += wtrans(i, j) * XiVector.at(j);
   }
   NewParCentral.at(i) = sum + setting.IterateParList.at(i).central + xtrans(i);
   //cout<<"Delta "<<sum<<" Initial "<<setting.IterateParList.at(i).central<<" New parameter "<<NewParCentral.at(i)<<endl;
 }
 //cout<<endl;

 UpdateParameters();
}

void Iterate::UpdateParameters()
{
 for(int i = 0; i < NPar; i++){
   TString ParName = setting.IterateParList.at(i).name;

   setting.FittingParameter.at(ParName) = NewParCentral.at(i);

   setting.ParameterList.at(i).central = NewParCentral.at(i);
 }

 for(int i = 0; i < NPar; i++){
   int id = setting.IterateParList.at(i).id;

   setting.IDtoParam.at(id) = NewParCentral.at(i);
 }

 setting.RefreshShapeParameter();

 map<TString, double> p = setting.FittingParameter;

 vector<TString> FlavorList = setting.FlavorList;
 vector<int> FlagList = setting.FlagList;

 for(int iflavor = 0; iflavor < FlavorList.size(); iflavor++){
   m_pdf_Q0->SetParameter(FlavorList.at(iflavor), setting.ShapeParameterValue.at(FlavorList.at(iflavor)));
 }

 m_pdf_Q0->SetgluonMomentumPar(p.at("gluM"));
 m_pdf_Q0->SetStrangeB0Par(p.at("strM"));

 m_pdf_Q0->Initialize(setting.IFun, FlavorList, FlagList);

 if(setting.EvolveType == "Hoppet"){
   m_hoppet->Initialize(m_pdf_Q0, setting.Qini);
 }
 else if(setting.EvolveType == "APFEL"){
   m_hoppet->InitializeAPFEL(m_pdf_Q0, setting.Qini);
 }
 else if(setting.EvolveType == "APFELxx"){
   m_hoppet->InitializeAPFELxx(m_pdf_Q0, setting.Qini);
 }

 setting.MomentumList = m_pdf_Q0->MomentumList;
 setting.B0List = m_pdf_Q0->B0List;

 pdsReader* pdftable = m_hoppet->PrepareCTEQTable();
 setting.ConfigPDF(pdftable);

 m_fcn->InitialPDF(setting);

 for(auto iter = setting.NormParDataList.begin(); iter != setting.NormParDataList.end(); iter++){
   for(int i = 0; i < iter->second.size(); i++){
     m_fcn->AllData.at(iter->second.at(i))->InputNormalization(p.at(iter->first));
   }
 }

// cout<<getTime()<<endl;
// m_pdf_Q0->ParameterOutput();
// cout<<"gluM = "<<m_pdf_Q0->GetgluonMomentum()<<endl;
// cout<<"strM = "<<m_pdf_Q0->GetStrangeB0()<<endl;
//   if(p.count("N71") > 0) cout<<"N71  = "<<p.at("N71")<<endl;
//   if(p.count("N72") > 0) cout<<"N72  = "<<p.at("N72")<<endl;
//   if(p.count("N73") > 0) cout<<"N73  = "<<p.at("N73")<<endl;
// cout<<endl;

 p.clear();
 FlavorList.clear();
 FlagList.clear();

 delete pdftable;
}

void Iterate::OutputPDFTable(TString name, int iSet)
{
 pdsReader* pdftable = m_hoppet->PrepareCTEQTable();

 if(!(name.Contains(".pds"))) name = name + ".pds";
 pdftable->OutputPDF(name);
}

double Iterate::GetChi2()
{
 double chi2 = m_fcn->GetChi2(false);

 double tier2 = GetTier2(Tier2Type);

 return chi2 + tier2;
}

double Iterate::GetTier2(TString type)
{
 double Tier2 = 0.0;

 double PL = 0.9;
// double PL = setting.CP.at(make_tuple(7, 3));
 double xiNv = ROOT::Math::normal_quantile(PL, 1.0);
 double xiN90 = 1.28155;

 if(type == "None"){
   return 0.0;
 }
 else if(type == "CTEQ"){
   for(int i = 0; i < AllData.size(); i++){
     double BestFitChi2 = m_fcn->AllBestFitChi2.at(i);
     double NPoints = (double)(m_fcn->AllNPoints.at(i));
     double ChiEff = m_fcn->AllChi2.at(i) * (1.0 < NPoints / BestFitChi2 ? 1.0 : NPoints / BestFitChi2);
     double spartyness = TranslateChi2ToSpartyness(ChiEff, m_fcn->AllNPoints.at(i));
     if(spartyness > 0.0) Tier2 += pow(spartyness * xiN90 / xiNv, 16.0);
     //cout<<i<<"    ChiEff = "<<ChiEff<<" BestFitChi2 = "<<BestFitChi2<<" NPoints = "<<NPoints<<" xiN90 = "<<xiN90<<" xiNv = "<<xiNv<<" Spartyness = "<<spartyness<<" Tier2 = "<<pow(spartyness * xiN90 / xiNv, 16.0)<<endl;
     //Tier2 += pow(spartyness * xiN90 / xiNv, setting.CP.at(make_tuple(6, 3)));
   }
 }
 else if(type == "MSTWS"){
   for(int i = 0; i < AllData.size(); i++){
     double spartyness_bestfit = TranslateChi2ToSpartyness(m_fcn->AllBestFitChi2.at(i), m_fcn->AllNPoints.at(i));
     double spartyness = TranslateChi2ToSpartyness(m_fcn->AllChi2.at(i), m_fcn->AllNPoints.at(i));
     double sres = spartyness - spartyness_bestfit;
     if(sres > 0.0) Tier2 += pow(sres * xiN90 / xiNv, 16.0);
   }
 }
 else if(type == "MSTW"){
   for(int i = 0; i < AllData.size(); i++){
     double xiChi2v = TLewisChi2(xiNv, m_fcn->AllNPoints.at(i));
     double xiChi20 = m_fcn->AllNPoints.at(i) - 2.0 / 3.0 + 4.0 / (27.0 * m_fcn->AllNPoints.at(i));

     double sres = (m_fcn->AllChi2.at(i) - m_fcn->AllBestFitChi2.at(i)) / (xiChi2v - xiChi20) * xiChi20 / m_fcn->AllBestFitChi2.at(i);
     Tier2 += pow(sres * xiN90, 16.0);
   }
 }

 return Tier2;
}

void Iterate::ReadHessian(TString FileName)
{

}

void Iterate::OutputHessian(TString FileName)
{

}

void Iterate::ReadHessianFortran(TString FileName)
{
 ifstream infile;
  infile.open(FileName, ios::in);

 string FileLine;
 string skip;
 double Value;
 int InputNPar = 0;

 infile >> skip >> InputNPar;
 getline(infile, FileLine);

 if(InputNPar != NPar){
   cout<<"ERROR! Parameters from .ev file don't match with input."<<endl;
   return;
 }

 getline(infile, FileLine);

 xtrans = Eigen::VectorXd(NPar);
 wtrans = Eigen::MatrixXd(NPar, NPar);

 evec = Eigen::VectorXd(NPar);
 umat = Eigen::MatrixXd(NPar, NPar);

 for(int i = 0; i < NPar; i++){
   infile >> Value;
   evec(i) = Value;
   //cout<<evec(i)<<endl;
 }

 for(int i = 0; i < NPar; i++){
   for(int j = 0; j < NPar; j++){
     infile >> Value;
     umat(j, i) = Value;
     //cout<<umat(j, i)<<"   ";
   }
   //cout<<endl;
 }

 for(int i = 0; i < NPar; i++){
   infile >> Value;
   xtrans(i) = Value;
   //cout<<xtrans(i)<<endl;
 }

 for(int i = 0; i < NPar; i++){
   for(int j = 0; j < NPar; j++){
     infile >> Value;
     wtrans(j, i) = Value;
     //cout<<wtrans(j, i)<<"   ";
   }
   //cout<<endl;
 }

}

void Iterate::OutputHessianFortran(TString FileName)
{
 ofstream evfile(FileName);

 evfile<<"NPar= "<<NPar<<endl;
 evfile<<"evec, umat, xtrans, wtrans:"<<endl;


 for(int i = 0; i < NPar; i++){
   evfile<<setw(13)<<scientific<<uppercase<<setprecision(5)<<evec(i);
   if((i + 1) % 6 == 0){
     evfile<<endl;
   }
 }
 if(NPar % 6 != 0) evfile<<endl;

 int ipt = 0;
 for(int i = 0; i < NPar; i++){
   for(int j = 0; j < NPar; j++){
     evfile<<setw(13)<<scientific<<uppercase<<setprecision(5)<<vmat(j, i);
     if((ipt + 1) % 6 == 0){
       evfile<<endl;
     }
     ipt++;
   }
 }
 if(NPar % 6 != 0) evfile<<endl;

 for(int i = 0; i < NPar; i++){
   evfile<<setw(13)<<scientific<<uppercase<<setprecision(5)<<xtrans(i);
   if((i + 1) % 6 == 0){
     evfile<<endl;
   }
 }
 if(NPar % 6 != 0) evfile<<endl;

 ipt = 0;
 for(int i = 0; i < NPar; i++){
   for(int j = 0; j < NPar; j++){
     evfile<<setw(13)<<scientific<<uppercase<<setprecision(5)<<wtrans(j, i);
     if((ipt + 1) % 6 == 0){
       evfile<<endl;
     }
     ipt++;
   }
 }

}

