#pragma once

#include <string>
#include <iostream>
#include <cstdlib>

#include "TMath.h"

namespace IntCat
{

	const int 			N_INT_CAT	=10;
	const int 			N_ICAT_NTAG	=11;
	
	enum				E_INT_CAT{ eCC_1P1H	=0,
								   eCC_2P2H	=1,
								   eCC_RES	=2,
								   eCC_DIS	=3,
								   eCC_COH	=4,
								   eNC_1P1H	=5,
								   eNC_RES	=6,
								   eNC_DIS	=7,
								   eNC_COH	=8,
								   eNC_NUEL	=9,
								   eACCBKG	=10,
								   eNONE
								 };

	const std::string	S_INT_CAT[ N_ICAT_NTAG ]=
								{"cc_1p1h",
								 "cc_2p2h",
								 "cc_res",
								 "cc_dis",
								 "cc_coh",
								 "nc_1p1h",
								 "nc_res",
								 "nc_dis",
								 "nc_coh",
								 "nc_nuel",
								 "accbkg"
								};

	enum E_INT_CAT getNeutMode2IntCat(int);
	enum E_INT_CAT int2enum(int);
}
