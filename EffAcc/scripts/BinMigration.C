#include <TH2.h>

#include <TH1D.h>

#include <iostream>
#include <vector>


void BinMigration(TFile* f1, const char* name){
  
  
  TH2F* h1 =(TH2F*) f1->Get(name)->Clone("cl1");
  
  
  
  for(int i=1;i<h1->GetNbinsY();i++){
    int bins=h1->GetNbinsY()+10;
    double metric[600];
    metric[0]=0;
    double minh=0,minc=0,maxc=0,maxh=0; 
    double truth=h1->GetBinLowEdge(i);
    for(int j=1;j<h1->GetNbinsX();j++){
      
      int value=h1->GetBinContent(j,i);
      int base=max(h1->GetBinContent(i,i),1);
      double ratio=value*100.0/base;
      
      if (ratio < 10){ metric[j]=100;
      }else if(ratio<50){ metric[j]=10;
      }else if (ratio < 100000){ metric[j]=1;
      }
      
      if(metric[j-1]==100 && metric[j]==10 && minh==0) minh=h1->GetBinLowEdge(j-1);
      if(metric[j-1]==10 && metric[j]==1 && minc==0) minc=h1->GetBinLowEdge(j-1);
      if(metric[j-1]==1 && metric[j]==10 && maxc==0) maxc=h1->GetBinLowEdge(j);
      if(metric[j-1]==10 && metric[j]==100 &&  maxh==0) maxh=h1->GetBinLowEdge(j);
      
    }//end j
    
    std::cout<<"for "<<i<<"th bin "<< h1->GetBinLowEdge(i)<<" we have: "<<truth-minh <<"  "<<truth-minc <<"  "<<maxc-truth<<"  "<<maxh-truth<<""<<std::endl;
    
    
    
  }//end i
  

}
