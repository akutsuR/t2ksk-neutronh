#pragma once

#include <string>
#include <iostream>

#include "TROOT.h"

#include "DefIntCat.h"
#include "DefOscChannels.h"

using std::string;

namespace NuNubarBrkDwn
{
	const int N_BKDN_COMP=2;
	enum E_BKDN_COMP{ eNU=0,
					  eNUBAR,
					  eNONE
					};

	const std::string S_BKDN_COMP[ N_BKDN_COMP ]=
					{ "nu",
					  "nubar"
					};

	const std::string S_BKDN_COMP_LEGE[ N_BKDN_COMP ]=
					{ "#nu",
					  "#bar{#nu}"
					 };

	const int color[ N_BKDN_COMP ]=
					{ kTeal-1,
					  kPink-1
					};

	enum E_BKDN_COMP getNuNubarBrkDwn(enum OscChan::E_OSC_CHAN, enum IntCat::E_INT_CAT);
	enum E_BKDN_COMP getNuNubarBrkDwn(int, int);
}
