#include "NeutronCount.h"

int main(int argc, char **argv)
{
	// Check command line arguments
	CmdLineArgParser ap;
	if( !ap.parse(argc, argv) )
	{
		cout<<" Invalid Command line arguments " <<endl;
		cout<<" -> EXIT"						 <<endl;
		exit( -1 );
	}

	// Inputs are NEUT based MC or DATA
	if( ap.fGenType==GenType::eNEUT ||
		ap.fOscChan==OscChan::eDATA )
	{
		NominalDist *nd=new NominalDist( ap );	
		nd->initialize();
		nd->loopEvents();	
		nd->normalize();
		nd->writeOutputs();
		delete nd;
	}
	

	// Inputs are NuWro or GENIE based MC
	if( ap.fGenType==GenType::eNuWro ||
		ap.fGenType==GenType::eGENIE )
	{
		AltMCDist *nd=new AltMCDist( ap );	
		nd->initialize();
		nd->loopEvents();	
		nd->normalize();
		nd->writeOutputs();
		delete nd;
	}

return 0;
}
