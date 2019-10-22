#include <string>
using std::string;

const int numColors = 10;
const int majorColors[numColors] =
  { kRed, kCyan+2, kBlue, kGreen, kMagenta,
    kViolet, kSpring, kTeal, kAzure, kOrange };


const int numTrees = 3;
struct t_info {
  double weight;
} treeInfo[numTrees] = 
  {
    { 1.0 }
    , { 0.29 } //, { 0.29 }
    , { 2.95 } //, { 2.95 }
    , { 3.77 } // , { 3.77}
  };

const int numBkgs = 6;
struct b_info {
  const char* name;
  const char* cut;
} bkgInfo[numBkgs] = 
  {
    { "SIG", "Bc_SIG_Mu | Bc_SIG_Mu_SWITCHED | Bc_SIG_Tau | Bc_SIG_Tau_SWITCHED | Bc_SIG_BadTau" }
    , { "Other", "Bc_SIG_Other | PartRecBKG | GhostBKG | FromPVBKG | PileupBKG | LightFlavourBKG | OtherBKG" }
    , { "JpsiX", "Bc_BKG_B02JpsiX | Bc_BKG_B2JpsiX" }
    , { "Comb", "BBBKG" }
    , { "LowMass", "LowMassBKG" }    
  };

const int numStacks = 34;
struct s_info {
  const char* var;
  const char* name;
  const char* title;
  int bins;
  double min;
  double max;
} stackInfo[numStacks] = 
  {
    { "MissMass2/1E6", "mm_stack", "Missing Mass Sq. (GeV^2)", 50, -10, 15 }
    , { "q2/1E6", "q2_stack", "Q^2 (GeV^2)", 50, 0, 15 }
    , { "LepEnergy/1E3", "le_stack", "BachMu energy in Bc rest frame (GeV)", 50, 0, 5 }
    , { "BachMu_PIDmu", "bmpidmu_stack", "BachMu PIDmu", 50, 0, 10 }
    , { "BachMu_ProbNNmu", "bmprobmu_stack", "BachMu ProbNNmu", 50, 0, 1 }
    , { "BachMu_PT/1E3", "bmpt_stack", "BachMu PT (GeV)", 50, 0, 5 }
    , { "BachMu_CosTheta", "bmpolar_stack", "BachMu Cos(theta)", 50, -1, 1 }
    , { "Bc_FD", "bcfd_stack", "Bc flight distance", 50, 0, 100}
    , { "Bc_FDCHI2", "bcfdchi2_stack", "Bc flight distance chi^2", 50, 0, 10000}
    , { "Bc_DIRA_OWNPV", "bcdira_stack", "Bc DIRA", 50, 0.995, 1}
    , { "DeltaChi2", "deltachi2_stack", "Delta chi^2 (Bc vtx. vs Jpsi vtx.)", 50, 0, 25 }
    , { "Bc_CTAU", "bcctau_stack", "Measured Liftime (microns)", 50, 0, 500 }
    , { "Lifetime", "lifetime_stack", "Lifetime (ps)", 50, 0, 10 }
    , { "Bc_MM", "bcmm_stack", "Rec. Mass (GeV)", 50,3000,6500 }
    , { "BachMu_IP_OWNPV", "bmip_stack", "BachMu IP(PV)", 50, 0, 10 }
    , { "BachMu_IPCHI2_OWNPV", "bmipchi2_stack", "BachMu IPCHI2(PV)", 50, 0, 10000 }
    , { "MuP_IP_OWNPV", "mpip_stack", "MuP IP(PV)", 50, 0, 10 }
    , { "MuP_IPCHI2_OWNPV", "mpipchi2_stack", "MuP IPCHI2(PV)", 50, 0, 10000 }
    , { "MuM_IP_OWNPV", "mmip_stack", "MuM IP(PV)", 50, 0, 10 }
    , { "MuM_IPCHI2_OWNPV", "mmipchi2_stack", "MuM IPCHI2(PV)", 50, 0, 10000 }
    , { "Bc_NOPARTWITHINDCHI2WDW", "bcdeltachiwdw_stack", "Bc # Part. w/i Delta CHI2 WDW", 11, 0, 10 }
//     , { "Bc_NOPARTWITHINDCHI2_1", "bcdeltachi1_stack", "Bc # Part. w/i 1 Delta CHI2", 11, 0, 10 }
//     , { "Bc_NOPARTWITHINDCHI2_4", "bcdeltachi4_stack", "Bc # Part. w/i 4 Delta CHI2", 11, 0, 10 }
//     , { "Bc_NOPARTWITHINDCHI2_9", "bcdeltachi9_stack", "Bc # Part. w/i 9 Delta CHI2", 11, 0, 10 }
//     , { "Bc_NOPARTWITHINDCHI2_16", "bcdeltachi16_stack", "Bc # Part. w/i 16 Delta CHI2", 11, 0, 10 }
//     , { "Bc_NOPARTWITHINDCHI2_25", "bcdeltachi25_stack", "Bc # Part. w/i 25 Delta CHI2", 11, 0, 10 }
    , { "Bc_NOPARTWITHINCHI2WDW", "bcchiwdw_stack", "Bc # Part. w/i CHI2 WDW", 11, 0, 10 }
//     , { "Bc_NOPARTWITHINCHI2_1", "bcchi1_stack", "Bc # Part. w/i 1  CHI2", 11, 0, 10 }
//     , { "Bc_NOPARTWITHINCHI2_4", "bcchi4_stack", "Bc # Part. w/i 4  CHI2", 11, 0, 10 }
//     , { "Bc_NOPARTWITHINCHI2_9", "bcchi9_stack", "Bc # Part. w/i 9  CHI2", 11, 0, 10 }
//     , { "Bc_NOPARTWITHINCHI2_16", "bcchi16_stack", "Bc # Part. w/i 16  CHI2", 11, 0, 10 }
//     , { "Bc_NOPARTWITHINCHI2_25", "bcchi25_stack", "Bc # Part. w/i 25  CHI2", 11, 0, 10 }
    , { "Bc_SMALLESTCHI2", "bcminchi2_stack", "Bc Min. CHI2 w/ Extra Track", 50, 0, 150 }
    , { "Bc_SMALLESTDELTACHI2", "bcmindeltachi2_stack", "Bc Min. Delta CHI2 w/ Extra Track", 50, 0, 150 }
//     , { "Bc_SMALLESTCHI2_MM", "bcextramm_stack", "Bc Mass w/ Best Extra Track", 50, 3000, 10000 }
    , { "Jpsi_NOPARTWITHINDCHI2WDW", "jpsideltachiwdw_stack", "Jpsi # Part. w/i Delta CHI2 WDW", 11, 0, 10 }
//     , { "Jpsi_NOPARTWITHINDCHI2_1", "jpsideltachi1_stack", "Jpsi # Part. w/i 1 Delta CHI2", 11, 0, 10 }
//     , { "Jpsi_NOPARTWITHINDCHI2_4", "jpsideltachi4_stack", "Jpsi # Part. w/i 4 Delta CHI2", 11, 0, 10 }
//     , { "Jpsi_NOPARTWITHINDCHI2_9", "jpsideltachi9_stack", "Jpsi # Part. w/i 9 Delta CHI2", 11, 0, 10 }
//     , { "Jpsi_NOPARTWITHINDCHI2_16", "jpsideltachi16_stack", "Jpsi # Part. w/i 16 Delta CHI2", 11, 0, 10 }
//     , { "Jpsi_NOPARTWITHINDCHI2_25", "jpsideltachi25_stack", "Jpsi # Part. w/i 25 Delta CHI2", 11, 0, 10 }
    , { "Jpsi_NOPARTWITHINCHI2WDW", "jpsichiwdw_stack", "Jpsi # Part. w/i CHI2 WDW", 11, 0, 10 }
//     , { "Jpsi_NOPARTWITHINCHI2_1", "jpsichi1_stack", "Jpsi # Part. w/i 1  CHI2", 11, 0, 10 }
//     , { "Jpsi_NOPARTWITHINCHI2_4", "jpsichi4_stack", "Jpsi # Part. w/i 4  CHI2", 11, 0, 10 }
//     , { "Jpsi_NOPARTWITHINCHI2_9", "jpsichi9_stack", "Jpsi # Part. w/i 9  CHI2", 11, 0, 10 }
//     , { "Jpsi_NOPARTWITHINCHI2_16", "jpsichi16_stack", "Jpsi # Part. w/i 16  CHI2", 11, 0, 10 }
//     , { "Jpsi_NOPARTWITHINCHI2_25", "jpsichi25_stack", "Jpsi # Part. w/i 25  CHI2", 11, 0, 10 }
    , { "Jpsi_SMALLESTCHI2", "jpsiminchi2_stack", "Jpsi Min. CHI2 w/ Extra Track", 50, 0, 150 }
    , { "Jpsi_SMALLESTDELTACHI2", "jpsimindeltachi2_stack", "Jpsi Min. Delta CHI2 w/ Extra Track", 50, 0, 150 }
//     , { "Jpsi_SMALLESTCHI2_MM", "jpsiextramm_stack", "Jpsi Mass w/ Best Extra Track", 50, 3000, 10000 }
    , { "BachMu_cmult_0.50","bmcmult5_stack", "BachMu Track Isolation 0.50", 50, 0, 50 }
    , { "BachMu_cmult_0.60","bmcmult6_stack", "BachMu Track Isolation 0.60", 50, 0, 50 }
    , { "BachMu_cmult_0.70","bmcmult7_stack", "BachMu Track Isolation 0.70", 50, 0, 50 }
    , { "BachMu_cmult_0.80","bmcmult8_stack", "BachMu Track Isolation 0.80", 50, 0, 50 }
    , { "BachMu_cmult_0.90","bmcmult9_stack", "BachMu Track Isolation 0.90", 50, 0, 50 }
    , { "BachMu_cmult_1.00","bmcmult10_stack", "BachMu Track Isolation 1.00", 50, 0, 50 }
//     , { "BachMu_ptasy_0.50","bmptasy5_stack", "BachMu PT Asymmetry 0.50", 50, -1,1 }
//     , { "BachMu_ptasy_0.60","bmptasy6_stack", "BachMu PT Asymmetry 0.60", 50, -1,1 }
//     , { "BachMu_ptasy_0.70","bmptasy7_stack", "BachMu PT Asymmetry 0.70", 50, -1,1 }
//     , { "BachMu_ptasy_0.80","bmptasy8_stack", "BachMu PT Asymmetry 0.80", 50, -1,1 }
//     , { "BachMu_ptasy_0.90","bmptasy9_stack", "BachMu PT Asymmetry 0.90", 50, -1,1 }
//     , { "BachMu_ptasy_1.00","bmptasy10_stack", "BachMu PT Asymmetry 1.00", 50, -1, 1 }
//     , { "Jpsi_cmult_0.50","jpsicmult5_stack", "Jpsi Track Isolation 0.50", 50, 0, 50 }
//     , { "Jpsi_cmult_0.60","jpsicmult6_stack", "Jpsi Track Isolation 0.60", 50, 0, 50 }
//     , { "Jpsi_cmult_0.70","jpsicmult7_stack", "Jpsi Track Isolation 0.70", 50, 0, 50 }
//     , { "Jpsi_cmult_0.80","jpsicmult8_stack", "Jpsi Track Isolation 0.80", 50, 0, 50 }
//     , { "Jpsi_cmult_0.90","jpsicmult9_stack", "Jpsi Track Isolation 0.90", 50, 0, 50 }
//     , { "Jpsi_cmult_1.00","jpsicmult10_stack", "Jpsi Track Isolation 1.00", 50, 0, 50 }
//     , { "Jpsi_ptasy_0.50","jpsiptasy5_stack", "Jpsi PT Asymmetry 0.50", 50, -1,1 }
//     , { "Jpsi_ptasy_0.60","jpsiptasy6_stack", "Jpsi PT Asymmetry 0.60", 50, -1,1 }
//     , { "Jpsi_ptasy_0.70","jpsiptasy7_stack", "Jpsi PT Asymmetry 0.70", 50, -1,1 }
//     , { "Jpsi_ptasy_0.80","jpsiptasy8_stack", "Jpsi PT Asymmetry 0.80", 50, -1,1 }
//     , { "Jpsi_ptasy_0.90","jpsiptasy9_stack", "Jpsi PT Asymmetry 0.90", 50, -1,1 }
//     , { "Jpsi_ptasy_1.00","jpsiptasy10_stack", "Jpsi PT Asymmetry 1.00", 50, -1,1 }
//     , { "BachMu_NOPARTWITHINCHI2WDW", "bmchiwdw_stack", "BachMu # Part. w/i CHI2 WDW", 11, 0, 10 }
//     , { "BachMu_NOPARTWITHINCHI2_1", "bmchi1_stack", "BachMu # Part. w/i 1  CHI2", 11, 0, 10 }
//     , { "BachMu_NOPARTWITHINCHI2_4", "bmchi4_stack", "BachMu # Part. w/i 4  CHI2", 11, 0, 10 }
//     , { "BachMu_NOPARTWITHINCHI2_9", "bmchi9_stack", "BachMu # Part. w/i 9  CHI2", 11, 0, 10 }
//     , { "BachMu_NOPARTWITHINCHI2_16", "bmchi16_stack", "BachMu # Part. w/i 16  CHI2", 11, 0, 10 }
//     , { "BachMu_NOPARTWITHINCHI2_25", "bmchi25_stack", "BachMu # Part. w/i 25  CHI2", 11, 0, 10 }
//     , { "BachMu_SMALLESTCHI2", "bmminchi2_stack", "BachMu Min. CHI2 w/ Extra Track", 50, 0, 150 }
//     , { "BachMu_SMALLESTCHI2_MM", "bmextramm_stack", "BachMu Mass w/ Best Extra Track", 50, 0, 5000 }
  };

