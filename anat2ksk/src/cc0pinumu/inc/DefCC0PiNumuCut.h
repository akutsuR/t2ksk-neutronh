#pragma once

#include <string>

using namespace std;

namespace CC0PiNumuCut
{
	const int N_EVE_SLC=6;

	enum E_EVE_SLC{ eFCFVDW200=0,
					eNRING_EQ_1,
					eEMUPID_MU,
					eMUMOM_GE_200,
					eDCYE_LE_1,
					eCPIMUPID_MU
				  };

	const string S_EVE_SLC[ N_EVE_SLC ]=
			{ "fcfv_dw200",
			  "nring_eq_1",
			  "emupid_mulike",
			  "mumom_ge_200",
			  "dcye_le_1",
			  "cpimupid_mulike"
			};
};
