#include <iostream>
#include <string>

#include "TRandom3.h"

using std::cout;
using std::endl;
using std::string;

class ToyTagging
{
	public :
		ToyTagging(int);
		virtual ~ToyTagging(){ delete fRand; }

		void setSignalEfficiency(double);
		void setBackgroundEfficiency(double);

		int getTaggedSignal(int);
		int getTaggedBackground(int);

	private :
		TRandom3 *fRand;
		double fSigEfficiency;
		double fBkgEfficiency;
};
