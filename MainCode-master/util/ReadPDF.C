#include "RootCommon.h"
#include "CTEQHelper/pdsReader.h"
#include "PDFHelper/PDFFigure.h"
#include "PDFHelper/PDFHelper.h"

using namespace std;

int main(int argc, char** argv)
{
// if(argc != 2){
//   cout<<"usage: ReadPDF filename"<<endl;
//   return 0;
// }


 pdsReader pdf;
 pdf.Initialize(argv[1]);
// cout<<pdf.CT14Alphas(91.187)<<endl;
 int flavor = stoi(argv[2]);
 double x = stod(argv[3]);
 double Q = stod(argv[4]);
 cout<<fixed<<setprecision(14)<<pdf.CT14PDF(flavor, x, Q)<<endl;

 PDFHelper lha;
 //lha.InitialPDF("CT18ANNLO_moreX", 58);

 PDFHelper lha2;
 //lha2.InitialPDF("CT18ANNLO_TieJiun", 58);

// pdf.FromLHAtoUPD("CT18NNLO", 0);
// pdf.l2pFullSet("MSHT20nnlo_as118", 64);


/* vector<TString> PDFList;
 TString PDFName;

 ifstream infile;
  infile.open(argv[1], ios::in);

 while(infile >> PDFName){
   PDFList.push_back(PDFName);
 }

 PDFFigure* data = new PDFFigure();
 data->InitialCTEQPDFSets(1, PDFList, "CT18NNLO");
 cout<<"u: "<<data->GetfError("CT18NNLO", 2, 0.0001, 91.1876, "Symmetry")<<endl;
 cout<<"d: "<<data->GetfError("CT18NNLO", 1, 0.0001, 91.1876, "Symmetry")<<endl;
 cout<<"ubar/u: "<<data->GetfError("CT18NNLO", 18, 0.0001, 91.1876, "Symmetry")<<endl;
 cout<<"dbar/d: "<<data->GetfError("CT18NNLO", 19, 0.0001, 91.1876, "Symmetry")<<endl;
 cout<<"dv-uv: "<<data->GetfError("CT18NNLO", 20, 0.0001, 91.1876, "Symmetry")<<endl;
*/








// double Q = 1.047120E+02;

 vector<double> XVector;

// for(int i = 0; i < 100; i++){
//   XVector.push_back(pow(10, (5.0 / 3.0) * log10((i + 1) / 100.0)));
// }

 XVector = {1.000E-08, 1.786E-06, 1.081E-05, 3.304E-05, 7.445E-05, 1.410E-04, 2.386E-04, 3.733E-04, 
            5.510E-04, 7.777E-04, 1.059E-03, 1.402E-03, 1.811E-03, 2.293E-03, 2.854E-03, 3.500E-03,
            4.237E-03, 5.070E-03, 6.005E-03, 7.050E-03, 8.209E-03, 9.488E-03, 1.089E-02, 1.243E-02,
            1.411E-02, 1.593E-02, 1.790E-02, 2.003E-02, 2.232E-02, 2.478E-02, 2.741E-02, 3.022E-02,
            3.322E-02, 3.641E-02, 3.980E-02, 4.339E-02, 4.719E-02, 5.121E-02, 5.545E-02, 5.992E-02,
            6.462E-02, 6.956E-02, 7.475E-02, 8.019E-02, 8.589E-02, 9.185E-02, 9.808E-02, 1.046E-01,
            1.114E-01, 1.184E-01, 1.258E-01, 1.335E-01, 1.414E-01, 1.497E-01, 1.583E-01, 1.673E-01,
            1.765E-01, 1.861E-01, 1.960E-01, 2.063E-01, 2.169E-01, 2.279E-01, 2.393E-01, 2.510E-01,
            2.631E-01, 2.756E-01, 2.885E-01, 3.017E-01, 3.154E-01, 3.295E-01, 3.440E-01, 3.589E-01,
            3.742E-01, 3.899E-01, 4.061E-01, 4.228E-01, 4.399E-01, 4.574E-01, 4.754E-01, 4.939E-01,
            5.128E-01, 5.322E-01, 5.522E-01, 5.725E-01, 5.934E-01, 6.148E-01, 6.367E-01, 6.591E-01,
            6.821E-01, 7.055E-01, 7.295E-01, 7.541E-01, 7.791E-01, 8.047E-01, 8.309E-01, 8.577E-01,
            8.850E-01, 9.129E-01, 9.413E-01, 9.704E-01};

 XVector = {9.261360E-10, 1.131185E-09, 1.381633E-09, 1.687530E-09, 2.061154E-09, 2.517499E-09, 3.074880E-09,
            3.755667E-09, 4.587182E-09, 5.602796E-09, 6.843271E-09, 8.358390E-09, 1.020896E-08, 1.246925E-08,
            1.522998E-08, 1.860194E-08, 2.272046E-08, 2.775083E-08, 3.389494E-08, 4.139938E-08, 5.056531E-08,
            6.176061E-08, 7.543458E-08, 9.213601E-08, 1.125352E-07, 1.374508E-07, 1.678828E-07, 2.050525E-07,
            2.504516E-07, 3.059023E-07, 3.736299E-07, 4.563526E-07, 5.573904E-07, 6.807981E-07, 8.315287E-07,
            1.015631E-06, 1.240495E-06, 1.515144E-06, 1.850601E-06, 2.260329E-06, 2.760773E-06, 3.372015E-06,
            4.118589E-06, 5.030456E-06, 6.144212E-06, 7.504558E-06, 9.166088E-06, 1.119548E-05, 1.367420E-05,
            1.670170E-05, 2.039950E-05, 2.491601E-05, 3.043248E-05, 3.717032E-05, 4.539993E-05, 5.545160E-05,
            6.772874E-05, 8.272407E-05, 1.010394E-04, 1.234098E-04, 1.507331E-04, 1.841058E-04, 2.248673E-04,
            2.746536E-04, 3.354626E-04, 4.097350E-04, 5.004514E-04, 6.112528E-04, 7.465858E-04, 9.118820E-04,
            1.113775E-03, 1.360368E-03, 1.661557E-03, 2.029431E-03, 2.478752E-03, 3.027555E-03, 3.697864E-03,
            4.516581E-03, 5.516564E-03, 6.737947E-03, 8.229747E-03, 1.005184E-02, 1.227734E-02, 1.499558E-02,
            1.831564E-02, 2.237077E-02, 2.732372E-02, 3.337327E-02, 4.076220E-02, 4.978707E-02, 6.081006E-02,
            7.427358E-02, 9.071795E-02, 1.108032E-01, 1.353353E-01, 1.446652E-01, 1.546383E-01, 1.652989E-01,
            1.766944E-01, 1.888756E-01, 2.018965E-01, 2.158151E-01, 2.306932E-01, 2.465970E-01, 2.635971E-01,
            2.817693E-01, 3.011942E-01, 3.219583E-01, 3.441538E-01, 3.678794E-01, 3.932407E-01, 4.203504E-01,
            4.493290E-01, 4.803053E-01, 5.134171E-01, 5.488116E-01, 5.611440E-01, 5.737534E-01, 5.866462E-01,
            5.998287E-01, 6.133075E-01, 6.270891E-01, 6.411804E-01, 6.555883E-01, 6.703200E-01, 6.853828E-01,
            7.007840E-01, 7.165313E-01, 7.326325E-01, 7.490954E-01, 7.659283E-01, 7.831395E-01, 8.007374E-01,
            8.187308E-01, 8.248179E-01, 8.309504E-01, 8.371284E-01, 8.433524E-01, 8.496227E-01, 8.559395E-01,
            8.623034E-01, 8.687145E-01, 8.751733E-01, 8.816802E-01, 8.882354E-01, 8.948393E-01, 9.014924E-01,
            9.081949E-01, 9.149472E-01, 9.217498E-01, 9.286029E-01, 9.355070E-01, 9.424624E-01, 9.494695E-01,
            9.565287E-01, 9.636404E-01, 9.708050E-01, 9.780229E-01, 9.852944E-01, 9.926200E-01, 1.000000E+00};

//   cout<<*right<<setw(10)<<fixed<<setprecision(6)<<" u:"<<pdf.Getf(2, 0.01, 100.0) * 0.01<<" lha:"<<lha.Getf(2, 0.01, 100.0) * 0.01<<endl;

/* cout<<"Q = "<<Q<<endl;
 for(int i = 0; i < XVector.size(); i++){
   cout<<*right<<setw(10)<<fixed<<setprecision(6)<<"x: "<<XVector.at(i);
   cout<<*right<<setw(10)<<fixed<<setprecision(6)<<" u(wrong):"<<lha.Getf(2, XVector.at(i), Q) * XVector.at(i);
   cout<<*right<<setw(10)<<fixed<<setprecision(6)<<" u(right):"<<lha2.Getf(2, XVector.at(i), Q) * XVector.at(i);
   cout<<*right<<setw(10)<<fixed<<setprecision(6)<<" dbar(wrong):"<<lha.Getf(-1, XVector.at(i), Q) * XVector.at(i);
   cout<<*right<<setw(10)<<fixed<<setprecision(6)<<" dbar(right):"<<lha2.Getf(-1, XVector.at(i), Q) * XVector.at(i);
   cout<<*right<<setw(10)<<fixed<<setprecision(6)<<" g(wrong):"<<lha.Getf(0, XVector.at(i), Q) * XVector.at(i);
   cout<<*right<<setw(10)<<fixed<<setprecision(6)<<" g(right):"<<lha2.Getf(0, XVector.at(i), Q) * XVector.at(i);
   cout<<endl;
 }

 Q = 1.3;
 cout<<"Q = "<<Q<<endl;
 for(int i = 0; i < XVector.size(); i++){
   cout<<*right<<setw(10)<<fixed<<setprecision(6)<<"x: "<<XVector.at(i);
   cout<<*right<<setw(10)<<fixed<<setprecision(6)<<" u(wrong):"<<lha.Getf(2, XVector.at(i), Q) * XVector.at(i);
   cout<<*right<<setw(10)<<fixed<<setprecision(6)<<" u(right):"<<lha2.Getf(2, XVector.at(i), Q) * XVector.at(i);
   cout<<*right<<setw(10)<<fixed<<setprecision(6)<<" dbar(wrong):"<<lha.Getf(-1, XVector.at(i), Q) * XVector.at(i);
   cout<<*right<<setw(10)<<fixed<<setprecision(6)<<" dbar(right):"<<lha2.Getf(-1, XVector.at(i), Q) * XVector.at(i);
   cout<<*right<<setw(10)<<fixed<<setprecision(6)<<" g(wrong):"<<lha.Getf(0, XVector.at(i), Q) * XVector.at(i);
   cout<<*right<<setw(10)<<fixed<<setprecision(6)<<" g(right):"<<lha2.Getf(0, XVector.at(i), Q) * XVector.at(i);
   cout<<endl;
 }
*/

/* for(int i = 0; i < XVector.size(); i++){
   //cout<<*right<<setw(10)<<fixed<<setprecision(6)<<"x: "<<XVector.at(i);
   //cout<<*right<<setw(10)<<fixed<<setprecision(6)<<" c:"<<pdf.Getf(4, XVector.at(i), Q) * XVector.at(i);
   //cout<<*right<<setw(10)<<fixed<<setprecision(6)<<" cbar:"<<pdf.Getf(-4, XVector.at(i), Q) * XVector.at(i);
   //cout<<*right<<setw(10)<<fixed<<setprecision(6)<<" s:"<<pdf.Getf(3, XVector.at(i), Q) * XVector.at(i);
   //cout<<*right<<setw(10)<<fixed<<setprecision(6)<<" sbar:"<<pdf.Getf(-3, XVector.at(i), Q) * XVector.at(i);
   //cout<<endl;
   cout<<*right<<setw(10)<<fixed<<setprecision(6)<<"x: "<<XVector.at(i);
   cout<<*right<<setw(10)<<fixed<<setprecision(6)<<" u:"<<pdf.Getf(2, XVector.at(i), Q) * XVector.at(i)<<" lha:"<<lha.Getf(2, XVector.at(i), Q) * XVector.at(i);
   cout<<*right<<setw(10)<<fixed<<setprecision(6)<<" ubar:"<<pdf.Getf(-2, XVector.at(i), Q) * XVector.at(i)<<" lha:"<<lha.Getf(-2, XVector.at(i), Q) * XVector.at(i);
   cout<<*right<<setw(10)<<fixed<<setprecision(6)<<" d:"<<pdf.Getf(1, XVector.at(i), Q) * XVector.at(i)<<" lha:"<<lha.Getf(1, XVector.at(i), Q) * XVector.at(i);
   cout<<*right<<setw(10)<<fixed<<setprecision(6)<<" dbar:"<<pdf.Getf(-1, XVector.at(i), Q) * XVector.at(i)<<" lha:"<<lha.Getf(-1, XVector.at(i), Q) * XVector.at(i);
   cout<<endl;
 }
*/
/* for(int i = 0; i < XVector.size(); i++){
   cout<<*right<<setw(10)<<fixed<<setprecision(6)<<"x: "<<XVector.at(i);
   cout<<*right<<setw(10)<<fixed<<setprecision(6)<<" c:"<<lha.Getf(4, XVector.at(i), Q) * XVector.at(i);
   cout<<*right<<setw(10)<<fixed<<setprecision(6)<<" cbar:"<<lha.Getf(-4, XVector.at(i), Q) * XVector.at(i);
   cout<<*right<<setw(10)<<fixed<<setprecision(6)<<" s:"<<lha.Getf(3, XVector.at(i), Q) * XVector.at(i);
   cout<<*right<<setw(10)<<fixed<<setprecision(6)<<" sbar:"<<lha.Getf(-3, XVector.at(i), Q) * XVector.at(i);
   cout<<endl;
   cout<<*right<<setw(10)<<fixed<<setprecision(6)<<"x: "<<XVector.at(i);
   cout<<*right<<setw(10)<<fixed<<setprecision(6)<<" u:"<<lha.Getf(2, XVector.at(i), Q) * XVector.at(i);
   cout<<*right<<setw(10)<<fixed<<setprecision(6)<<" ubar:"<<lha.Getf(-2, XVector.at(i), Q) * XVector.at(i);
   cout<<*right<<setw(10)<<fixed<<setprecision(6)<<" d:"<<lha.Getf(1, XVector.at(i), Q) * XVector.at(i);
   cout<<*right<<setw(10)<<fixed<<setprecision(6)<<" dbar:"<<lha.Getf(-1, XVector.at(i), Q) * XVector.at(i);
   cout<<endl;
 }
*/

 return 1;
}
