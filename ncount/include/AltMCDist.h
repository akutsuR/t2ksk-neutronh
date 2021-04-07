#include <iostream>
#include <string>
#include <cstdlib>

#include "TFile.h"
#include "TDirectoryFile.h"
#include "TChain.h"

#include "DefOscChannels.h"
#include "DefBeamMode.h"
#include "DefIntCat.h"
#include "DefEvSelHists.h"
#include "CC0PiNumu.h"
#include "CC0PiNumuEvSelHists.h"
#include "CC0PiNumuExtraHists.h"
#include "NtagHistManager.h"
#include "listWgtXSecFromSK_NIWG2015.h"
#include "NtagRes.h"
#include "EvSelVar_t.h"
#include "ExtraVar_t.h"
#include "VertexDistributions.h"
#include "VertexVar_t.h"
#include "MCTruthDistributions.h"
#include "MCTruthVar_t.h"

#include "CmdLineArgParser.h"
#include "TvarCorSum.h"
#include "AltMCReducTree.h"

using std::cout;
using std::endl;
using std::string;


class AltMCDist
{
	public :
		AltMCDist(CmdLineArgParser);
		virtual ~AltMCDist();

		void initialize();
		void loopEvents();	
		void normalize();
		void writeOutputs();

	private :
		void loadInputs();
		void configure();
		void initiOutputs();
		void initiToyTagging();
		VertexVar_t getVertexVar();
		MCTruthVar_t getMCTruthVar();

		CmdLineArgParser	 fCmdArg;
		TChain				*fTchfQMR;
		TChain				*fTchExtr;
		TChain				*fTchNtag;

		CC0PiNumu			*fNumu;
		NtagRes				*fNtag;
		AltMCReducTree		*fAltMC;

		CC0PiNumuEvSelHists		*fhEvselNuev[IntCat::N_INT_CAT+1];
		CC0PiNumuEvSelHists		*fhEvselNtag[IntCat::N_ICAT_NTAG+1];
		CC0PiNumuExtraHists		*fhExtra[IntCat::N_INT_CAT+1];
		NtagHistManager 		*fhNtag[IntCat::N_INT_CAT+1];
		VertexDistributions 	*fhVtxDist[IntCat::N_INT_CAT+1];	// for KS-test
		MCTruthDistributions 	*fhMCTDist[IntCat::N_INT_CAT+1];

		float 				fWTvarSig;
		float 				fWTvarBkg;
};
