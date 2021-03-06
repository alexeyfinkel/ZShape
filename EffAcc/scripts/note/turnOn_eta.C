#include "tdrstyle.C"

void turnOn_eta(TFile* f0){
  
  gROOT->SetStyle("Plain"); setTDRStyle();
  TCanvas* c1=new TCanvas("c1","c1",900,700);
  c1->SetRightMargin(0.02);
  c1->SetTopMargin(0.02);
  c1->SetBottomMargin(0.12);
  //double eff;
  double sum=0;  
  TH1* c0=f0->Get("myanalyzer/NoCuts/fabseta")->Clone("rc0");
  effSum = new TH1F ("TurnOnEta", "Efficiency for eta",90,2,5);
  
  for (int i=1;i<=90;i++){
    
    //eff=(c0->GetBinContent(i))+(c0->GetBinContent(i-1));
    // effSum->SetBinContent(i,(c0->GetBinContent(i-1))+(c0->GetBinContent(i)));
    //double here=c0->GetBinContent(i);
    //double there=c0->GetBinContent(i-1);
    sum+=c0->GetBinContent(i);
    effSum->SetBinContent(i,sum);

  }
  effSum->Scale(1.0/14627);
  gStyle->SetOptStat(0000);
  c1->SetGridy();
    
  effSum->GetYaxis()->SetTitle("");
  effSum->GetXaxis()->SetTitle("#eta");
    
  effSum->GetXaxis()->CenterTitle();
  effSum->GetYaxis()->CenterTitle();
  effSum->SetTitle(0);
  effSum->SetLineColor(1);

  
  effSum->SetMarkerColor(4);
 
 
  effSum->Draw("Hist");
 
}
