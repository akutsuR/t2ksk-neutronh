#pragma once

#include <iostream>
#include <string>

#include "TH1D.h"
#include "TH2D.h"
#include "TAxis.h"
#include "TDirectory.h"
#include "TKey.h"

#include "DefMCTruthDist.h"
#include "MCTruthVar_t.h"

using std::cout;
using std::endl;
using std::string;

class MCTruthDistributions
{
	public :
		MCTruthDistributions(string spf="");
		virtual ~MCTruthDistributions();

		template <typename T> void fillHist(int, T, float);
		void fillDST(const MCTruthVar_t, float w=1.0);
		void normalizeDST(double);

		TH1D *getDst(int);
		TH2D *getDst2D();

		void addDST(MCTruthDistributions*);
		void loadDST(TDirectory *td);

	private :
		void initialize();

		TAxis *fTrMomAxis;
		string fPostFix;
		TH1D *fhDst[MCTruth::N_MCT_DST];	
		TH2D *fhDst2D;
};
