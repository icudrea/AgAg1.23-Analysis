
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
    hist->GetXaxis()->CenterTitle();
    hist->GetYaxis()->CenterTitle();
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

void setLegend(char* cH1 , TH1D* h1 ,
	       char* cH2 , TH1D* h2 ,
	       char* cH3 , TH1D* h3 ,
	       char* cH4 , TH1D* h4
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

    if (h1) leg->AddEntry(h1 ,cH1 ,"l");
    if (h2) leg->AddEntry(h2 ,cH2 ,"l");
    if (h3) leg->AddEntry(h3 ,cH3 ,"l");
    if (h4) leg->AddEntry(h4 ,cH4 ,"l");
    leg->Draw("same");
}
//----------------------------------------------------------------------------



//----------------------------------------------------------------------------
void plot_cbm_cocktail_auau25gev_epem_carina()
{   TString f_data = "~/lustre/hades/user/icudrea/mar19/loop/phd/PairCorrection/EffCorrPair_mybins_oAngle9Mom100_alldays_fullCocktail.root";
   // TString f_data = "~/lustre/hades/user/icudrea/mar19/loop/phd/PairCorrection/EffCorrPair_spectra_ag123ag_CBSmear_3sigma_oAngle9Mom100_alldays_fullCocktail.root";
    TString f_eta  ="~/march19AgAg/submit/EffCorrection/cocktail/scaled_9oAngle100Mom_eta_allCC.root";
    TString f_pi0  ="~/march19AgAg/submit/EffCorrection/cocktail/scaled_9oAngle100Mom_pi0_allCC.root";
    TString f_rho  ="~/march19AgAg/submit/EffCorrection/cocktail/scaled_9oAngle100Mom_rho_allCC.root";
    TString f_w    ="~/march19AgAg/submit/EffCorrection/cocktail/scaled_9oAngle100Mom_w_allCC.root";
    TString f_wd   ="~/march19AgAg/submit/EffCorrection/cocktail/scaled_9oAngle100Mom_wD_allCC.root";

    
    TFile* file_data = new TFile(f_data, "READ");
    TFile* file_eta = new TFile(f_eta, "READ");
    TFile* file_pi0 = new TFile(f_pi0, "READ");
    TFile* file_rho = new TFile(f_rho, "READ");
    TFile* file_w   = new TFile(f_w, "READ");
    TFile* file_wd  = new TFile(f_wd, "READ");



    TH1D* h_pi0       = (TH1D*) file_pi0 ->Get("h_mass_acc_pi0_CCTotal");
    TH1D* h_eta       = (TH1D*) file_eta ->Get("h_mass_acc_eta_CCTotal");
    TH1D* h_omega     = (TH1D*) file_w   ->Get("h_mass_acc_w_CCTotal");
    TH1D* h_omega_dal = (TH1D*) file_wd  ->Get("h_mass_acc_wdalitz_CCTotal");
    TH1D* h_rho       = (TH1D*) file_rho ->Get("h_mass_acc_rho_CCTotal");
    TH1D* h_data      = (TH1D*) file_data->Get("h_Signal_epem");
 



    cout << h_pi0  ->GetNbinsX() << endl;
     cout << h_rho  ->GetNbinsX() << endl;
    cout << h_omega ->GetNbinsX() << endl;
    cout << h_data->GetNbinsX() << endl;

    Int_t nBins    = 360;
    Float_t low_m  = 0.;
    Float_t high_m = 1.8;

    // // freeze-out cocktail
    // TH1D* h_freezeout = new TH1D("h_freezeout", "",nBins,low_m,high_m);

    // h_freezeout->Add(h_pi0);
    // h_freezeout->Add(h_eta);
    // h_freezeout->Add(h_omega);
    // h_freezeout->Add(h_omega_dal);
  
    // // thermal radiation
    // TH1D* h_thermal = new TH1D("h_thermal", "",nBins,low_m,high_m);
    // h_thermal->Add(h_rho);
  
    //data
    //  TH1D* h_DataPoints = new TH1D("h_DataPoints", "",nBins,low_m,high_m);
    // h_DataPoints->Add(h_data);

    // // sum
    // TH1D* h_invmass = new TH1D("h_invmass", "",nBins,low_m,high_m);

    // h_invmass->Add(h_pi0);
    // h_invmass->Add(h_eta);
    // h_invmass->Add(h_omega);
    // h_invmass->Add(h_omega_dal);
    // h_invmass->Add(h_rho);
 

    // TCanvas *can1 = new TCanvas("c_invmass", "",158,28,900,750);
    // setOPT_canvas(can1,kTRUE);

    // can1->cd();

    // TH1D* hist = new TH1D("","dielectron invariant mass",nBins,low_m,high_m);

    // setOPT_hists(hist, "M_{ee} [GeV/c^{2}]", "dN/dM_{ee} [1/(GeV/c^{2})]", 510);

    // hist->GetXaxis()->SetRangeUser(0,1.8);
    // hist->SetMaximum(1e-2);
    // hist->SetMinimum(1e-9);

    // hist->Draw();

    // TString draw_option = "histcsame";
   
    // setOPT_hists(h_freezeout,      "","",510, 1, 2, kBlue+2);
    // h_freezeout  ->Draw(draw_option);


    // setOPT_hists(h_pi0 ,      "","",510, 7, 2, kAzure+6);
    // setOPT_hists(h_eta,      "","",510, 9, 2, kAzure+6);
    // setOPT_hists(h_omega,      "","",510, 7, 2, kAzure+6);
    // setOPT_hists(h_omega_dal,      "","",510, 5, 2, kAzure+6);
  

    // h_pi0    ->Draw(draw_option);
   
    // h_eta    ->Draw(draw_option);
    // h_omega ->Draw(draw_option);
    // h_omega_dal  ->Draw(draw_option);
 

    // setOPT_hists(h_thermal,        "","",510, 1, 2, kRed);
    // h_thermal    ->Draw(draw_option);



    // setOPT_hists(h_invmass,        "","",510, 1, 2, kOrange);
    // h_invmass    ->Draw(draw_option);


     TCanvas *can1 = new TCanvas("c_invmass", "",158,28,900,750);
     setOPT_canvas(can1,kTRUE);
     h_data->Draw();
     h_rho  ->Draw("histcsame"); 
     h_pi0  ->Draw("histcsame"); 
/*
    Float_t new_binwidth2 = 2;

    TH1D* h_measurement = h_invmass->Rebin(new_binwidth2,"h_measurement");
    h_measurement->Scale(1./new_binwidth2);

    h_measurement->SetMarkerStyle(21);
    h_measurement->SetMarkerColor(kBlack);
    h_measurement->SetMarkerSize(0.7);

    h_measurement->Draw("same p");
*/

    // cout << "zoom in" << endl;


    // TLatex *   tex = new TLatex(0.1720633,0.000958525,"#pi^{0}#rightarrow#gammae^{+}e^{-}");
    // tex->SetTextColor(kGray+2); //kAzure+6);
    // tex->SetTextSize(0.025);
    // tex->SetTextAngle(271.6);
    // tex->SetLineWidth(2);
    // tex->Draw();

    // tex = new TLatex(0.42,0.001080016,"#eta#rightarrow#gammae^{+}e^{-}");
    // tex->SetTextColor(kGray+2); //kAzure+6);
    // tex->SetTextSize(0.025);
    // tex->SetTextAngle(274.15);
    // tex->SetLineWidth(2);
    // tex->Draw();

    // tex = new TLatex(0.55,0.001426789,"#omega#rightarrow#pi^{0}e^{+}e^{-}");
    // tex->SetTextColor(kGray+2); //kAzure+6);
    // tex->SetTextSize(0.025);
    // tex->SetTextAngle(273.35);
    // tex->SetLineWidth(2);
    // tex->Draw();

    //tex = new TLatex(0.565,0.001,"#eta#rightarrowe^{+}e^{-}");
    //tex->SetTextColor(kGray+2); //kAzure+6);
    //tex->SetTextSize(0.025);
    //tex->SetTextAngle(-90);
    //tex->SetLineWidth(2);
    //tex->Draw();

//     tex = new TLatex(0.8450678,0.0001164111,"#omega#rightarrowe^{+}e^{-}");
//     tex->SetTextColor(kGray+2); //kAzure+6);
//     tex->SetTextSize(0.025);
//     tex->SetTextAngle(-90);
//     tex->SetLineWidth(2);
//     tex->Draw();

//     tex = new TLatex(1.066265,4.212148e-05,"#phi#rightarrowe^{+}e^{-}");
//     tex->SetTextColor(kGray+2); //kAzure+6);
//     tex->SetTextSize(0.025);
//     tex->SetTextAngle(270);
//     tex->SetLineWidth(2);
//     tex->Draw();

//     tex = new TLatex(0.2991341,0.02050348,"inmed. #rho");
//     tex->SetTextColor(kPink+2);
//     tex->SetTextSize(0.027);
//     tex->SetTextAngle(342.4);
//     tex->SetLineWidth(2);
//     tex->Draw();

//     tex = new TLatex(0.2473645,0.00434588,"QGP");
//     tex->SetTextColor(kPink+1);
//     tex->SetTextSize(0.027);
//     tex->SetTextAngle(339.85);
//     tex->SetLineWidth(2);
//     tex->Draw();


//     tex = new TLatex(3.15,1.e-05,"J/#Psi#rightarrowe^{+}e^{-}");
//     tex->SetTextColor(kGray+2); //kAzure+6);
//     tex->SetTextSize(0.025);
//     tex->SetTextAngle(270);
//     tex->SetLineWidth(2);
//     tex->Draw();

//     tex = new TLatex(3.58,2.5e-07,"#Psi'#rightarrowe^{+}e^{-}");
//     tex->SetTextColor(kGray+2); //kAzure+6);
//     tex->SetTextSize(0.025);
//     tex->SetTextAngle(270);
//     tex->SetLineWidth(2);
//     tex->Draw();


// /*
    // TLatex *   tex = new TLatex(0.07719128,0.004925999,"#pi^{0}#rightarrow#gammae^{+}e^{-}");
    // tex->SetTextColor(kAzure+6);
    // tex->SetTextSize(0.025);
    // tex->SetTextAngle(270);
    // tex->SetLineWidth(2);
    // tex->Draw();

    // tex = new TLatex(0.4393632,0.002784513,"#eta#rightarrow#gammae^{+}e^{-}");
    // tex->SetTextColor(kAzure+6);
    // tex->SetTextSize(0.025);
    // tex->SetTextAngle(279.3);
    // tex->SetLineWidth(2);
    // tex->Draw();

    // tex = new TLatex(0.1907078,0.02887382,"#omega#rightarrow#pi^{0}e^{+}e^{-}");
    // tex->SetTextColor(kAzure+6);
    // tex->SetTextSize(0.025);
    // tex->SetTextAngle(336.9);
    // tex->SetLineWidth(2);
    // tex->Draw();

    //tex = new TLatex(0.5637339,0.002659723,"#eta#rightarrowe^{+}e^{-}");
    //tex->SetTextColor(kAzure+6);
    //tex->SetTextSize(0.025);
    //tex->SetTextAngle(-90);
    //tex->SetLineWidth(2);
    //tex->Draw();

    // tex = new TLatex(0.7666303,0.001333157,"#omega#rightarrowe^{+}e^{-}");
    // tex->SetTextColor(kAzure+6);
    // tex->SetTextSize(0.025);
    // tex->SetTextAngle(-90);
    // tex->SetLineWidth(2);
    // tex->Draw();

    // tex = new TLatex(0.9474849,0.0006318468,"#phi#rightarrowe^{+}e^{-}");
    // tex->SetTextColor(kAzure+6);
    // tex->SetTextSize(0.025);
    // tex->SetTextAngle(270);
    // tex->SetLineWidth(2);
    // tex->Draw();

    // tex = new TLatex(0.5204464,0.01299155,"inmed. #rho");
    // tex->SetTextColor(kPink+2);
    // tex->SetTextSize(0.027);
    // tex->SetTextAngle(349.8);
    // tex->SetLineWidth(2);
    // tex->Draw();

    // tex = new TLatex(0.2709467,0.006306381,"QGP");
    // tex->SetTextColor(kPink+1);
    // tex->SetTextSize(0.027);
    // tex->SetTextAngle(335.7);
    // tex->SetLineWidth(2);
    // tex->Draw();




    // setLegend("freeze-out cocktail"     , h_freezeout,
	//       "thermal radiation (Rapp)", h_thermal  ,
	//       "c#bar{c} corr."          , h_opencharm,
	//       "Drell-Yan"               , h_drell_yan,
	//       "sum"                     , h_invmass
	//      );


    // can1->SaveAs("/u/fseck/my_docs/cbm_progress2014/can_invmass_ee.pdf");

}
