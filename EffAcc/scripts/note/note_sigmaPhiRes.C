#include "TH2F.h"
#include "TFile.h"
#include "TH1D.h"
#include "TF1.h"
#include "tdrstyle.C"
#include "zrapidityStandard.C"
#include <iostream>
using namespace std;

void note_sigmaPhiRes(TFile *fp)
{
  gROOT->SetStyle("Plain");setTDRStyle();    
  TH2F *ptr1;
  TCanvas* c1=new TCanvas("c1","c1",800,800);



   TH1D *py1 = 0;

   fp->GetObject("myanalyzer/cutNoCuts/NoCutsPhiRes",ptr1);
   ptr1->FitSlicesY();
 
  fp->GetObject("NoCutsPhiRes_2",py1);

  if (py1 == 0) {
    cerr << "Dang! Whatta I have to do anyway??"<<endl;
    return;
  }
  py1->SetStats(0);
  py1->GetXaxis()->SetTitle("#phi_{Cell}");
  // py1->GetXaxis()->CenterTitle();

  py1->SetTitle();
  py1->GetYaxis()->SetTitle("Width of #phi_{gen}-#phi_{reco}");
  gStyle->SetOptStat(111);
  py1->GetYaxis()->SetTitleOffset(1.6);
  c1->SetLeftMargin(0.20);
  py1->Draw();
  zrap_Prelim(.78,.9);
  c1->Print("/home/grad/klapoetke/public_html/cmsdoc/PHD/trunk/figs/fig_sigmaPhiRes.eps");
}
