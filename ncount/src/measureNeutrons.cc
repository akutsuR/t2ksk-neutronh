// This code computes ** mean neutron multiplicity ** by doning :
// 
//   - bkg. subtraction of n tagging based on # obs. nu events
//   - tagging efficiency correction 
//
// -- June 2019 by RA

#include "measureNeutrons.h"

int main(int argc, char** argv)
{
	// Check command line arguments
		parseCmdLineArgs(argc, argv);

	// Load tvar corrected MC expectation w/ 
	// n search winow from +18us to +513us
		loadMCTvar();

	// Load total sys. error on tagging efficiency
		loadSysError();
	
	// Compute MC expectations
		computeMCExpectation();

	// Compute tagging efficiency w/ systematics
		computeEfficiency();

	// Load data
		loadData();

	// Calculate # bkg. in obs. tagged n
		computeExpectedBkg();

	// Apply efficiency correction after subtracting bkg.
		measureNeutrons();

	// Write outputs
		writeOutputs();
	

		generateTable();
return 0;
}


//////////////////////////////////////////

void parseCmdLineArgs(int argc, char** argv)
{
	for(int i=1; i<argc; i++)
	{
		if	   ( string(argv[i])=="-i_mc_fhc" )	{ fInFileMC[eFHC]		=string( argv[i+1] );	i++;}
		else if( string(argv[i])=="-i_mc_rhc" )	{ fInFileMC[eRHC]		=string( argv[i+1] );	i++;}
		else if( string(argv[i])=="-i_syserr" )	{ fInFileSysErr			=string( argv[i+1] );	i++;}
		else if( string(argv[i])=="-i_da_fhc" )	{ fInFileData[eFHC]		=string( argv[i+1] );	i++;}
		else if( string(argv[i])=="-i_da_rhc" )	{ fInFileData[eRHC]		=string( argv[i+1] );	i++;}
		else if( string(argv[i])=="-o" )		{ fOutFileName			=string( argv[i+1] );	i++;}
		else if( string(argv[i])=="-rndmsd" )	{ fSeed					=atoi( argv[i+1] );		i++;}
		else if( string(argv[i])=="-nthrw" )	{ fNthrows				=atoi( argv[i+1] );		i++;}
		else if( string(argv[i])=="--RndmThrwStatErr" ) { fUseRndmThrw	=atoi( argv[i+1] ); 	i++;}
		else
		{
			cout<<" [ERROR] parseCmdLineArgs " <<endl;
			cout<<"  - Invalid argument :" << argv[i] <<endl;
		}
	}
}

//////////////////////////////////////////
void loadMCTvar()
{
	const int Ndf=3;
	const string Sdf[Ndf]={ "cc0pinumu",
						    "Extra",
							"ExHist_all"
						  };
	TFile *f=NULL;
	TDirectoryFile *df[Ndf];
	string sfn="";
	string shn="";
	for(int i=0; i<N_BEAM_MODE; i++)
	{
		sfn=fInFileMC[i];
		cout<<" Loading :" << sfn <<endl;

		f=TFile::Open(sfn.c_str(), "read");

			for(int j=0; j<Ndf; j++)
			{
				if( j==0 )
				{ 
					df[j]=(TDirectoryFile*)f->Get( Sdf[j].c_str() );
				}
				else
				{
					df[j]=(TDirectoryFile*)df[j-1]->Get( Sdf[j].c_str() );
				}
				df[j]->cd();
			}

			for(int j=0; j<NCAT; j++)
			{
				shn="hTrMom" + SCAT[j];
				fhTrMomMC[i][j]=(TH1D*)df[Ndf-1]->Get(shn.c_str())->Clone();
				fhTrMomMC[i][j]->SetDirectory( 0 );
			}	

		f->Close();
		delete f;	f=NULL;
	}
}

//////////////////////////////////////////
void loadData()
{
	const int Ndf=2;
	const string Sdf[Ndf]={ "Extra",
							"ExHist_data"
						  };
	TFile *f=NULL;
	TDirectoryFile *df[Ndf];
	string sfn="";
	string shn="";
	for(int i=0; i<N_BEAM_MODE; i++)
	{
		sfn=fInFileData[i];
		cout<<" Loading :" << sfn <<endl;

		f=TFile::Open(sfn.c_str(), "read");

			for(int j=0; j<Ndf; j++)
			{
				if( j==0 )
				{ 
					df[j]=(TDirectoryFile*)f->Get( Sdf[j].c_str() );
				}
				else
				{
					df[j]=(TDirectoryFile*)df[j-1]->Get( Sdf[j].c_str() );
				}
				df[j]->cd();
			}

			for(int j=0; j<NCAT; j++)
			{
				shn="hTrMom" + SCAT[j];
				fhTrMomData[i][j]=(TH1D*)df[Ndf-1]->Get(shn.c_str())->Clone();
				fhTrMomData[i][j]->SetDirectory( 0 );
			}	
			for(int j=0; j<N_TRMOM_BINS; j++)
			{
				shn=S_TRMOM_HIST[j];
				fhTagNmulti[i][j]=(TH1D*)df[Ndf-1]->Get(shn.c_str())->Clone();
				fhTagNmulti[i][j]->SetDirectory( 0 );
				cout<<" Integral :" << fhTagNmulti[i][j]->Integral() <<endl;
			}

		f->Close();
		delete f;	f=NULL;
	}
}

