#include "tdrstyle.C"
#include "zrapidityStandard.C"

void etaCompare(TFile* sigf, TFile* zfd_bkgd, TFile* zfd_final) {
  setTDRStyle();
  const double weight=1.0/(1350);
  char name[200];
  sprintf(name,"ZFromData/ECAL80-ECAL95/C08-m(60,120)/mZ_vs_e2_eta");
  TH2* bkshape=zfd_bkgd->Get(name)->Clone("bkgd");
  TH2* data=zfd_final->Get(name)->Clone("data");
  sprintf(name,"mcEff/ECAL80-ECAL95/C08-m(60,120)/mZ_vs_e2_eta");
  TH2* sig=sigf->Get(name)->Clone("sig");
  sprintf(name,"ZFromData/ECAL80-ECAL95/C08-m(60,120)/mZ_vs_e1_eta");
  TH2* bkshape1=zfd_bkgd->Get(name)->Clone("bkgd");
  TH2* data1=zfd_final->Get(name)->Clone("data");
  sprintf(name,"mcEff/ECAL80-ECAL95/C08-m(60,120)/mZ_vs_e1_eta");
  TH2* sig1=sigf->Get(name)->Clone("sig");

  TH1* data1d=data->ProjectionX("dx");
  data1d->Add(data1->ProjectionX("dx1"));
  TH1* sig1d=sig->ProjectionX("sx");
  sig1d->Add(sig1->ProjectionX("sx1"));
  sig1d->Scale(weight);
  TH1* bkg1d=sig1d->Clone("bx");
  bkg1d->SetFillColor(kRed);
  bkg1d->SetFillStyle(1001);


  TCanvas* c1=new TCanvas("c1","c1",900,800);
  c1->Divide(5,4);

  int ib=1;
  for (int i=1; i<=data->GetNbinsX(); i++) {
    bkg1d->SetBinContent(i,0);
    sprintf(name,"dy%d",i);
    TH1* sld=data->ProjectionY(name,i,i);
    if (i>=11 && i<=40) sld=data1->ProjectionY(name,i,i);
    if (sld->Integral()<1) continue;

    sprintf(name,"by%d",i);
    TH1* slbk=bkshape->ProjectionY(name,i-1,i+1);
    if (i>=11 && i<=40) slbk=bkshape1->ProjectionY(name,i-1,i+1);
    sprintf(name,"sy%d",i);
    TH1* sls=sig->ProjectionY(name,i,i);
    if (i>=11 && i<=40) sls=sig1->ProjectionY(name,i,i);

    if (slbk->Integral(1,17)<1 || sld->Integral(1,17)<1) continue;
    c1->cd(ib); ib++;
    

    double factor=0.007*sls->Integral()/sls->Integral(1,20);
    
    //    if (i<11 || i>39) factor=0.75;
    //factor=0.75;
    slbk->Scale(sld->Integral(1,20)*factor/slbk->Integral(1,20));
   
    //    if (i==14 || i==15 ) slbk->Scale(4.0);
 
    double oldSLS=sls->Integral();

    sls->Scale((sld->Integral(25,35)-slbk->Integral(25,35))/sls->Integral(25,35));

    slbk->SetMaximum(sld->GetMaximum()*1.5);


    sld->Draw("E");


    THStack* s1=new THStack();
    s1->Add(slbk);
    s1->Add(sls);
    s1->Draw("SAME HIST");

    double berr=slbk->Integral()/sqrt(sld->Integral(1,17));    
    printf("%d  Factor: %f   Background: %.2f +/- %.2f \n",i,oldSLS/sls->Integral(),slbk->Integral(), berr);

    bkg1d->SetBinContent(i,slbk->Integral());
    bkg1d->SetBinError(i,berr);
    //   sig1d->SetBinContent(i,sls->Integral());
    data1d->SetBinError(i,sqrt(berr*berr+pow(data1d->GetBinError(i),2)));
  }


  TCanvas* c2=new TCanvas("c2","c2",800,800);
  c2->SetLeftMargin(0.18);
  THStack* s2=new THStack();
  bkg1d->SetFillColor(kRed);
  s2->Add(bkg1d);
  s2->Add(sig1d);
  data1d->SetMarkerStyle(21);

  TLegend* tl=new TLegend(0.32,0.72,0.73,0.9);
  tl->SetFillStyle(0);
  tl->AddEntry(data1d,"Data","PL");
  tl->AddEntry(sig1d,"Signal (MC)","F");
  tl->AddEntry(bkg1d,"Background (Fit)","F");

  s2->SetMaximum(data1d->GetMaximum()*1.5);
  s2->Draw("HIST");
  s2->GetXaxis()->SetRangeUser(-5.0,5.0);
  s2->GetXaxis()->SetTitle("Electron #eta");
  s2->GetYaxis()->SetTitle("Candidates/0.2");
  s2->GetYaxis()->SetTitleOffset(1.5);
  s2->GetXaxis()->CenterTitle();
  data1d->Draw("E SAME");

  tl->Draw();

  zrap_Prelim(0.80,0.977);
  zrap_Lumi(0.80,0.90,36);
  c2->Print("~/public_html/talk/Z_CompareFINAL_ECAL80-ECAL95_e_eta_bkgd.eps");
}

