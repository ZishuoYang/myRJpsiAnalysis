//////////////////////////////////////////////////////////
// This class has been automatically generated on
// Wed Mar 12 04:53:01 2014 by ROOT version 5.34/10
// from TTree MCDecayTree/MCDecayTree
// found on file: LHCb/bcharm/chic_test/tupleProduction.root
//////////////////////////////////////////////////////////

#ifndef Psi2SFFPlotter_h
#define Psi2SFFPlotter_h

#include <TROOT.h>
#include <TChain.h>
#include <TFile.h>
#include <TSelector.h>

// Header file for the classes stored in the TTree if any.

// Fixed size dimensions of array or collections stored in the TTree if any.

class Psi2SFFPlotter : public TSelector {
public :
   TTree          *fChain;   //!pointer to the analyzed TTree or TChain

  // Histograms
  TH1F* angleHisto;
  TH1F* elepHisto;
  TH1F* q2Histo;

   // Declaration of leaf types
   Int_t           B_cplus_MC_MOTHER_ID;
   Int_t           B_cplus_MC_MOTHER_KEY;
   Int_t           B_cplus_MC_GD_MOTHER_ID;
   Int_t           B_cplus_MC_GD_MOTHER_KEY;
   Int_t           B_cplus_MC_GD_GD_MOTHER_ID;
   Int_t           B_cplus_MC_GD_GD_MOTHER_KEY;
   Double_t        B_cplus_TRUEP_E;
   Double_t        B_cplus_TRUEP_X;
   Double_t        B_cplus_TRUEP_Y;
   Double_t        B_cplus_TRUEP_Z;
   Double_t        B_cplus_TRUEPT;
   Double_t        B_cplus_TRUEORIGINVERTEX_X;
   Double_t        B_cplus_TRUEORIGINVERTEX_Y;
   Double_t        B_cplus_TRUEORIGINVERTEX_Z;
   Double_t        B_cplus_TRUEENDVERTEX_X;
   Double_t        B_cplus_TRUEENDVERTEX_Y;
   Double_t        B_cplus_TRUEENDVERTEX_Z;
   Bool_t          B_cplus_TRUEISSTABLE;
   Double_t        B_cplus_TRUETAU;
   Bool_t          B_cplus_OSCIL;
   Int_t           psi_2S_MC_MOTHER_ID;
   Int_t           psi_2S_MC_MOTHER_KEY;
   Int_t           psi_2S_MC_GD_MOTHER_ID;
   Int_t           psi_2S_MC_GD_MOTHER_KEY;
   Int_t           psi_2S_MC_GD_GD_MOTHER_ID;
   Int_t           psi_2S_MC_GD_GD_MOTHER_KEY;
   Double_t        psi_2S_TRUEP_E;
   Double_t        psi_2S_TRUEP_X;
   Double_t        psi_2S_TRUEP_Y;
   Double_t        psi_2S_TRUEP_Z;
   Double_t        psi_2S_TRUEPT;
   Double_t        psi_2S_TRUEORIGINVERTEX_X;
   Double_t        psi_2S_TRUEORIGINVERTEX_Y;
   Double_t        psi_2S_TRUEORIGINVERTEX_Z;
   Double_t        psi_2S_TRUEENDVERTEX_X;
   Double_t        psi_2S_TRUEENDVERTEX_Y;
   Double_t        psi_2S_TRUEENDVERTEX_Z;
   Bool_t          psi_2S_TRUEISSTABLE;
   Double_t        psi_2S_TRUETAU;
   Bool_t          psi_2S_OSCIL;
   Int_t           muplus_MC_MOTHER_ID;
   Int_t           muplus_MC_MOTHER_KEY;
   Int_t           muplus_MC_GD_MOTHER_ID;
   Int_t           muplus_MC_GD_MOTHER_KEY;
   Int_t           muplus_MC_GD_GD_MOTHER_ID;
   Int_t           muplus_MC_GD_GD_MOTHER_KEY;
   Double_t        muplus_TRUEP_E;
   Double_t        muplus_TRUEP_X;
   Double_t        muplus_TRUEP_Y;
   Double_t        muplus_TRUEP_Z;
   Double_t        muplus_TRUEPT;
   Double_t        muplus_TRUEORIGINVERTEX_X;
   Double_t        muplus_TRUEORIGINVERTEX_Y;
   Double_t        muplus_TRUEORIGINVERTEX_Z;
   Double_t        muplus_TRUEENDVERTEX_X;
   Double_t        muplus_TRUEENDVERTEX_Y;
   Double_t        muplus_TRUEENDVERTEX_Z;
   Bool_t          muplus_TRUEISSTABLE;
   Double_t        muplus_TRUETAU;
   Bool_t          muplus_OSCIL;
   Int_t           nu_mu_MC_MOTHER_ID;
   Int_t           nu_mu_MC_MOTHER_KEY;
   Int_t           nu_mu_MC_GD_MOTHER_ID;
   Int_t           nu_mu_MC_GD_MOTHER_KEY;
   Int_t           nu_mu_MC_GD_GD_MOTHER_ID;
   Int_t           nu_mu_MC_GD_GD_MOTHER_KEY;
   Double_t        nu_mu_TRUEP_E;
   Double_t        nu_mu_TRUEP_X;
   Double_t        nu_mu_TRUEP_Y;
   Double_t        nu_mu_TRUEP_Z;
   Double_t        nu_mu_TRUEPT;
   Double_t        nu_mu_TRUEORIGINVERTEX_X;
   Double_t        nu_mu_TRUEORIGINVERTEX_Y;
   Double_t        nu_mu_TRUEORIGINVERTEX_Z;
   Double_t        nu_mu_TRUEENDVERTEX_X;
   Double_t        nu_mu_TRUEENDVERTEX_Y;
   Double_t        nu_mu_TRUEENDVERTEX_Z;
   Bool_t          nu_mu_TRUEISSTABLE;
   Double_t        nu_mu_TRUETAU;
   Bool_t          nu_mu_OSCIL;
   UInt_t          nCandidate;
   ULong64_t       totCandidates;
   ULong64_t       EventInSequence;

