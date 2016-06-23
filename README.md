0) Setup initial directory:
```
CMSSWVER=CMSSW_8_0_5_patch1 # or whatever version to be used
cmsrel $CMSSWVER
cd $CMSSWVER/src
git clone https://github.com/cms-jet/JetMETAnalysis
cd JetMETAnalysis
cmsenv
scram b -j10
cd JetAnalyzers/test
git clone https://github.com/aminnj/jecs
```
And be sure to modify paths in scripts to match reality

1) Run on PUFlat and NoPU samples in the crab/ directory 

2) Merge files (scripts in crab/tomerge/) and move them into this current directory

3) Make L1 corrections, plot them, and apply them to the PUFlat sample with `commands.sh` in `l1/`

4) Plot L1 corrected PUFlat sample them with `commands.sh` in `l1/afterl1corr/`

5) Derive L2L3 with `commands.sh` in `l2l3`

6) `mkdir plots`, update filenames in `validation/doAll.C` and run it to make plots

7) Get appropriate uncertainties from latest FullSim era to use in `makeUncertainties.py`

8) Make slides with `python *py` inside of `validation/slides/`

9) Copy JECs with `. copy_jecs.sh`

10) Present at JetMET meeting
