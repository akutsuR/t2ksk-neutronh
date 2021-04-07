#include "VertexDistributions.h"

VertexDistributions::VertexDistributions(bool iscoarse, string spf) :
fIsCoarse( iscoarse ),
fPostFix( spf )
{
	this->initialize();
	this->initializeVis();
}

//////////////////////////////////////////////
void VertexDistributions::initialize()
{
	string shn="";
	for(int i=0; i<VtxDist::N_VTX_DST; i++)
	{
		// DST for KS-test
		shn="hKSDst" + VtxDist::S_VTX_DST[i];
		if( fPostFix!="" ){ shn=shn + "_" + fPostFix; }
		fhDstKS[i]=new TH1D(shn.c_str(), "", VtxDist::nbinsKS[i],
								VtxDist::xmin[i], VtxDist::xmax[i]);
		fhDstKS[i]->Sumw2();

		// CDF for KS-test
		shn="hKSCdf" + VtxDist::S_VTX_DST[i];
		if( fPostFix!="" ){ shn=shn + "_" + fPostFix; }
		fhCdfKS[i]=new TH1D(shn.c_str(), "", VtxDist::nbinsKS[i],
								VtxDist::xmin[i], VtxDist::xmax[i]);
		fhCdfKS[i]->Sumw2();
	}
}

//////////////////////////////////////////////
void VertexDistributions::initializeVis()
{
	string shn="";
	Int_t nbins=VtxDist::nbinsVIS;
	if( fIsCoarse ){ nbins=VtxDist::nbinsVISC; }

	for(int i=0; i<VtxDist::N_VTX_DST; i++)
	{
		// DST for KS-test
		shn="hVisDst" + VtxDist::S_VTX_DST[i];
		if( fPostFix!="" ){ shn=shn + "_" + fPostFix; }

		// Dwall	
		if( i==VtxDist::eNuevDWALL		|| 
			i==VtxDist::eNtagNNmcnDWALL ||
			i==VtxDist::eNtagNNbkgDWALL	||
			i==VtxDist::eNtagNNDWALL	)
		{
			if( !fIsCoarse )
			{
				fhDstVis[i]=new TH1D(shn.c_str(), "", nbins,
									VtxDist::edgesDwall);
			}
			else
			{
				fhDstVis[i]=new TH1D(shn.c_str(), "", nbins,
									VtxDist::edgesDwallC);
			}
		}

		// R2
		if( i==VtxDist::eNuevR2			|| 
			i==VtxDist::eNtagNNmcnR2 	||
			i==VtxDist::eNtagNNbkgR2	||
			i==VtxDist::eNtagNNR2	)
		{
			fhDstVis[i]=new TH1D(shn.c_str(), "", nbins,
								VtxDist::xminR2, VtxDist::xmaxR2);
		}

		// R2
		if( i==VtxDist::eNuevZ		|| 
			i==VtxDist::eNtagNNmcnZ ||
			i==VtxDist::eNtagNNbkgZ	||
			i==VtxDist::eNtagNNZ	)
		{
			fhDstVis[i]=new TH1D(shn.c_str(), "", nbins,
								VtxDist::xminZ, VtxDist::xmaxZ);
		}
		fhDstVis[i]->Sumw2();
	}
}

//////////////////////////////////////////////
VertexDistributions::~VertexDistributions()
{
	for(int i=0; i<VtxDist::N_VTX_DST; i++)
	{
		if( !fhDstVis[i] ){ delete fhDstVis[i]; }
		if( !fhDstKS[i] ){ delete fhDstKS[i]; }
		if( !fhCdfKS[i] ){ delete fhDstKS[i]; }
	}
}

//////////////////////////////////////////////
void VertexDistributions::fillDST(int idst, float var, float w)
{
	fhDstKS[idst]->Fill(var, w);
	fhDstVis[idst]->Fill(var, w);
}

