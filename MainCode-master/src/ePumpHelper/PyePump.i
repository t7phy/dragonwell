// ePumpHelper/PyePump.i
%module PyePump

%include <std_vector.i>
%include <std_string.i>

%template(DoubleVector) std::vector<double>;
%template(StringVector) std::vector<std::string>;

%{
  #include "ePumpHelper/PyePump.h"
%}

%include "ePumpHelper/PyePump.h"

