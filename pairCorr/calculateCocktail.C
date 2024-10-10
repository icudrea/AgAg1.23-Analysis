//macro for calculating the cocktai; for every source and drop it in histo
//for 4pi, in acc, in acc*Eff
//for every centrality!!

void calculateCocktail() {
       
    static const Int_t MAX_MULT = 4;

    TString infile_w       = "~/march19AgAg/submit/EffCorrection/cocktail/w/w_cocktail_scaled.root";
    TString infile_wdalitz = "~/march19AgAg/submit/EffCorrection/cocktail/wdalitz/wdalitz_cocktail_scaled.root";
    TString infile_pi0     = "~/march19AgAg/submit/EffCorrection/cocktail/pi0/pi0_cocktail_scaled.root";
    TString infile_eta     = "~/march19AgAg/submit/EffCorrection/cocktail/eta/eta_cocktail_scaled.root";
    TString infile_rho     = "~/march19AgAg/submit/EffCorrection/cocktail/eho/rho_cocktail_scaled.root";

 
    // TString infile_w       = "~/march19AgAg/submit/EffCorrection/cocktail/w/w_SmearMomOnly_scaled_0515pi0_9opAngle.root";
    // TString infile_wdalitz = "~/march19AgAg/submit/EffCorrection/cocktail/wdalitz/wdalitz_SmearMomOnly_scaled_0515pi0_9opAngle.root";
    // TString infile_pi0     = "~/march19AgAg/submit/EffCorrection/cocktail/pi0/pi0_SmearMomOnly_scaled_0515pi0_9opAngle.root";
    // TString infile_eta     = "~/march19AgAg/submit/EffCorrection/cocktail/eta/eta_SmearMomOnly_scaled_0515pi0_9opAngle.root";
    // TString infile_rho     = "~/march19AgAg/submit/EffCorrection/cocktail/rho/rho_SmearMomOnly_scaled_0515pi0_9opAngle.root";
    

    TFile* file_w          = new TFile(infile_w, "READ");
    TFile* file_wdalitz    = new TFile(infile_wdalitz, "READ");
    TFile* file_pi0        = new TFile(infile_pi0, "READ");
    TFile* file_eta        = new TFile(infile_eta, "READ");
    TFile* file_rho        = new TFile(infile_rho, "READ");

   
    TH1D *h_mass_4pi_w[MAX_MULT];    
    TH1D *h_mass_acc_w[MAX_MULT];       
    TH1D *h_mass_EffAcc_w[MAX_MULT];     

    TH1D *h_mass_4pi_wdalitz[MAX_MULT];    
    TH1D *h_mass_acc_wdalitz[MAX_MULT];       
    TH1D *h_mass_EffAcc_wdalitz[MAX_MULT];   

    TH1D *h_mass_4pi_pi0[MAX_MULT];    
    TH1D *h_mass_acc_pi0[MAX_MULT];       
    TH1D *h_mass_EffAcc_pi0[MAX_MULT];  
    
    TH1D *h_mass_4pi_eta[MAX_MULT];    
    TH1D *h_mass_acc_eta[MAX_MULT];       
    TH1D *h_mass_EffAcc_eta[MAX_MULT];    
 
    TH1D *h_mass_4pi_rho[MAX_MULT];    
    TH1D *h_mass_acc_rho[MAX_MULT];       
    TH1D *h_mass_EffAcc_rho[MAX_MULT];    
    
    TH1D *h_cocktail_4pi[MAX_MULT];    
    TH1D *h_cocktail_acc[MAX_MULT];       
    TH1D *h_cocktail_EffAcc[MAX_MULT];    
    
    for (Int_t mult = 1; mult <= MAX_MULT; ++mult) {
        
        h_mass_4pi_w[mult-1]    = (TH1D*) file_w->Get(Form("h_m;%i", mult)); 
        h_mass_acc_w[mult-1]    = (TH1D*) file_w->Get(Form("h_m_acc;%i", mult));
        h_mass_EffAcc_w[mult-1] = (TH1D*) file_w->Get(Form("h_m_recoCut;%i", mult));

        h_mass_4pi_wdalitz[mult-1]   = (TH1D*) file_wdalitz->Get(Form("h_m;%i", mult)); 
        h_mass_acc_wdalitz[mult-1]   = (TH1D*) file_wdalitz->Get(Form("h_m_acc;%i", mult));
        h_mass_EffAcc_wdalitz[mult-1]= (TH1D*) file_wdalitz->Get(Form("h_m_recoCut;%i", mult));

        h_mass_4pi_pi0[mult-1]    = (TH1D*) file_pi0->Get(Form("h_m;%i", mult)); 
        h_mass_acc_pi0[mult-1]    = (TH1D*) file_pi0->Get(Form("h_m_acc;%i", mult));
        h_mass_EffAcc_pi0[mult-1] = (TH1D*) file_pi0->Get(Form("h_m_recoCut;%i", mult));
        
        h_mass_4pi_eta[mult-1]    = (TH1D*) file_eta->Get(Form("h_m;%i", mult)); 
        h_mass_acc_eta[mult-1]    = (TH1D*) file_eta->Get(Form("h_m_acc_;%i", mult));
        h_mass_EffAcc_eta[mult-1] = (TH1D*) file_eta->Get(Form("h_m_recoCut;%i", mult));

        h_mass_4pi_rho[mult-1]    = (TH1D*) file_rho->Get(Form("h_m_%i", mult)); 
        h_mass_acc_rho[mult-1]    = (TH1D*) file_rho->Get(Form("h_m_acc;%i", mult));
        h_mass_EffAcc_rho[mult-1] = (TH1D*) file_rho->Get(Form("h_m_recoCut%i", mult));


  
    
       
            h_cocktail_4pi[mult-1] = (TH1D*) h_mass_4pi_w[mult-1]->Clone(Form("h_cocktail_4pi_%i", mult));
            if (h_mass_4pi_wdalitz[mult-1]) h_cocktail_4pi[mult-1]->Add(h_mass_4pi_wdalitz[mult-1]);
            if (h_mass_4pi_pi0[mult-1])     h_cocktail_4pi[mult-1]->Add(h_mass_4pi_pi0[mult-1]);
            if (h_mass_4pi_eta[mult-1])     h_cocktail_4pi[mult-1]->Add(h_mass_4pi_eta[mult-1]);
            if (h_mass_4pi_rho[mult-1])     h_cocktail_4pi[mult-1]->Add(h_mass_4pi_rho[mult-1]);
        


       
            h_cocktail_acc[mult-1] = (TH1D*) h_mass_acc_w[mult-1]->Clone(Form("h_cocktail_acc_%i", mult));
            if (h_mass_acc_wdalitz[mult-1]) h_cocktail_acc[mult-1]->Add(h_mass_acc_wdalitz[mult-1]);
            if (h_mass_acc_pi0[mult-1])     h_cocktail_acc[mult-1]->Add(h_mass_acc_pi0[mult-1]);
            if (h_mass_acc_eta[mult-1])     h_cocktail_acc[mult-1]->Add(h_mass_acc_eta[mult-1]);
            if (h_mass_acc_rho[mult-1])     h_cocktail_acc[mult-1]->Add(h_mass_acc_rho[mult-1]);
        

            h_cocktail_EffAcc[mult-1] = (TH1D*) h_mass_EffAcc_w[mult-1]->Clone(Form("h_cocktail_EffAcc_%i", mult));
            if (h_mass_EffAcc_wdalitz[mult-1]) h_cocktail_EffAcc[mult-1]->Add(h_mass_EffAcc_wdalitz[mult-1]);
            if (h_mass_EffAcc_pi0[mult-1])     h_cocktail_EffAcc[mult-1]->Add(h_mass_EffAcc_pi0[mult-1]);
            if (h_mass_EffAcc_eta[mult-1])     h_cocktail_EffAcc[mult-1]->Add(h_mass_EffAcc_eta[mult-1]);
            if (h_mass_EffAcc_rho[mult-1])     h_cocktail_EffAcc[mult-1]->Add(h_mass_EffAcc_rho[mult-1]);
        
    }

   
    TFile* cocktail_4pi    = new TFile("~/march19AgAg/submit/EffCorrection/cocktail/Cocktail_9oAngle_4pi_wrho.root", "RECREATE");
    TFile* cocktail_acc    = new TFile("~/march19AgAg/submit/EffCorrection/cocktail/Cocktail_9oAngle_acc_wrho.root", "RECREATE");
    TFile* cocktail_EffAcc = new TFile("~/march19AgAg/submit/EffCorrection/cocktail/Cocktail_9oAngle_EffAcc_wrho.root", "RECREATE");
 

    // Write histograms to files
    for (Int_t mult = 1; mult <= MAX_MULT; ++mult) {
      
            cocktail_4pi->cd();  
            h_cocktail_4pi[mult-1]->Write();
       
            cocktail_acc->cd();  
            h_cocktail_acc[mult-1]->Write();
    
            cocktail_EffAcc->cd(); 
            h_cocktail_EffAcc[mult-1]->Write();

          
      
        
        }
    
}