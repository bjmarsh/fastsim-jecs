{
    gStyle->SetPaintTextFormat("4.2f");
    // gStyle->SetOptStat(0);
    gEnv->SetValue("TFile.AsyncPrefetching",1);

    const int NRGBs = 5; // http://ultrahigh.org/2007/08/making-pretty-root-color-palettes/
    const int NCont = 255;
    double stops[NRGBs] = { 0.00, 0.34, 0.61, 0.84, 1.00 };
    double red[NRGBs]   = { 0.00, 0.00, 0.87, 1.00, 0.51 };
    double green[NRGBs] = { 0.00, 0.81, 1.00, 0.20, 0.00 };
    double blue[NRGBs]  = { 0.51, 1.00, 0.12, 0.00, 0.00 };
    TColor::CreateGradientColorTable(NRGBs, stops, red, green, blue, NCont);
    gStyle->SetNumberContours(NCont);

    // gSystem->Load("JetCorrector/CMS3_CORE.so");
    gSystem->Load("CORE/CMS3_CORE.so");
    gROOT->ProcessLine(".L val.C+");

    // TString l1JECpfx = "";
    // TString l2JECpfx = "";
    // TString l3JECpfx = "";

    TString era = "Summer16_07Aug2017_V11_94X_MC";

    l1JECpfx = "../l1/text/"+era+"_L1FastJet";
    l2JECpfx = "../l2l3/"+era+"_L2Relative";
    l3JECpfx = "../l2l3/"+era+"_L3Absolute";

    // l1JECpfx = "/home/users/bemarsh/analysis/mt2/current/MT2Analysis/babymaker/jetCorrections/Spring16_FastSimV1_L1FastJet";
    // l2JECpfx = "/home/users/bemarsh/analysis/mt2/current/MT2Analysis/babymaker/jetCorrections/Spring16_FastSimV1_L2Relative";
    // l3JECpfx = "/home/users/bemarsh/analysis/mt2/current/MT2Analysis/babymaker/jetCorrections/Spring16_FastSimV1_L3Absolute";
    
    // val(l1JECpfx, l2JECpfx, l3JECpfx, "AK4PF");
    // val(l1JECpfx, l2JECpfx, l3JECpfx, "AK4PFchs");
    val(l1JECpfx, l2JECpfx, l3JECpfx, "AK8PFchs");
    // val(l1JECpfx, l2JECpfx, l3JECpfx, "AK4PUPPI");
    // val(l1JECpfx, l2JECpfx, l3JECpfx, "AK8PUPPI");



}
