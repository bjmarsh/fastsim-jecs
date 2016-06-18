#include "CMS3.h"
CMS3 cms3;

void CMS3::Init(TTree *tree) {
  tree->SetMakeClass(1);
	npus_branch = 0;
	if (tree->GetBranch("npus") != 0) {
		npus_branch = tree->GetBranch("npus");
		if (npus_branch) {npus_branch->SetAddress(&npus_);}
	}
	tnpus_branch = 0;
	if (tree->GetBranch("tnpus") != 0) {
		tnpus_branch = tree->GetBranch("tnpus");
		if (tnpus_branch) {tnpus_branch->SetAddress(&tnpus_);}
	}
	zpositions_branch = 0;
	if (tree->GetBranch("zpositions") != 0) {
		zpositions_branch = tree->GetBranch("zpositions");
		if (zpositions_branch) {zpositions_branch->SetAddress(&zpositions_);}
	}
	bxns_branch = 0;
	if (tree->GetBranch("bxns") != 0) {
		bxns_branch = tree->GetBranch("bxns");
		if (bxns_branch) {bxns_branch->SetAddress(&bxns_);}
	}
	sumpt_lowpt_branch = 0;
	if (tree->GetBranch("sumpt_lowpt") != 0) {
		sumpt_lowpt_branch = tree->GetBranch("sumpt_lowpt");
		if (sumpt_lowpt_branch) {sumpt_lowpt_branch->SetAddress(&sumpt_lowpt_);}
	}
	sumpt_highpt_branch = 0;
	if (tree->GetBranch("sumpt_highpt") != 0) {
		sumpt_highpt_branch = tree->GetBranch("sumpt_highpt");
		if (sumpt_highpt_branch) {sumpt_highpt_branch->SetAddress(&sumpt_highpt_);}
	}
	ntrks_lowpt_branch = 0;
	if (tree->GetBranch("ntrks_lowpt") != 0) {
		ntrks_lowpt_branch = tree->GetBranch("ntrks_lowpt");
		if (ntrks_lowpt_branch) {ntrks_lowpt_branch->SetAddress(&ntrks_lowpt_);}
	}
	ntrks_highpt_branch = 0;
	if (tree->GetBranch("ntrks_highpt") != 0) {
		ntrks_highpt_branch = tree->GetBranch("ntrks_highpt");
		if (ntrks_highpt_branch) {ntrks_highpt_branch->SetAddress(&ntrks_highpt_);}
	}
	rhos_branch = 0;
	if (tree->GetBranch("rhos") != 0) {
		rhos_branch = tree->GetBranch("rhos");
		if (rhos_branch) {rhos_branch->SetAddress(&rhos_);}
	}
	rho_branch = 0;
	if (tree->GetBranch("rho") != 0) {
		rho_branch = tree->GetBranch("rho");
		if (rho_branch) {rho_branch->SetAddress(&rho_);}
	}
	pthat_branch = 0;
	if (tree->GetBranch("pthat") != 0) {
		pthat_branch = tree->GetBranch("pthat");
		if (pthat_branch) {pthat_branch->SetAddress(&pthat_);}
	}
	beta_branch = 0;
	if (tree->GetBranch("beta") != 0) {
		beta_branch = tree->GetBranch("beta");
		if (beta_branch) {beta_branch->SetAddress(&beta_);}
	}
	betaStar_branch = 0;
	if (tree->GetBranch("betaStar") != 0) {
		betaStar_branch = tree->GetBranch("betaStar");
		if (betaStar_branch) {betaStar_branch->SetAddress(&betaStar_);}
	}
	weight_branch = 0;
	if (tree->GetBranch("weight") != 0) {
		weight_branch = tree->GetBranch("weight");
		if (weight_branch) {weight_branch->SetAddress(&weight_);}
	}
	refpdgid_branch = 0;
	if (tree->GetBranch("refpdgid") != 0) {
		refpdgid_branch = tree->GetBranch("refpdgid");
		if (refpdgid_branch) {refpdgid_branch->SetAddress(&refpdgid_);}
	}
	refpdgid_algorithmicDef_branch = 0;
	if (tree->GetBranch("refpdgid_algorithmicDef") != 0) {
		refpdgid_algorithmicDef_branch = tree->GetBranch("refpdgid_algorithmicDef");
		if (refpdgid_algorithmicDef_branch) {refpdgid_algorithmicDef_branch->SetAddress(&refpdgid_algorithmicDef_);}
	}
	refpdgid_physicsDef_branch = 0;
	if (tree->GetBranch("refpdgid_physicsDef") != 0) {
		refpdgid_physicsDef_branch = tree->GetBranch("refpdgid_physicsDef");
		if (refpdgid_physicsDef_branch) {refpdgid_physicsDef_branch->SetAddress(&refpdgid_physicsDef_);}
	}
	refe_branch = 0;
	if (tree->GetBranch("refe") != 0) {
		refe_branch = tree->GetBranch("refe");
		if (refe_branch) {refe_branch->SetAddress(&refe_);}
	}
	refpt_branch = 0;
	if (tree->GetBranch("refpt") != 0) {
		refpt_branch = tree->GetBranch("refpt");
		if (refpt_branch) {refpt_branch->SetAddress(&refpt_);}
	}
	refeta_branch = 0;
	if (tree->GetBranch("refeta") != 0) {
		refeta_branch = tree->GetBranch("refeta");
		if (refeta_branch) {refeta_branch->SetAddress(&refeta_);}
	}
	refphi_branch = 0;
	if (tree->GetBranch("refphi") != 0) {
		refphi_branch = tree->GetBranch("refphi");
		if (refphi_branch) {refphi_branch->SetAddress(&refphi_);}
	}
	refy_branch = 0;
	if (tree->GetBranch("refy") != 0) {
		refy_branch = tree->GetBranch("refy");
		if (refy_branch) {refy_branch->SetAddress(&refy_);}
	}
	refdrjt_branch = 0;
	if (tree->GetBranch("refdrjt") != 0) {
		refdrjt_branch = tree->GetBranch("refdrjt");
		if (refdrjt_branch) {refdrjt_branch->SetAddress(&refdrjt_);}
	}
	refarea_branch = 0;
	if (tree->GetBranch("refarea") != 0) {
		refarea_branch = tree->GetBranch("refarea");
		if (refarea_branch) {refarea_branch->SetAddress(&refarea_);}
	}
	jte_branch = 0;
	if (tree->GetBranch("jte") != 0) {
		jte_branch = tree->GetBranch("jte");
		if (jte_branch) {jte_branch->SetAddress(&jte_);}
	}
	jtpt_branch = 0;
	if (tree->GetBranch("jtpt") != 0) {
		jtpt_branch = tree->GetBranch("jtpt");
		if (jtpt_branch) {jtpt_branch->SetAddress(&jtpt_);}
	}
	jteta_branch = 0;
	if (tree->GetBranch("jteta") != 0) {
		jteta_branch = tree->GetBranch("jteta");
		if (jteta_branch) {jteta_branch->SetAddress(&jteta_);}
	}
	jtphi_branch = 0;
	if (tree->GetBranch("jtphi") != 0) {
		jtphi_branch = tree->GetBranch("jtphi");
		if (jtphi_branch) {jtphi_branch->SetAddress(&jtphi_);}
	}
	jty_branch = 0;
	if (tree->GetBranch("jty") != 0) {
		jty_branch = tree->GetBranch("jty");
		if (jty_branch) {jty_branch->SetAddress(&jty_);}
	}
	jtjec_branch = 0;
	if (tree->GetBranch("jtjec") != 0) {
		jtjec_branch = tree->GetBranch("jtjec");
		if (jtjec_branch) {jtjec_branch->SetAddress(&jtjec_);}
	}
	jtarea_branch = 0;
	if (tree->GetBranch("jtarea") != 0) {
		jtarea_branch = tree->GetBranch("jtarea");
		if (jtarea_branch) {jtarea_branch->SetAddress(&jtarea_);}
	}
	jtchf_branch = 0;
	if (tree->GetBranch("jtchf") != 0) {
		jtchf_branch = tree->GetBranch("jtchf");
		if (jtchf_branch) {jtchf_branch->SetAddress(&jtchf_);}
	}
	jtnhf_branch = 0;
	if (tree->GetBranch("jtnhf") != 0) {
		jtnhf_branch = tree->GetBranch("jtnhf");
		if (jtnhf_branch) {jtnhf_branch->SetAddress(&jtnhf_);}
	}
	jtnef_branch = 0;
	if (tree->GetBranch("jtnef") != 0) {
		jtnef_branch = tree->GetBranch("jtnef");
		if (jtnef_branch) {jtnef_branch->SetAddress(&jtnef_);}
	}
	jtcef_branch = 0;
	if (tree->GetBranch("jtcef") != 0) {
		jtcef_branch = tree->GetBranch("jtcef");
		if (jtcef_branch) {jtcef_branch->SetAddress(&jtcef_);}
	}
	jtmuf_branch = 0;
	if (tree->GetBranch("jtmuf") != 0) {
		jtmuf_branch = tree->GetBranch("jtmuf");
		if (jtmuf_branch) {jtmuf_branch->SetAddress(&jtmuf_);}
	}
	jthfhf_branch = 0;
	if (tree->GetBranch("jthfhf") != 0) {
		jthfhf_branch = tree->GetBranch("jthfhf");
		if (jthfhf_branch) {jthfhf_branch->SetAddress(&jthfhf_);}
	}
	jthfef_branch = 0;
	if (tree->GetBranch("jthfef") != 0) {
		jthfef_branch = tree->GetBranch("jthfef");
		if (jthfef_branch) {jthfef_branch->SetAddress(&jthfef_);}
	}
	refdzvtx_branch = 0;
	if (tree->GetBranch("refdzvtx") != 0) {
		refdzvtx_branch = tree->GetBranch("refdzvtx");
		if (refdzvtx_branch) {refdzvtx_branch->SetAddress(&refdzvtx_);}
	}
  tree->SetMakeClass(0);
}
void CMS3::GetEntry(unsigned int idx) 
	// this only marks branches as not loaded, saving a lot of time
	{
		index = idx;
		npus_isLoaded = false;
		tnpus_isLoaded = false;
		zpositions_isLoaded = false;
		bxns_isLoaded = false;
		sumpt_lowpt_isLoaded = false;
		sumpt_highpt_isLoaded = false;
		ntrks_lowpt_isLoaded = false;
		ntrks_highpt_isLoaded = false;
		rhos_isLoaded = false;
		rho_isLoaded = false;
		pthat_isLoaded = false;
		beta_isLoaded = false;
		betaStar_isLoaded = false;
		weight_isLoaded = false;
		refpdgid_isLoaded = false;
		refpdgid_algorithmicDef_isLoaded = false;
		refpdgid_physicsDef_isLoaded = false;
		refe_isLoaded = false;
		refpt_isLoaded = false;
		refeta_isLoaded = false;
		refphi_isLoaded = false;
		refy_isLoaded = false;
		refdrjt_isLoaded = false;
		refarea_isLoaded = false;
		jte_isLoaded = false;
		jtpt_isLoaded = false;
		jteta_isLoaded = false;
		jtphi_isLoaded = false;
		jty_isLoaded = false;
		jtjec_isLoaded = false;
		jtarea_isLoaded = false;
		jtchf_isLoaded = false;
		jtnhf_isLoaded = false;
		jtnef_isLoaded = false;
		jtcef_isLoaded = false;
		jtmuf_isLoaded = false;
		jthfhf_isLoaded = false;
		jthfef_isLoaded = false;
		refdzvtx_isLoaded = false;
	}

