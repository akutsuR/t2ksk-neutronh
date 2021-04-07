#include "CC0PiNumuExtraHists.h"

CC0PiNumuExtraHists::CC0PiNumuExtraHists(string pfx) :
fPostFix(pfx)
{
	clearHists();
	setConstants();
	setDefaultNames();
}


CC0PiNumuExtraHists::CC0PiNumuExtraHists() : 
fPostFix("")
{
	clearHists();
	setConstants();
	setDefaultNames();
}


CC0PiNumuExtraHists::~CC0PiNumuExtraHists()
{
	for(int i=0; i<N_EXTRA_HIST; i++)
	{
		if( fHist[i]!=NULL )
		{
				delete fHist[i];
		}
	}
}
	

void CC0PiNumuExtraHists::clearHists()
{
	for(int i=0; i<N_EXTRA_HIST; i++)
	{
			fHist[i]=NULL;
	}
}


void CC0PiNumuExtraHists::setDefaultNames()
{
	for(int i=0; i<N_EXTRA_HIST; i++)
	{
		fDefName[i]=S_EXTRA_HIST[ i ];
	}
}


void CC0PiNumuExtraHists::setConstants()
{	
	for(int i=0; i<N_EXTRA_HIST; i++)
	{
		fNbins[ i ]	=NBINS[ i ];
		fXMax[ i ]	=XMAX[ i ];
		fXMin[ i ]	=XMIN[ i ];
	}
}


void CC0PiNumuExtraHists::setBinning(enum E_EXTRA_HIST eeh, 
									 const int nbins,
									 const double xmin, 
									 const double xmax)
{
	cout<<" [INFO] CC0PiNumuExtraHists::setBinning " 	<<endl;
	cout<<"   - Chaning binning of " << S_EXTRA_HIST[eeh]
		<<" from its default "						 	<<endl;
		fNbins[eeh]	=nbins;
		fXMax[eeh]	=xmax;
		fXMin[eeh]	=xmin;
}


void CC0PiNumuExtraHists::setHistNamePostFix(string pf)
{
	fPostFix=pf;
}


void CC0PiNumuExtraHists::initializeHists()
{
	string sn	="";
	for(int i=0; i<N_EXTRA_HIST; i++)
	{
		sn="";
		if( fPostFix!="" ){ sn=fDefName[i] + "_" + fPostFix; }
		else			  { sn=fDefName[i]; }

		if( i==eTrueEnuNuEvts )
		{
			fHist[i]=new TH1D(sn.c_str(), "",
								fNbins[i], fXMin[i], fXMax[i]);
		}

		else if( i>=eLepMomNuEvts && i<=eLepMomNtotTag )
		{
			int nbins=LepMomBin::N_LEPMOM_BINS;
			fHist[i]=new TH1D(sn.c_str(), "", nbins, LepMomBin::BinEdges);
		}

		else if( i>=eTrMomNuEvts && i<=eTrMomNtotTag )
		{
			int nbins=TrMomBin::N_TRMOM_BINS;
			fHist[i]=new TH1D(sn.c_str(), "", nbins, TrMomBin::BinEdges);
		}

		else if( i>=eRecoEnuNuEvts && i<=eRecoEnuNtotTag )
		{
			int nbins=RecoEnuBin::N_RECOENU_BINS;
			fHist[i]=new TH1D(sn.c_str(), "", nbins, RecoEnuBin::BinEdges);
		}

		else if( i>=eRecoQ2NuEvts && i<=eRecoQ2NtotTag )
		{
			int nbins=RecoQ2Bin::N_RECOQ2_BINS;
			fHist[i]=new TH1D(sn.c_str(), "", nbins, RecoQ2Bin::BinEdges);
		}

		else if( i>=eCosBmNuEvts && i<=eCosBmNtotTag )
		{
			fHist[i]=new TH1D(sn.c_str(), "",
								fNbins[i], fXMin[i], fXMax[i]);
		}

		else if( i>=efQDWallNuEvts && i<=efQDWallNtotTag )
		{
			int nbins=fQDWall::N_DWALL_BINS;
			fHist[i]=new TH1D(sn.c_str(), "", nbins, fQDWall::BinEdges);
		}

		else if( i>=efQVtxR2NuEvts && i<=efQVtxR2NtotTag )
		{
			fHist[i]=new TH1D(sn.c_str(), "",
								fNbins[i], fXMin[i], fXMax[i]);
		}

		else if( i>=efQVtxZNuEvts && i<=efQVtxZNtotTag )
		{
			fHist[i]=new TH1D(sn.c_str(), "",
								fNbins[i], fXMin[i], fXMax[i]);
		}

		else if( i>=eNuEvtsNumTagAllVis && i<=eNuEvtsNumTagAllTrMomGE__0p75 )
		{
			fHist[i]=new TH1D(sn.c_str(), "",
								fNbins[i], fXMin[i], fXMax[i]);
		}
		fHist[i]->Sumw2();
	}
}


