flatPU=JRA_PUFlat.root
noPU=JRA_NoPU.root
basepath=/home/users/namin/2016/jec/CMSSW_8_0_5_patch1/src/JetMETAnalysis/JetAnalyzers/test/
outputpath=${basepath}/l1/
era=Spring16_25nsV3

algos="
ak4pf
ak4pfchs
ak8pf
ak8pfchs
"


##### 1 #####

# # get root files for matched jets for L1 correction
# for algo in $algos; do
#     jet_synchtest_x -algo1 $algo -algo2 $algo -samplePU $flatPU -sampleNoPU $noPU -basepath $basepath -outputPath $outputpath >& log_${algo}.txt &
#     sleep 10m;
# done

##### 2 #####

# # make L1 corrections and plot them
# mkdir -p images/
# mkdir -p parameters/
# mkdir -p text/
# for algo in $algos; do
#     alias=$(python -c "print '$algo'.replace('ak','AK').replace('pf','PF')")
#     jet_synchfit_x -algo1 $algo -algo2 $algo
#     jet_synchplot_x -algo1 $algo -algo2 $algo -outputFormat ".pdf" -fixedRange false
#     mv Parameter_${algo}.* parameters/
#     mv parameters_${algo}.txt text/${era}_L1FastJet_${alias}.txt
# done

##### 3 #####

# # apply L1 correction to flatPU sample
# jecpath=$basepath/l1/text/
# jet_apply_jec_x -input $basepath/JRA_PUFlat.root -era $era -jecpath $jecpath -L1FastJet true -levels 1
