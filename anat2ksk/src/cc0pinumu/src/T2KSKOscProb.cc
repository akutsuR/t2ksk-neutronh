#include "T2KSKOscProb.h"

T2KSKOscProb::T2KSKOscProb() :
fIsSet( false ),
fIsSinSQ( true )
{
	this->setDefaultT2KPars();
}

T2KSKOscProb::T2KSKOscProb(enum OscChan::E_OSC_CHAN eoc) :
fIsSet( false ),
fIsSinSQ( true )
{
	this->setOscChannel(eoc);
	this->setDefaultT2KPars();
}


void T2KSKOscProb::setOscChannel(enum OscChan::E_OSC_CHAN eoc)
{
	feOC=eoc;
	switch ( feOC )
	{
		case OscChan::eNUMU :
			fEi=BargerIdx::eNUMU;	fEo=BargerIdx::eNUMU;	fPDG=Const::PDG_NUMU;
			break;

		case OscChan::eNUESIG :
			fEi=BargerIdx::eNUMU;	fEo=BargerIdx::eNUE;	fPDG=Const::PDG_NUE;
			break;

		case OscChan::eNUE :
			fEi=BargerIdx::eNUE;	fEo=BargerIdx::eNUE;	fPDG=Const::PDG_NUE;
			break;

		case OscChan::eNUMUBAR :
			fEi=-BargerIdx::eNUMU;	fEo=-BargerIdx::eNUMU;	fPDG=Const::PDG_NUMUBAR;
			break;

		case OscChan::eNUEBARSIG :
			fEi=-BargerIdx::eNUMU;	fEo=-BargerIdx::eNUE;	fPDG=Const::PDG_NUEBAR;
			break;

		case OscChan::eNUEBAR :
			fEi=-BargerIdx::eNUE;	fEo=-BargerIdx::eNUE;	fPDG=Const::PDG_NUEBAR;
			break;
	}
	fIsSet=true;
}


void T2KSKOscProb::setDefaultT2KPars()
{
	fS12     	=Const::S12;
	fS13     	=Const::S13;
	fS23     	=Const::S23;
	fM21     	=Const::M12;
	fM32     	=Const::M23;
	fdCP     	=Const::Dcp;
	fEDen    	=Const::eDen;
	fBaseLine	=Const::BaseLine;

	cout<<" [INFO] T2KSKOscProb::setDefaultT2KPars	   "<<endl;
	cout<<"   set parameters used for osc. probability "<<endl;
	cout<<"   - sin^2( th_12 ) :" << fS12		<<endl;
	cout<<"   - sin^2( th_13 ) :" << fS13		<<endl;
	cout<<"   - sin^2( th_23 ) :" << fS23		<<endl;
	cout<<"   - dm2_21         :" << fM21		<<endl;
	cout<<"   - dm2_32         :" << fM32		<<endl;
	cout<<"   - delta CP       :" << fdCP		<<endl;
	cout<<"   - e- density     :" << fEDen		<<endl;
	cout<<"   - Base line      :" << fBaseLine	<<endl;
	cout<<endl;
}	


float T2KSKOscProb::getOscProb(bool iscc,
							 double Etrue,
							 double ssq12,
							 double ssq13,
							 double ssq23,
							 double dm2_21,
							 double dm2_32,
							 double dCP,
							 bool isVac)
{
	// Neutral Current events
	if( !iscc )
	{
		if( feOC==OscChan::eNUESIG		||
			feOC==OscChan::eNUEBARSIG )
		{
			return 0.0; 
		}
		else
		{
			return 1.0;
		}
	}


	this->SetMNS(ssq12,
				 ssq13,
				 ssq23,
				 dm2_21,
				 dm2_32,
				 dCP,
				 Etrue,
				 fIsSinSQ,
				 fPDG);
	this->propagateLinear(fPDG,
						  fBaseLine,
						  fEDen);

	float prob=(float)this->GetProb(fEi, fEo);
	if( isVac ){ prob=(float)this->GetVacuumProb(fEi, fEo, Etrue, fBaseLine); }


	//return (float)this->GetProb(fEi, fEo);
	return prob;
}


float T2KSKOscProb::getOscProb(bool iscc,
							 double Etrue,
							 bool isVac)
{
	float w=this->getOscProb(iscc,
							 Etrue,
							 fS12,
							 fS13,
							 fS23,
							 fM21,
							 fM32,
							 fdCP,
							 isVac);
	return w;
}
