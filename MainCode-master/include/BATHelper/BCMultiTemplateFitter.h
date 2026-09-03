#ifndef BATHelper_BCMULTITEMPLATEFITTER__H
#define BATHelper_BCMULTITEMPLATEFITTER__H

#include <BAT/BCModel.h>
#include <iostream>
#include <cstdlib>
#include "RootCommon.h"
#include "Tools/Tools.h"

class BCChannel;
class BCProcess;
class BCTemplate;
class BCSystematic; 

// ---------------------------------------------------------
class BCMultiTemplateFitter : public BCModel
{

	public:

		// Constructors and destructor
		BCMultiTemplateFitter();
		~BCMultiTemplateFitter();

		// setters

		// getters

		// return number of channels
		int GetNChannels()
		{ return fNChannels; }; 

		// return number of processes
		int GetNProcesses()
		{ return fNProcesses; }; 
		
		// return number of systematics
		int GetNSystematics()
		{ return fNSystematics; }; 

		// return channel index
		int GetChannelIndex(const char* name); 

		// return process index
		int GetProcessIndex(const char* name); 

		// return systematic index
		int GetSystematicIndex(const char* name); 

		// return parameter index of process
		int GetParIndexProcess(int index)
		{ return fProcessParIndexContainer.at(index); }; 

		// return parameter index of systematic
		int GetParIndexSystematic(int index)
		{ return fSystematicParIndexContainer.at(index); }; 

		// return a channel
		BCChannel* GetChannel(int index)
		{ return fChannelContainer.at(index); }; 

		// return a process
		BCProcess* GetProcess(int index)
		{ return fProcessContainer.at(index); }; 

		// return a systematic
		BCSystematic* GetSystematic(int index)
		{ return fSystematicContainer.at(index); };

		// misc

		// add a channel
		int AddChannel(const char* name); 
		
		// add a process
		int AddProcess(const char* name, double nmin = 0., double nmax = 1.); 

		// add a systematic uncertainty
		int AddSystematic(const char* name, double min = -5., double max = 5.);

		// set template
		int SetTemplate(const char* channelname, const char* processname, TH1D hist, double efficiency = 1.);

                // set template
                int SetTemplate(const char* channelname, const char* processname, std::vector<TF1*>* funccont, int nbins, double efficiency = 1.);

		// set systematic variation
		int SetSystematicVariation(const char* channelname, const char* processname,  const char* systematicname, TH1D hist_up, TH1D hist_down);

                // set systematic variation using a vector of functions
                int SetSystematicVariation(const char* channelname,
                                           const char* processname,
                                           const char* systematicname,
                                           std::vector<TF1*>* funcContUp,
                                           std::vector<TF1*>* funcContDown );

		// set systematic variation
		int SetSystematicVariation(const char* channelname, const char* processname,  const char* systematicname, TH1D hist, TH1D hist_up, TH1D hist_down);
		
                // set systematic variation using a vector of functions
                int SetSystematicVariation(const char* channelname,
                                           const char* processname,
                                           const char* systematicname,
                                           std::vector<TF1*>* func,
                                           std::vector<TF1*>* funcContUp,
                                           std::vector<TF1*>* funcContDown );

		// set data
		int SetData(const char* channelname, TH1D hist); 

		// set flag (efficiency constraint on (true) or off (false)
		void SetFlagEfficiencyConstraint(bool flag)
		{ fFlagEfficiencyConstraint = flag; }; 

		// set flag: log-normals = true, Gaussian = false
		void SetFlagDoLogNormal(bool flag) { 
		  if (fFlagFirstSysSet) {
		    std::cout << "\nERROR: log-normal switch must be set before any sysVariations are passed to the object\n\n";
		    exit(1);
		  }
		  if (flag)
		    std::cout << "\nUsing log-normal treatment of signal and background levels\n\n";
		  else
		    std::cout << "\nUsing Gaussian treatment of signal and background levels\n\n";
		  fFlagDoLogNormal = flag; 
		}; 

		//To turn on/off treatment of MC statistical errors
		void SetFlagDoStatErr(bool value);

		//Get stat err flag
		bool GetFlagDoStatErr()
		{ return fFlagDoStatErr; };

                // set a function for the expectation
                void SetExpectationFunction(int parindex, TF1* func)
                { fExpectationFunctionContainer[parindex] = func; };

		// print summary
		int PrintSummary(const char* filename = "summary.txt"); 

		// return expectation value for a channel and bin
		double Expectation(int channelindex, int binindex, const std::vector<double>& parameters); 

                // return a function for the expecation
                double ExpectationFunction(int parindex, int channelindex, int processindex, std::vector<double>& parameters);

		// return efficiency for a channel, process and bin
		double Efficiency(int channelindex, int processindex, int binindex, const std::vector<double>& parameters); 
		
		// return probability for a channel, process and bin
		double Probability(int channelindex, int processindex, int binindex, const std::vector<double>& parameters); 

