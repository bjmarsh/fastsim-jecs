
// C++
#include <iostream>
#include <fstream>
#include <vector>
#include <map>

// ROOT
#include "TChain.h"
#include "TBranch.h"
#include "TTree.h"
#include "TF1.h"
#include "TH1F.h"
#include "TH2F.h"
#include "TProfile.h"
#include "TProfile2D.h"
#include "TDirectory.h"
#include "TFile.h"
#include "TROOT.h"
#include "TCanvas.h"
#include "TColor.h"
#include "TStyle.h"
#include "TLegend.h"
#include "TLorentzVector.h"
#include "TTreeReader.h"
#include "TTreeReaderValue.h"
#include "TTreeReaderArray.h"
#include "TTreeCache.h"

// #include "JetCorrector/JetCorrector.cc"
#include "../CORE/Tools/JetCorrector.h"
#include "../CORE/Tools/jetcorr/JetCorrectionUncertainty.h"
#include "../CORE/Tools/jetcorr/SimpleJetCorrectionUncertainty.h"

using namespace std;
// using namespace tas;

float deltaPhiMe_(float phi1, float phi2){
    const double PI = 3.14159265359;
    float deltaPhi = fabs(phi1-phi2);
    if(deltaPhi > PI)
        deltaPhi = 2*PI - deltaPhi;
    return deltaPhi;
}

float deltaR_(float eta1, float phi1, float eta2, float phi2){
    return sqrt(pow(eta1-eta2,2) + pow(deltaPhiMe_(phi1, phi2), 2));
}


struct Jet {
    float PUrecoPt = 0.0, NoPUrecoPt = 0.0;
    float PUrecoEta = 0.0, NoPUrecoEta = 0.0;
    
    float PUrecoPtDumb = 0.0;

    float PUgenPt = 0.0, NoPUgenPt = 0.0;
    float PUgenEta = 0.0, NoPUgenEta = 0.0;
    float PUgenPhi = 0.0, NoPUgenPhi = 0.0;

    float PUdR = 0.0;

    float npu = 0.0, rho = 0.0;

    float correctionL1 = 1.0;
    float correctionL2 = 1.0;
    bool matched = false;
};

std::map<int, vector<Jet>* > JetMap;


