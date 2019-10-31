//-----------------------------------------
// Compare histograms of multiple variables
// Zishuo Yang, 2019-08-01
// ----------------------------------------
#include <sstream>
#include <string.h>

void compare_run1_run2()
{
// Set output filepath
TString filepath = "./plots/compare_run1_run2/";

// Get input
TFile *inputFile1 = new TFile("~/my_eos/RJpsi/tuples/2012_Data_MD_subset.root");
TFile *inputFile2 = new TFile("~/my_eos/RJpsi/tuples/2018_Data_MD_subset.root");
TFile *inputFile3 = new TFile("~/my_eos/RJpsi/tuples/2012_MC_JpsiMuNu.root");
TFile *inputFile4 = new TFile("~/my_eos/RJpsi/tuples/2012_MC_JpsiTauNu.root");
//TFile *inputFile4 = new TFile("~/my_eos/RJpsi/tuples/2012_MC_Psi2SMu.root");
//TFile *inputFile5 = new TFile("~/my_eos/RJpsi/tuples/2012_MC_JpsiDx.root");
TTree *myTree1 = (TTree*) inputFile1->Get("DecayTree");
TTree *myTree2 = (TTree*) inputFile2->Get("DecayTree");
TTree *myTree3 = (TTree*) inputFile3->Get("DecayTree");
TTree *myTree4 = (TTree*) inputFile4->Get("DecayTree");
//TTree *myTree5 = (TTree*) inputFile5->Get("DecayTree");

TString approxSelection = "Jpsi_L0DiMuonDecision_TOS==1 && Jpsi_Hlt2DiMuonDetachedJPsiDecision_TOS==1 && BachMu_IPCHI2_OWNPV>4.8 && BachMu_PT>750 && Bc_OWNPV_CHI2<25 && Bc_DOCA<0.15 && Bc_ISOLATION_BDT<0.2 && BachMu_ProbNNmu>0.5"; // cuts to quickly approx. sig/norm selection

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


///// Simply draw in canvas
///TCanvas *c1 = new TCanvas("c1","c1");
/////c1->SetLogy();
///c1->SetGridx();
///c1->SetGridy();
///c1->SetTickx(1);
///c1->SetTicky(1);
///TString title1 = "MissingMass2";
///TString temp1a = "1a";
///TString temp1b = "1b";
///TString temp1c = "1c";
///TString temp1d = "1d";
/////TString temp1e = "1e";
///
///myTree1->Draw("FitVar_Mmiss2>>"+temp1a+"(25,-5e6,10e6)", approxSelection,"goff");
///TH1F *hist1a = (TH1F*)gDirectory->Get(temp1a);
///myTree2->Draw("FitVar_Mmiss2>>"+temp1b+"(25,-5e6,10e6)", approxSelection, "goff");
///TH1F *hist1b = (TH1F*)gDirectory->Get(temp1b);
///myTree3->Draw("FitVar_Mmiss2>>"+temp1c+"(25,-5e6,10e6)", approxSelection, "goff");
///TH1F *hist1c = (TH1F*)gDirectory->Get(temp1c);
///myTree4->Draw("FitVar_Mmiss2>>"+temp1d+"(25,-5e6,10e6)", approxSelection, "goff");
///TH1F *hist1d = (TH1F*)gDirectory->Get(temp1d);
/////myTree5->Draw("FitVar_Mmiss2>>"+temp1e+"(25,-5e6,10e6)", approxSelection, "goff");
/////TH1F *hist1e = (TH1F*)gDirectory->Get(temp1e);
///Double_t scale1 = (hist1b->Integral() / hist1a->Integral());
///hist1a->Scale(scale1,"nosw2");
///scale1 = (hist1b->Integral() / hist1c->Integral());
///hist1c->Scale(0.15*scale1,"nosw2");
///scale1 = (hist1b->Integral() / hist1d->Integral());
///hist1d->Scale(0.15*scale1,"nosw2");
///
///hist1a->SetLineColor(kRed);
///hist1b->SetLineColor(kBlue);
///hist1c->SetLineColor(kViolet);
///hist1d->SetLineColor(kTeal);
/////hist1e->SetLineColor(kGreen);
///auto max1 = std::max(hist1a->GetMaximum(),hist1b->GetMaximum());
///hist1a->SetMaximum(max1*1.2);
///hist1a->SetTitle("");
///hist1a->GetXaxis()->SetTitle(title1);
///hist1a->GetYaxis()->SetTitle("");
///hist1a->SetMinimum(0);
/////hist1a->SetMinimum(1);
///hist1a->Draw();
///gPad->Update();
///gStyle->SetOptStat(0);
/////TPaveStats *st_1a = (TPaveStats*)hist1a->FindObject("stats");
/////st_1a->SetX1NDC(0.58);
/////st_1a->SetX2NDC(0.78);
///hist1b->Draw("SAME");
///hist1c->Draw("SAME");
///hist1d->Draw("SAME");
/////hist1e->Draw("SAME");
///
///// Add Legend
///// c1->BuildLegend();
///TLegend *leg1 = new TLegend(0.55,0.70,0.90,0.90,NULL,"brNDC");
///leg1->SetBorderSize(1);
///leg1->SetLineColor(1);
///leg1->SetLineStyle(1);
///leg1->SetLineWidth(1);
///leg1->SetFillColor(0);
///leg1->SetFillStyle(1001);
///
///TLegendEntry *entry1=leg1->AddEntry("1a","2012 Data subset","lpf");
///entry1->SetFillStyle(1001);
///entry1->SetLineStyle(1);
///entry1->SetLineWidth(1);
///entry1->SetMarkerColor(1);
///entry1->SetMarkerStyle(1);
///entry1->SetMarkerSize(1);
///entry1->SetTextFont(42);
///
///entry1=leg1->AddEntry("1b","2018 Data subset","lpflpf");
///entry1->SetFillStyle(1001);
///entry1->SetLineStyle(1);
///entry1->SetLineWidth(1);
///entry1->SetMarkerColor(1);
///entry1->SetMarkerStyle(1);
///entry1->SetMarkerSize(1);
///entry1->SetTextFont(42);
///
///entry1=leg1->AddEntry("1c","2012 MC Bc->JpsiMuNu","lpflpf");
///entry1->SetFillStyle(1001);
///entry1->SetLineStyle(1);
///entry1->SetLineWidth(1);
///entry1->SetMarkerColor(1);
///entry1->SetMarkerStyle(1);
///entry1->SetMarkerSize(1);
///entry1->SetTextFont(42);
///
///entry1=leg1->AddEntry("1d","2012 MC Bc->JpsiTauNu","lpflpf");
///entry1->SetFillStyle(1001);
///entry1->SetLineStyle(1);
///entry1->SetLineWidth(1);
///entry1->SetMarkerColor(1);
///entry1->SetMarkerStyle(1);
///entry1->SetMarkerSize(1);
///entry1->SetTextFont(42);
///
/////entry1=leg1->AddEntry("1e","2012 MC Bc->JpsiDx","lpflpf");
/////entry1->SetFillStyle(1001);
/////entry1->SetLineStyle(1);
/////entry1->SetLineWidth(1);
/////entry1->SetMarkerColor(1);
/////entry1->SetMarkerStyle(1);
/////entry1->SetMarkerSize(1);
/////entry1->SetTextFont(42);
///
///leg1->Draw();
///
///c1->Modified();
///c1->SaveAs(filepath+title1+".png");
///
///// Draw in canvas
///TCanvas *c2 = new TCanvas("c2","c2");
///c2->SetGridx();
///c2->SetGridy();
///c2->SetTickx(1);
///c2->SetTicky(1);
/////c2->SetLogy();// draw with log scale Y
///TString title2 = "q2";
///TString temp2a = "2a";
///TString temp2b = "2b";
///
///myTree1->Draw("FitVar_q2>>"+temp2a+"(50,-10e6,1.5e7)", approxSelection,"goff");
///TH1F *hist2a = (TH1F*)gDirectory->Get(temp2a);
///myTree2->Draw("FitVar_q2>>"+temp2b+"(50,-10e6,1.5e7)", approxSelection,"goff");
///TH1F *hist2b = (TH1F*)gDirectory->Get(temp2b);
///Double_t scale2 = (hist2b->Integral() / hist2a->Integral());
///hist2a->Scale(scale2,"nosw2");
///
///hist2a->SetLineColor(kRed);
///hist2b->SetLineColor(kBlue);
///auto max2 = std::max(hist2a->GetMaximum(),hist2b->GetMaximum());
///hist2a->SetMaximum(max2*1.2);
///hist2a->SetTitle("");
///hist2a->GetXaxis()->SetTitle(title2);
///hist2a->GetYaxis()->SetTitle("");
/////hist2a->SetMinimum(1);
///hist2a->SetMinimum(0);
///hist2a->Draw();
/////gPad->Update();
/////TPaveStats *st_2a = (TPaveStats*)hist2a->FindObject("stats");
/////st_2a->SetX1NDC(0.58);
/////st_2a->SetX2NDC(0.78);
///hist2b->Draw("SAME");
///
///// Add Legend
///TLegend *leg2 = new TLegend(0.15,0.70,0.50,0.90,NULL,"brNDC");
///leg2->SetBorderSize(1);
///leg2->SetLineColor(1);
///leg2->SetLineStyle(1);
///leg2->SetLineWidth(1);
///leg2->SetFillColor(0);
///leg2->SetFillStyle(1001);
///
///TLegendEntry *entry2=leg2->AddEntry("2b","2018 Data subset","lpf");
///entry2->SetFillStyle(1001);
///entry2->SetLineStyle(1);
///entry2->SetLineWidth(1);
///entry2->SetMarkerColor(1);
///entry2->SetMarkerStyle(1);
///entry2->SetMarkerSize(1);
///entry2->SetTextFont(42);
///
///entry2=leg2->AddEntry("2a","2012 Data subset","lpflpf");
///entry2->SetFillStyle(1001);
///entry2->SetLineStyle(1);
///entry2->SetLineWidth(1);
///entry2->SetMarkerColor(1);
///entry2->SetMarkerStyle(1);
///entry2->SetMarkerSize(1);
///entry2->SetTextFont(42);
///leg2->Draw();
///
///c2->Modified();
///c2->SaveAs(filepath+title2+".png");
///
///// Draw in canvas
///TCanvas *c3 = new TCanvas("c3","c3");
///c3->SetGridx();
///c3->SetGridy();
///c3->SetTickx(1);
///c3->SetTicky(1);
/////c3->SetLogy();// draw with log scale Y
///TString title3 = "El";
///TString temp3a = "3a";
///TString temp3b = "3b";
///
///myTree1->Draw("FitVar_El>>"+temp3a+"(50,0e6,0.5e4)", approxSelection,"goff");
///TH1F *hist3a = (TH1F*)gDirectory->Get(temp3a);
///myTree2->Draw("FitVar_El>>"+temp3b+"(50,0e6,0.5e4)", approxSelection,"goff");
///TH1F *hist3b = (TH1F*)gDirectory->Get(temp3b);
///Double_t scale3 = (hist3b->Integral() / hist3a->Integral());
///hist3a->Scale(scale3,"nosw2");
///
///hist3a->SetLineColor(kRed);
///hist3b->SetLineColor(kBlue);
///auto max3 = std::max(hist3a->GetMaximum(),hist3b->GetMaximum());
///hist3a->SetMaximum(max3*1.2);
///hist3a->SetTitle("");
///hist3a->GetXaxis()->SetTitle(title3);
///hist3a->GetYaxis()->SetTitle("");
///hist3a->SetMinimum(0);
///hist3a->Draw();
/////gPad->Update();
/////TPaveStats *st_3a = (TPaveStats*)hist3a->FindObject("stats");
/////st_3a->SetX1NDC(0.58);
/////st_3a->SetX2NDC(0.78);
///hist3b->Draw("SAME");
///
///// Add Legend
///TLegend *leg3 = new TLegend(0.55,0.70,0.90,0.90,NULL,"brNDC");
///leg3->SetBorderSize(1);
///leg3->SetLineColor(1);
///leg3->SetLineStyle(1);
///leg3->SetLineWidth(1);
///leg3->SetFillColor(0);
///leg3->SetFillStyle(1001);
///
///TLegendEntry *entry3=leg3->AddEntry("3b","2018 Data subset","lpf");
///entry3->SetFillStyle(1001);
///entry3->SetLineStyle(1);
///entry3->SetLineWidth(1);
///entry3->SetMarkerColor(1);
///entry3->SetMarkerStyle(1);
///entry3->SetMarkerSize(1);
///entry3->SetTextFont(42);
///
///entry3=leg3->AddEntry("3a","2012 Data subset","lpflpf");
///entry3->SetFillStyle(1001);
///entry3->SetLineStyle(1);
///entry3->SetLineWidth(1);
///entry3->SetMarkerColor(1);
///entry3->SetMarkerStyle(1);
///entry3->SetMarkerSize(1);
///entry3->SetTextFont(42);
///leg3->Draw();
///
///c3->Modified();
///c3->SaveAs(filepath+title3+".png");
///
///// Draw in canvas
///TCanvas *c4 = new TCanvas("c4","c4");
///c4->SetGridx();
///c4->SetGridy();
///c4->SetTickx(1);
///c4->SetTicky(1);
/////c4->SetLogy();// draw with log scale Y
///TString title4 = "TAU";
///TString temp4a = "4a";
///TString temp4b = "4b";
///
///myTree1->Draw("FitVar_CTAU/(299792458e3)>>"+temp4a+"(20,0e-12,2.2e-12)", approxSelection,"goff");
///TH1F *hist4a = (TH1F*)gDirectory->Get(temp4a);
///myTree2->Draw("FitVar_CTAU/(299792458e3)>>"+temp4b+"(20,0e-12,2.2e-12)", approxSelection,"goff");
///TH1F *hist4b = (TH1F*)gDirectory->Get(temp4b);
///Double_t scale4 = (hist4b->Integral() / hist4a->Integral());
///hist4a->Scale(scale4,"nosw2");
///
///hist4a->SetLineColor(kRed);
///hist4b->SetLineColor(kBlue);
///auto max4 = std::max(hist4a->GetMaximum(),hist4b->GetMaximum());
///hist4a->SetMaximum(max4*1.2);
///hist4a->SetTitle("");
///hist4a->GetXaxis()->SetTitle(title4);
///hist4a->GetYaxis()->SetTitle("");
///hist4a->SetMinimum(0);
///hist4a->Draw();
/////gPad->Update();
/////TPaveStats *st_4a = (TPaveStats*)hist4a->FindObject("stats");
/////st_4a->SetX1NDC(0.58);
/////st_4a->SetX2NDC(0.78);
///hist4b->Draw("SAME");
///
///// Add Legend
///TLegend *leg4 = new TLegend(0.55,0.70,0.90,0.90,NULL,"brNDC");
///leg4->SetBorderSize(1);
///leg4->SetLineColor(1);
///leg4->SetLineStyle(1);
///leg4->SetLineWidth(1);
///leg4->SetFillColor(0);
///leg4->SetFillStyle(1001);
///
///TLegendEntry *entry4=leg4->AddEntry("4b","2018 Data subset","lpf");
///entry4->SetFillStyle(1001);
///entry4->SetLineStyle(1);
///entry4->SetLineWidth(1);
///entry4->SetMarkerColor(1);
///entry4->SetMarkerStyle(1);
///entry4->SetMarkerSize(1);
///entry4->SetTextFont(42);
///
///entry4=leg4->AddEntry("4a","2012 Data subset","lpflpf");
///entry4->SetFillStyle(1001);
///entry4->SetLineStyle(1);
///entry4->SetLineWidth(1);
///entry4->SetMarkerColor(1);
///entry4->SetMarkerStyle(1);
///entry4->SetMarkerSize(1);
///entry4->SetTextFont(42);
///leg4->Draw();
///
///c4->Modified();
///c4->SaveAs(filepath+title4+".png");

// Draw in canvas
TCanvas *c5 = new TCanvas("c5","c5");
c5->SetGridx();
c5->SetGridy();
c5->SetTickx(1);
c5->SetTicky(1);
//c5->SetLogy();// draw with log scale Y
TString title5 = "Bc_M";
TString temp5a = "5a";
TString temp5b = "5b";

myTree1->Draw("Bc_M>>"+temp5a+"(30,2e3,12e3)", approxSelection,"goff");
TH1F *hist5a = (TH1F*)gDirectory->Get(temp5a);
myTree2->Draw("Bc_M>>"+temp5b+"(30,2e3,12e3)", approxSelection,"goff");
TH1F *hist5b = (TH1F*)gDirectory->Get(temp5b);
Double_t scale5 = (hist5b->Integral() / hist5a->Integral());
hist5a->Scale(scale5,"nosw2");

hist5a->SetLineColor(kRed);
hist5b->SetLineColor(kBlue);
auto max5 = std::max(hist5a->GetMaximum(),hist5b->GetMaximum());
hist5a->SetMaximum(max5*1.2);
hist5a->SetTitle("");
hist5a->GetXaxis()->SetTitle(title5);
hist5a->GetYaxis()->SetTitle("");
hist5a->SetMinimum(0);
hist5a->SetStats(0);// turn off stats box 
hist5a->Draw();
hist5b->Draw("SAME");

// Add Legend
TLegend *leg5 = new TLegend(0.55,0.70,0.90,0.90,NULL,"brNDC");
leg5->SetBorderSize(1);
leg5->SetLineColor(1);
leg5->SetLineStyle(1);
leg5->SetLineWidth(1);
leg5->SetFillColor(0);
leg5->SetFillStyle(1001);

TLegendEntry *entry5=leg5->AddEntry("5b","2018 Data subset","lpf");
entry5->SetFillStyle(1001);
entry5->SetLineStyle(1);
entry5->SetLineWidth(1);
entry5->SetMarkerColor(1);
entry5->SetMarkerStyle(1);
entry5->SetMarkerSize(1);
entry5->SetTextFont(42);

entry5=leg5->AddEntry("5a","2012 Data subset","lpflpf");
entry5->SetFillStyle(1001);
entry5->SetLineStyle(1);
entry5->SetLineWidth(1);
entry5->SetMarkerColor(1);
entry5->SetMarkerStyle(1);
entry5->SetMarkerSize(1);
entry5->SetTextFont(42);
leg5->Draw();

c5->Modified();
c5->SaveAs(filepath+title5+".png");

// Draw in canvas
TCanvas *c6 = new TCanvas("c6","c6");
c6->SetGridx();
c6->SetGridy();
c6->SetTickx(1);
c6->SetTicky(1);
//c6->SetLogy();// draw with log scale Y
TString title6 = "Bc_PT";
TString temp6a = "6a";
TString temp6b = "6b";

myTree1->Draw("Bc_PT>>"+temp6a+"(25,0e3,20e3)", approxSelection,"goff");
TH1F *hist6a = (TH1F*)gDirectory->Get(temp6a);
myTree2->Draw("Bc_PT>>"+temp6b+"(25,0e3,20e3)", approxSelection,"goff");
TH1F *hist6b = (TH1F*)gDirectory->Get(temp6b);
Double_t scale6 = (hist6b->Integral() / hist6a->Integral());
hist6a->Scale(scale6,"nosw2");

hist6a->SetLineColor(kRed);
hist6b->SetLineColor(kBlue);
auto max6 = std::max(hist6a->GetMaximum(),hist6b->GetMaximum());
hist6a->SetMaximum(max6*1.2);
hist6a->SetTitle("");
hist6a->GetXaxis()->SetTitle(title6);
hist6a->GetYaxis()->SetTitle("");
hist6a->SetMinimum(0);
hist6a->SetStats(0);// turn off stats box 
hist6a->Draw();
hist6b->Draw("SAME");

// Add Legend
TLegend *leg6 = new TLegend(0.55,0.70,0.90,0.90,NULL,"brNDC");
leg6->SetBorderSize(1);
leg6->SetLineColor(1);
leg6->SetLineStyle(1);
leg6->SetLineWidth(1);
leg6->SetFillColor(0);
leg6->SetFillStyle(1001);

TLegendEntry *entry6=leg6->AddEntry("6b","2018 Data subset","lpf");
entry6->SetFillStyle(1001);
entry6->SetLineStyle(1);
entry6->SetLineWidth(1);
entry6->SetMarkerColor(1);
entry6->SetMarkerStyle(1);
entry6->SetMarkerSize(1);
entry6->SetTextFont(42);

entry6=leg6->AddEntry("6a","2012 Data subset","lpflpf");
entry6->SetFillStyle(1001);
entry6->SetLineStyle(1);
entry6->SetLineWidth(1);
entry6->SetMarkerColor(1);
entry6->SetMarkerStyle(1);
entry6->SetMarkerSize(1);
entry6->SetTextFont(42);
leg6->Draw();

c6->Modified();
c6->SaveAs(filepath+title6+".png");

// Draw in canvas
TCanvas *c7 = new TCanvas("c7","c7");
c7->SetGridx();
c7->SetGridy();
c7->SetTickx(1);
c7->SetTicky(1);
//c7->SetLogy();// draw with log scale Y
TString title7 = "Bc_P";
TString temp7a = "7a";
TString temp7b = "7b";

myTree1->Draw("Bc_P>>"+temp7a+"(25,0e3,500e3)", approxSelection,"goff");
TH1F *hist7a = (TH1F*)gDirectory->Get(temp7a);
myTree2->Draw("Bc_P>>"+temp7b+"(25,0e3,500e3)", approxSelection,"goff");
TH1F *hist7b = (TH1F*)gDirectory->Get(temp7b);
Double_t scale7 = (hist7b->Integral() / hist7a->Integral());
hist7a->Scale(scale7,"nosw2");

hist7a->SetLineColor(kRed);
hist7b->SetLineColor(kBlue);
auto max7 = std::max(hist7a->GetMaximum(),hist7b->GetMaximum());
hist7a->SetMaximum(max7*1.2);
hist7a->SetTitle("");
hist7a->GetXaxis()->SetTitle(title7);
hist7a->GetYaxis()->SetTitle("");
hist7a->SetMinimum(0);
hist7a->SetStats(0);// turn off stats box 
hist7a->Draw();
hist7b->Draw("SAME");

// Add Legend
TLegend *leg7 = new TLegend(0.55,0.70,0.90,0.90,NULL,"brNDC");
leg7->SetBorderSize(1);
leg7->SetLineColor(1);
leg7->SetLineStyle(1);
leg7->SetLineWidth(1);
leg7->SetFillColor(0);
leg7->SetFillStyle(1001);

TLegendEntry *entry7=leg7->AddEntry("7b","2018 Data subset","lpf");
entry7->SetFillStyle(1001);
entry7->SetLineStyle(1);
entry7->SetLineWidth(1);
entry7->SetMarkerColor(1);
entry7->SetMarkerStyle(1);
entry7->SetMarkerSize(1);
entry7->SetTextFont(42);

entry7=leg7->AddEntry("7a","2012 Data subset","lpflpf");
entry7->SetFillStyle(1001);
entry7->SetLineStyle(1);
entry7->SetLineWidth(1);
entry7->SetMarkerColor(1);
entry7->SetMarkerStyle(1);
entry7->SetMarkerSize(1);
entry7->SetTextFont(42);
leg7->Draw();

c7->Modified();
c7->SaveAs(filepath+title7+".png");

/// Add B flight distance 

}

