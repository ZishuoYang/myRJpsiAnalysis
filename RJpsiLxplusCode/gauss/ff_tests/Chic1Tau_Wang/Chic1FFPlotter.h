//////////////////////////////////////////////////////////
// This class has been automatically generated on
// Thu May 15 17:46:14 2014 by ROOT version 5.34/18
// from TTree MCDecayTree/MCDecayTree
// found on file: chic1_wang.root
//////////////////////////////////////////////////////////

#ifndef Chic1FFPlotter_h
#define Chic1FFPlotter_h

#include <TROOT.h>
#include <TChain.h>
#include <TFile.h>
#include <TSelector.h>
#include <TH1F.h>

// Header file for the classes stored in the TTree if any.

// Fixed size dimensions of array or collections stored in the TTree if any.

class Chic1FFPlotter : public TSelector {
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
   Int_t           chi_c1_1P_MC_MOTHER_ID;
   Int_t           chi_c1_1P_MC_MOTHER_KEY;
   Int_t           chi_c1_1P_MC_GD_MOTHER_ID;
   Int_t           chi_c1_1P_MC_GD_MOTHER_KEY;
   Int_t           chi_c1_1P_MC_GD_GD_MOTHER_ID;
   Int_t           chi_c1_1P_MC_GD_GD_MOTHER_KEY;
   Double_t        chi_c1_1P_TRUEP_E;
   Double_t        chi_c1_1P_TRUEP_X;
   Double_t        chi_c1_1P_TRUEP_Y;
   Double_t        chi_c1_1P_TRUEP_Z;
   Double_t        chi_c1_1P_TRUEPT;
   Double_t        chi_c1_1P_TRUEORIGINVERTEX_X;
   Double_t        chi_c1_1P_TRUEORIGINVERTEX_Y;
   Double_t        chi_c1_1P_TRUEORIGINVERTEX_Z;
   Double_t        chi_c1_1P_TRUEENDVERTEX_X;
   Double_t        chi_c1_1P_TRUEENDVERTEX_Y;
   Double_t        chi_c1_1P_TRUEENDVERTEX_Z;
   Bool_t          chi_c1_1P_TRUEISSTABLE;
   Double_t        chi_c1_1P_TRUETAU;
   Bool_t          chi_c1_1P_OSCIL;
   Int_t           tauplus_MC_MOTHER_ID;
   Int_t           tauplus_MC_MOTHER_KEY;
   Int_t           tauplus_MC_GD_MOTHER_ID;
   Int_t           tauplus_MC_GD_MOTHER_KEY;
   Int_t           tauplus_MC_GD_GD_MOTHER_ID;
   Int_t           tauplus_MC_GD_GD_MOTHER_KEY;
   Double_t        tauplus_TRUEP_E;
   Double_t        tauplus_TRUEP_X;
   Double_t        tauplus_TRUEP_Y;
   Double_t        tauplus_TRUEP_Z;
   Double_t        tauplus_TRUEPT;
   Double_t        tauplus_TRUEORIGINVERTEX_X;
   Double_t        tauplus_TRUEORIGINVERTEX_Y;
   Double_t        tauplus_TRUEORIGINVERTEX_Z;
   Double_t        tauplus_TRUEENDVERTEX_X;
   Double_t        tauplus_TRUEENDVERTEX_Y;
   Double_t        tauplus_TRUEENDVERTEX_Z;
   Bool_t          tauplus_TRUEISSTABLE;
   Double_t        tauplus_TRUETAU;
   Bool_t          tauplus_OSCIL;
   Int_t           nu_tau_MC_MOTHER_ID;
   Int_t           nu_tau_MC_MOTHER_KEY;
   Int_t           nu_tau_MC_GD_MOTHER_ID;
   Int_t           nu_tau_MC_GD_MOTHER_KEY;
   Int_t           nu_tau_MC_GD_GD_MOTHER_ID;
   Int_t           nu_tau_MC_GD_GD_MOTHER_KEY;
   Double_t        nu_tau_TRUEP_E;
   Double_t        nu_tau_TRUEP_X;
   Double_t        nu_tau_TRUEP_Y;
   Double_t        nu_tau_TRUEP_Z;
   Double_t        nu_tau_TRUEPT;
   Double_t        nu_tau_TRUEORIGINVERTEX_X;
   Double_t        nu_tau_TRUEORIGINVERTEX_Y;
   Double_t        nu_tau_TRUEORIGINVERTEX_Z;
   Double_t        nu_tau_TRUEENDVERTEX_X;
   Double_t        nu_tau_TRUEENDVERTEX_Y;
   Double_t        nu_tau_TRUEENDVERTEX_Z;
   Bool_t          nu_tau_TRUEISSTABLE;
   Double_t        nu_tau_TRUETAU;
   Bool_t          nu_tau_OSCIL;
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
   TBranch        *b_chi_c1_1P_MC_MOTHER_ID;   //!
   TBranch        *b_chi_c1_1P_MC_MOTHER_KEY;   //!
   TBranch        *b_chi_c1_1P_MC_GD_MOTHER_ID;   //!
   TBranch        *b_chi_c1_1P_MC_GD_MOTHER_KEY;   //!
   TBranch        *b_chi_c1_1P_MC_GD_GD_MOTHER_ID;   //!
   TBranch        *b_chi_c1_1P_MC_GD_GD_MOTHER_KEY;   //!
   TBranch        *b_chi_c1_1P_TRUEP_E;   //!
   TBranch        *b_chi_c1_1P_TRUEP_X;   //!
   TBranch        *b_chi_c1_1P_TRUEP_Y;   //!
   TBranch        *b_chi_c1_1P_TRUEP_Z;   //!
   TBranch        *b_chi_c1_1P_TRUEPT;   //!
   TBranch        *b_chi_c1_1P_TRUEORIGINVERTEX_X;   //!
   TBranch        *b_chi_c1_1P_TRUEORIGINVERTEX_Y;   //!
   TBranch        *b_chi_c1_1P_TRUEORIGINVERTEX_Z;   //!
   TBranch        *b_chi_c1_1P_TRUEENDVERTEX_X;   //!
   TBranch        *b_chi_c1_1P_TRUEENDVERTEX_Y;   //!
   TBranch        *b_chi_c1_1P_TRUEENDVERTEX_Z;   //!
   TBranch        *b_chi_c1_1P_TRUEISSTABLE;   //!
   TBranch        *b_chi_c1_1P_TRUETAU;   //!
   TBranch        *b_chi_c1_1P_OSCIL;   //!
   TBranch        *b_tauplus_MC_MOTHER_ID;   //!
   TBranch        *b_tauplus_MC_MOTHER_KEY;   //!
   TBranch        *b_tauplus_MC_GD_MOTHER_ID;   //!
   TBranch        *b_tauplus_MC_GD_MOTHER_KEY;   //!
   TBranch        *b_tauplus_MC_GD_GD_MOTHER_ID;   //!
   TBranch        *b_tauplus_MC_GD_GD_MOTHER_KEY;   //!
   TBranch        *b_tauplus_TRUEP_E;   //!
   TBranch        *b_tauplus_TRUEP_X;   //!
   TBranch        *b_tauplus_TRUEP_Y;   //!
   TBranch        *b_tauplus_TRUEP_Z;   //!
   TBranch        *b_tauplus_TRUEPT;   //!
   TBranch        *b_tauplus_TRUEORIGINVERTEX_X;   //!
   TBranch        *b_tauplus_TRUEORIGINVERTEX_Y;   //!
   TBranch        *b_tauplus_TRUEORIGINVERTEX_Z;   //!
   TBranch        *b_tauplus_TRUEENDVERTEX_X;   //!
   TBranch        *b_tauplus_TRUEENDVERTEX_Y;   //!
   TBranch        *b_tauplus_TRUEENDVERTEX_Z;   //!
   TBranch        *b_tauplus_TRUEISSTABLE;   //!
   TBranch        *b_tauplus_TRUETAU;   //!
   TBranch        *b_tauplus_OSCIL;   //!
   TBranch        *b_nu_tau_MC_MOTHER_ID;   //!
   TBranch        *b_nu_tau_MC_MOTHER_KEY;   //!
   TBranch        *b_nu_tau_MC_GD_MOTHER_ID;   //!
   TBranch        *b_nu_tau_MC_GD_MOTHER_KEY;   //!
   TBranch        *b_nu_tau_MC_GD_GD_MOTHER_ID;   //!
   TBranch        *b_nu_tau_MC_GD_GD_MOTHER_KEY;   //!
   TBranch        *b_nu_tau_TRUEP_E;   //!
   TBranch        *b_nu_tau_TRUEP_X;   //!
   TBranch        *b_nu_tau_TRUEP_Y;   //!
   TBranch        *b_nu_tau_TRUEP_Z;   //!
   TBranch        *b_nu_tau_TRUEPT;   //!
   TBranch        *b_nu_tau_TRUEORIGINVERTEX_X;   //!
   TBranch        *b_nu_tau_TRUEORIGINVERTEX_Y;   //!
   TBranch        *b_nu_tau_TRUEORIGINVERTEX_Z;   //!
   TBranch        *b_nu_tau_TRUEENDVERTEX_X;   //!
   TBranch        *b_nu_tau_TRUEENDVERTEX_Y;   //!
   TBranch        *b_nu_tau_TRUEENDVERTEX_Z;   //!
   TBranch        *b_nu_tau_TRUEISSTABLE;   //!
   TBranch        *b_nu_tau_TRUETAU;   //!
   TBranch        *b_nu_tau_OSCIL;   //!
   TBranch        *b_nCandidate;   //!
   TBranch        *b_totCandidates;   //!
   TBranch        *b_EventInSequence;   //!