   // List of branches
   TBranch        *b_B_cplus_MC_MOTHER_ID;   //!
   TBranch        *b_B_cplus_MC_MOTHER_KEY;   //!
   TBranch        *b_B_cplus_MC_GD_MOTHER_ID;   //!
   TBranch        *b_B_cplus_MC_GD_MOTHER_KEY;   //!
   TBranch        *b_B_cplus_MC_GD_GD_MOTHER_ID;   //!
   TBranch        *b_B_cplus_MC_GD_GD_MOTHER_KEY;   //!
   TBranch        *b_B_cplus_TRUEP_E;   //!
   TBranch        *b_B_cplus_TRUEP_X;   //!
   TBranch        *b_B_cplus_TRUEP_Y;   //!
   TBranch        *b_B_cplus_TRUEP_Z;   //!
   TBranch        *b_B_cplus_TRUEPT;   //!
   TBranch        *b_B_cplus_TRUEORIGINVERTEX_X;   //!
   TBranch        *b_B_cplus_TRUEORIGINVERTEX_Y;   //!
   TBranch        *b_B_cplus_TRUEORIGINVERTEX_Z;   //!
   TBranch        *b_B_cplus_TRUEENDVERTEX_X;   //!
   TBranch        *b_B_cplus_TRUEENDVERTEX_Y;   //!
   TBranch        *b_B_cplus_TRUEENDVERTEX_Z;   //!
   TBranch        *b_B_cplus_TRUEISSTABLE;   //!
   TBranch        *b_B_cplus_TRUETAU;   //!
   TBranch        *b_B_cplus_OSCIL;   //!
   TBranch        *b_psi_2S_MC_MOTHER_ID;   //!
   TBranch        *b_psi_2S_MC_MOTHER_KEY;   //!
   TBranch        *b_psi_2S_MC_GD_MOTHER_ID;   //!
   TBranch        *b_psi_2S_MC_GD_MOTHER_KEY;   //!
   TBranch        *b_psi_2S_MC_GD_GD_MOTHER_ID;   //!
   TBranch        *b_psi_2S_MC_GD_GD_MOTHER_KEY;   //!
   TBranch        *b_psi_2S_TRUEP_E;   //!
   TBranch        *b_psi_2S_TRUEP_X;   //!
   TBranch        *b_psi_2S_TRUEP_Y;   //!
   TBranch        *b_psi_2S_TRUEP_Z;   //!
   TBranch        *b_psi_2S_TRUEPT;   //!
   TBranch        *b_psi_2S_TRUEORIGINVERTEX_X;   //!
   TBranch        *b_psi_2S_TRUEORIGINVERTEX_Y;   //!
   TBranch        *b_psi_2S_TRUEORIGINVERTEX_Z;   //!
   TBranch        *b_psi_2S_TRUEENDVERTEX_X;   //!
   TBranch        *b_psi_2S_TRUEENDVERTEX_Y;   //!
   TBranch        *b_psi_2S_TRUEENDVERTEX_Z;   //!
   TBranch        *b_psi_2S_TRUEISSTABLE;   //!
   TBranch        *b_psi_2S_TRUETAU;   //!
   TBranch        *b_psi_2S_OSCIL;   //!
   TBranch        *b_muplus_MC_MOTHER_ID;   //!
   TBranch        *b_muplus_MC_MOTHER_KEY;   //!
   TBranch        *b_muplus_MC_GD_MOTHER_ID;   //!
   TBranch        *b_muplus_MC_GD_MOTHER_KEY;   //!
   TBranch        *b_muplus_MC_GD_GD_MOTHER_ID;   //!
   TBranch        *b_muplus_MC_GD_GD_MOTHER_KEY;   //!
   TBranch        *b_muplus_TRUEP_E;   //!
   TBranch        *b_muplus_TRUEP_X;   //!
   TBranch        *b_muplus_TRUEP_Y;   //!
   TBranch        *b_muplus_TRUEP_Z;   //!
   TBranch        *b_muplus_TRUEPT;   //!
   TBranch        *b_muplus_TRUEORIGINVERTEX_X;   //!
   TBranch        *b_muplus_TRUEORIGINVERTEX_Y;   //!
   TBranch        *b_muplus_TRUEORIGINVERTEX_Z;   //!
   TBranch        *b_muplus_TRUEENDVERTEX_X;   //!
   TBranch        *b_muplus_TRUEENDVERTEX_Y;   //!
   TBranch        *b_muplus_TRUEENDVERTEX_Z;   //!
   TBranch        *b_muplus_TRUEISSTABLE;   //!
   TBranch        *b_muplus_TRUETAU;   //!
   TBranch        *b_muplus_OSCIL;   //!
   TBranch        *b_nu_mu_MC_MOTHER_ID;   //!
   TBranch        *b_nu_mu_MC_MOTHER_KEY;   //!
   TBranch        *b_nu_mu_MC_GD_MOTHER_ID;   //!
   TBranch        *b_nu_mu_MC_GD_MOTHER_KEY;   //!
   TBranch        *b_nu_mu_MC_GD_GD_MOTHER_ID;   //!
   TBranch        *b_nu_mu_MC_GD_GD_MOTHER_KEY;   //!
   TBranch        *b_nu_mu_TRUEP_E;   //!
   TBranch        *b_nu_mu_TRUEP_X;   //!
   TBranch        *b_nu_mu_TRUEP_Y;   //!
   TBranch        *b_nu_mu_TRUEP_Z;   //!
   TBranch        *b_nu_mu_TRUEPT;   //!
   TBranch        *b_nu_mu_TRUEORIGINVERTEX_X;   //!
   TBranch        *b_nu_mu_TRUEORIGINVERTEX_Y;   //!
   TBranch        *b_nu_mu_TRUEORIGINVERTEX_Z;   //!
   TBranch        *b_nu_mu_TRUEENDVERTEX_X;   //!
   TBranch        *b_nu_mu_TRUEENDVERTEX_Y;   //!
   TBranch        *b_nu_mu_TRUEENDVERTEX_Z;   //!
   TBranch        *b_nu_mu_TRUEISSTABLE;   //!
   TBranch        *b_nu_mu_TRUETAU;   //!
   TBranch        *b_nu_mu_OSCIL;   //!
   TBranch        *b_nCandidate;   //!
   TBranch        *b_totCandidates;   //!
   TBranch        *b_EventInSequence;   //!

