#pragma once
#include <string>
using std::string;

namespace VtxDist
{
	const int N_VTX_DST=12;
	
	enum E_VTX_DST{ eNuevDWALL=0,
			 		eNuevR2,
					eNuevZ,
					eNtagNNmcnDWALL,
					eNtagNNmcnR2,
					eNtagNNmcnZ,
					eNtagNNbkgDWALL,
					eNtagNNbkgR2,
					eNtagNNbkgZ,
					eNtagNNDWALL,
					eNtagNNR2,
					eNtagNNZ,	
				 };	 
	
	const string S_VTX_DST[ N_VTX_DST ]=
					{ "NuevDWALL",
					  "NuevR2",
					  "NuevZ",
					  "NtagNNmcnDWALL",
					  "NtagNNmcnR2",
					  "NtagNNmcnZ",
					  "NtagNNbkgDWALL",
					  "NtagNNbkgR2",
					  "NtagNNbkgZ",
					  "NtagNNDWALL",
					  "NtagNNR2",
					  "NtagNNZ"
					};

	const double xmin[ N_VTX_DST ]=
					{ 0.0, 		// eNuevDWALL
					  0.0, 		// eNuevR2
					  -1810, 	// eNuevZ
					  0.0, 		// eNtagNNmcnDWALL
					  0.0, 		// eNtagNNmcnR2
					  -1810.0,  // eNtagNNmcnZ
					  0.0, 		// eNtagNNbkgDWALL
					  0.0, 		// eNtagNNbkgR2
					  -1810.0,  // eNtagNNbkgZ
					  0.0, 		// eNtagNNDWALL
					  0.0, 		// eNtagNNR2
					  -1810.0  	// eNtagNNZ
					};

	const double xmax[ N_VTX_DST ]=
					{ 1690.0,			// eNuevDWALL
					  1690.0*1690.0,	// eNuevR2
					  1810.0, 			// eNuevZ
					  1690.0, 			// eNtagNNmcnDWALL
					  1690.0*1690.0, 	// eNtagNNmcnR2
					  1810.0, 			// eNtagNNmcnZ
					  1690.0, 			// eNtagNNbkgDWALL
					  1690.0*1690.0, 	// eNtagNNbkgR2
					  1810.0, 			// eNtagNNbkgZ
					  1690.0, 			// eNtagNNDWALL
					  1690.0*1690.0, 	// eNtagNNR2
					  1810.0 			// eNtagNNZ
					};

	const int nbinsKS[ N_VTX_DST ]=
					{ 20000,	// eNuevDWALL
					  20000,	// eNuevR2
					  20000,	// eNuevZ
					  20000,	// eNtagNNmcnDWALL
					  20000,	// eNtagNNmcnR2
					  20000,	// eNtagNNmcnZ
					  20000,	// eNtagNNbkgDWALL
					  20000,	// eNtagNNbkgR2
					  20000,	// eNtagNNbkgZ
					  20000,	// eNtagNNDWALL
					  20000,	// eNtagNNR2
					  20000		// eNtagNNZ
					};

	const int nbinsVIS		=10;
	const double xminZ		=-1810.0;
	const double xmaxZ		=1810.0;
	const double xminR2		=0.0;
	const double xmaxR2		=1690.0*1690.0;
	const double edgesDwall[ nbinsVIS+1 ]=
					{0.0, 
					 61.2302629036242934,
					 125.465919157346065,
					 195.301183805144603,
					 272.143086190301744,
					 358.068285311677926,
					 456.356802284996320,
					 572.730792447264662,
					 718.872283034150541,
					 927.090732635987592,
					 1690.0
					};

	const int nbinsVISC		=5;
	const double edgesDwallC[ nbinsVISC+1 ]=
					{0.0, 
					 125.465919157346065,
					 272.143086190301744,
					 456.356802284996320,
					 718.872283034150541,
					 1690.0
					};
};
