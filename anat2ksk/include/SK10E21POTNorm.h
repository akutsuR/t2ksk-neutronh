// This class is used only for MC events.
// It handles constans that normalize MC events 
// by 10^21 POT
//
// Jan. 2019 - R.Akutsu

#pragma once

#include <iostream>

#include "DefBeamMode.h"
#include "DefOscChannels.h"
#include "DefGenType.h"

using namespace std;
using namespace BeamMode;
using namespace OscChan;

class SK10E21POTNorm
{
	public :
		SK10E21POTNorm();
		virtual ~SK10E21POTNorm(){};

		void setSKRate10E21POT();
		void setSKRate10E21POT(enum GenType::E_GEN_TYP);
		void setTrueWallEventsAllMC();
		void setTrueWallEventsAllMC(enum GenType::E_GEN_TYP);
		void setTrueWallEventsLastHalfMC();
		float get10E21POTNorm(enum E_BEAM_MODE, enum E_OSC_CHAN);

	private :
		void clearNormFactors();

		float fEvtsWallV[ N_BEAM_MODE ][ N_OSC_CHAN ];	
		float fSKRate[ N_BEAM_MODE ][ N_OSC_CHAN ];	
};
