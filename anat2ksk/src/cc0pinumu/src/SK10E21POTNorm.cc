#include "SK10E21POTNorm.h"

SK10E21POTNorm::SK10E21POTNorm()
{
	clearNormFactors();
}
///////////////////////////////////////////////


void SK10E21POTNorm::clearNormFactors()
{
	for(int i=0; i<N_BEAM_MODE; i++)
	{
		for(int j=0; j<N_OSC_CHAN; j++)
		{
			fSKRate[i][j]=0.0;
			fEvtsWallV[i][j]=0.0;
		}
	}
}

void SK10E21POTNorm::setSKRate10E21POT()
{
// Predictions made by NEUT5.3.2 and 
// 13a nominal fluxes
	fSKRate[ eFHC ][ eNUMU ]		=1396.245;	// numu->numu
	fSKRate[ eFHC ][ eNUESIG ]		=1483.994;	// numu->nue
	fSKRate[ eFHC ][ eNUMUBAR ]		=50.964;	// numubar->numbar
	fSKRate[ eFHC ][ eNUEBARSIG ]  	=52.939;	// numubar->nuebar
	fSKRate[ eFHC ][ eNUE ]			=26.663;	// nue->nue
	fSKRate[ eFHC ][ eNUEBAR ]		=2.884;		// nuebar->nuebar

	fSKRate[ eRHC ][ eNUMU ]		=208.369;
	fSKRate[ eRHC ][ eNUESIG ]		=215.099;
	fSKRate[ eRHC ][ eNUMUBAR ]		=353.789;
	fSKRate[ eRHC ][ eNUEBARSIG ]	=376.420;
	fSKRate[ eRHC ][ eNUE ]			=8.941;
	fSKRate[ eRHC ][ eNUEBAR ]		=6.811;
}


void SK10E21POTNorm::setTrueWallEventsAllMC()
{
	fEvtsWallV[ eFHC ][ eNUMU ]			=634881.;
	fEvtsWallV[ eFHC ][ eNUESIG ]		=126916.;
	fEvtsWallV[ eFHC ][ eNUMUBAR ]		=634600.;
	fEvtsWallV[ eFHC ][ eNUEBARSIG ]	=126984.;
	fEvtsWallV[ eFHC ][ eNUE ]			=126899.;
	fEvtsWallV[ eFHC ][ eNUEBAR ]		=126728;

	fEvtsWallV[ eRHC ][ eNUMU ]			=634659.;
	fEvtsWallV[ eRHC ][ eNUESIG ]		=127278.;
	fEvtsWallV[ eRHC ][ eNUMUBAR ]		=633988.;
	fEvtsWallV[ eRHC ][ eNUEBARSIG ]	=126812.;
	fEvtsWallV[ eRHC ][ eNUE ]			=127262.;
	fEvtsWallV[ eRHC ][ eNUEBAR ]		=127013.;
}


void SK10E21POTNorm::setTrueWallEventsLastHalfMC()
{
	fEvtsWallV[ eFHC ][ eNUMU ]			=317471.;		// obtained from 00[5-9].0??
	fEvtsWallV[ eFHC ][ eNUESIG ]		=63527.;		// Obtained from 011.0??
	fEvtsWallV[ eFHC ][ eNUMUBAR ]		=317772.;		// Obtained from 02[5-9].0??
	fEvtsWallV[ eFHC ][ eNUEBARSIG ]	=63566.;		// Obtained from 046.0??
	fEvtsWallV[ eFHC ][ eNUE ]			=63458.;		// Obtained from 013.0??
	fEvtsWallV[ eFHC ][ eNUEBAR ]		=63203.;		// Obtained from 041.0??

	fEvtsWallV[ eRHC ][ eNUMU ]			=317400.;		// Obtained from 00[5-9].0??
	fEvtsWallV[ eRHC ][ eNUESIG ]		=63722.;		// Obtained from 041.??
	fEvtsWallV[ eRHC ][ eNUMUBAR ]		=316989.;		// Obtained from 01[5-9].0??
	fEvtsWallV[ eRHC ][ eNUEBARSIG ]	=63337.;		// Obtained from 051.0??
	fEvtsWallV[ eRHC ][ eNUE ]			=63698.;		// Obtained from 021.0??
	fEvtsWallV[ eRHC ][ eNUEBAR ]		=63522.;		// Obtained from 031.0??
}