   Chic1FFPlotter(TTree * /*tree*/ =0) : fChain(0) { }
   virtual ~Chic1FFPlotter() { }
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

   ClassDef(Chic1FFPlotter,0);
};

#endif

#ifdef Chic1FFPlotter_cxx
void Chic1FFPlotter::Init(TTree *tree)
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
   fChain->SetBranchAddress("chi_c1_1P_MC_MOTHER_ID", &chi_c1_1P_MC_MOTHER_ID, &b_chi_c1_1P_MC_MOTHER_ID);
   fChain->SetBranchAddress("chi_c1_1P_MC_MOTHER_KEY", &chi_c1_1P_MC_MOTHER_KEY, &b_chi_c1_1P_MC_MOTHER_KEY);
   fChain->SetBranchAddress("chi_c1_1P_MC_GD_MOTHER_ID", &chi_c1_1P_MC_GD_MOTHER_ID, &b_chi_c1_1P_MC_GD_MOTHER_ID);
   fChain->SetBranchAddress("chi_c1_1P_MC_GD_MOTHER_KEY", &chi_c1_1P_MC_GD_MOTHER_KEY, &b_chi_c1_1P_MC_GD_MOTHER_KEY);
   fChain->SetBranchAddress("chi_c1_1P_MC_GD_GD_MOTHER_ID", &chi_c1_1P_MC_GD_GD_MOTHER_ID, &b_chi_c1_1P_MC_GD_GD_MOTHER_ID);
   fChain->SetBranchAddress("chi_c1_1P_MC_GD_GD_MOTHER_KEY", &chi_c1_1P_MC_GD_GD_MOTHER_KEY, &b_chi_c1_1P_MC_GD_GD_MOTHER_KEY);
   fChain->SetBranchAddress("chi_c1_1P_TRUEP_E", &chi_c1_1P_TRUEP_E, &b_chi_c1_1P_TRUEP_E);
   fChain->SetBranchAddress("chi_c1_1P_TRUEP_X", &chi_c1_1P_TRUEP_X, &b_chi_c1_1P_TRUEP_X);
   fChain->SetBranchAddress("chi_c1_1P_TRUEP_Y", &chi_c1_1P_TRUEP_Y, &b_chi_c1_1P_TRUEP_Y);
   fChain->SetBranchAddress("chi_c1_1P_TRUEP_Z", &chi_c1_1P_TRUEP_Z, &b_chi_c1_1P_TRUEP_Z);
   fChain->SetBranchAddress("chi_c1_1P_TRUEPT", &chi_c1_1P_TRUEPT, &b_chi_c1_1P_TRUEPT);
   fChain->SetBranchAddress("chi_c1_1P_TRUEORIGINVERTEX_X", &chi_c1_1P_TRUEORIGINVERTEX_X, &b_chi_c1_1P_TRUEORIGINVERTEX_X);
   fChain->SetBranchAddress("chi_c1_1P_TRUEORIGINVERTEX_Y", &chi_c1_1P_TRUEORIGINVERTEX_Y, &b_chi_c1_1P_TRUEORIGINVERTEX_Y);
   fChain->SetBranchAddress("chi_c1_1P_TRUEORIGINVERTEX_Z", &chi_c1_1P_TRUEORIGINVERTEX_Z, &b_chi_c1_1P_TRUEORIGINVERTEX_Z);
   fChain->SetBranchAddress("chi_c1_1P_TRUEENDVERTEX_X", &chi_c1_1P_TRUEENDVERTEX_X, &b_chi_c1_1P_TRUEENDVERTEX_X);
   fChain->SetBranchAddress("chi_c1_1P_TRUEENDVERTEX_Y", &chi_c1_1P_TRUEENDVERTEX_Y, &b_chi_c1_1P_TRUEENDVERTEX_Y);
   fChain->SetBranchAddress("chi_c1_1P_TRUEENDVERTEX_Z", &chi_c1_1P_TRUEENDVERTEX_Z, &b_chi_c1_1P_TRUEENDVERTEX_Z);
   fChain->SetBranchAddress("chi_c1_1P_TRUEISSTABLE", &chi_c1_1P_TRUEISSTABLE, &b_chi_c1_1P_TRUEISSTABLE);
   fChain->SetBranchAddress("chi_c1_1P_TRUETAU", &chi_c1_1P_TRUETAU, &b_chi_c1_1P_TRUETAU);
   fChain->SetBranchAddress("chi_c1_1P_OSCIL", &chi_c1_1P_OSCIL, &b_chi_c1_1P_OSCIL);
   fChain->SetBranchAddress("tauplus_MC_MOTHER_ID", &tauplus_MC_MOTHER_ID, &b_tauplus_MC_MOTHER_ID);
   fChain->SetBranchAddress("tauplus_MC_MOTHER_KEY", &tauplus_MC_MOTHER_KEY, &b_tauplus_MC_MOTHER_KEY);
   fChain->SetBranchAddress("tauplus_MC_GD_MOTHER_ID", &tauplus_MC_GD_MOTHER_ID, &b_tauplus_MC_GD_MOTHER_ID);
   fChain->SetBranchAddress("tauplus_MC_GD_MOTHER_KEY", &tauplus_MC_GD_MOTHER_KEY, &b_tauplus_MC_GD_MOTHER_KEY);
   fChain->SetBranchAddress("tauplus_MC_GD_GD_MOTHER_ID", &tauplus_MC_GD_GD_MOTHER_ID, &b_tauplus_MC_GD_GD_MOTHER_ID);
   fChain->SetBranchAddress("tauplus_MC_GD_GD_MOTHER_KEY", &tauplus_MC_GD_GD_MOTHER_KEY, &b_tauplus_MC_GD_GD_MOTHER_KEY);
   fChain->SetBranchAddress("tauplus_TRUEP_E", &tauplus_TRUEP_E, &b_tauplus_TRUEP_E);
   fChain->SetBranchAddress("tauplus_TRUEP_X", &tauplus_TRUEP_X, &b_tauplus_TRUEP_X);
   fChain->SetBranchAddress("tauplus_TRUEP_Y", &tauplus_TRUEP_Y, &b_tauplus_TRUEP_Y);
   fChain->SetBranchAddress("tauplus_TRUEP_Z", &tauplus_TRUEP_Z, &b_tauplus_TRUEP_Z);
   fChain->SetBranchAddress("tauplus_TRUEPT", &tauplus_TRUEPT, &b_tauplus_TRUEPT);
   fChain->SetBranchAddress("tauplus_TRUEORIGINVERTEX_X", &tauplus_TRUEORIGINVERTEX_X, &b_tauplus_TRUEORIGINVERTEX_X);
   fChain->SetBranchAddress("tauplus_TRUEORIGINVERTEX_Y", &tauplus_TRUEORIGINVERTEX_Y, &b_tauplus_TRUEORIGINVERTEX_Y);
   fChain->SetBranchAddress("tauplus_TRUEORIGINVERTEX_Z", &tauplus_TRUEORIGINVERTEX_Z, &b_tauplus_TRUEORIGINVERTEX_Z);
   fChain->SetBranchAddress("tauplus_TRUEENDVERTEX_X", &tauplus_TRUEENDVERTEX_X, &b_tauplus_TRUEENDVERTEX_X);
   fChain->SetBranchAddress("tauplus_TRUEENDVERTEX_Y", &tauplus_TRUEENDVERTEX_Y, &b_tauplus_TRUEENDVERTEX_Y);
   fChain->SetBranchAddress("tauplus_TRUEENDVERTEX_Z", &tauplus_TRUEENDVERTEX_Z, &b_tauplus_TRUEENDVERTEX_Z);
   fChain->SetBranchAddress("tauplus_TRUEISSTABLE", &tauplus_TRUEISSTABLE, &b_tauplus_TRUEISSTABLE);
   fChain->SetBranchAddress("tauplus_TRUETAU", &tauplus_TRUETAU, &b_tauplus_TRUETAU);
   fChain->SetBranchAddress("tauplus_OSCIL", &tauplus_OSCIL, &b_tauplus_OSCIL);
   fChain->SetBranchAddress("nu_tau_MC_MOTHER_ID", &nu_tau_MC_MOTHER_ID, &b_nu_tau_MC_MOTHER_ID);
   fChain->SetBranchAddress("nu_tau_MC_MOTHER_KEY", &nu_tau_MC_MOTHER_KEY, &b_nu_tau_MC_MOTHER_KEY);
   fChain->SetBranchAddress("nu_tau_MC_GD_MOTHER_ID", &nu_tau_MC_GD_MOTHER_ID, &b_nu_tau_MC_GD_MOTHER_ID);
   fChain->SetBranchAddress("nu_tau_MC_GD_MOTHER_KEY", &nu_tau_MC_GD_MOTHER_KEY, &b_nu_tau_MC_GD_MOTHER_KEY);
   fChain->SetBranchAddress("nu_tau_MC_GD_GD_MOTHER_ID", &nu_tau_MC_GD_GD_MOTHER_ID, &b_nu_tau_MC_GD_GD_MOTHER_ID);
   fChain->SetBranchAddress("nu_tau_MC_GD_GD_MOTHER_KEY", &nu_tau_MC_GD_GD_MOTHER_KEY, &b_nu_tau_MC_GD_GD_MOTHER_KEY);
   fChain->SetBranchAddress("nu_tau_TRUEP_E", &nu_tau_TRUEP_E, &b_nu_tau_TRUEP_E);
   fChain->SetBranchAddress("nu_tau_TRUEP_X", &nu_tau_TRUEP_X, &b_nu_tau_TRUEP_X);
   fChain->SetBranchAddress("nu_tau_TRUEP_Y", &nu_tau_TRUEP_Y, &b_nu_tau_TRUEP_Y);
   fChain->SetBranchAddress("nu_tau_TRUEP_Z", &nu_tau_TRUEP_Z, &b_nu_tau_TRUEP_Z);
   fChain->SetBranchAddress("nu_tau_TRUEPT", &nu_tau_TRUEPT, &b_nu_tau_TRUEPT);
   fChain->SetBranchAddress("nu_tau_TRUEORIGINVERTEX_X", &nu_tau_TRUEORIGINVERTEX_X, &b_nu_tau_TRUEORIGINVERTEX_X);
   fChain->SetBranchAddress("nu_tau_TRUEORIGINVERTEX_Y", &nu_tau_TRUEORIGINVERTEX_Y, &b_nu_tau_TRUEORIGINVERTEX_Y);
   fChain->SetBranchAddress("nu_tau_TRUEORIGINVERTEX_Z", &nu_tau_TRUEORIGINVERTEX_Z, &b_nu_tau_TRUEORIGINVERTEX_Z);
   fChain->SetBranchAddress("nu_tau_TRUEENDVERTEX_X", &nu_tau_TRUEENDVERTEX_X, &b_nu_tau_TRUEENDVERTEX_X);
   fChain->SetBranchAddress("nu_tau_TRUEENDVERTEX_Y", &nu_tau_TRUEENDVERTEX_Y, &b_nu_tau_TRUEENDVERTEX_Y);
   fChain->SetBranchAddress("nu_tau_TRUEENDVERTEX_Z", &nu_tau_TRUEENDVERTEX_Z, &b_nu_tau_TRUEENDVERTEX_Z);
   fChain->SetBranchAddress("nu_tau_TRUEISSTABLE", &nu_tau_TRUEISSTABLE, &b_nu_tau_TRUEISSTABLE);
   fChain->SetBranchAddress("nu_tau_TRUETAU", &nu_tau_TRUETAU, &b_nu_tau_TRUETAU);
   fChain->SetBranchAddress("nu_tau_OSCIL", &nu_tau_OSCIL, &b_nu_tau_OSCIL);
   fChain->SetBranchAddress("nCandidate", &nCandidate, &b_nCandidate);
   fChain->SetBranchAddress("totCandidates", &totCandidates, &b_totCandidates);
   fChain->SetBranchAddress("EventInSequence", &EventInSequence, &b_EventInSequence);
}

Bool_t Chic1FFPlotter::Notify()
{
   // The Notify() function is called when a new file is opened. This
   // can be either for a new TTree in a TChain or when when a new TTree
   // is started when using PROOF. It is normally not necessary to make changes
   // to the generated code, but the routine can be extended by the
   // user if needed. The return value is currently not used.

   return kTRUE;
}

#endif // #ifdef Chic1FFPlotter_cxx
