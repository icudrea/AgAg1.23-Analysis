
#include"Functions.C"

// void setOPT_canvas(TCanvas *canvas)
// {
//     gStyle->SetOptStat(0);
//     gStyle->SetErrorX(0);    // X errors of the data points set to be 0
//     gStyle->SetLineStyleString(22,"80 18 12 18 12 12"); // special style for the line
//     gStyle->SetEndErrorSize(5);   // define end width of error bars
//     canvas->SetLeftMargin(0.14);
//     canvas->SetRightMargin(0.05);
//     canvas->SetTopMargin(0.025);
//     canvas->SetBottomMargin(0.15);
//     canvas->ToggleEventStatus();
//     canvas->SetBorderMode(0);
//     canvas->SetBorderSize(0);
//     canvas->SetTickx();
//     canvas->SetTicky();
// //    canvas->SetLogy();
//     canvas->SetFrameLineWidth(2);
//     canvas->SetFrameBorderMode(0);
//     canvas->SetFrameBorderSize(0);
//     gStyle->SetCanvasColor(10);
//     gStyle->SetPadColor(10);
//     canvas->SetFrameFillColor(10);
//     canvas->SetFillColor(10);
//     canvas->SetFrameLineColor(1);
//     //gStyle->SetAxisColor(10,"X");
//     //gStyle->SetAxisColor(10,"Y");
// }
// this function is setting the style of the plotting historgrams
// as an argument one should give name of the histogram, title of the X and Y axis
// Ndevision for the X axis, style, size and the color of the marker
// e.g for the official PRL plot for the RAW spectra of the NOV02 it was used in the following way:
// setOPT_hists(signal,20,1.3);
// setOPT_hists(background,24,1.3,2);
// setOPT_hists(unlikesign,22,1.3,4);

