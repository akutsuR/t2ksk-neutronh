#include "DefGenType.h"

namespace GenType
{
	enum E_GEN_TYP chr2enum(char *gt)
	{
		E_GEN_TYP egt=eNONE;
		if( std::string( gt )==S_GEN_TYP[eNEUT] )	{ egt=eNEUT; }
		if( std::string( gt )==S_GEN_TYP[eNuWro] )	{ egt=eNuWro; }
		if( std::string( gt )==S_GEN_TYP[eGENIE] )	{ egt=eGENIE; }

		if( egt==eNONE )
		{
				std::cout<<" [ERROR] GenType::chr2enum " 					<<std::endl;
				std::cout<<"    - Invalid argument :" << std::string( gt ) 	<<std::endl;
				std::cout<<" -> EXIT "										<<std::endl;
				exit( -1 );
		}
		return egt;
	}
};
