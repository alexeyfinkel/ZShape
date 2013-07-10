#include "TH2F.h"
#include "TFile.h"
#include "TH1D.h"
#include "TF1.h"
#include "tdrstyle.C"
#include "zrapidityStandard.C"

#include <iostream>
using namespace std;

void note_meanEnergyRes(TFile *fp)
{
  gROOT->SetStyle("Plain");setTDRStyle();  
  TH2F *ptr1;
 TCanvas* c1=new TCanvas("c1","c1",800,800);

   TH1D *py1 = 0;

   fp->GetObject("myanalyzer/cutNoCuts/HFEnergyRes",ptr1);
   //fp->GetObject("myanalyzer/cuttwoDim/twoDimHFEnergyRes",ptr1);

   ptr1->FitSlicesY();
 
   fp->GetObject("HFEnergyRes_2",py1);
   //fp->GetObject("twoDimHFEnergyRes_2",py1);
  if (py1 == 0) {
    cerr << "Dang! Whatta I have to do anyway??"<<endl;
    return;
  }
  py1->SetStats(0);
  py1->GetXaxis()->SetTitle("Energy [GeV]");
  py1->GetXaxis()->SetRange(0,2000);
  //py1->GetXaxis()->CenterTitle();
  //TF1 *f1 = new TF1 ("f1","([0]/sqrt(x))+[1]+([2]^2)/x",0,2000);
  TF1 *f1 = new TF1 ("f1","sqrt([0]*[0]/(x)+[1]*[1])",0,1600);
  //TF1 *f1 = new TF1 ("f1","sqrt([0]*[0]/(x)+0.055*0.055)",0,1600);

  f1->SetParameters(3,1);
  f1->SetLineColor(2);
  f1->SetLineWidth(2);
  f1->SetLineStyle(2);
  py1->SetMarkerStyle(21);
  py1->SetTitle();
  py1->GetYaxis()->SetTitle("(E_{gen}-E_{reco})/E_{gen}");
  gStyle->SetOptStat(111);
  //py1->GetYaxis()->SetTitleOffset(1.5);
  c1->SetLeftMargin(0.20);
  py1->Fit("f1","R");
  py1->Draw();

  zrap_Prelim(.4,.8);
  //c1->Print("/home/grad/klapoetke/public_html/note/note_meanEnergyRes.eps");
c1->Print("/home/grad/klapoetke/public_html/cmsdoc/PHD/trunk/figs/fig_meanEnergyRes.eps");
}
