

void note_primecutBlacknWhite(TFile* f0,TFile* f2){//, TFile* f2,TFile* f3, TFile* f4, TFile* f5){


  gROOT->SetStyle("Plain"); 
  TCanvas* c1=new TCanvas("c1","c1",900,700);
   c1->SetRightMargin(0.02);
   c1->SetTopMargin(0.02);
   c1->SetBottomMargin(0.12);
  double scale;


  TH2* z0=f0->Get("myanalyzer/cutNoCuts/NoCutsCutPrime")->Clone("rz0");
  // TH2* z0=f0->Get("analLooseIDand2Dpt32/cutNoCuts/NoCutsCutPrime")->Clone("rz0");
   TH2* w0=f2->Get("analLooseIDand2Dpt5/cutNoCuts/NoCutsCutPrime")->Clone("rz1");

   w0->Scale(z0->GetEntries()/w0->GetEntries());



  gStyle->SetOptStat(0000);
  gStyle->SetOptFit(1111);
 
  z0->GetYaxis()->SetTitle("E_{CORE}/E_{9}");
  
  z0->GetXaxis()->SetTitle("E_{short}/E_{long}");


  //z0->GetXaxis()->CenterTitle();
  //z0->GetYaxis()->CenterTitle();
  z0->SetTitle(0);
  z0->SetLineColor(1);
 
  z0->SetLineWidth(2);
  z0->Draw("Hist");
  w0->Draw("SAME Box");

  }
