{

    // gSystem->Load("JetCorrector/CMS3_CORE.so");
    gSystem->Load("../CORE/CMS3_CORE.so");
    gROOT->ProcessLine(".L maketree.C+");

    TString l1JECpfx = "";
    TString l2JECpfx = "";
    TString l3JECpfx = "";

    // TString era = "Fall17_17Nov2017_V32_MC";
    TString era = "Summer16_07Aug2017_V11_94X_MC";

    l1JECpfx = "../../l1/text/"+era+"_L1FastJet";
    l2JECpfx = "../../l2l3/"+era+"_L2Relative";

    // l1JECpfx = "../fullsimjecs/"+era+"_L1FastJet";
    // l2JECpfx = "../fullsimjecs/"+era+"_L2Relative";
    
    // maketree(l1JECpfx, l2JECpfx, "AK4PFchs");
    maketree(l1JECpfx, l2JECpfx, "AK8PFchs");
    // maketree(l1JECpfx, l2JECpfx, "AK4PUPPI");
    // maketree(l1JECpfx, l2JECpfx, "AK8PUPPI");



}
