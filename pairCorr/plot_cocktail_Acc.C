
//macro to calculate the excess from Correction Factors
//----------------------------------------------------------------------------
void setOPT_hists(TH1D *hist, TString xAxisTitle=" ", TString yAxisTitle=" ", Int_t Ndevision=510,
		  Int_t line_style =20, Float_t line_size =1.3, Int_t color=1)
{
    hist->GetXaxis()->SetTitle(xAxisTitle);
    hist->GetYaxis()->SetTitle(yAxisTitle);
    hist->GetXaxis()->SetTitleSize(0.055); //11
    hist->GetYaxis()->SetTitleSize(0.06); //11
    hist->GetXaxis()->SetTitleFont(42);
    hist->GetYaxis()->SetTitleFont(42);
    hist->GetXaxis()->SetNdivisions(Ndevision);
    hist->GetYaxis()->SetTitleOffset(1.1); // 0.5
    hist->GetXaxis()->SetTitleOffset(1.);  // 0.5
    //hist->GetXaxis()->CenterTitle();
    //hist->GetYaxis()->CenterTitle();
    hist->GetXaxis()->SetLabelFont(42);
    hist->GetYaxis()->SetLabelFont(42);
    hist->GetXaxis()->SetLabelSize(0.05); //8
    hist->GetYaxis()->SetLabelSize(0.05); //8
    hist->SetLineStyle(line_style);
    hist->SetLineWidth(line_size);
    hist->SetLineColor(color);
    hist->SetTitle("");
    hist->SetLineWidth(2);
}

//----------------------------------------------------------------------------

void setOPT_canvas(TCanvas *canvas,  Bool_t IsLog)
{
    gStyle->SetOptStat(0);
    gStyle->SetEndErrorSize(5);
    gStyle->SetErrorX(0);    // X errors of the data points set to be 0
    gStyle->SetLineStyleString(22,"80 18 12 18 12 12"); // special style for the line
    gStyle->SetEndErrorSize(5);   // define end width of error bars
    gStyle->SetCanvasColor(10);
    gStyle->SetPadColor(10);

    canvas->SetLeftMargin  (0.14);
    canvas->SetRightMargin (0.03);
    canvas->SetTopMargin   (0.03);
    canvas->SetBottomMargin(0.12);

    canvas->ToggleEventStatus();
    canvas->Range(-200,-10,1000,-2);
    canvas->SetFillColor(0);
    canvas->SetBorderMode(0);
    canvas->SetBorderSize(0);
    canvas->SetTickx();
    canvas->SetTicky();
    if(IsLog){
	canvas->SetLogy();
    }
    canvas->SetFrameLineWidth(2);
    canvas->SetFrameBorderMode(0);
    canvas->SetFrameBorderSize(0);
}

//----------------------------------------------------------------------------

void setLegend(char* cH1 , TH1D* h1 ,
	       char* cH2 , TH1D* h2 ,
	       char* cH3 , TH1D* h3 ,
	       char* cH4 , TH1D* h4 ,
	       char* cH5 , TH1D* h5
	      )
{
    TLegend *leg = new TLegend(0.55, 0.7, 0.85, 0.95);
    leg->SetLineColor(10);
    leg->SetLineStyle(1);
    leg->SetLineWidth(1);
    leg->SetFillColor(10);
    leg->SetTextSize(0.03);
    leg->SetTextFont(62);
    leg->SetMargin(0.4);
    leg->SetBorderSize(0);

    if (h1) leg->AddEntry(h1 ,cH1 ,"l");
    if (h2) leg->AddEntry(h2 ,cH2 ,"l");
    if (h3) leg->AddEntry(h3 ,cH3 ,"l");
    if (h4) leg->AddEntry(h4 ,cH4 ,"l");
    if (h5) leg->AddEntry(h5 ,cH5 ,"l");
    leg->Draw("same");
}

