
//macro for calculating the cocktail
//for 4pi, in acc, in acc*Eff
//for 0 to 40. Continuation of calculateCocktail.C
void calculateCocktail0to40() {
       
    static const Int_t MAX_MULT = 4;
    Float_t MultPionsCC[MAX_MULT] = {8.22, 5.90, 4.13, 2.82}; 
    Float_t divideFactor = 4 * 5.26;

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

 
    // TFile* outputFile = new TFile("~/march19AgAg/submit/EffCorrection/cocktail/Cocktail_9oAngle_CCTotal_wrho.root", "RECREATE");
    // outputFile->cd();
     
    // h_cocktail_4pi_CCTotal->Write();
    // h_cocktail_acc_CCTotal->Write();
    // h_cocktail_EffAcc_CCTotal->Write();

    // outputFile->Close();
    
}
