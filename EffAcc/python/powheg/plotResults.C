#include "TH1.h"
#include "TFile.h"
#include "TROOT.h"
#include "TCanvas.h"
#include "TLegend.h"
#include "tdrstyle.C"

#include "stdio.h"
#include <iostream>

char baseDir[512] = "/local/cms/user/pastika/powhegZ";
double murefM[] = {80.0, 91.188, 100.0}; // reference scale in GeV
double facscfactM[] = {0.5, 1.0, 2.0}; // factorization scale factor: mufact=muref*facscfact
double renscfactM[] = {0.5, 1.0, 2.0}; // renormalization scale factor: muren=muref*renscfact
int bbscalevarM[] = {0, 1, 2}; // 0: fixed scales ; 1: dynamic scale M_V; 2: dynamic scales sqrt(m_V^2 +P_t^2)

void plotResults(int var, int plot = 0)
{
    setTDRStyle();//gROOT->SetStyle("Plane");
    char fileName[512], title[2][512], varName[4][128] = {"muref", "facscfact", "renscfact", "bbscalevar"};

    int index[4];
    index[0] = index[1] = index[2] = 1;
    index[3] = 2;

    TFile * f[3];
    TH1 * h[3];

    for(int i = 0; i < 3; i++)
    {
        index[var] = i;
        sprintf(fileName, "%s/%1.3f_%1.1f_%1.1f_%i/effAccOut.root", baseDir, murefM[index[0]], facscfactM[index[1]], renscfactM[index[2]], bbscalevarM[index[3]]);
        f[i] = TFile::Open(fileName);
        if(plot == 0) h[i] = (TH1*)f[i]->Get("mcEff/MUON-MUON/Acceptance/Z0_PtTL");
        else if(plot == 1) h[i] = (TH1*)f[i]->Get("mcEff/MUON-MUON/Acceptance/Z0_Pt");
        else if(plot == 2) h[i] = (TH1*)f[i]->Get("mcEff/MUON-MUON/Acceptance/Z0_PtTLMon");
        else if(plot == 3) h[i] = (TH1*)f[i]->Get("mcEff/MUON-MUON/Acceptance/Z0_Pt_masscut");
        for(int j = 1; j <= h[i]->GetNbinsX(); j++)
        {
            h[i]->SetBinContent(j, h[i]->GetBinContent(j) / (h[i]->GetEntries() * h[i]->GetBinWidth(j)));
            h[i]->SetBinError(j, h[i]->GetBinError(j) / (h[i]->GetEntries() * h[i]->GetBinWidth(j)));
        }
    }

    h[0]->Sumw2();
    h[1]->Sumw2();
    h[2]->Sumw2();

    TH1* hl = (TH1*)h[0]->Clone();
    TH1* hu = (TH1*)h[2]->Clone();
    hl->Sumw2();
    hu->Sumw2();
    hl->Divide(h[1]);
    hu->Divide(h[1]);
    for(int j = 1; j <= hl->GetNbinsX(); j++)
    {
        hl->SetBinContent(j, hl->GetBinContent(j) - 1);
    }
    for(int j = 1; j <= hu->GetNbinsX(); j++)
    {
        hu->SetBinContent(j, hu->GetBinContent(j) - 1);
    }

    hl->SetLineColor(kRed);
    hu->SetLineColor(kBlue);

    TCanvas* c1 = new TCanvas("c1", "c1", 800, 800);
    c1->cd();
    c1->SetLogx();
    c1->SetMargin(0.15, 0.05, 0.10, 0.05);

    hl->Draw();
    hl->SetTitle(0);
    hl->SetStats(0);
    hl->GetYaxis()->SetTitle("adjusted / base");
    hl->GetYaxis()->SetTitleOffset(1.5);
    hl->GetXaxis()->SetRangeUser(0.0, 500.0);

    TLegend* tl = new TLegend(0.15, 0.65, 0.45, 0.85, "generator variables");
    if(var == 0)
    {
        sprintf(title[0], "%s = %1.3f", varName[var], murefM[0]);
        sprintf(title[1], "%s = %1.3f", varName[var], murefM[2]);
    }
    else if(var == 1)
    {
        sprintf(title[0], "%s = %1.1f", varName[var], facscfactM[0]);
        sprintf(title[1], "%s = %1.1f", varName[var], facscfactM[2]);
    }
    else if(var == 2)
    {
        sprintf(title[0], "%s = %1.1f", varName[var], renscfactM[0]);
        sprintf(title[1], "%s = %1.1f", varName[var], renscfactM[2]);
    }
    else
    {
        sprintf(title[0], "%s = %i", varName[var], bbscalevarM[0]);
        sprintf(title[1], "%s = %i", varName[var], bbscalevarM[1]);
    }
    tl->AddEntry(hl, title[0]);
    tl->AddEntry(hu, title[1]);

    hl->Draw();
    hu->Draw("same");
    tl->Draw("same");
}

