

void rho_invmass_rhoPairCorrection( int centClass = 1){
//TString infileName = "~/lustre/hades/user/icudrea/mar19/CG/pluto_output_inmed_ebeam1.23_agag_1_masscut.root" ) {
 TString infileName ="~/lustre/hades/dstsim/mar19/ag1230ag/pluto/vertex/pi0/pi0";


	// -------------------------------------------------------------------------------------------------
	// load acceptance matrices for e+ and e-
	//TString infileNameAcc = "AccMatrix_wCBSmear.root";
	TString infileNameAcc = "~/march19AgAg/submit/EffCorrection/AccMatrix_wCBSmear_fix.root";
	TFile* infileAcc = new TFile( infileNameAcc, "READ" );

	// x-axis: phi in degree, y-axis: theta in degree, z-axis: momentum in MeV/c^2
	TH3D* h_acc_ep = ( TH3D* ) infileAcc->Get( Form( "h_Sm_matrix_kine_MomThetaPhi_ep_%d", centClass ) );
	TH3D* h_acc_em = ( TH3D* ) infileAcc->Get( Form( "h_Sm_matrix_kine_MomThetaPhi_em_%d", centClass ) );
	h_acc_ep->SetName( "h_acc_ep" );
	h_acc_em->SetName( "h_acc_em" );

	// load efficiency matrices for e+ and e-
	//TString infileNameEff = "EffMatrix_WLowMomCB_Rebin_30.root";
	TString infileNameEff = "~/march19AgAg/submit/EffCorrection/EffMatrix_WLowMomCB_Rebin_30_fix.root";
	TFile* infileEff = new TFile( infileNameEff, "READ" );

	// x-axis: phi in degree, y-axis: theta in degree, z-axis: momentum in MeV/c^2
	TH3D* h_eff_ep = ( TH3D* ) infileEff->Get( Form( "h_Sm_matrix_kine_MomThetaPhi_ep_%d", centClass ) );
	TH3D* h_eff_em = ( TH3D* ) infileEff->Get( Form( "h_Sm_matrix_kine_MomThetaPhi_em_%d", centClass ) );
	h_eff_ep->SetName( "h_eff_ep" );
	h_eff_em->SetName( "h_eff_em" );
	// -------------------------------------------------------------------------------------------------

    //  vector<double> binEgdes ={ 0, 0.01, 0.02, 0.03, 0.04, 0.05, 0.06, 0.07, 0.08,    
    //                                0.09, 0.11, 0.13, 0.15, 0.18, 0.21, 0.24, 0.27, 0.3,
    //                                0.33, 0.36, 0.39, 0.42,0.45,0.48, 0.51, 0.54, 0.57,
    //                                0.6, 0.65, 0.7, 0.75, 0.8, 0.85, 0.9, 0.95, 1,1.05, 1.1, 1.399};
	// -------------------------------------------------------------------------------------------------
    // int nBins = binEdges.size() - 1;
    // double* binArray = &binEdges[0];
   

	// set up single particle histograms
	// TH1F* h_phi_ep   = new TH1F( "h_phi_ep",   "", 360, 0., 360. );
	// TH1F* h_phi_em   = new TH1F( "h_phi_em",   "", 360, 0., 360. );
	// TH1F* h_theta_ep = new TH1F( "h_theta_ep", "", 180, 0., 180. );
	// TH1F* h_theta_em = new TH1F( "h_theta_em", "", 180, 0., 180. );

	// h_phi_em  ->SetLineColor( kRed );
	// h_theta_em->SetLineColor( kRed );

	// set up histograms in 4pi
	 TH1F* h_m   = new TH1F( "h_m",   "", 360, 0., 1.8 );
	// TH2F* h_mpt = new TH2F( "h_mpt", "", 100, 0., 1., 100, 0., 1. );
	// TH2F* h_ypt = new TH2F( "h_ypt", "", 100, -1.5, 3.5, 100, 0., 1. );
	// TH1F* h_m   = new TH1F( "h_m",   "",  nBins, binArray );
	// TH2F* h_mpt = new TH2F( "h_mpt", "",  nBins, binArray );
	// TH2F* h_ypt = new TH2F( "h_ypt", "",  nBins, binArray);
	h_m  ->Sumw2();
	// h_mpt->Sumw2();
	// h_ypt->Sumw2();

	// set up histograms in acc
	//TH1F* h_m_inacc = new TH1F("h_m_inacc", "", nBins, binArray);
	TH1F* h_m_inacc   = new TH1F( "h_m_inacc",   "", 360, 0., 1.8 );
	// TH2F* h_mpt_inacc = new TH2F( "h_mpt_inacc", "", 100, 0., 1., 100, 0., 1. );
	h_m_inacc  ->Sumw2();
	//h_mpt_inacc->Sumw2();

	// set up histograms in acc & eff -> reco
	TH1F* h_m_reco   = new TH1F( "h_m_reco",   "", 360, 0., 1.8 );
	//TH2F* h_mpt_reco = new TH2F( "h_mpt_reco", "", 100, 0., 1., 100, 0., 1. );
	//TH1F* h_m_reco   = new TH1F( "h_m_reco",   "", nBins, binArray);
    //TH2F* h_mpt_reco = new TH2F( "h_mpt_reco", "", 100, 0., 1., 100, 0., 1. );
	h_m_reco  ->Sumw2();
	//h_mpt_reco->Sumw2();

	// set up histograms in acc & eff + opening angle cut -> recoOpang
	
	//TH1F* h_m_recoOpang   = new TH1F( "h_m_recoOpang",   "",nBins, binArray);
	TH1F* h_m_recoOpang   = new TH1F( "h_m_recoOpang",   "", 360, 0., 1.8 );
	TH1F* h_m_acc_opAng   = new TH1F( "h_m_acc_opAng",   "", 360, 0., 1.8 );
    //TH2F* h_mpt_recoOpang = new TH2F( "h_mpt_recoOpang", "", 100, 0., 1., 100, 0., 1. );
	h_m_recoOpang  ->Sumw2();
	//h_mpt_recoOpang->Sumw2();

	// set up histograms in acc & eff + opening angle and momentum cut -> recoCut
	TH1F* h_m_recoCut   = new TH1F( "h_m_recoCut",   "", 360, 0., 1.8 );
	TH1F* h_m_acc       = new TH1F( "h_m_acc",   ""    , 360, 0., 1.8 );    
	//TH2F* h_mpt_recoCut = new TH2F( "h_mpt_recoCut", "", 100, 0., 1., 100, 0., 1. );

	h_m_recoCut  ->Sumw2();
	//h_mpt_recoCut->Sumw2();
	// -------------------------------------------------------------------------------------------------


	// -------------------------------------------------------------------------------------------------
	// input file
	TChain* tree = new TChain( "data" ); // create chain of trees with "data"//for pluto
	//10000

	for( int i=1; i<10000; i++ ) {
		TString name = infileName+Form( "_%d.root", i );

		tree->Add( name );
	}

	//TFile* infile =  new TFile( infileName, "READ" );//forCG
	//TTree* tree = ( TTree* ) infile->Get( "data" ); //forCG

	TClonesArray* evt = new TClonesArray( "PParticle", 100 ); // must create TClonesArray
	tree->SetBranchAddress( "Particles" , &evt );             // PParticle-array address
	PParticle* ep;
	PParticle* em;

	long nEvents  = 100000000;
	              //100000000
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

			float mom_ep = ep->P() * 1000.;
			float mom_em = em->P() * 1000.;
            
	

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

			//float ep_mom = ep->Vect().Mag();
            //float em_mom = em->Vect().Mag();

           //float ep_mom_smeared = Smearing(params_ep,ep_mom);
           // float em_mom_smeared = Smearing(params_em,em_mom);

           // float epE_smeared = TMath::Sqrt(mom_ep*mom_ep+ep->M()*ep->M());
            //float emE_smeared = TMath::Sqrt(mom_em*mom_em+em->M()*em->M());
			float epE_smeared = sqrt( pow(mom_ep / 1000., 2. ) + pow(ep->M(), 2.) );
			float emE_smeared = sqrt( pow(mom_em / 1000., 2. ) + pow(em->M(), 2.) );

  			TLorentzVector  em_smear = ( *( TLorentzVector* ) em );
			TLorentzVector  ep_smear = ( *( TLorentzVector* ) ep );

			ep_smear.SetRho(mom_ep/1000);
            em_smear.SetRho(mom_em/1000);

            ep_smear.SetE(epE_smeared);
            em_smear.SetE(emE_smeared);


			TLorentzVector dilepton_smear =  ep_smear  +  em_smear;

			float opang_smear = ep_smear.Angle( em_smear.Vect() ) * TMath::RadToDeg();
			float mass_smear  = dilepton_smear.M();
			float mom_smear   = dilepton_smear.P();
			

			
			/////////////////////////
			// TLorentzVector dilepton = ( *( TLorentzVector* ) ep ) + ( *( TLorentzVector* ) em );

			// float opang = ep->Angle( em->Vect() ) * TMath::RadToDeg();

			// float mass = dilepton.M();
			// float mom  = dilepton.P();
			// float pt   = dilepton.Pt();
			// float rap  = dilepton.Rapidity();

			h_m  	   ->Fill( mass_smear );
			//h_m_smear  ->Fill( mass_smear );

		
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

	//h_theta_em->Draw();
	//h_theta_ep->Draw( "same" );

	TFile* outfile = new TFile( Form("~/lustre/hades/user/icudrea/mar19/loop/phd/pluto_files_ag123ag/w/histSMEAR_centClass%d_w_100000000evt_pluto.root", centClass ), "RECREATE" );

	h_m  ->Write();
	//h_mpt->Write();
	//h_ypt->Write();

	h_m_inacc  ->Write();
	//h_mpt_inacc->Write();

	h_m_reco  ->Write();
	//h_mpt_reco->Write();

	h_m_recoOpang  ->Write();
	//h_mpt_recoOpang->Write();

	h_m_recoCut  ->Write();
	//h_mpt_recoCut->Write();
	h_m_acc      ->Write();
	h_m_acc_opAng->Write();
}