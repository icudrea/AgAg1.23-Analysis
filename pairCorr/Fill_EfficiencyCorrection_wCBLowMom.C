#include <iostream>
#include <vector>

#include "TFile.h"
#include "TH1F.h"
#include "TH2F.h"
#include "TMath.h"
#include "TROOT.h"
#include "TString.h"
#include "TSystem.h"
#include "hades.h"
#include "hcategory.h"
#include "hcategorymanager.h"
#include "henergylosscorrpar.h"
#include "hgeantkine.h"
#include "hloop.h"
#include "hparticleanglecor.h"
#include "hparticlebooker.h"
#include "hparticlecand.h"
#include "hparticledef.h"
#include "hparticleevtchara.h"
#include "hparticleevtinfo.h"
#include "hparticletool.h"
#include "hparticletracksorter.h"
#include "hphysicsconstants.h"
#include "hrichcal.h"
#include "hrichhit.h"
#include "htime.h"
#include "richdef.h"

HParticleEvtChara* evtChara;

#include "Useful_Stuff.h"
#include "eventclassifierFlow.h"
#include "heventmixer_backup.h"

using namespace std;

static const Int_t MAX_MULT = 4;

static Bool_t selectLeptonsBetaLoose(HParticleCand* pcand) {
  //  selection function for lepton candidates.

  Bool_t selectEpEm = kFALSE;

  if (pcand->isFlagAND(5,Particle::kIsAcceptedHitRICH,
                         Particle::kIsAcceptedHitInnerMDC,
                         Particle::kIsAcceptedHitOuterMDC, 
                         Particle::kIsAcceptedHitMETA,
                         Particle::kIsAcceptedRK) && pcand->getInnerSegmentChi2() > 0
                         && pcand->getOuterSegmentChi2() > 0 && pcand->getMetaMatchQuality() < 4
                         && pcand->getBeta() > 0.9 && HParticleTool::isGoodMetaCell(pcand, 4, kTRUE) 
                        && pcand->getChi2() < 1000. && pcand->getMomentum() < 2000. && !pcand->isAtAnyMdcEdge()) {
    selectEpEm = kTRUE;
  }

  return selectEpEm;
}

void doTrackCorr(HParticleAngleCor& trackcor, HCategory* candCat) {
  Int_t size = candCat->getEntries();
  for (Int_t j = 0; j < size; j++) {
    HParticleCand* cand;
    cand = HCategoryManager::getObject(cand, candCat, j);
    trackcor.recalcSetEmission(cand);  // changes values inside candidate
                                       // trackcor.realignRichRing(cand); //
  }
}

