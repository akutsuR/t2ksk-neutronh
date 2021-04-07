#include "mrgExtraCC0PiNumuBrkDwn.h"

int main(int argc, char** argv)
{
	bool isFHC		=atoi( argv[1] );
	fInputDir		=string( argv[2] );
	fOutFileName	=string( argv[3] );
	fDstName		=string( argv[4] );
	if( argc==6 )
	{
		fIsAltMC=atoi( argv[5] );
		if( fIsAltMC )
		{
			cout<<" [INFO] input MC files are for alternative MC rather that NEUT" <<endl;
		}
	}

	//if( argc==5 && atoi( argv[4] )==1 )
	//{
	//	cout<<" Will load MC input files with tvar correction" <<endl;
	//	fIsNominal=false;
	//}

	initialize();
	loadInputs(isFHC);
	copyInputs(isFHC);
	normalizeByPOT(isFHC);
	makeOutputs();
	writeOutputs();
	cout<<" FINISHED " <<endl;
return 0;
}


void initialize()
{
	// Initialize ouputs
	//////////////////////////////////////////////////////
	string spfx		="";
	string sp_inps	="";
	string sp_innn	="";
	string sp_oth	="";
	for(int i=0; i<N_BKDN_COMP+1; i++)
	{
		if( i==N_BKDN_COMP ){ spfx="_cc0pinumu"; }
		else				{ spfx="_" + S_BKDN_COMP[i]; }
		fExtra[i]=new CC0PiNumuExtraHists(spfx);
		fExtra[i]->initializeHists();

		sp_inps	="ps_" + spfx;	
		sp_innn	="nn_" + spfx;	
		sp_oth	=spfx;	
		fNtag[i]=new NtagHistManager();
		fNtag[i]->setInputVarHistsPostFixPS(sp_inps);
		fNtag[i]->setInputVarHistsPostFixNN(sp_innn);
		fNtag[i]->setOtherVarHistsPostFix(sp_oth);
		fNtag[i]->setCoarserBinningOthVars(true);
		//fNtag[i]->setCoarserBinning(true);
		fNtag[i]->initialize();

		if( i==N_BKDN_COMP ){ spfx="cc0pinumu"; }
		else				{ spfx=S_BKDN_COMP[i]; }
		fVtx[i]=new VertexDistributions(true, spfx );
		fMCT[i]=new MCTruthDistributions(spfx );
	}
}


void loadInputs(bool isFHC)
{
	loadExtraHists(isFHC);
	loadNtagHists(isFHC);
	loadVertexHists(isFHC);
	loadMCTruthHists(isFHC);
}

void loadExtraHists(bool isFHC)
{
	// Load inputs
	//////////////////////////////////////////////////////
	string sm="";
	string sf="";
	string so="";
	if( isFHC ){ sm="fhc"; }
	else	   { sm="rhc"; }
	//string sdir="/disk02/usr6/rakutsu/t2k/ncount/out/nominal";
	string sdir=fInputDir;
	TDirectoryFile *df_1=NULL,
				   *df_2=NULL;	// Extra Hists
	TFile *f=NULL;
	CC0PiNumuExtraHists *esh=NULL;
	for(int i=0; i<N_OSC_CHAN; i++)
	{
		if( fIsAltMC && i!=eNUMU && i!=eNUMUBAR )
		{
			cout<<" [INFO] Input is alternative MC" <<endl;
			cout<<"   - Skipping " << S_OSC_CHAN[i] <<endl;
			continue;
		}

		so=S_OSC_CHAN_FULL[i];
		sf=fInputDir + "/" + sm + "." + so + "." + fDstName + ".root";
		//sf=fInputDir + "/" + sm + "." + so + ".nominal.root";
		//if( !fIsNominal ){ sf=fInputDir + "/" + sm + "." + so + ".tvarcor.root"; }
		f=TFile::Open(sf.c_str());
		f->cd();

			// CC0pi numu hists
			df_1=(TDirectoryFile*)f->Get("Extra");
			for(int j=0; j<N_INT_CAT; j++)
			{
				enum E_BKDN_COMP ebc=getCC0PiNumuBrkDwn(i, j);
				cout<<" "   << S_OSC_CHAN[i]
					<<" - " << S_INT_CAT[j]
					<<" - " << S_BKDN_COMP[ebc]
					<<endl;

				df_1->cd();
				string sdn="";

				//if( i==N_INT_CAT ){ sdn="ExHist_all";	}
				if( j==N_INT_CAT ){ sdn="ExHist_all";	}
				else			  { sdn="ExHist_" + S_INT_CAT[j]; }
				df_2=(TDirectoryFile*)df_1->Get( sdn.c_str() );
				df_2->cd();

				esh=new CC0PiNumuExtraHists();
				esh->loadHists(df_2);
				*fExtra[ebc]+=*esh;

				delete esh;		esh=NULL;	
			df_1->cd();
			delete df_2;	df_2=NULL;
			}
			f->cd();
			delete df_1;	df_1=NULL;

		f->Close();
		delete f;		f=NULL;
	}
}

void loadNtagHists(bool isFHC)
{
	const int Nntagsub=3;
	const string Sntagsub[ Nntagsub ]=
					{ "NtagInputVarsPS",
					  "NtagInputVarsNN",
					  "NtagOtherVars"
					};
	// Load inputs
	//////////////////////////////////////////////////////
	string sm="";
	string sf="";
	string so="";
	if( isFHC ){ sm="fhc"; }
	else	   { sm="rhc"; }
	//string sdir="/disk02/usr6/rakutsu/t2k/ncount/out/nominal";
	string sdir=fInputDir;
	TDirectoryFile *df_1=NULL,
				   *df_2=NULL,
				   *df_3=NULL;
	TFile *f=NULL;
	NtagHistManager		*nhm=NULL;
	string st="";
	for(int i=0; i<N_OSC_CHAN; i++)
	{
		if( fIsAltMC && i!=eNUMU && i!=eNUMUBAR )
		{
			cout<<" [INFO] Input is alternative MC" <<endl;
			cout<<"   - Skipping " << S_OSC_CHAN[i] <<endl;
			continue;
		}
		so=S_OSC_CHAN_FULL[i];
		sf=fInputDir + "/" + sm + "." + so + "." + fDstName + ".root";
		//sf=fInputDir + "/" + sm + "." + so + ".nominal.root";
		//if( !fIsNominal ){ sf=fInputDir + "/" + sm + "." + so + ".tvarcor.root"; }

		f=TFile::Open(sf.c_str());
		f->cd();

			// CC0pi numu hists
			df_1=(TDirectoryFile*)f->Get("Ntag");
			for(int j=0; j<N_INT_CAT; j++)
			{
				enum E_BKDN_COMP ebc=getCC0PiNumuBrkDwn(i, j);
				df_1->cd();
				string sdn="";

				if( j==IntCat::N_INT_CAT ){ sdn="NtagHist_all"; }
				else					  { sdn="NtagHist_" + IntCat::S_INT_CAT[j]; }

				df_2=(TDirectoryFile*)df_1->Get( sdn.c_str() );
				df_2->cd();

				nhm=new NtagHistManager();
				for(int k=0; k<Nntagsub; k++)
				{
					df_2->cd();
					df_3=(TDirectoryFile*)df_2->Get( Sntagsub[k].c_str() );
					df_3->cd();
					if( k==NtagHist::eInVarsPS )
					{ 
						nhm->loadHists(NtagHist::eInVarsPS, df_3);
					}
					else if( k==NtagHist::eInVarsNN )
					{ 
						nhm->loadHists(NtagHist::eInVarsNN, df_3);
					}
					else
					{ 
						nhm->loadHists(NtagHist::eOthVars, df_3);
					}
					df_2->cd();
					delete df_3; df_3=NULL;
				}
				*fNtag[ebc]+=*nhm;
				delete nhm;

			df_1->cd();
			delete df_2;	df_2=NULL;
			}
			f->cd();
			delete df_1;	df_1=NULL;

		f->Close();
		delete f;		f=NULL;
	}
}

