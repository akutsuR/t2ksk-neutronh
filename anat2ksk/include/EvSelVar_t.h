#pragma once

#include "DefCC0PiNumuCut.h"

struct EvSelVar_t
{
	bool pass[CC0PiNumuCut::N_EVE_SLC];

	int	  nring;
	float emupid;
	float momm;
	int	  dcye;
	float cpimupid;
};
