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


void toy_acceptance(TTree* tree)
{
  TCanvas* c_eta = new TCanvas("eta","eta",0,0,1000,1000);
  c_eta->Divide(2,4);
  TH1F* etahist = new TH1F("etahist","etahist",100,-10,10);
  TH1F* etahist_sig = new TH1F("etahist_sig","etahist_sig",100,-10,10);
  TH1F* etahist_nsig = new TH1F("etahist_nsig","etahist_nsig",100,-10,10);
  TH1F* etahist_acc = new TH1F("etahist_acc","etahist_acc",100,-10,10);
  TH1F* etahist_nrough = new TH1F("etahist_nrough","etahist_nrough",100,-10,10);
  
  TCanvas* c_pt = new TCanvas("pt","pt",0,0,1000,1000);
  c_pt->Divide(2,4);
  TH1F* pthist = new TH1F("pthist","pthist",100,0,150000);
  TH1F* pthist_sig = new TH1F("pthist_sig","pthist_sig",100,0,150000);
  TH1F* pthist_nsig = new TH1F("pthist_nsig","pthist_nsig",100,0,150000);
  TH1F* pthist_acc = new TH1F("pthist_acc","pthist_acc",100,0,150000);
  TH1F* pthist_nrough = new TH1F("pthist_nrough","pthist_nrough",100,0,150000);
  
  TCanvas* c_bmtheta = new TCanvas("bmtheta","bmtheta",0,0,1000,1000);
  c_bmtheta->Divide(2,4);
  TH1F* bmthetahist = new TH1F("bmthetahist","bmthetahist",100,0,600);
  TH1F* bmthetahist_sig = new TH1F("bmthetahist_sig","bmthetahist_sig",100,0,600);
  TH1F* bmthetahist_nsig = new TH1F("bmthetahist_nsig","bmthetahist_nsig",100,0,600);
  TH1F* bmthetahist_acc = new TH1F("bmthetahist_acc","bmthetahist_acc",100,0,600);
  TH1F* bmthetahist_nrough = new TH1F("bmthetahist_nrough","bmthetahist_nrough",100,0,600);
  
  TCanvas* c_muptheta = new TCanvas("muptheta","muptheta",0,0,1000,1000);
  c_muptheta->Divide(2,4);
  TH1F* mupthetahist = new TH1F("mupthetahist","mupthetahist",100,0,600);
  TH1F* mupthetahist_sig = new TH1F("mupthetahist_sig","mupthetahist_sig",100,0,600);
  TH1F* mupthetahist_nsig = new TH1F("mupthetahist_nsig","mupthetahist_nsig",100,0,600);
  TH1F* mupthetahist_acc = new TH1F("mupthetahist_acc","mupthetahist_acc",100,0,600);
  TH1F* mupthetahist_nrough = new TH1F("mupthetahist_nrough","mupthetahist_nrough",100,0,600);
  
  TCanvas* c_mumtheta = new TCanvas("mumtheta","mumtheta",0,0,1000,1000);
  c_mumtheta->Divide(2,4);
  TH1F* mumthetahist = new TH1F("mumthetahist","mumthetahist",100,0,600);
  TH1F* mumthetahist_sig = new TH1F("mumthetahist_sig","mumthetahist_sig",100,0,600);
  TH1F* mumthetahist_nsig = new TH1F("mumthetahist_nsig","mumthetahist_nsig",100,0,600);
  TH1F* mumthetahist_acc = new TH1F("mumthetahist_acc","mumthetahist_acc",100,0,600);
  TH1F* mumthetahist_nrough = new TH1F("mumthetahist_nrough","mumthetahist_nrough",100,0,600);
  
  string BCETA = "Bc_MCETA";
  string BCPT = "Bc_MCPT";
  string BACHMUTHETA = "BachMu_MCTHETA";
  string MUPTHETA = "MuP_MCTHETA";
  string MUMTHETA = "MuM_MCTHETA";
  

  // DaughtersInLHCb acceptance cut (Daughters)
  string ACCEPTANCE = "BachMu_ACC && MuP_ACC && MuM_ACC";
  string NOT_ACCEPTANCE = "!(" + ACCEPTANCE + ")";

  string SIGNAL_BC = "Bc_PCS";
  string NOT_SIGNAL_BC = "!(" + SIGNAL_BC + ")";

  tree->Project("etahist",BCETA.c_str(),"");
  c_eta->cd(1);
  etahist->Draw();
  tree->Project("etahist_sig",BCETA.c_str(),SIGNAL_BC.c_str());
  c_eta->cd(3);
  etahist_sig->Draw();
  tree->Project("etahist_nsig",BCETA.c_str(),NOT_SIGNAL_BC.c_str());
  c_eta->cd(4);
  etahist_nsig->Draw();
  tree->Project("etahist_acc",BCETA.c_str(),ACCEPTANCE.c_str());
  c_eta->cd(5);
  etahist_acc->Draw();
  tree->Project("etahist_nrough",BCETA.c_str(),NOT_ACCEPTANCE.c_str());
  c_eta->cd(6);
  etahist_nrough->Draw();

  c_eta->Print("c_eta.png");
  delete c_eta;
  delete etahist;
  delete etahist_sig;
  delete etahist_nsig;
  delete etahist_acc;
  delete etahist_nrough;

  tree->Project("pthist",BCPT.c_str(),"");
  c_pt->cd(1);
  pthist->Draw();
  gPad->SetLogy();
  tree->Project("pthist_sig",BCPT.c_str(),SIGNAL_BC.c_str());
  c_pt->cd(3);
  pthist_sig->Draw();
  gPad->SetLogy();
  tree->Project("pthist_nsig",BCPT.c_str(),NOT_SIGNAL_BC.c_str());
  c_pt->cd(4);
  pthist_nsig->Draw();
  gPad->SetLogy();
  tree->Project("pthist_acc",BCPT.c_str(),ACCEPTANCE.c_str());
  c_pt->cd(5);
  pthist_acc->Draw();
  gPad->SetLogy();
  tree->Project("pthist_nrough",BCPT.c_str(),NOT_ACCEPTANCE.c_str());
  c_pt->cd(6);
  pthist_nrough->Draw();
  gPad->SetLogy();

  c_pt->Print("c_pt.png");
  gPad->SetLogy(false);
  delete c_pt;
  delete pthist;
  delete pthist_sig;
  delete pthist_nsig;
  delete pthist_acc;
  delete pthist_nrough;

  tree->Project("bmthetahist",BACHMUTHETA.c_str(),"");
  c_bmtheta->cd(1);
  bmthetahist->Draw();
  tree->Project("bmthetahist_sig",BACHMUTHETA.c_str(),SIGNAL_BC.c_str());
  c_bmtheta->cd(3);
  bmthetahist_sig->Draw();
  tree->Project("bmthetahist_nsig",BACHMUTHETA.c_str(),NOT_SIGNAL_BC.c_str());
  c_bmtheta->cd(4);
  bmthetahist_nsig->Draw();
  tree->Project("bmthetahist_acc",BACHMUTHETA.c_str(),ACCEPTANCE.c_str());
  c_bmtheta->cd(5);
  bmthetahist_acc->Draw();
  tree->Project("bmthetahist_nrough",BACHMUTHETA.c_str(),NOT_ACCEPTANCE.c_str());
  c_bmtheta->cd(6);
  bmthetahist_nrough->Draw();

  c_bmtheta->Print("c_bmtheta.png");
  delete c_bmtheta;
  delete bmthetahist;
  delete bmthetahist_sig;
  delete bmthetahist_nsig;
  delete bmthetahist_acc;
  delete bmthetahist_nrough;

  tree->Project("mupthetahist",MUPTHETA.c_str(),"");
  c_muptheta->cd(1);
  mupthetahist->Draw();
  tree->Project("mupthetahist_sig",MUPTHETA.c_str(),SIGNAL_BC.c_str());
  c_muptheta->cd(3);
  mupthetahist_sig->Draw();
  tree->Project("mupthetahist_nsig",MUPTHETA.c_str(),NOT_SIGNAL_BC.c_str());
  c_muptheta->cd(4);
  mupthetahist_nsig->Draw();
  tree->Project("mupthetahist_acc",MUPTHETA.c_str(),ACCEPTANCE.c_str());
  c_muptheta->cd(5);
  mupthetahist_acc->Draw();
  tree->Project("mupthetahist_nrough",MUPTHETA.c_str(),NOT_ACCEPTANCE.c_str());
  c_muptheta->cd(6);
  mupthetahist_nrough->Draw();
  
  c_muptheta->Print("c_muptheta.png");
  delete c_muptheta;
  delete mupthetahist;
  delete mupthetahist_sig;
  delete mupthetahist_nsig;
  delete mupthetahist_acc;
  delete mupthetahist_nrough;

  tree->Project("mumthetahist",MUMTHETA.c_str(),"");
  c_mumtheta->cd(1);
  mumthetahist->Draw();
  tree->Project("mumthetahist_sig",MUMTHETA.c_str(),SIGNAL_BC.c_str());
  c_mumtheta->cd(3);
  mumthetahist_sig->Draw();
  tree->Project("mumthetahist_nsig",MUMTHETA.c_str(),NOT_SIGNAL_BC.c_str());
  c_mumtheta->cd(4);
  mumthetahist_nsig->Draw();
  tree->Project("mumthetahist_acc",MUMTHETA.c_str(),ACCEPTANCE.c_str());
  c_mumtheta->cd(5);
  mumthetahist_acc->Draw();
  tree->Project("mumthetahist_nrough",MUMTHETA.c_str(),NOT_ACCEPTANCE.c_str());
  c_mumtheta->cd(6);
  mumthetahist_nrough->Draw();
  
  c_mumtheta->Print("c_mumtheta.png");
  delete c_mumtheta;
  delete mumthetahist;
  delete mumthetahist_sig;
  delete mumthetahist_nsig;
  delete mumthetahist_acc;
  delete mumthetahist_nrough;

  //  long N = count(tree);
  long N = count(tree);
  long N_SIG = count(tree,SIGNAL_BC);
  long N_ACC = count(tree,ACCEPTANCE);

  long N_N_SIG_ACC = count(tree,NOT_SIGNAL_BC,NOT_ACCEPTANCE);
  long N_SIG_N_ACC = count(tree,SIGNAL_BC,NOT_ACCEPTANCE);
  long N_ACC_N_SIG = count(tree,ACCEPTANCE,NOT_SIGNAL_BC);
  long N_SIG_A_ACC = count(tree,SIGNAL_BC,ACCEPTANCE);

  cout << "N() = " << N << endl;
  cout << "N(SIGNAL) = " << N_SIG << endl;
  cout << "N(ACCEPTANCE) = " << N_ACC << endl;
  
  cout << "N(\ SIGNAL \ ACCEPTANCE) = " << N_N_SIG_ACC << endl;
  cout << "N(SIGNAL \ ACCEPTANCE) = " << N_SIG_N_ACC << endl;
  cout << "N(ACCEPTANCE \ SIGNAL) = " << N_ACC_N_SIG << endl;  
  cout << "N(SIGNAL & ACCEPTANCE) = " << N_SIG_A_ACC << endl;

  cout << endl << " ------------------- " << endl << endl;
  
  cout << "P(SIGNAL) = "; probinfo(N_SIG,N);
  cout << "P(!SIGNAL) = "; probinfo(N-N_SIG,N);
  cout << "P(ACCEPTANCE) = "; probinfo(N_ACC,N);
  cout << "P(!ACCEPTANCE) = "; probinfo(N-N_ACC,N);

  cout << "P(\ SIGNAL \ ACCEPTANCE) = "; probinfo(N_N_SIG_ACC,N);
  cout << "P(SIGNAL \ ACCEPTANCE) = "; probinfo(N_SIG_N_ACC,N);
  cout << "P(ACCEPTANCE \ SIGNAL) = "; probinfo(N_ACC_N_SIG,N);
  cout << "P(SIGNAL & ACCEPTANCE) = "; probinfo(N_SIG_A_ACC,N);
  
  cout << "P(ACCEPTANCE|SIGNAL) = "; probinfo(N_SIG_A_ACC,N_SIG);
  cout << "P(ACCEPTANCE|!SIGNAL) = "; probinfo(N_ACC_N_SIG,N-N_SIG);
  cout << "P(SIGNAL|ACCEPTANCE) = "; probinfo(N_SIG_A_ACC,N_ACC);
  cout << "P(!SIGNAL|ACCEPTANCE) = "; probinfo(N_ACC_N_SIG,N_ACC);
  
  cout << endl << " ------------------- " << endl << endl;

}
