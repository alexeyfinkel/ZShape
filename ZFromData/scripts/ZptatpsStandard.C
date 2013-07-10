#ifndef ZPTATPS_STANDARD_INCLUDED
#define ZPTATPS_STANDARD_INCLUDED

#include "TText.h"
#include "TLatex.h"
#include "TDatime.h"
//{ 0.7, 2.5, 5, 7.5, 10, 12.5, 15, 17.5, 20, 30, 40, 50, 70, 90, 110, 150, 190, 250, 600, 3500 }
TH1* zap_rebinForPlot(TH1* original,int zdef,int vm) {
  char name[125];
  sprintf(name,"%s_4plot%i%i",original->GetName(),zdef,vm);
  
  if((vm == 0)||(vm == 1)){
  int    at_bins[4]={23,16,9};
 
  std::vector<double*> bin_set;
  double at_binning1[50]={ 0.1,1,2,3,4,5,6,7,8,10,12,16,20,25,30,35,40,50,60,70,80,90,100,150 };
  double at_binning2[50]={ 0.1,1,2,3,4,6,8,10,15,20,30,40,50,65,80,100,150 };
  double at_binning3[50]={ 0.1,1,2,3,5,15,30,50,80,150 };
  bin_set.push_back(at_binning1);
  bin_set.push_back(at_binning2);
  bin_set.push_back(at_binning3);
  TH1* rebinned=new TH1F(name,name,at_bins[zdef],bin_set[zdef]);
  
  for(int i=1;i<=original->GetNbinsX();i++){
    rebinned->Fill(original->GetBinCenter(i),original->GetBinContent(i));
   
  }
  return rebinned;

  } else if((vm == 2)||(vm == 3)){

 int    ps_bins[4]={100,50,8};
 
 std::vector<double*> bin_set;
double ps_binning1[150]={0.00001,0.01,0.02,0.03,0.04,0.05,0.06,0.07,0.08,0.09,0.1,0.11,0.12,0.13,0.14,0.15,0.16,
		 0.17,0.18,0.19,0.2,0.21,0.22,0.23,0.24,0.25,0.26,0.27,0.28,0.29,0.3,0.31,0.32,
		 0.33,0.34,0.35,0.36,0.37,0.38,0.39,0.4,0.41,0.42,0.43,0.44,0.45,0.46,0.47,0.48,
		 0.49,0.5,0.51,0.52,0.53,0.54,0.55,0.56,0.57,0.58,0.59,0.6,0.61,0.62,0.63,0.64,
		 0.65,0.66,0.67,0.68,0.69,0.7,0.71,0.72,0.73,0.74,0.75,0.76,0.77,0.78,0.79,0.8,
		 0.81,0.82,0.83,0.84,0.85,0.86,0.87,0.88,0.89,0.9,0.91,0.92,0.93,0.94,0.95,0.96,
		 0.97,0.98,0.99,1};
  double ps_binning2[150]={.00001,0.02,0.04,0.06,0.08,0.1,0.12,0.14,0.16,0.18,0.2,0.22,0.24,0.26,0.28,0.3,0.32,
		 0.34,0.36,0.38,0.4,0.42,0.44,0.46,0.48,0.5,0.52,0.54,0.56,0.58,0.6,0.62,0.64,
		 0.66,0.68,0.7,0.72,0.74,0.76,0.78,0.8,0.82,0.84,0.86,0.88,0.9,0.92,0.94,0.96,
		 0.98,1};
  double ps_binning3[150]={.00001,.02,.05,.1,.2,.3,.5,.75,1};
  bin_set.push_back( ps_binning1);
  bin_set.push_back( ps_binning2);
  bin_set.push_back( ps_binning3);
  TH1* rebinned=new TH1F(name,name,ps_bins[zdef],bin_set[zdef]);
  
  for(int i=1;i<=original->GetNbinsX();i++){
    rebinned->Fill(original->GetBinCenter(i),original->GetBinContent(i));
  }
  return rebinned;




  }else{


    return (TH1F*)(original->Clone("no_change"));

  }//end vm->




}


