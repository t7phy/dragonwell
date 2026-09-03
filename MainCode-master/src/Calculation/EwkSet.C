#include "Calculation/EwkSet.h"

EwkSet::EwkSet()
{
 // Electroweak parameters

 VKM(1, 1) = 0.97383; VKM(2, 1) = 0.22720; VKM(3, 1) = 0.00396;
 VKM(1, 2) = 0.22710; VKM(2, 2) = 0.97296; VKM(3, 2) = 0.04221;
 VKM(1, 3) = 0.00814; VKM(2, 3) = 0.04161; VKM(3, 3) = 0.99910;

 NFL = NSP * NGN;

/*
 AlfEW[1] = ALFE;
 AlfEW[2] = ALFE / SWG2 / 8.0;
 AlfEW[3] = AlfEW[2];
 AlfEW[4] = ALFE / SWG2 / (1.0 - SWG2) / 4.0;
*/

 SWG2 = SW2_EFF_MZ;

 double R2 = sqrt(2.0);
 double XMW2 = WMS * WMS;
 double XMZ2 = ZMS * ZMS;

//_____Weak couplings: g_w
 double GWEAK2 = 4.0*R2*XMW2*GMU;
 double GWEAK = sqrt(GWEAK2);

 ALFE = ALFA_EM_MZ;

// WCOUPL IS (g**2)/8
 WCOUPL = GWEAK2 / 8.0;

// WE IGNORE THE DIFFERENCE BETWEEN b-quark AND OTHER FERMIONS
// ZCOUPL IS (g/Cos_w)**2/4

//_____Sin^2 and Cos^2 of the weak angle - in the on shell scheme
 double CWS = XMW2/XMZ2;
 double SWS = 1.0-CWS;
 double ZCOUPL_MZ = Pi*ALFA_EM_MZ/SWS/CWS;
 ZCOUPL = ZCOUPL_MZ;

//------------------------------------
// To a good approximation:

 AlfEW(1) = ALFE;
 AlfEW(2) = WCOUPL/4.0/Pi;
 AlfEW(3) = AlfEW(2);
 AlfEW(4) = ZCOUPL/4.0/Pi;

 LeptonCharge(1) = 0.0;
 LeptonCharge(2) = -1.0;
// QuarkCharge(1) = 2.0 / 3.0;
// QuarkCharge(2) = -1.0 / 3.0;
 QuarkCharge(1) = 0.666666667;
 QuarkCharge(2) = -0.333333333;
 T3(1) = 0.5;
 T3(2) = -0.5;

 for(int is1 = 1; is1 <= NSP; is1++){
   for(int is2 = 1; is2 <= NSP; is2++){
     if(is1 == is2){
       GLV(is1, 1, is2) = LeptonCharge(is1);
       GLA(is1, 1, is2) = 0.0;
       GLV(is1, 2, is2) = 0.0;
       GLA(is1, 2, is2) = 0.0;
       GLV(is1, 3, is2) = 0.0;
       GLA(is1, 3, is2) = 0.0;
       GLV(is1, 4, is2) = T3(is1) - 2.0 * LeptonCharge(is1) * SWG2;
       GLA(is1, 4, is2) = T3(is1) * (-1.0);
       GQV(is1, 1, is2) = QuarkCharge(is1);
       GQA(is1, 1, is2) = 0.0;
       GQV(is1, 2, is2) = 0.0;
       GQA(is1, 2, is2) = 0.0;
       GQV(is1, 3, is2) = 0.0;
       GQA(is1, 3, is2) = 0.0;
       GQV(is1, 4, is2) = T3(is1) - 2.0 * QuarkCharge(is1) * SWG2;
       GQA(is1, 4, is2) = T3(is1) * (-1.0);
     }
     else if(is1 > is2){
       GLV(is1, 1, is2) = 0.0;
       GLA(is1, 1, is2) = 0.0;
       GLV(is1, 2, is2) = 1.0;
       GLA(is1, 2, is2) = -1.0;
       GLV(is1, 3, is2) = 0.0;
       GLA(is1, 3, is2) = 0.0;
       GLV(is1, 4, is2) = 0.0;
       GLA(is1, 4, is2) = 0.0;
       GQV(is1, 1, is2) = 0.0;
       GQA(is1, 1, is2) = 0.0;
       GQV(is1, 2, is2) = 1.0;
       GQA(is1, 2, is2) = -1.0;
       GQV(is1, 3, is2) = 0.0;
       GQA(is1, 3, is2) = 0.0;
       GQV(is1, 4, is2) = 0.0;
       GQA(is1, 4, is2) = 0.0;
     }
     else if(is1 < is2){
       GLV(is1, 1, is2) = 0.0;
       GLA(is1, 1, is2) = 0.0;
       GLV(is1, 2, is2) = 0.0;
       GLA(is1, 2, is2) = 0.0;
       GLV(is1, 3, is2) = 1.0;
       GLA(is1, 3, is2) = -1.0;
       GLV(is1, 4, is2) = 0.0;
       GLA(is1, 4, is2) = 0.0;
       GQV(is1, 1, is2) = 0.0;
       GQA(is1, 1, is2) = 0.0;
       GQV(is1, 2, is2) = 0.0;
       GQA(is1, 2, is2) = 0.0;
       GQV(is1, 3, is2) = 1.0;
       GQA(is1, 3, is2) = -1.0;
       GQV(is1, 4, is2) = 0.0;
       GQA(is1, 4, is2) = 0.0;
     }

     for(int ibn = 1; ibn <= NBN; ibn++){
       GLL(is1,ibn,is2) = (GLV(is1,ibn,is2) - GLA(is1,ibn,is2)) / 2.0;
       GLR(is1,ibn,is2) = (GLV(is1,ibn,is2) + GLA(is1,ibn,is2)) / 2.0;
       GQL(is1,ibn,is2) = (GQV(is1,ibn,is2) - GQA(is1,ibn,is2)) / 2.0;
       GQR(is1,ibn,is2) = (GQV(is1,ibn,is2) + GQA(is1,ibn,is2)) / 2.0;
     }
   }
 }

 for(int ig1 = 1; ig1 <= NGN; ig1++){
   for(int ig2 = 1; ig2 <= NGN; ig2++){
     for(int is1 = 1; is1 <= NSP; is1++){
       for(int is2 = 1; is2 <= NSP; is2++){
         GGQA(is1, ig1, is2, ig2) = GQA(is1, 2, is2) * VKM(ig1, ig2);
         GGQV(is1, ig1, is2, ig2) = GQV(is1, 2, is2) * VKM(ig1, ig2);
         GGQR(is1, ig1, is2, ig2) = GQR(is1, 2, is2) * VKM(ig1, ig2);
         GGQL(is1, ig1, is2, ig2) = GQL(is1, 2, is2) * VKM(ig1, ig2);
       }
     }
   }
 }

 IP(1, 1) = 1;
 IP(2, 1) = 2;
 IP(1, 2) = 4;
 IP(2, 2) = 3;
 IP(1, 3) = 6;
 IP(2, 3) = 5;

 for(int ig1 = 1; ig1 <= NGN; ig1++){
   for(int ig2 = 1; ig2 <= NGN; ig2++){
     for(int is1 = 1; is1 <= NSP; is1++){
       for(int is2 = 1; is2 <= NSP; is2++){
         int IP1 = IP(is1, ig1);
         int IP2 = IP(is2, ig2);
         for(int ibn = 1; ibn <= NBN; ibn++){
           if(ibn == 1 || ibn == 4){
             if(ig1 != ig2){
               HQA(IP1, ibn, IP2) = 0.0;
               HQV(IP1, ibn, IP2) = 0.0;
               HQL(IP1, ibn, IP2) = 0.0;
               HQR(IP1, ibn, IP2) = 0.0;
             }
             else{
               HQA(IP1, ibn, IP2) = GQA(is1, ibn, is2);
               HQV(IP1, ibn, IP2) = GQV(is1, ibn, is2);
               HQL(IP1, ibn, IP2) = GQL(is1, ibn, is2);
               HQR(IP1, ibn, IP2) = GQR(is1, ibn, is2);
             }
           }
         }
         HQA(IP1, 2, IP2) = GGQA(is1, ig1, is2, ig2);
         HQV(IP1, 2, IP2) = GGQV(is1, ig1, is2, ig2);
         HQL(IP1, 2, IP2) = GGQL(is1, ig1, is2, ig2);
         HQR(IP1, 2, IP2) = GGQR(is1, ig1, is2, ig2);

         HQA(IP1, 3, IP2) = GGQA(is2, ig2, is1, ig1);
         HQV(IP1, 3, IP2) = GGQV(is2, ig2, is1, ig1);
         HQL(IP1, 3, IP2) = GGQL(is2, ig2, is1, ig1);
         HQR(IP1, 3, IP2) = GGQR(is2, ig2, is1, ig1);
       }
     }
   }
 }

}

