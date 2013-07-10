#include "tdrstyle.C"
#include "zrapidityStandard.C"

void massPlotBkg(TFile* sigf, TFile* zfd_bkgd, TFile* zfd_final) {
  setTDRStyle();
  const double weight=1.0/(1771);
  char name[200];
 char name2[200];
  sprintf(name,"ZFromData/ECAL80-HF/C07-HLT-GSF/Z0_PtMon");
 //  sprintf(name,"ZFromData/ECAL80-ECAL95/C07-HLT-GSF/Z0_PtMon");

  TH1* bkshape=zfd_bkgd->Get(name)->Clone("bkgd");
  TH1* data=zfd_final->Get(name)->Clone("data");

     sprintf(name,"mcEff/ECAL80-HF/C07-HLT-GSF/Z0_PtMon");
  // sprintf(name,"mcEff/ECAL80-HF/C07-HLT-GSF/Z0_PtMon");

  TH1* sig=sigf->Get(name)->Clone("sig");

// //   for(int zz=1;zz<bkshape->GetNbinsX();zz++){


// //     if(zz==1)bkshape->SetBinContent(zz,9.3360);
// //     else if(zz==2)bkshape->SetBinContent(zz,12.4200);
// //     else if(zz==3)bkshape->SetBinContent(zz,9.9252);
// //     else if(zz==4)bkshape->SetBinContent(zz,8.5258);
// //     else if(zz==5)bkshape->SetBinContent(zz,14.8960);
// //     else if(zz==6)bkshape->SetBinContent(zz,12.0880);
// //     else if(zz==7)bkshape->SetBinContent(zz,4.2250);
// //     else if(zz==8)bkshape->SetBinContent(zz,7.2580);
// //     else if(zz==9)bkshape->SetBinContent(zz,11.2792);
// //     else if(zz==10)bkshape->SetBinContent(zz,6.3808);
    
// //     else if(zz>10 && zz<=15) bkshape->SetBinContent(zz,2.6520);
// //     else if(zz>15 && zz<=20) bkshape->SetBinContent(zz,0.9344);
// //     else if(zz>20 && zz<=25) bkshape->SetBinContent(zz,1.6450);
// //     else if(zz>25 && zz<=35) bkshape->SetBinContent(zz,0.9064);
// //     else if(zz>35 && zz<=45) bkshape->SetBinContent(zz,0.1500);
// //     else if(zz>45 && zz<=55) bkshape->SetBinContent(zz,0.1330);
// //     else if(zz>55 && zz<=75) bkshape->SetBinContent(zz,0.0299);
// //     else if(zz>75 && zz<=95) bkshape->SetBinContent(zz,0.0050);
// //     else if(zz>95 && zz<=125) bkshape->SetBinContent(zz,0.0017);
// //     else if(zz>125 && zz<=300) bkshape->SetBinContent(zz,0.0001);
// //     else if(zz>300) bkshape->SetBinContent(zz,0);
    
// //   }
  
  bkshape->Scale(235.718/bkshape->Integral());
 sig->Scale((data->Integral(1,20)-bkshape->Integral(1,20))/sig->Integral(1,20));

  //bkshape->Scale(data->Integral()*0.75/(bkshape->Integral()));
 
  // sig->Scale((data->Integral())/sig->Integral());


  TCanvas* c2=new TCanvas("c2","c2",800,800);
  c2->SetLeftMargin(0.18);
  
  THStack* s2=new THStack();
  bkshape->SetFillColor(kRed);
  s2->Add(bkshape);
  s2->Add(sig);
  data->SetMarkerStyle(21);

  TLegend* tl=new TLegend(0.32,0.72,0.73,0.9);
  tl->SetFillStyle(0);
  tl->AddEntry(data,"Data","PL");
  tl->AddEntry(sig,"Signal (MC)","F");
  tl->AddEntry(bkshape,"Background (Fit)","F");

  s2->SetMaximum(data->GetMaximum()*1.5);
  
  s2->Draw("HIST");
  s2->GetXaxis()->SetTitle("P_{T} [GeV]");
  s2->GetYaxis()->SetTitle("Candidates/2 GeV");
  s2->GetYaxis()->SetTitleOffset(1.5);
  s2->GetXaxis()->CenterTitle();
  data->Draw("E SAME");

  tl->Draw();

  zrap_Prelim(0.80,0.977);
  zrap_Lumi(0.80,0.90,36);
  // c2->Print("~/public_html/talk/Z_CompareFINAL_80-HF_Pt_bkgd.eps");
  //c2->Print("~/public_html/talk/bkgcompare/Z_CompareFINAL_80-95_Pt_bkgd.eps");


}