TH2* zap_rebinForPlot2D(TH2* original,int zdef,int vm) {

 char name[125];
  sprintf(name,"2d_%s_4plot%i%i",original->GetName(),zdef,vm);
  
  if((vm == 0)||(vm == 1)){
  int    at_bins[4]={23,16,9};
 
  std::vector<double*> bin_set;
  double at_binning1[50]={ 0.1,1,2,3,4,5,6,7,8,10,12,16,20,25,30,35,40,50,60,70,80,90,100,150 };
  double at_binning2[50]={ 0.1,1,2,3,4,6,8,10,15,20,30,40,50,65,80,100,150 };
  double at_binning3[50]={ 0.1,1,2,3,5,15,30,50,80,150 };
  bin_set.push_back(at_binning1);
  bin_set.push_back(at_binning2);
  bin_set.push_back(at_binning3);
  TH2* rebinned=new TH2F(name,name,at_bins[zdef],bin_set[zdef],at_bins[zdef],bin_set[zdef]);
  for(int j=1;j<=original->GetNbinsX();j++){
    for(int i=1;i<=original->GetNbinsX();i++){
       rebinned->Fill(original->GetXaxis()->GetBinCenter(i),original->GetXaxis()->GetBinCenter(j),original->GetBinContent(i,j));
    }
  }
  return rebinned;

  } else if((vm == 2)||(vm == 3)){

 int    ps_bins[4]={100,50,8};
 
 std::vector<double*> bin_set;
double ps_binning1[150]={0.00001,0.01,0.02,0.03,0.04,0.05,0.06,0.07,0.08,0.09,0.1,0.11,0.12,0.13,0.14,0.15,0.16,
		 0.17,0.18,0.19,0.2,0.21,0.22,0.23,0.24,0.25,0.26,0.27,0.28,0.29,0.3,0.31,0.32,
		 0.33,0.34,0.35,0.36,0.37,0.38,0.39,0.4,0.41,0.42,0.43,0.44,0.45,0.46,0.47,0.48,
		 0.49,0.5,0.51,0.52,0.53,0.54,0.55,0.56,0.57,0.58,0.59,0.6,0.61,0.62,0.63,0.64,
		 0.65,0.66,0.67,0.68,0.69,0.7,0.71,0.72,0.73,0.74,0.75,0.76,0.77,0.78,0.79,0.8,
		 0.81,0.82,0.83,0.84,0.85,0.86,0.87,0.88,0.89,0.9,0.91,0.92,0.93,0.94,0.95,0.96,
		 0.97,0.98,0.99,1};
  double ps_binning2[150]={.00001,0.02,0.04,0.06,0.08,0.1,0.12,0.14,0.16,0.18,0.2,0.22,0.24,0.26,0.28,0.3,0.32,
		 0.34,0.36,0.38,0.4,0.42,0.44,0.46,0.48,0.5,0.52,0.54,0.56,0.58,0.6,0.62,0.64,
		 0.66,0.68,0.7,0.72,0.74,0.76,0.78,0.8,0.82,0.84,0.86,0.88,0.9,0.92,0.94,0.96,
		 0.98,1};
  double ps_binning3[150]={.00001,.02,.05,.1,.2,.3,.5,.75,1};
  bin_set.push_back( ps_binning1);
  bin_set.push_back( ps_binning2);
  bin_set.push_back( ps_binning3);
  TH2* rebinned=new TH2F(name,name,ps_bins[zdef],bin_set[zdef],ps_bins[zdef],bin_set[zdef]);
  for(int j=1;j<=original->GetNbinsX();j++){
    for(int i=1;i<=original->GetNbinsX();i++){
      rebinned->Fill(original->GetXaxis()->GetBinCenter(i),original->GetXaxis()->GetBinCenter(j),original->GetBinContent(i,j));
      //  rebinned->SetBinError(i,original->GetBinError(i));
    }
  }
  return rebinned;




  }else{


    return (TH2F*)(original->Clone("no_change"));

  }//end vm->






}




#endif
