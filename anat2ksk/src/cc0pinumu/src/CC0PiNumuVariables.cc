#include "CC0PiNumuVariables.h"

CC0PiNumuVariables::CC0PiNumuVariables(BeamMode::E_BEAM_MODE ebm) :
feBM( ebm )
{
	this->setErecMass();
	this->setVarList();
}

template <typename T> T CC0PiNumuVariables::var(string var) const
{
	T t;
	if(	     var=="fqevis" )	{ t=fEvis; }
	else if( var=="fqmomm" )	{ t=fMom; }
	else if( var=="fqdcye" )	{ t=fDcye; }
	else if( var=="fqdwall" )	{ t=fDwall; }
	else if( var=="fqposr2" )	{ t=fPosR2; }
	else if( var=="fqposz" )	{ t=fPosZ; }
	else if( var=="cosbm" )		{ t=fCosRec; }
	else if( var=="erec" )		{ t=fErec; }
	else if( var=="momtr" )		{ t=fPtRec; }
	else if( var=="Q2rec" )		{ t=fQ2Rec; }
	else if( var=="pidemu" )	{ t=fPidEMu; }
	else if( var=="pidcpimu" )	{ t=fPidCPiMu; }
	else						{ printError( var ); }
	return t;
}


template <typename T> T CC0PiNumuVariables::var(string var, int i) const
{
	T t;
	if(	     var=="fqpos" )		{ t=fVtx[i]; }
	else if( var=="fqdir" )		{ t=fDir[i]; }
	else if( var=="ninfdir" )	{ t=fInfNDir[i]; }
	else if( var=="beamdir" )	{ t=beamDir[i]; }
	else						{ printError( var ); }
	return t;
}

template int CC0PiNumuVariables::var<int>(string) const;
template float CC0PiNumuVariables::var<float>(string) const;
template float CC0PiNumuVariables::var<float>(string, int) const;


void CC0PiNumuVariables::setVarList()
{
	fVarList.clear();
	fVarList.push_back("fqevis");
	fVarList.push_back("fqmomm");
	fVarList.push_back("fqdcye");
	fVarList.push_back("fqdwall");
	fVarList.push_back("fqposr2");
	fVarList.push_back("fqposz");
	fVarList.push_back("cosbm");
	fVarList.push_back("erec");
	fVarList.push_back("momtr");
	fVarList.push_back("Q2rec");
	fVarList.push_back("pidemu");
	fVarList.push_back("pidcpimu");
	fVarList.push_back("fqpos");
	fVarList.push_back("fqdir");
	fVarList.push_back("ninfdir");
	fVarList.push_back("beamdir");

	cout<<" [INFO] CC0PiNumuVariables::setVarList " <<endl;
	cout<<"   Currently available variables are... " <<endl;
	for(int i=0; i<(int)fVarList.size(); i++)
	{
		cout<<"       - " << fVarList[i] <<endl;
	}
	cout<<endl;
}


bool CC0PiNumuVariables::isSupported(string var)
{
	bool tmp=false;
	for(int i=0; i<(int)fVarList.size(); i++)
	{
		if( var==fVarList[i] )
		{
			tmp=true;
			break;
		}
	}
	return tmp;
}


void CC0PiNumuVariables::printError(string var) const
{
	cout<<" [ERROR] CC0PiNumuVariables::var" 		  <<endl;
	cout<<"    - var :" << var << " is not supported" <<endl;
	cout<<" -> EXIT"								  <<endl;
	exit( -1 );
}
	

void CC0PiNumuVariables::computeVariables(const SKh1Variables h1)
{
	for(int i=0; i<3; i++)
	{
		fVtx[i]=h1.var<float>("fq1rpos", 0, fQ_IDX_MU, i);
		fDir[i]=h1.var<float>("fq1rdir", 0, fQ_IDX_MU, i);
	}
	fPosR2	=computePosR2(fVtx);
	fPosZ	=h1.var<float>("fq1rpos", 0, fQ_IDX_MU, 2);
	fDwall	=computeDwall(fVtx);

	fEvis	=h1.var<float>("fq1rmom", 0, fQ_IDX_E);
	fMom	=h1.var<float>("fq1rmom", 0, fQ_IDX_MU);
	fDcye	=h1.var<int>("fqnse") -1; // # sub evts -> # dcye

	// 1R e-mu PID
	float nllr=0.0;
	nllr  =h1.var<float>("fq1rnll", 0, fQ_IDX_MU);
	nllr -=h1.var<float>("fq1rnll", 0, fQ_IDX_E);
	fPidEMu	=computeSignDist(true, fEvis, nllr );

	// 1R charged pi - mu PID
	nllr=0.0;
	nllr  =h1.var<float>("fq1rnll", 0, fQ_IDX_MU);
	nllr -=h1.var<float>("fq1rnll", 0, fQ_IDX_CPI);
	fPidCPiMu=computeSignDist(false, fMom, nllr);

	// Have to call computeCosRec first
	fCosRec =computeCosRec(fDir);
	fErec	=computeErec(fMom, fCosRec);
	fPtRec	=computePtRec(fMom, fCosRec);
	fQ2Rec	=computeQ2Rec(fErec, fMom, fDir);

	// Have to call after computing Erec
	this->computeNeutronInferredDirection();	
}



