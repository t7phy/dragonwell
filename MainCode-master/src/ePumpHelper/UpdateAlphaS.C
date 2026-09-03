#include "ePumpHelper/ePumpHelper.h"

void ePumpHelper::ReadAlphaSInput(TString FileName)
{
 DefineCombination();
 DefineDataLegend();
 NameTransfer();

 //m_hoppet = new HoppetInterface();
 //m_hoppet->InitializeAlphaS(0.118, AlphaS_Q);

 AlphaSEU = new ePump(FileName, 1.0);// AlphaS EV
 AlphaSEU->ReadInTheoryAndData();

 ExtendedEU = new ePump(this->FileName + "_AlphaS", 1.0);// N EV PDFs
 strcpy(ExtendedEU->mainfile, EU->mainfile);
 ExtendedEU->ReadInTheoryAndData();

 TString NewPDFOutName = ExtendedEU->PDFoutfile;
 NewPDFOutName.ReplaceAll("/", "_AlphaS/");
 strcpy(ExtendedEU->PDFoutfile, NewPDFOutName.Data());
 strcpy(ExtendedEU->mainfile, (FileName + "_AlphaS").Data());
 ExtendedEU->suppressCCs();

 myLog.Initial(cout, ExtendedEU->ePout);

 ExtendedEU->Ni = EU->Ni + 1;

 ExtendedEU->M.resize(EU->Ni + 1);
 ExtendedEU->A.resize(EU->Ni + 1);
 ExtendedEU->L.resize(EU->Ni + 1);
 ExtendedEU->LinvA.resize(EU->Ni + 1);
 ExtendedEU->TdynP.resize(EU->Ni + 1);
 ExtendedEU->TdynM.resize(EU->Ni + 1);
 ExtendedEU->TdynBar.resize(EU->Ni + 1);
 ExtendedEU->TdynRMS.resize(EU->Ni + 1);

 ExtendedEU->OldPDF.resize(2 * (EU->Ni + 1) + 1);
 ExtendedEU->NewPDF.resize(2 * (EU->Ni + 1) + 1);
 ExtendedEU->OldPDFAlphaS.resize(2 * (EU->Ni + 1) + 1);
 ExtendedEU->NewPDFAlphaS.resize(2 * (EU->Ni + 1) + 1);

 for(int i = 0; i < EU->Ni + 1; i++){
   ExtendedEU->M[i].resize(EU->Ni + 1);
   ExtendedEU->L[i].resize(EU->Ni + 1);
 }

 for(int k = 0; k < ExtendedEU->Ndata; k++){
   ExtendedEU->dChi2Set[k].resize(2 * ExtendedEU->Ni + 1);
   ExtendedEU->dChi2newSet[k].resize(2 * ExtendedEU->Ni + 1);

   ExtendedEU->Xset[k].resize(2 * ExtendedEU->Ni + 1);

   for(int a = 0; a < ExtendedEU->Na[k]; a++){
     ExtendedEU->Xmat[k][a].resize(2 * ExtendedEU->Ni + 1);
     ExtendedEU->XmatNew[k][a].resize(2 * ExtendedEU->Ni + 1);
     ExtendedEU->FractionalContribution[k][a].resize(2 * ExtendedEU->Ni + 1); //yfu
     ExtendedEU->dX[k][a].resize(ExtendedEU->Ni);
   }

   for(int i = 0; i < 2 * ExtendedEU->Ni + 1; i++){
     ExtendedEU->Xset[k][i].resize(ExtendedEU->Na[k]);
   }
 }

 ExtendedEU->TdynRMS.at(ExtendedEU->Ni - 1) = AlphaSEU->TdynRMS.at(0);
 ExtendedEU->TdynP.at(ExtendedEU->Ni - 1) = AlphaSEU->TdynP.at(0);
 ExtendedEU->TdynM.at(ExtendedEU->Ni - 1) = AlphaSEU->TdynM.at(0);
 ExtendedEU->TdynBar.at(ExtendedEU->Ni - 1) = AlphaSEU->TdynBar.at(0);

 for(int k = 0; k < ExtendedEU->Ndata; k++){
   for(int i = EU->Ni; i < ExtendedEU->Ni; i++){
     for(int a = 0; a < ExtendedEU->Na[k]; a++){
       ExtendedEU->Xmat[k][a][2*i+1] = AlphaSEU->Xmat[k][a][2 * (i - EU->Ni) + 1];
       ExtendedEU->XmatNew[k][a][2*i+1] = ExtendedEU->Xmat[k][a][2 * i + 1]; //yfu
       ExtendedEU->Xset[k][2*i+1][a] = ExtendedEU->Xmat[k][a][2 * i + 1];

       ExtendedEU->Xmat[k][a][2*i+2] = AlphaSEU->Xmat[k][a][2 * (i - EU->Ni) + 2];
       ExtendedEU->XmatNew[k][a][2*i+2] = ExtendedEU->Xmat[k][a][2 * i + 2]; //yfu
       ExtendedEU->Xset[k][2*i+2][a] = ExtendedEU->Xmat[k][a][2 * i + 2];
       ExtendedEU->dX[k][a][i] = (AlphaSEU->Xmat[k][a][2 * (i - EU->Ni) + 1] - AlphaSEU->Xmat[k][a][2 * (i - EU->Ni) + 2]) / 2.0;
     }
   }
 }

 for(int k = 0; k < EU->Ndata; k++){
   ExtendedEU->SetXdyn(k);
 }

 ExtendedEU->ConstructUpdateMatrix();

 ExtendedEU->pdftype = PDF_format_type::NONE;
 ExtendedEU->UpdateObservables();

 UpdateAlphaS();
 UpdateAlphaSPDFs();
 UpdateAlphaSObservables();
 UpdateAlphaSLMScan();
}

void ePumpHelper::UpdateAlphaS()
{
 pdsReader* Old_AlphaS_central_WA = new pdsReader();//0.118
 Old_AlphaS_central_WA->Initialize((TString)EU->PDFinfile + (TString)".00.pds");

 pdsReader* Old_AlphaS_central_GA = new pdsReader();//AlphaS from LM scan
 Old_AlphaS_central_GA->Initialize((TString)AlphaSEU->PDFinfile + (TString)".00.pds");

 // Usually the up EV set of AlphaS has smaller AlphaS value
 // and the down EV set of AlphaS has larger AlphaS value
 pdsReader* Old_AlphaS_up = new pdsReader();
 Old_AlphaS_up->Initialize((TString)AlphaSEU->PDFinfile + (TString)".01.pds");

 pdsReader* Old_AlphaS_down = new pdsReader();
 Old_AlphaS_down->Initialize((TString)AlphaSEU->PDFinfile + (TString)".02.pds");

 Old_Delta_AlphaS = (Old_AlphaS_up->CT14Alphas(AlphaS_Q) - Old_AlphaS_down->CT14Alphas(AlphaS_Q)) / 2.0;
 Old_Delta_AlphaS_up = Old_AlphaS_up->CT14Alphas(AlphaS_Q) - Old_AlphaS_central_GA->CT14Alphas(AlphaS_Q); // usually negative if the up-central-down are like 0.112 0.118 0.124
 Old_Delta_AlphaS_down = Old_AlphaS_central_GA->CT14Alphas(AlphaS_Q) - Old_AlphaS_down->CT14Alphas(AlphaS_Q); // usually negative

 Eigen::MatrixXd M = Eigen::MatrixXd(ExtendedEU->Ni, ExtendedEU->Ni);
 for(int i = 0; i < ExtendedEU->Ni; i++){
   for(int j = 0; j < ExtendedEU->Ni; j++){
     M(i, j) = ExtendedEU->M[i][j];
   }
 }

 Eigen::MatrixXd IplusM = Eigen::MatrixXd::Identity(ExtendedEU->Ni, ExtendedEU->Ni) + M;
 IplusM_inv = IplusM.inverse();

 Eigen::MatrixXd M_sub = Eigen::MatrixXd(ExtendedEU->Ni - 1, ExtendedEU->Ni - 1);
 for(int i = 0; i < ExtendedEU->Ni - 1; i++){
   for(int j = 0; j < ExtendedEU->Ni - 1; j++){
     M_sub(i, j) = ExtendedEU->M[i][j];
   }
 }

 Eigen::MatrixXd IplusM_sub = Eigen::MatrixXd::Identity(ExtendedEU->Ni - 1, ExtendedEU->Ni - 1) + M_sub;
 IplusM_sub_inv = IplusM_sub.inverse();

 //cout<<M<<endl;
 //cout<<endl;
 //cout<<M(ExtendedEU->Ni - 1, ExtendedEU->Ni - 1)<<endl;
 //cout<<endl;
 //cout<<IplusM_inv<<endl;

 // eq.18
 double Denom2 = 1.0 + M(ExtendedEU->Ni - 1, ExtendedEU->Ni - 1);
 for(int i = 0; i < EU->Ni; i++){
   for(int j = 0; j < EU->Ni; j++){
     Denom2 -= M(ExtendedEU->Ni - 1, i) * IplusM_sub_inv(i, j) * M(ExtendedEU->Ni - 1, j);
   }
 }
 New_Delta_AlphaS = Old_Delta_AlphaS / sqrt(Denom2);
 New_Delta_AlphaS_up = Old_Delta_AlphaS_up / sqrt(Denom2);
 New_Delta_AlphaS_down = Old_Delta_AlphaS_down / sqrt(Denom2);

 Eigen::VectorXd A = Eigen::VectorXd(ExtendedEU->Ni);
 for(int i = 0; i < ExtendedEU->Ni; i++){
   A(i) = ExtendedEU->A[i];
 }

 New_BestFit_Par = IplusM_inv * A; // eq.13

 Old_AlphaS_WA = Old_AlphaS_central_WA->CT14Alphas(AlphaS_Q);
 Old_AlphaS_GA = Old_AlphaS_central_GA->CT14Alphas(AlphaS_Q);
 New_AlphaS_WA = Old_AlphaS_WA + sqrt(ExtendedEU->Tsq / AlphaSEU->TsqAvg) * New_BestFit_Par(ExtendedEU->Ni - 1) * Old_Delta_AlphaS;// eq.14 (DynTol eq.A6)
 New_AlphaS_GA = Old_AlphaS_WA + sqrt(ExtendedEU->Tsq / AlphaSEU->TsqAvg) * New_BestFit_Par(ExtendedEU->Ni - 1) * Old_Delta_AlphaS;// to be updated

 myLog<<"z prime bar (new bestfit parameters):"<<endl;
 for(int i = 0; i < ExtendedEU->Ni; i++){
   myLog<<fixed<<setprecision(4)<<New_BestFit_Par(i)<<endl;
 }
 myLog<<endl;
 myLog<<fixed<<setprecision(10)<<"AlphaS zoom factor: "<<sqrt(Denom2)<<" square: "<<Denom2<<endl;
 myLog<<endl;

 myLog<<fixed<<setprecision(4)<<"T = "<<sqrt(ExtendedEU->Tsq)<<"  T_alphaS = "<<sqrt(AlphaSEU->TsqAvg)<<"  T/T_alphaS = "<<sqrt(ExtendedEU->Tsq / AlphaSEU->TsqAvg)<<endl;
 myLog<<fixed<<setprecision(4)<<"Original AlphaS (World Average) = "<<Old_AlphaS_WA<<endl;
 myLog<<fixed<<setprecision(4)<<"Original AlphaS (Global anaylsis) = "<<Old_AlphaS_GA<<endl;
 myLog<<fixed<<setprecision(4)<<"Updated AlphaS (World Average) = "<<New_AlphaS_WA<<endl;
 myLog<<fixed<<setprecision(4)<<"Updated AlphaS (Global anaylsis) (to be updated) = "<<New_AlphaS_GA<<endl;
 myLog<<fixed<<setprecision(4)<<"Original AlphaS up = "<<Old_AlphaS_up->CT14Alphas(AlphaS_Q)<<"  Original AlphaS down = "<<Old_AlphaS_down->CT14Alphas(AlphaS_Q)<<endl;
 myLog<<fixed<<setprecision(4)<<"Updated AlphaS up = "<<New_AlphaS_GA + New_Delta_AlphaS_up<<"  Updated AlphaS down = "<<New_AlphaS_GA - New_Delta_AlphaS_down<<endl;
 myLog<<fixed<<setprecision(4)<<"Old Delta AlphaS = "<<fabs(Old_Delta_AlphaS)<<endl;
 myLog<<fixed<<setprecision(4)<<"New Delta AlphaS = "<<fabs(New_Delta_AlphaS)<<endl;


}

