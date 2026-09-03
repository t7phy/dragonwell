#ifndef Calculation_hplog5_h
#define Calculation_hplog5_h

#include <array>
#include <complex>
#include <cmath>
#include <stdexcept>
#include <iostream>
#include <iomanip>

using namespace std;

namespace hplog5 {

 using cdouble = std::complex<double>;

 inline int map_index(int i, int n1) { return i - n1; }
 inline int extent(int n1, int n2) { return n2 - n1 + 1; }

 template<int Rank>
 struct HArr;

 template<>
 struct HArr<1> {
   int n1{}, n2{}, dim{};
   std::array<double,3> v{};
   void init(int n1_, int n2_) { n1=n1_; n2=n2_; dim=extent(n1,n2); }
   double& operator()(int i) { return v[map_index(i,n1)]; }
   const double& operator()(int i) const { return v[map_index(i,n1)]; }
 };

 template<>
 struct HArr<2> {
   int n1{}, n2{}, dim{};
   std::array<double,9> v{};
   void init(int n1_, int n2_) { n1=n1_; n2=n2_; dim=extent(n1,n2); }
   double& operator()(int i,int j){
     return v[map_index(i,n1)*dim + map_index(j,n1)];
   }
   const double& operator()(int i,int j) const {
     return v[map_index(i,n1)*dim + map_index(j,n1)];
   }
 };

 template<>
 struct HArr<3> {
   int n1{}, n2{}, dim{};
   std::array<double,27> v{};
   void init(int n1_, int n2_) { n1=n1_; n2=n2_; dim=extent(n1,n2); }
   double& operator()(int i,int j,int k){
     return v[(map_index(i,n1)*dim + map_index(j,n1))*dim + map_index(k,n1)];
   }
   const double& operator()(int i,int j,int k) const {
     return v[(map_index(i,n1)*dim + map_index(j,n1))*dim + map_index(k,n1)];
   }
 };

 template<>
 struct HArr<4> {
   int n1{}, n2{}, dim{};
   std::array<double,81> v{};
   void init(int n1_, int n2_) { n1=n1_; n2=n2_; dim=extent(n1,n2); }
   double& operator()(int a,int b,int c,int d){
     int ia=map_index(a,n1), ib=map_index(b,n1), ic=map_index(c,n1), id=map_index(d,n1);
     return v[ ((ia*dim + ib)*dim + ic)*dim + id ];
   }
   const double& operator()(int a,int b,int c,int d) const {
     int ia=map_index(a,n1), ib=map_index(b,n1), ic=map_index(c,n1), id=map_index(d,n1);
     return v[ ((ia*dim + ib)*dim + ic)*dim + id ];
   }
 };

 template<>
 struct HArr<5> {
   int n1{}, n2{}, dim{};
   std::array<double,243> v{};
   void init(int n1_, int n2_) { n1=n1_; n2=n2_; dim=extent(n1,n2); }
   double& operator()(int a,int b,int c,int d,int e){
     int ia=map_index(a,n1), ib=map_index(b,n1), ic=map_index(c,n1), id=map_index(d,n1), ie=map_index(e,n1);
     return v[ (((ia*dim + ib)*dim + ic)*dim + id)*dim + ie ];
   }
   const double& operator()(int a,int b,int c,int d,int e) const {
     int ia=map_index(a,n1), ib=map_index(b,n1), ic=map_index(c,n1), id=map_index(d,n1), ie=map_index(e,n1);
     return v[ (((ia*dim + ib)*dim + ic)*dim + id)*dim + ie ];
   }
 };

 template<int Rank>
 struct CArr;

 template<>
 struct CArr<1> {
   int n1{}, n2{}, dim{};
   std::array<cdouble,3> v{};
   void init(int n1_, int n2_) { n1=n1_; n2=n2_; dim=extent(n1,n2); }
   cdouble& operator()(int i) { return v[map_index(i,n1)]; }
   const cdouble& operator()(int i) const { return v[map_index(i,n1)]; }
 };

 template<>
 struct CArr<2> {
   int n1{}, n2{}, dim{};
   std::array<cdouble,9> v{};
   void init(int n1_, int n2_) { n1=n1_; n2=n2_; dim=extent(n1,n2); }
   cdouble& operator()(int i,int j){
     return v[map_index(i,n1)*dim + map_index(j,n1)];
   }
   const cdouble& operator()(int i,int j) const {
     return v[map_index(i,n1)*dim + map_index(j,n1)];
   }
 };

 template<>
 struct CArr<3> {
   int n1{}, n2{}, dim{};
   std::array<cdouble,27> v{};
   void init(int n1_, int n2_) { n1=n1_; n2=n2_; dim=extent(n1,n2); }
   cdouble& operator()(int i,int j,int k){
     return v[(map_index(i,n1)*dim + map_index(j,n1))*dim + map_index(k,n1)];
   }
   const cdouble& operator()(int i,int j,int k) const {
     return v[(map_index(i,n1)*dim + map_index(j,n1))*dim + map_index(k,n1)];
   }
 };

