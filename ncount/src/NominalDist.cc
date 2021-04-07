#include "NominalDist.h"

NominalDist::NominalDist(CmdLineArgParser arg) :
fCmdArg( arg )
{
	fTchfQMR=NULL;
	fTchRege=NULL;
	fTchNtag=NULL;
	fTchXSec=NULL;

	fNumu	=NULL;
	fNtag	=NULL;
	for(int i=0; i<IntCat::N_INT_CAT; i++)
	{
		fhEvselNuev[i]	=NULL;
		fhExtra[i]		=NULL;
		fhNtag[i]		=NULL;
		fhVtxDist[i]	=NULL;
		fhMCTDist[i]	=NULL;
	}

	for(int i=0; i<IntCat::N_ICAT_NTAG; i++)
	{
		fhEvselNtag[i]=NULL;
	}
	
	this->initiToyTagging();
}	


NominalDist::~NominalDist()
{
	if( fTchfQMR ){ delete fTchfQMR;	fTchfQMR=NULL;}
	if( fTchRege ){ delete fTchRege;	fTchRege=NULL;}
	if( fTchNtag ){ delete fTchNtag;	fTchNtag=NULL;}
	if( fTchXSec ){ delete fTchXSec;	fTchXSec=NULL;}

	if( fNumu )	  { delete fNumu;		fNumu	=NULL;}
	if( fNtag )	  { delete fNtag;		fNtag	=NULL;}

	for(int i=0; i<IntCat::N_INT_CAT+1; i++)
	{
		if( fhEvselNuev[i] ){ delete fhEvselNuev[i]; fhEvselNuev[i]=NULL;}
		if( fhExtra[i] )	{ delete fhExtra[i]; 	 fhExtra[i]	=NULL;}
		if( fhVtxDist[i] )	{ delete fhVtxDist[i];	 fhVtxDist[i]=NULL; }
		if( fhMCTDist[i] )	{ delete fhMCTDist[i];	 fhMCTDist[i]=NULL; }
	}

	for(int i=0; i<IntCat::N_ICAT_NTAG+1; i++)
	{
		if( fhEvselNtag[i] ){ delete fhEvselNtag[i]; fhEvselNtag[i]=NULL; }
	}
}


void NominalDist::initialize()
{
	this->loadInputs();
	this->configure();
	this->initiOutputs();
}


void NominalDist::loadInputs()
{
	fTchfQMR	=new TChain("h1");
	fTchRege	=new TChain("h1");
	fTchNtag	=new TChain("ntag");
	fTchXSec	=new TChain("weightstree");

	int nfQMR		=0,
		nRege		=0,
		nNtag		=0,
		nXSecWgt	=0;
	// h1 tree containing fiTQun MR results	
	if( fCmdArg.fInfQMR!="" )
	{
		nfQMR=fTchfQMR->Add( fCmdArg.fInfQMR.c_str() );
		cout<<" Loaded fQMR " << nfQMR <<" files" <<endl;
	}


	// h1 tree containing regenerated secondaries
	if( fCmdArg.fInRege!="" )
	{
		nRege=fTchRege->Add( fCmdArg.fInRege.c_str() );
		if( nRege!=nfQMR )
		{
			cout<<" [ERROR] NominalDist::loadInputs "		   <<endl;
			cout<<"   - Different # files for Rege :" << nRege <<endl;
			cout<<" -> EXIT " 								   <<endl;
			exit( -1 );
		}
		cout<<" Loaded Rege " << nRege <<" files" <<endl;
		fTchfQMR->AddFriend( fTchRege );
	}


	// ntag tree containing ntag results
	if( fCmdArg.fInNtag!="" )
	{
		nNtag=fTchNtag->Add( fCmdArg.fInNtag.c_str() );
		if( nNtag!=nfQMR )
		{
			cout<<" [ERROR] NominalDist::loadInputs "		   <<endl;
			cout<<"   - Different # files for Ntag :" << nNtag <<endl;
			cout<<" -> EXIT " 								   <<endl;
			exit( -1 );
		}
		cout<<" Loaded Ntag " << nNtag <<" files" <<endl;
		fTchfQMR->AddFriend( fTchNtag );
	}


	// weightstree tree containing XSec wgt
	if( fCmdArg.fInXSecWgt!="" )
	{
		nXSecWgt=fTchXSec->Add( fCmdArg.fInXSecWgt.c_str() );
		if( nXSecWgt!=nfQMR )
		{
			cout<<" [ERROR] NominalDist::loadInputs "		   			<<endl;
			cout<<"   - Different # files for XSecWgt :" << nXSecWgt	<<endl;
			cout<<" -> EXIT " 								 			<<endl;
			exit( -1 );
		}
		cout<<" Loaded XSecWgt " << nXSecWgt <<" files" <<endl;
		fTchfQMR->AddFriend( fTchXSec );
	}
}


