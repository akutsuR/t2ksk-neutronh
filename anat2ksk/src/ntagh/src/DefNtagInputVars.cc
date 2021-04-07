#include "DefNtagInputVars.h"

enum NtagInputVars::E_INPUT_VARS NtagInputVars::int2enum(int ivar)
{
	if( ivar<NtagInputVars::eN10n 	||
		ivar>NtagInputVars::etSDMin6 )
	{
		cout<<" [ERROR] NtagInputVars::int2enum"		  <<endl;
		cout<<"  - ivar :" << ivar <<" is not supported." <<endl;
		cout<<" -> EXIT " 								  <<endl;
		exit(-1);
	}

	NtagInputVars::E_INPUT_VARS eiv=
		static_cast<NtagInputVars::E_INPUT_VARS>(ivar);

	return eiv;
}