void loadVertexHists(bool isFHC)
{
	// Load inputs
	//////////////////////////////////////////////////////
	string sm="";
	string sf="";
	string so="";
	if( isFHC ){ sm="fhc"; }
	else	   { sm="rhc"; }
	//string sdir="/disk02/usr6/rakutsu/t2k/ncount/out/nominal";
	string sdir=fInputDir;
	TDirectoryFile *df_1=NULL,
				   *df_2=NULL;	// Extra Hists
	TFile *f=NULL;
	VertexDistributions *vtx=NULL;
	for(int i=0; i<N_OSC_CHAN; i++)
	{
		if( fIsAltMC && i!=eNUMU && i!=eNUMUBAR )
		{
			cout<<" [INFO] Input is alternative MC" <<endl;
			cout<<"   - Skipping " << S_OSC_CHAN[i] <<endl;
			continue;
		}
		so=S_OSC_CHAN_FULL[i];
		sf=fInputDir + "/" + sm + "." + so + "." + fDstName + ".root";

		//sf=fInputDir + "/" + sm + "." + so + ".nominal.root";
		//if( !fIsNominal ){ sf=fInputDir + "/" + sm + "." + so + ".tvarcor.root"; }
		f=TFile::Open(sf.c_str());
		f->cd();

			// CC0pi numu hists
			df_1=(TDirectoryFile*)f->Get("VtxDist");
			for(int j=0; j<N_INT_CAT; j++)
			{
				enum E_BKDN_COMP ebc=getCC0PiNumuBrkDwn(i, j);
				cout<<" "   << S_OSC_CHAN[i]
					<<" - " << S_INT_CAT[j]
					<<" - " << S_BKDN_COMP[ebc]
					<<endl;

				df_1->cd();
				string sdn="";

				//if( i==N_INT_CAT ){ sdn="ExHist_all";	}
				if( j==N_INT_CAT ){ sdn="VtxDst_all";	}
				else			  { sdn="VtxDst_" + S_INT_CAT[j]; }
				df_2=(TDirectoryFile*)df_1->Get( sdn.c_str() );
				df_2->cd();

				vtx=new VertexDistributions(true);
				vtx->loadDST(df_2);
				fVtx[ebc]->addDST( vtx );

				delete vtx;		vtx=NULL;	
			df_1->cd();
			delete df_2;	df_2=NULL;
			}
			f->cd();
			delete df_1;	df_1=NULL;

		f->Close();
		delete f;		f=NULL;
	}
}


void loadMCTruthHists(bool isFHC)
{
	// Load inputs
	//////////////////////////////////////////////////////
	string sm="";
	string sf="";
	string so="";
	if( isFHC ){ sm="fhc"; }
	else	   { sm="rhc"; }
	string sdir=fInputDir;
	TDirectoryFile *df_1=NULL,
				   *df_2=NULL;	// Extra Hists
	TFile *f=NULL;
	MCTruthDistributions *mct=NULL;
	for(int i=0; i<N_OSC_CHAN; i++)
	{
		if( fIsAltMC && i!=eNUMU && i!=eNUMUBAR )
		{
			cout<<" [INFO] Input is alternative MC" <<endl;
			cout<<"   - Skipping " << S_OSC_CHAN[i] <<endl;
			continue;
		}
		so=S_OSC_CHAN_FULL[i];
		sf=fInputDir + "/" + sm + "." + so + "." + fDstName + ".root";

		f=TFile::Open(sf.c_str());
		f->cd();

			// CC0pi numu hists
			df_1=(TDirectoryFile*)f->Get("MCTDist");
			for(int j=0; j<N_INT_CAT; j++)
			{
				enum E_BKDN_COMP ebc=getCC0PiNumuBrkDwn(i, j);
				cout<<" "   << S_OSC_CHAN[i]
					<<" - " << S_INT_CAT[j]
					<<" - " << S_BKDN_COMP[ebc]
					<<endl;

				df_1->cd();
				string sdn="";

				if( j==N_INT_CAT ){ sdn="MCTDst_all";	}
				else			  { sdn="MCTDst_" + S_INT_CAT[j]; }
				df_2=(TDirectoryFile*)df_1->Get( sdn.c_str() );
				df_2->cd();

				mct=new MCTruthDistributions();
				mct->loadDST(df_2);
				fMCT[ebc]->addDST( mct );

				delete mct;		mct=NULL;	
			df_1->cd();
			delete df_2;	df_2=NULL;
			}
			f->cd();
			delete df_1;	df_1=NULL;

		f->Close();
		delete f;		f=NULL;
	}
}


void copyInputs(bool isFHC)
{
// Copy inputs into output file
	string sm	="",
		   sf	="",
		   so	="";

	if( isFHC ){ sm="fhc"; }
	else	   { sm="rhc"; }

	//string sdir	="/disk02/usr6/rakutsu/t2k/ncount/out/nominal";
	//fOutFileName=sm + ".mrgExtraCC0PiNumuBrkDwn_out.root";

	TFile *fout=new TFile(fOutFileName.c_str(), "recreate");
	fout->cd();
	for(int i=0; i<N_OSC_CHAN; i++)
	{
		if( fIsAltMC && i!=eNUMU && i!=eNUMUBAR )
		{
			cout<<" [INFO] Input is alternative MC" <<endl;
			cout<<"   - Skipping " << S_OSC_CHAN[i] <<endl;
			continue;
		}
		so=S_OSC_CHAN_FULL[i];
		sf=fInputDir + "/" + sm + "." + so + "." + fDstName + ".root";
		//sf=fInputDir + "/" + sm + "." + so + ".nominal.root";
		//if( !fIsNominal ){ sf=fInputDir + "/" + sm + "." + so + ".tvarcor.root"; }
		CopyFile(sf.c_str(), S_OSC_CHAN[i].c_str());		
	}
	fout->cd();
	fout->Close();
	delete fout;
}


void normalizeByPOT(bool isFHC)
{
// Normalize by POT and then compute total expectaions 
// (i.e. sum of all MCs)
	double pot=Run1_9POT[0];
	if( !isFHC ){ pot=Run1_9POT[1]; }
	for(int i=0; i<N_BKDN_COMP; i++)
	{
		fExtra[i]	->normalizeHists( pot );
		fNtag[i]	->normalizeHists( pot );	
		fVtx[i]		->normalizeDST( pot );
		fMCT[i]		->normalizeDST( pot );

		fExtra[i]->setHistsColor( color[i] );
		*fExtra[N_BKDN_COMP]+=*fExtra[i];	
		*fNtag[N_BKDN_COMP] +=*fNtag[i];	
		fVtx[N_BKDN_COMP]	->addDST( fVtx[i] );
		fMCT[N_BKDN_COMP]	->addDST( fMCT[i] );
	}
}


