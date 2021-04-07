#pragma once

#include <iostream>

#include "TTree.h"
#include "TChain.h"
#include "TMath.h"

#include "DefNtagInputVars.h"

using namespace std;

const Int_t MAXNP	=500;
const Int_t MAXMCTN	=200;

class NtagRes
{
	public :
		NtagRes(Bool_t flagAmBe=false);
		virtual ~NtagRes(){};

		void createTree(TTree*, Bool_t);
		void setAmBeFlag(Bool_t);
		void setBranches(TTree*, Bool_t isRunNN=true);
		void getInputVars(int, float*);
		void computeLeptonRelated(const float*, const float*, const float*);


		Int_t		_nrun;
		Int_t		_nsub;
		Int_t		_nev;
		Int_t		_trgtype;
		Float_t 	_recpvtx[3];
		Float_t		_mctpvtx[3];
    	Int_t   	_n200max;
    	Float_t 	_t200max;
		Int_t		_tindex[MAXNP];
  
		Int_t		_np;	
		Int_t		_n10[ MAXNP ];
		Int_t		_n10n[ MAXNP ];
		Int_t		_n300n[ MAXNP ];
		Int_t		_nc[ MAXNP ];
		Float_t		_trms[ MAXNP ];
		Float_t		_mintrms6[ MAXNP ];
		Float_t		_ndwall[ MAXNP ];
		Float_t		_ntwall[ MAXNP ];
		Float_t		_llrca[MAXNP];
		Float_t		_beta1[MAXNP];
		Float_t		_beta2[MAXNP];
		Float_t		_beta3[MAXNP];
		Float_t		_beta4[MAXNP];
		Float_t		_beta5[MAXNP];
		Float_t		_accepAve[MAXNP];
		Float_t		_t0[ MAXNP ];
		Float_t		_t0n[ MAXNP ];
		Float_t		_npdist[ MAXNP ];
		Int_t		_mctruth_neutron[ MAXNP ];

		Float_t		_nvtx[ MAXNP ][3];
		Float_t 	_nvtx_mct[ MAXNP ][3];
		Float_t		_ndwall_mct[ MAXNP ];
		Float_t		_ncosac[ MAXNP ];
		Float_t		_ncosac_mct[ MAXNP ];
		Float_t		_nvtxres[ MAXNP ];		// dist. btw. true and fitted n cap. vertices
		Float_t		_npdist_mct[ MAXNP ];	// MC truth dist. btw nu int. and n cap. vertices
		Int_t		_nmcn_tot;
		Float_t		_npdist_mctTot[ MAXMCTN ];

		Float_t		_nnout[ MAXNP ];
		Bool_t		_istag[ MAXNP ];
		Bool_t		_istag_mctTot[ MAXMCTN ];
		Int_t		_nbkg_tag;
		Int_t		_nmcn_tag;
		Int_t		_ntot_tag;

		Float_t		fNCapDist[MAXNP];
		Float_t		fNCapDistLong[ MAXNP ];
		Float_t		fNCapDistTran[ MAXNP ];
		Float_t		fNCapAngAct[ MAXNP ];
		Float_t		fNCapAngInf[ MAXNP ];

		Int_t		nmcn_tot() const;
		Float_t		npdist_mctTot(Int_t) const;
		Int_t		ntot_ps() const;
		Int_t		nmcn_ps() const;
		Int_t		nbkg_ps() const;
		Int_t		ntot_nn() const;
		Int_t		nmcn_nn() const;
		Int_t		nbkg_nn() const;
		Int_t		unnmcn_ps() const;
		Int_t		unnmcn_nn_tot() const;
		Int_t		unnmcn_nn_fps() const;
		Int_t		unnbkg_nn_fps() const;
		Float_t		t0(Int_t) const;
		Float_t		t0n(Int_t) const;
		Int_t		n200max() const;
		Int_t		trgtype() const;

	private :
		Bool_t 		fAmBeFlag;
};
