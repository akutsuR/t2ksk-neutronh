#include "AltMCReducTree.h"

void AltMCReducTree::setTree(TTree* t)
{
	t->SetBranchAddress("iscc",			&fIsCC);
	t->SetBranchAddress("isnc",			&fIsNC);
	t->SetBranchAddress("isqel",		&fIsQEL);
	t->SetBranchAddress("ismec",		&fIsMEC);
	t->SetBranchAddress("isres",		&fIsRES);
	t->SetBranchAddress("isdis",		&fIsDIS);
	t->SetBranchAddress("iscoh",		&fIsCOH);
	t->SetBranchAddress("isve",			&fIsVE);

	t->SetBranchAddress("inNeuPDG",		&fInNeuPDG);
	t->SetBranchAddress("inNucPDG",		&fInNucPDG);
	t->SetBranchAddress("outLepPDG",	&fOutLepPDG);
	t->SetBranchAddress("inNeuAMom",	&fInNeuAMom);
	t->SetBranchAddress("inNucAMom",	&fInNucAMom);
	t->SetBranchAddress("outLepAMom",	&fOutLepAMom);
	t->SetBranchAddress("inNeuDir",		fInNeuDir);
	t->SetBranchAddress("inNucDir",		fInNucDir);
	t->SetBranchAddress("outLepDir",	fOutLepDir);

	t->SetBranchAddress("iNumPar",		&fINumPar);
	t->SetBranchAddress("iParPDG",		fIParPDG);
	t->SetBranchAddress("iParAMom",		fIParAMom);
	t->SetBranchAddress("iParDir",		fIParDir);

	t->SetBranchAddress("fNumPar",		&fFNumPar);
	t->SetBranchAddress("fParPDG",		fFParPDG);
	t->SetBranchAddress("fParAMom",		fFParAMom);
	t->SetBranchAddress("fParDir",		fFParDir);
}


enum IntCat::E_INT_CAT AltMCReducTree::getIntCat()
{
	enum IntCat::E_INT_CAT eic=IntCat::eNONE;

	if( iscc() )
	{
		if( isqel() ){ eic=IntCat::eCC_1P1H; }
		if( ismec() ){ eic=IntCat::eCC_2P2H; }
		if( isres() ){ eic=IntCat::eCC_RES; }
		if( isdis() ){ eic=IntCat::eCC_DIS; }
		if( iscoh() ){ eic=IntCat::eCC_COH; }
	}
	else
	{
		if( isqel() ){ eic=IntCat::eNC_1P1H; }
		if( isres() ){ eic=IntCat::eNC_RES; }
		if( isdis() ){ eic=IntCat::eNC_DIS; }
		if( iscoh() ){ eic=IntCat::eNC_COH; }
		if( isve() ){ eic=IntCat::eNC_NUEL; }
	}

	if( eic==IntCat::eNONE )
	{
		cout<<" [ERROR] AltMCReducTree::getIntCat" 						 <<endl;
		cout<<"   - Strange event and no matched interaction mode found" <<endl;
		cout<<" -> EXIT "												 <<endl;
		exit( -1 );
	}
	return eic;
}

void AltMCReducTree::setHadronMass()
{
	fMass[PostFSI::eNEUTRON]	=Const::Mn;
	fMass[PostFSI::ePROTON]		=Const::Mp;
	fMass[PostFSI::ePIPLUS]		=Const::Mpipl;
	fMass[PostFSI::ePIMINUS]	=Const::Mpipl;
}

float AltMCReducTree::computeEkin(int i, enum PostFSI::E_PFSI_PRT epp)
{
	float ekin=0.0;
	return ekin;
}

void AltMCReducTree::computeFSIPart()
{
	for(int i=0; i<PostFSI::N_PFSI_PRT; i++)
	{
		fFSIMulti[i]=0;
		for(int j=0; j<NFSIMAX; j++)
		{
			fFSIEkin[i][j]=0.0;
		}
	}
//////////////////////////////////////////
//
//	float ekin=0.0;
//	for(int i=0; i<fFNumPar; i++)
//	{
//		if( fFParPDG[i]==Const::PDG_NEUTRON )
//		{
//			ekin
//		}
//
//	}
//	const int PDG_NEUTRON		=2112;
//	const int PDG_PROTON		=2212;
//	const int PDG_PIPLUS		=211;
//	const int PDG_PIMINUS		=-211;
//
//
//			int		fFNumPar;
//			int		fFParPDG[IHADMAX];
//			double	fFParAMom[IHADMAX];
//
}

bool	AltMCReducTree::iscc() const					{ return fIsCC; }
bool	AltMCReducTree::isnc() const					{ return fIsNC; }
bool	AltMCReducTree::isqel() const					{ return fIsQEL; }
bool	AltMCReducTree::ismec() const					{ return fIsMEC; }
bool	AltMCReducTree::isres() const					{ return fIsRES; }
bool	AltMCReducTree::isdis() const					{ return fIsDIS; }
bool	AltMCReducTree::iscoh() const					{ return fIsCOH; }
bool	AltMCReducTree::isve() const					{ return fIsVE; }


int		AltMCReducTree::inNeuPDG() const				{ return fInNeuPDG; }
int		AltMCReducTree::inNucPDG() const				{ return fInNucPDG; }
int		AltMCReducTree::outLepPDG() const				{ return fOutLepPDG; }
double	AltMCReducTree::inNeuAMom() const				{ return fInNeuAMom; }
double	AltMCReducTree::inNucAMom() const				{ return fInNucAMom; }
double	AltMCReducTree::outLepAMom() const				{ return fOutLepAMom; }
double	AltMCReducTree::inNeuDir(int i) const			{ return fInNeuDir[i]; }
double	AltMCReducTree::inNucDir(int i) const			{ return fInNucDir[i]; }
double	AltMCReducTree::outLepDir(int i) const			{ return fOutLepDir[i]; }

int		AltMCReducTree::iNumPar() const					{ return fINumPar; }
int		AltMCReducTree::iParPDG(int i) const			{ return fIParPDG[i]; }
double	AltMCReducTree::iParAMom(int i) const			{ return fIParAMom[i]; }
double	AltMCReducTree::iParDir(int i, int j) const		{ return fIParDir[i][j]; }

int		AltMCReducTree::fNumPar() const					{ return fFNumPar; }
int		AltMCReducTree::fParPDG(int i) const			{ return fFParPDG[i]; }
double	AltMCReducTree::fParAMom(int i) const			{ return fFParAMom[i]; }
double	AltMCReducTree::fParDir(int i, int j) const		{ return fFParDir[i][j]; }
