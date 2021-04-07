#pragma once

#include <string>
#include <iostream>
#include <cstdlib>

namespace OscChan{

	enum E_OSC_CHAN{ eNUMU=0,
					 eNUESIG,
					 eNUE,
					 eNUMUBAR,
					 eNUEBARSIG,
					 eNUEBAR,
					 eDATA,
					 eNONE
				   };	

	const int N_OSC_CHAN=6;

//	const std::string S_OSC_CHAN[ N_OSC_CHAN+1 ]=
//				   { "numu",
//					 "nuesig",
//					 "numubar",
//					 "nuebarsig",
//					 "nue",
//					 "nuebar",
//					 "data"
//				   };

	const std::string S_OSC_CHAN[ N_OSC_CHAN+1 ]=
				   { "numu",
					 "nuesig",
					 "nue",
					 "numubar",
					 "nuebarsig",
					 "nuebar",
					 "data"
				   };


	const std::string S_OSC_CHAN_FULL[ N_OSC_CHAN+1 ]=
				  { "numu_x_numu",
					"numu_x_nue",
					"nue_x_nue",
					"numubar_x_numubar",
					"numubar_x_nuebar",
					"nuebar_x_nuebar",
					"data",
				  };


	enum E_OSC_CHAN getOscChan(std::string);
	enum E_OSC_CHAN chr2enum(char*);
	enum E_OSC_CHAN int2enum(int);
};