//////////////////////////////////////////////
void VertexDistributions::fillDST(const VertexVar_t vv, float w)
{
	this->fillDST(VtxDist::eNuevDWALL, vv.dwlnuev, w);
	this->fillDST(VtxDist::eNuevR2, vv.r2nuev, w);
	this->fillDST(VtxDist::eNuevZ, vv.znuev, w);

	for(int i=0; i<vv.ntot_tag; i++)
	{
		this->fillDST(VtxDist::eNtagNNDWALL, vv.dwlntag[i], w);
		this->fillDST(VtxDist::eNtagNNR2, vv.r2ntag[i], w);
		this->fillDST(VtxDist::eNtagNNZ, vv.zntag[i], w);
	}

	// Only for MC
	for(int i=0; i<vv.nmcn_tag; i++)
	{
		this->fillDST(VtxDist::eNtagNNmcnDWALL, vv.dwlntag_mcn[i], w);
		this->fillDST(VtxDist::eNtagNNmcnR2, vv.r2ntag_mcn[i], w);
		this->fillDST(VtxDist::eNtagNNmcnZ, vv.zntag_mcn[i], w);
	}

	for(int i=0; i<vv.nbkg_tag; i++)
	{
		this->fillDST(VtxDist::eNtagNNbkgDWALL, vv.dwlntag_bkg[i], w);
		this->fillDST(VtxDist::eNtagNNbkgR2, vv.r2ntag_bkg[i], w);
		this->fillDST(VtxDist::eNtagNNbkgZ, vv.zntag_bkg[i], w);
	}
}

//////////////////////////////////////////////
void VertexDistributions::makeCDFsKS()
{
	for(int i=0; i<VtxDist::N_VTX_DST; i++)
	{
		int nbins=fhDstKS[i]->GetNbinsX();
		double cdf=0.0;
		for(int j=0; j<nbins; j++)
		{
			cdf=fhDstKS[i]->Integral(1, j+1);	
			fhCdfKS[i]->SetBinContent(j+1, cdf);
		}	
		double norm=fhDstKS[i]->Integral();
		fhCdfKS[i]->Scale( 1.0/norm );
	}
}

//////////////////////////////////////////////
void VertexDistributions::normalizeDST(double norm)
{
	for(int i=0; i<VtxDist::N_VTX_DST; i++)
	{
		fhDstKS[i]->Scale( norm );
		fhDstVis[i]->Scale( norm );
	}
}

//////////////////////////////////////////////
TH1D* VertexDistributions::getDstVis(int idst)
{
	return (TH1D*)fhDstVis[idst]->Clone();
}

//////////////////////////////////////////////
TH1D* VertexDistributions::getDstKS(int idst)
{
	return (TH1D*)fhDstKS[idst]->Clone();
}

//////////////////////////////////////////////
TH1D* VertexDistributions::getCdfKS(int idst)
{
	return (TH1D*)fhCdfKS[idst]->Clone();
}

//////////////////////////////////////////////
void VertexDistributions::addDST(VertexDistributions *vd)
{
	for(int i=0; i<VtxDist::N_VTX_DST; i++)
	{
		fhDstKS[i]->Add( vd->getDstKS(i) );
		fhDstVis[i]->Add( vd->getDstVis(i) );
	}
}

//////////////////////////////////////////////
void VertexDistributions::loadDST(TDirectory *td)
{
	cout<<" [INFO] VertexDistributions::loadDST " <<endl;
	cout<<"   - Trying to load DST histograms from TDirectory "
		<<td->GetName() <<endl;

	TKey *tk=NULL;
	TIter titr(td->GetListOfKeys());
	while( tk=(TKey*)titr() )
	{
		if( string(tk->GetClassName())!="TH1D" ){ continue; }

		string shn( tk->GetName() );
		for(int i=0; i<VtxDist::N_VTX_DST; i++)
		{
			string shn_comp_1="hKSDst" + VtxDist::S_VTX_DST[i];
			string shn_comp_2="hVisDst" + VtxDist::S_VTX_DST[i];

			if( shn.find( shn_comp_1 )!=string::npos )
			{
				cout<<"     - Found " << shn_comp_1 <<endl;
				fhDstKS[i]=(TH1D*)tk->ReadObj();
				fhDstKS[i]->SetDirectory(0);
				break;
			}
			else if( shn.find( shn_comp_2 )!=string::npos )
			{
				cout<<"     - Found " << shn_comp_2 <<endl;
				fhDstVis[i]=(TH1D*)tk->ReadObj();
				fhDstVis[i]->SetDirectory(0);
				break;
			}
		}					
	}
	cout<<endl;
	td->cd();
}
