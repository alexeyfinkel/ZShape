#include <string>
#include <vector>
#include <math.h>
#include <iostream>
#include <stdlib.h>
#include <TRandom.h>
#include <time.h>
#include "Math/GenVector/PtEtaPhiM4D.h"


//void smearHF(const math::PtEtaPhiMLorentzVector in4v, double in_deteta,TRandom& rands, math::PtEtaPhiMLorentzVector& out4v,double& out_deteta){
//math::PtEtaPhiMLorentzVector -> ROOT::Math::PtEtaPhiM4D<double>
//ROOT::Math::PtEtaPhiM4D<double> v1;
//in4v->SetE(100);
//in4v->SetEta(3);
//in4v->SetPhi(1);

void smearHF(const ROOT::Math::PtEtaPhiM4D<double>& in4v, double in_deteta,TRandom& rands, ROOT::Math::PtEtaPhiM4D<double>& out4v,double& out_deteta){
 
  //initial declarations
  // TRandom rands;	
  //rands.SetSeed(time(NULL));
  ROOT::Math::PtEtaPhiM4D<double> v0;



  double EnScale,EtaScale,PhiScale;//=rands.Gaus(mean,sigma);
  double EnSigma,EtaSigma,PhiSigma;
  double energy=in4v.E();
  double phi=in4v.Phi();
  double deta=in_deteta;
  double trueEta=in4v.Eta();
  double ceta,cphi;
  v0=in4v;
  double  etaFact=sinh(trueEta)/sinh(deta);

  static const double HFEtaBounds[14] = {2.853, 2.964, 3.139, 3.314, 3.489, 3.664,3.839, 4.013, 4.191, 4.363, 4.538, 4.716, 4.889, 5.191};
  double RcellEta = fabs(deta);
  cphi = (phi>0.)?(fmod((phi),0.087*2)/(0.087*2)):((fmod((phi),0.087*2)/(0.087*2))+1.0);
  double Rbin = -1.0;
  for (int icell = 0; icell < 12; icell++ ){
    if ( (RcellEta>HFEtaBounds[icell]) && (RcellEta<HFEtaBounds[icell+1]) )
      Rbin = (RcellEta - HFEtaBounds[icell])/(HFEtaBounds[icell+1] - HFEtaBounds[icell]);
  }
  ceta=Rbin;
  
  
  
  //set EnSigma
  if((energy>0)&&(energy<=140)){
    EnSigma=0.1896;
  }else if((energy>140)&&(energy<=210)){
    EnSigma=0.2104;
  }else if((energy>210)&&(energy<=420)){
    EnSigma=0.19;
  }else if((energy>420)&&(energy<=560)){
    EnSigma=0.177;
  }else if((energy>560)&&(energy<=840)){
    EnSigma=0.16;
  }else if((energy>840)&&(energy<=1120)){
    EnSigma=0.16;
  }else if((energy>1120)&&(energy<=1400)){
    EnSigma=0.14;
  }else{
    EnSigma=0.17;
  }

  //set EtaSigma

  if ((ceta>0)&&(ceta<=.1)){
    EtaSigma=.0123;
  }else if ((ceta>.1)&&(ceta<=.2)){
    EtaSigma=.0153;
  }else if ((ceta>.2)&&(ceta<=.3)){
    EtaSigma=.0206;
  }else if ((ceta>.3)&&(ceta<=.4)){
    EtaSigma=.0246;
  }else if ((ceta>.4)&&(ceta<=.5)){
    EtaSigma=.0276;
  }else if ((ceta>.5)&&(ceta<=.6)){
    EtaSigma=.0306;
  }else if ((ceta>.6)&&(ceta<=.7)){
    EtaSigma=.0276;
  }else if ((ceta>.7)&&(ceta<=.8)){
    EtaSigma=.0225;
  }else if ((ceta>.8)&&(ceta<=.9)){
    EtaSigma=.0162;
  }else if ((ceta>.9)&&(ceta<=1)){
    EtaSigma=.0112;
  } 

  //set PhiSigma
  if ((cphi>0)&&(cphi<=.1)){
    PhiSigma=.0135;
  }else if ((cphi>.1)&&(cphi<=.2)){
    PhiSigma=.0186;
  }else if ((cphi>.2)&&(cphi<=.3)){
    PhiSigma=.0214;
  }else if ((cphi>.3)&&(cphi<=.4)){
    PhiSigma=.0258;
  }else if ((cphi>.4)&&(cphi<=.5)){
    PhiSigma=.0316;
  }else if ((cphi>.5)&&(cphi<=.6)){
    PhiSigma=.0315;
  }else if ((cphi>.6)&&(cphi<=.7)){
    PhiSigma=.0271;
  }else if ((cphi>.7)&&(cphi<=.8)){
    PhiSigma=.0217;
  }else if ((cphi>.8)&&(cphi<=.9)){
    PhiSigma=.0179;
  }else if ((cphi>.9)&&(cphi<=1)){
    PhiSigma=.0149;
  } 



  //get scalings
  EnScale=rands.Gaus(1,EnSigma);
  EtaScale=rands.Gaus(1,EtaSigma);
  PhiScale=rands.Gaus(1,PhiSigma);

  //use scalings
  energy=energy*EnScale;
  phi=phi*PhiScale;
  deta=deta*EtaScale;
  out_deteta=deta;
  
  v0.SetE(energy);
  v0.SetEta(asinh(etaFact*sinh(deta)));
  v0.SetPhi(phi);
  //out4v.SetE(energy);

  out4v=v0;
}
