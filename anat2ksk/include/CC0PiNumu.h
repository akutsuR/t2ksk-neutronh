#pragma once

#include <string>

#include "TTree.h"
#include "TChain.h"
#include "TMath.h"
#include "TArrayF.h"

#include "DefBeamMode.h"
#include "DefOscChannels.h" 
#include "DefGenType.h"
#include "DefCC0PiNumuCut.h"
#include "SKh1Variables.h"
#include "CC0PiNumuVariables.h"
#include "SKFluxTuning.h"
#include "SK10E21POTNorm.h"
#include "T2KSKOscProb.h"
#include "EvSelVar_t.h"
#include "listWgtXSecFromSK_NIWG2015.h"
#include "DefIntCat.h"

using std::string;
using namespace BeamMode;
using namespace OscChan;
using namespace CC0PiNumuCut;

class CC0PiNumu : public T2KSKOscProb
{
	public :
		CC0PiNumu(BeamMode::E_BEAM_MODE, 
				  OscChan::E_OSC_CHAN, 
				  GenType::E_GEN_TYP egt=GenType::eNEUT);
		virtual ~CC0PiNumu();
		
		void		computeCC0PiVariables();
		bool		applyfQ1RCC0PiNumuCut();
		bool		applyfQ1RCC0PiNumuCutExceptForFV();
		EvSelVar_t	getEvSelVar();
		bool		isWrongSignSpill();

		// Address h1 and CC0pi 1R numu selection related variables
		template <typename T> T var(string) const;
		template <typename T> T var(string, int) const;
		template <typename T> T var(string, int, int) const;
		template <typename T> T var(string, int, int, int) const;

		void	resisterVariable(string str){ fh1v->resisterVariable(str); };
		void	resisterDefault(string); 
		void	resisterDefaultAllStacks();
		void	seth1Tree(TTree* tree)		{ fh1v->setBranches(tree); };

		// Osc. probability
		float	getOscWgt();

		// Flux tuning 
		float   getFluxWgt(enum E_BEAM_MODE, enum E_OSC_CHAN, float);
		float   getFluxWgt();

		// POT normalization
		void 	setTrueWallEventsAllMC(enum GenType::E_GEN_TYP);
		void	setTrueWallEventsLastHalfMC();
		float	get10E21POTNorm(enum E_BEAM_MODE, enum E_OSC_CHAN);
		float	get10E21POTNorm();

		// Weight for CC Coh. (for 14a MC)
		float	getCCCohWgt();

		// Weights for XSec
		void	setXSecWgtTree(TTree*);
		float	getXSecWgt(enum WgtXSec::E_XSEC_WGT);

		// Convert NEUT int. cat. to a simplified int. cat.
		enum IntCat::E_INT_CAT getIntCat();

		void	printError(string) const;

	private :
		BeamMode::E_BEAM_MODE feBM;
		OscChan::E_OSC_CHAN   feOC;
		GenType::E_GEN_TYP    feGT;
		SKh1Variables		 *fh1v;
		CC0PiNumuVariables	 *fmuv;
		SK10E21POTNorm		 *fpnorm;
		SKFluxTuning		 *fflx;
		bool				  fSelec[N_EVE_SLC];
		TArrayF				 *fXSecWgt;
		Int_t				  fNWeights;
};
