#include <TDatime.h>
#include "TF1.h"
#include "TFile.h"
#include "TCanvas.h"
#include "TGraphErrors.h"
#include "TGraph.h"
#include "TH1.h"
#include "TH2.h"
#include "TStyle.h"
//#include "TSystem.h"
#include "TColor.h"
#include "TLegend.h"
#include "TMatrixD.h"
#include "TVectorT.h"
#include <math.h>
#include <algorithm>
#include <list>
#include <iostream>
#include <vector>
#include "TROOT.h"
#include "ZptatpsStandard.C"
//#include "zrapidityStandard.C"

void zap_binMigration(TFile* f0,std::string newNameFile, int var, int zdef,int rbin){
 
  gROOT->SetStyle("Plain");
  
  char Detector_Pair[3][128];
  sprintf(Detector_Pair[0],"EB-EB");
  sprintf(Detector_Pair[1],"EE-EB");
  sprintf(Detector_Pair[2],"EE-HF");
  
  char Variable_MC[4][128];
  sprintf(Variable_MC[0],"atTL_vs_at");
  sprintf(Variable_MC[1],"atTL_vs_at");
  sprintf(Variable_MC[2],"phiStarTL_vs_phiStar");
  sprintf(Variable_MC[3],"phiStarTL_vs_at");//some older files
  
  char varName[4][128];
  sprintf(varName[0],"at");
  sprintf(varName[1],"at");
  sprintf(varName[2],"phiStar");
  sprintf(varName[3],"phiStar");
  printf("var %s(%i) zdef %s(%i)",Variable_MC[var],var,Detector_Pair[zdef],zdef);
  char name[128];
  
  TFile *fnew= new TFile(newNameFile.c_str(),"recreate");
  fnew->cd();
  sprintf(name, "originalHistograms_%s_%s",varName[var], Detector_Pair[zdef]);
  TDirectory *oh0s = fnew->mkdir(name);
  oh0s->cd();

  sprintf(name, "/mcEff/%s/C08-m(60,120)/%s", Detector_Pair[zdef], Variable_MC[var]);
  
  int    at_bins[]={150,150,150};
  int    ps_bins[]={100,100,100};
  
  
  TH2F* h0=(TH2F*)f0->Get(name)->Clone("cloneR");
  h0->Clone("ho")->Write("Original2D");  
  if(rbin==1){
    h0=(TH2F*)zap_rebinForPlot2D(h0,zdef,var);
    h0->Clone("ro")->Write("OriginalRebinned2D");
    at_bins[0]=23;
    at_bins[1]=16;
    at_bins[2]=9;
    ps_bins[0]=100;
    ps_bins[1]=50;
    ps_bins[2]=8;
  }
  //make a Truth projection

  printf(" \n \n atbins %i %i %i  ps bins  %i %i %i \n",at_bins[0],at_bins[1],at_bins[2],ps_bins[0],ps_bins[1],ps_bins[2]);
  sprintf(name, "%s_MC_Truth",varName[var]);
  TH1D * h0_py = h0->ProjectionY(name,0,-1,"");
  h0_py->Clone("hopy")->Write("OriginalProjY_Truth");
  
  
  sprintf(name, "%s Simulated Smeared",varName[var]);
  TH1D * h0_px = h0->ProjectionX(name,0,-1,"");
  h0_px->Clone("hopx")->Write("OriginalProjX_SimSmear");
  sprintf(name, "Migration of %s %s",varName[var],Detector_Pair[zdef]);
  ///make sim-true/true
  TH1D * h_effect = (TH1D*)h0_px->Clone(name);
  h_effect->Reset();
  h_effect->Add(h0_px, h0_py, 1, -1);
  h_effect->Divide(h0_py);
  h_effect->SetTitle("(smeared-true)/true");
  h_effect->SetStats(0);




  TH2F * hMx  =  (TH2F*)h0->Clone("Migration_matrix");
  hMx->Reset();
  
  
  
  
  /////////////////////////////////////////////////////////////////////////
  double integral=0;
  for(int binY=1; binY<=h0->GetNbinsY(); binY++)
    {
      integral=0;
      
      for(int binX=1; binX<=h0->GetNbinsX(); binX++)
	{
	  integral+=h0->GetBinContent(binX,binY);
	}// binX
      
      if (integral==0) continue;
      
      // histomatrix has rows all normalized to 1
      // x-> reco; y-> true; => sum(y=const) has to be =1 , for probabilty conservation
      // note that in modern version of EffxAcc code there's an _matrix histogram which is normalize..
      for(int binX=1; binX<=h0->GetNbinsX(); binX++)
	{
	  hMx->SetBinContent(binX,binY, 1.*h0->GetBinContent(binX,binY)/integral );
	}// binX
    }// binY
  
  std::vector<int*> binz;  
  //   int    at_bins[4]={150,150,150};//{23,16,9};
  //   int    ps_bins[4]={100,100,100};//{100,50,8};
  
  
  binz.push_back(at_bins); binz.push_back(at_bins);
  binz.push_back(ps_bins); binz.push_back(ps_bins);
  int this_bin[4];
  int *tis = binz[var];
  this_bin[0]=tis[0];
  this_bin[1]=tis[1];
  this_bin[2]=tis[2];
  int maxbinx=this_bin[zdef];
  int minbinx=1;
  int maxbiny=maxbinx;
  int minbiny=minbinx;
  double migtrix[24025];
  printf (" \n maxbinx %i minbinx %i this bin %i %i %i  binz.var? %i %i %i  \n",maxbinx ,minbinx,this_bin[0],this_bin[1],this_bin[2],binz[var][0],binz[var][1],binz[var][2]);
  int bit=0;
  for(int u=minbinx;u<maxbinx+1;u++){//rows
    for(int v=minbiny;v<maxbiny+1;v++){//collumns
      
      
      migtrix[bit]=hMx->GetBinContent(u,v);
      if(u==v && hMx->GetBinContent(u,v)==0) migtrix[bit]=1;
      bit++; 
      
    }
  }//end u/v
  
  
  
  
  
  //http://root.cern.ch/root/html/tutorials/matrix/invertMatrix.C.html
  //this is the smearing matrix: it multiplies the unsmeared vector to give the smeared vector
  //gSystem->Load("libMatrix");
  
  TMatrixD MigrationMatrix(0, (maxbinx-minbinx), 0, (maxbiny-minbiny),  migtrix,"");
  
  // directory where one saves the matrices
  sprintf(name, "unsmearMatrices_%s_%s",varName[var],Detector_Pair[zdef]); 
  TDirectory *unsmearMatrices = fnew->mkdir(name);
  unsmearMatrices->cd();
  TMatrixD inverseMigrationMatrix = MigrationMatrix;

  Double_t determinant;
  inverseMigrationMatrix.Invert(&determinant);

  // this is the name I assign to the unfolding matrix for all Z candidates: ECAL-ECAL and ECAL-HF
  inverseMigrationMatrix.Write("unfoldingMatrixTotal");
  //end invert matrix

  ///make the latex table

char varTex[4][128];
 sprintf(varTex[0],"a^\\mathrm{reco}_{T,");
sprintf(varTex[1],"a^\\mathrm{true}_{T,i}");
sprintf(varTex[2],"a^{*}_\\mathrm{reco,");
sprintf(varTex[3],"a^{*}_\\mathrm{true,i}");
 int tvar=(var<2) ? 0 : 2;
 sprintf(name, "migrationTable_%s_%s.tex", Detector_Pair[zdef], Variable_MC[var]);
 FILE* texTable=fopen(name,"wt");
 fprintf(texTable,"\\begin{tabular}{|cc||ccccc|} \\hline \n");
 fprintf(texTable,"$min(%s)$ & $max(%s)$ & $%si-2}$ & $%si-1}$ & $%si}$ & $%si+1}$ & $%si+2}$ \\\\ \\hline \n",varTex[tvar+1],varTex[tvar+1],varTex[tvar],varTex[tvar],varTex[tvar],varTex[tvar],varTex[tvar]);
  



 for (int i=minbinx; i<maxbinx+1; i++) {
    double lv=h0->GetXaxis()->GetBinLowEdge(i);
    double lh=h0->GetXaxis()->GetBinUpEdge(i);

  
    //   if ( fabs(lv)>250 || fabs(lh)>600)) continue;
    
    fprintf(texTable,"%5.2f & %5.2f & ",lv,lh);

    for (int j=-2; j<=2; j++) {
      int ireco=i+j;
      if ((ireco)<1 || (ireco)>=(maxbinx-minbinx) ) {
   
	fprintf(texTable," -- ");
	if (j!=2) fprintf(texTable," & ");
	else fprintf(texTable,"\\\\\n");
	continue;
    } else {
      fprintf(texTable,"%.2e",MigrationMatrix(ireco-1,i-1));
	if (j!=2) fprintf(texTable," & ");
	else fprintf(texTable,"\\\\\n");
      }


    }
     
  }
  fprintf(texTable,"\\hline\n\\end{tabular}\n");  
  fclose(texTable);
  ///finish latx table


//   //sanity check, does it make unity?
//   TMatrixD isThisUnity(inverseMigrationMatrix,TMatrixD::kMult,MigrationMatrix);
//   // create reference to the diagonal and set the diagonal to 0
//   TMatrixDDiag diag1(isThisUnity); 
//   diag1 = 0.0;
//   const Double_t U1_max_offdiag = (isThisUnity.Abs()).Max();
//   cout << "\n\n\n  Verification that inversion was ok: maximum off-diagonal A * A^-1 = " << U1_max_offdiag << " is it SMALL?\n\n "<< endl;
//   //////end sane checking
  
  //////vector unsmearing test  
  double arraypx[11000];
  int pxint=0;
  
  for(int bin=minbinx; bin<maxbinx+1; bin++)
    {
      arraypx[pxint] =h0_px->GetBinContent(bin);
      pxint++;
    }

  TVectorD vectorSmeared; 
  vectorSmeared.Use( maxbinx , arraypx);
  TVectorD vectorUNSmeared = inverseMigrationMatrix * vectorSmeared;
  TH1D * h_UNSmeared = (TH1D*) h0_px->Clone("Varaible_Migration"); 
  h_UNSmeared->Reset();

  for(int bin=minbinx; bin<maxbinx+1; bin++)
    {
      h_UNSmeared->SetBinContent(bin,vectorUNSmeared[bin-1]);
    }

  //made an unsmeared version of px, should be similar to py



  /////pretty plot things
  // http://ultrahigh.org/2007/08/20/making-pretty-root-color-palettes/

   TCanvas * c4 = new TCanvas("Migration histogram","Migration histogram",1050,750);
   c4->cd(1);  c4->SetLogz();     
 
   //if(var<2){  c4->SetLogx();   c4->SetLogy();}
 
   h0->SetTitle("Migration histogram");
   h0->SetTitle("Migration Total");
   h0->GetXaxis()->CenterTitle();
   h0->GetYaxis()->CenterTitle();
   h0->Draw("colz");
   sprintf(name,"pictures/migration-total.png");
   c4->Print( name );



 TCanvas * c4q = new TCanvas("c4q","c4q",1050,750);
   c4q->cd();
   h_effect->SetLineColor(2);
   h_effect->Draw();

   //new way of getting the time 
   const char* time_;
   TDatime *mytime = new TDatime();
   time_ = mytime->AsString();
   TText *plabel = new TText();
   plabel-> SetNDC();
   plabel -> SetTextFont(1);
   plabel -> SetTextColor(1);
   plabel -> SetTextSize(0.04);
   plabel -> SetTextAlign(22);
   plabel -> SetTextAngle(0);
   TText *tlabel = new TText();
   tlabel-> SetNDC();
   tlabel -> SetTextFont(1);
   tlabel -> SetTextColor(1);
   tlabel -> SetTextSize(0.02);
   tlabel -> SetTextAlign(22);
   tlabel -> SetTextAngle(0);
   std::cout << "\n\n The local time is: " << time_ << "\n\n" << std::endl;


   TCanvas * c5 = new TCanvas("migration matrix","migration matrix",1050,750);
   c5->SetTopMargin(0.02);
   c5->SetRightMargin(0.14);
   c5->SetLeftMargin(0.11);   
   c5->SetBottomMargin(0.125);
   c5->cd(1);  c5->SetLogz();   
       
   hMx->GetXaxis()->SetTitle("q_{T,reco} [GeV/c]");
   hMx->GetYaxis()->SetTitle("q_{T,true} [GeV/c]");
   hMx->GetXaxis()->SetTitleOffset(1.3);
   hMx->GetYaxis()->SetTitleOffset(1.4);
   // hMx->GetXaxis()->SetRangeUser(0.0001,600);
   //hMx->GetYaxis()->SetRangeUser(0.0001,600);
   
   //c5->SetLogx();   c5->SetLogy();
   
   hMx->GetXaxis()->CenterTitle();
   hMx->GetYaxis()->CenterTitle(true);
   hMx->GetYaxis()->SetTitleOffset(0.8);
   hMx->SetMaximum(1);
   hMx->SetStats(0);
   
   hMx->Draw("colz");
   plabel -> DrawText(0.30, 0.93, "CMS preliminary 2010");
   tlabel -> DrawText(0.30, 0.90, Form("%s",time_));
   hMx->SetTitle("Migration matrix (normalized)");
   sprintf(name,"pictures/migrationMatrix_%s_%s.png",varName[var],Detector_Pair[zdef]);
   c5->Print(name);
   sprintf(name,"pictures/migrationMatrix_%s_%s.eps",varName[var],Detector_Pair[zdef]);
   c5->Print(name);
   sprintf(name,"pictures/migrationMatrix_%s_%s.pdf",varName[var],Detector_Pair[zdef]);
   c5->Print(name);

   TCanvas * c7pre = new TCanvas("closure test","closure test",1050,750);
   
   //c7pre->SetLogx();   c7pre->SetLogy();
   
   c7pre->cd();
   h0_py->SetLineWidth(2);//this is black for now
   h0_py->GetYaxis()->SetTitle("events");
   h0_py->SetTitle(0);
   h0_py->Draw("");//this is black for now
  
   h_UNSmeared->SetMarkerColor(4);
   h_UNSmeared->SetMarkerStyle(20);
   h_UNSmeared->SetMarkerSize(0.7);
   h_UNSmeared->SetLineWidth(1);
   h_UNSmeared->Draw("sameAP");

  
   
   h0_px->SetMarkerColor(2);
   h0_px->SetMarkerStyle(23);
   h0_px->SetMarkerSize(0.75);
   h0_px->Draw("sameAP");
   
   TLegend* leg = new TLegend(0.1,0.7,0.30,0.9);
   leg->SetHeader("");
   leg->AddEntry(h0_px,"variable smeared","p");
   leg->AddEntry(h0_py,"variable treeLevel","l");
   leg->AddEntry(h_UNSmeared,"variable unsmeared (overlap?)","p");
   leg->Draw();
   
   ///////////////////////////////////////////////////////
   c7pre->Print("pictures/rapdity-Tree-Smear-Unsmear-Closure.png");
   
   
   TH1D * h_effectUnsmearing = (TH1D*)h_effect->Clone("effectUnsmear");
   TCanvas * c8 = new TCanvas("closure test Tw0","closure test tw0",1050,750);
   c8->cd();
   h_effectUnsmearing->Reset();
   h_effectUnsmearing->Add(h_UNSmeared, h0_py, 1, -1);
   h_effectUnsmearing->Divide(h0_py);
h_effectUnsmearing->SetMinimum(-.0001);
   h_effectUnsmearing->Draw();

   c8->Print("pictures/UNsmeared-true-over-true-Closure.png");


}
