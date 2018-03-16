#include "./includes.h"

void Pure_Target_Dists(){

    TFile *f = new TFile("/scratch/IAA/Proton_Therapy/Basic_Hadrontherapy/build/SimulationOutputs/Pure_Targets/10e7_Calcium.root"); // Open the file to clone
    TH1D* GammaDistCalcium = (TH1D*)f->Get("h110c")->Clone();
    GammaDistCalcium->SetName("GammaDistCalcium");
    TFile *f1 = new TFile("/scratch/IAA/Proton_Therapy/Basic_Hadrontherapy/build/SimulationOutputs/Pure_Targets/10e7_Carbon.root"); // Open the file to clone
    TH1D* GammaDistCarbon = (TH1D*)f1->Get("h110c")->Clone();
    GammaDistCarbon->SetName("GammaDistCarbon");
    TFile *f2 = new TFile("/scratch/IAA/Proton_Therapy/Basic_Hadrontherapy/build/SimulationOutputs/Pure_Targets/10e7_Phosphorous.root"); // Open the file to clone
    TH1D* GammaDistPhosphorous = (TH1D*)f2->Get("h110c")->Clone();
    GammaDistPhosphorous->SetName("GammaDistPhosphorous");


    TCanvas *canvas = new TCanvas("canvas","canvas", 1920, 1080);
    TPad *pad = new TPad("pad","",0,0,1,1);
    pad->Draw();
    pad->cd();
    GammaDistCalcium->GetXaxis()->SetTitle("E_{#gamma}/MeV");
    GammaDistCalcium->GetYaxis()->SetTitle("counts/arb");
    GammaDistCalcium->SetLineColor(1);
    GammaDistCalcium->Draw("");
    GammaDistCarbon->SetLineColor(2);
    GammaDistCarbon->Draw("SAME");
    GammaDistPhosphorous->SetLineColor(4);
    GammaDistPhosphorous->Draw("SAME");
    leg = new TLegend(0.85, 0.15, 0.95, 0.25); // Add legend to plot
    leg->AddEntry(GammaDistCalcium, "Calcium", "l");
    leg->AddEntry(GammaDistCarbon, "Carbon", "l");
    leg->AddEntry(GammaDistPhosphorous, "Phosphorous", "l");
    leg->Draw("Same");

    TFile f3("/scratch/IAA/Proton_Therapy/Basic_Hadrontherapy/Analysis/10e7_Pure_Target_Dists.root", "RECREATE");
    canvas->Write();

    f3.Write();
    f3.Close();

}
