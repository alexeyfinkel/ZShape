import os
import string

workDir    = '/local/cms/user/klapoetke'
Nfiles     = 100

condorSubmitFileName = workDir + '/powhegZ/pythiaSubmit'
condorSubmitBase = """Universe             = vanilla
Executable           = /local/cms/sw/slc5_ia32_gcc434/cms/cmssw/CMSSW_3_9_7/bin/slc5_ia32_gcc434/cmsRun
Requirements = Memory > 400 && Arch=="X86_64" && (Machine != "zebra04.spa.umn.edu")
+CondorGroup = "cmsfarm"
WhenToTransferOutput = On_Exit
should_transfer_files = YES
getenv = True"""
condorFile = open(condorSubmitFileName, "w")
condorFile.write(condorSubmitBase)

#hadModels = ('PythiaUED6TSettings_cfi', 'PythiaUEP0Settings_cfi', 'PythiaUEProPT0Settings_cfi', 'PythiaUEProQ20Settings_cfi', 'PythiaUEZ2Settings_cfi')
hadModels = ('PythiaUEZ2Settings_cfi')
#hadModels = ('PythiaUEP0Settings_cfi', 'PythiaUEProPT0Settings_cfi', 'PythiaUEProQ20Settings_cfi')
print hadModels
exit()
for hadmod in hadModels:
    muref = 91.188
    bbscalevar = 2
    subFolderName = "/base/" + hadmod.replace('Settings_cfi','')
    os.system("mkdir -p " + workDir + '/powhegZ' + subFolderName)
    outputDir = workDir + '/powhegZ' + subFolderName
    os.system('mkdir -p ' + outputDir + '/cfg')
    for i in range(Nfiles):
        os.system('cp /home/grad/klapoetke/CMSSW_4_1_3/src/ZShape/EffAcc/python/powheg/pythia_cfg.py ' + outputDir + '/cfg/pythia_set-' + repr(i) + '_cfg.py')
        sedOutDir = outputDir.replace('/' + hadmod.replace('Settings_cfi',''), '').replace('/', '\\/')
        os.system(r"sed -i 's/file:pwgevents_noExcess.lhe/file:" + sedOutDir + "\/set-" + repr(i) + r"\/pwgevents_noExcess.lhe/' " + outputDir + '/cfg/pythia_set-' + repr(i) + '_cfg.py')
        os.system("sed -i \'s/PythiaUESettings_cfi/" + hadmod + "/\' " + outputDir + '/cfg/pythia_set-' + repr(i) + '_cfg.py')
        os.system("sed -i \'s/powhegz_LHAGLUE.root/Zee_Powheg_" + hadmod.replace('Settings_cfi','') + '_' + repr(i) + ".root/\' " + outputDir + '/cfg/pythia_set-' + repr(i) + '_cfg.py')
        os.system("sed -i \'s/123456789/" + repr(i + 100) + "/\' " + outputDir + '/cfg/pythia_set-' + repr(i) + '_cfg.py')

        condorSubmitNext = """


InitialDir           = %(outdir)s
Arguments            = %(outdir)s/cfg/pythia_set-%(num)i_cfg.py
Transfer_Input_Files = %(outdir)s/cfg/pythia_set-%(num)i_cfg.py
output               = log/pythia_set-%(num)i.out
error                = log/pythia_set-%(num)i.err
Log                  = log/pythia_set-%(num)i.log
Queue                = long
"""%{"outdir": outputDir, "num": i}

        condorFile.write(condorSubmitNext)
        
        os.system("mkdir -p " + outputDir + "/log")
        f = open(outputDir + '/log/pythia_set-%(num)i.out'%{"num":i}, "w")
        f.write('')
        f.close()
        f = open(outputDir + '/log/pythia_set-%(num)i.err'%{"num":i}, "w")
        f.write('')
        f.close()
        f = open(outputDir + '/log/pythia_set-%(num)i.log'%{"num":i}, "w")
        f.write('')
        f.close()

condorFile.close()
os.system('condor_submit ' + condorSubmitFileName)
