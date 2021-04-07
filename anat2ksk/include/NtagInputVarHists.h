#pragma once

#include <string>
#include <iostream>
#include <typeinfo>

#include "TH1D.h"
#include "TDirectory.h"
#include "TKey.h"

#include "DefNtagInputVars.h"
#include "DefNtagCategory.h"

using namespace std;

class NtagInputVarHists
{
	public :
		NtagInputVarHists();
		virtual ~NtagInputVarHists();
		void 	initializeHists();
		void 	setHistNamePostFix(string);
		void 	fillHists(float*, enum NtagCat::E_NTAG_CAT, float wnu=1.0);
		void 	normalizeHistsByArea();
		void 	normalizeHists(double);
		TH1D*	getHist(enum NtagCat::E_NTAG_CAT, enum NtagInputVars::E_INPUT_VARS);
		TH1D*	getHist(int, int);
		bool	operator+=(const NtagInputVarHists&) const;
		void	loadHists(TDirectory*);

		void 	setCoarserBinning(const bool);

	private :
		void 	setConstants();
		void	clearHists();
		void	setDefaultNames();
		
		TH1D 	*fhInVars[ NtagCat::N_NTAG_CAT ][ NtagInputVars::N_INPUT_VARS ];
		int		fNbins[ NtagInputVars::N_INPUT_VARS ];
		double	fXMax[ NtagInputVars::N_INPUT_VARS ];
		double	fXMin[ NtagInputVars::N_INPUT_VARS ];
		string  fPostFix;
		string  fDefName[ NtagCat::N_NTAG_CAT ][ NtagInputVars::N_INPUT_VARS ];
		bool	fIsCoarser;
};
