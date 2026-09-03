#ifndef BATHelper_BCTEMPLATE__H
#define BATHelper_BCTEMPLATE__H

#include <string>

#include <TF1.h>

class TH1D;

// ---------------------------------------------------------
class BCTemplate
{
 public:
	
	// Constructors and destructor
	BCTemplate(const char* channelname, const char* processname);
	~BCTemplate();
	
	// setters
	
	// set efficiency
	void SetEfficiency(double eff)
	{ fEfficiency = eff; }; 
	
	// set histogram
	void SetHistogram(TH1D* hist); 

        // set function container
        void SetFunctionContainer(std::vector<TF1*>* funccont, int nbins);
	
	// getters
	
	// return the name of the channel
	std::string GetChannelName() {
		return fChannelName; }; 

	// return the name of the process
	std::string GetProcessName() {
		return fProcessName; }; 

	// return efficiency
	double GetEfficiency()
	{ return fEfficiency; };

	// return histogram	
	TH1D* GetHistogram()
	{ return fHistogram; }; 

        std::vector<TF1*>* GetFunctionContainer()
          { return fFunctionContainer; };

	// return original histogram (not scaled to unity)
	TH1D* GetOriginalHistogram()
	{ return fOriginalHistogram; }; 

        // yfu 
        TH1D* GetExpectation()
        { return fExpectation;}

	// set original histogram (not scaled to unity)
	void SetOriginalHistogram(TH1D* hist)
	{ fOriginalHistogram = hist; }; 

	// return the number of bins
	int GetNBins()
	{ return fNBins; }; 

 private:

		// the efficiency of the contribution
		double fEfficiency; 

		// the template histogram
		TH1D* fHistogram;

		// the original template histogram (not scaled to unity)
		TH1D* fOriginalHistogram;

                // Expectation
                TH1D* fExpectation;

                // a histogram alternative for templates: a vector of TF1 functions
                std::vector<TF1*>* fFunctionContainer;

		// number of bins in the histogram
		int fNBins;

		// channel name
		std::string fChannelName;

		// process name
		std::string fProcessName;

};
// ---------------------------------------------------------

#endif

