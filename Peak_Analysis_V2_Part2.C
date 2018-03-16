#include "./includes.h"

void Peak_Analysis_V2_Part2(){

    Double_t CaFitVals[3][6], CFitVals[3][6], PeakRatio[3];
    double CaPar, CPar;

    char* Files[3] = {"/scratch/IAA/Proton_Therapy/Basic_Hadrontherapy/Analysis/Hybrid/10e8_2cm_Tissue_4cm_Bone.root",
                      "/scratch/IAA/Proton_Therapy/Basic_Hadrontherapy/Analysis/Hybrid/10e8_3cm_Tissue_4cm_Bone.root",
                      "/scratch/IAA/Proton_Therapy/Basic_Hadrontherapy/Analysis/Hybrid/10e8_9cm_Tissue_1cm_Bone.root"};

    for(Int_t i = 0; i < 3; i++){
        TFile *f1 = TFile::Open(Files[i]);
        TTree *t1 = (TTree*)f1->Get("Peak_Parameters");
        t1->SetBranchAddress("CalciumParameters", &CaPar);
        t1->SetBranchAddress("CarbonParameters", &CPar);

        for(Int_t j = 0; j < 6; j++){
            Peak_Parameters->GetEntry(j);
            CaFitVals[i][j] = CaPar;
            CFitVals[i][j] = CPar;
        }

        PeakRatio[i] = CaFitVals[i][5]/CFitVals[i][5];
        cout << PeakRatio[i] << endl;
    }

    TFile f2("/scratch/IAA/Proton_Therapy/Basic_Hadrontherapy/Analysis/Analysis_10e8_Hybrid", "RECREATE");

    f2.Write();
    f2.Close();
}
