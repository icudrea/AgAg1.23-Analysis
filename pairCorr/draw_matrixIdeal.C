

                          
void draw_matrixIdeal()
{
  TString fileNameWithData;
  fileNameWithData  = "/u/icudrea/lustre/hades/user/icudrea/mar19/loop/phd/SingleCorrection/SingleEffCorr_wIdealMom_oAngle9Mom100.root";
  TFile *file = new TFile(fileNameWithData);
  TFile *fileout = new TFile("/u/icudrea/lustre/hades/user/icudrea/mar19/loop/phd/SingleCorrection/EffMatrix_wIdealSmear.root","RECREATE");

    for (int mult =1 ; mult <= 4; ++mult) {



    TH3D *h_matrix_kine_MomThetaPhi_ep = (TH3D*) file ->Get(Form("h_matrix_kine_MomThetaPhi_ep_%i",mult)); 
    TH3D *h_matrix_kine_MomThetaPhi_em = (TH3D*) file ->Get(Form("h_matrix_kine_MomThetaPhi_em_%i",mult)); 
    TH3D *h_matrix_reco_MomThetaPhi_ep = (TH3D*) file ->Get(Form("h_matrix_reco_MomThetaPhi_ep_%i",mult));  
    TH3D *h_matrix_reco_MomThetaPhi_em = (TH3D*) file ->Get(Form("h_matrix_reco_MomThetaPhi_em_%i",mult));

    h_matrix_kine_MomThetaPhi_ep ->RebinY(2);
    h_matrix_kine_MomThetaPhi_em ->RebinY(2); 
    h_matrix_reco_MomThetaPhi_ep ->RebinY(2);  
    h_matrix_reco_MomThetaPhi_em ->RebinY(2);

    h_matrix_kine_MomThetaPhi_ep ->RebinZ(30); 
    h_matrix_kine_MomThetaPhi_em ->RebinZ(30); 
    h_matrix_reco_MomThetaPhi_ep ->RebinZ(30);  
    h_matrix_reco_MomThetaPhi_em ->RebinZ(30);

    
  
    
    Int_t xbins= h_matrix_reco_MomThetaPhi_em->GetNbinsX();
    Int_t ybins= h_matrix_reco_MomThetaPhi_em->GetNbinsY();
    Int_t zbins= h_matrix_reco_MomThetaPhi_em->GetNbinsZ();
    


    for(Int_t x=1; x<=xbins; x++){
      for(Int_t y=1; y<=ybins; y++){
        for(Int_t z=1; z<=zbins; z++){
         Float_t reco_bin_em = h_matrix_reco_MomThetaPhi_em->GetBinContent(x,y,z);
         Float_t reco_bin_ep = h_matrix_reco_MomThetaPhi_ep->GetBinContent(x,y,z);
         Float_t kine_bin_ep = h_matrix_kine_MomThetaPhi_ep->GetBinContent(x,y,z);
         Float_t kine_bin_em = h_matrix_kine_MomThetaPhi_em->GetBinContent(x,y,z);
        
         if(kine_bin_ep>0){
         h_matrix_reco_MomThetaPhi_ep->SetBinContent(x,y,z,reco_bin_ep/kine_bin_ep);}
        else{
        h_matrix_reco_MomThetaPhi_ep->SetBinContent(x,y,z,0);
        }
        if(kine_bin_em>0){
         h_matrix_reco_MomThetaPhi_em->SetBinContent(x,y,z,reco_bin_em/kine_bin_em);}
         else{
         h_matrix_reco_MomThetaPhi_em->SetBinContent(x,y,z,0);
         }
         
        }
      }
    }
   
   

    h_matrix_reco_MomThetaPhi_em->SetName(Form("h_matrix_kine_MomThetaPhi_em_%i",mult));
    h_matrix_reco_MomThetaPhi_ep->SetName(Form("h_matrix_kine_MomThetaPhi_ep_%i",mult));


    fileout->cd();
    h_matrix_reco_MomThetaPhi_em->Write();
    h_matrix_reco_MomThetaPhi_ep->Write();
        


    } 
}




//     TString fileNameWithData;
   
//   //  fileNameWithData  = "/u/icudrea/lustre/hades/user/icudrea/mar19/loop/phd/EfficiencyCorrection_revised/Loop_EffMatrices_wLowMomCB_OldCuts_3sigmaCut.root"; old one
 
