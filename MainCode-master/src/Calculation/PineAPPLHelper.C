#include "Calculation/PineAPPLHelper.h"

PineAPPLHelper::PineAPPLHelper()
{
}

void PineAPPLHelper::InitialPDF(TString PDFName, int iSet)
{
#ifdef USE_LHAPDF
 m_PDF1 = std::unique_ptr<LHAPDF::PDF>(LHAPDF::mkPDF(PDFName.Data(), iSet));
 m_PDF2 = std::unique_ptr<LHAPDF::PDF>(LHAPDF::mkPDF(PDFName.Data(), iSet));

 m_PDFs = {m_PDF1.get(), m_PDF2.get()};
 pdf_states = reinterpret_cast<void**>(m_PDFs.data());
#endif

 PDFType = PDFTypeEnum::CT_LHAPDF;
}

void PineAPPLHelper::InitialCTEQPDF(pdsReader* pdf)
{
 m_CTEQPDF1 = std::make_unique<pdsReader>();
 m_CTEQPDF1->CopyHeader(pdf);
 m_CTEQPDF1->InputAlphaS(pdf->AlsCTEQ);
 m_CTEQPDF1->InputUPD(pdf->UPD);

 m_CTEQPDF2 = std::make_unique<pdsReader>();
 m_CTEQPDF2->CopyHeader(pdf);
 m_CTEQPDF2->InputAlphaS(pdf->AlsCTEQ);
 m_CTEQPDF2->InputUPD(pdf->UPD);

 m_CTEQPDFs = {m_CTEQPDF1.get(), m_CTEQPDF2.get()};
 pdf_states = reinterpret_cast<void**>(m_CTEQPDFs.data());

 PDFType = PDFTypeEnum::CT_CTEQTable;
}

void PineAPPLHelper::InitialCTEQPDF(TString PDFFile)
{
 m_CTEQPDF1 = std::make_unique<pdsReader>();
 m_CTEQPDF1->Initialize(PDFFile);

 m_CTEQPDF2 = std::make_unique<pdsReader>();
 m_CTEQPDF2->Initialize(PDFFile);

 m_CTEQPDFs = {m_CTEQPDF1.get(), m_CTEQPDF2.get()};
 pdf_states = reinterpret_cast<void**>(m_CTEQPDFs.data());

 PDFType = PDFTypeEnum::CT_CTEQTable;
}

