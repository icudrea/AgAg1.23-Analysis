
//calculate scaleSources 
void calculate_scaledSources_CCTotal() {

    static const Int_t MAX_MULT = 4;
    //Float_t MultPionsCC[MAX_MULT] = {8.22, 5.90, 4.13, 2.82}; 
    Float_t MultPionsCC[MAX_MULT] = {8.22, 5.90, 4.13, 2.82}; 
    Float_t divideFactor = 4 * 5.26;


    // TString infile_w       = "~/march19AgAg/submit/EffCorrection/cocktail/w/";
    // TString infile_wdalitz = "~/march19AgAg/submit/EffCorrection/cocktail/wdalitz/";
    // TString infile_pi0     = "~/march19AgAg/submit/EffCorrection/cocktail/pi0/";
    // TString infile_eta     = "~/march19AgAg/submit/EffCorrection/cocktail/eta/";
    // TString infile_rho     = "~/march19AgAg/submit/EffCorrection/cocktail/rho/";

    TString infile_w       = "~/march19AgAg/submit/EffCorrection/cocktail/w/w_SmearMomOnly_scaled_0515pi0_9opAngle.root";
    TString infile_wdalitz = "~/march19AgAg/submit/EffCorrection/cocktail/wdalitz/wdalitz_SmearMomOnly_scaled_0515pi0_9opAngle.root";
    TString infile_pi0     = "~/march19AgAg/submit/EffCorrection/cocktail/pi0/pi0_SmearMomOnly_scaled_0515pi0_9opAngle.root";
    TString infile_eta     = "~/march19AgAg/submit/EffCorrection/cocktail/eta/eta_SmearMomOnly_scaled_0515pi0_9opAngle.root";
    TString infile_rho     = "~/march19AgAg/submit/EffCorrection/cocktail/rho/rho_SmearMomOnly_scaled_0515pi0_9opAngle.root";
    

    

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
    
 
    
    for (Int_t mult = 1; mult <= MAX_MULT; ++mult) {

        h_mass_4pi_w[mult-1]    = (TH1D*) file_w->Get(Form("h_m;%i", mult)); 
        h_mass_acc_w[mult-1]    = (TH1D*) file_w->Get(Form("h_m_acc_opAng;%i", mult));
        h_mass_EffAcc_w[mult-1] = (TH1D*) file_w->Get(Form("h_m_recoOpang;%i", mult));

        h_mass_4pi_wdalitz[mult-1]   = (TH1D*) file_wdalitz->Get(Form("h_m;%i", mult)); 
        h_mass_acc_wdalitz[mult-1]   = (TH1D*) file_wdalitz->Get(Form("h_m_acc_opAng;%i", mult));
        h_mass_EffAcc_wdalitz[mult-1]= (TH1D*) file_wdalitz->Get(Form("h_m_recoOpang;%i", mult));

        h_mass_4pi_pi0[mult-1]    = (TH1D*) file_pi0->Get(Form("h_m;%i", mult)); 
        h_mass_acc_pi0[mult-1]    = (TH1D*) file_pi0->Get(Form("h_m_acc_opAng;%i", mult));
        h_mass_EffAcc_pi0[mult-1] = (TH1D*) file_pi0->Get(Form("h_m_recoOpang;%i", mult));
        
        h_mass_4pi_eta[mult-1]    = (TH1D*) file_eta->Get(Form("h_m;%i", mult)); 
        h_mass_acc_eta[mult-1]    = (TH1D*) file_eta->Get(Form("h_m_acc_opAng;%i", mult));
        h_mass_EffAcc_eta[mult-1] = (TH1D*) file_eta->Get(Form("h_m_recoOpang;%i", mult));

        h_mass_4pi_rho[mult-1]    = (TH1D*) file_rho->Get(Form("h_m_%i", mult)); 
        h_mass_acc_rho[mult-1]    = (TH1D*) file_rho->Get(Form("h_m_acc_opAng_%i", mult));
        h_mass_EffAcc_rho[mult-1] = (TH1D*) file_rho->Get(Form("h_m_recoOpang_%i", mult));

        
        // h_mass_4pi_w[mult-1]    = (TH1D*) file_w->Get(Form("h_m;%i", mult)); 
        // h_mass_acc_w[mult-1]    = (TH1D*) file_w->Get(Form("h_m_acc;%i", mult));
        // h_mass_EffAcc_w[mult-1] = (TH1D*) file_w->Get(Form("h_m_recoCut;%i", mult));

        // h_mass_4pi_wdalitz[mult-1]   = (TH1D*) file_wdalitz->Get(Form("h_m;%i", mult)); 
        // h_mass_acc_wdalitz[mult-1]   = (TH1D*) file_wdalitz->Get(Form("h_m_acc;%i", mult));
        // h_mass_EffAcc_wdalitz[mult-1]= (TH1D*) file_wdalitz->Get(Form("h_m_recoCut;%i", mult));

        // h_mass_4pi_pi0[mult-1]    = (TH1D*) file_pi0->Get(Form("h_m;%i", mult)); 
        // h_mass_acc_pi0[mult-1]    = (TH1D*) file_pi0->Get(Form("h_m_acc;%i", mult));
        // h_mass_EffAcc_pi0[mult-1] = (TH1D*) file_pi0->Get(Form("h_m_recoCut;%i", mult));
        
        // h_mass_4pi_eta[mult-1]    = (TH1D*) file_eta->Get(Form("h_m;%i", mult)); 
        // h_mass_acc_eta[mult-1]    = (TH1D*) file_eta->Get(Form("h_m_acc;%i", mult));
        // h_mass_EffAcc_eta[mult-1] = (TH1D*) file_eta->Get(Form("h_m_recoCut;%i", mult));

        // h_mass_4pi_rho[mult-1]    = (TH1D*) file_rho->Get(Form("h_m_%i", mult)); 
        // h_mass_acc_rho[mult-1]    = (TH1D*) file_rho->Get(Form("h_m_acc_%i", mult));
        // h_mass_EffAcc_rho[mult-1] = (TH1D*) file_rho->Get(Form("h_m_recoCut_%i", mult));


    }

        TH1D* h_mass_4pi_w_CCTotal   = (TH1D*) h_mass_4pi_w[0]->Clone("h_mass_4pi_w_CCTotal"); 
        TH1D* h_mass_acc_w_CCTotal   = (TH1D*) h_mass_acc_w[0]->Clone("h_mass_acc_w_CCTotal");
        TH1D* h_mass_EffAcc_w_CCTotal= (TH1D*) h_mass_EffAcc_w[0]->Clone("h_mass_EffAcc_w_CCTotal");

        TH1D* h_mass_4pi_wdalitz_CCTotal  = (TH1D*) h_mass_4pi_wdalitz[0]->Clone("h_mass_4pi_wdalitz_CCTotal"); 
        TH1D* h_mass_acc_wdalitz_CCTotal  = (TH1D*) h_mass_acc_wdalitz[0]->Clone("h_mass_acc_wdalitz_CCTotal");
        TH1D* h_mass_EffAcc_wdalitz_CCTotal= (TH1D*)h_mass_EffAcc_wdalitz[0]->Clone("h_mass_EffAcc_wdalitz_CCTotal");

        TH1D* h_mass_4pi_pi0_CCTotal   = (TH1D*) h_mass_4pi_pi0[0]->Clone("h_mass_4pi_pi0_CCTotal");
        TH1D* h_mass_acc_pi0_CCTotal   = (TH1D*) h_mass_acc_pi0[0]->Clone("h_mass_acc_pi0_CCTotal");
        TH1D* h_mass_EffAcc_pi0_CCTotal= (TH1D*) h_mass_EffAcc_pi0[0]->Clone("h_mass_EffAcc_pi0_CCTotal");

     
        TH1D* h_mass_4pi_eta_CCTotal   = (TH1D*) h_mass_4pi_eta[0]->Clone("h_mass_4pi_eta_CCTotal");
        TH1D* h_mass_acc_eta_CCTotal   = (TH1D*) h_mass_acc_eta[0]->Clone("h_mass_acc_eta_CCTotal");
        TH1D* h_mass_EffAcc_eta_CCTotal= (TH1D*) h_mass_EffAcc_eta[0]->Clone("h_mass_EffAcc_eta_CCTotal");
        
        TH1D* h_mass_4pi_rho_CCTotal   = (TH1D*) h_mass_4pi_rho[0]->Clone("h_mass_4pi_rho_CCTotal");
        TH1D* h_mass_acc_rho_CCTotal   = (TH1D*) h_mass_acc_rho[0]->Clone("h_mass_acc_rho_CCTotal");
        TH1D* h_mass_EffAcc_rho_CCTotal= (TH1D*) h_mass_EffAcc_rho[0]->Clone("h_mass_EffAcc_rho_CCTotal");
        
        //Resetting histograms for 'w'
        h_mass_4pi_w_CCTotal->Reset();
        h_mass_acc_w_CCTotal->Reset();
        h_mass_EffAcc_w_CCTotal->Reset();

        // Resetting histograms for 'wdalitz'
        h_mass_4pi_wdalitz_CCTotal->Reset();
        h_mass_acc_wdalitz_CCTotal->Reset();
        h_mass_EffAcc_wdalitz_CCTotal->Reset();

        //Resetting histograms for 'pi0'
        h_mass_4pi_pi0_CCTotal->Reset();
        h_mass_acc_pi0_CCTotal->Reset();
        h_mass_EffAcc_pi0_CCTotal->Reset();

        // Resetting histograms for 'eta'
        h_mass_4pi_eta_CCTotal->Reset();
        h_mass_acc_eta_CCTotal->Reset();
        h_mass_EffAcc_eta_CCTotal->Reset();

        // // Resetting histograms for 'rho'
        h_mass_4pi_rho_CCTotal->Reset();
        h_mass_acc_rho_CCTotal->Reset();
        h_mass_EffAcc_rho_CCTotal->Reset();

        for (Int_t mult = 1; mult <= MAX_MULT; ++mult) {
        h_mass_4pi_w_CCTotal->Add(h_mass_4pi_w[mult-1], MultPionsCC[mult-1]);
        h_mass_acc_w_CCTotal->Add(h_mass_acc_w[mult-1], MultPionsCC[mult-1]);
        h_mass_EffAcc_w_CCTotal->Add(h_mass_EffAcc_w[mult-1], MultPionsCC[mult-1]);

        h_mass_4pi_wdalitz_CCTotal->Add(h_mass_4pi_wdalitz[mult-1], MultPionsCC[mult-1]);   
        h_mass_acc_wdalitz_CCTotal->Add(h_mass_acc_wdalitz[mult-1], MultPionsCC[mult-1]);   
        h_mass_EffAcc_wdalitz_CCTotal->Add(h_mass_EffAcc_wdalitz[mult-1], MultPionsCC[mult-1]);   

        h_mass_4pi_pi0_CCTotal->Add(h_mass_4pi_pi0[mult-1], MultPionsCC[mult-1]);
        h_mass_acc_pi0_CCTotal->Add(h_mass_acc_pi0[mult-1], MultPionsCC[mult-1]);
        h_mass_EffAcc_pi0_CCTotal->Add(h_mass_EffAcc_pi0[mult-1], MultPionsCC[mult-1]);

        h_mass_4pi_eta_CCTotal->Add(h_mass_4pi_eta[mult-1], MultPionsCC[mult-1]);
        h_mass_acc_eta_CCTotal->Add(h_mass_acc_eta[mult-1], MultPionsCC[mult-1]);
        h_mass_EffAcc_eta_CCTotal->Add(h_mass_EffAcc_eta[mult-1], MultPionsCC[mult-1]);
        h_mass_4pi_rho_CCTotal->Add(h_mass_4pi_rho[mult-1], MultPionsCC[mult-1]);
        h_mass_acc_rho_CCTotal->Add(h_mass_acc_rho[mult-1], MultPionsCC[mult-1]);
        h_mass_EffAcc_rho_CCTotal->Add(h_mass_EffAcc_rho[mult-1], MultPionsCC[mult-1]);
       }


        h_mass_4pi_w_CCTotal->Scale(1.0/divideFactor);
        h_mass_acc_w_CCTotal->Scale(1.0/divideFactor);
        h_mass_EffAcc_w_CCTotal->Scale(1.0/divideFactor);

        h_mass_4pi_wdalitz_CCTotal->Scale(1.0/divideFactor);
        h_mass_acc_wdalitz_CCTotal->Scale(1.0/divideFactor);  
        h_mass_EffAcc_wdalitz_CCTotal->Scale(1.0/divideFactor);

        h_mass_4pi_pi0_CCTotal->Scale(1.0/divideFactor);
        h_mass_acc_pi0_CCTotal->Scale(1.0/divideFactor);
        h_mass_EffAcc_pi0_CCTotal->Scale(1.0/divideFactor);

        h_mass_4pi_eta_CCTotal->Scale(1.0/divideFactor);
        h_mass_acc_eta_CCTotal->Scale(1.0/divideFactor);
        h_mass_EffAcc_eta_CCTotal->Scale(1.0/divideFactor);

        h_mass_4pi_rho_CCTotal->Scale(1.0/divideFactor);
        h_mass_acc_rho_CCTotal->Scale(1.0/divideFactor);
        h_mass_EffAcc_rho_CCTotal->Scale(1.0/divideFactor);



  
   
    TFile* f_pi0 = new TFile("~/march19AgAg/submit/EffCorrection/cocktail/pi0/scaled_smear_SmearMomOnly_9oAngle_allCC.root", "RECREATE");
    TFile* f_eta = new TFile("~/march19AgAg/submit/EffCorrection/cocktail/eta/scaled_smear_9oAngle_eta_allCC.root", "RECREATE");
    TFile* f_w   = new TFile("~/march19AgAg/submit/EffCorrection/cocktail/w/scaled_smear_9oAngle_w_allCC.root", "RECREATE");
    TFile* f_wD  = new TFile("~/march19AgAg/submit/EffCorrection/cocktail/wdalitz/scaled_smear_9oAngle_wD_allCC.root", "RECREATE");
    TFile* f_rho = new TFile("~/march19AgAg/submit/EffCorrection/cocktail/rho/scaled_smear_9oAngle_rho_allCC.root", "RECREATE");
 
        f_w->cd();
        h_mass_4pi_w_CCTotal->Write();
        h_mass_acc_w_CCTotal->Write();
        h_mass_EffAcc_w_CCTotal->Write();

        f_wD->cd();
        h_mass_4pi_wdalitz_CCTotal->Write();
        h_mass_acc_wdalitz_CCTotal->Write();  
        h_mass_EffAcc_wdalitz_CCTotal->Write();


        f_pi0->cd();
        h_mass_4pi_pi0_CCTotal->Write();
        h_mass_acc_pi0_CCTotal->Write();
        h_mass_EffAcc_pi0_CCTotal->Write();

        f_eta->cd();
        h_mass_4pi_eta_CCTotal->Write();
        h_mass_acc_eta_CCTotal->Write();
        h_mass_EffAcc_eta_CCTotal->Write();

        f_rho->cd();
        h_mass_4pi_rho_CCTotal->Write();
        h_mass_acc_rho_CCTotal->Write();
        h_mass_EffAcc_rho_CCTotal->Write();
    

          
      
        
        
    
}