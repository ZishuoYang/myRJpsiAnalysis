#include <iostream>
#include <string>
using std::cout;
using std::endl;
using std::string;

#include "TFile.h"
#include "TTree.h"
#include "THStack.h"
#include "TH1F.h"
#include "TCanvas.h"
#include "TColor.h"
#include "TROOT.h"

const int numColors = 7;
const int majorColors[numColors] = {
  kBlue, // TAU
  kRed, // FD
  kBlue+3, // MU
  kCyan, // GHOST
  kGreen, // PV
  kMagenta, // JpsiX
  kBlack, // COMB
};


const int numBkgs = 7;
struct b_info {
  const char* name;
  const char* cut;
} bkgInfo[numBkgs] = {
  { "SIG_Tau", "weight*(Bc_ENDVERTEX_CHI2<25&&Bc_DOCA<0.15&&BachMu_TRACK_CHI2NDOF<2&&MyBkgTag == 1)" }
  , { "BKG_FD", "weight*(Bc_ENDVERTEX_CHI2<25&&Bc_DOCA<0.15&&BachMu_TRACK_CHI2NDOF<2&&MyBkgTag == 100)" }
  , { "SIG_Mu", "weight*(Bc_ENDVERTEX_CHI2<25&&Bc_DOCA<0.15&&BachMu_TRACK_CHI2NDOF<2&&MyBkgTag == 0)" }
  , { "Ghost", "weight*(Bc_ENDVERTEX_CHI2<25&&Bc_DOCA<0.15&&BachMu_TRACK_CHI2NDOF<2&&MyBkgTag % 10 == 6)" }
  , { "PV", "weight*(Bc_ENDVERTEX_CHI2<25&&Bc_DOCA<0.15&&BachMu_TRACK_CHI2NDOF<2&&MyBkgTag % 10 == 5)" }
  , { "JpsiX", "weight*(Bc_ENDVERTEX_CHI2<25&&Bc_DOCA<0.15&&BachMu_TRACK_CHI2NDOF<2&&MyBkgTag % 10 == 2)" }
  , { "Comb", "weight*(Bc_ENDVERTEX_CHI2<25&&Bc_DOCA<0.15&&BachMu_TRACK_CHI2NDOF<2&&MyBkgTag % 10 == 4)" }
  //  , { "MisPID", "weight*(Bc_ENDVERTEX_CHI2<25&&Bc_DOCA<0.15&&BachMu_TRACK_CHI2NDOF<2&&MyBkgTag == 3)" }
};

