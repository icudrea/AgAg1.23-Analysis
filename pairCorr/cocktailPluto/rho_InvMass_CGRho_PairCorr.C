

 Double_t DoubleSidedCrystalballFunction(Double_t *x, Double_t *par)
  { 
  Double_t alpha_l = par[0]; 
  Double_t alpha_h = par[1]; 
  Double_t n_l     = par[2]; 
  Double_t n_h     = par[3]; 
  Double_t mean	  = par[4]; 
  Double_t sigma	  = par[5];
  Double_t N	      = par[6];
  Double_t t       = (x[0]-mean)/sigma;
  Double_t result;
  Double_t fact1TLessMinosAlphaL = alpha_l/n_l;
  Double_t fact2TLessMinosAlphaL = (n_l/alpha_l) - alpha_l -t;
  Double_t fact1THihgerAlphaH = alpha_h/n_h;
  Double_t fact2THigherAlphaH = (n_h/alpha_h) - alpha_h +t;

  if (-alpha_l <= t && alpha_h >= t)
    {
      result = exp(-0.5*t*t);
    }
  else if (t < -alpha_l)
    {
      
      result = exp(-0.5*alpha_l*alpha_l)*pow(fact1TLessMinosAlphaL*fact2TLessMinosAlphaL, -n_l);
      
    }
  else if (t > alpha_h)
    {
      result = exp(-0.5*alpha_h*alpha_h)*pow(fact1THihgerAlphaH*fact2THigherAlphaH, -n_h);
      
    }
  return N*result;
  }

/*
Double_t Smearing(TF1* param[], Double_t mom){


	static TF1 *CrystallBall = new TF1("CrystallBall",DoubleSidedCrystalballFunction, 0.4,1.3,7);  



		Double_t p0 = param[0]->Eval(mom);
		Double_t p1 = param[1]->Eval(mom);
		Double_t p2 = param[2]->Eval(mom);
		Double_t p3 = param[3]->Eval(mom);
		Double_t p4 = param[4]->Eval(mom);
		Double_t p5 = param[5]->Eval(mom);
		Double_t p6 = param[6]->Eval(mom);


		CrystallBall->SetParameters(p0, p1, p2, p3, p4, p5, p6);
				
									
		Double_t randomCB = CrystallBall->GetRandom();
		return  mom*randomCB ;

}
*/

double Smearing( TH2D* hist, double mom ) {
	int bin = hist->GetXaxis()->FindBin( mom );
	if( bin > hist->GetNbinsX() ) bin = hist->GetNbinsX();
	TH1D* h = ( TH1D* ) hist->ProjectionY( "h", bin, bin );

	double randomCB = h->GetRandom();
	return  mom * randomCB;
}