void NominalDist::configure()
{
	fNumu=new CC0PiNumu(fCmdArg.fBeamMode, fCmdArg.fOscChan);	
	fNumu->resisterDefaultAllStacks();
	fNumu->setTrueWallEventsLastHalfMC();
	fNumu->seth1Tree(fTchfQMR);
	fNumu->setXSecWgtTree(fTchXSec);

	fNtag=new NtagRes();
	fNtag->setBranches( fTchNtag );
}


void NominalDist::initiOutputs()
{
	string spfx="";
	for(int i=0; i<IntCat::N_INT_CAT+1; i++)
	{
		if( i==IntCat::N_INT_CAT )
		{
			spfx="nuev_all";
			if( fCmdArg.fOscChan==eDATA ){ spfx="nuev_data"; }
		}
		else
		{
			spfx="nuev_" + IntCat::S_INT_CAT[i];
		}
		fhEvselNuev[i]=new CC0PiNumuEvSelHists(spfx);
		fhEvselNuev[i]->initializeHists();
	}

	for(int i=0; i<IntCat::N_ICAT_NTAG+1; i++)
	{
		if( i==IntCat::N_ICAT_NTAG )
		{
			spfx="ntag_allmcn";
			if( fCmdArg.fOscChan==eDATA ){ spfx="ntag_data"; }
		}
		else
		{
			spfx="ntag_" + IntCat::S_INT_CAT[i];
		}
		fhEvselNtag[i]=new CC0PiNumuEvSelHists(spfx);
		fhEvselNtag[i]->initializeHists();
	}

	for(int i=0; i<IntCat::N_INT_CAT+1; i++)
	{
		if( i==IntCat::N_INT_CAT )
		{
			spfx="all";
			if( fCmdArg.fOscChan==eDATA ){ spfx="data"; }
		}
		else
		{
			spfx=IntCat::S_INT_CAT[i];
		}
		fhExtra[i]=new CC0PiNumuExtraHists(spfx);
		fhExtra[i]->initializeHists();
	}

	string sp_inps="",
		   sp_innn="",
		   sp_oth="";
	for(int i=0; i<IntCat::N_INT_CAT+1; i++)
	{
		if( i==IntCat::N_INT_CAT )
		{	
			spfx="all"; 
			if( fCmdArg.fOscChan==eDATA ){ spfx="data"; }
		}
		else					  { spfx=IntCat::S_INT_CAT[i]; }
		sp_inps	="ps_" + spfx;	
		sp_innn	="nn_" + spfx;	
		sp_oth	=spfx;	
		fhNtag[i]=new NtagHistManager();
		fhNtag[i]->setInputVarHistsPostFixPS(sp_inps);
		fhNtag[i]->setInputVarHistsPostFixNN(sp_innn);
		fhNtag[i]->setOtherVarHistsPostFix(sp_oth);
		fhNtag[i]->setCoarserBinningOthVars(true);
		fhNtag[i]->initialize();
	}

	// For KS-test vertex distributions
	for(int i=0; i<IntCat::N_INT_CAT+1; i++)
	{
		if( i==IntCat::N_INT_CAT )
		{	
			spfx="all"; 
			if( fCmdArg.fOscChan==eDATA ){ spfx="data"; }
		}
		else
		{ 
			spfx=IntCat::S_INT_CAT[i];
		}

		// Use coarser binning in case of 1R numu sample
		if( fCmdArg.fIsFCFVOnly )
		{
			fhVtxDist[i]=new VertexDistributions(false, spfx);
		}
		else
		{
			fhVtxDist[i]=new VertexDistributions(true, spfx);
		}
	}

	// MC truth distribution
	for(int i=0; i<IntCat::N_INT_CAT+1; i++)
	{
		if( i==IntCat::N_INT_CAT )
		{	
			spfx="all"; 
			if( fCmdArg.fOscChan==eDATA ){ spfx="data"; }
		}
		else
		{ 
			spfx=IntCat::S_INT_CAT[i];
		}
		fhMCTDist[i]=new MCTruthDistributions(spfx);
	}
}



