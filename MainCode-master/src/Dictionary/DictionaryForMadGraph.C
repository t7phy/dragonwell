// Do NOT change. Changes will be lost next time file is generated

#define R__DICTIONARY_FILENAME DictionaryForMadGraph
#define R__NO_DEPRECATION

/*******************************************************************/
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#define G__DICTIONARY
#include "RConfig.h"
#include "TClass.h"
#include "TDictAttributeMap.h"
#include "TInterpreter.h"
#include "TROOT.h"
#include "TBuffer.h"
#include "TMemberInspector.h"
#include "TInterpreter.h"
#include "TVirtualMutex.h"
#include "TError.h"

#ifndef G__ROOT
#define G__ROOT
#endif

#include "RtypesImp.h"
#include "TIsAProxy.h"
#include "TFileMergeInfo.h"
#include <algorithm>
#include "TCollectionProxyInfo.h"
/*******************************************************************/

#include "TDataMember.h"

// The generated code does not explicitly qualifies STL entities
namespace std {} using namespace std;

// Header files passed as explicit arguments
#include "/msu/data/t3work12/yaofu/MainCode/include/Analysis/TreeForMadGraph.h"
#include "/msu/data/t3work12/yaofu/MainCode/include/Analysis/ExRootClasses.h"
#include "ExRootClasses.h"
#include "ExRootClasses.h"

// Header files passed via #pragma extra_include