void SK10E21POTNorm::setTrueWallEventsAllMC(enum GenType::E_GEN_TYP egt)
{
	if( egt==GenType::eNEUT ){ this->setTrueWallEventsAllMC(); }

	// For neutron study using 1RNumu sample,
	// The contribution except for numu->numu
	// and numubar->numbar MC is negligble.
	// Thus, onlu numu->numu and numubar->numubar MC 
	// have been generated for the neutron study described in TN-371 

	// The below numbers were obtained from the files put on
	//
	//   /home/rakutsu/disk/t2k/mc/genie/tstgen_mec/out/fq_root/
	if( egt==GenType::eGENIE )
	{

		fEvtsWallV[ eFHC ][ eNUMU ]			=253916.; //00[0-3].???
		fEvtsWallV[ eFHC ][ eNUESIG ]		=-1.0;
		fEvtsWallV[ eFHC ][ eNUMUBAR ]		=253457.; //01[0-3].???
		fEvtsWallV[ eFHC ][ eNUEBARSIG ]	=-1.0;
		fEvtsWallV[ eFHC ][ eNUE ]			=-1.0;
		fEvtsWallV[ eFHC ][ eNUEBAR ]		=-1.0;

		fEvtsWallV[ eRHC ][ eNUMU ]			=253833.; //01[0-3].??? 
		fEvtsWallV[ eRHC ][ eNUESIG ]		=-1.0;
		fEvtsWallV[ eRHC ][ eNUMUBAR ]		=254001.; //00[0-3].???
		fEvtsWallV[ eRHC ][ eNUEBARSIG ]	=-1.0;
		fEvtsWallV[ eRHC ][ eNUE ]			=-1.0;
		fEvtsWallV[ eRHC ][ eNUEBAR ]		=-1.0;
	}

	// The below numbers were obtained from the files put on
	//
	//   /home/rakutsu/disk/t2k/mc/nuwro/tstgen/out/fq_root/
	if( egt==GenType::eNuWro )
	{
		fEvtsWallV[ eFHC ][ eNUMU ]			=316810.; // 00[0-4].???
		fEvtsWallV[ eFHC ][ eNUESIG ]		=-1.0;
		fEvtsWallV[ eFHC ][ eNUMUBAR ]		=317695.; // 01[0-4].???
		fEvtsWallV[ eFHC ][ eNUEBARSIG ]	=-1.0;
		fEvtsWallV[ eFHC ][ eNUE ]			=-1.0;
		fEvtsWallV[ eFHC ][ eNUEBAR ]		=-1.0;

		fEvtsWallV[ eRHC ][ eNUMU ]			=317751.; // 01[0-4].???
		fEvtsWallV[ eRHC ][ eNUESIG ]		=-1.0;
		fEvtsWallV[ eRHC ][ eNUMUBAR ]		=317551.; // 00[0-4].???
		fEvtsWallV[ eRHC ][ eNUEBARSIG ]	=-1.0;
		fEvtsWallV[ eRHC ][ eNUE ]			=-1.0;
		fEvtsWallV[ eRHC ][ eNUEBAR ]		=-1.0;
	}
}


float SK10E21POTNorm::get10E21POTNorm(enum E_BEAM_MODE eBM, enum E_OSC_CHAN eOC)
{
	return fSKRate[ eBM ][ eOC ]/fEvtsWallV[ eBM ][ eOC ];
}

// For GENIE and NuWro
void SK10E21POTNorm::setSKRate10E21POT(enum GenType::E_GEN_TYP egt)
{
	if( egt==GenType::eNEUT ){ this->setSKRate10E21POT(); }

	// Predictions made by GENIE R2_12_10 and 
	// 13a nominal fluxes
	if( egt==GenType::eGENIE )
	{
		fSKRate[ eFHC ][ eNUMU ]		=1396.231;	// numu->numu
		fSKRate[ eFHC ][ eNUESIG ]		=1461.307;	// numu->nue
		fSKRate[ eFHC ][ eNUMUBAR ]		=52.351;	// numubar->numbar
		fSKRate[ eFHC ][ eNUEBARSIG ]  	=53.583;	// numubar->nuebar
		fSKRate[ eFHC ][ eNUE ]			=26.150;	// nue->nue
		fSKRate[ eFHC ][ eNUEBAR ]		=2.893;		// nuebar->nuebar

		fSKRate[ eRHC ][ eNUMU ]		=206.223;
		fSKRate[ eRHC ][ eNUESIG ]		=210.941;
		fSKRate[ eRHC ][ eNUMUBAR ]		=370.589;
		fSKRate[ eRHC ][ eNUEBARSIG ]	=384.656;
		fSKRate[ eRHC ][ eNUE ]			=8.746;
		fSKRate[ eRHC ][ eNUEBAR ]		=6.887;
	}


	// Predictions made by NuWro 18.02.1 and 
	// 13a nominal fluxes
	if( egt==GenType::eNuWro )
	{
		fSKRate[ eFHC ][ eNUMU ]		=1300.779;	// numu->numu
		fSKRate[ eFHC ][ eNUESIG ]		=1365.339;	// numu->nue
		fSKRate[ eFHC ][ eNUMUBAR ]		=46.854;	// numubar->numbar
		fSKRate[ eFHC ][ eNUEBARSIG ]  	=48.087;	// numubar->nuebar
		fSKRate[ eFHC ][ eNUE ]			=24.163;	// nue->nue
		fSKRate[ eFHC ][ eNUEBAR ]		=2.630;		// nuebar->nuebar

		fSKRate[ eRHC ][ eNUMU ]		=191.246;
		fSKRate[ eRHC ][ eNUESIG ]		=196.026;
		fSKRate[ eRHC ][ eNUMUBAR ]		=328.618;
		fSKRate[ eRHC ][ eNUEBARSIG ]	=341.850;
		fSKRate[ eRHC ][ eNUE ]			=8.116;
		fSKRate[ eRHC ][ eNUEBAR ]		=6.182;
	}
}
