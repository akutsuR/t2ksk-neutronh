#include "SKh1Variables.h"

SKh1Variables::SKh1Variables()
{
	fVarList.clear();
}


void SKh1Variables::setBranches(TTree *t)
{
//	t->SetBranchStatus("*", 0);

	cout<<" [INFO] SKh1Variables::setBranches " <<endl;
	vector<bool> isOK;
	isOK.clear();
	for(Int_t i=0; i<(Int_t)fVarList.size(); i++)
	{
		if( !t->GetBranch(fVarList[i].c_str()) )
		{
			cout<<"   -> Trying to set the Branch :" << fVarList[i] 
				<<", but not found."				 <<endl;
			isOK.push_back( false );	
		}
		else
		{
			isOK.push_back( true );
		}
	}

	for(Int_t i=0; i<(Int_t)fVarList.size(); i++)
	{
		if( !isOK[i] ){ continue; }
		t->SetBranchStatus(fVarList[i].c_str(), 1);
	}

	for(Int_t i=0; i<(Int_t)fVarList.size(); i++)
	{
		if( !isOK[i] ){ continue; }

		if(		 fVarList[i]=="nhitac" )			{ t->SetBranchAddress(fVarList[i].c_str(),	&fnhitac); }

		else if( fVarList[i]=="evclass" )			{ t->SetBranchAddress(fVarList[i].c_str(),	&fevclass); }
		else if( fVarList[i]=="nspill" )			{ t->SetBranchAddress(fVarList[i].c_str(),	&fnspill); }
		else if( fVarList[i]=="good_spill_flag" )	{ t->SetBranchAddress(fVarList[i].c_str(),	&fgood_spill_flag); }

		else if( fVarList[i]=="fqmrnring" ) 		{ t->SetBranchAddress(fVarList[i].c_str(),	ffqmrnring); }
		else if( fVarList[i]=="fq1rmom" ) 			{ t->SetBranchAddress(fVarList[i].c_str(),	ffq1rmom); }
		else if( fVarList[i]=="fq1rpos" ) 			{ t->SetBranchAddress(fVarList[i].c_str(),	ffq1rpos); }
		else if( fVarList[i]=="fq1rdir" ) 			{ t->SetBranchAddress(fVarList[i].c_str(),	ffq1rdir); }
		else if( fVarList[i]=="fq1rnll" ) 			{ t->SetBranchAddress(fVarList[i].c_str(),	ffq1rnll); }
		else if( fVarList[i]=="fqnse" ) 			{ t->SetBranchAddress(fVarList[i].c_str(),	&ffqnse); }

		else if( fVarList[i]=="npar" )				{ t->SetBranchAddress(fVarList[i].c_str(),	&fnpar); }
		else if( fVarList[i]=="pmomv" )				{ t->SetBranchAddress(fVarList[i].c_str(),	fpmomv); }
		else if( fVarList[i]=="ipv" )				{ t->SetBranchAddress(fVarList[i].c_str(),	fipv); }
		else if( fVarList[i]=="ipnu" )				{ t->SetBranchAddress(fVarList[i].c_str(),	fipnu); }
		else if( fVarList[i]=="posv" )				{ t->SetBranchAddress(fVarList[i].c_str(),	fposv); }
		else if( fVarList[i]=="dirv" )				{ t->SetBranchAddress(fVarList[i].c_str(),	fdirv); }
		else if( fVarList[i]=="wallv" )				{ t->SetBranchAddress(fVarList[i].c_str(),	&fwallv); }

		else if( fVarList[i]=="mode" )				{ t->SetBranchAddress(fVarList[i].c_str(),	&fmode); }
		else if( fVarList[i]=="numnu" )				{ t->SetBranchAddress(fVarList[i].c_str(),	&fnumnu); }
		else if( fVarList[i]=="ipnu" )				{ t->SetBranchAddress(fVarList[i].c_str(),	fipnu); }
		else if( fVarList[i]=="pnu" )				{ t->SetBranchAddress(fVarList[i].c_str(),	fpnu); }
		else if( fVarList[i]=="dirnu" )				{ t->SetBranchAddress(fVarList[i].c_str(),	fdirnu); }

		else if( fVarList[i]=="Npvc" )				{ t->SetBranchAddress(fVarList[i].c_str(),	&fNpvc); }
		else if( fVarList[i]=="Ipvc" )				{ t->SetBranchAddress(fVarList[i].c_str(),	fIpvc); }
		else if( fVarList[i]=="Ichvc" )				{ t->SetBranchAddress(fVarList[i].c_str(),	fIchvc); }
		else if( fVarList[i]=="Abspvc" )			{ t->SetBranchAddress(fVarList[i].c_str(),	fAbspvc); }

		else if( fVarList[i]=="nscndprt" )			{ t->SetBranchAddress(fVarList[i].c_str(),	&fnscndprt); }
		else if( fVarList[i]=="iprtscnd" )			{ t->SetBranchAddress(fVarList[i].c_str(),	fiprtscnd); }
		else if( fVarList[i]=="iprntprt" )			{ t->SetBranchAddress(fVarList[i].c_str(),	fiprntprt); }
		else if( fVarList[i]=="lmecscnd" )			{ t->SetBranchAddress(fVarList[i].c_str(),	flmecscnd); }
		else if( fVarList[i]=="vtxscnd" )			{ t->SetBranchAddress(fVarList[i].c_str(),	fvtxscnd); }

		cout<<"   - Added branch for " << fVarList[i] <<endl;
	}
	cout<<endl;
};


