#include "TH2F.h"
#include "TFile.h"
#include "TH1D.h"
#include "TF1.h"
#include "tdrstyle.C"
#include "zrapidityStandard.C"
#include <iostream>
using namespace std;

void note_projectedPlots(TFile *fp,int plot,int cor,int mode)
{char name[126];
  char cname[126];
  char pname[126];
  char rname[126];
  switch(cor){
  case 0:
    sprintf(cname,"uncorr");
    break;
  case 1:
    sprintf(cname,"corr");
    break;
  }
  switch(plot){
  case 0:
    sprintf(pname,"HFDeltaEta");//th1
    break;
  case 1:
    sprintf(pname,"HFDeltaPhi");//th1
    break;
  case 2:
    sprintf(pname,"PhiRes");
    break;
  case 3:
    sprintf(pname,"EtaRes");//Corrections
    break;
  case 4:
    sprintf(pname,"HFEtaResVlogE");//Corrections
    break;
  case 5:
    sprintf(pname,"");
    break;
  case 6:
    sprintf(pname,"");
    break;
  }
  switch(mode){
  case 0:
    sprintf(rname,"old");
    break;
  case 1:
    sprintf(rname,"old_nocuts");
    break;
  case 2:
    sprintf(rname,"new");
    break;
  case 3:
    sprintf(rname,"new_nocuts");
    break;
  }
  sprintf(hname,"myanalyzer/cutNoCuts/%s",pname);
  gROOT->SetStyle("Plain");setTDRStyle();    
  TH2F *ptr1;
  TCanvas* c1=new TCanvas("c1","c1",800,800);
  TH1D *py1 = 0;
  fp->GetObject(hname,ptr1);
  ptr1->FitSlicesY();
  sprintf(hname,"%s_2",pname);//change it
  fp->GetObject(hname,py1);
  if (py1 == 0) {
    cerr << "Dang! Whatta I have to do anyway??"<<endl;
    return;
  }
  py1->SetStats(0);
  py1->GetXaxis()->SetTitle("#phi_{Cell}");//change it
  py1->SetTitle();
  py1->GetYaxis()->SetTitle("Width of #phi_{gen}-#phi_{reco}");//change it
  gStyle->SetOptStat(111);
  py1->GetYaxis()->SetTitleOffset(1.6);
  c1->SetLeftMargin(0.20);
  py1->Draw();
  zrap_Prelim(.78,.9);
  sprintf(name,"/home/grad/klapoetke/public_html/talk/fig_projected_%s_%s_%s.png",cname,pname,rname);
  c1->Print(name);
}
