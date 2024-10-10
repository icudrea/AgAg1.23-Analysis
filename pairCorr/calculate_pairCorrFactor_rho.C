void calculate_pairCorrFactor_rho() {
       
    static const Int_t MAX_MULT = 4;


    //TString f_rho    = "~/march19AgAg/submit/EffCorrection/cocktail/rho_cocktail_scaled.root";
    TString f_rho    ="~/march19AgAg/submit/EffCorrection/cocktail/rho/scaled_9oAngle100Mom_rho_allCC.root";

    TFile* file_rho     = new TFile(f_rho, "READ");
   

    // TH1D *h_cocktail_4pi[MAX_MULT];    
    // TH1D *h_cocktail_acc[MAX_MULT];       
    // TH1D *h_cocktail_EffAcc[MAX_MULT];    

    
    // TH1D *h_AccFactor[MAX_MULT];    
    // TH1D *h_EffFactor[MAX_MULT];       
   

    // for (Int_t mult = 1; mult <= MAX_MULT; ++mult) {
    //     h_cocktail_4pi[mult-1]    = (TH1D*) file_rho->Get(Form("h_m_%i", mult));
    //     h_cocktail_acc[mult-1]    = (TH1D*) file_rho->Get(Form("h_m_acc_%i", mult));
    //     h_cocktail_EffAcc[mult-1] = (TH1D*) file_rho->Get(Form("h_m_recoCut_%i", mult));

    //    h_AccFactor[mult-1]   = (TH1D*) h_cocktail_acc[mult-1]->Clone(Form("h_AccFactor_%i",mult));
    //    h_EffFactor[mult-1]   = (TH1D*) h_cocktail_EffAcc[mult-1]->Clone(Form("h_EffFactor_%i",mult));

    //    h_AccFactor[mult-1]->Divide(h_cocktail_4pi[mult-1]);
    //    h_EffFactor[mult-1]->Divide(h_cocktail_acc[mult-1]);
   
    // }

   

 
    // TFile* outputFile = new TFile("~/march19AgAg/submit/EffCorrection/cocktail/PairCorrFactors_9oAngle100Mom_CGrho.root", "RECREATE");
    // outputFile->cd();

    // for (Int_t mult = 1; mult <= MAX_MULT; ++mult) {

    // h_AccFactor[mult-1] ->Write();
    // h_EffFactor[mult-1] ->Write();
    // }
    // outputFile->Close();



TH1D* h_cocktail_4pi_CCTotal    = (TH1D*) file_rho->Get("h_mass_4pi_rho_CCTotal");
TH1D* h_cocktail_acc_CCTotal    = (TH1D*) file_rho->Get("h_mass_acc_rho_CCTotal");
TH1D* h_cocktail_EffAcc_CCTotal = (TH1D*) file_rho->Get("h_mass_EffAcc_rho_CCTotal");

if (!h_cocktail_4pi_CCTotal || !h_cocktail_acc_CCTotal || !h_cocktail_EffAcc_CCTotal) {
    cout << "Error: One or more histograms not found in the file." << endl;
    return;
}

TH1D* h_AccFactor  = (TH1D*) h_cocktail_acc_CCTotal->Clone("h_AccFactor");
TH1D* h_EffFactor  = (TH1D*) h_cocktail_EffAcc_CCTotal->Clone("h_EffFactor");

//  calculate the factors
h_AccFactor->Divide(h_cocktail_4pi_CCTotal);
h_EffFactor->Divide(h_cocktail_acc_CCTotal);


TH1D* h_AccFactor_inv  = (TH1D*) h_cocktail_4pi_CCTotal->Clone("h_AccFactor_inv");
TH1D* h_EffFactor_inv  = (TH1D*) h_cocktail_acc_CCTotal->Clone("h_EffFactor_inv");

//  calculate the factors
h_AccFactor_inv->Divide(h_cocktail_acc_CCTotal);
h_EffFactor_inv->Divide(h_cocktail_EffAcc_CCTotal);


 
    TFile* outputFile = new TFile("~/march19AgAg/submit/EffCorrection/cocktail/PairCorrFactors_9oAngle100Mom_CGrho_allCC.root", "RECREATE");
    outputFile->cd();

   
    h_AccFactor->Write();
    h_EffFactor->Write();
    h_AccFactor_inv->Write();
    h_EffFactor_inv->Write();
    
    outputFile->Close();
    
}
