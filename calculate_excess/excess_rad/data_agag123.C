
TGraphMultiErrors* data_agag123( TString cent = "0to40" ) {

	vector< double > massbins;
	vector< double > mass_width;
	vector< double > yield;

	vector< double > staterror;
	vector< double > syserror;


	TFile* infile = new TFile( "data_agag1.23/ag1230ag_final_forFlorian.root" );

	TString cc;
	if( cent == "0to40"  ) cc = "CCTotal";
	if( cent == "0to10"  ) cc = "CC1";
	if( cent == "10to20" ) cc = "CC2";
	if( cent == "20to30" ) cc = "CC3";
	if( cent == "30to40" ) cc = "CC4";

	TH1D* h     = ( TH1D* ) infile->Get( "InvMass_" + cc );
	TH1D* h_sys = ( TH1D* ) infile->Get( "InvMassSys_" + cc );

	// data
	for( int i=0; i<h->GetNbinsX(); i++ ) {
		massbins.  push_back( h->GetBinCenter( i+1 )      );
		mass_width.push_back( h->GetBinWidth( i+1 ) * 0.5 );
		yield.     push_back( h->GetBinContent( i+1 )     );
		staterror. push_back( h->GetBinError( i+1 )       );
		syserror.  push_back( h_sys->GetBinError( i+1 )   );
	}

	auto g = new TGraphMultiErrors( "g", "", massbins.size(), massbins.data(), yield.data(), mass_width.data(), mass_width.data(), staterror.data(), staterror.data() );
    g->AddYError( massbins.size(), syserror.data(), syserror.data() );
    // g->SetMarkerStyle(20);
    // g->SetMarkerSize(1);
    // g->SetLineColor(kBlack);
    // g->SetLineWidth(0);
    // g->GetAttLine(0)->SetLineColor(kBlack);
    // g->GetAttLine(0)->SetLineWidth(2);
    // g->GetAttLine(1)->SetLineColor(kBlue);
    // g->GetAttLine(1)->SetLineWidth(2);
    // g->GetAttFill(1)->SetFillStyle(0);
    // g->GetXaxis()->SetTitle("#it{M}_{ee} (GeV/#it{c}^{2})");
    // g->GetYaxis()->SetTitle("1/N_{#pi^{0}} dN^{4#pi}/d#it{M}_{ee} (GeV/#it{c}^{2})^{-1}");
    // g->Draw("APE1S ;  5 s=0.8");

	// gStyle->SetEndErrorSize( 0 );
    
    // g->SetMaximum(5e-3);
    // g->SetMinimum(1e-8);
    // g->GetXaxis()->SetRangeUser( 0.16, 0.94 );

    // g->GetXaxis()->SetLabelFont(42);
    // g->GetXaxis()->SetLabelSize(0.05);
    // g->GetXaxis()->SetTitleSize(0.06);
    // g->GetXaxis()->SetTitleOffset(0.95);
    // g->GetXaxis()->SetTitleFont(42);
    // g->GetYaxis()->SetLabelFont(42);
    // g->GetYaxis()->SetLabelSize(0.05);
    // g->GetYaxis()->SetLabelSize(0.05);
    // g->GetYaxis()->SetTitleSize(0.06);
    // g->GetYaxis()->SetTitleOffset(1.1);
    // g->GetYaxis()->SetTitleFont(42);

    return g;
}

TF1* fit_agag123( TString cent = "0to40" ) {

	TFile* infile = new TFile( "data_agag1.23/ag1230ag_final_forFlorian.root" );

	TString cc;
	if( cent == "0to40"  ) cc = "CCTotal";
	if( cent == "0to10"  ) cc = "CC1";
	if( cent == "10to20" ) cc = "CC2";
	if( cent == "20to30" ) cc = "CC3";
	if( cent == "30to40" ) cc = "CC4";

	TF1* f = ( TF1* ) infile->Get( "Fit_" + cc );

    return f;
}



TGraphMultiErrors* data_agag123_carina( TString cent = "0to40" ) {

	vector< double > massbins;
	vector< double > mass_width;
	vector< double > yield;

	vector< double > staterror;
	//vector< double > syserror;


	TFile* infile = new TFile( "data_agag1.23/AccCorr_excess_Rebin_NoPionv2.root" );

	TString cc;
	if( cent == "0to40"  ) cc = "CCTotal";
	if( cent == "0to10"  ) cc = "CC1";
	if( cent == "10to20" ) cc = "CC2";
	if( cent == "20to30" ) cc = "CC3";
	if( cent == "30to40" ) cc = "CC4";

	TH1D* h     = ( TH1D* ) infile->Get( "h_ExcessAccCorr" );
	//TH1D* h_sys = ( TH1D* ) infile->Get( "" );

	// for( int i=0; i<h->GetNbinsX(); i++ ) {
	// 	h->SetBinError( i+1, h->GetBinError( i+1 ) / h->GetBinWidth( i+1 ) );
	// }


	// data
	for( int i=0; i<h->GetNbinsX(); i++ ) {
		massbins.  push_back( h->GetBinCenter( i+1 )      );
		mass_width.push_back( h->GetBinWidth( i+1 ) * 0.5 );
		yield.     push_back( h->GetBinContent( i+1 )     );
		staterror. push_back( h->GetBinError( i+1 )       );
		//syserror.  push_back( h_sys->GetBinError( i+1 )   );
	}

	auto g = new TGraphMultiErrors( "g", "", massbins.size(), massbins.data(), yield.data(), mass_width.data(), mass_width.data(), staterror.data(), staterror.data() );
    //g->AddYError( massbins.size(), syserror.data(), syserror.data() );
    // g->SetMarkerStyle(20);
    // g->SetMarkerSize(1);
    // g->SetLineColor(kCyan);
    // g->SetMarkerColor(kCyan);
    // g->SetLineWidth(0);
    // g->GetAttLine(0)->SetLineColor(kBlack);
    // g->GetAttLine(0)->SetLineWidth(2);
    // g->GetAttLine(1)->SetLineColor(kBlue);
    // g->GetAttLine(1)->SetLineWidth(2);
    // g->GetAttFill(1)->SetFillStyle(0);
    // g->GetXaxis()->SetTitle("#it{M}_{ee} (GeV/#it{c}^{2})");
    // g->GetYaxis()->SetTitle("1/N_{#pi^{0}} dN^{4#pi}/d#it{M}_{ee} (GeV/#it{c}^{2})^{-1}");
    // g->Draw("APE1S ;  5 s=0.8");

	// gStyle->SetEndErrorSize( 0 );
    
    // g->SetMaximum(5e-3);
    // g->SetMinimum(1e-8);
    // g->GetXaxis()->SetRangeUser( 0.16, 0.94 );

    // g->GetXaxis()->SetLabelFont(42);
    // g->GetXaxis()->SetLabelSize(0.05);
    // g->GetXaxis()->SetTitleSize(0.06);
    // g->GetXaxis()->SetTitleOffset(0.95);
    // g->GetXaxis()->SetTitleFont(42);
    // g->GetYaxis()->SetLabelFont(42);
    // g->GetYaxis()->SetLabelSize(0.05);
    // g->GetYaxis()->SetLabelSize(0.05);
    // g->GetYaxis()->SetTitleSize(0.06);
    // g->GetYaxis()->SetTitleOffset(1.1);
    // g->GetYaxis()->SetTitleFont(42);

    return g;
}