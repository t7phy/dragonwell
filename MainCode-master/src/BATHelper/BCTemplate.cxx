#include "BATHelper/BCTemplate.h"

#include <TH1D.h>

// ---------------------------------------------------------
BCTemplate::BCTemplate(const char* channelname, const char* processname) : fEfficiency(0), fHistogram(0), fOriginalHistogram(0), fNBins(0)
{  
	fChannelName = channelname;
	fProcessName = processname;
        fFunctionContainer = new std::vector<TF1*>(0);
};

// ---------------------------------------------------------
BCTemplate::~BCTemplate()
{
	// debugKK
	//	if (fHistogram)
	//		delete fHistogram; 
};

// ---------------------------------------------------------
void BCTemplate::SetHistogram(TH1D* hist)
{
	fHistogram = hist; 
	if (hist)
		fNBins = fHistogram->GetNbinsX();

        if(hist) fExpectation = (TH1D *)fHistogram->Clone("");
        if(hist) fExpectation->Reset();
}; 

// ---------------------------------------------------------
void BCTemplate::SetFunctionContainer(std::vector<TF1*>* funccont, int nbins)
{
        fFunctionContainer = funccont;
        fNBins = nbins;
};
// ---------------------------------------------------------
