#pragma once

#include <cstdlib>
#include <iostream>
#include <string>
#include "const.h"

namespace ExtraHists
{
	const int N_EXTRA_HIST=47;

	enum E_EXTRA_HIST
		{ eTrueEnuNuEvts=0,
		  // Muon momentum
		  eLepMomNuEvts,
		  eLepMomNmcnTot,
		  eLepMomNmcnTag,
		  eLepMomNbkgTag,
		  eLepMomNtotTag,
		  // Transverse muon momentum
		  eTrMomNuEvts,
		  eTrMomNmcnTot,
		  eTrMomNmcnTag,
		  eTrMomNbkgTag,
		  eTrMomNtotTag,
		  // Reco. Enu assuming CCQE
		  eRecoEnuNuEvts,
		  eRecoEnuNmcnTot,
		  eRecoEnuNmcnTag,
		  eRecoEnuNbkgTag,
		  eRecoEnuNtotTag,
		  // Reco. Q2 assuming CCQE
		  eRecoQ2NuEvts,
		  eRecoQ2NmcnTot,
		  eRecoQ2NmcnTag,
		  eRecoQ2NbkgTag,
		  eRecoQ2NtotTag,
		  // Angle btw beam and muon directions
		  eCosBmNuEvts,
		  eCosBmNmcnTot,
		  eCosBmNmcnTag,
		  eCosBmNbkgTag,
		  eCosBmNtotTag,
		  // Dwall calculated by fiTQun 1R mu hypo.
		  efQDWallNuEvts,
		  efQDWallNmcnTot,
		  efQDWallNmcnTag,
		  efQDWallNbkgTag,
		  efQDWallNtotTag,
		  // R2 calculated by fiTQun 1R mu hypo.
		  efQVtxR2NuEvts,
		  efQVtxR2NmcnTot,
		  efQVtxR2NmcnTag,
		  efQVtxR2NbkgTag,
		  efQVtxR2NtotTag,
		  // Z calculated by fiTQun 1R mu hypo.
		  efQVtxZNuEvts,
		  efQVtxZNmcnTot,
		  efQVtxZNmcnTag,
		  efQVtxZNbkgTag,
		  efQVtxZNtotTag,
		  // Tagged neutron multiplicities
		  eNuEvtsNumTagAllVis,
		  eNuEvtsNumTagAllFull,
		  eNuEvtsNumTagAllTrMom0p00__0p25,
		  eNuEvtsNumTagAllTrMom0p25__0p50,
		  eNuEvtsNumTagAllTrMom0p50__0p75,
		  eNuEvtsNumTagAllTrMomGE__0p75,
		  eNONE
		};

	
	enum E_EXTRA_HIST int2enum(int);

	const std::string S_EXTRA_HIST[ N_EXTRA_HIST ]=
		{ "hTrueEnuNuEvts",
		  // Muon momentum
		  "hLepMomNuEvts",
		  "hLepMomNmcnTot",
		  "hLepMomNmcnTag",
		  "hLepMomNbkgTag",
		  "hLepMomNtotTag",
		  // Transverse muon momentum
		  "hTrMomNuEvts",
		  "hTrMomNmcnTot",
		  "hTrMomNmcnTag",
		  "hTrMomNbkgTag",
		  "hTrMomNtotTag",
		  // Reco. Enu assuming CCQE
		  "hRecoEnuNuEvts",
		  "hRecoEnuNmcnTot",
		  "hRecoEnuNmcnTag",
		  "hRecoEnuNbkgTag",
		  "hRecoEnuNtotTag",
		  // Reco. Q2 assuming CCQE
		  "hRecoQ2NuEvts",
		  "hRecoQ2NmcnTot",
		  "hRecoQ2NmcnTag",
		  "hRecoQ2NbkgTag",
		  "hRecoQ2NtotTag",
		  // Angle btw beam and muon directions
		  "hCosBmNuEvts",
		  "hCosBmNmcnTot",
		  "hCosBmNmcnTag",
		  "hCosBmNbkgTag",
		  "hCosBmNtotTag",
		  // Dwall calculated by fiTQun 1R mu hypo.
		  "hfQDWallNuEvts",
		  "hfQDWallNmcnTot",
		  "hfQDWallNmcnTag",
		  "hfQDWallNbkgTag",
		  "hfQDWallNtotTag",
		  // R2 calculated by fiTQun 1R mu hypo.
		  "hfQVtxR2NuEvts",
		  "hfQVtxR2NmcnTot",
		  "hfQVtxR2NmcnTag",
		  "hfQVtxR2NbkgTag",
		  "hfQVtxR2NtotTag",
		  // Z calculated by fiTQun 1R mu hypo.
		  "hfQVtxZNuEvts",
		  "hfQVtxZNmcnTot",
		  "hfQVtxZNmcnTag",
		  "hfQVtxZNbkgTag",
		  "hfQVtxZNtotTag",
		  // Tagged neutron multiplicities
		  "hNuEvtsNumTagAllVis",
		  "hNuEvtsNumTagAllFull",
		  "hNuEvtsNumTagAllTrMom0p00__0p25",
		  "hNuEvtsNumTagAllTrMom0p25__0p50",
		  "hNuEvtsNumTagAllTrMom0p50__0p75",
		  "hNuEvtsNumTagAllTrMomGE__0p75",
		};