void CMS3::LoadAllBranches() 
	// load all branches
{
	if (npus_branch != 0) npus();
	if (tnpus_branch != 0) tnpus();
	if (zpositions_branch != 0) zpositions();
	if (bxns_branch != 0) bxns();
	if (sumpt_lowpt_branch != 0) sumpt_lowpt();
	if (sumpt_highpt_branch != 0) sumpt_highpt();
	if (ntrks_lowpt_branch != 0) ntrks_lowpt();
	if (ntrks_highpt_branch != 0) ntrks_highpt();
	if (rhos_branch != 0) rhos();
	if (rho_branch != 0) rho();
	if (pthat_branch != 0) pthat();
	if (beta_branch != 0) beta();
	if (betaStar_branch != 0) betaStar();
	if (weight_branch != 0) weight();
	if (refpdgid_branch != 0) refpdgid();
	if (refpdgid_algorithmicDef_branch != 0) refpdgid_algorithmicDef();
	if (refpdgid_physicsDef_branch != 0) refpdgid_physicsDef();
	if (refe_branch != 0) refe();
	if (refpt_branch != 0) refpt();
	if (refeta_branch != 0) refeta();
	if (refphi_branch != 0) refphi();
	if (refy_branch != 0) refy();
	if (refdrjt_branch != 0) refdrjt();
	if (refarea_branch != 0) refarea();
	if (jte_branch != 0) jte();
	if (jtpt_branch != 0) jtpt();
	if (jteta_branch != 0) jteta();
	if (jtphi_branch != 0) jtphi();
	if (jty_branch != 0) jty();
	if (jtjec_branch != 0) jtjec();
	if (jtarea_branch != 0) jtarea();
	if (jtchf_branch != 0) jtchf();
	if (jtnhf_branch != 0) jtnhf();
	if (jtnef_branch != 0) jtnef();
	if (jtcef_branch != 0) jtcef();
	if (jtmuf_branch != 0) jtmuf();
	if (jthfhf_branch != 0) jthfhf();
	if (jthfef_branch != 0) jthfef();
	if (refdzvtx_branch != 0) refdzvtx();
}

	const vector<int> &CMS3::npus()
	{
		if (not npus_isLoaded) {
			if (npus_branch != 0) {
				npus_branch->GetEntry(index);
			} else { 
				printf("branch npus_branch does not exist!\n");
				exit(1);
			}
			npus_isLoaded = true;
		}
		return *npus_;
	}
	const vector<float> &CMS3::tnpus()
	{
		if (not tnpus_isLoaded) {
			if (tnpus_branch != 0) {
				tnpus_branch->GetEntry(index);
			} else { 
				printf("branch tnpus_branch does not exist!\n");
				exit(1);
			}
			tnpus_isLoaded = true;
		}
		return *tnpus_;
	}
	const vector<float> &CMS3::zpositions()
	{
		if (not zpositions_isLoaded) {
			if (zpositions_branch != 0) {
				zpositions_branch->GetEntry(index);
			} else { 
				printf("branch zpositions_branch does not exist!\n");
				exit(1);
			}
			zpositions_isLoaded = true;
		}
		return *zpositions_;
	}
	const vector<int> &CMS3::bxns()
	{
		if (not bxns_isLoaded) {
			if (bxns_branch != 0) {
				bxns_branch->GetEntry(index);
			} else { 
				printf("branch bxns_branch does not exist!\n");
				exit(1);
			}
			bxns_isLoaded = true;
		}
		return *bxns_;
	}
	const vector<float> &CMS3::sumpt_lowpt()
	{
		if (not sumpt_lowpt_isLoaded) {
			if (sumpt_lowpt_branch != 0) {
				sumpt_lowpt_branch->GetEntry(index);
			} else { 
				printf("branch sumpt_lowpt_branch does not exist!\n");
				exit(1);
			}
			sumpt_lowpt_isLoaded = true;
		}
		return *sumpt_lowpt_;
	}
	const vector<float> &CMS3::sumpt_highpt()
	{
		if (not sumpt_highpt_isLoaded) {
			if (sumpt_highpt_branch != 0) {
				sumpt_highpt_branch->GetEntry(index);
			} else { 
				printf("branch sumpt_highpt_branch does not exist!\n");
				exit(1);
			}
			sumpt_highpt_isLoaded = true;
		}
		return *sumpt_highpt_;
	}
	const vector<int> &CMS3::ntrks_lowpt()
	{
		if (not ntrks_lowpt_isLoaded) {
			if (ntrks_lowpt_branch != 0) {
				ntrks_lowpt_branch->GetEntry(index);
			} else { 
				printf("branch ntrks_lowpt_branch does not exist!\n");
				exit(1);
			}
			ntrks_lowpt_isLoaded = true;
		}
		return *ntrks_lowpt_;
	}
	const vector<int> &CMS3::ntrks_highpt()
	{
		if (not ntrks_highpt_isLoaded) {
			if (ntrks_highpt_branch != 0) {
				ntrks_highpt_branch->GetEntry(index);
			} else { 
				printf("branch ntrks_highpt_branch does not exist!\n");
				exit(1);
			}
			ntrks_highpt_isLoaded = true;
		}
		return *ntrks_highpt_;
	}
	const vector<float> &CMS3::rhos()
	{
		if (not rhos_isLoaded) {
			if (rhos_branch != 0) {
				rhos_branch->GetEntry(index);
			} else { 
				printf("branch rhos_branch does not exist!\n");
				exit(1);
			}
			rhos_isLoaded = true;
		}
		return *rhos_;
	}
	const float &CMS3::rho()
	{
		if (not rho_isLoaded) {
			if (rho_branch != 0) {
				rho_branch->GetEntry(index);
			} else { 
				printf("branch rho_branch does not exist!\n");
				exit(1);
			}
			rho_isLoaded = true;
		}
		return rho_;
	}
	const float &CMS3::pthat()
	{
		if (not pthat_isLoaded) {
			if (pthat_branch != 0) {
				pthat_branch->GetEntry(index);
			} else { 
				printf("branch pthat_branch does not exist!\n");
				exit(1);
			}
			pthat_isLoaded = true;
		}
		return pthat_;
	}
	const float &CMS3::beta()
	{
		if (not beta_isLoaded) {
			if (beta_branch != 0) {
				beta_branch->GetEntry(index);
			} else { 
				printf("branch beta_branch does not exist!\n");
				exit(1);
			}
			beta_isLoaded = true;
		}
		return beta_;
	}
	const float &CMS3::betaStar()
	{
		if (not betaStar_isLoaded) {
			if (betaStar_branch != 0) {
				betaStar_branch->GetEntry(index);
			} else { 
				printf("branch betaStar_branch does not exist!\n");
				exit(1);
			}
			betaStar_isLoaded = true;
		}
		return betaStar_;
	}
	const float &CMS3::weight()
	{
		if (not weight_isLoaded) {
			if (weight_branch != 0) {
				weight_branch->GetEntry(index);
			} else { 
				printf("branch weight_branch does not exist!\n");
				exit(1);
			}
			weight_isLoaded = true;
		}
		return weight_;
	}
	const vector<int> &CMS3::refpdgid()
	{
		if (not refpdgid_isLoaded) {
			if (refpdgid_branch != 0) {
				refpdgid_branch->GetEntry(index);
			} else { 
				printf("branch refpdgid_branch does not exist!\n");
				exit(1);
			}
			refpdgid_isLoaded = true;
		}
		return *refpdgid_;
	}
	const vector<int> &CMS3::refpdgid_algorithmicDef()
	{
		if (not refpdgid_algorithmicDef_isLoaded) {
			if (refpdgid_algorithmicDef_branch != 0) {
				refpdgid_algorithmicDef_branch->GetEntry(index);
			} else { 
				printf("branch refpdgid_algorithmicDef_branch does not exist!\n");
				exit(1);
			}
			refpdgid_algorithmicDef_isLoaded = true;
		}
		return *refpdgid_algorithmicDef_;
	}
	const vector<int> &CMS3::refpdgid_physicsDef()
	{
		if (not refpdgid_physicsDef_isLoaded) {
			if (refpdgid_physicsDef_branch != 0) {
				refpdgid_physicsDef_branch->GetEntry(index);
			} else { 
				printf("branch refpdgid_physicsDef_branch does not exist!\n");
				exit(1);
			}
			refpdgid_physicsDef_isLoaded = true;
		}
		return *refpdgid_physicsDef_;
	}
	const vector<float> &CMS3::refe()
	{
		if (not refe_isLoaded) {
			if (refe_branch != 0) {
				refe_branch->GetEntry(index);
			} else { 
				printf("branch refe_branch does not exist!\n");
				exit(1);
			}
			refe_isLoaded = true;
		}
		return *refe_;
	}
	const vector<float> &CMS3::refpt()
	{
		if (not refpt_isLoaded) {
			if (refpt_branch != 0) {
				refpt_branch->GetEntry(index);
			} else { 
				printf("branch refpt_branch does not exist!\n");
				exit(1);
			}
			refpt_isLoaded = true;
		}
		return *refpt_;
	}
	const vector<float> &CMS3::refeta()
	{
		if (not refeta_isLoaded) {
			if (refeta_branch != 0) {
				refeta_branch->GetEntry(index);
			} else { 
				printf("branch refeta_branch does not exist!\n");
				exit(1);
			}
			refeta_isLoaded = true;
		}
		return *refeta_;
	}
	const vector<float> &CMS3::refphi()
	{
		if (not refphi_isLoaded) {
			if (refphi_branch != 0) {
				refphi_branch->GetEntry(index);
			} else { 
				printf("branch refphi_branch does not exist!\n");
				exit(1);
			}
			refphi_isLoaded = true;
		}
		return *refphi_;
	}
	const vector<float> &CMS3::refy()
	{
		if (not refy_isLoaded) {
			if (refy_branch != 0) {
				refy_branch->GetEntry(index);
			} else { 
				printf("branch refy_branch does not exist!\n");
				exit(1);
			}
			refy_isLoaded = true;
		}
		return *refy_;
	}
	const vector<float> &CMS3::refdrjt()
	{
		if (not refdrjt_isLoaded) {
			if (refdrjt_branch != 0) {
				refdrjt_branch->GetEntry(index);
			} else { 
				printf("branch refdrjt_branch does not exist!\n");
				exit(1);
			}
			refdrjt_isLoaded = true;
		}
		return *refdrjt_;
	}
	const vector<float> &CMS3::refarea()
	{
		if (not refarea_isLoaded) {
			if (refarea_branch != 0) {
				refarea_branch->GetEntry(index);
			} else { 
				printf("branch refarea_branch does not exist!\n");
				exit(1);
			}
			refarea_isLoaded = true;
		}
		return *refarea_;
	}
	const vector<float> &CMS3::jte()
	{
		if (not jte_isLoaded) {
			if (jte_branch != 0) {
				jte_branch->GetEntry(index);
			} else { 
				printf("branch jte_branch does not exist!\n");
				exit(1);
			}
			jte_isLoaded = true;
		}
		return *jte_;
	}
	const vector<float> &CMS3::jtpt()
	{
		if (not jtpt_isLoaded) {
			if (jtpt_branch != 0) {
				jtpt_branch->GetEntry(index);
			} else { 
				printf("branch jtpt_branch does not exist!\n");
				exit(1);
			}
			jtpt_isLoaded = true;
		}
		return *jtpt_;
	}
	const vector<float> &CMS3::jteta()
	{
		if (not jteta_isLoaded) {
			if (jteta_branch != 0) {
				jteta_branch->GetEntry(index);
			} else { 
				printf("branch jteta_branch does not exist!\n");
				exit(1);
			}
			jteta_isLoaded = true;
		}
		return *jteta_;
	}
	const vector<float> &CMS3::jtphi()
	{
		if (not jtphi_isLoaded) {
			if (jtphi_branch != 0) {
				jtphi_branch->GetEntry(index);
			} else { 
				printf("branch jtphi_branch does not exist!\n");
				exit(1);
			}
			jtphi_isLoaded = true;
		}
		return *jtphi_;
	}
	const vector<float> &CMS3::jty()
	{
		if (not jty_isLoaded) {
			if (jty_branch != 0) {
				jty_branch->GetEntry(index);
			} else { 
				printf("branch jty_branch does not exist!\n");
				exit(1);
			}
			jty_isLoaded = true;
		}
		return *jty_;
	}
	const vector<float> &CMS3::jtjec()
	{
		if (not jtjec_isLoaded) {
			if (jtjec_branch != 0) {
				jtjec_branch->GetEntry(index);
			} else { 
				printf("branch jtjec_branch does not exist!\n");
				exit(1);
			}
			jtjec_isLoaded = true;
		}
		return *jtjec_;
	}
	const vector<float> &CMS3::jtarea()
	{
		if (not jtarea_isLoaded) {
			if (jtarea_branch != 0) {
				jtarea_branch->GetEntry(index);
			} else { 
				printf("branch jtarea_branch does not exist!\n");
				exit(1);
			}
			jtarea_isLoaded = true;
		}
		return *jtarea_;
	}
	const vector<float> &CMS3::jtchf()
	{
		if (not jtchf_isLoaded) {
			if (jtchf_branch != 0) {
				jtchf_branch->GetEntry(index);
			} else { 
				printf("branch jtchf_branch does not exist!\n");
				exit(1);
			}
			jtchf_isLoaded = true;
		}
		return *jtchf_;
	}
	const vector<float> &CMS3::jtnhf()
	{
		if (not jtnhf_isLoaded) {
			if (jtnhf_branch != 0) {
				jtnhf_branch->GetEntry(index);
			} else { 
				printf("branch jtnhf_branch does not exist!\n");
				exit(1);
			}
			jtnhf_isLoaded = true;
		}
		return *jtnhf_;
	}
	const vector<float> &CMS3::jtnef()
	{
		if (not jtnef_isLoaded) {
			if (jtnef_branch != 0) {
				jtnef_branch->GetEntry(index);
			} else { 
				printf("branch jtnef_branch does not exist!\n");
				exit(1);
			}
			jtnef_isLoaded = true;
		}
		return *jtnef_;
	}
	const vector<float> &CMS3::jtcef()
	{
		if (not jtcef_isLoaded) {
			if (jtcef_branch != 0) {
				jtcef_branch->GetEntry(index);
			} else { 
				printf("branch jtcef_branch does not exist!\n");
				exit(1);
			}
			jtcef_isLoaded = true;
		}
		return *jtcef_;
	}
	const vector<float> &CMS3::jtmuf()
	{
		if (not jtmuf_isLoaded) {
			if (jtmuf_branch != 0) {
				jtmuf_branch->GetEntry(index);
			} else { 
				printf("branch jtmuf_branch does not exist!\n");
				exit(1);
			}
			jtmuf_isLoaded = true;
		}
		return *jtmuf_;
	}
	const vector<float> &CMS3::jthfhf()
	{
		if (not jthfhf_isLoaded) {
			if (jthfhf_branch != 0) {
				jthfhf_branch->GetEntry(index);
			} else { 
				printf("branch jthfhf_branch does not exist!\n");
				exit(1);
			}
			jthfhf_isLoaded = true;
		}
		return *jthfhf_;
	}
	const vector<float> &CMS3::jthfef()
	{
		if (not jthfef_isLoaded) {
			if (jthfef_branch != 0) {
				jthfef_branch->GetEntry(index);
			} else { 
				printf("branch jthfef_branch does not exist!\n");
				exit(1);
			}
			jthfef_isLoaded = true;
		}
		return *jthfef_;
	}
	const vector<float> &CMS3::refdzvtx()
	{
		if (not refdzvtx_isLoaded) {
			if (refdzvtx_branch != 0) {
				refdzvtx_branch->GetEntry(index);
			} else { 
				printf("branch refdzvtx_branch does not exist!\n");
				exit(1);
			}
			refdzvtx_isLoaded = true;
		}
		return *refdzvtx_;
	}

  void CMS3::progress( int nEventsTotal, int nEventsChain ){
    int period = 1000;
    if(nEventsTotal%1000 == 0) {
      // xterm magic from L. Vacavant and A. Cerri
      if (isatty(1)) {
        if( ( nEventsChain - nEventsTotal ) > period ){
          float frac = (float)nEventsTotal/(nEventsChain*0.01);
          printf("\015\033[32m ---> \033[1m\033[31m%4.1f%%"
               "\033[0m\033[32m <---\033[0m\015", frac);
          fflush(stdout);
        }
        else {
          printf("\015\033[32m ---> \033[1m\033[31m%4.1f%%"
                 "\033[0m\033[32m <---\033[0m\015", 100.);
          cout << endl;
        }
      }
    }
  }
  
