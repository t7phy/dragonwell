#ifndef BATHelper_BCSYSTEMATIC__H
#define BATHelper_BCSYSTEMAITC__H

#include <string>

#include "RootCommon.h"

// ---------------------------------------------------------
class BCSystematic
{
 public:
	
	// Constructors and destructor
	BCSystematic(const char* name);
	~BCSystematic();
	
	// setters
	
	void SetFlagSystematicActive(bool flag)
	{ fFlagSystematicActive = flag; }; 
	
	// getters
	std::string GetName()
		{ return fSystematicName; }; 
	
	// return flag
	bool GetFlagSystematicActive()
	{ return fFlagSystematicActive; }; 

 private:

		// name of the systematic source
		std::string fSystematicName;

		// flag: systematic is used (true) or not (false) in fit
		bool fFlagSystematicActive; 
};
// ---------------------------------------------------------

#endif

