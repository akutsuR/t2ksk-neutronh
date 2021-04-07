#pragma once

#include <iostream>
#include <string>
#include <cstdlib>

namespace BeamMode{

	enum E_BEAM_MODE{ eFHC=0,
					  eRHC,
					  eNONE
				    };	

	const int N_BEAM_MODE=2;

	const std::string S_BEAM_MODE[ N_BEAM_MODE ]=
				   { "fhc",
					 "rhc"
				   };

	enum E_BEAM_MODE chr2enum(char*);
};
