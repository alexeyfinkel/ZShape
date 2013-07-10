#!/bin/sh
num=$1

for parp in `ls /local/cms/user/klapoetke/powhegZ/ptsqmin_${num}/base/ | grep evin`
  do
  list=num${num}_parp$parp.txt
  ls --color=none /local/cms/user/klapoetke/powhegZ/ptsqmin_${num}/base/$parp/*root > ~/txts/$list
  cfg=subcfg/${parp}_zshape_effacc_cfg.py
  cp ~/CMSSW_4_1_8/src/ZShape/EffAcc/python/zshape_effacc_kevin_cfg.py $cfg
  echo $cfg $list $parp
  condor_filelist.perl $cfg ~/txts/$list 250
done