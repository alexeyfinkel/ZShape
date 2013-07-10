void note_Zmass(TFile* f0, TFile* f1, TFile* f2,TFile* f3, TFile* f4, TFile* f5,TFile* f6,TFile* f7) {

  //root newVarsZStudy01.root newVarsWenu01.root /data/whybee0c/user/dudero/HFEMIDZeeAnal/Summer08_*root 
  //.x note/note_Zmass.C(_file0,_file3,_file4,_file5,_file6,_file7,_file8,_file1)
  gROOT->SetStyle("Plain"); 
  TCanvas* c1=new TCanvas("c1","c1",900,700);
  c1->SetRightMargin(0.02);
  c1->SetTopMargin(0.02);
  c1->SetBottomMargin(0.12);
  double scale;

  
  TH1* z0=f0->Get("analRobustIDand2Dpt5/cutNoCuts/NoCutsinvMass")->Clone("rz0");
  scale = 1323.0*100/50000;
  z0->Scale(scale);
  
  TH1* qe1=f4->Get("analRobustIDand2Dpt5/cutNoCuts/NoCutsinvMass")->Clone("rw1");
  scale = 127.7454;//4e8*0.008*50/3855219;
  qe1->Scale(scale);
  
  TH1* qe2=f5->Get("analRobustIDand2Dpt5/cutNoCuts/NoCutsinvMass")->Clone("rw2");
  scale = 123.7268;//1e8*0.047*50/4802942;
  qe2->Scale(scale);
  
  TH1* qe3=f6->Get("analRobustIDand2Dpt5/cutNoCuts/NoCutsinvMass")->Clone("rw3");
  scale = 6.5115;//19e5*0.15*50/8509935;
  qe3->Scale(scale);
  
  TH1* qb1=f1->Get("analRobustIDand2Dpt5/cutNoCuts/NoCutsinvMass")->Clone("rw4");
  scale =44.921;//4e8*0.00048*50/839940;
  qb1->Scale(scale);
  
  TH1* qb2=f2->Get("analRobustIDand2Dpt5/cutNoCuts/NoCutsinvMass")->Clone("rw5");
  scale =48.6583;//1e8*0.0024*50/1025263;
  qb2->Scale(scale);
  
  TH1* qb3=f3->Get("analRobustIDand2Dpt5/cutNoCuts/NoCutsinvMass")->Clone("rw6");
  scale = 2.8570;//19e5*0.012*50/798039;
  qb3->Scale(scale);
  
  TH1* w1=f7->Get("analRobustIDand2Dpt5/cutNoCuts/NoCutsinvMass")->Clone("rw7");
  scale =8756.37*50/1107701;
  w1->Scale(scale);
  
  
   
  
  // h0->Add(h1);
  
  qe1 ->Add(qe2);
  qe1->Add(qe3);
  qb1->Add(qb2);
  qb1->Add(qb3);
  //stacking 
  // qb1->Add(w1);
  qe1->Add(qb1);
  // ->Add();
  
  
  gStyle->SetStatX(0.98);
  gStyle->SetStatY(0.98);
  gStyle->SetStatW(0.3);
  //  gStyle->SetStatFontSize(0.98);
  gStyle->SetOptStat(0000);
  gStyle->cd();


  z0->Rebin(2);
  qb1->Rebin(2);
  qe1->Rebin(2);
  

  z0->SetLineWidth(3);
  w1->SetLineWidth(3);
  qb1->SetLineWidth(3);
  qe1->SetLineWidth(3);

   w1->SetLineStyle(3);
  qb1->SetLineStyle(5);
  qe1->SetLineStyle(2);

  z0->SetLineColor(1);
  w1->SetLineColor(1);
  qb1->SetLineColor(2);
  qe1->SetLineColor(4);
  //h0->SetLineStyle(2);
  
  qe1->SetStats(0);
  qe1->GetYaxis()->SetTitle("Events/bin in 100 pb^{-1}");
  qe1->GetXaxis()->SetTitle("Invarient Mass Gev");
  qe1->GetXaxis()->CenterTitle();
  
  z0->SetStats(0);
  z0->GetYaxis()->SetTitle("Events/bin in 100 pb^{-1}");
  z0->GetYaxis()->SetTitleOffset(1.2);
  z0->GetXaxis()->SetTitle("Invarient Mass [GeV]");
  z0->GetXaxis()->CenterTitle();
  
  z0->SetTitle(0);//"Projected 2 Dimensional Cut");
  qe1->SetTitle(0);
  z0->SetAxisRange(40,120);
  qe1->SetAxisRange(40,120);
  // qe1->Draw("HIST");
  //z0->Draw("SAMEHIST");
  // qe1->Draw("HIST");
   z0->Draw("HIST");
   qe1->Draw("SAMEHIST");
  // z0->Draw("SAMEHIST");
  qb1->Draw("SAMEHIST");
  w1->Draw("SAMEHIST");
  TLegend* tl=new TLegend(0.10,0.85,0.4,0.98,"");
  tl->SetFillColor(10);
  tl->AddEntry(z0,"Z#rightarrow e+e-");
  tl->AddEntry(w1,"W+jets");
  tl->AddEntry(qb1,"QCD BC to E");
  tl->AddEntry(qe1,"QCD EM enriched");

  
  tl->Draw("SAME");
  
  //  c1->Print("m_ee.png");
}
