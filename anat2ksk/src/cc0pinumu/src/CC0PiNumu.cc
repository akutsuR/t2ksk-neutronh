#include "CC0PiNumu.h"

CC0PiNumu::CC0PiNumu(BeamMode::E_BEAM_MODE ebm,
					 OscChan::E_OSC_CHAN eoc,
					 GenType::E_GEN_TYP egt) : 
feBM( ebm ),
feOC( eoc ),
feGT( egt )
{ 
	fh1v	=new SKh1Variables();
	fmuv	=new CC0PiNumuVariables(ebm);
	fpnorm	=new SK10E21POTNorm();
	fflx	=new SKFluxTuning();
	fXSecWgt=NULL;
	fpnorm	->setSKRate10E21POT(egt);
	fflx	->loadFluxTunings();
	this	->setOscChannel( feOC );
};


CC0PiNumu::~CC0PiNumu()
{
	delete fh1v;		fh1v	=NULL;
	delete fmuv;		fmuv	=NULL;
	delete fpnorm;		fpnorm	=NULL;
	if( fXSecWgt!=NULL)
	{
		delete fXSecWgt;	fXSecWgt=NULL;
	}
}


void CC0PiNumu::computeCC0PiVariables()
{
	fmuv->computeVariables(*fh1v);
}


bool CC0PiNumu::applyfQ1RCC0PiNumuCut()
{
	for(int i=0; i<N_EVE_SLC; i++){ fSelec[i]=false; }

	// FCFV
	if( fh1v->var<int>("nhitac")<16		&&
		fh1v->var<int>("evclass")==1	&&
		fmuv->var<float>("fqevis")>30 	&&
		fmuv->var<float>("fqdwall")>200	)
	{
		fSelec[eFCFVDW200]	=true;
	}	

	// 1R
	if( fh1v->var<int>("fqmrnring",0)==1 )
	{
		fSelec[eNRING_EQ_1]	=true;
	}

	// 1R e/mu PID -> mu-like
	if( fmuv->var<float>("pidemu")>0.0 )
	{
		fSelec[eEMUPID_MU]	=true;
	}

	// Pmu>200(MeV)
	if( fmuv->var<float>("fqmomm")>200.0 )
	{
		fSelec[eMUMOM_GE_200]	=true;
	}

	// 	Decay-e <=1
	if( fmuv->var<int>("fqdcye")<=1 )
	{
		fSelec[eDCYE_LE_1]		=true;
	}

	// 1R charged pi/mu -> mu-like
	if( fmuv->var<float>("pidcpimu")<0.0 &&
		fmuv->var<float>("erec")>0.0 )
	{
		fSelec[eCPIMUPID_MU]	=true;
	}

	// This is fQ 1R CC0pi numu event!
    bool pass_1rmu_selec = true;
	for(int i=0; i<N_EVE_SLC; i++)
    {
        if( !fSelec[i] )
        {
            pass_1rmu_selec = false;
            break;
        }
    }
	return pass_1rmu_selec;
}

bool CC0PiNumu::applyfQ1RCC0PiNumuCutExceptForFV()
{
	bool pass=false;
	// FCFV	
		if( fh1v->var<int>("nhitac")<16		&&
			fh1v->var<int>("evclass")==1	&&
			fmuv->var<float>("fqevis")>30 	)
		{
			pass=true;
		}	
		else{ return false; }

	// 1R
		if( fh1v->var<int>("fqmrnring",0)==1 )
		{
			pass=true;
		}
		else{ return false; }

	// 1R e/mu PID -> mu-like
		if( fmuv->var<float>("pidemu")>0.0 )
		{
			pass=true;
		}
		else{ return false; }

	// Pmu>200(MeV)
		if( fmuv->var<float>("fqmomm")>200.0 )
		{
			fSelec[eMUMOM_GE_200]	=true;
		}
		else{ return false; }

	// 	Decay-e <=1
		if( fmuv->var<int>("fqdcye")<=1 )
		{
			pass=true;
		}
		else{ return false; }

	// 1R charged pi/mu -> mu-like
		if( fmuv->var<float>("pidcpimu")<0.0 &&
			fmuv->var<float>("erec")>0.0 )
		{
			pass=true;
		}
		else{ return false; }

	// This is fQ 1R CC0pi numu event!
	// (* FV := dwall>200cm only)
	return true;
}