void ePumpHelper::UpdateAlphaSPDFs()
{
 vector<pdsReader *> OldAlphaSPDF;

 OldAlphaSPDF.resize(2 * ExtendedEU->Ni + 1);
 NewAlphaSPDF.resize(2 * ExtendedEU->Ni + 1);

 for(int i = 0; i < 2 * EU->Ni + 1; i++){
   OldAlphaSPDF.at(i) = new pdsReader();
   OldAlphaSPDF.at(i)->Initialize((TString)EU->PDFinfile + TString::Format(".%02d", i) + (TString)".pds");
   NewAlphaSPDF.at(i) = new pdsReader();
   NewAlphaSPDF.at(i)->Initialize((TString)EU->PDFinfile + TString::Format(".%02d", i) + (TString)".pds");
 }
 OldAlphaSPDF.at(2 * EU->Ni + 1) = new pdsReader();
 OldAlphaSPDF.at(2 * EU->Ni + 1)->Initialize((TString)AlphaSEU->PDFinfile + TString::Format(".%02d", 1) + (TString)".pds");
 OldAlphaSPDF.at(2 * EU->Ni + 2) = new pdsReader();
 OldAlphaSPDF.at(2 * EU->Ni + 2)->Initialize((TString)AlphaSEU->PDFinfile + TString::Format(".%02d", 2) + (TString)".pds");
 NewAlphaSPDF.at(2 * EU->Ni + 1) = new pdsReader();
 NewAlphaSPDF.at(2 * EU->Ni + 1)->Initialize((TString)AlphaSEU->PDFinfile + TString::Format(".%02d", 1) + (TString)".pds");
 NewAlphaSPDF.at(2 * EU->Ni + 2) = new pdsReader();
 NewAlphaSPDF.at(2 * EU->Ni + 2)->Initialize((TString)AlphaSEU->PDFinfile + TString::Format(".%02d", 2) + (TString)".pds");
 NewAlphaSOnlyPDF = new pdsReader();
 NewAlphaSOnlyPDF->Initialize((TString)EU->PDFinfile + TString::Format(".%02d", 0) + (TString)".pds");

 // Copy M
 Eigen::MatrixXd M = Eigen::MatrixXd(ExtendedEU->Ni, ExtendedEU->Ni);
 for(int i = 0; i < ExtendedEU->Ni; i++){
   for(int j = 0; j < ExtendedEU->Ni; j++){
     M(i, j) = ExtendedEU->M[i][j];
   }
 }

 // New best fit PDF eq.15
 vector<double> UPD = OldAlphaSPDF.at(0)->UPD;
 for(int i = 0; i < UPD.size(); i++){
   Eigen::VectorXd OldF(ExtendedEU->Ni);

   for(int iEV = 0; iEV < ExtendedEU->Ni; iEV++){

     double dx, ddx, tp, tm, tbar;

     if (ExtendedEU->T_flag == 1) {
         tp = ExtendedEU->TdynRMS[iEV];
         tm = ExtendedEU->TdynRMS[iEV];
         tbar = ExtendedEU->TdynRMS[iEV];
     } else {
         tp = ExtendedEU->TdynP[iEV];
         tm = ExtendedEU->TdynM[iEV];
         tbar = ExtendedEU->TdynBar[iEV];
     }

     TaylorCoeffs(dx, ddx, OldAlphaSPDF.at(0)->UPD.at(i), OldAlphaSPDF.at(2 * iEV + 1)->UPD.at(i), OldAlphaSPDF.at(2 * iEV + 2)->UPD.at(i), tp, tm, tbar);

     OldF(iEV) = dx;
   }
   double shift = New_BestFit_Par.dot(OldF); // eq.15
   NewAlphaSPDF.at(0)->UPD.at(i) = UPD.at(i) + shift;
   NewAlphaSOnlyPDF->UPD.at(i) = UPD.at(i) + OldF(ExtendedEU->Ni - 1) * New_BestFit_Par(ExtendedEU->Ni - 1);
 }

 //m_hoppet->InitializeAlphaS(New_AlphaS_WA, AlphaS_Q);

 vector<double> qv = OldAlphaSPDF.at(0)->qv;
 for(int i = 0; i < qv.size(); i++){
   //NewAlphaSPDF.at(0)->AlsCTEQ.at(i) = m_hoppet->EvolveAlphaS(qv.at(i));
   NewAlphaSPDF.at(0)->AlsCTEQ.at(i) = OldAlphaSPDF.at(0)->AlsCTEQ.at(i)
                                     + sqrt(ExtendedEU->Tsq / AlphaSEU->TsqAvg) * New_BestFit_Par(ExtendedEU->Ni - 1)
                                     * (OldAlphaSPDF.at(2 * EU->Ni + 1)->AlsCTEQ.at(i) - OldAlphaSPDF.at(2 * EU->Ni + 2)->AlsCTEQ.at(i)) / 2.0;


   // New 1~2N EV set have same AlphaS as the new central PDF
   for(int iEV = 0; iEV < EU->Ni; iEV++){
     NewAlphaSPDF.at(2 * iEV + 1)->AlsCTEQ.at(i) = NewAlphaSPDF.at(0)->AlsCTEQ.at(i);
     NewAlphaSPDF.at(2 * iEV + 2)->AlsCTEQ.at(i) = NewAlphaSPDF.at(0)->AlsCTEQ.at(i);
   }
 }

 // AlphaS Error PDF eq.21 (DynTol: eq.A7)
 for(int i = 0; i < UPD.size(); i++){
   double up = NewAlphaSPDF.at(0)->UPD.at(i);
   double down = NewAlphaSPDF.at(0)->UPD.at(i);

   double dx, ddx, tp, tm, tbar;

   if (ExtendedEU->T_flag == 1) {
       tp = ExtendedEU->TdynRMS[EU->Ni];
       tm = ExtendedEU->TdynRMS[EU->Ni];
       tbar = ExtendedEU->TdynRMS[EU->Ni];
   } else {
       tp = ExtendedEU->TdynP[EU->Ni];
       tm = ExtendedEU->TdynM[EU->Ni];
       tbar = ExtendedEU->TdynBar[EU->Ni];
   }

   TaylorCoeffs(dx, ddx, OldAlphaSPDF.at(0)->UPD.at(i), OldAlphaSPDF.at(2 * EU->Ni + 1)->UPD.at(i), OldAlphaSPDF.at(2 * EU->Ni + 2)->UPD.at(i), tp, tm, tbar);

   double DeltaPDF1 = OldAlphaSPDF.at(2 * EU->Ni + 1)->UPD.at(i) - OldAlphaSPDF.at(0)->UPD.at(i);
   double DeltaPDF2 = OldAlphaSPDF.at(0)->UPD.at(i) - OldAlphaSPDF.at(2 * EU->Ni + 2)->UPD.at(i);

   for(int ii = 0; ii < EU->Ni; ii++){
     for(int jj = 0; jj < EU->Ni; jj++){

       double dx, ddx, tp, tm, tbar;
       double dx1, dx2;

       if (ExtendedEU->T_flag == 1) {
           tp = ExtendedEU->TdynRMS[jj];
           tm = ExtendedEU->TdynRMS[jj];
           tbar = ExtendedEU->TdynRMS[jj];
       } else {
           tp = ExtendedEU->TdynP[jj];
           tm = ExtendedEU->TdynM[jj];
           tbar = ExtendedEU->TdynBar[jj];
       }

       TaylorCoeffs(dx, ddx, OldAlphaSPDF.at(0)->UPD.at(i), OldAlphaSPDF.at(2 * jj + 1)->UPD.at(i), OldAlphaSPDF.at(2 * jj + 2)->UPD.at(i), tp, tm, tbar);

       dx1 = OldAlphaSPDF.at(2 * jj + 1)->UPD.at(i) - OldAlphaSPDF.at(0)->UPD.at(i);
       dx2 = OldAlphaSPDF.at(0)->UPD.at(i) - OldAlphaSPDF.at(2 * jj + 2)->UPD.at(i);

       DeltaPDF1 -= M(ExtendedEU->Ni - 1, ii) * IplusM_sub_inv(ii, jj) * dx1;
       DeltaPDF2 -= M(ExtendedEU->Ni - 1, ii) * IplusM_sub_inv(ii, jj) * dx2;
     }
   }

   up = up + New_Delta_AlphaS / Old_Delta_AlphaS * DeltaPDF1;
   down = down - New_Delta_AlphaS / Old_Delta_AlphaS * DeltaPDF2;

   NewAlphaSPDF.at(2 * EU->Ni + 1)->UPD.at(i) = up;
   NewAlphaSPDF.at(2 * EU->Ni + 2)->UPD.at(i) = down;
 }

 // Error PDF set after PDF+AlphaS simultaneous fit eq.26
 for(int i = 0; i < UPD.size(); i++){
   double central = NewAlphaSPDF.at(0)->UPD.at(i);

   double dx, ddx, tp, tm, tbar;

   for(int iEV = 0; iEV < EU->Ni; iEV++){
     double f1 = 0.0, f2 = 0.0;
     for(int jEV = 0; jEV < EU->Ni; jEV++){
       double df1 = OldAlphaSPDF.at(2 * jEV + 1)->UPD.at(i) - OldAlphaSPDF.at(0)->UPD.at(i);
       double df2 = OldAlphaSPDF.at(0)->UPD.at(i) - OldAlphaSPDF.at(2 * jEV + 2)->UPD.at(i);
       f1 += ExtendedEU->U[jEV][iEV] * df1;
       f2 -= ExtendedEU->U[jEV][iEV] * df2;
     }
     f1 /= sqrt(ExtendedEU->Pweight + ExtendedEU->d[iEV]);
     f2 /= sqrt(ExtendedEU->Pweight + ExtendedEU->d[iEV]);
     f1 += central;
     f2 += central;

     NewAlphaSPDF.at(2 * iEV + 1)->UPD.at(i) = f1;
     NewAlphaSPDF.at(2 * iEV + 2)->UPD.at(i) = f2;
   }
 }

 double Denom2 = 1.0 + M(ExtendedEU->Ni - 1, ExtendedEU->Ni - 1);
 for(int ii = 0; ii < EU->Ni; ii++){
   for(int jj = 0; jj < EU->Ni; jj++){
     Denom2 -= M(ExtendedEU->Ni - 1, ii) * IplusM_sub_inv(ii, jj) * M(ExtendedEU->Ni - 1, jj);
   }
 }

 //m_hoppet->InitializeAlphaS(New_AlphaS_WA + New_Delta_AlphaS_up, AlphaS_Q);
 for(int i = 0; i < qv.size(); i++){
   //NewAlphaSPDF.at(2 * EU->Ni + 1)->AlsCTEQ.at(i) = m_hoppet->EvolveAlphaS(qv.at(i));

   double Old_Delta_AlphaS_up = OldAlphaSPDF.at(2 * EU->Ni + 1)->AlsCTEQ.at(i) - OldAlphaSPDF.at(0)->AlsCTEQ.at(i); // usually negative if the up-central-down are like 0.112 0.118 0.124
   double New_Delta_AlphaS_up = Old_Delta_AlphaS_up / sqrt(Denom2);

   NewAlphaSPDF.at(2 * EU->Ni + 1)->AlsCTEQ.at(i) = NewAlphaSPDF.at(0)->AlsCTEQ.at(i) + New_Delta_AlphaS_up;
 }

 //m_hoppet->InitializeAlphaS(New_AlphaS_WA - New_Delta_AlphaS_down, AlphaS_Q);
 for(int i = 0; i < qv.size(); i++){
   //NewAlphaSPDF.at(2 * EU->Ni + 2)->AlsCTEQ.at(i) = m_hoppet->EvolveAlphaS(qv.at(i));

   double Old_Delta_AlphaS_down = OldAlphaSPDF.at(0)->AlsCTEQ.at(i) - OldAlphaSPDF.at(2 * EU->Ni + 2)->AlsCTEQ.at(i); // usually negative
   double New_Delta_AlphaS_down = Old_Delta_AlphaS_down / sqrt(Denom2);

   NewAlphaSPDF.at(2 * EU->Ni + 2)->AlsCTEQ.at(i) = NewAlphaSPDF.at(0)->AlsCTEQ.at(i) - New_Delta_AlphaS_down;
 }

 NewAlphaSPDF.at(0)->OutputPDF((TString)ExtendedEU->PDFoutfile + (TString)".00.pds");

 for(int i = 0; i < ExtendedEU->Ni; i++){
   NewAlphaSPDF.at(2 * i + 1)->OutputPDF((TString)ExtendedEU->PDFoutfile + TString::Format(".%02d", 2 * i + 1) + (TString)".pds");
   NewAlphaSPDF.at(2 * i + 2)->OutputPDF((TString)ExtendedEU->PDFoutfile + TString::Format(".%02d", 2 * i + 2) + (TString)".pds");
 }
}

