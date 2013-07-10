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

void app_bob15(TFile* f1,TFile* f2,TFile* f3,TFile* f4,TFile* f5,TFile* f6,TFile* f7,TFile* f8,TFile* f9,TFile* f10,TFile* f11,TFile* f12){

  //gROOT->SetStyle("Plain");  //makes plot white not grey
  setTDRStyle();           //make





  TCanvas* c1=new TCanvas("Compare","Compare",800,600);
  TCanvas* c2=new TCanvas("Chi2","Chi2",800,600);
  c1->cd();
  TH1F* h[20];
  h[0]=(TH1F*)zpt_rebinForPlot((TH1*)f1->Get("mcEff/ECAL80-ECAL95-MUO/C01-PT10/Z0_Pt_masscut")->Clone("cl1"));
  h[1]=(TH1F*)zpt_rebinForPlot((TH1*)f2->Get("mcEff/ECAL80-ECAL95-MUO/C01-PT10/Z0_Pt_masscut")->Clone("cl2"));
  h[2]=(TH1F*)zpt_rebinForPlot((TH1*)f3->Get("mcEff/ECAL80-ECAL95-MUO/C01-PT10/Z0_Pt_masscut")->Clone("cl3"));
  h[3]=(TH1F*)zpt_rebinForPlot((TH1*)f4->Get("mcEff/ECAL80-ECAL95-MUO/C01-PT10/Z0_Pt_masscut")->Clone("cl4"));
  h[4]=(TH1F*)zpt_rebinForPlot((TH1*)f5->Get("mcEff/ECAL80-ECAL95-MUO/C01-PT10/Z0_Pt_masscut")->Clone("cl5"));
  h[5]=(TH1F*)zpt_rebinForPlot((TH1*)f6->Get("mcEff/ECAL80-ECAL95-MUO/C01-PT10/Z0_Pt_masscut")->Clone("cl6"));
  h[6]=(TH1F*)zpt_rebinForPlot((TH1*)f7->Get("mcEff/ECAL80-ECAL95-MUO/C01-PT10/Z0_Pt_masscut")->Clone("cl7"));
  h[7]=(TH1F*)zpt_rebinForPlot((TH1*)f8->Get("mcEff/ECAL80-ECAL95-MUO/C01-PT10/Z0_Pt_masscut")->Clone("cl8"));
  h[8]=(TH1F*)zpt_rebinForPlot((TH1*)f9->Get("mcEff/ECAL80-ECAL95-MUO/C01-PT10/Z0_Pt_masscut")->Clone("cl9"));
 h[9]=(TH1F*)zpt_rebinForPlot((TH1*)f10->Get("mcEff/ECAL80-ECAL95-MUO/C01-PT10/Z0_Pt_masscut")->Clone("cl10"));
  h[10]=(TH1F*)zpt_rebinForPlot((TH1*)f11->Get("mcEff/ECAL80-ECAL95-MUO/C01-PT10/Z0_Pt_masscut")->Clone("cl19"));
  h[11]=(TH1F*)zpt_rebinForPlot((TH1*)f12->Get("mcEff/ECAL80-ECAL95-MUO/C01-PT10/Z0_Pt_masscut")->Clone("cl110"));
  int hn=12;
  h[0]->SetLineColor(kRed);
  h[1]->SetLineColor(kYellow+3);
  h[2]->SetLineColor(kBlue);
  h[3]->SetLineColor(kGreen);
  h[4]->SetLineColor(kViolet);
  h[5]->SetLineColor(kCyan);
  h[6]->SetLineColor(kOrange);
  h[7]->SetLineColor(kYellow);
  h[8]->SetLineColor(kBlue+2);
  h[9]->SetLineColor(kPink+3);
  h[10]->SetLineColor(kGreen+2);
  h[11]->SetLineColor(kCyan+3);
  
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
    // h[k]->Scale((ob->Integral()*1.0)/(h[k]->Integral()*1.0));
    h[k]->SetLineWidth(2);
    
    
    h[k]->Draw("SAME HIST");
    
  }
  
  
  TLegend* tl=new TLegend(0.5,0.7,0.72,0.9,"");
  tl->SetFillStyle(0);
  tl->AddEntry(ob,"Combined Data","P");
  tl->AddEntry(h[0],"Z2 Tune","l");
  tl->AddEntry(h[1],"Parp[91]=0.25","l");
  tl->AddEntry(h[2],"Parp[91]=0.5","l");
  tl->AddEntry(h[3],"Parp[91]=1.0","l");
  tl->AddEntry(h[4],"Parp[91]=1.5","l");
  tl->AddEntry(h[5],"Parp[91]=2.25","l");
  tl->AddEntry(h[6],"Parp[91]=2.5","l");
  tl->AddEntry(h[7],"Parp[91]=2.75","l");
  tl->AddEntry(h[8],"Parp[91]=3.0","l");
  tl->AddEntry(h[9],"Parp[91]=3.25","l");
  tl->AddEntry(h[10],"Parp[91]=3.5","l");
  tl->AddEntry(h[11],"Parp[91]=4.0","l");
  tl->Draw();
  
  c1->Print("~/public_html/talk/appendiz_bob15_july25.eps");
  
  c2->cd();
  
  double x[20]={ 0,0.25,0.5,0.75,1.0,1.5,2.0,2.5,3.0,3.25,3.5,4.0};
  double chi2[20];  
  for(int j=1;j<hn;j++){ 
    chi2[j]=0 ;
    // h[j]->Scale((ob->GetEntries()*1.0)/(h[j]->GetEntries()*1.0));
    //std::cout<<"I'm Number  "<<x[j-1]<<std::endl;     
    for (int i=1;i<=9;i++){
      
      double s2obs= (ob->GetBinContent(i));   
      double s2exp = (h[j]->GetBinContent(i));
      double s2or = ob->GetBinError(i);
      if (s2obs==0){
	chi2[j]+=0;
      }else{
	chi2[j]+=((s2obs-s2exp)*(s2obs-s2exp)*1.0)/(((s2or))*((s2or))*1.0);
	
	//	std::cout<<"I'm Number chi2: "<<chi2[j]<<std::endl;	  
      }//end else
      
    }//end i
    std::cout<<"I'm Number chi2: "<<x[j]<<"  "<<chi2[j]<<std::endl;
    
  }//end j
  
  TH1* gr=new TH1F("name","name",25,-0.125,6.125);
  for(int j=0;j<hn;j++){
    gr->SetBinContent(gr->FindBin(x[j]),chi2[j]);
  }

  gr->GetYaxis()->SetTitle("#chi^{2}*DoF");
  gr->GetXaxis()->SetTitle("PARP 91 Value");


  gr->Draw("P");
zrap_Prelim(.8,.82);
  zrap_Lumi(0.80,0.780,36);
  c2->Print("~/public_html/talk/appendiz_bob15Chi2_july25.eps");
  
}
