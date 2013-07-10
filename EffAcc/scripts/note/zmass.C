
#include "tdrstyle.C"
void zmass(TFile* ef){
  gROOT->SetStyle("Plain");
  setTDRStyle();
  //  TH1* z0=ef->Get("analRobustIDand2Dpt5/cutNoCuts/NoCutsZeeMass")->Clone("rz0"); 
TH1* z0=ef->Get("analRobustIDand2Dpt5/cutNoCuts/NoCutsinvMass")->Clone("rz0"); 
scale = 1323.0*100/50000;
  z0->Scale(scale);

    
 c1->SetLeftMargin(0.20);
 
  z0->GetXaxis()->SetTitle("m_{ee}");
  z0->SetLineWidth(3);
  z0->SetStats(0);
  z0->GetYaxis()->SetTitle("Events/bin in 100 pb^{-1}");
  z0->GetXaxis()->CenterTitle();
  z0->GetYaxis()->CenterTitle();
  //z0->Rebin(3);
  //z0->Scale(1.0/3);
 z0->GetYaxis()->SetTitleOffset(1.6);
  TCanvas* c1=new TCanvas("c1","c1",800,800);
  z0->Draw("Hist"); 
  //z0->Draw("E"); 
  gStyle->SetOptStat(1111);
 zrap_Prelim(.75,.8); 
 

c1->Print("/home/grad/klapoetke/public_html/note/zmassONLY.eps");
  
 
 
  // c1->Print("note_Et_Efficiency.eps");
}
