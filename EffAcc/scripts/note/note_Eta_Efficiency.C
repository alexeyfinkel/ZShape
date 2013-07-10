#include "tdrstyle.C"

void note_Eta_Efficiency(TFile* ef,int flag){
  gROOT->SetStyle("Plain");setTDRStyle();
  TGraphAsymmErrors* effSum,* effSum2;
  effSum2=new TGraphAsymmErrors(84);
  char stub[20],stub2[20],title[120],filename[120]; 
  if(flag==0){
    TH1F* he  = (TH1F*)ef->Get("myanalyzer/cutNoCuts/absHFEta");
    TH1F* hp  = (TH1F*)ef->Get("myanalyzer/cutNoCuts/absGenEta");
    // effSum = new TH1F ("ETA_Effeciency", "Efficiency vs Eta", 84,2.9,5); 
    effSum=new TGraphAsymmErrors(84); 
  }else if (flag==6){
     TH1F* he  = (TH1F*)ef->Get("myanalyzer/cutNoCuts/absHFEta_range30");
    TH1F* hp  = (TH1F*)ef->Get("myanalyzer/cutNoCuts/absGenEta_range30");
    // effSum = new TH1F ("ETA_Effeciency", "Efficiency vs Eta, Et > 15 GeV", 84,2.9,5);
     effSum=new TGraphAsymmErrors(84); 
  }else{
    TH1F* he  = (TH1F*)ef->Get("myanalyzer/cutNoCuts/absHFEta_range20");
    TH1F* hp  = (TH1F*)ef->Get("myanalyzer/cutNoCuts/absGenEta_range20");
    // effSum = new TH1F ("ETA_Effeciency", "Efficiency vs Eta, Et > 20 GeV", 84,2.9,5);
 effSum=new TGraphAsymmErrors(84); 
  }
 
  
 
  
 //  int i;
//   int j;
//   double eff=0;  
     
//   for (i=1;i<=80;i++){
//     //std::cout<<i<<std::endl;
//     if (hp->GetBinContent(i)==0){
//       eff=0;
//     }else{
//       eff=(he->GetBinContent(i)*1.0/(hp->GetBinContent(i)));
//     }
//     effSum->SetBinContent(i,eff);
//   }

  effSum->BayesDivide(he,hp);
  // effSum2=effSum->Clone("fsum");
  effSum2->BayesDivide(he,hp);
  //effSum->SetMinimum(1e-3);
  //effSum->SetTitle(0);
  effSum->GetXaxis()->SetTitle("#eta");
 
  if (flag==0){
    effSum->GetYaxis()->SetTitle("#epsilon(#eta) per 0.025 in #eta");
  }else if (flag==6){
    effSum->GetYaxis()->SetTitle("#epsilon(#eta),E_{T} 30 GeV per 0.025 in #eta");
  }else{
    effSum->GetYaxis()->SetTitle("#epsilon(#eta),E_{T} 20 GeV per 0.025 in #eta");
  }
  effSum->SetLineWidth(3);
  //  effSum->SetStats(0);
  effSum->SetTitle(0);
  //effSum->SetTitle(title);
  //effSum->GetXaxis()->CenterTitle();
  
  //effSum->Rebin(3);
  //effSum->Scale(1.0/3);
  effSum->SetMinimum(.9);
  effSum->SetMaximum(1.02);


  TCanvas* c1=new TCanvas("c1","c1",900,600);
  //effSum->Draw("E"); 
  effSum->Draw("AP"); 
  zrap_Prelim(.75,.9); c1->SetGridy();
  
  // effSum2->GetYaxis()->SetTitle(0);
//   effSum2->GetXaxis()->SetTitle(0);
//   effSum2->SetTitle(0);

  TPad *npad= new TPad("npad","",.28,.15,.75,.7);
  npad->Draw();
  npad->cd();
  npad->SetGridy();
  effSum2->Draw("AP");

  if (flag==0){

    c1->Print("/home/grad/klapoetke/public_html/note/note_Eta_Efficiency.eps");
  }else if (flag==6){

     c1->Print("/home/grad/klapoetke/public_html/note/note_Eta_Efficiency_range30.eps");
  }else{

    c1->Print("/home/grad/klapoetke/public_html/note/note_Eta_Efficiency_range20.eps");
  }
  
 
  // c1->Print("note_Eta_Efficiency.eps");
}
