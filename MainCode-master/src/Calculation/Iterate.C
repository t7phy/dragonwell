#include "Calculation/Iterate.h"

Iterate::Iterate()
{
 util = new CTUtil();

 Tier2Type = "CTEQ";
}

void Iterate::Initialize()
{
 m_instance = new GlobalFittingCore();

 m_instance->InputParaFileName = "ForIterate.yml";
 m_instance->Initialize();

 Tolerance = m_instance->setting.Tolerance;
 Tier2Type = m_instance->setting.Tier2Type;

 NPar = m_instance->setting.IterateParList.size();

 dmeasRequirement = m_instance->setting.dmeasRequirement;
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

 double BestFitChi2 = m_instance->GetChi2(false, true);
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
     double F1 = m_instance->GetChi2(false);

     CalcNewParOn(ipar, step * (-1.0));
     double F2 = m_instance->GetChi2(false);

     // Adjust the step size if the Delta Chi2 < 0.0009 * up (step = 0.03 * sqrt(up), up = 0.05)
     if(F1 - BestFitChi2 < 0.0009 * up || F2 - BestFitChi2 < 0.0009 * up){

       int nloop = 0;
       double Step1 = step;
       while(F1 - BestFitChi2 < 0.0009 * up){
         Step1 = Step1 * 2.0;
         CalcNewParOn(ipar, Step1);
         F1 = m_instance->GetChi2(false);
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
         F1 = m_instance->GetChi2(false);
         cout<<"Delta Chi2 is too large for parameter "<<ipar<<", reduce the step to "<<Step1<<endl;
       }

       nloop = 0;
       double Step2 = step;
       while(F2 - BestFitChi2 < 0.0009 * up){
         Step2 = Step2 * 2.0;
         CalcNewParOn(ipar, Step2 * (-1.0));
         F2 = m_instance->GetChi2(false);
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
         F2 = m_instance->GetChi2(false);
         cout<<"Delta Chi2 is too large for parameter "<<ipar<<", reduce the step to "<<Step2<<endl;
       }

       if(Step1 > Step2){
         ParStep.at(ipar) = Step1;
         CalcNewParOn(ipar, ParStep.at(ipar) * (-1.0));
         F2 = m_instance->GetChi2(false);
       }
       else{
         ParStep.at(ipar) = Step2;
         CalcNewParOn(ipar, ParStep.at(ipar));
         F1 = m_instance->GetChi2(false);
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
         double F = m_instance->GetChi2(false);
         CalcNewParOn(ipar, x);
         double F0 = m_instance->GetChi2(false);
         cout<<"Try x = "<<x<<" F("<<x + ParStep.at(ipar)<<") = "<<F<<" F("<<x<<") = "<<F0<<" First derivative = "<<(F - F0) / ParStep.at(ipar)<<endl;
         return (F - F0) / ParStep.at(ipar);
       };

       PlusSolution = util->zbrnt(FindingZeroDerivative, left, right, 0.0001, irt);
       CalcNewParOn(ipar, PlusSolution);
       PlusChi2 = m_instance->GetChi2(false);
       cout<<"Plus direction changed. New solution is "<<PlusSolution<<" New chi2 = "<<PlusChi2<<endl;
     }
     if(F2 < BestFitChi2){
       double left = ParStep.at(ipar) * (-3.0);
       double right = 0.0;
       auto FindingZeroDerivative = [&](double x){
         CalcNewParOn(ipar, x - ParStep.at(ipar));
         double F = m_instance->GetChi2(false);
         CalcNewParOn(ipar, x);
         double F0 = m_instance->GetChi2(false);
         cout<<"Try x = "<<x<<" F("<<x<<") = "<<F0<<" F("<<x - ParStep.at(ipar)<<") = "<<F<<" First derivative = "<<(F0 - F) / ParStep.at(ipar)<<endl;
         return (F0 - F) / ParStep.at(ipar);
       };

       MinusSolution = util->zbrnt(FindingZeroDerivative, left, right, 0.0001, irt);
       CalcNewParOn(ipar, MinusSolution);
       MinusChi2 = m_instance->GetChi2(false);
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
       F1 = m_instance->GetChi2(false);

       CalcNewParOn(ipar, ParStep.at(ipar) * (-1.0));
       F2 = m_instance->GetChi2(false);

       CalcNewParOn(ipar, 0.0);
       BestFitChi2 = m_instance->GetChi2(false, true);

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
       double F11 = m_instance->GetChi2(false);

       CalcNewParOff(ipar, jpar, step1 * (-1.0), step2 * (-1.0));
       double F22 = m_instance->GetChi2(false);

       CalcNewParOff(ipar, jpar, step1 * (-1.0), step2);
       double F21 = m_instance->GetChi2(false);

       CalcNewParOff(ipar, jpar, step1, step2 * (-1.0));
       double F12 = m_instance->GetChi2(false);

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

 // Read from the previous iteration
 std::filesystem::path file_path = "Hessian.save";
 if(std::filesystem::exists(file_path)){
   ifstream PreviousHessian("Hessian.save");
   string FileLine;
   getline(PreviousHessian, FileLine);
   for(int i = 0; i < NPar; i++){
     PreviousHessian >> xtrans(i);
   }
   getline(PreviousHessian, FileLine);
   getline(PreviousHessian, FileLine);
   for(int i = 0; i < NPar; i++){
     for(int j = 0; j < NPar; j++){
       PreviousHessian >> wtrans(i, j);
     }
   }
   cout<<"Previous xtrans:"<<endl;
   cout<<xtrans<<endl;
   cout<<"Previous wtrans:"<<endl;
   cout<<wtrans<<endl;

   CalcNewParOn(0, 0.0);
 }

 double BestFitChi2 = m_instance->GetChi2(false, true);
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
     double StepPlus = step;
     double StepMinus = step;

     CalcNewParOn(ipar, step);
     double F1 = m_instance->GetChi2(false);

     CalcNewParOn(ipar, step * (-1.0));
     double F2 = m_instance->GetChi2(false);

     // Adjust the step size if the Delta Chi2 < 0.0009 * up (step = 0.03 * sqrt(up), up = 0.05)
     if(F1 - BestFitChi2 < 0.0009 * up || F2 - BestFitChi2 < 0.0009 * up){

       int nloop = 0;
       double Step1 = step;
       while(F1 - BestFitChi2 < 0.0009 * up){
         Step1 = Step1 * 2.0;
         CalcNewParOn(ipar, Step1);
         F1 = m_instance->GetChi2(false);
         cout<<"Change the step1 of parameter "<<ipar<<" to "<<Step1<<". F1 = "<<F1<<" BestFitChi2 = "<<BestFitChi2<<" Delta Chi2 = "<<F1 - BestFitChi2<<endl;
         nloop++;

         if(F1 < BestFitChi2){
           StepPlus = Step1;
           break;
         }

         if(nloop > 7){
           cout<<"Try too many times, revert the step to the initial one."<<endl;
           Step1 = 0.03 * sqrt(up);
           break;
         }
       }
       if(F1 - BestFitChi2 > 0.1 * up){
         Step1 = Step1 / sqrt(2.0);
         CalcNewParOn(ipar, Step1);
         F1 = m_instance->GetChi2(false);
         cout<<"Delta Chi2 is too large for parameter "<<ipar<<", reduce the step to "<<Step1<<endl;
       }

       nloop = 0;
       double Step2 = step;
       while(F2 - BestFitChi2 < 0.0009 * up){
         Step2 = Step2 * 2.0;
         CalcNewParOn(ipar, Step2 * (-1.0));
         F2 = m_instance->GetChi2(false);
         cout<<"Change the step2 of parameter "<<ipar<<" to "<<Step2<<". F2 = "<<F2<<" BestFitChi2 = "<<BestFitChi2<<" Delta Chi2 = "<<F2 - BestFitChi2<<endl;
         nloop++;

         if(F2 < BestFitChi2){
           StepMinus = Step2;
           break;
         }

         if(nloop > 7){
           cout<<"Try too many times, revert the step to the initial one."<<endl;
           Step2 = 0.03 * sqrt(up);
           break;
         }
       }
       if(F2 - BestFitChi2 > 0.1 * up){
         Step2 = Step2 / sqrt(2.0);
         CalcNewParOn(ipar, Step2 * (-1.0));
         F2 = m_instance->GetChi2(false);
         cout<<"Delta Chi2 is too large for parameter "<<ipar<<", reduce the step to "<<Step2<<endl;
       }

       if(Step1 > Step2){
         ParStep.at(ipar) = Step1;
         CalcNewParOn(ipar, ParStep.at(ipar) * (-1.0));
         F2 = m_instance->GetChi2(false);
       }
       else{
         ParStep.at(ipar) = Step2;
         CalcNewParOn(ipar, ParStep.at(ipar));
         F1 = m_instance->GetChi2(false);
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
       double left = StepPlus / 2.0;
       double right = StepPlus * 3.0;

       auto FindingZeroDerivative = [&](double x){
         CalcNewParOn(ipar, x + StepPlus / 2.0);
         double F = m_instance->GetChi2(false);
         CalcNewParOn(ipar, x - StepPlus / 2.0);
         double F0 = m_instance->GetChi2(false);
         cout<<"Try x = "<<x<<" F("<<x + StepPlus / 2.0<<") = "<<F<<" F("<<x - StepPlus / 2.0<<") = "<<F0<<" First derivative = "<<(F - F0) / StepPlus<<endl;
         return (F - F0) / StepPlus;
       };

       double TryBoundary = FindingZeroDerivative(right);
       while(TryBoundary < 0.0){
         right = right + StepPlus;
         cout<<"Move the right boundary to "<<right<<endl;
         TryBoundary = FindingZeroDerivative(right);
       }

       do{
         PlusSolution = util->zbrnt(FindingZeroDerivative, left, right, 0.0001, irt);
         CalcNewParOn(ipar, PlusSolution);
         PlusChi2 = m_instance->GetChi2(false);
         cout<<"Plus direction changed. New solution is "<<PlusSolution<<" New chi2 = "<<PlusChi2<<endl;
         right = PlusSolution + StepPlus;
       } while(PlusChi2 > BestFitChi2);

       cout<<"Plus direction changed. New solution is "<<PlusSolution<<" New chi2 = "<<PlusChi2<<endl;
     }

     if(F2 < BestFitChi2){
       double left = StepMinus * (-3.0);
       double right = StepMinus / (-2.0);
       auto FindingZeroDerivative = [&](double x){
         CalcNewParOn(ipar, x - StepMinus / 2.0);
         double F = m_instance->GetChi2(false);
         CalcNewParOn(ipar, x + StepMinus / 2.0);
         double F0 = m_instance->GetChi2(false);
         cout<<"Try x = "<<x<<" F("<<x + StepMinus / 2.0<<") = "<<F0<<" F("<<x - StepMinus / 2.0<<") = "<<F<<" First derivative = "<<(F0 - F) / StepMinus<<endl;
         return (F0 - F) / StepMinus;
       };

       double TryBoundary = FindingZeroDerivative(left);
       while(TryBoundary > 0.0){
         left = left - StepMinus;
         cout<<"Move the left boundary to "<<left<<endl;
         TryBoundary = FindingZeroDerivative(left);
       }

       do{
         MinusSolution = util->zbrnt(FindingZeroDerivative, left, right, 0.0001, irt);
         CalcNewParOn(ipar, MinusSolution);
         MinusChi2 = m_instance->GetChi2(false);
         cout<<"Minus direction changed. New solution is "<<MinusSolution<<" New chi2 = "<<MinusChi2<<endl;
         left = MinusSolution - StepMinus;
       } while(MinusChi2 > BestFitChi2);

       cout<<"Minus direction changed. New solution is "<<MinusSolution<<" New chi2 = "<<MinusChi2<<endl;
     }

     if(PlusSolution != 0.0 && MinusSolution == 0.0){
       Solution = PlusSolution;
       ParStep.at(ipar) = StepPlus;
     }
     else if(PlusSolution == 0.0 && MinusSolution != 0.0){
       Solution = MinusSolution;
       ParStep.at(ipar) = StepMinus;
     }
     else if(PlusSolution != 0.0 && MinusSolution != 0.0){
       Solution = PlusChi2 < MinusChi2 ? PlusSolution : MinusSolution;
       ParStep.at(ipar) = PlusChi2 < MinusChi2 ? StepPlus : StepMinus;
     }

     if(Solution != 0.0){
       for(int i = 0; i < NPar; i++){
         xtrans(i) = xtrans(i) + wtrans(i, ipar) * Solution;
       }

       CalcNewParOn(ipar, ParStep.at(ipar));
       F1 = m_instance->GetChi2(false);

       CalcNewParOn(ipar, ParStep.at(ipar) * (-1.0));
       F2 = m_instance->GetChi2(false);

       CalcNewParOn(ipar, 0.0);
       BestFitChi2 = m_instance->GetChi2(false, true);

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
       double F11 = m_instance->GetChi2(false);

       CalcNewParOff(ipar, jpar, step1 * (-1.0), step2 * (-1.0));
       double F22 = m_instance->GetChi2(false);

       CalcNewParOff(ipar, jpar, step1 * (-1.0), step2);
       double F21 = m_instance->GetChi2(false);

       CalcNewParOff(ipar, jpar, step1, step2 * (-1.0));
       double F12 = m_instance->GetChi2(false);

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

   // Update saved Hessian Matrix
   ofstream UpdateHessian("Hessian.save");
   UpdateHessian<<"xtrans: "<<endl;
   UpdateHessian<<xtrans<<endl;
   UpdateHessian<<"wtrans: "<<endl;
   UpdateHessian<<wtrans<<endl;

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
 double BestFitChi2 = m_instance->GetChi2(false, true);
 TString FileName = name + TString::Format(".%02d", 0) + ".pds";
 OutputPDFTable(FileName, 0);
 m_instance->m_hoppet->OutputLHAPDFTable(name, 0);
 TString ParFileName = name + TString::Format(".%02d", 0) + ".yml";
 m_instance->setting.OutputNewParameterFile(ParFileName);
 cout<<"Best Fit Chi2 = "<<BestFitChi2<<endl;

 for(int i = 1; i <= nSet; i++){
   TString FileName = name + TString::Format(".%02d", i) + ".pds";
   TString ParFileName = name + TString::Format(".%02d", i) + ".yml";

   auto FindingDistance = [&](double distance){
     EigenVectorShift(distance, (i + 1) / 2 - 1);
     double Chi2 = GetChi2();
     double Tier2Chi2 = GetTier2(Tier2Type);
     if(Tier2Type.Contains("T2Only")){
       Chi2 = BestFitChi2 + Tier2Chi2;
     }
     cout<<getTime()<<" Try distance = "<<distance<<" Chi2 = "<<Chi2<<" Tier2Chi2 = "<<Tier2Chi2<<endl;

     return Chi2 - BestFitChi2 - Tolerance;
   };

   auto FindingDistanceTier1Only = [&](double distance){
     EigenVectorShift(distance, (i + 1) / 2 - 1);
     double Chi2 = m_instance->GetChi2(false);
     cout<<getTime()<<" Try distance = "<<distance<<" Tier1Chi2 = "<<Chi2<<endl;

     return Chi2 - BestFitChi2 - Tolerance;
   };

   double left;
   double right;
   if(i % 2 != 0){
     left = 0.0;
     right = 1.0 * sqrt(Tolerance);
   }
   if(i % 2 == 0){
     left = -1.0 * sqrt(Tolerance);
     right = 0.0;
   }

   std::filesystem::path file_path = ParFileName.Data();
   if(!std::filesystem::exists(file_path)){

     if(Tier2Type.Contains("T2Only")){
       //double Solution_Tier1Only = util->zbrnt(FindingDistanceTier1Only, left, right, 0.00001, irt);
       //EigenVectorShift(Solution_Tier1Only, (i + 1) / 2 - 1);
       //double tmp_Tier1Chi2 = m_instance->GetChi2(false);
       //double tmp_Tier2Chi2 = GetTier2(Tier2Type);
       //if(tmp_Tier2Chi2 < Tolerance){
       //  if(i % 2 != 0){
       //    left = Solution_Tier1Only;
       //    right = 2.0 * sqrt(Tolerance);
       //  }
       //  if(i % 2 == 0){
       //    left = -2.0 * sqrt(Tolerance);
       //    right = Solution_Tier1Only;
       //  }
       //}
       //else{
       //  if(i % 2 != 0){
       //    left = 0.0;
       //    right = Solution_Tier1Only;
       //  }
       //  if(i % 2 == 0){
       //    left = Solution_Tier1Only;
       //    right = 0.0;
       //  }
       //}

       // Try 1.0 at first to speed up the solution finding
       if(i % 2 != 0){
         EigenVectorShift(1.0, (i + 1) / 2 - 1);
         double tmp_Tier1Chi2 = m_instance->GetChi2(false);
         double tmp_Tier2Chi2 = GetTier2(Tier2Type);
         if(tmp_Tier2Chi2 <= Tolerance){
           double tmp_right = 0.9 * sqrt(Tolerance);

           EigenVectorShift(tmp_right, (i + 1) / 2 - 1);
           double tmp_Tier1Chi2_right = m_instance->GetChi2(false);
           double tmp_Tier2Chi2_right = GetTier2(Tier2Type);

           while(tmp_Tier2Chi2_right <= Tolerance){
             tmp_right = tmp_right * 1.1;
             cout<<getTime()<<"  INFO| EV set "<<i<<": move the right limit to "<<tmp_right<<endl;

             EigenVectorShift(tmp_right, (i + 1) / 2 - 1);
             tmp_Tier1Chi2_right = m_instance->GetChi2(false);
             tmp_Tier2Chi2_right = GetTier2(Tier2Type);
           }

           left = 1.0;
           right = tmp_right;
         }
         else{
           left = 0.0;
           right = 1.0;
         }
       }
       if(i % 2 == 0){
         EigenVectorShift(-1.0, (i + 1) / 2 - 1);
         double tmp_Tier1Chi2 = m_instance->GetChi2(false);
         double tmp_Tier2Chi2 = GetTier2(Tier2Type);
         if(tmp_Tier2Chi2 <= Tolerance){
           double tmp_left = -0.9 * sqrt(Tolerance);

           EigenVectorShift(tmp_left, (i + 1) / 2 - 1);
           double tmp_Tier1Chi2_left = m_instance->GetChi2(false);
           double tmp_Tier2Chi2_left = GetTier2(Tier2Type);

           while(tmp_Tier2Chi2_left <= Tolerance){
             tmp_left = tmp_left * 1.1;
             cout<<getTime()<<"  INFO| EV set "<<i<<": move the left limit to "<<tmp_left<<endl;

             EigenVectorShift(tmp_left, (i + 1) / 2 - 1);
             tmp_Tier1Chi2_left = m_instance->GetChi2(false);
             tmp_Tier2Chi2_left = GetTier2(Tier2Type);
           }

           left = tmp_left;
           right = -1.0;
         }
         else{
           left = -1.0;
           right = 0.0;
         }
       }
     }

     double Solution = util->zbrnt(FindingDistance, left, right, 0.00001, irt);

     EigenVectorShift(Solution, (i + 1) / 2 - 1);
     double Tier1Chi2 = m_instance->GetChi2(false);
     double Tier2Chi2 = GetTier2(Tier2Type);
     double TotalChi2 = Tier1Chi2 + Tier2Chi2;
     if(Tier2Type.Contains("T2Only")) TotalChi2 = BestFitChi2 + Tier2Chi2;
     double DeltaChi2 = TotalChi2 - BestFitChi2;
     cout<<getTime()<<"  INFO| EV set "<<i<<": distance = "<<Solution<<" Tier1Chi2 = "<<Tier1Chi2 - BestFitChi2<<" Tier2Chi2 = "<<Tier2Chi2<<" Delta Chi2 = "<<DeltaChi2<<endl;

     m_instance->setting.OutputNewParameterFile(ParFileName);
   }
   else{
     cout<<"Reading from "<<ParFileName<<endl;
     m_instance->ReadingNewParaFile(ParFileName);
   }

   if(m_instance->setting.CalcLevel == "Full"){
     double Tier1Chi2 = m_instance->GetChi2(false);
     double Tier2Chi2 = GetTier2(Tier2Type);
     double TotalChi2 = Tier1Chi2 + Tier2Chi2;
     if(Tier2Type.Contains("T2Only")) TotalChi2 = BestFitChi2 + Tier2Chi2;
     double DeltaChi2 = TotalChi2 - BestFitChi2;
     cout<<getTime()<<"  INFO| EV set "<<i<<": Tier1Chi2 = "<<Tier1Chi2 - BestFitChi2<<" Tier2Chi2 = "<<Tier2Chi2<<" Delta Chi2 = "<<DeltaChi2<<endl;
   }

   OutputPDFTable(FileName, i);
   m_instance->m_hoppet->OutputLHAPDFTable(name, i);
 }

}

void Iterate::EigenVectorShift(double distance, int ipar)
{
// ipar is from 0

 NewParCentral.clear();
 NewParCentral.resize(NPar);

 for(int i = 0; i < NPar; i++){
   NewParCentral.at(i) = wtrans(i, ipar) * distance + xtrans(i) + m_instance->setting.IterateParList.at(i).central;
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
   NewParCentral.at(i) = sum + m_instance->setting.IterateParList.at(i).central + xtrans(i);
   //cout<<"Delta "<<sum<<" Initial "<<m_instance->setting.IterateParList.at(i).central<<" New parameter "<<NewParCentral.at(i)<<endl;
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
   NewParCentral.at(i) = sum + m_instance->setting.IterateParList.at(i).central + xtrans(i);
   //cout<<"Delta "<<sum<<" Initial "<<setting.IterateParList.at(i).central<<" New parameter "<<NewParCentral.at(i)<<endl;
 }
 //cout<<endl;

 UpdateParameters();
}

void Iterate::UpdateParameters()
{
 m_instance->UpdateIterateParameters(NewParCentral);
}

void Iterate::OutputPDFTable(TString name, int iSet)
{
 pdsReader* pdftable = m_instance->m_hoppet->PrepareCTEQTable();

 if(!(name.Contains(".pds"))) name = name + ".pds";
 pdftable->OutputPDF(name);
}

double Iterate::GetChi2()
{
 double chi2 = 0.0;

 chi2 = m_instance->GetChi2(false);

 double tier2 = GetTier2(Tier2Type);

 double TotalChi2 = chi2 + tier2;

 return TotalChi2;
}

double Iterate::GetTier2(TString type)
{
 double Tier2 = 0.0;

 double PL = 0.9;
// double PL = setting.CP.at(make_tuple(7, 3));
 double xiNv = ROOT::Math::normal_quantile(PL, 1.0);
 double xiN90 = 1.28155;

 TString subType = type;
 if(subType.Contains("T2Only")){
   subType.ReplaceAll("-T2Only", "");
 }

 if(subType == "None"){
   return 0.0;
 }
 else if(subType == "CTEQ"){
   for(int i = 0; i < m_instance->AllData.size(); i++){
     double BestFitChi2 = m_instance->m_fcn->AllBestFitChi2.at(i);
     double NPoints = (double)(m_instance->m_fcn->AllNPoints.at(i));
     double ChiEff = m_instance->m_fcn->AllChi2.at(i) * (1.0 < NPoints / BestFitChi2 ? 1.0 : NPoints / BestFitChi2);
     double spartyness = TranslateChi2ToSpartyness(ChiEff, m_instance->m_fcn->AllNPoints.at(i));
     if(spartyness > 0.0) Tier2 += pow(spartyness * xiN90 / xiNv, 16.0);
     //cout<<i<<"    ChiEff = "<<ChiEff<<" BestFitChi2 = "<<BestFitChi2<<" NPoints = "<<NPoints<<" xiN90 = "<<xiN90<<" xiNv = "<<xiNv<<" Spartyness = "<<spartyness<<" Tier2 = "<<pow(spartyness * xiN90 / xiNv, 16.0)<<" SumTier2 = "<<Tier2<<endl;
     //Tier2 += pow(spartyness * xiN90 / xiNv, m_instance->setting.CP.at(make_tuple(6, 3)));
   }
 }
 else if(subType == "MSTWS"){
   for(int i = 0; i < m_instance->AllData.size(); i++){
     double spartyness_bestfit = TranslateChi2ToSpartyness(m_instance->m_fcn->AllBestFitChi2.at(i), m_instance->m_fcn->AllNPoints.at(i));
     double spartyness = TranslateChi2ToSpartyness(m_instance->m_fcn->AllChi2.at(i), m_instance->m_fcn->AllNPoints.at(i));
     double sres = spartyness - spartyness_bestfit;
     if(sres > 0.0) Tier2 += pow(sres * xiN90 / xiNv, 16.0);
   }
 }
 else if(subType = "MSTW"){
   for(int i = 0; i < m_instance->AllData.size(); i++){
     double xiChi2v = TLewisChi2(xiNv, m_instance->m_fcn->AllNPoints.at(i));
     double xiChi20 = m_instance->m_fcn->AllNPoints.at(i) - 2.0 / 3.0 + 4.0 / (27.0 * m_instance->m_fcn->AllNPoints.at(i));

     double sres = (m_instance->m_fcn->AllChi2.at(i) - m_instance->m_fcn->AllBestFitChi2.at(i)) / (xiChi2v - xiChi20) * xiChi20 / m_instance->m_fcn->AllBestFitChi2.at(i);
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

