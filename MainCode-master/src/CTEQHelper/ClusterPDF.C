#include "CTEQHelper/ClusterPDF.h"

ClusterPDF::ClusterPDF()
{
 DefineCombination();
 //PreparexFlavorVector();
 DefineMetaData();
}

void ClusterPDF::OutputTSV(TString name)
{
 ofstream datafile((name + ".tsv").Data());
 ofstream metadata((name + "_metadata.tsv").Data());
 ofstream datafile_RenyiEntropy((name + "_RenyiEntropy.tsv").Data());

 vector<double> ReferenceValues(xFlavorVector.size());
 for(int i = 0; i < xFlavorVector.size(); i++){
   double PDFValue = reference->xfxQ(get<0>(xFlavorVector.at(i)), get<1>(xFlavorVector.at(i)), get<2>(xFlavorVector.at(i))) / get<1>(xFlavorVector.at(i));
   if(fabs(PDFValue) < 1e-20){
     cout<<"flavor = "<<get<0>(xFlavorVector.at(i))<<"  x = "<<get<1>(xFlavorVector.at(i))<<"  Q = "<<get<2>(xFlavorVector.at(i))<<"  PDF = "<<PDFValue<<endl;
     cout<<"Change another x/flavor/Q"<<endl;
   }

   ReferenceValues.at(i) = PDFValue;

   cout<<"flavor = "<<get<0>(xFlavorVector.at(i))<<"  x = "<<get<1>(xFlavorVector.at(i))<<"  Q = "<<get<2>(xFlavorVector.at(i))<<"  PDF = "<<PDFValue<<endl;
 }

 for(int ipdf = 0; ipdf < PDFList.size(); ipdf++){
   for(int i = 0; i < xFlavorVector.size(); i++){
     double PDFValue = PDFList.at(ipdf)->xfxQ(get<0>(xFlavorVector.at(i)), get<1>(xFlavorVector.at(i)), get<2>(xFlavorVector.at(i))) / get<1>(xFlavorVector.at(i));
     if(fabs(PDFValue) < 1e-20){
       cout<<"PDFFile = "<<PDFFileNames.at(ipdf)<<"  flavor = "<<get<0>(xFlavorVector.at(i))<<"  x = "<<get<1>(xFlavorVector.at(i))<<"  Q = "<<get<2>(xFlavorVector.at(i))<<"  PDF = "<<PDFValue<<endl;
       cout<<"Change another x/flavor/Q"<<endl;
     }

     double RelativePDFValue = PDFValue / ReferenceValues.at(i);

     int width = 12;
     int precision = 10;

     if(RelativePDFValue < 0.0){
       width = 12;
       precision = 9;
     }
     datafile << setw(width) << fixed << setprecision(precision) << RelativePDFValue ;
     if(i != xFlavorVector.size() - 1) datafile << "\t";
   }
   datafile << endl;
 }

 metadata << "name\tChi2R\tChi2F\t";
 metadata << "dummy1\t";
 metadata << "dummy2\t";
 metadata << "dummy3\t";
 metadata << "dummy4\t";
 metadata << "dummy5\t";
 metadata << "dummy6\t";
 metadata << "dummy7\t";
 metadata << "dummy8\t";
 metadata << "dummy9\t";
 metadata << "dummy10";

 for(int iflavor = 0; iflavor < FlavorVector.size(); iflavor++){
   metadata << "\t" + FlavorVector.at(iflavor) + "(alpha2)";
 }
 for(int iflavor = 0; iflavor < FlavorVector.size(); iflavor++){
   metadata << "\t" + FlavorVector.at(iflavor) + "(alpha3)";
 }
 for(int iflavor = 0; iflavor < FlavorVector.size(); iflavor++){
   metadata << "\t" + FlavorVector.at(iflavor) + "(alpha4)";
 }
 metadata << endl;

 for(int ipdf = 0; ipdf < PDFList.size(); ipdf++){
   TString PDFName = PDFFileNames.at(ipdf);
   PDFName.ReplaceAll(".pds", "");
   PDFName.ReplaceAll("Input/", "");

   // Check consistency between PDF list and Summary list
   TString SumName = SummaryList.at(ipdf)->FileName;
   SumName.ReplaceAll(".sum", "");
   SumName.ReplaceAll("Input/", "");
   if(PDFName != SumName){
     cout<<"ERROR! The name in pdf.list and sum.list don't agree. PDFName = "<<PDFName<<" SumName = "<<SumName<<endl;
   }

   metadata << PDFName << "\t";
   metadata << setw(7) << fixed << setprecision(2) << SummaryList.at(ipdf)->Chi2R << "\t";
   metadata << setw(7) << fixed << setprecision(2) << SummaryList.at(ipdf)->Chi2F << "\t";
   metadata << "dummy1" << "\t";
   metadata << "dummy2" << "\t";
   metadata << "dummy3" << "\t";
   metadata << "dummy4" << "\t";
   metadata << "dummy5" << "\t";
   metadata << "dummy6" << "\t";
   metadata << "dummy7" << "\t";
   metadata << "dummy8" << "\t";
   metadata << "dummy9" << "\t";
   metadata << "dummy10";

   vector<double> RenyiEntropies_alpha2 = CalculateRenyiEntropy(ipdf, 2);

   for(int iflavor = 0; iflavor < FlavorVector.size(); iflavor++){
     double RenyiEntropy = RenyiEntropies_alpha2.at(iflavor);
     int width = 12;
     int precision = 10;
     metadata << "\t" << setw(width) << fixed << setprecision(precision) << RenyiEntropy;

     datafile_RenyiEntropy << setw(width) << fixed << setprecision(precision) << RenyiEntropy << "\t";
   }

   vector<double> RenyiEntropies_alpha3 = CalculateRenyiEntropy(ipdf, 3);

   for(int iflavor = 0; iflavor < FlavorVector.size(); iflavor++){
     double RenyiEntropy = RenyiEntropies_alpha3.at(iflavor);
     int width = 12;
     int precision = 10;
     metadata << "\t" << setw(width) << fixed << setprecision(precision) << RenyiEntropy;
     datafile_RenyiEntropy << setw(width) << fixed << setprecision(precision) << RenyiEntropy << "\t";
   }

   vector<double> RenyiEntropies_alpha4 = CalculateRenyiEntropy(ipdf, 4);

   for(int iflavor = 0; iflavor < FlavorVector.size(); iflavor++){
     double RenyiEntropy = RenyiEntropies_alpha4.at(iflavor);
     int width = 12;
     int precision = 10;
     metadata << "\t" << setw(width) << fixed << setprecision(precision) << RenyiEntropy;
     datafile_RenyiEntropy << setw(width) << fixed << setprecision(precision) << RenyiEntropy;
     if(iflavor != FlavorVector.size() - 1) datafile_RenyiEntropy << "\t";
   }

   metadata << endl;
   datafile_RenyiEntropy << endl;
 }

}

