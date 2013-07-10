
#include "tdrstyle.C"
void note_Et_Efficiency(TFile* ef,int flag){
  gROOT->SetStyle("Plain");
  setTDRStyle();
  TGraphAsymmErrors* effSum;

  TH1F* he  = (TH1F*)ef->Get("myanalyzer/cutNoCuts/HFEt_fid");
  TH1F* hp  = (TH1F*)ef->Get("myanalyzer/cutNoCuts/GenEt_fid");
  
  char stub[20],stub2[20],title[120],filename[120];
  
  // effSum = new TH1F ("ET_Effeciency", "Efficiency vs Et", 80,0,150.0);
   effSum=new TGraphAsymmErrors(84); 
  int i;
  int j;
  double eff=0;  
  effSum->BayesDivide(he,hp);   
//   for (i=1;i<=80;i++){
//     if (hp->GetBinContent(i)==0){
//       eff=0;
//     }else{
//       eff=(he->GetBinContent(i)*1.0/(hp->GetBinContent(i)));
//     }
//     effSum->SetBinContent(i,eff);
//   }
  
  // effSum->SetMinimum(1e-3);
  //  effSum->SetTitle(0);
  effSum->GetXaxis()->SetTitle("E_{T}[GeV]");
  // effSum->SetLineWidth(3);
  //  effSum->SetStats(0);
  effSum->GetYaxis()->SetTitle("#epsilon(E_{T}) per 1.875 GeV");
  //effSum->GetXaxis()->CenterTitle();
  
  //effSum->Rebin(3);
  //effSum->Scale(1.0/3);
 
  TCanvas* c1=new TCanvas("c1","c1",900,600);
  effSum->Draw("AP"); 
  //effSum->Draw("E"); 
  TF1 *f1 = new TF1("f1","(1+exp(-[0]-[1]*x))^-1",0.5,1);
   effSum->Fit("f1");


   zrap_Prelim(.75,.9); c1->SetGridy();
   //c1->Print("/home/grad/klapoetke/public_html/note/note_Et_Efficiency.eps");
 
  c1->SetGridy();
  // c1->Print("note_Et_Efficiency.eps");
}
