#include "NtagRes.h"

NtagRes::NtagRes(Bool_t flagAmBe) :
fAmBeFlag( flagAmBe )
{
};

void NtagRes::createTree(TTree *tree, Bool_t isRunNN)
{
	// Primary event related
	tree->Branch("ntag_nrun", 			 &_nrun, 		  	"ntag_nrun/I");
	tree->Branch("ntag_nsub", 			 &_nsub, 		  	"ntag_nsub/I");
	tree->Branch("ntag_nev",  			 &_nev,	 		  	"ntag_nev/I");
	tree->Branch("ntag_trgtype",  		 &_trgtype,		  	"ntag_trgtype/I");
	tree->Branch("ntag_recpvtx", 		 _recpvtx, 		  	"ntag_recpvtx[3]/F");
	tree->Branch("ntag_mctpvtx", 		 _mctpvtx, 		  	"ntag_mctpvtx[3]/F");
	tree->Branch("ntag_n200max", 		 &_n200max, 		"ntag_n200max/I");
	tree->Branch("ntag_t200max",		 &_t200max, 		"ntag_t200max/F");

	// Input variable related
	tree->Branch("ntag_np", 			 &_np, 			  	"ntag_np/I");
	tree->Branch("ntag_n10",			 _n10, 			  	"ntag_n10[ntag_np]/I");
	tree->Branch("ntag_n10n",			 _n10n, 			"ntag_n10n[ntag_np]/I");
	tree->Branch("ntag_n300n",			 _n300n,			"ntag_n300n[ntag_np]/I");
	tree->Branch("ntag_nc",				 _nc,			  	"ntag_nc[ntag_np]/I");
	tree->Branch("ntag_trm",		 	 _trms,		  		"ntag_trms[ntag_np]/F");
	tree->Branch("ntag_mintrms6", 		 _mintrms6, 	  	"ntag_mintrms6[ntag_np]/F");
	tree->Branch("ntag_ndwall",			 _ndwall,		  	"ntag_ndwall[ntag_np]/F");
	tree->Branch("ntag_ntwall",			 _ntwall,		  	"ntag_ntwall[ntag_np]/F");
	tree->Branch("ntag_llrca",			 _llrca,			"ntag_llrca[ntag_np]/F");
	tree->Branch("ntag_beta1",			 _beta1,		  	"ntag_beta1[ntag_np]/F");
	tree->Branch("ntag_beta2",			 _beta2,		  	"ntag_beta2[ntag_np]/F");
	tree->Branch("ntag_beta3",			 _beta3,		  	"ntag_beta3[ntag_np]/F");
	tree->Branch("ntag_beta4",			 _beta4,		  	"ntag_beta4[ntag_np]/F");
	tree->Branch("ntag_beta5",			 _beta5,		  	"ntag_beta5[ntag_np]/F");
	tree->Branch("ntag_accepAve",		 _accepAve,		  	"ntag_accepAve[ntag_np]/F");

	// New and MC truth variables
	tree->Branch("ntag_t0",				 _t0,		  	  	"ntag_t0[ntag_np]/F");
	tree->Branch("ntag_t0n",			 _t0n,		  	  	"ntag_t0n[ntag_np]/F");
	tree->Branch("ntag_npdist",			 _npdist,			"ntag_npdist[ntag_np]/F");
	tree->Branch("ntag_mctruth_neutron", _mctruth_neutron,	"ntag_mctruth_neutron[ntag_np]/I");
	tree->Branch("ntag_nvtx",			 _nvtx,			  	"ntag_nvtx[ntag_np][3]/F");
	tree->Branch("ntag_nvtxres",		 _nvtxres,		  	"ntag_nvtxres[ntag_np]/F");
	tree->Branch("ntag_ncosac",			 _ncosac,		  	"ntag_ncosac[ntag_np]/F");
	tree->Branch("ntag_ndwall_mct",		 _ndwall_mct,		"ntag_ndwall_mct[ntag_np]/F");
	tree->Branch("ntag_npdist_mct",		 _npdist_mct,	  	"ntag_npdist_mct[ntag_np]/F");
	tree->Branch("ntag_ncosac_mct",		 _ncosac_mct,	  	"ntag_ncosnt_mct[ntag_np]/F");
	tree->Branch("ntag_nvtx_mct",		 _nvtx_mct,		  	"ntag_nvtx_mct[ntag_np][3]/F"); 
	tree->Branch("ntag_nmcn_tot",		 &_nmcn_tot,		"ntag_nmcn_tot/I");
	tree->Branch("ntag_npdist_mctTot",	 _npdist_mctTot,	"ntag_npdist_mctTot[ntag_nmcn_tot]/F");

	// NN related
	if( isRunNN )
	{
		tree->Branch("ntag_nnout",			_nnout,		  	  	"ntag_nnout[ntag_np]/F");
		tree->Branch("ntag_istag",			_istag,		  	  	"ntag_istag[ntag_np]/O");
		tree->Branch("ntag_istag_mctTot",	_istag_mctTot,      "ntag_istag_mctTot[ntag_nmcn_tot]/O");
		tree->Branch("ntag_ntot_tag",		&_ntot_tag,		  	"ntag_ntot_tag/I");
		tree->Branch("ntag_nmcn_tag",		&_nmcn_tag,		  	"ntag_nmcn_tag/I");
		tree->Branch("ntag_nbkg_tag",		&_nbkg_tag,		  	"ntag_nbkg_tag/I");
	}
}

