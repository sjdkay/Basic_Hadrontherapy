#include "./includes.h"


void Peak_Analysis_V2(){

    double CFPar[5], CaFPar[5], CaPar, CPar;

    TFile *f = new TFile("/scratch/IAA/Proton_Therapy/Basic_Hadrontherapy/build/SimulationOutputs/Hybrid/10e8_9cm_Tissue_1cm_Bone.root"); // Open the file to clone

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

    //cout << CaPeakCounts << "   " << CPeakCounts << endl;

    TFile f1("/scratch/IAA/Proton_Therapy/Basic_Hadrontherapy/Analysis/Hybrid/10e8_9cm_Tissue_1cm_Bone.root", "RECREATE");
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

    f1.Write();
    f1.Close();

}
