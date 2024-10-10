#include "plot_style.C"

Int_t APart[5]     = {102, 159, 113, 80, 55};
//Int_t APart_Jan[5] = {102, 160, 114, 81, 56};

Float_t linearScaling(Int_t A, Float_t totalMult) {  
    Float_t returnValue = totalMult * ((float)A / (float)APart[0]);
    return returnValue;
}

Float_t fourThirdScaling(Int_t A, Float_t totalMult) {
    Float_t returnValue = totalMult * pow((float)A / (float)APart[0], 4./3.);
    return returnValue;
}

void draw_ScaledSpectra_opAng(TString sourceName = "pion") {
    TString source[] = {"pion", "eta", "omega_dalitz", "omega","phi","rho"};
    Int_t sourceIndex = -1;

    for (Int_t i = 0; i < 6; ++i) {
        if (source[i] == sourceName) {
            sourceIndex = i;
            break;
        }
    }
    
    if (sourceIndex == -1) {
        cout << "Error: Source " << sourceName << " not found DAMN." << endl;
        return;
    }

    // TString infileNameAcc = "~/lustre/hades/user/icudrea/mar19/loop/phd/pluto_files_ag123ag/w/w_SmearMomCocktail_allCC.root";
    // TFile* file = new TFile(infileNameAcc, "READ");

    TString infileNameAcc = "~/lustre/hades/user/icudrea/mar19/loop/phd/pluto_files_ag123ag/pi0/pi0_SmearMomCocktail_allCC.root";
    TFile* file = new TFile(infileNameAcc, "READ");

    static const Int_t MAX_MULT = 4;
    TH1D *h_mass_4pi[MAX_MULT];    
    TH1D *h_mass_acc[MAX_MULT];       
    TH1D *h_mass_EffAcc[MAX_MULT];     

    for (Int_t mult = 1; mult <= MAX_MULT; ++mult) {
        h_mass_4pi[mult-1]    = (TH1D*) file->Get(Form("h_m_%i", mult)); 
        h_mass_acc[mult-1]    = (TH1D*) file->Get(Form("h_m_acc_opAng_%i", mult));
        h_mass_EffAcc[mult-1] = (TH1D*) file->Get(Form("h_m_recoOpang_%i", mult));

        if (!h_mass_4pi[mult-1] || !h_mass_acc[mult-1] || !h_mass_EffAcc[mult-1]) {
            cout << "Error: One or more histograms not found for multiplicity " << mult << endl;
            continue;
        }

        //////////////////////////////////////////////////////
        TString APartScaling[5]   = {"linear", "linear", "fourthird", "fourthird", "fourthird"};
        Float_t MultPerApart[5]   = {0.055, 8e-4, 6.91e-6, 6.91e-6, 4.15e-8}; 
        Float_t BR[5]             = {0.01174, 0.0069, 7.7e-4, 7.3e-5, 2.95e-4};
        Float_t CG_scaling[MAX_MULT+1]     = {3.3901925e-09, 6.67093e-09, 3.80744e-09,2.07883e-09, 1.00357e-09};
      

      //Float_t MultPionsCC[4]    = {8.22, 5.90, 4.13, 2.82}; 
        Float_t MultPerEventCC[5][MAX_MULT+1];
        Float_t NPionsPerEvent[MAX_MULT+1]     = {5.26, 8.22, 5.9, 4.13, 2.82};  
       // Float_t NPionsPerEvent_Jan[MAX_MULT+1] = {5.26, 9.05, 6.7, 4.95, 3.55};  //for APart = 160,114,81,56



        for (Int_t src = 0; src < 5; ++src) {  
            for (Int_t mult = 0; mult <= MAX_MULT; ++mult) {
          
                if (APartScaling[src] == "linear") {
                    MultPerEventCC[src][mult] = linearScaling(APart[mult], MultPerApart[src]*APart[0]);
                } else if (APartScaling[src] == "fourthird") {
                    MultPerEventCC[src][mult] = fourThirdScaling(APart[mult], MultPerApart[src]*APart[0]);                
                }

                // Display the computed value for each src and mult
                 cout << "MultPerEventCC[" << src << "][" << mult << "] = " << MultPerEventCC[src][mult] <<endl;
            }
        }

       
       

       // cout<<"brValue: "<<brValue<<endl;
      // cout<<"multPions: "<<multPions<<endl;

        Int_t n_bins  = h_mass_4pi[0]->GetNbinsX();
        Int_t Nevents = h_mass_4pi[0]->GetEntries();


        for (Int_t i = 1; i <= n_bins; i++) {
            Float_t N4pi    = h_mass_4pi[mult-1]->GetBinContent(i);
            Float_t Nacc    = h_mass_acc[mult-1]->GetBinContent(i);
            Float_t Neffacc = h_mass_EffAcc[mult-1]->GetBinContent(i);

            Float_t N4pi_error    = h_mass_4pi[mult-1]->GetBinError(i);
            Float_t Nacc_error    = h_mass_acc[mult-1]->GetBinError(i);
            Float_t Neffacc_error = h_mass_EffAcc[mult-1]->GetBinError(i);

            Float_t width = h_mass_4pi[0]->GetBinWidth(i);
          if(sourceIndex<5){
            h_mass_4pi[mult-1]->SetBinContent(i, N4pi / width);
            h_mass_acc[mult-1]->SetBinContent(i, Nacc / width);
            h_mass_EffAcc[mult-1]->SetBinContent(i, Neffacc / width);

            h_mass_4pi[mult-1]->SetBinError(i, N4pi_error / width);
            h_mass_acc[mult-1]->SetBinError(i, Nacc_error / width);
            h_mass_EffAcc[mult-1]->SetBinError(i, Neffacc_error / width);
          }
        }
        // Float_t brValue  = BR[sourceIndex]; 
        // Float_t multPions = MultPerEventCC[sourceIndex][mult];
         

         if (sourceIndex < 5){
         Float_t scaleFactor = ( BR[sourceIndex] * MultPerEventCC[sourceIndex][mult]) / (Nevents*NPionsPerEvent[mult]);
         h_mass_4pi[mult-1]->Scale(scaleFactor);
         h_mass_acc[mult-1]->Scale(scaleFactor);
         h_mass_EffAcc[mult-1]->Scale(scaleFactor); 
         }

         else if(sourceIndex == 5) {

         Float_t scaleFactor = CG_scaling[mult]/(NPionsPerEvent[mult]);
         
         h_mass_4pi[mult-1]->Scale(scaleFactor);
         h_mass_acc[mult-1]->Scale(scaleFactor);
         h_mass_EffAcc[mult-1]->Scale(scaleFactor); 

         }
    }


    
        TFile *outputFile = new TFile("~/march19AgAg/submit/EffCorrection/cocktail/pi0_SmearMom_cocktail_9opAng_scaled.root", "RECREATE");
        outputFile->cd();

        for (Int_t mult = 1; mult <= MAX_MULT; ++mult) {

        h_mass_4pi[mult-1]->Write();
        h_mass_acc[mult-1]->Write();
        h_mass_EffAcc[mult-1]->Write();
        }

    file->Close();
}
