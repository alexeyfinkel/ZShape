#include "tdrstyle.C"
#include "zrapidityStandard.C"

void bkgPTCompare(const char* item, TFile* sigf, TFile* zfd_bkgd, TFile* zfd_final) {

  setTDRStyle();
  const double weight=1.0/(1350);
  char name[200];
  // sprintf(name,"ZFromData/ECAL80-ECAL95/C08-m(60,120)/mZ_vs_%s",item);
  sprintf(name,"ZFromData/ECAL80-ECAL95/C08-m(60,120)/Z0_%s_v_mass",item);

  TH2* bkshape=zfd_bkgd->Get(name)->Clone("bkgd");
  TH2* data=zfd_final->Get(name)->Clone("data");
  // sprintf(name,"mcEff/ECAL80-ECAL95/C08-m(60,120)/mZ_vs_%s",item);
  sprintf(name,"mcEff/ECAL80-ECAL95/C08-m(60,120)/Z0_%s_v_mass",item);

  TH2* sig=sigf->Get(name)->Clone("sig");

  TH1* data1d=data->ProjectionX("dx");
  TH1* sig1d=sig->ProjectionX("sx");
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
    if (sld->Integral()<1) continue;

    sprintf(name,"by%d",i);
    TH1* slbk=bkshape->ProjectionY(name,i-1,i+1);
    sprintf(name,"sy%d",i);
    TH1* sls=sig->ProjectionY(name,i,i);

    c1->cd(ib); ib++;
    
    //  if (slbk->Integral(1,17)<1 || sld->Integral(1,17)<1) continue;
 if (slbk->Integral(1,51)<1 || sld->Integral(1,51)<1) continue;


    slbk->Scale(sld->Integral(1,51)/slbk->Integral(1,51));
    if (i==9 || i==42) slbk->Scale(2.0);
 
    double oldSLS=sls->Integral();
    //25/35
    sls->Scale((sld->Integral(75,105)-slbk->Integral(75,105))/sls->Integral(75,105));

    slbk->SetMaximum(sld->GetMaximum()*1.5);

    sld->Draw("E");


    THStack* s1=new THStack();
    s1->Add(slbk);
    s1->Add(sls);
    s1->Draw("SAME HIST");
   
    double berr=slbk->Integral()/sqrt(sld->Integral(1,51));    
    printf("%d  Factor: %f   Background: %.2f +/- %.2f \n",i,oldSLS/sls->Integral(),slbk->Integral(), berr);
   
    bkg1d->SetBinContent(i,slbk->Integral());
    bkg1d->SetBinError(i,berr);
    //    sig1d->SetBinContent(i,sls->Integral());
    data1d->SetBinError(i,sqrt(berr*berr+pow(data1d->GetBinError(i),2)));
  }
 
 data1d->SetMarkerStyle(21);
  TCanvas* c2=new TCanvas("c2","c2",800,800);
  c2->SetLeftMargin(.18);
  THStack* s2=new THStack();
  s2->SetMaximum(data1d->GetMaximum()*1.5); 
  bkg1d->SetFillColor(kRed);
  s2->Add(bkg1d);
  s2->Add(sig1d);
  
 
  s2->Draw("HIST");
s2->GetXaxis()->SetRangeUser(18,100);
s2->GetXaxis()->SetTitle("Electron P_{T} [GeV]");
//s2->GetXaxis()->SetTitle("Electron #eta,e2");
  s2->GetYaxis()->SetTitle("Candidates GeV");
//s2->GetYaxis()->SetTitle("Candidates/0.20");
   s2->GetYaxis()->SetTitleOffset(1.35);
  s2->GetXaxis()->CenterTitle();
  data1d->Draw("E SAME");
  TLegend* tl=new TLegend(0.32,0.82,0.73,0.95);
  tl->SetFillStyle(0);
  tl->AddEntry(data1d,"Data","PL");
  tl->AddEntry(sig1d,"Signal (MC)","F");
  tl->AddEntry(bkg1d,"Background (Fit)","F");
  tl->Draw();
zrap_Prelim(0.80,0.977);
  zrap_Lumi(0.80,0.90,36);

  char stuff[1024];
  // sprintf(stuff,"~/public_html/talk/ECAL_mc_v_bkg_%s.eps",item);
  c2->Print(stuff);
  


}