namespace ROOT {
   static void delete_TSortableObject(void *p);
   static void deleteArray_TSortableObject(void *p);
   static void destruct_TSortableObject(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const ::TSortableObject*)
   {
      ::TSortableObject *ptr = 0;
      static ::TVirtualIsAProxy* isa_proxy = new ::TInstrumentedIsAProxy< ::TSortableObject >(0);
      static ::ROOT::TGenericClassInfo 
         instance("TSortableObject", ::TSortableObject::Class_Version(), "", 37,
                  typeid(::TSortableObject), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &::TSortableObject::Dictionary, isa_proxy, 4,
                  sizeof(::TSortableObject) );
      instance.SetDelete(&delete_TSortableObject);
      instance.SetDeleteArray(&deleteArray_TSortableObject);
      instance.SetDestructor(&destruct_TSortableObject);
      return &instance;
   }
   TGenericClassInfo *GenerateInitInstance(const ::TSortableObject*)
   {
      return GenerateInitInstanceLocal((::TSortableObject*)0);
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_DICT_(Init) = GenerateInitInstanceLocal((const ::TSortableObject*)0x0); R__UseDummy(_R__UNIQUE_DICT_(Init));
} // end of namespace ROOT

namespace ROOT {
   static void *new_TRootWeight(void *p = 0);
   static void *newArray_TRootWeight(Long_t size, void *p);
   static void delete_TRootWeight(void *p);
   static void deleteArray_TRootWeight(void *p);
   static void destruct_TRootWeight(void *p);
   static void streamer_TRootWeight(TBuffer &buf, void *obj);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const ::TRootWeight*)
   {
      ::TRootWeight *ptr = 0;
      static ::TVirtualIsAProxy* isa_proxy = new ::TInstrumentedIsAProxy< ::TRootWeight >(0);
      static ::ROOT::TGenericClassInfo 
         instance("TRootWeight", ::TRootWeight::Class_Version(), "", 51,
                  typeid(::TRootWeight), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &::TRootWeight::Dictionary, isa_proxy, 16,
                  sizeof(::TRootWeight) );
      instance.SetNew(&new_TRootWeight);
      instance.SetNewArray(&newArray_TRootWeight);
      instance.SetDelete(&delete_TRootWeight);
      instance.SetDeleteArray(&deleteArray_TRootWeight);
      instance.SetDestructor(&destruct_TRootWeight);
      instance.SetStreamerFunc(&streamer_TRootWeight);
      return &instance;
   }
   TGenericClassInfo *GenerateInitInstance(const ::TRootWeight*)
   {
      return GenerateInitInstanceLocal((::TRootWeight*)0);
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_DICT_(Init) = GenerateInitInstanceLocal((const ::TRootWeight*)0x0); R__UseDummy(_R__UNIQUE_DICT_(Init));
} // end of namespace ROOT

namespace ROOT {
   static void *new_TRootLHEFEvent(void *p = 0);
   static void *newArray_TRootLHEFEvent(Long_t size, void *p);
   static void delete_TRootLHEFEvent(void *p);
   static void deleteArray_TRootLHEFEvent(void *p);
   static void destruct_TRootLHEFEvent(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const ::TRootLHEFEvent*)
   {
      ::TRootLHEFEvent *ptr = 0;
      static ::TVirtualIsAProxy* isa_proxy = new ::TInstrumentedIsAProxy< ::TRootLHEFEvent >(0);
      static ::ROOT::TGenericClassInfo 
         instance("TRootLHEFEvent", ::TRootLHEFEvent::Class_Version(), "", 61,
                  typeid(::TRootLHEFEvent), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &::TRootLHEFEvent::Dictionary, isa_proxy, 4,
                  sizeof(::TRootLHEFEvent) );
      instance.SetNew(&new_TRootLHEFEvent);
      instance.SetNewArray(&newArray_TRootLHEFEvent);
      instance.SetDelete(&delete_TRootLHEFEvent);
      instance.SetDeleteArray(&deleteArray_TRootLHEFEvent);
      instance.SetDestructor(&destruct_TRootLHEFEvent);
      return &instance;
   }
   TGenericClassInfo *GenerateInitInstance(const ::TRootLHEFEvent*)
   {
      return GenerateInitInstanceLocal((::TRootLHEFEvent*)0);
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_DICT_(Init) = GenerateInitInstanceLocal((const ::TRootLHEFEvent*)0x0); R__UseDummy(_R__UNIQUE_DICT_(Init));
} // end of namespace ROOT

namespace ROOT {
   static void *new_TRootLHEFParticle(void *p = 0);
   static void *newArray_TRootLHEFParticle(Long_t size, void *p);
   static void delete_TRootLHEFParticle(void *p);
   static void deleteArray_TRootLHEFParticle(void *p);
   static void destruct_TRootLHEFParticle(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const ::TRootLHEFParticle*)
   {
      ::TRootLHEFParticle *ptr = 0;
      static ::TVirtualIsAProxy* isa_proxy = new ::TInstrumentedIsAProxy< ::TRootLHEFParticle >(0);
      static ::ROOT::TGenericClassInfo 
         instance("TRootLHEFParticle", ::TRootLHEFParticle::Class_Version(), "", 80,
                  typeid(::TRootLHEFParticle), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &::TRootLHEFParticle::Dictionary, isa_proxy, 4,
                  sizeof(::TRootLHEFParticle) );
      instance.SetNew(&new_TRootLHEFParticle);
      instance.SetNewArray(&newArray_TRootLHEFParticle);
      instance.SetDelete(&delete_TRootLHEFParticle);
      instance.SetDeleteArray(&deleteArray_TRootLHEFParticle);
      instance.SetDestructor(&destruct_TRootLHEFParticle);
      return &instance;
   }
   TGenericClassInfo *GenerateInitInstance(const ::TRootLHEFParticle*)
   {
      return GenerateInitInstanceLocal((::TRootLHEFParticle*)0);
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_DICT_(Init) = GenerateInitInstanceLocal((const ::TRootLHEFParticle*)0x0); R__UseDummy(_R__UNIQUE_DICT_(Init));
} // end of namespace ROOT

namespace ROOT {
   static void *new_TRootGenParticle(void *p = 0);
   static void *newArray_TRootGenParticle(Long_t size, void *p);
   static void delete_TRootGenParticle(void *p);
   static void deleteArray_TRootGenParticle(void *p);
   static void destruct_TRootGenParticle(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const ::TRootGenParticle*)
   {
      ::TRootGenParticle *ptr = 0;
      static ::TVirtualIsAProxy* isa_proxy = new ::TInstrumentedIsAProxy< ::TRootGenParticle >(0);
      static ::ROOT::TGenericClassInfo 
         instance("TRootGenParticle", ::TRootGenParticle::Class_Version(), "", 130,
                  typeid(::TRootGenParticle), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &::TRootGenParticle::Dictionary, isa_proxy, 4,
                  sizeof(::TRootGenParticle) );
      instance.SetNew(&new_TRootGenParticle);
      instance.SetNewArray(&newArray_TRootGenParticle);
      instance.SetDelete(&delete_TRootGenParticle);
      instance.SetDeleteArray(&deleteArray_TRootGenParticle);
      instance.SetDestructor(&destruct_TRootGenParticle);
      return &instance;
   }
   TGenericClassInfo *GenerateInitInstance(const ::TRootGenParticle*)
   {
      return GenerateInitInstanceLocal((::TRootGenParticle*)0);
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_DICT_(Init) = GenerateInitInstanceLocal((const ::TRootGenParticle*)0x0); R__UseDummy(_R__UNIQUE_DICT_(Init));
} // end of namespace ROOT

namespace ROOT {
   static void *new_TRootMissingET(void *p = 0);
   static void *newArray_TRootMissingET(Long_t size, void *p);
   static void delete_TRootMissingET(void *p);
   static void deleteArray_TRootMissingET(void *p);
   static void destruct_TRootMissingET(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const ::TRootMissingET*)
   {
      ::TRootMissingET *ptr = 0;
      static ::TVirtualIsAProxy* isa_proxy = new ::TInstrumentedIsAProxy< ::TRootMissingET >(0);
      static ::ROOT::TGenericClassInfo 
         instance("TRootMissingET", ::TRootMissingET::Class_Version(), "", 201,
                  typeid(::TRootMissingET), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &::TRootMissingET::Dictionary, isa_proxy, 4,
                  sizeof(::TRootMissingET) );
      instance.SetNew(&new_TRootMissingET);
      instance.SetNewArray(&newArray_TRootMissingET);
      instance.SetDelete(&delete_TRootMissingET);
      instance.SetDeleteArray(&deleteArray_TRootMissingET);
      instance.SetDestructor(&destruct_TRootMissingET);
      return &instance;
   }
   TGenericClassInfo *GenerateInitInstance(const ::TRootMissingET*)
   {
      return GenerateInitInstanceLocal((::TRootMissingET*)0);
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_DICT_(Init) = GenerateInitInstanceLocal((const ::TRootMissingET*)0x0); R__UseDummy(_R__UNIQUE_DICT_(Init));
} // end of namespace ROOT

namespace ROOT {
   static void *new_TRootPhoton(void *p = 0);
   static void *newArray_TRootPhoton(Long_t size, void *p);
   static void delete_TRootPhoton(void *p);
   static void deleteArray_TRootPhoton(void *p);
   static void destruct_TRootPhoton(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const ::TRootPhoton*)
   {
      ::TRootPhoton *ptr = 0;
      static ::TVirtualIsAProxy* isa_proxy = new ::TInstrumentedIsAProxy< ::TRootPhoton >(0);
      static ::ROOT::TGenericClassInfo 
         instance("TRootPhoton", ::TRootPhoton::Class_Version(), "", 212,
                  typeid(::TRootPhoton), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &::TRootPhoton::Dictionary, isa_proxy, 4,
                  sizeof(::TRootPhoton) );
      instance.SetNew(&new_TRootPhoton);
      instance.SetNewArray(&newArray_TRootPhoton);
      instance.SetDelete(&delete_TRootPhoton);
      instance.SetDeleteArray(&deleteArray_TRootPhoton);
      instance.SetDestructor(&destruct_TRootPhoton);
      return &instance;
   }
   TGenericClassInfo *GenerateInitInstance(const ::TRootPhoton*)
   {
      return GenerateInitInstanceLocal((::TRootPhoton*)0);
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_DICT_(Init) = GenerateInitInstanceLocal((const ::TRootPhoton*)0x0); R__UseDummy(_R__UNIQUE_DICT_(Init));
} // end of namespace ROOT

namespace ROOT {
   static void *new_TRootElectron(void *p = 0);
   static void *newArray_TRootElectron(Long_t size, void *p);
   static void delete_TRootElectron(void *p);
   static void deleteArray_TRootElectron(void *p);
   static void destruct_TRootElectron(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const ::TRootElectron*)
   {
      ::TRootElectron *ptr = 0;
      static ::TVirtualIsAProxy* isa_proxy = new ::TInstrumentedIsAProxy< ::TRootElectron >(0);
      static ::ROOT::TGenericClassInfo 
         instance("TRootElectron", ::TRootElectron::Class_Version(), "", 231,
                  typeid(::TRootElectron), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &::TRootElectron::Dictionary, isa_proxy, 4,
                  sizeof(::TRootElectron) );
      instance.SetNew(&new_TRootElectron);
      instance.SetNewArray(&newArray_TRootElectron);
      instance.SetDelete(&delete_TRootElectron);
      instance.SetDeleteArray(&deleteArray_TRootElectron);
      instance.SetDestructor(&destruct_TRootElectron);
      return &instance;
   }
   TGenericClassInfo *GenerateInitInstance(const ::TRootElectron*)
   {
      return GenerateInitInstanceLocal((::TRootElectron*)0);
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_DICT_(Init) = GenerateInitInstanceLocal((const ::TRootElectron*)0x0); R__UseDummy(_R__UNIQUE_DICT_(Init));
} // end of namespace ROOT

namespace ROOT {
   static void *new_TRootMuon(void *p = 0);
   static void *newArray_TRootMuon(Long_t size, void *p);
   static void delete_TRootMuon(void *p);
   static void deleteArray_TRootMuon(void *p);
   static void destruct_TRootMuon(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const ::TRootMuon*)
   {
      ::TRootMuon *ptr = 0;
      static ::TVirtualIsAProxy* isa_proxy = new ::TInstrumentedIsAProxy< ::TRootMuon >(0);
      static ::ROOT::TGenericClassInfo 
         instance("TRootMuon", ::TRootMuon::Class_Version(), "", 254,
                  typeid(::TRootMuon), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &::TRootMuon::Dictionary, isa_proxy, 4,
                  sizeof(::TRootMuon) );
      instance.SetNew(&new_TRootMuon);
      instance.SetNewArray(&newArray_TRootMuon);
      instance.SetDelete(&delete_TRootMuon);
      instance.SetDeleteArray(&deleteArray_TRootMuon);
      instance.SetDestructor(&destruct_TRootMuon);
      return &instance;
   }
   TGenericClassInfo *GenerateInitInstance(const ::TRootMuon*)
   {
      return GenerateInitInstanceLocal((::TRootMuon*)0);
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_DICT_(Init) = GenerateInitInstanceLocal((const ::TRootMuon*)0x0); R__UseDummy(_R__UNIQUE_DICT_(Init));
} // end of namespace ROOT

namespace ROOT {
   static void *new_TRootTau(void *p = 0);
   static void *newArray_TRootTau(Long_t size, void *p);
   static void delete_TRootTau(void *p);
   static void deleteArray_TRootTau(void *p);
   static void destruct_TRootTau(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const ::TRootTau*)
   {
      ::TRootTau *ptr = 0;
      static ::TVirtualIsAProxy* isa_proxy = new ::TInstrumentedIsAProxy< ::TRootTau >(0);
      static ::ROOT::TGenericClassInfo 
         instance("TRootTau", ::TRootTau::Class_Version(), "", 282,
                  typeid(::TRootTau), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &::TRootTau::Dictionary, isa_proxy, 4,
                  sizeof(::TRootTau) );
      instance.SetNew(&new_TRootTau);
      instance.SetNewArray(&newArray_TRootTau);
      instance.SetDelete(&delete_TRootTau);
      instance.SetDeleteArray(&deleteArray_TRootTau);
      instance.SetDestructor(&destruct_TRootTau);
      return &instance;
   }
   TGenericClassInfo *GenerateInitInstance(const ::TRootTau*)
   {
      return GenerateInitInstanceLocal((::TRootTau*)0);
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_DICT_(Init) = GenerateInitInstanceLocal((const ::TRootTau*)0x0); R__UseDummy(_R__UNIQUE_DICT_(Init));
} // end of namespace ROOT

namespace ROOT {
   static void *new_TRootJet(void *p = 0);
   static void *newArray_TRootJet(Long_t size, void *p);
   static void delete_TRootJet(void *p);
   static void deleteArray_TRootJet(void *p);
   static void destruct_TRootJet(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const ::TRootJet*)
   {
      ::TRootJet *ptr = 0;
      static ::TVirtualIsAProxy* isa_proxy = new ::TInstrumentedIsAProxy< ::TRootJet >(0);
      static ::ROOT::TGenericClassInfo 
         instance("TRootJet", ::TRootJet::Class_Version(), "", 305,
                  typeid(::TRootJet), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &::TRootJet::Dictionary, isa_proxy, 4,
                  sizeof(::TRootJet) );
      instance.SetNew(&new_TRootJet);
      instance.SetNewArray(&newArray_TRootJet);
      instance.SetDelete(&delete_TRootJet);
      instance.SetDeleteArray(&deleteArray_TRootJet);
      instance.SetDestructor(&destruct_TRootJet);
      return &instance;
   }
   TGenericClassInfo *GenerateInitInstance(const ::TRootJet*)
   {
      return GenerateInitInstanceLocal((::TRootJet*)0);
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_DICT_(Init) = GenerateInitInstanceLocal((const ::TRootJet*)0x0); R__UseDummy(_R__UNIQUE_DICT_(Init));
} // end of namespace ROOT

//______________________________________________________________________________
atomic_TClass_ptr TSortableObject::fgIsA(0);  // static to hold class pointer

//______________________________________________________________________________
const char *TSortableObject::Class_Name()
{
   return "TSortableObject";
}

//______________________________________________________________________________
const char *TSortableObject::ImplFileName()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::TSortableObject*)0x0)->GetImplFileName();
}

//______________________________________________________________________________
int TSortableObject::ImplFileLine()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::TSortableObject*)0x0)->GetImplFileLine();
}

//______________________________________________________________________________
TClass *TSortableObject::Dictionary()
{
   fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::TSortableObject*)0x0)->GetClass();
   return fgIsA;
}

//______________________________________________________________________________
TClass *TSortableObject::Class()
{
   if (!fgIsA.load()) { R__LOCKGUARD(gInterpreterMutex); fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::TSortableObject*)0x0)->GetClass(); }
   return fgIsA;
}

