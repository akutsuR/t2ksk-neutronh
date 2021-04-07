#include "DefIntCat.h"

enum IntCat::E_INT_CAT IntCat::getNeutMode2IntCat(int m)
{
	int am=-1,
		icat=-1;
	am=TMath::Abs( m );

	if( am==1 )			
	{	
		return IntCat::eCC_1P1H;
	}
	else if( am==2 )
	{	
		return IntCat::eCC_2P2H;
	}
	else if( am==11 ||
			 am==12	||
			 am==13 ||
			 am==17 ||
			 am==21 ||
			 am==22	||
			 am==23
		   )
	{
		return IntCat::eCC_RES;
	}
	else if( am==26 )
	{
		return IntCat::eCC_DIS;
	}
	else if( am==16 )
	{
		return IntCat::eCC_COH;
	}
	else if( am==51 ||
			 am==52
		   )
	{
		return IntCat::eNC_1P1H;
	}
	else if( am==31	||
			 am==32 ||
			 am==33 ||
			 am==34 ||
			 am==38 ||
			 am==39 ||
			 am==41 ||
			 am==42 ||
			 am==43 ||
			 am==44 ||
			 am==45
			)
	{
		return IntCat::eNC_RES;
	}
	else if( am==46 )
	{
		return IntCat::eNC_DIS;
	}
	else if( am==36 )
	{
		return IntCat::eNC_COH;
	}


	if( icat==-1 )
	{
		std::cout<<" [ERROR]  IntCat::getNeutMode2IntCat "	<<std::endl;
		std::cout<<"   " << m << " is not supported."		<<std::endl;
		std::cout<<" -> EXIT "								<<std::endl;
		exit( -1 );
	}
	return IntCat::eNONE;
}


enum IntCat::E_INT_CAT IntCat::int2enum(int i)
{
	if( i==IntCat::eCC_1P1H )	{ return IntCat::eCC_1P1H; }
	if( i==IntCat::eCC_2P2H )	{ return IntCat::eCC_2P2H; }
	if( i==IntCat::eCC_RES )	{ return IntCat::eCC_RES; }
	if( i==IntCat::eCC_DIS )	{ return IntCat::eCC_DIS; }
	if( i==IntCat::eCC_COH )	{ return IntCat::eCC_COH; }
	if( i==IntCat::eNC_1P1H )	{ return IntCat::eNC_1P1H; }
	if( i==IntCat::eNC_RES )	{ return IntCat::eNC_RES; }
	if( i==IntCat::eNC_DIS )	{ return IntCat::eNC_DIS; }
	if( i==IntCat::eNC_COH )	{ return IntCat::eNC_COH; }
	if( i==IntCat::eNC_NUEL )	{ return IntCat::eNC_NUEL; }
	if( i==IntCat::eACCBKG )	{ return IntCat::eACCBKG; }
	
	std::cout<<" [ERROR]  IntCat::int2enum "		<<std::endl;
	std::cout<<"   " << i << " is not supported."	<<std::endl;
	std::cout<<" -> EXIT "							<<std::endl;
	exit( -1 );

	return IntCat::eNONE;
}