//////////////////////////////////////////
void loadSysError()
{
	TFile *f=TFile::Open(fInFileSysErr.c_str(), "read");
	string sn="";
	string sm="";
	for(int i=0; i<N_BEAM_MODE; i++)
	{
		sm=S_BEAM_MODE[i];
		sn="hAveEff_TotalFracError_" + sm;
		fhFracErrTotAve[i]=(TH1D*)f->Get(sn.c_str())->Clone();
		fhFracErrTotAve[i]->SetDirectory(0);

		for(int j=0; j<N_SIGMA_VAR; j++)
		{
			sn="hTrMomEff_TotalFracError_" + sm + "_" + S_SIGMA_VAR[j];
			fhFracErrTrMomAve[i][j]=(TH1D*)f->Get(sn.c_str())->Clone();
			fhFracErrTrMomAve[i][j]->SetDirectory( 0 );
		}
	}
	f->Close();
}


//////////////////////////////////////////
void computeMCExpectation()
{
	string sm="";
	string sn="";
	double Nnuevts=0.0;
	double Nmcntot=0.0;
	double Enuevts=0.0;
	double Emcntot=0.0;

	sn="gTotAveMC_fhc";
	fgTotAveMC[eFHC]=new TGraphErrors();
	fgTotAveMC[eFHC]->SetName( sn.c_str() );
	fgTotAveMC[eFHC]->SetLineWidth( 3 );
	fgTotAveMC[eFHC]->SetLineColor( kBlue-4 );
	fgTotAveMC[eFHC]->SetFillColor( kBlue-4 );

	sn="gTotAveMC_rhc";
	fgTotAveMC[eRHC]=new TGraphErrors();
	fgTotAveMC[eRHC]->SetName( sn.c_str() );
	fgTotAveMC[eRHC]->SetLineWidth( 3 );
	fgTotAveMC[eRHC]->SetLineColor( kRed-4 );
	fgTotAveMC[eRHC]->SetFillColor( kRed-4 );


	cout<<" Calculating MC expectations " <<endl;
	for(int i=0; i<N_BEAM_MODE; i++)
	{
		int b=fhTrMomMC[i][eNmcnTot]->GetNbinsX();
		Nnuevts=fhTrMomMC[i][eNuEvts]->Integral();
		Nmcntot=fhTrMomMC[i][eNmcnTot]->Integral();
		fhTrMomMC[i][eNmcnTot]->IntegralAndError(1, b, Enuevts);
		fhTrMomMC[i][eNmcnTag]->IntegralAndError(1, b, Emcntot);


		if( i==eFHC ){ sm="FHC"; }
		else		 { sm="RHC"; }	
		cout<<"   ---> " 		<< sm 
			<<" - Nnuevts :"	<< Nnuevts <<" (" << Enuevts <<")"
			<<" - Nmcntot :"	<< Nmcntot <<" (" << Emcntot <<")"
			<<" - Mean :"		<< Nmcntot/Nnuevts
			<<endl;

		double d1=(Enuevts/Nnuevts)*(Enuevts/Nnuevts);
		double d2=(Emcntot/Nmcntot)*(Emcntot/Nmcntot);
		double d3=TMath::Sqrt(d1 + d2);
		sn="hTotAveMC_" + S_BEAM_MODE[i];
		fhTotAveMC[i]=new TH1D(sn.c_str(), "", 1, 0, 1);
		fhTotAveMC[i]->SetBinContent(1, Nmcntot/Nnuevts);
		fhTotAveMC[i]->SetBinError(1, (Nmcntot/Nnuevts)*d3);

		if( i==eFHC )
		{
			fgTotAveMC[eFHC]->SetPoint(0, (Double_t)i+0.5, Nmcntot/Nnuevts);
			fgTotAveMC[eFHC]->SetPointError(0, 0.25, (Nmcntot/Nnuevts)*d3);
		}
		else
		{
			fgTotAveMC[eRHC]->SetPoint(0, (Double_t)i+0.5, Nmcntot/Nnuevts);
			fgTotAveMC[eRHC]->SetPointError(0, 0.25, (Nmcntot/Nnuevts)*d3);
		}

		sn="hTrMomAveMC_" + S_BEAM_MODE[i];
		fhTrMomAveMC[i]=(TH1D*)fhTrMomMC[i][eNmcnTot]->Clone();
		fhTrMomAveMC[i]->Divide( (TH1D*)fhTrMomMC[i][eNuEvts]->Clone() );
		fhTrMomAveMC[i]->SetName( sn.c_str() );

		sn="gTrMomAveMC_" + S_BEAM_MODE[i];
		fgTrMomAveMC[i]=new TGraphErrors();
		fgTrMomAveMC[i]->SetName( sn.c_str() );
		fgTrMomAveMC[i]->SetLineWidth( 3 );

		int cl=0;
		if( i==eFHC ){ cl=kBlue-4; }
		if( i==eRHC ){ cl=kRed-4; }

		fgTrMomAveMC[i]->SetFillColor( cl );
		fgTrMomAveMC[i]->SetLineColor( cl );

		int nbins=fhTrMomAveMC[i]->GetNbinsX();
		int np=0;
		double x=0.0;
		double dx=0.0;
		double y=0.0;
		double dy=0.0;
		for(int j=0; j<nbins; j++)
		{
			np	=fgTrMomAveMC[i]->GetN();
			x	=fhTrMomAveMC[i]->GetXaxis()->GetBinCenter(j+1);
			dx	=x - fhTrMomAveMC[i]->GetXaxis()->GetBinLowEdge(j+1);
			y	=fhTrMomAveMC[i]->GetBinContent(j+1);
			dy	=fhTrMomAveMC[i]->GetBinError(j+1);

			fgTrMomAveMC[i]->SetPoint(np, x, y);
			fgTrMomAveMC[i]->SetPointError(np, dx, dy);
		}

	}
	cout<<endl;
}

