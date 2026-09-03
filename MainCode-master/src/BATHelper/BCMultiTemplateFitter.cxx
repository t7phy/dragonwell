#include "BATHelper/BCMultiTemplateFitter.h"
#include "BATHelper/BCChannel.h"
#include "BATHelper/BCProcess.h"
#include "BATHelper/BCTemplate.h"
#include "BATHelper/BCSystematic.h"
#include "BATHelper/BCSystematicVariation.h"
#include "BATHelper/BCMTFAnalysisFacility.h"

#include <BAT/BCMath.h>
#include <BAT/BCLog.h>

#include <TCanvas.h>
#include <THStack.h>
#include <TH1D.h>
#include <TAxis.h> 
#include <TMath.h>
#include <TMinuit.h>
#include <TRandom3.h>

#include <iostream>
#include <fstream>

using namespace std;



//Global pointer and function needed by Minuit for significance calculation

BCMultiTemplateFitter* globalBCMTFpointer;

void MinusFrequentistLogLikelihoodWrapper(Int_t &npar, Double_t *gin, Double_t &f, Double_t *par, Int_t iflag) {

  std::vector<double> parameters;
  parameters.clear();

  for (int i = 0; i < globalBCMTFpointer->GetNSystematics() + globalBCMTFpointer->GetNProcesses(); i++)
    parameters.push_back(par[i]);

  f = -globalBCMTFpointer->FrequentistLogLikelihood(parameters);
}


//Class implementation

// ---------------------------------------------------------
BCMultiTemplateFitter::BCMultiTemplateFitter() : BCModel()
					       , fNChannels(0)
					       , fNProcesses(0)
					       , fNSystematics(0)
					       , fFlagEfficiencyConstraint(false)
					       , fFlagDoLogNormal(false)
					       , fFlagFirstSysSet(false)
					       , fDoingToys(false)
					       , fFlagDoStatErr(false)
{  
 //yfu
 SetMarginalizationMethod(BCIntegrate::kMargMetropolis);
// SetOptimizationMethod(BCIntegrate::kOptMinuit);
 SetRandomSeed(12345678);
};

// ---------------------------------------------------------
BCMultiTemplateFitter::~BCMultiTemplateFitter()
	// default destructor
{
	for (int i = 0; i < fNChannels; ++i) 
		delete fChannelContainer.at(i);
};

// ---------------------------------------------------------
int BCMultiTemplateFitter::GetChannelIndex(const char* name)
{
	// loop over all channels and compare names
	for (int i = 0; i < fNChannels; ++i) {
		// get channel
		BCChannel* channel = GetChannel(i); 

		// compare names
		if (!channel->GetName().compare(name))
			return i; 
	}
	
	// if channel does not exist, return -1
	return -1;
}

// ---------------------------------------------------------
int BCMultiTemplateFitter::GetProcessIndex(const char* name)
{
	// loop over all processs and compare names
	for (int i = 0; i < fNProcesses; ++i) {
		// get process
		BCProcess* process = GetProcess(i); 

		// compare names
		if (!process->GetName().compare(name))
			return i; 
	}

	// if process does not exist, return -1
	return -1;
}

// ---------------------------------------------------------
int BCMultiTemplateFitter::GetSystematicIndex(const char* name)
{
	// loop over all systematics and compare names
	for (int i = 0; i < fNSystematics; ++i) {
		// get systematic
		BCSystematic* systematic = GetSystematic(i); 

		// compare names
		if (!systematic->GetName().compare(name))
			return i; 
	}

	// if process does not exist, return -1
	return -1;
}

// ---------------------------------------------------------
int BCMultiTemplateFitter::SetTemplate(const char* channelname, const char* processname, TH1D hist, double efficiency)
{
	// get channel index
	int channelindex = GetChannelIndex(channelname);

	// check if channel exists
	if (channelindex < 0) {
      BCLog::OutWarning("BCMultitemplateFitter::SetTemplate() : Channel does not exist.");
			return -1;
	}

	// get process index
	int processindex = GetProcessIndex(processname);

	// check if process exists
	if (processindex < 0) {
      BCLog::OutWarning("BCMultitemplateFitter::SetTemplate() : Process does not exist.");
			return -1;
	}

	// get channel
	BCChannel* channel = GetChannel(channelindex);
	
	// get template
	BCTemplate* bctemplate = channel->GetTemplate(processindex);

//hist.Sumw2();
	//keep unscaled histogram
	bctemplate->SetOriginalHistogram((TH1D*)hist.Clone());

//cout<<"SetTemplate hist1: Name: "<<hist.GetName()<<" Data: "<<hist.GetBinContent(1)<<" Error: "<<hist.GetBinError(1)<<endl;
	// normalize histogram
	if (hist.Integral())
		hist.Scale(1.0 / hist.Integral()); 
//cout<<"SetTemplate hist2: Name: "<<hist.GetName()<<" Data: "<<hist.GetBinContent(1)<<" Error: "<<hist.GetBinError(1)<<endl;
//for(int ibin = 1; ibin <= hist.GetNbinsX(); ibin++){
//  hist.SetBinError(ibin, sqrt(hist.GetBinContent(ibin)));
//}


	// remove statistics box
	hist.SetStats(kFALSE);

	// set color and fill style
	hist.SetFillColor(2 + processindex);
	hist.SetFillStyle(1001);

	// create new histogram
	TH1D* temphist = new TH1D(hist);

	// set histogram
	bctemplate->SetHistogram(temphist);
	
	// set efficiency
	bctemplate->SetEfficiency(efficiency);

	// no error
	return 1;
}

// ---------------------------------------------------------
int BCMultiTemplateFitter::SetTemplate(const char* channelname, const char* processname, std::vector<TF1*>* funccont, int nbins, double efficiency)
{
        // get channel index
        int channelindex = GetChannelIndex(channelname);

        // check if channel exists
        if (channelindex < 0) {
      BCLog::OutWarning("BCMultitemplateFitter::SetTemplate() : Channel does not exist.");
                        return -1;
        }

        // get process index
        int processindex = GetProcessIndex(processname);

        // check if process exists
        if (processindex < 0) {
      BCLog::OutWarning("BCMultitemplateFitter::SetTemplate() : Process does not exist.");
                        return -1;
        }

        // get channel
        BCChannel* channel = GetChannel(channelindex);

        // get template
        BCTemplate* bctemplate = channel->GetTemplate(processindex);

        // set histogram
        bctemplate->SetFunctionContainer(funccont, nbins);

        // set efficiency
        bctemplate->SetEfficiency(efficiency);

        // no error
        return 1;
}


// ---------------------------------------------------------
int BCMultiTemplateFitter::SetData(const char* channelname, TH1D hist)
{
	int channelindex = GetChannelIndex(channelname);

	// check if channel exists
	if (channelindex < 0) {
      BCLog::OutWarning("BCMultitemplateFitter::SetTemplate() : Channel does not exist.");
			return -1;
	}

	// get channel
	BCChannel* channel = GetChannel(channelindex);
	
	// get template
	BCTemplate* data = channel->GetData();

	// remove statistics box
	hist.SetStats(kFALSE);

	// set marker
	hist.SetMarkerStyle(20);
	hist.SetMarkerSize(1.1);

	// remove old data set if it exists
	if (data->GetHistogram()) {
		delete data->GetHistogram();
		data->SetHistogram(0);
	}

	// set histogram
	data->SetHistogram(new TH1D(hist));
	
	// no error
	return 1;	
}

// ---------------------------------------------------------
int BCMultiTemplateFitter::AddChannel(const char* name)
{  
	// check if channel exists
	for (int i = 0; i < fNChannels; ++i) { 
		// compare names
		if (GetChannelIndex(name) >= 0) {
      BCLog::OutWarning("BCMultitemplateFitter::AddChannel() : Channel with this name exists already.");
			return -1;
		}
	}

	// create new channel
	BCChannel* channel = new BCChannel(name);

	// create new data
	BCTemplate* bctemplate = new BCTemplate(channel->GetName().c_str(), "data");

	// add data
	channel->SetData(bctemplate); 

	// add process templates
	for (int i = 0; i < fNProcesses; ++i) {
		// get process
		BCProcess* process = GetProcess(i); 

		// create new template
		BCTemplate* bctemplate = new BCTemplate(name, process->GetName().c_str()); 

		// add template
		channel->AddTemplate(bctemplate);
	}

	// loop over all systematics
	for (int i = 0; i < fNSystematics; ++i) {
		// get systematic
		BCSystematic* systematic = GetSystematic(i); 

		// create new systematic variation
		BCSystematicVariation* variation = new BCSystematicVariation(name, systematic->GetName().c_str(), fNProcesses); 

		// add systematic variation
		channel->AddSystematicVariation(variation);
	}

	// add channel
	fChannelContainer.push_back(channel);

	// increase number of channels
	fNChannels++;

	// no error
	return 1;
};

// ---------------------------------------------------------
int BCMultiTemplateFitter::AddProcess(const char* name, double nmin, double nmax)
{  
	// check if process exists
	for (int i = 0; i < fNProcesses; ++i) { 
		// compare names
		if (GetProcessIndex(name) >= 0) {
      BCLog::OutWarning("BCMultitemplateFitter::AddProcess() : Process with this name exists already.");
			return -1;
		}
	}

	// create new process
	BCProcess* process = new BCProcess(name);

	// add process
	fProcessContainer.push_back(process);

	// add process templates
	for (int i = 0; i < fNChannels; ++i) {
		// get channel
		BCChannel* channel = GetChannel(i); 

		// create new template
		BCTemplate* bctemplate = new BCTemplate(channel->GetName().c_str(), name); 

		// add template
		channel->AddTemplate(bctemplate);

		// loop over all systematic 
		for (int j = 0; j < fNSystematics; ++j) {
			// get systematic variation
			BCSystematicVariation* variation = channel->GetSystematicVariation(j);
			
			// add histogram
			variation->AddHistograms(0, 0);
		}
	}

	// increase number of processes
	fNProcesses++;

	// add parameter index to container
	fProcessParIndexContainer.push_back(GetNParameters());

	// add parameter
	AddParameter(name, nmin, nmax);

        // add a functional form for the expectation
        //fExpectationFunctionContainer.push_back(0);

	// no error
	return 1;
};

