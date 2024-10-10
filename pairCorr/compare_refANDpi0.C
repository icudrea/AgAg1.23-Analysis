//----------------------------------------------------------------------------

#include "plot_style.C"

//----------------------------------------------------------------------------
void compare_refANDpi0()
{   
    
    
    TString f_pi0_smear  ="/u/icudrea/march19AgAg/submit/EffCorrection/cocktail/pi0/scaled_SmearMomLookUp_SmearSmearing_9oAngle100Mom_pi0_allCC.root";
    TString f_pi0_ideal  ="/u/icudrea/march19AgAg/submit/EffCorrection/cocktail/pi0/scaled_IdealMomLookUp_IdealSmearing_9oAngle100Mom_pi0_allCC.root";
    TString f_ref        ="/u/icudrea/march19AgAg/submit/EffCorrection/Reference_ag1230ag.root";

    TFile* file_pi0_smear    = new TFile(f_pi0_smear, "READ");
    TFile* file_pi0_ideal    = new TFile(f_pi0_ideal, "READ");
    TFile* file_ref          = new TFile(f_ref, "READ");

    TH1D* histo_pi0Smear    = (TH1D*) file_pi0_smear  ->Get("h_mass_acc_pi0_CCTotal");
    TH1D* histo_pi0Ideal    = (TH1D*) file_pi0_ideal  ->Get("h_mass_acc_pi0_CCTotal");
    TH1D* h_ref             = (TH1D*) file_ref        ->Get("Reference");


   TFile *file_niklas = new TFile("~/march19AgAg/niklas/Corrections_ag1230ag_ForCarina_v2_MassSmeared_IdealLookUp.root");
   TList* l_Niklas    = (TList*)file_niklas  ->Get("Pi0list");
   TH1D *h_pi0_niklas = (TH1D*)l_Niklas      ->FindObject("AccClone_CCTotal");


   TFile *file_niklas2 = new TFile("~/march19AgAg/niklas/Corrections_ag1230ag_ForCarina_v1_MassIdeal_IdealLookUp.root");
   TList* l_Niklas2    = (TList*)file_niklas2  ->Get("Pi0list");
   TH1D *h_pi0_niklas2 = (TH1D*)l_Niklas2      ->FindObject("AccClone_CCTotal");

     vector<double> binEgdeNiklas ={ 0, 0.01, 0.02, 0.03, 0.04, 0.05, 0.06, 0.07, 0.08,    
                                   0.09, 0.11, 0.13, 0.15, 0.18, 0.21, 0.24, 0.27, 0.3,
                                   0.33, 0.36, 0.39, 0.42,0.45,0.48, 0.51, 0.54, 0.57,
                                   0.6, 0.65, 0.7, 0.75, 0.8, 0.85, 0.9, 0.95, 1,1.05, 1.1, 1.399};



    histo_pi0Ideal->Scale(histo_pi0Ideal->GetBinWidth(0));
    histo_pi0Smear->Scale(histo_pi0Smear->GetBinWidth(0));
    h_ref         ->Scale(1);

    TH1D *h_pi0Ideal = (TH1D*) histo_pi0Ideal->Rebin(binEgdeNiklas.size()-1, "h_pi0Ideal", binEgdeNiklas.data());
    TH1D *h_pi0Smear = (TH1D*) histo_pi0Smear->Rebin(binEgdeNiklas.size()-1, "h_pi0Smear", binEgdeNiklas.data());



    for (size_t i = 0; i < binEgdeNiklas.size() - 1; ++i) {
    h_pi0Ideal->SetBinContent(i+1,h_pi0Ideal->GetBinContent(i+1)/h_pi0Ideal->GetBinWidth(i+1));
    h_pi0Smear->SetBinContent(i+1,h_pi0Smear->GetBinContent(i+1)/h_pi0Smear->GetBinWidth(i+1));

    h_pi0Ideal->SetBinError(i+1,h_pi0Ideal->GetBinError(i+1)/h_pi0Ideal->GetBinWidth(i+1));
    h_pi0Smear->SetBinError(i+1,h_pi0Smear->GetBinError(i+1)/h_pi0Smear->GetBinWidth(i+1));


    }


    TCanvas *canFactor = new TCanvas("canFactor", "canFactor",158,28,900,918);
    setOPT_canvas(canFactor);
    
    canFactor->SetFillColor(10);
    canFactor->SetTopMargin(0.08);
    canFactor->SetRightMargin(0.12);
    //canFactor->SetLogy();
    canFactor->SetGridy();
   
    setOPT_TH1F(h_pi0Ideal,"#font[52]{M}_{ee} (GeV/#font[52]{c}^{2})","#pi^{0} in acc.",405,510);
    setOPT_TH1F(h_pi0Smear,"#font[52]{M}_{ee} (GeV/#font[52]{c}^{2})","#pi^{0} in acc.",405,510);
    setOPT_TH1F(h_pi0_niklas,"#font[52]{M}_{ee} (GeV/#font[52]{c}^{2})","#pi^{0} in acc.",405,510);
  //  setOPT_TH1F(h_ref,"#font[52]{M}_{ee} (GeV/#font[52]{c}^{2})","#pi^{0} in acc.",405,510);
    // setOPT_TH1F(h_pi0Ideal,"#font[52]{M}_{ee} (GeV/#font[52]{c}^{2})","Acceptance Corr. Factor ratio",510,510);
    // setOPT_TH1F(h_ref,"#font[52]{M}_{ee} (GeV/#font[52]{c}^{2})","Acceptance Corr. Factor",510,510);



   h_pi0Ideal->GetXaxis()->SetRangeUser(0., 0.2);
  
    h_pi0Ideal  ->SetMarkerStyle(8);
    h_pi0Smear  ->SetMarkerStyle(107);
    h_pi0_niklas->SetMarkerStyle(54);
    h_pi0_niklas2->SetMarkerStyle(21);
    h_ref        ->SetLineWidth(3);

   // h_ref         ->SetMarkerSize(1.5);
    h_pi0Ideal    ->SetMarkerSize(1.5);
    h_pi0Smear    ->SetMarkerSize(1.5);
    h_pi0_niklas  ->SetMarkerSize(1.5);
    h_pi0_niklas2 ->SetMarkerSize(1.5);





    h_pi0Ideal  ->SetMarkerColor(kBlue);
    h_pi0Smear  ->SetMarkerColor(kRed);
    h_ref       ->SetLineColor(kBlack);
    h_pi0_niklas->SetMarkerColor(kRed);
    h_pi0_niklas2->SetMarkerColor(kBlue);


    h_pi0Ideal->Draw();
    h_pi0Smear->Draw("same");
    h_pi0_niklas->Draw("same");
    h_pi0_niklas2->Draw("same");
    h_ref->Draw("same");




    


 setLegend5("Reference  ", h_ref,
            "#pi^{0},mass ideal, ideal look-up,this work", h_pi0Ideal,
            "#pi^{0},mass smear, ideal look-up,this work  ", h_pi0Smear,
            "#pi^{0},mass ideal, ideal look-up, standard ana.", h_pi0_niklas2,
            "#pi^{0},mass smear, ideal look-up, standard ana.", h_pi0_niklas
            
            );


  
//  TCanvas *canDivide = new TCanvas("canDivide", "",158,28,900,1018);
//   canDivide->SetFillColor(10);
//   canDivide->SetTopMargin(0.08);
//   canDivide->SetRightMargin(0.12);

//   h_CorrFactor->Divide(h_acc_niklas); 
//   h_CorrFactor->GetYaxis()->SetRangeUser(0, 2.);
//   h_CorrFactor->Draw("l");





    // TFile* outputFile = new TFile("~/march19AgAg/submit/EffCorrection/cocktail/AccCorr_excess_Rebin_NoPionv2.root", "RECREATE");
    // outputFile->cd();

   
    // h_ExcessAccCorr->Write();

}