float CC0PiNumuVariables::computePosR2(const float *vtx)
{
	return vtx[0]*vtx[0] + vtx[1]*vtx[1];
}


float CC0PiNumuVariables::computeDwall(const float *vtx)
{
	float rho	=TMath::Sqrt(vtx[0]*vtx[0] + vtx[1]*vtx[1]);
	float dR	=tankR - rho;

	float dZ=99999.;
	if( vtx[2]>0. ){ dZ=tankZ   - vtx[2]; }
	else		   { dZ=vtx[2] + tankZ; }

	float dwl=-9999.0;
	if( dR<dZ ){ dwl=dR; }
	else	   { dwl=dZ; }

	return dwl;
}


float CC0PiNumuVariables::computeCosRec(const float* dir)
{
	float cos=0.;
	for(int i=0; i<3; i++){ cos+=beamDir[i]*dir[i]; }
	return cos;
}


float CC0PiNumuVariables::computeErec(const float pl, const float cosbm)
{
	float El  =TMath::Sqrt( pl*pl + Mmu*Mmu );
	float Erec=0.;
	Erec += (fMNi - Eb)*El - Mmu2/2.;
	Erec += fMNi*Eb - Eb2/2.;
	Erec += (fMNf2 - fMNi2)/2.;
	Erec /= (fMNi - Eb - El + pl*cosbm);

	return Erec;
}


float CC0PiNumuVariables::computeSignDist(const bool is_emu, 
									 	  const float x,
									 	  const float y)
{
	float	a=-9999.,
			b=-9999.,
			c=-9999.,
			sqa2b2=0.,
			d=0.;
	if( is_emu ){	a=0.2;	b=1.;	c=0.;	}
	else		{	a=0.15;	b=1.;	c=0.;	}

	sqa2b2=TMath::Sqrt( a*a + b*b );
	d=TMath::Abs( a*x + b*y + c ) / sqa2b2;
	if( y>a*x ){ d=-1.0*d; }

	if( !is_emu ){ d=-1.0*d; }	// T2K convention?
	return d;	
}


float CC0PiNumuVariables::computePtRec(const float pl, const float cosbm)
{
	return pl*TMath::Sqrt(1. - cosbm*cosbm);
}


float CC0PiNumuVariables::computeQ2Rec(const float Erec, 
									   const float pl,
									   const float *dir)
{
	float dE2	=0.0,
		  dP2	=0.0,
		  El	=0.0,
		  Pnu[3]={},
		  Pl[3]	={},
		  q2	=0.0;

	El=TMath::Sqrt( pl*pl + Mmu*Mmu );
	dE2=(Erec - El)*(Erec - El );

	for(int i=0; i<3; i++ )
	{
		Pnu[i]	=Erec*beamDir[i];
		Pl[i]	=pl*dir[ i ];
		dP2		+=(Pnu[i] - Pl[i])*(Pnu[i] - Pl[i]);
	}
	q2=dE2 - dP2;
	return -q2;
}


void CC0PiNumuVariables::computeNeutronInferredDirection()
{
	float nuMomCCQE[3]	={0.0};
	float lepMom[3]		={0.0};
	float norm			=0.0;
	for(int i=0; i<3; i++)
	{ 
		nuMomCCQE[i]	=fErec*beamDir[i];
		lepMom[i]		=fMom*fDir[i];
		fInfNDir[i]		=nuMomCCQE[i] - lepMom[i];
		norm		   +=fInfNDir[i]*fInfNDir[i];
	}

	norm=TMath::Sqrt( norm );
	for(int i=0; i<3; i++){ fInfNDir[i] /=norm; }
}


void CC0PiNumuVariables::setErecMass()
{
	if( feBM==BeamMode::eFHC )
	{
		fMNi	=Const::Mn;
		fMNf	=Const::Mp;
	}
	else
	{
		fMNi	=Const::Mp;
		fMNf	=Const::Mn;
	}
	fMNi2	=fMNi*fMNi;
	fMNf2	=fMNf*fMNf;
}
