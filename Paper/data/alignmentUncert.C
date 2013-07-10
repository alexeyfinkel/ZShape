#include "../root/tdrstyle.C"
#include "../root/zrapidityStandard.C"

void alignmentUncert(){
  
  setTDRStyle();
  TCanvas* c2=new TCanvas("c2","c2",800,800);
  c2->SetLeftMargin(0.18);
  int    pt_bins=19;
  double pt_binning[]={ 0.7, 2.5, 5, 7.5, 10, 12.5, 15, 17.5, 20, 30, 40, 50, 70, 90, 110, 150, 190, 250, 600, 3500 };
  double eff[25]={0.044, 0.002, 0.007, 0.018, 0.013,  0.016, 0.021, 0.020, 0.002, 0.022, 0.010,  0.009, 0.040, 0.018, 0.020, 0.053, 0.040, 0.001};
  TH1F* h1 =new TH1F("h1j","h1j",pt_bins,pt_binning);
  h1->GetYaxis()->SetTitle("Alignment Uncertainty");
   h1->GetYaxis()->SetTitleOffset(1.5);
 h1->GetXaxis()->SetTitleOffset(1.03);
  h1->GetXaxis()->SetTitle("P_{T} [GeV]");
  
  for(int i=0;i<pt_bins;i++){
    h1->SetBinContent(i+1,eff[i]);
  }
  c2->SetLogy(); c2->SetLogx();
  h1->Draw("HIST");
  
  zrap_Prelim(0.80,0.977);
  zrap_Lumi(0.80,0.90,36);
  c2->Print("~/public_html/talk/bkgcompare/zpt_ee_alignment_uncertainty.eps");
}
