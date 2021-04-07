#pragma once

#include <iostream>
#include <string>

namespace RecoEnuBin
{
	const int N_RECOENU_BINS=5;

	enum E_RECOENU_BINS{ eRecoEnu0p00__0p50=0,
					     eRecoEnu0p25__1p00,
					     eRecoEnu0p50__1p50,
					     eRecoEnu1p50__2p50,
					     eRecoEnuGE__2p50,
					     eNONE
					 };

	const std::string S_RECOENU_BINS[ N_RECOENU_BINS ]=
					{ "RecoEnu0p00__0p50",
					  "RecoEnu0p25__1p00",
					  "RecoEnu0p50__1p50",
					  "RecoEnu1p50__2p50",
					  "RecoEnuGE__2p50"
					};

	const double BinEdges[N_RECOENU_BINS+1]=
					{ 0.0,
					  0.5,
					  1.0,
					  1.5,
					  2.5,
					  5.0
					};
	
	enum E_RECOENU_BINS int2enum(const int);
};
