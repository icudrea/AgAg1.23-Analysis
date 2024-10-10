//----------------------------------------------------------------------------
void setOPT_canvas( TCanvas* canvas )
{
    gStyle->SetOptStat(0);
    gStyle->SetEndErrorSize(5);
    gStyle->SetErrorX(0);    // X errors of the data points set to be 0
    gStyle->SetLineStyleString(22,"80 18 12 18 12 12"); // special style for the line
    gStyle->SetEndErrorSize(5);   // define end width of error bars
    gStyle->SetCanvasColor(10);
    gStyle->SetPadColor(10);
    
    canvas->SetLeftMargin(0.15);
    canvas->SetRightMargin(0.05);
    canvas->SetTopMargin(0.08);
    canvas->SetBottomMargin(0.10);
    
    canvas->ToggleEventStatus();
    canvas->Range(-200,-10,1000,-2);
    canvas->SetFillColor(0);
    canvas->SetBorderMode(0);
    canvas->SetBorderSize(0);
    canvas->SetTickx();
    canvas->SetTicky();
    canvas->SetFrameLineWidth(2);
    canvas->SetFrameBorderMode(0);
    canvas->SetFrameBorderSize(0);
}
//----------------------------------------------------------------------------
void setOPT_TH1F( TH1* hist, TString xAxisTitle="", TString yAxisTitle="", Int_t Ndevision=510,
                   Int_t marker_style =20, Float_t marker_size =1.3,
                   Int_t color=1 )
{
    if(xAxisTitle!="") hist->GetXaxis()->SetTitle(xAxisTitle);
    if(yAxisTitle!="") hist->GetYaxis()->SetTitle(yAxisTitle);
    hist->GetXaxis()->SetTitleSize(0.05);
    hist->GetYaxis()->SetTitleSize(0.05);
    hist->GetXaxis()->SetTitleFont(42);
    hist->GetYaxis()->SetTitleFont(42);
    hist->GetXaxis()->SetNdivisions(Ndevision);
    hist->GetYaxis()->SetNdivisions(Ndevision);
    hist->GetXaxis()->SetTitleOffset(0.9);
    hist->GetYaxis()->SetTitleOffset(0.95);
    //hist->GetXaxis()->CenterTitle();
    //hist->GetYaxis()->CenterTitle();
    hist->GetXaxis()->SetLabelFont(42);
    hist->GetYaxis()->SetLabelFont(42);
    hist->GetXaxis()->SetLabelSize(0.04);
    hist->GetYaxis()->SetLabelSize(0.04);
    hist->SetMarkerStyle(marker_style);
    hist->SetMarkerSize(marker_size);
    hist->SetMarkerColor(color);
    hist->SetLineColor(color);
    hist->SetTitle("");
    hist->SetLineWidth(3);
}
//----------------------------------------------------------------------------
void setOPT_canvas2D( TCanvas *canvas )
{
    gStyle->SetOptStat(0);
    gStyle->SetEndErrorSize(5);
    gStyle->SetErrorX(0);    // X errors of the data points set to be 0
    gStyle->SetLineStyleString(22,"80 18 12 18 12 12"); // special style for the line
    gStyle->SetEndErrorSize(5);   // define end width of error bars
    gStyle->SetCanvasColor(10);
    gStyle->SetPadColor(10);

    canvas->SetLeftMargin(0.25);
    canvas->SetRightMargin(0.25);
    canvas->SetTopMargin(0.1);
    canvas->SetBottomMargin(0.13);

    canvas->ToggleEventStatus();
    canvas->Range(-200,-10,1000,-2);
    canvas->SetFillColor(0);
    canvas->SetBorderMode(0);
    canvas->SetBorderSize(0);
    canvas->SetTickx();
    canvas->SetTicky();
    canvas->SetFrameLineWidth(2);
    canvas->SetFrameBorderMode(0);
    canvas->SetFrameBorderSize(0);
}
//----------------------------------------------------------------------------
  void setOPT_hists2D(TH2D *hist, TString xAxisTitle=" ", TString yAxisTitle=" ", Int_t NCont=255, Int_t Ndevision=510)
    {
        hist->GetXaxis()->SetTitle(xAxisTitle);
        hist->GetYaxis()->SetTitle(yAxisTitle);
        hist->GetXaxis()->SetTitleSize(0.06);
        hist->GetYaxis()->SetTitleSize(0.06);
        hist->GetXaxis()->SetTitleFont(42);
        hist->GetYaxis()->SetTitleFont(42);
        hist->GetXaxis()->SetNdivisions(Ndevision);
        hist->GetYaxis()->SetTitleOffset(1);
        //hist->GetXaxis()->CenterTitle();
        //hist->GetYaxis()->CenterTitle();
        hist->GetXaxis()->SetLabelFont(42);
        hist->GetYaxis()->SetLabelFont(42);
        hist->GetXaxis()->SetLabelSize(0.04);
        hist->GetYaxis()->SetLabelSize(0.04);
        hist->SetTitle("");
        hist->SetLineWidth(2);
            

        Int_t MyPalette[100];
        const Int_t NRGBs = 5;
        Double_t stops[NRGBs] = { 0.00, 0.34, 0.61, 0.84, 1.00 };
        Double_t reds[NRGBs] = { 0.00, 0.00, 0.87, 1.00, 0.51 };
        Double_t greens[NRGBs] = { 0.00, 0.81, 1.00, 0.20, 0.00 };
        Double_t blues[NRGBs] = { 0.51, 1.00, 0.12, 0.00, 0.00 };
        Int_t FI = TColor::CreateGradientColorTable(NRGBs, stops, reds,greens, blues, NCont);
    

    gStyle->SetNumberContours(NCont);



    }
