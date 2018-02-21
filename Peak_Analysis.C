#include "./includes.h"

// Predefine list of input/output files to read plots in from and fit to and then save as
// These are then fed into loops, if more materials needed add in a similar way

void Peak_Analysis(){

    double CFPar, CaFPar;

    char* BoneInputFiles[14] = {"/scratch/IAA/Proton_Therapy/Basic_Hadrontherapy/build/SimulationOutputs/proton/BraggPeak/10e6_1cm_Bone_ICRP.root",
                          "/scratch/IAA/Proton_Therapy/Basic_Hadrontherapy/build/SimulationOutputs/proton/BraggPeak/10e6_2cm_Bone_ICRP.root",
                          "/scratch/IAA/Proton_Therapy/Basic_Hadrontherapy/build/SimulationOutputs/proton/BraggPeak/10e6_3cm_Bone_ICRP.root",
                          "/scratch/IAA/Proton_Therapy/Basic_Hadrontherapy/build/SimulationOutputs/proton/BraggPeak/10e6_325mm_Bone_ICRP.root",
                          "/scratch/IAA/Proton_Therapy/Basic_Hadrontherapy/build/SimulationOutputs/proton/BraggPeak/10e6_35mm_Bone_ICRP.root",
                          "/scratch/IAA/Proton_Therapy/Basic_Hadrontherapy/build/SimulationOutputs/proton/BraggPeak/10e6_375mm_Bone_ICRP.root",
                          "/scratch/IAA/Proton_Therapy/Basic_Hadrontherapy/build/SimulationOutputs/proton/BraggPeak/10e6_4cm_Bone_ICRP.root",
                          "/scratch/IAA/Proton_Therapy/Basic_Hadrontherapy/build/SimulationOutputs/proton/BraggPeak/10e6_425mm_Bone_ICRP.root",
                          "/scratch/IAA/Proton_Therapy/Basic_Hadrontherapy/build/SimulationOutputs/proton/BraggPeak/10e6_45mm_Bone_ICRP.root",
                          "/scratch/IAA/Proton_Therapy/Basic_Hadrontherapy/build/SimulationOutputs/proton/BraggPeak/10e6_5cm_Bone_ICRP.root",
                          "/scratch/IAA/Proton_Therapy/Basic_Hadrontherapy/build/SimulationOutputs/proton/BraggPeak/10e6_55mm_Bone_ICRP.root",
                          "/scratch/IAA/Proton_Therapy/Basic_Hadrontherapy/build/SimulationOutputs/proton/BraggPeak/10e6_6cm_Bone_ICRP.root",
                          "/scratch/IAA/Proton_Therapy/Basic_Hadrontherapy/build/SimulationOutputs/proton/BraggPeak/10e6_7cm_Bone_ICRP.root",
                          "/scratch/IAA/Proton_Therapy/Basic_Hadrontherapy/build/SimulationOutputs/proton/BraggPeak/10e6_8cm_Bone_ICRP.root"};

    char* TissueInputFiles[8] = {"/scratch/IAA/Proton_Therapy/Basic_Hadrontherapy/build/SimulationOutputs/proton/BraggPeak/10e6_1cm_Soft_Tissue.root",
                          "/scratch/IAA/Proton_Therapy/Basic_Hadrontherapy/build/SimulationOutputs/proton/BraggPeak/10e6_2cm_Soft_Tissue.root",
                          "/scratch/IAA/Proton_Therapy/Basic_Hadrontherapy/build/SimulationOutputs/proton/BraggPeak/10e6_3cm_Soft_Tissue.root",
                          "/scratch/IAA/Proton_Therapy/Basic_Hadrontherapy/build/SimulationOutputs/proton/BraggPeak/10e6_4cm_Soft_Tissue.root",
                          "/scratch/IAA/Proton_Therapy/Basic_Hadrontherapy/build/SimulationOutputs/proton/BraggPeak/10e6_5cm_Soft_Tissue.root",
                          "/scratch/IAA/Proton_Therapy/Basic_Hadrontherapy/build/SimulationOutputs/proton/BraggPeak/10e6_6cm_Soft_Tissue.root",
                          "/scratch/IAA/Proton_Therapy/Basic_Hadrontherapy/build/SimulationOutputs/proton/BraggPeak/10e6_7cm_Soft_Tissue.root",
                          "/scratch/IAA/Proton_Therapy/Basic_Hadrontherapy/build/SimulationOutputs/proton/BraggPeak/10e6_8cm_Soft_Tissue.root"};

    char* ParaffinInputFiles[8] = {"/scratch/IAA/Proton_Therapy/Basic_Hadrontherapy/build/SimulationOutputs/proton/BraggPeak/10e6_1cm_Paraffin.root",
                      "/scratch/IAA/Proton_Therapy/Basic_Hadrontherapy/build/SimulationOutputs/proton/BraggPeak/10e6_2cm_Paraffin.root",
                      "/scratch/IAA/Proton_Therapy/Basic_Hadrontherapy/build/SimulationOutputs/proton/BraggPeak/10e6_3cm_Paraffin.root",
                      "/scratch/IAA/Proton_Therapy/Basic_Hadrontherapy/build/SimulationOutputs/proton/BraggPeak/10e6_4cm_Paraffin.root",
                      "/scratch/IAA/Proton_Therapy/Basic_Hadrontherapy/build/SimulationOutputs/proton/BraggPeak/10e6_5cm_Paraffin.root",
                      "/scratch/IAA/Proton_Therapy/Basic_Hadrontherapy/build/SimulationOutputs/proton/BraggPeak/10e6_6cm_Paraffin.root",
                      "/scratch/IAA/Proton_Therapy/Basic_Hadrontherapy/build/SimulationOutputs/proton/BraggPeak/10e6_7cm_Paraffin.root",
                      "/scratch/IAA/Proton_Therapy/Basic_Hadrontherapy/build/SimulationOutputs/proton/BraggPeak/10e6_8cm_Paraffin.root"};


    char* BoneOutputFiles[14] = {"/scratch/IAA/Proton_Therapy/Basic_Hadrontherapy/Analysis/Bone_ICRP_10e6_1cm.root",
                          "/scratch/IAA/Proton_Therapy/Basic_Hadrontherapy/Analysis/Bone_ICRP_10e6_2cm.root",
                          "/scratch/IAA/Proton_Therapy/Basic_Hadrontherapy/Analysis/Bone_ICRP_10e6_3cm.root",
                          "/scratch/IAA/Proton_Therapy/Basic_Hadrontherapy/Analysis/Bone_ICRP_10e6_325mm.root",
                          "/scratch/IAA/Proton_Therapy/Basic_Hadrontherapy/Analysis/Bone_ICRP_10e6_35mm.root",
                          "/scratch/IAA/Proton_Therapy/Basic_Hadrontherapy/Analysis/Bone_ICRP_10e6_375mm.root",
                          "/scratch/IAA/Proton_Therapy/Basic_Hadrontherapy/Analysis/Bone_ICRP_10e6_4cm.root",
                          "/scratch/IAA/Proton_Therapy/Basic_Hadrontherapy/Analysis/Bone_ICRP_10e6_425mm.root",
                          "/scratch/IAA/Proton_Therapy/Basic_Hadrontherapy/Analysis/Bone_ICRP_10e6_45mm.root",
                          "/scratch/IAA/Proton_Therapy/Basic_Hadrontherapy/Analysis/Bone_ICRP_10e6_5cm.root",
                          "/scratch/IAA/Proton_Therapy/Basic_Hadrontherapy/Analysis/Bone_ICRP_10e6_55mm.root",
                          "/scratch/IAA/Proton_Therapy/Basic_Hadrontherapy/Analysis/Bone_ICRP_10e6_6cm.root",
                          "/scratch/IAA/Proton_Therapy/Basic_Hadrontherapy/Analysis/Bone_ICRP_10e6_7cm.root",
                          "/scratch/IAA/Proton_Therapy/Basic_Hadrontherapy/Analysis/Bone_ICRP_10e6_8cm.root"};

    char* TissueOutputFiles[8] = {"/scratch/IAA/Proton_Therapy/Basic_Hadrontherapy/Analysis/Soft_Tissue_10e6_1cm.root",
                          "/scratch/IAA/Proton_Therapy/Basic_Hadrontherapy/Analysis/Soft_Tissue_10e6_2cm.root",
                          "/scratch/IAA/Proton_Therapy/Basic_Hadrontherapy/Analysis/Soft_Tissue_10e6_3cm.root",
                          "/scratch/IAA/Proton_Therapy/Basic_Hadrontherapy/Analysis/Soft_Tissue_10e6_4cm.root",
                          "/scratch/IAA/Proton_Therapy/Basic_Hadrontherapy/Analysis/Soft_Tissue_10e6_5cm.root",
                          "/scratch/IAA/Proton_Therapy/Basic_Hadrontherapy/Analysis/Soft_Tissue_10e6_6cm.root",
                          "/scratch/IAA/Proton_Therapy/Basic_Hadrontherapy/Analysis/Soft_Tissue_10e6_7cm.root",
                          "/scratch/IAA/Proton_Therapy/Basic_Hadrontherapy/Analysis/Soft_Tissue_10e6_8cm.root"};

    char* ParaffinOutputFiles[8] = {"/scratch/IAA/Proton_Therapy/Basic_Hadrontherapy/Analysis/Paraffin_10e6_1cm.root",
                      "/scratch/IAA/Proton_Therapy/Basic_Hadrontherapy/Analysis/Paraffin_10e6_2cm.root",
                      "/scratch/IAA/Proton_Therapy/Basic_Hadrontherapy/Analysis/Paraffin_10e6_3cm.root",
                      "/scratch/IAA/Proton_Therapy/Basic_Hadrontherapy/Analysis/Paraffin_10e6_4cm.root",
                      "/scratch/IAA/Proton_Therapy/Basic_Hadrontherapy/Analysis/Paraffin_10e6_5cm.root",
                      "/scratch/IAA/Proton_Therapy/Basic_Hadrontherapy/Analysis/Paraffin_10e6_6cm.root",
                      "/scratch/IAA/Proton_Therapy/Basic_Hadrontherapy/Analysis/Paraffin_10e6_7cm.root",
                      "/scratch/IAA/Proton_Therapy/Basic_Hadrontherapy/Analysis/Paraffin_10e6_8cm.root"};

    for(Int_t i = 0; i < 14; i++){
        TFile *f = new TFile(BoneInputFiles[i]); // Open the file to clone
        TF1* CFit = new TF1("CFit", "gaus",  4.2, 4.7);
        CFit->SetLineColor(2);
        TF1* CaFit = new TF1("CaFit", "gaus",  3.7, 3.8);
        CaFit->SetLineColor(4);

        h110c->Fit("CFit", "", "", 4.2, 4.7);
        CFit->Draw("SAME");
        h110c->Fit("CaFit", "", "", 3.7, 3.8);
        CaFit->Draw("SAME");

        Double_t CFit_Const = CFit->GetParameter(0);
        Double_t CaFit_Const = CaFit->GetParameter(0);

        Double_t CFit_Mean = CFit->GetParameter(1);
        Double_t CaFit_Mean = CaFit->GetParameter(1);

        Double_t CFit_Sig = CFit->GetParameter(2);
        Double_t CaFit_Sig = CaFit->GetParameter(2);

        Double_t CFit_LowLimit = CFit_Mean - 4*CFit_Sig;
        Double_t CFit_HighLimit = CFit_Mean + 4*CFit_Sig;
        Int_t CFit_LL = h110c->FindBin(CFit_LowLimit) +1; // +1 to ignore underflow bin!
        Int_t CFit_HL = h110c->FindBin(CFit_HighLimit) +1;
        Double_t CFit_Int = h110c->Integral(CFit_LL, CFit_HL);

        if (CaFit_Sig > 0.05) CaFit_Sig = 0.05;
        Double_t CaFit_LowLimit = CaFit_Mean - 4*CaFit_Sig;
        Double_t CaFit_HighLimit = CaFit_Mean + 4*CaFit_Sig;
        Int_t CaFit_LL = h110c->FindBin(CaFit_LowLimit) +1; // +1 to ignore underflow bin!
        Int_t CaFit_HL = h110c->FindBin(CaFit_HighLimit) +1;
        Double_t CaFit_Int = h110c->Integral(CaFit_LL, CaFit_HL);

        cout << CFit_Int << "   " << CaFit_Int << endl;

        TFile f1(BoneOutputFiles[i], "RECREATE");
        h110c->Write();
        CFit->Write();
        CaFit->Write();

        //Define new tree to store parameters in
        TTree* tree = new TTree("Peak_Parameters", "Tree_of_Values");

        tree->Branch("CarbonFitParameters", &CFPar, "CFPar/D");
        tree->Branch("CalciumFitParameters", &CaFPar, "CaFPar/D");

        CFPar = CFit_Const;
        CaFPar = CaFit_Const;
        tree->Fill();
        CFPar = CFit_Mean;
        CaFPar = CaFit_Mean;
        tree->Fill();
        CFPar = CFit_Sig;
        CaFPar = CaFit_Sig;
        tree->Fill();
        CFPar = CFit_Int;
        CaFPar = CaFit_Int;
        tree->Fill();

        f1.Write();
        f1.Close();
        }

    for(Int_t i = 0; i < 8; i++){
        TFile *f = new TFile(TissueInputFiles[i]);
        TF1* CFit = new TF1("CFit", "gaus",  4.2, 4.7);
        CFit->SetLineColor(2);
        TF1* CaFit = new TF1("CaFit", "gaus",  3.7, 3.8);
        CaFit->SetLineColor(4);

        h110c->Fit("CFit", "", "", 4.2, 4.7);
        CFit->Draw("SAME");
        h110c->Fit("CaFit", "", "", 3.7, 3.8);
        CaFit->Draw("SAME");

        Double_t CFit_Const = CFit->GetParameter(0);
        Double_t CaFit_Const = CaFit->GetParameter(0);

        Double_t CFit_Mean = CFit->GetParameter(1);
        Double_t CaFit_Mean = CaFit->GetParameter(1);

        Double_t CFit_Sig = CFit->GetParameter(2);
        Double_t CaFit_Sig = CaFit->GetParameter(2);

        Double_t CFit_LowLimit = CFit_Mean - 4*CFit_Sig;
        Double_t CFit_HighLimit = CFit_Mean + 4*CFit_Sig;
        Int_t CFit_LL = h110c->FindBin(CFit_LowLimit) +1; // +1 to ignore underflow bin!
        Int_t CFit_HL = h110c->FindBin(CFit_HighLimit) +1;
        Double_t CFit_Int = h110c->Integral(CFit_LL, CFit_HL);

        if (CaFit_Sig > 0.05) CaFit_Sig = 0.05;
        Double_t CaFit_LowLimit = CaFit_Mean - 4*CaFit_Sig;
        Double_t CaFit_HighLimit = CaFit_Mean + 4*CaFit_Sig;
        Int_t CaFit_LL = h110c->FindBin(CaFit_LowLimit) +1; // +1 to ignore underflow bin!
        Int_t CaFit_HL = h110c->FindBin(CaFit_HighLimit) +1;
        Double_t CaFit_Int = h110c->Integral(CaFit_LL, CaFit_HL);

        cout << CFit_Int << "   " << CaFit_Int << endl;

        TFile f1(TissueOutputFiles[i], "RECREATE");
        h110c->Write();
        CFit->Write();
        CaFit->Write();

        //Define new tree to store parameters in
        TTree* tree = new TTree("Peak_Parameters", "Tree_of_Values");

        tree->Branch("CarbonFitParameters", &CFPar, "CFPar/D");
        tree->Branch("CalciumFitParameters", &CaFPar, "CaFPar/D");

        CFPar = CFit_Const;
        CaFPar = CaFit_Const;
        tree->Fill();
        CFPar = CFit_Mean;
        CaFPar = CaFit_Mean;
        tree->Fill();
        CFPar = CFit_Sig;
        CaFPar = CaFit_Sig;
        tree->Fill();
        CFPar = CFit_Int;
        CaFPar = CaFit_Int;
        tree->Fill();

        f1.Write();
        f1.Close();
        }

    for(Int_t i = 0; i < 8; i++){
        TFile *f = new TFile(ParaffinInputFiles[i]); // Open the file to clone
        TF1* CFit = new TF1("CFit", "gaus",  4.2, 4.7);
        CFit->SetLineColor(2);
        TF1* CaFit = new TF1("CaFit", "gaus",  3.7, 3.8);
        CaFit->SetLineColor(4);

        h110c->Fit("CFit", "", "", 4.2, 4.7);
        CFit->Draw("SAME");
        h110c->Fit("CaFit", "", "", 3.7, 3.8);
        CaFit->Draw("SAME");

        Double_t CFit_Const = CFit->GetParameter(0);
        Double_t CaFit_Const = CaFit->GetParameter(0);

        Double_t CFit_Mean = CFit->GetParameter(1);
        Double_t CaFit_Mean = CaFit->GetParameter(1);

        Double_t CFit_Sig = CFit->GetParameter(2);
        Double_t CaFit_Sig = CaFit->GetParameter(2);

        Double_t CFit_LowLimit = CFit_Mean - 4*CFit_Sig;
        Double_t CFit_HighLimit = CFit_Mean + 4*CFit_Sig;
        Int_t CFit_LL = h110c->FindBin(CFit_LowLimit) +1; // +1 to ignore underflow bin!
        Int_t CFit_HL = h110c->FindBin(CFit_HighLimit) +1;
        Double_t CFit_Int = h110c->Integral(CFit_LL, CFit_HL);

        if (CaFit_Sig > 0.05) CaFit_Sig = 0.05;
        Double_t CaFit_LowLimit = CaFit_Mean - 4*CaFit_Sig;
        Double_t CaFit_HighLimit = CaFit_Mean + 4*CaFit_Sig;
        Int_t CaFit_LL = h110c->FindBin(CaFit_LowLimit) +1; // +1 to ignore underflow bin!
        Int_t CaFit_HL = h110c->FindBin(CaFit_HighLimit) +1;
        Double_t CaFit_Int = h110c->Integral(CaFit_LL, CaFit_HL);

        cout << CFit_Int << "   " << CaFit_Int << endl;

        TFile f1(ParaffinOutputFiles[i], "RECREATE");
        h110c->Write();
        CFit->Write();
        CaFit->Write();

        //Define new tree to store parameters in
        TTree* tree = new TTree("Peak_Parameters", "Tree_of_Values");

        tree->Branch("CarbonFitParameters", &CFPar, "CFPar/D");
        tree->Branch("CalciumFitParameters", &CaFPar, "CaFPar/D");

        CFPar = CFit_Const;
        CaFPar = CaFit_Const;
        tree->Fill();
        CFPar = CFit_Mean;
        CaFPar = CaFit_Mean;
        tree->Fill();
        CFPar = CFit_Sig;
        CaFPar = CaFit_Sig;
        tree->Fill();
        CFPar = CFit_Int;
        CaFPar = CaFit_Int;
        tree->Fill();

        f1.Write();
        f1.Close();
        }
}
