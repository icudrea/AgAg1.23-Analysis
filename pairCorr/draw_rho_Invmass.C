
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

void draw_rho_Invmass(int centClass = 1){



 
    //TFile *file1   = new TFile("~/march19AgAg/submit/EffCorrection/inmedRho_histo_centralityDep/hist_centClass1_inmedRho_100000000evt_new.root");
  //  TFile *fileout = new TFile("~/march19AgAg/submit/EffCorrection/ratio_9oAngle100Mom/CorrectionFactor_centClass4_inmedRhoCG_9oAngle100Mom_100000000evt.root","RECREATE");

   TString filename = Form("~/lustre/hades/user/icudrea/mar19/loop/phd/pluto_files_ag123ag/w/" + TString("hist_centClass%d_w_100000000evt_pluto.root"), centClass);
   TFile *file1 = TFile::Open(filename); 

    TString outputFilename = Form("~/march19AgAg/submit/EffCorrection/ratio_9oAngle100Mom/CorrectionFactor_centClass%d_wPLUTO_9oAngle100Mom_100000000evt.root", centClass);
    TFile *fileout = new TFile(outputFilename, "RECREATE");
    //----------9OAngle100Mom------------------------
    TH1D *h_mass_4pi         = (TH1D*) file1->Get("h_m");
    TH1D *h_mass_accW        = (TH1D*) file1->Get("h_m_acc");
    TH1D *h_mass_EffAcc      = (TH1D*) file1->Get("h_m_recoCut");     




    TH1D *h_AccCorr = (TH1D*) h_mass_accW->Clone("h_AccCorr");
    h_AccCorr->Divide(h_mass_4pi);

    TCanvas *cAccCorr = new TCanvas("cAccCorr", "AccCorr", 900, 900);
    h_AccCorr->Draw("histo");

    ///////


    TH1D *h_EffCorr = (TH1D*) h_mass_EffAcc->Clone("h_EffCorr");
    h_EffCorr->Divide(h_mass_accW);

    TCanvas *cEffCorr = new TCanvas("cEffCorr", "EffCorr", 900, 900);
    h_EffCorr->Draw("histo");

    h_AccCorr->Write();
    h_EffCorr->Write();

    // Int_t n_bins = h_mass_4pi->GetNbinsX();
    // for(Int_t i = 1; i<= n_bins; i++){

    // Float_t N4pi         = h_mass_4pi->GetBinContent(i);
    // Float_t N4pi_oAngle  = h_mass_4pi_oAngle->GetBinContent(i);
    // Float_t NaccW        = h_mass_accW->GetBinContent(i);
    // Float_t NeffW        = h_mass_effW->GetBinContent(i);

    // Float_t N4pi_error         = h_mass_4pi       ->GetBinError(i);
    // Float_t N4pi_oAngle_error  = h_mass_4pi_oAngle->GetBinError(i);
    // Float_t NaccW_error        = h_mass_accW->GetBinError(i);
    // Float_t NeffW_error        = h_mass_effW->GetBinError(i);

    // Float_t width = h_mass_4pi->GetBinWidth(i);

    // h_mass_4pi        ->SetBinContent(i,Nepem/width);     
    // h_mass_4pi_oAngle ->SetBinContent(i,N4pi_oAngle/width) 
    // h_mass_accW       ->SetBinContent(i,NaccW_error/width) 
    // h_mass_effW       ->SetBinContent(i,NeffW_error/width) 

    // h_mass_4pi        ->SetBinError(i,N4pi_error/width);     
    // h_mass_4pi_oAngle ->SetBinError(i,N4pi_oAngle_error/width) 
    // h_mass_accW       ->SetBinError(i,NaccW_error_error/width) 
    // h_mass_effW       ->SetBinError(i,NeffW_error_error/width) 

  


    // }


//   TCanvas* c_mass= new TCanvas( "c_mass", "", 900, 900 );

//   c_mass->SetLogy();
//   h_mass_4pi->Draw();

//   TCanvas* c_opAng= new TCanvas( "c_opAng", "c_opAng", 900, 900 );

//   c_opAng->SetLogy();
//   h_mass_4pi_oAngle->Draw();

//   TCanvas* c_pM_effW = new TCanvas( "c_pM_effW", "c_pM_effW", 900, 900 );

//   c_pM_effW->SetLogy();
//   h_mass_effW->Draw();

//   TCanvas* c_pM_accW = new TCanvas( "c_pM_accW", "c_pM_accW", 900, 900 );

//   c_pM_accW->SetLogy();
//   h_mass_accW->Draw( );


}



