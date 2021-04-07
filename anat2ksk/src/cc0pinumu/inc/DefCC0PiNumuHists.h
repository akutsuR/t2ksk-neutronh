#pragma once

#include <iostream>
#include <string>
#include <cstdlib>

using namespace std;

namespace CC0PiNumuSelec
{
	const int N_EVSEL_HIST=6;
	enum E_EVE_SLC{ eFCFVDW200=0,
					eNRING_EQ_1,
					eEMUPID_MU,
					eMUMOM_GE_200,
					eDCYE_LE_1,
					eCPIMUPID_MU
				  };


	const string S_EVE_SLC[ N_EVE_SLC ]=
			{ "fcfv_dw200",
			  "nring_eq_1"
			  "emupid_mulike",
			  "mumom_ge_200",
			  "dcye_le_1",
			  "cpimupid_mulike"
			};

	const int NBINS[ N_EVE_SLC ]=
			{ 1, 	/* dummy */
			  5,
			  100,
			  80,
			  6,
			  80
			};

	const float XMIN[ N_INPUT_VARS ]=
			{ 0.0,	/* dummy */
			  1.0, 
			  -1500.0,
			  0.0, 
			  0.0,
			  -300.0
			};

	const float XMAX[ N_INPUT_VARS ]=
			{ 1.0,	/* dummy */
			  25.0,
			  75.0,
			  1740.0,
			  5000.0,
			  7.5,
		    };

	const string TYPEDEF[ N_INPUT_VARS ]=
			{ "i",
			  "i",
			  "i",
			  "f",
			  "f",
			  "f"
			};
}