//______________________________________________________________________________
atomic_TClass_ptr TRootWeight::fgIsA(0);  // static to hold class pointer

//______________________________________________________________________________
const char *TRootWeight::Class_Name()
{
   return "TRootWeight";
}

//______________________________________________________________________________
const char *TRootWeight::ImplFileName()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::TRootWeight*)0x0)->GetImplFileName();
}

//______________________________________________________________________________
int TRootWeight::ImplFileLine()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::TRootWeight*)0x0)->GetImplFileLine();
}

//______________________________________________________________________________
TClass *TRootWeight::Dictionary()
{
   fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::TRootWeight*)0x0)->GetClass();
   return fgIsA;
}

//______________________________________________________________________________
TClass *TRootWeight::Class()
{
   if (!fgIsA.load()) { R__LOCKGUARD(gInterpreterMutex); fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::TRootWeight*)0x0)->GetClass(); }
   return fgIsA;
}

//______________________________________________________________________________
atomic_TClass_ptr TRootLHEFEvent::fgIsA(0);  // static to hold class pointer

//______________________________________________________________________________
const char *TRootLHEFEvent::Class_Name()
{
   return "TRootLHEFEvent";
}

//______________________________________________________________________________
const char *TRootLHEFEvent::ImplFileName()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::TRootLHEFEvent*)0x0)->GetImplFileName();
}