//----------------------------------------------------------------------------

//----------------------------------------------------------------------------
void setTextfield( float x, float y, TString text ) {
    TLatex* tex = new TLatex( x, y, text );
    tex->SetTextFont( 42 );
    tex->SetTextSize( 0.04 );
    tex->SetTextColorAlpha( kBlack, 1. );
    //tex->SetLineWidth( 3 );
    tex->Draw();
}

void setTextfield_big( float x, float y, TString text ) {
    TLatex* tex = new TLatex( x, y, text );
    tex->SetTextFont( 42 );
    tex->SetTextSize( 0.045 );
    tex->SetTextColorAlpha( kBlack, 1. );
    //tex->SetLineWidth( 3 );
    tex->Draw();
}

TLatex* setTextfieldTex( float x, float y, TString text ) {
    TLatex* tex = new TLatex( x, y, text );
    tex->SetTextFont( 42 );
    tex->SetTextSize( 0.03 );
    tex->SetTextColorAlpha( kBlack, 1 );
    tex->Draw();

    return tex;
}

void setLegend5( char* cH1,TH1* h1,
                char* cH2, TH1* h2,
                char* cH3, TH1* h3,
                char* cH4, TH1* h4,
                char* cH5, TH1* h5
                )
{
    TLegend *leg = new TLegend( 0.44, 0.72, 0.64, 0.94 );
    leg->SetLineColor(10);
    leg->SetLineStyle(1);
    leg->SetLineWidth(1);
    leg->SetFillColor(10);
    leg->SetTextSize(0.02);
    leg->SetTextFont(62);
    leg->SetMargin(0.4);
    leg->SetBorderSize(0);
    if( h1 ) leg->AddEntry( h1, cH1, "l" );
    if( h2 ) leg->AddEntry( h2, cH2, "p" );
    if( h3 ) leg->AddEntry( h3, cH3, "p" );
    if( h4 ) leg->AddEntry( h4, cH4, "p" );
    if( h5 ) leg->AddEntry( h5, cH5, "p" );

    leg->Draw( "same" );
}


void setLegend( char* cH1, TH1* h1,
                char* cH2, TH1* h2,
                char* cH3, TH1* h3,
                char* cH4, TH1* h4,
                char* cH5, TH1* h5,
                char* cH6, TH1* h6,
                char* cH7, TH1* h7,
                float x1 = 0.6, float y1 = 0.6,
                float x2 = 0.8, float y2 = 0.9,
                float textsize = 0.035
                )
{
    TLegend *leg = new TLegend( x1, y1, x2, y2 );
    leg->SetLineColor(10);
    leg->SetLineStyle(1);
    leg->SetLineWidth(1);
    leg->SetFillColor(10);
    leg->SetTextSize( textsize );
    leg->SetTextFont(62);
    leg->SetMargin(0.4);
    leg->SetBorderSize(0);
    if( h1 ) leg->AddEntry( h1, cH1, "l" );
    if( h2 ) leg->AddEntry( h2, cH2, "l" );
    if( h3 ) leg->AddEntry( h3, cH3, "l" );
    if( h4 ) leg->AddEntry( h4, cH4, "l" );
    if( h5 ) leg->AddEntry( h5, cH5, "l" );
    if( h6 ) leg->AddEntry( h6, cH6, "l" );
    if( h7 ) leg->AddEntry( h7, cH7, "l" );
    leg->Draw( "same" );
}


