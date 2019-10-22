#define JpsiTauMCSelector_cxx
// The class definition in JpsiTauMCSelector.h has been generated automatically
// by the ROOT utility TTree::MakeSelector(). This class is derived
// from the ROOT class TSelector. For more information on the TSelector
// framework see $ROOTSYS/README/README.SELECTOR or the ROOT User Manual.

// The following methods are defined in this file:
//    Begin():        called every time a loop on the tree starts,
//                    a convenient place to create your histograms.
//    SlaveBegin():   called after Begin(), when on PROOF called only on the
//                    slave servers.
//    Process():      called for each event, in this function you decide what
//                    to read and fill your histograms.
//    SlaveTerminate: called at the end of the loop on the tree, when on PROOF
//                    called only on the slave servers.
//    Terminate():    called at the end of the loop on the tree,
//                    a convenient place to draw/fit your histograms.
//
// To use this file, try the following session on your Tree T:
//
// Root > T->Process("JpsiTauMCSelector.C")
// Root > T->Process("JpsiTauMCSelector.C","some options")
// Root > T->Process("JpsiTauMCSelector.C+")
//

#include "JpsiTauMCSelector.h"
#include <TH2.h>
#include <TStyle.h>
#include <TMath.h>
#include <TVector3.h>
#include <TLorentzVector.h>


void JpsiTauMCSelector::Begin(TTree * /*tree*/)
{
  // The Begin() function is called at the start of the query.
  // When running with PROOF Begin() is only called on the client.
  // The tree argument is deprecated (on PROOF 0 is passed).

  // Get Options
  TString option = GetOption();
  TIterator* iterList = fInput->MakeIterator();
  fDataset = iterList->Next()->GetName(); // of course, this is "JpsiTauNu"

  // Histograms
  Lifetime_Histo = new TH1F("Lifetime_Histo","Lifetime_Histo",100,0,6);
  Q2_Histo = new TH1F("Q2_Histo","Q2_Histo",100,0,10.5);
  EL_Histo = new TH1F("EL_Histo","EL_Histo",100,1.7,2.15);
  CosTheta_Histo = new TH1F("CosTheta_Histo","CosTheta_Histo",100,-1,1);

}

void JpsiTauMCSelector::SlaveBegin(TTree * /*tree*/)
{
  // The SlaveBegin() function is called after the Begin() function.
  // When running with PROOF SlaveBegin() is called on each slave server.
  // The tree argument is deprecated (on PROOF 0 is passed).

  TString option = GetOption();

}

Bool_t JpsiTauMCSelector::Process(Long64_t entry)
{
  // The Process() function is called for each entry in the tree (or possibly
  // keyed object in the case of PROOF) to be processed. The entry argument
  // specifies which entry in the currently loaded tree is to be processed.
  // It can be passed to either JpsiTauMCSelector::GetEntry() or TBranch::GetEntry()
  // to read either all or the required parts of the data. When processing
  // keyed objects with PROOF, the object is already loaded and is available
  // via the fObject pointer.
  //
  // This function should contain the "body" of the analysis. It can contain
  // simple or elaborate selection criteria, run algorithms on the data
  // of the event and typically fill histograms.
  //
  // The processing can be stopped by calling Abort().
  //
  // Use fStatus to set the return value of TTree::Process().
  //
  // The return value is currently not used.


  fChain->GetTree()->GetEntry(entry);
  
  // -------------------------
  // TRIGGER VETO
  // -------------------------

  // TRIGGER TOS CUTS

  Bool_t PASSTRIGGER = true;
  if (not (L0MuonDecision or L0DiMuonDecision)) PASSTRIGGER = false;
  if (not (Hlt1DiMuonHighMassDecision or Hlt1DiMuonLowMassDecision)) PASSTRIGGER = false;
  if (not (Hlt2DiMuonJPsiHighPTDecision)) PASSTRIGGER = false;
  if (not (StrippingFullDSTDiMuonJpsi2MuMuDetachedLineDecision)) PASSTRIGGER = false;
  if (not PASSTRIGGER) {
    return kTRUE;
  }

  // --------
  // LIFETIME
  // --------
  
  Double_t Lifetime = Bc_TRUETAU * 1000;
  Lifetime_Histo->Fill(Lifetime);

  // --------
  // CM FRAME
  // --------

  // FOUR-MOMENTA
  TLorentzVector JpsiP;
  JpsiP.SetXYZT(Jpsi_TRUEP_X * 1.0e-3,
                Jpsi_TRUEP_Y * 1.0e-3,
                Jpsi_TRUEP_Z * 1.0e-3,
                Jpsi_TRUEP_E * 1.0e-3);
  
  TLorentzVector TauP;
  TauP.SetXYZT(Tau_TRUEP_X * 1.0e-3,
               Tau_TRUEP_Y * 1.0e-3,
               Tau_TRUEP_Z * 1.0e-3,
               Tau_TRUEP_E * 1.0e-3);
  
  TLorentzVector BcP;
  BcP.SetXYZT(Bc_TRUEP_X * 1.0e-3,
              Bc_TRUEP_Y * 1.0e-3,
              Bc_TRUEP_Z * 1.0e-3,
              Bc_TRUEP_E * 1.0e-3);
  
  TLorentzVector WP = BcP - JpsiP;
  
  // BOOST
  TVector3 boost = WP.BoostVector();
  JpsiP.Boost(-boost);
  TauP.Boost(-boost);
  BcP.Boost(-boost);
  WP.Boost(-boost);
  
  // Q2
  Double_t Q2 = WP.M2();
  Q2_Histo->Fill(Q2);
  
    // EL
  Double_t EL = TauP.E();
  EL_Histo->Fill(EL);
  
// COS THETA
  TVector3 v = -1*JpsiP.Vect();
  Double_t Theta = TauP.Angle(v);
  Double_t CosTheta = cos(Theta);
  CosTheta_Histo->Fill(CosTheta);
  
  return kTRUE;
}

void JpsiTauMCSelector::SlaveTerminate()
{
  // The SlaveTerminate() function is called after all entries or objects
  // have been processed. When running with PROOF SlaveTerminate() is called
  // on each slave server.

}

void JpsiTauMCSelector::Terminate()
{
  // The Terminate() function is the last function to be called during
  // a query. It always runs on the client, it can be used to present
  // the results graphically or save the results to file.

  TString outRootname = root_dict[fDataset] + "_HISTOGRAMS.root";
  OutFile = new TFile(outRootname,"UPDATE");
  
  OutFile->Add(Lifetime_Histo);
  OutFile->Add(Q2_Histo);
  OutFile->Add(EL_Histo);
  OutFile->Add(CosTheta_Histo);
  
  Lifetime_Histo->Write();
  Q2_Histo->Write();
  EL_Histo->Write();
  CosTheta_Histo->Write(); 

  OutFile->Close();
}