const int numStacks = 72;
struct s_info {
  const char* var;
  const char* name;
  const char* title;
  int bins;
  double min;
  double max;
} stackInfo[numStacks] = 
  {

    // VERTEX VARIABLES
    { "DeltaChi2", "deltachi2_stack", "Delta chi^2 (Bc vtx. vs Jpsi vtx.)", 50, 0, 30 }
    , { "Bc_ENDVERTEX_CHI2", "bcvtxchi2_stack", "Bc vtx. chi^2 Bc", 50, 0, 30 }

    // VERTEX VARIABLES
    , { "BachMu_TRACK_CHI2NDOF", "trchi2ndof_bmstack", "BachMu TRCHI2NDOF", 50, 0.0, 3.0}
    , { "log(BachMu_TRACK_MatchCHI2)", "trmatchchi2_bmstack", "BachMu TRACK MatchCHI2", 50, -3.0, 5.0}
    , { "log(-BachMu_TRACK_Likelihood)", "trlike_bmstack", "BachMu TRACK Likelihood", 50, -2.0, 4.0}
    , { "log(BachMu_TRACK_GhostProb)", "trghostprob_bmstack", "BachMu TRACK GhostProb", 50, -12.0, 0.1}

    , { "MuP_TRACK_CHI2NDOF", "trchi2ndof_mupstack", "MuP TRCHI2NDOF", 50, 0.0, 3.0}
    , { "log(MuP_TRACK_MatchCHI2)", "trmatchchi2_mupstack", "MuP TRACK MatchCHI2", 50, -3.0, 5.0}
    , { "log(-MuP_TRACK_Likelihood)", "trlike_mupstack", "MuP TRACK Likelihood", 50, -2.0, 4.0}
    , { "log(MuP_TRACK_GhostProb)", "trghostprob_mupstack", "MuP TRACK GhostProb", 50, -12.0, 0.1}

    , { "MuM_TRACK_CHI2NDOF", "trchi2ndof_mumstack", "MuM TRCHI2NDOF", 50, 0.0, 3.0}
    , { "log(MuM_TRACK_MatchCHI2)", "trmatchchi2_mumstack", "MuM TRACK MatchCHI2", 50, -3.0, 5.0}
    , { "log(-MuM_TRACK_Likelihood)", "trlike_mumstack", "MuM TRACK Likelihood", 50, -2.0, 4.0}
    , { "log(MuM_TRACK_GhostProb)", "trghostprob_mumstack", "MuM TRACK GhostProb", 50, -12.0, 0.1}
    

    // FLIGHT DISTANCES, DIRAS, AND ALL THAT
    , { "log(Bc_DOCA)", "doca_stack", "J/psi mu DOCA", 50, -10.0, -1.5}
    , { "log(Bc_DOCACHI2)", "docachi2_stack", "J/psi mu DOCA CHI2", 50, -15.0, 5.0}
    , { "log(Bc_FD_OWNPV)", "bcfd_stack", "Bc flight distance", 50, -1.5, 4.0}
    , { "log(Bc_FDCHI2_OWNPV)", "bcfdchi2_stack", "Bc flight distance chi^2", 50, -5.0, 8.0}
    , { "log(1-Bc_DIRA_OWNPV)", "bcdira_stack", "Bc DIRA", 50, -17.5,-5.0}
    , { "log(Bc_CTAU)", "bcctau_stack", "Measured Liftime (microns)", 50, 3.0, 8.0 }

    // KINEMATIC VARIABLES
    , { "Bc_MM", "bcmm_stack", "Rec. Mass (GeV)", 50, 3000,6500 }
    , { "Pointing","pointing_stack","Bc Pointing", 50, 0, 0.5 }
    , { "log(BachMu_PT)", "bmpt_stack", "BachMu PT (GeV)", 50, 5.5, 9.0 }

    // IMPACT PARAMETERS
    , { "log(Bc_IP_OWNPV)", "bcip_stack", "Bc IP", 50, -6.0, 0.0}
    , { "log(Bc_IPCHI2_OWNPV)", "bcipchi2_stack", "Bc IP chi^2", 50, -5.0, 8.0} // same as FDCHI2
    , { "log(BachMu_IP_OWNPV)", "bmip_stack", "BachMu IP(PV)", 50, -4.0, 2.0 }
    , { "log(BachMu_IPCHI2_OWNPV)", "bmipchi2_stack", "BachMu IPCHI2(PV)", 50, 1.0, 10.0 }
    , { "log(MuP_IP_OWNPV)", "mpip_stack", "MuP IP(PV)", 50, -4.0, 2.0 }
    , { "log(MuP_IPCHI2_OWNPV)", "mpipchi2_stack", "MuP IPCHI2(PV)", 50, 1.0, 10.0 }
    , { "log(MuM_IP_OWNPV)", "mmip_stack", "MuM IP(PV)", 50, -4.0, 2.0 }
    , { "log(MuM_IPCHI2_OWNPV)", "mmipchi2_stack", "MuM IPCHI2(PV)", 50, 1.0, 10.0 }

    // ESTIMATED VARIABLES
    , { "log(Lifetime)", "lifetime_stack", "Lifetime (ps)", 50, -2.5, 2.0 }
    , { "MissMass2", "mm_stack", "Missing Mass Sq. (GeV^2)", 50, -3.0, 9.0 }
    , { "Q2", "q2_stack", "Q^2 (GeV^2)", 50, -5, 10.4 }
    , { "BachMuEnergy", "bme_stack", "BachMu energy in Bc rest frame (GeV)", 50, 0, 5 }
    , { "JpsiEnergy", "jpsie_stack", "Jpsi energy in Bc rest frame (GeV)", 50, 3, 6 }

    // ISOLATION VARIABLES
    , { "Bc_NOPARTWITHINDCHI2_9", "bcdeltachiwdw_stack", "Bc # Part. w/i 9 Delta CHI2", 16, 0, 15 }
    , { "Bc_NOPARTWITHINDCHI2_16", "bcdeltachi16_stack", "Bc # Part. w/i 16 Delta CHI2", 16, 0, 15 }
    , { "Bc_NOPARTWITHINDCHI2_25", "bcdeltachi25_stack", "Bc # Part. w/i 25 Delta CHI2", 16, 0, 15 }
    , { "Bc_NOPARTWITHINCHI2_9", "bcchiwdw_stack", "Bc # Part. w/i 9 CHI2", 16, 0, 15 }
    , { "Bc_NOPARTWITHINCHI2_16", "bcchi16_stack", "Bc # Part. w/i 16  CHI2", 16, 0, 15 }
    , { "Bc_NOPARTWITHINCHI2_25", "bcchi25_stack", "Bc # Part. w/i 25  CHI2", 16, 0, 15 }
    , { "Bc_SMALLESTCHI2", "bcminchi2_stack", "Bc Min. CHI2 w/ Extra Track", 50, 0, 150 }
    , { "Bc_ENDVERTEX_CHI2-Bc_SMALLESTCHI2", "bcisodchi2_stack", "Bc VTX CHI2 - Bc Min. CHI2 w/ Extra Track", 50, -25, 75 }
    , { "Bc_ENDVERTEX_CHI2/3-Bc_SMALLESTCHI2/4", "bcisodchi2ndof_stack", "Bc VTX CHI2/NDOF - Min. CHI2/NDOF w/ Extra Track", 50, -10, 50 }
    , { "Bc_SMALLESTDELTACHI2", "bcmindeltachi2_stack", "Bc Min. Delta CHI2 w/ Extra Track", 50, 0, 150 }
    , { "Bc_SMALLESTCHI2_MM", "bcextramm_stack", "Bc Mass w/ Best Extra Track", 50, 3000, 10000 }

    , { "Jpsi_NOPARTWITHINDCHI2_9", "jpsideltachiwdw_stack", "Jpsi # Part. w/i 9 Delta CHI2", 16, 0, 15 }
    , { "Jpsi_NOPARTWITHINDCHI2_16", "jpsideltachi16_stack", "Jpsi # Part. w/i 16 Delta CHI2", 16, 0, 15 }
    , { "Jpsi_NOPARTWITHINDCHI2_25", "jpsideltachi25_stack", "Jpsi # Part. w/i 25 Delta CHI2", 16, 0, 15 }
    , { "Jpsi_NOPARTWITHINCHI2_9", "jpsichiwdw_stack", "Jpsi # Part. w/i 9 CHI2", 16, 0, 15 }
    , { "Jpsi_NOPARTWITHINCHI2_16", "jpsichi16_stack", "Jpsi # Part. w/i 16  CHI2", 16, 0, 15 }
    , { "Jpsi_NOPARTWITHINCHI2_25", "jpsichi25_stack", "Jpsi # Part. w/i 25  CHI2", 16, 0, 15 }
    , { "Jpsi_SMALLESTCHI2", "jpsiminchi2_stack", "Jpsi Min. CHI2 w/ Extra Track", 50, 0, 150 }
    , { "Jpsi_SMALLESTDELTACHI2", "jpsimindeltachi2_stack", "Jpsi Min. Delta CHI2 w/ Extra Track", 50, 0, 150 }
    , { "Jpsi_SMALLESTCHI2_MM", "jpsiextramm_stack", "Jpsi Mass w/ Best Extra Track", 50, 3000, 10000 }

    , { "BachMu_cmult_1.00","bmcmult1_stack", "BachMu Track Isolation 1.00", 16, 0, 15 }
    , { "BachMu_deltaEta_1.00","bmdeltaeta1_stack", "BachMu #Delta #eta 1.00", 50, -2, 6 }
    , { "BachMu_deltaPhi_1.00","bmdeltaphi1_stack", "BachMu #Delta #phi 1.00", 50, 0, 3.14159 }
    , { "BachMu_ptasy_1.00","bmptasy1_stack", "BachMu PT Asymmetry 1.00", 50, -1, 1 }
    , { "BachMu_cmult_0.75","bmcmultp75_stack", "BachMu Track Isolation 0.75", 31, 0, 30 }
    , { "BachMu_deltaEta_0.75","bmdeltaetap75_stack", "BachMu #Delta #eta 0.75", 50, -2, 6 }
    , { "BachMu_deltaPhi_0.75","bmdeltaphip75_stack", "BachMu #Delta #phi 0.75", 50, 0, 3.14159 }
    , { "BachMu_ptasy_0.75","bmptasyp75_stack", "BachMu PT Asymmetry 0.75", 50, -1, 1 }
    , { "BachMu_cmult_1.25","bmcmult1p25_stack", "BachMu Track Isolation 1.25", 51, 0, 50 }
    , { "BachMu_deltaEta_1.25","bmdeltaeta1p25_stack", "BachMu #Delta #eta 1.25", 50, -2, 6 }
    , { "BachMu_deltaPhi_1.25","bmdeltaphi1p25_stack", "BachMu #Delta #phi 1.25", 50, 0, 3.14159 }
    , { "BachMu_ptasy_1.25","bmptasy1p25_stack", "BachMu PT Asymmetry 1.25", 50, -1, 1 }
    , { "BachMu_cmult_totl","bmcmulttotl_stack", "BachMu Track Isolation totl", 51, 0, 50 }
    , { "BachMu_deltaEta_totl","bmdeltaetatotl_stack", "BachMu #Delta #eta totl", 50, -6, 2 }
    , { "BachMu_deltaPhi_totl","bmdeltaphitotl_stack", "BachMu #Delta #phi totl", 50, 0, 3.14159 }
    , { "BachMu_ptasy_totl","bmptasytotl_stack", "BachMu PT Asymmetry totl", 50, -1, 1 }
    
  };

    

