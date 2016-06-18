
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
#include "CORE/Tools/JetCorrector.h"
#include "CORE/Tools/jetcorr/JetCorrectionUncertainty.h"
#include "CORE/Tools/jetcorr/SimpleJetCorrectionUncertainty.h"


// CMS3
#include "CMS3.cc"

using namespace std;
using namespace tas;

const int nptbins = 6;
float ptbins[nptbins+1] = { 30, 50, 100, 200, 400, 600, 1000 };

const int netabins = 8;
float etabins[netabins+1] = { -4.7,-3.2,-2.6,-1.4,0.0,1.4,2.6,3.2,4.7 };

const int nptbinsFine = 33;
float ptbinsFine[nptbinsFine+1] = {10,11,12,13,14,15,17,
    20,23,27,30,35,40,45,57,72,90,120,150,
    200,300,400,550,750,1000,1500,2000,2500,3000,
    3500,4000,4500,5000,10000};

const int netabinsFine = 82;
float etabinsFine[netabinsFine+1] = {-5.191,-4.889,-4.716,-4.538,-4.363,-4.191,-4.013,-3.839,-3.664,
    -3.489,-3.314,-3.139,-2.964,-2.853,-2.650,-2.500,-2.322,-2.172,
    -2.043,-1.930,-1.830,-1.740,-1.653,-1.566,-1.479,-1.392,-1.305,
    -1.218,-1.131,-1.044,-0.957,-0.879,-0.783,-0.696,-0.609,-0.522,
    -0.435,-0.348,-0.261,-0.174,-0.087, 0.000,
    0.087, 0.174, 0.261, 0.348, 0.435, 0.522, 0.609, 0.696, 0.783,
    0.879, 0.957, 1.044, 1.131, 1.218, 1.305, 1.392, 1.479, 1.566,
    1.653, 1.740, 1.830, 1.930, 2.043, 2.172, 2.322, 2.500, 2.650,
    2.853, 2.964, 3.139, 3.314, 3.489, 3.664, 3.839, 4.013, 4.191,
    4.363, 4.538, 4.716, 4.889, 5.191};

const int nptbinsLow = 10;
float ptbinsLow[nptbinsLow+1] = {10,12,15,20,30,45,72,150,300,750,2000};

const int nptbinsFineSmall = 13;
float ptbinsFineSmall[nptbinsFineSmall+1] = { 30,57,72,90,120,150,200,300,400,550,750,1000,1500,2000 };

const int nptbinsFineSmall2 = 18;
float ptbinsFineSmall2[nptbinsFineSmall2+1] = { 10,11,13,19,24,30,57,72,90,120,150,200,300,400,550,750,1000,1500,2000 };

const int netabinsFineSmall = 78;
float etabinsFineSmall[netabinsFineSmall+1] = {-4.716,-4.538,-4.363,-4.191,-4.013,-3.839,-3.664,
    -3.489,-3.314,-3.139,-2.964,-2.853,-2.650,-2.500,-2.322,-2.172,
    -2.043,-1.930,-1.830,-1.740,-1.653,-1.566,-1.479,-1.392,-1.305,
    -1.218,-1.131,-1.044,-0.957,-0.879,-0.783,-0.696,-0.609,-0.522,
    -0.435,-0.348,-0.261,-0.174,-0.087, 0.000,
    0.087, 0.174, 0.261, 0.348, 0.435, 0.522, 0.609, 0.696, 0.783,
    0.879, 0.957, 1.044, 1.131, 1.218, 1.305, 1.392, 1.479, 1.566,
    1.653, 1.740, 1.830, 1.930, 2.043, 2.172, 2.322, 2.500, 2.650,
    2.853, 2.964, 3.139, 3.314, 3.489, 3.664, 3.839, 4.013, 4.191,
    4.363, 4.538, 4.716};

float chiSqL1[82] = { 1.60539,2.20951,3.21782,3.87299,3.51363,4.02838,3.82335,3.18909,2.14662,1.58314,
    1.52906,1.17514,1.24783,2.83435,1.74808,3.10027,3.41335,4.91578,5.17565,4.71982,
    4.15691,4.33661,3.13274,1.26361,1.00021,1.13738,1.2151,1.38217,1.1165,1.10621,
    1.43731,1.28473,1.37193,1.21442,1.1457,1.23535,1.15378,1.09692,1.31721,1.25756,
    1.19067,1.21601,1.17657,1.20704,1.15217,1.17708,1.1714,1.1888,1.31189,1.21833,
    1.15974,1.23092,1.21176,1.42142,1.32338,1.33472,1.09145,1.01003,1.18473,3.72695,
    3.32333,3.8451,4.76856,4.796,4.3495,3.78914,2.62312,1.68486,2.93507,1.20421,
    1.19638,1.5336,1.92688,1.92759,3.3954,3.75226,4.20831,3.98875,3.73054,3.25308,
    2.27797,1.28736 };