		// print stack
		int PrintStack(int channelindex, std::vector<double> parameters, const char* filename = "stack.eps", const char* options = "");

		// print stack
		int PrintStack(const char* channelname, std::vector<double> parameters, const char* filename = "stack.eps", const char* options = "");

		// calculate chi2 for single channel
		double CalculateChi2(int channelindex, std::vector<double> parameters);

		// calculate chi2 for all channels
		double CalculateChi2(std::vector<double> parameters);

		// calculate Cash statistics for single channel 
		double CalculateCash(int channelindex, std::vector<double> parameters);

		// calculate Cash statistics for all channels
		double CalculateCash(std::vector<double> parameters);

		// BAT

		// the log likelihood
		double LogLikelihood(const std::vector <double>& parameters);

		//
		//significance stuff
		//
		double FrequentistLogLikelihood(const std::vector <double>& parameters);

		double significance(double maxSigmaSig, bool doingLEE = false, bool* success = NULL);

		double significance_withToys(double maxSigmaSig, int Ntoys, TH1* q0hist = NULL);

		std::vector<double>* getBestFitBonlyParameters(double maxSigmaSig);
		std::vector<double>* getBestFitSplusBparameters(double maxSigmaSig);

		void setDoingToys(bool value) {

		  if (value) { fDoingToys = true; nuisanceParameterOffsets = new std::vector<double>(fNSystematics); }
		  else if (fDoingToys) { fDoingToys = false; delete nuisanceParameterOffsets; }
		}

		void setNuisanceParameterOffset(int idx, double value) { (*nuisanceParameterOffsets)[idx] = value; }

    // void MCMCIterationInterface(); 

                //yfu----------------------------------------------------------------------------------------//
                int MCMCGetNParameters()
                { return GetNParameters(); }
                int MCMCGetNChains()
                { return fMCMCNChains;}
                int MCMCGetNIterationsConvergenceGlobal()
                { return fMCMCNIterationsConvergenceGlobal; }

                std::string DumpIntegrationMethod(BCIntegrate::BCIntegrationMethod type)
                {
                   switch(type) {
                      //case BCIntegrate::kIntMonteCarlo:
                      //   return "Sampled Mean Monte Carlo";
                      //case BCIntegrate::kIntImportance:
                      //   return "Importance Sampling";
                      //case BCIntegrate::kIntMetropolis:
                      //   return "Metropolis";
                      //case BCIntegrate::kIntCuba:
                      //   return "Cuba";
                      default:
                         return "Undefined";
                   }
                }

                BCIntegrate::BCIntegrationMethod fIntegrationMethod;
                std::string DumpIntegrationMethod()
                { return DumpIntegrationMethod(fIntegrationMethod); }

                void PrintResults(const char * file);
                int SetParameterRange(int index, double parmin, double parmax);

                std::vector<double> GetFittedParameters(){
                  std::vector<double> vec;
                  for(int i = 0; i < GetNParameters(); i++){
                    vec.push_back(GetFittedParameter(i));
                  }
                  return vec;
                }

                double GetFittedParameter(int index){
                  if(GetParameter(index).Fixed()){
                    return GetParameter(index).GetFixedValue();
                  }
                  else{
                    BCH1D hist = GetMarginalized(index);
                    return hist.GetLocalMode();
                  }
                }

                bool isAddAFBPenalty = false;
                TString FChannelName = "", BChannelName = "";
                void AddAFBPenalty(TString FChannelName, TString BChannelName);
                double CalcAFBPenalty(TString FChannelName, TString BChannelName, const std::vector<double>& parameters);
                //-------------------------------------------------------------------------------------------//

 private:

		// a container of channels
		std::vector<BCChannel*> fChannelContainer;

		// a container of processes
		std::vector<BCProcess*> fProcessContainer;

		// a container of systematic sources
		std::vector<BCSystematic*> fSystematicContainer;

		// number of channels
		int fNChannels;

		// number of processes
		int fNProcesses;

		// number of systematics
		int fNSystematics;

		// a container of parameter indeces for the process normalization
		std::vector<int> fProcessParIndexContainer; 

		// a container of parameter indeces for the systematics
		std::vector<int> fSystematicParIndexContainer; 

		// flag: efficiency within 0 and 1 (true) or not (false)
		bool fFlagEfficiencyConstraint;

                // a container of functions for the expectation
                std::vector<TF1*> fExpectationFunctionContainer;

		// flag: whether to use a log-normal description
		bool fFlagDoLogNormal;

		// flag: whether any sysVariation has already been passed to the object
		bool fFlagFirstSysSet;

		//for running frequentist pseudo-experiments
		bool fDoingToys;
		std::vector<double>* nuisanceParameterOffsets;

		// flag: whether to use MC statistical uncertainty
		bool fFlagDoStatErr;
};
// ---------------------------------------------------------

#endif

