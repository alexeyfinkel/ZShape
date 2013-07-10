#include "tdrstyle.C"
//#include "zrapidityStandard.C"


void note_deltaPhi(TFile* f0, TFile* f1){//, TFile* f2,TFile* f3, TFile* f4, TFile* f5){
  
  gROOT->SetStyle("Plain"); setTDRStyle();
  TCanvas* c1=new TCanvas("c1","c1",900,700);
  c1->SetRightMargin(0.02);
  c1->SetTopMargin(0.02);
  c1->SetBottomMargin(0.12);
  double scale;
    
  TH1* c0=f0->Get("myanalyzer/cutNoCuts/HFDeltaPhi")->Clone("rc0");
  TH1* u0=f1->Get("myanalyzer/cutNoCuts/HFDeltaPhi")->Clone("rw1");
    
  gStyle->SetOptStat(1101);
  //gStyle->SetOptFit(111);
    
  c0->GetYaxis()->SetTitle("");
  c0->GetXaxis()->SetTitle("#phi_{gen}-#phi_{raw}");
    
  //c0->GetXaxis()->CenterTitle();
  c0->GetYaxis()->CenterTitle();
  c0->SetTitle(0);
  c0->SetName("Corrected");
  u0->SetName("Uncorrected");
  c0->SetLineColor(1);
  u0->SetLineColor(2);
  c0->SetLineWidth(2);
  u0->SetLineWidth(4);
  u0->SetLineStyle(5);
  
  c0->SetMarkerColor(4);
  u0->SetMarkerColor(2);
  TF1 *f2 = new TF1("f2","gaus",-.08,.08);
  TF1 *f3 = new TF1("f2","gaus",-.08,.08);
  c0->Fit("f2","R");
  u0->Fit("f3","R");
  TPaveStats *st = (TPaveStats*)u0->FindObject("stats");
  st->SetY1NDC(.05);  
  st->SetY2NDC(.1);  
  st->SetX1NDC(0.5);  
  st->SetX2NDC(0);  

  c0->Draw("Hist");
  gStyle->SetStatW(.19);
  
  u0->Draw("SAMES Hist");
  
  
  
  TLegend* tl=new TLegend(0.10,0.85,0.4,0.98,"");
  tl->SetFillColor(10);
  
  tl->AddEntry(c0,"Corrected");
  tl->AddEntry(u0,"Uncorrected");
  tl->Draw("SAME");

  //zrap_Prelim(.75,.8);
c1->Print("/home/grad/klapoetke/public_html/talk/fig_deltaphi.png");
  }