void rho_InvMass_CGRho_PairCorr( int centClass = 4){
   // TString infileName ="~/lustre/hades/user/fseck/pluto_output_inmed_ebeam1.23_agag";
	  //TString infileName ="~/lustre/hades/user/fseck/pluto_output_inmed_ebeam1.23_agag_1_masscut.root";
      TString infileName ="~/lustre/hades/user/fseck/pluto_output_inmed_ebeam1.23_agag_masscut";


    TFile *f_em    = TFile::Open("/u/icudrea/march19AgAg/loopDST/fits_all_em_NEW.root","READ");
    TFile *f_ep    = TFile::Open("/u/icudrea/march19AgAg/loopDST/fits_ALL_ep.root","READ");
    //################################################################################

	TF1* Param_0_ep      = ( TF1* ) f_ep  ->Get( "fit_alpha_low" );
	TF1* Param_1_ep      = ( TF1* ) f_ep  ->Get( "fit_alpha_high" );
	TF1* Param_2_ep      = ( TF1* ) f_ep  ->Get( "fit_n_low" );
	TF1* Param_3_ep      = ( TF1* ) f_ep  ->Get( "fit_n_high" );
	TF1* Param_4_ep      = ( TF1* ) f_ep  ->Get( "fit_mean" );
	TF1* Param_5_ep      = ( TF1* ) f_ep  ->Get( "fit_sigma" );
	TF1* Param_6_ep      = ( TF1* ) f_ep  ->Get( "fit_norm" );

	TF1* params_ep[] = {Param_0_ep, Param_1_ep, Param_2_ep, Param_3_ep,
	                    Param_4_ep, Param_5_ep, Param_6_ep};

	TF1* Param_1_em      = ( TF1* ) f_em  ->Get( "pol2_alpha_high" );
	TF1* Param_0_em      = ( TF1* ) f_em  ->Get( "pol1_alpha_low" );
	TF1* Param_2_em      = ( TF1* ) f_em  ->Get( "pol2_n_low" );
	TF1* Param_3_em      = ( TF1* ) f_em  ->Get( "pol2_n_high" );
	TF1* Param_5_em      = ( TF1* ) f_em  ->Get( "pol1_sigma" );
	TF1* Param_4_em      = ( TF1* ) f_em  ->Get( "pol1_mean" );
	TF1* Param_6_em      = ( TF1* ) f_em  ->Get( "pol2" );

   TF1* params_em[] = {Param_0_em, Param_1_em, Param_2_em, Param_3_em,
	                    Param_4_em, Param_5_em, Param_6_em};



	TH2D* h_crystalball_ep = new TH2D( "h_crystalball_ep", "", 400, 0., 2000., 200, 0., 2 );
	TH2D* h_crystalball_em = new TH2D( "h_crystalball_em", "", 400, 0., 2000., 200, 0., 2 );

	// -------------------------------------------------------------------------------------------------

	for( int i=0; i<h_crystalball_ep->GetNbinsX(); i++ ) {
		float mom = h_crystalball_ep->GetXaxis()->GetBinCenter( i+1 );

		TF1* crystallBall_ep = new TF1("CrystallBall_ep", DoubleSidedCrystalballFunction, 0., 2, 7 ); 
		TF1* crystallBall_em = new TF1("CrystallBall_em", DoubleSidedCrystalballFunction, 0., 2, 7 ); 

		double p0 = params_ep[ 0 ]->Eval( mom );
		double p1 = params_ep[ 1 ]->Eval( mom );
		double p2 = params_ep[ 2 ]->Eval( mom );
		double p3 = params_ep[ 3 ]->Eval( mom );
		double p4 = params_ep[ 4 ]->Eval( mom );
		double p5 = params_ep[ 5 ]->Eval( mom );
		double p6 = params_ep[ 6 ]->Eval( mom );

		crystallBall_ep->SetParameters( p0, p1, p2, p3, p4, p5, p6 );

		p0 = params_em[ 0 ]->Eval( mom );
		p1 = params_em[ 1 ]->Eval( mom );
		p2 = params_em[ 2 ]->Eval( mom );
		p3 = params_em[ 3 ]->Eval( mom );
		p4 = params_em[ 4 ]->Eval( mom );
		p5 = params_em[ 5 ]->Eval( mom );
		p6 = params_em[ 6 ]->Eval( mom );

		crystallBall_em->SetParameters( p0, p1, p2, p3, p4, p5, p6 );


		for( int j=0; j<h_crystalball_ep->GetNbinsY(); j++ ) {
			float val = h_crystalball_ep->GetYaxis()->GetBinCenter( j+1 );

			h_crystalball_ep->SetBinContent( i+1, j+1, crystallBall_ep->Eval( val ) );
			h_crystalball_em->SetBinContent( i+1, j+1, crystallBall_em->Eval( val ) );
		}
	}

    
	// -------------------------------------------------------------------------------------------------
	// load acceptance matrices for e+ and e-
	//TString infileNameAcc = "AccMatrix_wCBSmear.root";
	TString infileNameAcc = "/u/icudrea/march19AgAg/submit/EffCorrection/AccMatrices_wCBSmear_fix.root";
	TFile* infileAcc = new TFile( infileNameAcc, "READ" );

	// x-axis: phi in degree, y-axis: theta in degree, z-axis: momentum in MeV/c^2
	TH3D* h_acc_ep = ( TH3D* ) infileAcc->Get( Form( "h_Sm_matrix_kine_MomThetaPhi_ep_%d", centClass ) );
	TH3D* h_acc_em = ( TH3D* ) infileAcc->Get( Form( "h_Sm_matrix_kine_MomThetaPhi_em_%d", centClass ) );
	h_acc_ep->SetName( "h_acc_ep" );
	h_acc_em->SetName( "h_acc_em" );

	// load efficiency matrices for e+ and e-
	//TString infileNameEff = "EffMatrix_WLowMomCB_Rebin_30.root";
	TString infileNameEff = "/u/icudrea/march19AgAg/submit/EffCorrection/EffMatrices_wCBSmear_fix.root";
	TFile* infileEff = new TFile( infileNameEff, "READ" );

	// x-axis: phi in degree, y-axis: theta in degree, z-axis: momentum in MeV/c^2
	TH3D* h_eff_ep = ( TH3D* ) infileEff->Get( Form( "h_Sm_matrix_kine_MomThetaPhi_ep_%d", centClass ) );
	TH3D* h_eff_em = ( TH3D* ) infileEff->Get( Form( "h_Sm_matrix_kine_MomThetaPhi_em_%d", centClass ) );
	h_eff_ep->SetName( "h_eff_ep" );
	h_eff_em->SetName( "h_eff_em" );
	// -------------------------------------------------------------------------------------------------

	// set up histograms in 4pi
	 TH1F* h_m   = new TH1F( "h_m",   "", 360, 0., 1.8 );
	 h_m  ->Sumw2();


	// set up histograms in acc
	TH1F* h_m_inacc   = new TH1F( "h_m_inacc",   "", 360, 0., 1.8 );
	h_m_inacc  ->Sumw2();


	// set up histograms in acc & eff -> reco
	TH1F* h_m_reco   = new TH1F( "h_m_reco",   "", 360, 0., 1.8 );
	h_m_reco  ->Sumw2();
	

	// set up histograms in acc & eff + opening angle cut -> recoOpang
	
	//TH1F* h_m_recoOpang   = new TH1F( "h_m_recoOpang",   "",nBins, binArray);
	TH1F* h_m_recoOpang   = new TH1F( "h_m_recoOpang",   "", 360, 0., 1.8 );
	TH1F* h_m_acc_opAng   = new TH1F( "h_m_acc_opAng",   "", 360, 0., 1.8 );
   
	h_m_recoOpang  ->Sumw2();
	h_m_acc_opAng  ->Sumw2();

	// set up histograms in acc & eff + opening angle and momentum cut -> recoCut
	TH1F* h_m_recoCut   = new TH1F( "h_m_recoCut",   "", 360, 0., 1.8 );
	TH1F* h_m_acc       = new TH1F( "h_m_acc",   ""    , 360, 0., 1.8 );    
	
	h_m_recoCut  ->Sumw2();
	h_m_acc      ->Sumw2();
	// -------------------------------------------------------------------------------------------------


	// -------------------------------------------------------------------------------------------------
	// input file
	TChain* tree = new TChain( "data" ); // create chain of trees with "data"//for pluto
	//10000

	int nFiles = 1;

	for( int i=1; i<=nFiles; i++ ) {
		TString name = infileName+Form( "_%d.root", i );

		tree->Add( name );
	}

	

	TClonesArray* evt = new TClonesArray( "PParticle", 100 ); // must create TClonesArray
	tree->SetBranchAddress( "Particles" , &evt );             // PParticle-array address
	PParticle* ep;
	PParticle* em;

	long nEvents  = 1000000000;
	long nentries = tree->GetEntries();        // get number of entries
	if( nentries > nEvents ) nentries = nEvents;

	for( long i=0; i<nentries; i++ ) {         // enter event loop
			if( i % 100000 == 0 ) cout << i << endl;

			ep = nullptr;
			em = nullptr;

			tree->GetEntry( i ); // current event

		for( int j=0; j<evt->GetEntriesFast(); j++ ) {
			PParticle *current =( PParticle* ) evt->At( j );  // retrieve the j-th particle of the event
			if( current->Is( "e+" ) ) ep = current;
			if( current->Is( "e-" ) ) em = current;
		}

		if( ep && em ) {
			//particles found
			float phi_ep = ep->Phi() * TMath::RadToDeg();
			float phi_em = em->Phi() * TMath::RadToDeg();

			if( phi_ep < 0. ) phi_ep += 360.;
			if( phi_em < 0. ) phi_em += 360.;

			float theta_ep = ep->Theta() * TMath::RadToDeg();
			float theta_em = em->Theta() * TMath::RadToDeg();


			float mom_ep = Smearing(h_crystalball_ep, ep->P() * 1000. );
			float mom_em = Smearing(h_crystalball_em, em->P() * 1000. );

			int bin_phi_ep   = h_acc_ep->GetXaxis()->FindBin( phi_ep   );
			int bin_theta_ep = h_acc_ep->GetYaxis()->FindBin( theta_ep );
			int bin_mom_ep   = h_acc_ep->GetZaxis()->FindBin( mom_ep   );
			if( bin_mom_ep > h_acc_ep->GetNbinsZ() ) bin_mom_ep = h_acc_ep->GetNbinsZ();

			float acc_ep = h_acc_ep->GetBinContent( bin_phi_ep, bin_theta_ep, bin_mom_ep );

			bin_phi_ep   = h_eff_ep->GetXaxis()->FindBin( phi_ep   );
			bin_theta_ep = h_eff_ep->GetYaxis()->FindBin( theta_ep );
			bin_mom_ep   = h_eff_ep->GetZaxis()->FindBin( mom_ep   );
			if( bin_mom_ep > h_eff_ep->GetNbinsZ() ) bin_mom_ep = h_eff_ep->GetNbinsZ();

			float eff_ep = h_eff_ep->GetBinContent( bin_phi_ep, bin_theta_ep, bin_mom_ep );

			int bin_phi_em   = h_acc_em->GetXaxis()->FindBin( phi_em   );
			int bin_theta_em = h_acc_em->GetYaxis()->FindBin( theta_em );
			int bin_mom_em   = h_acc_em->GetZaxis()->FindBin( mom_em   );
			if( bin_mom_em > h_acc_em->GetNbinsZ() ) bin_mom_em = h_acc_em->GetNbinsZ();

			float acc_em = h_acc_em->GetBinContent( bin_phi_em, bin_theta_em, bin_mom_em );

			bin_phi_em   = h_eff_em->GetXaxis()->FindBin( phi_em   );
			bin_theta_em = h_eff_em->GetYaxis()->FindBin( theta_em );
			bin_mom_em   = h_eff_em->GetZaxis()->FindBin( mom_em   );
			if( bin_mom_em > h_eff_em->GetNbinsZ() ) bin_mom_em = h_eff_em->GetNbinsZ();

			float eff_em = h_eff_em->GetBinContent( bin_phi_em, bin_theta_em, bin_mom_em );

			float pair_weight_acc = acc_ep * acc_em;
			float pair_weight_eff = eff_ep * eff_em;

  			TLorentzVector  em_smear = ( *( TLorentzVector* ) em );
			TLorentzVector  ep_smear = ( *( TLorentzVector* ) ep );

			ep_smear.SetRho( mom_ep / 1000. );
     		 em_smear.SetRho( mom_em / 1000. );

            float epE_smeared = sqrt( pow(mom_ep / 1000., 2. ) + pow(ep->M(), 2.) );
            float emE_smeared = sqrt( pow(mom_em / 1000., 2. ) + pow(em->M(), 2.) );

			 ep_smear.SetE( epE_smeared );
     		 em_smear.SetE( emE_smeared );

			TLorentzVector dilepton_smear =  ep_smear  +  em_smear;

			float opang_smear = ep_smear.Angle( em_smear.Vect() ) * TMath::RadToDeg();
			float mass_smear  = dilepton_smear.M();
			float mom_smear   = dilepton_smear.P();
			

			
			/////////////////////////


			h_m  	   ->Fill( mass_smear );
			h_m_inacc  ->Fill( mass_smear, pair_weight_acc );
			h_m_reco   ->Fill( mass_smear,  pair_weight_acc * pair_weight_eff );//can be reconstructed 
			

			if( opang_smear > 9. ) {
				h_m_recoOpang  ->Fill(mass_smear,pair_weight_acc * pair_weight_eff );
				h_m_acc_opAng  ->Fill(mass_smear,pair_weight_acc);
			}

			if( opang_smear > 9. && mom_ep > 100. && mom_em > 100. ) {
				h_m_recoCut  ->Fill(mass_smear,pair_weight_acc * pair_weight_eff );
				h_m_acc      ->Fill(mass_smear,pair_weight_acc);

			

			}
		}
		
	}
	cout << "loop done" << endl;

	// -------------------------------------------------------------------------------------------------

	

	TFile* outfile = new TFile( Form("~/lustre/hades/user/icudrea/mar19/loop/phd/pluto_files_ag123ag/rho/histSmearMomRho_centClass%d_w_1000000evt_pluto.root", centClass ), "RECREATE" );
	
	h_m            ->Write();
	h_m_inacc      ->Write();
	h_m_reco       ->Write();
	h_m_recoOpang  ->Write();


	h_m_recoCut  ->Write();
	h_m_acc      ->Write();
	h_m_acc_opAng->Write();
}