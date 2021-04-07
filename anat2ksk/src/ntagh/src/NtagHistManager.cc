#include "NtagHistManager.h"

NtagHistManager::NtagHistManager() :
fPostFixPS("PS"),
fPostFixNN("NN"),
fPostFixOTH("")
{
	fnhPS	=new NtagInputVarHists();
	fnhNN	=new NtagInputVarHists();
	fnhOTH	=new NtagOtherVarHists();
};
////////////////////////////////////////////////////////////


void NtagHistManager::setInputVarHistsPostFixPS(string pf)
{
	fPostFixPS=pf;
}
////////////////////////////////////////////////////////////


void NtagHistManager::setInputVarHistsPostFixNN(string pf)
{
	fPostFixNN=pf;
}
////////////////////////////////////////////////////////////


void NtagHistManager::setOtherVarHistsPostFix(string pf)
{
	fPostFixOTH=pf;
}
////////////////////////////////////////////////////////////


void NtagHistManager::initialize()
{
	fnhPS	->setHistNamePostFix( fPostFixPS );
	fnhNN	->setHistNamePostFix( fPostFixNN );
	fnhOTH	->setHistNamePostFix( fPostFixOTH );

	fnhPS	->initializeHists();
	fnhNN	->initializeHists();
	fnhOTH	->initializeHists();
}
////////////////////////////////////////////////////////////


void NtagHistManager::fillHists(NtagRes nr, float wgt)
{
	// Num. of tagged neutrons after PS
	fnhOTH->fillHists((float)nr.ntot_ps(),eALL, eNP, wgt);
	fnhOTH->fillHists((float)nr.nmcn_ps(),eMCN, eNP, wgt);
	fnhOTH->fillHists((float)nr.nbkg_ps(),eBKG, eNP, wgt);

	// Num. of tagged neutrons after NN
	fnhOTH->fillHists((float)nr.ntot_nn(),eALL, eNN, wgt);
	fnhOTH->fillHists((float)nr.nmcn_nn(),eMCN, eNN, wgt);
	fnhOTH->fillHists((float)nr.nbkg_nn(),eBKG, eNN, wgt);


	float invars[ N_INPUT_VARS ]={};
	float vtxres=-9999.0; 
	enum E_NTAG_CAT eNC			=eNONE;
	for(int jnp=0; jnp<nr.ntot_ps(); jnp++)
	{
		nr.getInputVars(jnp, invars);
		eNC=eNONE;
		if( nr._mctruth_neutron[jnp]==1 )
		{
			eNC		=eMCN; 
			vtxres	=(float)nr._nvtxres[jnp];
			if( vtxres>NtagOtherVars::XMAX[envtxdist_PS] )
			{
				vtxres=NtagOtherVars::XMAX[envtxdist_PS]-0.01;
			}
		}
		else
		{ 
			eNC=eBKG;
			vtxres=-100.0;
		}

		// Captime (PS)
		fnhOTH->fillHists((float)nr.t0(jnp),eALL, et0_PS, 	  wgt);
		fnhOTH->fillHists((float)nr.t0(jnp),eNC,  et0_PS,     wgt);
		fnhOTH->fillHists((float)nr.t0(jnp),eALL, et0long_PS, wgt);
		fnhOTH->fillHists((float)nr.t0(jnp),eNC,  et0long_PS, wgt);

		// Rec. ncapdist (PS)
		//fnhOTH->fillHists((float)nr._npdist[jnp],eALL, enpdist_PS, wgt);
		//fnhOTH->fillHists((float)nr._npdist[jnp],eNC,  enpdist_PS, wgt);
		//
		fnhOTH->fillHists((float)nr.fNCapDist[jnp],eALL, enpdist_PS, wgt);
		fnhOTH->fillHists((float)nr.fNCapDist[jnp],eNC,  enpdist_PS, wgt);


		// N10
		fnhOTH->fillHists((float)nr._n10[jnp],eALL, eN10, wgt);
		fnhOTH->fillHists((float)nr._n10[jnp],eNC,  eN10, wgt);

		// Distance btw true and rec. n cap. verticies. (PS)
		// This is only for MC true neutrons
		fnhOTH->fillHists(vtxres, eNC, envtxdist_PS, wgt);

		// Input variables before NN
		fnhPS	->fillHists(invars, eNC, wgt);
		fnhPS	->fillHists(invars, eALL, wgt);

		// NN output 
		fnhOTH	->fillHists((float)nr._nnout[jnp], eNC, eNNout, wgt);
		fnhOTH	->fillHists((float)nr._nnout[jnp], eALL, eNNout, wgt);
		if( nr._istag[ jnp ]==1 )
		{
			fnhNN->fillHists(invars, eNC, wgt);

			// Captime (NN)
			fnhOTH->fillHists((float)nr.t0(jnp),eALL, et0_NN,	  wgt);
			fnhOTH->fillHists((float)nr.t0(jnp),eNC,  et0_NN,	  wgt);
			fnhOTH->fillHists((float)nr.t0(jnp),eALL, et0long_NN, wgt);
			fnhOTH->fillHists((float)nr.t0(jnp),eNC,  et0long_NN, wgt);

			// Rec. ncapdist (NN)
			//fnhOTH->fillHists((float)nr._npdist[jnp],eALL, enpdist_NN, wgt);
			//fnhOTH->fillHists((float)nr._npdist[jnp],eNC, enpdist_NN, wgt);
		
			fnhOTH->fillHists((float)nr.fNCapDist[jnp],eALL, enpdist_NN, wgt);
			fnhOTH->fillHists((float)nr.fNCapDist[jnp],eNC, enpdist_NN, wgt);

			fnhOTH->fillHists((float)nr.fNCapDistLong[jnp],eALL, eNPLong_NN, wgt);
			fnhOTH->fillHists((float)nr.fNCapDistLong[jnp],eNC, eNPLong_NN, wgt);

			fnhOTH->fillHists((float)nr.fNCapDistTran[jnp],eALL, eNPTran_NN, wgt);
			fnhOTH->fillHists((float)nr.fNCapDistTran[jnp],eNC, eNPTran_NN, wgt);

			fnhOTH->fillHists((float)nr.fNCapAngAct[jnp],eALL, enangAct_NN, wgt);
			fnhOTH->fillHists((float)nr.fNCapAngAct[jnp],eNC, enangAct_NN, wgt);

			fnhOTH->fillHists((float)nr.fNCapAngInf[jnp],eALL, enangInf_NN, wgt);
			fnhOTH->fillHists((float)nr.fNCapAngInf[jnp],eNC, enangInf_NN, wgt);

			// Distance btw true and rec. n cap. verticies. (NN)
			// This is only for MC true neutrons
			fnhOTH->fillHists(vtxres, eNC, envtxdist_NN, wgt);
			fnhOTH->fillHists(vtxres, eALL, envtxdist_NN, wgt);

			// Input variables after NN
			fnhNN->fillHists(invars, eNC, wgt);
			fnhNN->fillHists(invars, eALL, wgt);
		}
	}	
}
////////////////////////////////////////////////////////////


