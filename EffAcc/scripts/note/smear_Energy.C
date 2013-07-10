#include "TH2F.h"
#include "TFile.h"
#include "TH1D.h"
#include "TF1.h"

#include <iostream>
using namespace std;

void smear_Energy(TFile *fp)
{
  gROOT->SetStyle("Plain");  
  TH2F *ptr1;
 

   TH1D *py1 = 0;

   fp->GetObject("myanalyzer/cuttwoDim/twoDimHFEnergyRes",ptr1);
   ptr1->FitSlicesY();
 
  fp->GetObject("twoDimHFEnergyRes_1",py1);

  gStyle->SetOptFit(1111);

  ptr1->ProjectionY("EnergyRes0_140",1,2,"");
  ptr1->ProjectionY("EnergyRes140_210",3,3,"");
  ptr1->ProjectionY("EnergyRes210_420",4,6,"");
  ptr1->ProjectionY("EnergyRes420_560",7,8,"");
  ptr1->ProjectionY("EnergyRes560_840",9,12,"");
  ptr1->ProjectionY("EnergyRes840_1120",13,16,"");
  ptr1->ProjectionY("EnergyRes1120_1400",17,21,"");
  ptr1->ProjectionY("EnergyRes1400up",22,33,"");
  ptr1->ProjectionY("EnergyResnone",34,49,"");
  //ptr1->ProjectionY("EnergyRes",,,"");
  if (py1 == 0) {
    cerr << "Dang! Whatta I have to do anyway??"<<endl;
     return;
  }
  py1->SetStats(0);
  py1->GetXaxis()->SetTitle("Energy [GeV]");
  py1->GetXaxis()->CenterTitle();
  TF1 *f1 = new TF1 ("f1","[0]+[1]*x/999999999.9",0,2000);
  f1->SetParameters(.45,1);
  f1->SetLineColor(2);
  f1->SetLineWidth(2);
  f1->SetLineStyle(2);
  py1->SetMarkerStyle(21);
  py1->SetTitle();
  py1->GetYaxis()->SetTitle("(E_{gen}-E_{reco})/E_{gen}");
  gStyle->SetOptStat(111);

  //py1->GetYaxis()->SetTitleOffset(1.5);
  py1->Fit("f1","R");
  py1->Draw();
}
