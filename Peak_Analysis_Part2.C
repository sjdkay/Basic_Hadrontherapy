#include "./includes.h"

void Peak_Analysis_Part2(){

    Double_t CPeakConst[4][8], CPeakMean[4][8], CPeakSigma[4][8], CPeakIntegral[4][8],
    CaPeakConst[4][8], CaPeakMean[4][10], CaPeakSigma[4][8], CaPeakIntegral[4][8];
    double CFPar, CaFPar;
    Double_t x[8] = {1, 2, 3, 4, 5, 6, 7, 8};
    Double_t BoneCY[8], BoneCaY[8], TissueCY[8], TissueCaY[8], ParaffinCY[8], ParaffinCaY[8];

    char* BoneFiles[8] = {"/scratch/IAA/Proton_Therapy/Basic_Hadrontherapy/Analysis/Bone_ICRP_10e6_1cm.root",
                          "/scratch/IAA/Proton_Therapy/Basic_Hadrontherapy/Analysis/Bone_ICRP_10e6_2cm.root",
                          "/scratch/IAA/Proton_Therapy/Basic_Hadrontherapy/Analysis/Bone_ICRP_10e6_3cm.root",
                          "/scratch/IAA/Proton_Therapy/Basic_Hadrontherapy/Analysis/Bone_ICRP_10e6_4cm.root",
                          "/scratch/IAA/Proton_Therapy/Basic_Hadrontherapy/Analysis/Bone_ICRP_10e6_5cm.root",
                          "/scratch/IAA/Proton_Therapy/Basic_Hadrontherapy/Analysis/Bone_ICRP_10e6_6cm.root",
                          "/scratch/IAA/Proton_Therapy/Basic_Hadrontherapy/Analysis/Bone_ICRP_10e6_7cm.root",
                          "/scratch/IAA/Proton_Therapy/Basic_Hadrontherapy/Analysis/Bone_ICRP_10e6_8cm.root"};

    char* TissueFiles[8] = {"/scratch/IAA/Proton_Therapy/Basic_Hadrontherapy/Analysis/Soft_Tissue_10e6_1cm.root",
                          "/scratch/IAA/Proton_Therapy/Basic_Hadrontherapy/Analysis/Soft_Tissue_10e6_2cm.root",
                          "/scratch/IAA/Proton_Therapy/Basic_Hadrontherapy/Analysis/Soft_Tissue_10e6_3cm.root",
                          "/scratch/IAA/Proton_Therapy/Basic_Hadrontherapy/Analysis/Soft_Tissue_10e6_4cm.root",
                          "/scratch/IAA/Proton_Therapy/Basic_Hadrontherapy/Analysis/Soft_Tissue_10e6_5cm.root",
                          "/scratch/IAA/Proton_Therapy/Basic_Hadrontherapy/Analysis/Soft_Tissue_10e6_6cm.root",
                          "/scratch/IAA/Proton_Therapy/Basic_Hadrontherapy/Analysis/Soft_Tissue_10e6_7cm.root",
                          "/scratch/IAA/Proton_Therapy/Basic_Hadrontherapy/Analysis/Soft_Tissue_10e6_8cm.root"};

    char* ParaffinFiles[8] = {"/scratch/IAA/Proton_Therapy/Basic_Hadrontherapy/Analysis/Paraffin_10e6_1cm.root",
                      "/scratch/IAA/Proton_Therapy/Basic_Hadrontherapy/Analysis/Paraffin_10e6_2cm.root",
                      "/scratch/IAA/Proton_Therapy/Basic_Hadrontherapy/Analysis/Paraffin_10e6_3cm.root",
                      "/scratch/IAA/Proton_Therapy/Basic_Hadrontherapy/Analysis/Paraffin_10e6_4cm.root",
                      "/scratch/IAA/Proton_Therapy/Basic_Hadrontherapy/Analysis/Paraffin_10e6_5cm.root",
                      "/scratch/IAA/Proton_Therapy/Basic_Hadrontherapy/Analysis/Paraffin_10e6_6cm.root",
                      "/scratch/IAA/Proton_Therapy/Basic_Hadrontherapy/Analysis/Paraffin_10e6_7cm.root",
                      "/scratch/IAA/Proton_Therapy/Basic_Hadrontherapy/Analysis/Paraffin_10e6_8cm.root"};

    for(Int_t i = 0; i < 8; i++){

        TFile *f1 = TFile::Open(BoneFiles[i]);
        TTree *t1 = (TTree*)f1->Get("Peak_Parameters");
        t1->SetBranchAddress("CarbonFitParameters", &CFPar);
        t1->SetBranchAddress("CalciumFitParameters", &CaFPar);
        Peak_Parameters->GetEntry(0);
        CPeakConst[0][i] = CFPar;
        CaPeakConst[0][i] = CaFPar;

        Peak_Parameters->GetEntry(1);
        CPeakMean[0][i] = CFPar;
        CaPeakMean[0][i] = CaFPar;

        Peak_Parameters->GetEntry(2);
        CPeakSigma[0][i] = CFPar;
        CaPeakSigma[0][i] = CaFPar;

        Peak_Parameters->GetEntry(3);
        CPeakIntegral[0][i] = CFPar;
        CaPeakIntegral[0][i] = CaFPar;

        BoneCY[i] = CPeakIntegral[0][i];
        BoneCaY[i] = CaPeakIntegral[0][i];

    }

    for(Int_t i = 0; i < 8; i++){

        TFile *f1 = TFile::Open(TissueFiles[i]);
        TTree *t1 = (TTree*)f1->Get("Peak_Parameters");
        t1->SetBranchAddress("CarbonFitParameters", &CFPar);
        t1->SetBranchAddress("CalciumFitParameters", &CaFPar);
        Peak_Parameters->GetEntry(0);
        CPeakConst[1][i] = CFPar;
        CaPeakConst[1][i] = CaFPar;

        Peak_Parameters->GetEntry(1);
        CPeakMean[1][i] = CFPar;
        CaPeakMean[1][i] = CaFPar;

        Peak_Parameters->GetEntry(2);
        CPeakSigma[1][i] = CFPar;
        CaPeakSigma[1][i] = CaFPar;

        Peak_Parameters->GetEntry(3);
        CPeakIntegral[1][i] = CFPar;
        CaPeakIntegral[1][i] = CaFPar;

        TissueCY[i] = CPeakIntegral[1][i];
        TissueCaY[i] = CaPeakIntegral[1][i];

    }

    for(Int_t i = 0; i < 8; i++){

        TFile *f1 = TFile::Open(ParaffinFiles[i]);
        TTree *t1 = (TTree*)f1->Get("Peak_Parameters");
        t1->SetBranchAddress("CarbonFitParameters", &CFPar);
        t1->SetBranchAddress("CalciumFitParameters", &CaFPar);
        Peak_Parameters->GetEntry(0);
        CPeakConst[2][i] = CFPar;
        CaPeakConst[2][i] = CaFPar;

        Peak_Parameters->GetEntry(1);
        CPeakMean[2][i] = CFPar;
        CaPeakMean[2][i] = CaFPar;

        Peak_Parameters->GetEntry(2);
        CPeakSigma[2][i] = CFPar;
        CaPeakSigma[2][i] = CaFPar;

        Peak_Parameters->GetEntry(3);
        CPeakIntegral[2][i] = CFPar;
        CaPeakIntegral[2][i] = CaFPar;

        ParaffinCY[i] = CPeakIntegral[2][i];
        ParaffinCaY[i] = CaPeakIntegral[2][i];

    }

    gr1 = new TGraph(8, x, BoneCY);
    gr1->SetMarkerColor(2);
    gr1->SetLineColor(2);
    gr1->SetMarkerStyle(8);
    gr1->SetMarkerSize(1);
    gr1->SetTitle("Integral of Carbon 4.4MeV Peak as Fn of Bone Thickness");
    gr1->GetXaxis()->SetTitle("Material Thickness");
    gr1->GetYaxis()->SetTitle("Integral of Peak");
    gr1->SetName("BoneCY");
    gr1->Draw("ep");

    gr2 = new TGraph(8, x, BoneCaY);
    gr2->SetMarkerColor(2);
    gr2->SetLineColor(2);
    gr2->SetMarkerStyle(8);
    gr2->SetMarkerSize(1);
    gr2->SetTitle("Integral of Calcium 3.7MeV Peak as Fn of Bone Thickness");
    gr2->GetXaxis()->SetTitle("Material Thickness");
    gr2->GetYaxis()->SetTitle("Integral of Peak");
    gr2->SetName("BoneCaY");
    gr2->Draw("ep");

    gr3 = new TGraph(8, x, TissueCY);
    gr3->SetMarkerColor(2);
    gr3->SetLineColor(2);
    gr3->SetMarkerStyle(8);
    gr3->SetMarkerSize(1);
    gr3->SetTitle("Integral of Carbon 4.4MeV Peak as Fn of Tissue Thickness");
    gr3->GetXaxis()->SetTitle("Material Thickness");
    gr3->GetYaxis()->SetTitle("Integral of Peak");
    gr3->SetName("TissueCY");
    gr3->Draw("ep");

    gr4 = new TGraph(8, x, TissueCaY);
    gr4->SetMarkerColor(2);
    gr4->SetLineColor(2);
    gr4->SetMarkerStyle(8);
    gr4->SetMarkerSize(1);
    gr4->SetTitle("Integral of Calcium 3.7MeV Peak as Fn of Tissue Thickness");
    gr4->GetXaxis()->SetTitle("Material Thickness");
    gr4->GetYaxis()->SetTitle("Integral of Peak");
    gr4->SetName("TissueCaY");
    gr4->Draw("ep");

    gr5 = new TGraph(8, x, ParaffinCY);
    gr5->SetMarkerColor(2);
    gr5->SetLineColor(2);
    gr5->SetMarkerStyle(8);
    gr5->SetMarkerSize(1);
    gr5->SetTitle("Integral of Carbon 4.4MeV Peak as Fn of Paraffin Thickness");
    gr5->GetXaxis()->SetTitle("Material Thickness");
    gr5->GetYaxis()->SetTitle("Integral of Peak");
    gr5->SetName("ParaffinCY");
    gr5->Draw("ep");

    gr6 = new TGraph(8, x, ParaffinCaY);
    gr6->SetMarkerColor(2);
    gr6->SetLineColor(2);
    gr6->SetMarkerStyle(8);
    gr6->SetMarkerSize(1);
    gr6->SetTitle("Integral of Calcium 3.7MeV Peak as Fn of Paraffin Thickness");
    gr6->GetXaxis()->SetTitle("Material Thickness");
    gr6->GetYaxis()->SetTitle("Integral of Peak");
    gr6->SetName("ParaffinCaY");
    gr6->Draw("ep");

    TCanvas *canvas1 = new TCanvas("canvas1","canvas1", 1920, 1080);
    TPad *pad1 = new TPad("pad1","",0,0,1,1);
    TH1F *hr1 = canvas1->DrawFrame(0, 0, 9, 20000);
    hr1->SetTitle("Carbon 4.4MeV Peak Integral as a Fn of Thickness");
    gr1->SetMarkerStyle(4);
    gr1->SetMarkerSize(2);
    gr1->Draw("p");
    gr3->SetMarkerColor(4);
    gr3->SetMarkerStyle(4);
    gr3->SetMarkerSize(2);
    gr3->Draw("SAMEP");
    gr5->SetMarkerColor(1);
    gr5->SetMarkerStyle(3);
    gr5->SetMarkerSize(2);
    gr5->Draw("SAMEP");
    leg = new TLegend(0.75, 0.25, 0.95, 0.45); // Add legend to plot
    leg->AddEntry(gr1, "Bone", "p");
    leg->AddEntry(gr3, "Tissue", "p");
    leg->AddEntry(gr5, "Paraffin", "p");
    leg->Draw("Same");

    TCanvas *canvas2 = new TCanvas("canvas2","canvas2", 1920, 1080);
    TPad *pad2 = new TPad("pad2","",0,0,1,1);
    TH1F *hr2 = canvas1->DrawFrame(0, 0, 9, 10000);
    hr2->SetTitle("Calcium 3.7MeV Peak Integral as a Fn of Thickness");
    gr2->SetMarkerStyle(4);
    gr2->SetMarkerSize(2);
    gr2->Draw("p");
    gr4->SetMarkerColor(4);
    gr4->SetMarkerStyle(4);
    gr4->SetMarkerSize(2);
    gr4->Draw("SAMEP");
    gr6->SetMarkerColor(1);
    gr6->SetMarkerStyle(3);
    gr6->SetMarkerSize(2);
    gr6->Draw("SAMEP");
    leg2 = new TLegend(0.75, 0.25, 0.95, 0.45); // Add legend to plot
    leg2->AddEntry(gr2, "Bone", "p");
    leg2->AddEntry(gr4, "Tissue", "p");
    leg2->AddEntry(gr6, "Paraffin", "p");
    leg2->Draw("Same");

    TFile f2("/scratch/IAA/Proton_Therapy/Basic_Hadrontherapy/Analysis/Analysis_Plots.root", "RECREATE");
    gr1->Write();
    gr2->Write();
    gr3->Write();
    gr4->Write();
    gr5->Write();
    gr6->Write();
    canvas1->Write();
    canvas2->Write();

}