void NtagRes::setAmBeFlag(Bool_t flag)
{
	// If fAmBeFlag==true, then
	// branches for n200max and t200max
	// will be set in 
	// ** void setBranches(TTree*, Bool_t) **.
	// (This implementation is due to historical
	//  reason of developing ntag codes)

	fAmBeFlag=flag;
}


void NtagRes::setBranches(TTree *tree, Bool_t isRunNN)
{
	tree->SetBranchAddress("ntag_nrun",				&_nrun);
	tree->SetBranchAddress("ntag_nsub",				&_nsub);
	tree->SetBranchAddress("ntag_nev",				&_nev);
	tree->SetBranchAddress("ntag_trgtype", 			&_trgtype);
	tree->SetBranchAddress("ntag_recpvtx",			_recpvtx);
	tree->SetBranchAddress("ntag_mctpvtx",			_mctpvtx);
	if( fAmBeFlag )
	{
		tree->SetBranchAddress("ntag_n200max", 		&_n200max);
		tree->SetBranchAddress("ntag_t200max",		&_t200max);
	}

	tree->SetBranchAddress("ntag_np", 				&_np);
	tree->SetBranchAddress("ntag_n10",				_n10);
	tree->SetBranchAddress("ntag_n10n",				_n10n);
	tree->SetBranchAddress("ntag_n300n",			_n300n);
	tree->SetBranchAddress("ntag_nc",				_nc);
	tree->SetBranchAddress("ntag_trm",				_trms);
	tree->SetBranchAddress("ntag_mintrms6",			_mintrms6);
	tree->SetBranchAddress("ntag_ndwall",			_ndwall);
	tree->SetBranchAddress("ntag_ntwall",			_ntwall);
	tree->SetBranchAddress("ntag_llrca",			_llrca);
	tree->SetBranchAddress("ntag_beta1",			_beta1);
	tree->SetBranchAddress("ntag_beta2",			_beta2);
	tree->SetBranchAddress("ntag_beta3",			_beta3);
	tree->SetBranchAddress("ntag_beta4",			_beta4);
	tree->SetBranchAddress("ntag_beta5",			_beta5);
	tree->SetBranchAddress("ntag_accepAve",			_accepAve);

	// New and MC truth variables
	tree->SetBranchAddress("ntag_t0",				_t0);
	tree->SetBranchAddress("ntag_t0n",				_t0n);
	tree->SetBranchAddress("ntag_npdist",			_npdist);
	tree->SetBranchAddress("ntag_mctruth_neutron",	_mctruth_neutron);
	tree->SetBranchAddress("ntag_nvtx",				_nvtx);
	tree->SetBranchAddress("ntag_nvtxres",			_nvtxres);
	tree->SetBranchAddress("ntag_ncosac",			_ncosac);
	tree->SetBranchAddress("ntag_ndwall_mct",		_ndwall_mct);
	tree->SetBranchAddress("ntag_npdist_mct",		_npdist_mct);
	tree->SetBranchAddress("ntag_ncosac_mct",		_ncosac_mct);
	tree->SetBranchAddress("ntag_nvtx_mct",			_nvtx_mct); 
	tree->SetBranchAddress("ntag_nmcn_tot",			&_nmcn_tot);
	tree->SetBranchAddress("ntag_npdist_mctTot",	_npdist_mctTot);

	// NN related
	if( isRunNN )
	{
		tree->SetBranchAddress("ntag_nnout",		_nnout);
		tree->SetBranchAddress("ntag_istag",		_istag);
		tree->SetBranchAddress("ntag_istag_mctTot", _istag_mctTot);
		tree->SetBranchAddress("ntag_ntot_tag",		&_ntot_tag);
		tree->SetBranchAddress("ntag_nmcn_tag",		&_nmcn_tag);
		tree->SetBranchAddress("ntag_nbkg_tag",		&_nbkg_tag);
	}
}


void NtagRes::getInputVars(int inp, float* vars)
{	
	vars[ NtagInputVars::eN10n ]	=_n10n[ inp ];
	vars[ NtagInputVars::eNcS ]		=_n10n[ inp ]	- _nc[ inp ];
	vars[ NtagInputVars::eN300S ]	=_n300n[ inp ]	- _n10n[ inp ];
	vars[ NtagInputVars::enDwall ]	=_ndwall[ inp ];
	vars[ NtagInputVars::enTwall ]	=_ntwall[ inp ];
	vars[ NtagInputVars::elnAccep ]	=_accepAve[ inp ];
	vars[ NtagInputVars::ellrCAng ]	=_llrca[ inp ];
	vars[ NtagInputVars::eBeta1 ]	=_beta1[ inp ];
	vars[ NtagInputVars::eBeta2 ]	=_beta2[ inp ];
	vars[ NtagInputVars::eBeta3 ]	=_beta3[ inp ];
	vars[ NtagInputVars::eBeta4 ]	=_beta4[ inp ];
	vars[ NtagInputVars::eBeta5 ]	=_beta5[ inp ];
	vars[ NtagInputVars::etSD ]		=_trms[ inp ];
	vars[ NtagInputVars::etSDMin6 ]	=_mintrms6[ inp ];
}

