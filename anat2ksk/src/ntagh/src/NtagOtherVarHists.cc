#include "NtagOtherVarHists.h"

NtagOtherVarHists::NtagOtherVarHists(bool binning, bool ambe) :
fPostFix(""),
fBinningFlag(binning),
fAmBeFlag(ambe),
fIsCoarser( false )
{
	this->setConstants();
	this->clearHists();
	this->setDefaultNames();
}


void NtagOtherVarHists::setAmBeFlag(bool flag)
{
	// If fAmBeFlag==true, then
	// histograms for NtagOtherVars::et0long_PS 
	// and NtagOtherVars::et0long_NN will be 
	// instanciated and can be filled.
	// The flag is assumed to be used only
	// for Am/Be calib.
	fAmBeFlag=flag;
}


void NtagOtherVarHists::setBinningFlag(bool flag)
{
	// If fBinning==true, then number of bins and
	// binning for both rec. npdist and mct npdist 
	// are set to be the values defined by 
	// NtagOtherVars::NBINS, NtagOtherVars::XMIN,
	// and NtagOtherVars::XMAX.
	fBinningFlag=flag;
}

void NtagOtherVarHists::clearHists()
{
	for(int i=0; i<NtagCat::N_NTAG_CAT; i++)
	{
		for(int j=0; j<NtagOtherVars::N_OTHER_VARS; j++)
		{
			fhOthVars[i][j]=NULL;
		}
	}
}


void NtagOtherVarHists::setDefaultNames()
{
	string sn	="",
		   st1	="",
		   st2	="";
	for(int i=0; i<NtagCat::N_NTAG_CAT; i++)
	{
		st1="";	st1=NtagCat::S_NTAG_CAT[ i ];

		for(int j=0; j<NtagOtherVars::N_OTHER_VARS; j++)
		{
			st2="";	st2=NtagOtherVars::S_OTHER_VARS[ j ];
			sn="";	sn="h" + st2 + "_" + st1;
			fDefName[i][j]=sn;
		}
	}
}


void NtagOtherVarHists::setConstants()
{	
	// Binning and bin edges for input variables	
	for(int i=0; i<NtagOtherVars::N_OTHER_VARS; i++)
	{
		if( !fIsCoarser )
		{
			fNbins[ i ]	=NtagOtherVars::NBINS[ i ];
			fXMax[ i ]	=NtagOtherVars::XMAX[ i ];
			fXMin[ i ]	=NtagOtherVars::XMIN[ i ];
		}
		else
		{
			fNbins[ i ]	=NtagOtherVars::NBINSCoarse[ i ];
			fXMax[ i ]	=NtagOtherVars::XMAXCoarse[ i ];
			fXMin[ i ]	=NtagOtherVars::XMINCoarse[ i ];
		}
	}
}


void NtagOtherVarHists::setBinning(enum NtagOtherVars::E_OTHER_VARS eov, 
				   				   const int nbins, 
				   				   const double xmin, 
				   				   const double xmax)
{
	cout<<" [INFO] NtagOtherVarHists::setBinning " 	<<endl;
	cout<<"   - Chaning binning of " << NtagOtherVars::S_OTHER_VARS[eov]
		<<" from its default "						 <<endl;
		fNbins[eov]	=nbins;
		fXMax[eov]	=xmax;
		fXMin[eov]	=xmin;
}

void NtagOtherVarHists::setHistNamePostFix(string pf)
{
	fPostFix=pf;
}


void NtagOtherVarHists::initializeHists()
{
	string sn	="";
	for(int i=0; i<NtagCat::N_NTAG_CAT; i++)
	{

		for(int j=0; j<NtagOtherVars::N_OTHER_VARS; j++)
		{
			sn="";
			if( fPostFix!="" ){ sn=fDefName[i][j] + "_" + fPostFix; }
			else			  { sn=fDefName[i][j]; }

			// Use variable width binning for rec. npist
			// and mct npdist as default
			if( !fBinningFlag					&&
				(j==NtagOtherVars::enpdist_PS		||
				 j==NtagOtherVars::enpdist_NN		||
				 j==NtagOtherVars::emctnpdist_PS	||
				 j==NtagOtherVars::emctnpdist_NN)
			  )
			{
				// rec. travel distance
				if( j==NtagOtherVars::enpdist_PS ||
					j==NtagOtherVars::enpdist_NN 
				  )
				{
					fhOthVars[i][j]=
						new TH1D(sn.c_str(), "",
									NtagOtherVars::N_BINS_RECNPD,
										NtagOtherVars::B_EDGES_RECNPD);

					//fhOthVars[i][j]=
					//	new TH1D(sn.c_str(), "",
					//				20000, 0.0, 3500.0);

				}
				else
				{
					fhOthVars[i][j]=
						new TH1D(sn.c_str(), "",
									NtagOtherVars::N_BINS_MCTNPD,
										NtagOtherVars::B_EDGES_MCTNPD);
				}
			}
			else
			{
				fhOthVars[i][j]=
						new TH1D(sn.c_str(), "",
									fNbins[j], fXMin[j], fXMax[j]);
			}
			fhOthVars[i][j]->Sumw2();
		}

		// Do not instanciate histograms related to 
		// Am/Be calib.
		if( i==NtagOtherVars::emctdt0_NN &&
			!fAmBeFlag )
		{
			break;
		}
	}
}


