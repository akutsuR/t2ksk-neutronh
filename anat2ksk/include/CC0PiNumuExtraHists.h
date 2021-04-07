#pragma once

#include <string>
#include <iostream>
#include <typeinfo>

#include "TH1D.h"
#include "TDirectory.h"
#include "TKey.h"

#include "DefExtraHists.h"
#include "DefRecMuonMomentum.h"
#include "DefRecMuonTrMom.h"
#include "DefRecEnuCCQE.h"
#include "DefRecQ2CCQE.h"
#include "DeffQDWall.h"
#include "ExtraVar_t.h"


using std::cout;
using std::endl;
using std::string;
using namespace ExtraHists;

class CC0PiNumuExtraHists
{
	public :
		CC0PiNumuExtraHists();
		CC0PiNumuExtraHists(string);
		virtual ~CC0PiNumuExtraHists();

		void	setBinning(enum E_EXTRA_HIST, const int, const double, const double);
		void 	initializeHists();
		void 	setHistNamePostFix(string);

		template <typename T> void fillHist(enum E_EXTRA_HIST, T, float);
		void 	fillHists(const ExtraVar_t, float);
		void 	normalizeHists(double);

		void	setHistsColor(int);
		TH1D*	getHist(int);
		TH1D*	getHist(enum ExtraHists::E_EXTRA_HIST);
		bool	operator+=(const CC0PiNumuExtraHists&) const;

		void	loadHists(TDirectory*);


	private :
		void 	setConstants();
		void	clearHists();
		void	setDefaultNames();
		
		TH1D 	*fHist[ N_EXTRA_HIST ];
		int		fNbins[ N_EXTRA_HIST ];
		double	fXMax[ N_EXTRA_HIST ];
		double	fXMin[ N_EXTRA_HIST ];
		string  fPostFix;
		string  fDefName[ N_EXTRA_HIST ];
};
