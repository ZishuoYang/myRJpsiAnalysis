#include <cmath>
#include <iostream>
#include <string>
using std::cout;
using std::endl;
using std::string;

#include <TROOT.h>
#include <TFile.h>
#include <TTree.h>
#include <TH1F.h>
#include <TMath.h>

long count(TTree* tree,
           string condA="",
           string condB="",
           string condC="",
           string condD="",
           string condE="",
           string condF="",
           string condG="",
           string condH="",
           string condI="",
           string condJ="") 
{
  string cond = condA;
  if (condB != "")
    cond += " && " + condB ;
  if (condC != "")
    cond += " && " + condC ;
  if (condD != "")
    cond += " && " + condD ;
  if (condE != "")
    cond += " && " + condE ;
  if (condF != "")
    cond += " && " + condF ;
  if (condG != "")
    cond += " && " + condG ;
  if (condH != "")
    cond += " && " + condH ;
  if (condI != "")
    cond += " && " + condI ;
  if (condJ != "")
    cond += " && " + condJ ;

  long c = tree->Draw("",cond.c_str());
  return c;
}

long integrate(TTree* tree,
               string condA="",
               string condB="",
               string condC="",
               string condD="",
               string condE="",
               string condF="",
               string condG="",
               string condH="",
               string condI="",
               string condJ="") 
{
  string cond = condA;
  if (condB != "")
    cond += " && " + condB ;
  if (condC != "")
    cond += " && " + condC ;
  if (condD != "")
    cond += " && " + condD ;
  if (condE != "")
    cond += " && " + condE ;
  if (condF != "")
    cond += " && " + condF ;
  if (condG != "")
    cond += " && " + condG ;
  if (condH != "")
    cond += " && " + condH ;
  if (condI != "")
    cond += " && " + condI ;
  if (condJ != "")
    cond += " && " + condJ ;

  string cut = "weight/W*(" + cond + ")";
  TH1F* htemp = new TH1F("htemp","htemp",100,-100,100);
  tree->Draw("MissMass2>>htemp",cut.c_str());
  double num = htemp->Integral();
  long c = static_cast<long>(num);
  return c;
}

void prob_info(long N, long Ntot)
{
  if (Ntot == 0) {
    cout << "Ntot is 0!!!" << endl;
    return;
  }  
  
  double prob = N/double(Ntot);
  double var = prob*(1.0-prob)/double(Ntot);
  double err = TMath::Sqrt(var);
  cout << 100*prob << " +/- " << 100*err << " %\n";
}

// RATIO OF NA / (Ntot - NA), with error
void ratio_info(long NA, long Ntot)
{
  if (Ntot == 0) {
    cout << "Ntot is 0!!!\n";
    return;
  }  
  
  double Aprob = NA/double(Ntot);
  double Avar = Aprob*(1.0-Aprob)/double(Ntot);
  double Aerr = TMath::Sqrt(Avar);

  double r = Aprob/(1-Aprob);
  double rerr = Aerr/(1-2*Aprob+Aprob*Aprob);

  cout << r << " +/- " << rerr << "\n";
}

// RATIO OF NA/NB, disjoint samples out of Ntot, x probability for NC/Ntot2, with error
void uncor_ratio_info(long NA, long NB, long NC, long NtotC) 
{
  if (NB == 0 || NtotC == 0) {
    cout << "Ntot is 0!!!" << endl;
    return;
  }  
  
  double r = NA/double(NB);
  double rvar = r * r * ( 1.0/double(NA) + 1.0/double(NB) );

  double Cprob = NC/double(NtotC);
  double Cvar = Cprob*(1.0-Cprob)/double(NtotC);

  double p = r * Cprob;
  double perr = p * TMath::Sqrt( rvar / r / r + Cvar / Cprob / Cprob);
  
  cout << 100*p << " +/- " << 100*perr << "\n";  
}

// PRODUCT OF NA/NtotA,NB/NtotB FROM DISJOINT SAMPLE
void product_info(long NA, long NtotA, long NB, long NtotB) 
{
  if (NtotA == 0 || NtotB == 0) {
    cout << "Ntot is 0!!!" << endl;
    return;
  }  
  
  double Aprob = NA/double(NtotA);
  double Avar = Aprob*(1.0-Aprob)/double(NtotA);
  double Bprob = NB/double(NtotB);
  double Bvar = Bprob*(1.0-Bprob)/double(NtotB);

  double p = Aprob * Bprob;
  double perr = p * TMath::Sqrt( Avar / Aprob / Aprob + Bvar / Bprob / Bprob);
  
  cout << 100*p << " +/- " << 100*perr << "\n";  
}