void SKh1Variables::resisterVariable(string var)
{
	if     ( var=="nhitac" )			{ fVarList.push_back( var ); }	// <DST>

	else if( var=="evclass" )			{ fVarList.push_back( var ); }	// <T2KReduc>
	else if( var=="nspill" )			{ fVarList.push_back( var ); }
	else if( var=="good_spill_flag" )	{ fVarList.push_back( var ); }

	else if( var=="fqmrnring" )			{ fVarList.push_back( var ); }	// <fiTQun>
	else if( var=="fq1rmom" )			{ fVarList.push_back( var ); }
	else if( var=="fq1rpos" )			{ fVarList.push_back( var ); }
	else if( var=="fq1rdir" )			{ fVarList.push_back( var ); }
	else if( var=="fq1rnll" )			{ fVarList.push_back( var ); }
	else if( var=="fqnse" )				{ fVarList.push_back( var ); }

	else if( var=="npar" )				{ fVarList.push_back( var ); }	// <VECT>
	else if( var=="pmomv" )				{ fVarList.push_back( var ); }
	else if( var=="ipv" )				{ fVarList.push_back( var ); }
	else if( var=="ipnu" )				{ fVarList.push_back( var ); }
	else if( var=="posv" )				{ fVarList.push_back( var ); }
	else if( var=="dirv" )				{ fVarList.push_back( var ); }
	else if( var=="wallv" )				{ fVarList.push_back( var ); }

	else if( var=="mode" )				{ fVarList.push_back( var ); }	// <NEWORK>
	else if( var=="numnu" )				{ fVarList.push_back( var ); }
	else if( var=="pnu" )				{ fVarList.push_back( var ); }
	else if( var=="Npvc" )				{ fVarList.push_back( var ); }
	else if( var=="pnu" )				{ fVarList.push_back( var ); }
	else if( var=="dirnu" )				{ fVarList.push_back( var ); }

	else if( var=="Npvc" )				{ fVarList.push_back( var ); }	// <VCWORK>
	else if( var=="Ipvc" )				{ fVarList.push_back( var ); }
	else if( var=="Ichvc" )				{ fVarList.push_back( var ); }
	else if( var=="Abspvc" )			{ fVarList.push_back( var ); }

	else if( var=="nscndprt" )			{ fVarList.push_back( var ); }	// <CONVVECT>
	else if( var=="iprtscnd" )			{ fVarList.push_back( var ); }
	else if( var=="iprntprt" )			{ fVarList.push_back( var ); }
	else if( var=="lmecscnd" )			{ fVarList.push_back( var ); }
	else if( var=="vtxscnd" )			{ fVarList.push_back( var ); }
	else if( var=="tscnd" )				{ fVarList.push_back( var ); }
	else
	{
		cout<<" [ERROR] SKh1Variables::resisterVariable "	<<endl;
		cout<<"   - " << var <<" is not supported yet. "	<<endl;
		cout<<" -> EXIT "									<<endl;
		exit( -1 );
	}
}
//
//---------- Methods to acces variables from outside this class
//

bool SKh1Variables::isSupported(string var)
{
	bool tmp=false;
	for(int i=0; i<(int)fVarList.size(); i++)
	{
		if( var==fVarList[i] )
		{
			tmp=true;
			break;
		}
	}
	return tmp;
}


template <typename T> T SKh1Variables::var(string var) const
{
	T t;
	if( std::is_same<T, int>::value )
	{
		if(	     var=="nhitac" )			{ t=fnhitac; }
		else if( var=="evclass" )			{ t=fevclass; }
		else if( var=="nspill" )			{ t=fnspill; }
		else if( var=="good_spill_flag" )	{ t=fgood_spill_flag; }
		else if( var=="fqnse" )				{ t=ffqnse; }
		else if( var=="mode" )				{ t=fmode; }
		else if( var=="numnu" )				{ t=fnumnu; }
		else if( var=="npar" )				{ t=fnpar; }
		else if( var=="Npvc" )				{ t=fNpvc; }
		else if( var=="nscndprt" )			{ t=fnscndprt; }
		else								{ printError(var); }
	}
	else
	{
		if(	     var=="wallv" )		{ t=fwallv; }
		else						{ printError(var); }
	}
	return t;
}


