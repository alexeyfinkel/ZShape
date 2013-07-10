#!/bin/sh


#HF
#EB
#EE
det=$1
shift


#constantp
#constantm
#constantp2
#constantm2
#reseta
#resphi
#c 
var=$1
shift
day=`date +%b%d`
time=`date +%H%M`
vals1_=${*//./_}
vals_=${vals1_// /__}
cfg=scans/${det}_${var}_${day}_${time}_cfg.py
cp TOPLATE.py $cfg
path=scans/path.py
cp PATHPLATE.py $path
for num in $*; do
    num_=${num//./X}
    name=${det}X${var}X${num_}
    Sname=${name}Xsmear

    process=process.$name
    Sprocess=process.$Sname
# >> $cfg
# >> $path
echo ${Sprocess} \= ZShape.EffAcc.FullSimSmearedElectronProducer_cfi.FullSimSmearedElectronsProducer.clone\(\) >> $cfg
echo ${Sprocess}.$det.${var}p \= cms.double\($num\) >> $cfg
echo ${Sprocess}.$det.${var}m \= cms.double\($num\) >> $cfg

echo \+ $Sprocess >> $path
echo >> $cfg



echo ${process} \= ZShape.EffAcc.ZEfficiencyKevin_cfi.mcEff.clone\(\) >> $cfg
echo ${process}.zTreeLevelElectronsCollection \= cms.untracked.InputTag\(\"f2s\",\"ZEventEle3\"\) >> $cfg
echo ${process}.zsrc \= cms.untracked.InputTag\(\"${Sname}\",\"ZEventParticles\"\) >> $cfg
echo ${process}.zElectronsCollection \= cms.untracked.InputTag\(\"${Sname}\",\"ZEventParticles\"\) >> $cfg
echo >> $cfg
echo \+ $process >> $path
done



cat $path >> $cfg
echo \) >> $cfg
rm $path