template <typename T> void CC0PiNumuExtraHists::fillHist(enum ExtraHists::E_EXTRA_HIST eeh,
														 T t,
														 float w)
{
		fHist[eeh]->Fill(t, w);
}

template void CC0PiNumuExtraHists::fillHist(enum ExtraHists::E_EXTRA_HIST, int, float);
template void CC0PiNumuExtraHists::fillHist(enum ExtraHists::E_EXTRA_HIST, float, float);


void CC0PiNumuExtraHists::fillHists(const ExtraVar_t evar, float w)
{
	float mom		=evar.mom;		// sqrt(trans^2 + longi^2)
	float recoe		=evar.ereco;
	float recoQ2	=evar.Q2reco;
	float trmom		=evar.momtr;	// transverse mom.
	float cosBm 	=evar.cosbm;
	float dwall		=evar.fqdwall;
	float vtxr2		=evar.fqvtxr2;
	float vtxz		=evar.fqvtxz;
	int   ntotVis	=(int)evar.ntot_tag;
	int	  ntot		=(int)evar.ntot_tag;

	enum TrMomBin::E_TRMOM_BINS  etb=TrMomBin::getTrMomBin(trmom);
	enum E_EXTRA_HIST eeh=ExtraHists::eNONE;
	if( etb==TrMomBin::eTrMom0p00__0p25 )		{ eeh=eNuEvtsNumTagAllTrMom0p00__0p25; }
	else if( etb==TrMomBin::eTrMom0p25__0p50 )	{ eeh=eNuEvtsNumTagAllTrMom0p25__0p50; }
	else if( etb==TrMomBin::eTrMom0p50__0p75 )	{ eeh=eNuEvtsNumTagAllTrMom0p50__0p75; }
	else										{ eeh=eNuEvtsNumTagAllTrMomGE__0p75; }

	//int	  ntot	=(int)evar.nmcn_tag	+ evar.nbkg_tag;
	if( mom>LepMomBin::BinEdges[LepMomBin::N_LEPMOM_BINS] )
	{
		mom=LepMomBin::BinEdges[LepMomBin::N_LEPMOM_BINS]-0.001;	
	}

	if( trmom>TrMomBin::BinEdges[TrMomBin::N_TRMOM_BINS] )
	{
		trmom=TrMomBin::BinEdges[TrMomBin::N_TRMOM_BINS]-0.001;	
	}

	if( recoe>RecoEnuBin::BinEdges[RecoEnuBin::N_RECOENU_BINS] )
	{
		recoe=RecoEnuBin::BinEdges[RecoEnuBin::N_RECOENU_BINS]-0.001;	
	}
	
	if( recoQ2>RecoQ2Bin::BinEdges[RecoQ2Bin::N_RECOQ2_BINS] )
	{
		recoQ2=RecoQ2Bin::BinEdges[RecoQ2Bin::N_RECOQ2_BINS]-0.001;	
	}

	if( ntotVis>=(int)fXMax[eNuEvtsNumTagAllVis] )
	{
		ntotVis=(int)fXMax[eNuEvtsNumTagAllVis] - 1;
	}

	this->fillHist(eTrueEnuNuEvts,  evar.etrue, w);

	this->fillHist(eLepMomNuEvts,  mom, w);
	this->fillHist(eLepMomNmcnTot, mom, w*evar.nmcn_tot);
	this->fillHist(eLepMomNmcnTag, mom, w*evar.nmcn_tag);
	this->fillHist(eLepMomNbkgTag, mom, w*evar.nbkg_tag);
	this->fillHist(eLepMomNtotTag, mom, w*evar.ntot_tag);

	this->fillHist(eTrMomNuEvts,  trmom, w);
	this->fillHist(eTrMomNmcnTot, trmom, w*evar.nmcn_tot);
	this->fillHist(eTrMomNmcnTag, trmom, w*evar.nmcn_tag);
	this->fillHist(eTrMomNbkgTag, trmom, w*evar.nbkg_tag);
	this->fillHist(eTrMomNtotTag, trmom, w*evar.ntot_tag);

	this->fillHist(eRecoEnuNuEvts,  recoe, w);
	this->fillHist(eRecoEnuNmcnTot, recoe, w*evar.nmcn_tot);
	this->fillHist(eRecoEnuNmcnTag, recoe, w*evar.nmcn_tag);
	this->fillHist(eRecoEnuNbkgTag, recoe, w*evar.nbkg_tag);
	this->fillHist(eRecoEnuNtotTag, recoe, w*evar.ntot_tag);

	this->fillHist(eRecoQ2NuEvts,  recoQ2, w);
	this->fillHist(eRecoQ2NmcnTot, recoQ2, w*evar.nmcn_tot);
	this->fillHist(eRecoQ2NmcnTag, recoQ2, w*evar.nmcn_tag);
	this->fillHist(eRecoQ2NbkgTag, recoQ2, w*evar.nbkg_tag);
	this->fillHist(eRecoQ2NtotTag, recoQ2, w*evar.ntot_tag);

	this->fillHist(eCosBmNuEvts,  cosBm, w);
	this->fillHist(eCosBmNmcnTot, cosBm, w*evar.nmcn_tot);
	this->fillHist(eCosBmNmcnTag, cosBm, w*evar.nmcn_tag);
	this->fillHist(eCosBmNbkgTag, cosBm, w*evar.nbkg_tag);
	this->fillHist(eCosBmNtotTag, cosBm, w*evar.ntot_tag);

	this->fillHist(efQDWallNuEvts,  dwall, w);
	this->fillHist(efQDWallNmcnTot, dwall, w*evar.nmcn_tot);
	this->fillHist(efQDWallNmcnTag, dwall, w*evar.nmcn_tag);
	this->fillHist(efQDWallNbkgTag, dwall, w*evar.nbkg_tag);
	this->fillHist(efQDWallNtotTag, dwall, w*evar.ntot_tag);

	this->fillHist(efQVtxR2NuEvts,  vtxr2, w);
	this->fillHist(efQVtxR2NmcnTot, vtxr2, w*evar.nmcn_tot);
	this->fillHist(efQVtxR2NmcnTag, vtxr2, w*evar.nmcn_tag);
	this->fillHist(efQVtxR2NbkgTag, vtxr2, w*evar.nbkg_tag);
	this->fillHist(efQVtxR2NtotTag, vtxr2, w*evar.ntot_tag);

	this->fillHist(efQVtxZNuEvts,  vtxz, w);
	this->fillHist(efQVtxZNmcnTot, vtxz, w*evar.nmcn_tot);
	this->fillHist(efQVtxZNmcnTag, vtxz, w*evar.nmcn_tag);
	this->fillHist(efQVtxZNbkgTag, vtxz, w*evar.nbkg_tag);
	this->fillHist(efQVtxZNtotTag, vtxz, w*evar.ntot_tag);

	this->fillHist(eNuEvtsNumTagAllVis, ntotVis, w);
	this->fillHist(eNuEvtsNumTagAllFull, ntot, w);
	this->fillHist(eeh, ntot, w);
}

