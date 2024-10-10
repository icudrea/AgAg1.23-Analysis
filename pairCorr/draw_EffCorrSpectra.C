
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

void setLegendSignal(char* cH1, TH1D* h1
		
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

    legmass->Draw("same");
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
{// TLatex* tex2 = new TLatex(0.3,1.5e-4,"#alpha_{e^{+}e^{-}} > 9^{o}");

  //  TLatex* tex2 = new TLatex(0.5,1.5e-4,"#alpha_{e^{+}e^{-}} > 9^{o}");
    TLatex* tex2 = new TLatex(0.3,1.5e-4," #alpha_{e^{+}e^{-}} > 9^{o} #font[52]{p}_{e} > 0.1 GeV/#font[52]{c}");
    tex2->SetTextFont(42);
    tex2->SetTextSize(0.04);
   // tex2->SetTextColor(kRed);
    tex2->SetLineWidth(3);
    tex2->Draw();
    // tex1->SetTextFont(42);
    // tex1->SetTextSize(0.04);
    // tex1->SetTextColor(kBlue);
    // tex1->SetLineWidth(3);
    // tex1->Draw();
}

void calculateOverallDifferencePercentage(TH1D* h_Sign_me, TH1D* h_SignalNiklas) {
    // Ensure both histograms have the same number of bins
    if (h_Sign_me->GetNbinsX() != h_SignalNiklas->GetNbinsX()) {
        std::cerr << "Error: Histograms have different numbers of bins." << std::endl;
        return;
    }

    // Initialize sums for both histograms
    double sum_Sign_me = 0;
    double sum_SignalNiklas = 0;

    // Loop over each bin to calculate the sums
    for (int i = 1; i <= h_Sign_me->GetNbinsX(); ++i) {
        sum_Sign_me += h_Sign_me->GetBinContent(i);
        sum_SignalNiklas += h_SignalNiklas->GetBinContent(i);
    }

    // Calculate the total difference
    double difference = sum_Sign_me - sum_SignalNiklas;

    // Calculate the percentage difference relative to the sum of h_SignalNiklas
    double percentageDifference = (difference / sum_SignalNiklas) * 100;

    // Print the overall percentage difference
    std::cout << "Overall Percentage Difference = " << percentageDifference << "%" << std::endl;
}

void draw_EffCorrSpectra() {

//   TFile *outputFile = new TFile("EffCorr_spectras_ag123ag_CBSmear_3sigma_oAngle9MOmCut_alldays_OldCuts_wCentClassFix.root", "RECREATE");

// //     // Check the file 
//      if (!outputFile->IsOpen()) {
//      cout << "Error: Unable to open output ROOT file." << endl;
//      return;
//      }
   

TFile *file2 = new TFile("/u/icudrea/lustre/hades/user/icudrea/mar19/loop/phd/effStudies_mar19/CBCorrall_ag1230ag_cutsNiklas_fixedAlpha_098Window_EffCorrSingle_Smear.root");
 

///MomCut+oAnglecutSmearing Ideal-Reco///
 //TFile *file1 = new TFile("~/lustre/hades/user/icudrea/mar19/loop/phd/EfficiencyCorrection_revised/Loop_Eff_Smear_IdealmReco_3sigma_woldCut.root");
//TFile *file1 = new TFile("~/lustre/hades/user/icudrea/mar19/loop/phd/EfficiencyCorrection_revised/Loop_Eff_CBSmear_3sigma_oAngleCutwMomCut_OldCuts_alldays.root");
 //TFile *file1 = new TFile("~/lustre/hades/user/icudrea/mar19/loop/phd/EfficiencyCorrection_revised/Loop_Eff_wCBSmear_oAngle9_alldays.root");

   TFile *file3 = new TFile("~/lustre/hades/user/icudrea/mar19/loop/phd/PairCorrection/EffCorrPair_spectra_ag123ag_CBSmear_3sigma_oAngle9Mom100_alldays_fullCocktail.root");


// TFile *file1 = new TFile("~/lustre/hades/user/icudrea/mar19/loop/phd/EfficiencyCorrection_revised/Loop_Eff_CBSmear_3sigma_wMomCut_OldCuts_alldays.root");
  TFile *file1 = new TFile("~/lustre/hades/user/icudrea/mar19/loop/phd/SingleCorrection/Loop_SingleCorrection_3sigmacut_newCBSMearing.root");
   //TFile *file1 = new TFile("~/lustre/hades/user/icudrea/mar19/loop/phd/SingleCorrection/Loop_SingleCorrection_9oAngle_newCBSMearing.root");

    TH1D *h_mass_epem_orig        = (TH1D*) file1->Get("fh_mass_ep_em_effCorr");
    TH1D *h_mass_emem_orig        = (TH1D*) file1->Get("fh_mass_em_em_effCorr");
    TH1D *h_mass_epep_orig        = (TH1D*) file1->Get("fh_mass_ep_ep_effCorr");

    TH1D *h_mass_epem_mixEvt_orig = (TH1D*) file1->Get("fh_mass_ep_em_mixedEvents_effCorr");
    TH1D *h_mass_emem_mixEvt_orig = (TH1D*) file1->Get("fh_mass_em_em_mixedEvents_effCorr");
    TH1D *h_mass_epep_mixEvt_orig = (TH1D*) file1->Get("fh_mass_ep_ep_mixedEvents_effCorr");

    TH1D *h_events                = (TH1D*) file1->Get("hCounter");

    TList* l_signalNiklas         = (TList*)file2->Get("Invmasslist");
    TH1D *h_signalNiklas          = (TH1D*)l_signalNiklas->FindObject("Signal_CCTotal");

//..................Binning issue............................
//     TAxis *xAxis = h_signalNiklas->GetXaxis();

//     for (Int_t bin = 1; bin <= xAxis->GetNbins(); ++bin) {
//     Double_t binWidth = xAxis->GetBinWidth(bin);
//     Double_t binLow_edg = xAxis->GetBinLowEdge(bin);
//      Double_t binH_edg = xAxis->GetBinUpEdge(bin);
//    cout << "Bin " << bin << " Width: " << binLow_edg <<"hWidth: " <<binH_edg<<endl;
// //    h_mass_epem->Rebin((Int_t)(binWidth / h_mass_epem->GetBinWidth(1)));
// //    h_mass_emem->Rebin((Int_t)(binWidth / h_mass_emem->GetBinWidth(1)));
// //    h_mass_epep->Rebin((Int_t)(binWidth / h_mass_epep->GetBinWidth(1)));

//      }

    vector<double> binEgdeNiklas ={ 0, 0.01, 0.02, 0.03, 0.04, 0.05, 0.06, 0.07, 0.08,    
                                   0.09, 0.11, 0.13, 0.15, 0.18, 0.21, 0.24, 0.27, 0.3,
                                   0.33, 0.36, 0.39, 0.42,0.45,0.48, 0.51, 0.54, 0.57,
                                   0.6, 0.65, 0.7, 0.75, 0.8, 0.85, 0.9, 0.95, 1,1.05, 1.1, 1.399};




    TH1D *h_mass_epem = (TH1D*) h_mass_epem_orig->Rebin(binEgdeNiklas.size()-1, "h_mass_epem", binEgdeNiklas.data());
    TH1D *h_mass_emem = (TH1D*) h_mass_emem_orig->Rebin(binEgdeNiklas.size()-1, "h_mass_emem", binEgdeNiklas.data());
    TH1D *h_mass_epep = (TH1D*) h_mass_epep_orig->Rebin(binEgdeNiklas.size()-1, "h_mass_epep", binEgdeNiklas.data());

    TH1D *h_mass_epem_mixEvt = (TH1D*) h_mass_epem_mixEvt_orig->Rebin(binEgdeNiklas.size()-1, "h_mass_epem", binEgdeNiklas.data());
    TH1D *h_mass_emem_mixEvt = (TH1D*) h_mass_emem_mixEvt_orig->Rebin(binEgdeNiklas.size()-1, "h_mass_emem", binEgdeNiklas.data());
    TH1D *h_mass_epep_mixEvt = (TH1D*) h_mass_epep_mixEvt_orig->Rebin(binEgdeNiklas.size()-1, "h_mass_epep", binEgdeNiklas.data());

   
    // h_mass_epem->Scale(1,"width");
    // h_mass_emem->Scale(1,"width");
    // h_mass_epep->Scale(1,"width");

    // h_mass_epem_mixEvt->Scale(1,"width");
    // h_mass_emem_mixEvt->Scale(1,"width");
    // h_mass_epep_mixEvt->Scale(1,"width");


 

//................................................................
    setOPT_hists(h_mass_epem,"M_{ee} [GeV/c^{2}]","dN/dM_{ee} [1/(GeV/c^{2})]",510,510);
    setOPT_hists(h_mass_emem,"M_{ee} [GeV/c^{2}]","dN/dM_{ee} [1/(GeV/c^{2})]",510,510);
    setOPT_hists(h_mass_epep,"M_{ee} [GeV/c^{2}]","dN/dM_{ee} [1/(GeV/c^{2})]",510,510);

         
     h_mass_epem ->SetMarkerStyle(21);
     h_mass_emem ->SetMarkerStyle(21);
     h_mass_epep ->SetMarkerStyle(21);
 

    Int_t n_bins = h_mass_epem->GetNbinsX();

   // cout<<"w = "<< h_mass_epem->GetBinWidth(1)<<endl;

    for(Int_t i = 1; i<= n_bins; i++){

    Float_t Nepem = h_mass_epem->GetBinContent(i);
    Float_t Nemem = h_mass_emem->GetBinContent(i);
    Float_t Nepep = h_mass_epep->GetBinContent(i);

    Float_t Nepem_error = h_mass_epem->GetBinError(i);
    Float_t Nemem_error = h_mass_emem->GetBinError(i);
    Float_t Nepep_error = h_mass_epep->GetBinError(i);

    Float_t width = h_mass_epem->GetBinWidth(i);
     
     h_mass_epem ->SetBinContent(i, Nepem/width);
     h_mass_emem ->SetBinContent(i, Nemem/width);
     h_mass_epep ->SetBinContent(i, Nepep/width);

     h_mass_epem ->SetBinError(i, Nepem_error/width);
     h_mass_emem ->SetBinError(i, Nemem_error/width);
     h_mass_epep ->SetBinError(i, Nepep_error/width);


    }

  
    Int_t     Nevents = h_events->GetBinContent(4);
    Double_t  No_pi0  = 5.26;
    Double_t  normFactor = No_pi0*Nevents;
    // cout<<"Normf= "<<normFactor<<'\n';
    //cout<<"Evts_3= "<<h_events->GetBinContent(3)<<'\n';
    //cout<<"Evts_4= "<<h_events->GetBinContent(4)<<'\n';


    // TH1D* fh_mass_epem = new TH1D("fh_mass_epem","", n_bins, 0,1.8 );
    // TH1D* fh_mass_emem = new TH1D("fh_mass_emem","", n_bins, 0,1.8 );
    // TH1D* fh_mass_epep = new TH1D("fh_mass_epep","", n_bins, 0,1.8 );

      h_mass_epem->Scale(1/normFactor);
      h_mass_emem->Scale(1/normFactor);
      h_mass_epep->Scale(1/normFactor);
     

 //----------------------------------------------k FACTOR----------
  


   TH1D* h_kFactor =  (TH1D*) h_mass_epem_mixEvt->Clone("h_kFactor");
    h_kFactor->Reset();
    for (Int_t i=1; i<=n_bins;i++){
        h_kFactor->SetBinContent(i,getK(h_mass_epem_mixEvt,h_mass_emem_mixEvt,h_mass_epep_mixEvt,i));
        h_kFactor->SetBinError(i,getKError(h_mass_epem_mixEvt,h_mass_emem_mixEvt,h_mass_epep_mixEvt,i));
    }


   h_kFactor->Draw();
    

//--------------------------------------------------------------  

    TH1D*h_mass_geomMean =  (TH1D*) h_mass_epem->Clone("h_mass_geomMean");
    h_mass_geomMean->Reset();
     for (Int_t i=1; i<=n_bins;i++){
      h_mass_geomMean->SetBinContent(i,2*getGeomMean(h_mass_epep,h_mass_emem,i));
      h_mass_geomMean->SetBinError(i,2*getGeomMeanError(h_mass_epep,h_mass_emem,i));
    }

    TH1D* h_mass_CB = (TH1D*) h_mass_geomMean->Clone("h_mass_CB");
    h_mass_CB->Reset();
     for (Int_t i=1; i<=n_bins;i++){
       h_mass_CB->SetBinContent(i,getSECB(h_mass_geomMean,h_kFactor,i));
       h_mass_CB->SetBinError(i,getSECBError(h_mass_geomMean,h_kFactor,i));
     }
    


  //----------------------MIXEVENT CB-------------------------------------------------
   
  
   
    TH1D*h_mass_CB_ME =  (TH1D*) h_mass_epem_mixEvt->Clone("h_mass_CB_ME");
    h_mass_CB_ME->Reset();
    for (Int_t i=1; i<=n_bins;i++){
      h_mass_CB_ME->SetBinContent(i,2*getGeomMean(h_mass_epep_mixEvt,h_mass_emem_mixEvt,i));
      h_mass_CB_ME->SetBinError(i,2*getGeomMeanError(h_mass_epep_mixEvt,h_mass_emem_mixEvt,i));
    }

        
    Double_t integral_SE_CB = h_mass_CB->Integral(h_mass_CB->FindBin(0.2), h_mass_CB->FindBin(0.4));
    Double_t integral_ME_CB = h_mass_CB_ME->Integral(h_mass_CB_ME->FindBin(0.2), h_mass_CB_ME->FindBin(0.4));

    Double_t Xfactor       = integral_ME_CB/integral_SE_CB;

    // cout<<"Xfactor = "<<Xfactor<<endl;
    
    h_mass_CB_ME->Scale(1/Xfactor);

    TH1D* hmass_CB_final = (TH1D*)h_mass_CB->Clone("hmass_CB_final");

     for (Int_t j=1; j<=n_bins;j++){
        Float_t mass_CB_final = hmass_CB_final->GetBinCenter(j);
        if(mass_CB_final>0.4){
        hmass_CB_final->SetBinContent(j,h_mass_CB_ME->GetBinContent(j));
         hmass_CB_final->SetBinError(j,h_mass_CB_ME->GetBinError(j));
        }
     }  
     
   ////////////////////////////////////////////////////////  
     
     TH1D* h_Sign =  (TH1D*) h_mass_epem->Clone("h_Sign");
     h_Sign->Reset();

     setOPT_hists(h_Sign,"#font[52]{M}_{ee} (GeV/#font[52]{c}^{2})","1/N_{#pi^{0}} dN/d#font[52]{M}_{ee} (GeV/#font[52]{c}^{2})^{-1}",510,510);
     h_Sign->Add(h_mass_epem,hmass_CB_final,1,-1);



// // //..............................SIGNAL..............................
    TCanvas *canSignal = new TCanvas("canSignal", "canSignal",158,28,900,918);
    setOPT_canvas(canSignal);
    
     canSignal->SetFillColor(10);
     canSignal->SetTopMargin(0.08);
     canSignal->SetRightMargin(0.12);
     canSignal->SetLogy();
     canSignal->SetGridy();

     TH1D* h_Signal_epem =  (TH1D*) h_mass_epem->Clone("h_Signal_epem"); 

     h_Signal_epem->Reset();

     for (Int_t i=1; i<=n_bins;i++){
         h_Signal_epem->SetBinContent(i,h_Sign->GetBinContent(i));
                  Double_t BinError = TMath::Sqrt( TMath::Power(h_mass_epem->GetBinError(i), 2) + TMath::Power(h_mass_CB->GetBinError(i), 2) ); 
         //Double_t BinError = TMath::Sqrt( TMath::Power(h_mass_epem->GetBinError(i), 2) + TMath::Power(h_mass_CB->GetBinError(i), 2) + TMath::Power(h_Sign->GetBinError(i)/normFactor, 2) ); 
         h_Signal_epem->SetBinError(i, BinError); 
        //  Double_t error = h_Signal_epem->GetBinError(i);
        //  h_Signal_epem->SetBinError(i,error);
     }
   
    setOPT_hists(h_Signal_epem,"#font[52]{M}_{ee} (GeV/#font[52]{c}^{2})","1/N_{#pi^{0}} dN/d#font[52]{M}_{ee} (GeV/#font[52]{c}^{2})^{-1}",510,510);
    setOPT_hists(h_signalNiklas,"#font[52]{M}_{ee} (GeV/#font[52]{c}^{2})","1/N_{#pi^{0}} dN/d#font[52]{M}_{ee} (GeV/#font[52]{c}^{2})^{-1}",510,510);


    h_Signal_epem->GetYaxis()->SetRangeUser(1e-8,5e-3);
    h_Signal_epem->GetXaxis()->SetRangeUser(0,1.1);

    h_signalNiklas->GetYaxis()->SetRangeUser(1e-8,5e-3);
    h_signalNiklas->GetXaxis()->SetRangeUser(0,1.1);

    h_Signal_epem->SetMarkerStyle(21);
    h_signalNiklas->SetMarkerStyle(21);
    h_Signal_epem->SetMarkerColor(kRed);
    h_signalNiklas->SetMarkerColor(kBlue);
   // h_Signal_epem ->Smooth();
   // h_Signal_epem->Scale(0.8);
    h_Signal_epem->Draw();
    h_signalNiklas->Draw("same");
    h_Signal_epem->Draw("same");


    setHadesWorkInProgress();
    setMainTitle();
    setMomTitle();
    


 setLegend2("e^{+}e^{-} signal, standard analysis ", h_signalNiklas,
            "e^{+}e^{-} signal, this work", h_Signal_epem
            );


////...........................

     TCanvas *can3 = new TCanvas("can3", "",158,28,900,1018);
     setOPT_canvas(can3);
    
     can3->SetFillColor(10);
     can3->SetTopMargin(0.08);
     can3->SetRightMargin(0.12);
     can3->SetLogy();

     h_Signal_epem->SetMarkerStyle(21);
     h_mass_epem ->SetMarkerStyle(21);
     h_mass_CB   ->SetMarkerStyle(21);

     h_Signal_epem->GetXaxis()->SetRangeUser(0,1.1);
     h_mass_epem ->GetXaxis()->SetRangeUser(0,1.1);
     h_mass_CB   ->GetXaxis()->SetRangeUser(0,1.1);

     h_Signal_epem ->SetMarkerColor(kRed);
     h_mass_epem ->SetMarkerColor(kBlack);
     h_mass_CB   ->SetMarkerColor(kBlue);
   
     h_Signal_epem ->Draw();
     h_mass_epem ->Draw("same");
     h_mass_CB   ->Draw("samep");
     h_Signal_epem ->Draw("same");

    
    setHadesWorkInProgress();
    setMainTitle();
    setMomTitle();

     setLegend3("Signal ", h_Signal_epem,
            "All e^{+}e^{-} pairs", h_mass_epem,
            "CB",h_mass_CB
          

  );
//........................






//............................
 TCanvas *canKfactor = new TCanvas("canKfactor", "",158,28,900,1018);
setOPT_canvas(canKfactor);

canKfactor->SetFillColor(10);
canKfactor->SetTopMargin(0.08);
canKfactor->SetRightMargin(0.12);
h_kFactor->SetMarkerStyle(21);
h_kFactor->Draw();




TCanvas *canSignal_opAng = new TCanvas("canSignal_opAng", "",158,28,900,1018);
setOPT_canvas(canSignal_opAng);

canSignal_opAng->SetFillColor(10);
canSignal_opAng->SetTopMargin(0.08);
canSignal_opAng->SetRightMargin(0.12);
canSignal_opAng->SetLogy();

h_Signal_epem->SetMarkerStyle(21);
h_Signal_epem->GetXaxis()->SetRangeUser(0,1.1);
h_Signal_epem ->SetMarkerColor(kRed);


h_Signal_epem ->Draw();


setHadesWorkInProgress();
setMainTitle();
setMomTitle();

setLegendSignal("Signal ", h_Signal_epem);



  TH2D* h_Signal_epem_singleEff = (TH2D*) file3->Get("h_Signal_epem");
  
TCanvas *canDivide = new TCanvas("canDivide", "",158,28,900,1018);
  canDivide->SetFillColor(10);
  canDivide->SetTopMargin(0.08);
  canDivide->SetRightMargin(0.12);



//   TH1D* h_Signal_yo      =  (TH1D*) h_Signal_epem->Clone("h_Signal_yo");
//  setOPT_hists(h_Signal_yo,"M_{ee} (GeV/c^{2})","this analysis / standard analysis",510,510);
//   h_Signal_yo->GetYaxis()->SetRangeUser(0,2.);

//   TH1D* h_Signal_nik     =  (TH1D*) h_signalNiklas->Clone("h_Signal_nik");
//   h_Signal_nik->GetYaxis()->SetRangeUser(0,2.);

  //h_Signal_yo->Divide(h_Signal_nik);
 /// h_Signal_epem_singleEff_1d->Scale(100);
  h_Signal_epem_singleEff->Divide(h_signalNiklas); 
  h_Signal_epem_singleEff->GetYaxis()->SetRangeUser(0, 2.);
  h_Signal_epem_singleEff->Draw("l");




    //  outputFile->cd();

    //  h_mass_epem->Write();
    //  h_mass_epep->Write();
    //  h_mass_emem->Write();
    //  h_kFactor->Write();

    //  h_mass_epem_mixEvt->Write();
    //  h_mass_CB->Write();
    //  h_Signal_epem->Write();
    //  h_signalNiklas->Write();

}
 



/////////////////////////////////////////////////////



