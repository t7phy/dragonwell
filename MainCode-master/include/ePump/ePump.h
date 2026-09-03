#ifndef EUHDR
#define EUHDR

#include <math.h>
#include <iostream>
#include <iomanip>
#include <fstream>
#include <string.h>
#include <vector>
#include <stdio.h>
#include "ePump/VectorDef.h"
#include <Eigen/Dense>

using namespace std;

//yfu add a package for histogram
#include "ePump/ePumpHists.h"
//#include "ePumpHelper/ePumpHelper.h"

class ePumpHelper;

//We trim both leading and trailing space
const std::string WHITESPACE = " \n\r\t\f\v";
std::string ltrim(const std::string &s);
std::string rtrim(const std::string &s);
std::string trim(const std::string &s);

    // Na = Number of data points
    // Ni = Number of eigenvector pairs
    // Use indices a,b,c,... = 0,Na-1 for data points
    // Use indices i,j,k,... =0,Ni-1 for eigenvector pairs

enum PDF_format_type { CTEQ = 0, LHAPDF1 = 1, NONE = 2 };//yfu change the LHAPDF to LHAPDF1 to promise inconflict with the LHAPDF class
enum Data_format_type { ICM = 0, CSE = 1 };
    // ICM=Inverse covariance matrix
    // CSE=Correlated systematic errors

class ePump {

    //yfu add for ePumpHelper
    friend class ePumpHelper;
    //yfu

    protected:
        int Ni, Ndata;
        i_vec Na;     // Na[Ndata]
        vector<bool> dataIncluded;   //dataIncluded[Ndata]
        d_vec weight;   // weight[Ndata]
        vector<string> dataset;  //dataset[Ndata]
	vector<string> theoryset; //added by kp
        i_vec error_type;  //error_type[Ndata]

        //yfu defined for all data set
        i_vec error_type_all;
        d_vec weight_all;
        //yfu

        int df_flag;   //  Default=0 for linear only, =4 for diagonal quadratic;
             //  =0:  df1=(fp-f0);  df2 = (f0-fm);
             //       Plus fix sign of U[j][i] by [Sum over j](U[j][i]) > 0;
             //  =1:  df1 = df2 = (fp - fm)/2
             //  =2:  df1=(fp-f0);  df2 = (f0-fm);  (Sign of U[j][i] arbitrary)
             //  =3:  If U[j][i]>0  df1=(fp-f0); df2=(f0-fm);
             //       else  df1=(f0-fm);  df2=(fp-f0);
             //  =4:  Use Taylor expansion including diagonal quadratic terms
    
        bool DiagonalQuad, zrescale;  // If true, include diagonal quadratic terms in best-fit predictions.
             //  If false, include linear terms only in best-fit predictions.
    
        int T_flag;   //   Default=0;
             //  =0; Use TdynP, TdynM, TdynBar
             //  =1; Use TdynRMS
    
    
        double Gweight;    // Global weight (multiplies weight[Ndata])
        double Pweight;    // Weight multiplies original chi^2 (default=1.0)
    
        char mainfile[80];  // name of .in and .out files
    
        ofstream ePout;
    
        PDF_format_type pdftype;
        char PDFinfile[80];
        char PDFoutfile[80];
    
        bool verb;
        bool reportCCs;
    
// Initial theoretical predictions:
        d_mat_list Xmat;      // X values, stored as Xmat[Ndata][Na][2*Ni+1]
        d_mat_list XmatNew;   // yfu add for storing every new theory prediction
        d_mat_list FractionalContribution; // yfu
        d_mat_list Xset;      // Xset[Ndata][2*Ni+1][Na], in order to calculate chi^2 for each set
        d_mat_list dX;     //   dX[Ndata][Na][Ni]
           //  dX[r][a][i] = (X[r][a][i+] - X[r][a][i-]) / 2
    
        d_mat_list Xdyn;    //   dX[Ndata][Na][Ni]
           // Generalization of dX when including dynamical tolerances.
        d_mat_list XXdyn;    //   dX[Ndata][Na][Ni]
           // Diagonal 2nd-derivative terms in expansion of X (with dynamical tolerances).
        d_mat X0;    //   X0[Ndata][Na]
           // Initial best-fit values of X[a]
        d_mat_list Q;     //   Q[Ndata][Na][Na]
           //  Q[a][b] = dX[a].dX[b]
        double Chi2;
        d_vec dChi2;      // dchi2[Ndata]
        d_mat dChi2Set; //yfu
    
    
        //yfu add for updated results
        d_mat NewTheory;
        d_mat OldPDFError;
        d_mat NewPDFError;
        vector<d_mat_list> OldPDFCorrelation;
        vector<d_mat_list> NewPDFCorrelation;
        d_vec spartynessSave;
        d_vec spartynessNewSave;
        d_mat OldPDF;
        d_mat NewPDF;
        d_mat OldPDFAlphaS;
        d_mat NewPDFAlphaS;
        //yfu

