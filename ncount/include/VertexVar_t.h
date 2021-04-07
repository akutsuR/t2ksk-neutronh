#pragma once

struct VertexVar_t
{
	float r2nuev;
	float znuev;
	float dwlnuev;
	int ntot_tag;
	int nmcn_tag;
	int nbkg_tag;
	float r2ntag[200];
	float zntag[200];
	float dwlntag[200];

	// only for MC
	float r2ntag_mcn[200];
	float zntag_mcn[200];
	float dwlntag_mcn[200];
	float r2ntag_bkg[200];
	float zntag_bkg[200];
	float dwlntag_bkg[200];

	//float r2ntag[];
	//float zntag[];
	//float dwlntag[];
};
