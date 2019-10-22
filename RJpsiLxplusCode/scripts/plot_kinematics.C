#include <cmath>
#include <iostream>
#include <string>
using std::cout;
using std::endl;
using std::string;

#include <TROOT.h>
#include <TFile.h>
#include <TMath.h>
#include <TTree.h>
#include <TH1F.h>
#include <TCanvas.h>

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

void probinfo(long N, long Ntot)
{
  double prob = N/double(Ntot);
  // double err = sqrt(N)/double(Ntot);
  double upp_err = (+0.5 + sqrt(N+0.25))/double(Ntot);
  double low_err = (-0.5 + sqrt(N+0.25))/double(Ntot);
  cout << 100*prob << " + " << 100*upp_err << " - " << 100*low_err << " %" << endl;
}


void gen_acceptance(TTree* mctree)
{
  TCanvas* c_eta = new TCanvas("eta","eta",0,0,1000,1000);
  c_eta->Divide(2,4);
  TH1F* etahist = new TH1F("etahist","etahist",100,-10,10);
  TH1F* etahist_sig = new TH1F("etahist_sig","etahist_sig",100,-10,10);
  TH1F* etahist_nsig = new TH1F("etahist_nsig","etahist_nsig",100,-10,10);
  TH1F* etahist_acc = new TH1F("etahist_acc","etahist_acc",100,-10,10);
  TH1F* etahist_nrough = new TH1F("etahist_nrough","etahist_nrough",100,-10,10);
  TH1F* etahist_for = new TH1F("etahist_for","etahist_for",100,-10,10);
  TH1F* etahist_nfor = new TH1F("etahist_nfor","etahist_nfor",100,-10,10);
  
  TCanvas* c_pt = new TCanvas("pt","pt",0,0,1000,1000);
  c_pt->Divide(2,4);
  TH1F* pthist = new TH1F("pthist","pthist",100,0,150000);
  TH1F* pthist_sig = new TH1F("pthist_sig","pthist_sig",100,0,150000);
  TH1F* pthist_nsig = new TH1F("pthist_nsig","pthist_nsig",100,0,150000);
  TH1F* pthist_acc = new TH1F("pthist_acc","pthist_acc",100,0,150000);
  TH1F* pthist_nrough = new TH1F("pthist_nrough","pthist_nrough",100,0,150000);
  TH1F* pthist_for = new TH1F("pthist_for","pthist_for",100,0,150000);
  TH1F* pthist_nfor = new TH1F("pthist_nfor","pthist_nfor",100,0,150000);
  
  TCanvas* c_bmtheta = new TCanvas("bmtheta","bmtheta",0,0,1000,1000);
  c_bmtheta->Divide(2,4);
  TH1F* bmthetahist = new TH1F("bmthetahist","bmthetahist",100,0,600);
  TH1F* bmthetahist_sig = new TH1F("bmthetahist_sig","bmthetahist_sig",100,0,600);
  TH1F* bmthetahist_nsig = new TH1F("bmthetahist_nsig","bmthetahist_nsig",100,0,600);
  TH1F* bmthetahist_acc = new TH1F("bmthetahist_acc","bmthetahist_acc",100,0,600);
  TH1F* bmthetahist_nrough = new TH1F("bmthetahist_nrough","bmthetahist_nrough",100,0,600);
  TH1F* bmthetahist_for = new TH1F("bmthetahist_for","bmthetahist_for",100,0,600);
  TH1F* bmthetahist_nfor = new TH1F("bmthetahist_nfor","bmthetahist_nfor",100,0,600);
  
  TCanvas* c_muptheta = new TCanvas("muptheta","muptheta",0,0,1000,1000);
  c_muptheta->Divide(2,4);
  TH1F* mupthetahist = new TH1F("mupthetahist","mupthetahist",100,0,600);
  TH1F* mupthetahist_sig = new TH1F("mupthetahist_sig","mupthetahist_sig",100,0,600);
  TH1F* mupthetahist_nsig = new TH1F("mupthetahist_nsig","mupthetahist_nsig",100,0,600);
  TH1F* mupthetahist_acc = new TH1F("mupthetahist_acc","mupthetahist_acc",100,0,600);
  TH1F* mupthetahist_nrough = new TH1F("mupthetahist_nrough","mupthetahist_nrough",100,0,600);
  TH1F* mupthetahist_for = new TH1F("mupthetahist_for","mupthetahist_for",100,0,600);
  TH1F* mupthetahist_nfor = new TH1F("mupthetahist_nfor","mupthetahist_nfor",100,0,600);
  
  TCanvas* c_mumtheta = new TCanvas("mumtheta","mumtheta",0,0,1000,1000);
  c_mumtheta->Divide(2,4);
  TH1F* mumthetahist = new TH1F("mumthetahist","mumthetahist",100,0,600);
  TH1F* mumthetahist_sig = new TH1F("mumthetahist_sig","mumthetahist_sig",100,0,600);
  TH1F* mumthetahist_nsig = new TH1F("mumthetahist_nsig","mumthetahist_nsig",100,0,600);
  TH1F* mumthetahist_acc = new TH1F("mumthetahist_acc","mumthetahist_acc",100,0,600);
  TH1F* mumthetahist_nrough = new TH1F("mumthetahist_nrough","mumthetahist_nrough",100,0,600);
  TH1F* mumthetahist_for = new TH1F("mumthetahist_for","mumthetahist_for",100,0,600);
  TH1F* mumthetahist_nfor = new TH1F("mumthetahist_nfor","mumthetahist_nfor",100,0,600);
  
  string BCETA = "0.5*TMath::Log("
    "(TMath::Sqrt(Bc_TRUEP_Z*Bc_TRUEP_Z + Bc_TRUEPT*Bc_TRUEPT) + Bc_TRUEP_Z)"
    " / "
    " (TMath::Sqrt(Bc_TRUEP_Z*Bc_TRUEP_Z + Bc_TRUEPT*Bc_TRUEPT) - Bc_TRUEP_Z)"
    " )";
  string BCPT = "Bc_TRUEPT";
  string BACHMUTHETA = "(TMath::ATan(BachMu_TRUEPT/BachMu_TRUEP_Z)*1000)"; // in mrad
  string MUPTHETA = "(TMath::ATan(MuP_TRUEPT/MuP_TRUEP_Z)*1000)"; // in mrad
  string MUMTHETA = "(TMath::ATan(MuM_TRUEPT/MuM_TRUEP_Z)*1000)"; // in mrad

  // DaughtersInLHCb acceptance cut (Daughters)
  string ACCEPTANCE = 
    "(" + BACHMUTHETA + " > 5) && (" + BACHMUTHETA + " < 400)"
    " && (" + MUPTHETA    + " > 5) && (" + MUPTHETA + " < 400)"
    " && (" + MUMTHETA    + " > 5) && (" + MUMTHETA + " < 400)";

  // Bc dimuon in acceptance (opposite side dimuons don't pass) (GenCut)
//   string ACCEPTANCE =
//     "( ( (" + BACHMUTHETA + " > 10) && (" + BACHMUTHETA + " < 400)"
//     " && (" + MUMTHETA    + " > 10) && (" + MUMTHETA + " < 400) )"
//     " || ( (" + MUPTHETA + " > 10) && (" + MUPTHETA + " < 400)"
//     " && (" + MUMTHETA    + " > 10) && (" + MUMTHETA + " < 400) ) )";
  
  string NOT_ACCEPTANCE = "!(" + ACCEPTANCE + ")";

  string FORWARD_BC = "Bc_TRUEP_Z>0";
  string NOT_FORWARD_BC = "!(" + FORWARD_BC + ")";

  string SIGNAL_BC =
    "(TMath::Abs(" + BCETA + " - 3.5) < 1) && (Bc_TRUEPT > 5*1000) && (Bc_TRUEPT < 100*1000)";
  string NOT_SIGNAL_BC = "!(" + SIGNAL_BC + ")";

  string RECO =
    "BachMu_Reconstructed==1 && MuP_Reconstructed==1 && MuM_Reconstructed==1";
  string NRECO = "!(" + RECO + ")";

  string STRIPPED = 
    "StrippingTriMuonBc2ThreeMuDecision";
  string NOT_STRIPPED = "!(" + STRIPPED + ")";

  string TRIG = 
    "(L0MuonDecision | L0DiMuonDecision)"
    " && (Hlt1DiMuonHighMassDecision | Hlt1DiMuonLowMassDecision)"
    " && Hlt2DiMuonJPsiHighPTDecision";
  
  mctree->Project("etahist",BCETA.c_str(),"");
  c_eta->cd(1);
  etahist->Draw();
  mctree->Project("etahist_sig",BCETA.c_str(),SIGNAL_BC.c_str());
  c_eta->cd(3);
  etahist_sig->Draw();
  mctree->Project("etahist_nsig",BCETA.c_str(),NOT_SIGNAL_BC.c_str());
  c_eta->cd(4);
  etahist_nsig->Draw();
  mctree->Project("etahist_acc",BCETA.c_str(),ACCEPTANCE.c_str());
  c_eta->cd(5);
  etahist_acc->Draw();
  mctree->Project("etahist_nrough",BCETA.c_str(),NOT_ACCEPTANCE.c_str());
  c_eta->cd(6);
  etahist_nrough->Draw();
  mctree->Project("etahist_for",BCETA.c_str(),FORWARD_BC.c_str());
  c_eta->cd(7);
  etahist_for->Draw();
  mctree->Project("etahist_nfor",BCETA.c_str(),NOT_FORWARD_BC.c_str());
  c_eta->cd(8);
  etahist_nfor->Draw();

  c_eta->Print("c_eta.png");
  delete c_eta;
  delete etahist;
  delete etahist_sig;
  delete etahist_nsig;
  delete etahist_acc;
  delete etahist_nrough;
  delete etahist_for;
  delete etahist_nfor;

  mctree->Project("pthist",BCPT.c_str(),"");
  c_pt->cd(1);
  pthist->Draw();
  gPad->SetLogy();
  mctree->Project("pthist_sig",BCPT.c_str(),SIGNAL_BC.c_str());
  c_pt->cd(3);
  pthist_sig->Draw();
  gPad->SetLogy();
  mctree->Project("pthist_nsig",BCPT.c_str(),NOT_SIGNAL_BC.c_str());
  c_pt->cd(4);
  pthist_nsig->Draw();
  gPad->SetLogy();
  mctree->Project("pthist_acc",BCPT.c_str(),ACCEPTANCE.c_str());
  c_pt->cd(5);
  pthist_acc->Draw();
  gPad->SetLogy();
  mctree->Project("pthist_nrough",BCPT.c_str(),NOT_ACCEPTANCE.c_str());
  c_pt->cd(6);
  pthist_nrough->Draw();
  gPad->SetLogy();
  mctree->Project("pthist_for",BCPT.c_str(),FORWARD_BC.c_str());
  c_pt->cd(7);
  pthist_for->Draw();
  gPad->SetLogy();
  mctree->Project("pthist_nfor",BCPT.c_str(),NOT_FORWARD_BC.c_str());
  c_pt->cd(8);
  pthist_nfor->Draw();
  gPad->SetLogy();

  c_pt->Print("c_pt.png");
  gPad->SetLogy(false);
  delete c_pt;
  delete pthist;
  delete pthist_sig;
  delete pthist_nsig;
  delete pthist_acc;
  delete pthist_nrough;
  delete pthist_for;
  delete pthist_nfor;

  mctree->Project("bmthetahist",BACHMUTHETA.c_str(),"");
  c_bmtheta->cd(1);
  bmthetahist->Draw();
  mctree->Project("bmthetahist_sig",BACHMUTHETA.c_str(),SIGNAL_BC.c_str());
  c_bmtheta->cd(3);
  bmthetahist_sig->Draw();
  mctree->Project("bmthetahist_nsig",BACHMUTHETA.c_str(),NOT_SIGNAL_BC.c_str());
  c_bmtheta->cd(4);
  bmthetahist_nsig->Draw();
  mctree->Project("bmthetahist_acc",BACHMUTHETA.c_str(),ACCEPTANCE.c_str());
  c_bmtheta->cd(5);
  bmthetahist_acc->Draw();
  mctree->Project("bmthetahist_nrough",BACHMUTHETA.c_str(),NOT_ACCEPTANCE.c_str());
  c_bmtheta->cd(6);
  bmthetahist_nrough->Draw();
  mctree->Project("bmthetahist_for",BACHMUTHETA.c_str(),FORWARD_BC.c_str());
  c_bmtheta->cd(7);
  bmthetahist_for->Draw();
  mctree->Project("bmthetahist_nfor",BACHMUTHETA.c_str(),NOT_FORWARD_BC.c_str());
  c_bmtheta->cd(8);
  bmthetahist_nfor->Draw();

  c_bmtheta->Print("c_bmtheta.png");
  delete c_bmtheta;
  delete bmthetahist;
  delete bmthetahist_sig;
  delete bmthetahist_nsig;
  delete bmthetahist_acc;
  delete bmthetahist_nrough;
  delete bmthetahist_for;
  delete bmthetahist_nfor;  

  mctree->Project("mupthetahist",MUPTHETA.c_str(),"");
  c_muptheta->cd(1);
  mupthetahist->Draw();
  mctree->Project("mupthetahist_sig",MUPTHETA.c_str(),SIGNAL_BC.c_str());
  c_muptheta->cd(3);
  mupthetahist_sig->Draw();
  mctree->Project("mupthetahist_nsig",MUPTHETA.c_str(),NOT_SIGNAL_BC.c_str());
  c_muptheta->cd(4);
  mupthetahist_nsig->Draw();
  mctree->Project("mupthetahist_acc",MUPTHETA.c_str(),ACCEPTANCE.c_str());
  c_muptheta->cd(5);
  mupthetahist_acc->Draw();
  mctree->Project("mupthetahist_nrough",MUPTHETA.c_str(),NOT_ACCEPTANCE.c_str());
  c_muptheta->cd(6);
  mupthetahist_nrough->Draw();
  mctree->Project("mupthetahist_for",MUPTHETA.c_str(),FORWARD_BC.c_str());
  c_muptheta->cd(7);
  mupthetahist_for->Draw();
  mctree->Project("mupthetahist_nfor",MUPTHETA.c_str(),NOT_FORWARD_BC.c_str());
  c_muptheta->cd(8);
  mupthetahist_nfor->Draw();
  
  c_muptheta->Print("c_muptheta.png");
  delete c_muptheta;
  delete mupthetahist;
  delete mupthetahist_sig;
  delete mupthetahist_nsig;
  delete mupthetahist_acc;
  delete mupthetahist_nrough;
  delete mupthetahist_for;
  delete mupthetahist_nfor;  

  mctree->Project("mumthetahist",MUMTHETA.c_str(),"");
  c_mumtheta->cd(1);
  mumthetahist->Draw();
  mctree->Project("mumthetahist_sig",MUMTHETA.c_str(),SIGNAL_BC.c_str());
  c_mumtheta->cd(3);
  mumthetahist_sig->Draw();
  mctree->Project("mumthetahist_nsig",MUMTHETA.c_str(),NOT_SIGNAL_BC.c_str());
  c_mumtheta->cd(4);
  mumthetahist_nsig->Draw();
  mctree->Project("mumthetahist_acc",MUMTHETA.c_str(),ACCEPTANCE.c_str());
  c_mumtheta->cd(5);
  mumthetahist_acc->Draw();
  mctree->Project("mumthetahist_nrough",MUMTHETA.c_str(),NOT_ACCEPTANCE.c_str());
  c_mumtheta->cd(6);
  mumthetahist_nrough->Draw();
  mctree->Project("mumthetahist_for",MUMTHETA.c_str(),FORWARD_BC.c_str());
  c_mumtheta->cd(7);
  mumthetahist_for->Draw();
  mctree->Project("mumthetahist_nfor",MUMTHETA.c_str(),NOT_FORWARD_BC.c_str());
  c_mumtheta->cd(8);
  mumthetahist_nfor->Draw();
  
  c_mumtheta->Print("c_mumtheta.png");
  delete c_mumtheta;
  delete mumthetahist;
  delete mumthetahist_sig;
  delete mumthetahist_nsig;
  delete mumthetahist_acc;
  delete mumthetahist_nrough;
  delete mumthetahist_for;
  delete mumthetahist_nfor;  

  long N = count(mctree);
  long N_FOR = count(mctree,FORWARD_BC);
  long N_SIG = count(mctree,SIGNAL_BC);
  long N_ACC = count(mctree,ACCEPTANCE);

  long N_BACK = count(mctree,NOT_FORWARD_BC);
  long N_FOR_N_SIG = count(mctree,FORWARD_BC,NOT_SIGNAL_BC);
  long N_FOR_ONLY = count(mctree,FORWARD_BC,NOT_SIGNAL_BC,NOT_ACCEPTANCE);
  long N_SIG_N_ACC = count(mctree,SIGNAL_BC,NOT_ACCEPTANCE);
  long N_ACC_N_SIG = count(mctree,ACCEPTANCE,NOT_SIGNAL_BC);
  long N_SIG_A_ACC = count(mctree,SIGNAL_BC,ACCEPTANCE);

  cout << "N() = " << N << endl;
  cout << "N(BACKWARD) = " << N_BACK << endl;
  cout << "N(FORWARD) = " << N_FOR << endl;
  cout << "N(SIGNAL) = " << N_SIG << endl;
  cout << "N(ACCEPTANCE) = " << N_ACC << endl;

  cout << "N(FORWARD \ SIGNAL) = " << N_FOR_N_SIG << endl;
  cout << "N(FORWARD \ SIGNAL \ ACCEPTANCE) = " << N_FOR_ONLY << endl;
  cout << "N(SIGNAL \ ACCEPTANCE) = " << N_SIG_N_ACC << endl;
  cout << "N(ACCEPTANCE \ SIGNAL) = " << N_ACC_N_SIG << endl;  
  cout << "N(SIGNAL & ACCEPTANCE) = " << N_SIG_A_ACC << endl;

  cout << endl << " ------------------- " << endl << endl;
  
  cout << "P(BACKWARD) = "; probinfo(N_BACK,N);
  cout << "P(FORWARD) = "; probinfo(N_FOR,N);
  cout << "P(SIGNAL) = "; probinfo(N_SIG,N);
  cout << "P(ACCEPTANCE) = "; probinfo(N_ACC,N);

  cout << "P(FORWARD \ SIGNAL) = "; probinfo(N_FOR_N_SIG,N);
  cout << "P(FORWAFD \ SIGNAL \ ACCEPTANCE) = "; probinfo(N_FOR_ONLY,N);
  cout << "P(SIGNAL \ ACCEPTANCE) = "; probinfo(N_SIG_N_ACC,N);
  cout << "P(ACCEPTANCE \ SIGNAL) = "; probinfo(N_ACC_N_SIG,N);
  cout << "P(SIGNAL & ACCEPTANCE) = "; probinfo(N_SIG_A_ACC,N);
  
  cout << "P(SIGNAL|FORWARD) = "; probinfo(N_SIG,N_FOR);
  cout << "P(!SIGNAL|FORWARD) = "; probinfo(N_FOR_N_SIG,N_FOR);
  cout << "P(ACCEPTANCE|FORWARD) = "; probinfo(N_ACC,N_FOR);
  cout << "P(ACCEPTANCE|SIGNAL) = "; probinfo(N_SIG_A_ACC,N_SIG);
  cout << "P(ACCEPTANCE|FORWARD \ SIGNAL) = "; probinfo(N_ACC_N_SIG,N_FOR_ONLY);
  cout << "P(SIGNAL|ACCEPTANCE) = "; probinfo(N_SIG_A_ACC,N_ACC);
  cout << "P(FORWARD \ SIGNAL|ACCEPTANCE) = "; probinfo(N_ACC_N_SIG,N_ACC);
  
  cout << endl << " ------------------- " << endl << endl;

  long N_SIG_RECO = count(mctree,SIGNAL_BC,RECO);
  long N_ACC_RECO = count(mctree,ACCEPTANCE,RECO);
  long N_ACC_N_SIG_RECO = count(mctree,ACCEPTANCE,NOT_SIGNAL_BC,RECO);
  long N_SIG_N_ACC_RECO = count(mctree,NOT_ACCEPTANCE,SIGNAL_BC,RECO);
  long N_SIG_A_ACC_RECO = count(mctree,SIGNAL_BC,ACCEPTANCE,RECO);

  cout << "P(RECO|SIGNAL) = "; probinfo(N_SIG_RECO,N_SIG);
  cout << "P(RECO|ACCEPTANCE) = "; probinfo(N_ACC_RECO,N_ACC);
  cout << "P(RECO|SIGNAL \ ACCEPTANCE) = "; probinfo(N_SIG_N_ACC_RECO,N_SIG_N_ACC);
  cout << "P(RECO|ACCEPTANCE \ SIGNAL) = "; probinfo(N_ACC_N_SIG_RECO,N_ACC_N_SIG);
  cout << "P(RECO|SIGNAL & ACCEPTANCE) = "; probinfo(N_SIG_A_ACC_RECO,N_SIG_A_ACC);

  cout << endl << " ------------------- " << endl << endl;

  long N_SIG_RECO_STRIPPED = count(mctree,SIGNAL_BC,RECO,STRIPPED);
  long N_ACC_RECO_STRIPPED = count(mctree,ACCEPTANCE,RECO,STRIPPED);
  long N_ACC_N_SIG_RECO_STRIPPED = count(mctree,ACCEPTANCE,NOT_SIGNAL_BC,RECO,STRIPPED);
  long N_SIG_N_ACC_RECO_STRIPPED = count(mctree,NOT_ACCEPTANCE,SIGNAL_BC,RECO,STRIPPED);
  long N_SIG_A_ACC_RECO_STRIPPED = count(mctree,SIGNAL_BC,ACCEPTANCE,RECO,STRIPPED);

  cout << "P(STRIPPED|SIGNAL & RECO) = "; probinfo(N_SIG_RECO_STRIPPED,N_SIG_RECO);
  cout << "P(STRIPPED|ACCEPTANCE & RECO) = "; probinfo(N_ACC_RECO_STRIPPED,N_ACC_RECO);
  cout << "P(STRIPPED|SIGNAL \ ACCEPTANCE & RECO) = "; probinfo(N_SIG_N_ACC_RECO_STRIPPED,N_SIG_N_ACC_RECO);
  cout << "P(STRIPPED|ACCEPTANCE \ SIGNAL & RECO) = "; probinfo(N_ACC_N_SIG_RECO_STRIPPED,N_ACC_N_SIG_RECO);
  cout << "P(STRIPPED|SIGNAL & ACCEPTANCE & RECO) = "; probinfo(N_SIG_A_ACC_RECO_STRIPPED,N_SIG_A_ACC_RECO);

  cout << endl << " ------------------- " << endl << endl;

  cout << "N(STRIPPED & SIGNAL & RECO) = " << N_SIG_RECO_STRIPPED << endl;
  cout << "N(STRIPPED & ACCEPTANCE & RECO) = " << N_ACC_RECO_STRIPPED << endl;
  cout << "N(STRIPPED & SIGNAL \ ACCEPTANCE & RECO) = " << N_SIG_N_ACC_RECO_STRIPPED << endl;
  cout << "N(STRIPPED & ACCEPTANCE \ SIGNAL & RECO) = " << N_ACC_N_SIG_RECO_STRIPPED << endl;
  cout << "N(STRIPPED & SIGNAL & ACCEPTANCE & RECO) = " << N_SIG_A_ACC_RECO_STRIPPED << endl;

  cout << endl << " ------------------- " << endl << endl;

}
