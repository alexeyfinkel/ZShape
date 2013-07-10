#include "stdio.h"
#include "string.h"
#include "stdlib.h"

int main(int argc, char* argv[])
{
    const int Nfiles = 100;

    //double murefM[] = {80.0, 91.188, 100.0}; // reference scale in GeV
    //double facscfactM[] = {0.9, 1.0, 1.1}; // factorization scale factor: mufact=muref*facscfact
    //double renscfactM[] = {0.9, 1.0, 1.1}; // renormalization scale factor: muren=muref*renscfact
    //int bbscalevarM[] = {0, 1, 2}; // 0: fixed scales ; 1: dynamic scale M_V; 2: dynamic scales sqrt(m_V^2 +P_t^2)

    for(int i = 0; i < Nfiles; i++)
    {
        char fNO[512], fNF[512], *buff, zfNO[512];
        size_t SIZE = 4096;
        buff = new char[SIZE];
        FILE *fIN, *fOUT;
        bool isWrite = true;
        printf("set-%i/pwgevents.lhe\n", i);
        sprintf(fNO, "set-%i/pwgevents.lhe", i);
        sprintf(fNF, "set-%i/pwgevents_noExcess.lhe", i);
        fIN = fopen(fNO, "r");

        if(fIN == NULL) continue;
        fOUT = fopen(fNF, "w");

        while(!feof(fIN))
        {
            getline(&buff, &SIZE, fIN);
            if(strstr(buff, "<extra-info-previous-event>") != NULL || strstr(buff, "#Random number generator exit values:") != NULL) isWrite = false;
            if(isWrite) fprintf(fOUT, buff);
            if(strstr(buff, "</extra-info-previous-event>") != NULL || strstr(buff, "#Random number generator exit values:") != NULL) isWrite = true;
        }

        delete[] buff;
        fclose(fIN);
        fclose(fOUT);

        sprintf(zfNO, "gzip -f %s", fNO);
        system(zfNO);
    }
}

//for i in range(Nfiles):
//
//        subFolderName = "/%(m)03.3f_%(f)01.1f_%(r)01.1f_%(b)i"%{'m':muref,'f':facscfact,'r':renscfact,'b':bbscalevar}
//        openDir = workDir + subFolderName + '/powhegZ/set-' + repr(i)
//        fLHEO = open(openDir + '/pwgevents.lhe','r')
//        fLHEF = open(openDir + '/pwgevents_noExcess.lhe','w')
//
//        isWrite = True
//
//        for line in fLHEO:
//                if line.count('<extra-info-previous-event>') > 0 or line.count('#Random number generator exit values:') > 0: isWrite = False
//                if isWrite: fLHEF.write(line)
//                if line.count('</extra-info-previous-event>') > 0 or line.count('#Random number generator exit values:') > 0: isWrite = True
//
//        fLHEO.close()
//        fLHEF.close()
//
//        os.system('gzip ' + openDir + '/pwgevents.lhe')