void histomaker()
{
  // Input TTrees
  cout << "Finding input TTrees ..." << endl;
  //  TTree* mu = (TTree*)_file0->Get("DecayTree");
  TTree* tau = (TTree*)_file0->Get("DecayTree");
  TTree* bkg1 = (TTree*)_file1->Get("DecayTree");
  TTree* bkg2 = (TTree*)_file2->Get("DecayTree");
  //  TTree* trees[numTrees] = {mu, tau, bkg1, bkg2};
  TTree* trees[numTrees] = {tau, bkg1, bkg2};
  
  // Output File
  cout << "Creating output TFile ..." << endl;
  TFile OutFile("output_histos.root","RECREATE");

  // Style
//   Double_t Red[3]    = { 1.00, 0.00, 0.00 };
//   Double_t Green[3]  = { 0.00, 1.00, 0.00 };
//   Double_t Blue[3]   = { 1.00, 0.00, 1.00 };
//   Double_t Length[3] = { 0.00, 0.50, 1.00 };
//   TColor::CreateGradientColorTable(Number,Length,Red,Green,Blue,numBkgs);
//  gStyle->SetPalette(numBkgs);

  // Processing
  THStack* stacks_list[numStacks];
  TH1F* bkg_histos_list[numStacks][numBkgs];
  TH1F* all_histos_list[numStacks][numBkgs][numTrees];

  for (int s = 0; s < numStacks; s++) {
    THStack *var_stack = new THStack(stackInfo[s].name,stackInfo[s].title);

    for (int b = numBkgs-1; b >= 0; b--) {

      char bkghistoname[100];
      sprintf(bkghistoname, "%s_%s",stackInfo[s].name,bkgInfo[b].name);
      TH1F* bkghisto = new TH1F(bkghistoname,bkghistoname,stackInfo[s].bins, stackInfo[s].min, stackInfo[s].max);
      //      bkghisto->SetFillColor(majorColors[b % numColors]);
      bkghisto->SetLineColor(majorColors[b % numColors]);
      bkghisto->SetMarkerColor(majorColors[b % numColors]);
      //      bkghisto->Sumw2();

      for (int t = 0; t < numTrees; t++) {

        TTree* tree = trees[t];
        
        char histoname[100];
        sprintf(histoname, "%s_%s_%d",stackInfo[s].name,bkgInfo[b].name,t);
        TH1F* histo = new TH1F(histoname,histoname,stackInfo[s].bins, stackInfo[s].min, stackInfo[s].max);
        histo->SetFillColor(majorColors[b % numColors]);
        histo->SetLineColor(majorColors[b % numColors]);
        histo->SetMarkerColor(majorColors[b % numColors]);

        tree->Project(histoname,stackInfo[s].var,bkgInfo[b].cut);
        bkghisto->Add(histo,treeInfo[t].weight);
        all_histos_list[s][b][t] = histo;
        OutFile.cd();
        histo->Write();
      }
      
      // Get histo off of THStack
      var_stack->Add(bkghisto);
      bkg_histos_list[s][b] = bkghisto;
      OutFile.cd();
      bkghisto->Write();
    }

    char c1name[100];
    sprintf(c1name,"%s_stacked",stackInfo[s].name);
    TCanvas* c1 = new TCanvas(c1name,stackInfo[s].title,10,10,800,800);
    c1->cd();
    var_stack->Draw();

    char c2name[100];
    sprintf(c2name,"%s_notstacked",stackInfo[s].name);
    TCanvas* c2 = new TCanvas(c2name,stackInfo[s].title,10,10,800,800);
    c2->cd();
    var_stack->Draw("nostack");
    stacks_list[s] = var_stack;    
    OutFile.cd();
    var_stack->Write();
    c1->Write();
    c2->Write();
    delete c1;
    delete c2;
  }
}
