#include "DefNtagOtherVars.h"

enum NtagOtherVars::E_OTHER_VARS NtagOtherVars::int2enum(int ivar)
{
	if( ivar<NtagOtherVars::eNP			||
		ivar>NtagOtherVars::enangInf_NN )
	{
		cout<<" [ERROR] NtagOtherVars::int2enum"		  <<endl;
		cout<<"  - ivar :" << ivar <<" is not supported." <<endl;
		cout<<" -> EXIT " 								  <<endl;
		exit(-1);
	}

	NtagOtherVars::E_OTHER_VARS eiv=
		static_cast<NtagOtherVars::E_OTHER_VARS>(ivar);

	return eiv;
}
