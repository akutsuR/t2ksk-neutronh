#include "CC0PiNumuEvSelHists.h"

CC0PiNumuEvSelHists::CC0PiNumuEvSelHists(string pfx) :
fPostFix(pfx)
{
	clearHists();
	setConstants();
	setDefaultNames();
}


CC0PiNumuEvSelHists::CC0PiNumuEvSelHists() : 
fPostFix("")
{
	clearHists();
	setConstants();
	setDefaultNames();
}


CC0PiNumuEvSelHists::~CC0PiNumuEvSelHists()
{
	for(int i=0; i<N_EVSEL_HIST; i++)
	{
		if( fHist[i]!=NULL )
		{
				delete fHist[i];
		}
	}
}
	

void CC0PiNumuEvSelHists::clearHists()
{
	for(int i=0; i<N_EVSEL_HIST; i++)
	{
			fHist[i]=NULL;
	}
}


void CC0PiNumuEvSelHists::setDefaultNames()
{
	for(int i=0; i<N_EVSEL_HIST; i++)
	{
		fDefName[i]=S_EVSEL_HIST[ i ];
	}
}


void CC0PiNumuEvSelHists::setConstants()
{	
	for(int i=0; i<N_EVSEL_HIST; i++)
	{
		fNbins[ i ]	=NBINS[ i ];
		fXMax[ i ]	=XMAX[ i ];
		fXMin[ i ]	=XMIN[ i ];
	}
}



void CC0PiNumuEvSelHists::setHistNamePostFix(string pf)
{
	fPostFix=pf;
}


void CC0PiNumuEvSelHists::initializeHists()
{
	string sn	="";
	for(int i=0; i<N_EVSEL_HIST; i++)
	{
		sn="";
		if( fPostFix!="" ){ sn=fDefName[i] + "_" + fPostFix; }
		else			  { sn=fDefName[i]; }
		fHist[i]=new TH1D(sn.c_str(), "",
							fNbins[i], fXMin[i], fXMax[i]);
		fHist[i]->Sumw2();
	}


	// Event selection summary
	fHist[eEveSelSum]->GetXaxis()->SetLabelSize( 0.055 );
	for(int i=0; i<fNbins[eEveSelSum]; i++)
	{
		sn=CC0PiNumuCut::S_EVE_SLC[i];
		fHist[eEveSelSum]->GetXaxis()->SetBinLabel(i+1, sn.c_str());
	}

	// Nring
	fHist[eNRing]->GetXaxis()->SetLabelSize( 0.055 );
	for(int i=0; i<fNbins[eNRing]; i++)
	{
		fHist[eNRing]->GetXaxis()->SetBinLabel(i+1, Form("%d", i+1));
	}

	// Dcye
	fHist[eDcyE]->GetXaxis()->SetLabelSize( 0.055 );
	for(int i=0; i<fNbins[eDcyE]; i++)
	{
		fHist[eDcyE]->GetXaxis()->SetBinLabel(i+1, Form("%d", i));
	}
}


template <typename T> void CC0PiNumuEvSelHists::fillHist(enum EvSelHists::E_EVSEL_HIST eeh,
														 T t,
														 float w)
{
	if( t>fHist[eeh]->GetXaxis()->GetXmax() )
	{
		fHist[eeh]->AddBinContent(fNbins[eeh], w);
	}
	else if( t<fHist[eeh]->GetXaxis()->GetXmin() )
	{
		fHist[eeh]->AddBinContent(1, w);
	}
	else
	{
		fHist[eeh]->Fill(t, w);
	}
}

template void CC0PiNumuEvSelHists::fillHist(enum EvSelHists::E_EVSEL_HIST, int, float);
template void CC0PiNumuEvSelHists::fillHist(enum EvSelHists::E_EVSEL_HIST, float, float);


