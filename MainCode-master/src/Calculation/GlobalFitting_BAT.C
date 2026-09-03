#include <BAT/BCGaussianPrior.h>
#include <BAT/BCMath.h>
#include "Calculation/GlobalFitting_BAT.h"

#include <cassert>

GlobalFitting_BAT::GlobalFitting_BAT(const std::string& name) : BCModel(name)
{

}

GlobalFitting_BAT::~GlobalFitting_BAT()
{

}

void GlobalFitting_BAT::Initialize()
{
 m_instance = new GlobalFittingCore();

 m_instance->Initialize();

 for(int i = 0; i < (m_instance->setting).GetNPar(); i++){
   Input((m_instance->setting).GetParName(i),
         (m_instance->setting).GetParCentral(i),
         (m_instance->setting).GetParStep(i),
         (m_instance->setting).GetParLeft(i),
         (m_instance->setting).GetParRight(i));
 }
}

double GlobalFitting_BAT::LogLikelihood(const std::vector<double>& pars)
{
 double logl = m_instance->chi2(pars);

 return -0.5*logl;
}

void GlobalFitting_BAT::Finalize()
{
 vector<double> pars = GetBestFitParameters();
 vector<double> parerrs = GetBestFitParameterErrors();

 m_instance->Finalize(pars, parerrs);
}

// this function is completely copied from ResBos2 code
void GlobalFitting_BAT::CalculateCorrelationMatrix() const {
    BCLog::Out(BCLog::LogLevel::summary, TString::Format("").Data());
    BCLog::Out(BCLog::LogLevel::summary,
                TString::Format(" Correlation Matrix").Data());
    BCLog::Out(BCLog::LogLevel::summary,
                TString::Format(" ==================").Data());
    BCLog::Out(BCLog::LogLevel::summary,
                TString::Format(" List of correlations between the variables:").Data());
    BCLog::Out(BCLog::LogLevel::summary, TString::Format("").Data());
    for(unsigned i = 0; i < GetNVariables(); ++i) {
        double var_i = (i < fMCMCStatistics_AllChains.variance.size())
            ? fMCMCStatistics_AllChains.variance[i]
            : std::numeric_limits<double>::infinity();
        for(unsigned j = i+1; j < GetNVariables(); ++j) {
            double var_j = (j < fMCMCStatistics_AllChains.variance.size())
                ? fMCMCStatistics_AllChains.variance[j]
                : std::numeric_limits<double>::infinity();
            double covar_ij = (i < fMCMCStatistics_AllChains.covariance.size()
                    && j < fMCMCStatistics_AllChains.covariance[i].size())
                ? fMCMCStatistics_AllChains.covariance[i][j]
                : std::numeric_limits<double>::infinity();
            double corr_ij = std::numeric_limits<double>::infinity();
            if(std::isfinite(covar_ij) && std::isfinite(var_i) && std::isfinite(var_j))
                corr_ij = covar_ij / sqrt(var_i * var_j);
            else if (i < fH2Marginalized.size() && j < fH2Marginalized[i].size()
                    && fH2Marginalized[i][j])
                corr_ij = fH2Marginalized[i][j] -> GetCorrelationFactor();
            else if (j < fH2Marginalized.size() && i < fH2Marginalized[j].size()
                    && fH2Marginalized[j][i])
                corr_ij = fH2Marginalized[j][i] -> GetCorrelationFactor();
            BCLog::Out(BCLog::LogLevel::summary,
                        TString::Format("  Corr(%s, %s) = %.4f",
                        GetVariable(i).GetLatexNameWithUnits().data(),
                        GetVariable(j).GetLatexNameWithUnits().data(),
                        corr_ij).Data());
        }
    }
    BCLog::Out(BCLog::LogLevel::summary, TString::Format("").Data());
}

