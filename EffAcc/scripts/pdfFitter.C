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

double xFunction(double x,int i,TH1F* tr0,TH1F* trp,TH1F* trm ){
  double value=(std::max(0.0,x)*trp->GetBinContent(i))+((1.0-fabs(x))*tr0->GetBinContent(i))+(fabs(std::min(0.0,x))*trm->GetBinContent(i));
 //  double base=std::max(1.0,tr0->GetBinContent(i)*1.0);
//     double value=(std::max(0.0,x)*trp->GetBinContent(i)/(1.0*base))+((1.0-fabs(x))*tr0->GetBinContent(i)/(1.0*base))+(fabs(std::min(0.0,x))*trm->GetBinContent(i)/(1.0*base));


  return value;
}//double xFunction(){

TH1F* gPDFvarPlus, *gPDFvarMinus, *gPDFvarBase;


Double_t interpolPDF(Double_t* x, Double_t* par) {
  double xvar=*x;
  // figure out the bin...
  int theBin=gPDFvarBase->FindBin(xvar);
  
  return xFunction(par[0],theBin,gPDFvarBase,gPDFvarPlus,gPDFvarMinus);
}


double makeChi(double wj, int jj,TH1F* h0,TH1F* hp,TH1F* hm,TH1F* ht,double grain){
  double expt = ht->GetBinContent(jj);
  double chi2=10000;
  double obs=xFunction(wj,jj,h0,hp,hm);
 
  chi2=((obs-expt)*(obs-expt))/((sqrt(expt))*(sqrt(expt)));
  return chi2;
  
}//end makeChi()