Int_t Fill_EfficiencyCorrection_wCBLowMom(

    // TString infileList="/lustre/hades/dst/mar19/gen5/ag123ag/2500A/rotateRich/089_60deg/root/be*.hld_dst_mar19_accepted.root",
    TString infileList = "/lustre/hades/dst/mar19/gen5/ag123ag/2500A/089/root/be*.hld_dst_mar19_accepted.root",
    // TString infileList="/lustre/hades/dst/mar19/gen5/ag123ag/2500A/rotateRich/089_60deg/root/be*.hld_dst_mar19_accepted.root",
    TString outfile = "test.root", Int_t nEvents = -1) {
  Bool_t isDataulation = kFALSE;  // Data or real data

  //-------------------------------------------------
  // create loop obejct and hades
  HLoop loop(kTRUE);
  //-------------------------------------------------
  // TString paraFile = "/lustre/hades/user/bkardan/param/centrality_epcorr_mar19_ag158ag_3200A_glauber_gen5_pass3_2021_08.root";
  TString paraFile = "/lustre/hades/user/bkardan/param/centrality_epcorr_mar19_ag123ag_2500A_glauber_gen4_2020_10_pass3.root";
  //-------------------------------------------------
  // list of all files with working sectors
  if (!isDataulation) loop.readSectorFileList("/lustre/hades/dst/mar19/gen5/sector_selection/Mar19AgAg1230_Gen5.list", kFALSE, kFALSE);
  //-------------------------------------------------

  HParticleAngleCor trackcor;
  trackcor.setDefaults("mar19");
  trackcor.setShield(kTRUE);
  trackcor.setUseEventXYVertex();
  trackcor.setMeanZTarget(-34.8);
  trackcor.setVertexType(Particle::kVertexCluster);

  //-------------------------------------------------
  // reading input files and decalring containers
  Bool_t ret = kFALSE;
  if (infileList.Contains(",")) {
    ret = loop.addMultFiles(infileList);  // file1,file2,file3
  } else {
    ret = loop.addFiles(infileList);  // myroot*.root
  }
  if (ret == 0) {
    cout << "READBACK: ERROR : cannot find inputfiles : " << infileList.Data() << endl;
    return 1;
  }

  if (!loop.setInput("")) {  // all input categories
                             // if(!loop.setInput("-*,+HParticleCand,+HParticleEvtInfo,+HRichCal,+HRichHit,+")) {
    cout << "READBACK: ERROR : cannot read input !" << endl;
    exit(1);
  }  // read all categories
  loop.printCategories();
  loop.printChain();

  //-----gaus fit for betafix
  Double_t Xmin = -800;
  Double_t Xmax = 800;

  TF1* func = new TF1("func", "gaus", Xmin, Xmax);
  Double_t fgaus_param[3] = {3.06179e-02, 2.03138e+01, 1.56586e+03};
  func->SetParameters(fgaus_param);

  //###############################################
  TFile* S_dPhi          = TFile::Open("sigma_dPhi.root", "READ");
  TFile* S_dTheta        = TFile::Open("sigma_dTheta.root", "READ");
  TFile* f_EffCorrection = TFile::Open("EffMatrix_WLowMomCB_Rebin_30.root", "READ");

  TH1F* sigma_phi   = (TH1F*)S_dPhi->Get("SigmaHist1");
  TH1F* sigma_theta = (TH1F*)S_dTheta->Get("SigmaHist1");

  TH3D* h_Sm_matrix_kine_MomThetaPhi_ep[MAX_MULT];
  TH3D* h_Sm_matrix_kine_MomThetaPhi_em[MAX_MULT];

  // TH3D* h_Sm_Accmatrix_kine_MomThetaPhi_ep[MAX_MULT];
  // TH3D* h_Sm_Accmatrix_kine_MomThetaPhi_em[MAX_MULT];

  for (int mult = 1; mult <= MAX_MULT; ++mult) {
    h_Sm_matrix_kine_MomThetaPhi_ep[mult - 1] = (TH3D*)f_EffCorrection->Get(Form("h_Sm_matrix_kine_MomThetaPhi_ep_%i", mult));
    h_Sm_matrix_kine_MomThetaPhi_em[mult - 1] = (TH3D*)f_EffCorrection->Get(Form("h_Sm_matrix_kine_MomThetaPhi_em_%i", mult));
    // h_Sm_Accmatrix_kine_MomThetaPhi_ep[mult - 1] = (TH3D*)f_AccCorrection->Get(Form("h_Sm_matrix_kine_MomThetaPhi_ep_%i", mult));
    // h_Sm_Accmatrix_kine_MomThetaPhi_em[mult - 1] = (TH3D*)f_AccCorrection->Get(Form("h_Sm_matrix_kine_MomThetaPhi_em_%i", mult));

    if (h_Sm_matrix_kine_MomThetaPhi_ep[mult - 1] == nullptr) {
      cout << "Error: Histogram h_Sm_matrix_kine_MomThetaPhi_ep_" << mult << " not found, DAMN" << endl;
    }

    // if (h_Sm_Accmatrix_kine_MomThetaPhi_ep[mult - 1] == nullptr) {
    //   cout << "Error: Histogram h_Sm_Accmatrix_kine_MomThetaPhi_ep" << mult << " not found, DAMN " << endl;
    // }
  }
  //#################################################
  // histograms here
  TFile* out = new TFile(outfile.Data(), "RECREATE");
  out->cd();

  TH1F* hCounter = new TH1F("hCounter", " ", 20, 0, 20);

  TH1* PairSize = new TH1F("PairSize", "PairSize", 200, 0, 200);

  TH1* VemSize        = new TH1F("VemSize", "VemSize", 20, 0, 20);
  TH1* VepSize        = new TH1F("VepSize", "VepSize", 20, 0, 20);
  TH2D* Vem_ep_PID_ME = new TH2D("Vem_ep_PID_ME", "Vem_ep_PID_ME", 20, 0, 20, 20, 0, 20);

  VemSize->GetXaxis()->SetTitle("Number of electrons");
  VemSize->GetYaxis()->SetTitle("Number of events");

  VepSize->GetXaxis()->SetTitle("Number of positrons");
  VepSize->GetYaxis()->SetTitle("Number of events");

  PairSize->GetXaxis()->SetTitle("Number of pairs");
  PairSize->GetYaxis()->SetTitle("Number of events");

  Vem_ep_PID_ME->GetXaxis()->SetTitle("Number of positrons");
  Vem_ep_PID_ME->GetYaxis()->SetTitle("Number of electrons");

  TH1::SetDefaultSumw2();

  TH2D* hBvsMom_sys0_kIsLepton = new TH2D("hBvsMom_sys0_kIsLepton", "", 300, -3000, 3000, 300, 0, 2);
  TH2D* hBvsMom_sys1_kIsLepton = new TH2D("hBvsMom_sys1_kIsLepton", "", 300, -3000, 3000, 300, 0, 2);
  TH2D* hBvsMom_kIsLepton = new TH2D("hBvsMom_kIsLepton", "", 300, -3000, 3000, 300, 0, 2);

  TH2D* hBvsMom_sys0_beta = new TH2D("hBvsMom_sys0_beta", "", 300, -3000, 3000, 300, 0, 2);
  TH2D* hBvsMom_sys1_beta = new TH2D("hBvsMom_sys1_beta", "", 300, -3000, 3000, 300, 0, 2);

  TH2D* hBvsMom_sys0_richQA = new TH2D("hBvsMom_sys0_richQA", "", 300, -3000, 3000, 300, 0, 2);
  TH2D* hBvsMom_sys1_richQA = new TH2D("hBvsMom_sys1_richQA", "", 300, -3000, 3000, 300, 0, 2);

  TH2D* hBvsMom_sys0_RRad = new TH2D("hBvsMom_sys0_RRad", "", 300, -3000, 3000, 300, 0, 2);
  TH2D* hBvsMom_sys1_RRad = new TH2D("hBvsMom_sys0_RRad", "", 300, -3000, 3000, 300, 0, 2);

  TH2D* hBvsMom_sys0 = new TH2D("hBvsMom_sys0", "", 300, -3000, 3000, 300, 0, 2);
  TH2D* hBvsMom_sys1 = new TH2D("hBvsMom_sys1", "", 300, -3000, 3000, 300, 0, 2);
  TH2D* hBvsMom = new TH2D("hBvsMom", "", 300, -3000, 3000, 300, 0, 2);

  ////////////////////////////////////

  TH2D* hDelta_theta_Momentum_beforecuts = new TH2D("hDelta_theta_Momentum_beforecuts", " ", 100, -2000, 2000, 100, -10, 10);
  TH2D* hDelta_phi_Momentum_beforecuts   = new TH2D("hDelta_phi_Momentum_beforecuts", " ", 100, -2000, 2000, 100, -10, 10);
  TH2D* hDelta_theta_Momentum_aftercuts  = new TH2D("hDelta_theta_Momentum_aftercuts", " ", 100, -2000, 2000, 100, -10, 10);
  TH2D* hDelta_phi_Momentum_aftercuts    = new TH2D("hDelta_phi_Momentum_aftercuts", " ", 100, -2000, 2000, 100, -10, 10);

  ////////////////////////////////////


  TH1D* fh_mass_ep_em = new TH1D("fh_mass_ep_em", "Invariant mass e^{+}e^{-} [GeV/c^{2}]", 360, 0., 1.8);
  fh_mass_ep_em->GetXaxis()->SetTitle("M_{ee} [GeV/c^{2}]");
  fh_mass_ep_em->GetYaxis()->SetTitle("dN/dM_{ee} [1/(GeV/c^{2})]");

  TH1D* fh_mass_em_em = new TH1D("fh_mass_em_em", "Invariant mass e^{-}e^{-} [GeV/c^{2}]", 360, 0., 1.8);
  fh_mass_em_em->GetXaxis()->SetTitle("M_{ee} [GeV/c^{2}]");
  fh_mass_em_em->GetYaxis()->SetTitle("dN/dM_{ee} [1/(GeV/c^{2})]");

  TH1D* fh_mass_ep_ep = new TH1D("fh_mass_ep_ep", "Invariant mass e^{+}e^{+} [GeV/c^{2}]", 360, 0., 1.8);
  fh_mass_ep_ep->GetXaxis()->SetTitle("M_{ee} [GeV/c^{2}]");
  fh_mass_ep_ep->GetYaxis()->SetTitle("dN/dM_{ee} [1/(GeV/c^{2})]");

  TH1D* fh_mass_ep_em_effCorr = new TH1D("fh_mass_ep_em_effCorr", "Invariant mass e^{+}e^{-} [GeV/c^{2}]", 360, 0., 1.8);
  fh_mass_ep_em_effCorr->GetXaxis()->SetTitle("M_{ee} [GeV/c^{2}]");
  fh_mass_ep_em_effCorr->GetYaxis()->SetTitle("dN/dM_{ee} [1/(GeV/c^{2})]");

  TH1D* fh_mass_em_em_effCorr = new TH1D("fh_mass_em_em_effCorr", "Invariant mass e^{+}e^{-} [GeV/c^{2}]", 360, 0., 1.8);
  fh_mass_em_em_effCorr->GetXaxis()->SetTitle("M_{ee} [GeV/c^{2}]");
  fh_mass_em_em_effCorr->GetYaxis()->SetTitle("dN/dM_{ee} [1/(GeV/c^{2})]");

  TH1D* fh_mass_ep_ep_effCorr = new TH1D("fh_mass_ep_ep_effCorr", "Invariant mass e^{+}e^{-} [GeV/c^{2}]", 360, 0., 1.8);
  fh_mass_ep_ep_effCorr->GetXaxis()->SetTitle("M_{ee} [GeV/c^{2}]");
  fh_mass_ep_ep_effCorr->GetYaxis()->SetTitle("dN/dM_{ee} [1/(GeV/c^{2})]");

  //////////////////////////

  TH1D* fh_mass_ep_em_mixedEvents = new TH1D("fh_mass_ep_em_mixedEvents", "Invariant mass e^{+}e^{-} [GeV/c^{2}]", 360, 0., 1.8);
  fh_mass_ep_em_mixedEvents->GetXaxis()->SetTitle("M_{ee} [GeV/c^{2}]");
  fh_mass_ep_em_mixedEvents->GetYaxis()->SetTitle("dN/dM_{ee} [1/(GeV/c^{2})]");

  TH1D* fh_mass_em_em_mixedEvents = new TH1D("fh_mass_em_em_mixedEvents", "Invariant mass e^{-}e^{-} [GeV/c^{2}]", 360, 0., 1.8);
  fh_mass_em_em_mixedEvents->GetXaxis()->SetTitle("M_{ee} [GeV/c^{2}]");
  fh_mass_em_em_mixedEvents->GetYaxis()->SetTitle("dN/dM_{ee} [1/(GeV/c^{2})]");

  TH1D* fh_mass_ep_ep_mixedEvents = new TH1D("fh_mass_ep_ep_mixedEvents", "Invariant mass e^{+}e^{+} [GeV/c^{2}]", 360, 0., 1.8);
  fh_mass_ep_ep_mixedEvents->GetXaxis()->SetTitle("M_{ee} [GeV/c^{2}]");
  fh_mass_ep_ep_mixedEvents->GetYaxis()->SetTitle("dN/dM_{ee} [1/(GeV/c^{2})]");

  TH1D* fh_mass_ep_em_mixedEvents_effCorr = new TH1D("fh_mass_ep_em_mixedEvents_effCorr", "Invariant mass e^{+}e^{-} [GeV/c^{2}]", 360, 0., 1.8);
  fh_mass_ep_em_mixedEvents_effCorr->GetXaxis()->SetTitle("M_{ee} [GeV/c^{2}]");
  fh_mass_ep_em_mixedEvents_effCorr->GetYaxis()->SetTitle("dN/dM_{ee} [1/(GeV/c^{2})]");

  TH1D* fh_mass_em_em_mixedEvents_effCorr = new TH1D("fh_mass_em_em_mixedEvents_effCorr", "Invariant mass e^{+}e^{-} [GeV/c^{2}]", 360, 0., 1.8);
  fh_mass_em_em_mixedEvents_effCorr->GetXaxis()->SetTitle("M_{ee} [GeV/c^{2}]");
  fh_mass_em_em_mixedEvents_effCorr->GetYaxis()->SetTitle("dN/dM_{ee} [1/(GeV/c^{2})]");

  TH1D* fh_mass_ep_ep_mixedEvents_effCorr = new TH1D("fh_mass_ep_ep_mixedEvents_effCorr", "Invariant mass e^{+}e^{-} [GeV/c^{2}]", 360, 0., 1.8);
  fh_mass_ep_ep_mixedEvents_effCorr->GetXaxis()->SetTitle("M_{ee} [GeV/c^{2}]");
  fh_mass_ep_ep_mixedEvents_effCorr->GetYaxis()->SetTitle("dN/dM_{ee} [1/(GeV/c^{2})]");

  // TH2F* h_epem_oAngle9_mass_pt     = new TH2F("h_epem_oAngle9_mass_pt", ";#it{M}_{ee} (GeV/#it{c}^{2});p_{T} (GeV/#it{c})", 1000, 0., 1.8, 500, 0., 1.8);
  // TH2F* h_epem_oAngle9_mass_p      = new TH2F("h_epem_oAngle9_mass_p", ";#it{M}_{ee} (GeV/#it{c}^{2});p_{CM} (GeV/#it{c})", 1000, 0., 1.8, 500, 0., 1.8);
  // TH2F* h_epem_oAngle9_mass_oAngle = new TH2F("h_epem_oAngle9_mass_oAngle", ";#it{M}_{ee} (GeV/#it{c}^{2});#alpha_{op} (degree)", 1000, 0., 1.8, 180, 0., 180.);

  // TH2F* h_epep_oAngle9_mass_pt     = new TH2F("h_epep_oAngle9_mass_pt", ";#it{M}_{ee} (GeV/#it{c}^{2});p_{T} (GeV/#it{c})", 1000, 0., 1.8, 500, 0., 1.8);
  // TH2F* h_epep_oAngle9_mass_p      = new TH2F("h_epep_oAngle9_mass_p", ";#it{M}_{ee} (GeV/#it{c}^{2});p_{CM} (GeV/#it{c})", 1000, 0., 1.8, 500, 0., 1.8);
  // TH2F* h_epep_oAngle9_mass_oAngle = new TH2F("h_epep_oAngle9_mass_oAngle", ";#it{M}_{ee} (GeV/#it{c}^{2});#alpha_{op} (degree)", 1000, 0., 1.8, 180, 0., 180.);

  // TH2F* h_emem_oAngle9_mass_pt     = new TH2F("h_emem_oAngle9_mass_pt", ";#it{M}_{ee} (GeV/#it{c}^{2});p_{T} (GeV/#it{c})", 1000, 0., 1.8, 500, 0., 1.8);
  // TH2F* h_emem_oAngle9_mass_p      = new TH2F("h_emem_oAngle9_mass_p", ";#it{M}_{ee} (GeV/#it{c}^{2});p_{CM} (GeV/#it{c})", 1000, 0., 1.8, 500, 0., 1.8);
  // TH2F* h_emem_oAngle9_mass_oAngle = new TH2F("h_emem_oAngle9_mass_oAngle", ";#it{M}_{ee} (GeV/#it{c}^{2});#alpha_{op} (degree)", 1000, 0., 1.8, 180, 0., 180.);

  // parameters
  HEnergyLossCorrPar dEdxCorr;
  dEdxCorr.setDefaultPar("mar19");
  //-------------------------------------------------

  //----------------------------------------------------------------------------------------
  // input data

  HCategory* candCat = (HCategory*)HCategoryManager::getCategory(catParticleCand);
  // HCategory *kineCat          = (HCategory *)HCategoryManager::getCategory(catGeantKine);
  HCategory* evtInfoCat = (HCategory*)HCategoryManager::getCategory(catParticleEvtInfo);
  HCategory* richCalCat = (HCategory*)HCategoryManager::getCategory(catRichCal);
  HCategory* richHitCat = (HCategory*)HCategoryManager::getCategory(catRichHit);
  //----------------------------------------------------------------------------------------

  HParticleTrackSorter sorter;

  sorter.init();
  //---------------------------------------Event Chara-------------------------------------------------------
  evtChara = new HParticleEvtChara;
  cout << "HParticleEvtChara: reading: " << paraFile << endl;
  if (!evtChara->setParameterFile(paraFile)) {
    cout << "HParticleEvtChara: file not found!!! " << endl;
  }
  if (!evtChara->init()) {
    cout << "HParticleEvtChara not init!!! " << endl;
  }
  evtChara->printCentralityClass(HParticleEvtChara::kTOFRPC, HParticleEvtChara::k5);
  evtChara->printCentralityClass(HParticleEvtChara::kTOFRPC, HParticleEvtChara::k10);

  //------------------------------------------------------------------------------------------------

  //--------------------Event Mixing Method----------------------------

  HParticleEventMixer eventmixer;
  eventmixer.setPIDs(2, 3, 1);
  eventmixer.setBuffSize(80);
  eventmixer.setWaitForBuffer(kFALSE);  // do not wait for full buffer
  eventmixer.setEventClassifier(eventClassifierMultRPhiTarget);
  // eventmixer.setEventClassifier(eventClassifierMultRPhiTargetFewer);
  //--------------------------------------------------------------------------------------------

  //----event loop starts here
  Int_t entries = loop.getEntries();
  if (nEvents < entries && nEvents >= 0) entries = nEvents;
  TString filename;

  for (Int_t i = 0; i < entries; i++) {
    Int_t nbytes = loop.nextEvent(i);  // get next event. categories will be cleared before
    if (nbytes <= 0) {
      cout << nbytes << endl;
      break;
    }  // last event reached
    if (i % 1000 == 0) cout << "event " << i << endl;

    hCounter->Fill(0);

    if (loop.isNewFile(filename)) {                                                  // if the actual filename is needed
      if (!isDataulation) filename = HTime::stripFileName(filename, kTRUE, kFALSE);  // get hld file name
    }

    //-------------------------------------------------
    // summary event info object
    HParticleEvtInfo* evtInfo = 0;
    evtInfo = HCategoryManager::getObject(evtInfo, evtInfoCat, 0);

    HVertex PrimVertexReco = ((HEventHeader*)(gHades->getCurrentEvent()->getHeader()))->getVertexReco();
    Float_t vz = PrimVertexReco.getZ();

    if (vz < -70) continue;

    hCounter->Fill(1);

    if (evtInfo && !evtInfo->isGoodEvent(Particle::kGoodTRIGGER |      // more than 20 hits in TOF&RPC correlated to a hit in START
                                         Particle::kGoodVertexClust |  // converged custer vertex fit,vertex position of z>-70mm
                                         Particle::kGoodVertexCand |   // event vertex, calculated from cluster hits in inener MDCs
                                         Particle::kGoodSTART |        // hit in START
                                         // astanuParticle::kNoPileUpSTART|
                                         Particle::kNoSTART | Particle::kNoVETO | Particle::kGoodSTARTVETO |  // evts where a second START hit(15ns -350ns) is found that has no correlated VETO hit is excluded
                                         Particle::kGoodSTARTMETA                                             // reject evnts with second START hit correlated to at least 4 META hits in 7+-5ns
                                         ))
      continue;

    hCounter->Fill(2);

    //-----Centrality classes--------------------------------------------
    Int_t multClassNo10 = evtChara->getCentralityClass(HParticleEvtChara::kTOFRPC, HParticleEvtChara::k10);
    Int_t multClassNo = multClassNo10;
    if (multClassNo < 1 || multClassNo >= MAX_MULT) continue;

    //-------------------------------------------------------------------

    hCounter->Fill(3);

    //--- clean sorter
    sorter.cleanUp();
    sorter.resetFlags(kTRUE, kTRUE, kTRUE, kTRUE);  // reset all flags for flags (0-28) ,reject,used,lepton
    sorter.fill(selectLeptonsBetaLoose);            // fill only good leptons
    sorter.selectBest(Particle::kIsBestRKSorter, Particle::kIsLeptonSorter);
    // sorter.fill( HParticleTrackSorter::selectHadrons ); // fill only good hadrons (already marked good leptons will be skipped)
    // sorter.selectBest( Particle::kIsBestRKSorter, Particle::kIsHadronSorter );
    //--------------------------------------------------------------------

    // loop over particle candidates in event
    if (!candCat) continue;

    Int_t size = candCat->getEntries();

    doTrackCorr(trackcor, candCat);

    Bool_t conversionFlag[size];

    for (Int_t j = 0; j < size; j++) {
      conversionFlag[j] = kFALSE;
    }
    vector<Int_t> leptonIndex;  // vector of leptons
    vector<HParticleCand*> vep;
    vector<HParticleCand*> vem;

    HParticleCand* cand = 0;
    for (Int_t j = 0; j < size; j++) {
      cand = HCategoryManager::getObject(cand, candCat, j);

      if (!cand) continue;
      if (!loop.goodSector(cand->getSector())) {
        continue;
      }  // skipp inactive sectors
      if (!cand->isFlagBit(kIsUsed)) {
        continue;
      }  // skip particles rejected by HParticleTrackSorter

      cand->calc4vectorProperties(HPhysicsConstants::mass("e+"));

      //......attributes.................
      Int_t    cal_counter;
      Double_t beta      = cand->getBeta();
      Float_t DeltaTheta = cand->getDeltaTheta();
      Float_t DeltaPhi   = cand->getDeltaPhi();
      Int_t   sec        = cand->getSector();
      Float_t RingRad    = cand->getRingRadius();
      Int_t   system     = cand->getSystemUsed();
      Float_t Momentum   = cand->getMomentum();
      Short_t charge     = cand->getCharge();
      Float_t momPID     = charge * Momentum;
      Float_t MomentumCut= Momentum;
       

      //..........Lepton selection.............
      if (!cand->isFlagBit(Particle::kIsLepton)) continue;

      hBvsMom_kIsLepton->Fill(momPID, beta);
      if (system == 0) {
        hBvsMom_sys0_kIsLepton->Fill(momPID, beta);
      }
      if (system == 1) {
        hBvsMom_sys1_kIsLepton->Fill(momPID, beta);
      }

      hDelta_theta_Momentum_beforecuts->Fill(momPID, DeltaTheta);
      hDelta_phi_Momentum_beforecuts  ->Fill(momPID, DeltaPhi);

      if (isConversion(cand, richHitCat, richCalCat, cal_counter)) conversionFlag[j] = kTRUE;
      if (isOARing(cand, richHitCat)) continue;
      if (conversionFlag[j]) continue;

      // --------------lepton identification----------------------------------------------------

      if (system == 1 && beta < 1 - 3 * (func->Eval(momPID))) continue;

      if (system == 0 && beta < 1 - 3 * 0.012) continue;

      if (system == 0) {
        hBvsMom_sys0_beta->Fill(momPID, beta);
      }
      if (system == 1) {
        hBvsMom_sys1_beta->Fill(momPID, beta);
      }

      if (TMath::Abs(DeltaPhi) > 3 * sigma_phi->Interpolate(momPID)) continue;
      if (TMath::Abs(DeltaTheta) > 3 * sigma_theta->Interpolate(momPID)) continue;

      if (system == 0) {
        hBvsMom_sys0_richQA->Fill(momPID, beta);
      }
      if (system == 1) {
        hBvsMom_sys1_richQA->Fill(momPID, beta);
      }

      if (RingRad < 19) continue;

      if (system == 0) {
        hBvsMom_sys0_RRad->Fill(momPID, beta);
      }
      if (system == 1) {
        hBvsMom_sys1_RRad->Fill(momPID, beta);
      }

      // if(Momentum > 800 || Momentum < -800 )                                                                                        continue;
      hBvsMom->Fill(momPID, beta);
      if (system == 0) {
        hBvsMom_sys0->Fill(momPID, beta);
      }
      if (system == 1) {
        hBvsMom_sys1->Fill(momPID, beta);
      }

      hDelta_theta_Momentum_aftercuts->Fill(momPID, DeltaTheta);
      hDelta_phi_Momentum_aftercuts->Fill(momPID, DeltaPhi);

      leptonIndex.push_back(j);

      if (charge == -1) {
        vem.push_back(new HParticleCand(*cand));
      } else {
        vep.push_back(new HParticleCand(*cand));
      }
    }  // cand loop end

    //.................pair selection..................

    HParticleCand* cand1 = 0;
    HParticleCand* cand2 = 0;

    for (UInt_t j = 0; j < leptonIndex.size(); j++) {
      cand1 = HCategoryManager::getObject(cand, candCat, leptonIndex.at(j));
      if (!cand1) continue;

      for (UInt_t k = j + 1; k < leptonIndex.size(); k++) {
        cand2 = HCategoryManager::getObject(cand, candCat, leptonIndex.at(k));
        if (!cand2) continue;

        TLorentzVector em_ep_pair = (*cand1) + (*cand2);

        Short_t Charge1 = cand1->getCharge();
        Short_t Charge2 = cand2->getCharge();

        Float_t Theta1 = cand1->getTheta();
        Float_t Theta2 = cand2->getTheta();

        Float_t Phi1 = cand1->getPhi();
        Float_t Phi2 = cand2->getPhi();

        Float_t Momentum1 = cand1->getMomentum();
        Float_t Momentum2 = cand2->getMomentum();

        Float_t MassPair = em_ep_pair.M();
        // cout<<"massPair= "<<MassPair<<endl;
        Float_t MassPair_scaled = MassPair / 1000;
        Double_t pT = em_ep_pair.Pt();
        Double_t y = em_ep_pair.Rapidity();
        Double_t p = em_ep_pair.P();
        Float_t oAngle = HParticleTool::getOpeningAngle(cand1->getPhi(), cand1->getTheta(), cand2->getPhi(), cand2->getTheta());

        TLorentzVector dilep(em_ep_pair);
        dilep.Boost(0., 0., -0.629);

        Float_t dilep_m = dilep.M() / 1000.;
        Float_t dilep_p = dilep.P() / 1000.;
        Float_t dilep_pt = dilep.Perp() / 1000.;

        Int_t MombinCand1 = h_Sm_matrix_kine_MomThetaPhi_ep[multClassNo]->GetZaxis()->FindBin(Momentum1);
        Int_t MombinCand2 = h_Sm_matrix_kine_MomThetaPhi_em[multClassNo]->GetZaxis()->FindBin(Momentum2);

        Int_t ThetabinCand1 = h_Sm_matrix_kine_MomThetaPhi_ep[multClassNo]->GetYaxis()->FindBin(Theta1);
        Int_t ThetabinCand2 = h_Sm_matrix_kine_MomThetaPhi_em[multClassNo]->GetYaxis()->FindBin(Theta2);

        Int_t PhibinCand1 = h_Sm_matrix_kine_MomThetaPhi_ep[multClassNo]->GetXaxis()->FindBin(Phi1);
        Int_t PhibinCand2 = h_Sm_matrix_kine_MomThetaPhi_em[multClassNo]->GetXaxis()->FindBin(Phi2);

        Float_t effCand1;

        if (Charge1 == 1) {
          effCand1 = h_Sm_matrix_kine_MomThetaPhi_ep[multClassNo]->GetBinContent(PhibinCand1, ThetabinCand1, MombinCand1);
        } else {
          effCand1 = h_Sm_matrix_kine_MomThetaPhi_em[multClassNo]->GetBinContent(PhibinCand1, ThetabinCand1, MombinCand1);
        }

        Float_t effCand2;

        if (Charge2 == 1) {
          effCand2 = h_Sm_matrix_kine_MomThetaPhi_ep[multClassNo]->GetBinContent(PhibinCand2, ThetabinCand2, MombinCand2);

        } else {
          effCand2 = h_Sm_matrix_kine_MomThetaPhi_em[multClassNo]->GetBinContent(PhibinCand2, ThetabinCand2, MombinCand2);
        }

        Float_t effW = 0;
        if (effCand1 > 0 && effCand2 > 0) {
          effW = 1 / (effCand1 * effCand2);
        }
        // cout<<"effW= "<<effW<<endl;
        if (effW > 10) continue;

        //if ((oAngle > 9) && (Momentum1>100) && (Momentum2>100)) {
        if (oAngle > 9){
          if (Charge1 * Charge2 == -1) {
            fh_mass_ep_em->Fill(MassPair_scaled);
            fh_mass_ep_em_effCorr->Fill(MassPair_scaled, effW);
          }

          if (Charge1 == 1 && Charge2 == 1) {
            fh_mass_ep_ep->Fill(MassPair_scaled);
            fh_mass_ep_ep_effCorr->Fill(MassPair_scaled, effW);
          }

          if (Charge1 == -1 && Charge2 == -1) {
            fh_mass_em_em->Fill(MassPair_scaled);
            fh_mass_em_em_effCorr->Fill(MassPair_scaled, effW);
          }
        }

        // if (cand1->getCharge() + cand2->getCharge() == 0) {
        //   if (oAngle > 9) {
        //     h_epem_oAngle9_mass_pt->Fill(dilep_m, dilep_pt);
        //     h_epem_oAngle9_mass_p->Fill(dilep_m, dilep_p);
        //     h_epem_oAngle9_mass_oAngle->Fill(dilep_m, oAngle);
        //   }
        // }
        // if (cand1->getCharge() + cand2->getCharge() == 2) {
        //   if (oAngle > 9) {
        //     h_epep_oAngle9_mass_pt->Fill(dilep_m, dilep_pt);
        //     h_epep_oAngle9_mass_p->Fill(dilep_m, dilep_p);
        //     h_epep_oAngle9_mass_oAngle->Fill(dilep_m, oAngle);
        //   }
        // }
        // if (cand1->getCharge() + cand2->getCharge() == -2) {
        //   if (oAngle > 9) {
        //     h_emem_oAngle9_mass_pt->Fill(dilep_m, dilep_pt);
        //     h_emem_oAngle9_mass_p->Fill(dilep_m, dilep_p);
        //     h_emem_oAngle9_mass_oAngle->Fill(dilep_m, oAngle);
        //   }
        // }

        //  } //oAngle cut

      }  // loop 2nd candidate
    }    // loop first candidate

    //------EVENT MIXER--------------------------------------

    VemSize->Fill(vem.size());
    VepSize->Fill(vep.size());
    if (vem.size() + vep.size() > 1) {
      Vem_ep_PID_ME->Fill(vep.size(), vem.size());
    }

    eventmixer.nextEvent();
    eventmixer.addVector(vep, 2);
    eventmixer.addVector(vem, 3);
    vector<HParticlePair>& pairsVec = eventmixer.getMixedVector();

    Int_t sizePair = pairsVec.size();
    PairSize->Fill(sizePair);

    for (Int_t j = 0; j < sizePair; j++) {
      HParticlePair& pair = pairsVec[j];
      HParticleCand *cand1, *cand2;

      cand1 = dynamic_cast<HParticleCand*>(pair.getCand(0));
      if (!cand1->isFlagBit(Particle::kIsLepton)) continue;
      cand2 = dynamic_cast<HParticleCand*>(pair.getCand(1));
      if (!cand2->isFlagBit(Particle::kIsLepton)) continue;

      if (cand1->getCharge() == -1 && cand2->getCharge() == 1) {
        HParticleCand* temp = cand1;
        cand1 = cand2;
        cand2 = temp;
      }

      Short_t LChargeA = cand1->getCharge();
      Short_t LChargeB = cand2->getCharge();

      Float_t ThetaA = cand1->getTheta();
      Float_t ThetaB = cand2->getTheta();

      Float_t PhiA = cand1->getPhi();
      Float_t PhiB = cand2->getPhi();

      Float_t MomentumA = cand1->getMomentum();
      Float_t MomentumB = cand2->getMomentum();

      Int_t MombinCandA = h_Sm_matrix_kine_MomThetaPhi_ep[multClassNo]->GetZaxis()->FindBin(MomentumA);
      Int_t MombinCandB = h_Sm_matrix_kine_MomThetaPhi_em[multClassNo]->GetZaxis()->FindBin(MomentumB);

      Int_t ThetabinCandA = h_Sm_matrix_kine_MomThetaPhi_ep[multClassNo]->GetYaxis()->FindBin(ThetaA);
      Int_t ThetabinCandB = h_Sm_matrix_kine_MomThetaPhi_em[multClassNo]->GetYaxis()->FindBin(ThetaB);

      Int_t PhibinCandA = h_Sm_matrix_kine_MomThetaPhi_ep[multClassNo]->GetXaxis()->FindBin(PhiA);
      Int_t PhibinCandB = h_Sm_matrix_kine_MomThetaPhi_em[multClassNo]->GetXaxis()->FindBin(PhiB);

      Float_t effCandA;

      if (LChargeA == 1) {
        effCandA = h_Sm_matrix_kine_MomThetaPhi_ep[multClassNo]->GetBinContent(PhibinCandA, ThetabinCandA, MombinCandA);
      } else {
        effCandA = h_Sm_matrix_kine_MomThetaPhi_em[multClassNo]->GetBinContent(PhibinCandA, ThetabinCandA, MombinCandA);
      }

      Float_t effCandB;

      if (LChargeB == 1) {
        effCandB = h_Sm_matrix_kine_MomThetaPhi_ep[multClassNo]->GetBinContent(PhibinCandB, ThetabinCandB, MombinCandB);

      } else {
        effCandB = h_Sm_matrix_kine_MomThetaPhi_em[multClassNo]->GetBinContent(PhibinCandB, ThetabinCandB, MombinCandB);
      }

      Float_t effWeight = 0;
      if (effCandA > 0 && effCandB > 0) {
        effWeight = 1 / (effCandA * effCandB);
      }
      if (effWeight > 10) continue;

      TLorentzVector dilep = (*cand1) + (*cand2);
      Float_t masspairUnscaled = dilep.M();
      Float_t masspair = masspairUnscaled / 1000;
      Double_t PT = dilep.Pt();
      Double_t Y = dilep.Rapidity();
      Double_t P = dilep.P();
      Float_t oAngle = cand1->Angle(cand2->Vect()) * TMath::RadToDeg();

    //   if ((oAngle > 9)&& (MomentumA>100) && (MomentumB>100)) {
        if (oAngle > 9){
        if (LChargeA * LChargeB == -1) {
          fh_mass_ep_em_mixedEvents->Fill(masspair);
          fh_mass_ep_em_mixedEvents_effCorr->Fill(masspair, effWeight);
        }

        if (LChargeA == 1 && LChargeB == 1) {
          fh_mass_ep_ep_mixedEvents->Fill(masspair);
          fh_mass_ep_ep_mixedEvents_effCorr->Fill(masspair, effWeight);
        }

        if (LChargeA == -1 && LChargeB == -1) {
          fh_mass_em_em_mixedEvents->Fill(masspair);
          fh_mass_em_em_mixedEvents_effCorr->Fill(masspair, effWeight);
        }

      }  // OAcut

    }  // end of mixedpairs loop

    vector<HParticleCand*>* toDel = eventmixer.getObjectsToDelete();
    for (unsigned int ii = 0; ii < toDel->size(); ++ii) {
      delete toDel->at(ii);
    }
    toDel->clear();
    delete toDel;

    //-----------------------------------------------------

  }  // end eventloop

  out->cd();
  hCounter->Write();

  hBvsMom_sys0_kIsLepton->Write();
  hBvsMom_sys1_kIsLepton->Write();
  hBvsMom_sys0_beta->Write();
  hBvsMom_sys1_beta->Write();
  hBvsMom_sys0_richQA->Write();
  hBvsMom_sys1_richQA->Write();
  hBvsMom_sys0_RRad->Write();
  hBvsMom_sys1_RRad->Write();

  hDelta_theta_Momentum_beforecuts->Write();
  hDelta_phi_Momentum_beforecuts->Write();

  hDelta_theta_Momentum_aftercuts->Write();
  hDelta_phi_Momentum_aftercuts->Write();

  hBvsMom_kIsLepton->Write();
  hBvsMom_sys0->Write();
  hBvsMom_sys1->Write();
  hBvsMom->Write();

  VemSize                ->Write();
  VepSize                ->Write();
  Vem_ep_PID_ME          ->Write();
  PairSize               ->Write();

  fh_mass_ep_em->Write();
  fh_mass_ep_ep->Write();
  fh_mass_em_em->Write();

fh_mass_ep_em_effCorr  ->Write();
fh_mass_ep_ep_effCorr  ->Write();
fh_mass_em_em_effCorr  ->Write();

fh_mass_ep_em_mixedEvents->Write();
fh_mass_ep_ep_mixedEvents->Write();
fh_mass_em_em_mixedEvents->Write();

fh_mass_ep_em_mixedEvents_effCorr->Write();
fh_mass_ep_ep_mixedEvents_effCorr->Write();
fh_mass_em_em_mixedEvents_effCorr->Write();

  // h_epem_oAngle9_mass_pt->Write();
  // h_epem_oAngle9_mass_p->Write();
  // h_epem_oAngle9_mass_oAngle->Write();

  // h_epep_oAngle9_mass_pt->Write();
  // h_epep_oAngle9_mass_p->Write();
  // h_epep_oAngle9_mass_oAngle->Write();

  // h_emem_oAngle9_mass_pt->Write();
  // h_emem_oAngle9_mass_p->Write();
  // h_emem_oAngle9_mass_oAngle->Write();

  out->Close();

  sorter.finalize();
  delete gHades;
  return 0;
}
