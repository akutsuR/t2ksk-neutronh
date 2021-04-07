#pragma once

#include <iostream>
#include <cstdlib>
#include <string>

namespace GenType
{
	const int N_GEN_TYP=3;
	enum E_GEN_TYP
		{ eNEUT=0,
		  eNuWro,
		  eGENIE,
		  eNONE
		};
	const std::string S_GEN_TYP[N_GEN_TYP]
		{ "neut",
		  "nuwro",
		  "genie"
		};

	enum E_GEN_TYP chr2enum(char*);
};
