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

void phistar_pdf_comparison(TFile* t, int n, int comp_to,int rbins=1){
  gROOT->SetStyle("Plain"); gStyle->SetOptStat(0000);
  //setTDRStyle();
  char Detector_Pair[3][128];
  sprintf(Detector_Pair[0],"EB-EB");
  sprintf(Detector_Pair[1],"EE-EB");
  sprintf(Detector_Pair[2],"EE-HF");
  
  char Variable_MC[4][128];
  sprintf(Variable_MC[0],"wZ0_at");
  sprintf(Variable_MC[1],"wZ0_phiStar");
  
  char vnames[4][128];
  sprintf(vnames[0],"a_{T}");
  sprintf(vnames[1],"#phi*");
  char name[128];
  //	std::cout<<"# Sample    variable       pdfBase    pdfTrial     Chi^2     "<<std::endl;
  for(int D_P = 0; D_P < 3; D_P++){
    for(int V_M = 0; V_M < 2; V_M++){
      
      sprintf(name, "%s %s", Detector_Pair[D_P], Variable_MC[V_M]);
      // TCanvas *comp = new TCanvas(name, name, 500, 500);
      if(comp_to != -1)
	sprintf(name, "/pdf%d/%s/C08-m(60,120)/%s", comp_to, Detector_Pair[D_P], Variable_MC[V_M]);
      else
	sprintf(name, "/pdf%d/%s/C08-m(60,120)/%s", 0, Detector_Pair[D_P], Variable_MC[V_M]);
      printf("%s\n",name);
      TH1F* h2 = (TH1F*)t->Get(name);
      
      
      
      if(comp_to != -1)
	sprintf(name, "COMP pdf%d %s %s", comp_to, Detector_Pair[D_P], Variable_MC[V_M]);
      else
	sprintf(name, "COMP pdf%d %s %s", 0, Detector_Pair[D_P], Variable_MC[V_M]);
      
      h2 = (TH1F*)(h2->Clone(name));
      // h2->Rebin(rbins);
      //   std::cout<<"# Sample    variable       pdfBase    pdfTrial     Chi^2     "<<std::endl;
      
      if(comp_to != -1)
	sprintf(name, "/pdf%d/All/Z0_mass", comp_to);
      else
	sprintf(name, "/pdf%d/All/Z0_mass", 0);
      
      TH1F* i2 = (TH1F*)t->Get(name);
      
      sprintf(name, "Chi2_%s_%s", Detector_Pair[D_P], Variable_MC[V_M]);
      TH1F* g1 = new TH1F(name,name,54,-0.5,53.5);
      
      
      
      for(int i = 0; i < n; i++){
	//	comp->cd(1);
	sprintf(name, "/pdf%d/%s/C08-m(60,120)/%s", i, Detector_Pair[D_P], Variable_MC[V_M]);	
	TH1F* h1 = (TH1F*)t->Get(name);
	sprintf(name, "pdf%d %s %s", i, Detector_Pair[D_P], Variable_MC[V_M]);
	h1 = (TH1F*)(h1->Clone(name));
	//	h1->Rebin(rbins);
	int jj;
	double chi2=0;  
        int neff=0;
	
	sprintf(name, "/pdf%d/All/Z0_mass", i);
	TH1F* i1 = (TH1F*)t->Get(name);
	double scale=i2->Integral()*1.0/((double)i1->Integral());
	h1->Scale(scale);


	for (jj=1;jj<=h1->GetNbinsX();jj++){
	  double s2exp = (h2->GetBinContent(jj));
	  double s2obs= (h1->GetBinContent(jj));   


	  if (s2exp==0){
	  printf("%d %f %f \n",jj,s2exp,s2obs);
	    chi2+=0;
	  }else{
	    chi2+=((s2obs-s2exp)*(s2obs-s2exp))/((sqrt(s2exp))*(sqrt(s2exp)));
	    neff++;
	  }
	}

	printf("integral of h1 %0.2f for pdf %d %f %d %d \n",h1->Integral(),i,chi2,neff,h1->GetNbinsX());	
		
	if (neff==0) neff=1;
 	g1->Fill(i,1.0-chi2/neff);
	
      }
      sprintf(name, "Chi Squared %s %s", Detector_Pair[D_P], Variable_MC[V_M]);
      TCanvas *ch1 = new TCanvas(name, name, 500, 500);
      sprintf(name, "#Delta #chi^{2} From CT10 standard in %s, %s", vnames[V_M], Detector_Pair[D_P]);
      g1->SetTitle(name); 
      ch1->cd(1);
      g1->SetFillColor(kBlack);
      g1->SetBarWidth(0.75);
      g1->GetYaxis()->SetTitle("#Delta #chi^{2}");
      g1->GetXaxis()->SetTitle("PDFs");
      g1->GetXaxis()->CenterTitle();
      g1->Draw("HBAR1");
      
      sprintf(name,"~/public_html/pdf/chi2/Sensitivity2PDF_deltaCHI_s_%s_%s.png", Detector_Pair[D_P], Variable_MC[V_M]);
      std::cout<<name<<std::endl;
      // ch1->Print(name);
    }//end V_M varible majik name
  }//end etector particles
}//file