void CC0PiNumu::setTrueWallEventsAllMC(enum GenType::E_GEN_TYP egt)
{
	fpnorm->setTrueWallEventsAllMC(egt);
}

void CC0PiNumu::setTrueWallEventsLastHalfMC()
{
	fpnorm->setTrueWallEventsLastHalfMC();	
}


float CC0PiNumu::getOscWgt()
{
	bool iscc=false;
	if( TMath::Abs( fh1v->var<int>("mode") )<30 ){ iscc=true; }
	
	return this->getOscProb(iscc, (double)fh1v->var<float>("pnu",0));
}

template <typename T> T CC0PiNumu::var(string var) const
{
	bool ish1=fh1v->isSupported( var );
	bool ismu=fmuv->isSupported( var );
	if( !ish1 && !ismu ){ printError( var ); }

	T t;
	if( std::is_same<T, int>::value )
	{
		if( ish1 ){ t=fh1v->var<int>( var ); }
		else	  { t=fmuv->var<int>( var ); }
	}
	else
	{
		if( ish1 ){ t=fh1v->var<float>( var ); }
		else	  { t=fmuv->var<float>( var ); }
	}
	return t;
}


template <typename T> T CC0PiNumu::var(string var, int i) const
{
	bool ish1=fh1v->isSupported( var );
	bool ismu=fmuv->isSupported( var );
	if( !ish1 && !ismu ){ printError( var ); }

	T t;
	if( std::is_same<T, int>::value )
	{
		if( ish1 ){ t=fh1v->var<int>( var, i ); }
	}
	else
	{
		if( ish1 ){ t=fh1v->var<float>( var, i ); }
		else	  { t=fmuv->var<float>( var, i ); }
	}
	return t;
}


template <typename T> T CC0PiNumu::var(string var, int i, int j) const
{
	bool ish1=fh1v->isSupported( var );
	if( !ish1 ){ printError( var ); }

	T t;
	t=fh1v->var<float>(var, i, j);
	return t;
}


template <typename T> T CC0PiNumu::var(string var, int i, int j, int k) const
{
	bool ish1=fh1v->isSupported( var );
	if( !ish1 ){ printError( var ); }

	T t;
	t=fh1v->var<float>(var, i, j, k);
	return t;
}

template int CC0PiNumu::var<int>(string) const;
template float CC0PiNumu::var<float>(string) const;
template int CC0PiNumu::var<int>(string, int) const;
template float CC0PiNumu::var<float>(string, int) const;
template float CC0PiNumu::var<float>(string, int, int) const;
template float CC0PiNumu::var<float>(string, int, int, int) const;


void CC0PiNumu::printError(string var) const
{
	cout<<" [ERROR] CC0PiNumu::var "					<<endl;
	cout<<"   - " << var <<" is not supported yet. "	<<endl;
	cout<<" -> EXIT "									<<endl;
	exit( -1 );
}


void CC0PiNumu::resisterDefaultAllStacks()
{
	this->resisterDefault("DST");
	this->resisterDefault("T2KREDUC");
	this->resisterDefault("fiTQun");
	this->resisterDefault("VECT");
	this->resisterDefault("NEWORK");
	this->resisterDefault("VCWORK");
	this->resisterDefault("CONVVECT");
}


void CC0PiNumu::resisterDefault(string stk)
{
	if( stk=="DST" )			{ fh1v->resisterDefaultDST(); }
	else if( stk=="T2KREDUC" )	{ fh1v->resisterDefaultT2KREDUC(); }
	else if( stk=="fiTQun" )	{ fh1v->resisterDefaultfiTQun(); }
	else if( stk=="VECT" )		{ fh1v->resisterDefaultVECT(); }
	else if( stk=="NEWORK" )	{ fh1v->resisterDefaultNEWORK(); }
	else if( stk=="VCWORK" )	{ fh1v->resisterDefaultVCWORK(); }
	else if( stk=="CONVVECT" )	{ fh1v->resisterDefaultCONVVECT(); }
	else
	{
		cout<<" [ERROR] CC0PiNumu::resisterDefault "	<<endl;
		cout<<"   " << stk <<" is not supported yet."	<<endl;
		cout<<"   -> EXIT " 							<<endl;
		exit( -1 );
	}
}


