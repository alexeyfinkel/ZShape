import os
import string

workDir    = '/local/cms/user/pastika'
Nfiles     = 10

condorSubmitFileName = workDir + '/powhegZ/effAccSubmit'
condorSubmitBase = """Universe             = vanilla
Executable           = /local/cms/sw/slc5_ia32_gcc434/cms/cmssw/CMSSW_3_9_7/bin/slc5_ia32_gcc434/cmsRun
Requirements = Memory > 400 && Arch=="X86_64" && (Machine != "zebra04.spa.umn.edu")
+CondorGroup = "cmsfarm"
WhenToTransferOutput = On_Exit
should_transfer_files = YES
getenv = True"""
condorFile = open(condorSubmitFileName,"w")
condorFile.write(condorSubmitBase)

murefM = (80.0, 91.188, 100.0)  # reference scale in GeV
facscfactM = (0.5, 1.0, 2.0)    # factorization scale factor: mufact=muref*facscfact
renscfactM = (0.5, 1.0, 2.0)    # renormalization scale factor: muren=muref*renscfact
#facscfactM = (0.9, 1.0, 1.1)    # factorization scale factor: mufact=muref*facscfact
#renscfactM = (0.9, 1.0, 1.1)    # renormalization scale factor: muren=muref*renscfact
bbscalevarM = (0, 1, 2)   # 0: fixed scales ; 1: dynamic scale M_V; 2: dynamic scales sqrt(m_V^2 +P_t^2)

#for (muref, facscfact, renscfact, bbscalevar) in ((i, j, k, l) for i in murefM for j in facscfactM for k in renscfactM for l in bbscalevarM):
#for (facscfact, renscfact) in ((j, k) for j in facscfactM for k in renscfactM):
for (muref, bbscalevar) in ((j, k) for j in murefM for k in bbscalevarM):
    facscfact = facscfactM[1]
    renscfact = renscfactM[1]
    for i in range(Nfiles):
        if ((muref == 91.188) + (facscfact == 1.0) + (renscfact == 1.0) + (bbscalevar == 2)) >= 3:
            subFolderName = "/%(m)03.3f_%(f)01.1f_%(r)01.1f_%(b)i" % {'m':muref, 'f':facscfact, 'r':renscfact, 'b':bbscalevar}
            outputDir = workDir + '/powhegZ' + subFolderName + '/set-' + repr(i)

            os.system('cp $CMSSW_BASE/src/ZShape/EffAcc/python/zshape_effacc_base_cfg.py ' + outputDir + '/zshape_effacc_base_cfg.py')
            sedOutDir = outputDir.replace('/', '\\/')
            os.system("sed -i \'s/fileNames = cms.untracked.vstring(\"\" )/fileNames = cms.untracked.vstring(\"file:" + sedOutDir + "\/powhegz_LHAGLUE.root\")/\' " + outputDir + '/zshape_effacc_base_cfg.py')
            os.system(r"sed -i 's/histo_10M_partBUILDINGTTEST.root/" + sedOutDir + "\/effAccOut.root/\' " + outputDir + '/zshape_effacc_base_cfg.py')

            condorSubmitNext = """


InitialDir           = $$OUTDIR$$
Arguments            = zshape_effacc_base_cfg.py
Transfer_Input_Files = zshape_effacc_base_cfg.py
output               = log/effacc.out
error                = log/effacc.err
Log                  = log/effacc.log
Queue                = long
"""

            condorSubmitNext = condorSubmitNext.replace('$$OUTDIR$$', outputDir)
            condorFile.write(condorSubmitNext)

            f = open(outputDir + '/log/effacc.out',"w")
            f.write('')
            f.close()
            f = open(outputDir + '/log/effacc.err',"w")
            f.write('')
            f.close()
            f = open(outputDir + '/log/effacc.log',"w")
            f.write('')
            f.close()

condorFile.close()
os.system('condor_submit ' + condorSubmitFileName)
