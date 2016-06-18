// -*- C++ -*-
#ifndef CMS3_H
#define CMS3_H
#include "Math/LorentzVector.h"
#include "Math/Point3D.h"
#include "TMath.h"
#include "TBranch.h"
#include "TTree.h"
#include "TH1F.h"
#include "TFile.h"
#include "TDirectory.h"
#include "TDirectoryFile.h"
#include "TBits.h"
#include <vector> 
#include <unistd.h> 
typedef ROOT::Math::LorentzVector<ROOT::Math::PxPyPzE4D<float> > LorentzVector;

// Generated with the command
// makeCMS3ClassFiles("ak4pf", "t", "CMS3", "tas", "cms3")

using namespace std; 
class CMS3 {
private: 
protected: 
	unsigned int index;
	vector<int> *npus_;
	TBranch *npus_branch;
	bool npus_isLoaded;
	vector<float> *tnpus_;
	TBranch *tnpus_branch;
	bool tnpus_isLoaded;
	vector<float> *zpositions_;
	TBranch *zpositions_branch;
	bool zpositions_isLoaded;
	vector<int> *bxns_;
	TBranch *bxns_branch;
	bool bxns_isLoaded;
	vector<float> *sumpt_lowpt_;
	TBranch *sumpt_lowpt_branch;
	bool sumpt_lowpt_isLoaded;
	vector<float> *sumpt_highpt_;
	TBranch *sumpt_highpt_branch;
	bool sumpt_highpt_isLoaded;
	vector<int> *ntrks_lowpt_;
	TBranch *ntrks_lowpt_branch;
	bool ntrks_lowpt_isLoaded;
	vector<int> *ntrks_highpt_;
	TBranch *ntrks_highpt_branch;
	bool ntrks_highpt_isLoaded;
	vector<float> *rhos_;
	TBranch *rhos_branch;
	bool rhos_isLoaded;
	float	rho_;
	TBranch *rho_branch;
	bool rho_isLoaded;
	float	pthat_;
	TBranch *pthat_branch;
	bool pthat_isLoaded;
	float	beta_;
	TBranch *beta_branch;
	bool beta_isLoaded;
	float	betaStar_;
	TBranch *betaStar_branch;
	bool betaStar_isLoaded;
	float	weight_;
	TBranch *weight_branch;
	bool weight_isLoaded;
	vector<int> *refpdgid_;
	TBranch *refpdgid_branch;
	bool refpdgid_isLoaded;
	vector<int> *refpdgid_algorithmicDef_;
	TBranch *refpdgid_algorithmicDef_branch;
	bool refpdgid_algorithmicDef_isLoaded;
	vector<int> *refpdgid_physicsDef_;
	TBranch *refpdgid_physicsDef_branch;
	bool refpdgid_physicsDef_isLoaded;
	vector<float> *refe_;
	TBranch *refe_branch;
	bool refe_isLoaded;
	vector<float> *refpt_;
	TBranch *refpt_branch;
	bool refpt_isLoaded;
	vector<float> *refeta_;
	TBranch *refeta_branch;
	bool refeta_isLoaded;
	vector<float> *refphi_;
	TBranch *refphi_branch;
	bool refphi_isLoaded;
	vector<float> *refy_;
	TBranch *refy_branch;
	bool refy_isLoaded;
	vector<float> *refdrjt_;
	TBranch *refdrjt_branch;
	bool refdrjt_isLoaded;
	vector<float> *refarea_;
	TBranch *refarea_branch;
	bool refarea_isLoaded;
	vector<float> *jte_;
	TBranch *jte_branch;
	bool jte_isLoaded;
	vector<float> *jtpt_;
	TBranch *jtpt_branch;
	bool jtpt_isLoaded;
	vector<float> *jteta_;
	TBranch *jteta_branch;
	bool jteta_isLoaded;
	vector<float> *jtphi_;
	TBranch *jtphi_branch;
	bool jtphi_isLoaded;
	vector<float> *jty_;
	TBranch *jty_branch;
	bool jty_isLoaded;
	vector<float> *jtjec_;
	TBranch *jtjec_branch;
	bool jtjec_isLoaded;
	vector<float> *jtarea_;
	TBranch *jtarea_branch;
	bool jtarea_isLoaded;
	vector<float> *jtchf_;
	TBranch *jtchf_branch;
	bool jtchf_isLoaded;
	vector<float> *jtnhf_;
	TBranch *jtnhf_branch;
	bool jtnhf_isLoaded;
	vector<float> *jtnef_;
	TBranch *jtnef_branch;
	bool jtnef_isLoaded;
	vector<float> *jtcef_;
	TBranch *jtcef_branch;
	bool jtcef_isLoaded;
	vector<float> *jtmuf_;
	TBranch *jtmuf_branch;
	bool jtmuf_isLoaded;
	vector<float> *jthfhf_;
	TBranch *jthfhf_branch;
	bool jthfhf_isLoaded;
	vector<float> *jthfef_;
	TBranch *jthfef_branch;
	bool jthfef_isLoaded;
	vector<float> *refdzvtx_;
	TBranch *refdzvtx_branch;
	bool refdzvtx_isLoaded;
public: 
void Init(TTree *tree);
void GetEntry(unsigned int idx); 
void LoadAllBranches(); 
	const vector<int> &npus();
	const vector<float> &tnpus();
	const vector<float> &zpositions();
	const vector<int> &bxns();
	const vector<float> &sumpt_lowpt();
	const vector<float> &sumpt_highpt();
	const vector<int> &ntrks_lowpt();
	const vector<int> &ntrks_highpt();
	const vector<float> &rhos();
	const float &rho();
	const float &pthat();
	const float &beta();
	const float &betaStar();
	const float &weight();
	const vector<int> &refpdgid();
	const vector<int> &refpdgid_algorithmicDef();
	const vector<int> &refpdgid_physicsDef();
	const vector<float> &refe();
	const vector<float> &refpt();
	const vector<float> &refeta();
	const vector<float> &refphi();
	const vector<float> &refy();
	const vector<float> &refdrjt();
	const vector<float> &refarea();
	const vector<float> &jte();
	const vector<float> &jtpt();
	const vector<float> &jteta();
	const vector<float> &jtphi();
	const vector<float> &jty();
	const vector<float> &jtjec();
	const vector<float> &jtarea();
	const vector<float> &jtchf();
	const vector<float> &jtnhf();
	const vector<float> &jtnef();
	const vector<float> &jtcef();
	const vector<float> &jtmuf();
	const vector<float> &jthfhf();
	const vector<float> &jthfef();
	const vector<float> &refdzvtx();