template<typename T> T SKh1Variables::var(string var, int i) const
{
	T t;
	if( std::is_same<T, int>::value )
	{
		if(	     var=="fqmrnring" )	{ t=ffqmrnring[i]; }
		else if( var=="ipv" )		{ t=fipv[i]; }
		else if( var=="ipnu" )		{ t=fipnu[i]; }
		else if( var=="Ipvc" )		{ t=fIpvc[i]; }
		else if( var=="Ichvc" )		{ t=fIchvc[i]; }
		else if( var=="iprtscnd" )	{ t=fiprtscnd[i]; }
		else if( var=="iprntprt" )	{ t=fiprntprt[i]; }
		else if( var=="lmecscnd" )	{ t=flmecscnd[i]; }
		else						{ printError(var); }
	}
	else
	{
		if(	     var=="pmomv" )		{ t=fpmomv[i]; }
		else if( var=="posv" )		{ t=fposv[i]; }
		else if( var=="pnu" )		{ t=fpnu[i]; }
		else if( var=="Abspvc" )	{ t=fAbspvc[i]; }
		else if( var=="tscnd" )		{ t=ftscnd[i]; }
		else						{ printError(var); }
	}
	return t;
}

template <typename T> T SKh1Variables::var(string var, int i, int j) const
{
	T t;
	if(	     var=="dirv" )		{ t=fdirv[i][j]; }
	else if( var=="fq1rmom" )	{ t=ffq1rmom[i][j]; }
	else if( var=="fq1rnll" )	{ t=ffq1rnll[i][j]; }
	else if( var=="dirnu" )		{ t=fdirnu[i][j]; }
	else if( var=="vtxscnd" )	{ t=fvtxscnd[i][j]; }
	else						{ printError(var); }
	return t;
}


template <typename T> T SKh1Variables::var(string var, int i, int j, int k) const
{
	T t;
	if(	     var=="fq1rpos" )	{ t=ffq1rpos[i][j][k]; }
	else if( var=="fq1rdir" )	{ t=ffq1rdir[i][j][k]; }
	else						{ printError(var); }
	return t;
}

template int SKh1Variables::var<int>(string) const;
template float SKh1Variables::var<float>(string) const;
template int SKh1Variables::var<int>(string, int) const;
template float SKh1Variables::var<float>(string, int) const;
template float SKh1Variables::var<float>(string, int, int) const;
template float SKh1Variables::var<float>(string, int, int, int) const;



void SKh1Variables::printError(string var) const
{
		cout<<" [ERROR] SKh1Variables::var "				<<endl;
		cout<<"   - " << var <<" is not supported yet. "	<<endl;
		cout<<" -> EXIT "									<<endl;
		exit( -1 );
}

//
//---------- Some default setting 
//
void SKh1Variables::resisterDefaultDST()
{
	this->resisterVariable("nhitac");
}


void SKh1Variables::resisterDefaultT2KREDUC()
{
	this->resisterVariable("evclass");
	this->resisterVariable("nspill");
	this->resisterVariable("good_spill_flag");
}


void SKh1Variables::resisterDefaultfiTQun()
{
	this->resisterVariable("fqmrnring");
	this->resisterVariable("fq1rmom");
	this->resisterVariable("fq1rpos");
	this->resisterVariable("fq1rdir");
	this->resisterVariable("fq1rnll");
	this->resisterVariable("fqnse");
}


void SKh1Variables::resisterDefaultVECT()
{
	this->resisterVariable("npar");
	this->resisterVariable("pmomv");
	this->resisterVariable("ipv");
	this->resisterVariable("ipnu");
	this->resisterVariable("posv");
	this->resisterVariable("dirv");
	this->resisterVariable("wallv");
}


void SKh1Variables::resisterDefaultNEWORK()
{
	this->resisterVariable("mode");
	this->resisterVariable("numnu");
	this->resisterVariable("ipnu");
	this->resisterVariable("pnu");
	this->resisterVariable("dirnu");
}


void SKh1Variables::resisterDefaultVCWORK()
{
	this->resisterVariable("Npvc");
	this->resisterVariable("Ipvc");
	this->resisterVariable("Ichvc");
	this->resisterVariable("Abspvc");
}


void SKh1Variables::resisterDefaultCONVVECT()
{
	this->resisterVariable("nscndprt");
	this->resisterVariable("iprtscnd");
	this->resisterVariable("iprntprt");
	this->resisterVariable("lmecscnd");
	this->resisterVariable("vtxscnd");
	this->resisterVariable("tscnd");
}
