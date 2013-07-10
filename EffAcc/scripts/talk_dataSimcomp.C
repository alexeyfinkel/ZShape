#include "TF1.h"
#include "TFile.h"
#include "TCanvas.h"
#include "TGraphErrors.h"
#include "TGraph.h"
#include "TH1.h"
#include "TH2.h"
#include <math.h>
#include <algorithm>
#include <list>
#include <iostream>
#include "TROOT.h"
#include "tdrstyle.C"
#include "zrapidityStandard.C"

void talk_dataSimcomp(TFile* td,TFile* ts){
   gROOT->SetStyle("Plain");
  gStyle->SetOptStat(0000);
  gStyle->SetOptFit(0000);
    setTDRStyle();
  char Detector_Pair[10][128];
  sprintf(Detector_Pair[0],"EB-EB");
  sprintf(Detector_Pair[1],"EE-EB");
  sprintf(Detector_Pair[2],"EE-HF");
  sprintf(Detector_Pair[3],"EE-EE");
  sprintf(Detector_Pair[4],"EB-HF");

  char Variable_MC[20][128];
  sprintf(Variable_MC[0],"wZ0_at");
  sprintf(Variable_MC[1],"wZ0_phiStar");
  sprintf(Variable_MC[2],"wZ0_pt");
  sprintf(Variable_MC[3],"Z0_Y");
  sprintf(Variable_MC[4],"e1_eta");
  sprintf(Variable_MC[5],"e2_eta");
  sprintf(Variable_MC[6],"e_eta");
  sprintf(Variable_MC[7],"e1_phi");
  sprintf(Variable_MC[8],"e2_phi");
  sprintf(Variable_MC[9],"e_phi");
  sprintf(Variable_MC[10],"e1_P_t");
  sprintf(Variable_MC[11],"e2_P_t");
  sprintf(Variable_MC[12],"Z0_mass_zoom");
  // sprintf(Variable_MC[],"");
  
  /*
    Z0_Y,e1_eta,e2_eta,e_eta,e1_phi,e2_phi,e_phi,e1_P_t,e2_P_t
    
    
  */
  
  double range[20];
  range[0]=60;
  range[1]=0.5;
  range[2]=80;
  range[3]=5;
  range[4]=5;
  range[5]=5;
  range[6]=5;
  range[7]=3.14;
  range[8]=3.14;
  range[9]=3.14;
  range[10]=120;
  range[11]=120;
  range[12]=120;
  double lrange[20];
  lrange[0]=0;
  lrange[1]=0;
  lrange[2]=0;
  lrange[3]=-5;
  lrange[4]=-5;
  lrange[5]=-5;
  lrange[6]=-5;
  lrange[7]=-3.14;
  lrange[8]=-3.14;
  lrange[9]=-3.14;
  lrange[10]=0;
  lrange[11]=0;
  lrange[12]=60;
  char name[128];
  
  for(int zdef = 0; zdef < 3; zdef++){//0,5
    for(int vm = 1; vm < 2; vm++){//0,13
      if(vm >3 && vm <12)continue;
      sprintf(name, "Compare %s %s", Detector_Pair[zdef], Variable_MC[vm]);
      TCanvas *comp = new TCanvas(name, name, 500, 500);
      


      //sim plot h1
      sprintf(name, "/mcEff/%s/C08-m(60,120)/%s", Detector_Pair[zdef], Variable_MC[vm]);      
      printf("hey 1 %s\n",name);
      TH1F* h1 = (TH1F*)ts->Get(name);
      printf("h1 (smear) max=%i\n",h1->GetMaximum());
      sprintf(name, "clone_%s_%s", Detector_Pair[zdef], Variable_MC[vm]);
      h1 = (TH1F*)(h1->Clone(name));


      //sim background bg0
      sprintf(name, "MastBackground_%s_%s", Detector_Pair[zdef], Variable_MC[vm]);
      //if(zdef==2 || zdef==4)
      h1=(TH1F*)z_rebinForComp(h1,vm,zdef);
      TH1F* bg0=(TH1F*)(h1->Clone(name));
      bg0->Reset();
     
      //integral plots il
      if(zdef == 2){
	sprintf(name, "/mcEff/%s/C08-m(60,120)/Z0_mass_zoom", Detector_Pair[zdef]);
      }else{
	sprintf(name, "/mcEff/%s/C08-m(60,120)/Z0_mass_zoom", Detector_Pair[zdef]);
      }
      TH1F* io1 = (TH1F*)ts->Get(name);
      sprintf(name, "clone_i1_%s_%s", Detector_Pair[zdef], Variable_MC[vm]);
      TH1F* i1 = (TH1F*)(io1->Clone(name));

      sprintf(name, "%s %s", Detector_Pair[zdef], Variable_MC[vm]);
      // h1->SetTitle(name);
      h1->SetTitle(0);

      double max=-1.0;
      

      //data plot h2
      if((zdef == 2) || (zdef == 3) || (zdef == 4) )
	sprintf(name, "/ZFromData/%s/C06-m(60,120)/%s", Detector_Pair[zdef], Variable_MC[vm]);
      else
	sprintf(name, "/ZFromData/%s/C07-m(60,120)/%s", Detector_Pair[zdef], Variable_MC[vm]);
      printf("hey 2 %s\n",name);
      TH1F* h2 = (TH1F*)td->Get(name);
      printf("h2 (smear) max=%i\n",h2->GetMaximum());
      sprintf(name, "clone2_%s_%s", Detector_Pair[zdef], Variable_MC[vm]);
      h2 = (TH1F*)(h2->Clone(name));
      // if(zdef==2 || zdef==5)
      h2=(TH1F*)z_rebinForComp(h2,vm,zdef);
      
      //data background bg2
      sprintf(name, "bckgByBin_%s_%s", Detector_Pair[zdef], Variable_MC[vm]); 
      bg2 = (TH1F*)(h2->Clone(name));
      ///////////           
      if(vm!=12 ){
	

	// background by bin DATA bg2d
	if((zdef == 2) || (zdef == 3) || (zdef == 5) )
	  sprintf(name, "/ZFromData/%s/C06-m(60,120)/mZ_vs_%s", Detector_Pair[zdef], Variable_MC[vm]);
	else
	  sprintf(name, "/ZFromData/%s/C07-m(60,120)/mZ_vs_%s", Detector_Pair[zdef], Variable_MC[vm]);
	printf("hey 3 %s\n",name);
	//	TCanvas* m1=new TCanvas("m1","m1",600,600);
	//	m1->cd();
	TH2F* bg2d = (TH2F*)td->Get(name);
	sprintf(name, "2dmass_%s_%s", Detector_Pair[zdef], Variable_MC[vm]); 
	bg2d=(TH2F*)(bg2d->Clone(name));
	bg2d=(TH2F*)z_rebinForComp2D(bg2d,vm,zdef);

	for(int b=1;b<bg2d->GetNbinsX();b++){

	  //get background shape per bins  p2
	  sprintf(name, "proj_%s_%s_%i", Detector_Pair[zdef], Variable_MC[vm],b); 
	  // printf("Yuck 3 b=%i nx= %i name=%s\n",b,h2->GetNbinsX(),name);
	  bg2d->ProjectionY(name,b,b,"");
	  
	  TH1F* p2=(TH1F*)ts->Get(name);
	  sprintf(name, "C1_proj_%s_%s_%i", Detector_Pair[zdef], Variable_MC[vm],b);
	  TCanvas* cbkgi=new TCanvas(name,name,600,600);
	  cbkgi->cd();
	  double bmax=p2->GetMaximum();
	  // signal and bkground fit f1
	  TF1 *f1 = new TF1 ("pf1","([0]*exp(-0.5*((x-[1])/[2])**2))+(exp([3]+[4]*x))",60,120);
	    f1->SetParLimits(0,10,1000000);
	  f1->SetParLimits(1,86,96);
	  f1->SetParLimits(2,1,10);
	   f1->SetParLimits(3,-10,10);
	   f1->SetParLimits(4,-1,1);
	   // f1->SetParLimits(5,-1,0.001);
	  p2->Draw();
	  p2->Fit("pf1","RNQWLMI");
	  f1->Draw("same");
	  //  double scl=f1->GetParameter(3);
	  double amp=f1->GetParameter(3);  
	  double thing=f1->GetParameter(4);
	 

	  //just background f2
	  TF1 *f2 = new TF1 ("pf2","expo(0)",60,120);
	  // f2->SetParameter(0,scl);
	  f2->SetParameter(0,amp);
	  f2->SetParameter(1,thing);
	  f2->Draw("same");
	  double width=bg2->GetBinWidth(b);
	  double bval=((f2->Integral(60,120))*1.0);
	  bg2->SetBinContent(b,bval); 
	  // if(b>20)
	    cbkgi->Close();
	  //  else 
	  //  printf("moo   amp %0.2f thing  %0.2f integral %0.2f \n",amp,thing,bval);
	}  
	bg0=bg2;
      }///end if vm!=12
    
      /////////
      printf("hey out of bin",name);
     
      //data integral i2, with mass subtracted eventually
      if((zdef == 2) || (zdef == 3) || (zdef == 5) ){
	sprintf(name, "/ZFromData/%s/C06-m(60,120)/Z0_mass_zoom", Detector_Pair[zdef]);
      }else{
	sprintf(name, "/ZFromData/%s/C07-m(60,120)/Z0_mass_zoom", Detector_Pair[zdef]);
      }
      std::cout<<"integral of sim "<<h1->Integral()<<" integral of h2 "<<h2->Integral()<<std::endl;
      printf("hey 4 %s\n",name);
      TH1F* io2 = (TH1F*)td->Get(name);
      sprintf(name, "clone_i2_%s_%s", Detector_Pair[zdef], Variable_MC[vm]);
      TH1F* i2 = (TH1F*)io2->Clone(name);
      
      //   if(zdef==2 || zdef==5){	// background for scaling
      
      sprintf(name, "bckg_%s_%s", Detector_Pair[zdef], Variable_MC[vm]);
      TH1F* bgi = (TH1F*)(i2->Clone(name));
      bgi->Reset();
      sprintf(name, "C1_bckg_%s_%s", Detector_Pair[zdef], Variable_MC[vm]);
      TCanvas* cbkgi=new TCanvas(name,"The BKGi",600,600);
      cbkgi->cd();
      TF1 *f1 = new TF1 ("f1","([0]*exp(-0.5*((x-[1])/[2])**2))+(exp([3]+[4]*x))",60,120);
      f1->SetParLimits(0,0,200);
      f1->SetParLimits(1,80,100);
      f1->SetParLimits(2,0.5,10);
      f1->SetParLimits(3,-10,10);
      f1->SetParLimits(4,-1,0.001);
      
      
      io2->Fit("f1","RN");
      double amp=f1->GetParameter(3);  
      double thing=f1->GetParameter(4);
      
      TF1 *f2 = new TF1 ("f2","expo(0)",60,120);
      f2->SetParameter(0,amp);
      f2->SetParameter(1,thing);
      for (int j=1;j<bgi->GetNbinsX();j++){
	double bval=f2->Eval(bgi->GetBinCenter(j));
	bgi->SetBinContent(j,bval);
	
      }
      
      cbkgi->Close();
      
      
      i2->Add(bgi,-1);
      if(vm==12) bg0=bgi;
      //}////////@@@@@@@@@@   end bkg i
      
      comp->cd();
          
      double scale=i2->Integral(41,80)*1.0/(double)i1->Integral(41,80);
      h1->Scale(scale);
      if (vm==12){h1->Rebin(3);h2->Rebin(3);bg0->Rebin(3); }
      printf("made it here %s %s\n",Detector_Pair[zdef], Variable_MC[vm]);
     
      //pretty stuff for h2 and h1
      h2->SetTitle(0);
      h2->SetMarkerSize(1);
      h2->SetMarkerStyle(4);
      h2->GetXaxis()->SetRangeUser(lrange[vm],range[vm]);
      h1->SetLineWidth(2);
      h1->SetLineColor(kRed);
      //      if(zdef==2 || zdef==5)
      h1->Add(bg0);
      if(h1->GetMaximum()>max)max=h1->GetMaximum();
      if(h2->GetMaximum()>max)max=h2->GetMaximum();
      h2->SetMaximum(max*1.3);
      h2->Draw("PE");
      h1->Draw("Same Hist");
      bg0->Draw("Same Hist");
      // h2->Draw("Same P");
     
      //legend box
      TLegend* tl=new TLegend(0.20,0.78,0.4,0.88,"");//not good location now
      tl->SetFillColor(10);
      tl->AddEntry(h1,"Sim");
      tl->AddEntry(h2,"Data");
      //if(zdef==2 || zdef==5) 
      tl->AddEntry(bg0,"Background");
      tl->Draw("SAME");
      zrap_Prelim(0.70,0.977);
      zrap_Lumi(0.70,0.90,200);
      sprintf(name,"~/public_html/Jeremy/proofs/%s/test2_CompareSmear_%s.png", Detector_Pair[zdef], Variable_MC[vm]);
      std::cout<<std::endl;
      comp->Print(name);
      // comp->Close();
    }//end V_M varible majik name
  }//end zdef particles
}//file