float chiSqL2[82] = { 0.706227,0.544524,1.07239,2.12196,1.18089,2.39658,1.67861,1.45186,1.81325,1.70255,
    3.07921,7.57326,1.26159,4.75671,8.89831,12.3062,12.4805,9.20552,7.23037,8.89574,
    6.92363,4.54272,2.71894,6.59604,3.13407,1.90049,3.91683,3.70987,5.48496,5.05667,
    6.01469,7.98482,10.1005,7.49051,9.89398,8.78631,11.0208,8.9335,7.31033,9.94897,
    9.31896,12.7758,9.64578,8.13346,8.51277,8.6525,8.39573,7.4851,8.67488,10.5562,
    6.71233,3.72836,3.98651,4.68111,4.42212,4.32702,3.06728,2.78938,4.9642,4.73945,
    5.41188,7.934,7.94042,7.08113,9.3156,16.8132,15.5884,8.72753,3.20473,1.05719,
    7.688,3.28454,1.90776,1.52296,1.78217,2.06825,1.85841,1.04844,1.05921,0.89955,
    1.59457,1.98791 };

const int nptbinsUnc = 44;
float ptbinsUnc[nptbinsUnc+1] = {8, 10, 12, 15, 18, 21, 24, 28, 32, 37, 43, 49, 56, 64, 74, 84,
                                 97, 114, 133, 153, 174, 196, 220, 245, 272, 300, 362, 430,
                                 507, 592, 686, 790, 905, 1032, 1172, 1327, 1497, 1684, 1890, 
                                 2000 -1e-3, 2238, 2500, 2787, 3103, 3450};

const int netabinsUnc = 40;
float etabinsUnc[netabinsUnc+1] = {-5.4,-5.0,-4.4,-4,-3.5,-3,-2.8,-2.6,-2.4,-2.2,-2.0,
                                   -1.8,-1.6,-1.4,-1.2,-1.0, -0.8,-0.6,-0.4,-0.2,0.,
                                   0.2,0.4,0.6,0.8,1.0,1.2,1.4,
                                   1.6,1.8,2.0,2.2,2.4,2.6,2.8,3,3.5,4,4.4,5.0,5.4};


struct Jet {
    float PUrecoPt = 0.0, NoPUrecoPt = 0.0;
    float PUrecoEta = 0.0, NoPUrecoEta = 0.0;

    float PUgenPt = 0.0, NoPUgenPt = 0.0;
    float PUgenEta = 0.0, NoPUgenEta = 0.0;

    float correctionL1 = 1.0;
    float correctionL2 = 1.0;
    bool matched = false;
};

std::map<int, Jet> JetMap;


void addOverflow(TH1F * h1) {
    h1->SetBinContent(h1->GetNbinsX(), h1->GetBinContent(h1->GetNbinsX())+h1->GetBinContent(h1->GetNbinsX()+1) );
}
void myStyle(TProfile * h1) {
    h1->SetMarkerStyle(21);
    h1->SetMarkerSize(1.0);
    h1->SetMarkerColor(kRed);
    h1->SetLineColor(kRed);
}
void myStyle(TH1F * h1) {
    h1->SetMarkerStyle(21);
    h1->SetMarkerSize(1.0);
    h1->SetMarkerColor(kRed);
    h1->SetLineColor(kRed);
}
void myStyle2(TH1F * h1) {
    h1->SetMarkerStyle(20);
    h1->SetMarkerSize(0.7);
    h1->SetMarkerColor(kRed);
    h1->SetLineColor(kRed);
}
void doFit(TH1F * h, bool print=false) {
    float peak = h->GetMean();
    float sigma = h->GetRMS();
    float norm = h->GetEntries();
    int niters = 5;
    TF1* f1;

    if(norm > 10) {
        for(int ifit = 0; ifit < niters; ifit++) {
            f1 = new TF1("f1", "gaus", peak-1.0*sigma, peak+1.0*sigma);
            f1->SetParameter(0, norm);
            f1->SetParameter(1, peak);
            f1->SetParameter(2, sigma);
            if(ifit == niters-1) {
                h->Fit(f1, "RQ"); // draw fit if last iteration
                if(print) cout << h->GetName() << " mean,fitmean = " << h->GetMean() << ", " << peak << endl;
            } else {
                h->Fit(f1, "RQ0");
            }
            f1 = h->GetFunction("f1");
            norm = f1->GetParameter(0);
            peak = f1->GetParameter(1);
            sigma = f1->GetParameter(2);
            // cout << ifit << " " << norm << " " << peak << " " << sigma << endl;
        }
    }

}