void pdfFitter(TFile* f0,int typ,int var ,int pdf0, int pdfp, int pdfm,int pdft, int grain){
  gROOT->SetStyle("Plain");
  
  char Detector_Pair[3][128];
  sprintf(Detector_Pair[0],"EB-EB");
  sprintf(Detector_Pair[1],"EE-EB");
  sprintf(Detector_Pair[2],"EE-HF");
  
  char Variable_MC[4][128];
  sprintf(Variable_MC[0],"wZ0_at");
  sprintf(Variable_MC[1],"Z0_at_MC");
  sprintf(Variable_MC[2],"wZ0_phiStar");
  sprintf(Variable_MC[3],"wZ0_phiStar_MC");
 
  char name[128];
  char mess[128];
 
  double min[600];
  double wgt[600];
  double chi2bin[600];
  double total=0;
  double avewj=0;
  
  int nbins[10];nbins[4]=6;//set up gaps!!!!
  double width[10];
  
  TH1F* h0[10];
  TH1F* hp[10];
  TH1F* hm[10];
  TH1F* hr[10];
  
  
  
  for(int zdef=0;zdef<3;zdef++){
    sprintf(name, "/pdf%d/%s/C08-m(60,120)/%s", pdf0, Detector_Pair[zdef], Variable_MC[var]);
    h0[zdef] = (TH1F*)f0->Get(name)->Clone("clone0");
    sprintf(name, "/pdf%d/%s/C08-m(60,120)/%s", pdfp, Detector_Pair[zdef], Variable_MC[var]);
    hp[zdef] = (TH1F*)f0->Get(name)->Clone("cloneP");
    sprintf(name, "/pdf%d/%s/C08-m(60,120)/%s", pdfm, Detector_Pair[zdef], Variable_MC[var]);
    hm[zdef] = (TH1F*)f0->Get(name)->Clone("cloneM");
    sprintf(name, "/pdf%d/%s/C08-m(60,120)/%s", pdft, Detector_Pair[zdef], Variable_MC[var]);
    hr[zdef]= (TH1F*)f0->Get(name)->Clone("cloneR");
    
    //area for rebining based onzdef
    hp[zdef]=(TH1F*)zap_rebinForPlot(hp[zdef],zdef,var);
    h0[zdef]=(TH1F*)zap_rebinForPlot(h0[zdef],zdef,var);
    hm[zdef]=(TH1F*)zap_rebinForPlot(hm[zdef],zdef,var);
    hr[zdef]=(TH1F*)zap_rebinForPlot(hr[zdef],zdef,var);
    //end rebin
    
    nbins[zdef]=h0[zdef]->GetNbinsX();
    width[zdef]=h0[zdef]->GetBinWidth(1);
    nbins[4]+=nbins[zdef];//gaps already added 
    
    hp[zdef]->Divide(h0[zdef]);
    hm[zdef]->Divide(h0[zdef]);
    hr[zdef]->Divide(h0[zdef]);
    h0[zdef]->Divide(h0[zdef]); 
  }//end for zdef
  TH1F* trp[10];  
  trp[0] = new TH1F("trp0","Triple Plot base",nbins[4],0,nbins[4]);
  trp[1] = new TH1F("trpP","Triple Plot Plus Sigma",nbins[4],0,nbins[4]);
  trp[2] = new TH1F("trpM","Triple Plot Minus Sigma",nbins[4],0,nbins[4]);
  trp[3] = new TH1F("trpT]","Triple Plot Test Plot",nbins[4],0,nbins[4]);
 
  
  for(int n=0; n<nbins[0]+2;n++){
    trp[0]->SetBinContent(n+1,h0[0]->GetBinContent(n));
    trp[1]->SetBinContent(n+1,hp[0]->GetBinContent(n));
    trp[2]->SetBinContent(n+1,hm[0]->GetBinContent(n));
    trp[3]->SetBinContent(n+1,hr[0]->GetBinContent(n));
  }//end trp filler for loop int n
  
  for(int n=0; n<nbins[1]+2;n++){
    trp[0]->SetBinContent(n+1+nbins[0]+2,h0[1]->GetBinContent(n));
    trp[1]->SetBinContent(n+1+nbins[0]+2,hp[1]->GetBinContent(n));
    trp[2]->SetBinContent(n+1+nbins[0]+2,hm[1]->GetBinContent(n));
    trp[3]->SetBinContent(n+1+nbins[0]+2,hr[1]->GetBinContent(n));
  }//end trp filler for loop int n
  
  for(int n=0; n<nbins[2]+2;n++){
    trp[0]->SetBinContent(n+1+nbins[0]+nbins[1]+4,h0[2]->GetBinContent(n));
    trp[1]->SetBinContent(n+1+nbins[0]+nbins[1]+4,hp[2]->GetBinContent(n));
    trp[2]->SetBinContent(n+1+nbins[0]+nbins[1]+4,hm[2]->GetBinContent(n));
    trp[3]->SetBinContent(n+1+nbins[0]+nbins[1]+4,hr[2]->GetBinContent(n));
  }//end trp filler for loop int n
  
  gPDFvarPlus=trp[1];gPDFvarMinus=trp[2]; gPDFvarBase=trp[0];  
    
  TH1F* func = new TH1F("func","Pretty Function Plot",nbins[4],0,nbins[4]);

  TCanvas* c1=new TCanvas("c1","c1",900,700);
  c1->cd();
 
  TF1 *f1 = new TF1("myfunc",interpolPDF,0,nbins[4],1);
  // h0->SetMinimum(0.7);
  // h0->SetMaximum(1.25);
 
  //  f1->SetParameters(-1,0);
  f1->SetLineColor(kBlue);
 
  trp[grain]->Fit("myfunc");

  //c1->Print("~/public_html/pdf/summation/triplePrettyFunction2012.png");
  sprintf(name, "~/public_html/pdf/summation/comparisonPlot_%i_%s_pdf%i_matchedBy_pdf%i_and_pdf%i.png", grain, Variable_MC[var],pdft,pdfp,pdfm);
  c1->Print(name);
}//end void pdfFitter()



//

#ifdef NEED_MAIN

int main(int argc, char* argv[]) {
  if (argc<8) {
    printf("Arguments:TFile* f0 [type 0bb,1eb,2eh]  [variabl 0at,1atmc,2ps,3psmc] [pdf0 number] [pdfp number] [pdfm number] [pdf test number] [grainularity] \n");
    return 1;
  }
  TFile f0(argv[1]);
  int typ=atoi(argv[2]);
  int var =atoi(argv[3]);
  int pdf0=atoi(argv[4]);
  int pdfp=atoi(argv[5]);
  int pdfm=atoi(argv[6]); 
  int pdft=atoi(argv[7]);
  int grain=atoi(argv[8]);
  //  double var=atof(argv[3]);
  pdfFitter(&f0,typ,var,pdf0,pdfp,pdfm,pdft,grain);
  std::cout<<"@@@@20"<<std::endl;
   return 0;
}

// gcc -o pdfFitter.exe pdfFitter.C -DNEED_MAIN -O `root-config --cflags --libs`
// ./pdfFitter.exe /local/cms/user/klapoetke/zshape_effacc_pdf_ct10/dec08_pdf_ct10.root 0 0 0 1 2 1

#endif
