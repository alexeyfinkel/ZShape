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

void checkForPdfSensitivity(TFile* t, int n, int comp_to,int zdef,int V_M,int rbins=1){
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
  	std::cout<<"# Sample    variable       pdfBase    pdfTrial     Chi^2     "<<std::endl;

      sprintf(name, "%s %s", Detector_Pair[zdef], Variable_MC[V_M]);
      TCanvas *comp = new TCanvas(name, name, 500, 500);
      if(comp_to != -1)
	sprintf(name, "/pdf%d/%s/C08-m(60,120)/%s", comp_to, Detector_Pair[zdef], Variable_MC[V_M]);
      else
	sprintf(name, "/pdf%d/%s/C08-m(60,120)/%s", 0, Detector_Pair[zdef], Variable_MC[V_M]);

      TH1F* h2 = (TH1F*)t->Get(name);

      if(comp_to != -1)
	sprintf(name, "COMP pdf%d %s %s", comp_to, Detector_Pair[zdef], Variable_MC[V_M]);
      else
	sprintf(name, "COMP pdf%d %s %s", 0, Detector_Pair[zdef], Variable_MC[V_M]);
   
      h2 = (TH1F*)(h2->Clone(name));
      TH1F* r2=(TH1F*)zap_rebinForPlot(h2,zdef,V_M);
     
      // h2->Rebin(rbins);
      std::cout<<"# Sample    variable       pdfBase    pdfTrial     Chi^2     "<<std::endl;
        
      sprintf(name, "Chi2_%s_%s", Detector_Pair[zdef], Variable_MC[V_M]);
      TH1F* g1 = new TH1F(name,name,54,-0.5,53.5);
      TH1F* rg1 = new TH1F(name,name,54,-0.5,53.5);
      for(int i = 0; i < n; i++){
	comp->cd(1);
	sprintf(name, "/pdf%d/%s/C08-m(60,120)/%s", i, Detector_Pair[zdef], Variable_MC[V_M]);	
	TH1F* h1 = (TH1F*)t->Get(name);
	sprintf(name, "pdf%d %s %s", i, Detector_Pair[zdef], Variable_MC[V_M]);
	h1 = (TH1F*)(h1->Clone(name));
	//	h1->Rebin(rbins);
	TH1F* r1=(TH1F*)zap_rebinForPlot(h1,zdef,V_M);
	int jj;
	double chi2=0;  
	
	for (jj=1;jj<=h1->GetNbinsX();jj++){
	  double s2exp = (h2->GetBinContent(jj));
	  double s2obs= (h1->GetBinContent(jj));   
	  
	  if (s2exp==0){
	    chi2+=0;
	  }else{
	    chi2+=((s2obs-s2exp)*(s2obs-s2exp))/((sqrt(s2exp))*(sqrt(s2exp)));
	  }
	}

	int rjj;
	double rchi2=0;  
	
	for (rjj=1;rjj<=r1->GetNbinsX();rjj++){
	  double rs2exp = (r2->GetBinContent(rjj));
	  double rs2obs= (r1->GetBinContent(rjj));   
	  
	  if (rs2exp==0){
	    rchi2+=0;
	  }else{
	    rchi2+=((rs2obs-rs2exp)*(rs2obs-rs2exp))/((sqrt(rs2exp))*(sqrt(rs2exp)));
	  }
	}

	//	ch1->cd(1);
 	g1->Fill(i,chi2);
	rg1->Fill(i,rchi2);
	comp->cd(1);
	std::cout<<" "<<Detector_Pair[zdef] <<"    "<<Variable_MC[V_M] <<"       "<<comp_to <<"          " <<i <<"          "<<chi2<<std::endl;
	
	if(comp_to != -1)
	  h1->Divide(h2);
	  r1->Divide(r2);
// 	if(i == 0)
// 	  int ff=0; //h1->Draw("");
// 	else
// 	  int ff=0;// h1->Draw("SAME");
      }
      
      
      sprintf(name, "Chi Squared %s %s", Detector_Pair[zdef], Variable_MC[V_M]);
      TCanvas *ch1 = new TCanvas(name, name, 500, 500);
      ch1->cd(1);
      g1->Draw("PE");
      rg1->SetMarkerColor(4);
      rg1->SetMarkerStyle(4);
      rg1->Draw("SAME PE");
      sprintf(name,"~/public_html/pdf/chi2/jan16_chi2_%s_%s_cmprd%d_rebinned%d.png", Detector_Pair[zdef], Variable_MC[V_M],comp_to,rbins);
      std::cout<<name<<std::endl;
      // ch1->Print(name);
      
}//file
