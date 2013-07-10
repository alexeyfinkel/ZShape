#include "TH1.h"
#include "TMath.h"
#include "TCanvas.h"
#include "TFile.h"
#include "TGraph.h"
#include "TGraphErrors.h"
#include "TLegend.h"
#include "TH2.h"

#include "tdrstyle.C"
#include "zrapidityStandard.C"

//.x ../scripts/FourxFourRatio.C("mcEff/EE-HF/C08-m(60,120)/Z0_PtTLMon_MC","mcEff/EE-HF/C08-m(60,120)/wZ0_at","mcEff/EE-HF/C08-m(60,120)/Z0_at_MC","mcEff/EE-HF/C08-m(60,120)/wZ0_at",_file0,_file1,_file2,_file3,_file4,_file5,_file6)


//.x ../scripts/FourxFourRatio.C("mcEff/EE-HF/C08-m(60,120)/Z0_at_MC","mcEff/EE-HF/C08-m(60,120)/wZ0_at","mcEff/EE-HF/C08-m(60,120)/wZ0_phiStar_MC","mcEff/EE-HF/C08-m(60,120)/wZ0_phiStar",_file0,_file1,_file2,_file3,_file4,_file5,_file6)

//.x ../scripts/FourxFourRatio.C("mcEff/EE-HF/C08-m(60,120)/Z0_at_MC","mcEff/EE-HF/C08-m(60,120)/wZ0_at","mcEff/EE-HF/C08-m(60,120)/Z0_at_MC","mcEff/EE-HF/C08-m(60,120)/wZ0_at",_file0,_file3,_file5,_file7,_file9,_file12,_file13)  

