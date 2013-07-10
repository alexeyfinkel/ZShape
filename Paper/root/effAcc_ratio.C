EColor colorFor(int i) {
  switch (i) {
  case (0): return kBlack;
  case (1): return kRed;
  case (2): return kGreen+1;
  case (3): return kBlue;
  case (4): return kOrange;
  case (5): return kViolet-5;
  case (6): return kRed-6;
  default: return i+1;
  };

}

const char* labelFor(int i) {
  switch (i) {
  case(0) : return "Geometrical Acceptance";
  case(1) : return "Supercluster";
  case(2) : return "Supercluster with E_{T}>20 GeV";
  case(3) : return "Electron Reconstruction (Track)";
  case(4) : return "SKIPME";
  case(5) : return "Electron ID";
  case(6) : return "HLT";
  default : return "Huh?";
  }
}

#include "tdrstyle.C"
#include "zrapidityStandard.C"

void effAcc_ratio(TFile* f,TFile* f2, int mode=1) {

  const char* var="Z0_Pt_masscut";
  TDirectory* basedir=f->Get("mcEff");
  TDirectory* basedir2=f2->Get("mcEff");
  TH1* base=0, *base0=0, *base02=0, *base2=0;

  if (mode==1) {
    base=(TH1*)(((TDirectory*)basedir->Get("MUON-MUON-G20/C01-GPT20"))->Get(var));
    base2=(TH1*)(((TDirectory*)basedir2->Get("MUON-MUON-G20/C01-GPT20"))->Get(var));
    base0=(TH1*)(((TDirectory*)basedir->Get("MUON-MUON-G20/Acceptance"))->Get(var));
   base02=(TH1*)(((TDirectory*)basedir2->Get("MUON-MUON-G20/Acceptance"))->Get(var));
  
} else
    base=(TH1*)(((TDirectory*)basedir->Get("MUON-MUON/Acceptance"))->Get("Z0_PtTL_masscut"));

  TDirectory* zdir=basedir->Get("ECAL80-ECAL95-MUO");
 
  TList* cutz=zdir->GetListOfKeys();
 

  TDirectory* zdir2=basedir2->Get("ECAL80-ECAL95-MUO");
 
  TList* cutz2=zdir2->GetListOfKeys();
 
  gROOT->SetStyle("Plain");
  setTDRStyle();

  TCanvas* c1=new TCanvas("c1","c1",700,600);
  
  c1->cd();

  TLegend* tl;
  tl=new TLegend(0.15,0.2,0.75,0.45);
  tl->SetFillStyle(0);

  c1->SetTopMargin(0.05);
  c1->SetRightMargin(0.05);
  c1->SetBottomMargin(0.15);
  //  c1->SetRightMargin(0.05);

  TH1* final=0,*finalt=0;

  int n=0;
  for (int i=0; i<cutz->GetSize(); i++) {
    TH1* stage=((TDirectory*)zdir->Get(cutz->At(i)->GetName()))->Get(var);
    TH1* stage2=((TDirectory*)zdir2->Get(cutz2->At(i)->GetName()))->Get(var);
    char cleanname[256];
    char* pt=strchr(cutz->At(i)->GetName(),'-');
    if (pt!=0) strcpy(cleanname,pt+1);
    else strcpy(cleanname,cutz->At(i)->GetName());

    pt=strchr(cleanname,'-'); if (pt!=0) *pt=0;

    if (!strcmp(cleanname,"PT10")) continue;
    if (strstr(cleanname,"m(")!=0) continue;
    // if (!strcmp(cleanname,"PT20")) continue;
    printf("%d %s %s %p %p\n",n,cutz->At(i)->GetName(),cleanname,stage,pt);
    TH1* work=zpt_rebinForPlot(stage);
    TH1* rebase=zpt_rebinForPlot(base);
    TH1* work2=zpt_rebinForPlot(stage2);
    TH1* rebase2=zpt_rebinForPlot(base2);

    final=(TH1*)(stage->Clone());
    if (i==0)  {
      final->Divide(final,base0);
      rebase=zpt_rebinForPlot(base0);
      rebase2=zpt_rebinForPlot(base02);
    } else {
      final->Divide(final,base);
    }



   //  TH1* work2=base->Clone();

//     double w2f=0;
//     int w2fn=0;
//     for (int iii=-3; iii<=4; iii++) {
//       w2f+=work2->GetBinContent(work2->GetNbinsX()/2+iii);
//       w2fn++;
//     }
//     w2f/=w2fn;

//     work2->Scale(1.0/w2f);
    work->Divide(work,rebase);
    work2->Divide(work2,rebase2);
    work2->Divide(work2,work);
    work2->SetLineColor(colorFor(n));
    work2->SetLineWidth(2);
    if (i==0) {
      work2->GetYaxis()->SetTitle("Ratio of Efficiency #times Acceptance");
      work2->GetXaxis()->SetTitle(qt_xaxis_label);
      work2->GetYaxis()->SetTitleOffset(1.05);
      work2->SetTitle(0);
      work2->SetStats(false);
      work2->SetMaximum(1.00);
      work2->SetMinimum(0.5);
      if (strstr(var,"Y")!=0) {
	work2->GetXaxis()->SetRangeUser(-4.5,4.5);
      } else {
	work2->GetXaxis()->SetRangeUser(0.0,500.0);
      }
      work2->GetXaxis()->CenterTitle(true);
      work2->GetYaxis()->CenterTitle(true);
      work2->GetXaxis()->SetNoExponent(true);
      work2->GetXaxis()->SetMoreLogLabels(false);
      work2->Draw("HIST ][");
    } else if (n!=4 && n!=1) 
      work2->Draw("SAMEHIST ][");

    if (n==4 || n==1) { 
    } else if (n<3) 
      tl->AddEntry(work2,labelFor(n),"L");
    else
      tl->AddEntry(work2,labelFor(n),"L");
    
    n++;
    finalt=(TH1*)(work2->Clone());
  }
  tl->SetFillColor(0);
  tl->Draw("SAME");


  c1->SetLogx();

  zrap_Prelim(0.84,0.975,0.8,0.74);
  zqt_Cut(0.73,0.23,"e");

  char stuff[1024];
  //  sprintf(stuff,"eff_pt_bycut.png");
  //c1->Print(stuff);
  if (mode==1) sprintf(stuff,"eff_pt_bycut_smear_ratios.eps");
  if (mode==2) sprintf(stuff,"eff_pt_bycut_denomtl_ratios.eps");
  c1->Print(stuff);

 
  if (mode==1) {
    sprintf(stuff,"effAcc_pt_massCutdenom.txt");
  } else if (mode==2) {
    sprintf(stuff,"effAcc_pt_TLdenom.txt");
  } else return;
  // FILE* stats=fopen(stuff,"wt");

//   TDatime now;

//   fprintf(stats,"#Bin pt_min pt_max Eff %s\n",now.AsString());

//   for (int i=1; i<=finalt->GetNbinsX(); i++) {
//     fprintf(stats," %2d %5.2f %5.2f %.5f\n",i,finalt->GetBinLowEdge(i),finalt->GetBinWidth(i)+finalt->GetBinLowEdge(i),finalt->GetBinContent(i)); 
//   }
//   fclose(stats);

}
