#pragma once

#include <string>
#include "DefRecMuonTrMom.h"

namespace MCTruth
{
	const int N_MCT_DST=14+TrMomBin::N_TRMOM_BINS;

	enum E_MCT_DST{ ePostFSINeuMulti=0,
					 ePostFSIProMulti,
					 ePostFSIPiPMulti,
					 ePostFSIPiMMulti,
					 ePostFSINeuEkin,
					 ePostFSIProEkin,
					 ePostFSIPiPEkin,
					 ePostFSIPiMEkin,
					 eFSISINeuMulti,
					 eFSISINPDist,
					 eETrueRecTrMom0p00__0p25,
					 eETrueRecTrMom0p25__0p50,
					 eETrueRecTrMom0p50__0p75,
					 eETrueRecTrMomGE0p75,
					 eQ2TrueNuEvts,
					 eQ2TrueTotNeu,
					 eQ2TrueAveTotNeu,
					 eRecoTrMomTrueQ2
				   };

	const std::string S_MCT_DST[ N_MCT_DST ]=
				   { "PostFSINeuMulti",
					 "PostFSIProMulti",
					 "PostFSIPiPMulti",
					 "PostFSIPiMMulti",
					 "PostFSINeuEkin",
					 "PostFSIProEkin",
					 "PostFSIPiPEkin",
					 "PostFSIPiMEkin",
					 "FSISINeuMulti",
					 "FSISINPDist",
					 "EtrueRecTrMom0p00_0p25",
					 "EtrueRecTrMom0p25_0p50",
					 "EtrueRecTrMom0p50_0p75",
					 "EtrueRecTrMomGE0p75",
					 "Q2TrueNuEvts",
					 "Q2TrueTotNeu",
					 "Q2TrueAveTotNeu",
					 "RecoTrMomQ2True",
				   };

	const double xmin[ N_MCT_DST ]=
				   { 0.0, // ePostFSINeuMulti
					 0.0,
					 0.0,
					 0.0,

					 0.0, // ePostFSINeuEkin
					 0.0,
					 0.0,
					 0.0,

					 0.0,
					 0.0,
	
					 0.0, // eETrueRecTrMom0p00__0p25,
					 0.0,
					 0.0,
					 0.0,

					 0.0,  // eQ2True
					 0.0,
					 0.0,	

					 0.0  // eRecoTrMomTrueQ2 (dummy)
					};

	const double xmax[ N_MCT_DST ]=
				   { 10.0, // ePostFSINeuMulti
					 10.0,
					 10.0,
					 10.0,

					 4000.0, // ePostFSINeuEkin
					 4000.0,
					 4000.0,
					 4000.0,

					 50.0,
					 1000.0,

					 30.0, // eETrueRecTrMom0p00__0p25
					 30.0,
					 30.0,
					 30.0,

					 20.0, // eQ2True
					 20.0,
					 20.0,

					 20.0  // eRecoTrMomTrueQ2 (dummy)
					};

	const int nbins[ N_MCT_DST ]=
				   { 10, // ePostFSINeuMulti
					 10,
					 10,
					 10,

					 200, // ePostFSINeuEkin
					 200,
					 200,
					 200,

					 50,
					 50,

					 300, // eETrueRecTrMom0p00__0p25
					 300,
					 300,
					 300,

					 200, // eQ2True
					 200,
					 200,

					 200  // eRecoTrMomTrueQ2 (dummy)
					};

	const std::string TYPEDEF[ N_MCT_DST ]=
				  { "i", // ePostFSINeuMulti
					"i",
					"i",
					"i",

					"f",  // ePostFSINeuEkin
					"f",
					"f",
					"f",

					"i",
					"f",

					"f", // eETrueRecTrMom0p00__0p25
					"f",
					"f",
					"f",

					"f", // eQ2True
					"f",
					"f",

					"f"
				   };

	const int nbinsTrMom=400;
	const int nbinsQ2=400;
	const double xminTrMom=0.0;
	const double xminQ2=0.0;
	const double xmaxTrMom=20.0;
	const double xmaxQ2=20.0;
};
