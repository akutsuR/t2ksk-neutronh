#pragma once

#include <iostream>
#include <cstdlib>
#include <string>

#include "TTree.h"

#include "const.h"
#include "DefIntCat.h"
#include "DefPostFSIPart.h"

using std::cout;
using std::endl;

const int IHADMAX=50;
const int FHADMAX=100;
const int NFSIMAX=50;

class AltMCReducTree
{
	public :
		AltMCReducTree(){ this->setHadronMass(); };
		virtual ~AltMCReducTree(){};

		// Set TTree (or TChain) 
		void setTree(TTree*);
		void computeFSIPart();

		int getFSIMulti(enum PostFSI::E_PFSI_PRT) const;
		float getFSIEkin(enum PostFSI::E_PFSI_PRT, const int) const;
	
		enum IntCat::E_INT_CAT getIntCat();

		// Truncated interaction mode	
		// Ex. iscc() && isqel() means the interaction of the event is CCQE
		bool 	iscc() const;											// Charged Current if it's true
		bool 	isnc() const;											// Neutral Current if it's true
		bool	isqel() const;											// Quasi Elastic if it's true
		bool	ismec() const;											// Meason Exchange Current if it's true
		bool	isres() const;											// Resonat if it's true
		bool	isdis() const;											// Deap Inelastic if it's true
		bool	iscoh() const;											// Coherent if it's true
		bool	isve() const;											// Neutrino-electron elastic scat. (** ONLY for GENIE **)

		// Incoming neutrino, nucleon, and outgoing lepton
		int		inNeuPDG() const;										// PDG code of incoming neutrino
		int		inNucPDG() const;										// PDG code of initial state nucleon       
		int		outLepPDG() const;										// PDG code of outgoing lepton

		double	inNeuAMom() const;										// Absolute momentum of incoming neutrino (GeV)
		double	inNucAMom() const;										// Absolute momentum of initial state nucleon (GeV)
		double	outLepAMom() const;										// Absolute momentum of outgoing lepton (GeV)

		double	inNeuDir(int /* x, y, z */) const;						// Momentum direction of incoming neutrino
		double	inNucDir(int /* x, y, z */) const;						// Momentum direction of initial state nucleon
		double	outLepDir(int /* x, y, z */) const;						// Momentum direction of outgoing lepton

		
		// Particles in hadron system before FSI
		int		iNumPar() const;										// Number of particles in hadron system before FSI
		int		iParPDG(int /* i-th par */) const;						// PDG code of i-th particle
		double	iParAMom(int /* i-th par */) const;						// Absolute momentum of i-th particle (GeV)
		double	iParDir(int /* i-th par */, int /* x, y, z */) const;	// Momentum direction of i-th particle


		// Particles in hadron system after FSI
		int		fNumPar() const;										// Number of particles in hadron system after FSI
		int		fParPDG(int /* i-th par */) const;						// PDG code of i-th particle
		double	fParAMom(int /* i-th par */) const;						// Absolute momentum of i-th particle (GeV)
		double	fParDir(int /* i-th par */, int /* x, y, z */) const;	// Momentum direction of i-th particle

		//------------------------------------------------------------------------------------------------------------------------//

		private :
			bool	fIsCC;
			bool	fIsNC;
			bool	fIsQEL;
			bool	fIsMEC;
			bool	fIsRES;
			bool	fIsDIS;
			bool	fIsCOH;
			bool	fIsVE;

			int		fInNeuPDG;
            int		fInNucPDG;	
	        int		fOutLepPDG;	
			double	fInNeuAMom;
			double  fInNucAMom;
			double	fOutLepAMom;
			double	fInNeuDir[3];
			double	fInNucDir[3];
			double	fOutLepDir[3];

			int		fINumPar;
			int		fIParPDG[IHADMAX];
			double	fIParAMom[IHADMAX];
			double	fIParDir[IHADMAX][3];

			int		fFNumPar;
			int		fFParPDG[IHADMAX];
			double	fFParAMom[IHADMAX];
			double	fFParDir[IHADMAX][3];
			////////////////////////////////////

			void	setHadronMass();
			float	fMass[PostFSI::N_PFSI_PRT];

			float	computeEkin(int, enum PostFSI::E_PFSI_PRT);
			int		fFSIMulti[PostFSI::N_PFSI_PRT];
			float	fFSIEkin[PostFSI::N_PFSI_PRT][NFSIMAX];
};