// ---------------------------------------------------------
int BCMultiTemplateFitter::AddSystematic(const char* name, double min, double max)
{
	// check if systematic exists
	for (int i = 0; i < fNSystematics; ++i) { 
		// compare names
		if (GetSystematicIndex(name) >= 0) {
      BCLog::OutWarning("BCMultitemplateFitter::AddSystematic() : Systematic with this name exists already.");
			return -1;
		}
	}

	// create new systematic
	BCSystematic* systematic = new BCSystematic(name);

	// add systematic
	fSystematicContainer.push_back(systematic);

	// add systematic variations
	for (int i = 0; i < fNChannels; ++i) {
		// get channel
		BCChannel* channel = GetChannel(i); 

		// create new systematic variation
		BCSystematicVariation* variation = new BCSystematicVariation(channel->GetName().c_str(), name, fNProcesses); 

		// add systematic variation
		channel->AddSystematicVariation(variation);
	}
	// ...

	// increase number of systematices
	fNSystematics++;

	// add parameter index to container
	fSystematicParIndexContainer.push_back(GetNParameters());

	// add parameter
	AddParameter(name, min, max);

        //WTF commented out -this I think was a harmless bug
//      // add a functional form for the expectation
//      fExpectationFunctionContainer.push_back(0);

	// no error
	return 1;

}

// ---------------------------------------------------------
int BCMultiTemplateFitter::SetSystematicVariation(const char* channelname, const char* processname,  const char* systematicname, TH1D hist_up, TH1D hist_down)
{
  fFlagFirstSysSet = true;
  
	// get channel index
	int channelindex = GetChannelIndex(channelname);

	// check if channel exists
	if (channelindex < 0) {
      BCLog::OutWarning("BCMultitemplateFitter::SetTemplate() : Channel does not exist.");
			return -1;
	}

	// get process index
	int processindex = GetProcessIndex(processname);

	// check if process exists
	if (processindex < 0) {
      BCLog::OutWarning("BCMultitemplateFitter::SetTemplate() : Process does not exist.");
			return -1;
	}

	// get systematic index
	int systematicindex = GetSystematicIndex(systematicname);

	// check if systematic exists
	if (systematicindex < 0) {
          std::string warn_message="BCMultitemplateFitter::SetTemplate() : Systematic ";
          warn_message+=systematicname;
          warn_message+=" does not exist.";
          BCLog::OutWarning(warn_message.c_str());
			return -1;
	}

	// get channel
	BCChannel* channel = GetChannel(channelindex);
	
	// get systematic variation
	BCSystematicVariation* variation = channel->GetSystematicVariation(systematicindex);

	//do relevant conversion if using log-normal description
	if (fFlagDoLogNormal) {

	  //First check for asymmetric uncertainties
	  for (int bin = 1; bin <= hist_up.GetNbinsX(); bin++) 
	    if (hist_up.GetBinContent(bin) != hist_down.GetBinContent(bin)) {
	      
	      std::cout << "\nERROR: Asymmetric uncertainties not implemented with log-normal treatment\n\n";
	      exit(1);
	    }
	    

	  //Now convert to the "sigma" of the log-normal distribution
	  for (int bin = 1; bin <= hist_up.GetNbinsX(); bin++) {
	    
	    double relError = hist_up.GetBinContent(bin);
	    if (relError >= 0.0) {
	      hist_up.SetBinContent(bin,TMath::Sqrt(TMath::Log(1.0 + relError*relError)));
	      hist_down.SetBinContent(bin,TMath::Sqrt(TMath::Log(1.0 + relError*relError)));
	    }
	    else {
	      hist_up.SetBinContent(bin,-TMath::Sqrt(TMath::Log(1.0 + relError*relError)));
	      hist_down.SetBinContent(bin,-TMath::Sqrt(TMath::Log(1.0 + relError*relError)));
	    }
//cout<<"ibin: "<<bin<<" relError: "<<relError<<" BinContent: "<<hist_up.GetBinContent(bin)<<endl;
	  }
	} //end if (fFlagDoLogNormal)

	// set histogram
	variation->SetHistograms(processindex, new TH1D(hist_up), new TH1D(hist_down));
	
	// no error
	return 1;
}

// ---------------------------------------------------------
int BCMultiTemplateFitter::SetSystematicVariation(const char* channelname, const char* processname,  const char* systematicname, std::vector<TF1*>* funcContUp, std::vector<TF1*>* funcContDown )
{
        // get channel index
        int channelindex = GetChannelIndex(channelname);

        // check if channel exists
        if (channelindex < 0) {
      BCLog::OutWarning("BCMultitemplateFitter::SetTemplate() : Channel does not exist.");
                        return -1;
        }

        // get process index
        int processindex = GetProcessIndex(processname);

        // check if process exists
        if (processindex < 0) {
      BCLog::OutWarning("BCMultitemplateFitter::SetTemplate() : Process does not exist.");
                        return -1;
        }

        // get systematic index
        int systematicindex = GetSystematicIndex(systematicname);

        // check if systematic exists
        if (systematicindex < 0) {
      BCLog::OutWarning("BCMultitemplateFitter::SetTemplate() : Systematic does not exist.");
                        return -1;
        }

        // get channel
        BCChannel* channel = GetChannel(channelindex);

        // get systematic variation
        BCSystematicVariation* variation = channel->GetSystematicVariation(systematicindex);

        // set histogram
        variation->SetFunctionContainers
          (processindex, funcContUp, funcContDown);

        // no error
        return 1;
}

// ---------------------------------------------------------
int BCMultiTemplateFitter::SetSystematicVariation(const char* channelname, const char* processname,  const char* systematicname, TH1D hist, TH1D hist_up, TH1D hist_down)
{
	// get number of bins
	int nbins = hist.GetNbinsX(); 

	TH1D* hist_up_rel = new TH1D(hist);
	TH1D* hist_down_rel = new TH1D(hist);

	// loop over all bins
	for (int ibin = 1; ibin <= nbins; ++ibin) {
		hist_up_rel->SetBinContent(ibin, (hist_up.GetBinContent(ibin) - hist.GetBinContent(ibin)) / hist.GetBinContent(ibin));
		hist_down_rel->SetBinContent(ibin, (hist.GetBinContent(ibin) - hist_down.GetBinContent(ibin)) / hist.GetBinContent(ibin));
	}
	
	// set the systematic variation
	return SetSystematicVariation(channelname, processname, systematicname, *hist_up_rel, *hist_down_rel);
}

// ---------------------------------------------------------
int BCMultiTemplateFitter::SetSystematicVariation(const char* channelname, const char* processname,  const char* systematicname, std::vector<TF1*>* func, std::vector<TF1*>* funcContUp, std::vector<TF1*>* funcContDown)
{
        // get number of bins
        int nfunc = func->size();

        std::vector<TF1*>* func_up_rel = new std::vector<TF1*>(0);
        std::vector<TF1*>* func_down_rel = new std::vector<TF1*>(0);

        // loop over all bins
        for (int ifunc = 0; ifunc < nfunc; ++ifunc) {

          TF1* DummyNominal = func->at(ifunc);
          TF1* DummyUp = funcContUp->at(ifunc);
          TF1* DummyDown = funcContDown->at(ifunc);

          TF1* DNF = new TF1("DNF","[0]+[1]*x+[2]*x*x");
          DNF->SetParameter(0,DummyNominal->GetParameter(0));
          DNF->SetParameter(1,DummyNominal->GetParameter(1));
          DNF->SetParameter(2,DummyNominal->GetParameter(2));

          TF1* DUF = new TF1("DUF","[0]+[1]*x+[2]*x*x");
          DUF->SetParameter(0,DummyUp->GetParameter(0));
          DUF->SetParameter(1,DummyUp->GetParameter(1));
          DUF->SetParameter(2,DummyUp->GetParameter(2));

          TF1* DDF = new TF1("DDF","[0]+[1]*x+[2]*x*x");
          DDF->SetParameter(0,DummyDown->GetParameter(0));
          DDF->SetParameter(1,DummyDown->GetParameter(1));
          DDF->SetParameter(2,DummyDown->GetParameter(2));

          TF1* NewUp = new TF1("NewUp","sqrt(pow(((DUF-DNF)/DNF),2))");
          TF1* NewDown = new TF1("NewDown","sqrt(pow(((DDF-DNF)/DNF),2))");

          func_up_rel->push_back(NewUp);
          func_down_rel->push_back(NewDown);

        }

        // set the systematic variation
        return SetSystematicVariation(channelname, processname, systematicname, func_up_rel, func_down_rel);
}

// ---------------------------------------------------------
int BCMultiTemplateFitter::PrintSummary(const char* filename)
{
	// open file
	std::ofstream ofi(filename);
	ofi.precision(3);
	
	// check if file is open
	if(!ofi.is_open()) {
		BCLog::OutWarning(Form("BCMultitemplateFitter::PrintSummary() : Could not open file %s", filename));
		return 0;
	}
	
	ofi
		<< " Multi template fitter summary " << std::endl
		<< " ----------------------------- " << std::endl
		<< std::endl
		<< " Number of channels      : " << fNChannels << std::endl
		<< " Number of processes     : " << fNProcesses << std::endl
		<< " Number of systematics   : " << fNSystematics << std::endl
		<< std::endl;
		
	ofi
		<< " Channels :" << std::endl;
		for (int i = 0; i < GetNChannels(); ++i) {
			ofi 
				<< " " << i 
				<< " : \"" << GetChannel(i)->GetName().c_str() << "\""
				<< std::endl;
		}
		ofi 
			<< std::endl;

	ofi
		<< " Processes :" << std::endl;
		for (int i = 0; i < GetNProcesses(); ++i) {
			ofi 
				<< " " << i 
				<< " : \"" << GetProcess(i)->GetName().c_str()  << "\""
				<< " (par index " << GetParIndexProcess(i) << ")" 
				<< std::endl;
		}
		ofi 
			<< std::endl;

	ofi
		<< " Systematics :" << std::endl;
		for (int i = 0; i < GetNSystematics(); ++i) {
			ofi 
				<< " " << i 
				<< " : \"" << GetSystematic(i)->GetName().c_str()  << "\""
				<< " (par index " << GetParIndexSystematic(i) << ")" 
				<< std::endl;
		}
		ofi 
			<< std::endl;
		if (GetNSystematics() == 0)
			ofi 
				<< " - none - " << std::endl;

		ofi 
			<< " Goodness-of-fit: " << std::endl;
		for (int i = 0; i < GetNChannels(); ++i) {
			ofi 
				<< " i : \"" << GetChannel(i)->GetName().c_str() << "\" : chi2 = " 
				<< CalculateChi2( i, GetBestFitParameters() )
				<< std::endl;
		}
		ofi 
			<< std::endl;
		

	// close file
	ofi.close();

	// no error
	return 1;
}

