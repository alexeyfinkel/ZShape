
#include "TH2F.h"
#include "TFile.h"
#include "TH1D.h"
#include "TF1.h"
#include "tdrstyle.C"
//#include "zrapidityStandard.C"
#include <iostream>


void note_primecut(TFile* f0){//, TFile* f2,TFile* f3, TFile* f4, TFile* f5){
 
  gROOT->SetStyle("Plain"); setTDRStyle(); 
  char name[128];
  char mess[128];

  char vars[4][128];
  sprintf(vars[0],"eselVlogel");
  sprintf(vars[1],"COReselVlogel");
  sprintf(vars[2],"COReselVeCe9");


char varsy[4][128];
  sprintf(varsy[0],"E_{S}E_{L}");
  sprintf(varsy[1],"E_{S}E_{L}^{cor}");
  sprintf(varsy[2],"E_{S}E_{L}^{cor}");

char varsx[4][128];
  sprintf(varsx[0],"Log(E_{L}/100) [GeV]");
  sprintf(varsx[1],"Log(E_{L}/100) [GeV]");
  sprintf(varsx[2],"E_{C}E_{9}");
  
  
  for(int tt=0;tt<3;tt++){
     sprintf(name,"c_%s",vars[tt]);
    TCanvas* c1=new TCanvas(name,name,900,700);
    c1->SetRightMargin(0.02);
    c1->SetTopMargin(0.02);
    c1->SetBottomMargin(0.12);
    double scale;
    
    sprintf(name,"myanalyzer/cutNoCuts/%s",vars[tt]);
    sprintf(mess,"clone%i",tt);
    TH2* z0=f0->Get(name)->Clone(mess);
       
    gStyle->SetOptStat(0000);
    //gStyle->SetOptFit(1111);
    
    z0->GetYaxis()->SetTitle(varsy[tt]);
    
    z0->GetXaxis()->SetTitle(varsx[tt]);
    
    
    //z0->GetXaxis()->CenterTitle();
    //z0->GetYaxis()->CenterTitle();
    z0->SetTitle(0);
    z0->SetLineColor(1);
    
    z0->SetLineWidth(2);
    TF1 *f1 = new TF1 ("f1","[0]*x+[1]",0.0,3);
    
    z0->Fit("f1");//may be wrong
    
    z0->Draw("Box");
    zrap_Prelim(.78,.2);
    sprintf("/home/grad/klapoetke/public_html/cmsdoc/PHD/trunk/figs/fig_%s.eps",vars[tt]);
    //c1->Print(name);

double m=f1->GetParameter(0);
    double b=f1->GetParameter(1);
    printf("m=%0.2f b=%0.2f alpha= %0.2f  beta= %0.2f  gamma= %0.2f",m,b,-b*1.0/sqrt(1+m*m),-m*1.0/sqrt(1+m*m),1.0/sqrt(1+m*m));
  }
  
  
}