void plotResults()
{
    setTDRStyle();//gROOT->SetStyle("Plane");
    char fileName[4][512], title[4][2][512], varName[4][128] = {"muref", "facscfact", "renscfact", "bbscalevar"}, ofnames[4][2][512];

    int index[4];

    TFile * f[4][3];
    TH1 * h[4][3];
    TH1 * hl[4];
    TH1 * hu[4];
    TLegend * tl[4];
    FILE* ofile[2];

    TCanvas* c1 = new TCanvas("c1", "c1", 1200, 1200);
    c1->Divide(2, 2);

    for(int var = 0; var < 4; var++)
    {
        setTDRStyle();
        c1->cd(var+1);
        gPad->SetLogx();
        gPad->SetMargin(0.15, 0.05, 0.10, 0.05);

        index[0] = index[1] = index[2] = 1;
        index[3] = 2;

        for(int i = 0; i < 3; i++)
        {
            index[var] = i;
            sprintf(fileName[var], "%s/%1.3f_%1.1f_%1.1f_%i/effAccOut.root", baseDir, murefM[index[0]], facscfactM[index[1]], renscfactM[index[2]], bbscalevarM[index[3]]);
            f[var][i] = TFile::Open(fileName[var]);
            h[var][i] = (TH1*)f[var][i]->Get("mcEff/MUON-MUON-G20/C01-GPT20/Z0_PtTL_masscut");
            for(int j = 1; j <= h[var][i]->GetNbinsX(); j++)
            {
                h[var][i]->SetBinContent(j, h[var][i]->GetBinContent(j) / (h[var][i]->GetEntries() * h[var][i]->GetBinWidth(j)));
                h[var][i]->SetBinError(j, h[var][i]->GetBinError(j) / (h[var][i]->GetEntries() * h[var][i]->GetBinWidth(j)));
            }
        }
        
        h[var][0]->Sumw2();
        h[var][1]->Sumw2();
        h[var][2]->Sumw2();

        hl[var] = (TH1*)h[var][0]->Clone();
        hu[var] = (TH1*)h[var][2]->Clone();
        hl[var]->Sumw2();
        hu[var]->Sumw2();
        hl[var]->Divide(h[var][1]);
        hu[var]->Divide(h[var][1]);

        if(var == 0)
        {
            sprintf(ofnames[var][0], "pwg_ratio_%s_%1.3f.txt", varName[var], murefM[0]);
            sprintf(ofnames[var][1], "pwg_ratio_%s_%1.3f.txt", varName[var], murefM[2]);
        }
        else if(var == 1)
        {
            sprintf(ofnames[var][0], "pwg_ratio_%s_%1.1f.txt", varName[var], facscfactM[0]);
            sprintf(ofnames[var][1], "pwg_ratio_%s_%1.1f.txt", varName[var], facscfactM[2]);
        }
        else if(var == 2)
        {
            sprintf(ofnames[var][0], "pwg_ratio_%s_%1.1f.txt", varName[var], renscfactM[0]);
            sprintf(ofnames[var][1], "pwg_ratio_%s_%1.1f.txt", varName[var], renscfactM[2]);
        }
        else
        {
            sprintf(ofnames[var][0], "pwg_ratio_%s_%i.txt", varName[var], bbscalevarM[0]);
            sprintf(ofnames[var][1], "pwg_ratio_%s_%i.txt", varName[var], bbscalevarM[1]);
        }
        ofile[0] = fopen(ofnames[var][0], "w");
        ofile[1] = fopen(ofnames[var][1], "w");
        fprintf(ofile[0], "#\n#%9s %9s %9s %15s %15s\n", "Bin", "Y_min", "Y_max", "Value", "Uncertainty");
        for(int j = 1; j <= hl[var]->GetNbinsX(); j++)
        {
            hl[var]->SetBinContent(j, hl[var]->GetBinContent(j) - 1);
            fprintf(ofile[0], " %9i %9.1f %9.1f %15e %15e\n", j, hl[var]->GetBinLowEdge(j), hl[var]->GetBinLowEdge(j) + hl[var]->GetBinWidth(j),
                hl[var]->GetBinContent(j), hl[var]->GetBinError(j));

        }
        fprintf(ofile[1], "#\n#%9s %9s %9s %15s %15s\n", "Bin", "Y_min", "Y_max", "Value", "Uncertainty");
        for(int j = 1; j <= hu[var]->GetNbinsX(); j++)
        {
            hu[var]->SetBinContent(j, hu[var]->GetBinContent(j) - 1);
            fprintf(ofile[1], " %9i %9.1f %9.1f %15e %15e\n", j, hu[var]->GetBinLowEdge(j), hu[var]->GetBinLowEdge(j) + hu[var]->GetBinWidth(j),
                hu[var]->GetBinContent(j), hu[var]->GetBinError(j));
        }
        fclose(ofile[0]);
        fclose(ofile[1]);

        hl[var]->SetLineColor(kRed);
        hu[var]->SetLineColor(kBlue);

        hl[var]->Draw();
        hl[var]->SetTitle(0);
        hl[var]->SetStats(0);
        hl[var]->GetYaxis()->SetTitle("adjusted / base");
        hl[var]->GetYaxis()->SetTitleOffset(1.5);
        hl[var]->GetXaxis()->SetRangeUser(0.0, 500.0);

        
        tl[var] = new TLegend(0.25, 0.65, 0.55, 0.85, "generator variables");
        if(var == 0)
        {
            sprintf(title[var][0], "%s = %1.3f", varName[var], murefM[0]);
            sprintf(title[var][1], "%s = %1.3f", varName[var], murefM[2]);
        }
        else if(var == 1)
        {
            sprintf(title[var][0], "%s = %1.1f", varName[var], facscfactM[0]);
            sprintf(title[var][1], "%s = %1.1f", varName[var], facscfactM[2]);
        }
        else if(var == 2)
        {
            sprintf(title[var][0], "%s = %1.1f", varName[var], renscfactM[0]);
            sprintf(title[var][1], "%s = %1.1f", varName[var], renscfactM[2]);
        }
        else
        {
            sprintf(title[var][0], "%s = %i", varName[var], bbscalevarM[0]);
            sprintf(title[var][1], "%s = %i", varName[var], bbscalevarM[1]);
        }
        tl[var]->AddEntry(hl[var], title[var][0]);
        tl[var]->AddEntry(hu[var], title[var][1]);
        
        hl[var]->Draw();
        hu[var]->Draw("same");
        tl[var]->Draw("same");
    }
}

