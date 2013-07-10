//#include <iostream.h> 
//#include <stdlib.h>

// In this example, you pick up migration matrix from a file from the standard EffAcc (effAccSource.root),
// produce an unsmearing matrix and save it to a file (for usage with readUnfoldingMatrices.C)
// this macro works as well for Rapidity and transverse momentum, you have to choose when you launch it
// note if you want to _read_ the code: for how this code developed (written initially for rapidity)
// somewhere the 'variable' which is to be unsmeared is referred to as 'rapidity',
// while the macro consistently works for both Pt and Y

// to execute this example
//     root -l
//root [0] .L makeUnfoldingMatrices.C 
// if you want to produce a RAPIDITY unfolding matrix:
//root [1] makeUnfoldingMatrices("effAcc-V00-05-05/BASE.py.hadded.root","pincopincopFriday.root","Y");
// if you want to produce a TRANSVERSE MOMENTUM unfolding matrix:
//root [1] makeUnfoldingMatrices("effAcc-V00-05-05/BASE.py.hadded.root","pincopincopFriday.root","pt");

#include <TDatime.h>

#include "tdrstyle.C"
#include "zrapidityStandard.C"



template <class T> const T& max ( const T& a, const T& b ) {
  //std::cout << "max of " << a<< " and " << b << std::endl;
  return (b<a)?a:b;     // or: return comp(b,a)?a:b; for the comp version
}

template <class T> const T& min ( const T& a, const T& b ) {
  //std::cout << "min of " << a<< " and " << b << std::endl;
  return (b>a)?a:b;     // or: return comp(b,a)?a:b; for the comp version
}



