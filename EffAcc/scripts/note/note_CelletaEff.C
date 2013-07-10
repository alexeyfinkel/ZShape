

void note_CelletaEff(TFile* ef,int flag){
  gROOT->SetStyle("Plain");
  char stub[20],stub2[20],title[120],filename[120]; 
  if(flag==0){
    TH1F* he  = (TH1F*)ef->Get("myanalyzer/cutNoCuts/NoCutsHFcelleta");
    TH1F* hp  = (TH1F*)ef->Get("myanalyzer/cutNoCuts/NoCutsGencelleta");
    effSum = new TH1F ("CETA_Effeciency", "Efficiency vs Cell Eta", 40,-0.01,1.01);
  }else if (flag==1){
     TH1F* he  = (TH1F*)ef->Get("myanalyzer/cutNoCuts/NoCutsHFcelleta_range");
    TH1F* hp  = (TH1F*)ef->Get("myanalyzer/cutNoCuts/NoCutsGencelleta_range");
    effSum = new TH1F ("CETA_Effeciency", "Efficiency vs Cell Eta, Et > 30 GeV", 40,-0.01,1.01);
    
  }else{
    TH1F* he  = (TH1F*)ef->Get("myanalyzer/cutNoCuts/NoCutsHFcelleta_range20");
    TH1F* hp  = (TH1F*)ef->Get("myanalyzer/cutNoCuts/NoCutsGencelleta_range20");
    effSum = new TH1F ("CETA_Effeciency", "Efficiency vs Cell Eta, Et > 20 GeV", 40,-0.01,1.01);
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
  
  effSum->GetXaxis()->SetTitle("Cell Eta");
  effSum->SetLineWidth(3);
  effSum->SetStats(0);
  //effSum->SetTitle(title);
  effSum->GetXaxis()->CenterTitle();
  
  //effSum->Rebin(3);
  //effSum->Scale(1.0/3);
 
  TCanvas* c1=new TCanvas("c1","c1",900,600);
  effSum->Draw("Hist"); 

  
 
  c1->SetGridy();
  // c1->Print("note_Eta_Efficiency.eps");
}
