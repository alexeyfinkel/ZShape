makeTableFromGraph(TFile* f0, const char* hname, const char* txtName){


  TH1F* h1 =(TH1F*) f0->Get(hname)->Clone("cl1");
  
  char shout[128];
  // sprintf(shout, "originalHistograms_%s_%s",varName[var], Detector_Pair[zdef]);
  for(int i=1;i<h1->GetNbinsX()+1;i++){
  double lv=h1->GetXaxis()->GetBinLowEdge(i);
    double lh=h1->GetXaxis()->GetBinUpEdge(i);
    FILE* texTable=fopen(txtName,"wt");
    fprintf(texTable,"#Low \t High \t value \t simple error \n"); 
    
    fprintf(texTable,"%5.2f \t %5.2f \t %i \t %d \n",lv,hv,h1->GetBinContent(i),h1->GetBinError(i));
    
  }
}