void NominalDist::loopEvents()
{
	int nentries=fTchfQMR->GetEntries();
	cout<<" Loop for " << nentries <<" entries " <<endl;
	for(int i=0; i<nentries; i++)
	{
		fTchfQMR->GetEntry(i);
		fNumu->computeCC0PiVariables();
		bool iscc0pi	=fNumu->applyfQ1RCC0PiNumuCut();

		float nudir[3]={0.0};
		float nuvtx[3]={0.0};
		float ninfdir[3]={0.0};
		for(int j=0; j<3; j++)
		{
			nudir[j]	=fNumu->var<float>("beamdir", j);
			nuvtx[j]	=fNumu->var<float>("fqpos", j);
			ninfdir[j]	=fNumu->var<float>("ninfdir", j);
		}
		fNtag->computeLeptonRelated(nudir, nuvtx, ninfdir);


		// Only for data
		if( fCmdArg.fOscChan==eDATA && fNumu->isWrongSignSpill() ){ continue; }
		if( fCmdArg.fOscChan==eDATA && fNumu->var<float>("fqdwall")<200 ){ continue; }


		float wtot		=1.0;
		float wntag_mcn	=1.0;
		float wntag_bkg	=1.0;
		enum IntCat::E_INT_CAT eic=IntCat::eNONE;

		EvSelVar_t evselvar	= fNumu->getEvSelVar();
		VertexVar_t vv		= this->getVertexVar();
        MCTruthVar_t mv;
        if( fCmdArg.fOscChan!=eDATA ){ mv = this->getMCTruthVar(); }

		int toy_ntag_mcn=0;
		int toy_ntag_bkg=0;
		int toy_ntag_tot=0;
		if( fCmdArg.fOscChan!=eDATA )
		{
			toy_ntag_mcn=fToyTag->getTaggedSignal(fNtag->nmcn_tot());
			toy_ntag_bkg=fToyTag->getTaggedBackground(fNtag->nbkg_ps());
			toy_ntag_tot=toy_ntag_mcn + toy_ntag_bkg;
		}

		//----> MC
		if( fCmdArg.fOscChan!=eDATA && 
			fCmdArg.fOscChan!=OscChan::eNONE )
		{
			float wosc		=fNumu->getOscWgt();
			float wflx		=fNumu->getFluxWgt();
			float wsf		=fNumu->getXSecWgt( WgtXSec::SF_RFGRelRPA );
			float wcccoh	=fNumu->getCCCohWgt();
			wtot		*=wosc*wsf*wcccoh*wflx;
			wntag_mcn	 =wtot*fNtag->nmcn_nn()*fWTvarSig;
			wntag_bkg	 =wtot*fNtag->nbkg_nn()*fWTvarBkg;

			eic=fNumu->getIntCat();
			fhEvselNuev[ eic ]					->fillHists(evselvar, wtot);
			fhEvselNtag[ eic ]					->fillHists(evselvar, wntag_mcn);

			fhEvselNuev[ IntCat::N_INT_CAT ]	->fillHists(evselvar, wtot);
			fhEvselNtag[ IntCat::eACCBKG ]		->fillHists(evselvar, wntag_bkg);
			fhEvselNtag[ IntCat::N_ICAT_NTAG ]	->fillHists(evselvar, wntag_mcn);
	
			// Assumed to be used only for data quality check
			if( fCmdArg.fIsFCFVOnly )
			{
				fhVtxDist[ eic ]				->fillDST(vv, wtot);
				fhVtxDist[ IntCat::N_INT_CAT ]	->fillDST(vv, wtot);
				fhNtag[ eic ]->fillHists(*fNtag, wtot);
				fhNtag[ IntCat::N_INT_CAT ]->fillHists(*fNtag, wtot);
			}
		}
		else //----> Data
		{
			fhEvselNuev[ IntCat::N_INT_CAT ]	->fillHists(evselvar, wtot);
			fhEvselNtag[ IntCat::N_ICAT_NTAG ]	->fillHists(evselvar, fNtag->ntot_nn());

			if( fCmdArg.fIsFCFVOnly )
			{
				fhVtxDist[ IntCat::N_INT_CAT ]		->fillDST(vv, wtot);
				fhNtag[ IntCat::N_INT_CAT ]			->fillHists(*fNtag, wtot);
			}
		}


		if( iscc0pi )
		{
			ExtraVar_t exvar;
			exvar.etrue		=fNumu->var<float>("pnu", 0);
			exvar.ereco		=fNumu->var<float>("erec")/1.0e3;	// MeV -> GeV
			exvar.Q2reco	=fNumu->var<float>("Q2rec")/1.0e6;	// MeV^2 -> GeV^2
			exvar.momtr		=fNumu->var<float>("momtr")/1.0e3;	// MeV->GeV
			exvar.mom		=fNumu->var<float>("fqmomm")/1.0e3;	// MeV->GeV
			exvar.cosbm		=fNumu->var<float>("cosbm");
			exvar.fqdwall	=fNumu->var<float>("fqdwall");
			exvar.fqvtxr2	=fNumu->var<float>("fqposr2");
			exvar.fqvtxz	=fNumu->var<float>("fqposz");
			exvar.ntot_tag	=fNtag->ntot_nn();
			if( fCmdArg.fOscChan!=eDATA ){ exvar.ntot_tag	=toy_ntag_tot;}

			//---> For MC
			if( fCmdArg.fOscChan!=eDATA && 
				fCmdArg.fOscChan!=OscChan::eNONE )
			{
				//exvar.nmcn_tot	=fNtag->nmcn_tot();
				//exvar.nmcn_tag	=fNtag->nmcn_nn();
				//exvar.nbkg_tag	=fNtag->nbkg_nn();

				exvar.ntot_tag	=toy_ntag_tot;
				exvar.nmcn_tot	=fNtag->nmcn_tot();
				exvar.nmcn_tag	=fNtag->nmcn_nn()*fWTvarSig;
				exvar.nbkg_tag	=fNtag->nbkg_nn()*fWTvarBkg;

				fhExtra[ eic ]	->fillHists(exvar, wtot);

				// Should be normal case
				if( !fCmdArg.fIsFCFVOnly )
				{
					fhNtag[ eic ]		->fillHists(*fNtag, wtot);
					fhVtxDist[ eic ]	->fillDST(vv, wtot);
					fhMCTDist[ eic ]	->fillDST(mv, wtot);
				}
			}

			fhExtra[ IntCat::N_INT_CAT ]	->fillHists(exvar, wtot);
			// Should be normal case
			if( !fCmdArg.fIsFCFVOnly )
			{
				fhNtag[ IntCat::N_INT_CAT ]		->fillHists(*fNtag, wtot);
				fhVtxDist[ IntCat::N_INT_CAT ]	->fillDST(vv, wtot);
				fhMCTDist[ IntCat::N_INT_CAT ]	->fillDST(mv, wtot);
			}
		}
	}
}


