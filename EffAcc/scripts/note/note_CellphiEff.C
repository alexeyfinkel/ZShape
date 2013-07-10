#include "tdrstyle.C"

void note_CellphiEff(TFile* ef,int flag){
  gROOT->SetStyle("Plain");setTDRStyle();
  char stub[20],stub2[20],title[120],filename[120]; 
  if(flag==0){
    TH1F* he  = (TH1F*)ef->Get("myanalyzer/cutNoCuts/NoCutsHFcellphi");
    TH1F* hp  = (TH1F*)ef->Get("myanalyzer/cutNoCuts/NoCutsGencellphi");
    effSum = new TH1F ("CPHI_Effeciency", "Efficiency vs Cell Phi", 40,-0.01,1.01);
  }else if (flag==1){
     TH1F* he  = (TH1F*)ef->Get("myanalyzer/cutNoCuts/NoCutsHFcellphi_range");
    TH1F* hp  = (TH1F*)ef->Get("myanalyzer/cutNoCuts/NoCutsGencellphi_range");
    effSum = new TH1F ("CPHI_Effeciency", "Efficiency vs Cell Phi, Et > 30 GeV", 40,-0.01,1.01);
    
  }else{
    TH1F* he  = (TH1F*)ef->Get("myanalyzer/cutNoCuts/NoCutsHFcellphi_range20");
    TH1F* hp  = (TH1F*)ef->Get("myanalyzer/cutNoCuts/NoCutsGencellphi_range20");
    effSum = new TH1F ("CPHI_Effeciency", "Efficiency vs Cell Phi, Et > 20 GeV", 40,-0.01,1.01);
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
  
  effSum->GetXaxis()->SetTitle("Cell Phi");
  effSum->SetLineWidth(3);
  effSum->SetStats(0);
  //effSum->SetTitle(title);
  effSum->GetXaxis()->CenterTitle();
  
  //effSum->Rebin(3);
  //effSum->Scale(1.0/3);
 
  TCanvas* c1=new TCanvas("c1","c1",900,600);
  effSum->Draw("Hist"); 

  
 
  c1->SetGridy();
  // c1->Print("note_Phi_Efficiency.eps");
}