void FourxFourRatio(const char* name1R,const char* name1TL,const char* name2R,const char* name2TL,TFile* f1,TFile* f2,TFile* f3,TFile* f4,TFile* f5,TFile* f6,TFile* f7,int rbin/*,TFile* f8,TFile* f9*/){

  //gROOT->SetStyle("Plain");  //makes plot white not grey
  setTDRStyle();           //make

 TCanvas* c1=new TCanvas("Compare","Compare",800,600);
 c1->Divide(2,2);

 c1->cd(1);

  TH1F* h1[20];
  h1[0]=(TH1F*)f1->Get(name1R)->Clone("cl1");
  h1[1]=(TH1F*)f2->Get(name1R)->Clone("cl2");
  h1[2]=(TH1F*)f3->Get(name1R)->Clone("cl3");
  h1[3]=(TH1F*)f4->Get(name1R)->Clone("cl4");
  h1[4]=(TH1F*)f5->Get(name1R)->Clone("cl5");
  h1[5]=(TH1F*)f6->Get(name1R)->Clone("cl6");
  h1[6]=(TH1F*)f7->Get(name1R)->Clone("cl7");
  //h1[7]=(TH1F*)f8->Get(name1R)->Clone("cl8");
  //h1[8]=(TH1F*)f9->Get(name1R)->Clone("cl9");
  int hn=6;
  h1[0]->SetLineColor(kRed);
  h1[1]->SetLineColor(kBlack);
  h1[2]->SetLineColor(kBlue);
  h1[3]->SetLineColor(kGreen);
  h1[4]->SetLineColor(kViolet);
  h1[5]->SetLineColor(kCyan);
  h1[6]->SetLineColor(kOrange);
  //h1[7]->SetLineColor(kYellow+3);
  //h1[8]->SetLineColor();
  //h1[]->SetLineColor();
  
  TH1F* h2[20];
  h2[0]=(TH1F*)f1->Get(name1TL)->Clone("Ncl1");
  h2[1]=(TH1F*)f2->Get(name1TL)->Clone("Ncl2");
  h2[2]=(TH1F*)f3->Get(name1TL)->Clone("Ncl3");
  h2[3]=(TH1F*)f4->Get(name1TL)->Clone("Ncl4");
  h2[4]=(TH1F*)f5->Get(name1TL)->Clone("Ncl5");
  h2[5]=(TH1F*)f6->Get(name1TL)->Clone("Ncl6");
  h2[6]=(TH1F*)f7->Get(name1TL)->Clone("Ncl7");
  //h2[7]=(TH1F*)f8->Get(name1TL)->Clone("Ncl8");
  //h2[8]=(TH1F*)f9->Get(name1TL)->Clone("Ncl9");
  
  h2[0]->SetLineColor(kRed);
  h2[1]->SetLineColor(kBlack);
  h2[2]->SetLineColor(kBlue);
  h2[3]->SetLineColor(kGreen);
  h2[4]->SetLineColor(kViolet);
  h2[5]->SetLineColor(kCyan);
  h2[6]->SetLineColor(kOrange);
  //h2[7]->SetLineColor(kYellow+3);
  //h2[8]->SetLineColor();
  //h2[]->SetLineColor();
  
  TH1F* h3[20];
  h3[0]=(TH1F*)f1->Get(name2R)->Clone("Ocl1");
  h3[1]=(TH1F*)f2->Get(name2R)->Clone("cOl2");
  h3[2]=(TH1F*)f3->Get(name2R)->Clone("Ocl3");
  h3[3]=(TH1F*)f4->Get(name2R)->Clone("Ocl4");
  h3[4]=(TH1F*)f5->Get(name2R)->Clone("Ocl5");
  h3[5]=(TH1F*)f6->Get(name2R)->Clone("Ocl6");
  h3[6]=(TH1F*)f7->Get(name2R)->Clone("Ocl7");
  //h3[7]=(TH1F*)f8->Get(name2R)->Clone("Ocl8");
  //h3[8]=(TH1F*)f9->Get(name2R)->Clone("Ocl9");
  
  h3[0]->SetLineColor(kRed);
  h3[1]->SetLineColor(kBlack);
  h3[2]->SetLineColor(kBlue);
  h3[3]->SetLineColor(kGreen);
  h3[4]->SetLineColor(kViolet);
  h3[5]->SetLineColor(kCyan);
  h3[6]->SetLineColor(kOrange);
  //h[7]->SetLineColor(kYellow+3);
  //h[8]->SetLineColor();
  //h[]->SetLineColor();
  
  TH1F* h4[20];
  h4[0]=(TH1F*)f1->Get(name2TL)->Clone("Mcl1");
  h4[1]=(TH1F*)f2->Get(name2TL)->Clone("Mcl2");
  h4[2]=(TH1F*)f3->Get(name2TL)->Clone("Mcl3");
  h4[3]=(TH1F*)f4->Get(name2TL)->Clone("Mcl4");
  h4[4]=(TH1F*)f5->Get(name2TL)->Clone("Mcl5");
  h4[5]=(TH1F*)f6->Get(name2TL)->Clone("Mcl6");
  h4[6]=(TH1F*)f7->Get(name2TL)->Clone("Mcl7");
  //h4[7]=(TH1F*)f8->Get(name2TL)->Clone("Mcl8");
  //h4[8]=(TH1F*)f9->Get(name2TL)->Clone("Mcl9");
  
  h4[0]->SetLineColor(kRed);
  h4[1]->SetLineColor(kBlack);
  h4[2]->SetLineColor(kBlue);
  h4[3]->SetLineColor(kGreen);
  h4[4]->SetLineColor(kViolet);
  h4[5]->SetLineColor(kCyan);
  h4[6]->SetLineColor(kOrange);
  //h4[7]->SetLineColor(kYellow+3);
  //h4[8]->SetLineColor();
  //h4[]->SetLineColor();
  
  
  
  
  // h1[0]->GetYaxis()->SetTitle("1/#sigma d#sigma/dP_{T}");
  
  h1[0]->GetXaxis()->SetTitle("P_{T} MC [GeV]");
  h1[0]->SetMaximum(2.7);
  h1[0]->SetMinimum(0.15);
  //h1[0]->GetYaxis()->SetTitleOffset(1.2);
  h1[0]->SetTitle(0);  //no title
  h1[0]->SetStats(false);   //no stats box
  h1[0]->GetXaxis()->SetRangeUser(0,40);
  // h1[0]->Rebin(rbin); 
  for(int k=1;k<hn;k++){
    // h1[k]->Rebin(rbin);
    for(int i=1;i<h1[k]->GetNbinsX();i++){
      if(h1[0]->GetBinContent(i)>0){
	
	h1[k]->SetBinContent(i,(h1[k]->GetBinContent(i))*1.0/h1[0]->GetBinContent(i));
      }
    }
   
  
  }
  
  for(int i=1;i<h1[k]->GetNbinsX();i++){
    
    if(h1[0]->GetBinContent(i)>0){ 
      h1[0]->SetBinContent(i,1);
    }
  }
 
  h1[0]->Draw("HIST");
  for(int k=1;k<hn;k++){
  
    h1[k]->SetLineWidth(2);
    h1[k]->Draw("SAME HIST");
  }
  TLegend* tl=new TLegend(0.5,0.7,0.72,0.9,"");
  tl->SetFillStyle(0);
  tl->AddEntry(h1[0],"Parp[91]=0.25","l");
  tl->AddEntry(h1[1],"Parp[91]=0.5","l");
  tl->AddEntry(h1[2],"Parp[91]=0.75","l");
  tl->AddEntry(h1[3],"Parp[91]=1.0","l");
  tl->AddEntry(h1[4],"Parp[91]=1.25","l");
  tl->AddEntry(h1[5],"Parp[91]=1.5","l");
  tl->AddEntry(h1[6],"Parp[91]=2.0","l");
  //tl->AddEntry(h1[7],"Parp[91]=");
  //tl->AddEntry(h1[8],"Parp[91]=");
  tl->Draw();
  
  
  c1->cd(3);
  
  
  h2[0]->GetXaxis()->SetTitle("P_{T} [GeV]");
  h2[0]->SetMaximum(1.7);
  h2[0]->SetMinimum(0.5);
  //h1[0]->GetYaxis()->SetTitleOffset(1.2);
  h2[0]->SetTitle(0);  //no title
  h2[0]->SetStats(false);   //no stats box
  h2[0]->GetXaxis()->SetRangeUser(0,40);
  
  for(int k=1;k<hn;k++){  
    for(int i=1;i<h2[k]->GetNbinsX();i++){
      if(h2[0]->GetBinContent(i)>0){
	h2[k]->SetBinContent(i,(h2[k]->GetBinContent(i))*1.0/h2[0]->GetBinContent(i));
      }
    }
  }
  for(int i=1;i<h2[k]->GetNbinsX();i++){
    
    if(h2[0]->GetBinContent(i)>0){ 
      h2[0]->SetBinContent(i,1);
    }
  }
  // h2[0]->Rebin(rbin);
  h2[0]->Draw("HIST");
  for(int k=1;k<hn;k++){
    //   h2[k]->Rebin(rbin);
    h2[k]->SetLineWidth(2);
    h2[k]->Draw("SAME HIST");
  }

  TLegend* t2=new TLegend(0.5,0.7,0.72,0.9,"");
  t2->SetFillStyle(0);
  t2->AddEntry(h2[0],"Parp[91]=3","l");
  t2->AddEntry(h2[1],"Parp[91]=4","l");
  t2->AddEntry(h2[2],"Parp[91]=5","l");
  t2->AddEntry(h2[3],"Parp[91]=6","l");
  t2->AddEntry(h2[4],"Parp[91]=7","l");
  t2->AddEntry(h2[5],"Parp[91]=8","l");
  t2->AddEntry(h2[6],"Parp[91]=9","l");
  //t2->AddEntry(h2[7],"Parp[91]=");
  //t2->AddEntry(h2[8],"Parp[91]=");
  t2->Draw();

  c1->cd(2);
  h3[0]->GetXaxis()->SetTitle("a_{T} MC [GeV]");
  //h3[0]->GetXaxis()->SetTitle("#phi_{*} MC [GeV]");
  h3[0]->SetMaximum(1.7);
  h3[0]->SetMinimum(0.5);
  //h3[0]->GetYaxis()->SetTitleOffset(1.2);
  h3[0]->SetTitle(0);  //no title
  h3[0]->SetStats(false);   //no stats box
  h3[0]->GetXaxis()->SetRangeUser(0,40);
  h3[0]->Rebin(rbin);  
  for(int k=1;k<hn;k++){
    h3[k]->Rebin(rbin);
    for(int i=1;i<h3[k]->GetNbinsX();i++){
      if(h3[0]->GetBinContent(i)>0){
	h3[k]->SetBinContent(i,(h3[k]->GetBinContent(i))*1.0/h3[0]->GetBinContent(i));
      }
    }
  }
  
  for(int i=1;i<h3[k]->GetNbinsX();i++){
    
    if(h3[0]->GetBinContent(i)>0){ 
      h3[0]->SetBinContent(i,1);
    }
  }
  
  h3[0]->Draw("HIST");
  for(int k=1;k<hn;k++){
    h3[k]->SetLineWidth(2);
    h3[k]->Draw("SAME HIST");
  }
  
  TLegend* t3=new TLegend(0.5,0.7,0.72,0.9,"");
  t3->SetFillStyle(0);
  t3->AddEntry(h3[0],"Parp[91]=3","l");
  t3->AddEntry(h3[1],"Parp[91]=4","l");
  t3->AddEntry(h3[2],"Parp[91]=5","l");
  t3->AddEntry(h3[3],"Parp[91]=6","l");
  t3->AddEntry(h3[4],"Parp[91]=7","l");
  t3->AddEntry(h3[5],"Parp[91]=8","l");
  t3->AddEntry(h3[6],"Parp[91]=9","l");
  //t3->AddEntry(h3[7],"Parp[91]=");
  //t3->AddEntry(h3[8],"Parp[91]=");
  t3->Draw();

  c1->cd(4);
  h4[0]->GetXaxis()->SetTitle("a_{T} [GeV]");
  //  h4[0]->GetXaxis()->SetTitle("#phi_{*} [GeV]");
  h4[0]->SetMaximum(1.7);
  h4[0]->SetMinimum(0.5);
  //h4[0]->GetYaxis()->SetTitleOffset(1.2);
  h4[0]->SetTitle(0);  //no title
  h4[0]->SetStats(false);   //no stats box
  h4[0]->GetXaxis()->SetRangeUser(0,40);
  h4[0]->Rebin(rbin);
  for(int k=1;k<hn;k++){
    h4[k]->Rebin(rbin);
    for(int i=1;i<h4[k]->GetNbinsX();i++){
      if(h4[0]->GetBinContent(i)>0){
	h4[k]->SetBinContent(i,(h4[k]->GetBinContent(i))*1.0/h4[0]->GetBinContent(i));
      }
    }
  }
  
  for(int i=1;i<h4[k]->GetNbinsX();i++){
    
    if(h4[0]->GetBinContent(i)>0){ 
      h4[0]->SetBinContent(i,1);
    }
  }
 
  h4[0]->Draw("HIST");
  for(int k=1;k<hn;k++){
    h4[k]->SetLineWidth(2);
    h4[k]->Draw("SAME HIST");
  }

  TLegend* t4=new TLegend(0.5,0.7,0.72,0.9,"");
  t4->SetFillStyle(0);
  t4->AddEntry(h4[0],"Parp[91]=3","l");
  t4->AddEntry(h4[1],"Parp[91]=4","l");
  t4->AddEntry(h4[2],"Parp[91]=5","l");
  t4->AddEntry(h4[3],"Parp[91]=6","l");
  t4->AddEntry(h4[4],"Parp[91]=7","l");
  t4->AddEntry(h4[5],"Parp[91]=8","l");
  t4->AddEntry(h4[6],"Parp[91]=9","l");
  //t4->AddEntry(h4[7],"Parp[91]=");
  //t4->AddEntry(h4[8],"Parp[91]=");
  t4->Draw();
  
  c1->Print("~/public_html/talk/pwgCompare.png");
 
}