void ClusterPDF::OutputRenyiEntropy(TString name, int alpha)
{
 ofstream datafile((name + (TString)"_RenyiEntropy_alpha_" + alpha + (TString)".tsv").Data());

 for(int ipdf = 0; ipdf < PDFList.size(); ipdf++){

   vector<double> RenyiEntropies = CalculateRenyiEntropy(ipdf, alpha);

   for(int iflavor = 0; iflavor < RenyiEntropies.size(); iflavor++){

     double RenyiEntropy = RenyiEntropies.at(iflavor);

     int width = 12;
     int precision = 10;
     datafile << setw(width) << fixed << setprecision(precision) << RenyiEntropy;
     if(iflavor != FlavorVector.size() - 1) datafile << "\t";
   }

   datafile << endl;
 }

}

vector<double> ClusterPDF::CalculateRenyiEntropy(int ipdf, int alpha)
{
 vector<double> results;

 if(!isPrepareGaussPoints){
   cout<<"Call PrepareGaussPoints() at first!"<<endl;
   results = {};
   return results;
 }

 for(int iflavor = 0; iflavor < FlavorVector.size(); iflavor++){

   double SumValue = 0.0;
   for(int i = 0; i < xQVector.size(); i++){
     double PDFValue = PDFList.at(ipdf)->xfxQ(FlavorNameIndex.at(FlavorVector.at(iflavor)), get<0>(xQVector.at(i)), get<1>(xQVector.at(i))) / get<0>(xQVector.at(i));
     SumValue += PDFValue;
   }

   double Probability = 0.0;
   for(int i = 0; i < xQVector.size(); i++){
     double PDFValue = PDFList.at(ipdf)->xfxQ(FlavorNameIndex.at(FlavorVector.at(iflavor)), get<0>(xQVector.at(i)), get<1>(xQVector.at(i))) / get<0>(xQVector.at(i));

     Probability += pow(PDFValue / SumValue, alpha);
   }

   double RenyiEntropy = 1.0 / (1.0 - (double)alpha) * log(Probability);

   results.push_back(RenyiEntropy);
 }

 return results;
}