//////////////////////////////////////////
void computeEfficiency()
{
	string sm="";
	string sn="";
	double Nmcntot=0.0;
	double Nmcntag=0.0;
	double Nnuevts=0.0;
	double Nbkgtag=0.0;

	int nbins=N_SIGMA_VAR+1;	// Nominal and +- 1sigma

	cout<<" Calculating tagging efficiency " <<endl;
	for(int i=0; i<N_BEAM_MODE; i++)
	{

		// Compute total average
		Nmcntot=fhTrMomMC[i][eNmcnTot]->Integral();
		Nmcntag=fhTrMomMC[i][eNmcnTag]->Integral();

		// Compute bkg. rate
		Nnuevts=fhTrMomMC[i][eNuEvts]->Integral();
		Nbkgtag=fhTrMomMC[i][eNbkgTag]->Integral();

	
		if( i==eFHC ){ sm="FHC"; }
		else		 { sm="RHC"; }	
		cout<<" ---> " 			<< sm 
			<<" - Nmcntot :"	<< Nmcntot 
			<<" - Nmcntag :"	<< Nmcntag 
			<<" - Mean :"		<< Nmcntag/Nmcntot
			<<" | Nnuevts :"	<< Nnuevts
			<<" - Nbkgtag :"	<< Nbkgtag
			<<" - Brate :"		<< Nbkgtag/Nnuevts
			<<endl;

		sn="hTotAveEff_" + S_BEAM_MODE[i];
		Double_t eff=Nmcntag/Nmcntot;
		Double_t varPls=1.0 + fhFracErrTotAve[i]->GetBinContent(ePlusOneSigma+1)/100.0;
		Double_t varMns=1.0 - fhFracErrTotAve[i]->GetBinContent(eMinusOneSigma+1)/100.0;

		fhTotAveEff[i]=new TH1D(sn.c_str(), "", nbins, 0, (Double_t)nbins);
		fhTotAveEff[i]->SetBinContent(eNominal+1, eff);
		fhTotAveEff[i]->SetBinContent(ePls1Sig+1, eff*varPls);
		fhTotAveEff[i]->SetBinContent(eMns1Sig+1, eff*varMns);

		fhTotAveEff[i]->GetXaxis()->SetBinLabel(eNominal+1, "Nominal");
		fhTotAveEff[i]->GetXaxis()->SetBinLabel(ePls1Sig+1, "+ 1sigma");
		fhTotAveEff[i]->GetXaxis()->SetBinLabel(eMns1Sig+1, "- 1sigma");

		sn="hBkgRate_" + S_BEAM_MODE[i];
		fhBkgRate[i]=new TH1D(sn.c_str(), "", 1, 0, 1);
		fhBkgRate[i]->SetBinContent(1, Nbkgtag/Nnuevts);


		// Compute tr mom. average
		sn="hTrMomAveEff_" + S_BEAM_MODE[i] + "_nominal";
		fhTrMomAveEff[i][eNominal]=(TH1D*)fhTrMomMC[i][eNmcnTag]->Clone();
		fhTrMomAveEff[i][eNominal]->Divide( (TH1D*)fhTrMomMC[i][eNmcnTot]->Clone() );
		fhTrMomAveEff[i][eNominal]->SetName( sn.c_str() );


		sn="hTrMomAveEff_" + S_BEAM_MODE[i] + "_pls1sig";
		fhTrMomAveEff[i][ePls1Sig]=(TH1D*)fhTrMomAveEff[i][eNominal]->Clone(sn.c_str());

		sn="hTrMomAveEff_" + S_BEAM_MODE[i] + "_mns1sig";
		fhTrMomAveEff[i][eMns1Sig]=(TH1D*)fhTrMomAveEff[i][eNominal]->Clone(sn.c_str());


		nbins=fhTrMomAveEff[i][ePls1Sig]->GetNbinsX();
		if( fhFracErrTrMomAve[i][ePlusOneSigma]->GetNbinsX() != nbins ||
			fhFracErrTrMomAve[i][eMinusOneSigma]->GetNbinsX() != nbins )
		{
			cout<<" Number of bins are different btw efficiency and sys. error" <<endl;
			cout<<" -> EXIT" 													<<endl;
			exit( 1 );
		}

		for(int j=0; j<nbins; j++)
		{
			eff		=fhTrMomAveEff[i][eNominal]->GetBinContent(j+1);
			varPls	=1.0 + fhFracErrTrMomAve[i][ePlusOneSigma]->GetBinContent(j+1)/100.0;
			varMns	=1.0 - fhFracErrTrMomAve[i][eMinusOneSigma]->GetBinContent(j+1)/100.0;

			fhTrMomAveEff[i][ePls1Sig]->SetBinContent(j+1, eff*varPls);
			fhTrMomAveEff[i][eMns1Sig]->SetBinContent(j+1, eff*varMns);
		}

	}
	cout<<endl;
}


