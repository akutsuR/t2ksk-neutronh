#include "ROOTStyle.h"
string TopDir="/disk02/usr6/rakutsu/t2k/compact/ncount/files/nmeas";

void pltTotAveNeutrons()
{
ROOTStyle::SetROOTStyle();

	string sf="";
	sf=TopDir + "/nmeas_results.2019May.conststaterr.root";
	TGraphErrors *gmc[2];
	TGraphAsymmErrors *gda_stat	=NULL;
	TGraphAsymmErrors *gda_sys	=NULL;
	TGraphAsymmErrors *gda_sys_2=NULL;
	TGraphAsymmErrors *gda_tot	=NULL;

	TFile *f=TFile::Open(sf.c_str(), "read");
		gmc[0]		=(TGraphErrors*)f->Get("gTotAveMC_fhc");
		gmc[1]		=(TGraphErrors*)f->Get("gTotAveMC_rhc");
		gda_stat	=(TGraphAsymmErrors*)f->Get("gTotAveData_stat");
		gda_sys		=(TGraphAsymmErrors*)f->Get("gTotAveData_sys");
		gda_sys_2	=(TGraphAsymmErrors*)f->Get("gTotAveData_sys");
		gda_tot		=(TGraphAsymmErrors*)f->Get("gTotAveData_statsys");
	f->Close();
///////////////////////////////////////////////////

	gda_tot->SetLineWidth( 1 );
	gda_sys->SetLineWidth( 4 );
	gda_sys_2->SetLineWidth( 4 );
	gda_sys->SetLineColor( kGray+2 );
	gda_sys_2->SetLineColor( kGray+2 );

	Double_t ymax=2.5;

	TCanvas *c=NULL;
	c=new TCanvas();
	c->SetTopMargin( 0.05 );
	c->SetBottomMargin( 0.15 );
	c->SetLeftMargin( 0.15 );
	c->SetRightMargin( 0.05 );
	c->SetTicks(1);

	TH1F *frm=new TH1F("frm", "", 2, 0, 2);
	frm->GetYaxis()->SetRangeUser(0.0, ymax);
	frm->GetXaxis()->CenterTitle();
	frm->GetYaxis()->CenterTitle();
	frm->GetXaxis()->SetTitleOffset(1.0);
	frm->GetYaxis()->SetTitleOffset(0.8);
	frm->GetXaxis()->SetLabelOffset(0.01);
	frm->GetYaxis()->SetTitleSize(0.065);
	frm->GetXaxis()->SetTitleSize(0.065);
	//frm->GetYaxis()->SetTitle( "# neutrons/#nu event" );
	frm->GetYaxis()->SetTitle( "Mean neutron multiplicity" );
	frm->SetStats(0);
	frm->GetXaxis()->SetLabelSize(0.125);
	frm->GetXaxis()->SetBinLabel(1, Form("#color[%d]{#bf{FHC}}", kBlue+2));
	frm->GetXaxis()->SetBinLabel(2, Form("#color[%d]{#bf{RHC}}", kRed+2));
	frm->Draw();
	gmc[0]->Draw("2 same");
	gmc[1]->Draw("2 same");
	gda_tot->Draw("p");
//	gda_sys_2->Draw("p");
	gda_sys->Draw("[]");
//////////////////////////////////////////////////////////////////////
	Double_t da[2];
	Double_t daStat[2];
	Double_t daSysU[2];
	Double_t daSysL[2];
	Double_t mc[2];
	Double_t mcErr[2];
	Double_t x=0.0,
			 y=0.0;
	for(Int_t i=0; i<2; i++)
	{
		gmc[i]->GetPoint(0, x, y);
		mc[i]=y;
		mcErr[i]=gmc[i]->GetErrorY(0);

		gda_stat->GetPoint(i, x, y);
		da[i]=y;
		//daStat[i]=gda_stat->GetErrorYhigh(i);
		daStat[i]=gda_stat->GetErrorYlow(i);
		daSysU[i]=gda_sys->GetErrorYhigh(i);
		daSysL[i]=gda_sys->GetErrorYlow(i);
	}

	TLatex tx;
	tx.SetTextSize( 0.05 );
	tx.DrawLatex(0.1, 2.3, "#bf{T2K Runs 1-9 data}");
	tx.SetTextSize( 0.03 );
	tx.DrawLatex(0.1, 2.15,  "#bf{   - Using 1R#nu_{#mu} sample}");
	tx.DrawLatex(0.1, 2.00,  "#bf{   - Acc. bkg. subtracted}");
	tx.DrawLatex(0.1, 1.85,  "#bf{   - Efficiency corrected}");

	tx.SetTextSize( 0.035 );
	tx.DrawLatex(0.535,	1.05, "#bf{Sys.}");
	tx.DrawLatex(0.535, 1.205, "#bf{Stat. #oplus Sys.}");
	tx.DrawLatex(1.535,	1.45, "#bf{Sys.}");
	tx.DrawLatex(1.535, 1.725, "#bf{Stat. #oplus Sys.}");


	tx.SetTextSize( 0.0375 );
	tx.DrawLatex(0.075, 0.3, Form("#color[%d]{#bf{Exp.}}#bf{ = %3.2f #pm %3.2f(Stat.)}", kBlue-4, mc[0], mcErr[0]));
	tx.DrawLatex(0.075, 0.1, Form("#bf{Obs.}#bf{ = %3.2f #pm %3.2f(Stat.) ^{+%3.2f}_{-%3.2f}(Sys.)}", da[0], daStat[0], daSysU[0], daSysL[0]));

	tx.DrawLatex(1.075, 0.3, Form("#color[%d]{#bf{Exp.}}#bf{ = %3.2f #pm %3.2f(Stat.)}", kRed-4, mc[1], mcErr[1]));
	tx.DrawLatex(1.075, 0.1, Form("#bf{Obs.}#bf{ = %3.2f #pm %3.2f(Stat.) ^{+%3.2f}_{-%3.2f}(Sys.)}", da[1], daStat[1], daSysU[1], daSysL[1]));

	string spn="totaven_2019may.png";
    c->Print("~/public_html/tmp.png");
	//c->Print( Form("%s/plots/06_data/%s", TopDir.c_str(), spn.c_str()) );
}
