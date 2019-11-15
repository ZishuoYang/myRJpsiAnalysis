//-----------------------------------------
// Compare histograms of multiple variables
// Zishuo Yang, 2019-08-01
// ----------------------------------------
#include <sstream>
#include <string.h>

// Set output filepath
TString filepath = "./plots/compare_run1_run2/";

// Get input
TFile *inputFile1 = new TFile("~/my_eos/RJpsi/tuples/2012_Data_MD_subset.root");
TFile *inputFile2 = new TFile("~/my_eos/RJpsi/tuples/2018_Data_MD_subset.root");
TFile *inputFile3 = new TFile("~/my_eos/RJpsi/tuples/2012_MC_JpsiMuNu.root");
TFile *inputFile4 = new TFile("~/my_eos/RJpsi/tuples/2012_MC_JpsiTauNu.root");
//TFile *inputFile5 = new TFile("~/my_eos/RJpsi/tuples/2012_MC_Psi2SMu.root");
//TFile *inputFile6 = new TFile("~/my_eos/RJpsi/tuples/2012_MC_JpsiDx.root");
TTree *t1 = (TTree*) inputFile1->Get("DecayTree");
TTree *t2 = (TTree*) inputFile2->Get("DecayTree");
TTree *t3 = (TTree*) inputFile3->Get("DecayTree");
TTree *t4 = (TTree*) inputFile4->Get("DecayTree");

TString approxSelection = "Jpsi_L0DiMuonDecision_TOS==1 && Jpsi_Hlt2DiMuonDetachedJPsiDecision_TOS==1 && BachMu_IPCHI2_OWNPV>4.8 && BachMu_PT>750 && Bc_OWNPV_CHI2<25 && Bc_DOCA<0.15 && Bc_ISOLATION_BDT<0.2 && BachMu_ProbNNmu>0.5"; // cuts to quickly approx. sig/norm selection


void draw(TString variable, TString range, TString title = "", TString filename = "")
{
    TCanvas *c = new TCanvas("c","c");
    c->SetGridx();
    c->SetGridy();
    c->SetTickx(1);
    c->SetTicky(1);
    //c->SetLogy();// draw with log scale Y
    if (title == "") { title = variable;} // Set default title 
    if (filename == "") { filename = title;} // Set default filename
    TString tempa = "a";
    TString tempb = "b";
    TString tempc = "c";
    TString tempd = "d";
    
    t1->Draw(variable+">>"+tempa+range, approxSelection,"goff");
    TH1F *hista = (TH1F*)gDirectory->Get(tempa);
    t2->Draw(variable+">>"+tempb+range, approxSelection,"goff");
    TH1F *histb = (TH1F*)gDirectory->Get(tempb);
    t3->Draw(variable+">>"+tempc+range, approxSelection,"goff");
    TH1F *histc = (TH1F*)gDirectory->Get(tempc);
    t4->Draw(variable+">>"+tempd+range, approxSelection,"goff");
    TH1F *histd = (TH1F*)gDirectory->Get(tempd);
    Double_t scale = (histb->Integral() / hista->Integral());
    hista->Scale(scale,"nosw2");
    scale = (histb->Integral() / histc->Integral());
    histc->Scale(0.3*scale,"nosw2");
    scale = (histb->Integral() / histd->Integral());
    histd->Scale(0.3*scale,"nosw2");
    
    hista->SetLineWidth(2);
    histb->SetLineWidth(2);
    histc->SetLineWidth(2);
    histd->SetLineWidth(2);

    hista->SetLineColor(kRed);
    histb->SetLineColor(kBlue);
    histc->SetLineColor(kViolet-1);
    histc->SetLineStyle(kDashed);
    histd->SetLineColor(kGreen+2);
    histd->SetLineStyle(kDashed);

    auto max = std::max(hista->GetMaximum(),histb->GetMaximum());
    hista->SetMaximum(max*1.2);
    hista->SetTitle("");
    hista->GetXaxis()->SetTitle(title);
    hista->GetYaxis()->SetTitle("");
    hista->SetMinimum(0);
    hista->SetStats(0);// turn off stats box 
    hista->Draw();
    histb->Draw("SAME");
    histc->Draw("SAME");
    histd->Draw("SAME");
    gPad->RedrawAxis();
    
    // Add Legend
    TLegend *leg = new TLegend(0.55,0.70,0.90,0.90,NULL,"brNDC");
    TLegendEntry *entry=leg->AddEntry("a","2012 Data subset","lpf");
    entry=leg->AddEntry("b","2018 Data subset","lpflpf");
    entry=leg->AddEntry("c","2012 MC Bc->JpsiMuNu","lpflpf");
    entry=leg->AddEntry("d","2012 MC Bc->JpsiTauNu","lpflpf");
    leg->Draw();
    
    c->Modified();
    c->SaveAs(filepath+filename+".png");
    delete c;
}

void compare_run1_run2()
{

draw("Bc_M", "(30,2e3,10e3)");
draw("Bc_PT", "(30,0e4,2e4)");
draw("Bc_P", "(30,0e3,350e3)");
draw("Bc_FD_OWNPV", "(30,0e0,15e0)");
draw("Jpsi_M", "(30,3e3,3.2e3)");
draw("Jpsi_P", "(30,0e0,250e3)");
draw("Jpsi_PT", "(30,0e0,15e3)");
draw("FitVar_Mmiss2", "(25,-6e6,10e6)");
draw("FitVar_q2", "(30,-10e6,20e6)");
draw("FitVar_El", "(30,0e4,0.50e4)");
draw("FitVar_CTAU/(299792458e3)", "(20,0e-12,2.2e-12)", "proper lifetime [ps]", "FitVar_Tau");

// // For plotting Z distribution
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


}

