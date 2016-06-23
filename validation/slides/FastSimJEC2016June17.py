import sys, os
import slideMaker as sm
import tableMaker as tm

# sm.addGlobalOptions("--graphicspaths ../plots_120215/,/home/users/namin/2015/jec/an2013_131/CMSSW_7_4_1_patch1/src/JetMETAnalysis/JetAnalyzers/test/flat/,/home/users/namin/2015/jec/an2013_131/CMSSW_7_4_1_patch1/src/JetMETAnalysis/JetAnalyzers/test/flat/images/")
# sm.addGlobalOptions("--graphicspaths ../plots/,/home/users/namin/2015/jec/an2013_131/CMSSW_7_4_1_patch1/src/JetMETAnalysis/JetAnalyzers/test/flat/,/home/users/namin/2015/jec/an2013_131/CMSSW_7_4_1_patch1/src/JetMETAnalysis/JetAnalyzers/test/flat/images/")
sm.addGlobalOptions("--graphicspaths ../plots/,../../l1/images/")

# sm.initSlides(me="Nick",themeName="alex",opts="--themecolor 100,74,196 --casual \\textbf{Nick Amin} ENDL \\today --font gillius")
# sm.initSlides(me="Nick",themeName="alex",opts="--themecolor 29,76,165 --casual \\textbf{Nick Amin} ENDL \\today --font gillius")
sm.initSlides(me="Nick",themeName="alexmod",opts="--themecolor 255,105,180 --font gillius")

sm.addSlide(title="80X FastSim JECs", opts="")
        # - Use PU, NoPU samples to derive \\textbf{L1} corrections
        # -- /QCD\\_Pt-15to7000\\_TuneCUETP8M1\\_Flat\\_13TeV\\_pythia8/ RunIISpring15FSPremixDR-NoPU\\_ForSUSJECs\\_MCRUN2\\_74\\_V9-v1/AODSIM
        # -- /QCD\\_Pt-15to7000\\_TuneCUETP8M1\\_Flat\\_13TeV\\_pythia8/ RunIISpring15FSPremixDR-FlatPU0To50\\_ForSUSJECs\\_MCRUN2\\_74\\_V9-v1/AODSIM
        # -- Corrects for PU in bins of $\\eta$ as a function of $\\pt$
        # - Use NoPU sample to derive \\textbf{L2L3} correction
        # -- L3Absolute makes response flat in $\\pt$ using absolute response ($\\pt^\\text{gen}-\\pt^\\text{reco}$). Text file produced from this is a dummy file nowadays (L2L3 done together in one step)
        # -- L2Relative makes response flat in $\\eta$ using relative response ($\\pt^\\text{reco}/\\pt^\\text{gen}$).
        # - Produce corrections for ak\\{4,8\\}\\{pf,pfchs\\} jets since this is what we have in FastSim
        # -- Use TAMU framework (\\url{https://github.com/cms-jet/})
        # -- Focus on AK4PFchs here (other 3 are in backup)
sm.addSlide(title="Overview", text="""
        - Use PU, NoPU samples (made from same GEN events) to derive L1 corrections
        -- /QCD\\_Pt-15to7000\\_TuneCUETP8M1\\_Flat\\_13TeV\\_pythia8/RunIISpring16FSPremixDR-NoPU\\_ForSUSJECs\\_80X\\_mcRun2\\_asymptotic\\_v12-v1/AODSIM
        -- /QCD\\_Pt-15to7000\\_TuneCUETP8M1\\_Flat\\_13TeV\\_pythia8/RunIISpring16FSPremixDR-FlatPU0To50\\_ForSUSJECs\\_80X\\_mcRun2\\_asymptotic\\_v12-v1/AODSIM
        - Use L1 corrected PU sample to derive L2L3 correction
        - Produce corrections for ak\\{4,8\\}\\{pf,pfchs\\} jets
        -- Use TAMU framework (\\url{https://github.com/cms-jet/})
        -- Focus on AK4PFchs here (other 3 are in backup)
        - Results similar to 74X: \\url{https://indico.cern.ch/event/465389/contributions/1972876/attachments/1198596/1743132/FastSimJEC.pdf}
        """)

algs = ["ak4pfchs","ak4pf","ak8pf","ak8pfchs"]
for alg in algs:
    sm.addObject("t"+alg,"text",(0.92,0.07),width=0.3, text=alg, color="red", size=1, bold=False) 

offset = 0.03
sm.addObject("tbottomak4pfchs","text",(0.10+offset,0.93),width=0.3, text="ak4pfchs", color="black", size=0, bold=False) 
sm.addObject("tbottomak4pf"   ,"text",(0.35+offset,0.93),width=0.3, text="ak4pf"   , color="black", size=0, bold=False) 
sm.addObject("tbottomak8pfchs","text",(0.60+offset,0.93),width=0.3, text="ak8pfchs", color="black", size=0, bold=False) 
sm.addObject("tbottomak8pf"   ,"text",(0.85+offset,0.93),width=0.3, text="ak8pf   ", color="black", size=0, bold=False) 
    
sm.addObject("tfastsim","text",(0.27,0.83),width=0.3, text="FastSim", color="black", size=1, bold=False) 
sm.addObject("tfullsim","text",(0.72,0.83),width=0.3, text="FullSim", color="black", size=1, bold=False) 

offset = 0.073
sm.addObject("ltopbottom","arrow",(0.02, 0.513+offset), (0.98, 0.513+offset), color="black", opts="--noarrowhead")
sm.addObject("tcorr",  "text",(0.07,0.525+offset),width=0.3, text="Corrected",   color="black", size=-2, bold=False) 
sm.addObject("tuncorr","text",(0.07,0.492+offset),width=0.3, text="Uncorrected", color="black", size=-2, bold=False) 

