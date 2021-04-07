#include <iomanip>

string TopDir="/disk02/usr6/rakutsu/t2k/compact/ncount/files/nmeas";

void printMeasurementResults()
{
	string sf="";
	sf=TopDir + "/nmeas_results.2019May.conststaterr.root";

    for(Int_t i=0; i<2; i++)
    { 
	    TGraphErrors *gm_av_stat		=NULL;
	    TGraphErrors *gm_tr_stat		=NULL;
	    TGraphAsymmErrors *gda_av_stat	=NULL;
	    TGraphAsymmErrors *gda_av_syst	=NULL;
	    TGraphAsymmErrors *gda_tr_stat	=NULL;
	    TGraphAsymmErrors *gda_tr_syst	=NULL;

	    string sm="fhc";
	    if( i==1 ){ sm="rhc"; }

	    TFile *f=TFile::Open(sf.c_str(), "read");
	    	gmc_av_stat		=(TGraphErrors*)f->Get( Form("gTotAveMC_%s", sm.c_str()) );
	    	gmc_tr_stat		=(TGraphErrors*)f->Get( Form("gTrMomAveMC_%s", sm.c_str()) );
	    	gda_av_stat		=(TGraphAsymmErrors*)f->Get( Form("gTotAveData_stat", sm.c_str()) );
	    	gda_av_syst		=(TGraphAsymmErrors*)f->Get( Form("gTotAveData_sys", sm.c_str()) );
	    	gda_tr_stat		=(TGraphAsymmErrors*)f->Get( Form("gTrMomAveData_%s_stat", sm.c_str()) );
	    	gda_tr_syst		=(TGraphAsymmErrors*)f->Get( Form("gTrMomAveData_%s_sys", sm.c_str()) );
	    f->Close();

	    Int_t n=gda_tr_stat->GetN();
	    Double_t xda, yda, xmc, ymc;
	    Double_t eStatDA, eStatMC;
	    Double_t eSystU, eSystL;

	    std::cout<<std::setprecision(2);
	    std::cout<<std::fixed;
        std::string smom = "";
	    cout<<endl;
	    for(Int_t j=0; j<n; j++)
	    {
	    	gda_tr_stat->GetPoint(j, xda, yda);
	    	gmc_tr_stat->GetPoint(j, xmc, ymc);
	    	eStatDA=gda_tr_stat->GetErrorY(j);
	    	eSystU=gda_tr_syst->GetErrorYhigh(j);
	    	eSystL=gda_tr_syst->GetErrorYlow(j);
	    	eStatMC=gmc_tr_stat->GetErrorY(j);
	    	
            if( j==0 ){ smom = "trmomi"; }
            else if( j==1 ){ smom = "trmomii"; }
            else if( j==2 ){ smom = "trmomiii"; }
            else if( j==3 ){ smom = "trmomiv"; }
            string smc = "\\exp" + sm + smom;
            string sda = "\\obs" + sm + smom;
	    	cout<<"\\newcommand{" << smc 
                <<"}{" << ymc 
                <<" \$\\pm\$" << eStatMC 
                <<"}" <<endl;
            cout<<"\\newcommand{" << sda
                <<"}{" << yda
                <<" \$\\pm\$ "   << eStatDA
	    		<<" \$^{+" << eSystU <<"}_{-" << eSystL <<"}\$}" <<endl;
	    }


	    Int_t idx=0;
	    if( i==1 ){ idx=1; }	
	    gda_av_stat->GetPoint(idx, xda, yda);
	    gmc_av_stat->GetPoint(0, xmc, ymc);
        eStatMC=gmc_av_stat->GetErrorY(0);
	    eSystU=gda_av_syst->GetErrorYhigh(idx);
	    eSystL=gda_av_syst->GetErrorYlow(idx);
	    eStatDA=gda_av_stat->GetErrorYhigh(idx);

	    cout<<"\\newcommand{\\exp" << sm 
            <<"avetrmom}{" << ymc 
            <<" \$\\pm\$" << eStatMC 
            <<"}" <<endl;
        cout<<"\\newcommand{\\obs" << sm
            <<"avetrmom}{" << yda
            <<" \$\\pm\$ "   << eStatDA
	    	<<" \$^{+" << eSystU <<"}_{-" << eSystL <<"}\$}" <<endl;
    }
}
