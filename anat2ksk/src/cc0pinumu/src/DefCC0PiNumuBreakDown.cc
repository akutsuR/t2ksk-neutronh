#include "DefCC0PiNumuBreakDown.h"

enum CC0PiNumuBrkDwn::E_BKDN_COMP 
CC0PiNumuBrkDwn::getCC0PiNumuBrkDwn(enum OscChan::E_OSC_CHAN eoc,
									enum IntCat::E_INT_CAT eic)
{
	CC0PiNumuBrkDwn::E_BKDN_COMP ebc=CC0PiNumuBrkDwn::eNONE;

	if( eic==IntCat::eACCBKG )			{ return CC0PiNumuBrkDwn::eACCBKG; }

	if( eoc==OscChan::eNUESIG		||
		eoc==OscChan::eNUEBARSIG	)
	{
		return CC0PiNumuBrkDwn::eCC_NUENUEBAR;
	}

	if( eoc==OscChan::eNUE		||
		eoc==OscChan::eNUEBAR	)
	{
		if( eic<=IntCat::eCC_COH )	{ return CC0PiNumuBrkDwn::eCC_NUENUEBAR; }
		else						{ return CC0PiNumuBrkDwn::eNC_NUNUBAR; }
	}

	if( eoc==OscChan::eNUMU )
	{
		if( eic<=IntCat::eCC_2P2H )		{ return CC0PiNumuBrkDwn::eCCQE_NUMU; }
		else if( eic<=IntCat::eCC_COH )	{ return CC0PiNumuBrkDwn::eCCNQ_NUMU; }
		else							{ return CC0PiNumuBrkDwn::eNC_NUNUBAR; }
	}

	if( eoc==OscChan::eNUMUBAR )
	{
		if( eic<=IntCat::eCC_2P2H )		{ return CC0PiNumuBrkDwn::eCCQE_NUMUBAR; }
		else if( eic<=IntCat::eCC_COH )	{ return CC0PiNumuBrkDwn::eCCNQ_NUMUBAR; }
		else							{ return CC0PiNumuBrkDwn::eNC_NUNUBAR; }
	}


	return ebc;
}


enum CC0PiNumuBrkDwn::E_BKDN_COMP 
CC0PiNumuBrkDwn::getCC0PiNumuBrkDwn(int ioc, int iic)
{
	enum OscChan::E_OSC_CHAN eoc=OscChan::int2enum( ioc );
	enum IntCat::E_INT_CAT   eic=IntCat::int2enum( iic );

	return CC0PiNumuBrkDwn::getCC0PiNumuBrkDwn(eoc, eic);
}
