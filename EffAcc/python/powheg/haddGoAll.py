import os
import string

workDir    = '/local/cms/user/pastika'
Nfiles     = 10

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
    if ((muref == 91.188) + (facscfact == 1.0) + (renscfact == 1.0) + (bbscalevar == 2)) >= 3:
        paths = ''
        for i in range(Nfiles):
            subFolderName = "/%(m)03.3f_%(f)01.1f_%(r)01.1f_%(b)i" % {'m':muref, 'f':facscfact, 'r':renscfact, 'b':bbscalevar}
            outputDir = workDir + '/powhegZ' + subFolderName + '/set-' + repr(i) + '/effAccOut.root '
            paths = paths + outputDir

        os.system('hadd -f ' + workDir + '/powhegZ' + subFolderName + '/effAccOut.root ' + paths)
