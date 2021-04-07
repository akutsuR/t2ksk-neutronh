#pragma once

#include <iostream>
#include <string>

namespace RecoQ2Bin
{
	const int N_RECOQ2_BINS=4;

	enum E_RECOQ2_BINS{ eRecoQ20p00__0p25=0,
					    eRecoQ20p25__0p50,
					    eRecoQ20p50__0p75,
					    eRecoQ2GE__0p75,
					    eNONE
					 };

	const std::string S_RECOQ2_BINS[ N_RECOQ2_BINS ]=
					{ "RecoQ20p00__0p25",
					  "RecoQ20p25__0p50",
					  "RecoQ20p50__0p75",
					  "RecoQ2GE__0p75"
					};

	const double BinEdges[N_RECOQ2_BINS+1]=
					{ 0.0,
					  0.25,
					  0.5,
					  0.75,
					  3.0
					};
	
	enum E_RECOQ2_BINS int2enum(const int);
};
