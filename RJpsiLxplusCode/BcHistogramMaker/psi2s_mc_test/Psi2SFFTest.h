//////////////////////////////////////////////////////////
// This class has been automatically generated on
// Tue Mar 11 17:10:56 2014 by ROOT version 5.34/13
// from TTree MCBc2PsiMuNuDecayTree/MCBc2PsiMuNuDecayTree
// found on file: Bc_Psi2SMu_MC.root
//////////////////////////////////////////////////////////

#ifndef Psi2SFFTest_h
#define Psi2SFFTest_h

#include <TROOT.h>
#include <TChain.h>
#include <TFile.h>
#include <TSelector.h>

// Header file for the classes stored in the TTree if any.

// Fixed size dimensions of array or collections stored in the TTree if any.

class Psi2SFFTest : public TSelector {
public :
  TTree          *fChain;   //!pointer to the analyzed TTree or TChain

  // Histograms
  TH1F* angleHisto;
  TH1F* elepHisto;
  TH1F* q2Histo;

  // Declaration of leaf types
  Double_t        Bc_ACC;
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
  Double_t        Bc_TRUEP_E;
  Double_t        Bc_TRUEP_X;
  Double_t        Bc_TRUEP_Y;
  Double_t        Bc_TRUEP_Z;
  Double_t        Bc_TRUEPT;
  Double_t        Bc_TRUEORIGINVERTEX_X;
  Double_t        Bc_TRUEORIGINVERTEX_Y;
  Double_t        Bc_TRUEORIGINVERTEX_Z;
  Double_t        Bc_TRUEENDVERTEX_X;
  Double_t        Bc_TRUEENDVERTEX_Y;
  Double_t        Bc_TRUEENDVERTEX_Z;
  Bool_t          Bc_TRUEISSTABLE;
  Double_t        Bc_TRUETAU;
  Double_t        psi2S_ACC;
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
  Double_t        psi2S_TRUEP_E;
  Double_t        psi2S_TRUEP_X;
  Double_t        psi2S_TRUEP_Y;
  Double_t        psi2S_TRUEP_Z;
  Double_t        psi2S_TRUEPT;
  Double_t        psi2S_TRUEORIGINVERTEX_X;
  Double_t        psi2S_TRUEORIGINVERTEX_Y;
  Double_t        psi2S_TRUEORIGINVERTEX_Z;
  Double_t        psi2S_TRUEENDVERTEX_X;
  Double_t        psi2S_TRUEENDVERTEX_Y;
  Double_t        psi2S_TRUEENDVERTEX_Z;
  Bool_t          psi2S_TRUEISSTABLE;
  Double_t        psi2S_TRUETAU;
  Double_t        BachMu_ACC;
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
  Double_t        BachMu_TRUEP_E;
  Double_t        BachMu_TRUEP_X;
  Double_t        BachMu_TRUEP_Y;
  Double_t        BachMu_TRUEP_Z;
  Double_t        BachMu_TRUEPT;
  Double_t        BachMu_TRUEORIGINVERTEX_X;
  Double_t        BachMu_TRUEORIGINVERTEX_Y;
  Double_t        BachMu_TRUEORIGINVERTEX_Z;
  Double_t        BachMu_TRUEENDVERTEX_X;
  Double_t        BachMu_TRUEENDVERTEX_Y;
  Double_t        BachMu_TRUEENDVERTEX_Z;
  Bool_t          BachMu_TRUEISSTABLE;
  Double_t        BachMu_TRUETAU;
  Int_t           BachMu_Reconstructible;
  Int_t           BachMu_Reconstructed;
  Int_t           BachMu_ProtoParticles;
  Float_t         BachMu_PP_PX[20];   //[BachMu_ProtoParticles]
  Float_t         BachMu_PP_PY[20];   //[BachMu_ProtoParticles]
  Float_t         BachMu_PP_PZ[20];   //[BachMu_ProtoParticles]
  Float_t         BachMu_PP_Weight[20];   //[BachMu_ProtoParticles]
  Float_t         BachMu_PP_tr_pchi2[20];   //[BachMu_ProtoParticles]
  Float_t         BachMu_PP_DLLe[20];   //[BachMu_ProtoParticles]
  Float_t         BachMu_PP_DLLk[20];   //[BachMu_ProtoParticles]
  Float_t         BachMu_PP_DLLp[20];   //[BachMu_ProtoParticles]
  Float_t         BachMu_PP_DLLmu[20];   //[BachMu_ProtoParticles]
  Double_t        NuMu_ACC;
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
  Double_t        NuMu_TRUEP_E;
  Double_t        NuMu_TRUEP_X;
  Double_t        NuMu_TRUEP_Y;
  Double_t        NuMu_TRUEP_Z;
  Double_t        NuMu_TRUEPT;
  Double_t        NuMu_TRUEORIGINVERTEX_X;
  Double_t        NuMu_TRUEORIGINVERTEX_Y;
  Double_t        NuMu_TRUEORIGINVERTEX_Z;
  Double_t        NuMu_TRUEENDVERTEX_X;
  Double_t        NuMu_TRUEENDVERTEX_Y;
  Double_t        NuMu_TRUEENDVERTEX_Z;
  Bool_t          NuMu_TRUEISSTABLE;
  Double_t        NuMu_TRUETAU;
  UInt_t          nCandidate;
  ULong64_t       totCandidates;
  ULong64_t       EventInSequence;
  UInt_t          runNumber;
  ULong64_t       eventNumber;
  UInt_t          BCID;
  Int_t           BCType;
  UInt_t          OdinTCK;
  UInt_t          L0DUTCK;
  UInt_t          HLTTCK;
  ULong64_t       GpsTime;
  Short_t         Polarity;
  UInt_t          StrippingTriMuonBc2ThreeMuDecision;
  UInt_t          StrippingBc2JpsiMuLineDecision;
  UInt_t          StrippingFullDSTDiMuonJpsi2MuMuDetachedLineDecision;
  UInt_t          StrippingFullDSTDiMuonJpsi2MuMuTOSLineDecision;
  Int_t           L0Global;
  UInt_t          Hlt1Global;
  UInt_t          Hlt2Global;
  Int_t           L0MuonDecision;
  Int_t           L0DiMuonDecision;
  UInt_t          L0nSelections;
  Int_t           Hlt1DiMuonHighMassDecision;
  Int_t           Hlt1DiMuonLowMassDecision;
  UInt_t          Hlt1nSelections;
  Int_t           Hlt2DiMuonJPsiHighPTDecision;
  UInt_t          Hlt2nSelections;
  Int_t           MaxRoutingBits;
  Float_t         RoutingBits[64];   //[MaxRoutingBits]