void makeOutputs()
{
	makeLepMom();
	makeTrMom();
	makeRecoEnu();
	makeRecoQ2();
	makeCosBm();

	makefQDWall();
	makefQVtxR2();
	makefQVtxZ();

	makeTaggedNMulti();
	makeRecoNPDist();
	makeRecoNPDistLong();
	makeRecoNPDistTran();
	makeRecoCosNangActual();
	makeRecoCosNangInferred();
	makeRecoTDiff();
	makeLegend();
}

void makeLepMom()
{
	int eCC0PiNumu=N_BKDN_COMP;

	// Combine all bkg. into one
	fhLepMomNbkgTot=new TH1D();
	for(int i=0; i<N_BKDN_COMP; i++)
	{
		if( i==0 )
		{ 
			fhLepMomNbkgTot=(TH1D*)fExtra[i]->getHist(eLepMomNbkgTag)->Clone("hLepMomNbkgTot");
		}
		else
		{ 
			fhLepMomNbkgTot->Add( (TH1D*)fExtra[i]->getHist(eLepMomNbkgTag)->Clone() );
		}
	}
	fhLepMomNbkgTot->SetFillColor( color[ CC0PiNumuBrkDwn::eACCBKG ] );

	// Mean ** TOTAL ** n multiplicity as a function of rec. muon Pt
	fhLepMomAveTotMCN=(TH1D*)fExtra[eCC0PiNumu]->getHist(eLepMomNmcnTot)->Clone("hLepMomAveTotMCN");
	fhLepMomAveTotMCN->Divide( (TH1D*)fExtra[eCC0PiNumu]->getHist(eLepMomNuEvts)->Clone() );

	// Mean ** TAG ** n multiplicity as a function of rec. muon Pt (true n ONLY)
	fhLepMomAveTagMCN=(TH1D*)fExtra[eCC0PiNumu]->getHist(eLepMomNmcnTag)->Clone("hLepMomAveTagMCN");
	fhLepMomAveTagMCN->Divide( (TH1D*)fExtra[eCC0PiNumu]->getHist(eLepMomNuEvts)->Clone() );

	// Mean ** TAG ** n multiplicity as a function of rec. muon Pt (true n + bkg.)
	fhLepMomAveTagALL=(TH1D*)fExtra[eCC0PiNumu]->getHist(eLepMomNmcnTag)->Clone("hLepMomAveTagALL");
	fhLepMomAveTagALL->Add( (TH1D*)fhLepMomNbkgTot->Clone() );
	fhLepMomAveTagALL->Divide( (TH1D*)fExtra[eCC0PiNumu]->getHist(eLepMomNuEvts)->Clone() );

	// Stack hist for # nuevts, # total n, and # tagged n
	fhsLepMomNuEvts	=new THStack("hsLepMomNuEvts", "");
	fhsLepMomTotMCN	=new THStack("hsLepMomTotMCN", "");
	fhsLepMomTagALL	=new THStack("hsLepMomTagALL", "");

	fhsLepMomTagALL->Add( (TH1D*)fhLepMomNbkgTot->Clone() );
	for(int i=N_BKDN_COMP-1; i>=0; i--)
	{
		fhsLepMomNuEvts->Add( (TH1D*)fExtra[i]->getHist(eLepMomNuEvts)->Clone() );
		fhsLepMomTotMCN->Add( (TH1D*)fExtra[i]->getHist(eLepMomNmcnTot)->Clone() );
		fhsLepMomTagALL->Add( (TH1D*)fExtra[i]->getHist(eLepMomNmcnTag)->Clone() );
	}
}


void makeTrMom()
{
	int eCC0PiNumu=N_BKDN_COMP;

	// Combine all bkg. into one
	fhTrMomNbkgTot=new TH1D();
	for(int i=0; i<N_BKDN_COMP; i++)
	{
		if( i==0 )
		{ 
			fhTrMomNbkgTot=(TH1D*)fExtra[i]->getHist(eTrMomNbkgTag)->Clone("hTrMomNbkgTot");
		}
		else
		{ 
			fhTrMomNbkgTot->Add( (TH1D*)fExtra[i]->getHist(eTrMomNbkgTag)->Clone() );
		}
	}
	fhTrMomNbkgTot->SetFillColor( color[ CC0PiNumuBrkDwn::eACCBKG ] );

	// Mean ** TOTAL ** n multiplicity as a function of rec. muon Pt
	fhTrMomAveTotMCN=(TH1D*)fExtra[eCC0PiNumu]->getHist(eTrMomNmcnTot)->Clone("hTrMomAveTotMCN");
	fhTrMomAveTotMCN->Divide( (TH1D*)fExtra[eCC0PiNumu]->getHist(eTrMomNuEvts)->Clone() );

	// Mean ** TAG ** n multiplicity as a function of rec. muon Pt (true n ONLY)
	fhTrMomAveTagMCN=(TH1D*)fExtra[eCC0PiNumu]->getHist(eTrMomNmcnTag)->Clone("hTrMomAveTagMCN");
	fhTrMomAveTagMCN->Divide( (TH1D*)fExtra[eCC0PiNumu]->getHist(eTrMomNuEvts)->Clone() );

	// Mean ** TAG ** n multiplicity as a function of rec. muon Pt (true n + bkg.)
	fhTrMomAveTagALL=(TH1D*)fExtra[eCC0PiNumu]->getHist(eTrMomNmcnTag)->Clone("hTrMomAveTagALL");
	fhTrMomAveTagALL->Add( (TH1D*)fhTrMomNbkgTot->Clone() );
	fhTrMomAveTagALL->Divide( (TH1D*)fExtra[eCC0PiNumu]->getHist(eTrMomNuEvts)->Clone() );

	// Stack hist for # nuevts, # total n, and # tagged n
	fhsTrMomNuEvts	=new THStack("hsTrMomNuEvts", "");
	fhsTrMomTotMCN	=new THStack("hsTrMomTotMCN", "");
	fhsTrMomTagALL	=new THStack("hsTrMomTagALL", "");

	fhsTrMomTagALL->Add( (TH1D*)fhTrMomNbkgTot->Clone() );
	for(int i=N_BKDN_COMP-1; i>=0; i--)
	{
		fhsTrMomNuEvts->Add( (TH1D*)fExtra[i]->getHist(eTrMomNuEvts)->Clone() );
		fhsTrMomTotMCN->Add( (TH1D*)fExtra[i]->getHist(eTrMomNmcnTot)->Clone() );
		fhsTrMomTagALL->Add( (TH1D*)fExtra[i]->getHist(eTrMomNmcnTag)->Clone() );
	}
}

