#pragma once

#include <string>
#include <iostream>

#include "TROOT.h"

#include "DefIntCat.h"
#include "DefOscChannels.h"

using std::string;

namespace CC0PiNumuBrkDwn
{
	const int N_BKDN_COMP=6;
	const int N_BKDN_COMP_NTAG=7;	/* for ntag */
	enum E_BKDN_COMP{ eCCQE_NUMU=0,
					  eCCQE_NUMUBAR,
					  eCCNQ_NUMU,
					  eCCNQ_NUMUBAR,
					  eCC_NUENUEBAR,
					  eNC_NUNUBAR,
					  eACCBKG,		/* for ntag */
					  eNONE
					};

	const std::string S_BKDN_COMP[ N_BKDN_COMP_NTAG ]=
					{ "ccqe_numu",
					  "ccqe_numubar",
					  "ccnq_numu",
					  "ccnq_numubar",
					  "cc_nuenuebar",
					  "nc_nunubar",
				      "accbkg"		/* for ntag */
					};

	const std::string S_BKDN_COMP_LEGE[ N_BKDN_COMP_NTAG ]=
					{ "CCQE #nu_{#mu}",
					  "CCQE #bar{#nu}_{#mu}",
					  "CCNQ #nu_{#mu}",
					  "CCNQ #bar{#nu}_{#mu}",
					  "CC #nu_{e}/#bar{#nu}_{e}",
					  "NC #nu/#bar{#nu}",
					  "Acc. Bkg."	/* for ntag */
					 };

//	const int color[ N_BKDN_COMP_NTAG ]=
//					{ kAzure-6,
//					  kOrange+4,
//					  kAzure+7,
//					  kOrange-3,
//					  kMagenta+2,
//					  kTeal+2,
//					  15			/* for ntag */
//					};
	const int color[ N_BKDN_COMP_NTAG ]=
					{ kAzure-3,
					  kOrange-3,
					  kAzure-9,
					  kOrange-9,
					  kViolet-9,
					  kTeal+1,
					  kYellow+1			/* for ntag */
					};


	enum E_BKDN_COMP getCC0PiNumuBrkDwn(enum OscChan::E_OSC_CHAN, enum IntCat::E_INT_CAT);
	enum E_BKDN_COMP getCC0PiNumuBrkDwn(int, int);
}
