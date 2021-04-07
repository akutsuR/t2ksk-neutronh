#pragma once

#include <iostream>
#include <string>
#include <vector>
#include <cstdlib>
#include <type_traits>

#include "TROOT.h"
#include "TTree.h"
#include "TChain.h"

using std::string;
using std::vector;
using std::cout;
using std::endl;

class SKh1Variables
{
	public :
		SKh1Variables();
		virtual ~SKh1Variables(){};

		void	resisterVariable(string);
		void	setBranches(TTree*);

		void	resisterDefaultDST();
		void	resisterDefaultT2KREDUC();
		void	resisterDefaultfiTQun();
		void	resisterDefaultVECT();
		void	resisterDefaultNEWORK();
		void	resisterDefaultVCWORK();
		void	resisterDefaultCONVVECT();

		template <typename T> T var(string) const;
		template <typename T> T var(string, int) const;
		template <typename T> T var(string, int, int) const;
		template <typename T> T var(string, int, int, int) const;

		bool	isSupported(string);

	private :
		void printError(string) const;

		vector<string> fVarList;

		//<DST>
		UInt_t		fnhitac;	
		
		//<T2KReduc>
		Int_t		fevclass;
		Int_t		fnspill;
		Int_t		fgood_spill_flag;
		
		//<fiTQun>
		Int_t		ffqmrnring[32];
		Float_t		ffq1rmom[10][7];
		Float_t		ffq1rpos[10][7][3];
		Float_t		ffq1rdir[10][7][3];
		Float_t		ffq1rnll[10][7];
		Int_t		ffqnse;
		
		//<VECT>
		Int_t		fnpar;
		Float_t		fpmomv[50];
		UInt_t		fipv[50];
		Float_t		fposv[3];
		Float_t		fdirv[50][3];
		Float_t		fwallv;
		
		//<NEWORK>
		Int_t		fmode;
		Int_t 		fnumnu;
		Int_t		fipnu[50];
		Float_t		fpnu[50];
		Float_t		fdirnu[50][3];
		
		// <VCWORK>
		Int_t		fNpvc;
		Int_t		fIpvc[100];
		Int_t		fIchvc[100];
		Float_t		fAbspvc[50];
		
		// <CONVVECT>
		Int_t		fnscndprt;
		Int_t		fiprtscnd[500];
		Int_t		fiprntprt[500];
		Int_t		flmecscnd[500];
		Float_t		fvtxscnd[500][3];
		Float_t		ftscnd[500];
};
