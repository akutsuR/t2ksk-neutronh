#pragma once

#include <string>
#include <iostream>
#include <typeinfo>

#include "TH1D.h"
#include "TDirectory.h"
#include "TKey.h"

#include "DefEvSelHists.h"
#include "DefCC0PiNumuCut.h"
#include "EvSelVar_t.h"

using std::cout;
using std::endl;
using namespace EvSelHists;
using namespace CC0PiNumuCut;

class CC0PiNumuEvSelHists
{
	public :
		CC0PiNumuEvSelHists();
		CC0PiNumuEvSelHists(string);
		virtual ~CC0PiNumuEvSelHists();

		void 	initializeHists();
		void 	setHistNamePostFix(string);

		template <typename T> void fillHist(enum E_EVSEL_HIST, T, float);
		void 	fillHists(const EvSelVar_t, float);
		void 	normalizeHists(double);

		TH1D*	getHist(int);
		TH1D*	getHist(enum EvSelHists::E_EVSEL_HIST);
		bool	operator+=(const CC0PiNumuEvSelHists&) const;

		void	loadHists(TDirectory*);


	private :
		void 	setConstants();
		void	clearHists();
		void	setDefaultNames();
		
		TH1D 	*fHist[ N_EVSEL_HIST ];
		int		fNbins[ N_EVSEL_HIST ];
		double	fXMax[ N_EVSEL_HIST ];
		double	fXMin[ N_EVSEL_HIST ];
		string  fPostFix;
		string  fDefName[ N_EVSEL_HIST ];
};