void setLegendCocktail(char* cH1 , TH1D* h1 ,
	       char* cH2 , TGraph* h2 ,
	       char* cH3 , TGraph* h3 ,
	       char* cH4 , TGraph* h4,
           char* cH5 , TGraph* h5
	      )
{
    TLegend *leg = new TLegend(0.55, 0.7, 0.85, 0.9);
    leg->SetLineColor(10);
    leg->SetLineStyle(1);
    leg->SetLineWidth(2);
    leg->SetFillColor(10);
    leg->SetTextSize(0.03);
    leg->SetTextFont(62);
    leg->SetMargin(0.4);
    leg->SetBorderSize(0);

    if (h1) leg->AddEntry(h1 ,cH1 ,"p");
    if (h2) leg->AddEntry(h2 ,cH2 ,"l");
    if (h3) leg->AddEntry(h3 ,cH3 ,"l");
    if (h4) leg->AddEntry(h4 ,cH4 ,"l");
    if (h5) leg->AddEntry(h5 ,cH5 ,"l");
    leg->Draw("same");
}
//----------------------------------------------------------------------------

void setinfo()
{
    TLatex* tex = new TLatex(0.28, 4e-4,"Ag+Ag #sqrt{s_{NN}}=2.42 GeV 0-40%");
    tex->SetTextFont(42);
    tex->SetTextSize(0.04);
    tex->SetLineWidth(3);
    tex->Draw();
}
//----------------------------------------------------------------------------
void plot_cocktail_Acc()
{   TString f_data = "~/lustre/hades/user/icudrea/mar19/loop/phd/PairCorrection/EffCorrPair_mybins_oAngle9Mom100_alldays_fullCocktail.root";
    //TString f_data = "~/lustre/hades/user/icudrea/mar19/loop/phd/PairCorrection/EffCorrPair_spectra_ag123ag_CBSmear_3sigma_oAngle9Mom100_alldays_fullCocktail.root";
    TString f_eta  ="/u/icudrea/march19AgAg/submit/EffCorrection/cocktail/eta/scaled_9oAngle100Mom_eta_allCC.root";
 //   TString f_pi0  ="/u/icudrea/march19AgAg/submit/EffCorrection/cocktail/scaled_9oAngle100Mom_pi0_allCC.root";
    TString f_rho  ="/u/icudrea/march19AgAg/submit/EffCorrection/cocktail/rho/scaled_9oAngle100Mom_rho_allCC.root";
    TString f_w    ="/u/icudrea/march19AgAg/submit/EffCorrection/cocktail/w/scaled_9oAngle100Mom_w_allCC.root";
    TString f_wd   ="/u/icudrea/march19AgAg/submit/EffCorrection/cocktail/wdalitz/scaled_9oAngle100Mom_wD_allCC.root";
    TString f_ref  ="/u/icudrea/march19AgAg/submit/EffCorrection/Reference_ag1230ag.root";
    TString f_acc="~/march19AgAg/submit/EffCorrection/cocktail/PairCorrFactors_9oAngle100Mom_CGrho_allCC.root";

    
    TFile* file_data = new TFile(f_data, "READ");
    TFile* file_eta = new TFile(f_eta, "READ");
 //   TFile* file_pi0 = new TFile(f_pi0, "READ");
    TFile* file_rho = new TFile(f_rho, "READ");
    TFile* file_w   = new TFile(f_w, "READ");
    TFile* file_wd  = new TFile(f_wd, "READ");
    TFile* file_ref = new TFile(f_ref, "READ");
    TFile* file_acc = new TFile(f_acc, "READ");

  //  TH1D* h_pi0       = (TH1D*) file_pi0  ->Get("h_mass_acc_pi0_CCTotal");
    TH1D* h_eta       = (TH1D*) file_eta  ->Get("h_mass_acc_eta_CCTotal");
    TH1D* h_omega     = (TH1D*) file_w    ->Get("h_mass_acc_w_CCTotal");
    TH1D* h_omega_dal = (TH1D*) file_wd   ->Get("h_mass_acc_wdalitz_CCTotal");
    TH1D* h_rho       = (TH1D*) file_rho  ->Get("h_mass_acc_rho_CCTotal");
    TH1D* h_data      = (TH1D*) file_data ->Get("h_Signal_epem");
    TH1D* h_ref       = (TH1D*) file_ref  ->Get("Reference");
    TH1D* h_acc       = (TH1D*) file_acc  ->Get("h_AccFactor");

    // cout<<"bins data :"<<h_data->GetNbinsX()<<endl;
    // cout<<"bins pi0  :"<<h_pi0->GetNbinsX()<<endl;


    for( int i=0; i<h_omega->GetNbinsX(); i++ ) {
    //	h_pi0      ->SetBinError( i+1, 0. );
    	h_eta      ->SetBinError( i+1, 0. );
    	h_omega    ->SetBinError( i+1, 0. );
    	h_omega    ->SetBinError( i+1, 0. );
    	h_rho      ->SetBinError( i+1, 0. );
    }

  
    // freeze-out cocktail
    TH1D* h_freezeout = (TH1D*) h_omega->Clone( "h_freezeout" );
    h_freezeout->Reset();

    //h_freezeout->Add(h_pi0);
    h_freezeout->Add(h_eta);
    h_freezeout->Add(h_omega);
    h_freezeout->Add(h_omega_dal);
  
      // Subtract freezeout cocktail from data
    h_data->Add(h_freezeout, -1);
    h_data->Divide(h_acc);//test like this pls 

    Int_t bin = h_data->GetXaxis()->FindBin(0.2);
    cout<<"value: "<<h_data->GetBinContent(bin)<<endl;
  
    for (int i = 0; i < h_data->GetNbinsX(); i++) {
        if (h_data->GetBinContent(i + 1) < 0) {
            h_data->SetBinContent(i + 1, 0);
        }
    }
    
    TCanvas *can = new TCanvas("can", "",158,28,900,918);
    setOPT_canvas(can, true);

    h_data->GetXaxis()->SetRangeUser(0,1.2);
    h_data->SetMaximum(1e-2);
    h_data->SetMinimum(1e-9);

    h_data->SetMarkerColor( kBlack );
    h_data->Draw();



h_data->Scale( h_data->GetBinWidth(1) );

std::vector<double> binEgdeNiklas = {0, 0.01, 0.02, 0.03, 0.04, 0.05, 0.06, 0.07, 0.08,
                                     0.09, 0.11, 0.13, 0.15, 0.18, 0.21, 0.24, 0.27, 0.3,
                                     0.33, 0.36, 0.39, 0.42, 0.45, 0.48, 0.51, 0.54, 0.57,
                                     0.6, 0.65, 0.7, 0.75, 0.8, 0.85, 0.9, 0.95, 1, 1.05, 1.1, 1.399};


TH1D* h_ExcessAccCorr = (TH1D*)h_data->Rebin(binEgdeNiklas.size() - 1, "h_ExcessAccCorr", binEgdeNiklas.data());


for (size_t i = 0; i < binEgdeNiklas.size() - 1; ++i) {
  
    Double_t binWidth = binEgdeNiklas[i + 1] - binEgdeNiklas[i];
    
    
    Int_t binNumber = i + 1;

    Double_t binContent = h_ExcessAccCorr->GetBinContent(binNumber);
    
    h_ExcessAccCorr->SetBinContent(binNumber, binContent / binWidth);
    Double_t binError = h_ExcessAccCorr->GetBinError(binNumber);
    h_ExcessAccCorr->SetBinError(binNumber, binError/binWidth);
  
   
  
}


//  double binError = h_ExcessAccCorr->GetBinError(binNumber);
//   h_ExcessAccCorr->SetBinError(binNumber, binError / binWidth);



    // TFile* outputFile = new TFile("~/march19AgAg/submit/EffCorrection/cocktail/AccCorr_excess_Rebin_NoPionv2.root", "RECREATE");
    // outputFile->cd();

   
    // h_ExcessAccCorr->Write();

}