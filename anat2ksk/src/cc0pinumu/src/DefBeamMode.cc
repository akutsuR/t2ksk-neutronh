#include "DefBeamMode.h"

enum BeamMode::E_BEAM_MODE BeamMode::chr2enum(char* cbm)
{
	std::string sbm( cbm );
	if( sbm=="fhc" )	 { return BeamMode::eFHC; }
	else if( sbm=="rhc" ){ return BeamMode::eRHC; }
	else
	{
		std::cerr<< " [ERROR] BeamMod::chr2enum " <<std::endl;
		std::cerr<< "   - " 					  << sbm
				 << " is not supported. " 		  <<std::endl;
		std::cerr<< " -> EXIT " 				  <<std::endl;
		exit( -1 );
	}
	return eNONE;
}
