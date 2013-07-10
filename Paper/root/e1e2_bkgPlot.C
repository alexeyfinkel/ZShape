#include "tdrstyle.C"
#include "zrapidityStandard.C"

void e1e2_bkgPlot(TFile* sigf, TFile* zfd_bkgd, TFile* zfd_final) {
  setTDRStyle();
  const double weight=1.0/(2100);
  char name[200];
  //sprintf(name,"ZFromData/ECAL80-HF/C08-m(60,120)/e1_P_t");
   sprintf(name,"ZFromData/ECAL80-ECAL95/C08-m(60,120)/e1_P_t");
 //sprintf(name,"ZFromData/ECAL80-HF/C08-m(60,120)/e2_P_t");
   // sprintf(name,"ZFromData/ECAL80-ECAL95/C08-m(60,120)/e2_P_t");
 //   sprintf(name,"ZFromData/ECAL80-HF/C08-m(60,120)/e_eta");
   // sprintf(name,"ZFromData/ECAL80-ECAL95/C08-m(60,120)/e_eta");
 //   sprintf(name,"ZFromData/ECAL80-HF/C08-m(60,120)/e_phi");
   // sprintf(name,"ZFromData/ECAL80-ECAL95/C08-m(60,120)/e_phi");
 //   sprintf(name,"ZFromData/ECAL80-HF/C08-m(60,120)/e1_eta");
   // sprintf(name,"ZFromData/ECAL80-ECAL95/C08-m(60,120)/e1_eta");
 //   sprintf(name,"ZFromData/ECAL80-HF/C08-m(60,120)/e2_eta");
   // sprintf(name,"ZFromData/ECAL80-ECAL95/C08-m(60,120)/e2_eta");

  TH1* bkshape=zfd_bkgd->Get(name)->Clone("bkgd");
  TH1* data=zfd_final->Get(name)->Clone("data");
  //   sprintf(name,"mcEff/ECAL80-HF/C08-m(60,120)/e1_P_t");
   sprintf(name,"mcEff/ECAL80-ECAL95/C08-m(60,120)/e1_P_t");
 //   sprintf(name,"mcEff/ECAL80-HF/C08-m(60,120)/e2_P_t");
   // sprintf(name,"mcEff/ECAL80-ECAL95/C08-m(60,120)/e2_P_t");
 //   sprintf(name,"mcEff/ECAL80-HF/C08-m(60,120)/e_eta");
   // sprintf(name,"mcEff/ECAL80-ECAL95/C08-m(60,120)/e_eta");
 //   sprintf(name,"mcEff/ECAL80-HF/C08-m(60,120)/e_phi");
   // sprintf(name,"mcEff/ECAL80-ECAL95/C08-m(60,120)/e_phi");
 //   sprintf(name,"mcEff/ECAL80-HF/C08-m(60,120)/e1_eta");
   // sprintf(name,"mcEff/ECAL80-ECAL95/C08-m(60,120)/e1_eta");
 //   sprintf(name,"mcEff/ECAL80-HF/C08-m(60,120)/e2_eta");
   // sprintf(name,"mcEff/ECAL80-ECAL95/C08-m(60,120)/e2_eta");

  TH1* sig=sigf->Get(name)->Clone("sig");

    
  bkshape->Scale((data->Integral(1,8)*0.75+data->Integral(40,50)*0.75)/(bkshape->Integral(1,8)+bkshape->Integral(40,50)));
 
  sig->Scale((data->Integral(15,35)-bkshape->Integral(15,35))/sig->Integral(15,35));

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
  s2->GetXaxis()->SetTitle("P_{T},e1 [GeV]");
  s2->GetYaxis()->SetTitle("Candidates/2 GeV");
  s2->GetYaxis()->SetTitleOffset(1.5);
  s2->GetXaxis()->CenterTitle();
  data->Draw("E SAME");

  tl->Draw();

  zrap_Prelim(0.80,0.977);
  zrap_Lumi(0.80,0.90,36);
  // c2->Print("~/public_html/talk/Z_CompareFINAL_ECAL80-HF_mee_bkgd.eps");
  // c2->Print("~/public_html/talk/hf.eps");
   c2->Print("~/public_html/talk/Ecal_e1_ptbkg.eps");


}

