flatPU=JRA_FlatPU.root
flatPUL1cor=JRA_FlatPU_jec.root
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

# algos="
# ak4pfchs
# "

# algos="
# ak4pfchs
# "

mkdir -p images/
mkdir -p plots/
mkdir -p parameters/
mkdir -p text/

##### 0 #####

# # copy L1 corrections here and make the dummy L3 corrections which will be needed by a script later
# cp ../l1/text/*.txt .
# for algo in $algos; do
#     alias=$(python -c "print '$algo'.replace('ak','AK').replace('pf','PF')")
#     echo -e "{1         JetEta              1          JetPt               1     Correction     L3Absolute}\n -5.191          5.191              2              4           5000" >  ${era}_L3Absolute_${alias}.txt
# done

##### 1 #####

# # make jra_f.root for L2L3
# for algo in $algos; do
#     # jet_response_analyzer_x ../../config/jra_dr_finebinning.config -input $basepath/JRA_PUFlat_jec.root -presel "jte<6500" -algs ak4pfchsl1
#     jet_response_analyzer_x ../../../config/jra_dr_finebinning.config -input $basepath/$flatPUL1cor   -algs ${algo}l1
#     jet_response_fitter_x -input jra.root -output jra_f_${algo}.root -niter 10 -nsigma 1.5
# done

##### 2 #####

# actually calculate L2L3
for algo in $algos; do
    # jet_l3_correction_x -batch true -era $era -input jra_f_${algo}.root
    jet_l2_correction_x -input jra_f_${algo}.root -era $era -formats png -batch true -l2l3 true -maxFitIter 120 -l2pffit spline3
    # jet_l2_correction_x -input jra.root -era $era -formats png -batch true -l2l3 true -maxFitIter 120 -l2pffit spline3
done
for i in $(ls -1 *l1.txt); do echo $i; mv $i ${i%%l1.txt}.txt; done


##### 3 #####

# rename files
# draw corrections layered on top of the PUFlat0to50 sample
# for algo in $algos; do
#     jet_correction_analyzer_x -inputFilename $basepath/$flatPU -path ./ -era $era -useL2Cor true -useL3Cor true -useL1Cor true -algs $algo
#     jet_draw_corrections_x -path ./ -outputDir ./plots/ -era $era -useL1FasCor true -useL2Cor true -useL3Cor true -mpv false -algs $algo
# done


