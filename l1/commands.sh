flatPU=JRA_FlatPU.root
noPU=JRA_NoPU.root
basepath=/home/users/bemarsh/analysis/fastsim_jecs/JRA_fromAOD/CMSSW_9_4_12/src/JetMETAnalysis/JetAnalyzers/test/fastsim-jecs/
outputpath=${basepath}/l1/
era=Fall17_17Nov2017_V32_MC

algos="
ak4pf
ak4pfchs
ak8pfchs
ak4puppi
ak8puppi
"


# 1 #####

# # get root files for matched jets for L1 correction
# for algo in $algos; do
#     jet_match_x -algo1 $algo -algo2 $algo -samplePU $flatPU -sampleNoPU $noPU -basepath $basepath -outputPath $outputpath >& log_${algo}.txt &
#     # sleep 10m;
# done

##### 2 #####

# # make L1 corrections and plot them
# mkdir -p images/
# mkdir -p parameters/
# mkdir -p text/
# for algo in $algos; do
#     alias=$(python -c "print '$algo'.replace('ak','AK').replace('pf','PF').replace('puppi','PUPPI')")
#     jet_synchfit_x -algo1 $algo -algo2 $algo -functionType ak4 -era $era
#     jet_synchplot_x -algo1 $algo -algo2 $algo -outputFormat ".pdf" -fixedRange false
#     mv Parameter_${algo}.* parameters/
#     mv ${era}_L1FastJet_${alias}.txt text/${era}_L1FastJet_${alias}.txt
# done

##### 3 #####

# apply L1 correction to flatPU sample
jecpath=$basepath/l1/text/
jet_apply_jec_x -input $basepath/$flatPU -era $era -jecpath $jecpath -L1FastJet true -levels 1 -output /nfs-7/userdata/bemarsh/test.root -debug false -saveitree true &> log_apply_jec.txt &