// ---------------------------------------------------------
double BCMultiTemplateFitter::Expectation(int channelindex, int binindex, const std::vector<double>& parameters)
{
	double expectation = 0.;

	// loop over all processes
	for (int i = 0; i < fNProcesses; ++i) {
		// get efficiency
		double efficiency = Efficiency(channelindex, i, binindex, parameters); 

		// get probability
		double probability = Probability(channelindex, i, binindex, parameters);

		// get parameter index
		int parindex = fProcessParIndexContainer[i]; 

		//double thisExpectation = parameters[parindex] * efficiency * probability; 
                double thisExpectation = efficiency * probability; //yfu


//if(binindex == 1) cout<<"parameters: "<<parameters[parindex]<<" thisExpectation: "<<thisExpectation<<" probability: "<<probability<<" efficiency: "<<efficiency<<endl; 
		// add to expectation
		expectation += thisExpectation;

		// modify original histogram to maintain relative MC stat background error
		if (fFlagDoStatErr && binindex <= fChannelContainer[channelindex]->GetMaxBinStatErr() && 
		    fProcessContainer[i]->GetName().find("Bkg") != string::npos) {
		  TH1* h = fChannelContainer[channelindex]->GetTemplate(i)->GetOriginalHistogram();
		  if (h != NULL) {
		    h->SetBinError(binindex,h->GetBinError(binindex) * (thisExpectation/h->GetBinContent(binindex)));
		    h->SetBinContent(binindex,thisExpectation);
		  }
		}
	}
//cout<<endl;
	// check if expectation is positive
	if (expectation < 0)
		expectation = 0.;
//cout<<"Expectation: channel: "<<channelindex<<" bin: "<<binindex<<" "<<expectation<<endl;

	return expectation;
}

// ---------------------------------------------------------
double BCMultiTemplateFitter::ExpectationFunction(int parindex, int channelindex, int processindex, std::vector<double>& parameters)
{
  // get function container
  std::vector<TF1*>* funccont = fChannelContainer[channelindex]->GetTemplate(processindex)->GetFunctionContainer();

  if (funccont->size()>0)
    return 1.;

  else if (!fExpectationFunctionContainer[parindex])
    return parameters[parindex];

  else {
    TF1* func = fExpectationFunctionContainer[parindex];
    return func->Eval(parameters[parindex]);
  }
}

// ---------------------------------------------------------
double BCMultiTemplateFitter::Efficiency(int channelindex, int processindex, int binindex, const std::vector<double>& parameters)
{
	// get channel
	BCChannel* channel = fChannelContainer[channelindex];

	double efficiency = channel->GetTemplate(processindex)->GetEfficiency();

	double defficiency = 1.;
	
	if (fFlagDoLogNormal)
	  defficiency = 0.;

	// loop over all systematics
	for (int i = 0; i < fNSystematics; ++i) {
		if (!(fSystematicContainer[i]->GetFlagSystematicActive()))
			continue;
		
		// get parameter index
		int parindex = fSystematicParIndexContainer[i]; 
		
		// get histogram
		TH1D* hist = 0; 
                std::vector<TF1*>* funcVect=0;

                if (parameters[parindex] > 0){
                  hist = channel->GetSystematicVariation(i)->GetHistogramUp(processindex);
                  funcVect = channel->GetSystematicVariation(i)->GetFunctionVectorUpContainer(processindex);
                }
                else {
                  hist = channel->GetSystematicVariation(i)->GetHistogramDown(processindex);
                  funcVect = channel->GetSystematicVariation(i)->GetFunctionVectorDownContainer(processindex);
                }

                double unit_shift_value=0.0;
                // check if histogram exists
                if (hist && !funcVect){
                  unit_shift_value=hist->GetBinContent(binindex);
                }
                if (!hist && funcVect){
                  int process_parindex = fProcessParIndexContainer[processindex];
                  unit_shift_value=funcVect->at(binindex-1)->Eval(parameters[process_parindex]);
                }
                if (hist && funcVect){
                  //this is bad both a histogram and a function vector are set
                  BCLog::OutError("BCMultiTemplateFitter::Efficiency: histogram and function vector systematic variation both set. Exiting");
                  exit(13);
                }
                if (!hist && !funcVect){
                  continue;
                }
                // multiply efficiency
                defficiency += parameters[parindex] * unit_shift_value;
//if(binindex == 1) cout<<"parindex: "<<parindex<<" parameters: "<<parameters[parindex]<<" value: "<<unit_shift_value<<" efficiency: "<<parameters[parindex] * unit_shift_value<<endl;
		
		// check if histogram exists
		if (!hist) 
			continue;
	}

	if (fFlagDoLogNormal)
	  defficiency = TMath::Exp(defficiency);

	// calculate efficiency
	efficiency *= defficiency;

	// make sure efficiency is between 0 and 1
	if (fFlagEfficiencyConstraint) {
		if (efficiency < 0.)
			efficiency = 0.;
		if (efficiency > 1.)
			efficiency = 1.;
	}

//cout<<"Efficiency: channel: "<<channelindex<<" process: "<<processindex<<" bin: "<<binindex<<" "<<efficiency<<endl;

	return efficiency;
}

// ---------------------------------------------------------
double BCMultiTemplateFitter::Probability(int channelindex, int processindex, int binindex, const std::vector<double>& parameters)
{
	// get histogram
	TH1D* hist = fChannelContainer[channelindex]->GetTemplate(processindex)->GetHistogram();
//if(hist) cout<<"Probability: channel: "<<channelindex<<" process: "<<processindex<<" bin: "<<binindex<<" "<<hist->GetBinContent(binindex)<<endl;
//else cout<<"Probability: 0"<<endl;

        // get function container
        std::vector<TF1*>* funccont = fChannelContainer[channelindex]->GetTemplate(processindex)->GetFunctionContainer();

        int parindex = fProcessParIndexContainer[processindex];

	// this needs to be fast
	if (!hist && (funccont->size() == 0))
		return 0.;

        if (hist){
          //std::cerr<<"Will return: ";
          //std::cerr<<hist->GetBinContent(binindex)<<"\n";
          return hist->GetBinContent(binindex) * parameters.at(parindex);
        }
        else if(funccont->size() != 0) {
          int parindex = fProcessParIndexContainer[processindex];
          if(fabs(parameters[parindex]) < 1e-30) return 0.0;//yfu
          else return funccont->at(binindex-1)->Eval(parameters[parindex]);
        }
        else{
          return 0.0;
        }
}

// ---------------------------------------------------------
int BCMultiTemplateFitter::PrintStack(const char* channelname, std::vector<double> parameters, const char* filename, const char* options) 
{
	int index = GetChannelIndex(channelname);

	return PrintStack(index, parameters, filename, options);
}

// ---------------------------------------------------------
int BCMultiTemplateFitter::PrintStack(int channelindex, std::vector<double> parameters, const char* filename, const char* options)
{
	// check if parameters are filled
	if (!parameters.size())
		return -1;

	// check options
	bool flag_logx   = false; // plot x-axis in log-scale
	bool flag_logy   = false; // plot y-axis in log-scale

	if (std::string(options).find("logx") < std::string(options).size())
		flag_logx = true;

	if (std::string(options).find("logy") < std::string(options).size())
		flag_logy = true;

	// get channel
	BCChannel* channel = GetChannel(channelindex);

	// create canvas
	TCanvas* c1 = new TCanvas(); 
	c1->cd();

	// set log or linear scale
	if (flag_logx)
		c1->SetLogx();
	
	if (flag_logy)
		c1->SetLogy();
	
	// create stack
	THStack* stack = new THStack("", ""); 

	// create a container of temporary histograms
	std::vector<TH1D*> histcontainer;

	// get number of templates
	unsigned int ntemplates = GetNProcesses();

	// loop over all templates
	for (unsigned int i = 0; i < ntemplates; ++i) {

		// get histogram
		TH1D* temphist = channel->GetTemplate(i)->GetHistogram(); 

                // get function container
                std::vector<TF1*>* funccont = channel->GetTemplate(i)->GetFunctionContainer();

		// create new histogram
		TH1D* hist;

		if (temphist)
			hist = new TH1D( *(temphist) );
		else if (funccont) {
                        hist = new TH1D( *(channel->GetData()->GetHistogram()));
                        hist->SetFillColor(2 + i);
                        hist->SetFillStyle(1001);
                }
                else
			continue;

		// get number of bins
		int nbins = hist->GetNbinsX(); 

		// scale histogram
		for (int ibin = 1; ibin <= nbins; ++ibin) {

			// get efficiency
			double efficiency = Efficiency(channelindex, i, ibin, parameters); 

			// get probability
			double probability = Probability(channelindex, i, ibin, parameters);

			// get parameter index
			int parindex = GetParIndexProcess(i); 

			// add to expectation
			double expectation = parameters.at(parindex)
				* efficiency
				* probability;
			
			// set bin content
			hist->SetBinContent(ibin, expectation);
		}

		// add histogram to container (for memory management)
		histcontainer.push_back(hist);

		// add histogram to stack
		stack->Add(hist);
	}

	//draw data
	channel->GetData()->GetHistogram()->Draw("PE");
	
	// set range user
	channel->GetData()->GetHistogram()->GetYaxis()->SetRangeUser(0., channel->GetData()->GetHistogram()->GetMaximum() + 2. * sqrt(channel->GetData()->GetHistogram()->GetMaximum()));

	// draw stack
	stack->Draw("SAMEHIST");

	//draw data again
	channel->GetData()->GetHistogram()->Draw("SAMEPE");

	// redraw the axes
	gPad->RedrawAxis();

	// print
	c1->Print(filename);

	// free memory
	for (unsigned int i = 0; i < histcontainer.size(); ++i) {
		TH1D* hist = histcontainer.at(i);
		delete hist;
	}
	delete stack;
	delete c1; 

	// no error
	return 1;
}

