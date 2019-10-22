#include <cmath>
#include <iostream>
#include <string>
using std::cout;
using std::endl;
using std::string;

#include <TROOT.h>
#include <TFile.h>
#include <TTree.h>
//#include <TH1F.h>
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

// RATIO OF NA/NB, disjoint samples out of Ntot, with error
void uncor_ratio_info(long NA,long NB, long Ntot) 
{
  if (Ntot == 0) {
    cout << "Ntot is 0!!!" << endl;
    return;
  }  
  
  double Aprob = NA/double(Ntot);
  double Avar = Aprob*(1.0-Aprob)/double(Ntot);
  double Bprob = NB/double(Ntot);
  double Bvar = Bprob*(1.0-Bprob)/double(Ntot);

  double r = NA/double(NB);
  double rerr = r * TMath::Sqrt( Avar / Aprob / Aprob + Bvar / Bprob / Bprob);
  
  cout << r << " +/- " << rerr << "\n";  
}


void efficiencies()
{

  // OPEN FILE AND GET MC TREE, REC TREE
  gROOT->Reset();
  TFile* f = new TFile("Bc_SIG_MuEbert.root","READ");
  TTree* mctree = (TTree*)f->Get("MCBc2JpsiMuTuple/MCMuDecayTree");
  //TTree* mctree = (TTree*)f->Get("MCBc2JpsiTauTuple/MCTauDecayTree");
  TTree* rectree = (TTree*)f->Get("Bc2JpsiMu_Tuple/DecayTree");
   
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

  string STRIPPED = 
    //    "StrippingFullDSTDiMuonJpsi2MuMuDetachedLineDecision";
    "StrippingTriMuonBc2ThreeMuDecision";
  string NOT_STRIPPED = "!(" + STRIPPED + ")";

  string TRIG = 
    "(Bc_L0MuonDecision_TOS | Bc_L0DiMuonDecision_TOS)"
    " && (Bc_Hlt1DiMuonHighMassDecision_TOS | Bc_Hlt1DiMuonLowMassDecision_TOS)"
    " && Bc_Hlt2DiMuonJPsiHighPTDecision_TOS";
  
  string TMED = "Bc_BKGCAT==0 && " + STRIPPED;
  //string TMED = "Bc_BKGCAT==10";
  
  long N = count(mctree);
  long N_FOR = count(mctree,FORWARD_BC);
  cout << "P(FORWARD) = "; prob_info(N_FOR,N);

  long N_KR = count(mctree,FORWARD_BC,KR_BC);
  cout << "P(KR|FORWARD) = "; prob_info(N_KR,N_FOR);
  long N_EX = N_FOR - N_KR;
  cout << "P(EX|FORWARD) = "; prob_info(N_EX,N_FOR);

  cout << "RATIO EX:KR = "; ratio_info(N_EX,N_FOR);
  cout << "RATIO KR:EX = "; ratio_info(N_KR,N_FOR);

  cout << "\n---------------------------------------------------------\n";
  cout << "TRIGGER/STRIPPING EFFICIENCY IN KINEMATIC RANGE:";
  cout << "\n---------------------------------------------------------\n";
  
  long N_ACC = count(mctree,FORWARD_BC,KR_BC,ACCEPTANCE);
  cout << "P(ACCEPTANCE|KR) = "; prob_info(N_ACC,N_KR);
  long N_RECO = count(mctree,FORWARD_BC,KR_BC,ACCEPTANCE,RECO);
  cout << "P(RECO|ACCEPTANCE) = "; prob_info(N_RECO,N_ACC);
  long N_STRIPPED = count(mctree,FORWARD_BC,KR_BC,ACCEPTANCE,RECO,STRIPPED);
  cout << "P(STRIPPED|RECO) = "; prob_info(N_STRIPPED,N_RECO);

  // Now we get to selected, so we need the reconstructed tree
  long N_SEL = count(rectree,FORWARD_BC,KR_BC,ACCEPTANCE,STRIPPED,TMED);
  cout << "P(SEL|STRIPPED) = "; prob_info(N_SEL,N_STRIPPED);
  long N_TRIG = count(rectree,FORWARD_BC,KR_BC,ACCEPTANCE,STRIPPED,TMED,TRIG);
  cout << "P(TRIG|SEL) = "; prob_info(N_TRIG,N_SEL);
  cout << "TOTAL EFFICIENCY: "; prob_info(N_SEL,N_KR);
  cout << "TOTAL EFFICIENCY (excl acc): "; prob_info(N_SEL,N_ACC);

//   cout << "Cross check: we should get the same thing w/o require FORWARD_BC and ACCEPTANCE\n";
//   N_SEL = count(rectree,KR_BC,STRIPPED,TMED);
//   cout << "CHECK P(SEL|STRIPPED) = "; prob_info(N_SEL,N_STRIPPED);
//   N_TRIG = count(rectree,KR_BC,STRIPPED,TMED,TRIG);
//   cout << "CHECK P(TRIG|SEL) = "; prob_info(N_TRIG,N_SEL);
//   cout << "CHECK TOTAL EFFICIENCY: "; prob_info(N_SEL,N_KR);

  cout << "\n---------------------------------------------------------\n";
  cout << "TRIGGER/STRIPPING EFFICIENCY OUTSIDE KINEMATIC RANGE:";
  cout << "\n---------------------------------------------------------\n";
  
  N_ACC = count(mctree,FORWARD_BC,EX_BC,ACCEPTANCE);
  cout << "P(ACCEPTANCE|EX) = "; prob_info(N_ACC,N_EX);
  cout << "R x P(ACCEPTANCE|EX) = "; uncor_ratio_info(N_ACC,N_KR,N_FOR);
  N_RECO = count(mctree,FORWARD_BC,EX_BC,ACCEPTANCE,RECO);
  cout << "P(RECO|ACCEPTANCE) = "; prob_info(N_RECO,N_ACC);
  N_STRIPPED = count(mctree,FORWARD_BC,EX_BC,ACCEPTANCE,RECO,STRIPPED);
  cout << "P(STRIPPED|RECO) = "; prob_info(N_STRIPPED,N_RECO);

  // Now we get to selected, so we need the reconstructed tree
  N_SEL = count(rectree,FORWARD_BC,EX_BC,ACCEPTANCE,STRIPPED,TMED);
  cout << "P(SEL|STRIPPED) = "; prob_info(N_SEL,N_STRIPPED);
  N_TRIG = count(rectree,FORWARD_BC,EX_BC,ACCEPTANCE,STRIPPED,TMED,TRIG);
  cout << "P(TRIG|SEL) = "; prob_info(N_TRIG,N_SEL);
  cout << "TOTAL EFFICIENCY: "; prob_info(N_SEL,N_EX);
  cout << "TOTAL EFFICIENCY (excl acc): "; prob_info(N_SEL,N_ACC);

//   cout << "Cross check: we should get the same thing w/o require FORWARD_BC and ACCEPTANCE\n";
//   N_SEL = count(rectree,EX_BC,STRIPPED,TMED);
//   cout << "CHECK P(SEL|STRIPPED) = "; prob_info(N_SEL,N_STRIPPED);
//   N_TRIG = count(rectree,EX_BC,STRIPPED,TMED,TRIG);
//   cout << "CHECK P(TRIG|SEL) = "; prob_info(N_TRIG,N_SEL);
//   cout << "CHECK TOTAL EFFICIENCY: "; prob_info(N_SEL,N_EX);

}
