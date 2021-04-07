#pragma once

#include <iostream>
#include <string>

#include "TDirectory.h"
#include "TFile.h"
#include "TH1D.h"
#include "TDirectoryFile.h"

#include "DefNtagCategory.h"
#include "DefNtagInputVars.h"
#include "DefNtagOtherVars.h"
#include "NtagInputVarHists.h"
#include "NtagOtherVarHists.h"
#include "NtagRes.h"

namespace NtagHist
{
	enum E_HIST_CAT{ eInVarsPS=0,
					 eInVarsNN,
					 eOthVars
				   };
};


using namespace std;
using namespace NtagCat;
using namespace NtagHist;
using namespace NtagInputVars;
using namespace NtagOtherVars;


class NtagHistManager 
{
	public :
		NtagHistManager();
		virtual ~NtagHistManager(){};

		void setOtherVarsBinning(enum NtagOtherVars::E_OTHER_VARS, const int, const double, const double);
		void setInputVarHistsPostFixPS(string);
		void setInputVarHistsPostFixNN(string);
		void setOtherVarHistsPostFix(string);
		void initialize();
		void fillHists(NtagRes, float wnu=1.0);
		void normalizeHists(float);

		void writeHists(TDirectoryFile*, enum NtagHist::E_HIST_CAT, enum NtagCat::E_NTAG_CAT);
		void writeHists(TFile*, enum NtagHist::E_HIST_CAT, enum NtagCat::E_NTAG_CAT);
		void writeHists(enum NtagHist::E_HIST_CAT, enum NtagCat::E_NTAG_CAT);

		bool operator+=(const NtagHistManager&) const;	
		void loadHists(enum NtagHist::E_HIST_CAT, TDirectory*);
		TH1D *getHist(enum NtagHist::E_HIST_CAT, int, int);

		void setCoarserBinningInVars(bool);
		void setCoarserBinningOthVars(bool);

	private :
		NtagInputVarHists *fnhPS;		/* Input vars for PS */
		NtagInputVarHists *fnhNN;		/* Input vars for NN */
		NtagOtherVarHists *fnhOTH;		/* Other vars (e.g. cap. time) */

		string fPostFixPS;
		string fPostFixNN;
		string fPostFixOTH;
};