// ---------------------------------------------------------
double BCMultiTemplateFitter::CalculateChi2(int channelindex, std::vector<double> parameters)
{
	if (parameters.size() == 0)
		return -1;

	double chi2 = 0;
	
	// get channel
	BCChannel* channel = GetChannel(channelindex);
	
	// get data
	BCTemplate* data = channel->GetData();
	
	// get histogram
	TH1D* hist = data->GetHistogram(); 
	
	// check if histogram exists
	if (hist) {
		// get number of bins in data
		int nbins = hist->GetNbinsX();
		
		// loop over all bins
		for (int ibin = 1; ibin <= nbins; ++ibin) {
			// get expectation value
			double expectation = Expectation(channelindex, ibin, parameters);
			
			// get observation
			double observation = hist->GetBinContent(ibin);

                        if(fabs(expectation) < 1e-20) continue;//yfu
	
			// add Poisson term
			chi2 += (expectation - observation) * (expectation - observation) / expectation;
		}
	}
	
	// return chi2;
	return chi2;
}

// ---------------------------------------------------------
double BCMultiTemplateFitter::CalculateChi2(std::vector<double> parameters)
{
	if (parameters.size() == 0)
		return -1;

	double chi2 = 0;

	// get number of channels
	int nchannels = GetNChannels();

	// loop over all channels
	for (int i = 0; i < nchannels; ++i) {
		chi2 += CalculateChi2(i, parameters);
	}
	
	// return chi2
	return chi2;
}

// ---------------------------------------------------------
double BCMultiTemplateFitter::CalculateCash(int channelindex, std::vector<double> parameters)
{
	if (parameters.size() == 0)
		return -1;

	double cash = 0;
	
	// get channel
	BCChannel* channel = GetChannel(channelindex);
	
	// get data
	BCTemplate* data = channel->GetData();
	
	// get histogram
	TH1D* hist = data->GetHistogram(); 
	
	// check if histogram exists
	if (hist) {
		// get number of bins in data
		int nbins = hist->GetNbinsX();
		
		// loop over all bins
		for (int ibin = 1; ibin <= nbins; ++ibin) {
			// get expectation value
			double expectation = Expectation(channelindex, ibin, parameters);
			
			// get observation
			double observation = hist->GetBinContent(ibin);
			
			// calculate Cash statistic
			cash += 2. * (expectation - observation); 

                        if(fabs(expectation) < 1e-20) continue;//yfu

			// check negative log
			if (observation > 0)
				cash += 2. * observation * log (observation/expectation);
		}
	}
	
	// return cash;
	return cash;
	
}

// ---------------------------------------------------------
double BCMultiTemplateFitter::CalculateCash(std::vector<double> parameters)
{
	if (parameters.size() == 0)
		return -1;

	double cash = 0;

	// get number of channels
	int nchannels = GetNChannels();

	// loop over all channels
	for (int i = 0; i < nchannels; ++i) {
		cash += CalculateCash(i, parameters);
	}
	
	// return cash
	return cash;
}

// ---------------------------------------------------------
double BCMultiTemplateFitter::LogLikelihood(const std::vector<double>& parameters)
{
	double logprob = 0.;
	
	// loop over all channels
	for (int ichannel = 0; ichannel < fNChannels; ++ichannel) {
		
		// get channel
		BCChannel* channel = fChannelContainer[ichannel];
		
		// check if channel is active
		if (!(channel->GetFlagChannelActive()))
			continue;

		// get data
		BCTemplate* data = channel->GetData();

		// get histogram
		TH1D* hist = data->GetHistogram(); 

		// check if histogram exists
		if (!hist) 
			continue;

		// get number of bins in data
		int nbins = data->GetNBins();

		//prepare for MC stat. treatment
		string bgProcName = channel->GetName()+"Bkg";
		TH1* bgHist = channel->GetTemplate(GetProcessIndex(bgProcName.c_str()))->GetOriginalHistogram();
      
		// loop over all bins
		for (int ibin = 1; ibin <= nbins; ++ibin) {
			// get expectation value
			double expectation = Expectation(ichannel, ibin, parameters);
                        data->GetExpectation()->SetBinContent(ibin, expectation);

			// get observation
			double observation = hist->GetBinContent(ibin);



			if (fFlagDoStatErr && ibin <= channel->GetMaxBinStatErr()){ //add Gaussian with MC stat. included
			  logprob += BCMath::LogGaus(observation,expectation,TMath::Sqrt(TMath::Power(bgHist->GetBinError(ibin),2) + expectation),true);
//cout<<"ichannel: "<<ichannel<<" ibin: "<<ibin<<" parameter: "<<parameters.at(3)<<" expectation: "<<expectation<<" observation: "<<observation<<endl;
                        }
			else{ 
			  if(fabs(expectation) > 1e-10) logprob += BCMath::LogPoisson(observation, expectation); // add Poisson term
//if(ibin == 1) cout<<"ichannel: "<<ichannel<<" ibin: "<<ibin<<" parameter: "<<parameters.at(1)<<" expectation: "<<expectation<<" observation: "<<observation<<" logprob: "<<BCMath::LogPoisson(observation, expectation)<<endl;
                        }
//cout<<"ichannel: "<<ichannel<<" ibin: "<<ibin<<" parameter: "<<parameters.at(3)<<" expectation: "<<expectation<<" observation: "<<observation<<endl;
		}
	}

//yfu---------------------------------------------------------------------------
        //cout<<"logprob: "<<logprob<<endl;
        double AFBPenalty = 0.0;
        if(isAddAFBPenalty){
          AFBPenalty = CalcAFBPenalty(FChannelName, BChannelName, parameters);
          logprob += AFBPenalty;
        }
        //cout<<"AFBPenalty: "<<AFBPenalty<<endl;
//------------------------------------------------------------------------------

//cout<<"parameter: "<<parameters.at(3)<<" likelihood: "<<logprob<<endl;
	return logprob;
}

// ---------------------------------------------------------


double BCMultiTemplateFitter::FrequentistLogLikelihood(const std::vector<double>& parameters) {

  double logprob = LogLikelihood(parameters);

  for (int i = 0; i < fNSystematics; ++i) {
    if (!(fSystematicContainer[i]->GetFlagSystematicActive()))
      continue;

    // get parameter index
    int parindex = fSystematicParIndexContainer[i]; 

    if (!fDoingToys)
      logprob -= TMath::Power(parameters[parindex],2) / 2.0;
    else
      logprob -= TMath::Power(parameters[parindex] - (*nuisanceParameterOffsets)[i],2) / 2.0;
  }

  return logprob;
}