int maketree(TString l1JECpfx, TString l2JECpfx, TString algo = "AK4PFchs", TString prefix = "") {

    // load JECs
    bool doNoPU = true;
    bool makeMap = true;

    bool doSkip = false;

    TString PUfilename = "../../JRA_FlatPU_jec.root";
    TString PUfilenameJEC = "../../JRA_FlatPU_jec.root";

    if(prefix.Contains("NoFilt")) {
        doSkip = false;
    }
    if(prefix.Contains("FullSim")) {
        doNoPU = false;
        makeMap = false;
        PUfilename = "../crab/all/JRA_PUFlat0to50_FullSim.root";
    }


    std::vector<std::string> jetcorr_filenamesL1; jetcorr_filenamesL1.push_back(Form(l1JECpfx+"_%s.txt",algo.Data()));
    FactorizedJetCorrector *jetCorrectorL1 = makeJetCorrector(jetcorr_filenamesL1);

    std::vector<std::string> jetcorr_filenamesL2; jetcorr_filenamesL2.push_back(Form(l2JECpfx+"_%s.txt",algo.Data()));
    FactorizedJetCorrector *jetCorrectorL2 = makeJetCorrector(jetcorr_filenamesL2);

    algo.ToLower();
    // TFile *f = TFile::Open("../crab/all/JRA_PUFlat0to50.root");
    TFile *f = TFile::Open(PUfilename);
    TDirectory* df = f->GetDirectory(algo);
    TTree *tree = (TTree*)df->Get("t");
    TTreeCache::SetLearnEntries(100);
    tree->SetCacheSize(256*1024*1024);
    // tree->Print();

    TFile *fjec = TFile::Open(PUfilenameJEC);
    TDirectory *djec = fjec->GetDirectory(algo+"l1");
    TTree *treejec = (TTree*)djec->Get("t");
    treejec->SetMakeClass(1);

    unsigned char nref(0);
    long long event, run, lumi;
    // float refe[100], refpt[100], refeta[100], refphi[100], refarea[100];
    // float jete[100], jetpt[100], jeteta[100], jetphi[100], jetarea[100];
    // float refdrjet[100], rho;
    std::vector<float>* refe = 0;
    std::vector<float>* refpt = 0;
    std::vector<float>* refeta = 0;
    std::vector<float>* refphi = 0;
    std::vector<float>* refdrjet = 0;
    std::vector<float>* refarea = 0;
    std::vector<float>* jete = 0;
    std::vector<float>* jetpt = 0;
    std::vector<float>* jeteta = 0;
    std::vector<float>* jetphi = 0;
    std::vector<float>* jetarea = 0;
    float rho;
    vector<float>* tnpus = 0;

    tree->SetBranchAddress("nref",&nref);
    tree->SetBranchAddress("evt",&event);
    tree->SetBranchAddress("run",&run);
    tree->SetBranchAddress("lumi",&lumi);
    tree->SetBranchAddress("refe",&refe);
    tree->SetBranchAddress("refpt",&refpt);
    tree->SetBranchAddress("refeta",&refeta);
    tree->SetBranchAddress("refphi",&refphi);
    tree->SetBranchAddress("refdrjt",&refdrjet);
    tree->SetBranchAddress("refarea",&refarea);
    tree->SetBranchAddress("jte",&jete);
    tree->SetBranchAddress("jtpt",&jetpt);
    tree->SetBranchAddress("jteta",&jeteta);
    tree->SetBranchAddress("jtphi",&jetphi);
    tree->SetBranchAddress("jtarea",&jetarea);
    tree->SetBranchAddress("rho",&rho);
    tree->SetBranchAddress("tnpus",&tnpus);

    std::vector<float> * jetptdumb = 0;
    treejec->SetBranchAddress("jtpt", &jetptdumb);

    unsigned int nEventsTree = tree->GetEntries();
    unsigned int nEventsPU = nEventsTree;
    // unsigned int nEventsPU = 10000000;
    cout << "nEventsPU: " << nEventsPU << endl;

    unsigned int totJets = 0;

    for (unsigned int iEvent=0;iEvent<nEventsPU;iEvent++) {
        tree->GetEntry(iEvent);
        treejec->GetEntry(iEvent);
        JetMap[event] = new vector<Jet>;

        for (unsigned int iref=0;iref<(unsigned int)nref;iref++) {

            // if(refdrjet[iref] > 0.2) continue;
            if(refdrjet->at(iref) > 0.2) continue;
            if (doSkip && jete->at(iref) > 6500) continue; // skip bad jets

            float resp = jetpt->at(iref) / refpt->at(iref);
            // if ( resp < 0.0 || resp > 2.0 ) continue; // FIXME

            totJets++;

            // load JEC corrections
            jetCorrectorL1->setJetEta(jeteta->at(iref));
            jetCorrectorL1->setJetPt(jetpt->at(iref));
            jetCorrectorL1->setJetE(jete->at(iref));
            jetCorrectorL1->setJetA(jetarea->at(iref));
            jetCorrectorL1->setRho(rho);

            // load JEC corrections
            jetCorrectorL2->setJetEta(jeteta->at(iref));
            jetCorrectorL2->setJetPt(jetpt->at(iref));
            jetCorrectorL2->setJetE(jete->at(iref));

            float jetCorrectionL1 = jetCorrectorL1->getCorrection();
            float jetCorrectionL2 = jetCorrectorL2->getCorrection();

            if ( jetCorrectionL1*resp < 0.0 || jetCorrectionL1*resp > 2.0 ) continue; // FIXME
 
            TLorentzVector recojet;
            recojet.SetPtEtaPhiE(jetpt->at(iref), jeteta->at(iref), jetphi->at(iref), jete->at(iref));

            TLorentzVector genjet;
            genjet.SetPtEtaPhiE(refpt->at(iref), refeta->at(iref), refphi->at(iref), refe->at(iref));

            if(makeMap) {
                JetMap[event]->push_back(Jet());
                JetMap[event]->back().PUrecoPt = jetpt->at(iref);
                JetMap[event]->back().PUrecoEta = jeteta->at(iref);
                JetMap[event]->back().PUgenPt = refpt->at(iref);
                JetMap[event]->back().PUgenEta = refeta->at(iref);
                JetMap[event]->back().PUgenPhi = refphi->at(iref);
                JetMap[event]->back().PUrecoPtDumb = jetptdumb->at(iref);
                JetMap[event]->back().PUdR = refdrjet->at(iref);
                JetMap[event]->back().correctionL1 = jetCorrectionL1;
                JetMap[event]->back().correctionL2 = jetCorrectionL2;
                JetMap[event]->back().npu = tnpus->at(0);
                JetMap[event]->back().rho = rho;
            }

            if( jeteta->at(iref) < 0.087 && jeteta->at(iref) > 0.0 ) { // FIXME
                if(refpt->at(iref) > 40 && refpt->at(iref) < 45) {
                }
            }

        }
    }

    cout << "Considered " << totJets << " PU jets in total." << endl;

    if(doNoPU) {
        ///////////////////////////
        // LOOP OVER NoPU SAMPLE //
        ///////////////////////////
        algo.ToLower();
        TFile *f = TFile::Open("../../JRA_NoPU.root");
        TDirectory* df = f->GetDirectory(algo);
        TTree *tree = (TTree*)df->Get("t");
        TTreeCache::SetLearnEntries(100);
        tree->SetCacheSize(256*1024*1024);


        unsigned char nref(0);
        long long event, run, lumi;
        // float refe[100], refpt[100], refeta[100], refphi[100], refarea[100];
        // float jete[100], jetpt[100], jeteta[100], jetphi[100], jetarea[100];
        // float refdrjet[100], rho;
        std::vector<float>* refe = 0;
        std::vector<float>* refpt = 0;
        std::vector<float>* refeta = 0;
        std::vector<float>* refphi = 0;
        std::vector<float>* refdrjet = 0;
        std::vector<float>* refarea = 0;
        std::vector<float>* jete = 0;
        std::vector<float>* jetpt = 0;
        std::vector<float>* jeteta = 0;
        std::vector<float>* jetphi = 0;
        std::vector<float>* jetarea = 0;
        tree->SetBranchAddress("nref",&nref);
        tree->SetBranchAddress("evt",&event);
        tree->SetBranchAddress("run",&run);
        tree->SetBranchAddress("lumi",&lumi);
        tree->SetBranchAddress("nref",&nref);
        tree->SetBranchAddress("refe",&refe);
        tree->SetBranchAddress("refpt",&refpt);
        tree->SetBranchAddress("refeta",&refeta);
        tree->SetBranchAddress("refphi",&refphi);
        tree->SetBranchAddress("refdrjt",&refdrjet);
        tree->SetBranchAddress("refarea",&refarea);
        tree->SetBranchAddress("jte",&jete);
        tree->SetBranchAddress("jtpt",&jetpt);
        tree->SetBranchAddress("jteta",&jeteta);
        tree->SetBranchAddress("jtphi",&jetphi);
        tree->SetBranchAddress("jtarea",&jetarea);
        tree->SetBranchAddress("rho",&rho);

        unsigned int nEventsTree = tree->GetEntries();
        unsigned int nEventsNoPU = nEventsTree;
        // unsigned int nEventsNoPU = 10000000;
        cout << "nEventsNoPU: " << nEventsNoPU << endl;

        unsigned int totJets = 0;

        for (unsigned int iEvent=0;iEvent<nEventsNoPU;iEvent++) {
            tree->GetEntry(iEvent);

            for (unsigned int iref=0;iref<(unsigned int)nref;iref++) {

                if(refdrjet->at(iref) > 0.2) continue;
                if (doSkip && jete->at(iref) > 6500) continue; // skip bad jets

                float resp = jetpt->at(iref) / refpt->at(iref);
                // if ( resp < 0.0 || resp > 2.0 ) continue; // FIXME

                // load JEC corrections
                jetCorrectorL1->setJetEta(jeteta->at(iref));
                jetCorrectorL1->setJetPt(jetpt->at(iref));
                jetCorrectorL1->setJetE(jete->at(iref));
                jetCorrectorL1->setJetA(jetarea->at(iref));
                jetCorrectorL1->setRho(rho);

                float jetCorrectionL1 = jetCorrectorL1->getCorrection();
                if ( jetCorrectionL1*resp < 0.0 || jetCorrectionL1*resp > 2.0 ) continue; // FIXME

                totJets++;

                TLorentzVector recojet;
                recojet.SetPtEtaPhiE(jetpt->at(iref), jeteta->at(iref), jetphi->at(iref), jete->at(iref));

                TLorentzVector genjet;
                genjet.SetPtEtaPhiE(refpt->at(iref), refeta->at(iref), refphi->at(iref), refe->at(iref));


                float normToPU = 1.0*nEventsPU/nEventsNoPU;

                if(makeMap && JetMap.count(event)) {
                    uint njet = JetMap[event]->size();
                    for(uint ipu=0; ipu<njet; ipu++){
                        Jet j = JetMap[event]->at(ipu);
                        float dR = deltaR_(j.PUgenEta, j.PUgenPhi, refeta->at(iref), refphi->at(iref));
                        if(dR < 0.3){
                            JetMap[event]->at(ipu).NoPUrecoPt = jetpt->at(iref);
                            JetMap[event]->at(ipu).NoPUrecoEta = jeteta->at(iref);
                            JetMap[event]->at(ipu).NoPUgenPt = refpt->at(iref);
                            JetMap[event]->at(ipu).NoPUgenEta = refeta->at(iref);
                            JetMap[event]->at(ipu).NoPUgenPhi = refphi->at(iref);
                            JetMap[event]->at(ipu).matched = true;
                            break;
                        }
                    }
                }

            }
        }

        cout << "Considered " << totJets << " NoPU jets in total." << endl;

    }

    TFile *fout = new TFile(algo+".root","RECREATE");
    TTree *t = new TTree("t","t");
    float pt_nopu, pt_pu, pt_jra, pt_ref, eta_nopu, eta_pu, eta_ref,l1corr,l2corr, tnpu, dr;
    t->Branch("pt_nopu", &pt_nopu, "pt_nopu/F");
    t->Branch("pt_pu", &pt_pu, "pt_pu/F");
    t->Branch("pt_jra", &pt_jra, "pt_jra/F");
    t->Branch("pt_ref", &pt_ref, "pt_ref/F");
    t->Branch("eta_nopu", &eta_nopu, "eta_nopu/F");
    t->Branch("eta_pu", &eta_pu, "eta_pu/F");
    t->Branch("eta_ref", &eta_ref, "eta_ref/F");
    t->Branch("l1corr", &l1corr, "l1corr/F");
    t->Branch("l2corr", &l2corr, "l2corr/F");
    t->Branch("tnpu", &tnpu, "tnpu/F");
    t->Branch("rho", &rho, "rho/F");
    t->Branch("dr", &dr, "dr/F");
    t->Branch("event", &event, "event/I");

    if(makeMap) {
        for(auto const &jet : JetMap) {

            event = jet.first;
            for(uint i=0; i<jet.second->size(); i++){
                Jet j = jet.second->at(i);

                if(!j.matched)
                    continue;

                pt_nopu = j.NoPUrecoPt;
                pt_pu = j.PUrecoPt;
                pt_jra = j.PUrecoPtDumb;
                pt_ref = j.PUgenPt;
                eta_nopu = j.NoPUrecoEta;
                eta_pu = j.PUrecoEta;
                eta_ref = j.PUgenEta;
                l1corr = j.correctionL1;
                l2corr = j.correctionL2;
                tnpu = j.npu;
                rho = j.rho;
                dr = j.PUdR;

                t->Fill();
            }
        }
    }
    
    t->Write();
    fout->Close();

    JetMap.clear();

    return 0;
}