void makeRecoEnu()
{
	int eCC0PiNumu=N_BKDN_COMP;

	// Combine all bkg. into one
	fhRecoEnuNbkgTot=new TH1D();
	for(int i=0; i<N_BKDN_COMP; i++)
	{
		if( i==0 )
		{ 
			fhRecoEnuNbkgTot=(TH1D*)fExtra[i]->getHist(eRecoEnuNbkgTag)->Clone("hRecoEnuNbkgTot");
		}
		else
		{ 
			fhRecoEnuNbkgTot->Add( (TH1D*)fExtra[i]->getHist(eRecoEnuNbkgTag)->Clone() );
		}
	}
	fhRecoEnuNbkgTot->SetFillColor( color[ CC0PiNumuBrkDwn::eACCBKG ] );

	// Mean ** TOTAL ** n multiplicity as a function of rec. muon Pt
	fhRecoEnuAveTotMCN=(TH1D*)fExtra[eCC0PiNumu]->getHist(eRecoEnuNmcnTot)->Clone("hRecoEnuAveTotMCN");
	fhRecoEnuAveTotMCN->Divide( (TH1D*)fExtra[eCC0PiNumu]->getHist(eRecoEnuNuEvts)->Clone() );

	// Mean ** TAG ** n multiplicity as a function of rec. muon Pt (true n ONLY)
	fhRecoEnuAveTagMCN=(TH1D*)fExtra[eCC0PiNumu]->getHist(eRecoEnuNmcnTag)->Clone("hRecoEnuAveTagMCN");
	fhRecoEnuAveTagMCN->Divide( (TH1D*)fExtra[eCC0PiNumu]->getHist(eRecoEnuNuEvts)->Clone() );

	// Mean ** TAG ** n multiplicity as a function of rec. muon Pt (true n + bkg.)
	fhRecoEnuAveTagALL=(TH1D*)fExtra[eCC0PiNumu]->getHist(eRecoEnuNmcnTag)->Clone("hRecoEnuAveTagALL");
	fhRecoEnuAveTagALL->Add( (TH1D*)fhRecoEnuNbkgTot->Clone() );
	fhRecoEnuAveTagALL->Divide( (TH1D*)fExtra[eCC0PiNumu]->getHist(eRecoEnuNuEvts)->Clone() );

	// Stack hist for # nuevts, # total n, and # tagged n
	fhsRecoEnuNuEvts	=new THStack("hsRecoEnuNuEvts", "");
	fhsRecoEnuTotMCN	=new THStack("hsRecoEnuTotMCN", "");
	fhsRecoEnuTagALL	=new THStack("hsRecoEnuTagALL", "");

	fhsRecoEnuTagALL->Add( (TH1D*)fhRecoEnuNbkgTot->Clone() );
	for(int i=N_BKDN_COMP-1; i>=0; i--)
	{
		fhsRecoEnuNuEvts->Add( (TH1D*)fExtra[i]->getHist(eRecoEnuNuEvts)->Clone() );
		fhsRecoEnuTotMCN->Add( (TH1D*)fExtra[i]->getHist(eRecoEnuNmcnTot)->Clone() );
		fhsRecoEnuTagALL->Add( (TH1D*)fExtra[i]->getHist(eRecoEnuNmcnTag)->Clone() );
	}
}

void makeRecoQ2()
{
	int eCC0PiNumu=N_BKDN_COMP;

	// Combine all bkg. into one
	fhRecoQ2NbkgTot=new TH1D();
	for(int i=0; i<N_BKDN_COMP; i++)
	{
		if( i==0 )
		{ 
			fhRecoQ2NbkgTot=(TH1D*)fExtra[i]->getHist(eRecoQ2NbkgTag)->Clone("hRecoQ2NbkgTot");
		}
		else
		{ 
			fhRecoQ2NbkgTot->Add( (TH1D*)fExtra[i]->getHist(eRecoQ2NbkgTag)->Clone() );
		}
	}
	fhRecoQ2NbkgTot->SetFillColor( color[ CC0PiNumuBrkDwn::eACCBKG ] );

	// Mean ** TOTAL ** n multiplicity as a function of rec. muon Pt
	fhRecoQ2AveTotMCN=(TH1D*)fExtra[eCC0PiNumu]->getHist(eRecoQ2NmcnTot)->Clone("hRecoQ2AveTotMCN");
	fhRecoQ2AveTotMCN->Divide( (TH1D*)fExtra[eCC0PiNumu]->getHist(eRecoQ2NuEvts)->Clone() );

	// Mean ** TAG ** n multiplicity as a function of rec. muon Pt (true n ONLY)
	fhRecoQ2AveTagMCN=(TH1D*)fExtra[eCC0PiNumu]->getHist(eRecoQ2NmcnTag)->Clone("hRecoQ2AveTagMCN");
	fhRecoQ2AveTagMCN->Divide( (TH1D*)fExtra[eCC0PiNumu]->getHist(eRecoQ2NuEvts)->Clone() );

	// Mean ** TAG ** n multiplicity as a function of rec. muon Pt (true n + bkg.)
	fhRecoQ2AveTagALL=(TH1D*)fExtra[eCC0PiNumu]->getHist(eRecoQ2NmcnTag)->Clone("hRecoQ2AveTagALL");
	fhRecoQ2AveTagALL->Add( (TH1D*)fhRecoQ2NbkgTot->Clone() );
	fhRecoQ2AveTagALL->Divide( (TH1D*)fExtra[eCC0PiNumu]->getHist(eRecoQ2NuEvts)->Clone() );

	// Stack hist for # nuevts, # total n, and # tagged n
	fhsRecoQ2NuEvts	=new THStack("hsRecoQ2NuEvts", "");
	fhsRecoQ2TotMCN	=new THStack("hsRecoQ2TotMCN", "");
	fhsRecoQ2TagALL	=new THStack("hsRecoQ2TagALL", "");

	fhsRecoQ2TagALL->Add( (TH1D*)fhRecoQ2NbkgTot->Clone() );
	for(int i=N_BKDN_COMP-1; i>=0; i--)
	{
		fhsRecoQ2NuEvts->Add( (TH1D*)fExtra[i]->getHist(eRecoQ2NuEvts)->Clone() );
		fhsRecoQ2TotMCN->Add( (TH1D*)fExtra[i]->getHist(eRecoQ2NmcnTot)->Clone() );
		fhsRecoQ2TagALL->Add( (TH1D*)fExtra[i]->getHist(eRecoQ2NmcnTag)->Clone() );
	}
}


void makeCosBm()
{
	int eCC0PiNumu=N_BKDN_COMP;

	// Combine all bkg. into one
	fhCosBmNbkgTot=new TH1D();
	for(int i=0; i<N_BKDN_COMP; i++)
	{
		if( i==0 )
		{ 
			fhCosBmNbkgTot=(TH1D*)fExtra[i]->getHist(eCosBmNbkgTag)->Clone("hCosBmNbkgTot");
		}
		else
		{ 
			fhCosBmNbkgTot->Add( (TH1D*)fExtra[i]->getHist(eCosBmNbkgTag)->Clone() );
		}
	}
	fhCosBmNbkgTot->SetFillColor( color[ CC0PiNumuBrkDwn::eACCBKG ] );

	// Mean ** TOTAL ** n multiplicity as a function of rec. muon Pt
	fhCosBmAveTotMCN=(TH1D*)fExtra[eCC0PiNumu]->getHist(eCosBmNmcnTot)->Clone("hCosBmAveTotMCN");
	fhCosBmAveTotMCN->Divide( (TH1D*)fExtra[eCC0PiNumu]->getHist(eCosBmNuEvts)->Clone() );

	// Mean ** TAG ** n multiplicity as a function of rec. muon Pt (true n ONLY)
	fhCosBmAveTagMCN=(TH1D*)fExtra[eCC0PiNumu]->getHist(eCosBmNmcnTag)->Clone("hCosBmAveTagMCN");
	fhCosBmAveTagMCN->Divide( (TH1D*)fExtra[eCC0PiNumu]->getHist(eCosBmNuEvts)->Clone() );

	// Mean ** TAG ** n multiplicity as a function of rec. muon Pt (true n + bkg.)
	fhCosBmAveTagALL=(TH1D*)fExtra[eCC0PiNumu]->getHist(eCosBmNmcnTag)->Clone("hCosBmAveTagALL");
	fhCosBmAveTagALL->Add( (TH1D*)fhCosBmNbkgTot->Clone() );
	fhCosBmAveTagALL->Divide( (TH1D*)fExtra[eCC0PiNumu]->getHist(eCosBmNuEvts)->Clone() );

	// Stack hist for # nuevts, # total n, and # tagged n
	fhsCosBmNuEvts	=new THStack("hsCosBmNuEvts", "");
	fhsCosBmTotMCN	=new THStack("hsCosBmTotMCN", "");
	fhsCosBmTagALL	=new THStack("hsCosBmTagALL", "");

	fhsCosBmTagALL->Add( (TH1D*)fhCosBmNbkgTot->Clone() );
	for(int i=N_BKDN_COMP-1; i>=0; i--)
	{
		fhsCosBmNuEvts->Add( (TH1D*)fExtra[i]->getHist(eCosBmNuEvts)->Clone() );
		fhsCosBmTotMCN->Add( (TH1D*)fExtra[i]->getHist(eCosBmNmcnTot)->Clone() );
		fhsCosBmTagALL->Add( (TH1D*)fExtra[i]->getHist(eCosBmNmcnTag)->Clone() );
	}
}

