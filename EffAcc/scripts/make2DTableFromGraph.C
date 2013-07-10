make2DTableFromGraph(TFile* f0, const char* hname, const char* txtName){


  TH2F* h1 =(TH2F*) f0->Get(hname)->Clone("cl1");
  
  char shout[128];
  // sprintf(shout, "originalHistograms_%s_%s",varName[var], Detector_Pair[zdef]); 
  for(int i=1;i<h1->GetNbinsX()+1;i++){
    for(int j=1;j<h1->GetNbinsY()+1;j++){
      double lvx=h1->GetXaxis()->GetBinLowEdge(i);
      double lhx=h1->GetXaxis()->GetBinUpEdge(i);
      double lvy=h1->GetYaxis()->GetBinLowEdge(j);
      double lhy=h1->GetYaxis()->GetBinUpEdge(j);
      FILE* texTable=fopen(txtName,"wt");
      fprintf(texTable,"#Low x \t High x \t Low y \t High y \t value \t simple error \n"); 
      
      fprintf(texTable,"%5.2f \t %5.2f \t %5.2f \t %5.2f \t %i \t %d \n",lvx,hvx,lvy,hvy,h1->GetBinContent(i,j),h1->GetBinError(i,j));
    }
  }
}