double BCMultiTemplateFitter::significance(double maxSigmaSig, bool doingLEE, bool* success) {

  bool verbose = !doingLEE;

  TMinuit *minuit = new TMinuit(fNSystematics+fNProcesses);
  minuit->SetPrintLevel(-1);
  
  globalBCMTFpointer = this;
  minuit->SetFCN(MinusFrequentistLogLikelihoodWrapper);


  Double_t arglist[2];
  Int_t ierflg = 0;

  //Fixed background normalization parameters
  for (int i = 0; i < fNProcesses-1; i++) {

    //if (GetParameter(GetParIndexProcess(i))->GetLowerLimit() != GetParameter(GetParIndexProcess(i))->GetUpperLimit()) {
    if (GetParameter(GetParIndexProcess(i)).GetLowerLimit() != GetParameter(GetParIndexProcess(i)).GetUpperLimit()) {//yfu

      cout << "\nERROR: background process parameters must be fixed - systematics added only via AddSystematic()\n";
      cout << "Make sure to add the signal process last (after all background processes)\n\n";
      exit(1);
    }

//    minuit->mnparm(i, GetProcess(i)->GetName().c_str(), GetParameter(GetParIndexProcess(i))->GetLowerLimit(), 0.001, GetParameter(GetParIndexProcess(i))->GetLowerLimit(), GetParameter(GetParIndexProcess(i))->GetLowerLimit()+0.01, ierflg);
    minuit->mnparm(i, GetProcess(i)->GetName().c_str(), GetParameter(GetParIndexProcess(i)).GetLowerLimit(), 0.001, GetParameter(GetParIndexProcess(i)).GetLowerLimit(), GetParameter(GetParIndexProcess(i)).GetLowerLimit()+0.01, ierflg);//yfu

    minuit->FixParameter(i);
  }


  //signal
  minuit->mnparm(fNProcesses-1, GetProcess(fNProcesses-1)->GetName().c_str(), 0.0, maxSigmaSig/100000.0, 0.0, maxSigmaSig, ierflg);

  //fix signal to 0 for background-only maximization
  minuit->FixParameter(fNProcesses-1);


  //systematics
  for (int i = 0; i < fNSystematics; i++) 
    minuit->mnparm(i+fNProcesses, GetSystematic(i)->GetName(), 0.0, 0.001, -5.0, 5.0, ierflg);


  char* cmd = new char[300];
  double dummy;
  int dummyI;


  // For minimization step (MIGRAD takes an arglist of size 2)
  // OBS - don't change arglist after this, it will mess up the minimization!
  arglist[0] = 10000; //max number of calls to user function
  arglist[1] = .0001; //tolerance. Minimization will stop when estimated vertical distance to minimum is 0.001*[tolerance]*UP
    

  minuit->mnexcm("MINIMIZE", arglist,2,ierflg); //background-only fit


  if (ierflg != 0) {
    if (verbose) cout << "WRONG RETURN VALUE from minimization (background-only)!\n";
    //verbose = true;
    
    //In case of a failing background-only fit, play with nuisance parameter ranges
    int retry;
    bool fixed = false;
    for (retry = 0; retry < 100*fNSystematics; retry++) {

      //Set new upper limit for nuisance pars and retry fit
      double upLim = 5.0*TMath::Power(1.02,retry+1);
 
      sprintf(cmd,"SET LIM %d %f %f",((retry%fNSystematics)+fNProcesses+1),(-upLim),upLim);
      minuit->mncomd(cmd,ierflg);

      minuit->mnexcm("MINIMIZE", arglist,2,ierflg); 
      if (ierflg == 0) {
	fixed = true;
	break;
      }
    }

    if (fixed) {
      if (verbose) cout << "Background-only fit converged after " << (retry+1) << " retries\n";

      double maxLogLikelihoodBonly;
      minuit->mnstat(maxLogLikelihoodBonly,dummy,dummy,dummyI,dummyI,dummyI);
      maxLogLikelihoodBonly = -maxLogLikelihoodBonly;
      if (verbose) cout << "maxLogLikelihoodBonly = " << maxLogLikelihoodBonly << endl;
    }
    else {
      cout << "Background-only fit did not converge after " << retry << " retries\n";
      
      if (!doingLEE)
	exit(1);
      else {
	*success = false;
	delete minuit;
	delete[] cmd;
	return -999.0;
      }
    }
  }
  
  
  if (verbose) {
    cout << "--------------------------------------\nResults of background-only fit: \n------------------------------------\n";
    for (int i = 0; i < fNSystematics; i++) {
      
      double value,error;
      minuit->GetParameter(i+fNProcesses,value,error);
      
      cout << GetSystematic(i)->GetName() << "  " << value << endl;
    }
  }


  double maxLogLikelihoodBonly;
  minuit->mnstat(maxLogLikelihoodBonly,dummy,dummy,dummyI,dummyI,dummyI);
  maxLogLikelihoodBonly = -maxLogLikelihoodBonly;

  if (verbose) cout << "Maximum log-likelihood (background-only) = " << maxLogLikelihoodBonly << endl;


  //Release signal parameter for signal+background fit
  minuit->Release(fNProcesses-1);

  
  minuit->mnexcm("MINIMIZE", arglist,2,ierflg); //signal+background fit



  if (ierflg != 0) {
    if (verbose) cout << "WRONG RETURN VALUE from minimization (signal+background)!\n";
    //verbose = true;
      
    //In case of a failing signal+background fit, play with signal range
    int retry;
    bool fixed = false;
    for (retry = 0; retry < 100; retry++) {
	
      //Set new upper limit for signal and retry fit
      double upLim = maxSigmaSig*TMath::Power(1.02,retry+1);
      sprintf(cmd,"SET LIM %d 0.0 %f",fNProcesses,upLim);
      minuit->mncomd(cmd,ierflg);
      minuit->mnexcm("MINIMIZE", arglist,2,ierflg); 
      if (ierflg == 0) {
	fixed = true;
	break;
      }
    }
    int saveRetry = retry;

    //if that does not help, try to play with nuisance parameter ranges
    if (!fixed) {
      for (retry = 0; retry < 100*fNSystematics; retry++) {
	
	//Set new upper limit for nuisance pars and retry fit
	double upLim = 5.0*TMath::Power(1.02,retry+1);

	sprintf(cmd,"SET LIM %d %f %f",((retry%fNSystematics)+fNProcesses+1),(-upLim),upLim);
	minuit->mncomd(cmd,ierflg);
	  
	minuit->mnexcm("MINIMIZE", arglist,2,ierflg); 
	if (ierflg == 0) {
	  fixed = true;
	  break;
	}
      }
      retry = saveRetry+retry;
    }
      
    if (fixed) {
      if (verbose) cout << "Signal+background fit converged after " << (retry+1) << " retries\n";

      double maxLogLikelihoodSplusB;
      minuit->mnstat(maxLogLikelihoodSplusB,dummy,dummy,dummyI,dummyI,dummyI);
      maxLogLikelihoodSplusB = -maxLogLikelihoodSplusB;
      if (verbose) cout << "maxLogLikelihoodSplusB = " << maxLogLikelihoodSplusB << endl;
    }
    else {
      cout << "Signal+background fit did not converge after " << retry << " retries\n";
      
      if (!doingLEE)
	exit(1);
      else {
	*success = false;
	delete minuit;
	delete[] cmd;
	return -999.0;
      }
    }
  }
 


  double signal,sigErr;
  minuit->GetParameter(fNProcesses-1,signal,sigErr);


  if (verbose) {
    cout << "-------------------------------------\nResults of signal+background fit: \n------------------------------------\n";
    cout << GetProcess(fNProcesses-1)->GetName() << " (POI)  " << signal << endl;
    for (int i = 0; i < fNSystematics; i++) {
      
      double value,error;
      minuit->GetParameter(i+fNProcesses,value,error);
      
      cout << GetSystematic(i)->GetName() << "  " << value << endl;
    }
  }

  if (signal > 0.9*maxSigmaSig) {
    cout << "ERROR: Too low maxSigmaSig\n";
    exit(1);
  }

  double maxLogLikelihoodSplusB;
  minuit->mnstat(maxLogLikelihoodSplusB,dummy,dummy,dummyI,dummyI,dummyI);
  maxLogLikelihoodSplusB = -maxLogLikelihoodSplusB;

  if (verbose) cout << "Maximum log-likelihood (signal+background) = " << maxLogLikelihoodSplusB << endl;


  //Test statistic
  double q0 = -2.0 * (maxLogLikelihoodBonly - maxLogLikelihoodSplusB);
  
  //For downwards fluctuations, q0 is sometimes numerically negative - set to 0
  if (q0 < 0.0)
    q0 = 0.0;

  if (doingLEE)
    *success = true;

  delete minuit;
  delete[] cmd;

  return TMath::Sqrt(q0);;
}