for ialg,alg in enumerate(algs):
    
    sm.addSlide(title="L1 Correction", p1=alg+"_L1pt.pdf", p2=alg+"_L1eta.pdf", p3=alg+"_L1corrFine.pdf", objects=["t"+alg], text="""
    - Smooth correction in $\\pt-\\eta $ space (fitting converged reasonably)
    """)


    sm.addSlide(title="L1 Closure (NPV-binned)",
        plots=[
               "OffMeantnpuRef_BB_%s.pdf" % alg,
               "../../l1/afterl1corr/images/OffMeantnpuRef_BB_%sl1_%s.pdf" % (alg, alg),
               "OffMeantnpuRef_EI_%s.pdf" % alg,
               "../../l1/afterl1corr/images/OffMeantnpuRef_EI_%sl1_%s.pdf" % (alg, alg),
               "OffMeantnpuRef_EO_%s.pdf" % alg,
               "../../l1/afterl1corr/images/OffMeantnpuRef_EO_%sl1_%s.pdf" % (alg, alg)
               ],
        objects=["t"+alg, "ltopbottom", "tcorr", "tuncorr"],
        text="""
        - Offset ($\\pt^\\text{PU}-\\pt^\\text{NoPU}$) shifted to zero after corrections, although high $\\pt$ deviates for FastSim (relative offset still small)
        """
    )

    sm.addSlide(title="L1 PU vs NoPU Comparison ($\\pt$, $\\eta$)", 
            p1=alg+"_ptVsPt.pdf", 
            p2=alg+"_ptVsPtL1.pdf", 
            p3=alg+"_ptVsEta.pdf", 
            p4=alg+"_ptVsEtaL1.pdf", 
            objects=["t"+alg], text="""
        - Closure for L1 correction
    """)

    sm.addSlide(title="L2L3 Correction", p1=alg+"_L2pt.pdf", p2=alg+"_L2eta.pdf", p3=alg+"_L2corrFine.pdf", objects=["t"+alg], text="""
    -- Again, smooth behaviour in L2L3 correction
    """)


    sm.addSlide(title="Response - raw", p1=alg+"_responseFine.pdf", p2=alg+"_response.pdf", objects=["t"+alg], text="""
    - Finally we start layering the corrections on top of the raw jets (course binning on right)
    """)

    sm.addSlide(title="Response - L1L2L3 corrected", p1=alg+"_responseL1L2CorrFine.pdf", p2=alg+"_responseL1L2Corr.pdf", objects=["t"+alg], text="""
        - Fully corrected response (coarse binning on right)
    """)

    # sm.addSlide(title="Closure vs $\\pt$ for L1L2L3", p1=alg+"_uncorrResponse.pdf", p2=alg+"_corrResponse.pdf", objects=["t"+alg], text="""
    #  - Uncorrected (left) and fully corrected (right)
    #  - Uncertainties taken from the fully corrected response bins of $\\pt$ and $\\eta$ as departure from 1
    # """)


    if(alg == "ak4pfchs"):


        sm.addSlide(title="Closure vs $\\pt$ for L1L2L3", 
                plots=[
                    "ak4pfchs_uncorrResponse.pdf",
                    "ak4pfchs_corrResponse.pdf",
                    "ak4pf_uncorrResponse.pdf",
                    "ak4pf_corrResponse.pdf",
                    "ak8pfchs_uncorrResponse.pdf",
                    "ak8pfchs_corrResponse.pdf",
                    "ak8pf_uncorrResponse.pdf",
                    "ak8pf_corrResponse.pdf",
                    ],
            text="""
             - Uncorrected (top) and fully corrected (bottom)
             - Uncertainties taken from the fully corrected response in bins of $\\pt$ and $\\eta$ simply as the deviation from 1
                -- Then added to this in quadrature the FullSim residual uncertainties from Spring16\\_25nsV2\\_MC\\_Uncertainty
             - Recommend using AK8 jets above 60 GeV
        """, 
        objects=["tbottomak4pfchs","tbottomak4pf", "tbottomak8pfchs", "tbottomak8pf"]
        )

        sm.addSlide(title="Conclusions", text="""
        - Distributions look acceptable after applying L1L2L3 corrections
        - Text files in \\url{http://uaf-6.t2.ucsd.edu/~namin/dump/jecs_FastSim_80X_V1/}
        """)

        sm.startBackup()
            
        sm.addSlide(title="L1 Parameters", p1="../../l1/parameters/Parameter_%s.pdf" % alg, opts="--fithorizontal", objects=["t"+alg], text="""
            - Ignoring binning issues, parameters look reasonable
        """)

        sm.addSlide(title="L1 $\\chi^2$/ndof", p1=alg+"_L1chisq.pdf", objects=["t"+alg], text="""
        - Find reduced $\\chi^2$ for each $\\eta$ slice fit
        - The threshold for a ``bad'' fit is 9, so these are acceptable
        """)

        sm.addSlide(title="L2 $\\chi^2$/ndof", p1=alg+"_L2chisq.pdf", objects=["t"+alg], text="""
        """)

        # sm.addSlide(title="L2L3 Fit Results", p1="L2AbsCorGraphs_%s.pdf" % alg, objects=["t"+alg], text="""
        # - Fit correction as function of $\\pt$ for each of the 82 $\\eta$ bins
        # """)


sm.writeSlides("jecValidation2016June17_v2.tex", opts="--compile --copy --dump")
