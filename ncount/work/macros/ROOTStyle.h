#pragma once

#include "TStyle.h"
#include "TColor.h"

namespace ROOTStyle {

void SetROOTStyle(Bool_t isRBOnly=0)
{

  gROOT->SetStyle("Plain");
  TStyle* t2kstyle = new TStyle("T2K","T2K approved plots style");

  // use plain black on white colors
  t2kstyle->SetFrameBorderMode(0);
  t2kstyle->SetCanvasBorderMode(0);
  t2kstyle->SetPadBorderMode(0);
  t2kstyle->SetPadColor(0);
  t2kstyle->SetCanvasColor(0);

  // use large Times-Roman fonts
  t2kstyle->SetTextFont(132);
  t2kstyle->SetTitleFont(132);
  t2kstyle->SetTextSize(0.08);
  t2kstyle->SetLabelFont(132,"x");
  t2kstyle->SetLabelFont(132,"y");
  t2kstyle->SetLabelFont(132,"z");
  t2kstyle->SetLabelFont(132,"t");
  t2kstyle->SetLabelSize(0.05,"x");
  t2kstyle->SetLabelSize(0.05,"y");
  t2kstyle->SetLabelSize(0.05,"z");
  t2kstyle->SetTitleSize(0.04,"x");
  t2kstyle->SetTitleSize(0.04,"y");
  t2kstyle->SetTitleSize(0.04,"z");
  t2kstyle->SetTitleFont(132,"x");
  t2kstyle->SetTitleFont(132,"y");
  t2kstyle->SetTitleFont(132,"z");
  t2kstyle->SetTitleFont(132,"t");
  t2kstyle->SetTitleFillColor(0);
  t2kstyle->SetTitleX(0.25);
  t2kstyle->SetTitleFontSize(0.08);
  t2kstyle->SetTitleFont(132,"pad");
  t2kstyle->SetLineStyleString(2,"[12 12]"); // postscript dashes

    const Int_t NCont = 255;
    if( !isRBOnly )
    {
        const Int_t NRGBs = 5;
        Double_t stops[NRGBs] = { 0.00, 0.34, 0.61, 0.84, 1.00 };
        Double_t red[NRGBs]   = { 0.00, 0.00, 0.87, 1.00, 0.51 };
        Double_t green[NRGBs] = { 0.00, 0.81, 1.00, 0.20, 0.00 };
        Double_t blue[NRGBs]  = { 0.51, 1.00, 0.12, 0.00, 0.00 };
        TColor::CreateGradientColorTable(NRGBs, stops, red, green, blue, NCont);
        t2kstyle->SetNumberContours(NCont);
    }
    else
    {
        UInt_t Number = 3;
        Double_t red[3]   = { 0.1, 0.4, 0.95};
        Double_t green[3] = { 0.1, 1.0, 1.0};
        Double_t blue[3]  = { 1.0, 0.55, 0.15};
        Double_t stops[3] = { 0.0, 0.5, 1.0 };

        TColor::CreateGradientColorTable(Number, stops, red, green, blue, 255);
        t2kstyle->SetNumberContours(NCont);
    }
  gROOT->SetStyle("T2K");
}
}