void setOPT_canvas(TCanvas *canvas)
{
    gStyle->SetOptStat(0);
    gStyle->SetEndErrorSize(5);
    gStyle->SetErrorX(0);    // X errors of the data points set to be 0
    gStyle->SetLineStyleString(22,"80 18 12 18 12 12"); // special style for the line
    gStyle->SetEndErrorSize(5);   // define end width of error bars
    gStyle->SetCanvasColor(10);
    gStyle->SetPadColor(10);
    canvas->SetLeftMargin(0.2);
    canvas->SetRightMargin(0.05);
    canvas->SetTopMargin(0.05);
    canvas->SetBottomMargin(0.15);
    canvas->ToggleEventStatus();
    canvas->Range(-200,-10,1000,-2);
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

void setOPT_TH1F(TH1F *hist, TString xAxisTitle=" ", TString yAxisTitle=" ", Int_t Ndevision=510, Int_t marker_style =20, Float_t marker_size =1.3, Int_t color=1)
{
    hist->GetXaxis()->SetTitle(xAxisTitle);
    hist->GetYaxis()->SetTitle(yAxisTitle);
    hist->GetXaxis()->SetTitleSize(0.06);
    hist->GetYaxis()->SetTitleSize(0.06);
    hist->GetXaxis()->SetTitleFont(42);
    hist->GetYaxis()->SetTitleFont(42);
    hist->GetXaxis()->SetNdivisions(Ndevision);
    hist->GetYaxis()->SetTitleOffset(1.2);
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
void setOPT_hists(TH1D *hist, TString xAxisTitle=" ", TString yAxisTitle=" ", Int_t Ndevision=510, Int_t marker_style =20, Float_t marker_size =1.3, Int_t color=1)
{
    hist->GetXaxis()->SetTitle(xAxisTitle);
    hist->GetYaxis()->SetTitle(yAxisTitle);
    hist->GetXaxis()->SetTitleSize(0.06);
    hist->GetYaxis()->SetTitleSize(0.06);
    hist->GetXaxis()->SetTitleFont(42);
    hist->GetYaxis()->SetTitleFont(42);
    hist->GetXaxis()->SetNdivisions(Ndevision);
    hist->GetYaxis()->SetTitleOffset(1.22);
    //hist->GetXaxis()->CenterTitle();
    //hist->GetYaxis()->CenterTitle();
    hist->GetXaxis()->SetLabelFont(42);
    hist->GetYaxis()->SetLabelFont(42);
    hist->GetXaxis()->SetLabelSize(0.05);
    hist->GetYaxis()->SetLabelSize(0.05);
    hist->SetMarkerStyle(marker_style);
    hist->SetMarkerSize(marker_size);
    hist->SetMarkerColor(color);
 //   hist->SetLineColor(color);
 //   hist->SetLineWidth(2);
    hist->SetTitle("");
    hist->GetXaxis()->SetLabelColor(1);
    hist->GetYaxis()->SetLabelColor(1);
    hist->GetXaxis()->SetTitleColor(1);
    hist->GetYaxis()->SetTitleColor(1);
    hist->SetFillColor(10);
}

// this function is setting the style of the legend
// unfortunatly here the size and place of the legend is not correctly
// setted, it dependace how many histogrmas one want to add it, and what kind
// of the final spectra one want to plot. This example is done in the way
// how it is for FIG2 in the PRL
// and an argument to this function you are giving title of the entry and the name of the histogram
// e.g. setLegend("all pairs",unlikesign,"signal",signal,"CB",background)
void setLegend(char* cH1, TH1F* h1,
	       char* cH2, TH1F* h2,
	       char* cH3, TH1F* h3,
	       char* cH4, TH1F* h4,
	       char* cH5, TH1F* h5)
{
    TLegend *legmass = new TLegend(0.68, 0.67, 0.89, 0.86);
    legmass->SetLineColor(10);
    legmass->SetLineStyle(1);
    legmass->SetLineWidth(1);
    legmass->SetFillColor(10);
    legmass->SetTextSize(0.03);
    legmass->SetTextFont(42);
    legmass->SetMargin(0.4);
    legmass->SetBorderSize(0);
    if (h1) legmass->AddEntry(h1,cH1,"l");
    if (h2) legmass->AddEntry(h2,cH2,"l");
    if (h3) legmass->AddEntry(h3,cH3,"l");
    if (h4) legmass->AddEntry(h4,cH4,"l");
    if (h5) legmass->AddEntry(h5,cH5,"l");
    legmass->Draw("same");
}
void setLegend2(char* cH1, TH1* h1,
	       char* cH2, TH1* h2)
{
    TLegend *legmass = new TLegend(0.68, 0.67, 0.89, 0.86);
    legmass->SetLineColor(10);
    legmass->SetLineStyle(1);
    legmass->SetLineWidth(1);
    legmass->SetFillColor(10);
    legmass->SetTextSize(0.03);
    legmass->SetTextFont(42);
    legmass->SetMargin(0.4);
    legmass->SetBorderSize(0);
    if (h1) legmass->AddEntry(h1,cH1,"l");
    if (h2) legmass->AddEntry(h2,cH2,"l");
    legmass->Draw("same");
}
void setLegend3(char* cH1, TH1* h1,
		char* cH2, TH1* h2,
		char* cH3, TH1* h3
	       )
{
    TLegend *legmass = new TLegend(0.28, 0.78, 0.49, 0.89);
    legmass->SetLineColor(10);
    legmass->SetLineStyle(1);
    legmass->SetLineWidth(1);
    legmass->SetFillColor(10);
    legmass->SetTextSize(0.015);
    legmass->SetTextFont(42);
    legmass->SetMargin(0.4);
    legmass->SetBorderSize(0);
    if (h1) legmass->AddEntry(h1,cH1,"pl");
    if (h2) legmass->AddEntry(h2,cH2,"pl");
    if (h3) legmass->AddEntry(h3,cH3,"pl");
    legmass->Draw("same");
}



void setLegend1(char* cH1, TH1D* h1,
		char* cH2, TH1D* h2,
		char* cH3, TH1D* h3,char* cH4, TH1D* h4)
{
    TLegend *legmass = new TLegend(0.22, 0.25, 0.39, 0.39);
    legmass->SetLineColor(10);
    legmass->SetLineStyle(1);
    legmass->SetLineWidth(1);
    legmass->SetFillColor(10);
    legmass->SetTextSize(0.04);
    legmass->SetTextFont(42);
    legmass->SetMargin(0.4);
    legmass->SetBorderSize(0);
    if (h1) legmass->AddEntry(h1,cH1,"pl");
    if (h2) legmass->AddEntry(h2,cH2,"pl");
    if (h3) legmass->AddEntry(h3,cH3,"pl");
    if (h4) legmass->AddEntry(h4,cH4,"pl");
    legmass->Draw("same");
}

void setLegend2(char* cH1, TH1D* h1,
		char* cH2, TH1D* h2
	)
{
    TLegend *legmass = new TLegend(0.47, 0.63, 0.54, 0.70);
    legmass->SetLineColor(10);
    legmass->SetLineStyle(1);
    legmass->SetLineWidth(1);
    legmass->SetFillColor(10);
    legmass->SetTextSize(0.02);
    legmass->SetTextFont(42);
    legmass->SetMargin(0.4);
    legmass->SetBorderSize(0);
    if (h1) legmass->AddEntry(h1,cH1,"p");
    if (h2) legmass->AddEntry(h2,cH2,"p");
 
    legmass->Draw("same");
}

void setLegend3(char* cH1, TH1D* h1,
		char* cH2, TH1D* h2,
        char* cH3, TH1D* h3
	)
{
    TLegend *legmass = new TLegend(0.61, 0.58, 0.68, 0.65);
    legmass->SetLineColor(10);
    legmass->SetLineStyle(1);
    legmass->SetLineWidth(1);
    legmass->SetFillColor(10);
    legmass->SetTextSize(0.02);
    legmass->SetTextFont(42);
    legmass->SetMargin(0.4);
    legmass->SetBorderSize(0);
    if (h1) legmass->AddEntry(h1,cH1,"p");
    if (h2) legmass->AddEntry(h2,cH2,"p");
    if (h3) legmass->AddEntry(h3,cH3,"p");
 
    legmass->Draw("same");
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
    hist->SetFillColor(1);


    hist->SetTitleFont(42);

    Int_t MyPalette[100];
    const Int_t NRGBs = 5;
   // const Int_t NCont = 255;
    Double_t stops[NRGBs] = { 0.00, 0.34, 0.61, 0.84, 1.00 };
    Double_t reds[NRGBs] = { 0.00, 0.00, 0.87, 1.00, 0.51 };
    Double_t greens[NRGBs] = { 0.00, 0.81, 1.00, 0.20, 0.00 };
    Double_t blues[NRGBs] = { 0.51, 1.00, 0.12, 0.00, 0.00 };
    Int_t FI = TColor::CreateGradientColorTable(NRGBs, stops, reds,greens, blues, NCont);
    gStyle->SetNumberContours(NCont);
    hist->SetContour(50);
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

void setHadesWorkInProgress()
{
    TLatex* tex = new TLatex(0.3, 9e-4,"HADES Work In Progress");
    tex->SetTextFont(42);
    tex->SetTextSize(0.04);
    tex->SetLineWidth(3);
    tex->Draw();
}
void setMainTitle()
{
    TLatex* tex = new TLatex(0.28, 4e-4,"Ag+Ag #sqrt{s_{NN}}=2.42 GeV 0-40%");
    tex->SetTextFont(42);
    tex->SetTextSize(0.04);
    tex->SetLineWidth(3);
    tex->Draw();
}

void setMomTitle()
{
    TLatex* tex2 = new TLatex(0.3,1.5e-4,"#alpha_{e^{+}e^{-}} > 9^{o}, #font[52]{p}_{e} > 0.1 GeV/#font[52]{c}");
    tex2->SetTextFont(42);
    tex2->SetTextSize(0.04);
    tex2->SetLineWidth(3);
    tex2->Draw();
}

void draw_fullCocktailwData() {
       
    static const Int_t MAX_MULT = 4;

    TString f_data    = "~/lustre/hades/user/icudrea/mar19/loop/phd/PairCorrection/EffCorrPair_spectra_ag123ag_CBSmear_3sigma_oAngle9Mom100_alldays_fullCocktail.root";
    TString f_cocktail= "~/march19AgAg/submit/EffCorrection/cocktail/Cocktail_9oAngle100Mom_4pi_wrho.root";
  
    TFile* file_4pi     = new TFile(f_4pi, "READ");
    TFile* file_acc     = new TFile(f_acc, "READ");
    TFile* file_EffAcc  = new TFile(f_EffAcc, "READ");
    
    TH1D *h_cocktail_4pi[MAX_MULT];    
    TH1D *h_cocktail_acc[MAX_MULT];       
    TH1D *h_cocktail_EffAcc[MAX_MULT];    

    for (Int_t mult = 1; mult <= MAX_MULT; ++mult) {
        h_cocktail_4pi[mult-1]    = (TH1D*) file_4pi->Get(Form("h_cocktail_4pi_%i", mult));
        h_cocktail_acc[mult-1]    = (TH1D*) file_acc->Get(Form("h_cocktail_acc_%i", mult));
        h_cocktail_EffAcc[mult-1] = (TH1D*) file_EffAcc->Get(Form("h_cocktail_EffAcc_%i", mult));
    }

    TH1D* h_cocktail_4pi_CCTotal    = (TH1D*) h_cocktail_4pi[0]->Clone("h_cocktail_4pi_CCTotal");
    TH1D* h_cocktail_acc_CCTotal    = (TH1D*) h_cocktail_acc[0]->Clone("h_cocktail_acc_CCTotal");
    TH1D* h_cocktail_EffAcc_CCTotal = (TH1D*) h_cocktail_EffAcc[0]->Clone("h_cocktail_EffAcc_CCTotal");

    h_cocktail_4pi_CCTotal->Reset(); 
    h_cocktail_acc_CCTotal->Reset();
    h_cocktail_EffAcc_CCTotal->Reset();


    for (Int_t mult = 1; mult <= MAX_MULT; ++mult) {
        h_cocktail_4pi_CCTotal->Add(h_cocktail_4pi[mult-1], MultPionsCC[mult-1]);
        h_cocktail_acc_CCTotal->Add(h_cocktail_acc[mult-1], MultPionsCC[mult-1]);
        h_cocktail_EffAcc_CCTotal->Add(h_cocktail_EffAcc[mult-1], MultPionsCC[mult-1]);
    }

    h_cocktail_4pi_CCTotal->Scale(1.0 / divideFactor);
    h_cocktail_acc_CCTotal->Scale(1.0 / divideFactor);
    h_cocktail_EffAcc_CCTotal->Scale(1.0 / divideFactor);

 
    TFile* outputFile = new TFile("~/march19AgAg/submit/EffCorrection/cocktail/Cocktail_9oAngle100Mom_CCTotal_rho.root", "RECREATE");
    outputFile->cd();
     
    h_cocktail_4pi_CCTotal->Write();
    h_cocktail_acc_CCTotal->Write();
    h_cocktail_EffAcc_CCTotal->Write();

    outputFile->Close();
    
}
