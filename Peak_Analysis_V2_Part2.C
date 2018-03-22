#include "./includes.h"

void Peak_Analysis_V2_Part2(){

    Double_t CaFitVals[8][6], CFitVals[8][6], PeakRatio[8], PeakRatioErr[8];
    Double_t x[8] = {1, 2, 3, 4, 5, 6, 7, 8};
    Double_t xErr[8] = {0, 0, 0, 0, 0, 0, 0, 0};
    double CaPar, CPar;

    // Will be 9 files total with 1cm to 8cm of tissue in front of 4cm of bone
    char* Files[8] = {"/scratch/IAA/Proton_Therapy/Basic_Hadrontherapy/Analysis/Hybrid/10e8_1cm_4cm.root",
    "/scratch/IAA/Proton_Therapy/Basic_Hadrontherapy/Analysis/Hybrid/10e8_2cm_4cm.root",
    "/scratch/IAA/Proton_Therapy/Basic_Hadrontherapy/Analysis/Hybrid/10e8_3cm_4cm.root",
    "/scratch/IAA/Proton_Therapy/Basic_Hadrontherapy/Analysis/Hybrid/10e8_4cm_4cm.root",
    "/scratch/IAA/Proton_Therapy/Basic_Hadrontherapy/Analysis/Hybrid/10e8_5cm_4cm.root",
    "/scratch/IAA/Proton_Therapy/Basic_Hadrontherapy/Analysis/Hybrid/10e8_6cm_4cm.root",
    "/scratch/IAA/Proton_Therapy/Basic_Hadrontherapy/Analysis/Hybrid/10e8_7cm_4cm.root",
    "/scratch/IAA/Proton_Therapy/Basic_Hadrontherapy/Analysis/Hybrid/10e8_8cm_4cm.root"
    };

    for(Int_t i = 0; i < 8; i++){
        TFile *f1 = TFile::Open(Files[i]);
        TTree *t1 = (TTree*)f1->Get("Peak_Parameters");
        t1->SetBranchAddress("CalciumParameters", &CaPar);
        t1->SetBranchAddress("CarbonParameters", &CPar);

        for(Int_t j = 0; j < 7; j++){
            Peak_Parameters->GetEntry(j);
            CaFitVals[i][j] = CaPar;
            CFitVals[i][j] = CPar;
        }

        PeakRatio[i] = CaFitVals[i][5]/CFitVals[i][5];
        PeakRatioErr[i] = sqrt( ((CaFitVals[i][6]/CFitVals[i][5])**2) + ((((CaFitVals[i][5]*CFitVals[i][6])/((CFitVals[i][5])**2))**2)) );
    }

    PeakRatio[7] = 0;
    PeakRatioErr[7] = 0;

    TCanvas *canvas = new TCanvas("canvas","canvas", 1920, 1080);
    TPad *pad = new TPad("pad","",0,0,1,1);
    pad->Draw();
    pad->cd();

    gr1 = new TGraphErrors(8, x, PeakRatio, xErr, PeakRatioErr);
    gr1->SetMarkerColor(2);
    gr1->SetLineColor(2);
    gr1->SetMarkerStyle(8);
    gr1->SetMarkerSize(1);
    gr1->SetTitle("Ratio Between Calcium and Carbon Peak Counts as fn of Tissue Thickness");
    gr1->GetXaxis()->SetTitle("Tissue Thickness");
    gr1->GetYaxis()->SetTitle("Ratio");
    gr1->SetName("PeakRatio");
    gr1->Draw("aep");

    TFile f2("/scratch/IAA/Proton_Therapy/Basic_Hadrontherapy/Analysis/Analysis_10e8_Hybrid.root", "RECREATE");

    canvas->Write();
    gr1->Write();
    f2.Write();
    f2.Close();
}
