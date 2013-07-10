#!/bin/tcsh -f
########################################
# Simple Script to do the scanning
# of a single ZShape Variable
########################################
set me=`whoami`
set scandir="/local/cms/user/klapoetke/Electrons/TNPTREE10/Scans"
set pscdir=$scandir:h

#1.1 Scan the Variable
######################
./scanScripter.sh $*
set mytype="${1}${2}"


#1.2 Run the Jobs
###################### #../Zfiles.txt
foreach mypy (`ls |grep ${mytype}`)
#    ~/bin/condor_filelist.perl $mypy ../apr11Powheg.txt 100
 ~/bin/condor_filelist.perl $mypy ../aprZ2.txt 100
# ~/bin/condor_filelist.perl $mypy ../aprD6T.txt 100
# ~/bin/condor_filelist.perl $mypy ../mayP0.txt 100
# ~/bin/condor_filelist.perl $mypy ../mayProPT0.txt 100
# ~/bin/condor_filelist.perl $mypy ../mayProQ20.txt 100


    sleep 20s
end
#STAT
#1.3 Wait for the jobs to be finished
######################
#echo "Waiting for the ${mytype} jobs to finish\n ..."
#while (`condor_q -submitter ${me} -format '%s\n' Owner | grep -c "${me}"` > 0)
#    sleep 1m
#    echo "that was one min"
#end
#sleep 1m
#echo "\n The ${mytype} Jobs are DONE"

#1.4 Combine the output
######################
#foreach mydr (`ls $pscdir | grep ${mytype}` )
#    #echo $mydr
#    foreach myf (`ls  $pscdir/$mydr/TFEcalScan${mytype}*MCMIN*.root`)
#	#echo $myf
#	if (`ls -l $myf | awk '{print $5}'` < 100000 ) then
#	    echo "removing $myf"
#	    rm $myf
#	endif
#    end
#    hadd -f $scandir/${mydr}.root $pscdir/$mydr/TFEcalScan${mytype}*MCMIN*.root
#end

echo "now done"

#End of script
