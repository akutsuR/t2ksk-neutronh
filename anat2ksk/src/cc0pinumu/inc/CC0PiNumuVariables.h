#pragma once

#include <iostream>
#include <string>

#include "TMath.h"

#include "const.h"
#include "SKh1Variables.h"
#include "DefBeamMode.h"

using std::string;
using std::cout;
using std::endl;

using namespace Const;

class CC0PiNumuVariables
{
	public :
		CC0PiNumuVariables(BeamMode::E_BEAM_MODE);
		virtual ~CC0PiNumuVariables(){};

		void computeVariables(const SKh1Variables);
		template <typename T> T var(string) const;
		template <typename T> T var(string, int) const;
		void printError(string) const;
		bool isSupported(string);

	private :
		vector<string> fVarList;
		void setVarList();

		float fVtx[3];
		float fDir[3];
		float fInfNDir[3];
		float fEvis;
		float fMom;
		int   fDcye;
		
		float fErec; 	// MeV
		float fCosRec;
		float fPtRec;	// MeV/c
		float fQ2Rec;	// MeV^2
		float fPosZ;
		float fPosR2;
		float fDwall;
		float fPidEMu;
		float fPidCPiMu;


		float computePosR2(const float*);
		float computeDwall(const float*);
		float computeSignDist(const bool, const float, const float);
		float computeCosRec(const float*);
		float computeErec(const float, const float);
		float computePtRec(const float, const float);
		float computeQ2Rec(const float, const float, const float*);

		void computeNeutronInferredDirection();	

		void setErecMass();

		BeamMode::E_BEAM_MODE feBM;
		float fMNi;
		float fMNi2;
		float fMNf;
		float fMNf2;
};
