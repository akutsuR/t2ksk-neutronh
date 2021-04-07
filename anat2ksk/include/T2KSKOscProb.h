#pragma once

#include <iostream>
#include <cstdlib>

#include "BargerPropagator.h"

#include "DefOscChannels.h"
#include "const.h"

using std::cout;
using std::endl;


namespace BargerIdx
{
	enum E_BARGER_IDX{ eNUE=1,
					   eNUMU,
					   eNUTAU
					  };
};
					  

class T2KSKOscProb : public BargerPropagator
{
	public :
		T2KSKOscProb();
		T2KSKOscProb(enum OscChan::E_OSC_CHAN);
		virtual ~T2KSKOscProb(){};

		void	setOscChannel(enum OscChan::E_OSC_CHAN);
		float	getOscProb(bool, double, bool isVac=false);
		float	getOscProb(bool, double, double, double, double, double, double, double, bool isVac=false);


	private :
		void setOscChannel();
		void setDefaultT2KPars();

		bool fIsSet;
		enum OscChan::E_OSC_CHAN feOC;	
		int fEi;
		int fEo;
		int fPDG;

		bool   fIsSinSQ;
		double fS12;	// sin^2(x)
		double fS13;	// sin^2(x)
		double fS23;	// sin^2(x)
		double fM21;	// m_2^2 - m_1^2
		double fM32;	// m_3^2 - m_2^2
		double fdCP;	// (rad)
		double fEDen;
		double fBaseLine;
};
