#include "ePumpHelper/ePumpHelper.h"

void ePumpHelper::GetUpdateParameter()
{
 Xdyn = EU->Xdyn; // \Delta X
 XXdyn = EU->XXdyn; // \Delta X quardratic term
 Cm = EU->Cm; // Covariance
 XE = EU->XE; // Data Point
 X0 = EU->X0; // Original Theory
 weight = EU->weight; // Weight
 Tsq = EU->Tsq; // Total tolerance
 A = EU->A; // A_i
 M = EU->M; // M_ij

 ExtendedXdyn = Xdyn;
 ExtendedXXdyn = XXdyn;
 ExtendedA = A;
 ExtendedM = M;

 ExtendeddChi2new = EU->dChi2new;
 ExtendedX0new = EU->X0new;
}

void ePumpHelper::ReadParameterList()
{
 //ExtendedXmat[Ndata][NPoint][NExtendedPara]

 ifstream ParaFile;
  ParaFile.open(FileName + ".NewPara", ios::in);

 TString Name;
 double Central;
 double Plus;
 double Minus;

 while(ParaFile >> Name){
   ParaFile >> Central >> Plus >> Minus;
   ExtendedParaName.push_back(Name);
   ExtendedParaCentral.push_back(Central);
   ExtendedParaPlus.push_back(Plus);
   ExtendedParaMinus.push_back(Minus);
 }

 ParaFile.close();

 NExtendedPara = ExtendedParaName.size();

 if(NExtendedPara == 0) return;
 else isUpdateExtendPara = true;

/////////////////////////////////////////////////////////////////////////////////////////////////

 ExtendedEU = new ePump(FileName + "_NewPara", 1.0);
 strcpy(ExtendedEU->mainfile, EU->mainfile);
 ExtendedEU->ReadInTheoryAndData();
 strcpy(ExtendedEU->PDFoutfile, ((string)"outPDFs_NewPara/i2Tn3").c_str());
 strcpy(ExtendedEU->mainfile, (FileName + "_NewPara").Data());

 ExtendedEU->Ni = EU->Ni + NExtendedPara;

 ExtendedEU->M.resize(EU->Ni + NExtendedPara);
 ExtendedEU->A.resize(EU->Ni + NExtendedPara);
 ExtendedEU->L.resize(EU->Ni + NExtendedPara);
 ExtendedEU->LinvA.resize(EU->Ni + NExtendedPara);
 ExtendedEU->TdynP.resize(EU->Ni + NExtendedPara);
 ExtendedEU->TdynM.resize(EU->Ni + NExtendedPara);
 ExtendedEU->TdynBar.resize(EU->Ni + NExtendedPara);
 ExtendedEU->TdynRMS.resize(EU->Ni + NExtendedPara);

 ExtendedEU->OldPDF.resize(2 * (EU->Ni + NExtendedPara) + 1);
 ExtendedEU->NewPDF.resize(2 * (EU->Ni + NExtendedPara) + 1);
 ExtendedEU->OldPDFAlphaS.resize(2 * (EU->Ni + NExtendedPara) + 1);
 ExtendedEU->NewPDFAlphaS.resize(2 * (EU->Ni + NExtendedPara) + 1);

 for(int i = 0; i < EU->Ni + NExtendedPara; i++){
   ExtendedEU->M[i].resize(EU->Ni + NExtendedPara);
   ExtendedEU->L[i].resize(EU->Ni + NExtendedPara);
   ExtendedEU->TdynP[i]=1.0;
   ExtendedEU->TdynM[i]=1.0;
   ExtendedEU->TdynBar[i]=1.0;
   ExtendedEU->TdynRMS[i]=1.0;
 }

 for(int k = 0; k < ExtendedEU->Ndata; k++){
   ExtendedEU->Xset[k].resize(2 * ExtendedEU->Ni + 1);

   for(int a = 0; a < ExtendedEU->Na[k]; a++){
     ExtendedEU->Xmat[k][a].resize(2 * ExtendedEU->Ni + 1);
     ExtendedEU->XmatNew[k][a].resize(2 * ExtendedEU->Ni + 1); //yfu
     ExtendedEU->FractionalContribution[k][a].resize(2 * ExtendedEU->Ni + 1); //yfu
     ExtendedEU->dX[k][a].resize(ExtendedEU->Ni);
   }

   for(int i = 0; i < 2 * ExtendedEU->Ni + 1; i++){
     ExtendedEU->Xset[k][i].resize(ExtendedEU->Na[k]);
   }
 }

 ExtendedTdynRMS.resize(NExtendedPara);
 ExtendedTdynP.resize(NExtendedPara);
 ExtendedTdynM.resize(NExtendedPara);
 ExtendedTdynBar.resize(NExtendedPara);

 for(int i = 0; i < NExtendedPara; i++){
   double TPlus = pow((ExtendedParaPlus.at(i) - ExtendedParaCentral.at(i)) * 10.0, 2.0);
   double TMinus = pow((ExtendedParaMinus.at(i) - ExtendedParaCentral.at(i)) * 10.0, 2.0);
   ExtendedTdynRMS.at(i) = sqrt((TPlus + TMinus) / 2.0);
   ExtendedTdynP.at(i) = sqrt(TPlus);
   ExtendedTdynM.at(i) = sqrt(TMinus);
   ExtendedTdynBar.at(i) = (ExtendedTdynP.at(i) + ExtendedTdynM.at(i)) / 2.0;

   ExtendedTdynRMS.at(i) /= EU->Tfix;
   ExtendedTdynP.at(i) /= EU->Tfix;
   ExtendedTdynM.at(i) /= EU->Tfix;
   ExtendedTdynBar.at(i) /= EU->Tfix;
 }

 ExtendedXmat.resize(EU->Ndata);
 ExtendedXmatNew.resize(EU->Ndata);

 for(int k = 0; k < EU->Ndata; k++){
   ExtendedXmat[k].resize(EU->Na[k]);
   ExtendedXmatNew[k].resize(EU->Na[k]);
   for(int a = 0; a < EU->Na[k]; a++){
     ExtendedXmat[k][a].resize(2 * NExtendedPara + 1);
     ExtendedXmat[k][a][0] = EU->Xmat[k][a][0];
     ExtendedXmatNew[k][a].resize(2 * NExtendedPara + 1);
   }
 }

 string rawstring, inputstring;
 stringstream line;
 int Ncol;
 double dum;

 for(int k = 0; k < EU->Ndata; k++){
   for(int iPar = 0; iPar < NExtendedPara; iPar++){
     ifstream TheoryFile;
      TheoryFile.open(AllDataNames.at(k) + (TString)".theory." + ExtendedParaName.at(iPar), ios::in);

     if ( !TheoryFile.is_open() ) {
       cerr<<"Error opening theory file: "<<AllDataNames.at(k) + (TString)".theory." + ExtendedParaName.at(iPar)<<endl;
       exit(1);
     } else {
       cout<<"-----------------------------------------------------------------"<<endl;
       cout<<"Initializing Theory arrays for Data Set "<<k+1<<": "<<AllDataNames.at(k) + (TString)".theory." + ExtendedParaName.at(iPar)<<endl;
       cout<<"-----------------------------------------------------------------"<<endl;
       ExtendedEU->ePout<<"-----------------------------------------------------------------"<<endl;
       ExtendedEU->ePout<<"Initializing Theory arrays for Data Set "<<k+1<<": "<<AllDataNames.at(k) + (TString)".theory." + ExtendedParaName.at(iPar)<<endl;
       ExtendedEU->ePout<<"-----------------------------------------------------------------"<<endl;
     }
     cout<<endl;
     ExtendedEU->ePout<<endl;

     do {
       getline(TheoryFile, rawstring);
       inputstring=trim(rawstring);
       cout<<inputstring<<endl;
       ExtendedEU->ePout<<inputstring<<endl;
     } while ( inputstring[0]=='*');
     TheoryFile>>Ncol;
     getline(TheoryFile, inputstring);
     cout<<"      "<<Ncol<<endl;
     ExtendedEU->ePout<<"      "<<Ncol<<endl;

     getline(TheoryFile, rawstring);
     inputstring=trim(rawstring);

     for(int a = 0; a < EU->Na[k]; a++){
       getline(TheoryFile,inputstring);
       line.str(inputstring);
       for(int b = 0; b < Ncol - 1; b++){
         line>>dum;
       }
       line>>ExtendedXmat[k][a][2 * iPar + 1];
       line.clear();
     }

     getline(TheoryFile, rawstring);
     inputstring=trim(rawstring);

     for(int a = 0; a < EU->Na[k]; a++){
       getline(TheoryFile,inputstring);
       line.str(inputstring);
       for(int b = 0; b < Ncol - 1; b++){
         line>>dum;
       }
       line>>ExtendedXmat[k][a][2 * iPar + 2];
       line.clear();
     }

     TheoryFile.close();

     for(int a = 0; a < EU->Na[k]; a++){
       cout<<setw(13)<<scientific<<uppercase<<setprecision(5)<<ExtendedXmat[k][a][2 * iPar + 1];
       ExtendedEU->ePout<<setw(13)<<scientific<<uppercase<<setprecision(5)<<ExtendedXmat[k][a][2 * iPar + 1];
       cout<<endl;
       ExtendedEU->ePout<<endl;
     }
     cout<<endl;
     ExtendedEU->ePout<<endl;

     for(int a = 0; a < EU->Na[k]; a++){
       cout<<setw(13)<<scientific<<uppercase<<setprecision(5)<<ExtendedXmat[k][a][2 * iPar + 2];
       ExtendedEU->ePout<<setw(13)<<scientific<<uppercase<<setprecision(5)<<ExtendedXmat[k][a][2 * iPar + 2];
       cout<<endl;
       ExtendedEU->ePout<<endl;
     }
     cout<<endl;
     ExtendedEU->ePout<<endl;

   }
 }

 for(int k = 0; k < EU->Ndata; k++){
   ExtendXdyn(k);
 }

// NExtendedPara = 0;
 cout<<"NExtendedPara = "<<NExtendedPara<<endl;
 ExtendedEU->ePout<<"NExtendedPara = "<<NExtendedPara<<endl;

/////////////////////////////////////////////////////////////////////////////////

 for(int k = 0; k < ExtendedEU->Ndata; k++){
   for(int i = EU->Ni; i < ExtendedEU->Ni; i++){
     for(int a = 0; a < ExtendedEU->Na[k]; a++){
       ExtendedEU->Xmat[k][a][2*i+1]=ExtendedXmat[k][a][2 * (i - EU->Ni) + 1];
       ExtendedEU->XmatNew[k][a][2*i+1]=ExtendedXmat[k][a][2 * (i - EU->Ni) + 1]; //yfu
       ExtendedEU->Xset[k][2*i+1][a]=ExtendedEU->Xmat[k][a][2*i+1];

       ExtendedEU->Xmat[k][a][2*i+2]=ExtendedXmat[k][a][2 * (i - EU->Ni) + 2];
       ExtendedEU->XmatNew[k][a][2*i+2]=ExtendedXmat[k][a][2 * (i - EU->Ni) + 2]; //yfu
       ExtendedEU->Xset[k][2*i+2][a]=ExtendedEU->Xmat[k][a][2*i+2];

       ExtendedEU->dX[k][a][i] = (ExtendedXmat[k][a][2 * (i - EU->Ni) + 1] - ExtendedXmat[k][a][2 * (i - EU->Ni) + 2]) / 2.0;
     }
   }
 }

 for(int i = EU->Ni; i < ExtendedEU->Ni; i++){
   ExtendedEU->TdynP[i]=ExtendedTdynP.at(i - EU->Ni);
   ExtendedEU->TdynM[i]=ExtendedTdynM.at(i - EU->Ni);
   ExtendedEU->TdynBar[i]=ExtendedTdynBar.at(i - EU->Ni);
   ExtendedEU->TdynRMS[i]=ExtendedTdynRMS.at(i - EU->Ni);
 }

 ExtendedEU->Xdyn = ExtendedXdyn;
 ExtendedEU->XXdyn = ExtendedXXdyn;
 ExtendedEU->ConstructUpdateMatrix();
 ExtendedEU->UpdateObservables();
}

