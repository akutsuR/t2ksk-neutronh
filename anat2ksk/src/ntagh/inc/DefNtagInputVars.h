#pragma once

#include <iostream>
#include <string>
#include <cstdlib>

using namespace std;

namespace NtagInputVars
{
	enum E_INPUT_VARS{ eN10n=0,
					   eNcS,
					   eN300S,
					   enDwall,
					   enTwall,
					   elnAccep,
					   ellrCAng,
					   eBeta1,
					   eBeta2,
					   eBeta3,
					   eBeta4,
					   eBeta5,
					   etSD,
					   etSDMin6
					 };

	enum E_INPUT_VARS int2enum(int);

	const int N_INPUT_VARS=14;
	const string S_INPUT_VARS[ N_INPUT_VARS ]=
			{ "N10n",
			  "NcS",
			  "N300S",
			  "nDwall",
			  "nTwall",
			  "lnAccep",
			  "llrCAng",
			  "Beta1",
			  "Beta2",
			  "Beta3",
			  "Beta4",
			  "Beta5",
			  "tSD",
			  "tSDMin6",
			};

	const int NBINS[ N_INPUT_VARS ]=
			{ 30,
			  25,
			  75,
			  40,
			  40,
			  40,
			  70,
			  40,
			  40,
			  40,
			  40,
			  40,
			  40,
			  40
			};

	// For data - MC comparision
	const int NBINSCoarse[ N_INPUT_VARS ]=
			{ 30,
			  25,
			  75,
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
			  20
			};

	const float XMIN[ N_INPUT_VARS ]=
			{ 4.0,
			  0.0, 
			  0.0,
			  0.0, 
			  0.0,
			  1.0,
			  -150.0,
			  -0.1,
			  -0.1,
			  -0.1,
			  -0.1,
			  -0.1,
			  0.0,
			  0.0
			};

	const float XMAX[ N_INPUT_VARS ]=
			{ 34.0,
			  25.0,
			  75.0,
			  1740.0,
			  5000.0,
			  7.5,
			  400.0,
			  1.0,
			  1.0,
			  1.0,
			  1.0,
			  1.0,
			  4.5,
			  4.5
		    };

	const string TYPEDEF[ N_INPUT_VARS ]=
			{ "i",
			  "i",
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
			  "f"
			};
}
