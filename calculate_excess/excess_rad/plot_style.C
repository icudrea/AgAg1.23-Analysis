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
void setOPT_hists( TH1* hist, TString xAxisTitle="", TString yAxisTitle="", Int_t Ndevision=510,
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
    hist->GetYaxis()->SetTitleOffset(1.3);
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

    canvas->SetLeftMargin(0.12);
    canvas->SetRightMargin(0.17);
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
void setOPT_hists2D(TH2* hist, TString xAxisTitle="", TString yAxisTitle="", Int_t NCont=255, Int_t Ndevision=510)
{
    if(xAxisTitle!="") hist->GetXaxis()->SetTitle(xAxisTitle);
    if(yAxisTitle!="") hist->GetYaxis()->SetTitle(yAxisTitle);
    hist->GetXaxis()->SetTitleSize(0.04);
    hist->GetYaxis()->SetTitleSize(0.04);
    hist->GetZaxis()->SetTitleSize(0.04);
    hist->GetXaxis()->SetTitleFont(42);
    hist->GetYaxis()->SetTitleFont(42);
    hist->GetZaxis()->SetTitleFont(42);
    hist->GetXaxis()->SetNdivisions(Ndevision);
    hist->GetXaxis()->SetTitleOffset(1.1);
    hist->GetYaxis()->SetTitleOffset(1.15);
    hist->GetZaxis()->SetTitleOffset(1.2);
    hist->GetXaxis()->SetLabelFont(42);
    hist->GetYaxis()->SetLabelFont(42);
    hist->GetZaxis()->SetLabelFont(42);
    hist->GetXaxis()->SetLabelSize(0.04);
    hist->GetYaxis()->SetLabelSize(0.04);
    hist->GetZaxis()->SetLabelSize(0.04);
    hist->SetTitle("");

    gStyle->SetPalette( kRainBow );
    /*
    Int_t MyPalette[100];
    
    const    Int_t NRGBs   = 5;
    Double_t stops [NRGBs] = { 0.00, 0.34, 0.61, 0.84, 1.00 };
    Double_t reds  [NRGBs] = { 0.00, 0.00, 0.87, 1.00, 0.51 };
    Double_t greens[NRGBs] = { 0.00, 0.81, 1.00, 0.20, 0.00 };
    Double_t blues [NRGBs] = { 0.51, 1.00, 0.12, 0.00, 0.00 };
    */

    //const    Int_t NRGBs   = 3;
    //Double_t stops [NRGBs] = { 0.00, 0.35, 1.00 };
    //Double_t reds  [NRGBs] = { 0.00, 1.00, 0.75 };
    //Double_t greens[NRGBs] = { 0.00, 1.00, 0.00 };
    //Double_t blues [NRGBs] = { 0.75, 1.00, 0.00 };

    //Int_t FI = TColor::CreateGradientColorTable( NRGBs, stops, reds, greens, blues, NCont );

    //gStyle->SetNumberContours(NCont);
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



void setLegend( char* cH1, TH1F* h1,
                char* cH2, TH1F* h2,
                char* cH3, TH1F* h3,
                char* cH4, TH1F* h4,
                char* cH5, TH1F* h5,
                char* cH6, TH1F* h6,
                char* cH7, TH1F* h7,
                char* cH8, TH1F* h8,
                float x1 = 0.6, float y1 = 0.6,
                float x2 = 0.8, float y2 = 0.9
                )
{
    TLegend *leg = new TLegend( x1, y1, x2, y2 );
    leg->SetLineColor(10);
    leg->SetLineStyle(1);
    leg->SetLineWidth(1);
    leg->SetFillColor(10);
    leg->SetTextSize(0.028);
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

void setLegend( char* cH1, TH1F* h1,
                char* cH2, TH1F* h2,
                char* cH3, TH1F* h3,
                char* cH4, TH1F* h4,
                char* cH5, TH1F* h5,
                char* cH6, TH1F* h6,
                char* cH7, TH1F* h7,
                float x1 = 0.6, float y1 = 0.6,
                float x2 = 0.8, float y2 = 0.9
                )
{
    TLegend *leg = new TLegend( x1, y1, x2, y2 );
    leg->SetLineColor(10);
    leg->SetLineStyle(1);
    leg->SetLineWidth(1);
    leg->SetFillColor(10);
    leg->SetTextSize(0.028);
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

void setLegend( char* cH1, TH1F* h1,
                char* cH2, TH1F* h2,
                char* cH3, TH1F* h3,
                char* cH4, TH1F* h4,
                char* cH5, TH1F* h5,
                char* cH6, TH1F* h6,
                float x1 = 0.6, float y1 = 0.6,
                float x2 = 0.8, float y2 = 0.9
                )
{
    TLegend *leg = new TLegend( x1, y1, x2, y2 );
    leg->SetLineColor(10);
    leg->SetLineStyle(1);
    leg->SetLineWidth(1);
    leg->SetFillColor(10);
    leg->SetTextSize(0.028);
    leg->SetTextFont(62);
    leg->SetMargin(0.4);
    leg->SetBorderSize(0);
    if( h1 ) leg->AddEntry( h1, cH1, "l" );
    if( h2 ) leg->AddEntry( h2, cH2, "l" );
    if( h3 ) leg->AddEntry( h3, cH3, "l" );
    if( h4 ) leg->AddEntry( h4, cH4, "l" );
    if( h5 ) leg->AddEntry( h5, cH5, "l" );
    if( h6 ) leg->AddEntry( h6, cH6, "l" );
    leg->Draw( "same" );
}

void setLegend( char* cH1, TH1* h1,
                char* cH2, TH1* h2,
                char* cH3, TH1* h3,
                char* cH4, TH1* h4,
                char* cH5, TH1* h5,
                float x1 = 0.6, float y1 = 0.6,
                float x2 = 0.8, float y2 = 0.9,
                char* symbol = (char*) "l"
                )
{
    TLegend *leg = new TLegend( x1, y1, x2, y2 );
    leg->SetLineColor(10);
    leg->SetLineStyle(1);
    leg->SetLineWidth(1);
    leg->SetFillColor(10);
    leg->SetTextSize(0.028);
    leg->SetTextFont(62);
    leg->SetMargin(0.4);
    leg->SetBorderSize(0);
    if( h1 ) leg->AddEntry( h1, cH1, symbol );
    if( h2 ) leg->AddEntry( h2, cH2, symbol );
    if( h3 ) leg->AddEntry( h3, cH3, symbol );
    if( h4 ) leg->AddEntry( h4, cH4, symbol );
    if( h5 ) leg->AddEntry( h5, cH5, symbol );
    leg->Draw( "same" );
}

void setLegend( char* cH1, TH1* h1,
                char* cH2, TH1* h2,
                char* cH3, TH1* h3,
                char* cH4, TH1* h4,
                float x1 = 0.6, float y1 = 0.6,
                float x2 = 0.8, float y2 = 0.9,
                char* symbol = (char*) "l"
                )
{
    TLegend *leg = new TLegend( x1, y1, x2, y2 );
    leg->SetLineColor(10);
    leg->SetLineStyle(1);
    leg->SetLineWidth(1);
    leg->SetFillColor(10);
    leg->SetTextSize(0.028);
    leg->SetTextFont(62);
    leg->SetMargin(0.4);
    leg->SetBorderSize(0);
    if( h1 ) leg->AddEntry( h1, cH1, symbol );
    if( h2 ) leg->AddEntry( h2, cH2, symbol );
    if( h3 ) leg->AddEntry( h3, cH3, symbol );
    if( h4 ) leg->AddEntry( h4, cH4, symbol );
    leg->Draw( "same" );
}

void setLegend( char* cH1, TGraph* g1,
                char* cH2, TGraph* g2,
                char* cH3, TGraph* g3,
                char* cH4, TGraph* g4,
                float x1 = 0.6, float y1 = 0.6,
                float x2 = 0.8, float y2 = 0.9,
                char* symbol = (char*) "l"
                )
{
    TLegend *leg = new TLegend( x1, y1, x2, y2 );
    leg->SetLineColor(10);
    leg->SetLineStyle(1);
    leg->SetLineWidth(1);
    leg->SetFillColor(10);
    leg->SetTextSize(0.028);
    leg->SetTextFont(62);
    leg->SetMargin(0.4);
    leg->SetBorderSize(0);
    if( g1 ) leg->AddEntry( g1, cH1, symbol );
    if( g2 ) leg->AddEntry( g2, cH2, symbol );
    if( g3 ) leg->AddEntry( g3, cH3, symbol );
    if( g4 ) leg->AddEntry( g4, cH4, symbol );
    leg->Draw( "same" );
}

void setLegend( char* cH1, TH1F* h1,
                char* cH2, TH1F* h2,
                char* cH3, TH1F* h3,
                char* cH4, TH1F* h4,
                float x1 = 0.6, float y1 = 0.6,
                float x2 = 0.8, float y2 = 0.9
                )
{
    TLegend *leg = new TLegend( x1, y1, x2, y2 );
    leg->SetLineColor(10);
    leg->SetLineStyle(1);
    leg->SetLineWidth(1);
    leg->SetFillColor(10);
    leg->SetTextSize(0.028);
    leg->SetTextFont(62);
    leg->SetMargin(0.4);
    leg->SetBorderSize(0);
    if( h1 ) leg->AddEntry( h1, cH1, "l" );
    if( h2 ) leg->AddEntry( h2, cH2, "l" );
    if( h3 ) leg->AddEntry( h3, cH3, "l" );
    if( h4 ) leg->AddEntry( h4, cH4, "l" );

    leg->Draw( "same" );
}

void setLegend( char* cH1, TH1F* h1,
                char* cH2, TH1F* h2,
                char* cH3, TH1F* h3,
                float x1 = 0.6, float y1 = 0.6,
                float x2 = 0.8, float y2 = 0.9
                )
{
    TLegend *leg = new TLegend( x1, y1, x2, y2 );
    leg->SetLineColor(10);
    leg->SetLineStyle(1);
    leg->SetLineWidth(1);
    leg->SetFillColor(10);
    leg->SetTextSize(0.028);
    leg->SetTextFont(62);
    leg->SetMargin(0.4);
    leg->SetBorderSize(0);
    if( h1 ) leg->AddEntry( h1, cH1, "l" );
    if( h2 ) leg->AddEntry( h2, cH2, "l" );
    if( h3 ) leg->AddEntry( h3, cH3, "l" );

    leg->Draw( "same" );
}

void setLegend( char* cH1, TH1F* h1,
                char* cH2, TH1F* h2,
                float x1 = 0.6, float y1 = 0.6,
                float x2 = 0.8, float y2 = 0.9
                )
{
    TLegend *leg = new TLegend( x1, y1, x2, y2 );
    leg->SetLineColor(10);
    leg->SetLineStyle(1);
    leg->SetLineWidth(1);
    leg->SetFillColor(10);
    leg->SetTextSize(0.028);
    leg->SetTextFont(62);
    leg->SetMargin(0.4);
    leg->SetBorderSize(0);
    if( h1 ) leg->AddEntry( h1, cH1, "l" );
    if( h2 ) leg->AddEntry( h2, cH2, "l" );
    leg->Draw( "same" );
}


void setLegend( char* c1, TGraph* g, char* symbol1,
                char* c2, TH1* h,    char* symbol2,
                char* c3, TF1* f,    char* symbol3,
                float x1 = 0.6, float y1 = 0.6,
                float x2 = 0.8, float y2 = 0.9
                )
{
    TLegend *leg = new TLegend( x1, y1, x2, y2 );
    leg->SetLineColor(10);
    leg->SetLineStyle(1);
    leg->SetLineWidth(1);
    leg->SetFillColor(10);
    leg->SetTextSize(0.028);
    leg->SetTextFont(62);
    leg->SetMargin(0.4);
    leg->SetBorderSize(0);
    if( g ) leg->AddEntry( g, c1, symbol1 );
    if( h ) leg->AddEntry( h, c2, symbol2 );
    if( f ) leg->AddEntry( f, c3, symbol3 );
    leg->Draw( "same" );
}

void setLegend( char* c1, TGraph* g1, char* symbol1,
                char* c2, TGraph* g2, char* symbol2,
                char* c3, TH1* h,     char* symbol3,
                float x1 = 0.6, float y1 = 0.6,
                float x2 = 0.8, float y2 = 0.9
                )
{
    TLegend *leg = new TLegend( x1, y1, x2, y2 );
    leg->SetLineColor(10);
    leg->SetLineStyle(1);
    leg->SetLineWidth(1);
    leg->SetFillColor(10);
    leg->SetTextSize(0.028);
    leg->SetTextFont(62);
    leg->SetMargin(0.4);
    leg->SetBorderSize(0);
    if( g1 ) leg->AddEntry( g1, c1, symbol1 );
    if( g2 ) leg->AddEntry( g2, c2, symbol2 );
    if( h  ) leg->AddEntry( h,  c3, symbol3 );
    leg->Draw( "same" );
}
//----------------------------------------------------------------------------