void ePumpHelper::ExtendXdyn(int k)
{

    double dx, ddx, tp, tm, tbar;
    for (int a = 0; a < EU->Na[k]; a++) {
        for (int i = 0; i < NExtendedPara; i++) {
            if (EU->T_flag == 1) {
                tp = ExtendedTdynRMS[i];
                tm = ExtendedTdynRMS[i];
                tbar = ExtendedTdynRMS[i];
            } else {
                tp = ExtendedTdynP[i];
                tm = ExtendedTdynM[i];
                tbar = ExtendedTdynBar[i];
            }
            TaylorCoeffs(dx,ddx,EU->Xmat[k][a][0],ExtendedXmat[k][a][2*i+1],ExtendedXmat[k][a][2*i+2],tp,tm,tbar);
            ExtendedXdyn[k][a].push_back(dx);
            ExtendedXXdyn[k][a].push_back(ddx);
        }
    }

    //for (int a = 0; a < EU->Na[k]; a++) {
    //  cout<<ExtendedXmat[k][a][1]<<" "<<EU->Xmat[k][a][0]<<" "<<ExtendedXmat[k][a][2]<<" "<<ExtendedXdyn[k][a][29]<<endl;
    //  ExtendedEU->ePout<<ExtendedXmat[k][a][1]<<" "<<EU->Xmat[k][a][0]<<" "<<ExtendedXmat[k][a][2]<<" "<<ExtendedXdyn[k][a][29]<<endl;
    //}
    cout<<endl;
    ExtendedEU->ePout<<endl;

}

