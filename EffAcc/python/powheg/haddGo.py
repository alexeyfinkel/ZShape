import os
import string

workDir    = '/local/cms/user/pastika'
Nfiles     = 1

hadModels = ('PythiaUED6TSettings_cfi', 'PythiaUEP0Settings_cfi', 'PythiaUEProPT0Settings_cfi', 'PythiaUEProQ20Settings_cfi', 'PythiaUEZ2Settings_cfi')

for hadmod in hadModels:
    subFolderName = "/base/" + hadmod.replace('Settings_cfi','')
    os.system("mkdir -p " + workDir + '/powhegZ' + subFolderName)
    outputDir = workDir + '/powhegZ' + subFolderName
    paths      = ''
    for i in range(Nfiles):
        paths = paths + outputDir + '/effAccOut_set-' + repr(i) + ".root "

    os.system('hadd -f ' + workDir + '/powhegZ' + subFolderName + '/effAccOut_hadded.root ' + paths)
