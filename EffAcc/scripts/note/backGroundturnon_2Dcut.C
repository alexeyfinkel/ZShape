#include "tdrstyle.C"

void backGroundturnon_2Dcut(TFile* f0){
  
  gROOT->SetStyle("Plain");setTDRStyle(); 
  TCanvas* c1=new TCanvas("c1","c1",900,700);
  c1->SetRightMargin(0.02);
  c1->SetTopMargin(0.02);
  c1->SetBottomMargin(0.12);
  //double eff;
  double sum=0;  
  TH1* c0=f0->Get("myanalyzer/cutNoCuts/NoCutsyIntercept")->Clone("rc0");
  c0->Scale(1.0/c0->GetEntries()); 
  effSum = new TH1F ("TurnOne9e25", "Turn on curve for eSeL",80,-1.5,1.1);
  
  for (int i=1;i<=80;i++){
    
    sum+=c0->GetBinContent(i);
    effSum->SetBinContent(i,(sum));
    
  }
  
  gStyle->SetOptStat(0000);
  c1->SetGridy();
    
  effSum->GetYaxis()->SetTitle("#epsilon(E_{C/9}-E_{s/l}x1.125)");
  effSum->GetXaxis()->SetTitle("E_{C/9}-E_{s/l}x1.125");
    
  effSum->SetTitle(0);
  effSum->SetLineColor(1);

  
  effSum->SetMarkerColor(4);
  TLine* l1=new TLine(.55,0,.55,1);
  TLine* l2=new TLine(.32,0,.32,1);
  l1->SetLineWidth(3);
  l2->SetLineWidth(3);
  l2->SetLineStyle(5);

  effSum->Draw("Hist");
  l1->Draw("Same");
  l2->Draw("Same");
 TLegend* tl=new TLegend(0.20,0.8,0.4,0.9,"");
  tl->SetFillColor(10);
  
  tl->AddEntry(l1,"Tight Cut");
  tl->AddEntry(l2,"Loose Cut");
  tl->Draw("SAME");
  zrap_Prelim(.35,.6); c1->SetGridy();
  c1->Print("/home/grad/klapoetke/public_html/note/backGroundturnon_2Dcut.eps");


}
