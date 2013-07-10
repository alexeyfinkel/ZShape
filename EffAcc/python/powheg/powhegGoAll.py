import os
import random
import string

workDir    = '/local/cms/user/pastika'
Nevents    = 1000000
Nfiles     = 10

baseDir = workDir + '/powhegZ'
os.system('mkdir -p ' + baseDir)
#os.system('cp /home/ugrad/pastika/cms/gen/powheg/powhegGo.sh /local/cms/user/pastika/powhegZ/')
#os.system('cp /home/ugrad/pastika/cms/gen/powheg/powtopyth.out /local/cms/user/pastika/powhegZ/')
condorSubmitBase = """Universe             = vanilla
Executable           = /local/cms/other/powheg/powheg-box-svn38/pwhg_main_Z
Requirements = Memory > 400 && Arch=="X86_64" && (Machine != "zebra04.spa.umn.edu")
+CondorGroup = "cmsfarm"
WhenToTransferOutput = On_Exit
should_transfer_files = YES
getenv = True
nice_user = True"""
condorSubmitFileName = baseDir + '/powhegSubmit'
condorFile = open(condorSubmitFileName, "w")
condorFile.write(condorSubmitBase)

murefM = (80.0, 91.188, 100.0)  # reference scale in GeV
facscfactM = (0.5, 1.0, 2.0)    # factorization scale factor: mufact=muref*facscfact
renscfactM = (0.5, 1.0, 2.0)    # renormalization scale factor: muren=muref*renscfact
bbscalevarM = (0, 1, 2)   # 0: fixed scales ; 1: dynamic scale M_V; 2: dynamic scales sqrt(m_V^2 +P_t^2)

#for (muref, facscfact, renscfact, bbscalevar) in ((i, j, k, l) for i in murefM for j in facscfactM for k in renscfactM for l in bbscalevarM):
#for (facscfact, renscfact) in ((j, k) for j in facscfactM for k in renscfactM):
for (muref, bbscalevar) in ((j, k) for j in murefM for k in bbscalevarM):
    facscfact = facscfactM[1]
    renscfact = renscfactM[1]
    print muref
    for i in range(Nfiles):
        if ((muref == murefM[1]) + (facscfact == facscfactM[1]) + (renscfact == renscfactM[1]) + (bbscalevar == bbscalevarM[2])) > 2:
            pdfset     = 10901
            iSeed      = i
            #muref      = 91.188   # reference scale in GeV
            #facscfact  = 1    # factorization scale factor: mufact=muref*facscfact
            #renscfact  = 1    # renormalization scale factor: muren=muref*renscfact
            #bbscalevar = 2   # 0: fixed scales ; 1: dynamic scale M_V; 2: dynamic scales sqrt(m_V^2 +P_t^2)
            
            subFolderName = "/%(m)03.3f_%(f)01.1f_%(r)01.1f_%(b)i" % {'m':muref, 'f':facscfact, 'r':renscfact, 'b':bbscalevar}
            outputDir = baseDir + subFolderName + '/set-' + repr(i)
            os.system('mkdir -p ' + outputDir)
            os.system('mkdir -p ' + outputDir + '/log')

            f = open(outputDir + '/log/powheg.out', "w")
            f.write('')
            f.close()
            f = open(outputDir + '/log/powheg.err', "w")
            f.write('')
            f.close()
            f = open(outputDir + '/log/powheg.log', "w")
            f.write('')
            f.close()

            condorSubmitNext = """


InitialDir           = $$OUTDIR$$
Arguments            = powheg.input
Transfer_Input_Files = powheg.input
output               = log/powheg.out
error                = log/powheg.err
Log                  = log/powheg.log
Queue                = long
"""

            condorSubmitNext = condorSubmitNext.replace('$$OUTDIR$$', outputDir)
            condorFile.write(condorSubmitNext)

            powheg = """! Random Number Generato
iseed %(iSeed)i ! initialize random number sequence
!rand1 -1       ! initialize random number sequence
!rand2 -1       ! initialize random number sequence

! Single vector boson production parameters
idvecbos 23    ! PDG code for vector boson to be produced ( Z:23 )
vdecaymode 11  ! PDG code for first decay product of the vector boson  (11:e-; 12:ve; 13:mu-; 14:vmu; 15:tau; 16:vtau;)
numevts %(Nevents)i  ! number of events to be generated
ih1   1        ! hadron 1 (1: proton; -1: antiproton)
ih2   1        ! hadron 2 (1: proton; -1: antiproton)
lhans1  %(pdfset1)i  ! pdf set (LHAGLUE number)
lhans2  %(pdfset2)i  ! pdf set (LHAGLUE number)
ebeam1 3500    ! energy of beam 1 in GeV
ebeam2 3500    ! energy of beam 2 in GeV
muref %(muref)1.3f   ! reference scale in GeV
facscfact %(facscfact)1.1f    ! factorization scale factor: mufact=muref*facscfact
renscfact %(renscfact)1.1f    ! renormalization scale factor: muren=muref*renscfact
bbscalevar %(bbscalevar)i   ! 0: fixed scales ; 1: dynamic scale M_V; 2: dynamic scales sqrt(m_V^2 +P_t^2)

! Parameters to allow-disallow use of stored data
use-old-grid 0     ! if 0 use old grid if file pwggrids.dat is present (# 0: regenerate)
use-old-ubound 0   ! if 0 use norm of upper bounding function stored in pwgubound.dat, if present (# 0: regenerate)

! Integration parameters
ncall1 120000  ! number of calls for initializing the integration grid
itmx1 5        ! number of iterations for initializing the integration grid
ncall2 250000  ! number of calls for computing the integral and finding upper bound
itmx2 5        ! number of iterations for computing the integral and finding upper bound
foldcsi   1    ! number of folds on x integration
foldy   1      ! number of folds on y integration
foldphi 1      ! number of folds on phi integration
nubound 150000 ! number of bbarra calls to setup norm of upper bounding function
!ivmax 1       ! <= 10, number of bins of the upper bound grid along v direction
iymax 1        ! <= 10, number of bins of the upper bound grid along x direction
icsimax 1      ! <= 10, number of bins of the upper bound grid along x direction
xupbound 2     ! upper bound factor in radiation generation
withdamp 1     ! (default 0, do not use) use Born-zero damping factor

! Optional parameters
!pdfreweight 1 ! (default 0, do not) write extra PDF infos on LHEF
"""  % {"iSeed":iSeed, "Nevents":Nevents, "pdfset1":pdfset, "pdfset2":pdfset, "muref":muref, "facscfact":facscfact, "renscfact":renscfact, "bbscalevar":bbscalevar}

            powhegFileName = outputDir + '/powheg.input'
            powhegFile = open(powhegFileName, "w")
            powhegFile.write(powheg)
            powhegFile.close()

#os.system('export LHAPATH=/home/hep/rekovic/other/lhapdf-5.8.4/share/lhapdf/PDFsets')

condorFile.close()
os.system('condor_submit ' + condorSubmitFileName)
