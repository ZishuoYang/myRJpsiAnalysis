//-----------------------------------------
// Compare histograms of multiple variables
// Zishuo Yang, 2019-08-01
// ----------------------------------------
#include <sstream>
#include <string.h>

void compare_histograms()
{
// Set output filepath
TString filepath = "./plots/";

// Get input
TFile *inputFile1 = new TFile("Bc_JpsiTau_MC.root");
TFile *inputFile2 = new TFile("Bc_JpsiMu_MC.root");
TTree *myTree1 = (TTree*) inputFile1->Get("JpsiRecTuple/DecayTree");
TTree *myTree2 = (TTree*) inputFile2->Get("JpsiRecTuple/DecayTree");

// Draw in canvas
TCanvas *c1 = new TCanvas("c1","c1");
TString title1 = "MissingMass2";
TString temp1a = "1a";
TString temp1b = "1b";

myTree1->Draw("FitVar_Mmiss2>>"+temp1a+"(40,-10e6,10e6)","","goff");
TH1F *hist1a = (TH1F*)gDirectory->Get(temp1a);
Double_t scale1a = 1/(hist1a->Integral());
hist1a->Scale(scale1a,"nosw2");

myTree2->Draw("FitVar_Mmiss2>>"+temp1b+"(40,-10e6,10e6)","","goff");
TH1F *hist1b = (TH1F*)gDirectory->Get(temp1b);
Double_t scale1b = 1/(hist1b->Integral());
hist1b->Scale(scale1b,"nosw2");

hist1a->SetLineColor(kRed);
hist1b->SetLineColor(kBlue);
auto max1a = hist1a->GetMaximum();
auto max1b = hist1b->GetMaximum();
auto max1 = std::max(max1a,max1b);
hist1a->SetMaximum(max1*1.1);
hist1a->SetTitle("");
hist1a->GetXaxis()->SetTitle(title1);
hist1a->GetYaxis()->SetTitle("");
//TPaveStats *st = (TPaveStats*)hist1->GetListOfFunctions()->FindObject("stats");
//st->SetX1NDC(0.6);
//st->SetX2NDC(0.8);
hist1a->Draw();
hist1b->Draw("SAMES");
c1->SaveAs(filepath+title1+".png");

// Draw in canvas
TCanvas *c2 = new TCanvas("c2","c2");
TString title2 = "q2";
TString temp2a = "2a";
TString temp2b = "2b";

myTree1->Draw("FitVar_q2>>"+temp2a+"(40,-10e6,1.5e7)","","goff");
TH1F *hist2a = (TH1F*)gDirectory->Get(temp2a);
Double_t scale2a = 1/(hist2a->Integral());
hist2a->Scale(scale2a,"nosw2");

myTree2->Draw("FitVar_q2>>"+temp2b+"(40,-10e6,1.5e7)","","goff");
TH1F *hist2b = (TH1F*)gDirectory->Get(temp2b);
Double_t scale2b = 1/(hist2b->Integral());
hist2b->Scale(scale2b,"nosw2");

hist2a->SetLineColor(kRed);
hist2b->SetLineColor(kBlue);
auto max2a = hist2a->GetMaximum();
auto max2b = hist2b->GetMaximum();
auto max2 = std::max(max2a,max2b);
hist2a->SetMaximum(max2*1.1);
hist2a->SetTitle("");
hist2a->GetXaxis()->SetTitle(title2);
hist2a->GetYaxis()->SetTitle("");
hist2a->Draw();
hist2b->Draw("SAMES");
c2->SaveAs(filepath+title2+".png");

// Draw in canvas
TCanvas *c3 = new TCanvas("c3","c3");
TString title3 = "El";
TString temp3a = "3a";
TString temp3b = "3b";

myTree1->Draw("FitVar_El>>"+temp3a+"(40,0e6,0.5e4)","","goff");
TH1F *hist3a = (TH1F*)gDirectory->Get(temp3a);
Double_t scale3a = 1/(hist3a->Integral());
hist3a->Scale(scale3a,"nosw2");

myTree2->Draw("FitVar_El>>"+temp3b+"(40,0e6,0.5e4)","","goff");
TH1F *hist3b = (TH1F*)gDirectory->Get(temp3b);
Double_t scale3b = 1/(hist3b->Integral());
hist3b->Scale(scale3b,"nosw2");

hist3a->SetLineColor(kRed);
hist3b->SetLineColor(kBlue);
auto max3a = hist3a->GetMaximum();
auto max3b = hist3b->GetMaximum();
auto max3 = std::max(max3a,max3b);
hist3a->SetMaximum(max3*1.1);
hist3a->SetTitle("");
hist3a->GetXaxis()->SetTitle(title3);
hist3a->GetYaxis()->SetTitle("");
hist3a->Draw();
hist3b->Draw("SAMES");
c3->SaveAs(filepath+title3+".png");

// Draw in canvas
TCanvas *c4 = new TCanvas("c4","c4");
TString title4 = "TAU";
TString temp4a = "4a";
TString temp4b = "4b";

myTree1->Draw("FitVar_CTAU/(299792458e3)>>"+temp4a+"(20,0e-12,2.2e-12)","","goff");
TH1F *hist4a = (TH1F*)gDirectory->Get(temp4a);
Double_t scale4a = 1/(hist4a->Integral());
hist4a->Scale(scale4a,"nosw2");

myTree2->Draw("FitVar_CTAU/(299792458e3)>>"+temp4b+"(20,0e-12,2.2e-12)","","goff");
TH1F *hist4b = (TH1F*)gDirectory->Get(temp4b);
Double_t scale4b = 1/(hist4b->Integral());
hist4b->Scale(scale4b,"nosw2");

hist4a->SetLineColor(kRed);
hist4b->SetLineColor(kBlue);
auto max4a = hist4a->GetMaximum();
auto max4b = hist4b->GetMaximum();
auto max4 = std::max(max4a,max4b);
hist4a->SetMaximum(max4*1.1);
hist4a->SetTitle("");
hist4a->GetXaxis()->SetTitle(title4);
hist4a->GetYaxis()->SetTitle("");
hist4a->Draw();
hist4b->Draw("SAMES");
c4->SaveAs(filepath+title4+".png");
}