void plotResults(int var0, int var1, int var2, int var3, int plot = 0)
{
    char fileName[2][512];

    TFile * f[2];
    TH1 * h[2];

    sprintf(fileName[0], "%s/%1.3f_%1.1f_%1.1f_%i/effAccOut.root", baseDir, murefM[var0], facscfactM[var1], renscfactM[var2], bbscalevarM[var3]);
    sprintf(fileName[1], "%s/%1.3f_%1.1f_%1.1f_%i/effAccOut.root", baseDir, murefM[1], facscfactM[1], renscfactM[1], bbscalevarM[2]);
    for(int i = 0; i < 2; i++)
    {
        f[i] = TFile::Open(fileName[i]);
        if(plot == 0) h[i] = (TH1*)f[i]->Get("mcEff/MUON-MUON/Acceptance/Z0_PtTL")->Clone();
        else if(plot == 1) h[i] = (TH1*)f[i]->Get("mcEff/MUON-MUON/Acceptance/Z0_Pt")->Clone();
        else if(plot == 2) h[i] = (TH1*)f[i]->Get("mcEff/MUON-MUON/Acceptance/Z0_PtTLMon")->Clone();
        else if(plot == 3) h[i] = (TH1*)f[i]->Get("mcEff/MUON-MUON/Acceptance/Z0_Pt_masscut")->Clone();
        for(int j = 1; j <= h[i]->GetNbinsX(); j++)
        {
            h[i]->SetBinContent(j, h[i]->GetBinContent(j) / (h[i]->GetEntries() * h[i]->GetBinWidth(j)));
            h[i]->SetBinError(j, h[i]->GetBinError(j) / (h[i]->GetEntries() * h[i]->GetBinWidth(j)));
        }
    }

    h[0]->SetLineColor(kRed);

    h[0]->Draw();
    h[1]->Draw("same");
}

