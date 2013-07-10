#include "TH2F.h"
#include "TFile.h"
#include "TH1D.h"
#include "TF1.h"
#include "TCanvas.h"
//#include "tdrstyle.C"
#include <iostream>
//#include "zrapidityStandard.C"

using namespace std;

void note_project(TFile *fp, int mode)
{
  //gROOT->SetStyle("Plain");//setTDRStyle();  
  TH2F *ptr1;
  char name[126];
  char hname[126];
  char pname[126];
  TCanvas* c1=new TCanvas("c1","c1",400,400);
  
  switch (mode){
  case 0:
    sprintf(name,"HFEtaResVlogE"); 
    break; 
  case 1:
    sprintf(name,"eta_V_EtaRes");
    break; 
  case 2:
    sprintf(name,"logEcorrectin_EtaRes");
    break;
  
 case 3:
    sprintf(name,"EtaRes_genCell");
    break;
 
 case 4:
    sprintf(name,"EtaRes");
    break;
 case 5:
    sprintf(name,"EtaRes_all");
    break;
 case 6:
    sprintf(name,"DeltaCellEta_Vs_DeltaEta");
    break;
 case 7:
    sprintf(name,"DcelletaVsRecoCellEta");
    break;
 case 8:
    sprintf(name,"DeltaEta_Vs_seedDeta");
    break;
  case 9:
    sprintf(name,"HFEtaResVlogE_logcor"); 
    break; 
  case 10:
    sprintf(name,"EtaRes_logcor_etacor");//_etacor_logcor
    break;
  case 11:
    sprintf(name,"newcell_EtaRes_logcor_etacor");//_etacor_logcor
    break;
  }
  printf("%s",name);
  sprintf(hname,"myanalyzer/Corrections/%s",name);
  sprintf(pname,"%s_1",name);
  TH1D *py1 = 0;
  fp->GetObject(hname,ptr1);
  //ptr1->RebinX(5);
  ptr1->FitSlicesY();
  fp->GetObject(pname,py1);
  if (py1 == 0) {
    cerr << "Dang! Whatta I have to do anyway??"<<endl;
    return;
  }
  //  TF1 *f1 = new TF1 ("f1","[0]*sin(x*[1]+[2])+[3]",.0,1);//2pi=6.283185307
  //f1->SetParameters(1,6.283185307,-0.377,0.1);
  //  TF1 *f1 = new TF1 ("f1","[0]*sin(x*6.283185307+(-0.377))+[1]",0.1,0.9); 
  //f1->SetParameters(1,0.1);
  //TF1 *f1 = new TF1 ("f1","[0]*tan((x-[1])*[2])+[3]",-.1,1.2); 
  // TF1 *f3 = new TF1 ("f3","[0]+[1]*x+[2]*x*x+[3]*x*x*x",-.2,1.2);
  //TF1 *f1 = new TF1 ("f1","[0]+[1]*x+[2]*x*x",-.2,.5);

  //TF1 *f2 = new TF1 ("f2","[0]+[1]*x+[2]*x*x",.5,1.2);

  //f1->SetParameters(0.013,-0.091,0.14);
  //f2->SetParameters(-0.06,0.19,-0.14);
  py1->SetStats(0);
  py1->GetXaxis()->SetTitle(name);
  //py1->GetXaxis()->CenterTitle();
  //f1->SetLineColor(2);
  //f2->SetLineColor(2);
  //f3->SetLineColor(2);
  py1->SetTitle(0);
  py1->GetYaxis()->SetTitle("|#eta_{gen}|-|#eta_{raw}|");
  py1->GetYaxis()->SetTitleOffset(1.5);
  gStyle->SetOptStat(111);
  //py1->Fit("f1","","",-.2,.5);
  //py1->Fit("f2","","",.5,1.2);
  //py1->Fit("f3");
  py1->SetMaximum(0.04);
  py1->SetMinimum(-0.04);
  c1->SetLeftMargin(0.20);
  py1->Draw("P");
  //f1->Draw("same");
  //f2->SetLineColor(kRed);
  //f2->Draw("same");
  //f3->SetLineColor(kBlue);

  //zrap_Prelim(.7,.8);
  sprintf(hname,"/home/grad/klapoetke/public_html/talk/fig_%s.png",name);
  c1->Print(hname);
}