//////////////////////////////////////////
void computeExpectedBkg()
{
	string sn="";
	double Nnuevts=0.0;
	double Nbkg=0.0;
	double brate=0.0;
	for(int i=0; i<N_BEAM_MODE; i++)
	{
		brate	=fhBkgRate[i]->GetBinContent(1);
		Nnuevts	=fhTrMomData[i][eNuEvts]->Integral();
		Nbkg	=brate*Nnuevts;

		sn="hTotExpBkg_" + S_BEAM_MODE[i];
		fhTotExpBkg[i]=new TH1D(sn.c_str(), "", 1, 0, 1);
		fhTotExpBkg[i]->SetBinContent(1, Nbkg);
		
		sn="hTrMomExpBkg_" + S_BEAM_MODE[i];
		fhTrMomExpBkg[i]=(TH1D*)fhTrMomData[i][eNuEvts]->Clone( sn.c_str() );
		fhTrMomExpBkg[i]->Scale( brate );

		fBkgRate[i]=brate;
	}
}

//////////////////////////////////////////
void measureNeutrons()
{
	initiStatErrors();
	throwStatErrors();
	computeStatErrors();

	measureTrMomAve();
	measureTotAve();
}

//////////////////////////////////////////
void initiStatErrors()
{
	string sm="";
	string st="";
	string sn="";

	int nbins=40000;
	double xmin=0.0;
	double xmax=2.0;
	for(int i=0; i<N_BEAM_MODE; i++)
	{
		sm=S_BEAM_MODE[i];
		for(int j=0; j<N_TRMOM_BINS+1; j++)
		{
			if( j==N_TRMOM_BINS ){ st="TrMomAll"; }
			else				 { st=S_TRMOM_LABEL[j]; }

			sn="hDSTMean_" + sm + "_" + st;
			fhDSTMean[i][j]=new TH1D(sn.c_str(), "", nbins, xmin, xmax);
			fhDSTMean[i][j]->Sumw2();

			sn="hCDFMean_" + sm + "_" + st;
			fhCDFMean[i][j]=new TH1D(sn.c_str(), "", nbins, xmin, xmax);

			sn="gInvCDFMean_" + sm + "_" + st;
			fgInvCDFMean[i][j]=new TGraph();
			fgInvCDFMean[i][j]->SetName(sn.c_str());
		}
	}
}

//////////////////////////////////////////
void throwStatErrors()
{
	// For Runs 1-9 data statistics, Poisson error of tagged neutrons
	// does not correctly cover 68.3% region, which was comfirmed by toy MC.
	//
	// In order to estimate proper stat. error on ** data **,
	// Compute bkg. subtracted tagged mean n multiplicity 
	// by random throws.
	//
	// This results are used to assgin ** stat. error** of 
	// the data results.
	//
	// In the following, the central values used are 
	// derived from ** DATA **

	Int_t NevtFHC[N_TRMOM_BINS+1];
	Int_t NtagFHC[N_TRMOM_BINS+1];
	Double_t MeanFHC[N_TRMOM_BINS+1];
	Int_t NevtRHC[N_TRMOM_BINS+1];
	Int_t NtagRHC[N_TRMOM_BINS+1];
	Double_t MeanRHC[N_TRMOM_BINS+1];

	TFile *f=new TFile(fOutFileName.c_str(), "recreate");
	TTree *t=new TTree("res", "");
	t->Branch("NevtFHC", NevtFHC, "NevtFHC[5]/I");
	t->Branch("NtagFHC", NtagFHC, "NtagFHC[5]/I");
	t->Branch("MeanFHC", MeanFHC, "MeanFHC[5]/D");
	t->Branch("NevtRHC", NevtRHC, "NevtRHC[5]/I");
	t->Branch("NtagRHC", NtagRHC, "NtagRHC[5]/I");
	t->Branch("MeanRHC", MeanRHC, "MeanRHC[5]/D");

	// Set nominal value to # nu events
	// (i.e. observed numbers)
	double NevtNom[N_BEAM_MODE][N_TRMOM_BINS];
	cout<<" Setting nominal values for # nu events" <<endl;
	for(int i=0; i<N_BEAM_MODE; i++)
	{
		for(int j=0; j<N_TRMOM_BINS; j++)
		{
			NevtNom[i][j]=fhTagNmulti[i][j]->Integral();
			cout<<"   - NevtNom["<< i 
				<<"][" << j 
				<<"] : " << NevtNom[i][j]
				<<endl;
		}
	}
	cout<<endl;

	// Throwing
	///////////////////////////////////////////
	int iNevt[N_BEAM_MODE][N_TRMOM_BINS+1];
	int iNtag[N_BEAM_MODE][N_TRMOM_BINS+1];
	double iMean[N_BEAM_MODE][N_TRMOM_BINS+1];

	TRandom3 *Rndm3=new TRandom3( fSeed );
	gRandom->SetSeed( Rndm3->Integer( 10000 ) );

	cout<<" Throwing " << fNthrows << " times......" <<endl;
	for(int i=0; i<fNthrows; i++)
	{
		// Clear 
		for(int j=0; j<N_BEAM_MODE; j++)
		{
			for(int k=0; k<N_TRMOM_BINS+1; k++)
			{
				iNevt[j][k]=0;
				iNtag[j][k]=0;
				iMean[j][k]=0.0;
			}
		}

		// Throw # nu evets by Poisson
		for(int j=0; j<N_BEAM_MODE; j++)
		{
			for(int k=0; k<N_TRMOM_BINS; k++)
			{
				iNevt[j][k]=Rndm3->Poisson( NevtNom[j][k] );
				iNevt[j][eAll]+=iNevt[j][k];
			}
		}

		// Sample # tagged n from the obs. distribution
		for(int j=0; j<N_BEAM_MODE; j++)
		{
			for(int k=0; k<N_TRMOM_BINS; k++)
			{
				for(int l=0; l<iNevt[j][k]; l++)
				{
					iNtag[j][k]+=(int)fhTagNmulti[j][k]->GetRandom();
				}
				iNtag[j][eAll]+=iNtag[j][k];
			}
		}

		// Compute mean value of this throw
		for(int j=0; j<N_BEAM_MODE; j++)
		{
			for(int k=0; k<N_TRMOM_BINS+1; k++)
			{
				if( j==eFHC )
				{
					NevtFHC[k]		 =iNevt[j][k];
					NtagFHC[k]		 =iNtag[j][k];
					MeanFHC[k]		 =(double)iNtag[j][k]/iNevt[j][k];
					MeanFHC[k]		-=fBkgRate[eFHC];
				}
				else
				{
					NevtRHC[k]		 =iNevt[j][k];
					NtagRHC[k]		 =iNtag[j][k];
					MeanRHC[k]		 =(double)iNtag[j][k]/iNevt[j][k];
					MeanRHC[k]		-=fBkgRate[eRHC];
				}
			}
		}

		for(int j=0; j<N_TRMOM_BINS+1; j++)
		{
			fhDSTMean[eFHC][j]->Fill(MeanFHC[j]);
			fhDSTMean[eRHC][j]->Fill(MeanRHC[j]);
		}

		f->cd();
		t->Fill();
	}
	//////////////////////////////////////////
	
	f->cd();
	t->Write();
	f->Close();
}

