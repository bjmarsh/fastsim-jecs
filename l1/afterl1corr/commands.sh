flatPUL1cor=JRA_FlatPU_jec.root
noPU=JRA_NoPU.root
basepath=/home/users/bemarsh/analysis/fastsim_jecs/JRA_fromAOD/CMSSW_9_4_12/src/JetMETAnalysis/JetAnalyzers/test/fastsim-jecs/
outputpath=${basepath}/l1/afterl1corr/
era=Fall17_17Nov2017_V32_MC

algos="
ak4pf
ak4pfchs
ak8pfchs
ak4puppi
ak8puppi
"


##### 1 #####

# # get root files for matched jets for L1 correction
# for algo in $algos; do
#     jet_match_x -algo1 ${algo}l1 -algo2 $algo -samplePU $flatPUL1cor -sampleNoPU $noPU -basepath $basepath -outputPath $outputpath >& log_${algo}l1.txt &
# done

# wait

##### 2 #####

# make L1 corrections and plot them
mkdir -p images/
mkdir -p parameters/
mkdir -p text/
for algo in $algos; do
    # jet_synchfit_x -algo1 ${algo}l1 -algo2 $algo
    jet_synchplot_x -algo1 ${algo}l1 -algo2 $algo -outputFormat ".pdf" -fixedRange true
    # mv Parameter_${algo}.* parameters/
done