 template<>
 struct CArr<4> {
   int n1{}, n2{}, dim{};
   std::array<cdouble,81> v{};
   void init(int n1_, int n2_) { n1=n1_; n2=n2_; dim=extent(n1,n2); }
   cdouble& operator()(int a,int b,int c,int d){
     int ia=map_index(a,n1), ib=map_index(b,n1), ic=map_index(c,n1), id=map_index(d,n1);
     return v[ ((ia*dim + ib)*dim + ic)*dim + id ];
   }
   const cdouble& operator()(int a,int b,int c,int d) const {
     int ia=map_index(a,n1), ib=map_index(b,n1), ic=map_index(c,n1), id=map_index(d,n1);
     return v[ ((ia*dim + ib)*dim + ic)*dim + id ];
   }
 };

 template<>
 struct CArr<5> {
   int n1{}, n2{}, dim{};
   std::array<cdouble,243> v{};
   void init(int n1_, int n2_) { n1=n1_; n2=n2_; dim=extent(n1,n2); }
   cdouble& operator()(int a,int b,int c,int d,int e){
     int ia=map_index(a,n1), ib=map_index(b,n1), ic=map_index(c,n1), id=map_index(d,n1), ie=map_index(e,n1);
     return v[ (((ia*dim + ib)*dim + ic)*dim + id)*dim + ie ];
   }
   const cdouble& operator()(int a,int b,int c,int d,int e) const {
     int ia=map_index(a,n1), ib=map_index(b,n1), ic=map_index(c,n1), id=map_index(d,n1), ie=map_index(e,n1);
     return v[ (((ia*dim + ib)*dim + ic)*dim + id)*dim + ie ];
   }
 };

 template<int Rank>
 struct IArr;

 template<>
 struct IArr<1> {
   int n1{}, n2{}, dim{};
   std::array<int,3> v{};
   void init(int n1_, int n2_) { n1=n1_; n2=n2_; dim=extent(n1,n2); }
   int& operator()(int i) { return v[map_index(i,n1)]; }
   const int& operator()(int i) const { return v[map_index(i,n1)]; }
 };

 // Fortran COMMON blocks used with OpenMP threadprivate
 struct FillRedCommon {
   int infilldim = 0;
   std::array<int,4> infill{};
 };

 class hplog5
 {
  public:

  FillRedCommon fillred;

  hplog5();
  virtual void mainWrapper(double x, int nw,
                           CArr<1>& Hc1, CArr<2>& Hc2, CArr<3>& Hc3, CArr<4>& Hc4, CArr<5>& Hc5,
                           HArr<1>& Hr1, HArr<2>& Hr2, HArr<3>& Hr3, HArr<4>& Hr4, HArr<5>& Hr5,
                           HArr<1>& Hi1, HArr<2>& Hi2, HArr<3>& Hi3, HArr<4>& Hi4, HArr<5>& Hi5,
                           int n1, int n2);

  virtual void peval1dhplat0(double y,int nw, CArr<1>& H1, CArr<2>& H2, CArr<3>& H3, CArr<4>& H4, CArr<5>& H5,
                                              HArr<1>& HY1, HArr<2>& HY2, HArr<3>& HY3, HArr<4>& HY4, HArr<5>& HY5,
                                              HArr<1>& Hi1, HArr<2>& Hi2, HArr<3>& Hi3, HArr<4>& Hi4, HArr<5>& Hi5, int n1, int n2);
  virtual void peval1dhplin1(double y,int nw, CArr<1>& H1, CArr<2>& H2, CArr<3>& H3, CArr<4>& H4, CArr<5>& H5,
                                              HArr<1>& HY1, HArr<2>& HY2, HArr<3>& HY3, HArr<4>& HY4, HArr<5>& HY5,
                                              HArr<1>& Hi1, HArr<2>& Hi2, HArr<3>& Hi3, HArr<4>& Hi4, HArr<5>& Hi5, int n1, int n2);
  virtual void peval1dhplat1(double y,int nw, CArr<1>& H1, CArr<2>& H2, CArr<3>& H3, CArr<4>& H4, CArr<5>& H5,
                                              HArr<1>& HY1, HArr<2>& HY2, HArr<3>& HY3, HArr<4>& HY4, HArr<5>& HY5,
                                              HArr<1>& Hi1, HArr<2>& Hi2, HArr<3>& Hi3, HArr<4>& Hi4, HArr<5>& Hi5, int n1, int n2);
  virtual void peval1dhplatinf(double y,int nw, CArr<1>& H1, CArr<2>& H2, CArr<3>& H3, CArr<4>& H4, CArr<5>& H5,
                                                HArr<1>& HY1, HArr<2>& HY2, HArr<3>& HY3, HArr<4>& HY4, HArr<5>& HY5,
                                                HArr<1>& Hi1, HArr<2>& Hi2, HArr<3>& Hi3, HArr<4>& Hi4, HArr<5>& Hi5, int n1, int n2);
  virtual void peval1dhplinm1(double y,int nw, CArr<1>& H1, CArr<2>& H2, CArr<3>& H3, CArr<4>& H4, CArr<5>& H5,
                                               HArr<1>& HY1, HArr<2>& HY2, HArr<3>& HY3, HArr<4>& HY4, HArr<5>& HY5,
                                               HArr<1>& Hi1, HArr<2>& Hi2, HArr<3>& Hi3, HArr<4>& Hi4, HArr<5>& Hi5, int n1, int n2);
  virtual void peval1dhplatm1(double y,int nw, CArr<1>& H1, CArr<2>& H2, CArr<3>& H3, CArr<4>& H4, CArr<5>& H5,
                                               HArr<1>& HY1, HArr<2>& HY2, HArr<3>& HY3, HArr<4>& HY4, HArr<5>& HY5,
                                               HArr<1>& Hi1, HArr<2>& Hi2, HArr<3>& Hi3, HArr<4>& Hi4, HArr<5>& Hi5, int n1, int n2);
  virtual void peval1dhplatminf(double y,int nw, CArr<1>& H1, CArr<2>& H2, CArr<3>& H3, CArr<4>& H4, CArr<5>& H5,
                                                 HArr<1>& HY1, HArr<2>& HY2, HArr<3>& HY3, HArr<4>& HY4, HArr<5>& HY5,
                                                 HArr<1>& Hi1, HArr<2>& Hi2, HArr<3>& Hi3, HArr<4>& Hi4, HArr<5>& Hi5, int n1, int n2);

