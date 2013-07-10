#include "TH2F.h"
#include "TFile.h"
#include "TH1D.h"
#include "TF1.h"

#include <iostream>
using namespace std;

void project_etaRes(TFile *fp)
{
  gROOT->SetStyle("Plain");  
  TH2F *ptr1;
 

   TH1D *py1 = 0;

   fp->GetObject("myanalyzer/cuttwoDim/twoDimEtaRes",ptr1);
   // ptr1->FitSlicesY();
 
   //fp->GetObject("twoDimHFEnergyRes_1",py1);

  gStyle->SetOptFit(1111);
ptr1->ProjectionY("EtaRes_01",1,4,"");
ptr1->ProjectionY("EtaRes_02",5,8,"");
ptr1->ProjectionY("EtaRes_03",9,12,"");
ptr1->ProjectionY("EtaRes_04",13,16,"");
ptr1->ProjectionY("EtaRes_05",17,20,"");
ptr1->ProjectionY("EtaRes_06",21,24,"");
ptr1->ProjectionY("EtaRes_07",25,28,"");
ptr1->ProjectionY("EtaRes_08",27,32,"");
ptr1->ProjectionY("EtaRes_09",33,36,"");
ptr1->ProjectionY("EtaRes_10",37,40,"");  
  //ptr1->ProjectionY("EtaRes_",,,"");
 
 
}