void eff_calculator(int mode, int FF)
{
  string my_filename = "bcharm_gauss_roots/";
  string my_mctuple;
  string bkk_filename = "bcharm_mc_roots/";
  string bkk_mctuple;
  string bkk_rectuple;
  string tagger;

  if (mode == 0 && FF == 0) {
    my_filename += "Bc2JpsiMu_GaussTruth.root";
    my_mctuple = "MCBc2JpsiMuTuple/MCMuDecayTree";
    bkk_filename += "Bc_SIG_Mu";
    bkk_mctuple = "MCBc2JpsiMuTuple/MCMuDecayTree";
    bkk_rectuple = "Bc2JpsiMu_Tuple/DecayTree";
    tagger = "(Bc_Bc2JpsiMuNu == 1)";
  } else if (mode == 0 && FF == 1) {
    my_filename += "Bc2JpsiMuKiselev_GaussTruth.root";
    my_mctuple = "MCBc2JpsiMuTuple/MCMuDecayTree";
    bkk_filename += "Bc_SIG_MuKiselev";
    bkk_mctuple = "MCBc2JpsiMuTuple/MCMuDecayTree";
    bkk_rectuple = "Bc2JpsiMu_Tuple/DecayTree";
    tagger = "(Bc_Bc2JpsiMuNu == 1)";
  } else if (mode == 0 && FF == 2) {
    my_filename += "Bc2JpsiMuEbert_GaussTruth.root";
    my_mctuple = "MCBc2JpsiMuTuple/MCMuDecayTree";
    bkk_filename += "Bc_SIG_MuEbert";
    bkk_mctuple = "MCBc2JpsiMuTuple/MCMuDecayTree";
    bkk_rectuple = "Bc2JpsiMu_Tuple/DecayTree";
    tagger = "(Bc_Bc2JpsiMuNu == 1)";
  } else if (mode == 0 && FF == 3) {
    my_filename += "Bc2JpsiMu_GaussTruth.root";
    my_mctuple = "MCBc2JpsiMuTuple/MCMuDecayTree";
    bkk_filename += "Bc_SIG_Mu_2012";
    bkk_mctuple = "MCBc2JpsiMuTuple/MCMuDecayTree";
    bkk_rectuple = "Bc2JpsiMu_Tuple/DecayTree";
    tagger = "(Bc_Bc2JpsiMuNu == 1)";
  } else if (mode == 1 && FF == 0) {
    my_filename += "Bc2JpsiTau_GaussTruth.root";
    my_mctuple = "MCBc2JpsiTauTuple/MCTauDecayTree";
    bkk_filename += "Bc_SIG_Tau";
    bkk_mctuple = "MCBc2JpsiTauTuple/MCTauDecayTree";
    bkk_rectuple = "Bc2JpsiMu_Tuple/DecayTree";
    tagger = "(Bc_Bc2JpsiTauNu == 1)";
  } else if (mode == 2 && FF == 0) {
    my_filename += "Bc2psi2SFDMu_GaussTruth.root";
    my_mctuple = "MCBc2JpsiMuTuple/MCMuDecayTree";
    bkk_filename += "Bc_BKG_Psi2SFD";
    bkk_mctuple = "MCBc2Psi2SMuTuple/MCMuDecayTree";
    bkk_rectuple = "Bc2Psi2SMu_Tuple/DecayTree";
    tagger = "(Bc_Bc2Psi2SMuNu == 1)";
  } else {
    cout << "COMBINATION NOT AVAILABLE\n";
    return 0;
  }
  
  string cand_filename = bkk_filename + "_Cands.root";
  string weight_filename = bkk_filename + "_Weights.root";
  bkk_filename += ".root";

  // OPEN FILE AND GET MC TREE, REC TREE
  gROOT->Reset();
  gStyle->SetOptStat(1001111);

  // Generated MC with Acceptance info
  TFile* myf = new TFile(my_filename.c_str(),"READ");
  TTree* mymctree = (TTree*)myf->Get(my_mctuple.c_str());
  if (!mymctree)
    cout << "There is no MC Truth tree in the pythia toy rootfile" << endl;
  
  // BKK rootfile (after online selection)
  TFile* bkkf = new TFile(bkk_filename.c_str(),"READ");
  TTree* mctree = (TTree*)bkkf->Get(bkk_mctuple.c_str());
  if (!mctree)
    cout << "There is no MC Truth tree in the BKK rootfile" << endl;
  TTree* rectree = (TTree*)bkkf->Get(bkk_rectuple.c_str());
  if (!rectree)
    cout << "There is no REC tree in the BKK rootfile" << endl;

  // Cand rootfile (after trigger, stripping, offline selection)
  TFile* candf = new TFile(cand_filename.c_str(),"READ");
  TTree* candtree = (TTree*)candf->Get("DecayTree");
  candtree->AddFriend("weightTree",weight_filename.c_str());
  if (!candtree)
    cout << "There is no REC tree in the processed rootfile" << endl;
  

  // COUNTERS
  string BCETA = "0.5*TMath::Log("
    "(TMath::Sqrt(Bc_TRUEP_Z*Bc_TRUEP_Z + Bc_TRUEPT*Bc_TRUEPT) + Bc_TRUEP_Z)"
    " / "
    " (TMath::Sqrt(Bc_TRUEP_Z*Bc_TRUEP_Z + Bc_TRUEPT*Bc_TRUEPT) - Bc_TRUEP_Z)"
    " )";
  string BCPT = "Bc_TRUEPT";
  string BACHMUTHETA = "(TMath::ATan(BachMu_TRUEPT/BachMu_TRUEP_Z))";
  string MUPTHETA = "(TMath::ATan(MuP_TRUEPT/MuP_TRUEP_Z))";
  string MUMTHETA = "(TMath::ATan(MuM_TRUEPT/MuM_TRUEP_Z))";

  // DaughtersInLHCb acceptance cut (Daughters)
  // MC cut is 10 to 400 mrad
  string ACCEPTANCE = 
    "(" + BACHMUTHETA + " > 0.010) && (" + BACHMUTHETA + " < 0.400)"
    " && (" + MUPTHETA    + " > 0.010) && (" + MUPTHETA + " < 0.400)"
    " && (" + MUMTHETA    + " > 0.010) && (" + MUMTHETA + " < 0.400)";
  string NOT_ACCEPTANCE = "!(" + ACCEPTANCE + ")";

  string FORWARD_BC = "Bc_TRUEP_Z>0";
  string NOT_FORWARD_BC = "!(" + FORWARD_BC + ")";

  string KR_BC =
    "(TMath::Abs(" + BCETA + " - 3.5) < 1) && (Bc_TRUEPT > 5*1000) && (Bc_TRUEPT < 100*1000)";
  string EX_BC = "!(" + KR_BC + ")";

  string RECO =
    "BachMu_Reconstructed==1 && MuP_Reconstructed==1 && MuM_Reconstructed==1";
  string NRECO = "!(" + RECO + ")";

  //   string TriMuonStripped = "StrippingTriMuonBc2ThreeMuDecision";
  //   string FullDSTStripped = "StrippingFullDSTDiMuonJpsi2MuMuDetachedLineDecision";

  //  Stripping definitions out of date; use this instead
  // Stripping 17b -> Stripping 20 tightens StrippingTriMuonBc2ThreeMuDecision
  string FullDSTStripped =
    "(Jpsi_FD_OWNPV / sqrt(Jpsi_FDCHI2_OWNPV) < 3)"
    " && (Jpsi_ENDVERTEX_CHI2 / Jpsi_ENDVERTEX_NDOF < 20)"
    " && (MuM_PT > 550) && (MuM_PT > 550)"
    " && (MuP_IPCHI2_OWNPV > 4) && (MuM_IPCHI2_OWNPV > 4)"
    " && (MuP_TRACK_CHI2NDOF < 5) && (MuM_TRACK_CHI2NDOF < 5)"
    " && (MuP_PIDmu > 0) && (MuM_PIDmu > 0)";

  string STRIPPED = FullDSTStripped + " && " + tagger;
  string STRIPPED_BKG = FullDSTStripped + " && !(" + tagger + ")";
  
  // Hlt2DiMuonJpsiHighPT has the 2GeV PT cut -- put this in selection to move some efficiency over here
  string SELECTED = "Bc_ENDVERTEX_CHI2/Bc_ENDVERTEX_NDOF<25 && BachMu_IPCHI2_OWNPV>4 && Jpsi_PT>2000";
  //  SELECTED += " && MuP_IPCHI2_OWNPV>9 && MuM_IPCHI2_OWNPV>9";
  //  SELECTED += " && BachMu_PT > 300";

  string TRIG = 
    "(Bc_L0MuonDecision_TOS | Bc_L0DiMuonDecision_TOS)"
    " && (Bc_Hlt1DiMuonHighMassDecision_TOS | Bc_Hlt1DiMuonLowMassDecision_TOS)"
    " && Bc_Hlt2DiMuonJPsiHighPTDecision_TOS";

//   string OFFLINE = 
//     "(Bc_MM > 3202.574) && (Bc_MM < 6277)"
//     " && Bc_ENDVERTEX_CHI2 < 30"
//     " && abs(Jpsi_MM-3096.616) < 50"
//     " && abs(5279.25 - sqrt("
//     " (sqrt(493.677*493.677 + BachMu_P*BachMu_P)+Jpsi_PE)*(sqrt(483.677*493.677 + BachMu_P*BachMu_P)+Jpsi_PE)"
//     " - (BachMu_PX+Jpsi_PX)*(BachMu_PX+Jpsi_PX)"
//     " - (BachMu_PY+Jpsi_PY)*(BachMu_PY+Jpsi_PY)"
//     " - (BachMu_PZ+Jpsi_PZ)*(BachMu_PZ+Jpsi_PZ)"
//     " )) > 50"
//     " && abs(3096.916 - sqrt("
//     "   (BachMu_PE+MuM_PE)*(BachMu_PE+MuM_PE)"
//     " - (BachMu_PX+MuM_PX)*(BachMu_PX+MuM_PX)"
//     " - (BachMu_PY+MuM_PY)*(BachMu_PY+MuM_PY)"
//     " - (BachMu_PZ+MuM_PZ)*(BachMu_PZ+MuM_PZ)"
//     " )) > 50"
//     " && (BachMu_ProbNNmu > 0.5) && (BachMu_ProbNNghost < 0.1)"
//     " && (MuP_ProbNNmu > 0.2) && (MuM_ProbNNmu > 0.2)"
//     " && (MuP_ProbNNghost < 0.1) && (MuM_ProbNNghost < 0.1)";

  string MY_ACCEPTANCE = "BachMu_ACC && MuP_ACC && MuM_ACC";

  string MY_KR_BC =
    "(TMath::Abs( TMath::Abs(Bc_MCETA) - 3.5) < 1) && (Bc_MCPT > 5*1000) && (Bc_MCPT < 100*1000)";
  string MY_EX_BC = "!(" + MY_KR_BC + ")";
  
  long MY_N = count(mymctree);

  long MY_N_KR = count(mymctree,MY_KR_BC);
  cout << "P(KR|FORWARD) = "; prob_info(MY_N_KR,MY_N);
  long MY_N_EX = MY_N - MY_N_KR;
  cout << "P(EX|FORWARD) = "; prob_info(MY_N_EX,MY_N);

  cout << "RATIO EX:KR = "; ratio_info(MY_N_EX,MY_N);
  cout << "RATIO KR:EX = "; ratio_info(MY_N_KR,MY_N);

  cout << "\n---------------------------------------------------------\n";
  cout << "TRIGGER/STRIPPING EFFICIENCY IN KINEMATIC RANGE:";
  cout << "\n---------------------------------------------------------\n";
  
  long MY_N_ACC = count(mymctree,MY_KR_BC,MY_ACCEPTANCE);
  cout << "P(ACCEPTANCE|KR) = "; prob_info(MY_N_ACC,MY_N_KR);

  // NOW SWITCH TO USING BKK MONTE CARLO
  long N_ACC = count(mctree,FORWARD_BC,KR_BC,ACCEPTANCE);
  long N_RECO = count(mctree,FORWARD_BC,KR_BC,ACCEPTANCE,RECO);
  cout << "P(RECO|ACCEPTANCE) = "; prob_info(N_RECO,N_ACC);

  // Now we get to selected, so we need the reconstructed tree
  long N_STRIPPED = count(rectree,FORWARD_BC,KR_BC,ACCEPTANCE,STRIPPED);
  cout << "P(STRIPPED+TMED|RECO) = "; prob_info(N_STRIPPED,N_RECO);
  long N_SEL = count(rectree,FORWARD_BC,KR_BC,ACCEPTANCE,STRIPPED,SELECTED);
  cout << "P(SEL|STRIPPED+TMED) = "; prob_info(N_SEL,N_STRIPPED);
  long N_TRIG = count(rectree,FORWARD_BC,KR_BC,ACCEPTANCE,STRIPPED,SELECTED,TRIG);
  cout << "N(TRIG) = " << N_TRIG << endl;
  cout << "P(TRIG|SEL) = "; prob_info(N_TRIG,N_SEL);

  // For offline cuts, use candtree
  long N_OFFLINE = integrate(candtree,tagger,KR_BC);
  cout << "N(OFFLINE) = " << N_OFFLINE << endl;
  cout << "P(OFFLINE|TRIG) = "; prob_info(N_OFFLINE,N_TRIG);

  // Now to compute total efficiency: multiply above by the acceptance efficiency
  // These are completely uncorrelated
  cout << "TOTAL EFFICIENCY: "; product_info(MY_N_ACC,MY_N_KR,N_OFFLINE,N_ACC);

  cout << "\n---------------------------------------------------------\n";
  cout << "TRIGGER/STRIPPING EFFICIENCY OUTSIDE KINEMATIC RANGE:";
  cout << "\n---------------------------------------------------------\n";
  
  MY_N_ACC = count(mymctree,MY_EX_BC,MY_ACCEPTANCE);
  cout << "P(ACCEPTANCE|EX) = "; prob_info(MY_N_ACC,MY_N_EX);

  // NOW SWITCH TO USING BKK MONTE CARLO
  N_ACC = count(mctree,FORWARD_BC,EX_BC,ACCEPTANCE);
  N_RECO = count(mctree,FORWARD_BC,EX_BC,ACCEPTANCE,RECO);
  cout << "P(RECO|ACCEPTANCE) = "; prob_info(N_RECO,N_ACC);
  N_RECO = N_RECO;

  // Now we get to selected, so we need the reconstructed tree
  N_STRIPPED = count(rectree,FORWARD_BC,EX_BC,ACCEPTANCE,STRIPPED);
  cout << "P(STRIPPED+TMED|RECO) = "; prob_info(N_STRIPPED,N_RECO);
  N_SEL = count(rectree,FORWARD_BC,EX_BC,ACCEPTANCE,STRIPPED,SELECTED);
  cout << "P(SEL|STRIPPED) = "; prob_info(N_SEL,N_STRIPPED);
  N_TRIG = count(rectree,FORWARD_BC,EX_BC,ACCEPTANCE,STRIPPED,SELECTED,TRIG);
  cout << "P(TRIG|SEL) = "; prob_info(N_TRIG,N_SEL);

  // For offline cuts, use candtree
  long N_OFFLINE = integrate(candtree,tagger,EX_BC);
  cout << "N(OFFLINE) = " << N_OFFLINE << endl;
  cout << "P(OFFLINE|TRIG) = "; prob_info(N_OFFLINE,N_TRIG);

  // Now to compute total efficiency: multiply above by the acceptance efficiency
  // These are completely uncorrelated
  cout << "TOTAL EFFICIENCY: "; product_info(MY_N_ACC,MY_N_EX,N_OFFLINE,N_ACC);
  cout << "R x TOTAL EFFICIENCY = "; uncor_ratio_info(MY_N_ACC,MY_N_KR,N_OFFLINE,N_ACC);
  
  cout << "\n---------------------------------------------------------\n";
  cout << "TRIGGER/STRIPPING EFFICIENCY FOR BACKGROUND";
  cout << "\n---------------------------------------------------------\n";
  
  // For offline cuts, use candtree
  string isbkg = "!(" + tagger + ")";
  long N_BKG = integrate(candtree,isbkg);
  cout << "N(BKG) = " << N_BKG << endl;

}
