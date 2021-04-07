#pragma once

#include <iostream>
#include <string>

namespace TrMomBin
{
	const int N_TRMOM_BINS=4;

	enum E_TRMOM_BINS{ eTrMom0p00__0p25=0,
					   eTrMom0p25__0p50,
					   eTrMom0p50__0p75,
					   eTrMomGE__0p75,
					   eNONE
					 };

	const std::string S_TRMOM_BINS[ N_TRMOM_BINS ]=
					{ "TrMom0p00__0p25",
					  "TrMom0p25__0p50",
					  "TrMom0p50__0p75",
					  "TrMomGE__0p75"
					};

	const double BinEdges[N_TRMOM_BINS+1]=
					{ 0.0,
					  0.25,
					  0.5,
					  0.75,
					  1.5
					};
	
	enum E_TRMOM_BINS int2enum(const int);
	enum E_TRMOM_BINS getTrMomBin(const float);

};
