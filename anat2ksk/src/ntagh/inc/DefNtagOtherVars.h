#pragma once

#include <iostream>
#include <string>
#include <cstdlib>

using namespace std;

namespace NtagOtherVars
{
	enum E_OTHER_VARS{ eNP=0,
					   eNN,
					   eN10,
					   eNNout,
					   et0_PS,
					   et0_NN,
					   enpdist_PS,
					   enpdist_NN,
					   emcttotnn,
					   emctnpdist_PS,
					   emctnpdist_NN,
					   envtxdist_PS,
					   envtxdist_NN,
					   emctdt0_PS,
					   emctdt0_NN,
					   et0long_PS,	/* Assumed to be used in AmBe calib. */
					   et0long_NN,	/* Assumed to be used in AmBe calib. */
					   eNPLong_NN,	/* npdist projected onto beam direction */
					   eNPTran_NN,	/* npdist parpendicular to beam direction */
					   enangAct_NN,	/* angle between n dir. and beam dir. */
					   enangInf_NN	/* angle between n dir. and inferred n dir. */
					 };

	enum E_OTHER_VARS int2enum(int);

	const int N_OTHER_VARS=21;
	const string S_OTHER_VARS[ N_OTHER_VARS ]=
			{ "np",
			  "nn",
			  "n10",
			  "nnout",
			  "ctime_ps",
			  "ctime_nn",
			  "npdist_ps",
			  "npdist_nn",
			  "mcttotmcn",
			  "mctnpdist_ps",
			  "mctnpdist_nn",
			  "nvtxdist_ps",
			  "nvtxdist_nn",
			  "mctdt0_ps",
			  "mctdt0_nn",
			  "ctimeL_ps",
			  "ctimeL_nn",
			  "npdistL_nn",
			  "npdistT_nn",
			  "nangAct_nn",
			  "nangInf_nn",
			};

	const int NBINS[ N_OTHER_VARS ]=
			{ 25,
			   5,
			  40,
			  40,
			  27,
			  27,
			  70,
			  70,
			  15,
			  70,
			  70,
			  5000,
			  5000,
			  200,
			  200,
			  42,
			  42,
			  100,
			  100,
			  100,
			  100
			};

	const int NBINSCoarse[ N_OTHER_VARS ]=
			{ 25,
			   5,
			  40,
			  20,
			   8,
			   5,
			  20,
			  20,
			  20,
			  20,
			  20,
			  20,
			  20,
			  20,
			  20,
			  20,
			  20,
			  10,
			  10,
			  5,
			  5
			  //20000
			};

	const float XMIN[ N_OTHER_VARS ]=
			{ 0.0,
			  0.0, 
			  0.0,
			  0.0, 
			  0.0,
			  0.0,
			  0.0,
			  0.0,
			  0.0,
			  0.0,
			  0.0,
			  0.0,
			  0.0,
			  -100.0,
			  -100.0,
			  0.0,
			  0.0,
			  -1000.0,
			  0.0,
			  -1.0,
			  -1.0
			};

	const float XMINCoarse[ N_OTHER_VARS ]=
			{ 0.0,	// np
			  0.0, 	// nn
			  0.0,	// N10
			  0.0, 	// NN out
			  18.0,
			  18.0,
			  0.0,
			  0.0,
			  0.0,
			  0.0,
			  0.0,
			  0.0,
			  0.0,
			  -100.0,
			  -100.0,
			  0.0,
			  0.0,
			  -400.0,
			  0.0,
			  -1.0,
			  -1.0
			};

	const float XMAX[ N_OTHER_VARS ]=
			{ 25.0,
			  5.0,
			  40.0,
			  1.0,
			  513.0,
			  513.0,
			  3500.0,
			  3500.0,
			  15.0,
			  1000.0,
			  1000.0,
			  1000.0,
			  1000.0,
			  100.0,
			  100.0,
			  840.0,
			  840.0,
			  1500.0,
			  1000.0,
			  1.0,
			  1.0
		    };

	const float XMAXCoarse[ N_OTHER_VARS ]=
			{ 25.0,
			  5.0,
			  40.0,
			  1.0,
			  513.0,
			  513.0,
			  3500.0,
			  3500.0,
			  15.0,
			  1000.0,
			  1000.0,
			  1000.0,
			  1000.0,
			  100.0,
			  100.0,
			  840.0,
			  840.0,
			  600.0,
			  1000.0,
			  1.0,
			  1.0
		    };


	const string TYPEDEF[ N_OTHER_VARS ]=
			{ "i",
			  "i",
			  "i",
			  "f",
			  "f",
			  "f",
			  "f",
			  "f",
			  "i",
			  "f",
			  "f",
			  "f",
			  "f",
			  "f",
			  "f",
			  "f",
			  "f",
			  "f",
			  "f",
			  "f",
			  "f"
			};


	const int N_BINS_MCTNPD=11;
	const double B_EDGES_MCTNPD[ N_BINS_MCTNPD+1 ]=
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


	const int N_BINS_RECNPD=8;
	const double B_EDGES_RECNPD[ N_BINS_RECNPD+1 ]=
				 {   0,
				   100.,
				   200.,
				   400.,
				   600.,
				  1000.,
				  1500.,
				  2000.,
				  3500.
				 };
}
