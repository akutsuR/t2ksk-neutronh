#pragma once

#include <string>

namespace Global{

	const int N_NUMBERS=13;
	enum E_NUMBERS{ NuEvents=0,
					TotNCaptures,
					TagNCaptures_PS,
					TagNCaptures_NN,
					UnTagNCaptures_PS,
					UnTagNCaptures_NN_FromTot,
					UnTagNCaptures_NN_FromPS,
					TagBkgs,
					TotPiMiCaptures,
					TagEff_PS,
					TagEff_NN,
					TagEff_FromPS,
					BkgRate
				  };
	const std::string S_NUMBERS[ N_NUMBERS ]=
				 { "NuEvents",
				   "TotNCap",
				   "TagNCapPS",
				   "TagNCapNN",
				   "UnTagNCapPS",
				   "UnTagNCapNN_FromTot",
				   "UnTagNCapNN_FromPS",
				   "TagBkgs",
				   "TotPiMiCaptures",
				   "TagEff_PS",
				   "TagEff_NN",
				   "TagEff_FromPS",
				   "BkgRate"
				 };
	

	const int N_NCAPDIST=11;
	const double BINS_NCAPDIST[ N_NCAPDIST+1 ]=
				 {   0,
					50.,
				   100.,
				   150.,
				   200.,
				   250.,
				   300.,
				   400.,
				   500.,
				   600.,
				   800.,
				  1000
				 };

	const int N_REC_NCAPDIST=5;
	const double BINS_REC_NCAPDIST[ N_REC_NCAPDIST+1 ]=
				 {   0,
				   100.,
				   200.,
				   400.,
				   600.,
				  1000.
				 };
}