void makefQDWall()
{
	int eCC0PiNumu=N_BKDN_COMP;

	// Combine all bkg. into one
	fhfQDWallNbkgTot=new TH1D();
	for(int i=0; i<N_BKDN_COMP; i++)
	{
		if( i==0 )
		{ 
			fhfQDWallNbkgTot=(TH1D*)fExtra[i]->getHist(efQDWallNbkgTag)->Clone("hfQDWallNbkgTot");
		}
		else
		{ 
			fhfQDWallNbkgTot->Add( (TH1D*)fExtra[i]->getHist(efQDWallNbkgTag)->Clone() );
		}
	}
	fhfQDWallNbkgTot->SetFillColor( color[ CC0PiNumuBrkDwn::eACCBKG ] );

	// Mean ** TOTAL ** n multiplicity as a function of rec. muon Pt
	fhfQDWallAveTotMCN=(TH1D*)fExtra[eCC0PiNumu]->getHist(efQDWallNmcnTot)->Clone("hfQDWallAveTotMCN");
	fhfQDWallAveTotMCN->Divide( (TH1D*)fExtra[eCC0PiNumu]->getHist(efQDWallNuEvts)->Clone() );

	// Mean ** TAG ** n multiplicity as a function of rec. muon Pt (true n ONLY)
	fhfQDWallAveTagMCN=(TH1D*)fExtra[eCC0PiNumu]->getHist(efQDWallNmcnTag)->Clone("hfQDWallAveTagMCN");
	fhfQDWallAveTagMCN->Divide( (TH1D*)fExtra[eCC0PiNumu]->getHist(efQDWallNuEvts)->Clone() );

	// Mean ** TAG ** n multiplicity as a function of rec. muon Pt (true n + bkg.)
	fhfQDWallAveTagALL=(TH1D*)fExtra[eCC0PiNumu]->getHist(efQDWallNmcnTag)->Clone("hfQDWallAveTagALL");
	fhfQDWallAveTagALL->Add( (TH1D*)fhfQDWallNbkgTot->Clone() );
	fhfQDWallAveTagALL->Divide( (TH1D*)fExtra[eCC0PiNumu]->getHist(efQDWallNuEvts)->Clone() );

	// Stack hist for # nuevts, # total n, and # tagged n
	fhsfQDWallNuEvts	=new THStack("hsfQDWallNuEvts", "");
	fhsfQDWallTotMCN	=new THStack("hsfQDWallTotMCN", "");
	fhsfQDWallTagALL	=new THStack("hsfQDWallTagALL", "");

	fhsfQDWallTagALL->Add( (TH1D*)fhfQDWallNbkgTot->Clone() );
	for(int i=N_BKDN_COMP-1; i>=0; i--)
	{
		fhsfQDWallNuEvts->Add( (TH1D*)fExtra[i]->getHist(efQDWallNuEvts)->Clone() );
		fhsfQDWallTotMCN->Add( (TH1D*)fExtra[i]->getHist(efQDWallNmcnTot)->Clone() );
		fhsfQDWallTagALL->Add( (TH1D*)fExtra[i]->getHist(efQDWallNmcnTag)->Clone() );
	}
}

void makefQVtxR2()
{
	int eCC0PiNumu=N_BKDN_COMP;

	// Combine all bkg. into one
	fhfQVtxR2NbkgTot=new TH1D();
	for(int i=0; i<N_BKDN_COMP; i++)
	{
		if( i==0 )
		{ 
			fhfQVtxR2NbkgTot=(TH1D*)fExtra[i]->getHist(efQVtxR2NbkgTag)->Clone("hfQVtxR2NbkgTot");
		}
		else
		{ 
			fhfQVtxR2NbkgTot->Add( (TH1D*)fExtra[i]->getHist(efQVtxR2NbkgTag)->Clone() );
		}
	}
	fhfQVtxR2NbkgTot->SetFillColor( color[ CC0PiNumuBrkDwn::eACCBKG ] );

	// Mean ** TOTAL ** n multiplicity as a function of rec. muon Pt
	fhfQVtxR2AveTotMCN=(TH1D*)fExtra[eCC0PiNumu]->getHist(efQVtxR2NmcnTot)->Clone("hfQVtxR2AveTotMCN");
	fhfQVtxR2AveTotMCN->Divide( (TH1D*)fExtra[eCC0PiNumu]->getHist(efQVtxR2NuEvts)->Clone() );

	// Mean ** TAG ** n multiplicity as a function of rec. muon Pt (true n ONLY)
	fhfQVtxR2AveTagMCN=(TH1D*)fExtra[eCC0PiNumu]->getHist(efQVtxR2NmcnTag)->Clone("hfQVtxR2AveTagMCN");
	fhfQVtxR2AveTagMCN->Divide( (TH1D*)fExtra[eCC0PiNumu]->getHist(efQVtxR2NuEvts)->Clone() );

	// Mean ** TAG ** n multiplicity as a function of rec. muon Pt (true n + bkg.)
	fhfQVtxR2AveTagALL=(TH1D*)fExtra[eCC0PiNumu]->getHist(efQVtxR2NmcnTag)->Clone("hfQVtxR2AveTagALL");
	fhfQVtxR2AveTagALL->Add( (TH1D*)fhfQVtxR2NbkgTot->Clone() );
	fhfQVtxR2AveTagALL->Divide( (TH1D*)fExtra[eCC0PiNumu]->getHist(efQVtxR2NuEvts)->Clone() );

	// Stack hist for # nuevts, # total n, and # tagged n
	fhsfQVtxR2NuEvts	=new THStack("hsfQVtxR2NuEvts", "");
	fhsfQVtxR2TotMCN	=new THStack("hsfQVtxR2TotMCN", "");
	fhsfQVtxR2TagALL	=new THStack("hsfQVtxR2TagALL", "");

	fhsfQVtxR2TagALL->Add( (TH1D*)fhfQVtxR2NbkgTot->Clone() );
	for(int i=N_BKDN_COMP-1; i>=0; i--)
	{
		fhsfQVtxR2NuEvts->Add( (TH1D*)fExtra[i]->getHist(efQVtxR2NuEvts)->Clone() );
		fhsfQVtxR2TotMCN->Add( (TH1D*)fExtra[i]->getHist(efQVtxR2NmcnTot)->Clone() );
		fhsfQVtxR2TagALL->Add( (TH1D*)fExtra[i]->getHist(efQVtxR2NmcnTag)->Clone() );
	}
}

