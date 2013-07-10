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

hadModels = ('PythiaUED6TSettings_cfi', 'PythiaUEP0Settings_cfi', 'PythiaUEProPT0Settings_cfi', 'PythiaUEProQ20Settings_cfi', 'PythiaUEZ2Settings_cfi')

for hadmod in hadModels:
    subFolderName = "/base/" + hadmod.replace('Settings_cfi','')
    os.system("mkdir -p " + workDir + '/powhegZ' + subFolderName)
    outputDir = workDir + '/powhegZ' + subFolderName
    os.system('mkdir -p ' + outputDir + '/cfg')
    for i in range(Nfiles):
        os.system('cp ~/cms/CMSSW_3_9_7/src/ZShape/EffAcc/python/zshape_effacc_base_cfg.py ' + outputDir + '/cfg/zshape_effacc_base_set-' + repr(i) + '_cfg.py')
        sedOutDir = outputDir.replace('/', '\\/')
        os.system("sed -i \'s/fileNames = cms.untracked.vstring(\"\" )/fileNames = cms.untracked.vstring(\"file:" + sedOutDir + "\/powhegz_LHAGLUE.root\")/\' " + outputDir + '/cfg/zshape_effacc_base_set-' + repr(i) + '_cfg.py')
        os.system(r"sed -i 's/histo_10M_partBUILDINGTTEST.root/" + sedOutDir + "\/effAccOut_set-" + repr(i) + ".root/\' " + outputDir + '/cfg/zshape_effacc_base_set-' + repr(i) + '_cfg.py')
        os.system("sed -i \'s/powhegz_LHAGLUE.root/powhegz_LHAGLUE_set-" + repr(i) + ".root/\' " + outputDir + '/cfg/zshape_effacc_base_set-' + repr(i) + '_cfg.py')

        condorSubmitNext = """


InitialDir           = %(idir)s
Arguments            = %(idir)s/cfg/zshape_effacc_base_set-%(num)i_cfg.py
Transfer_Input_Files = %(idir)s/cfg/zshape_effacc_base_set-%(num)i_cfg.py
output               = log/effacc_set-%(num)i.out
error                = log/effacc_set-%(num)i.err
Log                  = log/effacc_set-%(num)i.log
Queue                = long
"""%{"idir":outputDir, "num":i}

        condorFile.write(condorSubmitNext)

        f = open(outputDir + '/log/effacc_set-%(num)i.out'%{"num":i},"w")
        f.write('')
        f.close()
        f = open(outputDir + '/log/effacc_set-%(num)i.err'%{"num":i},"w")
        f.write('')
        f.close()
        f = open(outputDir + '/log/effacc_set-%(num)i.log'%{"num":i},"w")
        f.write('')
        f.close()

condorFile.close()
os.system('condor_submit ' + condorSubmitFileName)
