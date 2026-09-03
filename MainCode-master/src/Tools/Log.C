#include "Tools/Log.h"

/*namespace mylog
{

void log(const char* format, ...)
{
 va_list vlist;
 va_start(vlist, format);

 TString total = "";
 TString tmp = "";
 while((tmp = va_arg(vlist, TString)) != ""){
  total += tmp;
 }

 va_end(vlist);

 std::cout<<total<<std::endl;
}

}
*/

Logstream::Logstream(std::ostream& o1, std::ostream& o2)
: std::ostream(&mybuf), mybuf(o1.rdbuf(), o2.rdbuf())
{

}

Logstream::Logstream()
: std::ostream(&mybuf)
{

}

void Logstream::Initial(std::ostream& o1, std::ostream& o2)
{
 mybuf.Initial(o1.rdbuf(), o2.rdbuf());
}

Logstream& Logstream::operator=(const Logstream &myClass)
{
 if(this != &myClass){
   this->mybuf = myClass.mybuf;
 }

 return *this;
}