  static void progress( int nEventsTotal, int nEventsChain );
};

#ifndef __CINT__
extern CMS3 cms3;
#endif

namespace tas {
	const vector<int> &npus();
	const vector<float> &tnpus();
	const vector<float> &zpositions();
	const vector<int> &bxns();
	const vector<float> &sumpt_lowpt();
	const vector<float> &sumpt_highpt();
	const vector<int> &ntrks_lowpt();
	const vector<int> &ntrks_highpt();
	const vector<float> &rhos();
	const float &rho();
	const float &pthat();
	const float &beta();
	const float &betaStar();
	const float &weight();
	const vector<int> &refpdgid();
	const vector<int> &refpdgid_algorithmicDef();
	const vector<int> &refpdgid_physicsDef();
	const vector<float> &refe();
	const vector<float> &refpt();
	const vector<float> &refeta();
	const vector<float> &refphi();
	const vector<float> &refy();
	const vector<float> &refdrjt();
	const vector<float> &refarea();
	const vector<float> &jte();
	const vector<float> &jtpt();
	const vector<float> &jteta();
	const vector<float> &jtphi();
	const vector<float> &jty();
	const vector<float> &jtjec();
	const vector<float> &jtarea();
	const vector<float> &jtchf();
	const vector<float> &jtnhf();
	const vector<float> &jtnef();
	const vector<float> &jtcef();
	const vector<float> &jtmuf();
	const vector<float> &jthfhf();
	const vector<float> &jthfef();
	const vector<float> &refdzvtx();
}
#endif
