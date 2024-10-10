#include "TMath.h"
#include "Math/IFunction.h"
#include "Math/SpecFuncMathMore.h"

    void setOPT_TH2D(TH2D *hist, TString xAxisTitle=" ", TString yAxisTitle=" ", Int_t NCont=255, Int_t Ndevision=510)
    {
        hist->GetXaxis()->SetTitle(xAxisTitle);
        hist->GetYaxis()->SetTitle(yAxisTitle);
        hist->GetXaxis()->SetTitleSize(0.06);
        hist->GetYaxis()->SetTitleSize(0.06);
        hist->GetXaxis()->SetTitleFont(42);
        hist->GetYaxis()->SetTitleFont(42);
        hist->GetXaxis()->SetNdivisions(Ndevision);
        hist->GetYaxis()->SetTitleOffset(1);
        //hist->GetXaxis()->CenterTitle();
        //hist->GetYaxis()->CenterTitle();
        hist->GetXaxis()->SetLabelFont(42);
        hist->GetYaxis()->SetLabelFont(42);
        hist->GetXaxis()->SetLabelSize(0.04);
        hist->GetYaxis()->SetLabelSize(0.04);
        hist->SetTitle("");
        hist->SetLineWidth(2);
            

        Int_t MyPalette[100];
        const Int_t NRGBs = 5;
        Double_t stops[NRGBs] = { 0.00, 0.34, 0.61, 0.84, 1.00 };
        Double_t reds[NRGBs] = { 0.00, 0.00, 0.87, 1.00, 0.51 };
        Double_t greens[NRGBs] = { 0.00, 0.81, 1.00, 0.20, 0.00 };
        Double_t blues[NRGBs] = { 0.51, 1.00, 0.12, 0.00, 0.00 };
        Int_t FI = TColor::CreateGradientColorTable(NRGBs, stops, reds,greens, blues, NCont);
    

    gStyle->SetNumberContours(NCont);



    }
void setOPT_canvas(TCanvas *canvas)
{
    gStyle->SetOptStat(0);
    gStyle->SetEndErrorSize(5);
    gStyle->SetErrorX(0);    // X errors of the data points set to be 0
    gStyle->SetLineStyleString(22,"80 18 12 18 12 12"); // special style for the line
    gStyle->SetEndErrorSize(5);   // define end width of error bars
    gStyle->SetCanvasColor(10);
    gStyle->SetPadColor(10);
    canvas->SetLeftMargin(0.15);
    canvas->SetRightMargin(0.05);
    canvas->SetTopMargin(0.05);
    canvas->SetBottomMargin(0.15);
    canvas->ToggleEventStatus();
    canvas->Range(-800,-10,1000,-2);
    canvas->SetFillColor(0);
    canvas->SetBorderMode(0);
    canvas->SetBorderSize(0);
    canvas->SetTickx();
    canvas->SetTicky();
    canvas->SetLogy();
    canvas->SetFrameLineWidth(2);
    canvas->SetFrameBorderMode(0);
    canvas->SetFrameBorderSize(0);
}
void setOPT_canvas2D(TCanvas *canvas)
{
    gStyle->SetOptStat(0);
    gStyle->SetEndErrorSize(5);
    gStyle->SetErrorX(0);    // X errors of the data points set to be 0
    gStyle->SetLineStyleString(22,"80 18 12 18 12 12"); // special style for the line
    gStyle->SetEndErrorSize(5);   // define end width of error bars
    gStyle->SetCanvasColor(10);
    gStyle->SetPadColor(10);
	gStyle->SetPalette(55);    
    canvas->SetLeftMargin(0.15);
    canvas->SetRightMargin(0.12);
    canvas->SetTopMargin(0.05);
    canvas->SetBottomMargin(0.15);
    canvas->ToggleEventStatus();
    canvas->Range(-800,-10,1000,-2);
    canvas->SetFillColor(0);
    canvas->SetBorderMode(0);
    canvas->SetBorderSize(0);
    canvas->SetTickx();
    canvas->SetTicky();
    canvas->SetFrameLineWidth(2);
    canvas->SetFrameBorderMode(0);
    canvas->SetFrameBorderSize(0);
}


