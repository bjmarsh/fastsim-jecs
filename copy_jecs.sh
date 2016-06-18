finaldir="${HOME}/public_html/dump/jecs_FastSim_80X_V1/"
era="Spring16_FastSimV1"

algos="
AK4PF
AK4PFchs
AK8PF
AK8PFchs
"

mkdir -p $finaldir
for algo in $algos; do
    cp l1/text/Spring16_25nsV3_L1FastJet_${algo}.txt $finaldir/${era}_L1FastJet_${algo}.txt
    cp l2l3/Spring16_25nsV3_L2Relative_${algo}.txt $finaldir/${era}_L2Relative_${algo}.txt
    cp l2l3/Spring16_25nsV3_L3Absolute_${algo}.txt $finaldir/${era}_L3Absolute_${algo}.txt
    cp validation/FS_Uncertainty_${algo}.txt $finaldir/${era}_Uncertainty_${algo}.txt
done

echo "Ok, I put stuff into $finaldir"
