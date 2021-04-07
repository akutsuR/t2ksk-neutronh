#pragma once

#include <cstdlib>
#include <iostream>
#include "string"

#include "DefCC0PiNumuCut.h"

namespace EvSelHists
{
	const int N_EVSEL_HIST=6;

	enum E_EVSEL_HIST
		{ eEveSelSum=0,
		  eNRing,
		  eEMuPid,
		  eMomMu,
		  eDcyE,
		  eCPiMuPid
		};

	
	enum E_EVSEL_HIST int2enum(int);

	const std::string S_EVSEL_HIST[ N_EVSEL_HIST ]=
		{ "hevselsum",
		  "hnring",
		  "hemupid",
		  "hmomm",
		  "hdcye",
		  "hcpimupid"
		};

	const int NBINS[ N_EVSEL_HIST ]=
		{ CC0PiNumuCut::N_EVE_SLC,
		  5,
		  100,
		  80,
		  6,
		  80
		};

	const double XMIN[ N_EVSEL_HIST ]=
		{ 0.0,
		  1.0,
		  -1500,
		  0.0,
		  0.0,
		  -300.0
		};

	const double XMAX[ N_EVSEL_HIST ]=
		{ (double)CC0PiNumuCut::N_EVE_SLC,
		  6.0,
		  1500.0,
		  3000.0,
		  6.0,
		  100.0
		};


	const std::string TYPEDEF[ N_EVSEL_HIST ]=
		{ "f",
		  "i",
		  "f",
		  "f",
		  "i",
		  "f"
		};
}
