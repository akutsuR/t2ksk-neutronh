#pragma once

namespace Const{

	const float beamDir[3]=
	{ 0.669764,
	  -0.742179,
	  0.024223
	};
	
	const float tankR			=1690.0;
	const float tankZ			=1810.0;
	const float one				=1.0;
	
	const float Mn   			=939.565346;
	const float Mp   			=938.272013;
	const float Mpipl   		=139.57;
	const float Mmu  			=105.65836;
	const float Mmu2			=Mmu*Mmu;
	const float Me   			=0.510998;
	const float Eb   			=27.0;
	const float Eb2  			=Eb*Eb;

	//// Taken from TN-360 (VALOR full Run1-9 results)
	//// w/ NH (global best fit) and reactor constraint
	//const double S12	 		=0.304;		// Tab. 2
	//const double S13	 		=0.0219;	// Tab. 2
	//const double S23	 		=0.532;		// Tab. 7
	//const double M12	 		=7.53e-5;	// Tab. 2
	//const double M23	 		=2.452e-3;	// Tab. 7
	//const double Dcp	 		=-1.885;	// Tab. 7
	//const double eDen			=2.6;
	//const double BaseLine		=295.;
	const double S12	 		=0.304;		// Tab. 2
	const double S13	 		=0.0212;	// Tab. 2
	const double S23	 		=0.532;		// Tab. 7
	const double M12	 		=7.53e-5;	// Tab. 2
	const double M23	 		=2.452e-3;	// Tab. 7
	const double Dcp	 		=-1.885;	// Tab. 7
	const double eDen			=2.6;
	const double BaseLine		=295.;

	const int G3_NEUTRON		=13;
	const int G3_PROTON			=14;
	const int G3_PIPLUS			=8;
	const int G3_PIMINUS		=9;
	const int PDG_GAMMA			=22;
	const int PDG_NEUTRON		=2112;
	const int PDG_PROTON		=2212;
	const int PDG_PIPLUS		=211;
	const int PDG_PIMINUS		=-211;

	const int PDG_NUE			=12;
	const int PDG_NUMU			=14;
	const int PDG_NUTAU			=16;
	const int PDG_NUEBAR		=-12;
	const int PDG_NUMUBAR		=-14;
	const int PDG_NUTAUBAR		=-16;
		

	const int SCND_INT_NCAP		=18;
	
	const int fQ_IDX_E  		=1;
	const int fQ_IDX_MU 		=2;
	const int fQ_IDX_CPI		=3;
	
//	const int MAXNP				=200;
}