void ClusterPDF::InputReferencePDF(TString name)
{
 reference = new pdsReader();
 reference->Initialize(name);
}

void ClusterPDF::InputPDFList(vector<TString> list)
{
 PDFList.resize(list.size());
 for(int i = 0; i < list.size(); i++){
   PDFList.at(i) = new pdsReader();
   PDFList.at(i)->Initialize(list.at(i));
 }

 PDFFileNames = list;
}

void ClusterPDF::InputSummaryList(vector<TString> list)
{
 SummaryList.resize(list.size());
 for(int i = 0; i < list.size(); i++){
   SummaryList.at(i) = new sumReader();
   SummaryList.at(i)->Initialize(list.at(i));
 }

}

void ClusterPDF::PreparexFlavorVector()
{
 QVector = {1.3};
 xVector = Logspace(1e-5, 0.7, 10, 10);
 FlavorVector = {"gluon", "ubar", "dbar", "u", "d", "s"};

 for(int iq = 0; iq < QVector.size(); iq++){
   for(int iflavor = 0; iflavor < FlavorVector.size(); iflavor++){
     for(int ix = 0; ix < xVector.size(); ix++){
       xFlavorVector.push_back(make_tuple(FlavorNameIndex.at(FlavorVector.at(iflavor)), xVector.at(ix), QVector.at(iq)));
       //cout<<"x = "<<xVector.at(ix)<<" flavor = "<<FlavorNameIndex.at(FlavorVector.at(iflavor))<<" Q = "<<QVector.at(iq)<<endl;
     }
   }
 }

}

void ClusterPDF::PrepareGaussPoints(int n, double alpha, int nStripStart, int nStripEnd)
{
 Eigen::VectorXd x;
 Eigen::VectorXd w;

 x.resize(n);
 w.resize(n);

 Eigen::VectorXd beta(n - 1);

 for(int k = 1; k <= n - 1; ++k){
   beta(k - 1) = std::sqrt((double)k * k / (4.0 * k * k - 1.0));
 }

 Eigen::MatrixXd J = Eigen::MatrixXd::Zero(n, n);

 for(int k = 0; k < n - 1; ++k){
   J(k, k + 1) = beta(k);
   J(k + 1, k) = beta(k);
 }

 Eigen::SelfAdjointEigenSolver<Eigen::MatrixXd> es(J);

 x = es.eigenvalues();
 Eigen::MatrixXd V = es.eigenvectors();

 vector<double> Positive_x;
 for(int i = nStripStart; i < n - nStripEnd; i++){
   double Value = (1 + x(i)) / 2.0;

   Positive_x.push_back(pow(Value, 1.0 / alpha));
 }

 QVector = {1.3};
 xVector = Positive_x;

// xVector = {0.00001,0.00019985,0.00094316,0.0027079,0.0060262,0.011482,0.019702,0.031352,0.047132,0.067772,0.094031,0.1267,0.16658,0.21451,0.27135,0.33798,0.41529,0.5042,0.60565,0.7206};

// xVector = {0.00001,0.00068289,0.002411,0.0051943,0.0090329,0.013927,0.019876,0.02688,0.034939,0.044054,0.054224,0.065449,0.077729,0.091065,0.10546,0.1209,0.1374,0.15496,0.17357,0.19324,0.21396,0.23574,0.25857,0.28246,0.3074,0.3334,0.36045,0.38856,0.41773,0.44794,0.47922,0.51155,0.54493,0.57937,0.61487,0.65142,0.68902,0.72769,0.7674,0.80817};

 FlavorVector = {"gluon", "ubar", "dbar", "u", "d", "s"};

 for(int iq = 0; iq < QVector.size(); iq++){
   for(int iflavor = 0; iflavor < FlavorVector.size(); iflavor++){
     for(int ix = 0; ix < xVector.size(); ix++){
       xFlavorVector.push_back(make_tuple(FlavorNameIndex.at(FlavorVector.at(iflavor)), xVector.at(ix), QVector.at(iq)));
       //cout<<"x = "<<xVector.at(ix)<<" flavor = "<<FlavorNameIndex.at(FlavorVector.at(iflavor))<<" Q = "<<QVector.at(iq)<<endl;
     }
   }
 }

 for(int iq = 0; iq < QVector.size(); iq++){
   for(int ix = 0; ix < xVector.size(); ix++){
     xQVector.push_back(make_tuple(xVector.at(ix), QVector.at(iq)));
   }
 }

 isPrepareGaussPoints = true;
}

void ClusterPDF::DefineMetaData()
{

}

