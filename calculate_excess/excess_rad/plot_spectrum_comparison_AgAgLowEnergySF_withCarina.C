#include "plot_style.C"
#include "data_agag123.C"


void plot_spectrum_comparison_AgAgLowEnergySF_withCarina( TString collsys = "AgAg1.23_cent0to40", bool restrictedRange = false ) {	

	TH1D* h1_inmed_sum_m   = nullptr;
	TH1D* h1_inmed_rho_m   = nullptr;
	TH1D* h1_inmed_omega_m = nullptr;
	TH1D* h1_inmed_phi_m   = nullptr;
	TH1D* h1_cont_m        = nullptr;

	TString infileName;
	TFile* infile;

	if( collsys == "AgAg1.23_cent0to40" ) {
		TString collsys_part[ 4 ];
		collsys_part[ 0 ] = "AgAg1.23_cent0to10";
		collsys_part[ 1 ] = "AgAg1.23_cent10to20";
		collsys_part[ 2 ] = "AgAg1.23_cent20to30";
		collsys_part[ 3 ] = "AgAg1.23_cent30to40";

		for( int i=0; i<4; i++ ) {
			infileName = "~/lustre/hades/user/fseck/dilepton-omega/output_SFpol_par_dilepton_yield_mpty_" + collsys_part[ i ] + ".root";
			infile = new TFile( infileName, "READ" );

			if( !h1_inmed_rho_m ) {
				cout << i << "  --> creating hist" << endl;

				h1_inmed_sum_m   = ( TH1D* ) infile->Get( "h1_inmed_sum_m"   );
				h1_inmed_rho_m   = ( TH1D* ) infile->Get( "h1_inmed_rho_m"   );
				h1_inmed_omega_m = ( TH1D* ) infile->Get( "h1_inmed_omega_m" );
				h1_inmed_phi_m   = ( TH1D* ) infile->Get( "h1_inmed_phi_m"   );
				h1_cont_m        = ( TH1D* ) infile->Get( "h1_cont_m"        );
			}
			else {
				cout << i << "  --> adding hist" << endl;

				h1_inmed_sum_m  ->Add( ( TH1D* ) infile->Get( "h1_inmed_sum_m"   ) );
				h1_inmed_rho_m  ->Add( ( TH1D* ) infile->Get( "h1_inmed_rho_m"   ) );
				h1_inmed_omega_m->Add( ( TH1D* ) infile->Get( "h1_inmed_omega_m" ) );
				h1_inmed_phi_m  ->Add( ( TH1D* ) infile->Get( "h1_inmed_phi_m"   ) );
				h1_cont_m       ->Add( ( TH1D* ) infile->Get( "h1_cont_m"        ) );
			}
		}

		h1_inmed_sum_m  ->Scale( 0.25 );
		h1_inmed_rho_m  ->Scale( 0.25 );
		h1_inmed_omega_m->Scale( 0.25 );
		h1_inmed_phi_m  ->Scale( 0.25 );
		h1_cont_m       ->Scale( 0.25 );
	}
	else {
		infileName = "~/lustre/hades/user/fseck/dilepton-omega/output_SFpol_par_dilepton_yield_mpty_" + collsys + ".root";
		infile = new TFile( infileName, "READ" );

		cout << " reading hist" << endl;

		h1_inmed_sum_m   = ( TH1D* ) infile->Get( "h1_inmed_sum_m"   );
		h1_inmed_rho_m   = ( TH1D* ) infile->Get( "h1_inmed_rho_m"   );
		h1_inmed_omega_m = ( TH1D* ) infile->Get( "h1_inmed_omega_m" );
		h1_inmed_phi_m   = ( TH1D* ) infile->Get( "h1_inmed_phi_m"   );
		h1_cont_m        = ( TH1D* ) infile->Get( "h1_cont_m"        );

	}


	double nPion = 1.;

	if( collsys.Contains( "AgAg" ) && collsys.Contains( "cent0to10"  ) ) nPion = 8.22;
	if( collsys.Contains( "AgAg" ) && collsys.Contains( "cent10to20" ) ) nPion = 5.90;
	if( collsys.Contains( "AgAg" ) && collsys.Contains( "cent20to30" ) ) nPion = 4.13;
	if( collsys.Contains( "AgAg" ) && collsys.Contains( "cent30to40" ) ) nPion = 2.82;
	if( collsys.Contains( "AgAg" ) && collsys.Contains( "cent0to40"  ) ) nPion = 5.26;


	h1_inmed_sum_m  ->Scale( 1. / nPion );
	h1_inmed_rho_m  ->Scale( 1. / nPion );
	h1_inmed_omega_m->Scale( 1. / nPion );
	h1_inmed_phi_m  ->Scale( 1. / nPion );
	h1_cont_m       ->Scale( 1. / nPion );

	for( int i=0; i<h1_inmed_sum_m->GetNbinsX(); i++ ) {
		h1_inmed_sum_m  ->SetBinError( i+1, 0. );
		h1_inmed_rho_m  ->SetBinError( i+1, 0. );
		h1_inmed_omega_m->SetBinError( i+1, 0. );
		h1_inmed_phi_m  ->SetBinError( i+1, 0. );
		h1_cont_m       ->SetBinError( i+1, 0. );
	}

	TString ions;
	TString roots;
	TString cent;

	if( collsys.Contains( "AgAg" ) ) ions = "Ag+Ag";

	if( collsys.Contains( "1.23" ) ) roots = "2.42";

	if( collsys.Contains( "cent0to10"  ) ) cent = "0-10";
	if( collsys.Contains( "cent10to20" ) ) cent = "10-20";
	if( collsys.Contains( "cent20to30" ) ) cent = "20-30";
	if( collsys.Contains( "cent30to40" ) ) cent = "30-40";
	if( collsys.Contains( "cent0to40"  ) ) cent = "0-40";


	setOPT_hists( h1_inmed_rho_m, "#it{M}_{ee} (GeV/#it{c}^{2})", "1/N_{#pi^{0}} dN^{4#pi}/d#it{M}_{ee} (GeV/#it{c}^{2})^{-1}" );

	h1_inmed_rho_m->GetXaxis()->SetRangeUser( 0.01, 1.1 );

	h1_inmed_rho_m->SetMinimum( 1.e-10 );
	h1_inmed_rho_m->SetMaximum( 8.e-2 );

	if( restrictedRange ) {
		h1_inmed_rho_m->GetXaxis()->SetRangeUser( 0.16, 0.74 );

		h1_inmed_rho_m->SetMinimum( 2.e-7 );
		h1_inmed_rho_m->SetMaximum( 5.e-3 );
	}

	h1_inmed_sum_m  ->SetLineColor( kMagenta+2 );
	h1_inmed_rho_m  ->SetLineColor( kBlue+1    );
	h1_inmed_omega_m->SetLineColor( kGreen  +1 );
	h1_inmed_phi_m  ->SetLineColor( kCyan   +1 );
	h1_cont_m       ->SetLineColor( kOrange +1 );

	h1_inmed_sum_m  ->SetLineWidth( 3 );
	h1_inmed_rho_m  ->SetLineWidth( 3 );
	h1_inmed_omega_m->SetLineWidth( 3 );
	h1_inmed_phi_m  ->SetLineWidth( 3 );
	h1_cont_m       ->SetLineWidth( 3 );


    TCanvas* c = new TCanvas( "c", "", 900, 900 );
    setOPT_canvas( c );
    c->SetLogy();

    gStyle->SetEndErrorSize( 3 );
    gStyle->SetErrorX( 0. );

	h1_inmed_rho_m  ->Draw( "c" );
	//h1_inmed_omega_m->Draw( "c same" );
	//h1_inmed_phi_m  ->Draw( "c same" );
	//h1_cont_m       ->Draw( "c same" );
	//h1_inmed_sum_m  ->Draw( "c same" );

/*
	setLegend( ( char* ) "sum",           h1_inmed_sum_m,
			   ( char* ) "inmed. #rho",   h1_inmed_rho_m,
			   ( char* ) "inmed. #omega", h1_inmed_omega_m,
			   ( char* ) "inmed. #phi",   h1_inmed_phi_m,
			   ( char* ) "cont.",         h1_cont_m,
			   0.7, 0.7, 0.9, 0.9, ( char* ) "l"
			 );
*/

    TGraphMultiErrors* g;
    if( collsys.Contains( "cent0to40"  ) ) g = data_agag123( "0to40"  );
    if( collsys.Contains( "cent0to10"  ) ) g = data_agag123( "0to10"  );
    if( collsys.Contains( "cent10to20" ) ) g = data_agag123( "10to20" );
    if( collsys.Contains( "cent20to30" ) ) g = data_agag123( "20to30" );
    if( collsys.Contains( "cent30to40" ) ) g = data_agag123( "30to40" );

    g->SetMarkerStyle( 21 );
    g->SetMarkerSize( 1.3 );
    g->SetLineColor( kBlack );
    g->SetLineWidth( 0 );
    g->GetAttLine( 0 )->SetLineColor( kBlack );
    g->GetAttLine( 0 )->SetLineWidth( 2 );
    g->GetAttLine( 1 )->SetLineColor( kBlack );
    g->GetAttLine( 1 )->SetLineWidth( 2 );
    g->GetAttFill( 1 )->SetFillColorAlpha( kOrange, 0.3 );

    g->Draw( "PE1SSame; 5 s=1.0" );
    gStyle->SetEndErrorSize( 0 );


    TGraphMultiErrors* g_carina;
    if( collsys.Contains( "cent0to40"  ) ) g_carina = data_agag123_carina( "0to40" );

    g_carina->SetMarkerStyle( 20 );
    g_carina->SetMarkerSize( 1.5 );
    g_carina->SetLineColor( kRed + 1 );
    g_carina->SetMarkerColor( kRed + 1);
    g_carina->SetLineColor( kRed + 1 );
    g_carina->SetLineWidth( 0 );
    g_carina->GetAttLine( 0 )->SetLineColor( kRed + 1 );
    g_carina->GetAttLine( 0 )->SetLineWidth( 2 );

    g_carina->Draw( "pe1ssame" );



    h1_inmed_rho_m->Draw( "c same" );


/*
    TF1* f;
    if( collsys.Contains( "cent0to40"  ) ) f = fit_agag123( "0to40"  );
    if( collsys.Contains( "cent0to10"  ) ) f = fit_agag123( "0to10"  );
    if( collsys.Contains( "cent10to20" ) ) f = fit_agag123( "10to20" );
    if( collsys.Contains( "cent20to30" ) ) f = fit_agag123( "20to30" );
    if( collsys.Contains( "cent30to40" ) ) f = fit_agag123( "30to40" );

    f->SetLineColor( kRed+1 );
    f->SetLineWidth( 3 );
    f->Draw( "same" );


*/

    TLatex* tex = new TLatex();
    tex->SetTextFont( 42 );
    tex->SetTextSize( 0.03 );
    tex->SetLineWidth( 3 );

	tex->DrawLatexNDC( 0.2, 0.25, "Ag+Ag   #sqrt{s_{NN}} = 2.42 GeV   0-40%" );
	tex->DrawLatexNDC( 0.2, 0.20, "HADES work in progress" );
	//tex->DrawLatexNDC( 0.45, 0.75, "Cocktail + measured NN sub." );

    // TLatex* tex2 = new TLatex();
    // tex2->SetTextFont( 42 );
    // tex2->SetTextColor( kRed+1 );
    // tex2->SetTextSize( 0.03 );
    // tex2->SetLineWidth( 3 );
	// tex2->DrawLatexNDC( 0.45, 0.70, Form("k_{B}T = %4.2f #pm 1.5_{stat} #pm 4.0_{sys} MeV", 1000 / f->GetParameter( 1 ) ) );

	setLegend( ( char* ) "Data (stand. ana.), Cocktail + measured NN sub.", g, ( char* ) "pe",
			   ( char* ) "Data (this work), stat. errors only, Cocktail sub.", g_carina, ( char* ) "pe",		
			   ( char* ) "in-medium #rho spectral function", h1_inmed_rho_m, ( char* ) "l",
			   0.25, 0.75, 0.45, 0.85
			 );

	// if( restrictedRange ) c->SaveAs( "AgAg1.23_NoPionsInCocktail_zoom.pdf" );
	// else                  c->SaveAs( "AgAg1.23_NoPionsInCocktail_full.pdf" );

}