//     fileNameWithData  = "/u/icudrea/lustre/hades/user/icudrea/mar19/loop/phd/SingleCorrection/SingleEffCorr_wIdealMom_oAngle9Mom100.root";
//     TFile *file = new TFile(fileNameWithData);
//     TFile *fileout = new TFile("/u/icudrea/lustre/hades/user/icudrea/mar19/loop/phd/SingleCorrection/AccMatrix_wIdealSmear.root","RECREATE");

//     for (int mult =1 ; mult <= 4; ++mult) {

  

//     TH3D *h_matrix_kine_MomThetaPhi_ep    = (TH3D*) file ->Get(Form("h_matrix_kine_MomThetaPhi_ep_%i",mult)); 
//     TH3D *h_matrix_kine_MomThetaPhi_em    = (TH3D*) file ->Get(Form("h_matrix_kine_MomThetaPhi_em_%i",mult)); 

//     TH3D *h_matrix_kine4pi_MomThetaPhi_ep = (TH3D*) file ->Get(Form("h_matrix_kine4pi_MomThetaPhi_ep_%i",mult));  
//     TH3D *h_matrix_kine4pi_MomThetaPhi_em = (TH3D*) file ->Get(Form("h_matrix_kine4pi_MomThetaPhi_em_%i",mult));

//     h_matrix_kine_MomThetaPhi_ep    ->RebinY(2); 
//     h_matrix_kine_MomThetaPhi_em    ->RebinY(2); 

//     h_matrix_kine4pi_MomThetaPhi_ep ->RebinY(2);  
//     h_matrix_kine4pi_MomThetaPhi_em ->RebinY(2);  

//     h_matrix_kine_MomThetaPhi_ep    ->RebinZ(30); 
//     h_matrix_kine_MomThetaPhi_em    ->RebinZ(30); 

//     h_matrix_kine4pi_MomThetaPhi_ep ->RebinZ(30);  
//     h_matrix_kine4pi_MomThetaPhi_em ->RebinZ(30);

    
  
    
//     Int_t xbins= h_matrix_kine4pi_MomThetaPhi_em->GetNbinsX();
//     Int_t ybins= h_matrix_kine4pi_MomThetaPhi_em->GetNbinsY();
//     Int_t zbins= h_matrix_kine4pi_MomThetaPhi_em->GetNbinsZ();
    


//     for(Int_t x=1; x<=xbins; x++){
//       for(Int_t y=1; y<=ybins; y++){
//         for(Int_t z=1; z<=zbins; z++){
//          Float_t kine4pi_bin_em = h_matrix_kine4pi_MomThetaPhi_em->GetBinContent(x,y,z);
//          Float_t kine4pi_bin_ep = h_matrix_kine4pi_MomThetaPhi_ep->GetBinContent(x,y,z);
//          Float_t kine_bin_ep = h_matrix_kine_MomThetaPhi_ep->GetBinContent(x,y,z);
//          Float_t kine_bin_em = h_matrix_kine_MomThetaPhi_em->GetBinContent(x,y,z);
        
//          if(kine_bin_ep>0){
//          h_matrix_kine4pi_MomThetaPhi_ep->SetBinContent(x,y,z,kine_bin_ep/kine4pi_bin_ep);}
//         else{
//         h_matrix_kine4pi_MomThetaPhi_ep->SetBinContent(x,y,z,0);
//         }
//         if(kine_bin_em>0){
//          h_matrix_kine4pi_MomThetaPhi_em->SetBinContent(x,y,z,kine_bin_em/kine4pi_bin_em);}
//          else{
//          h_matrix_kine4pi_MomThetaPhi_em->SetBinContent(x,y,z,0);
//          }
         
//         }
//       }
//     }
   

//     h_matrix_kine4pi_MomThetaPhi_em->SetName(Form("h_matrix_kine_MomThetaPhi_em_%i",mult));
//     h_matrix_kine4pi_MomThetaPhi_ep->SetName(Form("h_matrix_kine_MomThetaPhi_ep_%i",mult));


//     fileout->cd();
//     h_matrix_kine4pi_MomThetaPhi_em->Write();
//     h_matrix_kine4pi_MomThetaPhi_ep->Write();
        


//     } 

// }
