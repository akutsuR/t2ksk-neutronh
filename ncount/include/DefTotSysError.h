#pragma once

#include <string>

namespace TotSysErr
{
	const int N_AVE_ERR=2;

	enum E_AVE_ERR{ eAvePlusOneSigma=0,
			        eAveMinusOneSigma
				  };

	const std::string S_AVE_ERR[ N_AVE_ERR ]=
			 { "ave_plus_1sigma",
			   "ave_minus_1sigma"
			 };

	const int N_TRMOM_ERR=4;

	enum E_TRMOM_ERR{ eTrMom0p00__0p25=0,	
					  eTrMom0p25__0p50,
					  eTrMom0p50__0p75,
					  eTrMomGE0p75,
					};

	const std::string S_TRMOM_ERR[ N_TRMOM_ERR ]=
				{ "trmom0p00__0p25",	
                  "trmom0p25__0p50",
                  "trmom0p50__0p75",
                  "trmomge0p75"
				};

	const int N_SIGMA_VAR=2;
	enum E_SIGMA_VAR{ ePlusOneSigma=0,
					  eMinusOneSigma
					};
	const std::string S_SIGMA_VAR[ N_SIGMA_VAR ]=
				{ "plus_1sigma",
				  "minus_1sigma"
				};
};
