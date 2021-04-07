#pragma once

#include <string>

namespace SumW{

	const int N_SUMW_TYP=5;
	enum E_SUMW_TYP{
		eSUM_WGTSQ_T=0,
		eSUM_WGTSQ_P,
		eSUM_WGTSQ_F,
		eSUM_WGT_P,
		eSUM_WGT_F
		};
	const std::string S_SUMW_TYP[ N_SUMW_TYP ]=
		{ "wgtsq_tot",
		  "wgtsq_pass",
		  "wgtsq_fail",
		  "wgt_pass",
		  "wgt_fail"
		};
}
