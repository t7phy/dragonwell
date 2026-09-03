#ifndef _CALIBRATION_H_
#define _CALIBRATION_H_

#include "Analysis/HistsResBos.h"
#include "Analysis/control.h"

#ifdef CalibrationForResBos_cxx
double Min_Chi2 = 1000000.0;
#endif

void RunResBosCalibration(Control run, HistsResBos *hists);
void CalibrationForResBos(Int_t &npbar, Double_t *gin, Double_t &f, Double_t *par, Int_t iflag);

#endif