void ePumpHelper::UpdateAlphaSObservables()
{
 // Initialize vector of new observables
 NewObservableSet.resize(ExtendedEU->Ndata);
 ObservableDeltaAlphaS.resize(ExtendedEU->Ndata);
 ObservableDeltaAlphaSPlus.resize(ExtendedEU->Ndata);
 ObservableDeltaAlphaSMinus.resize(ExtendedEU->Ndata);
 NewObservableAlphaSOnly.resize(ExtendedEU->Ndata);
 for(int idata = 0; idata < ExtendedEU->Ndata; idata++){
   NewObservableSet.at(idata).resize(ExtendedEU->Na[idata]);
   ObservableDeltaAlphaS.at(idata).resize(ExtendedEU->Na[idata]);
   ObservableDeltaAlphaSPlus.at(idata).resize(ExtendedEU->Na[idata]);
   ObservableDeltaAlphaSMinus.at(idata).resize(ExtendedEU->Na[idata]);
   NewObservableAlphaSOnly.at(idata).resize(ExtendedEU->Na[idata]);
   for(int ipoint = 0; ipoint < ExtendedEU->Na[idata]; ipoint++){
     NewObservableSet.at(idata).at(ipoint).resize(2 * ExtendedEU->Ni + 1);
   }
 }

 // Copy M
 Eigen::MatrixXd M = Eigen::MatrixXd(ExtendedEU->Ni, ExtendedEU->Ni);
 for(int i = 0; i < ExtendedEU->Ni; i++){
   for(int j = 0; j < ExtendedEU->Ni; j++){
     M(i, j) = ExtendedEU->M[i][j];
   }
 }

 for(int idata = 0; idata < ExtendedEU->Ndata; idata++){

   for(int ipoint = 0; ipoint < ExtendedEU->Na[idata]; ipoint++){

     // New best fit observable eq.15
     double Central = ExtendedEU->Xmat[idata][ipoint][0];

     Eigen::VectorXd OldObservable(ExtendedEU->Ni);
    
     for(int iEV = 0; iEV < ExtendedEU->Ni; iEV++){
    
       double Up = ExtendedEU->Xmat[idata][ipoint][2 * iEV + 1];
       double Down = ExtendedEU->Xmat[idata][ipoint][2 * iEV + 2];

       double dx, ddx, tp, tm, tbar;
    
       if (ExtendedEU->T_flag == 1) {
           tp = ExtendedEU->TdynRMS[iEV];
           tm = ExtendedEU->TdynRMS[iEV];
           tbar = ExtendedEU->TdynRMS[iEV];
       } else {
           tp = ExtendedEU->TdynP[iEV];
           tm = ExtendedEU->TdynM[iEV];
           tbar = ExtendedEU->TdynBar[iEV];
       }

       TaylorCoeffs(dx, ddx, Central, Up, Down, tp, tm, tbar);
    
       OldObservable(iEV) = dx;
     }
     double shift = New_BestFit_Par.dot(OldObservable); // eq.15
     NewObservableSet.at(idata).at(ipoint).at(0) = Central + shift;
     NewObservableAlphaSOnly.at(idata).at(ipoint) = Central + OldObservable(ExtendedEU->Ni - 1) * New_BestFit_Par(ExtendedEU->Ni - 1);
    
     // AlphaS Error observable eq.21 (DynTol: eq.A7)
     double up = NewObservableSet.at(idata).at(ipoint).at(0);
     double down = NewObservableSet.at(idata).at(ipoint).at(0);

     double dx, ddx, tp, tm, tbar;
    
     if (ExtendedEU->T_flag == 1) {
         tp = ExtendedEU->TdynRMS[EU->Ni];
         tm = ExtendedEU->TdynRMS[EU->Ni];
         tbar = ExtendedEU->TdynRMS[EU->Ni];
     } else {
         tp = ExtendedEU->TdynP[EU->Ni];
         tm = ExtendedEU->TdynM[EU->Ni];
         tbar = ExtendedEU->TdynBar[EU->Ni];
     }
    
     TaylorCoeffs(dx, ddx, Central, ExtendedEU->Xmat[idata][ipoint][2 * EU->Ni + 1], ExtendedEU->Xmat[idata][ipoint][2 * EU->Ni + 2], tp, tm, tbar);

     double DeltaPDF = dx;
     double DeltaPDF1 = ExtendedEU->Xmat[idata][ipoint][2 * EU->Ni + 1] - Central;
     double DeltaPDF2 = Central - ExtendedEU->Xmat[idata][ipoint][2 * EU->Ni + 2];

     for(int ii = 0; ii < EU->Ni; ii++){
       for(int jj = 0; jj < EU->Ni; jj++){
    
         double dx, ddx, tp, tm, tbar;
         double dx1, dx2;
    
         if (ExtendedEU->T_flag == 1) {
             tp = ExtendedEU->TdynRMS[jj];
             tm = ExtendedEU->TdynRMS[jj];
             tbar = ExtendedEU->TdynRMS[jj];
         } else {
             tp = ExtendedEU->TdynP[jj];
             tm = ExtendedEU->TdynM[jj];
             tbar = ExtendedEU->TdynBar[jj];
         }
    
         TaylorCoeffs(dx, ddx, Central, ExtendedEU->Xmat[idata][ipoint][2 * jj + 1], ExtendedEU->Xmat[idata][ipoint][2 * jj + 2], tp, tm, tbar);

         dx1 = ExtendedEU->Xmat[idata][ipoint][2 * jj + 1] - Central;
         dx2 = Central - ExtendedEU->Xmat[idata][ipoint][2 * jj + 2];

         DeltaPDF -= M(ExtendedEU->Ni - 1, ii) * IplusM_sub_inv(ii, jj) * dx;
         DeltaPDF1 -= M(ExtendedEU->Ni - 1, ii) * IplusM_sub_inv(ii, jj) * dx1;
         DeltaPDF2 -= M(ExtendedEU->Ni - 1, ii) * IplusM_sub_inv(ii, jj) * dx2;
       }
     }

     ObservableDeltaAlphaS.at(idata).at(ipoint) = DeltaPDF;
     ObservableDeltaAlphaSPlus.at(idata).at(ipoint) = DeltaPDF1;
     ObservableDeltaAlphaSMinus.at(idata).at(ipoint) = DeltaPDF2;

     //up = up + AlphaSEU->TsqAvg / ExtendedEU->Tsq * New_Delta_AlphaS / Old_Delta_AlphaS * DeltaPDF;
     //down = down - AlphaSEU->TsqAvg / ExtendedEU->Tsq * New_Delta_AlphaS / Old_Delta_AlphaS * DeltaPDF;
     up = up + New_Delta_AlphaS / Old_Delta_AlphaS * DeltaPDF1;
     down = down - New_Delta_AlphaS / Old_Delta_AlphaS * DeltaPDF2;

     NewObservableSet.at(idata).at(ipoint).at(2 * EU->Ni + 1) = up;
     NewObservableSet.at(idata).at(ipoint).at(2 * EU->Ni + 2) = down;
   }
 }

 myLog<<endl;
 myLog<<"---------------------------------------------------------------"<<endl;
 myLog<<"      Original and Updated Predictions and Uncertainties"<<endl;
 myLog<<"------------------------------------------------------------"<<endl;
 myLog<<endl;

 for(int idata = 0; idata < ExtendedEU->Ndata; idata++){

   myLog<<" For Observables X[a] in Data Set: "<<ExtendedEU->dataset[idata]<<endl<<endl;
   myLog<<"      a         X[a]          X+[a]         X-[a]       DXsym[a]"<<endl;

   for(int ipoint = 0; ipoint < ExtendedEU->Na[idata]; ipoint++){

     myLog<<"Old"<<setw(4)<<ipoint + 1<<"  ";
     myLog<<setw(14)<<setprecision(4)<<scientific<<ExtendedEU->Xmat[idata][ipoint][0];
     myLog<<setw(14)<<setprecision(4)<<scientific<<ExtendedEU->Xmat[idata][ipoint][2 * EU->Ni + 1];
     myLog<<setw(14)<<setprecision(4)<<scientific<<ExtendedEU->Xmat[idata][ipoint][2 * EU->Ni + 2];
     myLog<<setw(14)<<setprecision(4)<<scientific<<fabs(ExtendedEU->Xmat[idata][ipoint][2 * EU->Ni + 2] - ExtendedEU->Xmat[idata][ipoint][2 * EU->Ni + 1]) / 2.0<<endl;
     myLog<<"New"<<setw(4)<<ipoint + 1<<"  ";
     myLog<<setw(14)<<setprecision(4)<<scientific<<NewObservableSet[idata][ipoint][0];
     myLog<<setw(14)<<setprecision(4)<<scientific<<NewObservableSet[idata][ipoint][2 * EU->Ni + 1];
     myLog<<setw(14)<<setprecision(4)<<scientific<<NewObservableSet[idata][ipoint][2 * EU->Ni + 2];
     myLog<<setw(14)<<setprecision(4)<<scientific<<fabs(NewObservableSet[idata][ipoint][2 * EU->Ni + 2] - NewObservableSet[idata][ipoint][2 * EU->Ni + 1]) / 2.0<<endl;
     myLog<<endl;
   }
 }
}