  virtual void psetzero(int nw, HArr<1>& Hi1, HArr<2>& Hi2, HArr<3>& Hi3, HArr<4>& Hi4, HArr<5>& Hi5,
                        int n1, int n2);
  virtual void psetzero(int nw, CArr<1>& Hc1, CArr<2>& Hc2, CArr<3>& Hc3, CArr<4>& Hc4, CArr<5>& Hc5,
                        int n1, int n2);

  virtual void pfillred1dhpl(int nw, CArr<1>& H1, CArr<2>& H2, CArr<3>& H3, CArr<4>& H4, CArr<5>& H5,
                                     HArr<1>& HY1, HArr<2>& HY2, HArr<3>& HY3, HArr<4>& HY4, HArr<5>& HY5,
                                     HArr<1>& Hi1, HArr<2>& Hi2, HArr<3>& Hi3, HArr<4>& Hi4, HArr<5>& Hi5, int n1, int n2);
  virtual void pFILLREDHPL2(int iflag, CArr<1>& H1, CArr<2>& H2, int i1, int i2, int na, int nb);
  virtual void pFILLREDHPL3(int iflag, CArr<1>& H1, CArr<2>& H2, CArr<3>& H3, int i1, int i2, int ia, int ib, int ic);
  virtual void pFILLREDHPL4(int iflag, CArr<1>& H1, CArr<2>& H2, CArr<3>& H3, CArr<4>& H4, int i1, int i2, int ia, int ib, int ic, int id);
  virtual void pprinter2(int na, int nb);
  virtual void pprinter3(int na, int nb, int nc);
  virtual void pprinter4(int na, int nb, int nc, int nd);
  virtual void psubprint(int n, int na);
  virtual void pFILLREDHPL5(int iflag, CArr<1>& HZ1, CArr<2>& HZ2, CArr<3>& HZ3, CArr<4>& HZ4, CArr<5>& HZ5, int n1, int n2);
  virtual void pfillh1(double y, CArr<1>& H1, HArr<1>& HY1, HArr<1>& Hi1, int n1, int n2);
  virtual void pfillirr1dhplat0(double y, int nw, HArr<1>& HY1, HArr<2>& HY2, HArr<3>& HY3, HArr<4>& HY4, HArr<5>& HY5, int n1, int n2);
  virtual void pfillirr1dhplat1(double r, int nw, HArr<1>& HR1, HArr<2>& HR2, HArr<3>& HR3, HArr<4>& HR4, HArr<5>& HR5,
                                                  HArr<1>& HY1, HArr<2>& HY2, HArr<3>& HY3, HArr<4>& HY4, HArr<5>& HY5,
                                                  HArr<1>& Hi1, HArr<2>& Hi2, HArr<3>& Hi3, HArr<4>& Hi4, HArr<5>& Hi5, int n1, int n2);
  virtual void pfillirr1dhplatinf(double x, int nw, HArr<1>& HX1, HArr<2>& HX2, HArr<3>& HX3, HArr<4>& HX4, HArr<5>& HX5,
                                                    HArr<1>& HY1, HArr<2>& HY2, HArr<3>& HY3, HArr<4>& HY4, HArr<5>& HY5,
                                                    HArr<1>& Hi1, HArr<2>& Hi2, HArr<3>& Hi3, HArr<4>& Hi4, HArr<5>& Hi5, int n1, int n2);
  virtual void pfillirr1dhplin1(double y, int nw, HArr<1>& HY1, HArr<2>& HY2, HArr<3>& HY3, HArr<4>& HY4, HArr<5>& HY5, int n1, int n2);

 };
}

#endif
