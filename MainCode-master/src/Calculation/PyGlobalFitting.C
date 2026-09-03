#include "Calculation/PyGlobalFitting.h"

PyGlobalFitting::PyGlobalFitting()
{

}

PyGlobalFitting::~PyGlobalFitting()
{

}

void PyGlobalFitting::Initialize()
{
 m_instance = new GlobalFittingCore();

 m_instance->Initialize();
}

double PyGlobalFitting::Chi2(const std::vector<double>& pars)
{
 double chi2 = m_instance->chi2(pars);

 return chi2;
}

void PyGlobalFitting::Finalize(std::vector<double> pars, std::vector<double> parerrs)
{
 m_instance->Finalize(pars, parerrs);
}

void PyGlobalFitting::ResetFit()
{
 m_instance->ResetFit();
}

void PyGlobalFitting::UpdateParameterCentral()
{
 m_instance->UpdateParameterCentral();
}

double PyGlobalFitting::GetDeltaChi2()
{
 return m_instance->DeltaChi2;
}

int PyGlobalFitting::GetLFit()
{
 return m_instance->setting.LFit;
}

int PyGlobalFitting::GetMaxCall()
{
 return m_instance->setting.MaxCall;
}

double PyGlobalFitting::GetMinTol()
{
 return m_instance->setting.MinTol;
}

std::vector<double> PyGlobalFitting::GetInitialParameters()
{
 return m_instance->GetInitialParameters();
}

std::vector<double> PyGlobalFitting::GetTheoryPrediction(std::string name)
{
 return m_instance->m_fcn->GetTheoryPrediction(name.c_str());
}

