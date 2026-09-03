#define CutForPythia(CutInfo, left, right, isCut)                                       \
  do                                                                                    \
  {                                                                                     \
    if(CutInfo == "0") isCut = false;                                                   \
    if(CutInfo == "ZPt"){                                                               \
      if(ZBoson.Pt() < left || ZBoson.Pt() > right) isCut = true;                       \
    }                                                                                   \
    if(CutInfo == "ZY"){                                                                \
      if(ZBoson.Rapidity() < left || ZBoson.Rapidity() > right) isCut = true;           \
    }                                                                                   \
    if(CutInfo == "ZMass"){                                                             \
      if(ZBoson.M() < left || ZBoson.M() > right) isCut = true;                         \
    }                                                                                   \
    if(CutInfo == "absZY"){                                                             \
      if(fabs(ZBoson.Rapidity()) < left || fabs(ZBoson.Rapidity()) > right)             \
        isCut = true;                                                                   \
    }                                                                                   \
    if(CutInfo == "lepPt"){                                                             \
      if(Electron.Pt() < left || Positron.Pt() < left || Electron.Pt() > right || Positron.Pt() > right)\
        isCut = true;                                                                   \
    }                                                                                   \
    if(CutInfo == "lepEtaAbs"){                                                         \
      if(fabs(Electron.Eta()) < left || fabs(Electron.Eta()) > right || fabs(Positron.Eta()) < left || fabs(Positron.Eta()) > right)\
        isCut = true;                                                                   \
    }                                                                                   \
    if(CutInfo == "ZPzPtBalance"){                                                             \
      if(fabs(ZBoson.Pz()) / ZBoson.Pt() < left || fabs(ZBoson.Pz()) / ZBoson.Pt() > right)             \
        isCut = true;                                                                   \
    }                                                                                   \
  } while(0);

