//-----------------------------------------
// Project histograms of multiple variables
// Zishuo Yang, 2019-10-01
// ----------------------------------------
#include <sstream>
#include <string.h>

void projection_histograms()
{
//-- Set output filepath
TString filepath = "./plots/projection_for_MC/";
TString id = "JpsiMuNu_";

//-- Get input
TFile *inputFile1 = new TFile("~/my_eos/RJpsi/tuples/2012_MC_JpsiMuNu.root");
TTree *myTree1 = (TTree*) inputFile1->Get("DecayTree");

//-- Read tree and fill histogram
TCanvas *c_z = new TCanvas("c_z","c_z");
TH1* hist_z1 = new TH1I("hist_z1","Z(q2,El)", 8, 0, 8);
Double_t q2, El;
myTree1->SetBranchAddress("FitVar_q2", &q2);
myTree1->SetBranchAddress("FitVar_El", &El);

for (Int_t i=0;i<myTree1->GetEntries();i++) {
    Int_t Z;
    myTree1->GetEntry(i);
    if (q2<7.15e6) {
        if (El>=0. && El<680.){Z=0;}
        else if (El>=680. && El<1150.){Z=1;}
        else if (El>=1150. && El<1640.){Z=2;}
        else if (El>=1640.){Z=3;}
        else {cout<<"wrong El value"<<endl;}
        }
    else {
        if (El>=0. && El<680.){Z=4;}
        else if (El>=680. && El<1150.){Z=5;}
        else if (El>=1150. && El<1640.){Z=6;}
        else if (El>=1640.){Z=7;}
        else {cout<<"wrong El value"<<endl;}
        }
    hist_z1->Fill(Z);
    //if (i>10000) break;//
    }
hist_z1->SetTitle("");
hist_z1->GetXaxis()->SetTitle("Z (q^2, E*_mu)");
hist_z1->GetYaxis()->SetTitle("");
hist_z1->SetLineColor(kBlue);
hist_z1->Draw();
c_z->SaveAs(filepath+id+"Z"+".png");

// Simply draw in canvas
TCanvas *c1 = new TCanvas("c1","c1");
TString title1 = "MissingMass2";
TString temp1a = "1a";

myTree1->Draw("FitVar_Mmiss2>>"+temp1a+"(50,-10e6,10e6)","","goff");
TH1F *hist1a = (TH1F*)gDirectory->Get(temp1a);

hist1a->SetLineColor(kBlue);
hist1a->SetTitle("");
hist1a->GetXaxis()->SetTitle(title1);
hist1a->GetYaxis()->SetTitle("");
hist1a->Draw();
c1->SaveAs(filepath+id+title1+".png");

// Draw in canvas
TCanvas *c2 = new TCanvas("c2","c2");
TString title2 = "q2";
TString temp2a = "2a";

myTree1->Draw("FitVar_q2>>"+temp2a+"(50,-10e6,1.5e7)","","goff");
TH1F *hist2a = (TH1F*)gDirectory->Get(temp2a);

hist2a->SetLineColor(kBlue);
hist2a->SetTitle("");
hist2a->GetXaxis()->SetTitle(title2);
hist2a->GetYaxis()->SetTitle("");
hist2a->Draw();
c2->SaveAs(filepath+id+title2+".png");

// Draw in canvas
TCanvas *c3 = new TCanvas("c3","c3");
TString title3 = "El";
TString temp3a = "3a";

myTree1->Draw("FitVar_El>>"+temp3a+"(50,0e6,0.5e4)","","goff");
TH1F *hist3a = (TH1F*)gDirectory->Get(temp3a);

hist3a->SetLineColor(kBlue);
hist3a->SetTitle("");
hist3a->GetXaxis()->SetTitle(title3);
hist3a->GetYaxis()->SetTitle("");
hist3a->Draw();
c3->SaveAs(filepath+id+title3+".png");

// Draw in canvas
TCanvas *c4 = new TCanvas("c4","c4");
TString title4 = "TAU";
TString temp4a = "4a";

myTree1->Draw("FitVar_CTAU/(299792458e3)>>"+temp4a+"(20,0e-12,2.2e-12)","","goff");
TH1F *hist4a = (TH1F*)gDirectory->Get(temp4a);
hist4a->SetLineColor(kBlue);
hist4a->SetTitle("");
hist4a->GetXaxis()->SetTitle(title4);
hist4a->GetYaxis()->SetTitle("");
hist4a->Draw();
c4->SaveAs(filepath+id+title4+".png");
}

