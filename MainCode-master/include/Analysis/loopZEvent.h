#ifndef loopZEvent_h
#define loopZEvent_h

#include "Analysis/loopMC.h"

#include "Analysis/HistsZEvent.h"
#include "Analysis/TreeForZEvent.h"

using namespace std;

class loopZEvent : public loopMC
{
 public:

 HistsZEvent *myhists;

 TreeForZEvent *ZEventTree;

 bool isCut = false;

 loopZEvent(TString RootType);
 virtual void InputHist(HistsZEvent* &myhists);
 virtual void InputTree(TreeForZEvent *ZEventTree);
 virtual void ReadTree(int ifile);
 virtual void End(int RootNumber);
 virtual void Finish();
 virtual ~loopZEvent();

};
#endif
