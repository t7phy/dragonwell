#ifndef Common_h
#define Common_h

#include <iostream>
#include <fstream>
#include <pthread.h>

#include "TMinuitHelper/TMinuitHelper.h"

#include "Analysis/loopMC.h"

#include "Tools/Tools.h"
#include "Tools/Log.h"
#include "RootCommon.h"

#include "Analysis/loopMC.h"
#include "Analysis/control.h"

#include "Analysis/loopResBos.h"
#include "Analysis/HistsResBos.h"
#include "Analysis/TreeForResBos.h"
#include "Analysis/loopResBosW.h"
#include "Analysis/HistsResBosW.h"
#include "Analysis/loopResBosWTev.h"
#include "Analysis/HistsResBosWTev.h"
//#include "Calibration/Calibration.h"

#include "Analysis/loopPythia.h"
#include "Analysis/HistsPythia.h"
#include "Analysis/TreeForPythia.h"

#include "Analysis/loopPythiaW.h"
#include "Analysis/HistsPythiaW.h"
#include "Analysis/TreeForPythiaW.h"

#include "Analysis/loopPythiaWW.h"
#include "Analysis/HistsPythiaWW.h"
#include "Analysis/TreeForPythiaWW.h"

#include "Analysis/loopZEvent.h"
#include "Analysis/HistsZEvent.h"
#include "Analysis/TreeForZEvent.h"

#include "Analysis/loopHerwig.h"
#include "Analysis/HistsHerwig.h"
#include "Analysis/TreeForHerwig.h"

#include "Analysis/loopFwdReco.h"
#include "Analysis/HistsFwdReco.h"
#include "Analysis/TreeForFwdReco.h"

#include "Wasymmetry/loopWasym.h"
#include "Wasymmetry/HistsWasym.h"
#include "Wasymmetry/TreeForWasym.h"

#include "Tools/SumOfWeightHelper.h"
#include "WZPolarization/loopWZPolarization.h"
#include "WZPolarization/HistsWZPolarization.h"
#include "WZPolarization/TreeForWZPolarization.h"
#include "WZPolarization/TreeForPreWZPolarization.h"

#include "Analysis/loopCustom.h"
#include "Analysis/HistsCustom.h"
#include "Analysis/TreeForCustom.h"

#include "Analysis/loopCellInfo.h"
#include "Analysis/HistsCellInfo.h"
#include "Analysis/TreeForCellInfo.h"

#include "Analysis/loopSherpaWW.h"
#include "Analysis/HistsSherpaWW.h"
#include "Analysis/TreeForSherpaWW.h"

#include "Analysis/loopResBosCMS.h"
#include "Analysis/HistsResBosCMS.h"
#include "Analysis/TreeForResBosCMS.h"

#include "Analysis/loopResBosD0.h"
#include "Analysis/HistsResBosD0.h"
#include "Analysis/TreeForResBosD0.h"

#include "Analysis/loopFlavorAsym.h"
#include "Analysis/HistsFlavorAsym.h"
#include "Analysis/TreeForFlavorAsym.h"

#include "Analysis/loopResBosHighMassZ.h"
#include "Analysis/HistsResBosHighMassZ.h"
#include "Analysis/TreeForResBosHighMassZ.h"

#include "Analysis/loopMadGraph.h"
#include "Analysis/HistsMadGraph.h"
#include "Analysis/TreeForMadGraph.h"

#include "QBH/loopQBH.h"
#include "QBH/HistsQBH.h"
#include "QBH/TreeForQBH.h"
#include "QBH/TreeForPreQBH.h"

#include "HighMassDY/loopHMDY.h"
#include "HighMassDY/HistsHMDY.h"
#include "HighMassDY/TreeForHMDY.h"
#include "HighMassDY/TreeForPreHMDY.h"

#include "ZPrime/loopZPrime.h"
#include "ZPrime/HistsZPrime.h"
#include "ZPrime/TreeForZPrime.h"
#include "ZPrime/TreeForPreZPrime.h"

extern pthread_mutex_t mtx;

void* StartThread(void* arg);

void ThreadRunResBos(Control process);
void CondorRunResBos(Control process);

void ThreadRunResBosEnergyScale(Control process);
void CondorRunResBosEnergyScale(Control process);

void ThreadRunResBosW(Control process);
void CondorRunResBosW(Control process);

void ThreadRunResBosWTev(Control process);
void CondorRunResBosWTev(Control process);

void ThreadRunPythia(Control process, HistsPythia* myhists, int prerunFlag = 0);
void CondorRunPythia(Control process, HistsPythia* myhists, int prerunFlag = 0);

void ThreadRunPythiaW(Control process);
void CondorRunPythiaW(Control process);

void ThreadRunPythiaWW(Control process);
void CondorRunPythiaWW(Control process);

void ThreadRunZEvent(Control process);
void CondorRunZEvent(Control process);

void ThreadRunHerwig(Control process);
void CondorRunHerwig(Control process);

void ThreadRunFwdReco(Control process);
void CondorRunFwdReco(Control process);

void ThreadRunWasym(Control process);
void CondorRunWasym(Control process);

void ThreadRunWZPolarization(Control process, HistsWZPolarization* myhists);
void ThreadRunPreWZPolarization(Control process, HistsWZPolarization* myhists);
void CondorRunWZPolarization(Control process, HistsWZPolarization* myhists);
void CondorRunPreWZPolarization(Control process, HistsWZPolarization* myhists);

void ThreadRunCustom(Control process);
void CondorRunCustom(Control process);

void ThreadRunCellInfo(Control process);
void CondorRunCellInfo(Control process);

void ThreadRunSherpaWW(Control process);
void CondorRunSherpaWW(Control process);

void ThreadRunResBosCMS(Control process);
void CondorRunResBosCMS(Control process);

void ThreadRunResBosD0(Control process);
void CondorRunResBosD0(Control process);

void ThreadRunFlavorAsym(Control process);
void CondorRunFlavorAsym(Control process);

void ThreadRunResBosHighMassZ(Control process);
void CondorRunResBosHighMassZ(Control process);

void ThreadRunMadGraph(Control process);
void CondorRunMadGraph(Control process);

void ThreadRunQBH(Control process, HistsQBH* myhists);
void ThreadRunPreQBH(Control process, HistsQBH* myhists);
void CondorRunQBH(Control process, HistsQBH* myhists);
void CondorRunPreQBH(Control process, HistsQBH* myhists);

void ThreadRunHMDY(Control process, HistsHMDY* myhists);
void ThreadRunPreHMDY(Control process, HistsHMDY* myhists);
void CondorRunHMDY(Control process, HistsHMDY* myhists);
void CondorRunPreHMDY(Control process, HistsHMDY* myhists);

void ThreadRunZPrime(Control process, HistsZPrime* myhists);
void ThreadRunPreZPrime(Control process, HistsZPrime* myhists);
void CondorRunZPrime(Control process, HistsZPrime* myhists);
void CondorRunPreZPrime(Control process, HistsZPrime* myhists);

#endif

