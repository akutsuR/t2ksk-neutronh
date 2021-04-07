#pragma once

#include <string>

namespace NtagCat
{
	const int N_NTAG_CAT=3;
	enum E_NTAG_CAT{ eMCN=0,
					 eBKG,
					 eALL,
					 eNONE
				   };

	const std::string S_NTAG_CAT[ N_NTAG_CAT ]=
				   { "mcn",
					 "bkg",
					 "all"
				   };

	enum E_NTAG_CAT getNTagCat(int);
	enum E_NTAG_CAT int2enum(int);
}
