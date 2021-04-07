#include "DefOscChannels.h"

enum OscChan::E_OSC_CHAN OscChan::getOscChan(std::string oscchan)
{
	enum OscChan::E_OSC_CHAN eoc=eNONE;
	if( oscchan=="numu_x_numu" )				eoc=OscChan::eNUMU;
	else if( oscchan=="numu_x_nue" )			eoc=OscChan::eNUESIG;
	else if( oscchan=="nue_x_nue" )				eoc=OscChan::eNUE;
	else if( oscchan=="numubar_x_numubar" )		eoc=OscChan::eNUMUBAR;
	else if( oscchan=="numubar_x_nuebar"  )		eoc=OscChan::eNUEBARSIG;
	else if( oscchan=="nuebar_x_nuebar" )		eoc=OscChan::eNUEBAR;
	else if( oscchan=="data" )					eoc=OscChan::eDATA;
	else
	{
		std::cerr<< " [ERROR] OscChan::getOscChan " <<std::endl;
		std::cerr<< "   - " 						<< oscchan
				 << " is not supported. " 			<<std::endl;
		std::cerr<< " -> EXIT " 					<<std::endl;
		exit( -1 );
	}
	return eoc;
}


enum OscChan::E_OSC_CHAN OscChan::chr2enum(char* oc)
{
	std::string st( oc );
	return OscChan::getOscChan( st );
}


enum OscChan::E_OSC_CHAN OscChan::int2enum(int ioc)
{
	if( ioc==OscChan::eNUMU )		{ return OscChan::eNUMU; }
	if( ioc==OscChan::eNUESIG )		{ return OscChan::eNUESIG; }
	if( ioc==OscChan::eNUE )		{ return OscChan::eNUE; }
	if( ioc==OscChan::eNUMUBAR )	{ return OscChan::eNUMUBAR; }
	if( ioc==OscChan::eNUEBARSIG )	{ return OscChan::eNUEBARSIG; }
	if( ioc==OscChan::eNUEBAR )		{ return OscChan::eNUEBAR; }
	if( ioc==OscChan::eDATA )		{ return OscChan::eDATA; }

	std::cerr<< " [ERROR] OscChan::int2enum "   <<std::endl;
	std::cerr<< "   - " 						<< ioc
			 << " is not supported. " 			<<std::endl;
	std::cerr<< " -> EXIT " 					<<std::endl;
	exit( -1 );

	return OscChan::eNONE;
}
