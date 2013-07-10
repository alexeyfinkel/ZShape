#!/bin/tcsh -f
##########################################################################
###STARTUP STUFF
###
set me=`whoami`
set scandir="/local/cms/user/klapoetke/Electrons/TNPTREE10/EffStat"
set pscdir=$scandir:h
set ogdir=`pwd`

#1 Run for each Efficiency Parameters
##########################################################################
./scanone.csh 100 Trials WP80 WP95  NTTightElectronId HFSuperCluster-Et HFElectronId-EtaDet Supercluster-Eta GsfTrack-EtaDet HLT-GSF 



#end of file