void makefQVtxZ()
{
	int eCC0PiNumu=N_BKDN_COMP;

	// Combine all bkg. into one
	fhfQVtxZNbkgTot=new TH1D();
	for(int i=0; i<N_BKDN_COMP; i++)
	{
		if( i==0 )
		{ 
			fhfQVtxZNbkgTot=(TH1D*)fExtra[i]->getHist(efQVtxZNbkgTag)->Clone("hfQVtxZNbkgTot");
		}
		else
		{ 
			fhfQVtxZNbkgTot->Add( (TH1D*)fExtra[i]->getHist(efQVtxZNbkgTag)->Clone() );
		}
	}
	fhfQVtxZNbkgTot->SetFillColor( color[ CC0PiNumuBrkDwn::eACCBKG ] );

	// Mean ** TOTAL ** n multiplicity as a function of rec. muon Pt
	fhfQVtxZAveTotMCN=(TH1D*)fExtra[eCC0PiNumu]->getHist(efQVtxZNmcnTot)->Clone("hfQVtxZAveTotMCN");
	fhfQVtxZAveTotMCN->Divide( (TH1D*)fExtra[eCC0PiNumu]->getHist(efQVtxZNuEvts)->Clone() );

	// Mean ** TAG ** n multiplicity as a function of rec. muon Pt (true n ONLY)
	fhfQVtxZAveTagMCN=(TH1D*)fExtra[eCC0PiNumu]->getHist(efQVtxZNmcnTag)->Clone("hfQVtxZAveTagMCN");
	fhfQVtxZAveTagMCN->Divide( (TH1D*)fExtra[eCC0PiNumu]->getHist(efQVtxZNuEvts)->Clone() );

	// Mean ** TAG ** n multiplicity as a function of rec. muon Pt (true n + bkg.)
	fhfQVtxZAveTagALL=(TH1D*)fExtra[eCC0PiNumu]->getHist(efQVtxZNmcnTag)->Clone("hfQVtxZAveTagALL");
	fhfQVtxZAveTagALL->Add( (TH1D*)fhfQVtxZNbkgTot->Clone() );
	fhfQVtxZAveTagALL->Divide( (TH1D*)fExtra[eCC0PiNumu]->getHist(efQVtxZNuEvts)->Clone() );

	// Stack hist for # nuevts, # total n, and # tagged n
	fhsfQVtxZNuEvts	=new THStack("hsfQVtxZNuEvts", "");
	fhsfQVtxZTotMCN	=new THStack("hsfQVtxZTotMCN", "");
	fhsfQVtxZTagALL	=new THStack("hsfQVtxZTagALL", "");

	fhsfQVtxZTagALL->Add( (TH1D*)fhfQVtxZNbkgTot->Clone() );
	for(int i=N_BKDN_COMP-1; i>=0; i--)
	{
		fhsfQVtxZNuEvts->Add( (TH1D*)fExtra[i]->getHist(efQVtxZNuEvts)->Clone() );
		fhsfQVtxZTotMCN->Add( (TH1D*)fExtra[i]->getHist(efQVtxZNmcnTot)->Clone() );
		fhsfQVtxZTagALL->Add( (TH1D*)fExtra[i]->getHist(efQVtxZNmcnTag)->Clone() );
	}
}

void makeTaggedNMulti()
{
	// Stack hist for # tagged n vs rec. np distance
	fhsTaggedNMulti	=new THStack("hsTaggedNMulti", "");
	for(int i=N_BKDN_COMP-1; i>=0; i--)
	{
		fhsTaggedNMulti->Add( (TH1D*)fExtra[i]->getHist(eNuEvtsNumTagAllFull)->Clone() );
	}
}


void makeRecoNPDist()
{
	int eCC0PiNumu=N_BKDN_COMP;
	// Stack hist for # tagged n vs rec. np distance
	fhsRecoNPDistTagALL	=new THStack("hsRecoNPDistTagALL", "");

	TH1D *htmp=NULL;
	NtagHist::E_HIST_CAT		ehc=NtagHist::eOthVars;
	NtagCat::E_NTAG_CAT			enc=NtagCat::eBKG;
	NtagOtherVars::E_OTHER_VARS	eov=NtagOtherVars::enpdist_NN;

	// First add acc. bkg. tag and then add true n sequentially
	htmp=fNtag[eCC0PiNumu]->getHist(ehc, enc, eov);
	htmp->SetFillColor( color[CC0PiNumuBrkDwn::eACCBKG] );
	fhsRecoNPDistTagALL->Add( (TH1D*)htmp->Clone() );
	delete htmp;

	enc=NtagCat::eMCN;
	for(int i=N_BKDN_COMP-1; i>=0; i--)
	{
		htmp=fNtag[i]->getHist(ehc, enc, eov);
		htmp->SetFillColor( color[i] );
		fhsRecoNPDistTagALL->Add( (TH1D*)htmp->Clone() );
		delete htmp;
	}
}

void makeRecoNPDistLong()
{
	int eCC0PiNumu=N_BKDN_COMP;
	// Stack hist for # tagged n vs rec. np distance
	fhsRecoNPDistLongTagALL	=new THStack("hsRecoNPDistLongTagALL", "");

	TH1D *htmp=NULL;
	NtagHist::E_HIST_CAT		ehc=NtagHist::eOthVars;
	NtagCat::E_NTAG_CAT			enc=NtagCat::eBKG;
	NtagOtherVars::E_OTHER_VARS	eov=NtagOtherVars::eNPLong_NN;

	// First add acc. bkg. tag and then add true n sequentially
	htmp=fNtag[eCC0PiNumu]->getHist(ehc, enc, eov);
	htmp->SetFillColor( color[CC0PiNumuBrkDwn::eACCBKG] );
	fhsRecoNPDistLongTagALL->Add( (TH1D*)htmp->Clone() );
	delete htmp;

	enc=NtagCat::eMCN;
	for(int i=N_BKDN_COMP-1; i>=0; i--)
	{
		htmp=fNtag[i]->getHist(ehc, enc, eov);
		htmp->SetFillColor( color[i] );
		fhsRecoNPDistLongTagALL->Add( (TH1D*)htmp->Clone() );
		delete htmp;
	}
}

void makeRecoNPDistTran()
{
	int eCC0PiNumu=N_BKDN_COMP;
	// Stack hist for # tagged n vs rec. np distance
	fhsRecoNPDistTranTagALL	=new THStack("hsRecoNPDistTranTagALL", "");

	TH1D *htmp=NULL;
	NtagHist::E_HIST_CAT		ehc=NtagHist::eOthVars;
	NtagCat::E_NTAG_CAT			enc=NtagCat::eBKG;
	NtagOtherVars::E_OTHER_VARS	eov=NtagOtherVars::eNPTran_NN;

	// First add acc. bkg. tag and then add true n sequentially
	htmp=fNtag[eCC0PiNumu]->getHist(ehc, enc, eov);
	htmp->SetFillColor( color[CC0PiNumuBrkDwn::eACCBKG] );
	fhsRecoNPDistTranTagALL->Add( (TH1D*)htmp->Clone() );
	delete htmp;

	enc=NtagCat::eMCN;
	for(int i=N_BKDN_COMP-1; i>=0; i--)
	{
		htmp=fNtag[i]->getHist(ehc, enc, eov);
		htmp->SetFillColor( color[i] );
		fhsRecoNPDistTranTagALL->Add( (TH1D*)htmp->Clone() );
		delete htmp;
	}
}


