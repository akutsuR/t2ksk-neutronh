#include "SKFluxTuning.h"

SKFluxTuning::SKFluxTuning() :
fBeamMode( BeamMode::eNONE ),
fOscChan( OscChan::eNONE )
{
	clearFluxTuningHists();
	setDefaultTuningFileNames();
	setDefaultTuningHistNames();
}
/////////////////////////////////////////////////////////


SKFluxTuning::~SKFluxTuning()
{
	for(int i=0; i<N_BEAM_MODE; i++)
	{
		for(int j=0; j<N_OSC_CHAN; j++)
		{
			delete fhFluxTuning[i][j];
		}
	}
}
/////////////////////////////////////////////////////////


void SKFluxTuning::clearFluxTuningHists()
{
	for(int i=0; i<N_BEAM_MODE; i++)
	{
		for(int j=0; j<N_OSC_CHAN; j++)
		{
			fhFluxTuning[i][j]=NULL;
		}
	}
}
/////////////////////////////////////////////////////////


void SKFluxTuning::setDefaultTuningFileNames()
{
	string sdir="";
	// 13va3 tuning using thinned target
	//sdir="/disk02/usr6/rakutsu/t2k/neutron/sigmavar/files/out/tuned13av3";
	//fFileName[eFHC]=sdir + "/run1-9a_v2/sk_tuned13av3_13anom_run1-9a_numode_fine.root";
	//fFileName[eRHC]=sdir + "/run5c-9d_v2/sk_tuned13av3_13anom_run5c-9d_antinumode_fine.root";

	// 13va4 tuning using replica target
	sdir="/disk02/usr6/rakutsu/t2k/regene_mc/files/flux/13av4/tuned13av4.0";
	fFileName[eFHC]=sdir + "/run1-9a_v2/sk_tuned13av4_13anom_run1-9a_numode_fine.root";
	fFileName[eRHC]=sdir + "/run5c-9d_v2/sk_tuned13av4_13anom_run5c-9d_antinumode_fine.root";
}


void SKFluxTuning::setDefaultTuningHistNames()
{
	fHistName[eNUMU]		="enu_sk_tuned13a_numu_ratio";
	fHistName[eNUESIG]		=fHistName[eNUMU];
	fHistName[eNUMUBAR]		="enu_sk_tuned13a_numub_ratio";
	fHistName[eNUEBARSIG]	=fHistName[eNUMUBAR];
	fHistName[eNUE]			="enu_sk_tuned13a_nue_ratio";
	fHistName[eNUEBAR]		="enu_sk_tuned13a_nueb_ratio";
}
/////////////////////////////////////////////////////////


void SKFluxTuning::loadFluxTunings()
{
	TFile *f=NULL;
	for(int i=0; i<N_BEAM_MODE; i++)
	{
		f=TFile::Open(fFileName[i].c_str(), "read");
		if( !f->IsOpen() )
		{
			cout<<" [ERROR] SKFluxTuning::loadFluxTunings " <<endl;
			cout<<" - Can not load " << fFileName[i]		<<endl;
			cout<<"   -> EXIT "								<<endl;
		}
		if( i==0 ){ cout<<" [INFO] SKFluxTuning::loadFluxTunings " <<endl; }
		cout<<" - Loaded " << fFileName[i]			   <<endl;
		
			
		for(int j=0; j<N_OSC_CHAN; j++)
		{
			fhFluxTuning[i][j]=
				(TH1D*)f->Get( fHistName[j].c_str() )->Clone();
			fhFluxTuning[i][j]->SetDirectory(0);
		}

		f->Close();
		delete f;
		f=NULL;	
	}
}
/////////////////////////////////////////////////////////


float SKFluxTuning::getFluxTuning(enum E_BEAM_MODE ebm,
								  enum E_OSC_CHAN eoc,
								  float Enu)
{
// Enu : true neutrino energy in GeV

	int bin=-1;
	bin=fhFluxTuning[ebm][eoc]->GetXaxis()->FindBin( Enu );
	return fhFluxTuning[ebm][eoc]->GetBinContent( bin );
}
/////////////////////////////////////////////////////////


float SKFluxTuning::getFluxTuning(float Enu)
{
// Enu : true neutrino energy in GeV
	return this->getFluxTuning(fBeamMode, fOscChan, Enu);
}
/////////////////////////////////////////////////////////


void SKFluxTuning::setBeamMode(enum E_BEAM_MODE ebm)
{
	fBeamMode=ebm;
}
/////////////////////////////////////////////////////////
	

void SKFluxTuning::setOscChannel(enum E_OSC_CHAN eoc)
{
	fOscChan=eoc;
}