double BCMultiTemplateFitter::significance_withToys(double maxSigmaSig, int Ntoys, TH1* q0hist) {


  TMinuit *minuit = new TMinuit(fNSystematics+fNProcesses);
  minuit->SetPrintLevel(-1);
  
  globalBCMTFpointer = this;
  minuit->SetFCN(MinusFrequentistLogLikelihoodWrapper);


  Double_t arglist[2];
  Int_t ierflg = 0;

  //Fixed background normalization parameters
  for (int i = 0; i < fNProcesses-1; i++) {

//    if (GetParameter(GetParIndexProcess(i))->GetLowerLimit() != GetParameter(GetParIndexProcess(i))->GetUpperLimit()) {
    if (GetParameter(GetParIndexProcess(i)).GetLowerLimit() != GetParameter(GetParIndexProcess(i)).GetUpperLimit()) {//yfu

      cout << "\nERROR: background process parameters must be fixed - systematics added only via AddSystematic()\n\n";
      exit(1);
    }

    //minuit->mnparm(i, GetProcess(i)->GetName().c_str(), GetParameter(GetParIndexProcess(i))->GetLowerLimit(), 0.001, GetParameter(GetParIndexProcess(i))->GetLowerLimit(), GetParameter(GetParIndexProcess(i))->GetLowerLimit()+0.01, ierflg);
    minuit->mnparm(i, GetProcess(i)->GetName().c_str(), GetParameter(GetParIndexProcess(i)).GetLowerLimit(), 0.001, GetParameter(GetParIndexProcess(i)).GetLowerLimit(), GetParameter(GetParIndexProcess(i)).GetLowerLimit()+0.01, ierflg);//yfu

    minuit->FixParameter(i);
  }


  //signal
  minuit->mnparm(fNProcesses-1, GetProcess(fNProcesses-1)->GetName().c_str(), 0.0, maxSigmaSig/100000.0, 0.0, maxSigmaSig, ierflg);

  //fix signal to 0 for background-only maximization
  minuit->FixParameter(fNProcesses-1);


  //systematics
  for (int i = 0; i < fNSystematics; i++) 
    minuit->mnparm(i+fNProcesses, GetSystematic(i)->GetName(), 0.0, 0.001, -5.0, 5.0, ierflg);



  // For minimization step (MIGRAD takes an arglist of size 2)
  // OBS - don't change arglist after this, it will mess up the minimization!
  arglist[0] = 10000; //max number of calls to user function
  arglist[1] = .0001; //tolerance. Minimization will stop when estimated vertical distance to minimum is 0.001*[tolerance]*UP
    

  minuit->mnexcm("MINIMIZE", arglist,2,ierflg); //background-only fit

  if (ierflg != 0) {
    cout << "WRONG RETURN VALUE from minimization (background-only)!\n";
    exit(1);
  }
    

  vector<double> bestFitBonlyParameters;
  bestFitBonlyParameters.clear();
  for (int i = 0; i < fNProcesses-1; i++)
    //bestFitBonlyParameters.push_back(GetParameter(GetParIndexProcess(i))->GetLowerLimit());
    bestFitBonlyParameters.push_back(GetParameter(GetParIndexProcess(i)).GetLowerLimit());//yfu

  bestFitBonlyParameters.push_back(0.0);

  
  cout << "--------------------------------------\nResults of background-only fit: \n------------------------------------\n";
  for (int i = 0; i < fNSystematics; i++) {
   
    double value,error;
    minuit->GetParameter(i+fNProcesses,value,error);

    bestFitBonlyParameters.push_back(value);

    cout << GetSystematic(i)->GetName() << "  " << value << endl;
  }


  double maxLogLikelihoodBonly;
  double dummy;
  int dummyI;
  minuit->mnstat(maxLogLikelihoodBonly,dummy,dummy,dummyI,dummyI,dummyI);
  maxLogLikelihoodBonly = -maxLogLikelihoodBonly;

  cout << "Maximum log-likelihood (background-only) = " << maxLogLikelihoodBonly << endl;
  


  //Release signal parameter for signal+background fit
  minuit->Release(fNProcesses-1);

  
  minuit->mnexcm("MINIMIZE", arglist,2,ierflg); //signal+background fit

  if (ierflg != 0) {
    cout << "WRONG RETURN VALUE from minimization (signal+background)!\n";
    exit(1);
  }
  

  cout << "-------------------------------------\nResults of signal+background fit: \n------------------------------------\n";
  double signal,sigErr;
  minuit->GetParameter(fNProcesses-1,signal,sigErr);
  cout << GetProcess(fNProcesses-1)->GetName() << " (POI)  " << signal << endl;
  for (int i = 0; i < fNSystematics; i++) {
   
    double value,error;
    minuit->GetParameter(i+fNProcesses,value,error);

    cout << GetSystematic(i)->GetName() << "  " << value << endl;
  }


  double maxLogLikelihoodSplusB;
  minuit->mnstat(maxLogLikelihoodSplusB,dummy,dummy,dummyI,dummyI,dummyI);
  maxLogLikelihoodSplusB = -maxLogLikelihoodSplusB;

  cout << "Maximum log-likelihood (signal+background) = " << maxLogLikelihoodSplusB << endl;


  //Test statistic
  double q0_obs = -2.0 * (maxLogLikelihoodBonly - maxLogLikelihoodSplusB);

  cout << "\n\nObserved q0 = " << q0_obs << endl << endl;
  
  //For downwards fluctuations, q0 is sometimes numerically negative - set to 0
  if (q0_obs < 0.0)
    q0_obs = 0.0;


  //Store original data
  vector<TH1D*> originalData;
  originalData.clear();

  for (int ichannel = 0; ichannel < fNChannels; ++ichannel) {

      // get channel
      BCChannel* channel = fChannelContainer[ichannel];
		
      // check if channel is active
      if (!(channel->GetFlagChannelActive()))
	continue;

      originalData.push_back((TH1D*)(channel->GetData()->GetHistogram()->Clone()));
  }


  //Generate pseudo-experiments under best-fit background hypothesis
  BCMTFAnalysisFacility* facility = new BCMTFAnalysisFacility(this);
  TRandom* rnd = new TRandom3(0);

  fDoingToys = true;
  nuisanceParameterOffsets = new vector<double>(fNSystematics);

  int Nlargerq0Obs = 0;
  int NmcSuccessful = 0;

  char* cmd = new char[300];

  for (int mc = 0; mc < Ntoys; mc++) {

    if (mc % 1000 == 0 && mc > 0)
      cout << "Done with " << mc << " pseudo-experiments\n";


    //Generate pseudo-data
    vector<TH1D> pseudoData = facility->BuildEnsemble(bestFitBonlyParameters);

    //Set as data
    for (int ichannel = 0; ichannel < fNChannels; ++ichannel) {

      // get channel
      BCChannel* channel = fChannelContainer[ichannel];
		
      // check if channel is active
      if (!(channel->GetFlagChannelActive()))
	continue;

      SetData(channel->GetName().c_str(),pseudoData[ichannel]);
    }

    
    //Under the "unconditional ensemble", we generate the nuisance parameter central values for the constraints
    //according to the Gaussian prior around the background-only best fit
    for (int i = 0; i < fNSystematics; ++i) {
      if (!(fSystematicContainer[i]->GetFlagSystematicActive()))
	continue;

      (*nuisanceParameterOffsets)[i] = rnd->Gaus(bestFitBonlyParameters[i+fNProcesses],1.0);
    }

    //Calculate PLR test statistic
    
    //First, fix signal to 0 for background-only fit
    sprintf(cmd,"SET PAR %d 0.0",fNProcesses);
    minuit->mncomd(cmd,ierflg);
    minuit->FixParameter(fNProcesses-1);

    minuit->mnexcm("MINIMIZE", arglist,2,ierflg); //background-only fit

    bool didRetryBonly = false;
    if (ierflg != 0) {
      //cout << "WRONG RETURN VALUE from minimization (background-only) in pseudo-experiment!\n";
      //continue;

      //In case of a failing background-only fit, play with nuisance parameter ranges
      int retry;
      bool fixed = false;
      for (retry = 0; retry < 100*fNSystematics; retry++) {

	//Set new upper limit for nuisance pars and retry fit
	double upLim = 5.0*TMath::Power(1.02,retry+1);

	sprintf(cmd,"SET LIM %d %f %f",((retry%fNSystematics)+fNProcesses+1),(-upLim),upLim);
	minuit->mncomd(cmd,ierflg);

	minuit->mnexcm("MINIMIZE", arglist,2,ierflg); 
	if (ierflg == 0) {
	  fixed = true;
	  break;
	}
      }

      if (fixed) {
	//cout << "Background-only fit converged after " << (retry+1) << " retries\n";

	minuit->mnstat(maxLogLikelihoodBonly,dummy,dummy,dummyI,dummyI,dummyI);
	maxLogLikelihoodBonly = -maxLogLikelihoodBonly;
	//cout << "maxLogLikelihoodBonly = " << maxLogLikelihoodBonly << endl;

	//Reset original upper limit
	for (int i = 0; i < fNSystematics; ++i) {
	  sprintf(cmd,"SET LIM %d %f %f",(i+fNProcesses+1),(-5.0),5.0);
	  minuit->mncomd(cmd,ierflg);
	}

	didRetryBonly = true;
      }
      else {
	cout << "Background-only fit did not converge after " << retry << " retries\nDropping this pseudo-experiment...\n";
	//Reset original upper limit
	for (int i = 0; i < fNSystematics; ++i) {
	  sprintf(cmd,"SET LIM %d %f %f",(i+fNProcesses+1),(-5.0),5.0);
	  minuit->mncomd(cmd,ierflg);
	}
	continue; //drop the pseudo-exp.
      }
    }
  
    
    if (!didRetryBonly) {
      minuit->mnstat(maxLogLikelihoodBonly,dummy,dummy,dummyI,dummyI,dummyI);
      maxLogLikelihoodBonly = -maxLogLikelihoodBonly;
    }


    //Release signal parameter for signal+background fit
    minuit->Release(fNProcesses-1);
    
    minuit->mnexcm("MINIMIZE", arglist,2,ierflg); //signal+background fit
    
    bool didRetrySplusB = false;
    if (ierflg != 0) {
      //cout << "WRONG RETURN VALUE from minimization (signal+background) in pseudo-experiment!\n";
      //continue;

      //In case of a failing signal+background fit, play with signal range
      int retry;
      bool fixed = false;
      for (retry = 0; retry < 100; retry++) {
	
	//Set new upper limit for signal and retry fit
	double upLim = maxSigmaSig*TMath::Power(1.02,retry+1);
	sprintf(cmd,"SET LIM %d 0.0 %f",fNProcesses,upLim);
	minuit->mncomd(cmd,ierflg);
	minuit->mnexcm("MINIMIZE", arglist,2,ierflg); 
	if (ierflg == 0) {
	  fixed = true;
	  break;
	}
      }
      int saveRetry = retry;

      //if that does not help, try to play with nuisance parameter ranges
      if (!fixed) {
	for (retry = 0; retry < 100*fNSystematics; retry++) {
	
	  //Set new upper limit for nuisance pars and retry fit
	  double upLim = 5.0*TMath::Power(1.02,retry+1);

	  sprintf(cmd,"SET LIM %d %f %f",((retry%fNSystematics)+fNProcesses+1),(-upLim),upLim);
	  minuit->mncomd(cmd,ierflg);
	  
	  minuit->mnexcm("MINIMIZE", arglist,2,ierflg); 
	  if (ierflg == 0) {
	    fixed = true;
	    break;
	  }
	}
	retry = saveRetry+retry;
      }
      
      if (fixed) {
	//cout << "Signal+background fit converged after " << (retry+1) << " retries\n";

	minuit->mnstat(maxLogLikelihoodSplusB,dummy,dummy,dummyI,dummyI,dummyI);
	maxLogLikelihoodSplusB = -maxLogLikelihoodSplusB;
	//cout << "maxLogLikelihoodSplusB = " << maxLogLikelihoodSplusB << endl;

	//Reset original upper limit
	sprintf(cmd,"SET LIM %d 0.0 %f",fNProcesses,maxSigmaSig);
	minuit->mncomd(cmd,ierflg);

	didRetrySplusB = true;
      }
      else {
	cout << "Signal+background fit did not converge after " << retry << " retries\nDropping this pseudo-experiment...\n";
	//Reset original upper limit
	sprintf(cmd,"SET LIM %d 0.0 %f",fNProcesses,maxSigmaSig);
	minuit->mncomd(cmd,ierflg);
	continue; //drop the pseudo-exp.
      }
    }
  
    if (!didRetrySplusB) {
      minuit->mnstat(maxLogLikelihoodSplusB,dummy,dummy,dummyI,dummyI,dummyI);
      maxLogLikelihoodSplusB = -maxLogLikelihoodSplusB;
    }


    //Test statistic
    double q0 = -2.0 * (maxLogLikelihoodBonly - maxLogLikelihoodSplusB);

    //Test for weird failures
    if (TMath::IsNaN(q0) || !TMath::Finite(q0)) {
      cout << "Strange value of q0 encountered: " << q0 << endl;
      cout << "Dropping pseudo-experiment..." << endl;
      continue;
    }

    //For downwards fluctuations, q0 is sometimes numerically negative - set to 0
    if (q0 < 0.0)
      q0 = 0.0;

    //Test for outliers
    if (q0 > 50.0)
      cout << "Large value of q0 encountered: " << q0 << endl;

    if (q0hist != NULL)
      q0hist->Fill(q0);

    if (q0 >= q0_obs)
      Nlargerq0Obs++;

    NmcSuccessful++;
  }

  fDoingToys = false;

  double pValue = Nlargerq0Obs*1.0 / NmcSuccessful;

  double significance;

  if (pValue > 0.5)
    significance = 0.0;
  else
    significance = TMath::Abs(TMath::NormQuantile(pValue));


  cout << "\nTotal number of attempted pseudo-experiments: " << Ntoys << endl;
  cout << "Number of successful pseudo-experiments: " << NmcSuccessful << endl;
  cout << "Number of q0 > q0_obs: " << Nlargerq0Obs << endl;
  cout << "p-value: " << pValue << endl;
  cout << "significance: " << significance << endl << endl;


  //Reset original data
  int cnt = 0;
  for (int ichannel = 0; ichannel < fNChannels; ++ichannel) {

      // get channel
      BCChannel* channel = fChannelContainer[ichannel];
		
      // check if channel is active
      if (!(channel->GetFlagChannelActive()))
	continue;

      SetData(channel->GetName().c_str(),*originalData[cnt++]);
  }

  delete minuit;
  delete nuisanceParameterOffsets;
  delete facility;
  delete rnd;
  delete[] cmd;

  return significance;
}



