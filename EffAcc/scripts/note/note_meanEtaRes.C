#include "TH2F.h"
#include "TFile.h"
#include "TH1D.h"
#include "TF1.h"
#include "tdrstyle.C"
#include <iostream>
//#include "zrapidityStandard.C"

using namespace std;

void note_meanEtaRes(TFile *fp)
{
  gROOT->SetStyle("Plain");setTDRStyle();  
  TH2F *ptr1;
 
  TCanvas* c1=new TCanvas("c1","c1",800,800);


   TH1D *py1 = 0;

   fp->GetObject("myanalyzer/cutNoCuts/EtaRes",ptr1);
   ptr1->FitSlicesY();
 
  fp->GetObject("EtaRes_1",py1);

  if (py1 == 0) {
    cerr << "Dang! Whatta I have to do anyway??"<<endl;
    return;
  }

  
  //  TF1 *f1 = new TF1 ("f1","[0]*sin(x*[1]+[2])+[3]",.0,1);//2pi=6.283185307
  //f1->SetParameters(1,6.283185307,-0.377,0.1);
  
  TF1 *f1 = new TF1 ("f1","[0]*sin(x*6.283185307+(-0.377))+[1]",0.1,0.9); 
  f1->SetParameters(1,0.1);
  
  
  py1->SetStats(0);
  py1->GetXaxis()->SetTitle("#eta_{Cell}");
  //py1->GetXaxis()->CenterTitle();
  // f1->SetLineColor(2);
  py1->SetTitle(0);
  py1->GetYaxis()->SetTitle("|#eta_{gen}|-|#eta_{raw}|");
  py1->GetYaxis()->SetTitleOffset(1.5);
  gStyle->SetOptStat(111);
  py1->Fit("f1");

  c1->SetLeftMargin(0.20);
  
  py1->Draw();

  //zrap_Prelim(.7,.8);
  //c1->Print("/home/grad/klapoetke/public_html/note/note_meanEtaRes.eps");
  c1->Print("/home/grad/klapoetke/public_html/cmsdoc/PHD/trunk/figs/fig_meanEtaRes.eps");
}