void setOPT_hists2D(TH2D *hist, TString xAxisTitle=" ", TString yAxisTitle=" ", Int_t NCont=255, Int_t Ndevision=510)
{
    hist->GetXaxis()->SetTitle(xAxisTitle);
    hist->GetYaxis()->SetTitle(yAxisTitle);
    hist->GetXaxis()->SetTitleSize(0.06);
    hist->GetYaxis()->SetTitleSize(0.06);
    hist->GetZaxis()->SetTitleSize(0.06);
    hist->GetXaxis()->SetTitleFont(42);
    hist->GetYaxis()->SetTitleFont(42);
    hist->GetZaxis()->SetTitleFont(42);
    hist->GetXaxis()->SetNdivisions(Ndevision);
    hist->GetYaxis()->SetTitleOffset(1.16);
    hist->GetXaxis()->SetLabelFont(42);
    hist->GetYaxis()->SetLabelFont(42);
    hist->GetZaxis()->SetLabelFont(42);
    hist->GetXaxis()->SetLabelSize(0.05);
    hist->GetYaxis()->SetLabelSize(0.05);
    hist->GetZaxis()->SetLabelSize(0.04);
    hist->SetTitle("");
    gStyle->SetNumberContours(NCont);
}

// To set style of the legend
// In this example three labels are used, so one might need to adjust for plots with fewer/more labels
void setLegend(TString cH1, TH1F* h1,
	       TString cH2, TH1F* h2,
	       TString cH3, TH1F* h3)
{
    TLegend *legmass = new TLegend(0.7, 0.6, 0.8, 0.72);
    legmass->SetLineColor(10);
    legmass->SetLineStyle(1);
    legmass->SetLineWidth(1);
    legmass->SetFillColor(10);
    legmass->SetTextSize(0.04);
    legmass->SetTextFont(42);
    legmass->SetMargin(0.4);
    legmass->SetBorderSize(0);
    if (h1) legmass->AddEntry(h1,cH1,"p");
    if (h2) legmass->AddEntry(h2,cH2,"p");
    if (h3) legmass->AddEntry(h3,cH3,"p");
    legmass->Draw("same");
}

// To add text and labels in the plots
void setHadesWorkInProgress()
{
    TLatex* tex = new TLatex(0.3, 5e-4,"HADES Work In Progress");
    tex->SetTextFont(42);
    tex->SetTextSize(0.04);
    tex->SetLineWidth(3);
    tex->Draw();
}
void setMainTitle()
{
    TLatex* tex = new TLatex(0.3, 2e-4,"Ag+Ag #sqrt{s_{NN}}=2.55 GeV 0-40%");
    tex->SetTextFont(42);
    tex->SetTextSize(0.04);
    tex->SetLineWidth(3);
    tex->Draw();
}

void setMomTitle()
{
    TLatex* tex2 = new TLatex(0.3,6e-5,"100 GeV/#font[52]{c} < #font[52]{p}_{ee} < 1800 GeV/#font[52]{c}");
    tex2->SetTextFont(42);
    tex2->SetTextSize(0.04);
    tex2->SetLineWidth(3);
    tex2->Draw();
}

void setLegend3(char* cH1, TH2D* h1,
		char* cH2, TH2D* h2
       
        
	)
{
    TLegend *legmass = new TLegend(0.56, 0.63, 0.70, 0.88);
    legmass->SetLineColor(10);
    legmass->SetLineStyle(1);
    legmass->SetLineWidth(1);
    legmass->SetFillColor(10);
    legmass->SetTextSize(0.03);
    legmass->SetTextFont(42);
    legmass->SetMargin(0.4);
    legmass->SetBorderSize(0);
    if (h1) legmass->AddEntry(h1,cH1,"p");
    if (h2) legmass->AddEntry(h2,cH2,"p");
  
    
 
    legmass->Draw("same");
}