double EwkSet::AlfEwk(int iboson)
{
 return AlfEW(iboson);
}

double EwkSet::vBnMas(int iboson)
{
 double Value = 0.0;

 if(iboson == 1){
   Value = 0.0;
 }
 else if(iboson == 2 || iboson == 3){
   Value = WMS;
 }
 else if(iboson == 4){
   Value = ZMS;
 }
 else{
   cout<<" Vector Boson Index out of range"<<endl;
   cout<<" in VBNMAS; IBOSON = "<<iboson<<endl;
 }

 return Value;
}

double EwkSet::gEWlH(int it1, int ibs, int ibh, int it2)
{
//           (G) Electro-Weak coupling for Leptons in the cHirality base.
//            -  -       -                 -               -

//               To be used in the calculation of general E-WK matrix elements.

//           IT1, IT2 = 1,2 :  Weak Isospin (T3) of the two leptons
//           IBS =  1 -4    :  Boson label (see SETEWK)
//           IBH =             Boson polarization (helicity) label
//                  1       :  right-handed
//                 -1       :  left -handed
//                  other   :  illegal

//                 For now, this still just apply to fiels rather then particles;
//                       hence there is no distinction between particle & anti-p.

//                 To distinquish between them, either write another module, or
//                       use the convention, IT1 = -1, -2 for the anti-part;
//                            and test the signs upon Entry to determine the 
//                            channel (i.e. scattering, decay, or production).

//         When make the field ---> particle transition, cHirality ---> Helicity

  double Value = 0.0;
  if((it1 < 1 || it1 > NSP) || (it2 < 1 || it2 > NSP)){
    cout<<" Lepton Label out of range in GEWLH; IT1,IT2 = "<<it1<<"  "<<it2<<endl;
    return 0.0;
  } 
  
  if(ibh == 1){
    Value = GLR(it1, ibs, it2);
  } 
  else if(ibh == -1){
    Value = GLL(it1, ibs, it2);
  } 
  else{
    cout<<" IBoson cHirality index out of range in GEWLH; IBH = "<<ibh<<endl;
    return 0.0;
  } 
  
  return Value;
} 