void NominalDist::writeOutputs()
{
	const int Nntagsub=3;
	const string Sntagsub[ Nntagsub ]=
					{ "NtagInputVarsPS",
					  "NtagInputVarsNN",
					  "NtagOtherVars"
					};
	string st="";

	TDirectoryFile *dfEvselNuev=NULL;
	TDirectoryFile *dfEvselNuevSub[IntCat::N_INT_CAT+1];
	TDirectoryFile *dfEvselNtag=NULL;
	TDirectoryFile *dfEvselNtagSub[IntCat::N_ICAT_NTAG+1];
	TDirectoryFile *dfExtra=NULL;
	TDirectoryFile *dfExtraSub[IntCat::N_INT_CAT+1];
	TDirectoryFile *dfNtag=NULL;	
	TDirectoryFile *dfNtagSub[IntCat::N_INT_CAT+1];
	TDirectoryFile *dfNtagSubSub[IntCat::N_INT_CAT+1][Nntagsub];
	TDirectoryFile *dfVtxDist=NULL;
	TDirectoryFile *dfVtxDistSub[IntCat::N_ICAT_NTAG+1];
	TDirectoryFile *dfMCTDist=NULL;
	TDirectoryFile *dfMCTDistSub[IntCat::N_ICAT_NTAG+1];



	TFile *fout=new TFile(fCmdArg.fOutFile.c_str(), "recreate");

	// Event selection hist for Nu envents
	fout->cd();
	dfEvselNuev=(TDirectoryFile*)fout->mkdir("EvselNuev");
		for(int i=0; i<IntCat::N_INT_CAT+1; i++)
		{
			if( fCmdArg.fOscChan!=eDATA && 
				fCmdArg.fOscChan!=OscChan::eNONE )
			{
				if( i==IntCat::N_INT_CAT ){	st="Nuev_all"; }
				else					  { st="Nuev_" + IntCat::S_INT_CAT[i]; }
				dfEvselNuev->cd();
				dfEvselNuevSub[i]=(TDirectoryFile*)dfEvselNuev->mkdir( st.c_str() );
				
					dfEvselNuevSub[i]->cd();
					for(int j=0; j<EvSelHists::N_EVSEL_HIST; j++)
					{
						fhEvselNuev[i]->getHist(j)->Write();
					}
			}
			else // for data
			{
				if( i==IntCat::N_INT_CAT )
				{	
					st="Nuev_data";
					dfEvselNuev->cd();
					dfEvselNuevSub[i]=(TDirectoryFile*)dfEvselNuev->mkdir( st.c_str() );
				
					dfEvselNuevSub[i]->cd();
					for(int j=0; j<EvSelHists::N_EVSEL_HIST; j++)
					{
						fhEvselNuev[i]->getHist(j)->Write();
					}
				}
				else{ continue; }
			}
		}

	// Event selection hist for tagged n (mcn + bkg)
	fout->cd();
		dfEvselNtag=(TDirectoryFile*)fout->mkdir("EvselNtag");
		for(int i=0; i<IntCat::N_ICAT_NTAG+1; i++)
		{
			if( fCmdArg.fOscChan!=eDATA && 
				fCmdArg.fOscChan!=OscChan::eNONE )
			{
				if( i==IntCat::N_ICAT_NTAG ){ st="Ntag_allmcn"; }
				else						{ st="Ntag_" + IntCat::S_INT_CAT[i]; }
				dfEvselNtag->cd();
				dfEvselNtagSub[i]=(TDirectoryFile*)dfEvselNtag->mkdir( st.c_str() );
				
					dfEvselNtagSub[i]->cd();
					for(int j=0; j<EvSelHists::N_EVSEL_HIST; j++)
					{
						fhEvselNtag[i]->getHist(j)->Write();
					}
			}
			else // for data
			{
				if( i==IntCat::N_ICAT_NTAG )
				{ 
					st="Ntag_data";
					dfEvselNtag->cd();
					dfEvselNtagSub[i]=(TDirectoryFile*)dfEvselNtag->mkdir( st.c_str() );
						dfEvselNtagSub[i]->cd();
						for(int j=0; j<EvSelHists::N_EVSEL_HIST; j++)
						{
							fhEvselNtag[i]->getHist(j)->Write();
						}
				}
				else{ continue; }
			}
		}


	// Histograms after the CC0pi numu selection
	fout->cd();
	dfExtra=(TDirectoryFile*)fout->mkdir("Extra");
		for(int i=0; i<IntCat::N_INT_CAT+1; i++)
		{
			if( fCmdArg.fOscChan!=eDATA && 
				fCmdArg.fOscChan!=OscChan::eNONE )
			{
				if( i==IntCat::N_INT_CAT ){ st="ExHist_all"; }
				else					  { st="ExHist_" + IntCat::S_INT_CAT[i]; }
				dfExtra->cd();
				dfExtraSub[i]=(TDirectoryFile*)dfExtra->mkdir( st.c_str() );
				
					dfExtraSub[i]->cd();
					for(int j=0; j<ExtraHists::N_EXTRA_HIST; j++)
					{
						fhExtra[i]->getHist(j)->Write();
					}
			}
			else // for data
			{
				if( i==IntCat::N_INT_CAT )
				{ 
					st="ExHist_data";
					dfExtra->cd();
					dfExtraSub[i]=(TDirectoryFile*)dfExtra->mkdir( st.c_str() );
				
						dfExtraSub[i]->cd();
						for(int j=0; j<ExtraHists::N_EXTRA_HIST; j++)
						{
							fhExtra[i]->getHist(j)->Write();
						}
				}
				else{ continue; }
			}
		}


	// Ntag histograms after the CC0pi numu selection 
	fout->cd();
	dfNtag=(TDirectoryFile*)fout->mkdir("Ntag");
		for(int i=0; i<IntCat::N_INT_CAT+1; i++)
		{
			if( fCmdArg.fOscChan!=eDATA && 
				fCmdArg.fOscChan!=OscChan::eNONE )
			{
				if( i==IntCat::N_INT_CAT ){ st="NtagHist_all"; }
				else					  { st="NtagHist_" + IntCat::S_INT_CAT[i]; }
				dfNtag->cd();

				dfNtagSub[i]=(TDirectoryFile*)dfNtag->mkdir( st.c_str() );
				dfNtagSub[i]->cd();
				for(int j=0; j<Nntagsub; j++)
				{
					dfNtagSub[i]->cd();
					dfNtagSubSub[i][j]=(TDirectoryFile*)dfNtagSub[i]->mkdir( Sntagsub[j].c_str() );
					dfNtagSubSub[i][j]->cd();
					
					if( j==0 )
					{
						fhNtag[i]->writeHists(dfNtagSubSub[i][j], NtagHist::eInVarsPS, NtagCat::eMCN);
						fhNtag[i]->writeHists(dfNtagSubSub[i][j], NtagHist::eInVarsPS, NtagCat::eBKG);
					}
					else if( j==1 )
					{
						fhNtag[i]->writeHists(dfNtagSubSub[i][j], NtagHist::eInVarsNN, NtagCat::eMCN);
						fhNtag[i]->writeHists(dfNtagSubSub[i][j], NtagHist::eInVarsNN, NtagCat::eBKG);
					}
					else
					{
						fhNtag[i]->writeHists(dfNtagSubSub[i][j], NtagHist::eOthVars, NtagCat::eMCN);
						fhNtag[i]->writeHists(dfNtagSubSub[i][j], NtagHist::eOthVars, NtagCat::eBKG);
					}
				}
			}
			else // for data
			{
				if( i==IntCat::N_INT_CAT )
				{ 
					st="NtagHist_data";
					dfNtag->cd();

					dfNtagSub[i]=(TDirectoryFile*)dfNtag->mkdir( st.c_str() );
					dfNtagSub[i]->cd();
					for(int j=0; j<Nntagsub; j++)
					{
						dfNtagSub[i]->cd();
						dfNtagSubSub[i][j]=(TDirectoryFile*)dfNtagSub[i]->mkdir( Sntagsub[j].c_str() );
						dfNtagSubSub[i][j]->cd();
						
						if( j==0 )
						{
							fhNtag[i]->writeHists(dfNtagSubSub[i][j], NtagHist::eInVarsPS, NtagCat::eALL);
						}
						else if( j==1 )
						{
							fhNtag[i]->writeHists(dfNtagSubSub[i][j], NtagHist::eInVarsNN, NtagCat::eALL);
						}
						else
						{
							fhNtag[i]->writeHists(dfNtagSubSub[i][j], NtagHist::eOthVars, NtagCat::eALL);
						}
					}
				}
			}
		}

	// Vertex distributions
	fout->cd();
	dfVtxDist=(TDirectoryFile*)fout->mkdir("VtxDist");
		for(int i=0; i<IntCat::N_INT_CAT+1; i++)
		{
			if( fCmdArg.fOscChan!=eDATA && 
				fCmdArg.fOscChan!=OscChan::eNONE )
			{
				if( i==IntCat::N_INT_CAT ){ st="VtxDst_all"; }
				else					  	{ st="VtxDst_" + IntCat::S_INT_CAT[i]; }
				dfVtxDist->cd();
				dfVtxDistSub[i]=(TDirectoryFile*)dfVtxDist->mkdir( st.c_str() );
				
					dfVtxDistSub[i]->cd();
					for(int j=0; j<VtxDist::N_VTX_DST; j++)
					{
							fhVtxDist[i]->getDstVis(j)->Write();
					}
					for(int j=0; j<VtxDist::N_VTX_DST; j++)
					{
						fhVtxDist[i]->getDstKS(j)->Write();
					}
			}
			else // for data
			{
				if( i==IntCat::N_INT_CAT )
				{	
					st="VtxDst_data";
					dfVtxDist->cd();
					dfVtxDistSub[i]=(TDirectoryFile*)dfVtxDist->mkdir( st.c_str() );
					
						dfVtxDistSub[i]->cd();
						fhVtxDist[i]->makeCDFsKS();
						for(int j=0; j<VtxDist::N_VTX_DST; j++)
						{
							fhVtxDist[i]->getDstVis(j)->Write();
						}
						for(int j=0; j<VtxDist::N_VTX_DST; j++)
						{
							fhVtxDist[i]->getDstKS(j)->Write();
						}
						for(int j=0; j<VtxDist::N_VTX_DST; j++)
						{
							fhVtxDist[i]->getCdfKS(j)->Write();
						}

				}
				else{ continue; }
			}
		}

	// MC truth distributions
	if( fCmdArg.fOscChan!=eDATA && 
		fCmdArg.fOscChan!=OscChan::eNONE )
	{
		fout->cd();
		dfMCTDist=(TDirectoryFile*)fout->mkdir("MCTDist");
		for(int i=0; i<IntCat::N_INT_CAT+1; i++)
		{
			if( i==IntCat::N_INT_CAT ){ st="MCTDst_all"; }
			else					  	{ st="MCTDst_" + IntCat::S_INT_CAT[i]; }
			dfMCTDist->cd();
			dfMCTDistSub[i]=(TDirectoryFile*)dfMCTDist->mkdir( st.c_str() );
			
				dfMCTDistSub[i]->cd();
				for(int j=0; j<MCTruth::N_MCT_DST; j++)
				{
					if( j!=MCTruth::eRecoTrMomTrueQ2 )
					{
						fhMCTDist[i]->getDst(j)->Write();
					}
					else
					{
						fhMCTDist[i]->getDst2D()->Write();
					}
				}
		}
	}


	// To close
	fout->cd();
	fout->Close();
}