void setOPT_hists(TH1F *hist, TString xAxisTitle=" ", TString yAxisTitle=" ", Int_t Ndevision=510, Int_t marker_style =20, Float_t marker_size =1.3, Int_t color=1)
{
    hist->GetXaxis()->SetTitle(xAxisTitle);
    hist->GetYaxis()->SetTitle(yAxisTitle);
    hist->GetXaxis()->SetTitleSize(0.06);
    hist->GetYaxis()->SetTitleSize(0.06);
    hist->GetXaxis()->SetTitleFont(42);
    hist->GetYaxis()->SetTitleFont(42);
    hist->GetXaxis()->SetNdivisions(Ndevision);
    hist->GetYaxis()->SetTitleOffset(1.5);
    //hist->GetXaxis()->CenterTitle();
    //hist->GetYaxis()->CenterTitle();
    hist->GetXaxis()->SetLabelFont(42);
    hist->GetYaxis()->SetLabelFont(42);
    hist->GetXaxis()->SetLabelSize(0.05);
    hist->GetYaxis()->SetLabelSize(0.05);
    hist->SetMarkerStyle(marker_style);
    hist->SetMarkerSize(marker_size);
    hist->SetMarkerColor(color);
    hist->SetLineColor(color);
    hist->SetTitle("");
    hist->SetLineWidth(2);
}
//-------------------------------------------------------------
//-------------------------------------------------------------




void draw_ratioPi0()
{


  TFile *file_new = new TFile("~/march19AgAg/submit/EffCorrection/cocktail/pi0/scaled_0515pi0_SmearMomOnly_9oAngle100Mom_allCC.root");
  TFile *file_old = new TFile("~/march19AgAg/submit/EffCorrection/cocktail/pi0/scaled_pi0_SmearMomOnly_9oAngle100Mom_allCC.root");

  TH2D* h_mass_acc_pi0_new   = (TH2D*) file_new->Get("h_mass_acc_pi0_CCTotal");
  TH2D* h_mass_acc_pi0_old   = (TH2D*) file_old->Get("h_mass_acc_pi0_CCTotal");

  setOPT_hists2D(h_mass_acc_pi0_new,"M_{ee} (GeV/c^{2})","Cocktail Corr./ CG Corr.",510,510);


  TCanvas *canDivide = new TCanvas("canDivide", "",158,28,900,1018);
  canDivide->SetFillColor(10);
  canDivide->SetTopMargin(0.08);
  canDivide->SetRightMargin(0.12);

  TH1D* h_mass_acc_pi0_new_1d    =  (TH1D*) h_mass_acc_pi0_new->Clone("h_mass_acc_pi0_new_1d");
  h_mass_acc_pi0_new_1d->GetYaxis()->SetRangeUser(0,2.);

  TH1D* h_h_mass_acc_pi0_old_1d  =  (TH1D*) h_mass_acc_pi0_old->Clone("h_h_mass_acc_pi0_old_1d");
  h_h_mass_acc_pi0_old_1d->GetYaxis()->SetRangeUser(0,2.);

  h_mass_acc_pi0_new_1d->Divide(h_h_mass_acc_pi0_old_1d);
 /// h_Signal_epem_singleEff_1d->Scale(100);
  h_mass_acc_pi0_new_1d->GetYaxis()->SetRangeUser(0, 2.);
  h_mass_acc_pi0_new_1d->GetXaxis()->SetRangeUser(0, 0.2);
  h_mass_acc_pi0_new_1d->Draw("l");


    // TCanvas *can1 = new TCanvas("can1", "",158,28,900,1018);
    // setOPT_canvas2D(can1);
    // can1->SetFillColor(10);
    // can1->SetTopMargin(0.08);
    // can1->SetRightMargin(0.12);
    // can1->SetLeftMargin(0.14);
    // can1->SetLogy();

    // h_Signal_epem_singleEff->SetMarkerStyle(21);
    // h_Signal_epem_pairEff->SetMarkerStyle(21);
    // h_Signal_epem_singleEff->SetMarkerColor(kRed);
    // h_Signal_epem_pairEff->SetMarkerColor(kBlue);

    // h_Signal_epem_singleEff ->Draw();
    // h_Signal_epem_pairEff->Draw("same");

    // setLegend3("Pair Corection w. CG rho", h_Signal_epem_singleEff,
    //                "Pair Corection w. cocktail",h_Signal_epem_pairEff
    // );
 }


