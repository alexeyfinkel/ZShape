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



void FourxFourRatio(const int typeZ,const int novVar,const int numTfile,int rbin){

  
  setTDRStyle();
  
  TCanvas* c1=new TCanvas("Compare","Compare",800,600);
  c1->Divide(2,2);
  
 
  
  string VarNov[20];
  VarNov[0]="Z0_PtTLMon";
  VarNov[1]="wZ0_pt";
  if(novVar==1){
    VarNov[2]="Z0_at_MC";
    VarNov[3]="wZ0_at";
  }else if(novVar==0){
    VarNov[2]="wZ0_phiStar_MC";
    VarNov[3]="wZ0_phiStar";
  }
  string Ztypes[20]={"EB-EB","EE-EB","EE-HF"};
  int lcolor[10]={27,1,2,3,4,6};
  int lstyle[10]={1,2,3,5,9,10,4,6,7,8};
  TH1F* h[6][numTfile+5];
  for(int kk=0;kk<4;kk++){  
    for(int ii=0;ii<numTfile;ii++){
  
      char tfile[20], cl1[20],hname[200];
      sprintf(cl1,"cl%i%i",ii,kk);
      sprintf(tfile,"_file%i",ii);
      sprintf(hname,"mcEff/%c/C08-m(60,120)/%c",Ztypes[typeZ].c_str(),VarNov[kk].c_str());
      TFile* f(tfile);
      h[kk][ii]=(TH1F*)f->Get(hname)->Clone(cl1);
      h[kk][ii]->SetLineColor(lcolor[numTfile%6]);
      h[kk][ii]->SetLineStyle(lstyle[numTfile/6]);
    }//end ii
  }//end kk
  
  
  
 

  for(int kk=0;kk<4;kk++){  
    c1->cd(kk);
    //h[kk][0]->GetXaxis()->SetTitle("P_{T} MC [GeV]");
    h[kk][0]->SetMaximum(2.0* h[kk][0]->GetMaximum());
    h[kk][0]->SetMinimum(1.5* h[kk][0]->GetMinimum());
    //h[kk][0]->GetYaxis()->SetTitleOffset(1.2);
    h[kk][0]->SetTitle(0);  //no title
    h[kk][0]->SetStats(false);   //no stats box
    h[kk][0]->GetXaxis()->SetRangeUser(0,40);
    h[kk][0]->Rebin(rbin); 
    
    for(int k=1;k<numTfile;k++){
      h[kk][k]->Rebin(rbin);
      for(int i=1;i<h[kk][k]->GetNbinsX();i++){
	if(h[kk][0]->GetBinContent(i)>0){
	  h[kk][k]->SetBinContent(i,(h[kk][k]->GetBinContent(i))*1.0/h[kk][0]->GetBinContent(i));
	}
      }
    } //end k   
    for(int i=1;i<h[kk][k]->GetNbinsX();i++){
      if(h[kk][0]->GetBinContent(i)>0){ 
	h[kk][0]->SetBinContent(i,1);
      }
    }
    h[kk][0]->Draw("HIST");
    for(int k=1;k<numTfile;k++){
      h[kk][k]->SetLineWidth(2);
      h[kk][k]->Draw("SAME HIST");
    }
  }//END KK   
  
  /*  
      TLegend* tl=new TLegend(0.5,0.7,0.72,0.9,"");
      tl->SetFillStyle(0);
      tl->AddEntry(h[kk][0],"Parp[91]=0.25","l");
      tl->AddEntry(h[kk][1],"Parp[91]=0.5","l");
      tl->AddEntry(h[kk][2],"Parp[91]=0.75","l");
      tl->AddEntry(h[kk][3],"Parp[91]=1.0","l");
      tl->AddEntry(h[kk][4],"Parp[91]=1.25","l");
      tl->AddEntry(h[kk][5],"Parp[91]=1.5","l");
      tl->AddEntry(h[kk][6],"Parp[91]=2.0","l");
      //tl->AddEntry(h[kk][7],"Parp[91]=");
      //tl->AddEntry(h[kk][8],"Parp[91]=");
      tl->Draw();
      
    */
    
    

  
  c1->Print("~/public_html/talk/fiddle_pwgCompare.png");
 
}











