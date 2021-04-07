#include "ToyTagging.h"

ToyTagging::ToyTagging(int iseed) :
fSigEfficiency( -1.0 ),
fBkgEfficiency( -1.0 )
{
	fRand=new TRandom3( iseed );
	int rand=fRand->Integer( 10000 );
	gRandom->SetSeed( rand );

	cout<<" [INFO] ToyTagging::ToyTagging " 				<<endl;
	cout<<"   - Instanciated "								<<endl;
	cout<<"   - gRandom is initialized with seed :" << rand <<endl;
}

void ToyTagging::setSignalEfficiency(double se)
{
	fSigEfficiency=se;
	cout<<" [INFO] ToyTagging::setSignalEfficiency " 				<<endl;
	cout<<"   - Set signal tagging efficiency :" << fSigEfficiency	<<endl;
}

void ToyTagging::setBackgroundEfficiency(double be)
{
	fBkgEfficiency=be;
	cout<<" [INFO] ToyTagging::setBackgroundEfficiency " 				<<endl;
	cout<<"   - Set background tagging efficiency :" << fBkgEfficiency	<<endl;
}

int ToyTagging::getTaggedSignal(int nsig_tot)
{
	return (int)fRand->Binomial(nsig_tot, fSigEfficiency);
}

int ToyTagging::getTaggedBackground(int nbkg_tot)
{
	return (int)fRand->Binomial(nbkg_tot, fBkgEfficiency);
}
