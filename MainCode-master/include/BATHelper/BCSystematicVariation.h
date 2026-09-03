#ifndef BATHelper_BCSYSTEMATICVARIATION__H
#define BATHelper_BCSYSTEMATICVARIATION__H

#include <string>
#include <vector> 

#include "TF1.h"

class TH1D;

// ---------------------------------------------------------
class BCSystematicVariation
{
 public:
	
	// Constructors and destructor
	BCSystematicVariation(const char* channelname, const char* systematicname, int nprocesses);
	~BCSystematicVariation();
	
	// setters
	
	// set histogram
	void SetHistogramUp(int index, TH1D* hist)
	{ fHistogramUpContainer[index] = hist; }; 

	// set histogram
	void SetHistogramDown(int index, TH1D* hist)
	{ fHistogramDownContainer[index] = hist; }; 

	// set histogram
	void SetHistograms(int index, TH1D* hist_up, TH1D* hist_down)
	{ fHistogramUpContainer[index] = hist_up; 
		fHistogramDownContainer[index] = hist_down; }; 

        void SetFunctionContainers(int index,
                                  std::vector<TF1*>* funcVectContUp,
                                  std::vector<TF1*>* funcVectContDown);

	// getters

	// return histogram	
	TH1D* GetHistogramUp(int index)
	{ return fHistogramUpContainer.at(index); }; 

	// return histogram	
	TH1D* GetHistogramDown(int index)
	{ return fHistogramDownContainer.at(index); }; 

        //return vector of functions
        std::vector<TF1*>* GetFunctionVectorUpContainer(int index)
          { return fSystematicFunctionVectorUpContainer.at(index); };

        //return vector of functions
        std::vector<TF1*>* GetFunctionVectorDownContainer(int index)
          { return fSystematicFunctionVectorDownContainer.at(index); };

	// misc
	void AddHistogramUp(TH1D* hist)
	{ fHistogramUpContainer.push_back(hist); }; 

	// misc
	void AddHistogramDown(TH1D* hist)
	{ fHistogramDownContainer.push_back(hist); }; 

	// misc
	void AddHistograms(TH1D* hist_up, TH1D* hist_down)
	{ fHistogramUpContainer.push_back(hist_up); 
		fHistogramDownContainer.push_back(hist_down); }; 

 private:
	
	// a container of histograms
	std::vector<TH1D*> fHistogramUpContainer;

	// a container of histograms
	std::vector<TH1D*> fHistogramDownContainer;

        std::vector< std::vector<TF1*>* >
          fSystematicFunctionVectorUpContainer;
        std::vector< std::vector<TF1*>* >
          fSystematicFunctionVectorDownContainer;

	// channel name
	std::string fChannelName;
	
	// systematic name
	std::string fSystematicName;
	
};
// ---------------------------------------------------------

#endif