//______________________________________________________________________________
int TRootLHEFEvent::ImplFileLine()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::TRootLHEFEvent*)0x0)->GetImplFileLine();
}

//______________________________________________________________________________
TClass *TRootLHEFEvent::Dictionary()
{
   fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::TRootLHEFEvent*)0x0)->GetClass();
   return fgIsA;
}

//______________________________________________________________________________
TClass *TRootLHEFEvent::Class()
{
   if (!fgIsA.load()) { R__LOCKGUARD(gInterpreterMutex); fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::TRootLHEFEvent*)0x0)->GetClass(); }
   return fgIsA;
}

//______________________________________________________________________________
atomic_TClass_ptr TRootLHEFParticle::fgIsA(0);  // static to hold class pointer

//______________________________________________________________________________
const char *TRootLHEFParticle::Class_Name()
{
   return "TRootLHEFParticle";
}

//______________________________________________________________________________
const char *TRootLHEFParticle::ImplFileName()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::TRootLHEFParticle*)0x0)->GetImplFileName();
}

//______________________________________________________________________________
int TRootLHEFParticle::ImplFileLine()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::TRootLHEFParticle*)0x0)->GetImplFileLine();
}

//______________________________________________________________________________
TClass *TRootLHEFParticle::Dictionary()
{
   fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::TRootLHEFParticle*)0x0)->GetClass();
   return fgIsA;
}

//______________________________________________________________________________
TClass *TRootLHEFParticle::Class()
{
   if (!fgIsA.load()) { R__LOCKGUARD(gInterpreterMutex); fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::TRootLHEFParticle*)0x0)->GetClass(); }
   return fgIsA;
}

//______________________________________________________________________________
atomic_TClass_ptr TRootGenParticle::fgIsA(0);  // static to hold class pointer

//______________________________________________________________________________
const char *TRootGenParticle::Class_Name()
{
   return "TRootGenParticle";
}

//______________________________________________________________________________
const char *TRootGenParticle::ImplFileName()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::TRootGenParticle*)0x0)->GetImplFileName();
}

//______________________________________________________________________________
int TRootGenParticle::ImplFileLine()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::TRootGenParticle*)0x0)->GetImplFileLine();
}

//______________________________________________________________________________
TClass *TRootGenParticle::Dictionary()
{
   fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::TRootGenParticle*)0x0)->GetClass();
   return fgIsA;
}

//______________________________________________________________________________
TClass *TRootGenParticle::Class()
{
   if (!fgIsA.load()) { R__LOCKGUARD(gInterpreterMutex); fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::TRootGenParticle*)0x0)->GetClass(); }
   return fgIsA;
}

//______________________________________________________________________________
atomic_TClass_ptr TRootMissingET::fgIsA(0);  // static to hold class pointer

//______________________________________________________________________________
const char *TRootMissingET::Class_Name()
{
   return "TRootMissingET";
}

//______________________________________________________________________________
const char *TRootMissingET::ImplFileName()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::TRootMissingET*)0x0)->GetImplFileName();
}

//______________________________________________________________________________
int TRootMissingET::ImplFileLine()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::TRootMissingET*)0x0)->GetImplFileLine();
}

//______________________________________________________________________________
TClass *TRootMissingET::Dictionary()
{
   fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::TRootMissingET*)0x0)->GetClass();
   return fgIsA;
}

