#include "DefNuNubarBreakDown.h"

enum NuNubarBrkDwn::E_BKDN_COMP 
NuNubarBrkDwn::getNuNubarBrkDwn(enum OscChan::E_OSC_CHAN eoc,
								enum IntCat::E_INT_CAT eic)
{
	NuNubarBrkDwn::E_BKDN_COMP ebc=NuNubarBrkDwn::eNONE;

	if( eoc==OscChan::eNUMU		||
		eoc==OscChan::eNUE		||
		eoc==OscChan::eNUESIG )
	{
		return NuNubarBrkDwn::eNU;
	}
	else
	{
		return NuNubarBrkDwn::eNUBAR;
	}

	return ebc;
}


enum NuNubarBrkDwn::E_BKDN_COMP 
NuNubarBrkDwn::getNuNubarBrkDwn(int ioc, int iic)
{
	enum OscChan::E_OSC_CHAN eoc=OscChan::int2enum( ioc );
	enum IntCat::E_INT_CAT   eic=IntCat::int2enum( iic );

	return NuNubarBrkDwn::getNuNubarBrkDwn(eoc, eic);
}
