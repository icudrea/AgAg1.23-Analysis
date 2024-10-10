void setOPT_canvas(TCanvas *canvas)
{
    gStyle->SetOptStat(0);
    gStyle->SetEndErrorSize(5);
    gStyle->SetErrorX(0);    // X errors of the data points set to be 0
    gStyle->SetLineStyleString(22, "80 18 12 18 12 12"); // special style for the line
    gStyle->SetEndErrorSize(5);   // define end width of error bars
    gStyle->SetCanvasColor(10);
    gStyle->SetPadColor(10);
    canvas->SetLeftMargin(0.2);
    canvas->SetRightMargin(0.05);
    canvas->SetTopMargin(0.05);
    canvas->SetBottomMargin(0.15);
    canvas->ToggleEventStatus();
    canvas->Range(-200, -10, 1000, -2);
    canvas->SetFillColor(0);
    canvas->SetBorderMode(0);
    canvas->SetBorderSize(0);
    canvas->SetTickx();
    canvas->SetTicky();
    canvas->SetLogy();
    canvas->SetFrameLineWidth(2);
    canvas->SetFrameBorderMode(0);
    canvas->SetFrameBorderSize(0);
}

void setOPT_TH1F(TH1F *hist, TString xAxisTitle = " ", TString yAxisTitle = " ", Int_t Ndevision = 510, Int_t marker_style = 20, Float_t marker_size = 1.3, Int_t color = 1)
{
    hist->GetXaxis()->SetTitle(xAxisTitle);
    hist->GetYaxis()->SetTitle(yAxisTitle);
    hist->GetXaxis()->SetTitleSize(0.06);
    hist->GetYaxis()->SetTitleSize(0.06);
    hist->GetXaxis()->SetTitleFont(42);
    hist->GetYaxis()->SetTitleFont(42);
    hist->GetXaxis()->SetNdivisions(Ndevision);
    hist->GetYaxis()->SetTitleOffset(1.2);
    hist->GetXaxis()->SetLabelFont(42);
    hist->GetYaxis()->SetLabelFont(42);
    hist->GetXaxis()->SetLabelSize(0.05);
    hist->GetYaxis()->SetLabelSize(0.05);
    hist->SetMarkerStyle(marker_style);
    hist->SetMarkerSize(marker_size);
    hist->SetMarkerColor(color);
    hist->SetLineColor(color);
    hist->SetTitle("");
    hist->SetLineWidth(2);
}

void setOPT_hists(TH1D *hist, TString xAxisTitle = " ", TString yAxisTitle = " ", Int_t Ndevision = 510, Int_t marker_style = 20, Float_t marker_size = 1.3, Int_t color = 1)
{
    hist->GetXaxis()->SetTitle(xAxisTitle);
    hist->GetYaxis()->SetTitle(yAxisTitle);
    hist->GetXaxis()->SetTitleSize(0.06);
    hist->GetYaxis()->SetTitleSize(0.06);
    hist->GetXaxis()->SetTitleFont(42);
    hist->GetYaxis()->SetTitleFont(42);
    hist->GetXaxis()->SetNdivisions(Ndevision);
    hist->GetYaxis()->SetTitleOffset(1.22);
    hist->GetXaxis()->SetLabelFont(42);
    hist->GetYaxis()->SetLabelFont(42);
    hist->GetXaxis()->SetLabelSize(0.05);
    hist->GetYaxis()->SetLabelSize(0.05);
    hist->SetMarkerStyle(marker_style);
    hist->SetMarkerSize(marker_size);
    hist->SetMarkerColor(color);
    hist->SetTitle("");
    hist->GetXaxis()->SetLabelColor(1);
    hist->GetYaxis()->SetLabelColor(1);
    hist->GetXaxis()->SetTitleColor(1);
    hist->GetYaxis()->SetTitleColor(1);
    hist->SetFillColor(10);
}

void draw_CorrFactors_PolFits()
{
    TFile *f1 = new TFile("CorrectionFactor_centClass1_inmedRhoCG_9oAngle100Mom_100000000evt.root", "READ");
    TFile *f2 = new TFile("CorrectionFactor_centClass2_inmedRhoCG_9oAngle100Mom_100000000evt.root", "READ");
    TFile *f3 = new TFile("CorrectionFactor_centClass3_inmedRhoCG_9oAngle100Mom_100000000evt.root", "READ");
    TFile *f4 = new TFile("CorrectionFactor_centClass4_inmedRhoCG_9oAngle100Mom_100000000evt.root", "READ");

    if (!f1 || !f1->IsOpen() || !f2 || !f2->IsOpen() || !f3 || !f3->IsOpen() || !f4 || !f4->IsOpen()) {
        std::cerr << "Error opening one or more input files" << std::endl;
        return;
    }

    TH1D *hAccFactor[4];
    hAccFactor[0] = (TH1D*)f1->Get("h_AccCorr");
    hAccFactor[1] = (TH1D*)f2->Get("h_AccCorr");
    hAccFactor[2] = (TH1D*)f3->Get("h_AccCorr");
    hAccFactor[3] = (TH1D*)f4->Get("h_AccCorr");

    TH1D *hEffFactor[4];
    hEffFactor[0] = (TH1D*)f1->Get("h_EffCorr");
    hEffFactor[1] = (TH1D*)f2->Get("h_EffCorr");
    hEffFactor[2] = (TH1D*)f3->Get("h_EffCorr");
    hEffFactor[3] = (TH1D*)f4->Get("h_EffCorr");

    for (int i = 0; i < 4; ++i) {
        if (!hAccFactor[i] || !hEffFactor[i]) {
            std::cerr << "Error retrieving histogram from file " << i + 1 << std::endl;
            return;
        }
    }

    TH1D *hEffFactor_fit[4];
    for (int i = 0; i < 4; ++i) {
        TF1 *fit = new TF1("fit", "pol0", 0.6, 1.8);
        hEffFactor[i]->Fit(fit, "LQ");

        hEffFactor_fit[i] = (TH1D*)hEffFactor[i]->Clone();
        hEffFactor_fit[i]->SetName(Form("hEffFactor_fit_%d", i));

        double p0 = fit->GetParameter(0); 
        for (int bin = 1; bin <= hEffFactor_fit[i]->GetNbinsX(); ++bin) {
        double x = hEffFactor_fit[i]->GetBinCenter(bin);
        if (x > 0.6 && x <= 1.8) {
        hEffFactor_fit[i]->SetBinContent(bin, p0);
        }
      }

        // for (int bin = 1; bin <= hEffFactor_fit[i]->GetNbinsX(); ++bin) {
            // double x = hEffFactor_fit[i]->GetBinCenter(bin);
            // if (x > 0.6 && x <= 1.8) {
                // hEffFactor_fit[i]->SetBinContent(bin, fit->Eval(x));
            // }
        // }
    }

    const char* output_file = "output_new.root";
    TFile *fout = new TFile(output_file, "RECREATE");
    if (!fout || !fout->IsOpen()) {
        std::cerr << "Error creating output file" << std::endl;
        return;
    }

    for (int i = 0; i < 4; ++i) {
        hEffFactor_fit[i]->Write();
    }

    fout->Close();

    f1->Close();
    f2->Close();
    f3->Close();
    f4->Close();

    delete f1;
    delete f2;
    delete f3;
    delete f4;
    delete fout;
}


 