namespace tas {
	const vector<int> &npus() { return cms3.npus(); }
	const vector<float> &tnpus() { return cms3.tnpus(); }
	const vector<float> &zpositions() { return cms3.zpositions(); }
	const vector<int> &bxns() { return cms3.bxns(); }
	const vector<float> &sumpt_lowpt() { return cms3.sumpt_lowpt(); }
	const vector<float> &sumpt_highpt() { return cms3.sumpt_highpt(); }
	const vector<int> &ntrks_lowpt() { return cms3.ntrks_lowpt(); }
	const vector<int> &ntrks_highpt() { return cms3.ntrks_highpt(); }
	const vector<float> &rhos() { return cms3.rhos(); }
	const float &rho() { return cms3.rho(); }
	const float &pthat() { return cms3.pthat(); }
	const float &beta() { return cms3.beta(); }
	const float &betaStar() { return cms3.betaStar(); }
	const float &weight() { return cms3.weight(); }
	const vector<int> &refpdgid() { return cms3.refpdgid(); }
	const vector<int> &refpdgid_algorithmicDef() { return cms3.refpdgid_algorithmicDef(); }
	const vector<int> &refpdgid_physicsDef() { return cms3.refpdgid_physicsDef(); }
	const vector<float> &refe() { return cms3.refe(); }
	const vector<float> &refpt() { return cms3.refpt(); }
	const vector<float> &refeta() { return cms3.refeta(); }
	const vector<float> &refphi() { return cms3.refphi(); }
	const vector<float> &refy() { return cms3.refy(); }
	const vector<float> &refdrjt() { return cms3.refdrjt(); }
	const vector<float> &refarea() { return cms3.refarea(); }
	const vector<float> &jte() { return cms3.jte(); }
	const vector<float> &jtpt() { return cms3.jtpt(); }
	const vector<float> &jteta() { return cms3.jteta(); }
	const vector<float> &jtphi() { return cms3.jtphi(); }
	const vector<float> &jty() { return cms3.jty(); }
	const vector<float> &jtjec() { return cms3.jtjec(); }
	const vector<float> &jtarea() { return cms3.jtarea(); }
	const vector<float> &jtchf() { return cms3.jtchf(); }
	const vector<float> &jtnhf() { return cms3.jtnhf(); }
	const vector<float> &jtnef() { return cms3.jtnef(); }
	const vector<float> &jtcef() { return cms3.jtcef(); }
	const vector<float> &jtmuf() { return cms3.jtmuf(); }
	const vector<float> &jthfhf() { return cms3.jthfhf(); }
	const vector<float> &jthfef() { return cms3.jthfef(); }
	const vector<float> &refdzvtx() { return cms3.refdzvtx(); }
}
