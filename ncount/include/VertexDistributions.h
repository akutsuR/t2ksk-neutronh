#pragma once

#include <iostream>
#include <string>

#include "TH1D.h"
#include "TDirectory.h"
#include "TKey.h"

#include "DefVertexDist.h"
#include "VertexVar_t.h"

using std::cout;
using std::endl;
using std::string;

class VertexDistributions
{
	public :
		VertexDistributions(bool, string spf="");
		virtual ~VertexDistributions();

		void fillDST(int, float, float w=1.0);
		void fillDST(const VertexVar_t, float w=1.0);
		void makeCDFsKS();
		void normalizeDST(double);

		TH1D *getDstVis(int);
		TH1D *getDstKS(int);
		TH1D *getCdfKS(int);

		void addDST(VertexDistributions*);
		void loadDST(TDirectory *td);

	private :
		void initialize();
		void initializeVis();

		bool	fIsCoarse;
		string fPostFix;
		TH1D *fhDstVis[VtxDist::N_VTX_DST];	
		TH1D *fhDstKS[VtxDist::N_VTX_DST];	
		TH1D *fhCdfKS[VtxDist::N_VTX_DST];	
};