void makeRecoCosNangActual()
{
	int eCC0PiNumu=N_BKDN_COMP;
	// Stack hist for # tagged n vs rec. np distance
	fhsRecoCosNangActTagALL	=new THStack("hsRecoCosNangActTagALL", "");

	TH1D *htmp=NULL;
	NtagHist::E_HIST_CAT		ehc=NtagHist::eOthVars;
	NtagCat::E_NTAG_CAT			enc=NtagCat::eBKG;
	NtagOtherVars::E_OTHER_VARS	eov=NtagOtherVars::enangAct_NN;

	// First add acc. bkg. tag and then add true n sequentially
	htmp=fNtag[eCC0PiNumu]->getHist(ehc, enc, eov);
	htmp->SetFillColor( color[CC0PiNumuBrkDwn::eACCBKG] );
	fhsRecoCosNangActTagALL->Add( (TH1D*)htmp->Clone() );
	delete htmp;

	enc=NtagCat::eMCN;
	for(int i=N_BKDN_COMP-1; i>=0; i--)
	{
		htmp=fNtag[i]->getHist(ehc, enc, eov);
		htmp->SetFillColor( color[i] );
		fhsRecoCosNangActTagALL->Add( (TH1D*)htmp->Clone() );
		delete htmp;
	}
}

void makeRecoCosNangInferred()
{
	int eCC0PiNumu=N_BKDN_COMP;
	// Stack hist for # tagged n vs rec. np distance
	fhsRecoCosNangInfTagALL	=new THStack("hsRecoCosNangInfTagALL", "");

	TH1D *htmp=NULL;
	NtagHist::E_HIST_CAT		ehc=NtagHist::eOthVars;
	NtagCat::E_NTAG_CAT			enc=NtagCat::eBKG;
	NtagOtherVars::E_OTHER_VARS	eov=NtagOtherVars::enangInf_NN;

	// First add acc. bkg. tag and then add true n sequentially
	htmp=fNtag[eCC0PiNumu]->getHist(ehc, enc, eov);
	htmp->SetFillColor( color[CC0PiNumuBrkDwn::eACCBKG] );
	fhsRecoCosNangInfTagALL->Add( (TH1D*)htmp->Clone() );
	delete htmp;

	enc=NtagCat::eMCN;
	for(int i=N_BKDN_COMP-1; i>=0; i--)
	{
		htmp=fNtag[i]->getHist(ehc, enc, eov);
		htmp->SetFillColor( color[i] );
		fhsRecoCosNangInfTagALL->Add( (TH1D*)htmp->Clone() );
		delete htmp;
	}
}


void makeRecoTDiff()
{
	int eCC0PiNumu=N_BKDN_COMP;
	// Stack hist for # tagged n vs rec. time difference (i.e. capture time)
	fhsRecoTDiffTagALL	=new THStack("hsRecoTDiffTagALL", "");

	TH1D *htmp=NULL;
	NtagHist::E_HIST_CAT		ehc=NtagHist::eOthVars;
	NtagCat::E_NTAG_CAT			enc=NtagCat::eBKG;
	NtagOtherVars::E_OTHER_VARS	eov=NtagOtherVars::et0_NN;

	// First add acc. bkg. tag and then add true n sequentially
	htmp=fNtag[eCC0PiNumu]->getHist(ehc, enc, eov);
	htmp->SetFillColor( color[CC0PiNumuBrkDwn::eACCBKG] );
	fhsRecoTDiffTagALL->Add( (TH1D*)htmp->Clone() );
	delete htmp;

	enc=NtagCat::eMCN;
	for(int i=N_BKDN_COMP-1; i>=0; i--)
	{
		htmp=fNtag[i]->getHist(ehc, enc, eov);
		htmp->SetFillColor( color[i] );
		fhsRecoTDiffTagALL->Add( (TH1D*)htmp->Clone() );
		delete htmp;
	}
}

void makeLegend()
{
	fLegRNumu=new TLegend(0.65, 0.65, 0.88, 0.89);
  	fLegRNumu->SetFillColor(0);
  	fLegRNumu->SetLineColor(0);
	fLegRNumu->SetName("legRNumu");

	fLegRNtag=new TLegend(0.65, 0.65, 0.88, 0.93);
  	fLegRNtag->SetFillColor(0);
  	fLegRNtag->SetLineColor(0);
	fLegRNtag->SetName("legRNtag");

	fLegLNumu=new TLegend(0.2, 0.65, 0.43, 0.89);
  	fLegLNumu->SetFillColor(0);
  	fLegLNumu->SetLineColor(0);
	fLegLNumu->SetName("legLNumu");

	fLegLNtag=new TLegend(0.2, 0.65, 0.43, 0.93);
  	fLegLNtag->SetFillColor(0);
  	fLegLNtag->SetLineColor(0);
	fLegLNtag->SetName("legLNtag");


	for(int i=0; i<N_BKDN_COMP; i++)
	{
		TH1D *h=(TH1D*)fExtra[i]->getHist(eTrMomNuEvts)->Clone();
		fLegRNumu->AddEntry(h, S_BKDN_COMP_LEGE[i].c_str(), "f");
		fLegRNtag->AddEntry(h, S_BKDN_COMP_LEGE[i].c_str(), "f");
		fLegLNumu->AddEntry(h, S_BKDN_COMP_LEGE[i].c_str(), "f");
		fLegLNtag->AddEntry(h, S_BKDN_COMP_LEGE[i].c_str(), "f");
	}
	TH1D *h0=(TH1D*)fhTrMomNbkgTot->Clone();
	fLegRNtag->AddEntry(h0, S_BKDN_COMP_LEGE[CC0PiNumuBrkDwn::eACCBKG].c_str(), "f");
	fLegLNtag->AddEntry(h0, S_BKDN_COMP_LEGE[CC0PiNumuBrkDwn::eACCBKG].c_str(), "f");
}