double EwkSet::gEWqH(int iq1, int ibs, int ibh, int iq2)
{
//           (G) Electro-Weak coupling for Quarks in the cHirality base.
//            -  -       -                 -             -

//               To be used in the calculation of general E-WK matrix elements.

//           IBH =  1     :  right-handed
//                 -1     :  left -handed
//                  other :  illegal

  double Value = 0.0;
  if((iq1 < 1 || iq1 > NFL) || (iq2 < 1 || iq2 > NFL)){
    cout<<" Quark Label out of range in GEWQH; IQ1,IQ2 = "<<iq1<<"  "<<iq2<<endl;
    return 0.0;
  }

  if(ibh == 1){
    Value = HQR(iq1, ibs, iq2);
  }
  else if(ibh == -1){
    Value = HQL(iq1, ibs, iq2);
  }
  else{
    cout<<" IBoson cHirality index out of range in GEWQH; IBH = "<<ibh<<endl;
  }

  return Value;
}

double EwkSet::gEWqT(int iq1, int ibs, int ibt, int iq2)
{
//           (G) Electro-Weak coupling for Quarks in the Tensor base.
//            -  -       -                 -             -

//               To be used in the calculation of general E-WK matrix elements.

//           IBT =  1     :  Vector
//                 -1     :  Axial-vector
//                  other :  illegal

  double Value = 0.0;
  if((iq1 < 1 || iq1 > NFL) || (iq2 < 1 || iq2 > NFL)){
    cout<<" Quark Label out of range in GEWQT; IQ1,IQ2 = "<<iq1<<"  "<<iq2<<endl;
    return 0.0;
  }

  if(ibt == 1){
    Value = HQV(iq1, ibs, iq2);
  }
  else if(ibt == -1){
    Value = HQA(iq1, ibs, iq2);
  }
  else{
    cout<<" IBoson Tensor index out of range in GEWQT; IBT = "<<ibt<<endl;
    return 0.0;
  }

  return Value;
}

