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
//.x pwgCompare.C(_file0,_file1,_file2,_file3,_file4,_file5,_file6,_file7,_file8,_file9)
//.x pwgCompare.C(_file0,_file0,_file0,_file0,_file0,_file0)

void app_z2d6t(TFile* f1,TFile* f2){

  //gROOT->SetStyle("Plain");  //makes plot white not grey
  setTDRStyle();           //make

  TCanvas* c1=new TCanvas("Compare","Compare",800,600);
 
  c1->cd();
  TH1F* h[20];
  h[0]=(TH1F*)zpt_rebinForPlot((TH1*)f1->Get("mcEff/ECAL80-ECAL95-MUO/C01-PT10/Z0_Pt_masscut")->Clone("cl1"));
  h[1]=(TH1F*)zpt_rebinForPlot((TH1*)f2->Get("mcEff/ECAL80-ECAL95-MUO/C01-PT10/Z0_Pt_masscut")->Clone("cl2"));
 


  int hn=2;
  h[0]->SetLineColor(kRed);
  h[1]->SetLineColor(kGray);
 
  
 
  
  int    pt_bins=19;
  double pt_binning[]={ 0.7, 2.5, 5, 7.5, 10, 12.5, 15, 17.5, 20, 30, 40, 50, 70, 90, 110, 150, 190, 250, 600, 3500 };
  TH1* ob=new TH1F("name","name",pt_bins,pt_binning);
  double obd[40]={0.0252650,
		  0.0529320,
		  0.0519310,
		  0.0433030,
		  0.0361780,
		  0.0281900,
		  0.0218000,
		  0.0177650,
		  0.0125330,
		  0.0060380,
		  0.0035020,
		  0.0020820,
		  0.0009440,
		  0.0005570,
		  0.0002570,
		  0.0000580,
		  0.0000220,
		  0.0000010,
		  0.0000000};//data form file
  double obr[40]={0.0013143760,
		  0.0019037862,
		  0.0015389837,
		  0.0013646084,
		  0.0012681356,
		  0.0011279038,
		  0.0010322166,
		  0.0009314261,
		  0.0004266585,
		  0.0002932765,
		  0.0002263689,
		  0.0001313929,
		  0.0000872529,
		  0.0000660862,
		  0.0000309360,
		  0.0000159360,
		  0.0000084084,
		  0.0000009057,
		  0.0000000000};//err from file
  for (int z=0;z<pt_bins;z++){
    ob->SetBinContent(z+1,obd[z]);
    ob->SetBinError(z+1,obr[z]);
  }//end z
  
  
  

  ob->GetYaxis()->SetTitle("1/#sigma d#sigma/dP_{T}");
  ob->GetXaxis()->SetTitle("P_{T} [GeV]");
  //ob->GetYaxis()->SetTitleOffset(1.2);
  ob->SetTitle(0);  //no title
  ob->SetStats(false);   //no stats box
  ob->GetXaxis()->SetRangeUser(0,20);
  
  ob->Draw("PE");
  zrap_Prelim(.8,.82);
  zrap_Lumi(0.80,0.78,36);
  for(int k=0;k<hn;k++){
    double inter =   h[k]->Integral();
    for(int p=0;p<pt_bins;p++){
      
      h[k]->SetBinContent(p+1,h[k]->GetBinContent(p+1)*1.0/(h[k]->GetBinWidth(p+1)*inter*1.0));
    }//end p
    h[k]->Scale((ob->Integral(1,12)*1.0)/(h[k]->Integral(1,12)*1.0));
    h[k]->SetLineWidth(2);
    
    
    h[k]->Draw("SAME HIST");
    
  }
  
  
  TLegend* tl=new TLegend(0.5,0.7,0.72,0.9,"");
  tl->SetFillStyle(0);
  tl->AddEntry(ob,"Combined Data","P");
  tl->AddEntry(h[0],"Z2 Tune","l");
  tl->AddEntry(h[1],"D6T Tune","l");
  


  tl->Draw();
  
  c1->Print("~/public_html/talk/appendiz_z2d6t_july25.eps");
  
 
}
