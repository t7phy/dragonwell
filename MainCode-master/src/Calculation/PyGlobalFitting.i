// Calculation/PyGlobalFitting.i
%module PyGlobalFitting

%include <std_vector.i>
%include <std_string.i>

%template(DoubleVector) std::vector<double>;

%{
  #include "Calculation/PyGlobalFitting.h"
%}

%include "Calculation/PyGlobalFitting.h"