void ePumpHelper::UpdateAlphaSLMScan()
{
 DefineCombination();
 DefineDataLegend();
 NameTransfer();

 int nScanPoint = 20;//yfu search here

 vector<double> AlphaSSet(nScanPoint);
 vector<double> BestFitSet(nScanPoint);

 map<TString, vector<double>> Chi2Map;
 for(int idata = 0; idata < ExtendedEU->Ndata; idata++){
   Chi2Map[ExtendedEU->dataset[idata]].resize(nScanPoint);
 }
 Chi2Map[(TString)"Total"].resize(nScanPoint);

 double step = (0.126 - 0.110) / (double)(nScanPoint - 1);
 for(int i = 0; i < AlphaSSet.size(); i++){
   cout<<"Scan "<<i + 1<<endl;
   AlphaSSet.at(i) = 0.110 + step * i;

   double TotalDeltaChi2 = 0.0;
   for(int idata = 0; idata < ExtendedEU->Ndata; idata++){

     vector<double> TheoryVector(ExtendedEU->Na[idata]);
     for(int ipoint = 0; ipoint < ExtendedEU->Na[idata]; ipoint++){

       double Value = NewObservableSet.at(idata).at(ipoint).at(0);
       // replace the New_Delta_AlphaS by (AlphaSSet.at(i) - New_AlphaS_GA)
       // if the AlphaSSet.at(i) = New_AlphaS_GA + New_Delta_AlphaS, the results will be corresponding to X+[a]
       // if the AlphaSSet.at(i) = New_AlphaS_GA - New_Delta_AlphaS, the results will be corresponding to X-[a]

       if((AlphaSSet.at(i) - Old_AlphaS_GA) * Old_Delta_AlphaS_up > 0){
         Value = Value + (AlphaSSet.at(i) - New_AlphaS_GA) / Old_Delta_AlphaS * ObservableDeltaAlphaSPlus.at(idata).at(ipoint);
       }
       else{
         Value = Value + (AlphaSSet.at(i) - New_AlphaS_GA) / Old_Delta_AlphaS * ObservableDeltaAlphaSMinus.at(idata).at(ipoint);
       }
       //Value = Value + (AlphaSSet.at(i) - New_AlphaS_GA) / Old_Delta_AlphaS * ObservableDeltaAlphaS.at(idata).at(ipoint);

       TheoryVector.at(ipoint) = Value;
     }

     Chi2Map[(TString)ExtendedEU->dataset[idata]].at(i) = ExtendedEU->DeltaChiSquareReal(TheoryVector, idata);
     TotalDeltaChi2 += Chi2Map[(TString)ExtendedEU->dataset[idata]].at(i);
   }
   Chi2Map[(TString)"Total"].at(i) = TotalDeltaChi2;
   Chi2Map[(TString)"Total"].at(i) = ExtendedEU->Tsq * pow((AlphaSSet.at(i) - New_AlphaS_GA) / New_Delta_AlphaS, 2);
 }

 BestFitSet = AlphaSSet;

 double BestFitSolution = Chi2Solution(BestFitSet, Chi2Map[(TString)"Total"]);//find the bestfit of the total chi2

 double xmax = BestFitSet.at(0) - 3.0 * (BestFitSet.at(1) - BestFitSet.at(0));
 double xmin = BestFitSet.at(nScanPoint - 1) + 3.0 * (BestFitSet.at(nScanPoint - 1) - BestFitSet.at(nScanPoint - 2));
 double PlotXMin = 0.0;
 double PlotXMax = 0.0;

 double Q = AlphaS_Q;
 TString Qstring = TString::Format("%.2f", Q);;

 map<double, TString> LMErrors;
 map<double, TString> ChiSquare1Map;
 map<double, TString> ChiSquare2Map;
 map<TString, double> ChiSquare1;
 map<TString, double> ChiSquare2;

 for(auto iter = Chi2Map.begin(); iter != Chi2Map.end(); iter++){

   TString HistName = (TString)"AlphaSLMScanOriginResult_" + iter->first;
   HistName.ReplaceAll("/", "_");
   HistName.ReplaceAll(".", "_");
   HistName.ReplaceAll("-", "m");
   TString FittingName = (TString)"AlphaSLMScanOriginFitting_" + iter->first;
   FittingName.ReplaceAll("/", "_");
   FittingName.ReplaceAll(".", "_");
   FittingName.ReplaceAll("-", "m");
   TString PointName = (TString)"AlphaSLMScanOriginPoint_" + iter->first;
   PointName.ReplaceAll("/", "_");
   PointName.ReplaceAll(".", "_");
   PointName.ReplaceAll("-", "m");


   AlphaSLMScanOriginResult[make_tuple(iter->first)] = new TGraph(nScanPoint);
   AlphaSLMScanOriginResult[make_tuple(iter->first)]->SetName(HistName);
   AlphaSLMScanOriginResult[make_tuple(iter->first)]->SetTitle(HistName);

   AlphaSLMScanOriginPoint[make_tuple(iter->first)] = new TGraph(nScanPoint);
   AlphaSLMScanOriginPoint[make_tuple(iter->first)]->SetName(PointName);
   AlphaSLMScanOriginPoint[make_tuple(iter->first)]->SetTitle(PointName);

   for(int ibin = 1; ibin <= nScanPoint; ibin++){
     AlphaSLMScanOriginResult[make_tuple(iter->first)]->SetPointX(ibin, BestFitSet.at(ibin - 1));
     AlphaSLMScanOriginResult[make_tuple(iter->first)]->SetPointY(ibin, Chi2Map[iter->first].at(ibin - 1));
     AlphaSLMScanOriginPoint[make_tuple(iter->first)]->SetPointX(ibin, BestFitSet.at(ibin - 1));
     AlphaSLMScanOriginPoint[make_tuple(iter->first)]->SetPointY(ibin, Chi2Map[iter->first].at(ibin - 1));
     myLog<<"ScanResult for Data "<<iter->first<<" BestFit = "<<BestFitSet.at(ibin - 1)<<" Chi2 = "<<Chi2Map[iter->first].at(ibin - 1)<<endl;
   }
   AlphaSLMScanOriginResult[make_tuple(iter->first)]->RemovePoint(0);
   AlphaSLMScanOriginResult[make_tuple(iter->first)]->SetMarkerSize(0);
   AlphaSLMScanOriginResult[make_tuple(iter->first)]->SetMarkerColor(0);
   AlphaSLMScanOriginResult[make_tuple(iter->first)]->SetLineWidth(0);
   AlphaSLMScanOriginResult[make_tuple(iter->first)]->SetLineColor(0);
   AlphaSLMScanOriginResult[make_tuple(iter->first)]->SetLineStyle(1);
   AlphaSLMScanOriginResult[make_tuple(iter->first)]->SetMarkerStyle(34);
   AlphaSLMScanOriginPoint[make_tuple(iter->first)]->RemovePoint(0);

   AlphaSLMScanOriginFitting[make_tuple(iter->first)] = new TF1(FittingName, "[0]*x*x+[1]*x+[2]", xmin, xmax);
   AlphaSLMScanOriginResult[make_tuple(iter->first)]->Fit(AlphaSLMScanOriginFitting[make_tuple(iter->first)], "W");

   /////////////////////////////////////////////////////////////////////////////////////////////////////////////////

   HistName.ReplaceAll("AlphaSLMScanOriginResult", "AlphaSLMScanResult");
   FittingName.ReplaceAll("AlphaSLMScanOriginFitting", "AlphaSLMScanFitting");
   PointName.ReplaceAll("AlphaSLMScanOriginPoint", "AlphaSLMScanPoint");

   AlphaSLMScanResult[make_tuple(iter->first)] = new TGraph(nScanPoint);
   AlphaSLMScanResult[make_tuple(iter->first)]->SetName(HistName);
   AlphaSLMScanResult[make_tuple(iter->first)]->SetTitle(HistName);

   AlphaSLMScanPoint[make_tuple(iter->first)] = new TGraph(nScanPoint);
   AlphaSLMScanPoint[make_tuple(iter->first)]->SetName(PointName);
   AlphaSLMScanPoint[make_tuple(iter->first)]->SetTitle(PointName);

   for(int ibin = 1; ibin <= nScanPoint; ibin++){
     double DataOriginChi2 = AlphaSLMScanOriginFitting[make_tuple(iter->first)]->Eval(BestFitSolution);

     AlphaSLMScanResult[make_tuple(iter->first)]->SetPointX(ibin, BestFitSet.at(ibin - 1));
     AlphaSLMScanResult[make_tuple(iter->first)]->SetPointY(ibin, Chi2Map[iter->first].at(ibin - 1) - DataOriginChi2);
     AlphaSLMScanPoint[make_tuple(iter->first)]->SetPointX(ibin, BestFitSet.at(ibin - 1));
     AlphaSLMScanPoint[make_tuple(iter->first)]->SetPointY(ibin, Chi2Map[iter->first].at(ibin - 1) - DataOriginChi2);
     myLog<<"ScanResult for Data "<<iter->first<<" BestFit = "<<BestFitSet.at(ibin - 1)<<" Chi2 = "<<Chi2Map[iter->first].at(ibin - 1) - DataOriginChi2<<endl;
   }
   AlphaSLMScanResult[make_tuple(iter->first)]->RemovePoint(0);
   AlphaSLMScanResult[make_tuple(iter->first)]->SetMarkerSize(0);
   AlphaSLMScanResult[make_tuple(iter->first)]->SetMarkerColor(0);
   AlphaSLMScanResult[make_tuple(iter->first)]->SetLineWidth(0);
   AlphaSLMScanResult[make_tuple(iter->first)]->SetLineColor(0);
   AlphaSLMScanResult[make_tuple(iter->first)]->SetLineStyle(1);
   AlphaSLMScanResult[make_tuple(iter->first)]->SetMarkerStyle(34);
   AlphaSLMScanResult[make_tuple(iter->first)]->SetFillStyle(0);
   AlphaSLMScanResult[make_tuple(iter->first)]->SetFillColor(0);

   AlphaSLMScanPoint[make_tuple(iter->first)]->RemovePoint(0);

   AlphaSLMScanFitting[make_tuple(iter->first)] = new TF1(FittingName, "[0]*x*x+[1]*x+[2]", xmin, xmax);
   if(iter->first == "Total") AlphaSLMScanFitting[make_tuple(iter->first)]->SetNpx(1000);
   AlphaSLMScanResult[make_tuple(iter->first)]->Fit(AlphaSLMScanFitting[make_tuple(iter->first)], "W");
   AlphaSLMScanFitting[make_tuple(iter->first)]->SetFillStyle(0);

   /////////////////////////////////////////////////////////////////////////////////////////////////////////////////


   double par[3];
   AlphaSLMScanFitting[make_tuple(iter->first)]->GetParameters(par);

   double Central = -par[1] / (2 * par[0]);
   double MinChi2 = (4 * par[0] * par[2] - par[1] * par[1]) / (4 * par[0]);
   double Solution1 = (-par[1] - sqrt(par[1] * par[1] - 4.0 * par[0] * (par[2] - AlphaSEU->Tsq))) / (2 * par[0]);
   double Solution2 = (-par[1] + sqrt(par[1] * par[1] - 4.0 * par[0] * (par[2] - AlphaSEU->Tsq))) / (2 * par[0]);
   double Solution3 = (-par[1] - sqrt(par[1] * par[1] - 4.0 * par[0] * (par[2] - 2.0 * AlphaSEU->Tsq - 30.0))) / (2 * par[0]);
   double Solution4 = (-par[1] + sqrt(par[1] * par[1] - 4.0 * par[0] * (par[2] - 2.0 * AlphaSEU->Tsq - 30.0))) / (2 * par[0]);

   myLog<<"T2 = "<<AlphaSEU->Tsq<<endl;
   myLog<<"MinChi2 for Data "<<iter->first<<" = "<<MinChi2<<" Central = "<<Central<<" Solution1 = "<<Solution1<<" Solution2 = "<<Solution2<<" Delta = "<<(Solution2 - Solution1) / 2.0<<endl;
   myLog<<"Solution3 = "<<Solution3<<"  Solution4 = "<<Solution4<<"  xmin = "<<xmin<<"  xmax = "<<xmax<<endl;

   if(iter->first == "Total"){
     PlotXMin = Solution1;
     PlotXMax = Solution2;
     //AlphaSLMScanPlotXMin = Solution3;
     //AlphaSLMScanPlotXMax = Solution4;
     AlphaSLMScanPlotXMin = Solution3 < xmin ? xmin : Solution3;
     AlphaSLMScanPlotXMax = Solution4 > xmax ? xmax : Solution4;
   }

   if(iter->first != "Total") LMErrors[(Solution2 - Solution1) / 2.0] = iter->first;
   if(iter->first != "Total") ChiSquare1[iter->first] = AlphaSLMScanFitting[make_tuple(iter->first)]->Eval(PlotXMin);
   if(iter->first != "Total") ChiSquare2[iter->first] = AlphaSLMScanFitting[make_tuple(iter->first)]->Eval(PlotXMax);
   if(iter->first != "Total") ChiSquare1Map[AlphaSLMScanFitting[make_tuple(iter->first)]->Eval(PlotXMin)] = iter->first;
   if(iter->first != "Total") ChiSquare2Map[AlphaSLMScanFitting[make_tuple(iter->first)]->Eval(PlotXMax)] = iter->first;

   if(isLinkFile){
     hf->cd();

     AlphaSLMScanOriginResult[make_tuple(iter->first)]->Write();
     AlphaSLMScanOriginFitting[make_tuple(iter->first)]->Write();
     AlphaSLMScanOriginPoint[make_tuple(iter->first)]->Write();

     AlphaSLMScanResult[make_tuple(iter->first)]->Write();
     AlphaSLMScanFitting[make_tuple(iter->first)]->Write();
     AlphaSLMScanPoint[make_tuple(iter->first)]->Write();
   }
 }

 ////////////////
 //  Plotting  //
 ////////////////

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

 TString FigureName = (TString)"UpdatedAlphaSLMScan.pdf";
 TString XaxisName = "#alpha_{s}(M_{Z})";
 TString YaxisName = "#Delta #chi^{2}";

 Figure* f;

 f = new Figure(FigureName, XaxisName, YaxisName);
 f->SetMode("CUSTOM");
 f->InputTF1(1, AlphaSLMScanFitting[make_tuple((TString)"Total")], "Total");

 int iplot = 2;

 if(LMScanDrawList.size() == 0){
   int nNewData = 0;
   for(int idata = 0; idata < ExtendedEU->Ndata; idata++){
     if(iplot >= 15) break;
     if(fabs(ExtendedEU->weight[idata]) < 1e-20) continue;

     f->InputTF1(iplot, AlphaSLMScanFitting[make_tuple((TString)ExtendedEU->dataset[idata])], DataLegend[NickNameMap[(TString)ExtendedEU->dataset[idata]]]);

     iplot++;
     nNewData++;
   }

   for(auto iter = LMErrors.begin(); iter != LMErrors.end(); iter++){
     if(iplot >= 15) break;

     if(fabs(ExtendedEU->weight[DataIndex[iter->second]]) > 1e-20) continue;

     f->InputTF1(iplot, AlphaSLMScanFitting[make_tuple(iter->second)], DataLegend[NickNameMap[iter->second]]);
     iplot++;
   }
 }
 else{
   for(int i = 0; i < LMScanDrawList.size(); i++){
     f->InputTF1(i + 2, AlphaSLMScanFitting[make_tuple(LMScanDrawList.at(i))], DataLegend[NickNameMap[LMScanDrawList.at(i)]]);
   }
 }

 //f->InputTF1(iplot, AlphaSLMScanFitting[make_tuple("tabsCT18Am253/ZpT_as0118")], DataLegend[NickNameMap["tabsCT18Am253/ZpT_as0118"]]);

 double LegendYMin = 0.4; 
 if(LMScanDrawList.size() >= 13) LegendYMin = 0.4 - (LMScanDrawList.size() - 13) * 0.05;

 f->Compare("MultiSimple");
 f->SetCustomPlotFormat(1, 1, kBlack);
 f->SetCanvasSize(1400.0, 1200.0);
 f->SetLegendPosition(1.0, LegendYMin, 1.2, 0.9);
 f->SetCustomLegendSize(1, 0.025);
 f->SetCustomRightMargin(1, 0.2);
 f->SetCustomLeftMargin(1, 0.15);
 f->SetXRange(AlphaSLMScanPlotXMin, AlphaSLMScanPlotXMax);
 f->SetCustomYRange(1, -20, 100);
 f->SetCustomXTitleOffset(1, 1.0);

 if(LMScanDrawList.size() == 0){
   for(int i = 2; i <= 16; i++){
     f->SetCustomLineStyle(1, i, PlotLineStyle[i]);
   }
 }
 else{
   for(int i = 1; i <= LMScanDrawList.size(); i++){
     f->SetCustomLineStyle(1, i + 1, PlotLineStyle[i + 1]);
   }
 }

 f->SetCustomLineWidth(1, 1, 6);

 f->Draw();

 iplot = 2;
 for(auto iter = ChiSquare2Map.begin(); iter != ChiSquare2Map.end(); iter++){
   //if(iplot >= 9) break;
   myLog<<fixed<<setprecision(3)<<iter->second<<": "<<iter->first<<" Chi2 = "<<ChiSquare1[iter->second]<<" "<<ChiSquare2[iter->second]<<endl;
   iplot++;
 }

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

 LMErrors.clear();
 Chi2Map.clear();
}