void histomaker()
{
  // Input TTrees
  cout << "Finding input TTrees ..." << endl;
  TFile* file = new TFile("Bc_MC.root","READ");
  TTree* tree = (TTree*)file->Get("DecayTree");
  tree->AddFriend("weightTree","Bc_MCW.root");
  //  file->Close();
  
  // Output File
  cout << "Creating output TFile ..." << endl;
  TFile OutFile("comparison_histos.root","RECREATE");

  // Style
  //   Double_t Red[3]    = { 1.00, 0.00, 0.00 };
  //   Double_t Green[3]  = { 0.00, 1.00, 0.00 };
  //   Double_t Blue[3]   = { 1.00, 0.00, 1.00 };
  //   Double_t Length[3] = { 0.00, 0.50, 1.00 };
  //   TColor::CreateGradientColorTable(Number,Length,Red,Green,Blue,numBkgs);
  //  gStyle->SetPalette(numBkgs);

  // Processing
  //  THStack* stacks_list[numStacks];
  TH1F* bkg_histos_list[numStacks][numBkgs];
  //  TH1F* all_histos_list[numStacks][numBkgs][numTrees];

  for (int s = 0; s < numStacks; s++) {
    THStack *var_stack = new THStack(stackInfo[s].name,stackInfo[s].title);

    for (int b = numBkgs-1; b >= 0; b--) {

      char bkghistoname[100];
      sprintf(bkghistoname, "%s_%s",stackInfo[s].name,bkgInfo[b].name);
      TH1F* bkghisto = new TH1F(bkghistoname,bkghistoname,stackInfo[s].bins, stackInfo[s].min, stackInfo[s].max);
      bkghisto->SetFillColor(majorColors[b % numColors]);
      bkghisto->SetLineColor(majorColors[b % numColors]);
      bkghisto->SetMarkerColor(majorColors[b % numColors]);
      //      bkghisto->Sumw2();
      tree->Project(bkghistoname,stackInfo[s].var,bkgInfo[b].cut);
      
      // Get histo off of THStack
      var_stack->Add(bkghisto);
      bkg_histos_list[s][b] = bkghisto;
      OutFile.cd();
      //      bkghisto->Write();
    }

//     char c1name[100];
//     sprintf(c1name,"%s_stacked",stackInfo[s].name);
//     TCanvas* c1 = new TCanvas(c1name,stackInfo[s].title,10,10,800,800);
//     c1->cd();
//     var_stack->Draw();

//     char c2name[100];
//     sprintf(c2name,"%s_notstacked",stackInfo[s].name);
//     TCanvas* c2 = new TCanvas(c2name,stackInfo[s].title,10,10,800,800);
//     c2->cd();
//    var_stack->Draw("nostack");
//    stacks_list[s] = var_stack;    
    OutFile.cd();
    var_stack->Write();
//     c1->Write();
//     c2->Write();
//     delete c1;
//     delete c2;
  }
}
    