//______________________________________________________________________________
TClass *TRootMissingET::Class()
{
   if (!fgIsA.load()) { R__LOCKGUARD(gInterpreterMutex); fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::TRootMissingET*)0x0)->GetClass(); }
   return fgIsA;
}

//______________________________________________________________________________
atomic_TClass_ptr TRootPhoton::fgIsA(0);  // static to hold class pointer

//______________________________________________________________________________
const char *TRootPhoton::Class_Name()
{
   return "TRootPhoton";
}

//______________________________________________________________________________
const char *TRootPhoton::ImplFileName()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::TRootPhoton*)0x0)->GetImplFileName();
}

//______________________________________________________________________________
int TRootPhoton::ImplFileLine()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::TRootPhoton*)0x0)->GetImplFileLine();
}

//______________________________________________________________________________
TClass *TRootPhoton::Dictionary()
{
   fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::TRootPhoton*)0x0)->GetClass();
   return fgIsA;
}

//______________________________________________________________________________
TClass *TRootPhoton::Class()
{
   if (!fgIsA.load()) { R__LOCKGUARD(gInterpreterMutex); fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::TRootPhoton*)0x0)->GetClass(); }
   return fgIsA;
}

//______________________________________________________________________________
atomic_TClass_ptr TRootElectron::fgIsA(0);  // static to hold class pointer

//______________________________________________________________________________
const char *TRootElectron::Class_Name()
{
   return "TRootElectron";
}

//______________________________________________________________________________
const char *TRootElectron::ImplFileName()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::TRootElectron*)0x0)->GetImplFileName();
}

//______________________________________________________________________________
int TRootElectron::ImplFileLine()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::TRootElectron*)0x0)->GetImplFileLine();
}

//______________________________________________________________________________
TClass *TRootElectron::Dictionary()
{
   fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::TRootElectron*)0x0)->GetClass();
   return fgIsA;
}

//______________________________________________________________________________
TClass *TRootElectron::Class()
{
   if (!fgIsA.load()) { R__LOCKGUARD(gInterpreterMutex); fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::TRootElectron*)0x0)->GetClass(); }
   return fgIsA;
}

//______________________________________________________________________________
atomic_TClass_ptr TRootMuon::fgIsA(0);  // static to hold class pointer

//______________________________________________________________________________
const char *TRootMuon::Class_Name()
{
   return "TRootMuon";
}

//______________________________________________________________________________
const char *TRootMuon::ImplFileName()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::TRootMuon*)0x0)->GetImplFileName();
}

//______________________________________________________________________________
int TRootMuon::ImplFileLine()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::TRootMuon*)0x0)->GetImplFileLine();
}

//______________________________________________________________________________
TClass *TRootMuon::Dictionary()
{
   fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::TRootMuon*)0x0)->GetClass();
   return fgIsA;
}

//______________________________________________________________________________
TClass *TRootMuon::Class()
{
   if (!fgIsA.load()) { R__LOCKGUARD(gInterpreterMutex); fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::TRootMuon*)0x0)->GetClass(); }
   return fgIsA;
}

//______________________________________________________________________________
atomic_TClass_ptr TRootTau::fgIsA(0);  // static to hold class pointer

//______________________________________________________________________________
const char *TRootTau::Class_Name()
{
   return "TRootTau";
}

//______________________________________________________________________________
const char *TRootTau::ImplFileName()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::TRootTau*)0x0)->GetImplFileName();
}

//______________________________________________________________________________
int TRootTau::ImplFileLine()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::TRootTau*)0x0)->GetImplFileLine();
}

//______________________________________________________________________________
TClass *TRootTau::Dictionary()
{
   fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::TRootTau*)0x0)->GetClass();
   return fgIsA;
}

//______________________________________________________________________________
TClass *TRootTau::Class()
{
   if (!fgIsA.load()) { R__LOCKGUARD(gInterpreterMutex); fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::TRootTau*)0x0)->GetClass(); }
   return fgIsA;
}

//______________________________________________________________________________
atomic_TClass_ptr TRootJet::fgIsA(0);  // static to hold class pointer

//______________________________________________________________________________
const char *TRootJet::Class_Name()
{
   return "TRootJet";
}

//______________________________________________________________________________
const char *TRootJet::ImplFileName()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::TRootJet*)0x0)->GetImplFileName();
}

//______________________________________________________________________________
int TRootJet::ImplFileLine()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::TRootJet*)0x0)->GetImplFileLine();
}

//______________________________________________________________________________
TClass *TRootJet::Dictionary()
{
   fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::TRootJet*)0x0)->GetClass();
   return fgIsA;
}

//______________________________________________________________________________
TClass *TRootJet::Class()
{
   if (!fgIsA.load()) { R__LOCKGUARD(gInterpreterMutex); fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::TRootJet*)0x0)->GetClass(); }
   return fgIsA;
}

//______________________________________________________________________________
void TSortableObject::Streamer(TBuffer &R__b)
{
   // Stream an object of class TSortableObject.

   if (R__b.IsReading()) {
      R__b.ReadClassBuffer(TSortableObject::Class(),this);
   } else {
      R__b.WriteClassBuffer(TSortableObject::Class(),this);
   }
}

namespace ROOT {
   // Wrapper around operator delete
   static void delete_TSortableObject(void *p) {
      delete ((::TSortableObject*)p);
   }
   static void deleteArray_TSortableObject(void *p) {
      delete [] ((::TSortableObject*)p);
   }
   static void destruct_TSortableObject(void *p) {
      typedef ::TSortableObject current_t;
      ((current_t*)p)->~current_t();
   }
} // end of namespace ROOT for class ::TSortableObject