void ePumpHelper::UpdateAlphaSLMScanPDF(int flavor, double x, double Q)
{
 int isNewPDF = 1;

 ePump* LMScan = Clone(EU);
 AddLMScanConstrain(LMScan);

 for(int i = 0; i < EU->weight.size(); i++){
   LMScan->weight.at(i) = EU->weight.at(i);
 }

 LMScan->X0[LMScan->Ndata - 1][0] = NewAlphaSOnlyPDF->Getf(flavor, x, Q);
 for(int i = 0; i < 2 * LMScan->Ni + 1; i++){
   LMScan->Xmat[LMScan->Ndata - 1][0][i] = OldPDFSet.at(i)->Getf(flavor, x, Q) + (NewAlphaSOnlyPDF->Getf(flavor, x, Q) - OldPDFSet.at(0)->Getf(flavor, x, Q));
   LMScan->XmatNew[LMScan->Ndata - 1][0][i] = OldPDFSet.at(i)->Getf(flavor, x, Q) + (NewAlphaSOnlyPDF->Getf(flavor, x, Q) - OldPDFSet.at(0)->Getf(flavor, x, Q));
   LMScan->Xset[LMScan->Ndata - 1][i][0] = OldPDFSet.at(i)->Getf(flavor, x, Q) + (NewAlphaSOnlyPDF->Getf(flavor, x, Q) - OldPDFSet.at(0)->Getf(flavor, x, Q));
 }

 LMScan->Xmat[LMScan->Ndata - 1][0][0] = NewAlphaSOnlyPDF->Getf(flavor, x, Q);
 LMScan->XmatNew[LMScan->Ndata - 1][0][0] = NewAlphaSOnlyPDF->Getf(flavor, x, Q);
 LMScan->Xset[LMScan->Ndata - 1][0][0] = NewAlphaSOnlyPDF->Getf(flavor, x, Q);

 for(int i = 0; i < LMScan->Ni; i++){
   LMScan->dX[LMScan->Ndata - 1][0][i] = (OldPDFSet.at(2 * i + 1)->Getf(flavor, x, Q) - OldPDFSet.at(2 * i + 2)->Getf(flavor, x, Q)) / 2.0;
 }

 LMScan->XE[LMScan->Ndata - 1][0] = NewAlphaSOnlyPDF->Getf(flavor, x, Q);//Data Point (to be the same as theory), from 0

 LMScan->s[LMScan->Ndata - 1][0] = 1.0;//Data Err
 LMScan->dataset[LMScan->Ndata - 1] = "LMConstrain";
 LMScan->SetLMScanData(LMScan->Ndata - 1);

 LMScan->ConstructCm1(LMScan->Ndata - 1);

 LMScan->dChi2[LMScan->Ndata - 1] = LMScan->DeltaChiSquare(LMScan->X0[LMScan->Ndata - 1], LMScan->Ndata - 1);
 LMScan->dChi2Set[LMScan->Ndata - 1].resize(2 * LMScan->Ni + 1);
 LMScan->dChi2newSet[LMScan->Ndata - 1].resize(2 * LMScan->Ni + 1);

 for(int iEV = 0; iEV < 2 * LMScan->Ni + 1; iEV++){
   vector<double> TheoryTemplate(1);
   TheoryTemplate.at(0) = LMScan->Xmat[LMScan->Ndata - 1][0][iEV];
   LMScan->dChi2Set[LMScan->Ndata - 1][iEV] = LMScan->DeltaChiSquare(TheoryTemplate, LMScan->Ndata - 1);
   TheoryTemplate.clear();
 }

 LMScan->SetXdyn(LMScan->Ndata - 1);

//Calculate Old PDF Uncertainty
 double Unc2 = 0.0;
 for(int i = 0; i < LMScan->Ni; i++){
   Unc2 += (LMScan->Xmat[LMScan->Ndata - 1][0][2 * i + 1] - LMScan->Xmat[LMScan->Ndata - 1][0][2 * i + 2]) * (LMScan->Xmat[LMScan->Ndata - 1][0][2 * i + 1] - LMScan->Xmat[LMScan->Ndata - 1][0][2 * i + 2]) / 4.0;
 }
 LMScan->OldPDFError[LMScan->Ndata - 1].at(0) = sqrt(Unc2);

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

 int nScanPoint = 10;//yfu search here

 vector<double> LambdaSet(nScanPoint);
 vector<double> BestFitSet(nScanPoint);

 map<TString, vector<double>> Chi2Map;
 for(int idata = 0; idata < AllDataNames.size(); idata++){
   Chi2Map[AllDataNames.at(idata)].resize(nScanPoint);
 }
 Chi2Map[(TString)"Total"].resize(nScanPoint);

 double nTimesUnc = 1.0;

 double step = nTimesUnc * LMScan->Tsq / LMScan->OldPDFError[LMScan->Ndata - 1].at(0) / ((double)nScanPoint / 2.0);
 for(int i = 0; i < LambdaSet.size(); i++){
   cout<<"Scan "<<i + 1<<endl;
   LambdaSet.at(i) = (-1.0) * nTimesUnc * LMScan->Tsq / LMScan->OldPDFError[LMScan->Ndata - 1].at(0) + step * i;

   LMScan->weight[LMScan->Ndata - 1] = LambdaSet.at(i);
   LMScan->ConstructUpdateMatrix();
   LMScan->UpdateObservables();

   BestFitSet.at(i) = LMScan->NewTheory.at(LMScan->Ndata - 1).at(0);
   double TotalDeltaChi2 = 0.0;
   for(int idata = 0; idata < AllDataNames.size(); idata++){
     //Chi2Map[AllDataNames.at(idata)].at(i) = LMScan->dChi2new.at(idata);
     //TotalDeltaChi2 += LMScan->dChi2new.at(idata);

     vector<double> TheoryVector(LMScan->Na[idata]);
     for(int ipoint = 0; ipoint < LMScan->Na[idata]; ipoint++){
       TheoryVector.at(ipoint) = LMScan->NewTheory.at(idata).at(ipoint) + (NewObservableAlphaSOnly.at(idata).at(ipoint) - LMScan->Xmat.at(idata).at(ipoint).at(0));
     }
     Chi2Map[AllDataNames.at(idata)].at(i) = LMScan->DeltaChiSquareReal(TheoryVector, idata);
   }

   // Calculate Total Delta Chi2, T^2 * sum z_i*2;
   //Chi2Map[(TString)"Total"].at(i) = TotalDeltaChi2;
   Chi2Map[(TString)"Total"].at(i) = LMScan->Tsq * pow(LMScan->NewLength, 2);
 }

 double BestFitSolution = Chi2Solution(BestFitSet, Chi2Map[(TString)"Total"]);//find the bestfit of the total chi2
 double SortingSolution = Chi2Solution(BestFitSet, Chi2Map[(TString)"Total"], LMScan->Tsq);//sorting

 double xmin = BestFitSet.at(0) - 20.0 * (BestFitSet.at(1) - BestFitSet.at(0));
 double xmax = BestFitSet.at(nScanPoint - 1) + 20.0 * (BestFitSet.at(nScanPoint - 1) - BestFitSet.at(nScanPoint - 2));
 double PlotXMin = 0.0;
 double PlotXMax = 0.0;

 stringstream s_Qstring;
 TString Qstring;
 s_Qstring<<fixed<<setprecision(2)<<Q;
 Qstring = s_Qstring.str();

 stringstream s_xstring;
 stringstream s_xstring_fixed;
 TString xstring;
 TString xstring_fixed;
 s_xstring<<scientific<<setprecision(2)<<x;
 xstring = s_xstring.str();
 s_xstring_fixed<<fixed<<setprecision(2)<<x;
 xstring_fixed = s_xstring_fixed.str();

 map<double, TString> LMErrors;
 map<double, TString> ChiSquare1InverseMap;
 map<double, TString> ChiSquare2InverseMap;
 map<TString, double> ChiSquare1;
 map<TString, double> ChiSquare2;

 for(auto iter = Chi2Map.begin(); iter != Chi2Map.end(); iter++){

   TString HistName;
   HistName = (TString)"UpdatedAlphaSPDFLMScanOriginResult_" + iter->first + "_" + FlavorNameMap[flavor] + "_x" + xstring + "_Q" + Qstring;
   HistName.ReplaceAll("/", "_");
   HistName.ReplaceAll(".", "_");
   HistName.ReplaceAll("-", "m");

   TString FittingName;
   FittingName = (TString)"UpdatedAlphaSPDFLMScanOriginFitting_" + iter->first + "_" + FlavorNameMap[flavor] + "_x" + xstring + "_Q" + Qstring;
   FittingName.ReplaceAll("/", "_");
   FittingName.ReplaceAll(".", "_");
   FittingName.ReplaceAll("-", "m");

   TString PointName;
   PointName = (TString)"UpdatedAlphaSPDFLMScanOriginPoint_" + iter->first + "_" + FlavorNameMap[flavor] + "_x" + xstring + "_Q" + Qstring;
   PointName.ReplaceAll("/", "_");
   PointName.ReplaceAll(".", "_");
   PointName.ReplaceAll("-", "m");

   PDFLMScanOriginResult[make_tuple(iter->first, flavor, x, Q, isNewPDF)] = new TGraph(nScanPoint);
   PDFLMScanOriginResult[make_tuple(iter->first, flavor, x, Q, isNewPDF)]->SetName(HistName);
   PDFLMScanOriginResult[make_tuple(iter->first, flavor, x, Q, isNewPDF)]->SetTitle(HistName);
   PDFLMScanOriginPoint[make_tuple(iter->first, flavor, x, Q, isNewPDF)] = new TGraph(nScanPoint);
   PDFLMScanOriginPoint[make_tuple(iter->first, flavor, x, Q, isNewPDF)]->SetName(PointName);
   PDFLMScanOriginPoint[make_tuple(iter->first, flavor, x, Q, isNewPDF)]->SetTitle(PointName);

   for(int ibin = 1; ibin <= nScanPoint; ibin++){
     PDFLMScanOriginResult[make_tuple(iter->first, flavor, x, Q, isNewPDF)]->SetPointX(ibin, BestFitSet.at(ibin - 1) - BestFitSolution);
     PDFLMScanOriginResult[make_tuple(iter->first, flavor, x, Q, isNewPDF)]->SetPointY(ibin, Chi2Map[iter->first].at(ibin - 1));
     PDFLMScanOriginPoint[make_tuple(iter->first, flavor, x, Q, isNewPDF)]->SetPointX(ibin, BestFitSet.at(ibin - 1));
     PDFLMScanOriginPoint[make_tuple(iter->first, flavor, x, Q, isNewPDF)]->SetPointY(ibin, Chi2Map[iter->first].at(ibin - 1));
     myLog<<"ScanResult for Data "<<iter->first<<" : Lambda = "<<LambdaSet.at(ibin - 1)<<" BestFit = "<<BestFitSet.at(ibin - 1)<<" Chi2 = "<<Chi2Map[iter->first].at(ibin - 1)<<endl;
   }
   PDFLMScanOriginPoint[make_tuple(iter->first, flavor, x, Q, isNewPDF)]->RemovePoint(0);
   PDFLMScanOriginResult[make_tuple(iter->first, flavor, x, Q, isNewPDF)]->RemovePoint(0);
   PDFLMScanOriginResult[make_tuple(iter->first, flavor, x, Q, isNewPDF)]->SetMarkerSize(0);
   PDFLMScanOriginResult[make_tuple(iter->first, flavor, x, Q, isNewPDF)]->SetMarkerColor(0);
   PDFLMScanOriginResult[make_tuple(iter->first, flavor, x, Q, isNewPDF)]->SetLineWidth(0);
   PDFLMScanOriginResult[make_tuple(iter->first, flavor, x, Q, isNewPDF)]->SetLineColor(0);
   PDFLMScanOriginResult[make_tuple(iter->first, flavor, x, Q, isNewPDF)]->SetLineStyle(1);
   PDFLMScanOriginResult[make_tuple(iter->first, flavor, x, Q, isNewPDF)]->SetMarkerStyle(34);

   PDFLMScanOriginFitting[make_tuple(iter->first, flavor, x, Q, isNewPDF)] = new TF1(FittingName, "[0]*x*x+[1]*x+[2]", xmin, xmax);
   PDFLMScanOriginResult[make_tuple(iter->first, flavor, x, Q, isNewPDF)]->Fit(PDFLMScanOriginFitting[make_tuple(iter->first, flavor, x, Q, isNewPDF)], "W");

   double par1 = PDFLMScanOriginFitting[make_tuple(iter->first, flavor, x, Q, isNewPDF)]->GetParameter(0);
   double par2 = PDFLMScanOriginFitting[make_tuple(iter->first, flavor, x, Q, isNewPDF)]->GetParameter(1);
   double par3 = PDFLMScanOriginFitting[make_tuple(iter->first, flavor, x, Q, isNewPDF)]->GetParameter(2);
   double newpar1 = par1;
   double newpar2 = -1.0 * (2.0 * par1 * BestFitSolution - par2);
   double newpar3 = par1 * BestFitSolution * BestFitSolution - par2 * BestFitSolution + par3;
   PDFLMScanOriginFitting[make_tuple(iter->first, flavor, x, Q, isNewPDF)]->SetParameter(0, newpar1);
   PDFLMScanOriginFitting[make_tuple(iter->first, flavor, x, Q, isNewPDF)]->SetParameter(1, newpar2);
   PDFLMScanOriginFitting[make_tuple(iter->first, flavor, x, Q, isNewPDF)]->SetParameter(2, newpar3);

   ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

   HistName.ReplaceAll("PDFLMScanOriginResult", "PDFLMScanResult");
   FittingName.ReplaceAll("PDFLMScanOriginFitting", "PDFLMScanFitting");
   PointName.ReplaceAll("PDFLMScanOriginPoint", "PDFLMScanPoint");

   PDFLMScanResult[make_tuple(iter->first, flavor, x, Q, isNewPDF)] = new TGraph(nScanPoint);
   PDFLMScanResult[make_tuple(iter->first, flavor, x, Q, isNewPDF)]->SetName(HistName);
   PDFLMScanResult[make_tuple(iter->first, flavor, x, Q, isNewPDF)]->SetTitle(HistName);
   PDFLMScanPoint[make_tuple(iter->first, flavor, x, Q, isNewPDF)] = new TGraph(nScanPoint);
   PDFLMScanPoint[make_tuple(iter->first, flavor, x, Q, isNewPDF)]->SetName(PointName);
   PDFLMScanPoint[make_tuple(iter->first, flavor, x, Q, isNewPDF)]->SetTitle(PointName);

   for(int ibin = 1; ibin <= nScanPoint; ibin++){
     double DataOriginChi2 = PDFLMScanOriginFitting[make_tuple(iter->first, flavor, x, Q, isNewPDF)]->Eval(BestFitSolution);

     PDFLMScanResult[make_tuple(iter->first, flavor, x, Q, isNewPDF)]->SetPointX(ibin, BestFitSet.at(ibin - 1) - BestFitSolution);
     PDFLMScanResult[make_tuple(iter->first, flavor, x, Q, isNewPDF)]->SetPointY(ibin, Chi2Map[iter->first].at(ibin - 1) - DataOriginChi2);
     PDFLMScanPoint[make_tuple(iter->first, flavor, x, Q, isNewPDF)]->SetPointX(ibin, BestFitSet.at(ibin - 1));
     PDFLMScanPoint[make_tuple(iter->first, flavor, x, Q, isNewPDF)]->SetPointY(ibin, Chi2Map[iter->first].at(ibin - 1) - DataOriginChi2);
     myLog<<"ScanResult(After subtract) for Data "<<iter->first<<" : Lambda = "<<LambdaSet.at(ibin - 1)<<" BestFit = "<<BestFitSet.at(ibin - 1)<<" Chi2 = "<<Chi2Map[iter->first].at(ibin - 1) - DataOriginChi2<<endl;
   }
   PDFLMScanPoint[make_tuple(iter->first, flavor, x, Q, isNewPDF)]->RemovePoint(0);
   PDFLMScanResult[make_tuple(iter->first, flavor, x, Q, isNewPDF)]->RemovePoint(0);
   PDFLMScanResult[make_tuple(iter->first, flavor, x, Q, isNewPDF)]->SetMarkerSize(0);
   PDFLMScanResult[make_tuple(iter->first, flavor, x, Q, isNewPDF)]->SetMarkerColor(0);
   PDFLMScanResult[make_tuple(iter->first, flavor, x, Q, isNewPDF)]->SetLineWidth(0);
   PDFLMScanResult[make_tuple(iter->first, flavor, x, Q, isNewPDF)]->SetLineColor(0);
   PDFLMScanResult[make_tuple(iter->first, flavor, x, Q, isNewPDF)]->SetLineStyle(1);
   PDFLMScanResult[make_tuple(iter->first, flavor, x, Q, isNewPDF)]->SetMarkerStyle(34);

   PDFLMScanFitting[make_tuple(iter->first, flavor, x, Q, isNewPDF)] = new TF1(FittingName, "[0]*x*x+[1]*x+[2]", xmin, xmax);
   if(iter->first == "Total") PDFLMScanFitting[make_tuple(iter->first, flavor, x, Q, isNewPDF)]->SetNpx(50000);
   PDFLMScanResult[make_tuple(iter->first, flavor, x, Q, isNewPDF)]->Fit(PDFLMScanFitting[make_tuple(iter->first, flavor, x, Q, isNewPDF)], "W");

   par1 = PDFLMScanFitting[make_tuple(iter->first, flavor, x, Q, isNewPDF)]->GetParameter(0);
   par2 = PDFLMScanFitting[make_tuple(iter->first, flavor, x, Q, isNewPDF)]->GetParameter(1);
   par3 = PDFLMScanFitting[make_tuple(iter->first, flavor, x, Q, isNewPDF)]->GetParameter(2);
   newpar1 = par1;
   newpar2 = -1.0 * (2.0 * par1 * BestFitSolution - par2);
   newpar3 = par1 * BestFitSolution * BestFitSolution - par2 * BestFitSolution + par3;
   PDFLMScanFitting[make_tuple(iter->first, flavor, x, Q, isNewPDF)]->SetParameter(0, newpar1);
   PDFLMScanFitting[make_tuple(iter->first, flavor, x, Q, isNewPDF)]->SetParameter(1, newpar2);
   PDFLMScanFitting[make_tuple(iter->first, flavor, x, Q, isNewPDF)]->SetParameter(2, newpar3);
   ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

   double par[3];
   PDFLMScanFitting[make_tuple(iter->first, flavor, x, Q, isNewPDF)]->GetParameters(par);

   double Central = -par[1] / (2 * par[0]);
   double MinChi2 = (4 * par[0] * par[2] - par[1] * par[1]) / (4 * par[0]);
   double Solution1 = (-par[1] - sqrt(par[1] * par[1] - 4.0 * par[0] * (par[2] - LMScan->Tsq))) / (2 * par[0]);
   double Solution2 = (-par[1] + sqrt(par[1] * par[1] - 4.0 * par[0] * (par[2] - LMScan->Tsq))) / (2 * par[0]);
   double Solution3 = (-par[1] - sqrt(par[1] * par[1] - 4.0 * par[0] * (par[2] - 2.0 * LMScan->Tsq - 50.0))) / (2 * par[0]);
   double Solution4 = (-par[1] + sqrt(par[1] * par[1] - 4.0 * par[0] * (par[2] - 2.0 * LMScan->Tsq - 50.0))) / (2 * par[0]);

   myLog<<"T2 = "<<LMScan->Tsq<<endl;
   myLog<<"MinChi2 for Data "<<iter->first<<" = "<<MinChi2<<" Central = "<<Central<<" Solution1 = "<<Solution1<<" Solution2 = "<<Solution2<<" Delta = "<<(Solution2 - Solution1) / 2.0<<endl;

   if(iter->first == "Total"){
     PlotXMin = Solution1;
     PlotXMax = Solution2;

     if(!isSetPDFLMScanXRange[make_tuple(flavor, x, Q)]){
       PDFLMScanPlotXMin[make_tuple(flavor, x, Q, isNewPDF)]  = Solution3;
       PDFLMScanPlotXMax[make_tuple(flavor, x, Q, isNewPDF)]  = Solution4;
     }

     SortingSolution = (-par[1] + sqrt(par[1] * par[1] - 4.0 * par[0] * (par[2] - LMScan->Tsq))) / (2 * par[0]);//sorting
   }

   double SortingSolutionChi2 = PDFLMScanFitting[make_tuple(iter->first, flavor, x, Q, isNewPDF)]->Eval(SortingSolution);

   //if(iter->first != "Total") LMErrors[SortingSolutionChi2 * (-1.0)] = iter->first;//sorting
   if(iter->first != "Total") LMErrors[(Solution2 - Solution1) / 2.0] = iter->first;//sorting
   if(iter->first != "Total") ChiSquare1[iter->first] = PDFLMScanFitting[make_tuple(iter->first, flavor, x, Q, isNewPDF)]->Eval(PlotXMin);
   if(iter->first != "Total") ChiSquare2[iter->first] = PDFLMScanFitting[make_tuple(iter->first, flavor, x, Q, isNewPDF)]->Eval(PlotXMax);
   if(iter->first != "Total") ChiSquare1InverseMap[1.0 - PDFLMScanFitting[make_tuple(iter->first, flavor, x, Q, isNewPDF)]->Eval(PlotXMin)] = iter->first;
   if(iter->first != "Total") ChiSquare2InverseMap[1.0 - PDFLMScanFitting[make_tuple(iter->first, flavor, x, Q, isNewPDF)]->Eval(PlotXMax)] = iter->first;

   if(isLinkFile){
     PDFLMScanOriginResult[make_tuple(iter->first, flavor, x, Q, isNewPDF)]->Write();
     PDFLMScanOriginFitting[make_tuple(iter->first, flavor, x, Q, isNewPDF)]->Write();
     PDFLMScanOriginPoint[make_tuple(iter->first, flavor, x, Q, isNewPDF)]->Write();
     PDFLMScanResult[make_tuple(iter->first, flavor, x, Q, isNewPDF)]->Write();
     PDFLMScanFitting[make_tuple(iter->first, flavor, x, Q, isNewPDF)]->Write();
     PDFLMScanPoint[make_tuple(iter->first, flavor, x, Q, isNewPDF)]->Write();
   }
 }

 ////////////////
 //  Plotting  //
 ////////////////

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

 TString FigureName;
 FigureName = (TString)"PDFLMScanUpdatedAlphaS_" + FlavorNameMap[flavor] + "_x" + xstring + "_Q" + Qstring + ".pdf";
 TString XaxisName = TitleMap[flavor] + "(x = " + xstring_fixed + ", Q = " + Qstring + " GeV)";
 TString YaxisName = "#Delta #chi^{2}";

 Figure* f;

 f = new Figure(FigureName, XaxisName, YaxisName);
 f->SetMode("CUSTOM");
 f->InputTF1(1, PDFLMScanFitting[make_tuple((TString)"Total", flavor, x, Q, isNewPDF)], "Total");

 int iplot = 2;

 if(LMScanDrawList.size() == 0){
   int nNewData = 0;
   for(int idata = 0; idata < ExtendedEU->Ndata; idata++){
     if(iplot >= 15) break;
     if(fabs(ExtendedEU->weight[idata]) < 1e-20) continue;

     f->InputTF1(iplot, PDFLMScanFitting[make_tuple((TString)ExtendedEU->dataset[idata], flavor, x, Q, isNewPDF)], DataLegend[NickNameMap[(TString)ExtendedEU->dataset[idata]]]);

     iplot++;
     nNewData++;
   }

   for(auto iter = LMErrors.begin(); iter != LMErrors.end(); iter++){
     if(iplot >= 15) break;

     if(fabs(ExtendedEU->weight[DataIndex[iter->second]]) > 1e-20) continue;

     f->InputTF1(iplot, PDFLMScanFitting[make_tuple(iter->second, flavor, x, Q, isNewPDF)], DataLegend[NickNameMap[iter->second]]);
     iplot++;
   }
 }
 else{
   for(int i = 0; i < LMScanDrawList.size(); i++){
     f->InputTF1(i + 2, PDFLMScanFitting[make_tuple(LMScanDrawList.at(i), flavor, x, Q, isNewPDF)], DataLegend[NickNameMap[LMScanDrawList.at(i)]]);
   }
 }

 //f->InputTF1(iplot, PDFLMScanFitting[make_tuple("tabsCT18Am253/ZpT_as0118", flavor, x, Q, isNewPDF)], DataLegend[NickNameMap["tabsCT18Am253/ZpT_as0118"]]);

 double LegendYMin = 0.4; 
 if(LMScanDrawList.size() >= 13) LegendYMin = 0.4 - (LMScanDrawList.size() - 13) * 0.05;

 f->Compare("MultiSimple");
 f->SetCustomPlotFormat(1, 1, kBlack);
 f->SetCanvasSize(1400.0, 1200.0);
 f->SetLegendPosition(1.0, LegendYMin, 1.2, 0.9);
 f->SetCustomLegendSize(1, 0.025);
 f->SetCustomRightMargin(1, 0.2);
 f->SetCustomLeftMargin(1, 0.15);
 f->SetXRange(PDFLMScanPlotXMin[make_tuple(flavor, x, Q, isNewPDF)], PDFLMScanPlotXMax[make_tuple(flavor, x, Q, isNewPDF)]);
 f->SetCustomYRange(1, -20, 50);
 f->SetCustomXTitleOffset(1, 1.0);

 if(LMScanDrawList.size() == 0){
   for(int i = 2; i <= 16; i++){
     f->SetCustomLineStyle(1, i, PlotLineStyle[i]);
   }
 }
 else{
   for(int i = 1; i <= LMScanDrawList.size(); i++){
     f->SetCustomLineStyle(1, i + 1, PlotLineStyle[i + 1]);
   }
 }

 f->SetCustomLineWidth(1, 1, 6);

 f->Draw();

 iplot = 2;
 for(auto iter = LMErrors.begin(); iter != LMErrors.end(); iter++){
   //if(iplot >= 11) break;
   myLog<<fixed<<setprecision(3)<<iter->second<<": "<<iter->first * (-1.0)<<endl;
   iplot++;
 }

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

 LMErrors.clear();
 Chi2Map.clear();
}

