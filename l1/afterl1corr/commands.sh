flatPUL1cor=JRA_PUFlat_jec.root
noPU=JRA_NoPU.root
basepath=/home/users/namin/2016/jec/CMSSW_8_0_5_patch1/src/JetMETAnalysis/JetAnalyzers/test/
outputpath=${basepath}/l1/afterl1corr/
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
#     jet_synchtest_x -algo1 ${algo}l1 -algo2 $algo -samplePU $flatPUL1cor -sampleNoPU $noPU -basepath $basepath -outputPath $outputpath >& log_${algo}l1.txt &
#     sleep 3m;
# done

wait

##### 2 #####

# make L1 corrections and plot them
mkdir -p images/
mkdir -p parameters/
mkdir -p text/
for algo in $algos; do
    # jet_synchfit_x -algo1 ${algo}l1 -algo2 $algo
    jet_synchplot_x -algo1 ${algo}l1 -algo2 $algo -outputFormat ".pdf" -fixedRange false
    mv Parameter_${algo}.* parameters/
done
