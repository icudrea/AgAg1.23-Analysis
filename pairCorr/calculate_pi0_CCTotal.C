

void calculate_pi0_CCTotal() {

    static const Int_t MAX_MULT = 4;
    //Float_t MultPionsCC[MAX_MULT] = {8.22, 5.90, 4.13, 2.82}; 
    Float_t MultPionsCC[MAX_MULT] = {8.22, 5.90, 4.13, 2.82}; 
    Float_t divideFactor = 4 * 5.26;


    TString infile_pi0     = "~/march19AgAg/submit/EffCorrection/cocktail/pi0/pi0_SmearMomOnly_scaled_0515pi0_9opAngle100Mom.root";

    TFile* file_pi0        = new TFile(infile_pi0, "READ");
   

    TH1D *h_mass_4pi_pi0[MAX_MULT];    
    TH1D *h_mass_acc_pi0[MAX_MULT];       
    TH1D *h_mass_EffAcc_pi0[MAX_MULT];  
    

 
    
    for (Int_t mult = 1; mult <= MAX_MULT; ++mult) {

    

         h_mass_4pi_pi0[mult-1]    = (TH1D*) file_pi0->Get(Form("h_m;%i", mult)); 
         h_mass_acc_pi0[mult-1]    = (TH1D*) file_pi0->Get(Form("h_m_acc;%i", mult));
         h_mass_EffAcc_pi0[mult-1] = (TH1D*) file_pi0->Get(Form("h_m_recoCut;%i", mult));
       

    }

       
        TH1D* h_mass_4pi_pi0_CCTotal   = (TH1D*) h_mass_4pi_pi0[0]->Clone("h_mass_4pi_pi0_CCTotal");
        TH1D* h_mass_acc_pi0_CCTotal   = (TH1D*) h_mass_acc_pi0[0]->Clone("h_mass_acc_pi0_CCTotal");
        TH1D* h_mass_EffAcc_pi0_CCTotal= (TH1D*) h_mass_EffAcc_pi0[0]->Clone("h_mass_EffAcc_pi0_CCTotal");

     
      
        //Resetting histograms for 'pi0'
        h_mass_4pi_pi0_CCTotal->Reset();
        h_mass_acc_pi0_CCTotal->Reset();
        h_mass_EffAcc_pi0_CCTotal->Reset();

       

        for (Int_t mult = 1; mult <= MAX_MULT; ++mult) {
       

        h_mass_4pi_pi0_CCTotal->Add(h_mass_4pi_pi0[mult-1], MultPionsCC[mult-1]);
        h_mass_acc_pi0_CCTotal->Add(h_mass_acc_pi0[mult-1], MultPionsCC[mult-1]);
        h_mass_EffAcc_pi0_CCTotal->Add(h_mass_EffAcc_pi0[mult-1], MultPionsCC[mult-1]);
       }


       
        h_mass_4pi_pi0_CCTotal->Scale(1.0/divideFactor);
        h_mass_acc_pi0_CCTotal->Scale(1.0/divideFactor);
        h_mass_EffAcc_pi0_CCTotal->Scale(1.0/divideFactor);

       



  
   
    TFile* f_pi0 = new TFile("~/march19AgAg/submit/EffCorrection/cocktail/pi0/scaled_0515pi0_SmearMomOnly_9oAngle100Mom_allCC.root", "RECREATE");
   
 
       

        f_pi0->cd();
        h_mass_4pi_pi0_CCTotal->Write();
        h_mass_acc_pi0_CCTotal->Write();
        h_mass_EffAcc_pi0_CCTotal->Write();

       
          
      
        
        
    
}