std::vector<double>* BCMultiTemplateFitter::getBestFitBonlyParameters(double maxSigmaSig) {


  TMinuit *minuit = new TMinuit(fNSystematics+fNProcesses);
  minuit->SetPrintLevel(-1);
  
  globalBCMTFpointer = this;
  minuit->SetFCN(MinusFrequentistLogLikelihoodWrapper);


  Double_t arglist[2];
  Int_t ierflg = 0;

  //Fixed background normalization parameters
  for (int i = 0; i < fNProcesses-1; i++) {

    //if (GetParameter(GetParIndexProcess(i))->GetLowerLimit() != GetParameter(GetParIndexProcess(i))->GetUpperLimit()) {
    if (GetParameter(GetParIndexProcess(i)).GetLowerLimit() != GetParameter(GetParIndexProcess(i)).GetUpperLimit()) {//yfu

      cout << "\nERROR: background process parameters must be fixed - systematics added only via AddSystematic()\n\n";
      exit(1);
    }

    //minuit->mnparm(i, GetProcess(i)->GetName().c_str(), GetParameter(GetParIndexProcess(i))->GetLowerLimit(), 0.001, GetParameter(GetParIndexProcess(i))->GetLowerLimit(), GetParameter(GetParIndexProcess(i))->GetLowerLimit()+0.01, ierflg);
    minuit->mnparm(i, GetProcess(i)->GetName().c_str(), GetParameter(GetParIndexProcess(i)).GetLowerLimit(), 0.001, GetParameter(GetParIndexProcess(i)).GetLowerLimit(), GetParameter(GetParIndexProcess(i)).GetLowerLimit()+0.01, ierflg);//yfu

    minuit->FixParameter(i);
  }

  //signal
  minuit->mnparm(fNProcesses-1, GetProcess(fNProcesses-1)->GetName().c_str(), 0.0, maxSigmaSig/100000.0, 0.0, maxSigmaSig, ierflg);

  //fix signal to 0 for background-only maximization
  minuit->FixParameter(fNProcesses-1);


  //systematics
  for (int i = 0; i < fNSystematics; i++) 
    minuit->mnparm(i+fNProcesses, GetSystematic(i)->GetName(), 0.0, 0.001, -5.0, 5.0, ierflg);



  // For minimization step (MIGRAD takes an arglist of size 2)
  // OBS - don't change arglist after this, it will mess up the minimization!
  arglist[0] = 10000; //max number of calls to user function
  arglist[1] = .0001; //tolerance. Minimization will stop when estimated vertical distance to minimum is 0.001*[tolerance]*UP
    

  minuit->mnexcm("MINIMIZE", arglist,2,ierflg); //background-only fit

  if (ierflg != 0) {
    cout << "WRONG RETURN VALUE from minimization (background-only)!\n";
    exit(1);
  }
    

  vector<double>* bestFitBonlyParameters = new vector<double>;
  bestFitBonlyParameters->clear();
  for (int i = 0; i < fNProcesses-1; i++)
    //bestFitBonlyParameters->push_back(GetParameter(GetParIndexProcess(i))->GetLowerLimit());
    bestFitBonlyParameters->push_back(GetParameter(GetParIndexProcess(i)).GetLowerLimit());//yfu

  bestFitBonlyParameters->push_back(0.0);

  
  cout << "--------------------------------------\nResults of background-only fit: \n------------------------------------\n";
  for (int i = 0; i < fNSystematics; i++) {
   
    double value,error;
    minuit->GetParameter(i+fNProcesses,value,error);

    bestFitBonlyParameters->push_back(value);

    cout << GetSystematic(i)->GetName() << "  " << value << endl;
  }


  return bestFitBonlyParameters;
}




std::vector<double>* BCMultiTemplateFitter::getBestFitSplusBparameters(double maxSigmaSig) {


  TMinuit *minuit = new TMinuit(fNSystematics+fNProcesses);
  minuit->SetPrintLevel(-1);
  
  globalBCMTFpointer = this;
  minuit->SetFCN(MinusFrequentistLogLikelihoodWrapper);


  Double_t arglist[2];
  Int_t ierflg = 0;

  //Fixed background normalization parameters
  for (int i = 0; i < fNProcesses-1; i++) {

    //if (GetParameter(GetParIndexProcess(i))->GetLowerLimit() != GetParameter(GetParIndexProcess(i))->GetUpperLimit()) {
    if (GetParameter(GetParIndexProcess(i)).GetLowerLimit() != GetParameter(GetParIndexProcess(i)).GetUpperLimit()) {//yfu

      cout << "\nERROR: background process parameters must be fixed - systematics added only via AddSystematic()\n\n";
      exit(1);
    }

    //minuit->mnparm(i, GetProcess(i)->GetName().c_str(), GetParameter(GetParIndexProcess(i))->GetLowerLimit(), 0.001, GetParameter(GetParIndexProcess(i))->GetLowerLimit(), GetParameter(GetParIndexProcess(i))->GetLowerLimit()+0.01, ierflg);
    minuit->mnparm(i, GetProcess(i)->GetName().c_str(), GetParameter(GetParIndexProcess(i)).GetLowerLimit(), 0.001, GetParameter(GetParIndexProcess(i)).GetLowerLimit(), GetParameter(GetParIndexProcess(i)).GetLowerLimit()+0.01, ierflg);//yfu

    minuit->FixParameter(i);
  }

  //signal
  minuit->mnparm(fNProcesses-1, GetProcess(fNProcesses-1)->GetName().c_str(), 0.0, maxSigmaSig/100000.0, 0.0, maxSigmaSig, ierflg);


  //systematics
  for (int i = 0; i < fNSystematics; i++) 
    minuit->mnparm(i+fNProcesses, GetSystematic(i)->GetName(), 0.0, 0.001, -5.0, 5.0, ierflg);



  // For minimization step (MIGRAD takes an arglist of size 2)
  // OBS - don't change arglist after this, it will mess up the minimization!
  arglist[0] = 10000; //max number of calls to user function
  arglist[1] = .0001; //tolerance. Minimization will stop when estimated vertical distance to minimum is 0.001*[tolerance]*UP
    

  minuit->mnexcm("MINIMIZE", arglist,2,ierflg); //background-only fit

  if (ierflg != 0) {
    cout << "WRONG RETURN VALUE from minimization (background-only)!\n";
    exit(1);
  }
    

  vector<double>* bestFitSplusBparameters = new vector<double>;
  bestFitSplusBparameters->clear();
  for (int i = 0; i < fNProcesses-1; i++)
    //bestFitSplusBparameters->push_back(GetParameter(GetParIndexProcess(i))->GetLowerLimit());
    bestFitSplusBparameters->push_back(GetParameter(GetParIndexProcess(i)).GetLowerLimit());//yfu

  
  cout << "--------------------------------------\nResults of signal+background fit: \n------------------------------------\n";
  double signal,sigErr;
  minuit->GetParameter(fNProcesses-1,signal,sigErr);
  cout << GetProcess(fNProcesses-1)->GetName() << " (POI)  " << signal << endl;
  
  bestFitSplusBparameters->push_back(signal);

  for (int i = 0; i < fNSystematics; i++) {
   
    double value,error;
    minuit->GetParameter(i+fNProcesses,value,error);

    bestFitSplusBparameters->push_back(value);

    cout << GetSystematic(i)->GetName() << "  " << value << endl;
  }


  return bestFitSplusBparameters;
}



// set flag for statistical error treatment
void BCMultiTemplateFitter::SetFlagDoStatErr(bool value) {

  if (value) {

    //check that user has set the maxbin for stat errors for at least one channel
    bool ok = false;
    for (int ichannel = 0; ichannel < fNChannels; ++ichannel) {
      
      BCChannel* channel = fChannelContainer[ichannel];

      if (channel->GetMaxBinStatErr() != 0)
	ok = true;
    }

    if (!ok) {
      cout << "\nERROR: You have opted to take into account MC statistical errors, but have not set MaxBinStatErr for any channel\n";
      exit(1);
    }

    std::cout << "\nTurned on treatment of MC statistical errors in the background estimate\n";

    //Print some relative stat. errors
    for (int ichannel = 0; ichannel < fNChannels; ++ichannel) {

      BCChannel* channel = fChannelContainer[ichannel];

      if (!(channel->GetFlagChannelActive()))
	continue;

      cout << "-----------------\n";
      cout << "Channel: " << channel->GetName() << endl;

      string bgProcName = channel->GetName()+"Bkg";
      TH1* h = channel->GetTemplate(GetProcessIndex(bgProcName.c_str()))->GetHistogram();
//cout<<"which histogram: "<<h->GetName()<<endl;

      int highestRelStatIdx = -1;
      double highestRelStat = -1.0;
      int lowestDataIdx = -1;
      double lowestData = 1.0e100;

      for (int bin = 1; bin <= channel->GetMaxBinStatErr(); bin++) {
	cout << "Bin number " << bin << ": relative stat err = " << h->GetBinError(bin) / h->GetBinContent(bin)
	     << "   data = " << channel->GetData()->GetHistogram()->GetBinContent(bin) << endl; 
//cout<<"??? Error: "<<h->GetBinError(bin)<<endl;

	if (channel->GetData()->GetHistogram()->GetBinContent(bin) < lowestData) {
	  lowestData = channel->GetData()->GetHistogram()->GetBinContent(bin);
	  lowestDataIdx = bin;
	}

	if (h->GetBinError(bin) / h->GetBinContent(bin) > highestRelStat) {
	  highestRelStat = h->GetBinError(bin) / h->GetBinContent(bin);
	  highestRelStatIdx = bin;
	}
      }
      
      if (channel->GetMaxBinStatErr() > 0) {

	cout << "\nHighest relative stat err:\n";
	cout << "Bin number " << highestRelStatIdx << ": relative stat err = " << h->GetBinError(highestRelStatIdx) / h->GetBinContent(highestRelStatIdx)
	     << "   data = " << channel->GetData()->GetHistogram()->GetBinContent(highestRelStatIdx) << endl; 

	cout << "\nLowest data count:\n";
	cout << "Bin number " << lowestDataIdx << ": relative stat err = " << h->GetBinError(lowestDataIdx) / h->GetBinContent(lowestDataIdx)
	     << "   data = " << channel->GetData()->GetHistogram()->GetBinContent(lowestDataIdx) << endl; 
      }
    }

    fFlagDoStatErr = true;
  }
  else {
    std::cout << "Turned off treatment of MC statistical errors in the background estimate\n";
    fFlagDoStatErr = false;
  }
}