EvSelVar_t CC0PiNumu::getEvSelVar()
{
	EvSelVar_t tmp;
	for(int i=0; i<CC0PiNumuCut::N_EVE_SLC; i++)
	{
		tmp.pass[i]=fSelec[i];
	}

	tmp.nring		=fh1v->var<int>("fqmrnring", 0);
	tmp.emupid		=fmuv->var<float>("pidemu");
	tmp.momm		=fmuv->var<float>("fqmomm");
	tmp.dcye		=fmuv->var<int>("fqdcye");
	tmp.cpimupid	=fmuv->var<float>("pidcpimu");

	return tmp;
}

float CC0PiNumu::getFluxWgt(enum E_BEAM_MODE ebm,
							enum E_OSC_CHAN eoc,
							float etrue)
{
	return fflx->getFluxTuning(ebm, eoc, etrue);
}


float CC0PiNumu::getFluxWgt()
{
	float etrue=this->var<float>("pnu", 0);	
	return fflx->getFluxTuning(feBM, feOC, etrue);
}


float CC0PiNumu::get10E21POTNorm(enum E_BEAM_MODE ebm,
								 enum E_OSC_CHAN eos)
{
	return fpnorm->get10E21POTNorm(ebm, eos);
}


float CC0PiNumu::get10E21POTNorm()
{
	return fpnorm->get10E21POTNorm(feBM, feOC);
}


float CC0PiNumu::getCCCohWgt()
{
	int	amode=TMath::Abs( fh1v->var<int>("mode") );
	float	Epi=0.0,	//MeV
			p  =0.0,
	  		weight=1.;
	
	if( amode==16 )	// CCCoh prefit weight
	{     
	  int j	 =0,
		  find =0;
	  while(j<fh1v->var<int>("npar") && find==0)
	  {
		if( fh1v->var<int>("ipv", j)==8 || 
			fh1v->var<int>("ipv", j)==9 )
		{
	      p		=fh1v->var<float>("pmomv", j);
		  Epi	=p*p;
	      Epi	/=2.*139.57;
	      find++;
	    }
	    j++;
	  }
	  if(Epi<250.)		{ weight *= 0.135; }
	  else if(Epi<500.) { weight *= 0.4; }
	  else if(Epi<750.) { weight *= 0.294; }
	  else if(Epi<1000.){ weight *= 1.206; }
	}
	return weight;
}


void CC0PiNumu::setXSecWgtTree(TTree *t)
{
	fXSecWgt=new TArrayF();
	t->SetBranchStatus("nweights", 1);
	t->SetBranchStatus("weights", 1);
	t->SetBranchAddress("nweights", &fNWeights);
	t->SetBranchAddress("weights",  &fXSecWgt);
}

float CC0PiNumu::getXSecWgt(enum WgtXSec::E_XSEC_WGT exw)
{
	return (float)fXSecWgt->At(exw);
}


enum IntCat::E_INT_CAT CC0PiNumu::getIntCat()
{
	return IntCat::getNeutMode2IntCat(fh1v->var<int>("mode"));
}


bool CC0PiNumu::isWrongSignSpill()
{
// Assumed to be used for REAL DATA
// For MC, "false" is alway returned.
//
	if( feOC!=eDATA ){ return false; }
	bool tmp=false;

	if( feBM==eFHC &&
		fh1v->var<int>("good_spill_flag")<0 )
	{
		tmp=true;
	}

	if( feBM==eRHC &&
		fh1v->var<int>("good_spill_flag")>0 )
	{
		tmp=true;
	}
	return tmp;
}