        double Tfix,Tsq,Tol,TsqAvg;  // CT14 default Tolerance
    
    
        // All Dynamical Tolerances are normalized to global tolerance T.
        // If dynamical tolerances are given then value of T is defined by:
                         // Tdyn[i]  = Sqrt[  Tdyn[i+]^2 + Tdyn[i-]^2 / 2 ]
                         // TsqAvg = 1/Ni * Sum [Tdyn[i]^2] and Tol=Sqrt[TsqAvg];
        // If dynamical tolerances are not given, then all of the following are all set to 1.0 by default.
    
        d_vec TdynP;     // TdynP[i] = Tdyn[i+]/T
        d_vec TdynM;     // TdynM[i] = Tdyn[i-]/T
        d_vec TdynBar;   // TdynBar[i] = (TdynP[i]+TdynM[i])/2
        d_vec TdynRMS;  // TdynRMS[i] = Sqrt[  TdynP[i]^2 + TdynM[i]^2 / 2 ]
    
// Experimental inputs:
        d_mat XE;    // XE[Ndata][Na]
           // Experimental values of X[a]
        d_mat_list Cm;    //   Cm[Ndata][Na][Na]
           // Experimental Inverse Covariance Error Matrix
    
// Alternative Experimental inputs:
        i_vec Nlam;  //Nlam[Ndata]
           // Number of correlated systematic errors
        d_mat s;    // s[Ndata][Na]
           // Uncorrelated errors, includes stat and sys errors in quadrature
           // For error_type 1 or 4
        d_mat s_stat;    // s_stat[Ndata][Na]
           // Uncorrelated statistical errors, for error_type 2
        d_mat s_sys;    // s_sys[Ndata][Na]
           // Uncorrelated systematic errors, for error_type 2
        d_mat_list beta; // beta[Ndata][Na][Nlam]
        d_mat_list CorrErrs; // yfu added Correlated systematic uncertainties
        map<int, Eigen::VectorXd> EigenData;
        map<int, Eigen::VectorXd> EigenUnCorr;
           // Correlated systematic errors
        d_mat_list rhocc;     // rhocc[Ndata][Na][Na]
        void  ConstructCm1(int i);
           // Constructs Cm[Ndata][Na][Na] from s[Ndata][Na] and beta[Ndata][Na][Nlam]
        void  ConstructCm2(int i);
           // Constructs Cm[Ndata][Na][Na] from s[Ndata][Na] and beta[Ndata][Na][Nlam]
           // and rhocc[Ndata][Na][Na]
	void  ConstructCm3(int i); //added by kp
    
// Re-diagonalization Objects:
        d_mat M;  // M[Ni][Ni]
        d_vec A;       // A[Ni]
        d_mat L;       //    L[Ni][Ni] (lower triangular: LL^T=IplusM)
        d_vec LinvA;   //LinvA[Ni]
        d_mat_list calAinvBeta;  //calAinvBeta[Ndata][Na][Nlam]
    

// Updated theoretical predictions:
        d_mat X0new;      // X0new[Ndata][Na]
//        d_mat_list Qnew;       // Qnew[Ndata][Na][Na]
        double Chi2new;
        double Chi20new;
//        double Chi2diff;
        d_vec dChi2new;      // dChi2new[Ndata]
        d_mat dChi2newSet; //yfu
    
//   New best-fit parameters
        d_vec z0;  // z0[Ni]
        d_vec z0sqr;    // z0sqr[Ni]
    
// Eigenvectors and Eigenvalues of matrix M:
        d_mat U;  // U[i][j],  i=original basis, j=rotated basis
        d_vec d;     // d[j]
    
// Read in theory and data files:
    
        void ReadInTheory(char* Theoryfile,int i);
        void ReadInData1(char* Datafile, int i);
        void ReadInData2(char* Datafile, int i);
        void ReadInData3(char* Datafile, int i);
        void ReadInTolerances(void);
    
// Prepare Diagonalization objects:
    
        void SetCinv_Max(int i);
        void PrepareAM(int i, double alpha);
        void PrepareAMlinear(int i);
        void PrepareM(int i);
        void SetQ(int i);
        void SetXdyn(int i);
        void Meig(void);
        void ConstructX0newChi2new(void);
        double NewBestFitLinear(void);  // Returns length of z0[i] vector
        double NewBestFitQuadratic(double alpha);  // Returns CHANGE in length of z0[i] vector
                                              // from previous iteration


////////////////////////////////////////////////////////////////
//Yao add for LMScan
        bool doLMScan = false;
        void PerformLMScan(){this->doLMScan = true;};
        double NewBestFitLMScan(void);
        void PrepareAMLMScan(int k);
        double NewLength = 0.0;
        double OldParaError = 0.0;
        double NewParaError = 0.0;
        map<int, bool> isLMScanData;
        void SetLMScanData(int k){this->isLMScanData[k] = true;}
////////////////////////////////////////////////////////////////

//  Update Calls:
    
        void UpdatePDFs(void) {
            if (pdftype==CTEQ) {UpdatePDFs_CTEQ();
            } else if (pdftype==LHAPDF1) {UpdatePDFs_LHAPDF();
            } else {cout<<"Unknown PDF format.  Choose either CTEQ or LHAPDF."<<endl;}
        }
        void UpdatePDFs_CTEQ(void);
        void UpdatePDFs_LHAPDF(void);
    
//  Optimize Calls:
    