//______________________________________________________________________________
void TRootWeight::Streamer(TBuffer &R__b)
{
   // Stream an object of class TRootWeight.

   UInt_t R__s, R__c;
   if (R__b.IsReading()) {
      Version_t R__v = R__b.ReadVersion(&R__s, &R__c); if (R__v) { }
      TObject::Streamer(R__b);
      R__b >> Weight;
      R__b.CheckByteCount(R__s, R__c, TRootWeight::IsA());
   } else {
      R__c = R__b.WriteVersion(TRootWeight::IsA(), kTRUE);
      TObject::Streamer(R__b);
      R__b << Weight;
      R__b.SetByteCount(R__c, kTRUE);
   }
}

namespace ROOT {
   // Wrappers around operator new
   static void *new_TRootWeight(void *p) {
      return  p ? new(p) ::TRootWeight : new ::TRootWeight;
   }
   static void *newArray_TRootWeight(Long_t nElements, void *p) {
      return p ? new(p) ::TRootWeight[nElements] : new ::TRootWeight[nElements];
   }
   // Wrapper around operator delete
   static void delete_TRootWeight(void *p) {
      delete ((::TRootWeight*)p);
   }
   static void deleteArray_TRootWeight(void *p) {
      delete [] ((::TRootWeight*)p);
   }
   static void destruct_TRootWeight(void *p) {
      typedef ::TRootWeight current_t;
      ((current_t*)p)->~current_t();
   }
   // Wrapper around a custom streamer member function.
   static void streamer_TRootWeight(TBuffer &buf, void *obj) {
      ((::TRootWeight*)obj)->::TRootWeight::Streamer(buf);
   }
} // end of namespace ROOT for class ::TRootWeight

//______________________________________________________________________________
void TRootLHEFEvent::Streamer(TBuffer &R__b)
{
   // Stream an object of class TRootLHEFEvent.

   if (R__b.IsReading()) {
      R__b.ReadClassBuffer(TRootLHEFEvent::Class(),this);
   } else {
      R__b.WriteClassBuffer(TRootLHEFEvent::Class(),this);
   }
}

namespace ROOT {
   // Wrappers around operator new
   static void *new_TRootLHEFEvent(void *p) {
      return  p ? new(p) ::TRootLHEFEvent : new ::TRootLHEFEvent;
   }
   static void *newArray_TRootLHEFEvent(Long_t nElements, void *p) {
      return p ? new(p) ::TRootLHEFEvent[nElements] : new ::TRootLHEFEvent[nElements];
   }
   // Wrapper around operator delete
   static void delete_TRootLHEFEvent(void *p) {
      delete ((::TRootLHEFEvent*)p);
   }
   static void deleteArray_TRootLHEFEvent(void *p) {
      delete [] ((::TRootLHEFEvent*)p);
   }
   static void destruct_TRootLHEFEvent(void *p) {
      typedef ::TRootLHEFEvent current_t;
      ((current_t*)p)->~current_t();
   }
} // end of namespace ROOT for class ::TRootLHEFEvent

//______________________________________________________________________________
void TRootLHEFParticle::Streamer(TBuffer &R__b)
{
   // Stream an object of class TRootLHEFParticle.

   if (R__b.IsReading()) {
      R__b.ReadClassBuffer(TRootLHEFParticle::Class(),this);
   } else {
      R__b.WriteClassBuffer(TRootLHEFParticle::Class(),this);
   }
}

namespace ROOT {
   // Wrappers around operator new
   static void *new_TRootLHEFParticle(void *p) {
      return  p ? new(p) ::TRootLHEFParticle : new ::TRootLHEFParticle;
   }
   static void *newArray_TRootLHEFParticle(Long_t nElements, void *p) {
      return p ? new(p) ::TRootLHEFParticle[nElements] : new ::TRootLHEFParticle[nElements];
   }
   // Wrapper around operator delete
   static void delete_TRootLHEFParticle(void *p) {
      delete ((::TRootLHEFParticle*)p);
   }
   static void deleteArray_TRootLHEFParticle(void *p) {
      delete [] ((::TRootLHEFParticle*)p);
   }
   static void destruct_TRootLHEFParticle(void *p) {
      typedef ::TRootLHEFParticle current_t;
      ((current_t*)p)->~current_t();
   }
} // end of namespace ROOT for class ::TRootLHEFParticle

//______________________________________________________________________________
void TRootGenParticle::Streamer(TBuffer &R__b)
{
   // Stream an object of class TRootGenParticle.

   if (R__b.IsReading()) {
      R__b.ReadClassBuffer(TRootGenParticle::Class(),this);
   } else {
      R__b.WriteClassBuffer(TRootGenParticle::Class(),this);
   }
}

namespace ROOT {
   // Wrappers around operator new
   static void *new_TRootGenParticle(void *p) {
      return  p ? new(p) ::TRootGenParticle : new ::TRootGenParticle;
   }
   static void *newArray_TRootGenParticle(Long_t nElements, void *p) {
      return p ? new(p) ::TRootGenParticle[nElements] : new ::TRootGenParticle[nElements];
   }
   // Wrapper around operator delete
   static void delete_TRootGenParticle(void *p) {
      delete ((::TRootGenParticle*)p);
   }
   static void deleteArray_TRootGenParticle(void *p) {
      delete [] ((::TRootGenParticle*)p);
   }
   static void destruct_TRootGenParticle(void *p) {
      typedef ::TRootGenParticle current_t;
      ((current_t*)p)->~current_t();
   }
} // end of namespace ROOT for class ::TRootGenParticle

//______________________________________________________________________________
void TRootMissingET::Streamer(TBuffer &R__b)
{
   // Stream an object of class TRootMissingET.

   if (R__b.IsReading()) {
      R__b.ReadClassBuffer(TRootMissingET::Class(),this);
   } else {
      R__b.WriteClassBuffer(TRootMissingET::Class(),this);
   }
}

