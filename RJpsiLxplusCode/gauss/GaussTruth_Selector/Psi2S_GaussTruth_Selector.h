//////////////////////////////////////////////////////////
// This class has been automatically generated on
// Fri Aug 30 19:22:03 2013 by ROOT version 5.34/09
// from TTree MCMuDecayTree/MCMuDecayTree
// found on file: bcharm_gauss_roots/Bc2psi2SFDMu_GaussTruth.root
//////////////////////////////////////////////////////////

#ifndef Psi2S_GaussTruth_Selector_h
#define Psi2S_GaussTruth_Selector_h

#include <TROOT.h>
#include <TChain.h>
#include <TFile.h>
#include <TSelector.h>

// Header file for the classes stored in the TTree if any.

// Fixed size dimensions of array or collections stored in the TTree if any.

class Psi2S_GaussTruth_Selector : public TSelector {
public :
  TTree          *fChain;   //!pointer to the analyzed TTree or TChain
  TTree          *OutChain;
  TFile          *OutFile;
  
  Double_t Y_MCMM;
  Double_t Y_MCE;
  Double_t Y_MCP;
  Double_t Y_MCPT;
  Double_t Y_MCPX;
  Double_t Y_MCPY;
  Double_t Y_MCPZ;
  Double_t Y_MCETA;
  Double_t Y_MCTHETA;
  Double_t Y_MCPHI;

  Double_t Momentum;
  Double_t MissMass2;
  Double_t BachMuEnergy;
  Double_t Q2;
  Double_t Lifetime;


  // Declaration of leaf types
  Double_t        Bc_ACC;
  Double_t        Bc_MCCTAU;
  Double_t        Bc_MCE;
  Double_t        Bc_MCETA;
  Double_t        Bc_MCP;
  Double_t        Bc_MCPHI;
  Double_t        Bc_MCPT;
  Double_t        Bc_MCPX;
  Double_t        Bc_MCPY;
  Double_t        Bc_MCPZ;
  Double_t        Bc_MCTHETA;
  Double_t        Bc_PCS;
  Double_t        NuMu_ACC;
  Double_t        NuMu_MCCTAU;
  Double_t        NuMu_MCE;
  Double_t        NuMu_MCETA;
  Double_t        NuMu_MCP;
  Double_t        NuMu_MCPHI;
  Double_t        NuMu_MCPT;
  Double_t        NuMu_MCPX;
  Double_t        NuMu_MCPY;
  Double_t        NuMu_MCPZ;
  Double_t        NuMu_MCTHETA;
  Double_t        NuMu_PCS;
  Double_t        BachMu_ACC;
  Double_t        BachMu_MCCTAU;
  Double_t        BachMu_MCE;
  Double_t        BachMu_MCETA;
  Double_t        BachMu_MCP;
  Double_t        BachMu_MCPHI;
  Double_t        BachMu_MCPT;
  Double_t        BachMu_MCPX;
  Double_t        BachMu_MCPY;
  Double_t        BachMu_MCPZ;
  Double_t        BachMu_MCTHETA;
  Double_t        BachMu_PCS;
  Double_t        psi2S_ACC;
  Double_t        psi2S_MCCTAU;
  Double_t        psi2S_MCE;
  Double_t        psi2S_MCETA;
  Double_t        psi2S_MCP;
  Double_t        psi2S_MCPHI;
  Double_t        psi2S_MCPT;
  Double_t        psi2S_MCPX;
  Double_t        psi2S_MCPY;
  Double_t        psi2S_MCPZ;
  Double_t        psi2S_MCTHETA;
  Double_t        psi2S_PCS;
//   Double_t        Jpsi_ACC;
//   Double_t        Jpsi_MCCTAU;
//   Double_t        Jpsi_MCE;
//   Double_t        Jpsi_MCETA;
//   Double_t        Jpsi_MCP;
//   Double_t        Jpsi_MCPHI;
//   Double_t        Jpsi_MCPT;
//   Double_t        Jpsi_MCPX;
//   Double_t        Jpsi_MCPY;
//   Double_t        Jpsi_MCPZ;
//   Double_t        Jpsi_MCTHETA;
//   Double_t        Jpsi_PCS;
  Double_t        MuM_ACC;
  Double_t        MuM_MCCTAU;
  Double_t        MuM_MCE;
  Double_t        MuM_MCETA;
  Double_t        MuM_MCP;
  Double_t        MuM_MCPHI;
  Double_t        MuM_MCPT;
  Double_t        MuM_MCPX;
  Double_t        MuM_MCPY;
  Double_t        MuM_MCPZ;
  Double_t        MuM_MCTHETA;
  Double_t        MuM_PCS;
  Double_t        MuP_ACC;
  Double_t        MuP_MCCTAU;
  Double_t        MuP_MCE;
  Double_t        MuP_MCETA;
  Double_t        MuP_MCP;
  Double_t        MuP_MCPHI;
  Double_t        MuP_MCPT;
  Double_t        MuP_MCPX;
  Double_t        MuP_MCPY;
  Double_t        MuP_MCPZ;
  Double_t        MuP_MCTHETA;
  Double_t        MuP_PCS;
  UInt_t          nCandidate;
  ULong64_t       totCandidates;
  ULong64_t       EventInSequence;

