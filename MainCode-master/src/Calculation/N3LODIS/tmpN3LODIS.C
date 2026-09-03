#include "Calculation/CalcDIS.h"

void CalcDIS::InitializeHoppetSF()
{
#ifdef USE_HOPPET

 int ihadron = 1;

 double mc = Amhat.at(4); 
 double mb = Amhat.at(5);
 double mt = Amhat.at(6);
  
 double Qmax   = 1e5;
 double Qmin   = 1.29;
 int order      = -6; 
 double dy      = 0.2;
 double dlnlnQ  = dy/4.0;
 int    nloop   = EvolveOrder;
 double xmuR   = 1.0;
 double xmuF   = 1.0;
 double minQval = min(xmuF*Qmin, Qmin);
 double maxQval = max(xmuF*Qmax, Qmax);
 double xmin = 1e-9;
 double ymax = log(1.0 / xmin);
 int factscheme = 1;

 hoppetStartExtended(ymax, dy, minQval, maxQval, dlnlnQ, nloop, order, factscheme);
 hoppetSetPoleMassVFN(mc, mb, mt);

 int nflav = -5;
 int order_max = 4;
 int sc_choice = hoppet::scale_choice_Q;
 double zmass = 91.1876;
 double wmass = 80.377;
 bool param_coefs = true;

 hoppetStartStrFctExtended(order_max, nflav, sc_choice, zmass, param_coefs, wmass, zmass);
    
 double Q0 = 1.295;
 double AsQ0 = 0.118;
 double Q0_as = 91.19;
 double muR_Q    = 1.0;

 auto empty_pdf = [](const double &x, const double &Q, double *pdf){
   for(int i = -6; i <= 6; i++){
     pdf[i + 6] = 0.0;
   }
 };
 hoppetEvolve(AsQ0, Q0_as, nloop, muR_Q, empty_pdf, Q0);

 hoppetInitStrFct(order_max, param_coefs, xmuR, xmuF);

 Hoppet_C2LO = hoppet_get_C2LO_clone();
 Hoppet_CLLO = hoppet_get_CLLO_clone();
 Hoppet_C3LO = hoppet_get_C3LO_clone();

 //cout<<"Clone C2NLO:"<<endl;
 Hoppet_C2NLO = split_mat_clone(hoppet_get_C2NLO_clone());
 //cout<<"Clone CLNLO:"<<endl;
 Hoppet_CLNLO = split_mat_clone(hoppet_get_CLNLO_clone());
 //cout<<"Clone C3NLO:"<<endl;
 Hoppet_C3NLO = split_mat_clone(hoppet_get_C3NLO_clone());

 //cout<<"Clone C2NNLO:"<<endl;
 Hoppet_C2NNLO = split_mat_clone(hoppet_get_C2NNLO_clone());
 //cout<<"Clone CLNNLO:"<<endl;
 Hoppet_CLNNLO = split_mat_clone(hoppet_get_CLNNLO_clone());
 //cout<<"Clone C3NNLO:"<<endl;
 Hoppet_C3NNLO = split_mat_clone(hoppet_get_C3NNLO_clone());

 //cout<<"Clone C2N3LO:"<<endl;
 Hoppet_C2N3LO = split_mat_clone(hoppet_get_C2N3LO_clone());
 //cout<<"Clone CLN3LO:"<<endl;
 Hoppet_CLN3LO = split_mat_clone(hoppet_get_CLN3LO_clone());
 //cout<<"Clone C3N3LO:"<<endl;
 Hoppet_C3N3LO = split_mat_clone(hoppet_get_C3N3LO_clone());

 //cout<<"Clone C2N3LO_fl11:"<<endl;
 Hoppet_C2N3LO = split_mat_clone(hoppet_get_C2N3LO_fl11_clone());
 //cout<<"Clone CLN3LO_fl11:"<<endl;
 Hoppet_CLN3LO = split_mat_clone(hoppet_get_CLN3LO_fl11_clone());

 //cout<<"Clone P_LO:"<<endl;
 Hoppet_P_LO = split_mat_clone(hoppet_get_P_LO_clone());
 //cout<<"Clone P_NLO:"<<endl;
 Hoppet_P_NLO = split_mat_clone(hoppet_get_P_NLO_clone());

 if(nloop > 2){
   //cout<<"Clone P_NNLO:"<<endl;
   Hoppet_P_NNLO = split_mat_clone(hoppet_get_P_NNLO_clone());
 }

 if(nloop > 3){
   //cout<<"Clone P_N3LO:"<<endl;
   Hoppet_P_N3LO = split_mat_clone(hoppet_get_P_N3LO_clone());
 }

 Hoppet_grid = hoppet::grid_def(hoppet_cxx__grid_def__copy(Hoppet_C2NLO.grid().ptr()));

 Hoppet_xpdf = hoppet::grid_quant_2d(Hoppet_grid, 14);

 for(int iflv = 0; iflv < Hoppet_xpdf.extras().size_dim0; iflv++){
   int parton = iflv - 6;
   if(iflv - 6 == 1) parton = 2;
   else if(iflv - 6 == 2) parton = 1;
   else if(iflv - 6 == -1) parton = -2;
   else if(iflv - 6 == -2) parton = -1;
   else parton = iflv - 6;

   for(int iy = 0; iy < Hoppet_xpdf.extras().size_dim1; iy++){
     double x = Hoppet_xpdf.grid().x_values().at(iy);
     Hoppet_xpdf(iflv, iy) = (abs(parton) <= NfTotal) ? x * GetPDF(ihadron, parton, x, 100.0) : 0.0;
   }
 }

 Hoppet_xgluon = hoppet::grid_quant(Hoppet_xpdf[0 + 6]);



 hoppet::grid_quant_2d f2NLO = Hoppet_C2NLO.ptr() * Hoppet_xpdf;
 hoppet::grid_quant_2d f2NNLO = Hoppet_C2NNLO.ptr() * Hoppet_xpdf;

 cout<<"u - ubar: "<<0.1 * (GetPDFP(1, 0.1, 100.0) - GetPDFP(-1, 0.1, 100.0))<<endl;
 cout<<"d - dbar: "<<0.1 * (GetPDFP(2, 0.1, 100.0) - GetPDFP(-2, 0.1, 100.0))<<endl;

 double f2NLO_EM = ((f2NLO[-6 + 6].at_x(0.1) + f2NLO[-4 + 6].at_x(0.1) + f2NLO[-2 + 6].at_x(0.1) + f2NLO[6 + 6].at_x(0.1) + f2NLO[4 + 6].at_x(0.1) + f2NLO[2 + 6].at_x(0.1)) * 4.0 / 9.0
                  + (f2NLO[-5 + 6].at_x(0.1) + f2NLO[-3 + 6].at_x(0.1) + f2NLO[-1 + 6].at_x(0.1) + f2NLO[5 + 6].at_x(0.1) + f2NLO[3 + 6].at_x(0.1) + f2NLO[1 + 6].at_x(0.1)) * 1.0 / 9.0)
                  * GetAlphaS(100.0) / 2.0 / TMath::Pi();

 double f2NNLO_EM = ((f2NNLO[-6 + 6].at_x(0.1) + f2NNLO[-4 + 6].at_x(0.1) + f2NNLO[-2 + 6].at_x(0.1) + f2NNLO[6 + 6].at_x(0.1) + f2NNLO[4 + 6].at_x(0.1) + f2NNLO[2 + 6].at_x(0.1)) * 4.0 / 9.0
                   + (f2NNLO[-5 + 6].at_x(0.1) + f2NNLO[-3 + 6].at_x(0.1) + f2NNLO[-1 + 6].at_x(0.1) + f2NNLO[5 + 6].at_x(0.1) + f2NNLO[3 + 6].at_x(0.1) + f2NNLO[1 + 6].at_x(0.1)) * 1.0 / 9.0)
                   * pow(GetAlphaS(100.0) / 2.0 / TMath::Pi(), 2);

 cout<<"f2 NLO EM = "<<f2NLO_EM<<endl;
 cout<<"f2 NNLO EM = "<<f2NNLO_EM<<endl;



 auto sf_C2Hg0 = [&](double y, int piece){
    double x = exp(-y);
    double res = 0.0;


    double QQ = 100.0;//tmp
    double Mu = 100.0;//tmp
    double MQ = 1.3;//tmp

    double C2Hg0 = HQcoef0(2, x, QQ, Mu, MQ);
    //print*,x, QQ, Mu, MQ

    if(piece == hoppet::cc_REAL){
       res = C2Hg0; //learn from HOPPET C2
    }
    else if(piece == hoppet::cc_REALVIRT){
       res = C2Hg0;
    }
    else if(piece == hoppet::cc_VIRT){
       res = 0.0;
    }
    else if(piece == hoppet::cc_DELTA){
       res = 0.0;
    }
    else{
       res = 0.0;
    }
    res = res * 0.5 * 0.5; // (as/4pi)->(as/2pi), q+qb->q
    if(piece != hoppet::cc_DELTA) res = res * x;

    return res;
 };

 hoppet::grid_conv xC2Hg0 = hoppet::grid_conv(Hoppet_grid, sf_C2Hg0);

 hoppet::grid_quant xF2Hg0 = xC2Hg0 * Hoppet_xgluon;

 cout<<"xF2Hg0: "<<xF2Hg0.at_x(0.1)<<endl;

#endif
}