namespace ROOT {
   // Wrappers around operator new
   static void *new_TRootMissingET(void *p) {
      return  p ? new(p) ::TRootMissingET : new ::TRootMissingET;
   }
   static void *newArray_TRootMissingET(Long_t nElements, void *p) {
      return p ? new(p) ::TRootMissingET[nElements] : new ::TRootMissingET[nElements];
   }
   // Wrapper around operator delete
   static void delete_TRootMissingET(void *p) {
      delete ((::TRootMissingET*)p);
   }
   static void deleteArray_TRootMissingET(void *p) {
      delete [] ((::TRootMissingET*)p);
   }
   static void destruct_TRootMissingET(void *p) {
      typedef ::TRootMissingET current_t;
      ((current_t*)p)->~current_t();
   }
} // end of namespace ROOT for class ::TRootMissingET

//______________________________________________________________________________
void TRootPhoton::Streamer(TBuffer &R__b)
{
   // Stream an object of class TRootPhoton.

   if (R__b.IsReading()) {
      R__b.ReadClassBuffer(TRootPhoton::Class(),this);
   } else {
      R__b.WriteClassBuffer(TRootPhoton::Class(),this);
   }
}

namespace ROOT {
   // Wrappers around operator new
   static void *new_TRootPhoton(void *p) {
      return  p ? new(p) ::TRootPhoton : new ::TRootPhoton;
   }
   static void *newArray_TRootPhoton(Long_t nElements, void *p) {
      return p ? new(p) ::TRootPhoton[nElements] : new ::TRootPhoton[nElements];
   }
   // Wrapper around operator delete
   static void delete_TRootPhoton(void *p) {
      delete ((::TRootPhoton*)p);
   }
   static void deleteArray_TRootPhoton(void *p) {
      delete [] ((::TRootPhoton*)p);
   }
   static void destruct_TRootPhoton(void *p) {
      typedef ::TRootPhoton current_t;
      ((current_t*)p)->~current_t();
   }
} // end of namespace ROOT for class ::TRootPhoton

//______________________________________________________________________________
void TRootElectron::Streamer(TBuffer &R__b)
{
   // Stream an object of class TRootElectron.

   if (R__b.IsReading()) {
      R__b.ReadClassBuffer(TRootElectron::Class(),this);
   } else {
      R__b.WriteClassBuffer(TRootElectron::Class(),this);
   }
}

namespace ROOT {
   // Wrappers around operator new
   static void *new_TRootElectron(void *p) {
      return  p ? new(p) ::TRootElectron : new ::TRootElectron;
   }
   static void *newArray_TRootElectron(Long_t nElements, void *p) {
      return p ? new(p) ::TRootElectron[nElements] : new ::TRootElectron[nElements];
   }
   // Wrapper around operator delete
   static void delete_TRootElectron(void *p) {
      delete ((::TRootElectron*)p);
   }
   static void deleteArray_TRootElectron(void *p) {
      delete [] ((::TRootElectron*)p);
   }
   static void destruct_TRootElectron(void *p) {
      typedef ::TRootElectron current_t;
      ((current_t*)p)->~current_t();
   }
} // end of namespace ROOT for class ::TRootElectron

//______________________________________________________________________________
void TRootMuon::Streamer(TBuffer &R__b)
{
   // Stream an object of class TRootMuon.

   if (R__b.IsReading()) {
      R__b.ReadClassBuffer(TRootMuon::Class(),this);
   } else {
      R__b.WriteClassBuffer(TRootMuon::Class(),this);
   }
}

namespace ROOT {
   // Wrappers around operator new
   static void *new_TRootMuon(void *p) {
      return  p ? new(p) ::TRootMuon : new ::TRootMuon;
   }
   static void *newArray_TRootMuon(Long_t nElements, void *p) {
      return p ? new(p) ::TRootMuon[nElements] : new ::TRootMuon[nElements];
   }
   // Wrapper around operator delete
   static void delete_TRootMuon(void *p) {
      delete ((::TRootMuon*)p);
   }
   static void deleteArray_TRootMuon(void *p) {
      delete [] ((::TRootMuon*)p);
   }
   static void destruct_TRootMuon(void *p) {
      typedef ::TRootMuon current_t;
      ((current_t*)p)->~current_t();
   }
} // end of namespace ROOT for class ::TRootMuon

//______________________________________________________________________________
void TRootTau::Streamer(TBuffer &R__b)
{
   // Stream an object of class TRootTau.

   if (R__b.IsReading()) {
      R__b.ReadClassBuffer(TRootTau::Class(),this);
   } else {
      R__b.WriteClassBuffer(TRootTau::Class(),this);
   }
}

namespace ROOT {
   // Wrappers around operator new
   static void *new_TRootTau(void *p) {
      return  p ? new(p) ::TRootTau : new ::TRootTau;
   }
   static void *newArray_TRootTau(Long_t nElements, void *p) {
      return p ? new(p) ::TRootTau[nElements] : new ::TRootTau[nElements];
   }
   // Wrapper around operator delete
   static void delete_TRootTau(void *p) {
      delete ((::TRootTau*)p);
   }
   static void deleteArray_TRootTau(void *p) {
      delete [] ((::TRootTau*)p);
   }
   static void destruct_TRootTau(void *p) {
      typedef ::TRootTau current_t;
      ((current_t*)p)->~current_t();
   }
} // end of namespace ROOT for class ::TRootTau

//______________________________________________________________________________
void TRootJet::Streamer(TBuffer &R__b)
{
   // Stream an object of class TRootJet.

   if (R__b.IsReading()) {
      R__b.ReadClassBuffer(TRootJet::Class(),this);
   } else {
      R__b.WriteClassBuffer(TRootJet::Class(),this);
   }
}

