#define CutForWZPolarization(CutInfo, left, right, isCut)					\
  do											\
  {											\
    if(CutInfo == "0") isCut = false;							\
    if(CutInfo == "Lep1Pt"){								\
      if(ProcessEvent.Lep1Pt < left || ProcessEvent.Lep1Pt > right) isCut = true;			\
    }											\
    if(CutInfo == "Lep2Pt"){								\
      if(ProcessEvent.Lep2Pt < left || ProcessEvent.Lep2Pt > right) isCut = true;		\
    }											\
    if(CutInfo == "Lep3Pt"){								\
      if(ProcessEvent.Lep3Pt < left || ProcessEvent.Lep3Pt > right) isCut = true;				\
    }											\
    if(CutInfo == "Channel"){                                                            \
      if(!(ProcessEvent.DecayChannel >= (int)left && ProcessEvent.DecayChannel <= (int)right)) isCut = true;                               \
    }                                                                                   \
    if(CutInfo == "Njets"){                                                            \
      if(ProcessEvent.Njets < (int)left || ProcessEvent.Njets > (int)right) isCut = true;                               \
    }                                                                                   \
    if(CutInfo == "MissingET"){                                                            \
      if(ProcessEvent.Met < left || ProcessEvent.Met > right) isCut = true;                               \
    }                                                                                   \
    if(CutInfo == "WTransverseMass"){                                                            \
      if(ProcessEvent.Mt_W < left || ProcessEvent.Mt_W > right) isCut = true;                               \
    }                                                                                   \
    if(CutInfo == "ZPt"){                                                            \
      if(ProcessEvent.Pt_Z < left || ProcessEvent.Pt_Z > right) isCut = true;                               \
    }                                                                                   \
    if(CutInfo == "MuonEta"){                                                            \
      if(((fabs(ProcessEvent.Lep1Flavor) == 13 && fabs(ProcessEvent.Lep1Eta) < left) || (fabs(ProcessEvent.Lep1Flavor) == 13 && fabs(ProcessEvent.Lep1Eta) > right)) \
      || ((fabs(ProcessEvent.Lep2Flavor) == 13 && fabs(ProcessEvent.Lep2Eta) < left) || (fabs(ProcessEvent.Lep2Flavor) == 13 && fabs(ProcessEvent.Lep2Eta) > right)) \
      || ((fabs(ProcessEvent.Lep3Flavor) == 13 && fabs(ProcessEvent.Lep3Eta) < left) || (fabs(ProcessEvent.Lep3Flavor) == 13 && fabs(ProcessEvent.Lep3Eta) > right))) \
                                       isCut = true;                               \
    }                                                                                   \
    if(CutInfo == "Year"){                                                            \
      if(ProcessEvent.Year != (int)right) isCut = true;                               \
    }                                                                                   \
  } while(0);
