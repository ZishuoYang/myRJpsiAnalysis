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

// // Read tree and fill histogram
// TCanvas *c_z = new TCanvas("c_z","c_z");
// //c_z->SetLogy();// draw with log scale Y
// TH1* hist_z1 = new TH1I("hist_z1","Z(q2,El)", 8, 0, 8);
// Double_t q2, El;
// myTree1->SetBranchAddress("FitVar_q2", &q2);
// myTree1->SetBranchAddress("FitVar_El", &El);
// 
// for (Int_t i=0;i<myTree1->GetEntries();i++) {
//     Int_t Z;
//     myTree1->GetEntry(i);
//     if (q2<7.15e6) {
//         if (El>=0. && El<680.){Z=0;}
//         else if (El>=680. && El<1150.){Z=1;}
//         else if (El>=1150. && El<1640.){Z=2;}
//         else if (El>=1640.){Z=3;}
//         else {cout<<"wrong El value"<<endl;}
//         }
//     else {
//         if (El>=0. && El<680.){Z=4;}
//         else if (El>=680. && El<1150.){Z=5;}
//         else if (El>=1150. && El<1640.){Z=6;}
//         else if (El>=1640.){Z=7;}
//         else {cout<<"wrong El value"<<endl;}
//         }
//     hist_z1->Fill(Z);
//     if (i>10000) break;//
//     }
// 
// TH1* hist_z2 = new TH1I("hist_z2","Z(q2,El)", 8, 0, 8);
// //Double_t q2, El;
// myTree2->SetBranchAddress("FitVar_q2", &q2);
// myTree2->SetBranchAddress("FitVar_El", &El);
// 
// for (Int_t i=0;i<myTree2->GetEntries();i++) {
//     Int_t Z;
//     myTree2->GetEntry(i);
//     if (q2<7.15e6) {
//         if (El>=0. && El<680.){Z=0;}
//         else if (El>=680. && El<1150.){Z=1;}
//         else if (El>=1150. && El<1640.){Z=2;}
//         else if (El>=1640.){Z=3;}
//         else {cout<<"wrong El value"<<endl;}
//         }
//     else {
//         if (El>=0. && El<680.){Z=4;}
//         else if (El>=680. && El<1150.){Z=5;}
//         else if (El>=1150. && El<1640.){Z=6;}
//         else if (El>=1640.){Z=7;}
//         else {cout<<"wrong El value"<<endl;}
//         }
//     hist_z2->Fill(Z);
//     if (i>10000) break;//
//     }
// 
// Double_t scale_z = hist_z2->Integral()/hist_z1->Integral();
// hist_z1->Scale(scale_z,"nosw2");
// auto max_z = std::max(hist_z1->GetMaximum(),hist_z2->GetMaximum());
// hist_z1->SetMaximum(max_z*1.1);
// hist_z1->SetTitle("");
// hist_z1->GetXaxis()->SetTitle("Z (q^2, E*_mu)");
// hist_z1->GetYaxis()->SetTitle("");
// hist_z1->SetLineColor(kRed);
// hist_z2->SetLineColor(kBlue);
// hist_z1->SetMinimum(0);
// hist_z1->Draw();
// gPad->Update();
// TPaveStats *st_z1 = (TPaveStats*)hist_z1->FindObject("stats");
// st_z1->SetX1NDC(0.58);
// st_z1->SetX2NDC(0.78);
// hist_z2->Draw("SAMES");
// c_z->SaveAs(filepath+"Z_q2_El"+".png");


// Simply draw in canvas
TCanvas *c1 = new TCanvas("c1","c1");
c1->SetLogy();
c1->SetGridx();
c1->SetGridy();
c1->SetTickx(1);
c1->SetTicky(1);
TString title1 = "MissingMass2";
TString temp1a = "1a";
TString temp1b = "1b";
TString approxSelection = "Jpsi_L0DiMuonDecision_TOS==1 && Jpsi_Hlt2DiMuonDetachedJPsiDecision_TOS==1 && BachMu_IPCHI2_OWNPV>4.8 && BachMu_PT>750 && Bc_OWNPV_CHI2<25 && Bc_DOCA<0.15 && Bc_ISOLATION_BDT<0.2 && BachMu_ProbNNmu>0.5"; // cuts to quickly approx. sig/norm selection

myTree1->Draw("FitVar_Mmiss2>>"+temp1a+"(25,-5e6,10e6)","BachMu_PIDmu<4","goff");
TH1F *hist1a = (TH1F*)gDirectory->Get(temp1a);
myTree2->Draw("FitVar_Mmiss2>>"+temp1b+"(25,-5e6,10e6)", approxSelection, "goff");
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
hist1a->SetMinimum(1);
hist1a->Draw();
gPad->Update();
TPaveStats *st_1a = (TPaveStats*)hist1a->FindObject("stats");
st_1a->SetX1NDC(0.58);
st_1a->SetX2NDC(0.78);
hist1b->Draw("SAMES");