int makeUnfoldingMatrices(std::string effAccFileInputFile, std::string unfoldingMatrixOutPutFile, std::string variable) 
{

  bool isRapidity(true);
  if (variable==std::string("Y")){
	std::cout << "\n\tyou have chosen Y. \n\tI'll make Y and |Y| unfolding matrices." << std::endl;
  }  
  else if (variable==std::string("pt")){
	std::cout << "\n\tyou have chosen pt" << std::endl;
	isRapidity=false;
  }
  else{
	std::cout << "not done a valid choice of variable. Bailing out" << std::endl;
	return 0;
  }

  setTDRStyle();
  zrap_colors();

  //gStyle->SetPalette(1);
  gStyle->SetPaintTextFormat(".2f");
  gStyle->SetOptStat(0);
  
  std::cout << "\n\n\tGetting migration matrices from: " << effAccFileInputFile          << std::endl;
  std::cout << "\tCreating unfolding matrices in:  "     << unfoldingMatrixOutPutFile <<"\n\n"<< std::endl;
  
  TFile *theEffAccInpuntFile = new TFile(effAccFileInputFile.c_str());
  //theEffAccInpuntFile->ls();
  
  TFile *theunfoldingMatrixOutpuFile = new TFile(unfoldingMatrixOutPutFile.c_str(),"recreate");
  theunfoldingMatrixOutpuFile ->cd();

  // directory where one saves the original histograms (from EffAcc calculator) the unfolding matrices have been obtained from
  TDirectory *originalHistograms = theunfoldingMatrixOutpuFile->mkdir("originalHistograms");
  originalHistograms->cd();
  
  gStyle->SetOptStat(110011);
  
  //////////////////////////////////////////////////////
  // to be consistent with the definitions 
  // of AN-10-367/AN-11-xxx one needs to use the YZTL_vs_YZ/PtTL_vs_PtZ before Eff and Acc
  // are applied ==> move to the "All" folder
  

  // at least for PT this is the way to go  
  std::string prefix("mcEff/");
  std::string definition=std::string("MUON-MUON-G20");
  std::string cut("C01-GPT20/");
  std::string plot=std::string("YZTL_vs_YZ"); // bin migration histogram for rapidity

  if(isRapidity) {
    // so far Thu Apr 28 17:36:57 CEST 2011 matrices were done like this:
    prefix = std::string("mcEff/");
    definition=std::string("All");
    cut = str::string("");
    //definition=std::string("ECAL80-ECAL95");
    //std::string cut("C01-PT10/");
    plot=std::string("YZTL_vs_YZ"); // bin migration histogram for rapidity
  }
  else{
    plot=std::string("PtTL_vs_PtZ"); // bin migration histogram for Pt
    std::string cut("C01-GPT20/");
    definition=std::string("MUON-MUON-G20");
  }
  std::string plotName = prefix + definition;
  plotName = plotName + std::string("/");    plotName = plotName + cut;
  /*plotName = plotName + std::string("/");*/    plotName = plotName + plot;
  std::cout << "\tUsing directly the total plot:     "<< plotName << endl;
  TH2F * histoMigration  = (TH2F*) theEffAccInpuntFile->Get(plotName.c_str());
  TH2F * histoMigrationFolded; // this is for folded rapidity matrix 

  int binsXMatrixEcalEcal = histoMigration->GetNbinsX();
  int binsYMatrixEcalEcal = histoMigration->GetNbinsY();
  float xminEcalEcal = histoMigration->GetXaxis()->GetXmin();
  float xmaxEcalEcal = histoMigration->GetXaxis()->GetXmax();
  float yMinEcalEcal = histoMigration->GetYaxis()->GetXmin();
  float yMaxEcalEcal = histoMigration->GetYaxis()->GetXmax();

   if(isRapidity){
   histoMigration->GetXaxis()->SetTitle("Y_{reco}");
   histoMigration->GetYaxis()->SetTitle("Y_{ZtreeLevel}");

   // set up the |Y| matrix
   histoMigrationFolded = new TH2F("YZTL_vs_YZ_folded","YZTL_vs_YZ_folded",binsXMatrixEcalEcal/2.,0,xmaxEcalEcal,binsYMatrixEcalEcal/2.,0,yMaxEcalEcal);
   histoMigrationFolded->GetXaxis()->SetTitle("|Y_{reco}|");
   histoMigrationFolded->GetYaxis()->SetTitle("|Y_{ZtreeLevel}|");

   for(int v=1; v<=binsXMatrixEcalEcal/2.; v++){
     for(int u=1; u<=binsXMatrixEcalEcal/2.; u++){
       histoMigrationFolded->SetBinContent(v,u,0);
     }}
   histoMigrationFolded->Reset();
   
   for(int v=1; v<=histoMigration->GetNbinsX(); v++){
     for(int u=1; u<=histoMigration->GetNbinsY(); u++){
       int        foldedX = 51-v;
       if (v>50)  foldedX = v-50;
       int        foldedY = 51-u;
       if (u>50)  foldedY = u-50;
       float theX = histoMigrationFolded->GetXaxis()->GetBinCenter(foldedX); 
       float theY = histoMigrationFolded->GetYaxis()->GetBinCenter(foldedY); 
       histoMigrationFolded->Fill( theX,
				   theY,
				   histoMigration->GetBinContent(v,u) );
       if ( histoMigration->GetBinContent(v,u) > 0){
	 //	 std::cout << v << "\t"<< u<< "\tfoldedX: " << foldedX << "\tfoldedY: " << foldedY 
	 //		   << "\t" <<  theX << "\t" << theY
	 //		   << "\t content: " <<  histoMigration->GetBinContent(v,u)<< "\t" <<  histoMigrationFolded->GetBinContent(v,u)
	 //		   << std::endl;       
       }
     }
   }
   }
   else
     {
       histoMigration->GetXaxis()->SetTitle("q_{T,reco} [GeV/c]");
       histoMigration->GetYaxis()->SetTitle("q_{T,ZtreeLevel} [GeV/c]");
       histoMigration->GetXaxis()->SetTitleOffset(1.3);
       histoMigration->GetYaxis()->SetTitleOffset(1.4);
     }

   TH2F * histoMigrationTotal_toBeSaved       = histoMigration->Clone();
   histoMigrationTotal_toBeSaved->Write("originalHistoMigrationTotal");
   if(isRapidity){
     TH2F * histoMigrationTotalFolded_toBeSaved = histoMigrationFolded->Clone();
   histoMigrationTotalFolded_toBeSaved->Write("originalHistoMigrationTotalFolded");
   }

   // build verification histograms
   std::string histoMigrationTitle("");
   std::string histoMigrationFoldedTitle("");
   std::string theEffectTitle("");
   std::string theEffectTitleFolded("");
  
   {
	histoMigrationTitle = std::string("Pt TreeLevel");
        theEffectTitle = std::string("Pt migration");
   }
   TH1D * h_RapidityTreeLevel = h0->ProjectionY(h0Title.c_str(),0,-1,"");
   TH1D * h_RapidityTreeLevelFolded;
  
   else  { h0->SetTitle("PtTreeLevel");}
   
   TH1D * h_RapidityTreeLevel_toSave =  h_RapidityTreeLevel->Clone();  
   TH1D * h_RapidityTreeLevelFolded_toSave;  
     {     h_RapidityTreeLevel_toSave->Write("original1dTreeLevelPt");}

   TH1D * h_RapiditySmeared   = h0->ProjectionX("Rapidity Smeared",0,-1,"");
   TH1D * h_RapiditySmearedFolded;
             h_RapiditySmeared->SetTitle("PtSmeared");


   //h_RapiditySmeared      ->SetLineColor(2);
   //h_RapiditySmearedFolded->SetLineColor(2);
   TH1D * h_RapiditySmeared_toSave =  h_RapiditySmeared->Clone();
   TH1D * h_RapiditySmearedFolded_toSave;
     {         h_RapiditySmeared_toSave->Write("original1dSmearedPt");}
   
   //TH1D * h_effect = new TH1D("Y migration","Y migration",binsXMatrixEcalEcal,xminEcalEcal,xmaxEcalEcal); 
   TH1D * h_effect = h_RapiditySmeared->Clone(theEffectTitle.c_str());
   h_effect->Reset();
   h_effect->Add(h_RapiditySmeared, h_RapidityTreeLevel, 1, -1);
   h_effect->Divide(h_RapidityTreeLevel);
   h_effect->SetTitle("(smeared-true)/true");
   h_effect->SetStats(0);
   TH1D * h_effectFolded;
   if(isRapidity) {
     h_effectFolded = (TH1D*)h_RapiditySmearedFolded->Clone(theEffectTitleFolded.c_str());
     h_effectFolded->Reset();
     h_effectFolded->Add(h_RapiditySmearedFolded, h_RapidityTreeLevelFolded, 1, -1);
     h_effectFolded->Divide(h_RapidityTreeLevelFolded);
     h_effectFolded->SetTitle("|Y|: (smeared-true)/true");
     h_effectFolded->SetStats(0);
   }

   TH2F * histoMatrix  = h0->Clone("Migration matrix");
   histoMatrix->Reset();
   TH2F * histoMatrixFolded;
     {
   histoMatrix->GetXaxis()->SetTitle("q_{T,reco} [GeV/c]");
   histoMatrix->GetYaxis()->SetTitle("q_{T,true} [GeV/c]");
   histoMatrix->GetXaxis()->SetTitleOffset(1.3);
   histoMatrix->GetYaxis()->SetTitleOffset(1.4);
   }




   /////////////////////////////////////////////////////////////////////////
   // take care of inverting full matrices;
   // the case of the folded rapidity |Y| is treated separately below
   /////////////////////////////////////////////////////////////////////////
   float integral=0;
   for(int binY=1; binY<=h0->GetNbinsY(); binY++)
     {
       integral=0;
       
       for(int binX=1; binX<=h0->GetNbinsX(); binX++)
       {
        integral+=h0->GetBinContent(binX,binY);
       }// binX

       if (integral==0) continue;

       // histomatrix has rows all normalized to 1
       // x-> reco; y-> true; => sum(y=const) has to be =1 , for probabilty conservation
       // note that in modern version of EffxAcc code there's an _matrix histogram which is normalize..
       for(int binX=1; binX<=binsXMatrixEcalEcal; binX++)
       {
        histoMatrix->SetBinContent(binX,binY, 1.*h0->GetBinContent(binX,binY)/integral );
       }// binX

    }// binY
   

   int limitNumberBinX(50); // number of bins which are kept for |Y| 
   int limitNumberBinY(50); // for Y, bins will be the double, automatically
   if(isRapidity){// pipp0
     limitNumberBinX=35;
     limitNumberBinY=35;
     //limitNumberBinX=50;
     //limitNumberBinY=50;
     int a=313;
   } else {
     limitNumberBinX=19;
     limitNumberBinY=19;
   }

   int lowestBinX      = histoMatrix->GetNbinsX()/2 - min(histoMatrix->GetNbinsX()/2, limitNumberBinX);
   int highestBinX     = histoMatrix->GetNbinsX()/2 + min(histoMatrix->GetNbinsX()/2, limitNumberBinX);
   int lowestBinY      = histoMatrix->GetNbinsY()/2 - min(histoMatrix->GetNbinsY()/2, limitNumberBinY);
   int highestBinY     = histoMatrix->GetNbinsY()/2 + min(histoMatrix->GetNbinsY()/2, limitNumberBinY);
   if(!isRapidity){
     lowestBinX = 0;     lowestBinY = 0;
     highestBinX =limitNumberBinX;      highestBinY = limitNumberBinY; 
   }
   std::cout << "\n++ limitNumberBinX: " << limitNumberBinX << " lowestBinX: " << lowestBinX << " highestBinX: " << highestBinX << std::endl;
   std::cout << "++ limitNumberBinY: " << limitNumberBinY << " lowestBinY: " << lowestBinY << " highestBinY: " << highestBinY << std::endl;


   int counter(0);
   // double migration[1936];//array reordering histoMatrix, to construct TMatrix
   double migration[10000];    //array reordering histoMatrix, to construct TMatrix
                               // this has to be hard-coded
   //for (int u=0; u<histoMatrix->GetNbinsX(); u++){//rows
   //for (int v=0; v<histoMatrix->GetNbinsX(); v++){//col

     for (int u=lowestBinX; u<highestBinX; u++){//rows
     for (int v=lowestBinY; v<highestBinY; v++){//col

       migration[counter]=histoMatrix->GetBinContent(u+1,v+1);

       // for matrix to be invertible, no diagonal elements can be 0
       // for now set, in all rows which are empty, the diagonal element to 1
       if(u==v && histoMatrix->GetBinContent(u+1,v+1)==0) migration[counter]=1;
       if(0 &&  migration[counter]!=0)  std::cout << u << " " << v << " " << migration[counter] <<std::endl;

       counter++;

       }	
     }
     
     //http://root.cern.ch/root/html/tutorials/matrix/invertMatrix.C.html
     //this is the smearing matrix: it multiplies the unsmeared vector to give the smeared vector
  gSystem->Load("libMatrix");
  //TMatrixD MigrationMatrix(0, histoMatrix->GetNbinsX()-1, 0, histoMatrix->GetNbinsX()-1, migration,"");
  TMatrixD MigrationMatrix(0, (highestBinX-lowestBinX)-1, 0, (highestBinY-lowestBinY)-1, migration,"");

  // directory where one saves the matrices
  TDirectory *unsmearMatrices = theunfoldingMatrixOutpuFile->mkdir("unsmearMatrices");
  unsmearMatrices->cd();
  TMatrixD inverseMigrationMatrix = MigrationMatrix;

  Double_t determinant;
  inverseMigrationMatrix.Invert(&determinant);

  // this is the name I assign to the unfolding matrix for all Z candidates: ECAL-ECAL and ECAL-HF
  inverseMigrationMatrix.Write("unfoldingMatrixTotal");
  /////////////////////////////////////////////////////////////////////////







  /////////////////////////////////////////////////////////////////////////
  std::string tableFileName; 
  if(isRapidity) tableFileName=std::string("migration_table_Y.tex");
  else           tableFileName=std::string("migration_table_Pt.tex");

  //FILE* texTable=fopen("migration_table.tex","wt");
  FILE* texTable=fopen(tableFileName.c_str(),"wt");
  fprintf(texTable,"\\begin{tabular}{|cc||ccccc|} \\hline \n");
  
  else fprintf(texTable,"$min(q^\\mathrm{true}_{T,i})$ & $max(q^\\mathrm{true}_{T,i})$ & $q^\\mathrm{reco}_{T,i-2}$ & $q^\\mathrm{reco}_{T,i-1}$ & $q^\\mathrm{reco}_i$ & $q^\\mathrm{reco}_{T,i+1}$ & $q^\\mathrm{reco}_{T,i+2}$ \\\\ \\hline \n");
  //for (int i=0; i<h0->GetNbinsX(); i++) {
  for (int i=lowestBinX; i<highestBinX; i++) {
    double lv=h0->GetXaxis()->GetBinLowEdge(i+1);
    double lh=h0->GetXaxis()->GetBinUpEdge(i+1);

    if ((isRapidity) && ( fabs(lv)>3.5 || fabs(lh)>3.5)) continue;
    if ((!isRapidity) && ( fabs(lv)>250 || fabs(lh)>600)) continue;
    
    fprintf(texTable,"%5.2f & %5.2f & ",lv,lh);

    for (int j=-2; j<=2; j++) {
      int ireco=i+j-minbinx;
      if ((ireco)<0 || (ireco)>=(maxbinx-minbinx-1) ) {
      //      if ((ireco)<0 || (ireco)>=(70)) {
	fprintf(texTable," -- ");
	if (j!=2) fprintf(texTable," & ");
	else fprintf(texTable,"\\\\\n");
	continue;
    } else {
      fprintf(texTable,"%.2e",MigrationMatrix(ireco,i-lowestBinY));
	if (j!=2) fprintf(texTable," & ");
	else fprintf(texTable,"\\\\\n");
      }


    }
     
  }
  fprintf(texTable,"\\hline\n\\end{tabular}\n");  fclose(texTable);
  /////////////////////////////////////////////////////////////////////////

  //checking whether the inversion is sound: multiply matrix and its inverse, anche check if unity
  TMatrixD isThisUnity(inverseMigrationMatrix,TMatrixD::kMult,MigrationMatrix);
  // create reference to the diagonal and set the diagonal to 0
  TMatrixDDiag diag1(isThisUnity); diag1 = 0.0;
  const Double_t U1_max_offdiag = (isThisUnity.Abs()).Max();
  cout << "\n\n\n  Verification that inversion was ok: maximum off-diagonal A * A^-1 = " << U1_max_offdiag << " is it SMALL?\n\n "<< endl;

  Double_t arrayRapiditySmeared[100]; // this needs be hardcoded...
  int      counter_arrayRapiditySmeared(0);
  //  for(int bin=1; bin<=binsXMatrixEcalEcal; bin++)
  for(int bin=minbinx; bin<maxbinx; bin++)
  {
   arrayRapiditySmeared[counter_arrayRapiditySmeared]=h_RapiditySmeared->GetBinContent(bin+1);
   counter_arrayRapiditySmeared++;
   //arrayRapiditySmeared[bin-1]=h_RapiditySmeared->GetBinContent(bin);
  }


  //TVectorD vectorRapiditySmeared; vectorRapiditySmeared.Use(binsXMatrixEcalEcal,arrayRapiditySmeared);
  TVectorD vectorRapiditySmeared; vectorRapiditySmeared.Use( (maxbinx-minbinx) ,arrayRapiditySmeared);

  // this is the multiplication for clusure test
  TVectorD vectorRapidityUNSmeared = inverseMigrationMatrix * vectorRapiditySmeared;

  TH1D * h_RapidityUNSmeared = h_RapiditySmeared->Clone(theEffectTitle.c_str()); 
  h_RapidityUNSmeared->Reset();

  // turning the unsmeared vector into a histogram
  //  for(int bin=1; bin<=binsXMatrixEcalEcal; bin++)
  //    {
  for(int bin=minbinx; bin<maxbinx; bin++)
    {
      h_RapidityUNSmeared->SetBinContent(bin+1,vectorRapidityUNSmeared[bin-minbinx]);
      //std::cout << vectorRapidityUNSmeared[bin-1]<<std::endl;
    }



  //+++++++++++++++++++++++++++++++++++++++++++++++++++++++++
  if(1){//GF

    // http://ultrahigh.org/2007/08/20/making-pretty-root-color-palettes/

   TCanvas * c4 = new TCanvas("Migration histogram","Migration histogram",1050,750);
   c4->cd(1);  c4->SetLogz();     
   if(!isRapidity) {
   c4->SetLogx();   c4->SetLogy();
   }
   h0->SetTitle("Migration histogram");
   h0->SetTitle("Migration Total");
   h0->GetXaxis()->CenterTitle();
   h0->GetYaxis()->CenterTitle();
   h0->Draw("colz");
   c4->Print( (std::string("migration-total") + std::string(".png") ).c_str() );


   TCanvas * c4q = new TCanvas("c4q","c4q",1050,750);
   c4q->cd();
   h_effect->SetLineColor(2);
   h_effect->Draw();

   //new way of getting the time 
   const char* time_;
   TDatime *mytime = new TDatime();
   time_ = mytime->AsString();
   TText *plabel = new TText();
   plabel-> SetNDC();
   plabel -> SetTextFont(1);
   plabel -> SetTextColor(1);
   plabel -> SetTextSize(0.04);
   plabel -> SetTextAlign(22);
   plabel -> SetTextAngle(0);
   TText *tlabel = new TText();
   tlabel-> SetNDC();
   tlabel -> SetTextFont(1);
   tlabel -> SetTextColor(1);
   tlabel -> SetTextSize(0.02);
   tlabel -> SetTextAlign(22);
   tlabel -> SetTextAngle(0);
   std::cout << "\n\n The local time is: " << time_ << "\n\n" << std::endl;

   TCanvas * c5 = new TCanvas("migration matrix","migration matrix",1050,750);
   c5->SetTopMargin(0.02);
   c5->SetRightMargin(0.14);
   c5->SetLeftMargin(0.11);   
   c5->SetBottomMargin(0.125);
   c5->cd(1);  c5->SetLogz();   
   TH2F * dummyForRange = new TH2F("dummyForRange","dummyForRange",2,0,600,2,0,600);
   dummyForRange->GetXaxis()->CenterTitle();
   dummyForRange->GetYaxis()->CenterTitle(true);
   dummyForRange->GetYaxis()->SetTitleOffset(0.8);
   dummyForRange->SetStats(0);
    
   hMx->GetXaxis()->SetTitle("q_{T,reco} [GeV/c]");
   hMx->GetYaxis()->SetTitle("q_{T,true} [GeV/c]");
   hMx->GetXaxis()->SetTitleOffset(1.3);
   hMx->GetYaxis()->SetTitleOffset(1.4);
   hMx->GetXaxis()->SetRangeUser(0.0001,600);
   hMx->GetYaxis()->SetRangeUser(0.0001,600);
   // dummyForRange->Draw();
   c5->SetLogx();   c5->SetLogy();
   
   hMx->GetXaxis()->CenterTitle();
   hMx->GetYaxis()->CenterTitle(true);
   hMx->GetYaxis()->SetTitleOffset(0.8);
   hMx->SetMaximum(1);
   hMx->SetStats(0);
   //hMx->Draw("colz same");
   hMx->Draw("colz");
   plabel -> DrawText(0.30, 0.93, "CMS preliminary 2010");
   tlabel -> DrawText(0.30, 0.90, Form("%s",time_));
   hMx->SetTitle("Migration matrix (normalized)");
   c5->Print("migrationMatrix.png");
   c5->Print("migrationMatrix.eps");
   c5->Print("migrationMatrix.pdf");


   TCanvas * c7pre = new TCanvas("closure test","closure test",1050,750);
   
   //c7pre->SetLogx();   c7pre->SetLogy();
   
   c7pre->cd();
   h0_py->SetLineWidth(2);//this is black for now
   h0_py->GetYaxis()->SetTitle("events");
   h0_py->SetTitle(0);
   h0_py->Draw("");//this is black for now
  
   h_UNSmeared->SetMarkerColor(4);
   h_UNSmeared->SetMarkerStyle(20);
   h_UNSmeared->SetMarkerSize(0.7);
   h_UNSmeared->SetLineWidth(1);
   h_UNSmeared->Draw("sameAP");

   TH1F *h0_pxDummy = new TH1F("a","b",10,0,10);
   h0_pxDummy->SetMarkerColor(3);
   h0_pxDummy->SetMarkerStyle(23);
   h0_pxDummy->SetMarkerSize(1.5);
   TH1F * h_UNSmearedDummy = new TH1F("c","d",10,0,10);
   h_UNSmearedDummy->SetMarkerColor(4);
   h_UNSmearedDummy->SetMarkerStyle(20);
   h_UNSmearedDummy->SetMarkerSize(1.5);
   
   h0_px->SetMarkerColor(2);
   h0_px->SetMarkerStyle(23);
   h0_px->SetMarkerSize(0.75);
   h0_px->Draw("sameAP");
   
   TLegend* leg = new TLegend(0.1,0.7,0.30,0.9);
   leg->SetHeader("Z Rapidity");
   leg->AddEntry(h_RapiditySmeared,"Y_{Z} smeared","p");
   leg->AddEntry(h0_py,"Y_{Z} treeLevel","l");
   leg->AddEntry(h_UNSmeared,"Y_{Z} unsmeared (overlap?)","p");
   leg->Draw();

   ///////////////////////////////////////////////////////
   c7pre->Print("rapdity-Tree-Smear-Unsmear-Closure.png");
   ///////////////////////////////////////////////////////

  }// end of switch on/off plotting of many canvases
  //+++++++++++++++++++++++++++++++++++++++++++++++++++++++++


   TH1D * h_effectUnsmearing       = new TH1D("Y unsmearing","Y unsmearing",binsXMatrixEcalEcal,xminEcalEcal,xmaxEcalEcal); 
   TH1D * h_effectUnsmearingByHand = new TH1D("Y unsmearing BH","Y unsmearing BH",binsXMatrixEcalEcal,xminEcalEcal,xmaxEcalEcal); 
   h_UNSmeared->Sumw2();
   h0_py->Sumw2();
   h_effectUnsmearing->Add(h_UNSmeared, h0_py, 1, -1);
   h_effectUnsmearing->Divide(h0_py);
   h_effectUnsmearing->SetTitle(0);
   for(int a=1; a<=binsXMatrixEcalEcal; a++){
     if(h0_py->GetBinContent(a)>1){
     h_effectUnsmearingByHand->SetBinContent(a,(h_UNSmeared->GetBinContent(a)-h0_py->GetBinContent(a))/h0_py->GetBinContent(a));
     }
   }
  
     TCanvas * c8 = new TCanvas("closure test: (UNsmeared-true)/true","closure test: (UNsmeared-true)/true",1050,750);
     c8->cd();
     //h_effectUnsmearing->Draw();
     // h_effectUnsmearingByHand->Draw("e hpx HIST");
     h_effectUnsmearingByHand->Draw("hpx HIST");
   
  
   c8->Print("UNsmeared-true-over-true-Closure.png");

   //////////////////////////////////////////////////////////////////////////////////////////////
   //checking whether the FOLDED inversion is sound: multiply matrix and its inverse, anche check if unity    

   
   

  //+++++++++++++++++++++++++++++++++++++++++++++++++++++++++
    
    
  
   
  
  //+++++++++++++++++++++++++++++++++++++++++++++++++++++++++

   

   //}// end special operations in case of rapidity, for FOLDED distribution



}