////////////////////////////////////////////////////////
////// The following code will not be used at all //////
////////////////////////////////////////////////////////

void ePumpHelper::InputExtendedParameter()
{
/* ExtendedEU->Ndata = EU->Ndata;
 ExtendedEU->Na = EU->Na;
 ExtendedEU->dataIncluded = EU->dataIncluded;
 ExtendedEU->weight = EU->weight;
 ExtendedEU->dataset = EU->dataset;
 ExtendedEU->theoryset = EU->theoryset;
 ExtendedEU->error_type = EU->error_type;
 ExtendedEU->error_type_all = EU->error_type_all;
 ExtendedEU->weight_all = EU->weight_all;

 ExtendedEU->df_flag = EU->df_flag;
 ExtendedEU->DiagonalQuad = EU->DiagonalQuad;
 ExtendedEU->zrescale = EU->zrescale;
 ExtendedEU->T_flag = EU->T_flag;

 ExtendedEU->Gweight = EU->Gweight;
 ExtendedEU->Pweight = EU->Pweight;

 ExtendedEU->pdftype = EU->pdftype;

 strcpy(ExtendedEU->PDFinfile, EU->PDFinfile);
 strcpy(ExtendedEU->PDFoutfile, ((string)"outPDFs_NewPara/i2Tn3").c_str());

 ExtendedEU->verb = EU->verb;
 ExtendedEU->reportCCs = EU->reportCCs;

 ExtendedEU->Ni = EU->Ni + NExtendedPara;
 ExtendedEU->Xmat = ExtendedXmat;
 ExtendedEU->XmatNew = ExtendedXmatNew;
 ExtendedEU->Xset = ExtendedXset; //!
 ExtendedEU->dX = ExtendeddX; //!
 ExtendedEU->Xdyn = ExtendedXdyn;
 ExtendedEU->XXdyn = ExtendedXXdyn;
 ExtendedEU->X0 = EU->X0;
 ExtendedEU->Q = EU->Q;
 ExtendedEU->Chi2 = EU->Chi2;
 ExtendedEU->dChi2 = EU->dChi2;
 ExtendedEU->dChi2Set = ExtendeddChi2Set; //!

 ExtendedEU->XE = EU->XE;
 ExtendedEU->Cm = EU->Cm;
*/

}

