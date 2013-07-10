
#include <TGraphAsymmErrors.h>
#include <time.h>
#include <TText.h>
#include <TROOT.h>
#include <TPaveLabel.h>
#include <TStyle.h>
typedef std::map<int, int> colors;
void makeHFEIdeff(){

TStyle *mystyle_;
 colors Cols_;
  colors Marker_;

  mystyle_ = new TStyle("mystyle","mystyle");

 Cols_[0] = kBlack;
   Cols_[1] = kRed;
   Cols_[2] = kMagenta;
   Cols_[3] = kBlue;
   Cols_[4] = kCyan+1;
   Cols_[5] = kGreen;
   Cols_[6] = kYellow+2;

   Marker_[0] = kOpenCircle;
   Marker_[1] = kOpenTriangleUp;
   Marker_[2] = kOpenSquare;
   Marker_[3] = kOpenStar;
   Marker_[4] = kOpenDiamond;
   Marker_[5] = kOpenCross;
   Marker_[6] = kOpenCircle;


// For the canvas:
  mystyle_->SetCanvasBorderMode(0);
  mystyle_->SetCanvasColor(kWhite);
  mystyle_->SetCanvasDefH(600); //Height of canvas
  mystyle_->SetCanvasDefW(600); //Width of canvas
  mystyle_->SetCanvasDefX(0);   //POsition on screen
  mystyle_->SetCanvasDefY(0);

// For the Pad:
  mystyle_->SetPadBorderMode(0);
  // mystyle_->SetPadBorderSize(Width_t size = 1);
  mystyle_->SetPadColor(kWhite);
  mystyle_->SetPadGridX(false);
  mystyle_->SetPadGridY(false);
  mystyle_->SetGridColor(0);
  mystyle_->SetGridStyle(3);
  mystyle_->SetGridWidth(1);

// For the frame:
  mystyle_->SetFrameBorderMode(0);
  mystyle_->SetFrameBorderSize(1);
  mystyle_->SetFrameFillColor(0);
  mystyle_->SetFrameFillStyle(0);
  mystyle_->SetFrameLineColor(1);
  mystyle_->SetFrameLineStyle(1);
  mystyle_->SetFrameLineWidth(1);

  mystyle_->SetAxisColor(1, "XYZ");
  mystyle_->SetStripDecimals(kTRUE);
  mystyle_->SetTickLength(0.03, "XYZ");
  mystyle_->SetNdivisions(510, "XYZ");
  mystyle_->SetPadTickX(1);  // To get tick marks on the opposite side of the frame
  mystyle_->SetPadTickY(1);
// For the axis titles:

  mystyle_->SetTitleColor(1, "XYZ");
  mystyle_->SetTitleFont(42, "XYZ");
  mystyle_->SetTitleSize(0.06, "XYZ");
  // mystyle_->SetTitleXSize(Float_t size = 0.02); // Another way to set the size?
  // mystyle_->SetTitleYSize(Float_t size = 0.02);
  mystyle_->SetTitleXOffset(0.9);
  mystyle_->SetTitleYOffset(1.25);
  // mystyle_->SetTitleOffset(1.1, "Y"); // Another way to set the Offset
// Margins:
  mystyle_->SetPadTopMargin(0.05);
  mystyle_->SetPadBottomMargin(0.13);
  mystyle_->SetPadLeftMargin(0.16);
  mystyle_->SetPadRightMargin(0.02);
// For the statistics box:
  mystyle_->SetOptFile(0);
  mystyle_->SetOptStat(0); // To display the mean and RMS:   SetOptStat("mr");
  mystyle_->SetStatColor(kWhite);
  mystyle_->SetStatFont(42);
  mystyle_->SetStatFontSize(0.025);
  mystyle_->SetStatTextColor(1);
  mystyle_->SetStatFormat("6.4g");
  mystyle_->SetStatBorderSize(1);
  mystyle_->SetStatH(0.1);
  mystyle_->SetStatW(0.15);
  mystyle_->SetPaperSize(20.,20.);

// For the Global title:

  mystyle_->SetOptTitle(0);
  mystyle_->SetTitleFont(42);
  mystyle_->SetTitleColor(1);
  mystyle_->SetTitleTextColor(1);
  mystyle_->SetTitleFillColor(10);
  mystyle_->SetTitleFontSize(0.05);

  mystyle_->SetLabelColor(1, "XYZ");
  mystyle_->SetLabelFont(42, "XYZ");
  mystyle_->SetLabelOffset(0.007, "XYZ");
  mystyle_->SetLabelSize(0.05, "XYZ");

  mystyle_->cd();



  TGraphAsymmErrors *myt1 = new TGraphAsymmErrors(1);
  TGraphAsymmErrors *myt2 = new TGraphAsymmErrors(2);
  TGraphAsymmErrors *myt3 = new TGraphAsymmErrors(2);
  TGraphAsymmErrors *myt4 = new TGraphAsymmErrors(2);
  TGraphAsymmErrors *myt5 = new TGraphAsymmErrors(2);
  TGraphAsymmErrors *myt6 = new TGraphAsymmErrors(2);
  TGraphAsymmErrors *myt7 = new TGraphAsymmErrors(1);
 
 TGraphAsymmErrors*  effgraphs_[10];  
  
  myt1->SetPoint(0,70, 0.5787);
  myt1->SetPointError(0,50,50,0.5787-0.5618, 0.5967-0.5787);
  effgraphs_[0]=(myt1);
  
  myt2->SetPoint(0,25,0.7621);
  myt2->SetPointError(0,5,5,0.7621-0.733,0.7937-0.7621);
  myt2->SetPoint(1,75,0.692);
  myt2->SetPointError(1,45,45,0.692-0.6813,0.7043-0.692);
  effgraphs_[1]=(myt2);
  
  myt3->SetPoint(0,25, 0.6529);
  myt3->SetPointError(0,5,5,0.6529-0.6276,0.6804-0.6529);
  myt3->SetPoint(1,75, 0.89);
  myt3->SetPointError(1,45,45,0.89-0.8777,0.9068-0.89);
  effgraphs_[2]=(myt3);
  effgraphs_[3]=(myt1);


  myt4->SetPoint(0,25,0.9279);
  myt4->SetPointError(0,5,5,0.9279-0.8797,0.9816-0.9279);
  myt4->SetPoint(1,75,0.8553);
  myt4->SetPointError(1,45,45,0.8553-0.8382,0.873-0.8553);
  effgraphs_[4]=(myt4);
  
  myt5->SetPoint(0,25,0.876);
  myt5->SetPointError(0,5,5,0.876-0.8319,0.9254-0.876);
  myt5->SetPoint(1,75,0.6792);
  myt5->SetPointError(1,45,45, 0.6792-0.667,0.6919-0.6792);
  effgraphs_[5]=(myt5);
  
  myt7->SetPoint(0,70,0.6369);
  myt7->SetPointError(0,50,50,0.6369-0.6171, 0.6581-0.6369);
  effgraphs_[6]=(myt7);
  
  
  


mystyle_->cd();
	TCanvas *tempCan = new TCanvas("tempcan","tempcan");
        TLegend *myLeg = new TLegend(.42,.13,.73,.39);
	for (int b=0; b<7; ++b){
	  if (b==3){continue;}
	  double BinInfo[] = {-4.6,-4.0,-3.4,-3.1,3.1,3.4,4.0,4.6};
	  effgraphs_[b]->GetXaxis()->CenterTitle(kTRUE);
	  effgraphs_[b]->GetYaxis()->CenterTitle(kTRUE);
	  effgraphs_[b]->SetLineColor(Cols_[b]);
	  effgraphs_[b]->SetMarkerColor(Cols_[b]);
	  effgraphs_[b]->SetMarkerStyle(Marker_[b]);
	  //  effgraphs_[b]->SetTitle("HF Loose Electron Identification");
	  if ( b == 0) 
	    {
	      effgraphs_[b]->Draw("AP");
	      effgraphs_[b]->SetTitle(Form("HF Loose Electron Identification;%s %s;Single Electron Efficiency","P_{T}" ,"[GeV/c]"));
	      // double min = effgraphs_[b]->GetYaxis()->GetXmin();
	      double max = effgraphs_[b]->GetYaxis()->GetXmax();
	      //double dmin = min-0.15;
	      double dmax = 1.02;
	      //if ( max - min < 0.05 ) {
	      //	dmin = min - 0.02; dmax = 1.01;
	      //}
	      // effgraphs_[b]->SetMaximum(dmax);
	      // effgraphs_[b]->SetMinimum(dmin);
	      effgraphs_[b]->SetMaximum(1.02);
		effgraphs_[b]->SetMinimum(0.30);
	    effgraphs_[b]->SetTitle("HF Loose Electron Identification");
	    }
	  else effgraphs_[b]->Draw("P");
	  myLeg->AddEntry(effgraphs_[b],Form("#eta_{d} %.2f to %.2f",BinInfo[b],BinInfo[b+1]),"lp");
	  
	}
	
	myLeg->SetFillColor(kWhite);
	myLeg->Draw();
	TText *plabel = new TText();
	plabel-> SetNDC();
	plabel -> SetTextFont(1);
	plabel -> SetTextColor(1);
	plabel -> SetTextSize(0.04);
	plabel -> SetTextAlign(22);
	plabel -> SetTextAngle(0);
	plabel -> DrawText(0.29, 0.20, "PRELIMINARY");
	TText *tlabel = new TText();
	tlabel-> SetNDC();
	tlabel -> SetTextFont(1);
	tlabel -> SetTextColor(1);
	tlabel -> SetTextSize(0.04);
        tlabel -> SetTextAlign(22);
        tlabel -> SetTextAngle(0);
	tlabel -> DrawText(0.4, 0.97, "HF Loose Electron Identification");

	// TPaveLabel *tpave = new TPaveLabel(0.90,0.89,0.98,0.95,Form("%s","HF Loose Electron Identification","NDC"));
        // tpave->SetTextSize(0.6);
//         tpave->SetFillColor(kWhite);
	 // tpave->Draw();
	tempCan->Print(Form("sbs_eff_%s.png","HFEIdEtaPt"));
		tempCan->Print(Form("sbs_eff_%s.eps","HFEIdEtaPt"));
 	
	
	
	

    
}



/*
 Cols_[0] = kBlack;
   Cols_[1] = kRed;
   Cols_[2] = kMagenta;
   Cols_[3] = kBlue;
   Cols_[4] = kCyan+1;
   Cols_[5] = kGreen;
   Cols_[6] = kYellow+2;

   Marker_[0] = kOpenCircle;
   Marker_[1] = kOpenTriangleUp;
   Marker_[2] = kOpenSquare;
   Marker_[3] = kOpenStar;
   Marker_[4] = kOpenDiamond;
   Marker_[5] = kOpenCross;
   Marker_[6] = kPlus;


*/
