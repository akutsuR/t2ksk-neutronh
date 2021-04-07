#include "NtagInputVarHists.h"

NtagInputVarHists::NtagInputVarHists() :
fPostFix(""),
fIsCoarser(false)
{
	this->clearHists();
	this->setConstants();
	this->setDefaultNames();
}



NtagInputVarHists::~NtagInputVarHists()
{
	for(int i=0; i<NtagCat::N_NTAG_CAT; i++)
	{
		for(int j=0; j<NtagInputVars::N_INPUT_VARS; j++)
		{
			if( fhInVars[i][j]!=NULL )
			{
				delete fhInVars[i][j];
			}
		}
	}
}
	

void NtagInputVarHists::clearHists()
{
	for(int i=0; i<NtagCat::N_NTAG_CAT; i++)
	{
		for(int j=0; j<NtagInputVars::N_INPUT_VARS; j++)
		{
			fhInVars[i][j]=NULL;
		}
	}
}


void NtagInputVarHists::setDefaultNames()
{
	string sn	="",
		   st1	="",
		   st2	="";
	for(int i=0; i<NtagCat::N_NTAG_CAT; i++)
	{
		st1="";	st1=NtagCat::S_NTAG_CAT[ i ];

		for(int j=0; j<NtagInputVars::N_INPUT_VARS; j++)
		{
			st2="";	st2=NtagInputVars::S_INPUT_VARS[ j ];
			sn="";	sn="h" + st2 + "_" + st1;
			fDefName[i][j]=sn;
		}
	}
}


void NtagInputVarHists::setConstants()
{	
	// Binning and bin edges for input variables	
	for(int i=0; i<NtagInputVars::N_INPUT_VARS; i++)
	{
		fNbins[ i ]	=NtagInputVars::NBINS[ i ];
		fXMax[ i ]	=NtagInputVars::XMAX[ i ];
		fXMin[ i ]	=NtagInputVars::XMIN[ i ];
	}

	if( fIsCoarser )
	{
		for(int i=0; i<NtagInputVars::N_INPUT_VARS; i++)
		{
			fNbins[ i ]	=NtagInputVars::NBINSCoarse[ i ];
		}
	}
}



void NtagInputVarHists::setHistNamePostFix(string pf)
{
	fPostFix=pf;
}


void NtagInputVarHists::initializeHists()
{
	string sn	="";
	for(int i=0; i<NtagCat::N_NTAG_CAT; i++)
	{
		for(int j=0; j<NtagInputVars::N_INPUT_VARS; j++)
		{
			sn="";
			if( fPostFix!="" ){ sn=fDefName[i][j] + "_" + fPostFix; }
			else			  { sn=fDefName[i][j]; }
			fhInVars[i][j]=new TH1D(sn.c_str(), "",
										fNbins[j], fXMin[j], fXMax[j]);
			fhInVars[i][j]->Sumw2();
		}
	}
}


void NtagInputVarHists::fillHists(float *vars,
							   	  enum NtagCat::E_NTAG_CAT eNC,
							   	  float wgt)
{
	for(int i=0; i<NtagInputVars::N_INPUT_VARS; i++)
	{
		if(	NtagInputVars::TYPEDEF[i]==(string)typeid(int).name() )
		{
			fhInVars[ eNC ][ i ]->Fill((int)vars[i], wgt);
		}
		else
		{
			fhInVars[ eNC ][ i ]->Fill(vars[i], wgt);
		}
	}
}


void NtagInputVarHists::normalizeHistsByArea()
{
	double norm=-9999.9;
	for(int i=0; i<NtagCat::N_NTAG_CAT; i++)
	{
		for(int j=0; j<NtagInputVars::N_INPUT_VARS; j++)
		{
			if( fhInVars[i][j]!=NULL )
			{
				norm=-9999.9;
				norm=fhInVars[i][j]->Integral();
				fhInVars[i][j]->Scale( 1./norm );
			}
		}
	}
}


void NtagInputVarHists::normalizeHists(double fac)
{
	for(int i=0; i<NtagCat::N_NTAG_CAT; i++)
	{
		for(int j=0; j<NtagInputVars::N_INPUT_VARS; j++)
		{
			if( fhInVars[i][j]!=NULL )
			{
				fhInVars[i][j]->Scale( fac );
			}
		}
	}
}


TH1D* NtagInputVarHists::getHist(int icat, int ivar)
{
	enum NtagInputVars::E_INPUT_VARS eiv=
			NtagInputVars::int2enum(ivar);
	enum NtagCat::E_NTAG_CAT enc=
			NtagCat::int2enum(icat);
	return this->getHist(enc, eiv);
}


TH1D* NtagInputVarHists::getHist(enum NtagCat::E_NTAG_CAT enc,
								 enum NtagInputVars::E_INPUT_VARS eiv)
{
	return (TH1D*)fhInVars[enc][eiv]->Clone(fDefName[enc][eiv].c_str());
}


bool NtagInputVarHists::operator+=(const NtagInputVarHists& h) const
{
	for(int i=0; i<NtagCat::N_NTAG_CAT; i++)
	{
		for(int j=0; j<NtagInputVars::N_INPUT_VARS; j++)
		{
			if( fhInVars[i][j]!=NULL && h.fhInVars[i][j]!=NULL )
			{
				fhInVars[i][j]->Add( (TH1D*)h.fhInVars[i][j]->Clone() );
			}
		}
	}
	return true;
}

void NtagInputVarHists::loadHists(TDirectory *td)
{
	cout<<" [INFO] NtagInputVarHists::loadHists " <<endl;
	cout<<"   - Trying to load histograms from TDirectory "
		<<td->GetName() <<endl;

	TKey *tk=NULL;
	TIter titr(td->GetListOfKeys());
	bool isFound[NtagCat::N_NTAG_CAT][NtagInputVars::N_INPUT_VARS];
	for(int i=0; i<NtagCat::N_NTAG_CAT; i++)
	{
		for(int j=0; j<NtagInputVars::N_INPUT_VARS; j++)
		{
			isFound[i][j]=false;
		}
	}

	while( tk=(TKey*)titr() )
	{
		if( string(tk->GetClassName())!="TH1D" ){ continue; }
		string shn( tk->GetName() );
		
		for(int i=0; i<NtagCat::N_NTAG_CAT; i++)
		{
			if( shn.find( NtagCat::S_NTAG_CAT[i] )!=string::npos )
			{
				for(int j=0; j<NtagInputVars::N_INPUT_VARS; j++)
				{
					if( shn.find( NtagInputVars::S_INPUT_VARS[j] )!=string::npos )
					{
						cout<<"     - Found " << NtagCat::S_NTAG_CAT[i] 
							<<" - "			  << NtagInputVars::S_INPUT_VARS[j]
							<<endl;

						//if( fhInVars[i][j] ){ continue; }
						if( !fhInVars[i][j] && !isFound[i][j] )
						{ 
							fhInVars[i][j]=(TH1D*)tk->ReadObj();
							fhInVars[i][j]->SetDirectory(0);
							isFound[i][j]=true;
							break;
						}
					}
				}
				break;
			}
		}
	}

	cout<<"   - Successfully loaded"				<<endl;
	cout<<endl;
	td->cd();
}

void NtagInputVarHists::setCoarserBinning(const bool flg)
{
	fIsCoarser=flg;
	if( fIsCoarser )
	{
		cout<<" [INFO] NtagInputVarHists::setCoarserBinning " <<endl;
		cout<<"   - Using coarser binning "<<endl;
		this->setConstants();
	}
}
