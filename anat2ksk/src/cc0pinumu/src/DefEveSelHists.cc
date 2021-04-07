#include "DefEvSelHists.h"

enum EvSelHists::E_EVSEL_HIST EvSelHists::int2enum(int ieh)
{
	if( ieh<EvSelHists::eEveSelSum	||
		ieh>EvSelHists::eCPiMuPid )
	{
		std::cout<<" [ERROR] EvSelHists::int2enum"		  		<<std::endl;
		std::cout<<"  - ieh :" << ieh <<" is not supported."	<<std::endl;
		std::cout<<" -> EXIT " 									<<std::endl;
		exit(-1);
	}

	EvSelHists::E_EVSEL_HIST eeh=
		static_cast<EvSelHists::E_EVSEL_HIST>(ieh);

	return eeh;
}