        void OptimizedEVContributions(void);
        void OptimizePDFs(void) {
            if (pdftype==CTEQ) {OptimizePDFs_CTEQ();
            } else if (pdftype==LHAPDF1) {OptimizePDFs_LHAPDF();
            } else {cout<<"Unknown PDF format.  Choose either CTEQ or LHAPDF."<<endl;}
        }
        void OptimizePDFs_CTEQ(void);
        void OptimizePDFs_LHAPDF(void);
    
//  Update error subroutines:

//  yfu add newYY
        void UpdateErrors(const d_vec &YY, d_vec &newYY, double &DY0sym, double &DY0up, double &DY0down,
                           double &DYnewSym, double &DYnewUp, double &DYnewDown, double &Y0new);
                 // Give 2*Ni+1 dimensional vector of Y values as input, with
                 //       YY[0]=Y[0] (central value), YY[2*i+1]=Y[i+], YY[2*i+2]=Y[i-].
                 // Calculates Y0new, and both symmetric and asymmetric versions of the errors:
                 //      DY0sym, DY0up, DY0down,band DYnewSym, DYnewUp, DYnewDown.
        void UpdateCorrCosine(const d_vec &YY1, const d_vec &YY2, double &DY1, double &DY2,  double &Cos12, double &DY1new, double &DY2new, double &Cos12new);
                 // Give 2*Ni+1 dimensional vector of Y1 and Y2 values as input, with
                 //       YY1[0]=Y1[0] (central value), YY1[2*i+1]=Y[i+], YY1[2*i+2]=Y[i-].   (Similarly for Y2.)
                 // Uses symmetric error vectors.
        void UpdateErrors0(const d_vec &dY, const d_vec &ddY, double &DY0, double &DYnew);
                 // Give error vector dY and ddY as input to calculate DY0 and DYnew.
        void UpdateCorrCosine0(const d_vec &dY1, const d_vec &dY2, const d_vec &ddY1, const d_vec &ddY2, double &DY1, double &DY2,  double &Cos12, double &DY1new, double &DY2new, double &Cos12new);
                 // Give error vectors dY1, dY2, ddY1, and ddY2 as input.
    
        double DeltaChiSquare(const d_vec &YY, int k);
        double DeltaChiSquareReal(const d_vec &YY, int k);
        void PrepareOldChi2();// yfu add this function

        double Chi2Residuals(const d_vec &YY, int k);
        double NuisanceParameters(const d_vec &YY, int k);

//yfu
        void OptimizeErrors(const d_vec &YY, d_vec &newYY);
//
    
    public:

//yfu add histogram
        char mainhisto[80];
        ePumpHists* myhists;
        bool DoSaveHist = false;
        void SaveHist(){DoSaveHist = true;}
        void SaveHists(){myhists->saveHists();}
//yfu

        ePump(const char* filename, double wgt=1.0) {strcpy(mainfile,filename);
            char mainout[80];
            strcpy(mainout,filename);
            strcat(mainout,".out");
//yfu add histogram
            strcpy(mainhisto, filename);
            strcat(mainhisto, ".root");
//yfu

            ePout.open(mainout);
            if ( !ePout.is_open() ) {
               cerr<<"Error opening out file: "<<mainout<<endl;
               exit(1);
            }
            Tfix=10.0; Tsq=Tfix*Tfix; df_flag=0 ; Gweight=wgt; verb=false; reportCCs=true;
            DiagonalQuad=false; T_flag=0; Pweight=1.0; zrescale=false;
        }
        ~ePump(void) {ePout.close();}
    
// Set output flags:
    
        void set_df_flag(int dff) {df_flag=dff;}
        void set_Pweight(double pw) {Pweight=pw;}
        void set_T_flag(int Tf) {T_flag=Tf;}
        void set_DiagonalQuad(void) {DiagonalQuad=false; df_flag=4; T_flag=0;}
        void set_linear(void) {DiagonalQuad=false; df_flag=0; T_flag=0;}
	void set_oldDefaults(void) { T_flag=1; df_flag=0; DiagonalQuad=false;}
	void verbose(void) {verb=true;}   // Output lots of extra info
        void suppressCCs(void) {reportCCs=false;}  // Suppress output of Correlation Cosine Updates.
    
// Called by UpdatePDFs:
    
        void ReadInTheoryAndData(void);
        void ConstructUpdateMatrix(void);
        void UpdateObservables(void);
    
// Called by OptimizePDFs:
    
        void ReadInTheory_Optimize(void);
        void ConstructOptimizeMatrix(void);
        void OptimizeObservables(void);

// Called by ConvertToleranceFile:
    
        void ConvertTolerance(const char* infile, const char* outfile);
    
// Called by PseudoData:  (This needs to be updated in order to be
    // consistent with current file formats.)
    
        void MakePseudoData(const char* Xfile, const char* Datafile);
    
// Called by InterpolatePDFs:
    
        void Interpolate(const char* PDFfile);
};


#endif


