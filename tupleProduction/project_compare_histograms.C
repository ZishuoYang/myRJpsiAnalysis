//-----------------------------------------
// Compare histograms of multiple variables
// Zishuo Yang, 2019-08-01
// ----------------------------------------
#include <sstream>
#include <string.h>

void project_compare_histograms()
{
// Set output filepath
TString filepath = "./plots/projection_for_MC/";

// Get input
TFile *inputFile1 = new TFile("~/my_eos/RJpsi/tuples/2012_Data_MD_subset.root");
TFile *inputFile2 = new TFile("~/my_eos/RJpsi/tuples/2012_MC_JpsiMuNu.root");
TTree *myTree1 = (TTree*) inputFile1->Get("DecayTree");
TTree *myTree2 = (TTree*) inputFile2->Get("DecayTree");

// Read tree and fill histogram
TCanvas *c_z = new TCanvas("c_z","c_z");
//c_z->SetLogy();// draw with log scale Y
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

TH1* hist_z2 = new TH1I("hist_z2","Z(q2,El)", 8, 0, 8);
//Double_t q2, El;
myTree2->SetBranchAddress("FitVar_q2", &q2);
myTree2->SetBranchAddress("FitVar_El", &El);

for (Int_t i=0;i<myTree2->GetEntries();i++) {
    Int_t Z;
    myTree2->GetEntry(i);
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
    hist_z2->Fill(Z);
    //if (i>10000) break;//
    }

Double_t scale_z = hist_z2->Integral()/hist_z1->Integral();
hist_z1->Scale(scale_z,"nosw2");
//hist_z2->Scale(scale_z2,"nosw2");
auto max_z = std::max(hist_z1->GetMaximum(),hist_z2->GetMaximum());
hist_z1->SetMaximum(max_z*1.1);
hist_z1->SetTitle("");
hist_z1->GetXaxis()->SetTitle("Z (q^2, E*_mu)");
hist_z1->GetYaxis()->SetTitle("");
hist_z1->SetLineColor(kRed);
hist_z2->SetLineColor(kBlue);
hist_z1->Draw();
gPad->Update();
TPaveStats *st_z1 = (TPaveStats*)hist_z1->FindObject("stats");
st_z1->SetX1NDC(0.58);
st_z1->SetX2NDC(0.78);
hist_z2->Draw("SAMES");
c_z->SaveAs(filepath+"Z_q2_El"+".png");


// Simply draw in canvas
TCanvas *c1 = new TCanvas("c1","c1");
c1->SetLogy();// draw with log scale Y
TString title1 = "MissingMass2";
TString temp1a = "1a";
TString temp1b = "1b";

myTree1->Draw("FitVar_Mmiss2>>"+temp1a+"(50,-10e6,10e6)","","goff");
TH1F *hist1a = (TH1F*)gDirectory->Get(temp1a);
myTree2->Draw("FitVar_Mmiss2>>"+temp1b+"(50,-10e6,10e6)","","goff");
TH1F *hist1b = (TH1F*)gDirectory->Get(temp1b);
Double_t scale1 = (hist1b->Integral() / hist1a->Integral());
hist1a->Scale(scale1,"nosw2");

hist1a->SetLineColor(kRed);
hist1b->SetLineColor(kBlue);
auto max1 = std::max(hist1a->GetMaximum(),hist1b->GetMaximum());
hist1a->SetMaximum(max1*10);
hist1a->SetTitle("");
hist1a->GetXaxis()->SetTitle(title1);
hist1a->GetYaxis()->SetTitle("");
hist1a->Draw();
gPad->Update();
TPaveStats *st_1a = (TPaveStats*)hist1a->FindObject("stats");
st_1a->SetX1NDC(0.58);
st_1a->SetX2NDC(0.78);
hist1b->Draw("SAMES");

c1->SaveAs(filepath+title1+".png");

// Draw in canvas
TCanvas *c2 = new TCanvas("c2","c2");
c2->SetLogy();// draw with log scale Y
TString title2 = "q2";
TString temp2a = "2a";
TString temp2b = "2b";

myTree1->Draw("FitVar_q2>>"+temp2a+"(50,-10e6,1.5e7)","","goff");
TH1F *hist2a = (TH1F*)gDirectory->Get(temp2a);
myTree2->Draw("FitVar_q2>>"+temp2b+"(50,-10e6,1.5e7)","","goff");
TH1F *hist2b = (TH1F*)gDirectory->Get(temp2b);
Double_t scale2 = (hist2b->Integral() / hist2a->Integral());
hist2a->Scale(scale2,"nosw2");

hist2a->SetLineColor(kRed);
hist2b->SetLineColor(kBlue);
auto max2 = std::max(hist2a->GetMaximum(),hist2b->GetMaximum());
hist2a->SetMaximum(max2*10);
hist2a->SetTitle("");
hist2a->GetXaxis()->SetTitle(title2);
hist2a->GetYaxis()->SetTitle("");
hist2a->Draw();
gPad->Update();
TPaveStats *st_2a = (TPaveStats*)hist2a->FindObject("stats");
st_2a->SetX1NDC(0.58);
st_2a->SetX2NDC(0.78);
hist2b->Draw("SAMES");
c2->SaveAs(filepath+title2+".png");

// Draw in canvas
TCanvas *c3 = new TCanvas("c3","c3");
c3->SetLogy();// draw with log scale Y
TString title3 = "El";
TString temp3a = "3a";
TString temp3b = "3b";

myTree1->Draw("FitVar_El>>"+temp3a+"(50,0e6,0.5e4)","","goff");
TH1F *hist3a = (TH1F*)gDirectory->Get(temp3a);
myTree2->Draw("FitVar_El>>"+temp3b+"(50,0e6,0.5e4)","","goff");
TH1F *hist3b = (TH1F*)gDirectory->Get(temp3b);
Double_t scale3 = (hist3b->Integral() / hist3a->Integral());
hist3a->Scale(scale3,"nosw2");

hist3a->SetLineColor(kRed);
hist3b->SetLineColor(kBlue);
auto max3 = std::max(hist3a->GetMaximum(),hist3b->GetMaximum());
hist3a->SetMaximum(max3*10);
hist3a->SetTitle("");
hist3a->GetXaxis()->SetTitle(title3);
hist3a->GetYaxis()->SetTitle("");
hist3a->Draw();
gPad->Update();
TPaveStats *st_3a = (TPaveStats*)hist3a->FindObject("stats");
st_3a->SetX1NDC(0.58);
st_3a->SetX2NDC(0.78);
hist3b->Draw("SAMES");
c3->SaveAs(filepath+title3+".png");

// Draw in canvas
TCanvas *c4 = new TCanvas("c4","c4");
c4->SetLogy();// draw with log scale Y
TString title4 = "TAU";
TString temp4a = "4a";
TString temp4b = "4b";

myTree1->Draw("FitVar_CTAU/(299792458e3)>>"+temp4a+"(20,0e-12,2.2e-12)","","goff");
TH1F *hist4a = (TH1F*)gDirectory->Get(temp4a);
myTree2->Draw("FitVar_CTAU/(299792458e3)>>"+temp4b+"(20,0e-12,2.2e-12)","","goff");
TH1F *hist4b = (TH1F*)gDirectory->Get(temp4b);
Double_t scale4 = (hist4b->Integral() / hist4a->Integral());
hist4a->Scale(scale4,"nosw2");

hist4a->SetLineColor(kRed);
hist4b->SetLineColor(kBlue);
auto max4 = std::max(hist4a->GetMaximum(),hist4b->GetMaximum());
hist4a->SetMaximum(max4*10);
hist4a->SetTitle("");
hist4a->GetXaxis()->SetTitle(title4);
hist4a->GetYaxis()->SetTitle("");
hist4a->Draw();
gPad->Update();
TPaveStats *st_4a = (TPaveStats*)hist4a->FindObject("stats");
st_4a->SetX1NDC(0.58);
st_4a->SetX2NDC(0.78);
hist4b->Draw("SAMES");
c4->SaveAs(filepath+title4+".png");

}

