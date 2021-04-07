#include "DefNtagCategory.h"

enum NtagCat::E_NTAG_CAT NtagCat::getNTagCat(int cat)
{
	enum NtagCat::E_NTAG_CAT eNC=NtagCat::eNONE;
	if( cat==0 )	 { eNC=NtagCat::eMCN; }
	else if( cat==1 ){ eNC=NtagCat::eBKG; }
	else if( cat==2 ){ eNC=NtagCat::eALL; }
	return eNC;
}

enum NtagCat::E_NTAG_CAT NtagCat::int2enum(int cat)
{
	return getNTagCat(cat);
}
