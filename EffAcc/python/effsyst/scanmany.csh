#!/bin/tcsh -f
##########################################################################
###STARTUP STUFF
###
set me=`whoami`
set scandir="/local/cms/user/klapoetke/Electrons/TNPTREE10/EffSyst"
set pscdir=$scandir:h
set ogdir=`pwd`

#1 Run for each Efficiency Parameters
##########################################################################
#./scanone.csh ECAL80-HF Def WP80 WP95  NTTightElectronId-EtaDet HFSuperCluster-Et HFElectronId-EtaDet Supercluster-Eta GsfTrack-EtaDet HLT-GSF 
#./scanone.csh ECAL80-NTLoose Def WP80 WP95  NTTightElectronId-EtaDet HFSuperCluster-Et HFElectronId-EtaDet Supercluster-Eta GsfTrack-EtaDet HLT-GSF 
#./scanone.csh ECAL80-ECAL95 Def WP80 WP95  NTTightElectronId-EtaDet HFSuperCluster-Et HFElectronId-EtaDet Supercluster-Eta GsfTrack-EtaDet HLT-GSF 

#Skimed to just the effs that matter for a given definition
./scanone.csh ECAL80-HF Def WP80 HFSuperCluster-Et HFElectronId-EtaDet Supercluster-Eta GsfTrack-EtaDet HLT-GSF 
./scanone.csh ECAL80-NTLoose Def WP80 NTTightElectronId-EtaDet Supercluster-Eta GsfTrack-EtaDet HLT-GSF 
./scanone.csh ECAL80-ECAL95 Def WP80 WP95 Supercluster-Eta GsfTrack-EtaDet HLT-GSF
./scanone.csh ECAL80-ECAL95-MUO Def WP80 WP95 Supercluster-Eta GsfTrack-EtaDet HLT-GSF


#end of file