void NtagOtherVarHists::fillHists(float cont,
							   	  enum NtagCat::E_NTAG_CAT eNC,
								  int ivar,
							   	  float wgt)
{
		//if( ivar==6 && eNC==NtagCat::eMCN ){ std::cout<<" npdist ps:" << cont <<std::endl; }
	if(	NtagOtherVars::TYPEDEF[ivar]==(string)typeid(int).name() )
	{
		fhOthVars[ eNC ][ ivar ]->Fill((int)cont, wgt);
	}
	else
	{
		fhOthVars[ eNC ][ ivar ]->Fill(cont, wgt);
	}
}


void NtagOtherVarHists::normalizeHistsByArea()
{
	double norm=-9999.9;
	for(int i=0; i<NtagCat::N_NTAG_CAT; i++)
	{
		for(int j=0; j<NtagOtherVars::N_OTHER_VARS; j++)
		{
			if( fhOthVars[i][j]!=NULL )
			{
				norm=-9999.9;
				norm=fhOthVars[i][j]->Integral();
				fhOthVars[i][j]->Scale( 1./norm );
			}
		}
	}
}


void NtagOtherVarHists::normalizeHists(double fac)
{
	for(int i=0; i<NtagCat::N_NTAG_CAT; i++)
	{
		for(int j=0; j<NtagOtherVars::N_OTHER_VARS; j++)
		{
			if( fhOthVars[i][j]!=NULL )
			{
				fhOthVars[i][j]->Scale( fac );

				//double bf=fhOthVars[i][j]->Integral();
				//fhOthVars[i][j]->Scale( fac );
				//double af=fhOthVars[i][j]->Integral();
				//cout<<" Normalize " << NtagCat::S_NTAG_CAT[i]
				//	<<" - " << NtagOtherVars::S_OTHER_VARS[j]
				//	<<" - bf:" << bf 
				//	<<" - af:" << af
				//	<<endl;
			}
		}
	}
	//exit(-1);
}


TH1D* NtagOtherVarHists::getHist(int icat, int ivar)
{
	enum NtagOtherVars::E_OTHER_VARS eiv=
			NtagOtherVars::int2enum(ivar);
	enum NtagCat::E_NTAG_CAT enc=
			NtagCat::int2enum(icat);
	return this->getHist(enc, eiv);
}


TH1D* NtagOtherVarHists::getHist(enum NtagCat::E_NTAG_CAT enc,
								 enum NtagOtherVars::E_OTHER_VARS eiv)
{
	return (TH1D*)fhOthVars[enc][eiv]->Clone(fDefName[enc][eiv].c_str());
}


bool NtagOtherVarHists::operator+=(const NtagOtherVarHists& h) const
{
	for(int i=0; i<NtagCat::N_NTAG_CAT; i++)
	{
		for(int j=0; j<NtagOtherVars::N_OTHER_VARS; j++)
		{
			if( fhOthVars[i][j]!=NULL && h.fhOthVars[i][j]!=NULL )
			{
				fhOthVars[i][j]->Add( (TH1D*)h.fhOthVars[i][j]->Clone() );
			}
		}
	}
	return true;
}


void NtagOtherVarHists::loadHists(TDirectory *td)
{
	cout<<" [INFO] NtagOtherVarHists::loadHists " <<endl;
	cout<<"   - Trying to load histograms from TDirectory "
		<<td->GetName() <<endl;

	TKey *tk=NULL;
	TIter titr(td->GetListOfKeys());
	while( tk=(TKey*)titr() )
	{
		if( string(tk->GetClassName())!="TH1D" ){ continue; }
		string shn( tk->GetName() );

		for(int i=0; i<NtagCat::N_NTAG_CAT; i++)
		{
			if( shn.find( NtagCat::S_NTAG_CAT[i] )!=string::npos )
			{
				for(int j=0; j<NtagOtherVars::N_OTHER_VARS; j++)
				{
					if( shn.find( "h" + NtagOtherVars::S_OTHER_VARS[j] + "_" )!=string::npos )
					{
						cout<<"     - Found " << NtagCat::S_NTAG_CAT[i] 
							<<" - "			  << NtagOtherVars::S_OTHER_VARS[j]
							<<endl;

						fhOthVars[i][j]=(TH1D*)tk->ReadObj();
						fhOthVars[i][j]->SetDirectory(0);
						break;
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

void NtagOtherVarHists::setCoarserBinning(const bool flg)
{
	fIsCoarser=flg;
	if( fIsCoarser )
	{
		cout<<" [INFO] NtagOtherVarHists::setCoarserBinning " <<endl;
		cout<<"   - Using coarser binning "<<endl;
		this->setConstants();
	}
}
