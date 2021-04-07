#include "DefExtraHists.h"

enum ExtraHists::E_EXTRA_HIST ExtraHists::int2enum(int ieh)
{
	if( ieh<ExtraHists::eTrueEnuNuEvts	||
		ieh>ExtraHists::N_EXTRA_HIST-1 )
	{
		std::cout<<" [ERROR] ExtraHists::int2enum"		  		<<std::endl;
		std::cout<<"  - ieh :" << ieh <<" is not supported."	<<std::endl;
		std::cout<<" -> EXIT " 									<<std::endl;
		exit(-1);
	}

	ExtraHists::E_EXTRA_HIST eeh=
		static_cast<ExtraHists::E_EXTRA_HIST>(ieh);

	return eeh;
}
