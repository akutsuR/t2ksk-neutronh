#pragma once

#include <iostream>
#include <string>
#include <cstdlib>

#include "DefBeamMode.h"
#include "DefOscChannels.h"
#include "DefGenType.h"

using std::cout;
using std::endl;
using std::string;

class CmdLineArgParser
{
	public :
		CmdLineArgParser();
		virtual ~CmdLineArgParser(){};

		bool parse(int, char**);


		string fInfQMR;
		string fInRege;
		string fInNtag;
		string fInXSecWgt;
		string fInPiFSISI;
		string fInAltMCInfo;
		string fOutFile;
	
		enum BeamMode::E_BEAM_MODE fBeamMode;
		enum OscChan::E_OSC_CHAN   fOscChan;
		enum GenType::E_GEN_TYP	   fGenType;

		int fRandSeed;
		bool fIsFCFVOnly;
};
