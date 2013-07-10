#include "tdrstyle.C"
#include "zrapidityStandard.C"

void note_eCOREe9(TFile* f0, TFile* f1){
  
  gROOT->SetStyle("Plain");  setTDRStyle();
  TCanvas* c1=new TCanvas("c1","c1",900,700);
  c1->SetRightMargin(0.02);
  c1->SetTopMargin(0.02);
  c1->SetBottomMargin(0.12);
  double scale;
    
  TH1* c0=f0->Get("myanalyzer/cutNoCuts/NoCutseCOREe9")->Clone("rc0");
  TH1* u0=f1->Get("myanalyzer/cutNoCuts/NoCutseCOREe9")->Clone("rw1");
   c0->Scale(u0->GetEntries()/c0->GetEntries()); 
  gStyle->SetOptStat(0000);
  gStyle->SetOptFit(1111);
    
  c0->GetYaxis()->SetTitle("");
  c0->GetXaxis()->SetTitle("E_{CORE}/E_{3x3}");
    
  c0->GetXaxis()->CenterTitle();
  c0->GetYaxis()->CenterTitle();
  c0->SetTitle(0);
  c0->SetLineColor(1);
  u0->SetLineColor(2);
  c0->SetLineWidth(2);
  u0->SetLineWidth(4);
  u0->SetLineStyle(5);
  
  c0->SetMarkerColor(4);
  u0->SetMarkerColor(2);
 
  c0->Draw("Hist");
  u0->Draw("Same Hist");
  
  TLegend* tl=new TLegend(0.10,0.85,0.4,0.98,"");
  tl->SetFillColor(10);
  
  tl->AddEntry(c0,"Z#rightarrow e+e-");
  tl->AddEntry(u0,"QCD EM enriched");
  //tl->AddEntry(u0,"W+jets");
  //tl->AddEntry(u0,"QCD BC to E");
  //tl->AddEntry(u0,"QCD EM enriched");
  tl->Draw("SAME");
  zrap_Prelim(.75,.8);
c1->Print("/home/grad/klapoetke/public_html/cmsdoc/PHD/trunk/figs/fig_eCe9.eps");
  }