void ePumpHelper::UpdateAlphaSLMScanObservable(TString DataName, int ipoint, TString TitleName)
{
 int isNewPDF = 2;

 ePump* LMScan = Clone(EU);
 AddLMScanConstrain(LMScan);

 for(int i = 0; i < EU->weight.size(); i++){
   LMScan->weight.at(i) = EU->weight.at(i);
 }

 LMScan->X0[LMScan->Ndata - 1][0] = NewObservableAlphaSOnly.at(DataIndex.at(DataName)).at(ipoint);
 for(int i = 0; i < 2 * LMScan->Ni + 1; i++){
   LMScan->Xmat[LMScan->Ndata - 1][0][i] = TheoryTemplate[DataName].at(ipoint).at(i) + (NewObservableAlphaSOnly.at(DataIndex.at(DataName)).at(ipoint) - TheoryTemplate[DataName].at(ipoint).at(0));
   LMScan->XmatNew[LMScan->Ndata - 1][0][i] = TheoryTemplate[DataName].at(ipoint).at(i) + (NewObservableAlphaSOnly.at(DataIndex.at(DataName)).at(ipoint) - TheoryTemplate[DataName].at(ipoint).at(0));
   LMScan->Xset[LMScan->Ndata - 1][i][0] = TheoryTemplate[DataName].at(ipoint).at(i) + (NewObservableAlphaSOnly.at(DataIndex.at(DataName)).at(ipoint) - TheoryTemplate[DataName].at(ipoint).at(0));
 }

 LMScan->Xmat[LMScan->Ndata - 1][0][0] = NewObservableAlphaSOnly.at(DataIndex.at(DataName)).at(ipoint);
 LMScan->XmatNew[LMScan->Ndata - 1][0][0] = NewObservableAlphaSOnly.at(DataIndex.at(DataName)).at(ipoint);
 LMScan->Xset[LMScan->Ndata - 1][0][0] = NewObservableAlphaSOnly.at(DataIndex.at(DataName)).at(ipoint);

 for(int i = 0; i < LMScan->Ni; i++){
   LMScan->dX[LMScan->Ndata - 1][0][i] = (TheoryTemplate[DataName].at(ipoint).at(2 * i + 1) - TheoryTemplate[DataName].at(ipoint).at(2 * i + 2)) / 2.0;
 }

 LMScan->XE[LMScan->Ndata - 1][0] = NewObservableAlphaSOnly.at(DataIndex.at(DataName)).at(ipoint);//Data Point (to be the same as theory), from 0

 LMScan->s[LMScan->Ndata - 1][0] = 1.0;//Data Err
 LMScan->dataset[LMScan->Ndata - 1] = "LMConstrain";
 LMScan->SetLMScanData(LMScan->Ndata - 1);

 LMScan->ConstructCm1(LMScan->Ndata - 1);

 LMScan->dChi2[LMScan->Ndata - 1] = LMScan->DeltaChiSquare(LMScan->X0[LMScan->Ndata - 1], LMScan->Ndata - 1);
 LMScan->dChi2Set[LMScan->Ndata - 1].resize(2 * LMScan->Ni + 1);
 LMScan->dChi2newSet[LMScan->Ndata - 1].resize(2 * LMScan->Ni + 1);

 for(int iEV = 0; iEV < 2 * LMScan->Ni + 1; iEV++){
   vector<double> TheoryTemplate(1);
   TheoryTemplate.at(0) = LMScan->Xmat[LMScan->Ndata - 1][0][iEV];
   LMScan->dChi2Set[LMScan->Ndata - 1][iEV] = LMScan->DeltaChiSquare(TheoryTemplate, LMScan->Ndata - 1);
   TheoryTemplate.clear();
 }

 LMScan->SetXdyn(LMScan->Ndata - 1);

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

 cout<<"Starting Lagrange Multiplier Scan"<<endl;

 if(isLinkFile) hf->cd();

 //1sigma uncertainty will be at +- 2 * Tsq / Delta_X

 int nScanPoint = 10;

 vector<double> LambdaSet(nScanPoint);
 vector<double> Chi2Set(nScanPoint);
 vector<double> BestFitSet(nScanPoint);
 double step = 8.0 * LMScan->Tsq / OldPDFError[DataName].at(ipoint) / ((double)nScanPoint / 2.0);
 for(int i = 0; i < LambdaSet.size(); i++){
   cout<<"Scan "<<i + 1<<endl;
   LambdaSet.at(i) = -8.0 * LMScan->Tsq / OldPDFError[DataName].at(ipoint) + step * i;

   LMScan->weight[LMScan->Ndata - 1] = LambdaSet.at(i);
   LMScan->ConstructUpdateMatrix();
   LMScan->UpdateObservables();

   Chi2Set.at(i) = LMScan->Tsq * LMScan->NewLength * LMScan->NewLength;
   BestFitSet.at(i) = LMScan->NewTheory.at(LMScan->Ndata - 1).at(0);
 }

 double xmin = BestFitSet.at(0) - (BestFitSet.at(1) - BestFitSet.at(0));
 double xmax = BestFitSet.at(nScanPoint - 1) + (BestFitSet.at(nScanPoint - 1) - BestFitSet.at(nScanPoint - 2));

 TString HistName = (TString)"UpdatedAlphaSLMScanResult_" + DataName + "_" + (int)(ipoint + 1);
 HistName.ReplaceAll("/", "_");
 HistName.ReplaceAll(".", "_");
 TString FittingName = (TString)"UpdatedAlphaSLMScanFitting_" + DataName + "_" + (int)(ipoint + 1);
 FittingName.ReplaceAll("/", "_");
 FittingName.ReplaceAll(".", "_");
 TString PointName = (TString)"UpdatedAlphaSLMScanPoint_" + DataName + "_" + (int)(ipoint + 1);
 PointName.ReplaceAll("/", "_");
 PointName.ReplaceAll(".", "_");

 LMScanResult[make_tuple(DataName, ipoint, isNewPDF)] = new TGraph(nScanPoint);
 LMScanResult[make_tuple(DataName, ipoint, isNewPDF)]->SetName(HistName);
 LMScanResult[make_tuple(DataName, ipoint, isNewPDF)]->SetTitle(HistName);

 LMScanPoint[make_tuple(DataName, ipoint, isNewPDF)] = new TGraph(nScanPoint);
 LMScanPoint[make_tuple(DataName, ipoint, isNewPDF)]->SetName(PointName);
 LMScanPoint[make_tuple(DataName, ipoint, isNewPDF)]->SetTitle(PointName);

 for(int ibin = 1; ibin <= nScanPoint; ibin++){
   LMScanResult[make_tuple(DataName, ipoint, isNewPDF)]->SetPointX(ibin, BestFitSet.at(ibin - 1));
   LMScanResult[make_tuple(DataName, ipoint, isNewPDF)]->SetPointY(ibin, Chi2Set.at(ibin - 1));
   LMScanPoint[make_tuple(DataName, ipoint, isNewPDF)]->SetPointX(ibin, BestFitSet.at(ibin - 1));
   LMScanPoint[make_tuple(DataName, ipoint, isNewPDF)]->SetPointY(ibin, Chi2Set.at(ibin - 1));
   cout<<"ScanResult: Lambda = "<<LambdaSet.at(ibin - 1)<<" BestFit = "<<BestFitSet.at(ibin - 1)<<" Chi2 = "<<Chi2Set.at(ibin - 1)<<endl;
 }
 LMScanPoint[make_tuple(DataName, ipoint, isNewPDF)]->RemovePoint(0);
 LMScanResult[make_tuple(DataName, ipoint, isNewPDF)]->RemovePoint(0);
 LMScanResult[make_tuple(DataName, ipoint, isNewPDF)]->SetMarkerSize(2);
 LMScanResult[make_tuple(DataName, ipoint, isNewPDF)]->SetLineWidth(0);
 LMScanResult[make_tuple(DataName, ipoint, isNewPDF)]->SetLineColor(0);
 LMScanResult[make_tuple(DataName, ipoint, isNewPDF)]->SetLineStyle(1);
 LMScanResult[make_tuple(DataName, ipoint, isNewPDF)]->SetMarkerStyle(34);

 LMScanFitting[make_tuple(DataName, ipoint, isNewPDF)] = new TF1(FittingName, "[0]*x*x+[1]*x+[2]", xmin, xmax);
 LMScanResult[make_tuple(DataName, ipoint, isNewPDF)]->Fit(LMScanFitting[make_tuple(DataName, ipoint, isNewPDF)], "W");

 double par[3];
 LMScanFitting[make_tuple(DataName, ipoint, isNewPDF)]->GetParameters(par);

 double Central = -par[1] / (2 * par[0]);
 double MinChi2 = (4 * par[0] * par[2] - par[1] * par[1]) / (4 * par[0]);
 double Solution1 = (-par[1] - sqrt(par[1] * par[1] - 4.0 * par[0] * (par[2] - LMScan->Tsq))) / (2 * par[0]);
 double Solution2 = (-par[1] + sqrt(par[1] * par[1] - 4.0 * par[0] * (par[2] - LMScan->Tsq))) / (2 * par[0]);

 cout<<"T2 = "<<LMScan->Tsq<<endl;
 cout<<"MinChi2 = "<<MinChi2<<" Central = "<<Central<<" Solution1 = "<<Solution1<<" Solution2 = "<<Solution2<<" Delta = "<<(Solution2 - Solution1) / 2.0<<endl;

 if(isLinkFile){
   LMScanResult[make_tuple(DataName, ipoint, isNewPDF)]->Write();
   LMScanFitting[make_tuple(DataName, ipoint, isNewPDF)]->Write();
   LMScanPoint[make_tuple(DataName, ipoint, isNewPDF)]->Write();
 }

 ////////////////
 //  Plotting  //
 ////////////////

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

 TString FigureName;
 FigureName = (TString)"LMScanUpdatedAlphaS_" + DataName + "_Point" + (int)(ipoint + 1) + ".pdf";
 FigureName.ReplaceAll("/", "_");

 Graph* g;

 g = new Graph(FigureName, TitleName, "#Delta #chi^{2}");
 g->SetMode("CUSTOM");
 g->InputGraph(1, (TGraphErrors *)LMScanResult[make_tuple(DataName, ipoint, isNewPDF)], "");
 g->InputGraph(2, (TGraphErrors *)LMScanPoint[make_tuple(DataName, ipoint, isNewPDF)], "");
 g->Compare("MultiSimple");
 g->SetCustomPlot(1, 1, "AC");
 g->SetCustomPlot(1, 2, "Point");
 g->SetCustomPlotFormat(1, 2, kBlack);
 g->Draw();
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

}

