void pwgCompare(TFile* f1,TFile* f2,TFile* f3,TFile* f4,TFile* f){



  TH1F* h[20];
h[]=(TH1F*)f->Get("mcEff/ECAL80-ECAL95-MUO/C08-m(60,120)/Z0_Pt_masscut")->Clone("cl");


 ob=new TH1F("","",18,);











    double chi2[20]=0;  
    for(j=0;j<20;j++){
      chi2[j]=0 ;
      h[j]->Scale((ob->GetEntries()*1.0)/(h[j]->GetEntries()*1.0));
      
      for (i=1;i<=200;i++){
	double s2obs= (ob->GetBinContent(i));   
	double s2exp = (h[j]->GetBinContent(i));
	if (s2obs==0){
	  chi2[j]+=0;
	}else{
	  chi2[j]+=((s2obs-s2exp)*(s2obs-s2exp)*1.0)/((sqrt(s2obs))*(sqrt(s2obs))*1.0);
	    
	  
	}//end else
      }//end i
      
    }//end j
    

    double x[20]={1,2,3,4,5,6,7,8,9};
    int n=9;
    gr = new TGraph(n,x,chi2);

    
}
