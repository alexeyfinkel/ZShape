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
#include "ZptatpsStandard.C"

void FullSimDataCompare(TFile* fmc, TFile* fd,int zmax=3,int vmax=9){
  gROOT->SetStyle("Plain");
  
  char name[128];
  char mess[128];
  char Zdefs[6][128];
  //TCanvas* c1[20];
  sprintf(Zdefs[0],"EB-EB");
  sprintf(Zdefs[1],"EE-EB");
  sprintf(Zdefs[2],"EE-HF"); 
  sprintf(Zdefs[3],"EE-EE");
  sprintf(Zdefs[4],"EB-HF");
  
  char Vars[20][128];
  sprintf(Vars[0],"Z0_mass");
  sprintf(Vars[1],"Z0_Y"); 
  sprintf(Vars[2],"Z0_PtMon");
  sprintf(Vars[3],"e1_eta");
  sprintf(Vars[4],"e2_eta");
  sprintf(Vars[5],"e1_phi"); 
  sprintf(Vars[6],"e2_phi");
  sprintf(Vars[7],"e1_P_t");
  sprintf(Vars[8],"e2_P_t");
  //   sprintf(Vars[9],""); 
  //   sprintf(Vars[10],"");
  //   sprintf(Vars[11],"");
  //   sprintf(Vars[12],"");
  //   sprintf(Vars[13],""); 
  //   sprintf(Vars[14],"");
  //   sprintf(Vars[15],"");
  //   sprintf(Vars[16],"");
  //   sprintf(Vars[17],""); 
  //   sprintf(Vars[18],"");
  //   sprintf(Vars[19],"");
  
  for(int v=0;v<vmax;v++){
    sprintf(name,"cv%i_%i",v,v);
    TCanvas* c1=new TCanvas(name,name,900,900);
    c1->Divide(3,2);
    for(int z=0;z<zmax;z++){
      if(z==2 || z==4){
	sprintf(name,"/ZFromData/%s/C06-m(60,120)/%s",Zdefs[z],Vars[v]);
      }else{
	sprintf(name,"/ZFromData/%s/C07-m(60,120)/%s",Zdefs[z],Vars[v]);
      }
      sprintf(mess,"%s_%s",Zdefs[z],Vars[v]);
      //std::cout<<name<<std::endl;
      TH1F* hm=(TH1F*)fmc->Get(name)->Clone(mess);
      sprintf(mess,"%s_%s_0",Zdefs[z],Vars[v]);
      TH1F* hd=(TH1F*)fd->Get(name)->Clone(mess);
      hm->Scale(1.0/hm->GetEntries());
      hd->Scale(1.0/hd->GetEntries());
      hm->SetLineColor(kRed);
      hm->SetLineWidth(2);
      hd->SetMarkerStyle(21);//black box
      hd->SetMarkerSize(1);
      c1->cd(z+1);
      // c1->cd();
      hm->Draw("Hist");
      hd->Draw("same P");
    }//end z   
    sprintf(name,"~/public_html/Jeremy/dataFullCompare/fullSimDataCompare_march2012_compare_%s.png",Vars[v]);
    // std::cout<<name<<std::endl;
    c1->Print(name);
  }//end v
}//end function
