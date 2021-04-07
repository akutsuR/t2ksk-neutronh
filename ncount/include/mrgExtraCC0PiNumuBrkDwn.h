#include <iostream>
#include <string>

#include "TFile.h"
#include "THStack.h"
#include "TDirectoryFile.h"
#include "TLegend.h"

#include "CC0PiNumuExtraHists.h"
#include "NtagHistManager.h"
#include "VertexDistributions.h"
#include "MCTruthDistributions.h"
#include "DefIntCat.h"
#include "DefOscChannels.h"
#include "DefNuNubarBreakDown.h"
#include "DefCC0PiNumuBreakDown.h"
#include "DefBeamMode.h"

#include "copyFiles.h"

using std::cout;
using std::endl;
using std::string;

using namespace IntCat;
using namespace OscChan;
using namespace CC0PiNumuBrkDwn;
using namespace BeamMode;

double Run1_9POT[N_BEAM_MODE]={1.4938, 1.6346};

void initialize();
void loadInputs(bool);
void loadExtraHists(bool);
void loadNtagHists(bool);
void loadVertexHists(bool);
void loadMCTruthHists(bool);
void copyInputs(bool);
void normalizeByPOT(bool);
void makeOutputs();
void makeLepMom();
void makeTrMom();
void makeRecoEnu();
void makeRecoQ2();
void makeCosBm();

void makefQDWall();
void makefQVtxR2();
void makefQVtxZ();

void makeTaggedNMulti();
void makeRecoNPDist();
void makeRecoNPDistLong();
void makeRecoNPDistTran();
void makeRecoTDiff();
void makeRecoCosNangActual();
void makeRecoCosNangInferred();
void makeLegend();
void writeOutputs();
////////////////////////////////////////////////////////

CC0PiNumuExtraHists 	*fExtra[N_BKDN_COMP+1];
NtagHistManager 		*fNtag[N_BKDN_COMP+1];
VertexDistributions		*fVtx[N_BKDN_COMP+1];
MCTruthDistributions	*fMCT[N_BKDN_COMP+1];

// Ave. tagged n vs mu momentum (not Pt)
TH1D		*fhLepMomAveTotMCN;
TH1D		*fhLepMomAveTagMCN;
TH1D		*fhLepMomAveTagALL;	// (true n + bkg)/nu evt
TH1D		*fhLepMomNbkgTot;	// all bkg. are combined
THStack		*fhsLepMomNuEvts;
THStack		*fhsLepMomTotMCN;
THStack		*fhsLepMomTagALL;	// true n + bkg


// Ave. tagged n vs Pt
TH1D		*fhTrMomAveTotMCN;
TH1D		*fhTrMomAveTagMCN;
TH1D		*fhTrMomAveTagALL;	// (true n + bkg)/nu evt
TH1D		*fhTrMomNbkgTot;	// all bkg. are combined
THStack		*fhsTrMomNuEvts;
THStack		*fhsTrMomTotMCN;
THStack		*fhsTrMomTagALL;	// true n + bkg

// Ave. tagged n vs Erec
TH1D		*fhRecoEnuAveTotMCN;
TH1D		*fhRecoEnuAveTagMCN;
TH1D		*fhRecoEnuAveTagALL;	// (true n + bkg)/nu evt
TH1D		*fhRecoEnuNbkgTot;
THStack		*fhsRecoEnuNuEvts;
THStack		*fhsRecoEnuTotMCN;
THStack		*fhsRecoEnuTagALL;

// Ave. tagged n vs Q2rec
TH1D		*fhRecoQ2AveTotMCN;
TH1D		*fhRecoQ2AveTagMCN;
TH1D		*fhRecoQ2AveTagALL;	// (true n + bkg)/nu evt
TH1D		*fhRecoQ2NbkgTot;
THStack		*fhsRecoQ2NuEvts;
THStack		*fhsRecoQ2TotMCN;
THStack		*fhsRecoQ2TagALL;

// Ave. tagged n vs cosbm (angle btw mu and nu)
TH1D		*fhCosBmAveTotMCN;
TH1D		*fhCosBmAveTagMCN;
TH1D		*fhCosBmAveTagALL;	// (true n + bkg)/nu evt
TH1D		*fhCosBmNbkgTot;
THStack		*fhsCosBmNuEvts;
THStack		*fhsCosBmTotMCN;
THStack		*fhsCosBmTagALL;

// Ave. tagged n vs fQDWall
TH1D		*fhfQDWallAveTotMCN;
TH1D		*fhfQDWallAveTagMCN;
TH1D		*fhfQDWallAveTagALL;	// (true n + bkg)/nu evt
TH1D		*fhfQDWallNbkgTot;
THStack		*fhsfQDWallNuEvts;
THStack		*fhsfQDWallTotMCN;
THStack		*fhsfQDWallTagALL;

// Ave. tagged n vs fQ vertex R2
TH1D		*fhfQVtxR2AveTotMCN;
TH1D		*fhfQVtxR2AveTagMCN;
TH1D		*fhfQVtxR2AveTagALL;	// (true n + bkg)/nu evt
TH1D		*fhfQVtxR2NbkgTot;
THStack		*fhsfQVtxR2NuEvts;
THStack		*fhsfQVtxR2TotMCN;
THStack		*fhsfQVtxR2TagALL;

// Ave. tagged n vs cosbm (angle btw mu and nu)
TH1D		*fhfQVtxZAveTotMCN;
TH1D		*fhfQVtxZAveTagMCN;
TH1D		*fhfQVtxZAveTagALL;	// (true n + bkg)/nu evt
TH1D		*fhfQVtxZNbkgTot;
THStack		*fhsfQVtxZNuEvts;
THStack		*fhsfQVtxZTotMCN;
THStack		*fhsfQVtxZTagALL;


// Tagged n multiplicity
THStack		*fhsTaggedNMulti;

// Tagged n vs rec. np distance
THStack		*fhsRecoNPDistTagALL;

// Tagged n rec. capture time
THStack		*fhsRecoTDiffTagALL;

// Tagged n vs rec. np distance projected onto beam direction
THStack		*fhsRecoNPDistLongTagALL;

// Tagged n vs rec. np distance projected onto beam direction
THStack		*fhsRecoNPDistTranTagALL;

// Tagged n angle btw reco. n and beam directions
THStack		*fhsRecoCosNangActTagALL;

// Tagged n angle btw reco. n and beam directions
THStack		*fhsRecoCosNangInfTagALL;

TLegend		*fLegRNumu;
TLegend		*fLegRNtag;
TLegend		*fLegLNumu;
TLegend		*fLegLNtag;


string fOutFileName	="";
string fInputDir	="";
string fDstName		="";
bool fIsNominal=true;
bool fIsAltMC=false;
