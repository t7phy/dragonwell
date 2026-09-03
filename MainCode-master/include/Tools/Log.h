#ifndef Tools_Log_h
#define Tools_Log_h

#include <iostream>
#include <fstream>
#include "TString.h"
#include "Tools/Tools.h"

/*namespace mylog
{
 void log(const char* format, ...);
}

#define LOG_INFO(...) \
 mylog::log(__VA_ARGS__)
*/

class Logbuf : public std::streambuf
{
 public:

 Logbuf(std::streambuf* stream1, std::streambuf* stream2)
 : stream1(stream1), stream2(stream2){}
 Logbuf(){}

 virtual void Initial(std::streambuf* stream1, std::streambuf* stream2)
 {
   this->stream1 = stream1;
   this->stream2 = stream2;
 }

 Logbuf(const Logbuf& myClass)
 {
   this->stream1 = myClass.stream1;
   this->stream2 = myClass.stream2;
 }

 Logbuf& operator=(const Logbuf &myClass)
 {
   if(this != &myClass){
     this->stream1 = myClass.stream1;
     this->stream2 = myClass.stream2;
   }
   return *this;
 }

 private:

 virtual int overflow(int c)
 {
   if(c == EOF){
     return !EOF;
   }
   else{
     int const r1 = stream1->sputc(c);
     int const r2 = stream2->sputc(c);
     return r1 == EOF || r2 == EOF ? EOF : c;
   }
 }

 virtual int sync()
 {
   int const r1 = stream1->pubsync();
   int const r2 = stream2->pubsync();
   return r1 == 0 || r2 == 0 ? 0 : -1;
 }

 private:

 std::streambuf* stream1;
 std::streambuf* stream2;
};

class Logstream : public std::ostream
{
 public:

 Logstream(std::ostream& o1, std::ostream& o2);
 Logstream();
 Logstream(const Logstream& myClass)
 {
   this->mybuf = myClass.mybuf;
 }

 virtual void Initial(std::ostream& o1, std::ostream& o2);
 Logstream& operator=(const Logstream &myClass);

 private:

 Logbuf mybuf;
};

#define LOG_INFO getTime()<<"  INFO| "
#define LOG_ERROR getTime()<<"  ERROR| "

#endif
