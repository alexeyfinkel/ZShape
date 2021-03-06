#include "tdrstyle.C"

void note_turnOn_e9e25(TFile* f0,TFile* f1){
  
  gROOT->SetStyle("Plain"); setTDRStyle();
  TCanvas* c1=new TCanvas("c1","c1",900,700);
  c1->SetRightMargin(0.02);
  c1->SetTopMargin(0.02);
  c1->SetBottomMargin(0.12);
  //double eff;
  double sum=0; 
  double bsum=0; 
  TH1* c0=f0->Get("myanalyzer/cutNoCuts/NoCutse9e25")->Clone("rc0");
  effSum = new TH1F ("TurnOne9e25", "Turn on curve for e9e25",80,0,1.1);
  c0->Scale(1.0/c0->GetEntries());//c0->GetEntries()50149
  
  TH1* b0=f1->Get("myanalyzer/cutNoCuts/NoCutse9e25")->Clone("rc9");
  beffSum = new TH1F ("TurnOne9e25", "Turn on curve for e9e25",80,0,1.1);
  b0->Scale(1.0/b0->GetEntries());//c0->GetEntries()50149
  
  for (int i=1;i<=80;i++){
    
    //eff=(c0->GetBinContent(i))+(c0->GetBinContent(i-1));
    // effSum->SetBinContent(i,(c0->GetBinContent(i-1))+(c0->GetBinContent(i)));
    //double here=c0->GetBinContent(i);
    //double there=c0->GetBinContent(i-1);
    sum+=c0->GetBinContent(i);
    bsum+=b0->GetBinContent(i);

    effSum->SetBinContent(i,1-sum);
    beffSum->SetBinContent(i,1-bsum);
  }
  
  gStyle->SetOptStat(0);
  c1->SetGridy();
    
  effSum->GetYaxis()->SetTitle("#epsilon(E_{3x3}/E_{5x5})");
  effSum->GetXaxis()->SetTitle("E_{3x3}/E_{5x5}");
    
  
  effSum->SetTitle(0);
  effSum->SetLineColor(1);
 
  beffSum->SetTitle(0);
 
  beffSum->SetLineStyle(5);
  beffSum->SetLineWidth(2);
 
  TLine* l1=new TLine(.94,0,.94,1);
  l1->SetLineWidth(3);

  effSum->Draw("Hist");
  beffSum->Draw("Same Hist");
  l1->Draw("Same");
 
 TLegend* tl=new TLegend(0.20,0.8,0.4,0.9,"");
  tl->SetFillColor(10);
  tl->AddEntry(effSum,"Z #rightarrow e+e-");
  tl->AddEntry(beffSum,"QCD EM enriched");
  tl->AddEntry(l1,"Identification Cut");
  
  
  tl->Draw("SAME");
  zrap_Prelim(.7,.8); c1->SetGridy();
  c1->Print("/home/grad/klapoetke/public_html/note/note_turnOn_e9e25.eps");

 
}
