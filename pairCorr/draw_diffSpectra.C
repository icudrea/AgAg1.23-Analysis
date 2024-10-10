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


void setOPT_hists2D(TH2F *hist, TString xAxisTitle=" ", TString yAxisTitle=" ", Int_t NCont=255, Int_t Ndevision=510)
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
		char* cH2, TH2D* h2,
        char* cH3, TH2D* h3,
        char* cH4, TH2D* h4
        
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
    if (h3) legmass->AddEntry(h3,cH3,"p");
    if (h4) legmass->AddEntry(h4,cH4,"p");
    
 
    legmass->Draw("same");
}

//-------------------------------------------------------------
//-------------------------------------------------------------

    void setOPT_TH1F(TH1D *hist, TString xAxisTitle=" ", TString yAxisTitle=" ", Int_t Ndevision=510, Int_t marker_style =20, Float_t marker_size =1, Int_t color=1)
    {
        hist->GetXaxis()->SetTitle(xAxisTitle);
        hist->GetYaxis()->SetTitle(yAxisTitle);
        hist->GetXaxis()->SetTitleSize(0.06);
        hist->GetYaxis()->SetTitleSize(0.06);
        hist->GetXaxis()->SetTitleFont(42);
        hist->GetYaxis()->SetTitleFont(42);
        hist->GetXaxis()->SetNdivisions(Ndevision);
        hist->GetYaxis()->SetTitleOffset(0.6);
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
        hist->SetLineWidth(1);
        hist->SetFillColor(10);
    }



void draw_diffSpectra()
{

TFile *file1 = new TFile("/u/icudrea/lustre/hades/user/icudrea/mar19/loop/phd/Eff_wNewCuts/EffCorr_spectras_ag123ag_Smear_3sigma_oAngle4_alldays_OldCuts_WEffCorr.root");
TFile *file2 = new TFile("/u/icudrea/lustre/hades/user/icudrea/mar19/loop/phd/Eff_wNewCuts/EffCorr_spectras_ag123ag_Smear_3sigma_oAngle5_alldays_OldCuts_WEffCorr.root");
TFile *file3 = new TFile("/u/icudrea/lustre/hades/user/icudrea/mar19/loop/phd/Eff_wNewCuts/EffCorr_spectras_ag123ag_Smear_3sigma_oAngle5Mom100_alldays_OldCuts_WEffCorr.root"); 
TFile *file4 = new TFile("/u/icudrea/lustre/hades/user/icudrea/mar19/loop/phd/Eff_wNewCuts/EffCorr_spectras_ag123ag_Smear_3sigma_oAngle9Mom100_alldays_OldCuts_WEffCorr.root"); 
TFile *file5 = new TFile("/u/icudrea/lustre/hades/user/icudrea/mar19/loop/phd/Eff_wNewCuts/EffCorr_spectras_ag123ag_Smear_3sigma_oAngle9_alldays_OldCuts_WEffCorr.root");
   Int_t bins=300;

    TH2D* h_Signal_epem_opa4 = (TH2D*) file1->Get("h_Signal_epem");
    TH2D* h_Signal_epem_opa5 = (TH2D*) file2->Get("h_Signal_epem");
    TH2D* h_Signal_epem_opa9 = (TH2D*) file5->Get("h_Signal_epem");

    TH2D* h_Signal_epem_opa5mom100 = (TH2D*) file3->Get("h_Signal_epem");
    TH2D* h_Signal_epem_opa9mom100 = (TH2D*) file4->Get("h_Signal_epem");

    TH1D* h_kFactor = (TH1D*) file4->Get("h_kFactor");

    setOPT_TH1F(h_kFactor,"M_{ee} [GeV/c^{2}]","k-factor",505,505);

    TCanvas *cansys1 = new TCanvas("cansys1", "",900,900);
    setOPT_canvas2D(cansys1);
    cansys1->SetFillColor(10);
    cansys1->SetTopMargin(0.08);
    cansys1->SetRightMargin(0.12);
    cansys1->SetLeftMargin(0.14);
    cansys1->SetLogy();

   // h_Signal_epem_opa4 ->SetMarkerColor(kBlue);
    h_Signal_epem_opa5 ->SetMarkerColor(kMagenta);
    h_Signal_epem_opa9 ->SetMarkerColor(93);
    h_Signal_epem_opa5mom100 ->SetMarkerColor(kBlue);
    h_Signal_epem_opa9mom100 ->SetMarkerColor(kRed);

    // h_Signal_epem_opa9mom100  ->SetMarkerSize(0.9);
    // h_Signal_epem_opa9        ->SetMarkerSize(0.8);

    //h_Signal_epem_opa4 ->SetMarkerStyle(21);
    h_Signal_epem_opa5 ->SetMarkerStyle(21);
    h_Signal_epem_opa9 ->SetMarkerStyle(21);

    h_Signal_epem_opa5mom100 ->SetMarkerStyle(22);
    h_Signal_epem_opa9mom100 ->SetMarkerStyle(22);


    h_Signal_epem_opa5mom100 ->SetMarkerSize(1.8);
    h_Signal_epem_opa9mom100 ->SetMarkerSize(1.2);
  
  

   // h_Signal_epem_opa4 ->SetMarkerSize(1);
    h_Signal_epem_opa5 ->SetMarkerSize(1);
    h_Signal_epem_opa9 ->SetMarkerSize(1.5);


 
    
    //h_Signal_epem_opa4 ->GetYaxis()->SetRangeUser(1e-8,1e-2);
    h_Signal_epem_opa5 ->GetYaxis()->SetRangeUser(1e-6,1e-2);
    h_Signal_epem_opa9 ->GetYaxis()->SetRangeUser(1e-6,1e-2);

    h_Signal_epem_opa5 ->GetXaxis()->SetRangeUser(0,0.6);
    h_Signal_epem_opa9 ->GetXaxis()->SetRangeUser(0,0.6);
   
   
    h_Signal_epem_opa5 ->Draw();
    h_Signal_epem_opa9->Draw("same");
    h_Signal_epem_opa5mom100 ->Draw("same");
    h_Signal_epem_opa9mom100 ->Draw("same");
    h_Signal_epem_opa5 ->Draw("same");





        setLegend3("#alpha_{ee} > 5^{o}", h_Signal_epem_opa5,
                   "#alpha_{ee} > 9^{o}",h_Signal_epem_opa9,
                   "#alpha_{ee} > 5^{o}, p >100 MeV/#it{c}",h_Signal_epem_opa5mom100,
                   "#alpha_{ee} > 9^{o}, p >100 MeV/#it{c}",h_Signal_epem_opa9mom100

          

  );

  TCanvas *can = new TCanvas("can", "",900,900);
    setOPT_canvas2D(can);
    can->SetFillColor(10);
    can->SetTopMargin(0.08);
    can->SetRightMargin(0.12);
    can->SetLeftMargin(0.15);
    h_kFactor->GetXaxis()->SetRangeUser(0,1);
    h_kFactor->GetYaxis()->SetRangeUser(0.8,1.1);
    h_kFactor->SetMarkerStyle(22);
    h_kFactor->SetMarkerSize(1.2);
     h_kFactor->SetMarkerColor(kRed);

    h_kFactor->GetYaxis()->SetTitleOffset(1.2);

    //can->SetLogy();
   h_kFactor->Draw("p");

 }


