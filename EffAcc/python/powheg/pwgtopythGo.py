import os
import string

workDir    = '/local/cms/user/pastika'
Nfiles     = 1

condorSubmitFileName = workDir + '/powhegZ/powtopythSubmit'
condorSubmitBase = """Universe             = vanilla
Executable           = /home/ugrad/pastika/cms/gen/powheg/powtopyth.out
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
bbscalevarM = (0, 1, 2)   # 0: fixed scales ; 1: dynamic scale M_V; 2: dynamic scales sqrt(m_V^2 +P_t^2)

for muref in murefM:
    #subFolderName = "/%(m)03.3f_%(f)01.1f_%(r)01.1f_%(b)i"%{'m':muref,'f':facscfact,'r':renscfact,'b':bbscalevar}
    outputDir = workDir + '/powhegZ'
    os.system('mkdir -p ' + outputDir + '/log')
    condorSubmitNext = """


InitialDir           = $$OUTDIR$$
Arguments            = $$ARGS$$
output               = $$OUTDIR$$/log/pwgtopyth_$$REF$$.out
error                = $$OUTDIR$$/log/pwgtopyth_$$REF$$.err
Log                  = $$OUTDIR$$/log/pwgtopyth_$$REF$$.log
Queue                = long
"""

    condorSubmitNext = condorSubmitNext.replace('$$OUTDIR$$', outputDir)
    thing = "%(a)1.3f"%{"a":muref}
    condorSubmitNext = condorSubmitNext.replace('$$ARGS$$', outputDir + ' ' + thing)
    condorSubmitNext = condorSubmitNext.replace('$$REF$$', '%(a)1.3f'%{"a":muref})
    condorFile.write(condorSubmitNext)

    logdir = '/log/pwgtopyth_%(a)1.3f'%{"a":muref}
    f = open(outputDir + logdir + '.out', "w")
    f.write('')
    f.close()
    f = open(outputDir + logdir + '.err', "w")
    f.write('')
    f.close()
    f = open(outputDir + logdir + '.log', "w")
    f.write('')
    f.close()

condorFile.close()
os.system('condor_submit ' + condorSubmitFileName)