//////////////////////////////////////////
void computeStatErrors()
{
	
	double cdf=0.0;
	double norm=0.0;
	double x=0.0;
	double y=0.0;
	for(int i=0; i<N_BEAM_MODE; i++)
	{
		for(int j=0; j<N_TRMOM_BINS+1; j++)
		{
			cdf=0.0;
			norm=0.0;
			for(int k=0; k<fhDSTMean[i][j]->GetNbinsX(); k++)
			{
				cdf+=fhDSTMean[i][j]->GetBinContent(k+1);
				fhCDFMean[i][j]->SetBinContent(k+1, cdf);
			}
			norm=(double)fhDSTMean[i][j]->GetEntries();
			fhCDFMean[i][j]->Scale( 1.0/norm );

			for(int k=0; k<fhCDFMean[i][j]->GetNbinsX(); k++)
			{
				x=fhCDFMean[i][j]->GetXaxis()->GetBinCenter(k+1);
				y=fhCDFMean[i][j]->GetBinContent(k+1);
				fgInvCDFMean[i][j]->SetPoint(k, y, x);
			}
		}
	}

}

//////////////////////////////////////////
void measureTotAve()
{
	cout<<endl;
	cout<<" Computing ** DATA ** total average multiplicity " <<endl;

	for(int i=0; i<NERR; i++)
	{
		string sn="gTotAveData_" + SERR[i];
		fgTotAveData[i]=new TGraphAsymmErrors();
		fgTotAveData[i]->SetName( sn.c_str() );
		fgTotAveData[i]->SetMarkerStyle( 20 );
		fgTotAveData[i]->SetMarkerSize( 1.2 );
	}

	for(int i=0; i<N_BEAM_MODE; i++)
	{
		double Nnu=fhTrMomData[i][eNuEvts]->Integral();
		double Ntg=fhTrMomData[i][eNtotTag]->Integral();
		double Bkg=fhTotExpBkg[i]->GetBinContent(1);
		double Eff=fhTotAveEff[i]->GetBinContent(eNominal+1);
		double M  =(Ntg - Bkg)/Nnu;
		M /= Eff;

		fgTotAveData[eStatOnly]	->SetPoint(i, (Double_t)i+0.5, M);
		fgTotAveData[eSysOnly]	->SetPoint(i, (Double_t)i+0.5, M);
		fgTotAveData[eStatSys]	->SetPoint(i, (Double_t)i+0.5, M);

		// Compute errors
		double nuErr		=TMath::Sqrt( Nnu );
		double tgErr		=TMath::Sqrt( Ntg );
		double effErrPls	=fhTotAveEff[i]->GetBinContent(ePls1Sig+1) - Eff;
		double effErrMns	=Eff - fhTotAveEff[i]->GetBinContent(eMns1Sig+1);
		double MErrStatPls 	=0.0;
		double MErrStatMns 	=0.0;
		double MErrSysPls	=0.0;
		double MErrSysMns	=0.0;
		double MErrTotPls	=0.0;
		double MErrTotMns	=0.0;

		cout<<" --> Nnu :"	<< Nnu 
			<< " - Ntg :" 	<< Ntg 
			<< " - Eff :" 	<< Eff
			<< " - dEff_pls :" 	<< effErrPls/Eff
			<< " - dEff_mns :" 	<< effErrMns/Eff
			<<endl;

		// Stat. error
		double d1=(nuErr/Nnu)*(nuErr/Nnu);
		double d2=(tgErr/Ntg)*(tgErr/Ntg);
		double d3=TMath::Sqrt( d1 + d2 );
		if( fUseRndmThrw )
		{
			MErrStatPls =fgInvCDFMean[i][eAll]->Eval(fTailUp)/Eff;
			MErrStatPls-=M;
			MErrStatMns =M;
			MErrStatMns-=fgInvCDFMean[i][eAll]->Eval(fTailLow)/Eff;
		}
		else
		{
			MErrStatPls=(tgErr/Nnu)/Eff;
			MErrStatMns=MErrStatPls;
		}

		// Sys. err
		MErrSysPls=M*(effErrPls/Eff);
		MErrSysMns=M*(effErrMns/Eff);

		// Tot. err	
		MErrTotPls =MErrStatPls*MErrStatPls;
		MErrTotPls+=MErrSysPls*MErrSysPls;
		MErrTotPls =TMath::Sqrt( MErrTotPls );

		MErrTotMns =MErrStatMns*MErrStatMns;
		MErrTotMns+=MErrSysMns*MErrSysMns;
		MErrTotMns =TMath::Sqrt( MErrTotMns );

		fgTotAveData[eStatOnly]	->SetPointError(i, 0.0, 0.0, MErrStatMns, MErrStatPls);
		fgTotAveData[eSysOnly]	->SetPointError(i, 0.0, 0.0, MErrSysMns, MErrSysPls);
		fgTotAveData[eStatSys]	->SetPointError(i, 0.0, 0.0, MErrTotMns, MErrTotPls);

		MeanN_t tmn;
		tmn.ptbin	=eGE_0p75+1;
		tmn.ntag	=(int)Ntg;
		tmn.nnu		=(int)Nnu;
		tmn.eff		=Eff;
		//tmn.brate	=Bkg/Nnu;
		tmn.brate	=Bkg;
		tmn.meann	=M;
		tmn.stat	=(MErrStatPls/M)*100.0;
		tmn.sysU	=(MErrSysPls/M)*100.0;
		tmn.sysL	=(MErrSysMns/M)*100.0;
		tmn.totU	=(MErrTotPls/M)*100.0;
		tmn.totL	=(MErrTotMns/M)*100.0;

		fNumMeanN[i].push_back( tmn );
////		vmn.push_back( tmn );
//		cout<<endl;
//		cout<<endl;
//		cout<<" ------ fNumMeanN.size() :" << fNumMeanN.size() <<endl;
//		cout<<" ------ fNumMeanN[0].size() :" << fNumMeanN[0].size() <<endl;
//		cout<<" ------ fNumMeanN[1].size() :" << fNumMeanN[1].size() <<endl;
//		cout<<endl;
//		cout<<endl;
	}
	cout<<endl;
}