  // List of branches
  TBranch        *b_Bc_ACC;   //!
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
  TBranch        *b_Bc_TRUEP_E;   //!
  TBranch        *b_Bc_TRUEP_X;   //!
  TBranch        *b_Bc_TRUEP_Y;   //!
  TBranch        *b_Bc_TRUEP_Z;   //!
  TBranch        *b_Bc_TRUEPT;   //!
  TBranch        *b_Bc_TRUEORIGINVERTEX_X;   //!
  TBranch        *b_Bc_TRUEORIGINVERTEX_Y;   //!
  TBranch        *b_Bc_TRUEORIGINVERTEX_Z;   //!
  TBranch        *b_Bc_TRUEENDVERTEX_X;   //!
  TBranch        *b_Bc_TRUEENDVERTEX_Y;   //!
  TBranch        *b_Bc_TRUEENDVERTEX_Z;   //!
  TBranch        *b_Bc_TRUEISSTABLE;   //!
  TBranch        *b_Bc_TRUETAU;   //!
  TBranch        *b_psi2S_ACC;   //!
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
  TBranch        *b_psi2S_TRUEP_E;   //!
  TBranch        *b_psi2S_TRUEP_X;   //!
  TBranch        *b_psi2S_TRUEP_Y;   //!
  TBranch        *b_psi2S_TRUEP_Z;   //!
  TBranch        *b_psi2S_TRUEPT;   //!
  TBranch        *b_psi2S_TRUEORIGINVERTEX_X;   //!
  TBranch        *b_psi2S_TRUEORIGINVERTEX_Y;   //!
  TBranch        *b_psi2S_TRUEORIGINVERTEX_Z;   //!
  TBranch        *b_psi2S_TRUEENDVERTEX_X;   //!
  TBranch        *b_psi2S_TRUEENDVERTEX_Y;   //!
  TBranch        *b_psi2S_TRUEENDVERTEX_Z;   //!
  TBranch        *b_psi2S_TRUEISSTABLE;   //!
  TBranch        *b_psi2S_TRUETAU;   //!
  TBranch        *b_BachMu_ACC;   //!
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
  TBranch        *b_BachMu_TRUEP_E;   //!
  TBranch        *b_BachMu_TRUEP_X;   //!
  TBranch        *b_BachMu_TRUEP_Y;   //!
  TBranch        *b_BachMu_TRUEP_Z;   //!
  TBranch        *b_BachMu_TRUEPT;   //!
  TBranch        *b_BachMu_TRUEORIGINVERTEX_X;   //!
  TBranch        *b_BachMu_TRUEORIGINVERTEX_Y;   //!
  TBranch        *b_BachMu_TRUEORIGINVERTEX_Z;   //!
  TBranch        *b_BachMu_TRUEENDVERTEX_X;   //!
  TBranch        *b_BachMu_TRUEENDVERTEX_Y;   //!
  TBranch        *b_BachMu_TRUEENDVERTEX_Z;   //!
  TBranch        *b_BachMu_TRUEISSTABLE;   //!
  TBranch        *b_BachMu_TRUETAU;   //!
  TBranch        *b_BachMu_Reconstructible;   //!
  TBranch        *b_BachMu_Reconstructed;   //!
  TBranch        *b_BachMu_ProtoParticles;   //!
  TBranch        *b_BachMu_PP_PX;   //!
  TBranch        *b_BachMu_PP_PY;   //!
  TBranch        *b_BachMu_PP_PZ;   //!
  TBranch        *b_BachMu_PP_Weight;   //!
  TBranch        *b_BachMu_PP_tr_pchi2;   //!
  TBranch        *b_BachMu_PP_DLLe;   //!
  TBranch        *b_BachMu_PP_DLLk;   //!
  TBranch        *b_BachMu_PP_DLLp;   //!
  TBranch        *b_BachMu_PP_DLLmu;   //!
  TBranch        *b_NuMu_ACC;   //!
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
  TBranch        *b_NuMu_TRUEP_E;   //!
  TBranch        *b_NuMu_TRUEP_X;   //!
  TBranch        *b_NuMu_TRUEP_Y;   //!
  TBranch        *b_NuMu_TRUEP_Z;   //!
  TBranch        *b_NuMu_TRUEPT;   //!
  TBranch        *b_NuMu_TRUEORIGINVERTEX_X;   //!
  TBranch        *b_NuMu_TRUEORIGINVERTEX_Y;   //!
  TBranch        *b_NuMu_TRUEORIGINVERTEX_Z;   //!
  TBranch        *b_NuMu_TRUEENDVERTEX_X;   //!
  TBranch        *b_NuMu_TRUEENDVERTEX_Y;   //!
  TBranch        *b_NuMu_TRUEENDVERTEX_Z;   //!
  TBranch        *b_NuMu_TRUEISSTABLE;   //!
  TBranch        *b_NuMu_TRUETAU;   //!
  TBranch        *b_nCandidate;   //!
  TBranch        *b_totCandidates;   //!
  TBranch        *b_EventInSequence;   //!
  TBranch        *b_runNumber;   //!
  TBranch        *b_eventNumber;   //!
  TBranch        *b_BCID;   //!
  TBranch        *b_BCType;   //!
  TBranch        *b_OdinTCK;   //!
  TBranch        *b_L0DUTCK;   //!
  TBranch        *b_HLTTCK;   //!
  TBranch        *b_GpsTime;   //!
  TBranch        *b_Polarity;   //!
  TBranch        *b_StrippingTriMuonBc2ThreeMuDecision;   //!
  TBranch        *b_StrippingBc2JpsiMuLineDecision;   //!
  TBranch        *b_StrippingFullDSTDiMuonJpsi2MuMuDetachedLineDecision;   //!
  TBranch        *b_StrippingFullDSTDiMuonJpsi2MuMuTOSLineDecision;   //!
  TBranch        *b_L0Global;   //!
  TBranch        *b_Hlt1Global;   //!
  TBranch        *b_Hlt2Global;   //!
  TBranch        *b_L0MuonDecision;   //!
  TBranch        *b_L0DiMuonDecision;   //!
  TBranch        *b_L0nSelections;   //!
  TBranch        *b_Hlt1DiMuonHighMassDecision;   //!
  TBranch        *b_Hlt1DiMuonLowMassDecision;   //!
  TBranch        *b_Hlt1nSelections;   //!
  TBranch        *b_Hlt2DiMuonJPsiHighPTDecision;   //!
  TBranch        *b_Hlt2nSelections;   //!
  TBranch        *b_MaxRoutingBits;   //!
  TBranch        *b_RoutingBits;   //!

