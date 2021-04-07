#pragma once

#include "DefBeamMode.h"

namespace TvarCor
{
	// Nominal values taken from 
	//     - ~/disk2/t2k/neutron/nsivar/anal/outputs/nominal/?hc.fq1rnumu.nominal.root
	//
	// Time variation corrected values taken from
	//     -  ~/disk2/t2k/neutron/tvar_fnnn/anal/out/fitntagtvar/fitntagtvar.Run1_9.normal.root


	// Tagging efficiency
	//- FHC 
	//  ---> Nominal Sig. efficiency : 1.98917212503602808e-01
	//  ---> Tvar corrected 		 : 2.00870183601022934e-01
	//
	//- RHC
	// ----> Nominal Sig. efficiency : 2.04032407013022943e-01
	// ----> Tvar corrected 		 : 2.03711708254085605e-01 
	float WgtSigTvar[BeamMode::N_BEAM_MODE]=
			{ 2.00870183601022934e-01/1.98917212503602808e-01,
			  2.03711708254085605e-01/2.04032407013022943e-01
			};
			  
	// Background rate 
	//- FHC
	//  ---> Nominal Bkg. rate (Bkg. tagging efficiency from PS)
	//   	 : 2.09887338792166117e-02
	//  ---> Tvar corrected bkg. rate (after NN)
	//       : 2.01839269593416214e-02
	//
	//- RHC
	//  ---> Nominal Bkg. rate (Bkg. tagging efficiency from PS )
	//       : 1.98596289492870316e-02/3.50877125705993809e+00
	//  ---> Tvar corrected bkg. rate (after NN)
	//       : 1.93755388489533290e-02
	float WgtBkgTvar[BeamMode::N_BEAM_MODE]=
			{ 2.01839269593416214e-02/2.09887338792166117e-02,
			  1.93755388489533290e-02/1.98596289492870316e-02
			};

//////////////////////////////////////////////////////////////////
// Scaling factor for 535us -> 513us
	// ---> 535us : /disk02/usr6/rakutsu/t2k/ncount/out/tvarcor/fhc.mrgEvSelCC0PiNumuBrkDwn.tvarcor.root
	// ---> 513us : /disk02/usr6/rakutsu/t2k/ncount/out/tvarcor513us/fhc.mrgEvSelCC0PiNumuBrkDwn.tvarcor513us.root

	// Tagging efficiency
	//- FHC
	// ----> 535us : 6.07710844967167390e+01 [tagged neutrons]
	// ----> 513us : 6.01959124449790366e+01 [tagged neutrons]
	//
	//- RHC
	// ----> 535us : 4.78620305678018454e+01 [tagged neutrons]
	// ----> 513us : 4.73871416986316518e+01 [tagged neutrons]
	const float ConvEff535usTO513us[BeamMode::N_BEAM_MODE]=
			{6.01959124449790366e+01/6.07710844967167390e+01,
			 4.78620305678018454e+01/4.73871416986316518e+01
			};

	// Bkg. rate
	//- FHC
	// ----> 535us : 4.07666638762360378e+00 [tagged bkg]
	// ----> 513us : 3.88161263082888164e+00 [tagged bkg]
	//
	//- RHC
	// ----> 535us : 2.12539349906306763e+00 [tagged neutrons]
	// ----> 513us : 2.03280354616409253e+00 [tagged neutrons]
	const float ConvBkg535usTO513us[BeamMode::N_BEAM_MODE]=
			{ 3.88161263082888164e+00/4.07666638762360378e+00,
			  2.03280354616409253e+00/2.12539349906306763e+00 
			};
};