void NominalDist::normalize()
{
	if( fCmdArg.fOscChan!=eDATA && 
		fCmdArg.fOscChan!=OscChan::eNONE )
	{
		double mcnorm=(double)fNumu->get10E21POTNorm();
		cout<<" [INFO] NominalDist::normalize "			 	<<endl;
		cout<<"   - Normalizing histograms to 10^21 POT " 	<<endl;
		cout<<"   - Using normalization factor :" << mcnorm <<endl;

		for(int i=0; i<IntCat::N_INT_CAT+1; i++)
		{
			fhEvselNuev[i]	->normalizeHists( mcnorm );
			fhExtra[i]		->normalizeHists( mcnorm );
			fhNtag[i]		->normalizeHists( mcnorm );
			fhVtxDist[i]	->normalizeDST( mcnorm );
			fhMCTDist[i]	->normalizeDST( mcnorm );
		}

		for(int i=0; i<IntCat::N_ICAT_NTAG+1; i++)
		{
			fhEvselNtag[i]->normalizeHists( mcnorm );
		}
	}
	else
	{
		cout<<" [INFO] NominalDist::normalize "			<<endl;
		cout<<"   - Dealing with data." 				<<endl;
		cout<<"   - No normalization applied" 			<<endl;
	}
}


VertexVar_t NominalDist::getVertexVar()
{
	VertexVar_t tvv;
	tvv.ntot_tag=0;
	tvv.nmcn_tag=0;
	tvv.nbkg_tag=0;

	double vtxNuev[3]={0.0};
	for(int j=0; j<3; j++){ vtxNuev[j]=fNumu->var<float>("fqpos",j); }
	double r2Nuev=vtxNuev[0]*vtxNuev[0] + vtxNuev[1]*vtxNuev[1];
	double dwlNuev=fNumu->var<float>("fqdwall");

	tvv.r2nuev	=r2Nuev;
	tvv.znuev	=vtxNuev[2];
	tvv.dwlnuev	=dwlNuev;
	
	for(int j=0; j<fNtag->ntot_ps(); j++)
	{
		if( fNtag->_istag[j]!=1 ){ continue; }	// Not tagged in NN

		double vtxNtag[3]={0.0};
		for(int k=0; k<3; k++){ vtxNtag[k]=fNtag->_nvtx[j][k]; }
		double r2Ntag=vtxNtag[0]*vtxNtag[0] + vtxNtag[1]*vtxNtag[1];
		double dwlNtag=fNtag->_ndwall[j];

		tvv.r2ntag[ tvv.ntot_tag ]	=r2Ntag;
		tvv.zntag[ tvv.ntot_tag ]	=vtxNtag[2];
		tvv.dwlntag[ tvv.ntot_tag ]	=dwlNtag;
		tvv.ntot_tag +=1;

		// Only for MC	
		if( fNtag->_mctruth_neutron[j]==1 )
		{
			tvv.r2ntag_mcn[ tvv.nmcn_tag ]	=r2Ntag;
			tvv.zntag_mcn[ tvv.nmcn_tag ]	=vtxNtag[2];
			tvv.dwlntag_mcn[ tvv.nmcn_tag ]	=dwlNtag;
			tvv.nmcn_tag +=1;
		}
		else
		{
			tvv.r2ntag_bkg[ tvv.nbkg_tag ]	=r2Ntag;
			tvv.zntag_bkg[ tvv.nbkg_tag ]	=vtxNtag[2];
			tvv.dwlntag_bkg[ tvv.nbkg_tag ]	=dwlNtag;
			tvv.nbkg_tag +=1;
		}
	}

	return tvv;
}

