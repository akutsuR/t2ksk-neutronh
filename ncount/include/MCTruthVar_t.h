#pragma once

#include "const.h"

namespace MCTVar
{
	const int NMAX=100;
}

struct MCTruthVar_t
{
	int NneuPostFSI;
	int NproPostFSI;
	int NpipPostFSI;
	int NpimPostFSI;

	float neuEkin[MCTVar::NMAX];	// NneuPostFSI
	float proEkin[MCTVar::NMAX];	// NproPostFSI
	float pipEkin[MCTVar::NMAX];	// NpipPostFSI
	float pimEkin[MCTVar::NMAX];	// NpimPostFSI

	int NneuFSISI;
	float npdistFSISI[MCTVar::NMAX];

	float recotrmom;	// GeV/c
	float etrue;		// GeV/c
	float Q2true;
////////////////////////////////////////
	void clear()
	{
		NneuPostFSI=0;
		NproPostFSI=0;
		NpipPostFSI=0;
		NpimPostFSI=0;

		for(int i=0; i<MCTVar::NMAX; i++)
		{
			neuEkin[i]		=-9999.9;	// NneuPostFSI
			proEkin[i]		=-9999.9;	// NproPostFSI
			pipEkin[i]		=-9999.9;	// NpipPostFSI
			pimEkin[i]		=-9999.9;	// NpimPostFSI

			npdistFSISI[i]	=-9999.9;
		}

		recotrmom	=-9999.9;
		etrue		=-9999.9;
		Q2true		=-9999.9;
	}

	float getMass(int ip)
	{
		float mass=0.0;
		switch ( ip ) 
		{
			case Const::PDG_PROTON :
				mass=Const::Mp;		break;
			case Const::PDG_NEUTRON :
				mass=Const::Mn;		break;
			case Const::PDG_PIPLUS :
				mass=Const::Mpipl;	break;
			case Const::PDG_PIMINUS :
				mass=Const::Mpipl;	break;
			default : 
				mass=-999.9;		break;
		}
		return mass;
	}

	void addPostFSIHadron(int ip, float ekin)
	{
		switch ( ip ) 
		{
			case Const::PDG_PROTON :
				proEkin[NproPostFSI]=ekin;
				NproPostFSI+=1;
				break;
			case Const::PDG_NEUTRON :
				neuEkin[NneuPostFSI]=ekin;
				NneuPostFSI+=1;
				break;
			case Const::PDG_PIPLUS :
				pipEkin[NpipPostFSI]=ekin;
				NpipPostFSI+=1;
				break;
			case Const::PDG_PIMINUS :
				pimEkin[NpimPostFSI]=ekin;
				NpimPostFSI+=1;
				break;
		}
	}
};