void ePumpHelper::AlphaSObservableCorrelation(TString DataName, int ipoint, TString TitleName)
{
 int Index = DataIndex.at(DataName);
 double OldPDFUnc = OldPDFError.at(DataName).at(ipoint) / 1.645;
 double NewPDFUnc = NewPDFError.at(DataName).at(ipoint) / 1.645;
 double OldAlphaSUnc = (ExtendedEU->Xmat[Index][ipoint][2 * EU->Ni + 2] - ExtendedEU->Xmat[Index][ipoint][2 * EU->Ni + 1]) / 2.0 / 1.645;
 double NewAlphaSUnc = (NewObservableSet[Index][ipoint][2 * EU->Ni + 2] - NewObservableSet[Index][ipoint][2 * EU->Ni + 1]) / 2.0 / 1.645;
 double OldObservable = OldTheory.at(DataName).at(ipoint);
 double NewObservable = NewTheory.at(DataName).at(ipoint);
 double NewAlphaSObservable = NewObservableSet[Index][ipoint][0];
 double OldCorrelation = OldAlphaSUnc / sqrt(pow(OldPDFUnc, 2) + pow(OldAlphaSUnc, 2));
 double NewCorrelation = OldAlphaSUnc / sqrt(pow(NewPDFUnc, 2) + pow(OldAlphaSUnc, 2));
 double NewAlphaSCorrelation = NewAlphaSUnc / sqrt(pow(NewPDFUnc, 2) + pow(NewAlphaSUnc, 2));

 TString BeforeUpdatePointName = (TString)"BeforeUpdatePoint_" + DataName + "_" + ipoint;
 BeforeUpdatePointName.ReplaceAll("/", "_");

 TString AfterUpdatePointName = BeforeUpdatePointName;
 AfterUpdatePointName.ReplaceAll("BeforeUpdatePoint", "AfterUpdatePoint");

 TString AfterUpdateAlphaSPointName = BeforeUpdatePointName;
 AfterUpdateAlphaSPointName.ReplaceAll("BeforeUpdatePoint", "AfterUpdateAlphaSPoint");

 TString BeforeUpdateEllipseName = BeforeUpdatePointName;
 BeforeUpdateEllipseName.ReplaceAll("BeforeUpdatePoint", "BeforeUpdateEllipse");

 TString AfterUpdateEllipseName = BeforeUpdatePointName;
 AfterUpdateEllipseName.ReplaceAll("BeforeUpdatePoint", "AfterUpdateEllipse");

 TString AfterUpdateAlphaSEllipseName = BeforeUpdatePointName;
 AfterUpdateAlphaSEllipseName.ReplaceAll("BeforeUpdatePoint", "AfterUpdateAlphaSEllipse");

 TGraph* BeforeUpdatePoint = new TGraph(1);
 BeforeUpdatePoint->SetName(BeforeUpdatePointName);
 BeforeUpdatePoint->SetTitle(BeforeUpdatePointName);
 BeforeUpdatePoint->SetPoint(1, Old_AlphaS_GA, OldObservable);

 TGraph* AfterUpdatePoint = new TGraph(1);
 AfterUpdatePoint->SetName(AfterUpdatePointName);
 AfterUpdatePoint->SetTitle(AfterUpdatePointName);
 AfterUpdatePoint->SetPoint(1, Old_AlphaS_GA, NewObservable);

 TGraph* AfterUpdateAlphaSPoint = new TGraph(1);
 AfterUpdateAlphaSPoint->SetName(AfterUpdateAlphaSPointName);
 AfterUpdateAlphaSPoint->SetTitle(AfterUpdateAlphaSPointName);
 AfterUpdateAlphaSPoint->SetPoint(1, New_AlphaS_GA, NewAlphaSObservable);

 TGraph* BeforeUpdateEllipse = GenerateEllipse(Old_AlphaS_GA, OldObservable, fabs(Old_Delta_AlphaS) / 1.645, sqrt(pow(OldPDFUnc, 2) + pow(OldAlphaSUnc, 2)), OldCorrelation);
 BeforeUpdateEllipse->SetName(BeforeUpdateEllipseName);
 BeforeUpdateEllipse->SetTitle(BeforeUpdateEllipseName);

 TGraph* AfterUpdateEllipse = GenerateEllipse(Old_AlphaS_GA, NewObservable, fabs(Old_Delta_AlphaS) / 1.645, sqrt(pow(NewPDFUnc, 2) + pow(OldAlphaSUnc, 2)), NewCorrelation);
 AfterUpdateEllipse->SetName(AfterUpdateEllipseName);
 AfterUpdateEllipse->SetTitle(AfterUpdateEllipseName);

 TGraph* AfterUpdateAlphaSEllipse = GenerateEllipse(New_AlphaS_GA, NewAlphaSObservable, fabs(New_Delta_AlphaS) / 1.645, sqrt(pow(NewPDFUnc, 2) + pow(NewAlphaSUnc, 2)), NewAlphaSCorrelation);
 AfterUpdateAlphaSEllipse->SetName(AfterUpdateAlphaSEllipseName);
 AfterUpdateAlphaSEllipse->SetTitle(AfterUpdateAlphaSEllipseName);

 TString FigureName = BeforeUpdatePointName;
 FigureName.ReplaceAll("BeforeUpdatePoint", "CorrelationEllipse");
 FigureName = FigureName + ".pdf";

 Graph* g = new Graph(FigureName, "#alpha_{s}(M_{Z})", TitleName);
 g->SetMode("CUSTOM");
 g->InputGraph(1, (TGraphErrors *)BeforeUpdatePoint,   "Before update");
 g->InputGraph(2, (TGraphErrors *)BeforeUpdateEllipse, "");
 g->InputGraph(3, (TGraphErrors *)AfterUpdatePoint,   "After update (PDF only)");
 g->InputGraph(4, (TGraphErrors *)AfterUpdateEllipse, "");
 g->InputGraph(5, (TGraphErrors *)AfterUpdateAlphaSPoint,   "After update (PDF + #alpha_{S})");
 g->InputGraph(6, (TGraphErrors *)AfterUpdateAlphaSEllipse, "");
 g->Compare("MultiSimple");
 g->SetCustomPlot(1, 1, "Point");
 g->SetCustomPlot(1, 2, "AC");
 g->SetCustomPlot(1, 3, "Point");
 g->SetCustomPlot(1, 4, "AC");
 g->SetCustomPlot(1, 5, "Point");
 g->SetCustomPlot(1, 6, "AC");
 g->SetCustomPlotFormat(1, 1, kBlue);
 g->SetCustomPlotFormat(1, 2, kBlue);
 g->SetCustomPlotFormat(1, 3, kRed);
 g->SetCustomPlotFormat(1, 4, kRed);
 g->SetCustomPlotFormat(1, 5, kGreen);
 g->SetCustomPlotFormat(1, 6, kGreen);
 g->SetCustomLineStyle(1, 4, 2);
 g->SetXRange(Old_AlphaS_GA - 1.2 * fabs(Old_Delta_AlphaS) / 1.645, Old_AlphaS_GA + 1.2 * fabs(Old_Delta_AlphaS) / 1.645);
 g->SetCustomYRange(1, OldObservable - 1.2 * sqrt(pow(OldPDFUnc, 2) + pow(OldAlphaSUnc, 2)), OldObservable + 1.4 * sqrt(pow(OldPDFUnc, 2) + pow(OldAlphaSUnc, 2)));
 g->SetLegendPosition(0.05, 0.7, 0.5, 0.95);
 g->AddCustomText(1, Old_AlphaS_GA, OldObservable + 1.2 * sqrt(pow(OldPDFUnc, 2) + pow(OldAlphaSUnc, 2)), "68\% C.L., LHC 13 TeV");
 g->Draw();

 if(isLinkFile) hf->cd();

 BeforeUpdatePoint->Write();
 AfterUpdatePoint->Write();
 AfterUpdateAlphaSPoint->Write();
 BeforeUpdateEllipse->Write();
 AfterUpdateEllipse->Write();
 AfterUpdateAlphaSEllipse->Write();
}

