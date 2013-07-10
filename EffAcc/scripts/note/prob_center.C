

void prob_center(TFile* ef){
  gROOT->SetStyle("Plain");
  

  TH2F* he  = (TH2F*)ef->Get("myanalyzer/cutNoCuts/NoCutsGenEtaVsGenEnergy");
  TH2F* hp  = (TH2F*)ef->Get("myanalyzer/cutNoCuts/NoCutsGenEtaVsGenEnergy_center");
  
  char stub[20],stub2[20],title[120],filename[120];
  
  effSum = new TH2F ("ProbCenter", "Probability of central cell eta reconstruction", 60,2.8,5,50,0,2000);
  
  int i;
  int j;
  double eff=0;  
     
  for (i=1;i<=60;i++){
    for (j=1;j<=50;j++){
      if (he->GetBinContent(i,j)==0){
	eff=0;
      }else{
	eff=(hp->GetBinContent(i,j)*1.0/(he->GetBinContent(i,j)));
      }
      effSum->SetBinContent(i,j,eff);
    }
  }
  
  effSum->SetMinimum(1e-3);
  effSum->SetTitle(0);
  effSum->GetXaxis()->SetTitle("E_{T}[GeV]");
  effSum->SetLineWidth(3);
  effSum->SetStats(111);
  effSum->GetYaxis()->SetTitle("Efficiency");
  //effSum->GetXaxis()->CenterTitle();
  
  //effSum->Rebin(3);
  //effSum->Scale(1.0/3);
 
  TCanvas* c1=new TCanvas("c1","c1",900,600);
  effSum->Draw("Hist"); 
  //effSum->Draw("E"); 

  
 
  c1->SetGridy();
  // c1->Print("note_Et_Efficiency.eps");
}