void setLegend( char* cH1, TH1* h1,
                char* cH2, TH1* h2,
                char* cH3, TH1* h3,
                char* cH4, TH1* h4,
                char* cH5, TH1* h5,
                char* cH6, TH1* h6,
                char* cH7, TH1* h7,
                char* cH8, TH1* h8,
                float x1 = 0.6, float y1 = 0.6,
                float x2 = 0.8, float y2 = 0.9,
                float textsize = 0.035
                )
{
    TLegend *leg = new TLegend( x1, y1, x2, y2 );
    leg->SetLineColor(10);
    leg->SetLineStyle(1);
    leg->SetLineWidth(1);
    leg->SetFillColor(10);
    leg->SetTextSize( textsize );
    leg->SetTextFont(62);
    leg->SetMargin(0.4);
    leg->SetBorderSize(0);
    if( h1 ) leg->AddEntry( h1, cH1, "l" );
    if( h2 ) leg->AddEntry( h2, cH2, "l" );
    if( h3 ) leg->AddEntry( h3, cH3, "l" );
    if( h4 ) leg->AddEntry( h4, cH4, "l" );
    if( h5 ) leg->AddEntry( h5, cH5, "l" );
    if( h6 ) leg->AddEntry( h6, cH6, "l" );
    if( h7 ) leg->AddEntry( h7, cH7, "l" );
    if( h8 ) leg->AddEntry( h8, cH8, "l" );
    leg->Draw( "same" );
}

void setLegend( char* cH1, TH1* h1,
                char* cH2, TH1* h2,
                float x1 = 0.6, float y1 = 0.6,
                float x2 = 0.8, float y2 = 0.9
                )
{
    TLegend *leg = new TLegend( x1, y1, x2, y2 );
    leg->SetLineColor(10);
    leg->SetLineStyle(1);
    leg->SetLineWidth(1);
    leg->SetFillColor(10);
    leg->SetTextSize(0.035);
    leg->SetTextFont(62);
    leg->SetMargin(0.4);
    leg->SetBorderSize(0);
    if( h1 ) leg->AddEntry( h1, cH1, "l" );
    if( h2 ) leg->AddEntry( h2, cH2, "l" );
    leg->Draw( "same" );
}
//----------------------------------------------------------------------------
void setLegend2( char* cH1, TH1* h1,
                char* cH2, TH1* h2
               
            
                )
{
    TLegend *leg = new TLegend(0.58, 0.54, 0.69, 0.64);
    leg->SetLineColor(10);
    leg->SetLineStyle(1);
    leg->SetLineWidth(1);
    leg->SetFillColor(10);
    leg->SetTextSize( 0.035 );
    leg->SetTextFont(42);
    leg->SetMargin(0.4);
    leg->SetBorderSize(0);
    if( h1 ) leg->AddEntry( h1, cH1, "l" );
    if( h2 ) leg->AddEntry( h2, cH2, "p" );
  
    leg->Draw( "same" );
}
//----------------------------------------------------------------------------
void setLegend(char* cH1, TH1* h1

		
	       )
{
    TLegend *legmass = new TLegend(0.34, 0.78, 0.45, 0.88);
    legmass->SetLineColor(10);
    legmass->SetLineStyle(1);
    legmass->SetLineWidth(1);
    legmass->SetFillColor(10);
    legmass->SetTextSize(0.035);
    legmass->SetTextFont(42);
    legmass->SetMargin(0.4);
    legmass->SetBorderSize(0);
    if (h1) legmass->AddEntry(h1,cH1,"pl");
  
    legmass->Draw("same");
}

// To add text and labels in the plots
void setHadesWorkInProgress()
{
    TLatex* tex = new TLatex(0.3, 5e-4,"HADES Work In Progress");
    tex->SetTextFont(42);
    tex->SetTextSize(0.04);
    tex->SetLineWidth(3);
    tex->Draw();
}
void setMainTitle()
{
    TLatex* tex = new TLatex(0.3, 2e-4,"Ag+Ag #sqrt{s_{NN}}=2.55 GeV 0-40%");
    tex->SetTextFont(42);
    tex->SetTextSize(0.04);
    tex->SetLineWidth(3);
    tex->Draw();
}

void setMomTitle()
{
    TLatex* tex2 = new TLatex(0.3,6e-5,"100 GeV/#font[52]{c} < #font[52]{p}_{ee} < 1800 GeV/#font[52]{c}");
    tex2->SetTextFont(42);
    tex2->SetTextSize(0.04);
    tex2->SetLineWidth(3);
    tex2->Draw();
}

void ep()
{
    TLatex* tex3 = new TLatex(0.3, 2e-4,"e^{+}");
    tex3->SetTextFont(42);
    tex3->SetTextSize(0.04);
    tex3->SetLineWidth(3);
    tex3->Draw();
}
void em()
{
    TLatex* tex3 = new TLatex(0.3, 2e-4,"e^{-}");
    tex3->SetTextFont(42);
    tex3->SetTextSize(0.04);
    tex3->SetLineWidth(3);
    tex3->Draw();
}