void PineAPPLHelper::InitialGrid(TString GridName)
{
 this->GridName = GridName;

#ifdef USE_PINEAPPL
 grid = pineappl_grid_read(GridName.Data());

 // how many bins does this grid have?
 nPoints = pineappl_grid_bin_count(grid);

 // how many dimensions does each bin have?
 nDim = pineappl_grid_bin_dimensions(grid);

 // allocate a vector holding the left and right bin limits for each dimension
 bin_limits.resize(2 * nPoints * nDim);

 for(std::size_t dim = 0; dim != nDim; ++dim){
   pineappl_grid_bin_limits_left(grid, dim, &bin_limits.at((2 * dim + 0) * nPoints));
   pineappl_grid_bin_limits_right(grid, dim, &bin_limits.at((2 * dim + 1) * nPoints));
 }

 binx_left.resize(nPoints);
 binx_right.resize(nPoints);
 biny_left.resize(nPoints);
 biny_right.resize(nPoints);
 binz_left.resize(nPoints);
 binz_right.resize(nPoints);

 if(nDim > 3){
   cout<<"The dimensions of input grid is greater than 3, be careful of the binning. ndims = "<<nDim<<endl;
 }

 for (std::size_t bin = 0; bin != nPoints; ++bin) {
   for (std::size_t dim = 0; dim != nDim; ++dim) {
     double left_limit = bin_limits.at((2 * dim + 0) * nPoints + bin);
     double right_limit = bin_limits.at((2 * dim + 1) * nPoints + bin);

     if(dim == 0) binx_left.at(bin) = left_limit;
     if(dim == 0) binx_right.at(bin) = right_limit;
     if(dim == 1) biny_left.at(bin) = left_limit;
     if(dim == 1) biny_right.at(bin) = right_limit;
     if(dim == 2) binz_left.at(bin) = left_limit;
     if(dim == 2) binz_right.at(bin) = right_limit;

   }
   if(nDim >= 1) cout<<"binx left = "<<setw(10)<<fixed<<setprecision(2)<<binx_left.at(bin)<<"  binx right = "<<setw(10)<<fixed<<setprecision(2)<<binx_right.at(bin)<<endl;
   if(nDim >= 2) cout<<"biny left = "<<setw(10)<<fixed<<setprecision(2)<<biny_left.at(bin)<<"  biny right = "<<setw(10)<<fixed<<setprecision(2)<<biny_right.at(bin)<<endl;
   if(nDim >= 3) cout<<"binz left = "<<setw(10)<<fixed<<setprecision(2)<<binz_left.at(bin)<<"  binz right = "<<setw(10)<<fixed<<setprecision(2)<<binz_right.at(bin)<<endl;
 }

 std::cout.unsetf(std::ios::floatfield);
 std::cout.precision(6);

 // allocate a vector holding the differential cross sections
 results.resize(nPoints);

 // how many perturbative orders does the grid contain?
 orders = pineappl_grid_order_count(grid);

 std::vector<std::uint32_t> order_params(4 * orders);
 // read out all exponents of the perturbative orders in the grid
 pineappl_grid_order_params(grid, order_params.data());

    for (std::size_t order = 0; order != orders; ++order) {
        std::cout << std::setw(4) << order << ' ';

        // exponent of the strong coupling
        std::uint32_t exp_as = order_params.at(4 * order + 0);
        // exponent of the electromagnetic/electroweak coupling
        std::uint32_t exp_al = order_params.at(4 * order + 1);
        // exponent of the renormalization log
        std::uint32_t exp_lr = order_params.at(4 * order + 2);
        // exponent of the factorization log
        std::uint32_t exp_lf = order_params.at(4 * order + 3);

        std::cout << "O(as^" << exp_as << " a^" << exp_al << " lr^" << exp_lr << " lf^" << exp_lf
            << ")\n";
    }

 // how many channels does the grid have?
 channels = pineappl_grid_channels(grid);
 channels_length = pineappl_channels_count(channels);

 /*
   // How many convolutions are there?
   auto n_conv = pineappl_grid_convolutions_len(grid);

   for (std::size_t channel = 0; channel != channels_length; ++channel) {
        // print channel index
        std::cout << std::setw(4) << channel << ' ';

        // how many partonic combinations does this channel have?
        auto combinations = pineappl_channels_combinations(channels, channel);

        std::vector<double> factors(combinations);
        std::vector<int> pids(n_conv * combinations);

        // read out the channel with index given by `channel`, writing the particle identifiers into
        // `pids` and the corresponding factors into `factors`
        pineappl_channels_entry(channels, channel, pids.data(), factors.data());

        for (std::size_t combination = 0; combination != combinations; ++combination) {
            auto factor = factors.at(combination);
            auto pida = pids.at(2 * combination + 0);
            auto pidb = pids.at(2 * combination + 1);

            if (combination != 0) {
                std::cout << " + ";
            }

            // print factor and particle ids
            std::cout << factor << " x (" << std::setw(3) << pida << ',' << std::setw(4) << pidb
                << ")";
        }

        std::cout << '\n';
    }
 */

 // std::vector<bool> doesn't have `.data()` member
 order_mask = std::make_unique<bool[]>(orders);
 std::fill_n(order_mask.get(), orders, false);

 channel_mask = std::make_unique<bool[]>(channels_length);
 std::fill_n(channel_mask.get(), channels_length, true);

 cout<<LOG_INFO<<"Initialize Grid done."<<endl;
 cout<<LOG_INFO<<"Grid name: "<<GridName<<endl;
 cout<<LOG_INFO<<"orders = "<<orders<<endl;
 cout<<LOG_INFO<<"channels = "<<channels_length<<endl;
#endif
}

vector<double> PineAPPLHelper::Convolute()
{
#ifdef USE_PINEAPPL
 // use the variables to select the included orders and channels

 if(nHardOrder >= 0) order_mask[0] = true;

 if(nHardOrder >= 1) order_mask[1] = true;

 if(nHardOrder >= 2) order_mask[4] = true;

 // use these variables to perform scale variations
 double xir = 1.0;
 double xif = 1.0;
 double xia = 1.0;

 std::vector<double> mu_scales = { xir, xif, xia };

 if(PDFType == PDFTypeEnum::CT_LHAPDF){
#ifdef USE_LHAPDF
   auto xfx1 = [](int32_t id, double x, double q2, void* pdf) {
     return static_cast <LHAPDF::PDF*> (pdf)->xfxQ2(id, x, q2);
   };

   auto xfx2 = [](int32_t id, double x, double q2, void* pdf) {
     return static_cast <LHAPDF::PDF*> (pdf)->xfxQ2(id * (-1), x, q2);
   };

   auto alphas = [](double q2, void* pdf) {
     return static_cast <LHAPDF::PDF*> (pdf)->alphasQ2(q2);
   };

   pineappl_grid_convolve(grid,
                          xfx1,
                        alphas,
                    pdf_states,
                  m_PDF1.get(),
              order_mask.get(),
            channel_mask.get(),
                       nullptr,
                             1,
              mu_scales.data(),
                results.data());
#endif
 }
 else if(PDFType == PDFTypeEnum::CT_CTEQTable){
   //if(abs(id) >= 4){
   //  if(sqrt(q2) > Amhat(abs(id))) Value = static_cast <pdsReader*> (pdf)->xfxQ(id, x, sqrt(q2));
   //}        
   //else{  
   //  Value = static_cast <pdsReader*> (pdf)->xfxQ(id, x, sqrt(q2));
   //}            

   auto xfx1 = [](int32_t id, double x, double q2, void* pdf) {
     return static_cast <pdsReader*> (pdf)->xfxQ(id, x, sqrt(q2));
   };

   auto xfx2 = [](int32_t id, double x, double q2, void* pdf) {
     return static_cast <pdsReader*> (pdf)->xfxQ(id * (-1), x, sqrt(q2));
   };

   auto alphas = [](double q2, void* pdf) {
     return static_cast <pdsReader*> (pdf)->CT14Alphas(sqrt(q2));
   };

   pineappl_grid_convolve(grid,
                          xfx1,
                        alphas,
                    pdf_states,
              m_CTEQPDF1.get(),
              order_mask.get(),
            channel_mask.get(),
                       nullptr,
                             1,
              mu_scales.data(),
                results.data());
 }

#endif

 order_mask[0] = false;
 order_mask[1] = false;
 order_mask[4] = false;

 return results;
}

