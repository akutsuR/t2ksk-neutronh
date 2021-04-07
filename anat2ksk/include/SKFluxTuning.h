#pragma once

#include <iostream>
#include <string>
#include <cstdlib>

#include "TFile.h"
#include "TH1D.h"

#include "DefOscChannels.h"
#include "DefBeamMode.h"

using std::cout;
using std::endl;
using std::string;
using namespace BeamMode;
using namespace OscChan;

class SKFluxTuning
{
	public :
		SKFluxTuning();
		virtual ~SKFluxTuning();
		void	loadFluxTunings();
		void	setBeamMode(enum E_BEAM_MODE);
		void	setOscChannel(enum E_OSC_CHAN);
		float	getFluxTuning(enum E_BEAM_MODE, enum E_OSC_CHAN, float);
		float	getFluxTuning(float);

	private :
		void 	clearFluxTuningHists();
		void	setDefaultTuningFileNames();
		void	setDefaultTuningHistNames();

		TH1D 	*fhFluxTuning[N_BEAM_MODE][N_OSC_CHAN];
		string 	fFileName[N_BEAM_MODE];
		string	fHistName[N_OSC_CHAN];

		enum E_BEAM_MODE fBeamMode;
		enum E_OSC_CHAN fOscChan;
};			