  Psi2SFFTest(TTree * /*tree*/ =0) : fChain(0) { }
  virtual ~Psi2SFFTest() { }
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

  ClassDef(Psi2SFFTest,0);
};

#endif

#ifdef Psi2SFFTest_cxx
void Psi2SFFTest::Init(TTree *tree)
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
  fChain->SetBranchAddress("Bc_TRUEP_E", &Bc_TRUEP_E, &b_Bc_TRUEP_E);
  fChain->SetBranchAddress("Bc_TRUEP_X", &Bc_TRUEP_X, &b_Bc_TRUEP_X);
  fChain->SetBranchAddress("Bc_TRUEP_Y", &Bc_TRUEP_Y, &b_Bc_TRUEP_Y);
  fChain->SetBranchAddress("Bc_TRUEP_Z", &Bc_TRUEP_Z, &b_Bc_TRUEP_Z);
  fChain->SetBranchAddress("Bc_TRUEPT", &Bc_TRUEPT, &b_Bc_TRUEPT);
  fChain->SetBranchAddress("Bc_TRUEORIGINVERTEX_X", &Bc_TRUEORIGINVERTEX_X, &b_Bc_TRUEORIGINVERTEX_X);
  fChain->SetBranchAddress("Bc_TRUEORIGINVERTEX_Y", &Bc_TRUEORIGINVERTEX_Y, &b_Bc_TRUEORIGINVERTEX_Y);
  fChain->SetBranchAddress("Bc_TRUEORIGINVERTEX_Z", &Bc_TRUEORIGINVERTEX_Z, &b_Bc_TRUEORIGINVERTEX_Z);
  fChain->SetBranchAddress("Bc_TRUEENDVERTEX_X", &Bc_TRUEENDVERTEX_X, &b_Bc_TRUEENDVERTEX_X);
  fChain->SetBranchAddress("Bc_TRUEENDVERTEX_Y", &Bc_TRUEENDVERTEX_Y, &b_Bc_TRUEENDVERTEX_Y);
  fChain->SetBranchAddress("Bc_TRUEENDVERTEX_Z", &Bc_TRUEENDVERTEX_Z, &b_Bc_TRUEENDVERTEX_Z);
  fChain->SetBranchAddress("Bc_TRUEISSTABLE", &Bc_TRUEISSTABLE, &b_Bc_TRUEISSTABLE);
  fChain->SetBranchAddress("Bc_TRUETAU", &Bc_TRUETAU, &b_Bc_TRUETAU);
  fChain->SetBranchAddress("psi2S_ACC", &psi2S_ACC, &b_psi2S_ACC);
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
  fChain->SetBranchAddress("psi2S_TRUEP_E", &psi2S_TRUEP_E, &b_psi2S_TRUEP_E);
  fChain->SetBranchAddress("psi2S_TRUEP_X", &psi2S_TRUEP_X, &b_psi2S_TRUEP_X);
  fChain->SetBranchAddress("psi2S_TRUEP_Y", &psi2S_TRUEP_Y, &b_psi2S_TRUEP_Y);
  fChain->SetBranchAddress("psi2S_TRUEP_Z", &psi2S_TRUEP_Z, &b_psi2S_TRUEP_Z);
  fChain->SetBranchAddress("psi2S_TRUEPT", &psi2S_TRUEPT, &b_psi2S_TRUEPT);
  fChain->SetBranchAddress("psi2S_TRUEORIGINVERTEX_X", &psi2S_TRUEORIGINVERTEX_X, &b_psi2S_TRUEORIGINVERTEX_X);
  fChain->SetBranchAddress("psi2S_TRUEORIGINVERTEX_Y", &psi2S_TRUEORIGINVERTEX_Y, &b_psi2S_TRUEORIGINVERTEX_Y);
  fChain->SetBranchAddress("psi2S_TRUEORIGINVERTEX_Z", &psi2S_TRUEORIGINVERTEX_Z, &b_psi2S_TRUEORIGINVERTEX_Z);
  fChain->SetBranchAddress("psi2S_TRUEENDVERTEX_X", &psi2S_TRUEENDVERTEX_X, &b_psi2S_TRUEENDVERTEX_X);
  fChain->SetBranchAddress("psi2S_TRUEENDVERTEX_Y", &psi2S_TRUEENDVERTEX_Y, &b_psi2S_TRUEENDVERTEX_Y);
  fChain->SetBranchAddress("psi2S_TRUEENDVERTEX_Z", &psi2S_TRUEENDVERTEX_Z, &b_psi2S_TRUEENDVERTEX_Z);
  fChain->SetBranchAddress("psi2S_TRUEISSTABLE", &psi2S_TRUEISSTABLE, &b_psi2S_TRUEISSTABLE);
  fChain->SetBranchAddress("psi2S_TRUETAU", &psi2S_TRUETAU, &b_psi2S_TRUETAU);
  fChain->SetBranchAddress("BachMu_ACC", &BachMu_ACC, &b_BachMu_ACC);
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
  fChain->SetBranchAddress("BachMu_TRUEP_E", &BachMu_TRUEP_E, &b_BachMu_TRUEP_E);
  fChain->SetBranchAddress("BachMu_TRUEP_X", &BachMu_TRUEP_X, &b_BachMu_TRUEP_X);
  fChain->SetBranchAddress("BachMu_TRUEP_Y", &BachMu_TRUEP_Y, &b_BachMu_TRUEP_Y);
  fChain->SetBranchAddress("BachMu_TRUEP_Z", &BachMu_TRUEP_Z, &b_BachMu_TRUEP_Z);
  fChain->SetBranchAddress("BachMu_TRUEPT", &BachMu_TRUEPT, &b_BachMu_TRUEPT);
  fChain->SetBranchAddress("BachMu_TRUEORIGINVERTEX_X", &BachMu_TRUEORIGINVERTEX_X, &b_BachMu_TRUEORIGINVERTEX_X);
  fChain->SetBranchAddress("BachMu_TRUEORIGINVERTEX_Y", &BachMu_TRUEORIGINVERTEX_Y, &b_BachMu_TRUEORIGINVERTEX_Y);
  fChain->SetBranchAddress("BachMu_TRUEORIGINVERTEX_Z", &BachMu_TRUEORIGINVERTEX_Z, &b_BachMu_TRUEORIGINVERTEX_Z);
  fChain->SetBranchAddress("BachMu_TRUEENDVERTEX_X", &BachMu_TRUEENDVERTEX_X, &b_BachMu_TRUEENDVERTEX_X);
  fChain->SetBranchAddress("BachMu_TRUEENDVERTEX_Y", &BachMu_TRUEENDVERTEX_Y, &b_BachMu_TRUEENDVERTEX_Y);
  fChain->SetBranchAddress("BachMu_TRUEENDVERTEX_Z", &BachMu_TRUEENDVERTEX_Z, &b_BachMu_TRUEENDVERTEX_Z);
  fChain->SetBranchAddress("BachMu_TRUEISSTABLE", &BachMu_TRUEISSTABLE, &b_BachMu_TRUEISSTABLE);
  fChain->SetBranchAddress("BachMu_TRUETAU", &BachMu_TRUETAU, &b_BachMu_TRUETAU);
  fChain->SetBranchAddress("BachMu_Reconstructible", &BachMu_Reconstructible, &b_BachMu_Reconstructible);
  fChain->SetBranchAddress("BachMu_Reconstructed", &BachMu_Reconstructed, &b_BachMu_Reconstructed);
  fChain->SetBranchAddress("BachMu_ProtoParticles", &BachMu_ProtoParticles, &b_BachMu_ProtoParticles);
  fChain->SetBranchAddress("BachMu_PP_PX", BachMu_PP_PX, &b_BachMu_PP_PX);
  fChain->SetBranchAddress("BachMu_PP_PY", BachMu_PP_PY, &b_BachMu_PP_PY);
  fChain->SetBranchAddress("BachMu_PP_PZ", BachMu_PP_PZ, &b_BachMu_PP_PZ);
  fChain->SetBranchAddress("BachMu_PP_Weight", BachMu_PP_Weight, &b_BachMu_PP_Weight);
  fChain->SetBranchAddress("BachMu_PP_tr_pchi2", BachMu_PP_tr_pchi2, &b_BachMu_PP_tr_pchi2);
  fChain->SetBranchAddress("BachMu_PP_DLLe", BachMu_PP_DLLe, &b_BachMu_PP_DLLe);
  fChain->SetBranchAddress("BachMu_PP_DLLk", BachMu_PP_DLLk, &b_BachMu_PP_DLLk);
  fChain->SetBranchAddress("BachMu_PP_DLLp", BachMu_PP_DLLp, &b_BachMu_PP_DLLp);
  fChain->SetBranchAddress("BachMu_PP_DLLmu", BachMu_PP_DLLmu, &b_BachMu_PP_DLLmu);
  fChain->SetBranchAddress("NuMu_ACC", &NuMu_ACC, &b_NuMu_ACC);
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
  fChain->SetBranchAddress("NuMu_TRUEP_E", &NuMu_TRUEP_E, &b_NuMu_TRUEP_E);
  fChain->SetBranchAddress("NuMu_TRUEP_X", &NuMu_TRUEP_X, &b_NuMu_TRUEP_X);
  fChain->SetBranchAddress("NuMu_TRUEP_Y", &NuMu_TRUEP_Y, &b_NuMu_TRUEP_Y);
  fChain->SetBranchAddress("NuMu_TRUEP_Z", &NuMu_TRUEP_Z, &b_NuMu_TRUEP_Z);
  fChain->SetBranchAddress("NuMu_TRUEPT", &NuMu_TRUEPT, &b_NuMu_TRUEPT);
  fChain->SetBranchAddress("NuMu_TRUEORIGINVERTEX_X", &NuMu_TRUEORIGINVERTEX_X, &b_NuMu_TRUEORIGINVERTEX_X);
  fChain->SetBranchAddress("NuMu_TRUEORIGINVERTEX_Y", &NuMu_TRUEORIGINVERTEX_Y, &b_NuMu_TRUEORIGINVERTEX_Y);
  fChain->SetBranchAddress("NuMu_TRUEORIGINVERTEX_Z", &NuMu_TRUEORIGINVERTEX_Z, &b_NuMu_TRUEORIGINVERTEX_Z);
  fChain->SetBranchAddress("NuMu_TRUEENDVERTEX_X", &NuMu_TRUEENDVERTEX_X, &b_NuMu_TRUEENDVERTEX_X);
  fChain->SetBranchAddress("NuMu_TRUEENDVERTEX_Y", &NuMu_TRUEENDVERTEX_Y, &b_NuMu_TRUEENDVERTEX_Y);
  fChain->SetBranchAddress("NuMu_TRUEENDVERTEX_Z", &NuMu_TRUEENDVERTEX_Z, &b_NuMu_TRUEENDVERTEX_Z);
  fChain->SetBranchAddress("NuMu_TRUEISSTABLE", &NuMu_TRUEISSTABLE, &b_NuMu_TRUEISSTABLE);
  fChain->SetBranchAddress("NuMu_TRUETAU", &NuMu_TRUETAU, &b_NuMu_TRUETAU);
  fChain->SetBranchAddress("nCandidate", &nCandidate, &b_nCandidate);
  fChain->SetBranchAddress("totCandidates", &totCandidates, &b_totCandidates);
  fChain->SetBranchAddress("EventInSequence", &EventInSequence, &b_EventInSequence);
  fChain->SetBranchAddress("runNumber", &runNumber, &b_runNumber);
  fChain->SetBranchAddress("eventNumber", &eventNumber, &b_eventNumber);
  fChain->SetBranchAddress("BCID", &BCID, &b_BCID);
  fChain->SetBranchAddress("BCType", &BCType, &b_BCType);
  fChain->SetBranchAddress("OdinTCK", &OdinTCK, &b_OdinTCK);
  fChain->SetBranchAddress("L0DUTCK", &L0DUTCK, &b_L0DUTCK);
  fChain->SetBranchAddress("HLTTCK", &HLTTCK, &b_HLTTCK);
  fChain->SetBranchAddress("GpsTime", &GpsTime, &b_GpsTime);
  fChain->SetBranchAddress("Polarity", &Polarity, &b_Polarity);
  fChain->SetBranchAddress("StrippingTriMuonBc2ThreeMuDecision", &StrippingTriMuonBc2ThreeMuDecision, &b_StrippingTriMuonBc2ThreeMuDecision);
  fChain->SetBranchAddress("StrippingBc2JpsiMuLineDecision", &StrippingBc2JpsiMuLineDecision, &b_StrippingBc2JpsiMuLineDecision);
  fChain->SetBranchAddress("StrippingFullDSTDiMuonJpsi2MuMuDetachedLineDecision", &StrippingFullDSTDiMuonJpsi2MuMuDetachedLineDecision, &b_StrippingFullDSTDiMuonJpsi2MuMuDetachedLineDecision);
  fChain->SetBranchAddress("StrippingFullDSTDiMuonJpsi2MuMuTOSLineDecision", &StrippingFullDSTDiMuonJpsi2MuMuTOSLineDecision, &b_StrippingFullDSTDiMuonJpsi2MuMuTOSLineDecision);
  fChain->SetBranchAddress("L0Global", &L0Global, &b_L0Global);
  fChain->SetBranchAddress("Hlt1Global", &Hlt1Global, &b_Hlt1Global);
  fChain->SetBranchAddress("Hlt2Global", &Hlt2Global, &b_Hlt2Global);
  fChain->SetBranchAddress("L0MuonDecision", &L0MuonDecision, &b_L0MuonDecision);
  fChain->SetBranchAddress("L0DiMuonDecision", &L0DiMuonDecision, &b_L0DiMuonDecision);
  fChain->SetBranchAddress("L0nSelections", &L0nSelections, &b_L0nSelections);
  fChain->SetBranchAddress("Hlt1DiMuonHighMassDecision", &Hlt1DiMuonHighMassDecision, &b_Hlt1DiMuonHighMassDecision);
  fChain->SetBranchAddress("Hlt1DiMuonLowMassDecision", &Hlt1DiMuonLowMassDecision, &b_Hlt1DiMuonLowMassDecision);
  fChain->SetBranchAddress("Hlt1nSelections", &Hlt1nSelections, &b_Hlt1nSelections);
  fChain->SetBranchAddress("Hlt2DiMuonJPsiHighPTDecision", &Hlt2DiMuonJPsiHighPTDecision, &b_Hlt2DiMuonJPsiHighPTDecision);
  fChain->SetBranchAddress("Hlt2nSelections", &Hlt2nSelections, &b_Hlt2nSelections);
  fChain->SetBranchAddress("MaxRoutingBits", &MaxRoutingBits, &b_MaxRoutingBits);
  fChain->SetBranchAddress("RoutingBits", RoutingBits, &b_RoutingBits);
}

Bool_t Psi2SFFTest::Notify()
{
  // The Notify() function is called when a new file is opened. This
  // can be either for a new TTree in a TChain or when when a new TTree
  // is started when using PROOF. It is normally not necessary to make changes
  // to the generated code, but the routine can be extended by the
  // user if needed. The return value is currently not used.

  return kTRUE;
}

#endif // #ifdef Psi2SFFTest_cxx