namespace ROOT {
   // Wrappers around operator new
   static void *new_TRootJet(void *p) {
      return  p ? new(p) ::TRootJet : new ::TRootJet;
   }
   static void *newArray_TRootJet(Long_t nElements, void *p) {
      return p ? new(p) ::TRootJet[nElements] : new ::TRootJet[nElements];
   }
   // Wrapper around operator delete
   static void delete_TRootJet(void *p) {
      delete ((::TRootJet*)p);
   }
   static void deleteArray_TRootJet(void *p) {
      delete [] ((::TRootJet*)p);
   }
   static void destruct_TRootJet(void *p) {
      typedef ::TRootJet current_t;
      ((current_t*)p)->~current_t();
   }
} // end of namespace ROOT for class ::TRootJet

namespace {
  void TriggerDictionaryInitialization_DictionaryForMadGraph_Impl() {
    static const char* headers[] = {
"/msu/data/t3work12/yaofu/MainCode/include/Analysis/TreeForMadGraph.h",
"/msu/data/t3work12/yaofu/MainCode/include/Analysis/ExRootClasses.h",
0
    };
    static const char* includePaths[] = {
"/cvmfs/sft.cern.ch/lcg/releases/ROOT/v6.20.06-3f7fd/x86_64-centos7-gcc8-opt/include/",
"/msu/data/t3work12/yaofu/MainCode/src/Dictionary/",
0
    };
    static const char* fwdDeclCode = R"DICTFWDDCLS(
#line 1 "DictionaryForMadGraph dictionary forward declarations' payload"
#pragma clang diagnostic ignored "-Wkeyword-compat"
#pragma clang diagnostic ignored "-Wignored-attributes"
#pragma clang diagnostic ignored "-Wreturn-type-c-linkage"
extern int __Cling_Autoloading_Map;
class __attribute__((annotate("$clingAutoload$ExRootClasses.h")))  TSortableObject;
class __attribute__((annotate("$clingAutoload$ExRootClasses.h")))  TRootWeight;
class __attribute__((annotate("$clingAutoload$ExRootClasses.h")))  TRootLHEFEvent;
class __attribute__((annotate("$clingAutoload$ExRootClasses.h")))  TRootLHEFParticle;
class __attribute__((annotate("$clingAutoload$ExRootClasses.h")))  TRootGenParticle;
class __attribute__((annotate("$clingAutoload$ExRootClasses.h")))  TRootMissingET;
class __attribute__((annotate("$clingAutoload$ExRootClasses.h")))  TRootPhoton;
class __attribute__((annotate("$clingAutoload$ExRootClasses.h")))  TRootElectron;
class __attribute__((annotate("$clingAutoload$ExRootClasses.h")))  TRootMuon;
class __attribute__((annotate("$clingAutoload$ExRootClasses.h")))  TRootTau;
class __attribute__((annotate("$clingAutoload$ExRootClasses.h")))  TRootJet;
)DICTFWDDCLS";
    static const char* payloadCode = R"DICTPAYLOAD(
#line 1 "DictionaryForMadGraph dictionary payload"


#define _BACKWARD_BACKWARD_WARNING_H
// Inline headers
#include "/msu/data/t3work12/yaofu/MainCode/include/Analysis/TreeForMadGraph.h"
#include "/msu/data/t3work12/yaofu/MainCode/include/Analysis/ExRootClasses.h"
/** \class ExRootAnalysisLinkDef
 *
 *  Lists classes to be included in cint dicitonary
 *
 *  $Date: 2006/09/22 14:15:42 $
 *  $Revision: 1.1 $
 *
 *  
 *  \author P. Demin - UCL, Louvain-la-Neuve
 *
 */

#include "ExRootClasses.h"

#ifdef __CINT__

#pragma link off all globals;
#pragma link off all classes;
#pragma link off all functions;

#pragma link C++ class TSortableObject+;
#pragma link C++ class TRootWeight;
#pragma link C++ class TRootLHEFEvent+;
#pragma link C++ class TRootLHEFParticle+;
#pragma link C++ class TRootGenParticle+;
//#pragma link C++ class TRootTrack+;
//#pragma link C++ class TRootCalTower+;
#pragma link C++ class TRootMissingET+;
//#pragma link C++ class TRootCalCluster+;
#pragma link C++ class TRootPhoton+;
#pragma link C++ class TRootElectron+;
#pragma link C++ class TRootMuon+;
#pragma link C++ class TRootTau+;
#pragma link C++ class TRootJet+;
//#pragma link C++ class TRootHeavy+;

//#pragma link C++ class ExRootTreeBranch+;
//#pragma link C++ class ExRootTreeWriter+;

#endif


#undef  _BACKWARD_BACKWARD_WARNING_H
)DICTPAYLOAD";
    static const char* classesHeaders[] = {
"TRootElectron", payloadCode, "@",
"TRootGenParticle", payloadCode, "@",
"TRootJet", payloadCode, "@",
"TRootLHEFEvent", payloadCode, "@",
"TRootLHEFParticle", payloadCode, "@",
"TRootMissingET", payloadCode, "@",
"TRootMuon", payloadCode, "@",
"TRootPhoton", payloadCode, "@",
"TRootTau", payloadCode, "@",
"TRootWeight", payloadCode, "@",
"TSortableObject", payloadCode, "@",
nullptr
};
    static bool isInitialized = false;
    if (!isInitialized) {
      TROOT::RegisterModule("DictionaryForMadGraph",
        headers, includePaths, payloadCode, fwdDeclCode,
        TriggerDictionaryInitialization_DictionaryForMadGraph_Impl, {}, classesHeaders, /*hasCxxModule*/false);
      isInitialized = true;
    }
  }
  static struct DictInit {
    DictInit() {
      TriggerDictionaryInitialization_DictionaryForMadGraph_Impl();
    }
  } __TheDictionaryInitializer;
}
void TriggerDictionaryInitialization_DictionaryForMadGraph() {
  TriggerDictionaryInitialization_DictionaryForMadGraph_Impl();
}