MCTruthVar_t NominalDist::getMCTruthVar()
{
	MCTruthVar_t tmv;	
	tmv.clear();

	int ip=-1;
	float ekin=0.0;
	float m=0.0;
	float p=0.0;
	
	float mass=0.0;
	int out=2;
	int amode=TMath::Abs( fNumu->var<int>("mode") );
	int anupdg=TMath::Abs( fNumu->var<int>("ipnu", 0) );

	if ( amode==2 ){ out=3; }

	if ( amode<30 )
	{
		if ( anupdg==Const::PDG_NUMU )		{ mass=Const::Mmu/1000.0; }
		else if ( anupdg==Const::PDG_NUE )	{ mass=Const::Me/1000.0; }
		else
		{
			cout<<" [ERROR] NominalDist::getMCTruthVar" <<endl;
			cout<<"  - ipnu[0]:"<< fNumu->var<int>("ipnu", 0) <<" is not supported." <<endl;
			cout<<"  -> EXIT" <<endl;
			exit(-1);
		}
	}

	float mass2	=mass*mass;
	float Pin	=fNumu->var<float>("pnu", 0);
	float Pout	=fNumu->var<float>("pnu", out);
	float Eout	=TMath::Sqrt( Pout*Pout + mass2 );
	float cosa=0.0;
	for(int i=0; i<3; i++)
	{
		cosa+=fNumu->var<float>("dirnu", 0, i)*fNumu->var<float>("dirnu", out, i); 
	}
	float Q2=2.*Pin*(Eout - Pout*cosa) - mass2;

	for(int i=0; i<fNumu->var<int>("Npvc"); i++)
	{
		if( fNumu->var<int>("Ichvc",i)!=1 ){ continue; }
		ip	=fNumu->var<int>("Ipvc", i);
		p	=fNumu->var<float>("Abspvc",i);
		m	=tmv.getMass(ip);
		ekin=TMath::Sqrt(p*p + m*m) - m;
		if( ekin>0.0 )
		{
			tmv.addPostFSIHadron(ip, ekin);
		}
	}
	tmv.NneuFSISI=fNtag->nmcn_tot();
	for(int i=0; i<fNtag->nmcn_tot(); i++)
	{
		tmv.npdistFSISI[i]=fNtag->npdist_mctTot(i);
	}

	tmv.recotrmom=fNumu->var<float>("momtr")/1.0e3;	// MeV->GeV
	tmv.etrue	 =fNumu->var<float>("pnu", 0);
	tmv.Q2true	 =Q2;
	return tmv;
}

