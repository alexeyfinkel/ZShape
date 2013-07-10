#include "TH2F.h"
#include "TFile.h"
#include "TH1D.h"
#include "TF1.h"

#include <iostream>
using namespace std;

void smear_Eta(TFile *fp)
{
  gROOT->SetStyle("Plain");  
  TH2F *ptr1;
 

   TH1D *py1 = 0;

   fp->GetObject("myanalyzer/cuttwoDim/twoDimEtaRes",ptr1);
   //ptr1->Rebin(5);
   ptr1->FitSlicesY();
 
  fp->GetObject("twoDimEtaRes_2",py1);

  if (py1 == 0) {
    cerr << "Dang! Whatta I have to do anyway??"<<endl;
    return;
  }
  py1->SetStats(0);
  py1->GetXaxis()->SetTitle("#eta_{Cell}");
  py1->GetXaxis()->CenterTitle();
  py1->SetTitle(0);
  //py1->Rebin(5);

  //py1->Scale(1.0/5);
  py1->GetYaxis()->SetTitle("#sigma of |#eta_{gen}|-|#eta_{reco}|");
  gStyle->SetOptStat(111);
  py1->GetYaxis()->SetTitleOffset(1.5);
  
  py1->Draw();
}
