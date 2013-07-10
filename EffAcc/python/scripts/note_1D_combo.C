#include "TH2F.h"
#include "TFile.h"
#include "TH1D.h"
#include "TF1.h"
#include "tdrstyle.C"
//#include "zrapidityStandard.C"
#include <iostream>
using namespace std;

void note_1D_combo(TFile *fp,TFile *fm,int plot,int cor,int mode)
{

  bool is1D=false;
  char name[126];
  char hname[126];
  char cname[126];
  char pname[126];
  char rname[126];
  char xname[126];
  char yname[126];
  char dname[126];
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
    sprintf(xname,"|#eta^{gen}|-|#eta^{reco}|");
    sprintf(yname,"Events/bin");
    sprintf(dname,"cutNoCuts");
    is1D=true;
    break;
  case 1:
    sprintf(pname,"HFDeltaPhi");//th1
    sprintf(xname,"#Delta#phi");
    sprintf(yname,"Events/bin");
    sprintf(dname,"cutNoCuts");
    is1D=true;
    break;
  case 2:
    sprintf(pname,"PhiRes");
    sprintf(xname,"#phi^{reco}_{cell}");
    sprintf(yname,"#Delta#phi");
    sprintf(dname,"cutNoCuts");

    break;
  case 3:
    sprintf(pname,"EtaRes");//Corrections
    sprintf(xname,"#eta^{reco}_{cell}");
    sprintf(yname,"|#eta^{gen}|-|#eta^{reco}|");
    sprintf(dname,"Corrections");

    break;
  case 4:
    sprintf(pname,"HFEtaResVlogE");//Corrections
    sprintf(xname,"Log(E^{3x3}/100 GeV)");
    sprintf(yname,"|#eta^{gen}|-|#eta^{reco}|");
    sprintf(dname,"Corrections");

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
  sprintf(hname,"myanalyzer/%s/%s",dname,pname);
gROOT->SetStyle("Plain");
  setTDRStyle();    
  TCanvas* c1=new TCanvas("c1","c1",600,600);
  if(is1D) { TH1F *py1 = 0; TH1F *py2 = 0;}
  else {TH2F *py1 = 0;TH2F *py2 = 0;}
  
  fp->GetObject(hname,py1);
    fm->GetObject(hname,py2);
  if (py1 == 0) {
    cerr << "Dang! Whatta I have to do anyway??"<<endl;
    return;
  }
  py1->SetStats(0);
  py1->GetXaxis()->SetTitle(xname);
  //py1->GetXaxis()->CenterTitle();
  py1->SetTitle();
  py1->GetYaxis()->SetTitle(yname);
  //py1->GetYaxis()->CenterTitle();
  gStyle->SetOptStat(111);
  py1->GetYaxis()->SetTitleOffset(2.0);
  c1->SetLeftMargin(0.20);
  py1->Draw();
  py2->SetLineColor(kRed);
  py2->Draw("Same");
  // zrap_Prelim(.78,.9);
  sprintf(name,"/home/grad/klapoetke/public_html/talk/fig1D_%s_%s_%s.png",cname,pname,rname);
  c1->Print(name);
}