/////////////////////////////////////////////////////////////////////////////////

void NtagRes::computeLeptonRelated(const float* nudir, const float* nuvtx, const float *ndirinf)
{
	for(int i=0; i<_np; i++)
	{
		if( _istag[i]==1 )
		//if( _mctruth_neutron[i]==1 )
		{
			float dist[3]={0.0};
			for(int j=0; j<3; j++){ dist[j]=_nvtx[i][j] - nuvtx[j]; }

			fNCapDistLong[i]	=0.0;
			fNCapDistTran[i]	=0.0;
			fNCapDist[i]		=0.0;
			fNCapAngAct[i]		=0.0;
			fNCapAngInf[i]		=0.0;
			for(int j=0; j<3; j++)
			{ 
				fNCapDist[i]	+=dist[j]*dist[j];
				fNCapDistLong[i]+=dist[j]*nudir[j];
				fNCapAngAct[i]	+=dist[j]*nudir[j];
				fNCapAngInf[i]	+=dist[j]*ndirinf[j];
			}

			fNCapDist[i]	 =TMath::Sqrt( fNCapDist[i] );
			fNCapAngAct[i]	/=fNCapDist[i];
			fNCapAngInf[i]	/=fNCapDist[i];

			fNCapDistTran[i] +=fNCapDist[i]*fNCapDist[i];
			fNCapDistTran[i] -=fNCapDistLong[i]*fNCapDistLong[i];
			fNCapDistTran[i]  =TMath::Sqrt( fNCapDistTran[i] );
		}
		else
		{
			fNCapDist[i]		=-9999.9;
			fNCapDistLong[i]	=-9999.9;
			fNCapAngAct[i]		=-9999.9;
			fNCapAngInf[i]		=-9999.9;
		}
	}
}
/////////////////////////////////////////////////////////////////////////
Int_t NtagRes::nmcn_tot() const 
{
	return _nmcn_tot;
}

Float_t NtagRes::npdist_mctTot(Int_t i) const
{
	return _npdist_mctTot[i];
}

Int_t NtagRes::nmcn_ps() const
{
	Int_t n=0;
	for(Int_t i=0; i<_np; i++)
	{
		if( _mctruth_neutron[i]==1 )
		{
			n+=1;
		}
	}
	return n;
}


Int_t NtagRes::nbkg_ps() const
{
	Int_t n=0;
	for(Int_t i=0; i<_np; i++)
	{
		if( _mctruth_neutron[i]==0 )
		{
			n+=1;
		}
	}
	return n;
}


Int_t NtagRes::ntot_ps() const
{
	return _np;
}


Int_t NtagRes::nmcn_nn() const
{
	return _nmcn_tag;
}


Int_t NtagRes::nbkg_nn() const
{
	return _nbkg_tag;
}


Int_t NtagRes::ntot_nn() const
{
	return _ntot_tag;
}


Int_t NtagRes::unnmcn_ps() const
{
// Returen number of neutrons that were not tagged in
// in the primary selection (PS)

	Int_t n=nmcn_tot() - nmcn_ps();
	if( n<0 )
	{
		cout<<" [WARNING] NtagRes::unnmcn_ps" <<endl;
		cout<<"   - Detected negative value :" << n 
			<<" -> Set the value to ** ZERO ** " <<endl;
		cout<<"   - Should not be happened ideally. (but, it's possible due to" <<
			  " the current method to identify true 2.2 MeV gammas)" <<endl;
		n=0;
	}
	return n;
}


Int_t NtagRes::unnmcn_nn_tot() const
{
// Retrun number of neutrons that were not tagged in
// both the primary selection and neural network
// classification
	Int_t n=nmcn_tot() - nmcn_nn();
	return n;
}


Int_t NtagRes::unnmcn_nn_fps() const
{
// Retrun number of neutrons that were selected in
// the primary selection, but were not tagged in 
// the neural network classification
	Int_t n=nmcn_ps() - nmcn_nn();
	return n;
}


Int_t NtagRes::unnbkg_nn_fps() const
{
// Retrun number of bkg. that were selected in
// the primary selection, but were not tagged in 
// the neural network classification
	Int_t n=nbkg_ps() - nbkg_nn();
	return n;
}


Float_t NtagRes::t0(Int_t inp) const
{
// Retrun rec. cap. time computed
// using primary vertex
	return _t0[ inp ]/1000.0; // ns -> us
}


Float_t NtagRes::t0n(Int_t inp) const
{
// Retrun rec. cap. time computed
// using rec. ncap vertex
	return _t0n[ inp ]/1000.0; // ns -> us
}


Int_t NtagRes::n200max() const
{
// Used for Am/Be calib
	return _n200max;
}


Int_t NtagRes::trgtype() const
{
// Used for Am/Be calib
	return _trgtype;
}