void ePumpHelper::PrepareAMlinearExtended(int k)
{
    d_mat temp;
    d_vec Atemp;
    d_mat Mtemp;

    int NPara = EU->Ni + NExtendedPara;

    temp.resize(NPara);
    Atemp.resize(NPara);
    Mtemp.resize(NPara);
    for (int i=0;i<NPara;i++) {
        temp[i].resize(EU->Na[k]);
        Mtemp[i].resize(NPara);
    }

    for (int i=0;i<NPara;i++) {
        Atemp[i]=0.0;
        for (int a=0;a<EU->Na[k];a++) {
            temp[i][a]=0.0;
            for (int b=0;b<EU->Na[k];b++) {
                temp[i][a]+=Cm[k][a][b]*ExtendedXdyn[k][b][i];
            }
            Atemp[i]+=(XE[k][a]-X0[k][a])*temp[i][a];
        }
        Atemp[i]*=(weight[k]/Tsq);
        ExtendedA[i]+=Atemp[i];
    }


    for (int i=0;i<NPara;i++) {
        for (int j=i;j<NPara;j++) {
            Mtemp[i][j]=0.0;
            for (int a=0;a<EU->Na[k];a++) {
                Mtemp[i][j]+=ExtendedXdyn[k][a][i]*temp[j][a];
            }
            Mtemp[i][j]*=(weight[k]/Tsq);
            ExtendedM[i][j]+=Mtemp[i][j];
        }
    }

}