void EwkSet::SetEWcpl2()
{
 int nfl = 6;
 int nbn = 4;
 int Lprt = 0;

 int nflt = 5;

 if(Lprt >= 1){
   cout<<"Squared EW Couplings for Annih. and Compton processes:"<<endl;
 }

 for(int ibn = 1; ibn <= nbn; ibn++){
   if(Lprt >= 1) cout<<"ANNIH: 'cb','cb','db','ub','G','u','d','s','c'"<<endl;
   for(int ip1 = -nflt; ip1 <= nflt; ip1++){
     if(ip1 == 0) continue;
//                                                                Scattering
//                                                        Final state summed
     cplsct(ip1, ibn) = 0.0;
     for(int ip2 = 1; ip2 <= nflt; ip2++){
       double CPLV, CPLA;
       if(ip1 > 0){
         CPLV = gEWqT(ip1, ibn, 1, ip2);
         CPLA = gEWqT(ip1, ibn,-1, ip2);
       }
       else{
         CPLV = gEWqT(ip2, ibn, 1,-ip1);
         CPLA = gEWqT(ip2, ibn,-1,-ip1);
       }
       double CPL2 = pow(CPLV, 2.0) + pow(CPLA, 2.0);
       cplsct(ip1, ibn) = cplsct(ip1, ibn) + CPL2;
     }

//                                                                Annihilation
     for(int ip2 = -nflt; ip2 <= nflt; ip2++){
       if(ip2 == 0) continue;
//                                  To annihilate, must have quark - antiquark
       if((abs(ip2) / ip2) == (abs(ip1) / ip1)){
         cplanh(ip1, ibn, ip2) = 0.0;
         continue;
       }

       double CPLV, CPLA;
       if(ip1 > 0){
         CPLV = gEWqT(ip1, ibn, 1,-ip2);
         CPLA = gEWqT(ip1, ibn,-1,-ip2);
       }
       else{
         CPLV = gEWqT(ip2, ibn, 1,-ip1);
         CPLA = gEWqT(ip2, ibn,-1,-ip1);
       }
       double CPL2 = pow(CPLV, 2.0) + pow(CPLA, 2.0);
       cplanh(ip1, ibn, ip2) = CPL2;
     }

     if(Lprt >= 1) cout<<"(CPLANH(IP1, IBN, IP2), IP2=-4,4)"<<endl;
   }

   if(Lprt >= 1) cout<<"Compt.:, (CPLSCT(IP1, IBN), IP1=-4,4)"<<endl;
 }

 isSetEWcpl2 = true;
}

double EwkSet::EwCpl2An(int jp1, int jbn, int jp2)
{
 if(!isSetEWcpl2) SetEWcpl2();

 return cplanh(jp1, jbn, jp2);
}

double EwkSet::EwCpl2Cn(int jp, int jbn)
{
 if(!isSetEWcpl2) SetEWcpl2();

 return cplsct(jp, jbn);
}