//////////////////////////////////////////
void measureTrMomAve()
{
	cout<<endl;
	cout<<" Computing ** DATA ** total average multiplicity " <<endl;
	for(int i=0; i<N_BEAM_MODE; i++)
	{
		for(int j=0; j<NERR; j++)
		{
			string sn="gTrMomAveData_" + S_BEAM_MODE[i] + "_" + SERR[j];
			fgTrMomAveData[i][j]=new TGraphAsymmErrors();
			fgTrMomAveData[i][j]->SetName( sn.c_str() );
			fgTrMomAveData[i][j]->SetMarkerStyle( 20 );
			fgTrMomAveData[i][j]->SetMarkerSize( 1.2 );
		}
	}

	for(int i=0; i<N_BEAM_MODE; i++)
	{
		int nbins=fhTrMomData[i][eNuEvts]->GetNbinsX();

		vector<MeanN_t> vmn;
		for(int j=0; j<nbins; j++)
		{

			double xcntr=fhTrMomData[i][eNuEvts]->GetXaxis()->GetBinCenter(j+1);
			double xlow=fhTrMomData[i][eNuEvts]->GetXaxis()->GetBinLowEdge(j+1);
			double dx=xcntr - xlow;

			double Nnu=fhTrMomData[i][eNuEvts]->GetBinContent(j+1);
			double Ntg=fhTrMomData[i][eNtotTag]->GetBinContent(j+1);
			double Bkg=fhTrMomExpBkg[i]->GetBinContent(j+1);
			double Eff=fhTrMomAveEff[i][eNominal]->GetBinContent(j+1);
			double M  =(Ntg - Bkg)/Nnu;
			M /= Eff;

			fgTrMomAveData[i][eStatOnly]	->SetPoint(j, xcntr, M);
			fgTrMomAveData[i][eSysOnly]		->SetPoint(j, xcntr, M);
			fgTrMomAveData[i][eStatSys]		->SetPoint(j, xcntr, M);

			// Compute errors
			double nuErr		=TMath::Sqrt( Nnu );
			double tgErr		=TMath::Sqrt( Ntg );
			double effErrPls	=fhTrMomAveEff[i][ePls1Sig]->GetBinContent(j+1) - Eff;
			double effErrMns	=Eff - fhTrMomAveEff[i][eMns1Sig]->GetBinContent(j+1);
			double MErrStatPls 	=0.0;
			double MErrStatMns 	=0.0;
			double MErrSysPls	=0.0;
			double MErrSysMns	=0.0;
			double MErrTotPls	=0.0;
			double MErrTotMns	=0.0;

			cout<<" --> Nnu :"	<< Nnu 
				<< " - Ntg :" 	<< Ntg 
				<< " - Eff :" 	<< Eff
				<< " - dEff_pls :" 	<< effErrPls/Eff
				<< " - dEff_mns :" 	<< effErrMns/Eff
				<<endl;

			// Stat. error
			double d1=(nuErr/Nnu)*(nuErr/Nnu);
			double d2=(tgErr/Ntg)*(tgErr/Ntg);
			double d3=TMath::Sqrt( d1 + d2 );

			if( fUseRndmThrw )
			{
				MErrStatPls =fgInvCDFMean[i][j]->Eval(fTailUp)/Eff;
				MErrStatPls-=M;
				MErrStatMns =M;
				MErrStatMns-=fgInvCDFMean[i][j]->Eval(fTailLow)/Eff;
			}
			else
			{
				MErrStatPls=(tgErr/Nnu)/Eff;
				MErrStatMns=MErrStatPls;
			}

			// Sys. err
			MErrSysPls=M*(effErrPls/Eff);
			MErrSysMns=M*(effErrMns/Eff);

			// Tot. err	
			MErrTotPls =MErrStatPls*MErrStatPls;
			MErrTotPls+=MErrSysPls*MErrSysPls;
			MErrTotPls =TMath::Sqrt( MErrTotPls );

			MErrTotMns =MErrStatMns*MErrStatMns;
			MErrTotMns+=MErrSysMns*MErrSysMns;
			MErrTotMns =TMath::Sqrt( MErrTotMns );

			fgTrMomAveData[i][eStatOnly]->SetPointError(j, dx, dx, MErrStatMns, MErrStatPls);
			fgTrMomAveData[i][eSysOnly]	->SetPointError(j, 0.0, 0.0, MErrSysMns, MErrSysPls);
			fgTrMomAveData[i][eStatSys]	->SetPointError(j, dx, dx, MErrTotMns, MErrTotPls);


			MeanN_t tmn;
			tmn.ptbin	=e0p00_0p25+j;
			tmn.ntag	=(int)Ntg;
			tmn.nnu		=(int)Nnu;
			tmn.eff		=Eff;
			//tmn.brate	=Bkg/Nnu;
			tmn.brate	=Bkg;
			tmn.meann	=M;
			tmn.stat	=(MErrStatPls/M)*100.0;
			tmn.sysU	=(MErrSysPls/M)*100.0;
			tmn.sysL	=(MErrSysMns/M)*100.0;
			tmn.totU	=(MErrTotPls/M)*100.0;
			tmn.totL	=(MErrTotMns/M)*100.0;
			vmn.push_back( tmn );
		}
		fNumMeanN.push_back( vmn );
	}
	cout<<endl;
}