   Psi2SFFPlotter(TTree * /*tree*/ =0) : fChain(0) { }
   virtual ~Psi2SFFPlotter() { }
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

   ClassDef(Psi2SFFPlotter,0);
};

#endif

#ifdef Psi2SFFPlotter_cxx
void Psi2SFFPlotter::Init(TTree *tree)
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

   fChain->SetBranchAddress("B_cplus_MC_MOTHER_ID", &B_cplus_MC_MOTHER_ID, &b_B_cplus_MC_MOTHER_ID);
   fChain->SetBranchAddress("B_cplus_MC_MOTHER_KEY", &B_cplus_MC_MOTHER_KEY, &b_B_cplus_MC_MOTHER_KEY);
   fChain->SetBranchAddress("B_cplus_MC_GD_MOTHER_ID", &B_cplus_MC_GD_MOTHER_ID, &b_B_cplus_MC_GD_MOTHER_ID);
   fChain->SetBranchAddress("B_cplus_MC_GD_MOTHER_KEY", &B_cplus_MC_GD_MOTHER_KEY, &b_B_cplus_MC_GD_MOTHER_KEY);
   fChain->SetBranchAddress("B_cplus_MC_GD_GD_MOTHER_ID", &B_cplus_MC_GD_GD_MOTHER_ID, &b_B_cplus_MC_GD_GD_MOTHER_ID);
   fChain->SetBranchAddress("B_cplus_MC_GD_GD_MOTHER_KEY", &B_cplus_MC_GD_GD_MOTHER_KEY, &b_B_cplus_MC_GD_GD_MOTHER_KEY);
   fChain->SetBranchAddress("B_cplus_TRUEP_E", &B_cplus_TRUEP_E, &b_B_cplus_TRUEP_E);
   fChain->SetBranchAddress("B_cplus_TRUEP_X", &B_cplus_TRUEP_X, &b_B_cplus_TRUEP_X);
   fChain->SetBranchAddress("B_cplus_TRUEP_Y", &B_cplus_TRUEP_Y, &b_B_cplus_TRUEP_Y);
   fChain->SetBranchAddress("B_cplus_TRUEP_Z", &B_cplus_TRUEP_Z, &b_B_cplus_TRUEP_Z);
   fChain->SetBranchAddress("B_cplus_TRUEPT", &B_cplus_TRUEPT, &b_B_cplus_TRUEPT);
   fChain->SetBranchAddress("B_cplus_TRUEORIGINVERTEX_X", &B_cplus_TRUEORIGINVERTEX_X, &b_B_cplus_TRUEORIGINVERTEX_X);
   fChain->SetBranchAddress("B_cplus_TRUEORIGINVERTEX_Y", &B_cplus_TRUEORIGINVERTEX_Y, &b_B_cplus_TRUEORIGINVERTEX_Y);
   fChain->SetBranchAddress("B_cplus_TRUEORIGINVERTEX_Z", &B_cplus_TRUEORIGINVERTEX_Z, &b_B_cplus_TRUEORIGINVERTEX_Z);
   fChain->SetBranchAddress("B_cplus_TRUEENDVERTEX_X", &B_cplus_TRUEENDVERTEX_X, &b_B_cplus_TRUEENDVERTEX_X);
   fChain->SetBranchAddress("B_cplus_TRUEENDVERTEX_Y", &B_cplus_TRUEENDVERTEX_Y, &b_B_cplus_TRUEENDVERTEX_Y);
   fChain->SetBranchAddress("B_cplus_TRUEENDVERTEX_Z", &B_cplus_TRUEENDVERTEX_Z, &b_B_cplus_TRUEENDVERTEX_Z);
   fChain->SetBranchAddress("B_cplus_TRUEISSTABLE", &B_cplus_TRUEISSTABLE, &b_B_cplus_TRUEISSTABLE);
   fChain->SetBranchAddress("B_cplus_TRUETAU", &B_cplus_TRUETAU, &b_B_cplus_TRUETAU);
   fChain->SetBranchAddress("B_cplus_OSCIL", &B_cplus_OSCIL, &b_B_cplus_OSCIL);
   fChain->SetBranchAddress("psi_2S_MC_MOTHER_ID", &psi_2S_MC_MOTHER_ID, &b_psi_2S_MC_MOTHER_ID);
   fChain->SetBranchAddress("psi_2S_MC_MOTHER_KEY", &psi_2S_MC_MOTHER_KEY, &b_psi_2S_MC_MOTHER_KEY);
   fChain->SetBranchAddress("psi_2S_MC_GD_MOTHER_ID", &psi_2S_MC_GD_MOTHER_ID, &b_psi_2S_MC_GD_MOTHER_ID);
   fChain->SetBranchAddress("psi_2S_MC_GD_MOTHER_KEY", &psi_2S_MC_GD_MOTHER_KEY, &b_psi_2S_MC_GD_MOTHER_KEY);
   fChain->SetBranchAddress("psi_2S_MC_GD_GD_MOTHER_ID", &psi_2S_MC_GD_GD_MOTHER_ID, &b_psi_2S_MC_GD_GD_MOTHER_ID);
   fChain->SetBranchAddress("psi_2S_MC_GD_GD_MOTHER_KEY", &psi_2S_MC_GD_GD_MOTHER_KEY, &b_psi_2S_MC_GD_GD_MOTHER_KEY);
   fChain->SetBranchAddress("psi_2S_TRUEP_E", &psi_2S_TRUEP_E, &b_psi_2S_TRUEP_E);
   fChain->SetBranchAddress("psi_2S_TRUEP_X", &psi_2S_TRUEP_X, &b_psi_2S_TRUEP_X);
   fChain->SetBranchAddress("psi_2S_TRUEP_Y", &psi_2S_TRUEP_Y, &b_psi_2S_TRUEP_Y);
   fChain->SetBranchAddress("psi_2S_TRUEP_Z", &psi_2S_TRUEP_Z, &b_psi_2S_TRUEP_Z);
   fChain->SetBranchAddress("psi_2S_TRUEPT", &psi_2S_TRUEPT, &b_psi_2S_TRUEPT);
   fChain->SetBranchAddress("psi_2S_TRUEORIGINVERTEX_X", &psi_2S_TRUEORIGINVERTEX_X, &b_psi_2S_TRUEORIGINVERTEX_X);
   fChain->SetBranchAddress("psi_2S_TRUEORIGINVERTEX_Y", &psi_2S_TRUEORIGINVERTEX_Y, &b_psi_2S_TRUEORIGINVERTEX_Y);
   fChain->SetBranchAddress("psi_2S_TRUEORIGINVERTEX_Z", &psi_2S_TRUEORIGINVERTEX_Z, &b_psi_2S_TRUEORIGINVERTEX_Z);
   fChain->SetBranchAddress("psi_2S_TRUEENDVERTEX_X", &psi_2S_TRUEENDVERTEX_X, &b_psi_2S_TRUEENDVERTEX_X);
   fChain->SetBranchAddress("psi_2S_TRUEENDVERTEX_Y", &psi_2S_TRUEENDVERTEX_Y, &b_psi_2S_TRUEENDVERTEX_Y);
   fChain->SetBranchAddress("psi_2S_TRUEENDVERTEX_Z", &psi_2S_TRUEENDVERTEX_Z, &b_psi_2S_TRUEENDVERTEX_Z);
   fChain->SetBranchAddress("psi_2S_TRUEISSTABLE", &psi_2S_TRUEISSTABLE, &b_psi_2S_TRUEISSTABLE);
   fChain->SetBranchAddress("psi_2S_TRUETAU", &psi_2S_TRUETAU, &b_psi_2S_TRUETAU);
   fChain->SetBranchAddress("psi_2S_OSCIL", &psi_2S_OSCIL, &b_psi_2S_OSCIL);
   fChain->SetBranchAddress("muplus_MC_MOTHER_ID", &muplus_MC_MOTHER_ID, &b_muplus_MC_MOTHER_ID);
   fChain->SetBranchAddress("muplus_MC_MOTHER_KEY", &muplus_MC_MOTHER_KEY, &b_muplus_MC_MOTHER_KEY);
   fChain->SetBranchAddress("muplus_MC_GD_MOTHER_ID", &muplus_MC_GD_MOTHER_ID, &b_muplus_MC_GD_MOTHER_ID);
   fChain->SetBranchAddress("muplus_MC_GD_MOTHER_KEY", &muplus_MC_GD_MOTHER_KEY, &b_muplus_MC_GD_MOTHER_KEY);
   fChain->SetBranchAddress("muplus_MC_GD_GD_MOTHER_ID", &muplus_MC_GD_GD_MOTHER_ID, &b_muplus_MC_GD_GD_MOTHER_ID);
   fChain->SetBranchAddress("muplus_MC_GD_GD_MOTHER_KEY", &muplus_MC_GD_GD_MOTHER_KEY, &b_muplus_MC_GD_GD_MOTHER_KEY);
   fChain->SetBranchAddress("muplus_TRUEP_E", &muplus_TRUEP_E, &b_muplus_TRUEP_E);
   fChain->SetBranchAddress("muplus_TRUEP_X", &muplus_TRUEP_X, &b_muplus_TRUEP_X);
   fChain->SetBranchAddress("muplus_TRUEP_Y", &muplus_TRUEP_Y, &b_muplus_TRUEP_Y);
   fChain->SetBranchAddress("muplus_TRUEP_Z", &muplus_TRUEP_Z, &b_muplus_TRUEP_Z);
   fChain->SetBranchAddress("muplus_TRUEPT", &muplus_TRUEPT, &b_muplus_TRUEPT);
   fChain->SetBranchAddress("muplus_TRUEORIGINVERTEX_X", &muplus_TRUEORIGINVERTEX_X, &b_muplus_TRUEORIGINVERTEX_X);
   fChain->SetBranchAddress("muplus_TRUEORIGINVERTEX_Y", &muplus_TRUEORIGINVERTEX_Y, &b_muplus_TRUEORIGINVERTEX_Y);
   fChain->SetBranchAddress("muplus_TRUEORIGINVERTEX_Z", &muplus_TRUEORIGINVERTEX_Z, &b_muplus_TRUEORIGINVERTEX_Z);
   fChain->SetBranchAddress("muplus_TRUEENDVERTEX_X", &muplus_TRUEENDVERTEX_X, &b_muplus_TRUEENDVERTEX_X);
   fChain->SetBranchAddress("muplus_TRUEENDVERTEX_Y", &muplus_TRUEENDVERTEX_Y, &b_muplus_TRUEENDVERTEX_Y);
   fChain->SetBranchAddress("muplus_TRUEENDVERTEX_Z", &muplus_TRUEENDVERTEX_Z, &b_muplus_TRUEENDVERTEX_Z);
   fChain->SetBranchAddress("muplus_TRUEISSTABLE", &muplus_TRUEISSTABLE, &b_muplus_TRUEISSTABLE);
   fChain->SetBranchAddress("muplus_TRUETAU", &muplus_TRUETAU, &b_muplus_TRUETAU);
   fChain->SetBranchAddress("muplus_OSCIL", &muplus_OSCIL, &b_muplus_OSCIL);
   fChain->SetBranchAddress("nu_mu_MC_MOTHER_ID", &nu_mu_MC_MOTHER_ID, &b_nu_mu_MC_MOTHER_ID);
   fChain->SetBranchAddress("nu_mu_MC_MOTHER_KEY", &nu_mu_MC_MOTHER_KEY, &b_nu_mu_MC_MOTHER_KEY);
   fChain->SetBranchAddress("nu_mu_MC_GD_MOTHER_ID", &nu_mu_MC_GD_MOTHER_ID, &b_nu_mu_MC_GD_MOTHER_ID);
   fChain->SetBranchAddress("nu_mu_MC_GD_MOTHER_KEY", &nu_mu_MC_GD_MOTHER_KEY, &b_nu_mu_MC_GD_MOTHER_KEY);
   fChain->SetBranchAddress("nu_mu_MC_GD_GD_MOTHER_ID", &nu_mu_MC_GD_GD_MOTHER_ID, &b_nu_mu_MC_GD_GD_MOTHER_ID);
   fChain->SetBranchAddress("nu_mu_MC_GD_GD_MOTHER_KEY", &nu_mu_MC_GD_GD_MOTHER_KEY, &b_nu_mu_MC_GD_GD_MOTHER_KEY);
   fChain->SetBranchAddress("nu_mu_TRUEP_E", &nu_mu_TRUEP_E, &b_nu_mu_TRUEP_E);
   fChain->SetBranchAddress("nu_mu_TRUEP_X", &nu_mu_TRUEP_X, &b_nu_mu_TRUEP_X);
   fChain->SetBranchAddress("nu_mu_TRUEP_Y", &nu_mu_TRUEP_Y, &b_nu_mu_TRUEP_Y);
   fChain->SetBranchAddress("nu_mu_TRUEP_Z", &nu_mu_TRUEP_Z, &b_nu_mu_TRUEP_Z);
   fChain->SetBranchAddress("nu_mu_TRUEPT", &nu_mu_TRUEPT, &b_nu_mu_TRUEPT);
   fChain->SetBranchAddress("nu_mu_TRUEORIGINVERTEX_X", &nu_mu_TRUEORIGINVERTEX_X, &b_nu_mu_TRUEORIGINVERTEX_X);
   fChain->SetBranchAddress("nu_mu_TRUEORIGINVERTEX_Y", &nu_mu_TRUEORIGINVERTEX_Y, &b_nu_mu_TRUEORIGINVERTEX_Y);
   fChain->SetBranchAddress("nu_mu_TRUEORIGINVERTEX_Z", &nu_mu_TRUEORIGINVERTEX_Z, &b_nu_mu_TRUEORIGINVERTEX_Z);
   fChain->SetBranchAddress("nu_mu_TRUEENDVERTEX_X", &nu_mu_TRUEENDVERTEX_X, &b_nu_mu_TRUEENDVERTEX_X);
   fChain->SetBranchAddress("nu_mu_TRUEENDVERTEX_Y", &nu_mu_TRUEENDVERTEX_Y, &b_nu_mu_TRUEENDVERTEX_Y);
   fChain->SetBranchAddress("nu_mu_TRUEENDVERTEX_Z", &nu_mu_TRUEENDVERTEX_Z, &b_nu_mu_TRUEENDVERTEX_Z);
   fChain->SetBranchAddress("nu_mu_TRUEISSTABLE", &nu_mu_TRUEISSTABLE, &b_nu_mu_TRUEISSTABLE);
   fChain->SetBranchAddress("nu_mu_TRUETAU", &nu_mu_TRUETAU, &b_nu_mu_TRUETAU);
   fChain->SetBranchAddress("nu_mu_OSCIL", &nu_mu_OSCIL, &b_nu_mu_OSCIL);
   fChain->SetBranchAddress("nCandidate", &nCandidate, &b_nCandidate);
   fChain->SetBranchAddress("totCandidates", &totCandidates, &b_totCandidates);
   fChain->SetBranchAddress("EventInSequence", &EventInSequence, &b_EventInSequence);
}

Bool_t Psi2SFFPlotter::Notify()
{
   // The Notify() function is called when a new file is opened. This
   // can be either for a new TTree in a TChain or when when a new TTree
   // is started when using PROOF. It is normally not necessary to make changes
   // to the generated code, but the routine can be extended by the
   // user if needed. The return value is currently not used.

   return kTRUE;
}

#endif // #ifdef Psi2SFFPlotter_cxx