  // List of branches
  TBranch        *b_Bc_ACC;   //!
  TBranch        *b_Bc_MCCTAU;   //!
  TBranch        *b_Bc_MCE;   //!
  TBranch        *b_Bc_MCETA;   //!
  TBranch        *b_Bc_MCP;   //!
  TBranch        *b_Bc_MCPHI;   //!
  TBranch        *b_Bc_MCPT;   //!
  TBranch        *b_Bc_MCPX;   //!
  TBranch        *b_Bc_MCPY;   //!
  TBranch        *b_Bc_MCPZ;   //!
  TBranch        *b_Bc_MCTHETA;   //!
  TBranch        *b_Bc_PCS;   //!
  TBranch        *b_NuMu_ACC;   //!
  TBranch        *b_NuMu_MCCTAU;   //!
  TBranch        *b_NuMu_MCE;   //!
  TBranch        *b_NuMu_MCETA;   //!
  TBranch        *b_NuMu_MCP;   //!
  TBranch        *b_NuMu_MCPHI;   //!
  TBranch        *b_NuMu_MCPT;   //!
  TBranch        *b_NuMu_MCPX;   //!
  TBranch        *b_NuMu_MCPY;   //!
  TBranch        *b_NuMu_MCPZ;   //!
  TBranch        *b_NuMu_MCTHETA;   //!
  TBranch        *b_NuMu_PCS;   //!
  TBranch        *b_BachMu_ACC;   //!
  TBranch        *b_BachMu_MCCTAU;   //!
  TBranch        *b_BachMu_MCE;   //!
  TBranch        *b_BachMu_MCETA;   //!
  TBranch        *b_BachMu_MCP;   //!
  TBranch        *b_BachMu_MCPHI;   //!
  TBranch        *b_BachMu_MCPT;   //!
  TBranch        *b_BachMu_MCPX;   //!
  TBranch        *b_BachMu_MCPY;   //!
  TBranch        *b_BachMu_MCPZ;   //!
  TBranch        *b_BachMu_MCTHETA;   //!
  TBranch        *b_BachMu_PCS;   //!
   TBranch        *b_psi2S_ACC;   //!
   TBranch        *b_psi2S_MCCTAU;   //!
   TBranch        *b_psi2S_MCE;   //!
   TBranch        *b_psi2S_MCETA;   //!
   TBranch        *b_psi2S_MCP;   //!
   TBranch        *b_psi2S_MCPHI;   //!
   TBranch        *b_psi2S_MCPT;   //!
   TBranch        *b_psi2S_MCPX;   //!
   TBranch        *b_psi2S_MCPY;   //!
   TBranch        *b_psi2S_MCPZ;   //!
   TBranch        *b_psi2S_MCTHETA;   //!
   TBranch        *b_psi2S_PCS;   //!
//   TBranch        *b_Jpsi_ACC;   //!
//   TBranch        *b_Jpsi_MCCTAU;   //!
//   TBranch        *b_Jpsi_MCE;   //!
//   TBranch        *b_Jpsi_MCETA;   //!
//   TBranch        *b_Jpsi_MCP;   //!
//   TBranch        *b_Jpsi_MCPHI;   //!
//   TBranch        *b_Jpsi_MCPT;   //!
//   TBranch        *b_Jpsi_MCPX;   //!
//   TBranch        *b_Jpsi_MCPY;   //!
//   TBranch        *b_Jpsi_MCPZ;   //!
//   TBranch        *b_Jpsi_MCTHETA;   //!
//   TBranch        *b_Jpsi_PCS;   //!
  TBranch        *b_MuM_ACC;   //!
  TBranch        *b_MuM_MCCTAU;   //!
  TBranch        *b_MuM_MCE;   //!
  TBranch        *b_MuM_MCETA;   //!
  TBranch        *b_MuM_MCP;   //!
  TBranch        *b_MuM_MCPHI;   //!
  TBranch        *b_MuM_MCPT;   //!
  TBranch        *b_MuM_MCPX;   //!
  TBranch        *b_MuM_MCPY;   //!
  TBranch        *b_MuM_MCPZ;   //!
  TBranch        *b_MuM_MCTHETA;   //!
  TBranch        *b_MuM_PCS;   //!
  TBranch        *b_MuP_ACC;   //!
  TBranch        *b_MuP_MCCTAU;   //!
  TBranch        *b_MuP_MCE;   //!
  TBranch        *b_MuP_MCETA;   //!
  TBranch        *b_MuP_MCP;   //!
  TBranch        *b_MuP_MCPHI;   //!
  TBranch        *b_MuP_MCPT;   //!
  TBranch        *b_MuP_MCPX;   //!
  TBranch        *b_MuP_MCPY;   //!
  TBranch        *b_MuP_MCPZ;   //!
  TBranch        *b_MuP_MCTHETA;   //!
  TBranch        *b_MuP_PCS;   //!
  TBranch        *b_nCandidate;   //!
  TBranch        *b_totCandidates;   //!
  TBranch        *b_EventInSequence;   //!

