#!/bin/bash

workDir=/export/scratch/users/pastika
baseDir=$workDir/powhegZ
mkdir -p $baseDir
outputDir=$baseDir$4/set-$5
mkdir -p $outputDir
#mkdir -p $baseDir/log
cd $outputDir
cat > $baseDir/powheg-set-$5.log
cat > $baseDir/powheg-set-$5.err
cat > $baseDir/powheg-set-$5.out
ls -lh $baseDir
cp /local/cms/user/pastika/powhegZ/powheg.input $outputDir
echo $6
set -i 's/ISEED/$6/' $outputDir/powheg.input
set -i 's/PDFSET/$8/g' $outputDir/powheg.input
set -i 's/NEVENTS/$7/' $outputDir/powheg.input
set -i 's/MUREF/$9/' $outputDir/powheg.input
set -i 's/FACSCFACT/$10/' $outputDir/powheg.input
set -i 's/RENSCFACT/$11/' $outputDir/powheg.input
set -i 's/BBSCALEVAR/$12/' $outputDir/powheg.input
/local/cms/other/powheg/powheg-box-svn38/pwhg_main_Z $1
/local/cms/user/pastika/powhegZ/powtopyth.out $2
mv $3 /local/cms/user/pastika/powhegZ/
mv $workDir/powheg-set-$5.log /local/cms/user/pastika/powhegZ/$4
mv $workDir/powheg-set-$5.err /local/cms/user/pastika/powhegZ/$4
mv $workDir/powheg-set-$5.out /local/cms/user/pastika/powhegZ/$4 