//yfu-----------------------------------------------------------------------------------------//
void BCMultiTemplateFitter::PrintResults(const char * file)
{
   // print summary of Markov Chain Monte Carlo

   // open file
        std::ofstream ofi(file);

   // check if file is open
   if (!ofi.is_open()) {
      std::cerr << "Couldn't open file " << file << std::endl;
      return;
   }

   // number of parameters and chains
   int npar = MCMCGetNParameters();
   int nchains = MCMCGetNChains();

   // check convergence
   bool flag_conv = MCMCGetNIterationsConvergenceGlobal() > 0;

   ofi << std::endl
          << " -----------------------------------------------------" << std::endl
          << " Summary" << std::endl
       << " -----------------------------------------------------" << std::endl
       << std::endl;

   ofi << " Model summary" << std::endl << " =============" << std::endl
       << " Model: " << fName.data() << std::endl
       << " Number of parameters: " << npar << std::endl
       << " List of Parameters and ranges:" << std::endl;
   for (int i = 0; i < npar; ++i)
      ofi << "  (" << i << ") Parameter \""
          //<< fParameterSet->at(i)->GetName().data() << "\"" << ": "
          //<< "(" << fParameterSet->at(i)->GetLowerLimit() << ", "
          //<< fParameterSet->at(i)->GetUpperLimit() << ")" << std::endl;
          << fParameters.At(i).GetName().data() << "\"" << ": "//yfu
          << "(" << fParameters.At(i).GetLowerLimit() << ", "
          << fParameters.At(i).GetUpperLimit() << ")" << std::endl;
   ofi << std::endl;

   ofi << " Results of the optimization" << std::endl
       << " ===========================" << std::endl
       << " Optimization algorithm used: "
       << DumpUsedOptimizationMethod()<< std::endl;

   if (int(GetBestFitParameters().size()) > 0) {
      ofi << " List of parameters and global mode:" << std::endl;
      for (int i = 0; i < npar; ++i) {
         ofi << "  (" << i << ") Parameter \""
             //<< fParameterSet->at(i)->GetName().data() << "\": "
             << fParameters.At(i).GetName().data() << "\": "//yfu
             << GetBestFitParameters()[i];
             if (int(GetBestFitParameterErrors().size()) == npar)
                if(GetBestFitParameterErrors()[i]>=0.)
                   ofi << " +- " << GetBestFitParameterErrors()[i];
         ofi << std::endl;
      }
      ofi << std::endl;
   }
   else {
      ofi << " No best fit information available." << std::endl;
      ofi << std::endl;
   }
/*
   if (fPValue >= 0.) {
      ofi << " Results of the model test" << std::endl
          << " =========================" << std::endl
          << " p-value at global mode: " << fPValue << std::endl << std::endl;
   }

   if (fNormalization >= 0.) {
       ofi << " Results of the normalization" << std::endl
             << " ============================" << std::endl
             << " Integration method used:"
             << DumpIntegrationMethod() << std::endl;
       ofi << " Normalization factor: " << fNormalization << std::endl << std::endl;
   }

   // give warning if MCMC did not converge
   if (!flag_conv && fMCMCFlagRun)
      ofi << " WARNING: the Markov Chain did not converge!" << std::endl
          << " Be cautious using the following results!" << std::endl
          << std::endl;

   // print results of marginalization (if MCMC was run)
   if (fMCMCFlagRun && fMCMCFlagFillHistograms) {
      ofi << " Results of the marginalization" << std::endl
          << " ==============================" << std::endl
          << " List of parameters and properties of the marginalized"
          << std::endl << " distributions:" << std::endl;
      for (int i = 0; i < npar; ++i) {
         if (!fMCMCFlagsFillHistograms[i])
            continue;

         BCH1D  bch1d = GetMarginalized(i);

         ofi << "  (" << i << ") Parameter \""
             << fParameters.At(i).GetName().data() << "\":" << std::endl

             << "      Mean +- sqrt(V):                " << std::setprecision(4)
             << bch1d.GetHistogram()->GetMean() << " +- " << std::setprecision(4)
             << bch1d.GetHistogram()->GetRMS() << std::endl

                   << "      Median +- central 68% interval: "
             << std::setprecision(4) << bch1d.GetMedian() << " +  "
             << std::setprecision(4) << bch1d.GetQuantile(0.84) - bch1d.GetMedian()
             << " - " << std::setprecision(4)
             << bch1d.GetMedian() - bch1d.GetQuantile(0.16) << std::endl

             << "      (Marginalized) mode:            " << bch1d.GetHistogram()->GetBinCenter(bch1d.GetHistogram()->GetMaximumBin()) << std::endl;

         ofi << "       5% quantile:                   " << std::setprecision(4)
             << bch1d.GetQuantile(0.05) << std::endl
             << "      10% quantile:                   " << std::setprecision(4)
             << bch1d.GetQuantile(0.10) << std::endl
             << "      16% quantile:                   " << std::setprecision(4)
             << bch1d.GetQuantile(0.16) << std::endl
             << "      84% quantile:                   " << std::setprecision(4)
             << bch1d.GetQuantile(0.85) << std::endl
             << "      90% quantile:                   " << std::setprecision(4)
             << bch1d.GetQuantile(0.90) << std::endl
             << "      95% quantile:                   " << std::setprecision(4)
             << bch1d.GetQuantile(0.95) << std::endl;

         std::vector<double> v;
         v = bch1d.GetSmallestIntervals(0.68);
         int ninter = int(v.size());
         ofi << "      Smallest interval(s) containing at least 68% and local mode(s):"
             << std::endl;
         for (int j = 0; j < ninter; j += 5)
            ofi << "       (" << v[j] << ", " << v[j + 1]
                << ") (local mode at " << v[j + 3] << " with rel. height "
                << v[j + 2] << "; rel. area " << v[j + 4] << ")"
                << std::endl;
            ofi << std::endl;
      }
   }

   if (fMCMCFlagRun) {
      ofi << " Status of the MCMC" << std::endl << " ==================" << std::endl
          << " Convergence reached:                    " << (flag_conv ? "yes" : "no")
          << std::endl;

      if (flag_conv)
         ofi << " Number of iterations until convergence: "
             << MCMCGetNIterationsConvergenceGlobal() << std::endl;
      else
         ofi << " WARNING: the Markov Chain did not converge! Be\n"
             << " cautious using the following results!" << std::endl
             << std::endl;
      ofi << " Number of chains:                       " << MCMCGetNChains() << std::endl
          << " Number of iterations per chain:         " << MCMCGetNIterationsRun() << std::endl
          << " Average efficiencies:" << std::endl;

      std::vector<double> efficiencies;
      efficiencies.assign(npar, 0.);

      for (int ipar = 0; ipar < npar; ++ipar)
         for (int ichain = 0; ichain < nchains; ++ichain) {
            int index = ichain * npar + ipar;
            efficiencies[ipar] +=
                  double(MCMCGetNTrialsTrue().at(index)) / double(MCMCGetNTrialsTrue().at(index)
                  + MCMCGetNTrialsFalse().at(index)) / double(nchains) * 100.;
         }

      for (int ipar = 0; ipar < npar; ++ipar)
         ofi << "  (" << ipar << ") Parameter \""
             << fParameterSet->at(ipar)->GetName().data() << "\": "
             << efficiencies.at(ipar) << "%" << std::endl;
      ofi << std::endl;
   }

    ofi << " -----------------------------------------------------" << std::endl
          << " Notation:" << std::endl
          << " Mean        : mean value of the marg. pdf" << std::endl
          << " Median      : maximum of the marg. pdf" << std::endl
          << " Marg. mode  : most probable value of the marg. pdf" << std::endl
          << " V           : Variance of the marg. pdf" << std::endl
          << " Quantiles   : most commonly used quantiles" <<std::endl
          << " -----------------------------------------------------" << std::endl
          << std::endl;

   // close file
   //   ofi.close;
*/
}

int BCMultiTemplateFitter::SetParameterRange(int index, double parmin, double parmax)
{
   // check index
   if (index < 0 || index >= int(GetNParameters())) {
      BCLog::OutError("BCModel::SetParameterRange : Index out of range.");
      return 0;
   }

   // set parameter ranges in BAT
   GetParameter(index).SetLowerLimit(parmin);
   GetParameter(index).SetUpperLimit(parmax);
   //fMCMCBoundaryMin[index] = parmin;
   //fMCMCBoundaryMax[index] = parmax;

   // reset results
   ResetResults();

   // no error
   return 1;
}
//--------------------------------------------------------------------------------------------//
