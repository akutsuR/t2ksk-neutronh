#pragma once

#include <iostream>
#include <string>

namespace LepMomBin
{
	const int N_LEPMOM_BINS=4;

	enum E_LEPMOM_BINS{ eLepMom0p00__0p50=0,
					    eLepMom0p50__1p00,
					    eLepMom1p00__2p00,
					    eLepMomGE__2p00,
					    eNONE
					  };

	const std::string S_LEPMOM_BINS[ N_LEPMOM_BINS ]=
					{ "LepMom0p00__0p50",
					  "LepMom0p50__1p00",
					  "LepMom1p00__2p00",
					  "LepMomGE__2p00"
					};

	const double BinEdges[N_LEPMOM_BINS+1]=
					{ 0.0,
					  0.5,
					  1.0,
					  2.0,
					  6.0
					};
	
	enum E_LEPMOM_BINS int2enum(const int);
};
