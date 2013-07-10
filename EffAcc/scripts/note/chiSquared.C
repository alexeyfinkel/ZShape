

void chiSquared(TFile* ef,TFile* ed){
   
  // TH1F* he  = (TH1F*)ef->Get("ZFromData/Tight-ECAL-HF/C07-HLT-EtaDet/Z0_mass");//observed
  //TH1F* hp  = (TH1F*)ef->Get("ZFromData/Tight-ECAL-HF/C07-HLT-EtaDet/Z0_mass");//expected
  
  TH1F *ob = 0;
  TH1F *ex = 0;
  
  ef->GetObject("mcEff/Tight-ECAL-HF/C07-HLT-EtaDet/Z0_mass",ob);
  ed->GetObject("ZFromData/Tight-ECAL-HF/C07-HLT-EtaDet/Z0_mass",ex);
  
  if (ob == 0) {
    cerr << "Dang! Whatta I have to do anyway??"<<endl;
    return;
  }
  int i;
  int j;
  double chi2=0;  
  
  for (i=1;i<=50;i++){
    double s2exp = (ex->GetBinContent(i));
    double s2obs= (ob->GetBinContent(i));   
   
    if (s2exp==0){
      chi2+=0;
    }else{
      chi2+=((s2obs-s2exp)*(s2obs-s2exp))/((sqrt(s2exp))*(sqrt(s2exp)));
    }
  }
  
  std::cout<<"Chi^2 is: "<<chi2<<std::endl;
}
