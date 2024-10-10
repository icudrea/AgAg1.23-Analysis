//----------------------------------------------------------------------------

#include "plot_style.C"

//----------------------------------------------------------------------------
void compare_AccFactor()
{   
    
    TString f_acc_me  ="~/march19AgAg/submit/EffCorrection/cocktail/PairCorrFactors_9oAngle100Mom_CGrho_allCC.root";
    TFile* file_me    = new TFile(f_acc_me, "READ");
    TH1D* h_accMe    = (TH1D*) file_me      ->Get("h_AccFactor_inv");
   // TH1D* h_CorrFactor    = (TH1D*) file_me      ->Get("h_AccFactor_inv");


   
   TFile *file_niklas = new TFile("~/march19AgAg/niklas/Corrections_ag1230ag_ForCarina_v2_MassSmeared_IdealLookUp.root");
   TList* l_Niklas    = (TList*)file_niklas  ->Get("MeanCorrectionslist");
   TH1D *h_acc_niklas = (TH1D*)l_Niklas      ->FindObject("Acceptance");



     vector<double> binEgdeNiklas ={ 0, 0.01, 0.02, 0.03, 0.04, 0.05, 0.06, 0.07, 0.08,    
                                   0.09, 0.11, 0.13, 0.15, 0.18, 0.21, 0.24, 0.27, 0.3,
                                   0.33, 0.36, 0.39, 0.42,0.45,0.48, 0.51, 0.54, 0.57,
                                   0.6, 0.65, 0.7, 0.75, 0.8, 0.85, 0.9, 0.95, 1,1.05, 1.1, 1.399};



    h_accMe->Scale(h_accMe->GetBinWidth(0));

    TH1D *h_CorrFactor = (TH1D*) h_accMe->Rebin(binEgdeNiklas.size()-1, "h_CorrFactor", binEgdeNiklas.data());

    for (size_t i = 0; i < binEgdeNiklas.size() - 1; ++i) {
    h_CorrFactor->SetBinContent(i+1,h_CorrFactor->GetBinContent(i+1)/h_CorrFactor->GetBinWidth(i+1));
    h_CorrFactor->SetBinError(i+1,h_CorrFactor->GetBinError(i+1)/h_CorrFactor->GetBinWidth(i+1));


    }


    TCanvas *canFactor = new TCanvas("canFactor", "canFactor",158,28,900,918);
    setOPT_canvas(canFactor);
    
    canFactor->SetFillColor(10);
    canFactor->SetTopMargin(0.08);
    canFactor->SetRightMargin(0.12);
    canFactor->SetLogy();
    canFactor->SetGridy();
   
    setOPT_TH1F(h_CorrFactor,"#font[52]{M}_{ee} (GeV/#font[52]{c}^{2})","Acceptance Corr. Factor ratio",510,510);
    setOPT_TH1F(h_acc_niklas,"#font[52]{M}_{ee} (GeV/#font[52]{c}^{2})","Acceptance Corr. Factor",510,510);




  
    h_CorrFactor->SetMarkerStyle(21);
    h_CorrFactor->SetMarkerSize(1.5);
    h_CorrFactor->SetMarkerColor(kRed);
    h_acc_niklas->SetLineColor(kBlue);
 
    h_CorrFactor->Draw();
    h_acc_niklas->Draw("same");
   // h_CorrFactor->Draw("same");


    


 setLegend2("Acc. factor, #rho , standard analysis ", h_acc_niklas,
            "Acc. factor, #rho , this work", h_CorrFactor
            );


  
 TCanvas *canDivide = new TCanvas("canDivide", "",158,28,900,1018);
  canDivide->SetFillColor(10);
  canDivide->SetTopMargin(0.08);
  canDivide->SetRightMargin(0.12);

  h_CorrFactor->Divide(h_acc_niklas); 
  h_CorrFactor->GetYaxis()->SetRangeUser(0, 2.);
  h_CorrFactor->Draw("l");





    // TFile* outputFile = new TFile("~/march19AgAg/submit/EffCorrection/cocktail/AccCorr_excess_Rebin_NoPionv2.root", "RECREATE");
    // outputFile->cd();

   
    // h_ExcessAccCorr->Write();

}