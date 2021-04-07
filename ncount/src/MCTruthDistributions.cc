#include "MCTruthDistributions.h"

MCTruthDistributions::MCTruthDistributions(string spf) :
fPostFix( spf )
{
	this->initialize();
}

//////////////////////////////////////////////
void MCTruthDistributions::initialize()
{
	string shn="";
	for(int i=0; i<MCTruth::N_MCT_DST; i++)
	{
		shn="h" + MCTruth::S_MCT_DST[i];
		if( fPostFix!="" ){ shn=shn + "_" + fPostFix; }

		if( i!=MCTruth::eRecoTrMomTrueQ2 )
		{
			fhDst[i]=new TH1D(shn.c_str(), "", MCTruth::nbins[i],
								MCTruth::xmin[i], MCTruth::xmax[i]);
			fhDst[i]->Sumw2();
		}
		else
		{
			int 	ybins=MCTruth::nbinsTrMom;
			int		xbins=MCTruth::nbinsQ2;
			double	ymin=MCTruth::xminTrMom;
			double	xmin=MCTruth::xminQ2;
			double	ymax=MCTruth::xmaxTrMom;
			double	xmax=MCTruth::xmaxQ2;

			fhDst2D=new TH2D(shn.c_str(), "", xbins, xmin, xmax,
										ybins, ymin, ymax);
			fhDst2D->Sumw2();
		}
	}

	fTrMomAxis=new TAxis(TrMomBin::N_TRMOM_BINS, TrMomBin::BinEdges);
	fTrMomAxis->SetName("momAxis");
}

//////////////////////////////////////////////
MCTruthDistributions::~MCTruthDistributions()
{
	for(int i=0; i<MCTruth::N_MCT_DST; i++)
	{

		if( i!=MCTruth::eRecoTrMomTrueQ2 )
		{
			if( !fhDst[i] ){ delete fhDst[i]; fhDst[i]=NULL;}
		}
		else
		{
			if( !fhDst2D ){ delete fhDst2D; fhDst2D=NULL; }
		}
	}
}

//////////////////////////////////////////////
template <typename T> void MCTruthDistributions::fillHist(int idst, T t, float w)
{
	fhDst[idst]->Fill(t, w);
}
template void MCTruthDistributions::fillHist(int, int, float);
template void MCTruthDistributions::fillHist(int, float, float);

//////////////////////////////////////////////
void MCTruthDistributions::fillDST(const MCTruthVar_t mv, float w)
{
	// Post-FSI neutron
	this->fillHist(MCTruth::ePostFSINeuMulti, mv.NneuPostFSI, w);
	for(int i=0; i<mv.NneuPostFSI; i++)
	{
		this->fillHist(MCTruth::ePostFSINeuEkin, mv.neuEkin[i], w);
	}

	// Post-FSI proton
	this->fillHist(MCTruth::ePostFSIProMulti, mv.NproPostFSI, w);
	for(int i=0; i<mv.NproPostFSI; i++)
	{
		this->fillHist(MCTruth::ePostFSIProEkin, mv.proEkin[i], w);
	}

	// Post-FSI pi+
	this->fillHist(MCTruth::ePostFSIPiPMulti, mv.NpipPostFSI, w);
	for(int i=0; i<mv.NpipPostFSI; i++)
	{
		this->fillHist(MCTruth::ePostFSIPiPEkin, mv.pipEkin[i], w);
	}

	// Post-FSI pi-
	this->fillHist(MCTruth::ePostFSIPiMMulti, mv.NpimPostFSI, w);
	for(int i=0; i<mv.NpimPostFSI; i++)
	{
		this->fillHist(MCTruth::ePostFSIPiMEkin, mv.pimEkin[i], w);
	}

	// FSI/SI neutron
	this->fillHist(MCTruth::eFSISINeuMulti, mv.NneuFSISI, w);
	for(int i=0; i<mv.NneuFSISI; i++)
	{
		this->fillHist(MCTruth::eFSISINPDist, mv.npdistFSISI[i], w);
	}

	// Etrue binned by Reco. Tr. momentum
	int bin=fTrMomAxis->FindBin( mv.recotrmom ) -1;
	//cout<<" Trmom:" << mv.recotrmom <<" bin:" << bin <<endl;
	if( mv.recotrmom>fTrMomAxis->GetXmax() ){ bin-=1; }
	this->fillHist(MCTruth::eETrueRecTrMom0p00__0p25+bin, mv.etrue, w);


	// Q2true
	float wtotneu=(float)mv.NneuFSISI*w;
	this->fillHist(MCTruth::eQ2TrueNuEvts, mv.Q2true, w);
	this->fillHist(MCTruth::eQ2TrueTotNeu, mv.Q2true, wtotneu);

	// Reco. TrMom vs True Q2
	//fhDst2D->Fill(mv.Q2true, mv.recotrmom, w);
	fhDst2D->Fill(mv.recotrmom, mv.Q2true, w);
}

//////////////////////////////////////////////
void MCTruthDistributions::normalizeDST(double norm)
{
	for(int i=0; i<MCTruth::N_MCT_DST; i++)
	{
		if( i!=MCTruth::eRecoTrMomTrueQ2 )
		{ 
			fhDst[i]->Scale( norm );
		}
		else
		{
			fhDst2D->Scale(norm);
		}
	}
}

//////////////////////////////////////////////
TH1D* MCTruthDistributions::getDst(int idst)
{
	return (TH1D*)fhDst[idst]->Clone();
}

//////////////////////////////////////////////
TH2D* MCTruthDistributions::getDst2D()
{
	return (TH2D*)fhDst2D->Clone();
}

//////////////////////////////////////////////
void MCTruthDistributions::addDST(MCTruthDistributions *vd)
{
	for(int i=0; i<MCTruth::N_MCT_DST; i++)
	{
		if( i!=MCTruth::eRecoTrMomTrueQ2 )
		{
			fhDst[i]->Add( vd->getDst(i) );
		}
		else
		{
			fhDst2D->Add( vd->getDst2D() );
		}
	}
}

//////////////////////////////////////////////
void MCTruthDistributions::loadDST(TDirectory *td)
{
	cout<<" [INFO] MCTruthDistributions::loadDST " <<endl;
	cout<<"   - Trying to load DST histograms from TDirectory "
		<<td->GetName() <<endl;

	TKey *tk=NULL;
	TIter titr(td->GetListOfKeys());
	while( tk=(TKey*)titr() )
	{
		string cname(tk->GetClassName());
		//if( string(tk->GetClassName())!="TH1D" || 
		if( cname!="TH1D" && cname!="TH2D" ){ continue; }

		string shn( tk->GetName() );
		for(int i=0; i<MCTruth::N_MCT_DST; i++)
		{
			string shn_comp="h" + MCTruth::S_MCT_DST[i];

			if( shn.find( shn_comp )!=string::npos )
			{
				cout<<"     - Found " << shn_comp <<endl;
				if( i!=MCTruth::eRecoTrMomTrueQ2 )
				{
					fhDst[i]=(TH1D*)tk->ReadObj();
					fhDst[i]->SetDirectory(0);
				}
				else
				{
					fhDst2D=(TH2D*)tk->ReadObj();
					fhDst2D->SetDirectory(0);
				}
				break;
			}
		}					
	}
	cout<<endl;
	td->cd();
}