///////////////////////////////////////////////////////////////////////
void writeOutputs()
{
// Write outputs	

	const int Nntagsub=3;
	const string Sntagsub[ Nntagsub ]=
					{ "NtagInputVarsPS",
					  "NtagInputVarsNN",
					  "NtagOtherVars"
					};

	string st="";
	TDirectoryFile *dfCC0PiNumu	=NULL;
	TDirectoryFile *dfExtra		=NULL;
	TDirectoryFile *dfExtraSub[N_BKDN_COMP+1];
	TDirectoryFile *dfNtag		=NULL;
	TDirectoryFile *dfNtagSub[N_BKDN_COMP+1];
	TDirectoryFile *dfNtagSubSub[N_BKDN_COMP+1][Nntagsub];
	TDirectoryFile *dfVertex	=NULL;
	TDirectoryFile *dfVertexSub[N_BKDN_COMP+1];
	TDirectoryFile *dfMCTruth	=NULL;
	TDirectoryFile *dfMCTruthSub[N_BKDN_COMP+1];


	TDirectoryFile *dfStack		=NULL;

	TFile *fout=new TFile(fOutFileName.c_str(), "update");
	fout->cd();

	dfCC0PiNumu=(TDirectoryFile*)fout->mkdir("cc0pinumu");

	// Extra related histograms
	dfExtra=(TDirectoryFile*)dfCC0PiNumu->mkdir("Extra");
		for(int i=0; i<N_BKDN_COMP+1; i++)
		{
			if( i==N_BKDN_COMP ){ st="ExHist_all";	}
			else				{ st="ExHist_" + S_BKDN_COMP[i]; }
			dfExtra->cd();
			dfExtraSub[i]=(TDirectoryFile*)dfExtra->mkdir( st.c_str() );
			
				dfExtraSub[i]->cd();
				for(int j=0; j<ExtraHists::N_EXTRA_HIST; j++)
				{
					fExtra[i]->getHist(j)->Write();
				}
		}

	// Ntag related histograms
	dfCC0PiNumu->cd();
	dfNtag=(TDirectoryFile*)dfCC0PiNumu->mkdir("Ntag");
		for(int i=0; i<N_BKDN_COMP+1; i++)
		{
			if( i==N_BKDN_COMP ){ st="NtagHist_all";	}
			else				{ st="NtagHist_" + S_BKDN_COMP[i]; }
			dfNtag->cd();
			dfNtagSub[i]=(TDirectoryFile*)dfNtag->mkdir( st.c_str() );
		
				for(int j=0; j<Nntagsub; j++)
				{	
					dfNtagSub[i]->cd();
					dfNtagSubSub[i][j]=(TDirectoryFile*)dfNtagSub[i]->mkdir( Sntagsub[j].c_str() );
					dfNtagSubSub[i][j]->cd();
					if( j==0 )
					{
						fNtag[i]->writeHists(dfNtagSubSub[i][j], NtagHist::eInVarsPS, NtagCat::eMCN);
						fNtag[i]->writeHists(dfNtagSubSub[i][j], NtagHist::eInVarsPS, NtagCat::eBKG);
					}
					else if( j==1 )
					{
						fNtag[i]->writeHists(dfNtagSubSub[i][j], NtagHist::eInVarsNN, NtagCat::eMCN);
						fNtag[i]->writeHists(dfNtagSubSub[i][j], NtagHist::eInVarsNN, NtagCat::eBKG);
					}
					else
					{
						fNtag[i]->writeHists(dfNtagSubSub[i][j], NtagHist::eOthVars, NtagCat::eMCN);
						fNtag[i]->writeHists(dfNtagSubSub[i][j], NtagHist::eOthVars, NtagCat::eBKG);
					}
				}
		}
/////////////////////////////////
	// Vertex related histograms
	dfCC0PiNumu->cd();
	dfVertex=(TDirectoryFile*)dfCC0PiNumu->mkdir("Vertex");
		for(int i=0; i<N_BKDN_COMP+1; i++)
		{
			if( i==N_BKDN_COMP ){ st="VtxHist_all";	}
			else				{ st="VtxHist_" + S_BKDN_COMP[i]; }
			dfVertex->cd();
			dfVertexSub[i]=(TDirectoryFile*)dfVertex->mkdir( st.c_str() );
			
				dfVertexSub[i]->cd();
				for(int j=0; j<VtxDist::N_VTX_DST; j++)
				{
					fVtx[i]->getDstVis(j)->Write();
				}
		}

/////////////////////////////////
	// MC truth related histograms
	dfCC0PiNumu->cd();
	dfMCTruth=(TDirectoryFile*)dfCC0PiNumu->mkdir("MCTruth");
		for(int i=0; i<N_BKDN_COMP+1; i++)
		{
			if( i==N_BKDN_COMP ){ st="MCTHist_all";	}
			else				{ st="MCTHist_" + S_BKDN_COMP[i]; }
			dfMCTruth->cd();
			dfMCTruthSub[i]=(TDirectoryFile*)dfMCTruth->mkdir( st.c_str() );
			
				dfMCTruthSub[i]->cd();
				for(int j=0; j<MCTruth::N_MCT_DST; j++)
				{
					if( j!=MCTruth::eRecoTrMomTrueQ2 )
					{
						fMCT[i]->getDst(j)->Write();
					}
					else
					{
						fMCT[i]->getDst2D()->Write();
					}
				}
		}

//////////////////////////////////
	// Related stacked histograms
	dfCC0PiNumu->cd();
	fout->cd();
	dfStack=(TDirectoryFile*)fout->mkdir("Stacked");
	dfStack->cd();
		fhLepMomAveTotMCN	->Write();
		fhLepMomAveTagMCN	->Write();
		fhLepMomAveTagALL	->Write();
		fhLepMomNbkgTot		->Write();
		fhsLepMomNuEvts		->Write();
		fhsLepMomTotMCN		->Write();
		fhsLepMomTagALL		->Write();

		fhTrMomAveTotMCN	->Write();
		fhTrMomAveTagMCN	->Write();
		fhTrMomAveTagALL	->Write();
		fhTrMomNbkgTot		->Write();
		fhsTrMomNuEvts		->Write();
		fhsTrMomTotMCN		->Write();
		fhsTrMomTagALL		->Write();

		fhRecoEnuAveTotMCN	->Write();
		fhRecoEnuAveTagMCN	->Write();
		fhRecoEnuAveTagALL	->Write();
		fhRecoEnuNbkgTot	->Write();
		fhsRecoEnuNuEvts	->Write();
		fhsRecoEnuTotMCN	->Write();
		fhsRecoEnuTagALL	->Write();

		fhRecoQ2AveTotMCN	->Write();
		fhRecoQ2AveTagMCN	->Write();
		fhRecoQ2AveTagALL	->Write();
		fhRecoQ2NbkgTot		->Write();
		fhsRecoQ2NuEvts		->Write();
		fhsRecoQ2TotMCN		->Write();
		fhsRecoQ2TagALL		->Write();

		fhCosBmAveTotMCN	->Write();
		fhCosBmAveTagMCN	->Write();
		fhCosBmAveTagALL	->Write();
		fhCosBmNbkgTot		->Write();
		fhsCosBmNuEvts		->Write();
		fhsCosBmTotMCN		->Write();
		fhsCosBmTagALL		->Write();

		fhfQDWallAveTotMCN	->Write();
		fhfQDWallAveTagMCN	->Write();
		fhfQDWallAveTagALL	->Write();
		fhfQDWallNbkgTot	->Write();
		fhsfQDWallNuEvts	->Write();
		fhsfQDWallTotMCN	->Write();
		fhsfQDWallTagALL	->Write();

		fhfQVtxR2AveTotMCN	->Write();
		fhfQVtxR2AveTagMCN	->Write();
		fhfQVtxR2AveTagALL	->Write();
		fhfQVtxR2NbkgTot	->Write();
		fhsfQVtxR2NuEvts	->Write();
		fhsfQVtxR2TotMCN	->Write();
		fhsfQVtxR2TagALL	->Write();

		fhfQVtxZAveTotMCN	->Write();
		fhfQVtxZAveTagMCN	->Write();
		fhfQVtxZAveTagALL	->Write();
		fhfQVtxZNbkgTot		->Write();
		fhsfQVtxZNuEvts		->Write();
		fhsfQVtxZTotMCN		->Write();
		fhsfQVtxZTagALL		->Write();

		fhsTaggedNMulti		->Write();

		fhsRecoNPDistTagALL		->Write();
		fhsRecoNPDistLongTagALL	->Write();
		fhsRecoNPDistTranTagALL	->Write();
		fhsRecoCosNangActTagALL	->Write();
		fhsRecoCosNangInfTagALL	->Write();
		fhsRecoTDiffTagALL		->Write();

		fLegRNumu->Write();
		fLegLNumu->Write();
		fLegRNtag->Write();
		fLegLNtag->Write();
	
	fout->cd();
	fout->Close();
}