void NtagHistManager::normalizeHists(float fac)
{
	fnhPS	->normalizeHists(fac);
	fnhNN	->normalizeHists(fac);
	fnhOTH	->normalizeHists(fac);
}


////////////////////////////////////////////////////////////
void NtagHistManager::writeHists(TDirectoryFile *df,
								 enum NtagHist::E_HIST_CAT ehc,
								 enum NtagCat::E_NTAG_CAT enc)
{
	df->cd();
	writeHists(ehc, enc);
}
////////////////////////////////////////////////////////////


void NtagHistManager::writeHists(TFile *f,
								 enum NtagHist::E_HIST_CAT ehc,
								 enum NtagCat::E_NTAG_CAT enc)
{
	f->cd();
	writeHists(ehc, enc);
}
////////////////////////////////////////////////////////////


void NtagHistManager::writeHists(enum NtagHist::E_HIST_CAT ehc,
								 enum NtagCat::E_NTAG_CAT enc)
{
	if( ehc==eInVarsPS )
	{
		for(int i=0; i<N_INPUT_VARS; i++){ fnhPS->getHist(enc, i)->Write(); }
	}

	if( ehc==eInVarsNN )
	{
		for(int i=0; i<N_INPUT_VARS; i++){ fnhNN->getHist(enc, i)->Write(); }
	}

	if( ehc==eOthVars )
	{
		for(int i=0; i<N_OTHER_VARS; i++){ fnhOTH->getHist(enc, i)->Write(); }
	}
}


////////////////////////////////////////////////////////////
bool NtagHistManager::operator+=(const NtagHistManager& hm) const
{
	*fnhPS	+=*(hm.fnhPS);	
	*fnhNN	+=*(hm.fnhNN);	
	*fnhOTH	+=*(hm.fnhOTH);	
	return true;
}


void NtagHistManager::loadHists(enum NtagHist::E_HIST_CAT ehc, TDirectory* td)
{
	if( ehc==eInVarsPS ){ fnhPS	->loadHists(td); }
	if( ehc==eInVarsNN ){ fnhNN	->loadHists(td); }
	if( ehc==eOthVars ) { fnhOTH->loadHists(td); }
}


TH1D* NtagHistManager::getHist(enum NtagHist::E_HIST_CAT ehc,
							   int icat,
							   int ivar)
{
	TH1D *htmp=new TH1D();
	if( ehc==eInVarsPS ){ htmp=fnhPS ->getHist(icat, ivar); }
	if( ehc==eInVarsNN ){ htmp=fnhNN ->getHist(icat, ivar); }
	if( ehc==eOthVars ) { htmp=fnhOTH->getHist(icat, ivar); }

	return (TH1D*)htmp->Clone();
}

void NtagHistManager::setCoarserBinningInVars(bool flag)
{
	fnhPS->setCoarserBinning(flag);
	fnhNN->setCoarserBinning(flag);
}

void NtagHistManager::setCoarserBinningOthVars(bool flag)
{
	fnhOTH->setCoarserBinning(flag);
}


void NtagHistManager::setOtherVarsBinning(enum NtagOtherVars::E_OTHER_VARS eov,
										  const int nbins,
										  const double xmin, 
										  const double xmax)
{
	fnhOTH->setBinning(eov, nbins, xmin, xmax);
}
