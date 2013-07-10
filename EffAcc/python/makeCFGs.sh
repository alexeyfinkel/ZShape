#!/bin/sh

cfg=$1

for nmb in 1 2
do
condor_filelist.perl parp${nmb}_${cfg} ~/parp${nmb}_pwg_May10.txt 10
#echo parp${nmb}_${cfg}
done