void CC0PiNumuEvSelHists::fillHists(const EvSelVar_t evar, float w)
{
	if( evar.pass[eFCFVDW200] )
	{
		this->fillHist(eEveSelSum, (int)eFCFVDW200+0.5, w);
		this->fillHist(eNRing, evar.nring, w);
	}

	if( evar.pass[eNRING_EQ_1] )
	{
		this->fillHist(eEveSelSum, (int)eNRING_EQ_1+0.5, w);
		this->fillHist(eEMuPid, evar.emupid, w);
	}

	if( evar.pass[eEMUPID_MU] )
	{
		this->fillHist(eEveSelSum, (int)eEMUPID_MU+0.5, w);
		this->fillHist(eMomMu, evar.momm, w);
	}

	if( evar.pass[eMUMOM_GE_200] )
	{
		this->fillHist(eEveSelSum, (int)eMUMOM_GE_200+0.5, w);
		this->fillHist(eDcyE, evar.dcye, w);
	}

	if( evar.pass[eDCYE_LE_1] )
	{
		this->fillHist(eEveSelSum, (int)eDCYE_LE_1+0.5, w);
		this->fillHist(eCPiMuPid, evar.cpimupid, w);
	}

	if( evar.pass[eCPIMUPID_MU] )
	{
		this->fillHist(eEveSelSum, (int)eCPIMUPID_MU+0.5, w);
	}
}



void CC0PiNumuEvSelHists::normalizeHists(double fac)
{
	for(int i=0; i<N_EVSEL_HIST; i++)
	{
		fHist[i]->Scale( fac );
	}
}


TH1D* CC0PiNumuEvSelHists::getHist(int ieh)
{
	E_EVSEL_HIST eeh=int2enum(ieh);
	return this->getHist(eeh);
}


TH1D* CC0PiNumuEvSelHists::getHist(enum EvSelHists::E_EVSEL_HIST eeh)
{
	return (TH1D*)fHist[eeh]->Clone(fDefName[eeh].c_str());
}


bool CC0PiNumuEvSelHists::operator+=(const CC0PiNumuEvSelHists& h) const
{
	for(int i=0; i<N_EVSEL_HIST; i++)
	{
		if( fHist[i]!=NULL )
		{
			fHist[i]->Add( (TH1D*)h.fHist[i]->Clone() );
		}
	}
	return true;
}


void CC0PiNumuEvSelHists::loadHists(TDirectory *td)
{
	cout<<" [INFO] CC0PiNumuEvSelHists::loadHists " <<endl;
	cout<<"   - Trying to load histograms from TDirectory "
		<<td->GetName() <<endl;

	bool isFound[N_EVSEL_HIST]={false};
	TKey *tk=NULL;
	TIter titr(td->GetListOfKeys());
	while( tk=(TKey*)titr() )
	{
		if( string(tk->GetClassName())!="TH1D" ){ continue; }

		string shn( tk->GetName() );
		for(int i=0; i<N_EVSEL_HIST; i++)
		{
			if( shn.find( S_EVSEL_HIST[i] )!=string::npos )
			{
				cout<<"     - Found " << S_EVSEL_HIST[i] <<endl;
				fHist[i]=(TH1D*)tk->ReadObj();
				fHist[i]->SetDirectory(0);
				isFound[i]=true;
				break;
			}
		}					
	}

	// Check whether all fHist[] were found or not
	bool isOK=true;
	for(int i=0; i<N_EVSEL_HIST; i++)
	{
		if( !isFound[i] )
		{
			cout<<"   - " << S_EVSEL_HIST[i] <<" was not found. "<<endl;
			isOK=false;
		}	
	}	

	if( !isOK )
	{
		cout<<" [ERROR] CC0PiNumuEvSelHists::loadHists " <<endl;
		cout<<"   - All histograms were not found."		 <<endl;
		cout<<"   - Input TDirectory might be wrong."	 <<endl;
		cout<<" -> EXIT "								 <<endl;
		exit( -1 );
	}

	cout<<"   - Successfully loaded"				<<endl;
	cout<<endl;
	td->cd();
}
