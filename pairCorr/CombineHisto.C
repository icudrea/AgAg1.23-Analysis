void CombineHisto(){

const char* inputFile[] = {"hist_centClass1_inmedRho_100000000evt.root","hist_centClass2_inmedRho_100000000evt.root",
                           "hist_centClass3_inmedRho_100000000evt.root","hist_centClass3_inmedRho_100000000evt.root"}

const int nFiles = 4;



TFile* outfile = new TFile("inmedRho_centClass_100000000evt.root", "RECREATE");

outifile->cd();


}