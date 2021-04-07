#include "CmdLineArgParser.h"

CmdLineArgParser::CmdLineArgParser()
{
	fInfQMR		="";
	fInRege		="";
	fInNtag		="";
	fInXSecWgt	="";
	fInPiFSISI	="";
	fInAltMCInfo="";
	fOutFile	="";
	
	fBeamMode	=BeamMode::eNONE;
	fOscChan	=OscChan::eNONE;
	fGenType	=GenType::eNEUT;

	fRandSeed	=-9999;

	fIsFCFVOnly	=false;
}


bool CmdLineArgParser::parse(int argc, char **argv)
{
	for(int i=1; i<argc; i++)
	{
		cout<<" argv[" << i <<"] :" <<argv[i] <<endl;
	}
	cout<<endl;

	for(int i=1; i<argc; i++)
	{
		if( string(argv[i])=="-if" )			{ fInfQMR		=string( argv[i+1] );	i++;}
		else if( string(argv[i])=="-ir" )		{ fInRege		=string( argv[i+1] );	i++;}
		else if( string(argv[i])=="-in" )		{ fInNtag		=string( argv[i+1] );	i++;}
		else if( string(argv[i])=="-ix" )		{ fInXSecWgt	=string( argv[i+1] );	i++;}
		else if( string(argv[i])=="-ip" )		{ fInPiFSISI	=string( argv[i+1] );	i++;}
		else if( string(argv[i])=="-ie" )		{ fInAltMCInfo	=string( argv[i+1] );	i++;}
		else if( string(argv[i])=="-m" )		{ fBeamMode		=BeamMode::chr2enum(argv[i+1]);	i++;}
		else if( string(argv[i])=="-c" )		{ fOscChan		=OscChan::chr2enum(argv[i+1]);	i++;}
		else if( string(argv[i])=="-o" )		{ fOutFile		=string( argv[i+1] ); i++;}
		else if( string(argv[i])=="--rand" )	{ fRandSeed		=atoi( argv[i+1] );	i++; }
		else if( string(argv[i])=="--FCFVonly" ){ fIsFCFVOnly	=atoi( argv[i+1] );	i++; }
		else if( string(argv[i])=="--altmc" )	{ fGenType		=GenType::chr2enum(argv[i+1]);	i++;}
		else
		{
			return false;
		}
	}
	return true;
}
