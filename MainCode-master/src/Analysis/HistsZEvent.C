#include "Analysis/HistsZEvent.h"

using namespace std;

void HistsZEvent::bookHists(int TotalThread)
{
 this->TotalThread = TotalThread;


 //////////////////////////////////////////////////////////////////////////////////////////////////////
 //  Define histograms:                                                                              //
 //                                                                                                  //
 //  1d histogram example:                                                                           //
 //  BookHist(ZMass, "ZMass", "ZMass", 100, 2000, 5000);                                             //
 //                                                                                                  //
 //  2d histogram example:                                                                           //
 //  Book2DHist(ZMass_ZY, "ZMass_ZY", "ZMass_ZY", 100, 2000, 5000, 10, -5, 5);                       //
 //                                                                                                  //
 //  3d histogram example:                                                                           //
 //  Book3DHist(ZMass_ZY_QT, "ZMass_ZY_QT", "ZMass_ZY_QT", 100, 2000, 5000, 10, -5, 5, 10, 0, 100);  //
 //////////////////////////////////////////////////////////////////////////////////////////////////////



}

void HistsZEvent::InitialSysName()
{

}
