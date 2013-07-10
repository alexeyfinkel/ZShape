#include "TH2F.h"
#include "TFile.h"
#include "TH1D.h"
#include "TF1.h"
#include "tdrstyle.C"
#include <iostream>
using namespace std;
//#include "zrapidityStandard.C"

void note_meanPhiRes(TFile *fp)
{
  gROOT->SetStyle("Plain");setTDRStyle();  
  TH2F *ptr1;
  TCanvas* c1=new TCanvas("c1","c1",800,800);
  
  
  TH1D *py1 = 0;
  
  fp->GetObject("myanalyzer/cutNoCuts/PhiRes",ptr1);
  ptr1->FitSlicesY();
  
  //fp->GetObject("myanalyzer/cutNoCuts/PhiRes_1",py1);
  fp->GetObject(/*"myanalyzer/cutNoCuts/*/"PhiRes_1",py1);
  if (py1 == 0) {
    cerr << "Dang! Whatta I have to do anyway??"<<endl;
    return;
  }
  
  
  TF1 *f1 = new TF1 ("f1","[0]*sin((x-[1])*[2])",.0,1);//2pi=6.283185307
  //  TF1 *f1 = new TF1 ("f1","[0]*tan((x-[1])*[2])+[3]",-.1,1.2); 
  f1->SetParameters(-0.0001,.5,3);
  //f1->SetParameter(0,1);
   py1->SetMaximum(0.04);
  py1->SetMinimum(-0.04);
  py1->SetTitle(0);
  py1->SetStats(0);
  py1->GetXaxis()->SetTitle("#phi_{Cell}");
  //py1->GetXaxis()->CenterTitle();
   f1->SetLineColor(2);
  py1->GetYaxis()->SetTitle("#phi_{gen}-#phi_{raw}");
  py1->GetYaxis()->SetTitleOffset(1.6);
  gStyle->SetOptStat(0);
  py1->Fit("f1");
  c1->SetLeftMargin(0.20);
  py1->Draw();
  //zrap_Prelim(.4,.8);
  //c1->Print("/home/grad/klapoetke/public_html/note/note_meanPhiRes.eps");
  //c1->Print("/home/grad/klapoetke/public_html/cmsdoc/PHD/trunk/figs/fig_meanPhiRes.eps");
}