double ePumpHelper::NewBestFitLinearExtended(void)
{

// Returns length of z0[i] vector

    int NPara = EU->Ni + NExtendedPara;

    d_mat ident(NPara);
    d_mat LinvIdent(NPara);
    d_mat IplusM(NPara);

    d_mat L(NPara);
    d_vec LinvA(NPara);

    ExtendedA.resize(NPara);
    ExtendedM.resize(NPara);

    for (int i=0;i<NPara;i++) {
        ident[i].resize(NPara);
        IplusM[i].resize(NPara);
        LinvIdent[i].resize(NPara);

        L[i].resize(NPara);

        ExtendedM[i].resize(NPara);
    }
    for (int i=0;i<NPara;i++) {
        for (int j=0;j<NPara;j++) {
                if (i==j) {
                    ident[i][j]=1.0;
                } else {
                    ident[i][j]=0.0;
                }
        }
    }

    for (int i=0;i<NPara;i++) {
        ExtendedA[i]=0.0;
        for (int j=i;j<NPara;j++) {
            ExtendedM[i][j]=0.0;
        }
    }

    for (int k=0;k<EU->Ndata;k++) {
        if (EU->dataIncluded[k]) {
            PrepareAMlinearExtended(k);
        }
    }

    for (int i=0;i<NPara;i++) {
        for (int j=0;j<i;j++) {
            ExtendedM[i][j]=ExtendedM[j][i];
            IplusM[i][j]=ExtendedM[i][j];
            IplusM[j][i]=ExtendedM[j][i];
        }
        IplusM[i][i]=EU->Pweight+ExtendedM[i][i];
    }
    Cholesky(IplusM,L,NPara);
    BackSub(L,ExtendedA,LinvA,NPara);
    double dzsqr=0.0;
    for (int i=0;i<NPara;i++) {
        BackSub(L,ident[i],LinvIdent[i],NPara);
        Extendedz0[i]=dot(LinvIdent[i],LinvA,NPara);
        Extendedz0sqr[i]+=Extendedz0[i]*Extendedz0[i];
        dzsqr+=Extendedz0sqr[i];
    }

    return sqrt(dzsqr);
}

void ePumpHelper::ConstructUpdateMatrixExtended(void)
{
    int NPara = EU->Ni + NExtendedPara;

    Extendedz0.resize(NPara);
    Extendedz0sqr.resize(NPara);
    double dz;

    // Calculate original total Chi-square

    ExtendedChi2=0.0;
    for (int k=0;k<EU->Ndata;k++) {
        if (EU->dataIncluded[k]) {
            ExtendedChi2+=weight[k]*EU->dChi2[k];
        }
    }

    if (!EU->DiagonalQuad) {

        cout<<" Only Linear terms included in updating of best-fit predictions (Extended)."<<endl<<endl;
        EU->ePout<<" Only Linear terms included in updating of best-fit predictions (Extended)."<<endl<<endl;

        dz=NewBestFitLinearExtended();

        ConstructX0newChi2newExtended();

        cout<<" Total Chi2 (z=0) (Extended) = "<<fixed<<setprecision(4)<<ExtendedChi2<<endl;
        cout<<" Total Chi2 (z=z0) (Extended) = "<<fixed<<setprecision(4)<<ExtendedChi2new<<endl<<endl;
        EU->ePout<<" Total Chi2 (z=0) (Extended) = "<<fixed<<setprecision(4)<<ExtendedChi2<<endl;
        EU->ePout<<" Total Chi2 (z=z0) (Extended) = "<<fixed<<setprecision(4)<<ExtendedChi2new<<endl<<endl;

    }

    Meig();

        cout<<"  Vector zh0[i]=z0[i] from i=1,NPara  (original eigenvector basis)"<<endl;
        EU->ePout<<"  Vector zh0[i]=z0[i] from i=1,NPara  (original eigenvector basis)"<<endl;
        dz=0.0;
        for (int i=0;i<NPara;i++) {
            double z0bar=Extendedz0[i]; // Rescaled already /TdynBar[i];
            cout<<setw(2)<<i<<"  "<<setw(10)<<fixed<<setprecision(4)<<right<<z0bar<<endl;
            EU->ePout<<setw(2)<<i<<"  "<<setw(10)<<fixed<<setprecision(4)<<right<<z0bar<<endl;
            dz+=z0bar*z0bar;
        }
        dz=sqrt(dz);
        cout<<endl;
        EU->ePout<<endl;
        cout<<" Length of best-fit zh0 vector (Extended) is "<<scientific<<setprecision(2)<<dz<<endl<<endl;
        EU->ePout<<" Length of best-fit zh0 vector (Extended) is "<<scientific<<setprecision(2)<<dz<<endl<<endl;

        dz=0.0;
        if (EU->Pweight!=1.0) {
            cout<<"  Vector ch0[r] = -sqrt(p+lambda[r])*sum(U[r][i]z0[i] over i=1,NPara) from r=1,NPara  (updated eigenvector basis)"<<endl;
            EU->ePout<<"  Vector ch0[r] = -sqrt(p+lambda[r])*sum(U[r][i]z0[i] over i=1,NPara) from r=1,NPara  (updated eigenvector basis)"<<endl;
            cout<<"   (weighted by w="<<EU->Pweight<<" in update)";
        } else {
            cout<<"  Vector ch0[r] = -sqrt(1+lambda[r])*sum(U[r][i]z0[i] over i=1,NPara) from r=1,NPara  (updated eigenvector basis)"<<endl;
            EU->ePout<<"  Vector ch0[r] = -sqrt(1+lambda[r])*sum(U[r][i]z0[i] over i=1,NPara) from r=1,NPara  (updated eigenvector basis)"<<endl;
        }
        for (int i=0;i<NPara;i++) {
            double z0r=0.0;
            for (int j=0;j<NPara;j++) {
                z0r+=ExtendedU[j][i]*Extendedz0[j];// Rescaled already /TdynBar[j];
            }
            z0r*=(-sqrt(EU->Pweight+Extendedd[i]));
            cout<<setw(2)<<i<<"  "<<setw(10)<<fixed<<setprecision(4)<<right<<z0r<<endl;
            EU->ePout<<setw(2)<<i<<"  "<<setw(10)<<fixed<<setprecision(4)<<right<<z0r<<endl;
            dz+=z0r*z0r;
        }
        dz=sqrt(dz);
        cout<<endl;
        EU->ePout<<endl;

        cout<<" Length of best-fit ch0 vector (Extended) is "<<scientific<<setprecision(2)<<dz<<endl<<endl;
        EU->ePout<<" Length of best-fit ch0 vector (Extended) is "<<scientific<<setprecision(2)<<dz<<endl<<endl;

}