// Add Legend
// c1->BuildLegend();
TLegend *leg1 = new TLegend(0.15,0.15,0.50,0.35,NULL,"brNDC");
leg1->SetBorderSize(1);
leg1->SetLineColor(1);
leg1->SetLineStyle(1);
leg1->SetLineWidth(1);
leg1->SetFillColor(0);
leg1->SetFillStyle(1001);

TLegendEntry *entry1=leg1->AddEntry("1b","2012 MC Bc2JpsiMuNu","lpf");
entry1->SetFillStyle(1001);
entry1->SetLineStyle(1);
entry1->SetLineWidth(1);
entry1->SetMarkerColor(1);
entry1->SetMarkerStyle(1);
entry1->SetMarkerSize(1);
entry1->SetTextFont(42);

entry1=leg1->AddEntry("1a","2012 Data subset PIDmu<4","lpflpf");
entry1->SetFillStyle(1001);
entry1->SetLineStyle(1);
entry1->SetLineWidth(1);
entry1->SetMarkerColor(1);
entry1->SetMarkerStyle(1);
entry1->SetMarkerSize(1);
entry1->SetTextFont(42);
leg1->Draw();

c1->Modified();
c1->SaveAs(filepath+title1+".png");

// // Draw in canvas
// TCanvas *c2 = new TCanvas("c2","c2");
// c2->SetLogy();
// c2->SetGridx();
// c2->SetGridy();
// c2->SetTickx(1);
// c2->SetTicky(1);
// c2->SetLogy();// draw with log scale Y
// TString title2 = "q2";
// TString temp2a = "2a";
// TString temp2b = "2b";
// 
// myTree1->Draw("FitVar_q2>>"+temp2a+"(50,-10e6,1.5e7)","","goff");
// TH1F *hist2a = (TH1F*)gDirectory->Get(temp2a);
// myTree2->Draw("FitVar_q2>>"+temp2b+"(50,-10e6,1.5e7)","","goff");
// TH1F *hist2b = (TH1F*)gDirectory->Get(temp2b);
// Double_t scale2 = (hist2b->Integral() / hist2a->Integral());
// hist2a->Scale(scale2,"nosw2");
// 
// hist2a->SetLineColor(kRed);
// hist2b->SetLineColor(kBlue);
// auto max2 = std::max(hist2a->GetMaximum(),hist2b->GetMaximum());
// hist2a->SetMaximum(max2*10);
// hist2a->SetTitle("");
// hist2a->GetXaxis()->SetTitle(title2);
// hist2a->GetYaxis()->SetTitle("");
// hist2a->SetMinimum(1);
// hist2a->Draw();
// gPad->Update();
// TPaveStats *st_2a = (TPaveStats*)hist2a->FindObject("stats");
// st_2a->SetX1NDC(0.58);
// st_2a->SetX2NDC(0.78);
// hist2b->Draw("SAMES");
// 
// // Add Legend
// TLegend *leg2 = new TLegend(0.15,0.15,0.50,0.35,NULL,"brNDC");
// leg2->SetBorderSize(1);
// leg2->SetLineColor(1);
// leg2->SetLineStyle(1);
// leg2->SetLineWidth(1);
// leg2->SetFillColor(0);
// leg2->SetFillStyle(1001);
// 
// TLegendEntry *entry2=leg2->AddEntry("2b","2012 MC Bc2JpsiMuNu","lpf");
// entry2->SetFillStyle(1001);
// entry2->SetLineStyle(1);
// entry2->SetLineWidth(1);
// entry2->SetMarkerColor(1);
// entry2->SetMarkerStyle(1);
// entry2->SetMarkerSize(1);
// entry2->SetTextFont(42);
// 
// entry2=leg2->AddEntry("2a","2012 Data subset (rescaled)","lpflpf");
// entry2->SetFillStyle(1001);
// entry2->SetLineStyle(1);
// entry2->SetLineWidth(1);
// entry2->SetMarkerColor(1);
// entry2->SetMarkerStyle(1);
// entry2->SetMarkerSize(1);
// entry2->SetTextFont(42);
// leg2->Draw();
// 
// c2->Modified();
// c2->SaveAs(filepath+title2+".png");
// 
// // Draw in canvas
// TCanvas *c3 = new TCanvas("c3","c3");
// c3->SetLogy();
// c3->SetGridx();
// c3->SetGridy();
// c3->SetTickx(1);
// c3->SetTicky(1);
// c3->SetLogy();// draw with log scale Y
// TString title3 = "El";
// TString temp3a = "3a";
// TString temp3b = "3b";
// 
// myTree1->Draw("FitVar_El>>"+temp3a+"(50,0e6,0.5e4)","","goff");
// TH1F *hist3a = (TH1F*)gDirectory->Get(temp3a);
// myTree2->Draw("FitVar_El>>"+temp3b+"(50,0e6,0.5e4)","","goff");
// TH1F *hist3b = (TH1F*)gDirectory->Get(temp3b);
// Double_t scale3 = (hist3b->Integral() / hist3a->Integral());
// hist3a->Scale(scale3,"nosw2");
// 
// hist3a->SetLineColor(kRed);
// hist3b->SetLineColor(kBlue);
// auto max3 = std::max(hist3a->GetMaximum(),hist3b->GetMaximum());
// hist3a->SetMaximum(max3*10);
// hist3a->SetTitle("");
// hist3a->GetXaxis()->SetTitle(title3);
// hist3a->GetYaxis()->SetTitle("");
// hist3a->SetMinimum(1);
// hist3a->Draw();
// gPad->Update();
// TPaveStats *st_3a = (TPaveStats*)hist3a->FindObject("stats");
// st_3a->SetX1NDC(0.58);
// st_3a->SetX2NDC(0.78);
// hist3b->Draw("SAMES");
// 
// // Add Legend
// TLegend *leg3 = new TLegend(0.15,0.15,0.50,0.35,NULL,"brNDC");
// leg3->SetBorderSize(1);
// leg3->SetLineColor(1);
// leg3->SetLineStyle(1);
// leg3->SetLineWidth(1);
// leg3->SetFillColor(0);
// leg3->SetFillStyle(1001);
// 
// TLegendEntry *entry3=leg3->AddEntry("3b","2012 MC Bc2JpsiMuNu","lpf");
// entry3->SetFillStyle(1001);
// entry3->SetLineStyle(1);
// entry3->SetLineWidth(1);
// entry3->SetMarkerColor(1);
// entry3->SetMarkerStyle(1);
// entry3->SetMarkerSize(1);
// entry3->SetTextFont(42);
// 
// entry3=leg3->AddEntry("3a","2012 Data subset (rescaled)","lpflpf");
// entry3->SetFillStyle(1001);
// entry3->SetLineStyle(1);
// entry3->SetLineWidth(1);
// entry3->SetMarkerColor(1);
// entry3->SetMarkerStyle(1);
// entry3->SetMarkerSize(1);
// entry3->SetTextFont(42);
// leg3->Draw();
// 
// c3->Modified();
// c3->SaveAs(filepath+title3+".png");
// 
// // Draw in canvas
// TCanvas *c4 = new TCanvas("c4","c4");
// c4->SetLogy();
// c4->SetGridx();
// c4->SetGridy();
// c4->SetTickx(1);
// c4->SetTicky(1);
// c4->SetLogy();// draw with log scale Y
// TString title4 = "TAU";
// TString temp4a = "4a";
// TString temp4b = "4b";
// 
// myTree1->Draw("FitVar_CTAU/(299792458e3)>>"+temp4a+"(20,0e-12,2.2e-12)","","goff");
// TH1F *hist4a = (TH1F*)gDirectory->Get(temp4a);
// myTree2->Draw("FitVar_CTAU/(299792458e3)>>"+temp4b+"(20,0e-12,2.2e-12)","","goff");
// TH1F *hist4b = (TH1F*)gDirectory->Get(temp4b);
// Double_t scale4 = (hist4b->Integral() / hist4a->Integral());
// hist4a->Scale(scale4,"nosw2");
// 
// hist4a->SetLineColor(kRed);
// hist4b->SetLineColor(kBlue);
// auto max4 = std::max(hist4a->GetMaximum(),hist4b->GetMaximum());
// hist4a->SetMaximum(max4*10);
// hist4a->SetTitle("");
// hist4a->GetXaxis()->SetTitle(title4);
// hist4a->GetYaxis()->SetTitle("");
// hist4a->SetMinimum(1);
// hist4a->Draw();
// gPad->Update();
// TPaveStats *st_4a = (TPaveStats*)hist4a->FindObject("stats");
// st_4a->SetX1NDC(0.58);
// st_4a->SetX2NDC(0.78);
// hist4b->Draw("SAMES");
// 
// // Add Legend
// TLegend *leg4 = new TLegend(0.15,0.15,0.50,0.35,NULL,"brNDC");
// leg4->SetBorderSize(1);
// leg4->SetLineColor(1);
// leg4->SetLineStyle(1);
// leg4->SetLineWidth(1);
// leg4->SetFillColor(0);
// leg4->SetFillStyle(1001);
// 
// TLegendEntry *entry4=leg4->AddEntry("4b","2012 MC Bc2JpsiMuNu","lpf");
// entry4->SetFillStyle(1001);
// entry4->SetLineStyle(1);
// entry4->SetLineWidth(1);
// entry4->SetMarkerColor(1);
// entry4->SetMarkerStyle(1);
// entry4->SetMarkerSize(1);
// entry4->SetTextFont(42);
// 
// entry4=leg4->AddEntry("4a","2012 Data subset (rescaled)","lpflpf");
// entry4->SetFillStyle(1001);
// entry4->SetLineStyle(1);
// entry4->SetLineWidth(1);
// entry4->SetMarkerColor(1);
// entry4->SetMarkerStyle(1);
// entry4->SetMarkerSize(1);
// entry4->SetTextFont(42);
// leg4->Draw();
// 
// c4->Modified();
// c4->SaveAs(filepath+title4+".png");

}

