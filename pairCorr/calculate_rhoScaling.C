
Double_t calculateIntegral(TH1D* hist, Double_t xMin, Double_t xMax) {
    int binMin = hist->GetXaxis()->FindBin(xMin);
    int binMax = hist->GetXaxis()->FindBin(xMax);
    return hist->Integral(binMin, binMax,"width");
}

void calculate_rhoScaling() {
       
    static const Int_t MAX_MULT = 4;
    
   //-----------------Rho from CG----------------
    TString f_rho_CG_1         = "~/lustre/hades/user/fseck/dilepton-omega/output_SFpol_par_dilepton_yield_mpty_AgAg1.23_cent0to10.root";
    TString f_rho_CG_2         = "~/lustre/hades/user/fseck/dilepton-omega/output_SFpol_par_dilepton_yield_mpty_AgAg1.23_cent10to20.root";
    TString f_rho_CG_3         = "~/lustre/hades/user/fseck/dilepton-omega/output_SFpol_par_dilepton_yield_mpty_AgAg1.23_cent20to30.root";
    TString f_rho_CG_4         = "~/lustre/hades/user/fseck/dilepton-omega/output_SFpol_par_dilepton_yield_mpty_AgAg1.23_cent30to40.root";
  //  TString f_rho_CG_ccTotal   = "~/lustre/hades/user/fseck/dilepton-omega/output_SFpol_par_dilepton_yield_mpty_AgAg1.23_cent0to40.root";

    TFile* file_CG_1       = new TFile(f_rho_CG_1, "READ");
    TFile* file_CG_2       = new TFile(f_rho_CG_2, "READ");
    TFile* file_CG_3       = new TFile(f_rho_CG_3, "READ");
    TFile* file_CG_4       = new TFile(f_rho_CG_4, "READ");
   // TFile* file_CG_ccTotal = new TFile(f_rho_CG_ccTotal, "READ");
    // TH1D* h_rho_CG_ccTotal  = (TH1D*) file_CG_ccTotal->Get("h1_inmed_rho_m");

   //--------------Rho from pluto-----------------------
    TString f_rho_pluto_ccTotal   = "~/lustre/hades/user/icudrea/mar19/loop/phd/pluto_files_ag123ag/rho/rho_SmearMom_Combined_allCC.root";
    TFile* file_pluto_ccTotal = new TFile(f_rho_pluto_ccTotal, "READ");
    
                                                    
    TH1D* h_rho_CG_1        = (TH1D*) file_CG_1->Get("h1_inmed_rho_m");
    TH1D* h_rho_CG_2        = (TH1D*) file_CG_2->Get("h1_inmed_rho_m");
    TH1D* h_rho_CG_3        = (TH1D*) file_CG_3->Get("h1_inmed_rho_m");
    TH1D* h_rho_CG_4        = (TH1D*) file_CG_4->Get("h1_inmed_rho_m");
  

    TH1D* h_rho_pluto_1     = (TH1D*) file_pluto_ccTotal->Get("h_m_1");
    TH1D* h_rho_pluto_2     = (TH1D*) file_pluto_ccTotal->Get("h_m_2");
    TH1D* h_rho_pluto_3     = (TH1D*) file_pluto_ccTotal->Get("h_m_3");
    TH1D* h_rho_pluto_4     = (TH1D*) file_pluto_ccTotal->Get("h_m_4");
   
    Double_t xMin = 0.2;
    Double_t xMax = 1.0;


    Double_t integral_CG_1 = calculateIntegral(h_rho_CG_1, xMin, xMax);
    Double_t integral_CG_2 = calculateIntegral(h_rho_CG_2, xMin, xMax);
    Double_t integral_CG_3 = calculateIntegral(h_rho_CG_3, xMin, xMax);
    Double_t integral_CG_4 = calculateIntegral(h_rho_CG_4, xMin, xMax);
    
    Double_t integral_pluto_1 = calculateIntegral(h_rho_pluto_1, xMin, xMax);
    Double_t integral_pluto_2 = calculateIntegral(h_rho_pluto_2, xMin, xMax);
    Double_t integral_pluto_3 = calculateIntegral(h_rho_pluto_3, xMin, xMax);
    Double_t integral_pluto_4 = calculateIntegral(h_rho_pluto_4, xMin, xMax);
    

    Double_t scaleFactor_1 = integral_CG_1/integral_pluto_1;
    Double_t scaleFactor_2 = integral_CG_2/integral_pluto_2;
    Double_t scaleFactor_3 = integral_CG_3/integral_pluto_3;
    Double_t scaleFactor_4 = integral_CG_4/integral_pluto_4;
    

    h_rho_pluto_1->Scale(scaleFactor_1);
    h_rho_pluto_2->Scale(scaleFactor_2);
    h_rho_pluto_3->Scale(scaleFactor_3);
    h_rho_pluto_4->Scale(scaleFactor_4);
    
  
    cout << "Scale Factor 1: " << scaleFactor_1 << "\n";
    cout << "Scale Factor 2: " << scaleFactor_2 << "\n";
    cout << "Scale Factor 3: " << scaleFactor_3 << "\n";
    cout << "Scale Factor 4: " << scaleFactor_4 << "\n";

    TCanvas* canvas = new TCanvas("canvas", "Scaled Histograms", 800, 600);
    canvas->Divide(2, 2); 
    canvas->SetLogy();

    canvas->cd(1);
    h_rho_CG_1->SetLineColor(kRed);
    h_rho_pluto_1->SetLineColor(kBlue);
    h_rho_CG_1->Draw();
    h_rho_pluto_1->Draw("SAME");

    canvas->cd(2);
    h_rho_CG_2->SetLineColor(kRed);
    h_rho_pluto_2->SetLineColor(kBlue);
    h_rho_CG_2->Draw();
    h_rho_pluto_2->Draw("SAME");

    canvas->cd(3);
    h_rho_CG_3->SetLineColor(kRed);
    h_rho_pluto_3->SetLineColor(kBlue);
    h_rho_CG_3->Draw();
    h_rho_pluto_3->Draw("SAME");

    canvas->cd(4);
    h_rho_CG_4->SetLineColor(kRed);
    h_rho_pluto_4->SetLineColor(kBlue);
    h_rho_CG_4->Draw();
    h_rho_pluto_4->Draw("SAME");


    canvas->Update();


 
// Scale Factor 1: 6.67093e-09
// Scale Factor 2: 3.80744e-09
// Scale Factor 3: 2.07883e-09
// Scale Factor 4: 1.00357e-09

 
    TFile* outputFile = new TFile("~/march19AgAg/submit/EffCorrection/cocktail/cocktail_9oAngle100Mom_rho.root", "RECREATE");
    outputFile->cd();
     
    h_rho_pluto_1->Write();
    h_rho_pluto_2->Write();
    h_rho_pluto_3->Write();
    h_rho_pluto_4->Write();


    outputFile->Close();
    
}