void ePumpHelper::ConstructX0newChi2newExtended(void)
{

    // Construct new best-fit predictions for each data point

        int NPara = EU->Ni + NExtendedPara;

        for (int k=0;k<EU->Ndata;k++) {
            for (int a=0;a<EU->Na[k];a++) {
                ExtendedX0new[k][a]=X0[k][a]+dot(ExtendedXdyn[k][a],Extendedz0,NPara);
                if (EU->DiagonalQuad) {
                    ExtendedX0new[k][a]+=(dot(ExtendedXXdyn[k][a],Extendedz0sqr,NPara)/2.0);
                }
            }
        }

    // New delta Chi^2 for each data set

        ExtendedChi2new=0.0;
        for (int k=0;k<EU->Ndata;k++) {
            if (EU->dataIncluded[k]) {
                ExtendeddChi2new[k]=EU->DeltaChiSquare(ExtendedX0new[k],k);
                ExtendedChi2new+=weight[k]*ExtendeddChi2new[k];
            }
        }

    //  New delta Chi^2 for original global analysis:

        ExtendedChi20new=0.0;
        for (int i=0;i<NPara;i++) {
            ExtendedChi20new+=Extendedz0sqr[i];
        }
        ExtendedChi20new*=Tsq;
        ExtendedChi2new+=EU->Pweight*ExtendedChi20new;
}

