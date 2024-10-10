#include "hades.h"
#include "hcategory.h"
#include "hcategorymanager.h"
#include "hloop.h"
#include "htime.h"

#include "henergylosscorrpar.h"
#include "hgeantkine.h"
#include "hparticleanglecor.h"
#include "hparticlebooker.h"
#include "hparticlecand.h"
#include "hparticlecandsim.h"
#include "hparticledef.h"
#include "hparticleevtchara.h"
#include "hparticleevtinfo.h"
#include "hparticlegeantdecay.h"
#include "hparticlegeantevent.h"
#include "hparticlegeantpair.h"
#include "hparticletool.h"
#include "hparticletracksorter.h"
#include "hphysicsconstants.h"
#include "hrichcal.h"
#include "hrichhit.h"
#include "richdef.h"

#include "TFile.h"
#include "TH1F.h"
#include "TH2F.h"
#include "TLorentzVector.h"
#include "TMath.h"
#include "TROOT.h"
#include "TString.h"
#include "TSystem.h"
#include "Useful_Stuff.h"
#include "hhistmap.h"
#include "TF1.h"
#include <iostream>
#include <vector>


using namespace std;
HParticleEvtChara* evtChara;

static const Int_t MAX_MULT = 4;


static Bool_t selectLeptonsBetaLoose( HParticleCand* pcand ) {
//  selection function for lepton candidates.

	Bool_t selectEpEm = kFALSE;

	if( pcand->isFlagAND( 5, Particle::kIsAcceptedHitRICH,
							 Particle::kIsAcceptedHitInnerMDC,
							 Particle::kIsAcceptedHitOuterMDC,
							 Particle::kIsAcceptedHitMETA,
							 Particle::kIsAcceptedRK ) &&
		pcand->getInnerSegmentChi2() > 0 && pcand->getOuterSegmentChi2() > 0 &&
		pcand->getMetaMatchQuality() < 4 && pcand->getBeta() > 0.9 &&
		HParticleTool::isGoodMetaCell(pcand, 4, kTRUE) &&
		pcand->getChi2() < 1000. && pcand->getMomentum() < 2000. &&
		!pcand->isAtAnyMdcEdge() ) {
		selectEpEm = kTRUE;
	}

	return selectEpEm;
}

void doTrackCorr( HParticleAngleCor& trackcor, HCategory* candCat ) {
	Int_t size = candCat->getEntries();
	for( Int_t j = 0; j < size; j++ ) {
		HParticleCand* cand;
		cand = HCategoryManager::getObject( cand, candCat, j );
		trackcor.recalcSetEmission( cand );  // changes values inside candidate
		// trackcor.realignRichRing( cand ); //
	}
}


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

