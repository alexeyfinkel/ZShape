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


void pwgCompare(TFile* f1,TFile* f2,TFile* f3,TFile* f4,TFile* f5,TFile* f6,TFile* f7/*,TFile* f8,TFile* f9*/){

  //gROOT->SetStyle("Plain");  //makes plot white not grey
  setTDRStyle();           //make





 TCanvas* c1=new TCanvas("Compare","Compare",800,600);
 TCanvas* c2=new TCanvas("Chi2","Chi2",800,600);
 c1->cd();
  TH1F* h[20];
  h[0]=(TH1F*)zpt_rebinForPlot((TH1*)f1->Get("mcEff/ECAL80-ECAL95-MUO/C01-PT10/Z0_PtTL")->Clone("cl1"));
  h[1]=(TH1F*)zpt_rebinForPlot((TH1*)f2->Get("mcEff/ECAL80-ECAL95-MUO/C01-PT10/Z0_PtTL")->Clone("cl2"));
  h[2]=(TH1F*)zpt_rebinForPlot((TH1*)f3->Get("mcEff/ECAL80-ECAL95-MUO/C01-PT10/Z0_PtTL")->Clone("cl3"));
  h[3]=(TH1F*)zpt_rebinForPlot((TH1*)f4->Get("mcEff/ECAL80-ECAL95-MUO/C01-PT10/Z0_PtTL")->Clone("cl4"));
  h[4]=(TH1F*)zpt_rebinForPlot((TH1*)f5->Get("mcEff/ECAL80-ECAL95-MUO/C01-PT10/Z0_PtTL")->Clone("cl5"));
  h[5]=(TH1F*)zpt_rebinForPlot((TH1*)f6->Get("mcEff/ECAL80-ECAL95-MUO/C01-PT10/Z0_PtTL")->Clone("cl6"));
  h[6]=(TH1F*)zpt_rebinForPlot((TH1*)f7->Get("mcEff/ECAL80-ECAL95-MUO/C01-PT10/Z0_PtTL")->Clone("cl7"));
//h[7]=(TH1F*)zpt_rebinForPlot((TH1*)f8->Get("mcEff/ECAL80-ECAL95-MUO/C01-PT10/Z0_PtTL")->Clone("cl8"));
//h[8]=(TH1F*)zpt_rebinForPlot((TH1*)f9->Get("mcEff/ECAL80-ECAL95-MUO/C01-PT10/Z0_PtTL")->Clone("cl9"));
 int hn=7;
 h[0]->SetLineColor(kRed);
 h[1]->SetLineColor(kBlack);
 h[2]->SetLineColor(kBlue);
 h[3]->SetLineColor(kGreen);
 h[4]->SetLineColor(kViolet);
 h[5]->SetLineColor(kCyan);
 h[6]->SetLineColor(kOrange);
 //h[7]->SetLineColor(kYellow+3);
 //h[8]->SetLineColor();
 //h[]->SetLineColor();


 int    pt_bins=19;
 double pt_binning[]={ 0.7, 2.5, 5, 7.5, 10, 12.5, 15, 17.5, 20, 30, 40, 50, 70, 90, 110, 150, 190, 250, 600, 3500 };
  TH1* ob=new TH1F("name","name",pt_bins,pt_binning);
  double obd[40]={0.033737615 ,0.060849532 ,0.054848209 ,0.039108086 ,0.034748245 ,0.026549902 ,0.021082869 ,0.015919408 ,0.011421548 ,0.006058531 ,0.003427496 ,0.001804253 ,0.000785000 ,0.000483902 ,0.000195649 ,0.000063486 ,0.000014073 ,0.000001828 ,0.0};//data form file
  double obr[40]={0.001512026 ,0.002131419 ,0.002148360 ,0.001987187 ,0.001646839 ,0.001341312 ,0.001314977 ,0.001143478 ,0.000296154 ,0.000209322 ,0.000155537 ,0.000074367 ,0.000051002 ,0.000039993 ,0.000016336 ,0.000009896 ,0.000004056 ,0.000000533 ,0.0};//err from file
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
  for(int k=0;k<hn;k++){
    for(int p=0;p<pt_bins;p++){

      h[k]->SetBinContent(p+1,h[k]->GetBinContent(p+1)*1.0/(h[k]->GetBinWidth(p+1)*h[k]->Integral()*1.0));
    }//end p
    h[k]->Scale((ob->Integral(1,10)*1.0)/(h[k]->Integral()*1.0));
    h[k]->SetLineWidth(2);
    
    
    h[k]->Draw("SAME HIST");
  
  }

 
  TLegend* tl=new TLegend(0.5,0.7,0.72,0.9,"");
  tl->SetFillStyle(0);
  tl->AddEntry(ob,"Combined Data","P");
  tl->AddEntry(h[0],"Parp[91]=3","l");
  tl->AddEntry(h[1],"Parp[91]=4","l");
  tl->AddEntry(h[2],"Parp[91]=5","l");
  tl->AddEntry(h[3],"Parp[91]=6","l");
  tl->AddEntry(h[4],"Parp[91]=7","l");
  tl->AddEntry(h[5],"Parp[91]=8","l");
  tl->AddEntry(h[6],"Parp[91]=9","l");
  //tl->AddEntry(h[7],"Parp[91]=");
  //tl->AddEntry(h[8],"Parp[91]=");
  tl->Draw();
  
  c1->Print("~/public_html/talk/pwgCompare.png");
  
  
  
  c2->cd();
  std::cout<<"I'm Number Legend"<<std::endl;
  
  double chi2[20];  
  for(int j=0;j<hn;j++){
    chi2[j]=0 ;
    // h[j]->Scale((ob->GetEntries()*1.0)/(h[j]->GetEntries()*1.0));
      std::cout<<"I'm Number J "<< j<<std::endl;
      for (int i=1;i<pt_bins+1;i++){
	std::cout<<"I'm Number I "<< i<<std::endl;
	double s2obs= (ob->GetBinContent(i));   
	double s2exp = (h[j]->GetBinContent(i));
	if (s2obs==0){
	  chi2[j]+=0;
	}else{
	  chi2[j]+=((s2obs-s2exp)*(s2obs-s2exp)*1.0)/((sqrt(s2obs))*(sqrt(s2obs))*1.0);
	  
	  
	}//end else
      }//end i
      
  }//end j
  
  std::cout<<"I'm Number chi2"<< chi2<<std::endl;
  double x[20]={3,4,5,6,7,8,9};
  
  TGraph* gr = new TGraph(hn,x,chi2);
  gr->Draw("PE");
  c2->Print("~/public_html/talk/chi2_parp91.png");
  
}