vector<double> PineAPPLHelper::Convoluteppbar()
{
 cout<<"Not Finished! Do not call this function!"<<endl;

#ifdef USE_PINEAPPL
 // use the variables to select the included orders and channels
 order_mask[0] = true;
 order_mask[1] = true;
 order_mask[4] = true;

 // use these variables to perform scale variations
 double xir = 1.0;
 double xif = 1.0;
 double xia = 1.0;

 std::vector<double> mu_scales = { xir, xif, xia };

 if(PDFType == PDFTypeEnum::CT_LHAPDF){
#ifdef USE_LHAPDF
   auto xfx1 = [](int32_t id, double x, double q2, void* pdf) {
     return static_cast <LHAPDF::PDF*> (pdf)->xfxQ2(id, x, q2);
   };

   auto xfx2 = [](int32_t id, double x, double q2, void* pdf) {
     return static_cast <LHAPDF::PDF*> (pdf)->xfxQ2(id * (-1), x, q2);
   };

   auto alphas = [](double q2, void* pdf) {
     return static_cast <LHAPDF::PDF*> (pdf)->alphasQ2(q2);
   };

   pineappl_grid_convolve(grid,
                          xfx1,
                        alphas,
                    pdf_states,
                  m_PDF1.get(),
              order_mask.get(),
            channel_mask.get(),
                       nullptr,
                             1,
              mu_scales.data(),
                results.data());
#endif
 }
 else if(PDFType == PDFTypeEnum::CT_CTEQTable){
   auto xfx1 = [](int32_t id, double x, double q2, void* pdf) {
     return static_cast <pdsReader*> (pdf)->xfxQ(id, x, sqrt(q2));
   };

   auto xfx2 = [](int32_t id, double x, double q2, void* pdf) {
     return static_cast <pdsReader*> (pdf)->xfxQ(id * (-1), x, sqrt(q2));
   };

   auto alphas = [](double q2, void* pdf) {
     return static_cast <pdsReader*> (pdf)->CT14Alphas(sqrt(q2));
   };

   pineappl_grid_convolve(grid,
                          xfx1,
                        alphas,
                    pdf_states,
              m_CTEQPDF1.get(),
              order_mask.get(),
            channel_mask.get(),
                       nullptr,
                             1,
              mu_scales.data(),
                results.data());
 }
#endif

 order_mask[0] = false;
 order_mask[1] = false;
 order_mask[4] = false;

 return results;
}

void PineAPPLHelper::DefaultConvolute()
{
 results = Convolute();

 if(nDim == 1){
   for(int i = 0; i < results.size(); i++){
     cout<<"binx:["<<setw(7)<<fixed<<setprecision(2)<<binx_left.at(i)<<", "<<setw(7)<<binx_right.at(i)<<"]: ";
     cout<<setw(10)<<fixed<<setprecision(6)<<results.at(i)<<endl;
   }
 }
 else if(nDim == 2){
   for(int i = 0; i < results.size(); i++){
     cout<<"binx:["<<setw(7)<<fixed<<setprecision(2)<<binx_left.at(i)<<", "<<setw(7)<<binx_right.at(i)<<"], ";
     cout<<"biny:["<<setw(7)<<fixed<<setprecision(2)<<biny_left.at(i)<<", "<<setw(7)<<biny_right.at(i)<<"]: ";
     cout<<setw(10)<<fixed<<setprecision(6)<<results.at(i)<<endl;
   }
 }
 else if(nDim == 3){
   for(int i = 0; i < results.size(); i++){
     cout<<"binx:["<<setw(7)<<fixed<<setprecision(2)<<binx_left.at(i)<<", "<<setw(7)<<binx_right.at(i)<<"], ";
     cout<<"biny:["<<setw(7)<<fixed<<setprecision(2)<<biny_left.at(i)<<", "<<setw(7)<<biny_right.at(i)<<"], ";
     cout<<"binz:["<<setw(7)<<fixed<<setprecision(2)<<binz_left.at(i)<<", "<<setw(7)<<binz_right.at(i)<<"]: ";
     cout<<setw(10)<<fixed<<setprecision(6)<<results.at(i)<<endl;
   }
 }

 std::cout.unsetf(std::ios::floatfield);
 std::cout.precision(6);

}