  Psi2S_GaussTruth_Selector(TTree * /*tree*/ =0) : fChain(0) { }
  virtual ~Psi2S_GaussTruth_Selector() { }
  virtual Int_t   Version() const { return 2; }
  virtual void    Begin(TTree *tree);
  virtual void    SlaveBegin(TTree *tree);
  virtual void    Init(TTree *tree);
  virtual Bool_t  Notify();
  virtual Bool_t  Process(Long64_t entry);
  virtual Int_t   GetEntry(Long64_t entry, Int_t getall = 0) { return fChain ? fChain->GetTree()->GetEntry(entry, getall) : 0; }
  virtual void    SetOption(const char *option) { fOption = option; }
  virtual void    SetObject(TObject *obj) { fObject = obj; }
  virtual void    SetInputList(TList *input) { fInput = input; }
  virtual TList  *GetOutputList() const { return fOutput; }
  virtual void    SlaveTerminate();
  virtual void    Terminate();

  ClassDef(Psi2S_GaussTruth_Selector,0);
};

#endif

#ifdef Psi2S_GaussTruth_Selector_cxx
void Psi2S_GaussTruth_Selector::Init(TTree *tree)
{
  // The Init() function is called when the selector needs to initialize
  // a new tree or chain. Typically here the branch addresses and branch
  // pointers of the tree will be set.
  // It is normally not necessary to make changes to the generated
  // code, but the routine can be extended by the user if needed.
  // Init() will be called many times when running on PROOF
  // (once per file to be processed).

  // Set branch addresses and branch pointers
  if (!tree) return;
  fChain = tree;
   
  fChain->SetMakeClass(1);

  fChain->SetBranchAddress("Bc_ACC", &Bc_ACC, &b_Bc_ACC);
  fChain->SetBranchAddress("Bc_MCCTAU", &Bc_MCCTAU, &b_Bc_MCCTAU);
  fChain->SetBranchAddress("Bc_MCE", &Bc_MCE, &b_Bc_MCE);
  fChain->SetBranchAddress("Bc_MCETA", &Bc_MCETA, &b_Bc_MCETA);
  fChain->SetBranchAddress("Bc_MCP", &Bc_MCP, &b_Bc_MCP);
  fChain->SetBranchAddress("Bc_MCPHI", &Bc_MCPHI, &b_Bc_MCPHI);
  fChain->SetBranchAddress("Bc_MCPT", &Bc_MCPT, &b_Bc_MCPT);
  fChain->SetBranchAddress("Bc_MCPX", &Bc_MCPX, &b_Bc_MCPX);
  fChain->SetBranchAddress("Bc_MCPY", &Bc_MCPY, &b_Bc_MCPY);
  fChain->SetBranchAddress("Bc_MCPZ", &Bc_MCPZ, &b_Bc_MCPZ);
  fChain->SetBranchAddress("Bc_MCTHETA", &Bc_MCTHETA, &b_Bc_MCTHETA);
  fChain->SetBranchAddress("Bc_PCS", &Bc_PCS, &b_Bc_PCS);
  fChain->SetBranchAddress("NuMu_ACC", &NuMu_ACC, &b_NuMu_ACC);
  fChain->SetBranchAddress("NuMu_MCCTAU", &NuMu_MCCTAU, &b_NuMu_MCCTAU);
  fChain->SetBranchAddress("NuMu_MCE", &NuMu_MCE, &b_NuMu_MCE);
  fChain->SetBranchAddress("NuMu_MCETA", &NuMu_MCETA, &b_NuMu_MCETA);
  fChain->SetBranchAddress("NuMu_MCP", &NuMu_MCP, &b_NuMu_MCP);
  fChain->SetBranchAddress("NuMu_MCPHI", &NuMu_MCPHI, &b_NuMu_MCPHI);
  fChain->SetBranchAddress("NuMu_MCPT", &NuMu_MCPT, &b_NuMu_MCPT);
  fChain->SetBranchAddress("NuMu_MCPX", &NuMu_MCPX, &b_NuMu_MCPX);
  fChain->SetBranchAddress("NuMu_MCPY", &NuMu_MCPY, &b_NuMu_MCPY);
  fChain->SetBranchAddress("NuMu_MCPZ", &NuMu_MCPZ, &b_NuMu_MCPZ);
  fChain->SetBranchAddress("NuMu_MCTHETA", &NuMu_MCTHETA, &b_NuMu_MCTHETA);
  fChain->SetBranchAddress("NuMu_PCS", &NuMu_PCS, &b_NuMu_PCS);
  fChain->SetBranchAddress("BachMu_ACC", &BachMu_ACC, &b_BachMu_ACC);
  fChain->SetBranchAddress("BachMu_MCCTAU", &BachMu_MCCTAU, &b_BachMu_MCCTAU);
  fChain->SetBranchAddress("BachMu_MCE", &BachMu_MCE, &b_BachMu_MCE);
  fChain->SetBranchAddress("BachMu_MCETA", &BachMu_MCETA, &b_BachMu_MCETA);
  fChain->SetBranchAddress("BachMu_MCP", &BachMu_MCP, &b_BachMu_MCP);
  fChain->SetBranchAddress("BachMu_MCPHI", &BachMu_MCPHI, &b_BachMu_MCPHI);
  fChain->SetBranchAddress("BachMu_MCPT", &BachMu_MCPT, &b_BachMu_MCPT);
  fChain->SetBranchAddress("BachMu_MCPX", &BachMu_MCPX, &b_BachMu_MCPX);
  fChain->SetBranchAddress("BachMu_MCPY", &BachMu_MCPY, &b_BachMu_MCPY);
  fChain->SetBranchAddress("BachMu_MCPZ", &BachMu_MCPZ, &b_BachMu_MCPZ);
  fChain->SetBranchAddress("BachMu_MCTHETA", &BachMu_MCTHETA, &b_BachMu_MCTHETA);
  fChain->SetBranchAddress("BachMu_PCS", &BachMu_PCS, &b_BachMu_PCS);
   fChain->SetBranchAddress("psi2S_ACC", &psi2S_ACC, &b_psi2S_ACC);
   fChain->SetBranchAddress("psi2S_MCCTAU", &psi2S_MCCTAU, &b_psi2S_MCCTAU);
   fChain->SetBranchAddress("psi2S_MCE", &psi2S_MCE, &b_psi2S_MCE);
   fChain->SetBranchAddress("psi2S_MCETA", &psi2S_MCETA, &b_psi2S_MCETA);
   fChain->SetBranchAddress("psi2S_MCP", &psi2S_MCP, &b_psi2S_MCP);
   fChain->SetBranchAddress("psi2S_MCPHI", &psi2S_MCPHI, &b_psi2S_MCPHI);
   fChain->SetBranchAddress("psi2S_MCPT", &psi2S_MCPT, &b_psi2S_MCPT);
   fChain->SetBranchAddress("psi2S_MCPX", &psi2S_MCPX, &b_psi2S_MCPX);
   fChain->SetBranchAddress("psi2S_MCPY", &psi2S_MCPY, &b_psi2S_MCPY);
   fChain->SetBranchAddress("psi2S_MCPZ", &psi2S_MCPZ, &b_psi2S_MCPZ);
   fChain->SetBranchAddress("psi2S_MCTHETA", &psi2S_MCTHETA, &b_psi2S_MCTHETA);
   fChain->SetBranchAddress("psi2S_PCS", &psi2S_PCS, &b_psi2S_PCS);
//   fChain->SetBranchAddress("Jpsi_ACC", &Jpsi_ACC, &b_Jpsi_ACC);
//   fChain->SetBranchAddress("Jpsi_MCCTAU", &Jpsi_MCCTAU, &b_Jpsi_MCCTAU);
//   fChain->SetBranchAddress("Jpsi_MCE", &Jpsi_MCE, &b_Jpsi_MCE);
//   fChain->SetBranchAddress("Jpsi_MCETA", &Jpsi_MCETA, &b_Jpsi_MCETA);
//   fChain->SetBranchAddress("Jpsi_MCP", &Jpsi_MCP, &b_Jpsi_MCP);
//   fChain->SetBranchAddress("Jpsi_MCPHI", &Jpsi_MCPHI, &b_Jpsi_MCPHI);
//   fChain->SetBranchAddress("Jpsi_MCPT", &Jpsi_MCPT, &b_Jpsi_MCPT);
//   fChain->SetBranchAddress("Jpsi_MCPX", &Jpsi_MCPX, &b_Jpsi_MCPX);
//   fChain->SetBranchAddress("Jpsi_MCPY", &Jpsi_MCPY, &b_Jpsi_MCPY);
//   fChain->SetBranchAddress("Jpsi_MCPZ", &Jpsi_MCPZ, &b_Jpsi_MCPZ);
//   fChain->SetBranchAddress("Jpsi_MCTHETA", &Jpsi_MCTHETA, &b_Jpsi_MCTHETA);
//   fChain->SetBranchAddress("Jpsi_PCS", &Jpsi_PCS, &b_Jpsi_PCS);
  fChain->SetBranchAddress("MuM_ACC", &MuM_ACC, &b_MuM_ACC);
  fChain->SetBranchAddress("MuM_MCCTAU", &MuM_MCCTAU, &b_MuM_MCCTAU);
  fChain->SetBranchAddress("MuM_MCE", &MuM_MCE, &b_MuM_MCE);
  fChain->SetBranchAddress("MuM_MCETA", &MuM_MCETA, &b_MuM_MCETA);
  fChain->SetBranchAddress("MuM_MCP", &MuM_MCP, &b_MuM_MCP);
  fChain->SetBranchAddress("MuM_MCPHI", &MuM_MCPHI, &b_MuM_MCPHI);
  fChain->SetBranchAddress("MuM_MCPT", &MuM_MCPT, &b_MuM_MCPT);
  fChain->SetBranchAddress("MuM_MCPX", &MuM_MCPX, &b_MuM_MCPX);
  fChain->SetBranchAddress("MuM_MCPY", &MuM_MCPY, &b_MuM_MCPY);
  fChain->SetBranchAddress("MuM_MCPZ", &MuM_MCPZ, &b_MuM_MCPZ);
  fChain->SetBranchAddress("MuM_MCTHETA", &MuM_MCTHETA, &b_MuM_MCTHETA);
  fChain->SetBranchAddress("MuM_PCS", &MuM_PCS, &b_MuM_PCS);
  fChain->SetBranchAddress("MuP_ACC", &MuP_ACC, &b_MuP_ACC);
  fChain->SetBranchAddress("MuP_MCCTAU", &MuP_MCCTAU, &b_MuP_MCCTAU);
  fChain->SetBranchAddress("MuP_MCE", &MuP_MCE, &b_MuP_MCE);
  fChain->SetBranchAddress("MuP_MCETA", &MuP_MCETA, &b_MuP_MCETA);
  fChain->SetBranchAddress("MuP_MCP", &MuP_MCP, &b_MuP_MCP);
  fChain->SetBranchAddress("MuP_MCPHI", &MuP_MCPHI, &b_MuP_MCPHI);
  fChain->SetBranchAddress("MuP_MCPT", &MuP_MCPT, &b_MuP_MCPT);
  fChain->SetBranchAddress("MuP_MCPX", &MuP_MCPX, &b_MuP_MCPX);
  fChain->SetBranchAddress("MuP_MCPY", &MuP_MCPY, &b_MuP_MCPY);
  fChain->SetBranchAddress("MuP_MCPZ", &MuP_MCPZ, &b_MuP_MCPZ);
  fChain->SetBranchAddress("MuP_MCTHETA", &MuP_MCTHETA, &b_MuP_MCTHETA);
  fChain->SetBranchAddress("MuP_PCS", &MuP_PCS, &b_MuP_PCS);
  fChain->SetBranchAddress("nCandidate", &nCandidate, &b_nCandidate);
  fChain->SetBranchAddress("totCandidates", &totCandidates, &b_totCandidates);
  fChain->SetBranchAddress("EventInSequence", &EventInSequence, &b_EventInSequence);
}

Bool_t Psi2S_GaussTruth_Selector::Notify()
{
  // The Notify() function is called when a new file is opened. This
  // can be either for a new TTree in a TChain or when when a new TTree
  // is started when using PROOF. It is normally not necessary to make changes
  // to the generated code, but the routine can be extended by the
  // user if needed. The return value is currently not used.

  return kTRUE;
}

#endif // #ifdef Psi2S_GaussTruth_Selector_cxx
