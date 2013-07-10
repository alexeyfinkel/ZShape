#include "tdrstyle.C"

void note_Phi_Efficiency(TFile* ef,int flag){
  gROOT->SetStyle("Plain");setTDRStyle();
  char stub[20],stub2[20],title[120],filename[120]; 
  if(flag==0){
    TH1F* he  = (TH1F*)ef->Get("myanalyzer/cutNoCuts/NoCutsHFPhi");
    TH1F* hp  = (TH1F*)ef->Get("myanalyzer/cutNoCuts/NoCutsGenPhi");
    effSum = new TH1F ("PHI_Effeciency", "Efficiency vs Phi", 216,-3.14159,3.14159);  
  }else if (flag==1){
     TH1F* he  = (TH1F*)ef->Get("myanalyzer/cutNoCuts/NoCutsHFPhi_range");
    TH1F* hp  = (TH1F*)ef->Get("myanalyzer/cutNoCuts/NoCutsGenPhi_range");
    effSum = new TH1F ("PHI_Effeciency", "Efficiency vs Phi, Et > 30 GeV", 216,-3.14159,3.14159);
    
  }else{
    TH1F* he  = (TH1F*)ef->Get("myanalyzer/cutNoCuts/NoCutsHFPhi_range20");
    TH1F* hp  = (TH1F*)ef->Get("myanalyzer/cutNoCuts/NoCutsGenPhi_range20");
    effSum = new TH1F ("PHI_Effeciency", "Efficiency vs Phi, Et > 20 GeV", 216,-3.14159,3.14159);
  }
 
  int i;
  int j;
  double eff=0;  
     
  for (i=1;i<=216;i++){
    if (hp->GetBinContent(i)==0){
      eff=0;
    }else{
      eff=(he->GetBinContent(i)*1.0/(hp->GetBinContent(i)));
    }
    effSum->SetBinContent(i,eff);
  }
  
  effSum->SetMinimum(0.6);
  
  effSum->GetXaxis()->SetTitle("#phi"); 
 
  if (flag==0){
    effSum->GetYaxis()->SetTitle("#epsilon(#phi)");
  }else if (flag==1){
    effSum->GetYaxis()->SetTitle("#epsilon(#phi),E_{T} 30 GeV");
  }else{
    effSum->GetYaxis()->SetTitle("#epsilon(#phi),E_{T} 20 GeV");
  }


  effSum->SetTitle(0);
  effSum->SetLineWidth(3);
  effSum->SetStats(0);
  //effSum->SetTitle(title);
  //effSum->GetXaxis()->CenterTitle();
  
  //effSum->Rebin(3);
  //effSum->Scale(1.0/3);
 
  TCanvas* c1=new TCanvas("c1","c1",900,600);
   //effSum->Draw("E"); 
  effSum->Draw("Hist"); 
  zrap_Prelim(.75,.4); c1->SetGridy();

  if (flag==0){
  
  c1->Print("/home/grad/klapoetke/public_html/note/note_Phi_Efficiency.eps");
  }else if (flag==1){
  
  c1->Print("/home/grad/klapoetke/public_html/note/note_Phi_Efficiency_range.eps");
  }else{
  
  c1->Print("/home/grad/klapoetke/public_html/note/note_Phi_Efficiency_range20.eps");
  }

  c1->Print("/home/grad/klapoetke/public_html/note/note_Phi_Efficiency_range.eps");
}
