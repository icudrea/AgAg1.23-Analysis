#include "plot_style.C"


void draw_acc1D() {

   
 TString fileNameWithData;
 TString fileNameWithData2;

  //fileNameWithData = "/u/icudrea/lustre/hades/user/icudrea/mar19/loop/phd/SingleCorrection/SingleEffCorr_wIdealMom_oAngle9Mom100.root";   
 fileNameWithData = "~/march19AgAg/submit/CBMatrices/Loop_EfficiencyAcceptance_Matrix_SmearedCBMom.root";

 TFile *file = new TFile(fileNameWithData);
 //TFile *file2 = new TFile(fileNameWithDataSm);

//  fileNameWithData2 = "/u/nschild/Niklas/PhD/mar19/carina/Matrices_Ele_embData_ag1230ag_MomThetaPhi_fixedAlpha_098Window_betaMomSigma.root";   
//  TFile *file2 = new TFile(fileNameWithData2);

  //TH1D* Proj_z_ep_niklas=(TH1D*) file2->Get("hacc1D_Ele_z_CCTotal");  
 // TH1D* Proj_z_em_niklas=(TH1D*) fil2->Get("hacc1D_Ele_z_CCTotal");  

 const int multClassNo=4;

  TH1D* Proj_x_em_kine[multClassNo];
  TH1D* Proj_y_em_kine[multClassNo];  
  TH1D* Proj_z_em_kine[multClassNo]; 

  TH1D* Proj_x_em_kine4pi[multClassNo];
  TH1D* Proj_y_em_kine4pi[multClassNo];  
  TH1D* Proj_z_em_kine4pi[multClassNo];  



  TH1D* Proj_x_ep_kine[multClassNo];
  TH1D* Proj_y_ep_kine[multClassNo];  
  TH1D* Proj_z_ep_kine[multClassNo];  

  TH1D* Proj_x_ep_kine4pi[multClassNo];
  TH1D* Proj_y_ep_kine4pi[multClassNo];  
  TH1D* Proj_z_ep_kine4pi[multClassNo];  


    for (int mult = 1; mult <= multClassNo; ++mult) {

    TH3D* hist_MomTheta_kine_em = (TH3D*) file->Get(Form("h_Sm_matrix_kine_MomThetaPhi_em_%i", mult));  
    TH3D* hist_MomTheta_kine_ep = (TH3D*) file->Get(Form("h_Sm_matrix_kine_MomThetaPhi_ep_%i", mult));
    TH3D* hist_MomTheta_kine4pi_em = (TH3D*) file->Get(Form("h_Sm_matrix_kine4pi_MomThetaPhi_em_%i", mult));  
    TH3D* hist_MomTheta_kine4pi_ep = (TH3D*) file->Get(Form("h_Sm_matrix_kine4pi_MomThetaPhi_ep_%i", mult));


  

    // Electrons projections
    Proj_x_em_kine[mult - 1] = hist_MomTheta_kine_em->ProjectionX(Form("Proj_x_em_kine_%i", mult), 0, -1, 0, -1, "e");
    Proj_y_em_kine[mult - 1] = hist_MomTheta_kine_em->ProjectionY(Form("Proj_y_em_kine_%i", mult), 0, -1, 0, -1, "e");
    Proj_z_em_kine[mult - 1] = hist_MomTheta_kine_em->ProjectionZ(Form("Proj_z_em_kine_%i", mult), 0, -1, 0, -1, "e");

    Proj_x_em_kine4pi[mult - 1] = hist_MomTheta_kine4pi_em->ProjectionX(Form("Proj_x_em_kine4pi_%i", mult), 0, -1, 0, -1, "e");
    Proj_y_em_kine4pi[mult - 1] = hist_MomTheta_kine4pi_em->ProjectionY(Form("Proj_y_em_kine4pi_%i", mult), 0, -1, 0, -1, "e");
    Proj_z_em_kine4pi[mult - 1] = hist_MomTheta_kine4pi_em->ProjectionZ(Form("Proj_z_em_kine4pi_%i", mult), 0, -1, 0, -1, "e");

    
    Proj_x_em_kine[mult - 1]->Divide(Proj_x_em_kine4pi[mult - 1]);
    Proj_y_em_kine[mult - 1]->Divide(Proj_y_em_kine4pi[mult - 1]);
    Proj_z_em_kine[mult - 1]->Divide(Proj_z_em_kine4pi[mult - 1]);

    // Positrons projections
    Proj_x_ep_kine[mult - 1] = hist_MomTheta_kine_ep->ProjectionX(Form("Proj_x_ep_kine_%i", mult), 0, -1, 0, -1, "e");
    Proj_y_ep_kine[mult - 1] = hist_MomTheta_kine_ep->ProjectionY(Form("Proj_y_ep_kine_%i", mult), 0, -1, 0, -1, "e");
    Proj_z_ep_kine[mult - 1] = hist_MomTheta_kine_ep->ProjectionZ(Form("Proj_z_ep_kine_%i", mult), 0, -1, 0, -1, "e");

    Proj_x_ep_kine4pi[mult - 1] = hist_MomTheta_kine4pi_ep->ProjectionX(Form("Proj_x_ep_kine4pi_%i", mult), 0, -1, 0, -1, "e");
    Proj_y_ep_kine4pi[mult - 1] = hist_MomTheta_kine4pi_ep->ProjectionY(Form("Proj_y_ep_kine4pi_%i", mult), 0, -1, 0, -1, "e");
    Proj_z_ep_kine4pi[mult - 1] = hist_MomTheta_kine4pi_ep->ProjectionZ(Form("Proj_z_ep_kine4pi_%i", mult), 0, -1, 0, -1, "e");

    Proj_x_ep_kine[mult - 1]->Divide(Proj_x_ep_kine4pi[mult - 1]);
    Proj_y_ep_kine[mult - 1]->Divide(Proj_y_ep_kine4pi[mult - 1]);
    Proj_z_ep_kine[mult - 1]->Divide(Proj_z_ep_kine4pi[mult - 1]);

   //   TCanvas* c1 = new TCanvas(Form("c1_mult_%i", mult), Form("Projections for Electrons and Positrons (Mult: %i)", mult), 1200, 800);
   //      c1->Divide(3, 2);

   //      // Electrons Projections
   //      c1->cd(1);
   //      Proj_x_em_kine[mult - 1]->Draw("COLZ");
   //      Proj_x_em_kine[mult - 1]->SetTitle(Form("Electrons X Projection (Mult: %i)", mult));

   //      c1->cd(2);
   //      Proj_y_em_kine[mult - 1]->Draw("COLZ");
   //      Proj_y_em_kine[mult - 1]->SetTitle(Form("Electrons Y Projection (Mult: %i)", mult));

   //      c1->cd(3);
   //      Proj_z_em_kine[mult - 1]->Draw("COLZ");
   //      Proj_z_ep_niklas        ->Draw("SAME");
   //      Proj_z_ep_niklas        ->SetLineColor(kRed);
   //      Proj_z_em_kine[mult - 1]->SetTitle(Form("Electrons Z Projection (Mult: %i)", mult));

   //      // Positrons Projections
   //      c1->cd(4);
   //      Proj_x_ep_kine[mult - 1]->Draw("COLZ");
   //      Proj_x_ep_kine[mult - 1]->SetTitle(Form("Positrons X Projection (Mult: %i)", mult));

   //      c1->cd(5);
   //      Proj_y_ep_kine[mult - 1]->Draw("COLZ");
   //      Proj_y_ep_kine[mult - 1]->SetTitle(Form("Positrons Y Projection (Mult: %i)", mult));

   //      c1->cd(6);
   //      Proj_z_ep_kine[mult - 1]->Draw("COLZ");
   
      //  Proj_z_ep_kine[mult - 1]->SetTitle(Form("Positrons Z Projection (Mult: %i)", mult));
   // c1->Update(); 

  
 }

 TFile *outputFile = new TFile("~/march19AgAg/submit/EffCorrection/SmearProj.root", "RECREATE");
        outputFile->cd();

      for (int mult = 1; mult <= multClassNo; ++mult) {
       Proj_x_ep_kine[mult - 1]->Write();
       Proj_y_ep_kine[mult - 1]->Write();
       Proj_z_ep_kine[mult - 1]->Write();

        }
}


