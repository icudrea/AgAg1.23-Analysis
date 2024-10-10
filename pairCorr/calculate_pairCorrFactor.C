void calculate_pairCorrFactor() {
       
    static const Int_t MAX_MULT = 4;


    TString f_4pi    = "~/march19AgAg/submit/EffCorrection/cocktail/Cocktail_9oAngle100Mom_4pi_wrho.root";
    TString f_acc    = "~/march19AgAg/submit/EffCorrection/cocktail/Cocktail_9oAngle100Mom_acc_wrho.root";
    TString f_EffAcc = "~/march19AgAg/submit/EffCorrection/cocktail/Cocktail_9oAngle100Mom_EffAcc_wrho.root";

    // TString f_4pi    = "~/march19AgAg/submit/EffCorrection/cocktail/Cocktail_9oAngle_4pi_wrho.root";
    // TString f_acc    = "~/march19AgAg/submit/EffCorrection/cocktail/Cocktail_9oAngle_acc_wrho.root";
    // TString f_EffAcc = "~/march19AgAg/submit/EffCorrection/cocktail/Cocktail_9oAngle_EffAcc_wrho.root";



    TFile* file_4pi     = new TFile(f_4pi, "READ");
    TFile* file_acc     = new TFile(f_acc, "READ");
    TFile* file_EffAcc  = new TFile(f_EffAcc, "READ");

       
    TH1D *h_cocktail_4pi[MAX_MULT];    
    TH1D *h_cocktail_acc[MAX_MULT];       
    TH1D *h_cocktail_EffAcc[MAX_MULT];    

    
    TH1D *h_AccFactor[MAX_MULT];    
    TH1D *h_EffFactor[MAX_MULT];       
   

    for (Int_t mult = 1; mult <= MAX_MULT; ++mult) {
        h_cocktail_4pi[mult-1]    = (TH1D*) file_4pi->Get(Form("h_cocktail_4pi_%i", mult));
        h_cocktail_acc[mult-1]    = (TH1D*) file_acc->Get(Form("h_cocktail_acc_%i", mult));
        h_cocktail_EffAcc[mult-1] = (TH1D*) file_EffAcc->Get(Form("h_cocktail_EffAcc_%i", mult));

       h_AccFactor[mult-1]   = (TH1D*) h_cocktail_acc[mult-1]->Clone(Form("h_AccFactor_%i",mult));
       h_EffFactor[mult-1]   = (TH1D*) h_cocktail_EffAcc[mult-1]->Clone(Form("h_EffFactor_%i",mult));

       h_AccFactor[mult-1]->Divide(h_cocktail_4pi[mult-1]);
       h_EffFactor[mult-1]->Divide(h_cocktail_acc[mult-1]);
   
    }

   

 
    TFile* outputFile = new TFile("~/march19AgAg/submit/EffCorrection/cocktail/PairCorrFactors_9oAngle_fullCocktail.root", "RECREATE");
    outputFile->cd();

    for (Int_t mult = 1; mult <= MAX_MULT; ++mult) {

    h_AccFactor[mult-1] ->Write();
    h_EffFactor[mult-1] ->Write();
    }
    outputFile->Close();
    
}
