#include "TF1.h"
#include "TFile.h"
#include "TCanvas.h"
#include "TGraphErrors.h"
#include "TGraph.h"
#include "TH1.h"
#include "TH2.h"
#include <math.h>
#include <algorithm>
#include <list>
#include <iostream>
#include "TROOT.h"
#include "Math/VectorUtil_Cint.h"


void sanityCheck(double e1, double e2, double p1, double p2, double c1, double c2){

  double PI=3.14159265359;


    double thetaStar;
    if (c1 < 0){
        thetaStar=acos(tanh(.5*(e1-e2)));
    }else{
        thetaStar=acos(tanh(.5*(e2-e1)));
    }

    double dphi=p1-p2;


    if(dphi<0){dphi+=2*PI;}
    if(dphi>2*PI){dphi-=2*PI;}
    double phiStar=tan((3.141596-dphi)/2)*sin(thetaStar);





    std::cout<<" eta1="<<e1<<" eta2="<<e2<<" ph1="<<p1<<" phi2="<<p2<<" charge1="<<c1<<" charge2="<<c2<<" "<<std::endl;

    std::cout<<"PhiStar="<<phiStar<<" thetaStar="<<thetaStar<<" delta phi="<<dphi<<" tan((3.141596-delPhi)/2)="<<tan((3.141596-dphi)/2)<<" sin(thetaStar) " <<sin(thetaStar)<<std::endl;
}
#ifdef NEED_MAIN

int main(int argc, char* argv[]) {
  if (argc<6) {
    printf("Arguments:eta1 eta2 phi1 phi2 charge1 charge2\n");
    return 1;
  }
  double e1=atof(argv[1]);
   double e2=atof(argv[2]);
   double p1=atof(argv[3]);

 double p2=atof(argv[4]);
   double c1=atof(argv[5]);
   double c2=atof(argv[6]);

  //  double var=atof(argv[3]);
   sanityCheck(e1,e2,p1,p2,c1,c2);
  std::cout<<"@@@@20"<<std::endl;
   return 0;
}

// gcc -o sanityCheck.exe sanityCheck.C -DNEED_MAIN -O `root-config --cflags --libs`
// ./sanityCheck.exe 1 1 1 1 1 1

#endif