//////////////////////////////////////////
void generateTable()
{
	fss<<std::setprecision(3);
	fss<<std::fixed;

	string outfile="nmeas_sumingredient_table.tex";
	std::ofstream ofs(outfile);

	ofs<< getFirstLine() <<endl;
	ofs<< getSecondLine() <<endl;

	ofs<< getLineForNumbers(0,0) <<endl;
	ofs<< getLineForNumbers(0,1) <<endl;
	ofs<< getLineForNumbers(0,2) <<endl;
	ofs<< getLineForNumbers(0,3) <<endl;
	ofs<< getLineForNumbers(0,4) <<endl;
	ofs<< getLineForNumbers(1,0) <<endl;
	ofs<< getLineForNumbers(1,1) <<endl;
	ofs<< getLineForNumbers(1,2) <<endl;
	ofs<< getLineForNumbers(1,3) <<endl;
	ofs<< getLineForNumbers(1,4) <<endl;


	ofs<< getLastLine() <<endl;

	ofs.close();

}

string getFirstLine()
{
	string str="";
//	str="\\begin{tabular}{clllllllll} \\hline \\hline \\\\\[-8pt]";
	str="\\begin{tabular}{cccccccccc} \\hline \\hline \\\\\[-8pt]";
	return str;
}

string getSecondLine()
{
	string str="";
	str ="Beam mode ";
	str+="& \\pt bin ";
	str+="& \\ntag ";
	str+="& \\enu ";      
	str+="& \\eff ";
    str+="& \\bkg ";
	str+="& \\mnm ";
	str+="& \\dmnmstat ";
	str+="& \\dmnmsyst ";
	str+="& \\dmnmtot ";
	str+=" \\\\ \\hline \\\\[-8pt]";
	return str;
}

string getLastLine()
{
	string str="";
	str="\\hline \\end{tabular}";
	return str;
}

