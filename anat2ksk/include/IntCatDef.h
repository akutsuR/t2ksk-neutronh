#pragma once

#include <string>
#include <iostream>
#include <cstdlib>

namespace IntCat{

	const int 			N_INT_CAT=10;
	
	enum				E_INT_CAT{ eCC_1P1H=0,
								   eCC_2P2H,
								   eCC_RES,
								   eCC_DIS,
								   eCC_COH,
								   eNC_1P1H,
								   eNC_RES,
								   eNC_DIS,
								   eNC_COH,
								   eNC_NUEL
								 };
	
	const std::string	S_INT_CAT[ N_INT_CAT ]={"cc_1p1h",
												"cc_2p2h",
												"cc_res",
												"cc_dis",
												"cc_coh",
												"nc_1p1h",
												"nc_res",
												"nc_dis",
												"nc_coh",
												"nc_nuel"
											    };
	
	
	enum E_INT_CAT getInt2IntCat(int i)
	{
		if( i<eCC_1P1H ||
			i>eNC_NUEL
		  )
		{
			std::cout<<" enum IntCat::E_INT_CAT"	   	<<
					   " IntCat::getInt2IntCat(int i) "	<<
					   " - i:" 							<< i <<
					   " is not supported " 			<<
					   " -> EXIT "						<<std::endl; 
			exit( -1 );
		}
	
		enum E_INT_CAT eic;
	
		switch (i)
		{
			case 0:
				eic=eCC_1P1H;	break;
			case 1:
				eic=eCC_2P2H;	break;
			case 2:
				eic=eCC_RES;	break;
			case 3:
				eic=eCC_DIS;	break;
			case 4:
				eic=eCC_COH;	break;
			case 5:
				eic=eNC_1P1H;	break;
			case 6:
				eic=eNC_RES;	break;
			case 7:
				eic=eNC_DIS;	break;
			case 8:
				eic=eNC_COH;	break;
			case 9:
				eic=eNC_NUEL;	break;
		}
		return eic;
	}

}