void CC0PiNumuExtraHists::normalizeHists(double fac)
{
	for(int i=0; i<N_EXTRA_HIST; i++)
	{
		fHist[i]->Scale( fac );
	}
}


void CC0PiNumuExtraHists::setHistsColor(int cl)
{
	for(int i=0; i<N_EXTRA_HIST; i++)
	{
		fHist[i]->SetFillColor( cl );
	}
}

TH1D* CC0PiNumuExtraHists::getHist(int ieh)
{
	E_EXTRA_HIST eeh=ExtraHists::int2enum(ieh);
	return this->getHist(eeh);
}


TH1D* CC0PiNumuExtraHists::getHist(enum ExtraHists::E_EXTRA_HIST eeh)
{
	return (TH1D*)fHist[eeh]->Clone(fDefName[eeh].c_str());
}


bool CC0PiNumuExtraHists::operator+=(const CC0PiNumuExtraHists& h) const
{
	for(int i=0; i<N_EXTRA_HIST; i++)
	{
		if( fHist[i]!=NULL )
		{
			fHist[i]->Add( (TH1D*)h.fHist[i]->Clone() );
		}
	}
	return true;
}


void CC0PiNumuExtraHists::loadHists(TDirectory *td)
{
	cout<<" [INFO] CC0PiNumuExtraHists::loadHists " <<endl;
	cout<<"   - Trying to load histograms from TDirectory "
		<<td->GetName() <<endl;

	bool isFound[N_EXTRA_HIST]={false};
	TKey *tk=NULL;
	TIter titr(td->GetListOfKeys());
	while( tk=(TKey*)titr() )
	{
		if( string(tk->GetClassName())!="TH1D" ){ continue; }

		string shn( tk->GetName() );
		for(int i=0; i<N_EXTRA_HIST; i++)
		{
			if( shn.find( S_EXTRA_HIST[i] )!=string::npos )
			{
				cout<<"     - Found " << S_EXTRA_HIST[i] <<endl;
				fHist[i]=(TH1D*)tk->ReadObj();
				fHist[i]->SetDirectory(0);
				isFound[i]=true;
				break;
			}
		}					
	}

	// Check whether all fHist[] were found or not
	bool isOK=true;
	for(int i=0; i<N_EXTRA_HIST; i++)
	{
		if( !isFound[i] )
		{
			cout<<"   - " << S_EXTRA_HIST[i] <<" was not found. "<<endl;
			isOK=false;
		}	
	}	

	if( !isOK )
	{
		cout<<" [ERROR] CC0PiNumuExtraHists::loadHists " <<endl;
		cout<<"   - All histograms were not found."		 <<endl;
		cout<<"   - Input TDirectory might be wrong."	 <<endl;
		cout<<" -> EXIT "								 <<endl;
		exit( -1 );
	}

	cout<<"   - Successfully loaded"				<<endl;
	cout<<endl;
	td->cd();
}
