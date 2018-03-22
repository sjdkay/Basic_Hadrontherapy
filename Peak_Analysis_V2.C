#include "./includes.h"


void Peak_Analysis_V2(){

    double CFPar[5], CaFPar[5], CaPar, CPar;

    char* InFiles[8] = {"/scratch/IAA/Proton_Therapy/Basic_Hadrontherapy/build/SimulationOutputs/Hybrid/10e8_1cm_Tissue_4cm_Bone.root",
    "/scratch/IAA/Proton_Therapy/Basic_Hadrontherapy/build/SimulationOutputs/Hybrid/10e8_2cm_Tissue_4cm_Bone_2.root",
    "/scratch/IAA/Proton_Therapy/Basic_Hadrontherapy/build/SimulationOutputs/Hybrid/10e8_3cm_Tissue_4cm_Bone_2.root",
    "/scratch/IAA/Proton_Therapy/Basic_Hadrontherapy/build/SimulationOutputs/Hybrid/10e8_4cm_Tissue_4cm_Bone.root",
    "/scratch/IAA/Proton_Therapy/Basic_Hadrontherapy/build/SimulationOutputs/Hybrid/10e8_5cm_Tissue_4cm_Bone.root",
    "/scratch/IAA/Proton_Therapy/Basic_Hadrontherapy/build/SimulationOutputs/Hybrid/10e8_6cm_Tissue_4cm_Bone.root",
    "/scratch/IAA/Proton_Therapy/Basic_Hadrontherapy/build/SimulationOutputs/Hybrid/10e8_7cm_Tissue_4cm_Bone.root",
    "/scratch/IAA/Proton_Therapy/Basic_Hadrontherapy/build/SimulationOutputs/Hybrid/10e8_8cm_Tissue_4cm_Bone.root"
    };

    char* OutFiles[8] = {"/scratch/IAA/Proton_Therapy/Basic_Hadrontherapy/Analysis/Hybrid/10e8_1cm_4cm.root",
    "/scratch/IAA/Proton_Therapy/Basic_Hadrontherapy/Analysis/Hybrid/10e8_2cm_4cm.root",
    "/scratch/IAA/Proton_Therapy/Basic_Hadrontherapy/Analysis/Hybrid/10e8_3cm_4cm.root",
    "/scratch/IAA/Proton_Therapy/Basic_Hadrontherapy/Analysis/Hybrid/10e8_4cm_4cm.root",
    "/scratch/IAA/Proton_Therapy/Basic_Hadrontherapy/Analysis/Hybrid/10e8_5cm_4cm.root",
    "/scratch/IAA/Proton_Therapy/Basic_Hadrontherapy/Analysis/Hybrid/10e8_6cm_4cm.root",
    "/scratch/IAA/Proton_Therapy/Basic_Hadrontherapy/Analysis/Hybrid/10e8_7cm_4cm.root",
    "/scratch/IAA/Proton_Therapy/Basic_Hadrontherapy/Analysis/Hybrid/10e8_8cm_4cm.root"
    };

    for(Int_t j = 0; j < 8; j++){

        TFile *f = TFile::Open(InFiles[j]);

        TF1* CPeakFit = new TF1("CPeakFit", "gaus",  4.2, 4.7);
        TF1* CBGFit = new TF1("CBGFit", "pol1", 4, 4.9);
        TF1* CFit = new TF1("CFit", "gaus(0)+pol1(3)",  4.2, 4.7);

        h110e->Fit(CPeakFit, "", "", 4.3, 4.55);
        h110e->Fit(CBGFit, "", "", 4, 4.2);

        CFPar[0] = CPeakFit->GetParameter(0); // Constant
        CFPar[1] = CPeakFit->GetParameter(1); // Mean
        CFPar[2] = CPeakFit->GetParameter(2); // Sigma
        CFPar[3] = CBGFit->GetParameter(0); // Constant
        CFPar[4] = CBGFit->GetParameter(1); // Gradient

        for(Int_t i = 0; i < 5; i++){
            CFit->SetParameter(i, CFPar[i]);
        }

        h110e->Fit(CFit, "", "", 4.2, 4.7);
        CPeakFit->SetParameter(0, CFit->GetParameter(0));
        CPeakFit->SetParameter(1, CFit->GetParameter(1));
        CPeakFit->SetParameter(2, CFit->GetParameter(2));
        CBGFit->SetParameter(0, CFit->GetParameter(3));
        CBGFit->SetParameter(1, CFit->GetParameter(4));

        TF1* CaPeakFit = new TF1("CaPeakFit", "gaus",  3.65, 3.85);
        TF1* CaBGFit = new TF1("CaBGFit", "pol1", 3.6, 4.0);
        TF1* CaFit = new TF1("CaFit", "gaus(0)+pol1(3)",  3.65, 3.85);

        h110e->Fit(CaPeakFit, "", "", 3.7, 3.8);
        h110e->Fit(CaBGFit, "", "", 3.6, 3.7);

        CaFPar[0] = CaPeakFit->GetParameter(0);
        CaFPar[1] = CaPeakFit->GetParameter(1);
        CaFPar[2] = CaPeakFit->GetParameter(2);
        CaFPar[3] = CaBGFit->GetParameter(0);
        CaFPar[4] = CaBGFit->GetParameter(1);


        for(Int_t i = 0; i < 5; i++){
            CaFit->SetParameter(i, CaFPar[i]);
        }

        h110e->Fit(CaFit, "", "", 3.65, 3.85);
        CaPeakFit->SetParameter(0, CaFit->GetParameter(0));
        CaPeakFit->SetParameter(1, CaFit->GetParameter(1));
        CaPeakFit->SetParameter(2, CaFit->GetParameter(2));
        CaBGFit->SetParameter(0, CaFit->GetParameter(3));
        CaBGFit->SetParameter(1, CaFit->GetParameter(4));

        TCanvas *canvas = new TCanvas("canvas","canvas", 1920, 1080);
        TPad *pad = new TPad("pad","",0,0,1,1);
        pad->Draw();
        pad->cd();
        h110e->GetXaxis()->SetTitle("E_{#gamma}/MeV");
        h110e->GetYaxis()->SetTitle("counts/arb");

        h110e->Draw("");
        CaFit->SetLineColor(2);
        CaPeakFit->SetLineColor(2);
        CaPeakFit->SetLineStyle(2);
        CaBGFit->SetLineColor(2);
        CaBGFit->SetLineStyle(2);
        CaFit->Draw("Same");
        CaPeakFit->Draw("Same");
        CaBGFit->Draw("Same");
        CFit->SetLineColor(1);
        CPeakFit->SetLineColor(1);
        CPeakFit->SetLineStyle(2);
        CBGFit->SetLineColor(1);
        CBGFit->SetLineStyle(2);
        CFit->Draw("Same");
        CPeakFit->Draw("Same");
        CBGFit->Draw("Same");

        Double_t BinWidth = h110e->GetBinWidth(1);
        Double_t CaPeakInt = CaPeakFit->Integral(3.65, 3.85);
        Double_t CPeakInt = CPeakFit->Integral(4.2, 4.7);
        Double_t CaPeakCounts = CaPeakInt/BinWidth;
        Double_t CPeakCounts = CPeakInt/BinWidth;

        // Note that this is an APPROXIMATION using 2.507*Sgima*Amplitude to get the area under the gaussian
        // Propagate error from this to get error on area, this then needs to be divided by bin width to get counts
        // GetIntegralArea requires covariance matrix but getting this fucks up the fits
        Double_t CaPeakAreaErr = sqrt( ((2.507*(CaFit->GetParameter(2))*(CaFit->GetParError(0)))**2) + ((2.507*(CaFit->GetParameter(0))*(CaFit->GetParError(2)))**2) );
        Double_t CPeakAreaErr = sqrt( ((2.507*(CFit->GetParameter(2))*(CFit->GetParError(0)))**2) + ((2.507*(CFit->GetParameter(0))*(CFit->GetParError(2)))**2) );
        Double_t CaPeakCountsErr = CaPeakAreaErr/BinWidth;
        Double_t CPeakCountsErr = CPeakAreaErr/BinWidth;

        TFile f1(OutFiles[j], "RECREATE");
        h110e->Write();
        canvas->Write();
        CaPeakFit->Write();
        CaBGFit->Write();
        CaFit->Write();
        CPeakFit->Write();
        CBGFit->Write();
        CFit->Write();

        TTree* tree = new TTree("Peak_Parameters", "Tree_of_Values");

        tree->Branch("CarbonParameters", &CPar, "CPar/D");
        tree->Branch("CalciumParameters", &CaPar, "CaPar/D");

        for(Int_t i = 0; i < 5; i++){
            CPar = CFit->GetParameter(i);
            CaPar = CaFit->GetParameter(i);
            tree->Fill();
        }

        CPar = CPeakCounts;
        CaPar = CaPeakCounts;
        tree->Fill();
        CPar = CPeakCountsErr;
        CaPar = CaPeakCountsErr;
        tree->Fill();

        f1.Write();
        f1.Close();
    }
}
