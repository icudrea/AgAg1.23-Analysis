

//macro for every centrality bin calulculation on dilepton invariant mass spectra + full cocktail

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
void draw_cocktail_CCdependent()
{   //TString f_data = "~/lustre/hades/user/icudrea/mar19/loop/phd/PairCorrection/EffCorrPair_mybins_oAngle9Mom100_alldays_fullCocktail.root";// 
   // TString f_data = "~/lustre/hades/user/icudrea/mar19/loop/phd/PairCorrection/EffCorrPair_spectra_ag123ag_CBSmear_3sigma_oAngle9Mom100_alldays_fullCocktail.root";
    TString f_eta  ="/u/icudrea/march19AgAg/submit/EffCorrection/cocktail/eta/eta_cocktail_scaled.root";
    TString f_pi0  ="/u/icudrea/march19AgAg/submit/EffCorrection/cocktail/pi0/pi0_SmearMomOnly_scaled_0515pi0_9opAngle100Mom.root";
    TString f_rho  ="/u/icudrea/march19AgAg/submit/EffCorrection/cocktail/rho/rho_cocktail_scaled.root";
    TString f_w    ="/u/icudrea/march19AgAg/submit/EffCorrection/cocktail/w/w_cocktail_scaled.root";
    TString f_wd   ="/u/icudrea/march19AgAg/submit/EffCorrection/cocktail/wdalitz/wdalitz_cocktail_scaled.root";
    TString f_ref  ="/u/icudrea/march19AgAg/submit/EffCorrection/Reference_ag1230ag.root";
    TString f_data = "~/lustre/hades/user/icudrea/mar19/loop/phd/PairCorrection/EffCorrPair_spectra_ag123ag_CBSmear_3sigma_oAngle9Mom100_alldays_wFullCoCktail0to10.root";  
     //TString f_data = "~/lustre/hades/user/icudrea/mar19/loop/phd/PairCorrection/EffCorrPair_spectra_ag123ag_CBSmear_3sigma_oAngle9Mom100_alldays_wFullCoCktail_10to20.root";  
    
    TFile* file_data = new TFile(f_data, "READ");
    TFile* file_eta = new TFile(f_eta, "READ");
    TFile* file_pi0 = new TFile(f_pi0, "READ");
    TFile* file_rho = new TFile(f_rho, "READ");
    TFile* file_w   = new TFile(f_w, "READ");
    TFile* file_wd  = new TFile(f_wd, "READ");
    TFile* file_ref = new TFile(f_ref, "READ");

    TH1D* h_pi0       = (TH1D*) file_pi0 ->Get("h_m_acc;1");
    TH1D* h_eta       = (TH1D*) file_eta ->Get("h_m_acc;1");
    TH1D* h_omega     = (TH1D*) file_w   ->Get("h_m_acc;1");
    TH1D* h_omega_dal = (TH1D*) file_wd  ->Get("h_m_acc;1");
    TH1D* h_rho       = (TH1D*) file_rho ->Get("h_m_acc_1");

    


    TH1D* h_data      = (TH1D*) file_data->Get("h_Signal_epem");
    TH1D* h_ref      = (TH1D*)  file_ref-> Get("Reference");

    for( int i=0; i<h_pi0->GetNbinsX(); i++ ) {
    	h_pi0      ->SetBinError( i+1, 0. );
    	h_eta      ->SetBinError( i+1, 0. );
    	h_omega    ->SetBinError( i+1, 0. );
    	h_omega    ->SetBinError( i+1, 0. );
    	h_rho      ->SetBinError( i+1, 0. );
    }

    // freeze-out cocktail
    TH1D* h_freezeout = (TH1D*) h_pi0->Clone( "h_freezeout" );
    h_freezeout->Reset();

    h_freezeout->Add(h_pi0);
    h_freezeout->Add(h_eta);
    h_freezeout->Add(h_omega);
    h_freezeout->Add(h_omega_dal);
  
    // // thermal radiation
    TH1D* h_thermal = (TH1D*) h_pi0->Clone( "h_thermal" );
    h_thermal->Reset();

    h_thermal->Add(h_rho);
  
    // sum
    TH1D* h_sum = (TH1D*) h_pi0->Clone( "h_sum" );
    h_sum->Reset();

    h_sum->Add(h_freezeout);
    h_sum->Add(h_thermal);

    TGraph* g_sum = new TGraph();
    g_sum->SetName( "g_sum" );

    TGraph* g_thermal = new TGraph();
    g_thermal->SetName( "g_thermal" );

    TGraph* g_freezeout = new TGraph();
    g_freezeout->SetName( "g_freezeout" );
 
    TGraph* g_pi0       = new TGraph();
    TGraph* g_eta       = new TGraph();
    TGraph* g_omega     = new TGraph();
    TGraph* g_omega_dal = new TGraph();
    TGraph* g_ref       = new TGraph();

    g_pi0       ->SetName("g_oi0"); 
    g_eta       ->SetName("g_eta"); 
    g_omega     ->SetName("g_omega"); 
    g_omega_dal ->SetName("g_omega_dal"); 
    g_ref       ->SetName("g_ref"); 


    for( int i=0; i<h_sum->GetNbinsX(); i++ ) {
    	g_sum->AddPoint( h_sum->GetBinCenter( i+1), h_sum->GetBinContent( i+1 ) );
    	g_thermal->AddPoint( h_thermal->GetBinCenter( i+1 ), h_thermal->GetBinContent( i+1 ) );
    	g_freezeout->AddPoint( h_freezeout->GetBinCenter( i+1 ), h_freezeout->GetBinContent( i+1 ) );
        g_pi0       ->AddPoint(h_pi0->GetBinCenter(i+1),h_pi0->GetBinContent(i+1));
        g_eta       ->AddPoint(h_pi0->GetBinCenter(i+1),h_eta->GetBinContent(i+1));
        g_omega     ->AddPoint(h_pi0->GetBinCenter(i+1),h_omega->GetBinContent(i+1)); 
        g_omega_dal ->AddPoint(h_pi0->GetBinCenter(i+1),h_omega_dal->GetBinContent(i+1));
        

      }
    for( int i=0; i<h_ref->GetNbinsX(); i++ ) {
      g_ref       ->AddPoint(h_ref->GetBinCenter(i+1),h_ref->GetBinContent(i+1));
      }

    TCanvas *can = new TCanvas("can", "",158,28,900,918);
    setOPT_canvas(can, true);

    h_data->GetXaxis()->SetRangeUser(0,1.2);
    h_data->SetMaximum(1e-2);
    h_data->SetMinimum(1e-10);

    g_sum->SetMaximum(1e-2);
    g_sum->SetMinimum(1e-10);

    g_thermal->SetMaximum(1e-2);
    g_thermal->SetMinimum(1e-10);

    g_freezeout->SetMaximum(1e-2);
    g_freezeout->SetMinimum(1e-10);

    g_ref->SetMaximum(1e-2);
    g_ref->SetMinimum(1e-10);


    h_data->Scale(4);
    h_data->SetMarkerColor( kBlack );
    h_data->Draw();

    g_sum->SetLineColor( kMagenta +3 );
    g_sum->SetLineWidth( 3 );
	g_sum->Draw( "c same" );

    g_thermal->SetLineColor( kRed + 1 );
    g_thermal->SetLineWidth( 2 );
    g_thermal->Draw( "c same" );

    g_freezeout->SetLineColor( kBlue + 1 );
    g_freezeout->SetLineWidth( 2 );
    g_freezeout->Draw( "c same" );

    g_ref->SetLineColor( kGreen + 1 );
    g_ref->SetLineWidth( 2 );
    g_ref->Draw( "c same" );


    g_pi0      ->SetLineStyle(5);
    g_eta      ->SetLineStyle(5);
    g_omega    ->SetLineStyle(5);
    g_omega_dal->SetLineStyle(5);

    g_pi0      ->SetLineColor( kAzure + 6 );
    g_pi0      ->SetLineWidth( 2 );
    g_eta      ->SetLineColor( kAzure + 6 );
    g_eta      ->SetLineWidth( 2 );
    g_omega    ->SetLineColor( kAzure + 6 );
    g_omega    ->SetLineWidth( 2 );
    g_omega_dal->SetLineColor( kAzure + 6 );
    g_omega_dal->SetLineWidth( 2 );


    g_pi0      ->Draw( "c same" );
    g_eta      ->Draw( "c same" );
    g_omega    ->Draw( "c same" );
    g_omega_dal->Draw( "c same" );

    h_data->Draw( "same" );


    TLatex *   tex = new TLatex(0.145957,2.50541e-06,"#pi^{0}#rightarrow#gammae^{+}e^{-}");
    tex->SetTextColor(kGray+2); //kAzure+6);
    tex->SetTextSize(0.025);
    tex->SetTextAngle(271.6);
    tex->SetLineWidth(2);
    tex->Draw();

    tex = new TLatex(0.46688,3.09885e-07,"#eta#rightarrowe^{+}e^{-}");
    tex->SetTextColor(kGray+2); //kAzure+6);
    tex->SetTextSize(0.025);
    tex->SetTextAngle(274.15);
    tex->SetLineWidth(2);
    tex->Draw();

    tex = new TLatex(0.289181,1.10812e-08,"#omega#rightarrow#pi^{0}e^{+}e^{-}");
    tex->SetTextColor(kGray+2); //kAzure+6);
    tex->SetTextSize(0.025);
    tex->SetTextAngle(273.35);
    tex->SetLineWidth(2);
    tex->Draw();



    tex = new TLatex(0.783,8.72e-09,"#omega#rightarrowe^{+}e^{-}");
    tex->SetTextColor(kGray+2); //kAzure+6);
    tex->SetTextSize(0.025);
    tex->SetTextAngle(-90);
    tex->SetLineWidth(2);
    tex->Draw();


    tex = new TLatex(0.5673,3.380e-07,"inmed. #rho");
    tex->SetTextColor(kRed+2);
    tex->SetTextSize(0.027);
    tex->SetTextAngle(342.4);
    tex->SetLineWidth(2);
    tex->Draw();

    setLegendCocktail( "Data 0-10%", h_data,
        "freeze-out cocktail"     , g_freezeout,
	    "thermal radiation"       , g_thermal,
	    "sum"                     , g_sum,
       "reference"                , g_ref
	     );
       



    // can1->SaveAs("/u/fseck/my_docs/cbm_progress2014/can_invmass_ee.pdf");

}
