#include <iostream>
#include <string>
#include <sstream>
#include <fstream>
#include <iomanip>
#include <vector>

#include "TFile.h"
#include "TDirectoryFile.h"
#include "TH1D.h"
#include "TTree.h"
#include "TGraph.h"
#include "TGraphErrors.h"
#include "TGraphAsymmErrors.h"
#include "TMath.h"
#include "TRandom3.h"

#include "DefBeamMode.h"
#include "DefTotSysError.h"

using std::cout;
using std::endl;
using std::string;
using std::stringstream;
using std::vector;

using namespace BeamMode;
using namespace TotSysErr;

///////////////////////////////////////
const double fTail		=(1.0 - 0.683)/2.0;
const double fTailLow	=fTail;
const double fTailUp	=1.0 - fTail;

const int eNominal=0;
const int ePls1Sig=1;
const int eMns1Sig=2;

const int NERR=3;
const int NCAT=5;

const int N_TBL_NUM=8;
enum E_TBL_NUM{ eNtag=0,
				eNnu,
				eEff,
				eBkg,
				eMnm,
				eStat,
				eSyst,
				eTot
				  };


enum EERR{ eStatOnly=0,
		   eSysOnly,
		   eStatSys
		  };
enum ECAT{ eNuEvts=0,
		   eNmcnTot,
		   eNmcnTag,
		   eNbkgTag,
		   eNtotTag
		 };

const string SERR[ NERR ]=
		  { "stat",
			"sys",
			"statsys"
		  };
const string SCAT[ NCAT ]=
		  { "NuEvts",
		    "NmcnTot",
			"NmcnTag",
			"NbkgTag",
			"NtotTag"
		  };

const int N_TRMOM_BINS=4;
const int eAll=N_TRMOM_BINS;
enum E_TRMOM_BINS{ e0p00_0p25,
				   e0p25_0p50,
				   e0p50_0p75,
				   eGE_0p75
				  };
const string S_TRMOM_HIST[ N_TRMOM_BINS ]=
				{ "hNuEvtsNumTagAllTrMom0p00__0p25",
				  "hNuEvtsNumTagAllTrMom0p25__0p50",
				  "hNuEvtsNumTagAllTrMom0p50__0p75",
				  "hNuEvtsNumTagAllTrMomGE__0p75"
			    };
const string S_TRMOM_LABEL[ N_TRMOM_BINS ]=
				{ "TrMom0p00__0p25",
				  "TrMom0p25__0p50",
				  "TrMom0p50__0p75",
				  "TrMomGE__0p75"
			    };

///////////////////////////////////////

struct MeanN_t{
	int ptbin;
	int ntag;
	int nnu;
	float eff;
	float brate;
	float meann;
	float stat;
	float sysU;
	float sysL;
	float totU;
	float totL;	
};

///////////////////////////////////////
Double_t fBkgRate[N_BEAM_MODE];

TH1D *fhFracErrTotAve[N_BEAM_MODE];
TH1D *fhFracErrTrMomAve[N_BEAM_MODE][N_SIGMA_VAR];

TH1D *fhTotAveEff[N_BEAM_MODE];
TH1D *fhTrMomAveEff[N_BEAM_MODE][N_SIGMA_VAR+1];
TH1D *fhBkgRate[N_BEAM_MODE];
TH1D *fhTotExpBkg[N_BEAM_MODE];
TH1D *fhTrMomExpBkg[N_BEAM_MODE];

TH1D *fhTotAveDa[N_BEAM_MODE][NERR];
TH1D *fhTrMomAveDa[N_BEAM_MODE][NERR];
TGraphAsymmErrors *fgTotAveData[NERR];
TGraphAsymmErrors *fgTrMomAveData[N_BEAM_MODE][NERR];

TH1D *fhTotAveMC[N_BEAM_MODE];
TH1D *fhTrMomAveMC[N_BEAM_MODE];
TGraphErrors *fgTotAveMC[N_BEAM_MODE];
TGraphErrors *fgTrMomAveMC[N_BEAM_MODE];

TH1D *fhTrMomMC[N_BEAM_MODE][NCAT];
TH1D *fhTrMomData[N_BEAM_MODE][NCAT];
TH1D *fhTagNmulti[N_BEAM_MODE][N_TRMOM_BINS];

TH1D *fhDSTMean[N_BEAM_MODE][N_TRMOM_BINS+1];
TH1D *fhCDFMean[N_BEAM_MODE][N_TRMOM_BINS+1];
TGraph *fgInvCDFMean[N_BEAM_MODE][N_TRMOM_BINS+1];

vector< vector<MeanN_t> > fNumMeanN;
///////////////////////////////////////
void parseCmdLineArgs(int, char**);

void loadMCTvar();
void loadSysError();
void computeMCExpectation();
void computeEfficiency();
void loadData();
void computeExpectedBkg();
void measureNeutrons();

void initiStatErrors();
void throwStatErrors();
void computeStatErrors();

void measureTotAve();
void measureTrMomAve();
void writeOutputs();


void generateTable();
	string getFirstLine();
	string getSecondLine();
	string getLastLine();
	string getLineForNumbers(int, int);

///////////////////////////////////////
string fInFileMC[N_BEAM_MODE];
string fInFileData[N_BEAM_MODE];
string fInFileSysErr;
string fOutFileName;
int fSeed=65868;
int fNthrows=20000;
bool fUseRndmThrw=true;

stringstream fss;