void NominalDist::initiToyTagging()
{
	// Nominal values taken from 
	//     - ~/disk2/t2k/neutron/nsivar/anal/outputs/nominal/?hc.fq1rnumu.nominal.root
	//
	// Time variation corrected values taken from
	//     -  ~/disk2/t2k/neutron/tvar_fnnn/anal/out/fitntagtvar/fitntagtvar.Run1_9.normal.root
	
	fToyTag=new ToyTagging( fCmdArg.fRandSeed );
	if( fCmdArg.fBeamMode==BeamMode::eFHC )
	{
		// Nominal Sig. efficiency : 1.98917212503602808e-01
		// Tvar corrected 		   : 2.00870183601022934e-01
		fToyTag->setSignalEfficiency( 2.00870183601022934e-01 );

		// Nominal Bkg. rate
		//  -- Bkg. tagging efficiency from PS 
		//  -- 2.09887338792166117e-02/3.54562641002242040e+00 = 5.91961234829698011e-03
		// 
		// Tvar corrected bkg. rate (after NN)
		// -- 2.01839269593416214e-02
		// -- 2.01839269593416214e-02/3.54562641002242040e+00 = 5.69262652779427801e-03 
		fToyTag->setBackgroundEfficiency( 5.69262652779427801e-03 );
	}
	else
	{
		// Nominal Sig. efficiency : 2.04032407013022943e-01
		// Tvar corrected 		   : 2.03711708254085605e-01 
		fToyTag->setSignalEfficiency( 2.03711708254085605e-01 );

		// Nominal Bkg. rate
		// -- Bkg. tagging efficiency from PS 
		// -- 1.98596289492870316e-02/3.50877125705993809e+00
		//
		// Tvar corrected bkg. rate (after NN)
		// -- 1.93755388489533290e-02
		// -- 1.93755388489533290e-02/3.50877125705993809e+00 = 5.65999533578252344e-03
		fToyTag->setBackgroundEfficiency( 5.65999533578252344e-03 );
	}

	// Weight to account for SK time variation
	fWTvarSig=1.0;
	fWTvarBkg=1.0;
	fWTvarSig=TvarCor::WgtSigTvar[fCmdArg.fBeamMode];
	fWTvarBkg=TvarCor::WgtBkgTvar[fCmdArg.fBeamMode];
}