void saveBasePlots(bool draw = false)
{
    const int numMod = 5;
    char hadModels[numMod][64], fname[numMod][512], tfname[numMod][512];
    sprintf(hadModels[0], "PythiaUED6T");
    sprintf(hadModels[1], "PythiaUEP0");
    sprintf(hadModels[2], "PythiaUEProPT0");
    sprintf(hadModels[3], "PythiaUEProQ20");
    sprintf(hadModels[4], "PythiaUEZ2");
    FILE * f[numMod];
    TFile * tf[numMod];
    TH1 * h[numMod];
    for(int i = 0; i < numMod; i++)
    {
        sprintf(tfname[i], "%s/base/%s/effAccOut_hadded.root", baseDir, hadModels[i]);
        tf[i] = TFile::Open(tfname[i]);
        h[i] = (TH1*)tf[i]->Get("mcEff/MUON-MUON-G20/C01-GPT20/Z0_PtTL_masscut");

        sprintf(fname[i], "%s/base/PtTL_pwg_%s.txt", baseDir, hadModels[i]);
        f[i] = fopen(fname[i], "w");

        fprintf(f[i], "#\n#%9s %9s %9s %15s %15s\n", "Bin", "Y_min", "Y_max", "Value", "Uncertainty");
        for(int j = 1; j <= h[i]->GetNbinsX(); j++)
        {
            fprintf(f[i], " %9i %9.1f %9.1f %15e %15e\n", j, h[i]->GetBinLowEdge(j), h[i]->GetBinLowEdge(j) + h[i]->GetBinWidth(j),
                    h[i]->GetBinContent(j) / (h[i]->GetEntries() * h[i]->GetBinWidth(j)), h[i]->GetBinError(j) / (h[i]->GetEntries() * h[i]->GetBinWidth(j)));
        }
        fclose(f[i]);
    }

    if(draw)
    {
        for(int i = 0; i < numMod; i++)
        {
            for(int j = 1; j <= h[i]->GetNbinsX(); j++)
            {
                h[i]->SetBinContent(j, h[i]->GetBinContent(j) / (h[i]->GetEntries() * h[i]->GetBinWidth(j)));
                h[i]->SetBinError(j, h[i]->GetBinError(j) / (h[i]->GetEntries() * h[i]->GetBinWidth(j)));
            }
        }
        h[0]->Draw();
        h[1]->Draw("same");
        h[2]->Draw("same");
        h[3]->Draw("same");
        h[4]->Draw("same");
    }
}

