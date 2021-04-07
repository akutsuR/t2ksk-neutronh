#pragma once

#include <string>
#include <iostream>
#include <typeinfo>

#include "TH1D.h"
#include "TDirectory.h"
#include "TKey.h"

#include "DefNtagOtherVars.h"
#include "DefNtagCategory.h"

using namespace std;

class NtagOtherVarHists
{
	public :
		NtagOtherVarHists(bool binning=false, bool ambe=false);

		virtual ~NtagOtherVarHists(){};
		void	setBinning(enum NtagOtherVars::E_OTHER_VARS, const int, const double, const double);
		void 	initializeHists();
		void 	setHistNamePostFix(string);
		void 	setBinningFlag(bool);
		void 	setAmBeFlag(bool);
		void 	fillHists(float, enum NtagCat::E_NTAG_CAT, int, float wnu=1.0);
		void 	normalizeHistsByArea();
		void 	normalizeHists(double);
		TH1D*	getHist(enum NtagCat::E_NTAG_CAT, enum NtagOtherVars::E_OTHER_VARS);
		TH1D* 	getHist(int, int);
		bool	operator+=(const NtagOtherVarHists&) const;
		void	loadHists(TDirectory*);

		void 	setCoarserBinning(const bool);

	private :
		void 	setConstants();
		void	clearHists();
		void	setDefaultNames();
	
		TH1D	*fhOthVars[ NtagCat::N_NTAG_CAT ][ NtagOtherVars::N_OTHER_VARS ];
		string  fDefName[ NtagCat::N_NTAG_CAT ][ NtagOtherVars::N_OTHER_VARS ];
		int		fNbins[ NtagOtherVars::N_OTHER_VARS ];
		double	fXMax[ NtagOtherVars::N_OTHER_VARS ];
		double	fXMin[ NtagOtherVars::N_OTHER_VARS ];
		string  fPostFix;
		bool	fBinningFlag;
		bool	fAmBeFlag;
		bool	fIsCoarser;
};
