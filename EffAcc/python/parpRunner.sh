#!/bin/sh




for n in 2.0 #0.25 0.5 1.0 #2.0 2.5 3.0 #.25 0.5 0.75 1.0 1.5

do
fn=${n%%.*}
rn=${n##*.}
echo fn $fn rn $rn  ${fn}_${rn}

ls --color=none /local/cms/user/klapoetke/powhegZ/ptsqmin_30/base/Kevin_parp${fn}_${rn}_cfi/*root > ~/parp${fn}_${rn}_pwg_jun08.txt
cp zshape_effacc_base_cfg.py parp${fn}_${rn}_93fitzshape_pt30_effacc_base_cfg.py

condor_filelist.perl parp${fn}_${rn}_93fitzshape_pt30_effacc_base_cfg.py ~/parp${fn}_${rn}_pwg_jun08.txt 10

done