	const int NBINS[ N_EXTRA_HIST ]=
		{ 80,
		  // Muon momentum
		  4,
		  4,
		  4,
		  4,
		  4,
		  // Transverse muon momentum
		  4,
		  4,
		  4,
		  4,
		  4,
		  // Reco. Enu assuming CCQE
		  4,
		  4,
		  4,
		  4,
		  4,
		  // Reco. Q2 assuming CCQE
		  4,	 
		  4,
		  4,
		  4,
		  4,
		  // Angle btw beam and muon directions
		  4,
		  4,
		  4,
		  4,
		  4,
		  // Dwall calculated by fiTQun 1R mu hypo.
		  5,
		  5,
		  5,
		  5,
		  5,
		  // R2 calculated by fiTQun 1R mu hypo.
		  5,
		  5,
		  5,
		  5,
		  5,
		  // Z calculated by fiTQun 1R mu hypo.
		  5,
		  5,
		  5,
		  5,
		  5,
		  // Tagged neutron multiplicities
		  3,
		  10,
		  10,
		  10,
		  10,
		  10
		};

	const double XMIN[ N_EXTRA_HIST ]=
		{ 0.0,
		  // Muon momentum
		  0.0,
		  0.0,
		  0.0,
		  0.0,
		  0.0,
		  // Transverse muon momentum
		  0.0,
		  0.0,
		  0.0,
		  0.0,
		  0.0,
		  // Reco. Enu assuming CCQE
		  0.0,
		  0.0,
		  0.0,
		  0.0,
		  0.0,
		  // Reco. Q2 assuming CCQE
		  0.0,
		  0.0,
		  0.0,
		  0.0,
		  0.0,
		  // Angle btw beam and muon directions
		  -1.0,
		  -1.0,
		  -1.0,
		  -1.0,
		  -1.0,
		  // Dwall calculated by fiTQun 1R mu hypo.
		  0.0,
		  0.0,
		  0.0,
		  0.0,
		  0.0,
		  // R2 calculated by fiTQun 1R mu hypo.
		  0.0,
		  0.0,
		  0.0,
		  0.0,
		  0.0,
		  // Z calculated by fiTQun 1R mu hypo.
		  -1.0*(Const::tankZ - 200.0),
		  -1.0*(Const::tankZ - 200.0),
		  -1.0*(Const::tankZ - 200.0),
		  -1.0*(Const::tankZ - 200.0),
		  -1.0*(Const::tankZ - 200.0),
		  // Tagged neutron multiplicities
		  0.0,
		  0.0,
		  0.0,
		  0.0,
		  0.0,
		  0.0
		};

	const double XMAX[ N_EXTRA_HIST ]=
		{ 5.0,
		  // Muon momentum
		  1.0,
		  1.0,
		  1.0,
		  1.0,
		  1.0,
		  // Transverse muon momentum
		  1.0,
		  1.0,
		  1.0,
		  1.0,
		  1.0,
		  // Reco. Enu assuming CCQE
		  1.0,
		  1.0,
		  1.0,
		  1.0,
		  1.0,
		  // Reco. Q2 assuming CCQE
		  1.0,
		  1.0,
		  1.0,
		  1.0,
		  1.0,
		  // Angle btw beam and muon directions
		  1.0,
		  1.0,
		  1.0,
		  1.0,
		  1.0,
		  // Dwall calculated by fiTQun 1R mu hypo.
		  1.0,
		  1.0,
		  1.0,
		  1.0,
		  1.0,
		  // R2 calculated by fiTQun 1R mu hypo.
		  Const::tankR*Const::tankR,
		  Const::tankR*Const::tankR,
		  Const::tankR*Const::tankR,
		  Const::tankR*Const::tankR,
		  Const::tankR*Const::tankR,
		  // Z calculated by fiTQun 1R mu hypo.
		  Const::tankZ - 200.0,
		  Const::tankZ - 200.0,
		  Const::tankZ - 200.0,
		  Const::tankZ - 200.0,
		  Const::tankZ - 200.0,
		  // Tagged neutron multiplicities
		  3.0,
		  10.0,
		  10.0,
		  10.0,
		  10.0,
		  10.0
		};


	const std::string TYPEDEF[ N_EXTRA_HIST ]=
		{ "f",
		  // Muon momentum
		  "f",
		  "f",
		  "f",
		  "f",
		  "f",
		  // Transverse muon momentum
		  "f",
		  "f",
		  "f",
		  "f",
		  "f",
		  // Reco. Enu assuming CCQE
		  "f",
		  "f",
		  "f",
		  "f",
		  "f",
		  // Reco. Q2 assuming CCQE
		  "f",
		  "f",
		  "f",
		  "f",
		  "f",
		  // Angle btw beam and muon directions
		  "f",
		  "f",
		  "f",
		  "f",
		  "f",
		  // Dwall calculated by fiTQun 1R mu hypo.
		  "f",
		  "f",
		  "f",
		  "f",
		  "f",
		  // R2 calculated by fiTQun 1R mu hypo.
		  "f",
		  "f",
		  "f",
		  "f",
		  "f",
		  // Z calculated by fiTQun 1R mu hypo.
		  "f",
		  "f",
		  "f",
		  "f",
		  "f",
		  // Tagged neutron multiplicities
		  "i",
		  "i",
		  "i",
		  "i",
		  "i",
		  "i"
		};
}