void ePumpHelper::Meig(void)
{
    int NPara = EU->Ni + NExtendedPara;

    int i,j;
    d_mat MM(NPara), X(NPara);
    d_vec n(NPara);
    for (i=0;i<NPara;i++) {
        ExtendedU.resize(NPara);
        Extendedd.resize(NPara);
    }
    for (i=0;i<NPara;i++) {
        ExtendedU[i].resize(NPara);
        X[i].resize(NPara);
        MM[i].resize(NPara);
    }
    for (i=0;i<NPara;i++) {
        for (j=0;j<NPara;j++) {
            MM[i][j]=ExtendedM[i][j];
        }
    }

    if (EU->verb) {
        cout<<" Input Matrix M(Extended):"<<endl<<endl;
        EU->ePout<<" Input Matrix M(Extended):"<<endl<<endl;
        for (i=0;i<NPara;i++) {
            for (j=0;j<NPara;j++) {
                cout<<setw(12)<<fixed<<setprecision(9);
                EU->ePout<<setw(12)<<fixed<<setprecision(9);
                cout<<MM[i][j]<<"  ";
                EU->ePout<<MM[i][j]<<"  ";
            }
            cout<<endl;
            EU->ePout<<endl;
        }
        cout<<endl<<endl;
        EU->ePout<<endl<<endl;
    }

    Eigen_ePump(MM,ExtendedU,Extendedd,NPara);


    eigsrt(ExtendedU,Extendedd,NPara);

//  Choose sign of eigenvector so it is predominantly positive:
    if (EU->df_flag==0) {
       double Usum;
       for (i=0;i<NPara;i++) {
           Usum=0.0;
           for (j=0;j<NPara;j++) {
               Usum+=ExtendedU[j][i];
           }
           if (Usum<0.0) {
               if (EU->verb) {
                   cout<<" Changed sign of eigenvector (Extended) "<<i<<endl;
                   EU->ePout<<" Changed sign of eigenvector (Extended) "<<i<<endl;
               }
               for (j=0;j<NPara;j++) {
                   ExtendedU[j][i]=-ExtendedU[j][i];
               }
           }
       }
    }

    cout<<endl;
    EU->ePout<<endl;

    if (EU->verb) {
        cout<<" Sorted (column) eigenvectors of M(Extended):"<<endl<<endl;
        EU->ePout<<" Sorted (column) eigenvectors of M(Extended):"<<endl<<endl;
        for (i=0;i<NPara;i++) {
            for (j=0;j<NPara;j++) {
                cout<<setw(12)<<fixed<<setprecision(9);
                EU->ePout<<setw(12)<<fixed<<setprecision(9);
                cout<<ExtendedU[i][j]<<"  ";
                EU->ePout<<ExtendedU[i][j]<<"  ";
            }
            cout<<endl;
            EU->ePout<<endl;
        }
        cout<<endl;
        EU->ePout<<endl;
    }

    cout<<"-----------------------------------"<<endl;
    cout<<"     Sorted eigenvalues of M(Extended):"<<endl;
    cout<<"-----------------------------------"<<endl<<endl;
    EU->ePout<<"-----------------------------------"<<endl;
    EU->ePout<<"Sorted eigenvalues of M(Extended):"<<endl;
    EU->ePout<<"-----------------------------------"<<endl<<endl;
    for (i=0;i<NPara;i++) {
        cout<<setw(12)<<fixed<<setprecision(8)<<right;
        EU->ePout<<setw(12)<<fixed<<setprecision(8)<<right;
        cout<<Extendedd[i]<<" ";
        EU->ePout<<Extendedd[i]<<" ";
    }
    cout<<endl<<endl;
    EU->ePout<<endl<<endl;

    if (EU->verb) {
        cout<<" Check normalization of eigenvectors (Extended):"<<endl<<endl;
        EU->ePout<<" Check normalization of eigenvectors (Extended):"<<endl<<endl;
        for (j=0;j<NPara;j++) {
            n[j]=0.0;
            for (i=0;i<NPara;i++) {
                n[j]+=ExtendedU[i][j]*ExtendedU[i][j];
            }
            cout<<"e["<<j<<"].e["<<j<<"] = ";
            EU->ePout<<"e["<<j<<"].e["<<j<<"] = ";
            cout<<setw(19)<<fixed<<setprecision(16)<<n[j]<<endl;
            EU->ePout<<setw(19)<<fixed<<setprecision(16)<<n[j]<<endl;
        }
        cout<<endl<<endl;
        EU->ePout<<endl<<endl;
        cout<<" Check that they are eigenvectors:"<<endl;
        cout<<" Calculate M.O-O.D, where O is column matrix of eigenvectors"<<endl;
        cout<<" and D is diagonal matrix of eigenvalues"<<endl<<endl;
        EU->ePout<<" Check that they are eigenvectors:"<<endl;
        EU->ePout<<" Calculate M.O-O.D, where O is column matrix of eigenvectors"<<endl;
        EU->ePout<<" and D is diagonal matrix of eigenvalues"<<endl<<endl;
        for (i=0;i<NPara;i++) {
            for (j=0;j<NPara;j++) {
                X[i][j]=-ExtendedU[i][j]*Extendedd[j];
                for (int k=0;k<NPara;k++) {
                    X[i][j]+=MM[i][k]*ExtendedU[k][j];
                }
            }
        }
        for (i=0;i<NPara;i++) {
            for (j=0;j<NPara;j++) {
                cout<<setw(10)<<scientific<<setprecision(2)<<X[i][j]<<"  ";
                EU->ePout<<setw(10)<<scientific<<setprecision(2)<<X[i][j]<<"  ";
            }
            cout<<endl;
            EU->ePout<<endl;
        }
        cout<<endl;
        EU->ePout<<endl;
    }

//    for (i=0;i<NPara;i++) {
//        if (Extendedd[i]<-0.5) {
//            cout<<"Eigenvalue "<<i+1<<" is less than -0.5.  It has been replaced by -0.5."<<endl;
//            EU->ePout<<"Eigenvalue "<<i+1<<" is less than -0.5.  It has been replaced by -0.5."<<endl;
//            Extendedd[i]=-0.5;
//        }
//        cout<<Extendedd[i];
//        EU->ePout<<Extendedd[i];
//    }
//    cout<<endl<<endl;
//    EU->ePout<<endl<<endl;
}