int val(TString l1JECpfx, TString l2JECpfx, TString l3JECpfx, TString algo = "AK4PFchs", TString prefix = "") {

    // load JECs
    bool doNoPU = true;
    bool debug = false;
    bool makeMap = true;

    bool doSkip = false;

    TString PUfilename = "../JRA_PUFlat.root";

    if(prefix.Contains("NoFilt")) {
        doSkip = false;
    }
    if(prefix.Contains("FullSim")) {
        doNoPU = false;
        makeMap = false;
        PUfilename = "../crab/all/JRA_PUFlat0to50_FullSim.root";
    }


    unsigned int debugCount = 100;

    std::vector<std::string> jetcorr_filenamesL1; jetcorr_filenamesL1.push_back(Form(l1JECpfx+"_%s.txt",algo.Data()));
    std::vector<std::string> jetcorr_filenamesL2; jetcorr_filenamesL2.push_back(Form(l2JECpfx+"_%s.txt",algo.Data()));
    std::vector<std::string> jetcorr_filenamesL3; jetcorr_filenamesL3.push_back(Form(l3JECpfx+"_%s.txt",algo.Data()));
    // jetcorr_filenamesL2L3.push_back(Form(l3JECpfx+"_%s.txt",algo.Data()));
    FactorizedJetCorrector *jetCorrectorL1 = makeJetCorrector(jetcorr_filenamesL1);
    FactorizedJetCorrector *jetCorrectorL2 = makeJetCorrector(jetcorr_filenamesL2);
    FactorizedJetCorrector *jetCorrectorL3 = makeJetCorrector(jetcorr_filenamesL3);


    TH2F *response = new TH2F("response", "p_{T}(reco)/p_{T}(gen) in gen bins;p_{T};#eta", nptbins,ptbins,netabins,etabins);
    TH2F *responseFine = new TH2F("responseFine", "p_{T}(reco)/p_{T}(gen) in fine gen bins;p_{T};#eta", nptbinsFine,ptbinsFine,netabinsFine,etabinsFine);
    TH2F *counts = new TH2F("counts", "counts;pt;eta", nptbins,ptbins,netabins,etabins);
    TH2F *countsFine = new TH2F("countsFine", "counts;pt;eta", nptbinsFine,ptbinsFine,netabinsFine,etabinsFine);
    TH2F *countsLow = new TH2F("countsLow", "counts;pt;eta", nptbinsLow,ptbinsLow,netabins,etabins);
    TH2F *countsUnc = new TH2F("countsUnc", "counts;pt;eta", nptbinsUnc,ptbinsUnc,netabinsUnc,etabinsUnc);

    TProfile *L1pt = new TProfile("L1pt", "L1 correction vs p_{T};p_{T}", 50,0,1000);
    TProfile *L1eta = new TProfile("L1eta", "L1 correction vs #eta;#eta", 50,-4.7,4.7);
    TH2F *L1corr = new TH2F("L1corr", "L1 in gen bins;p_{T};#eta", nptbins,ptbins,netabins,etabins);
    TH2F *L1corrFine = new TH2F("L1corrFine", "L1 in fine gen bins;p_{T};#eta", nptbinsFine,ptbinsFine,netabinsFine,etabinsFine);
    TH2F *responseL1Corr = new TH2F("responseL1Corr", "L1*p_{T}(reco)/p_{T}(gen) in gen bins;p_{T};#eta", nptbins,ptbins,netabins,etabins);
    TH2F *responseL1CorrFine = new TH2F("responseL1CorrFine", "L1*p_{T}(reco)/p_{T}(gen) in fine gen bins;p_{T};#eta", nptbinsFine,ptbinsFine,netabinsFine,etabinsFine);

    TProfile *L2pt = new TProfile("L2pt", "L2L3 correction vs p_{T};p_{T}", 50,0,1000);
    TProfile *L2eta = new TProfile("L2eta", "L2L3 correction vs #eta;#eta", 50,-4.7,4.7);
    TH2F *L2corr = new TH2F("L2corr", "L2L3 in gen bins;p_{T};#eta", nptbins,ptbins,netabins,etabins);
    TH2F *L2corrFine = new TH2F("L2corrFine", "L2L3 in fine gen bins;p_{T};#eta", nptbinsFine,ptbinsFine,netabinsFine,etabinsFine);
    TH2F *responseL1L2Corr = new TH2F("responseL1L2Corr", "L1*L2L3*p_{T}(reco)/p_{T}(gen) in gen bins;p_{T};#eta", nptbins,ptbins,netabins,etabins);
    TH2F *responseL1L2CorrFine = new TH2F("responseL1L2CorrFine", "L1*L2L3*p_{T}(reco)/p_{T}(gen) in fine gen bins;p_{T};#eta", nptbinsFine,ptbinsFine,netabinsFine,etabinsFine);
    TH2F *responseL1L2CorrLow = new TH2F("responseL1L2CorrLow", "L1*L2L3*p_{T}(reco)/p_{T}(gen) in semi-fine gen bins;p_{T};#eta", nptbinsLow,ptbinsLow,netabins,etabins);
    TH2F *responseL1L2CorrUnc = new TH2F("responseL1L2CorrUnc", "L1*L2L3*p_{T}(reco)/p_{T}(gen) in JEC uncertainty bins;p_{T};#eta", nptbinsUnc,ptbinsUnc,netabinsUnc,etabinsUnc);

    // TProfile *ptVsEta = new TProfile("ptVsEta", "p_{T}(NoPU) - p_{T}(PU) in gen bins of #eta;#eta;p_{T}^{RECO}", netabinsFineSmall,etabinsFineSmall);
    // TProfile *ptVsEtaL1 = new TProfile("ptVsEtaL1", "p_{T}(NoPU) - L1*p_{T}(PU) in gen bins of #eta;#eta;p_{T}^{RECO}", netabinsFineSmall,etabinsFineSmall);
    // TProfile *ptVsPt = new TProfile("ptVsPt", "p_{T}(NoPU) - p_{T}(PU) in gen bins of p_{T};p_{T};p_{T}^{RECO}", nptbinsFineSmall,ptbinsFineSmall);
    // TProfile *ptVsPtL1 = new TProfile("ptVsPtL1", "p_{T}(NoPU) - L1*p_{T}(PU) in gen bins of p_{T};p_{T};p_{T}^{RECO}", nptbinsFineSmall,ptbinsFineSmall);

    TProfile *ptVsEta = new TProfile("ptVsEta", "p_{T}(PU) - p_{T}(NoPU) in gen bins of #eta;#eta;p_{T}^{RECO}", netabinsFineSmall,etabinsFineSmall);
    TProfile *ptVsEtaL1 = new TProfile("ptVsEtaL1", "L1*p_{T}(PU) - p_{T}(NoPU) in gen bins of #eta;#eta;p_{T}^{RECO}", netabinsFineSmall,etabinsFineSmall);
    TProfile *ptVsPt = new TProfile("ptVsPt", "p_{T}(PU) - p_{T}(NoPU) in gen bins of p_{T};p_{T};p_{T}^{RECO}", nptbinsFineSmall,ptbinsFineSmall);
    TProfile *ptVsPtL1 = new TProfile("ptVsPtL1", "L1*p_{T}(PU) - p_{T}(NoPU) in gen bins of p_{T};p_{T};p_{T}^{RECO}", nptbinsFineSmall,ptbinsFineSmall);

    TH1F *L1chisq = new TH1F("L1chisq", "Fit chi2/ndof for L1;#eta", netabinsFine,etabinsFine);
    TH1F *L2chisq = new TH1F("L2chisq", "Fit chi2/ndof for L2;#eta", netabinsFine,etabinsFine);

    TProfile *corrResponse13 = new TProfile("corrResponse13", ";p_{T}^{GEN} [GeV];Corrected Response", nptbinsFineSmall2,ptbinsFineSmall2);
    TProfile *corrResponse25 = new TProfile("corrResponse25", ";p_{T}^{GEN} [GeV];Corrected Response", nptbinsFineSmall2,ptbinsFineSmall2);
    TProfile *corrResponse30 = new TProfile("corrResponse30", ";p_{T}^{GEN} [GeV];Corrected Response", nptbinsFineSmall2,ptbinsFineSmall2);
    TProfile *corrResponse50 = new TProfile("corrResponse50", ";p_{T}^{GEN} [GeV];Corrected Response", nptbinsFineSmall2,ptbinsFineSmall2);

    TProfile *uncorrResponse13 = new TProfile("uncorrResponse13", ";p_{T}^{GEN} [GeV];Uncorrected Response", nptbinsFineSmall2,ptbinsFineSmall2);
    TProfile *uncorrResponse25 = new TProfile("uncorrResponse25", ";p_{T}^{GEN} [GeV];Uncorrected Response", nptbinsFineSmall2,ptbinsFineSmall2);
    TProfile *uncorrResponse30 = new TProfile("uncorrResponse30", ";p_{T}^{GEN} [GeV];Uncorrected Response", nptbinsFineSmall2,ptbinsFineSmall2);
    TProfile *uncorrResponse50 = new TProfile("uncorrResponse50", ";p_{T}^{GEN} [GeV];Uncorrected Response", nptbinsFineSmall2,ptbinsFineSmall2);

    TH1F *responseEtaRegion = new TH1F("responseEtaRegion", "p_{T}(reco)/p_{T}(gen) in specified #eta", 50,0.0,2.0);
    TH1F *responseEtaRegionL1 = new TH1F("responseEtaRegionL1", "p_{T}(reco)/p_{T}(gen) in specified #eta", 50,0.0,2.0);
    TH1F *responseEtaRegionL1L2 = new TH1F("responseEtaRegionL1L2", "p_{T}(reco)/p_{T}(gen) in specified #eta", 50,0.0,2.0);

    vector<TH1F*> responseRegions;
    vector<TH1F*> responseRegionsL1;
    vector<TH1F*> responseRegionsL1L2;
    for(int i = 0; i < nptbinsFineSmall2; i++) {
        responseRegions.push_back( new TH1F( Form("responseRegions_%.0fto%.0f",ptbinsFineSmall2[i],ptbinsFineSmall2[i+1]), "response", 50, 0.0, 5.0 ) );
        responseRegionsL1.push_back( new TH1F( Form("responseRegionsL1_%.0fto%.0f",ptbinsFineSmall2[i],ptbinsFineSmall2[i+1]), "response L1", 50, 0.0, 5.0 ) );
        responseRegionsL1L2.push_back( new TH1F( Form("responseRegionsL1L2_%.0fto%.0f",ptbinsFineSmall2[i],ptbinsFineSmall2[i+1]), "response L1L2", 50, 0.0, 5.0 ) );
    }




    algo.ToLower();
    // TFile *f = TFile::Open("../crab/all/JRA_PUFlat0to50.root");
    TFile *f = TFile::Open(PUfilename);
    TDirectory* df = f->GetDirectory(algo);
    TTree *tree = (TTree*)df->Get("t");
    TTreeCache::SetLearnEntries(100);
    tree->SetCacheSize(256*1024*1024);
    // tree->Print();

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
    unsigned int nEventsPU = nEventsTree;
    cout << "nEventsPU: " << nEventsPU << endl;

    unsigned int totJets = 0;

    for (unsigned int iEvent=0;iEvent<nEventsPU;iEvent++) {
        tree->GetEntry(iEvent);
        if(debug && iEvent > debugCount) break;
        CMS3::progress( iEvent, nEventsTree );

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

            jetCorrectorL2->setJetEta(jeteta->at(iref));
            jetCorrectorL2->setJetPt(jetpt->at(iref));
            jetCorrectorL2->setJetE(jete->at(iref));

            jetCorrectorL3->setJetEta(jeteta->at(iref));
            jetCorrectorL3->setJetPt(jetpt->at(iref));
            jetCorrectorL3->setJetE(jete->at(iref));

            float jetCorrectionL1 = jetCorrectorL1->getCorrection();
            float jetCorrectionL2 = jetCorrectorL2->getCorrection();
            float jetCorrectionL3 = 1.0; // jetCorrectorL3->getCorrection();

            if ( jetCorrectionL1*resp < 0.0 || jetCorrectionL1*resp > 2.0 ) continue; // FIXME

            float jetCorrectionL2L3 = jetCorrectionL2*jetCorrectionL3;

            TLorentzVector recojet;
            recojet.SetPtEtaPhiE(jetpt->at(iref), jeteta->at(iref), jetphi->at(iref), jete->at(iref));

            TLorentzVector genjet;
            genjet.SetPtEtaPhiE(refpt->at(iref), refeta->at(iref), refphi->at(iref), refe->at(iref));



            if(fabs(jeteta->at(iref)) > 3.0 && fabs(jeteta->at(iref)) < 5.0) {
                int iPt = 0;
                for(int i = 0; i < nptbinsFineSmall2+1; i++) {
                    if( refpt->at(iref) < ptbinsFineSmall2[i] ) {
                        iPt = i-1;
                        break;
                    }
                }
                if(iPt >= 0 && iPt < nptbinsFineSmall2+1) {
                    responseRegions.at(iPt)->Fill( resp );
                    responseRegionsL1.at(iPt)->Fill( jetCorrectionL1*resp );
                    responseRegionsL1L2.at(iPt)->Fill( jetCorrectionL2L3*jetCorrectionL1*resp );
                }
            }


            if(makeMap) {
                Jet j;
                j.PUrecoPt = jetpt->at(iref);
                j.PUrecoEta = jeteta->at(iref);
                j.PUgenPt = refpt->at(iref);
                j.PUgenEta = refeta->at(iref);
                j.correctionL1 = jetCorrectionL1;
                j.correctionL2 = jetCorrectionL2;
                JetMap[(int)(event * 100) + iref] = j;
            }

            // FILL HISTS

            response->Fill(genjet.Pt(), genjet.Eta(), resp);
            responseFine->Fill(genjet.Pt(), genjet.Eta(), resp);
            counts->Fill(genjet.Pt(), genjet.Eta());
            countsFine->Fill(genjet.Pt(), genjet.Eta());
            countsLow->Fill(genjet.Pt(), genjet.Eta());
            countsUnc->Fill(genjet.Pt(), genjet.Eta());

            L1pt->Fill(genjet.Pt(), jetCorrectionL1);
            L1eta->Fill(genjet.Eta(), jetCorrectionL1);
            L1corr->Fill(genjet.Pt(), genjet.Eta(), jetCorrectionL1);
            L1corrFine->Fill(genjet.Pt(), genjet.Eta(), jetCorrectionL1);
            responseL1Corr->Fill(genjet.Pt(), genjet.Eta(), resp*jetCorrectionL1);
            responseL1CorrFine->Fill(genjet.Pt(), genjet.Eta(), resp*jetCorrectionL1);

            L2pt->Fill(genjet.Pt(), jetCorrectionL2L3);
            L2eta->Fill(genjet.Eta(), jetCorrectionL2L3);
            L2corr->Fill(genjet.Pt(), genjet.Eta(), jetCorrectionL2L3);
            L2corrFine->Fill(genjet.Pt(), genjet.Eta(), jetCorrectionL2L3);
            responseL1L2Corr->Fill(genjet.Pt(), genjet.Eta(), resp*jetCorrectionL1*jetCorrectionL2L3);
            responseL1L2CorrFine->Fill(genjet.Pt(), genjet.Eta(), resp*jetCorrectionL1*jetCorrectionL2L3);
            responseL1L2CorrUnc->Fill(genjet.Pt(), genjet.Eta(), resp*jetCorrectionL1*jetCorrectionL2L3);
            responseL1L2CorrLow->Fill(genjet.Pt(), genjet.Eta(), resp*jetCorrectionL1*jetCorrectionL2L3);

            if( jeteta->at(iref) < 0.087 && jeteta->at(iref) > 0.0 ) { // FIXME
                if(refpt->at(iref) > 10 && refpt->at(iref) < 11) {
                    responseEtaRegion->Fill(resp);
                    responseEtaRegionL1->Fill(jetCorrectionL1*resp);
                    responseEtaRegionL1L2->Fill(jetCorrectionL2L3*jetCorrectionL1*resp);
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
        TFile *f = TFile::Open("../JRA_NoPU.root");
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
        cout << "nEventsNoPU: " << nEventsNoPU << endl;

        unsigned int totJets = 0;

        for (unsigned int iEvent=0;iEvent<nEventsNoPU;iEvent++) {
            tree->GetEntry(iEvent);
            if(debug && iEvent > debugCount) break;
            CMS3::progress( iEvent, nEventsTree );

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
                if(debug) normToPU = 1.0;

                if(makeMap) {
                    if(JetMap.count( (int)(event * 100) + iref )) {
                        JetMap[(int)(event*100)+iref].NoPUrecoPt = jetpt->at(iref);
                        JetMap[(int)(event*100)+iref].NoPUrecoEta = jeteta->at(iref);
                        JetMap[(int)(event*100)+iref].NoPUgenPt = refpt->at(iref);
                        JetMap[(int)(event*100)+iref].NoPUgenEta = refeta->at(iref);
                        JetMap[(int)(event*100)+iref].matched = true;
                    }
                }

                jetCorrectorL2->setJetEta(jeteta->at(iref));
                jetCorrectorL2->setJetPt(jetpt->at(iref));
                jetCorrectorL2->setJetE(jete->at(iref));
                float jetCorrectionL2 = jetCorrectorL2->getCorrection();


            }
        }

        cout << "Considered " << totJets << " NoPU jets in total." << endl;

    }


    int matchedJets = 0;
    if(makeMap) {
        for(auto const &jet : JetMap) {
            if(!jet.second.matched) continue;

            Jet j = jet.second;

            matchedJets++;

            ptVsPt->Fill(j.PUgenPt, -(j.NoPUrecoPt-j.PUrecoPt));
            ptVsPtL1->Fill(j.PUgenPt, -(j.NoPUrecoPt-j.correctionL1*j.PUrecoPt));

            ptVsEta->Fill(j.PUgenEta, -(j.NoPUrecoPt-j.PUrecoPt));
            ptVsEtaL1->Fill(j.PUgenEta, -(j.NoPUrecoPt-j.correctionL1*j.PUrecoPt));

            float response = j.PUrecoPt/j.PUgenPt;
            float corrResponse = j.correctionL1*j.correctionL2*j.PUrecoPt/j.PUgenPt;

            if(fabs(j.PUrecoEta) < 1.3) {
                corrResponse13->Fill(j.PUgenPt,corrResponse);
                uncorrResponse13->Fill(j.PUgenPt,response);
            }
            else if(fabs(j.PUrecoEta) < 2.5 && fabs(j.PUrecoEta) > 1.3) {
                corrResponse25->Fill(j.PUgenPt,corrResponse);
                uncorrResponse25->Fill(j.PUgenPt,response);
            }
            else if(fabs(j.PUrecoEta) < 3.0 && fabs(j.PUrecoEta) > 2.5) {
                corrResponse30->Fill(j.PUgenPt,corrResponse);
                uncorrResponse30->Fill(j.PUgenPt,response);
            }
            else if(fabs(j.PUrecoEta) < 5.0 && fabs(j.PUrecoEta) > 3.0) {
                corrResponse50->Fill(j.PUgenPt,corrResponse);
                uncorrResponse50->Fill(j.PUgenPt,response);
            }


        }
    }
    cout << matchedJets << " matched jets" << endl;

    TString plotdir = "plots/";
    prefix += algo + "_";

    TCanvas *c1 = new TCanvas("c1");


    //////////
    // MISC //
    //////////
    gStyle->SetOptStat("ormen");
    gStyle->SetOptFit(0001);

    for(unsigned int i = 0; i < responseRegions.size(); i++) {
        doFit(responseRegions[i]);
        myStyle2(responseRegions[i]);
        addOverflow(responseRegions[i]);
        responseRegions[i]->Draw("PE");
        c1->SaveAs(Form("%s%sresponseRegions_%i.pdf",plotdir.Data(),prefix.Data(),i));
        
        doFit(responseRegionsL1[i]);
        myStyle2(responseRegionsL1[i]);
        addOverflow(responseRegionsL1[i]);
        responseRegionsL1[i]->Draw("PE");
        c1->SaveAs(Form("%s%sresponseRegionsL1_%i.pdf",plotdir.Data(),prefix.Data(),i));

        doFit(responseRegionsL1L2[i], true);
        myStyle2(responseRegionsL1L2[i]);
        addOverflow(responseRegionsL1L2[i]);
        responseRegionsL1L2[i]->Draw("PE");
        c1->SaveAs(Form("%s%sresponseRegionsL1L2_%i.pdf",plotdir.Data(),prefix.Data(),i));

    }


    myStyle2(responseEtaRegion);
    responseEtaRegion->Draw("PE");
    addOverflow(responseEtaRegion);
    c1->SaveAs(plotdir+prefix+"responseEtaRegion.pdf");

    myStyle2(responseEtaRegionL1);
    responseEtaRegionL1->Draw("PE");
    addOverflow(responseEtaRegionL1);
    c1->SaveAs(plotdir+prefix+"responseEtaRegionL1.pdf");

    myStyle2(responseEtaRegionL1L2);
    responseEtaRegionL1L2->Draw("PE");
    addOverflow(responseEtaRegionL1L2);
    c1->SaveAs(plotdir+prefix+"responseEtaRegionL1L2.pdf");

    gStyle->SetOptStat(0);
    gStyle->SetOptFit(0);

    counts->Draw("colztext");
    c1->SaveAs(plotdir+prefix+"counts.pdf");

    response->Divide(counts);
    response->SetMaximum(1.2);
    response->SetMinimum(0.8);
    response->Draw("colztexte");
    c1->SaveAs(plotdir+prefix+"response.pdf");

    c1->SetLogx(1);
    responseFine->Divide(countsFine);
    responseFine->SetMaximum(2.0);
    responseFine->SetMinimum(0.0);
    responseFine->Draw("colz");
    c1->SaveAs(plotdir+prefix+"responseFine.pdf");
    c1->SetLogx(0);


    for (int ieta = 0; ieta < 82; ieta++) {
        L1chisq->SetBinContent(ieta, chiSqL1[ieta]);
        L2chisq->SetBinContent(ieta, chiSqL2[ieta]);
    }

    myStyle2(L1chisq);
    L1chisq->Draw("P");
    c1->SaveAs(plotdir+prefix+"L1chisq.pdf");

    myStyle2(L2chisq);
    L2chisq->Draw("P");
    c1->SaveAs(plotdir+prefix+"L2chisq.pdf");

    TLegend* leg = new TLegend(0.7,0.15,0.89,0.35);
    leg->SetFillStyle(0);
    leg->SetLineColor(kWhite);

    c1->SetLogx(1);
    corrResponse13->GetYaxis()->SetRangeUser(0.8,1.2);
    corrResponse25->GetYaxis()->SetRangeUser(0.8,1.2);
    corrResponse30->GetYaxis()->SetRangeUser(0.8,1.2);
    corrResponse50->GetYaxis()->SetRangeUser(0.8,1.2);

    corrResponse13->SetMarkerStyle(kFullCircle);
    corrResponse13->SetMarkerColor(kBlack);
    corrResponse13->SetLineColor(kBlack);
    corrResponse13->GetXaxis()->SetMoreLogLabels();
    corrResponse13->GetXaxis()->SetNoExponent();
    corrResponse13->Draw("PE");
    leg->AddEntry(corrResponse13,"|#eta|<1.3","lep");

    corrResponse25->Draw("SAMEPE");
    corrResponse25->SetMarkerStyle(kOpenCircle);
    corrResponse25->SetMarkerColor(kBlue);
    corrResponse25->SetLineColor(kBlue);
    leg->AddEntry(corrResponse25,"1.3<|#eta|<2.5","lep");

    corrResponse30->Draw("SAMEPE");
    corrResponse30->SetMarkerStyle(kFullTriangleUp);
    corrResponse30->SetMarkerColor(kRed);
    corrResponse30->SetLineColor(kRed);
    leg->AddEntry(corrResponse30,"2.5<|#eta|<3.0","lep");

    corrResponse50->Draw("SAMEPE");
    corrResponse50->SetMarkerStyle(kOpenTriangleUp);
    corrResponse50->SetMarkerColor(kMagenta);
    corrResponse50->SetLineColor(kMagenta);
    leg->AddEntry(corrResponse50,"3.0<|#eta|<5.0","lep");

    leg->Draw();

    TF1 *line1 = new TF1("line1","0*x+1.02",0,5000);
    TF1 *line2 = new TF1("line2","0*x+0.98",0,5000);
    line1->SetLineColor(1);
    line1->SetLineWidth(1);
    line1->SetLineStyle(2);
    line2->SetLineColor(1);
    line2->SetLineWidth(1);
    line2->SetLineStyle(2);
    line1->Draw("same");
    line2->Draw("same");

    c1->SaveAs(plotdir+prefix+"corrResponse.pdf");
    c1->SetLogx(0);


    c1->SetLogx(1);
    uncorrResponse13->GetYaxis()->SetRangeUser(0.8,1.6);
    uncorrResponse25->GetYaxis()->SetRangeUser(0.8,1.6);
    uncorrResponse30->GetYaxis()->SetRangeUser(0.8,1.6);
    uncorrResponse50->GetYaxis()->SetRangeUser(0.8,1.6);

    uncorrResponse13->SetMarkerStyle(kFullCircle);
    uncorrResponse13->SetMarkerColor(kBlack);
    uncorrResponse13->SetLineColor(kBlack);
    uncorrResponse13->GetXaxis()->SetMoreLogLabels();
    uncorrResponse13->GetXaxis()->SetNoExponent();
    uncorrResponse13->Draw("PE");

    uncorrResponse25->Draw("SAMEPE");
    uncorrResponse25->SetMarkerStyle(kOpenCircle);
    uncorrResponse25->SetMarkerColor(kBlue);
    uncorrResponse25->SetLineColor(kBlue);

    uncorrResponse30->Draw("SAMEPE");
    uncorrResponse30->SetMarkerStyle(kFullTriangleUp);
    uncorrResponse30->SetMarkerColor(kRed);
    uncorrResponse30->SetLineColor(kRed);

    uncorrResponse50->Draw("SAMEPE");
    uncorrResponse50->SetMarkerStyle(kOpenTriangleUp);
    uncorrResponse50->SetMarkerColor(kMagenta);
    uncorrResponse50->SetLineColor(kMagenta);


    leg->Draw();
    c1->SaveAs(plotdir+prefix+"uncorrResponse.pdf");
    c1->SetLogx(0);


    /////////////////////
    // L1 CORRECTIONS  //
    /////////////////////


    responseL1Corr->Divide(counts);
    responseL1Corr->SetMaximum(1.2);
    responseL1Corr->SetMinimum(0.8);
    responseL1Corr->Draw("colztexte");
    c1->SaveAs(plotdir+prefix+"responseL1Corr.pdf");

    c1->SetLogx(1);
    responseL1CorrFine->Divide(countsFine);
    responseL1CorrFine->SetMaximum(2.0);
    responseL1CorrFine->SetMinimum(0.0);
    responseL1CorrFine->Draw("colz");
    c1->SaveAs(plotdir+prefix+"responseL1CorrFine.pdf");
    c1->SetLogx(0);

    L1corr->Divide(counts);
    L1corr->SetMaximum(1.2);
    L1corr->SetMinimum(0.8);
    L1corr->Draw("colztexte");
    c1->SaveAs(plotdir+prefix+"L1corr.pdf");

    c1->SetLogx(1);
    L1corrFine->Divide(countsFine);
    L1corrFine->SetMaximum(2.0);
    L1corrFine->SetMinimum(0.0);
    L1corrFine->Draw("colz");
    c1->SaveAs(plotdir+prefix+"L1corrFine.pdf");
    c1->SetLogx(0);

    myStyle(L1pt);
    L1pt->Draw("PE");
    c1->SaveAs(plotdir+prefix+"L1pt.pdf");

    myStyle(L1eta);
    L1eta->Draw("PE");
    c1->SaveAs(plotdir+prefix+"L1eta.pdf");

    ptVsEta->GetYaxis()->SetRangeUser(-10.0,10.0);
    myStyle(ptVsEta);
    ptVsEta->Draw("PE");
    c1->SaveAs(plotdir+prefix+"ptVsEta.pdf");

    ptVsEtaL1->GetYaxis()->SetRangeUser(-10.0,10.0);
    myStyle(ptVsEtaL1);
    ptVsEtaL1->Draw("PE");
    c1->SaveAs(plotdir+prefix+"ptVsEtaL1.pdf");

    c1->SetLogx(1);
    ptVsPt->GetYaxis()->SetRangeUser(-10.0,10.0);
    myStyle(ptVsPt);
    ptVsPt->Draw("PE");
    c1->SaveAs(plotdir+prefix+"ptVsPt.pdf");
    c1->SetLogx(0);

    c1->SetLogx(1);
    ptVsPtL1->GetYaxis()->SetRangeUser(-10.0,10.0);
    myStyle(ptVsPtL1);
    ptVsPtL1->Draw("PE");
    c1->SaveAs(plotdir+prefix+"ptVsPtL1.pdf");
    c1->SetLogx(0);

    /////////////////////
    // L2 CORRECTIONS  //
    /////////////////////

    responseL1L2Corr->Divide(counts);
    responseL1L2Corr->SetMaximum(2.0);
    responseL1L2Corr->SetMinimum(0.0);
    responseL1L2Corr->Draw("colztexte");
    c1->SaveAs(plotdir+prefix+"responseL1L2Corr.pdf");

    c1->SetLogx(1);
    responseL1L2CorrFine->Divide(countsFine);
    responseL1L2CorrFine->SetMaximum(2.0);
    responseL1L2CorrFine->SetMinimum(0.0);
    responseL1L2CorrFine->Draw("colz");
    c1->SaveAs(plotdir+prefix+"responseL1L2CorrFine.pdf");
    c1->SetLogx(0);

    c1->SetLogx(1);
    responseL1L2CorrLow->Divide(countsLow);
    responseL1L2CorrLow->SetMaximum(1.2);
    responseL1L2CorrLow->SetMinimum(0.8);
    responseL1L2CorrLow->Draw("colz");
    c1->SaveAs(plotdir+prefix+"responseL1L2CorrLow.pdf");
    c1->SetLogx(0);

    L2corr->Divide(counts);
    L2corr->SetMaximum(1.2);
    L2corr->SetMinimum(0.8);
    L2corr->Draw("colztexte");
    c1->SaveAs(plotdir+prefix+"L2corr.pdf");

    c1->SetLogx(1);
    L2corrFine->Divide(countsFine);
    L2corrFine->SetMaximum(2.0);
    L2corrFine->SetMinimum(0.0);
    L2corrFine->Draw("colz");
    c1->SaveAs(plotdir+prefix+"L2corrFine.pdf");
    c1->SetLogx(0);

    L2pt->SetMarkerStyle(21);
    L2pt->SetMarkerSize(1.0);
    L2pt->SetMarkerColor(kRed);
    L2pt->SetLineColor(kRed);
    L2pt->Draw("PE");
    c1->SaveAs(plotdir+prefix+"L2pt.pdf");

    L2eta->SetMarkerStyle(21);
    L2eta->SetMarkerSize(1.0);
    L2eta->SetMarkerColor(kRed);
    L2eta->SetLineColor(kRed);
    L2eta->Draw("PE");
    c1->SaveAs(plotdir+prefix+"L2eta.pdf");


    // TEXT FILE
    
    TAxis *xaxis = responseL1L2CorrUnc->GetXaxis();
    TAxis *yaxis = responseL1L2CorrUnc->GetYaxis();
    ofstream outfile;
    outfile.open( (prefix+"unc.txt").Data() );
    for (int i=1; i<=xaxis->GetNbins(); i++) {
        for (int j=1; j<=yaxis->GetNbins(); j++) {
            float xlow = xaxis->GetBinLowEdge(i);
            float ylow = yaxis->GetBinLowEdge(j);
            int bin = responseL1L2CorrUnc->GetBin(i,j);
            float sumResponse = responseL1L2CorrUnc->GetBinContent(bin);
            float counts = countsUnc->GetBinContent(bin);
            outfile << ylow << " " << xlow << " " << sumResponse << " " << counts << " " << endl;
        }
    }
    outfile.close();

    JetMap.clear();

    return 0;
}