Int_t Fill_Matrices_CBFunction(
	TString infileList ="/lustre/hades/dst/mar19/gen5/ag123ag/2500A/embedding/vertexCluster/white/e*/089/dst/root/be*.hld_embedding_dst_mar19.root",
	TString outfile    = "test_martini.root", 
	Int_t nEvents      = -1 ) {

	Bool_t isSimulation = kTRUE; // sim or real data

	//---create loop obejct and hades
	HLoop loop( kTRUE );
	//-------------------------------------------------

	

    TString paraFile = "/lustre/hades/user/bkardan/param/centrality_epcorr_mar19_ag123ag_2500A_glauber_gen4_2020_10_pass3.root";
	//TString paraFile = "/lustre/hades/user/bkardan/param/centrality_epcorr_mar19_ag158ag_3200A_glauber_gen5_pass3_2021_08.root";
	//-------------------------------------------------
	//---list of all files with working sectors
	if (!isSimulation)
	loop.readSectorFileList("/lustre/hades/dst/mar19/gen5/sector_selection/Mar19AgAg1230_Gen5.list", kFALSE, kFALSE );
	//-------------------------------------------------
	HParticleAngleCor trackcor;
	trackcor.setDefaults( "mar19" );
	trackcor.setShield( kTRUE );
	trackcor.setUseEventXYVertex();
	trackcor.setMeanZTarget( -34.8 );
	trackcor.setVertexType( Particle::kVertexCluster );

	//-------------------------------------------------
	//---reading input files and decalring containers
	Bool_t ret = kFALSE;
	if( infileList.Contains( "," ) ) {
		ret = loop.addMultFiles( infileList ); // file1,file2,file3
	} else {
		ret = loop.addFiles( infileList ); // myroot*.root
	}
	if( ret == 0 ) {
		cout << "READBACK: ERROR : cannot find inputfiles : " << infileList.Data() << endl;
		return 1;
	}

	if( !loop.setInput( "" ) ) { // all input categories
	// if( !loop.setInput( "-*, +HParticleCand, +HParticleCandSim, +HGeantKine, +HParticleEvtInfo, +HRichHit, +HRichCal, +HGeantMdc" ) ) {  // select some Categories
		cout << "READBACK: ERROR : cannot read input !" << endl;
		exit(1);
	} //---read all categories
	loop.printCategories();
	loop.printChain();
	//-------------------------------------------------
 
    TFile *f_em    = TFile::Open("fits_all_em_NEW.root","READ");
    TFile *f_ep    = TFile::Open("fits_ALL_ep.root","READ");
    //################################################################################

	TF1* Param_0_em      = ( TF1* ) f_em  ->Get( "pol1_alpha_low" );
	TF1* Param_1_em      = ( TF1* ) f_em  ->Get( "pol2_alpha_high" );
	TF1* Param_2_em      = ( TF1* ) f_em  ->Get( "pol2_n_low" );
	TF1* Param_3_em      = ( TF1* ) f_em  ->Get( "pol2_n_high" );
	TF1* Param_4_em      = ( TF1* ) f_em  ->Get( "pol1_mean" );
	TF1* Param_5_em      = ( TF1* ) f_em  ->Get( "pol1_sigma" );
	TF1* Param_6_em      = ( TF1* ) f_em  ->Get( "pol2" );

	TF1* Param_0_ep      = ( TF1* ) f_ep  ->Get( "fit_alpha_low" );
	TF1* Param_1_ep      = ( TF1* ) f_ep  ->Get( "fit_alpha_high" );
	TF1* Param_2_ep      = ( TF1* ) f_ep  ->Get( "fit_n_low" );
	TF1* Param_3_ep      = ( TF1* ) f_ep  ->Get( "fit_n_high" );
	TF1* Param_4_ep      = ( TF1* ) f_ep  ->Get( "fit_mean" );
	TF1* Param_5_ep      = ( TF1* ) f_ep  ->Get( "fit_sigma" );
	TF1* Param_6_ep      = ( TF1* ) f_ep  ->Get( "fit_norm" );

	//----------------
	TFile* S_dPhi      = TFile::Open( "dPhi_sim_noLowMomCut_MMQ4.root",   "READ" );
	TFile* S_dTheta    = TFile::Open( "dTheta_sim_noLowMomCut_MMQ4.root", "READ" );
	TFile* M_dPhi      = TFile::Open( "dPhi_sim_noLowMomCut_MMQ4.root",   "READ" );
	TFile* M_dTheta    = TFile::Open( "dTheta_sim_noLowMomCut_MMQ4.root", "READ" );
	TFile* S_beta_sys0 = TFile::Open( "sigma_beta_sys0_sim.root", "READ" );
	TFile* S_beta_sys1 = TFile::Open( "sigma_beta_sys1_sim.root", "READ" );

	//----------------------------------------------------------------------------------
	TH1F* sigma_phi   = ( TH1F* ) S_dPhi  ->Get( "SigmaHist1" );
	TH1F* sigma_theta = ( TH1F* ) S_dTheta->Get( "SigmaHist1" );

	TH1F* mean_phi   = ( TH1F* ) M_dPhi  ->Get( "meanHist1" );
	TH1F* mean_theta = ( TH1F* ) M_dTheta->Get( "meanHist1" );

	TH1F* sigma_beta_sys0 = ( TH1F* ) S_beta_sys0->Get( "SigmaHist1" );
	TH1F* sigma_beta_sys1 = ( TH1F* ) S_beta_sys1->Get( "SigmaHist1" );


	//---add your histograms here
	TFile* out = new TFile( outfile.Data(), "RECREATE" );
	out->cd();

	TH1F* hCounter = new TH1F( "hCounter", " ", 20, 0, 20 );

	TH1::SetDefaultSumw2();


    TH3D *h_matrix_kine_MomThetaPhi_ep[MAX_MULT]; 
    TH3D *h_matrix_kine_MomThetaPhi_em[MAX_MULT]; 
    TH3D *h_matrix_reco_MomThetaPhi_ep[MAX_MULT];  
    TH3D *h_matrix_reco_MomThetaPhi_em[MAX_MULT]; 

	// TH3D *h_Sm_matrix_kine_MomThetaPhi_ep[MAX_MULT]; 
    // TH3D *h_Sm_matrix_kine_MomThetaPhi_em[MAX_MULT]; 
    // TH3D *h_Sm_matrix_reco_MomThetaPhi_ep[MAX_MULT];  
    // TH3D *h_Sm_matrix_reco_MomThetaPhi_em[MAX_MULT]; 

    // TH3D *h_Sm_matrix_kine4pi_MomThetaPhi_ep[MAX_MULT];
    // TH3D *h_Sm_matrix_kine4pi_MomThetaPhi_em[MAX_MULT];

    TH3D *h_matrix_kine4pi_MomThetaPhi_ep[MAX_MULT];
    TH3D *h_matrix_kine4pi_MomThetaPhi_em[MAX_MULT];
	



  for (Int_t i = 1; i<=MAX_MULT; ++i) {

	// h_Sm_matrix_kine4pi_MomThetaPhi_ep[i-1] = new TH3D(Form("h_Sm_matrix_kine4pi_MomThetaPhi_ep_%i",i), Form("h_Sm_matrix_kine4pi_MomThetaPhi_ep_%i",i),90,0,360,90,0,90,1000,0,2000);
    // h_Sm_matrix_kine4pi_MomThetaPhi_em[i-1] = new TH3D(Form("h_Sm_matrix_kine4pi_MomThetaPhi_em_%i",i), Form("h_Sm_matrix_kine4pi_MomThetaPhi_em_%i",i),90,0,360,90,0,90,1000,0,2000);

    h_matrix_kine4pi_MomThetaPhi_ep[i-1] = new TH3D(Form("h_matrix_kine4pi_MomThetaPhi_ep_%i",i), Form("h_matrix_kine4pi_MomThetaPhi_ep_%i",i),90,0,360,90,0,90,1000,0,2000);
    h_matrix_kine4pi_MomThetaPhi_em[i-1] = new TH3D(Form("h_matrix_kine4pi_MomThetaPhi_em_%i",i), Form("h_matrix_kine4pi_MomThetaPhi_em_%i",i),90,0,360,90,0,90,1000,0,2000);

    // h_Sm_matrix_kine_MomThetaPhi_ep[i-1] = new TH3D(Form("h_Sm_matrix_kine_MomThetaPhi_ep_%i",i), Form("h_Sm_matrix_kine_MomThetaPhi_ep_%i",i),90,0,360,90,0,90,1000,0,2000);
    // h_Sm_matrix_kine_MomThetaPhi_em[i-1] = new TH3D(Form("h_Sm_matrix_kine_MomThetaPhi_em_%i",i), Form("h_Sm_matrix_kine_MomThetaPhi_em_%i",i),90,0,360,90,0,90,1000,0,2000);
    // h_Sm_matrix_reco_MomThetaPhi_ep[i-1] = new TH3D(Form("h_Sm_matrix_reco_MomThetaPhi_ep_%i",i), Form("h_Sm_matrix_reco_MomThetaPhi_ep_%i",i),90,0,360,90,0,90,1000,0,2000);
    // h_Sm_matrix_reco_MomThetaPhi_em[i-1] = new TH3D(Form("h_Sm_matrix_reco_MomThetaPhi_em_%i",i), Form("h_Sm_matrix_reco_MomThetaPhi_em_%i",i),90,0,360,90,0,90,1000,0,2000);
 	
    h_matrix_kine_MomThetaPhi_ep[i-1] = new TH3D(Form("h_matrix_kine_MomThetaPhi_ep_%i",i), Form("h_matrix_kine_MomThetaPhi_ep_%i",i),90,0,360,90,0,90,1000,0,2000);
    h_matrix_kine_MomThetaPhi_em[i-1] = new TH3D(Form("h_matrix_kine_MomThetaPhi_em_%i",i), Form("h_matrix_kine_MomThetaPhi_em_%i",i),90,0,360,90,0,90,1000,0,2000);
    h_matrix_reco_MomThetaPhi_ep[i-1] = new TH3D(Form("h_matrix_reco_MomThetaPhi_ep_%i",i), Form("h_matrix_reco_MomThetaPhi_ep_%i",i),90,0,360,90,0,90,1000,0,2000);
    h_matrix_reco_MomThetaPhi_em[i-1] = new TH3D(Form("h_matrix_reco_MomThetaPhi_em_%i",i), Form("h_matrix_reco_MomThetaPhi_em_%i",i),90,0,360,90,0,90,1000,0,2000);
 	
	h_matrix_reco_MomThetaPhi_em[i-1]->GetXaxis()->SetTitle("#phi[deg]");
	h_matrix_reco_MomThetaPhi_em[i-1]->GetYaxis()->SetTitle("#theta[deg]");
    h_matrix_reco_MomThetaPhi_em[i-1]->GetZaxis()->SetTitle("p [MeV/c]");
  }




	//---parameters
	HEnergyLossCorrPar dEdxCorr;
	dEdxCorr.setDefaultPar("mar19"); //
	//-------------------------------------------------

	HParticleGeantEvent geantevent;
	//----------------------------------------------------------------------------------------
	//---input data
	HCategory *candCat    =(HCategory *)HCategoryManager::getCategory(catParticleCand);
	HCategory *evtInfoCat =(HCategory *)HCategoryManager::getCategory(catParticleEvtInfo);
	HCategory *kineCat    =(HCategory *)HCategoryManager::getCategory(catGeantKine);
	HCategory *richCalCat =(HCategory *)HCategoryManager::getCategory(catRichCal);
	HCategory *richHitCat =(HCategory *)HCategoryManager::getCategory(catRichHit);

	//----------------------------------------------------------------------------------------

	//..sorter
	HParticleTrackSorter sorter;

	sorter.init(); // get catgegory pointers etc...

	//---------------------------------------Event Chara-------------------------------------------------------

	evtChara = new HParticleEvtChara;
	cout << "HParticleEvtChara: reading: " << paraFile << endl;
	if( !evtChara->setParameterFile( paraFile ) ) {
		cout << "HParticleEvtChara: file not found!!! " << endl;
	}
	if( !evtChara->init() ) {
		cout << "HParticleEvtChara not init!!! " << endl;
	}
	evtChara->printCentralityClass( HParticleEvtChara::kTOFRPC, HParticleEvtChara::k5  );
	evtChara->printCentralityClass( HParticleEvtChara::kTOFRPC, HParticleEvtChara::k10 );

	//----------------------------------------------------------------------------------------------------------
	//---event loop starts here
	Int_t entries = loop.getEntries();
	if( nEvents < entries && nEvents >= 0 ) entries = nEvents;
	
	TString filename;

	for( Int_t i = 0; i < entries; i++ ) {
		Int_t nbytes = loop.nextEvent(i); // get next event. categories will be cleared before
		if( nbytes <= 0 ) {
			cout << nbytes << endl;
			break;
		}                    // last event reached
		if( i % 10000 == 0 ) cout << "event " << i << endl;
		
		hCounter->Fill( 0 );

		if( loop.isNewFile( filename ) ) { // if the actual filename is needed
			if( !isSimulation ) filename = HTime::stripFileName( filename, kTRUE, kFALSE ); // get hld file name
		}

		//-------------------------------------------------
		//---summary event info object
		HParticleEvtInfo* evtInfo = 0;
		evtInfo = HCategoryManager::getObject( evtInfo, evtInfoCat, 0 );

		HVertex PrimVertexReco = ( ( HEventHeader* ) ( gHades->getCurrentEvent()->getHeader() ) )->getVertexReco();
		
		Float_t vz = PrimVertexReco.getZ();
		
		 if (vz < -70) continue;

		hCounter->Fill( 1 );

		if( evtInfo &&
			!evtInfo->isGoodEvent(  Particle::kGoodTRIGGER | // standard event selection apr12
									Particle::kGoodVertexClust | Particle::kGoodVertexCand |
									Particle::kGoodSTART |
									// Particle::kNoPileUpSTART|
									Particle::kNoSTART | Particle::kNoVETO | Particle::kGoodSTARTVETO |
									Particle::kGoodSTARTMETA) )
			continue;

    	hCounter->Fill( 2 );

		Int_t multClassNo10 = evtChara->getCentralityClass( HParticleEvtChara::kTOFRPC, HParticleEvtChara::k10 );
		Int_t multClassNo   = multClassNo10;

		if( multClassNo < 1 || multClassNo > MAX_MULT  ) continue;
 
		

		//------------------ clean sorter------------------------------------------------------------------
		sorter.cleanUp();
		sorter.resetFlags( kTRUE, kTRUE, kTRUE, kTRUE ); // reset all flags for flags (0-28),reject,used,lepton
		sorter.fill( selectLeptonsBetaLoose ); // fill only good leptons
		sorter.selectBest( Particle::kIsBestRKSorter, Particle::kIsLeptonSorter );
		
		//---------------------------------------------------------------------------------------------------

		if( candCat ) {
			Int_t size = candCat->getEntries();
			Bool_t conversionFlag[ size ];

			doTrackCorr( trackcor, candCat );

			HParticleCand *cand;
			HParticleCandSim *sim;

		

			for( Int_t j = 0; j < size; j++ ) {

				conversionFlag[j] = kFALSE;

				cand = HCategoryManager::getObject( cand, candCat, j );
				sim = dynamic_cast< HParticleCandSim* > ( cand );

				HGeantKine* kine = HCategoryManager::getObject( kine, kineCat, sim->getGeantTrack() - 1 );
				if( kine == NULL ) continue;

				Int_t cal_counter;
				Double_t beta      = sim->getBeta();
				Int_t   system     = sim->getSystemUsed();
				Float_t RingRad    = sim->getRingRadius();
				Short_t charge     = sim->getCharge();
				Float_t Momentum   = sim->getMomentum();
				Float_t DeltaTheta = sim->getDeltaTheta();
				Float_t DeltaPhi   = sim->getDeltaPhi();
				Float_t momPID     = charge * Momentum;

			
				sim->calc4vectorProperties(HPhysicsConstants::mass("e+"));

				if( sim->getGeantParentTrackNum() != 0 ) continue;

		

				//.............. kine momIdeal........................
				Float_t thetaIdeal, phiIdeal;

				kine->getPhiThetaDeg( thetaIdeal, phiIdeal );

				Float_t momReco   = sim->getMomentum();
		
				Float_t momIdeal  = kine->getTotalMomentum();

				if( !kine->isInAcceptanceBit( 4, 4, 4, 4, 0, 0 ) ) continue;
				if( !kine->isPrimary() ) continue;

				//............. kine over.........................
				if( !sim->isFlagBit( Particle::kIsLepton ) ) continue;
				if( isConversion( cand, richHitCat, richCalCat, cal_counter ) ) conversionFlag[ j ] = kTRUE;
                if( isOARing(cand, richHitCat)) continue;
				if( conversionFlag[ j ] ) continue;

				// --------------lepton identification----------------------------------------------------
			

				if( system == 1 && beta < 1 - 3 * sigma_beta_sys1->Interpolate( momPID ) ) continue;


				if( system == 0 && beta < 1 - 3 * sigma_beta_sys0->Interpolate( momPID ) ) continue;

				
				if( RingRad < 19 ) continue;


				if( TMath::Abs( DeltaPhi - mean_phi->Interpolate( momPID ) ) > 3 * sigma_phi->Interpolate( momPID ) ) continue;

				if( TMath::Abs(DeltaTheta - mean_theta->Interpolate(momPID) ) > 3 * sigma_theta->Interpolate( momPID) ) continue;

			
			

				if( sim->getGeantPID() == 3 ) {
					
          		
				    h_matrix_reco_MomThetaPhi_em[multClassNo-1]   ->Fill( phiIdeal,thetaIdeal,momIdeal); 
					//h_Sm_matrix_reco_MomThetaPhi_em[multClassNo-1]->Fill(phiIdeal,thetaIdeal,momReco); 
      
					
				}

				else if( sim->getGeantPID() == 2 ) {
				
                    h_matrix_reco_MomThetaPhi_ep[multClassNo-1]   ->Fill( phiIdeal, thetaIdeal,momIdeal); 
				//	h_Sm_matrix_reco_MomThetaPhi_ep[multClassNo-1]->Fill( phiIdeal, thetaIdeal,momReco); 

					
				}
			}
   
		} // end cand cat

		//---------kine----------------------------------------------------------------------
		if( kineCat ) {
			

			HGeantKine* kine = 0;

			for( Int_t j = 0; j < kineCat->getEntries(); j++ ) {
				kine = HCategoryManager::getObject( kine, kineCat, j );

				Float_t theta_kine, phi_kine;
				Float_t mom_kine = kine->getTotalMomentum();

				if( !kine->isPrimary() ) continue;
				if( kine->getID() != 2 && kine->getID() != 3 ) continue;

				Float_t MomSmeard = 0;

                static TF1 *CrystallBall = new TF1("CrystallBall",DoubleSidedCrystalballFunction, 0.4,1.3,7);  

				
                    if( kine->getID() == 3 ) {

					if(Param_0_em == nullptr) cout<<"NullPtr Param_0_em!"<<endl;
					
					
				
				//	cout<<" po: "<<p0<<"mom: "<<mom_kine<<endl;
					Double_t p0 = Param_0_em->Eval(mom_kine);
					Double_t p1 = Param_1_em->Eval(mom_kine);
					Double_t p2 = Param_2_em->Eval(mom_kine);
					Double_t p3 = Param_3_em->Eval(mom_kine);
					Double_t p4 = Param_4_em->Eval(mom_kine);
					Double_t p5 = Param_5_em->Eval(mom_kine);
					Double_t p6 = Param_6_em->Eval(mom_kine);

	
					CrystallBall->SetParameters(p0, p1, p2, p3, p4, p5, p6);
							
												
                    Double_t randomCB = CrystallBall->GetRandom();
					MomSmeard = mom_kine*randomCB ;

                
                
				 }
                 else
			     {
                    if(Param_0_ep== nullptr) cout<<"NullPtr Param_0_ep!"<<endl;

					Double_t P0 = Param_0_ep->Eval(mom_kine);
					Double_t P1 = Param_1_ep->Eval(mom_kine);
					Double_t P2 = Param_2_ep->Eval(mom_kine);
					Double_t P3 = Param_3_ep->Eval(mom_kine);
					Double_t P4 = Param_4_ep->Eval(mom_kine);
					Double_t P5 = Param_5_ep->Eval(mom_kine);
					Double_t P6 = Param_6_ep->Eval(mom_kine);

					CrystallBall->SetParameters(P0, P1, P2, P3, P4, P5, P6);
							
                    Double_t randomCB = CrystallBall->GetRandom();
					MomSmeard = mom_kine*randomCB ;
						
				}

				kine->getPhiThetaDeg( theta_kine, phi_kine );

				if(kine->getID() == 3) {
				
					//h_Sm_matrix_kine4pi_MomThetaPhi_em[multClassNo-1] ->Fill(phi_kine,theta_kine,MomSmeard);
                    h_matrix_kine4pi_MomThetaPhi_em[multClassNo-1]    ->Fill(phi_kine,theta_kine,mom_kine);
				}

				if (kine->getID() == 2) {
					
					//h_Sm_matrix_kine4pi_MomThetaPhi_ep[multClassNo-1]  ->Fill(phi_kine,theta_kine,MomSmeard);
                    h_matrix_kine4pi_MomThetaPhi_ep[multClassNo-1]     ->Fill(phi_kine,theta_kine,mom_kine);
				} 

				if( !kine->isInAcceptanceBit(4, 4, 4, 4, 0, 0) ) continue;


				if( kine->getID() == 3 ) {
				
                    h_matrix_kine_MomThetaPhi_em[multClassNo-1]       ->Fill(phi_kine,theta_kine,mom_kine);
					//h_Sm_matrix_kine_MomThetaPhi_em[multClassNo-1]    ->Fill(phi_kine,theta_kine,MomSmeard);

				} 
				else if( kine->getID() == 2 ) {
					
                    h_matrix_kine_MomThetaPhi_ep[multClassNo-1]->Fill(phi_kine,theta_kine,mom_kine);
					//h_Sm_matrix_kine_MomThetaPhi_ep[multClassNo-1]->Fill(phi_kine,theta_kine,MomSmeard);

				}
			} // end loop kine

		}
	} // end eventloop


	out->cd();

	hCounter->Write();

   
    for (Int_t i = 1; i<= MAX_MULT; i++) {


    h_matrix_kine_MomThetaPhi_ep[i-1] ->Write();
    h_matrix_kine_MomThetaPhi_em[i-1] ->Write();
    h_matrix_reco_MomThetaPhi_ep[i-1] ->Write();
    h_matrix_reco_MomThetaPhi_em[i-1] ->Write();

	    
    // h_Sm_matrix_kine_MomThetaPhi_ep[i-1] ->Write();
    // h_Sm_matrix_kine_MomThetaPhi_em[i-1] ->Write();
    // h_Sm_matrix_reco_MomThetaPhi_ep[i-1] ->Write();
    // h_Sm_matrix_reco_MomThetaPhi_em[i-1] ->Write();

	// h_Sm_matrix_kine4pi_MomThetaPhi_ep[i-1] ->Write();
	// h_Sm_matrix_kine4pi_MomThetaPhi_em[i-1] ->Write();

    h_matrix_kine4pi_MomThetaPhi_ep[i-1] ->Write();
	h_matrix_kine4pi_MomThetaPhi_em[i-1] ->Write();

  }


	out->Save();
	out->Close();
	// #################################################

	delete gHades;
	return 0;
}