void ePumpHelper::UpdateObservablesExtended(void) {

    double Dsym,Dup,Ddown,DnewSym,DnewUp,DnewDown,D0new;
    double DY1,DY2,Cos12,DY1new,DY2new,Cos12new;

    //yfu add histogram
    if(DoSaveHist) myhistsExtended = new ePumpHists();
    if(DoSaveHist) myhistsExtended->openFile(FileName + "_NewPara.root");

    cout<<endl;
    cout<<"------------------------------------------------------------"<<endl;
    cout<<"            Original and Updated Delta Chi-Squares"<<endl;
    cout<<"------------------------------------------------------------"<<endl;
    cout<<endl;
    EU->ePout<<endl;
    EU->ePout<<"------------------------------------------------------------"<<endl;
    EU->ePout<<"            Original and Updated Delta Chi-Squares"<<endl;
    EU->ePout<<"------------------------------------------------------------"<<endl;
    EU->ePout<<endl;

    cout<<" Delta Chi2 for original global analysis";
    if (EU->Pweight!=1.0) {
        cout<<"   (weighted by w="<<EU->Pweight<<" in update)";
    }
    cout<<endl;
    cout<<" Old "<<fixed<<setprecision(4)<<0.0<<endl;
    cout<<" New "<<ExtendedChi20new<<endl;
    cout<<endl;
    EU->ePout<<" Delta Chi2 for original global analysis";
    if (EU->Pweight!=1.0) {
        EU->ePout<<"   (weighted by w="<<EU->Pweight<<" in update)";
    }
    EU->ePout<<endl;
    EU->ePout<<" Old "<<fixed<<setprecision(4)<<0.0<<endl;
    EU->ePout<<" New "<<ExtendedChi20new<<endl;
    EU->ePout<<endl;
    ExtendedChi2=0.0;
    ExtendedChi2new=0.0;
    int NaTot=0;
    for (int k=0;k<EU->Ndata;k++) {
        if (EU->dataIncluded[k]) {
            NaTot+=EU->Na[k];
            cout<<" Delta Chi2 for Data Set: "<<EU->dataset[k]<<" with "<<EU->Na[k]<<" data points (excluding weight factor w[k] = "<<EU->weight[k]<<")"<<endl;
            cout<<" Old "<<EU->dChi2[k]<<endl;
            cout<<" New "<<ExtendeddChi2new[k]<<endl;
            double spartyness=(pow(18.*EU->Na[k], 1.5)/(18.*EU->Na[k]+1))*(6./(6.-log(EU->dChi2[k]/EU->Na[k]))-9.*EU->Na[k]/(9.*EU->Na[k]-1));
            double spartynessnew=(pow(18.*EU->Na[k], 1.5)/(18.*EU->Na[k]+1))*(6./(6.-log(ExtendeddChi2new[k]/EU->Na[k]))-9.*EU->Na[k]/(9.*EU->Na[k]-1));
            //yfu
            //spartynessSave[k] = spartyness;
            //spartynessNewSave[k] = spartynessnew;
            EU->ePout<<" Delta Chi2 for Data Set: "<<EU->dataset[k]<<" with "<<EU->Na[k]<<" data points (excluding weight factor w[k] = "<<EU->weight[k]<<")"<<endl;
            EU->ePout<<" Old "<<EU->dChi2[k]<<endl;
            EU->ePout<<" New "<<ExtendeddChi2new[k]<<endl;
            EU->ePout<<" Old Spartyness " << spartyness<<endl;
            EU->ePout<<" New Spartyness " << spartynessnew<<endl<<endl;
            ExtendedChi2+=EU->weight[k]*EU->dChi2[k];
            ExtendedChi2new+=EU->weight[k]*ExtendeddChi2new[k];
        }
    }
    cout<<endl;
    EU->ePout<<endl;

}


