#define FFSelector_cxx
// The class definition in FFSelector.h has been generated automatically
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
// Root > T->Process("FFSelector.C")
// Root > T->Process("FFSelector.C","some options")
// Root > T->Process("FFSelector.C+")
//

#include "FFSelector.h"
#include <iostream>
#include <TH2.h>
#include <TStyle.h>
#include <TH1F.h>
#include <TCanvas.h>
#include <TLorentzVector.h>
#include <TVector3.h>

void FFSelector::Begin(TTree * /*tree*/)
{
  // The Begin() function is called at the start of the query.
  // When running with PROOF Begin() is only called on the client.
  // The tree argument is deprecated (on PROOF 0 is passed).

  angleHisto = new TH1F("angleHisto","angleHisto",100,-1,1);

  TString option = GetOption();

}

void FFSelector::SlaveBegin(TTree * /*tree*/)
{
  // The SlaveBegin() function is called after the Begin() function.
  // When running with PROOF SlaveBegin() is called on each slave server.
  // The tree argument is deprecated (on PROOF 0 is passed).

  TString option = GetOption();

}

Bool_t FFSelector::Process(Long64_t entry)
{
  // The Process() function is called for each entry in the tree (or possibly
  // keyed object in the case of PROOF) to be processed. The entry argument
  // specifies which entry in the currently loaded tree is to be processed.
  // It can be passed to either FFSelector::GetEntry() or TBranch::GetEntry()
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

  // FOUR-MOMENTA
  TLorentzVector TrueJpsiP;
  TrueJpsiP.SetXYZT(Jpsi_TRUEP_X * 1.0e-3,
                    Jpsi_TRUEP_Y * 1.0e-3,
                    Jpsi_TRUEP_Z * 1.0e-3,
                    Jpsi_TRUEP_E * 1.0e-3);
    
  TLorentzVector TrueTauP;
  TrueTauP.SetXYZT(Tau_TRUEP_X * 1.0e-3,
                   Tau_TRUEP_Y * 1.0e-3,
                   Tau_TRUEP_Z * 1.0e-3,
                   Tau_TRUEP_E * 1.0e-3);
  
  TLorentzVector TrueBcP;
  TrueBcP.SetXYZT(Bc_TRUEP_X * 1.0e-3,
                  Bc_TRUEP_Y * 1.0e-3,
                  Bc_TRUEP_Z * 1.0e-3,
                  Bc_TRUEP_E * 1.0e-3);

  TLorentzVector TrueWP = TrueBcP - TrueJpsiP;

  std::cout << TrueJpsiP.Rho() << " , " << TrueTauP.Rho() << endl;

  // CM
  TVector3 boost = TrueWP.BoostVector();
  TrueJpsiP.Boost(-boost);
  TrueTauP.Boost(-boost);
  std::cout << TrueJpsiP.Rho() << " , " << TrueTauP.Rho() << endl;

  TVector3 v = TrueJpsiP.Vect();
  Double_t TrueTheta = TrueTauP.Angle(v);
  Double_t TrueCosTheta = cos(TrueTheta);
  std::cout << TrueTheta << " --> " << TrueCosTheta << std::endl;
  
  angleHisto->Fill(TrueCosTheta);
  return kTRUE;  
}

void FFSelector::SlaveTerminate()
{
  // The SlaveTerminate() function is called after all entries or objects
  // have been processed. When running with PROOF SlaveTerminate() is called
  // on each slave server.

  TCanvas* c1 = new TCanvas("c1","c1",800,600);
  c1->cd();
  angleHisto->Draw("E");
}

void FFSelector::Terminate()
{
  // The Terminate() function is the last function to be called during
  // a query. It always runs on the client, it can be used to present
  // the results graphically or save the results to file.

}