string getLineForNumbers(int imode, int itrbin)
{
	for(int i=0; i<N_BEAM_MODE; i++)
	{
		int nbins=fhTrMomData[i][eNuEvts]->GetNbinsX() + 1;
		for(int j=0; j<nbins; j++)
		{
			cout<<" i:"		<< i
				<<" - j:"	<< j
				<<" = Ntag:"	<< fNumMeanN[i][j].ntag
				<<endl;
		}
	}
	fss.str("");
	string str="";
	MeanN_t n=fNumMeanN[imode][itrbin];
	if( imode==eFHC && itrbin==0 )
	{
		str ="\\multirow{6}{*}{FHC} ";	fss.str("");
	}
	else if( imode==eRHC && itrbin==0 )
	{
		str ="\\multirow{6}{*}{RHC} ";	fss.str("");
	}
	else
	{
		str ="                      ";	fss.str("");
	}

	if( n.ptbin==e0p00_0p25 ){ str+="& \\ptfrst ";}
	else if(  n.ptbin==e0p25_0p50 ){ str+="& \\ptscnd ";}
	else if(  n.ptbin==e0p50_0p75 ){ str+="& \\ptthrd ";}
	else if(  n.ptbin==eGE_0p75 ){ str+="& \\ptfrth ";}
	else if(  n.ptbin==eGE_0p75+1 ){ str+="& \\ptall ";}
	else
	{
		cout<<" [ERROR] getLineForNumbers " <<endl;
		cout<<"  - n.ptbin:" << n.ptbin << " is not supported." <<endl;
		cout<<" -> EXIT "					<<endl;
		exit( -1 );
	}
	
//str+="& \\ptfrst ";

	///fss<< fNumMeanN[0][4].ntag;	str+=" & " + fss.str(); fss.str("");
	fss<<n.ntag;	str+=" & " + fss.str(); fss.str("");
	fss<<n.nnu;		str+=" & " + fss.str(); fss.str("");
	fss<<n.eff;		str+=" & " + fss.str(); fss.str("");
	fss<<n.brate;	str+=" & " + fss.str(); fss.str("");
	fss<<n.meann;	str+=" & " + fss.str(); fss.str("");
	fss<<n.stat;	str+=" & $\\pm$" + fss.str(); fss.str("");
	fss<<n.sysU;	str+=" & $^{+" + fss.str(); fss.str("");
	fss<<n.sysL;	str+="}_{-" + fss.str(); fss.str("");
	fss<<n.totU;	str+="}$ & $^{+" + fss.str(); fss.str("");
	fss<<n.totL;	str+="}_{-" + fss.str(); fss.str("");
	if( imode==eFHC && itrbin==4 )
	{
		str+="}$\\\\ \\\\[-8pt] \\\\";
	}
	else
	{
		str+="}$\\\\ \\\\[-8pt]";
	}

	return str;
}

//////////////////////////////////////////
void writeOutputs()
{
	TFile *fout=new TFile(fOutFileName.c_str(), "update");

	for(int i=0; i<N_BEAM_MODE; i++){ fhBkgRate[i]->Write(); }
	for(int i=0; i<N_BEAM_MODE; i++){ fhTotAveEff[i]->Write(); }
	for(int i=0; i<N_BEAM_MODE; i++){ fhTrMomAveEff[i][eNominal]->Write(); }
	for(int i=0; i<N_BEAM_MODE; i++){ fhTrMomAveEff[i][ePls1Sig]->Write(); }
	for(int i=0; i<N_BEAM_MODE; i++){ fhTrMomAveEff[i][eMns1Sig]->Write(); }
	for(int i=0; i<N_BEAM_MODE; i++){ fhTotExpBkg[i]->Write(); }
	for(int i=0; i<N_BEAM_MODE; i++){ fhTrMomExpBkg[i]->Write(); }

	for(int i=0; i<N_BEAM_MODE; i++){ fhTotAveMC[i]->Write(); }
	for(int i=0; i<N_BEAM_MODE; i++){ fhTrMomAveMC[i]->Write(); }
	for(int i=0; i<N_BEAM_MODE; i++){ fgTotAveMC[i]->Write(); }
	for(int i=0; i<N_BEAM_MODE; i++){ fgTrMomAveMC[i]->Write(); }
	for(int i=0; i<NERR; i++){ fgTotAveData[i]->Write(); }
	for(int i=0; i<NERR; i++){ fgTrMomAveData[eFHC][i]->Write(); }
	for(int i=0; i<NERR; i++){ fgTrMomAveData[eRHC][i]->Write(); }

	for(int i=0; i<N_TRMOM_BINS+1; i++){ fhDSTMean[eFHC][i]->Write(); }
	for(int i=0; i<N_TRMOM_BINS+1; i++){ fhDSTMean[eRHC][i]->Write(); }
	for(int i=0; i<N_TRMOM_BINS+1; i++){ fhCDFMean[eFHC][i]->Write(); }
	for(int i=0; i<N_TRMOM_BINS+1; i++){ fhCDFMean[eRHC][i]->Write(); }
	for(int i=0; i<N_TRMOM_BINS+1; i++){ fgInvCDFMean[eFHC][i]->Write(); }
	for(int i=0; i<N_TRMOM_BINS+1; i++){ fgInvCDFMean[eRHC][i]->Write(); }
}
