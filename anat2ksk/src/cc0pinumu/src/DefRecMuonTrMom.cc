#include "DefRecMuonTrMom.h"

namespace TrMomBin
{
	enum E_TRMOM_BINS getTrMomBin(const float trmom /* GeV/c */)
	{
		enum E_TRMOM_BINS etb=TrMomBin::eNONE;

		if( trmom>0.0 && trmom<0.25 )		{ etb=eTrMom0p00__0p25; }
		else if( trmom>=0.25 && trmom<0.5 )	{ etb=eTrMom0p25__0p50; }
		else if( trmom>=0.5 && trmom<0.75 )	{ etb=eTrMom0p50__0p75; }
		else								{ etb=eTrMomGE__0p75; }

		return etb;
	}
};
