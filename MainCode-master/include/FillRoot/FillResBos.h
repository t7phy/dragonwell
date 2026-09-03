#ifndef FillResBos_h
#define FillResBos_h

#include "FillRoot/FillRoot.h"

class FillResBos : public FillRoot
{
 public:

 float Px_d1;
 float Py_d1;
 float Pz_d1;
 float E_d1;
 float Px_d2;
 float Py_d2;
 float Pz_d2;
 float E_d2;

 float Px_V;
 float Py_V;
 float Pz_V;
 float E_V;

 float Px_g1;
 float Py_g1;
 float Pz_g1;
 float E_g1;
 float Px_g2;
 float Py_g2;
 float Pz_g2;
 float E_g2;

 float WT00;

 int evt;
 double skip;
 virtual void DefineTree();
 virtual void FillIn();
};
#endif
