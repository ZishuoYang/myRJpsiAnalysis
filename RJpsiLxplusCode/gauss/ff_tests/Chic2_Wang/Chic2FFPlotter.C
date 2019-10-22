#define Chic2FFPlotter_cxx
// The class definition in Chic2FFPlotter.h has been generated automatically
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
// Root > T->Process("Chic2FFPlotter.C")
// Root > T->Process("Chic2FFPlotter.C","some options")
// Root > T->Process("Chic2FFPlotter.C+")
//

#include "Chic2FFPlotter.h"
#include <TH2.h>
#include <TStyle.h>


void Chic2FFPlotter::Begin(TTree * /*tree*/)
{
   // The Begin() function is called at the start of the query.
   // When running with PROOF Begin() is only called on the client.
   // The tree argument is deprecated (on PROOF 0 is passed).

  angleHisto = new TH1F("angleHisto","angleHisto",100,-1,1);
  elepHisto = new TH1F("elepHisto","elepHisto",100,0.0,1.5);
  q2Histo = new TH1F("q2Histo","q2Histo",100,0.0,8);

  TString option = GetOption();

}

void Chic2FFPlotter::SlaveBegin(TTree * /*tree*/)
{
   // The SlaveBegin() function is called after the Begin() function.
   // When running with PROOF SlaveBegin() is called on each slave server.
   // The tree argument is deprecated (on PROOF 0 is passed).

   TString option = GetOption();

}

Bool_t Chic2FFPlotter::Process(Long64_t entry)
{
   // The Process() function is called for each entry in the tree (or possibly
   // keyed object in the case of PROOF) to be processed. The entry argument
   // specifies which entry in the currently loaded tree is to be processed.
   // It can be passed to either Chic2FFPlotter::GetEntry() or TBranch::GetEntry()
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
  TLorentzVector TrueChiP;
  TrueChiP.SetXYZT(chi_c2_1P_TRUEP_X * 1.0e-3,
                   chi_c2_1P_TRUEP_Y * 1.0e-3,
                   chi_c2_1P_TRUEP_Z * 1.0e-3,
                   chi_c2_1P_TRUEP_E * 1.0e-3);
    
  TLorentzVector TrueLepP;
  TrueLepP.SetXYZT(muplus_TRUEP_X * 1.0e-3,
                   muplus_TRUEP_Y * 1.0e-3,
                   muplus_TRUEP_Z * 1.0e-3,
                   muplus_TRUEP_E * 1.0e-3);
  
  TLorentzVector TrueBcP;
  TrueBcP.SetXYZT(B_cplus_TRUEP_X * 1.0e-3,
                  B_cplus_TRUEP_Y * 1.0e-3,
                  B_cplus_TRUEP_Z * 1.0e-3,
                  B_cplus_TRUEP_E * 1.0e-3);

  TLorentzVector TrueWP = TrueBcP - TrueChiP;


  // CM
  TVector3 boost = TrueWP.BoostVector();
  TrueChiP.Boost(-boost);
  TrueLepP.Boost(-boost);

  TVector3 v = TrueChiP.Vect();
  Double_t TrueTheta = TrueLepP.Angle(v);
  Double_t TrueCosTheta = -1*cos(TrueTheta);
  Double_t TrueElep = TrueLepP.E();
  Double_t TrueQ2 = TrueWP.M2();

  angleHisto->Fill(TrueCosTheta);
  elepHisto->Fill(TrueElep);
  q2Histo->Fill(TrueQ2);

  return kTRUE;
}

void Chic2FFPlotter::SlaveTerminate()
{
   // The SlaveTerminate() function is called after all entries or objects
   // have been processed. When running with PROOF SlaveTerminate() is called
   // on each slave server.

}

void Chic2FFPlotter::Terminate()
{
   // The Terminate() function is the last function to be called during
   // a query. It always runs on the client, it can be used to present
   // the results graphically or save the results to file.
  TFile outputfile("chic2_wang_ffhistos_2.root","RECREATE");
  outputfile.cd();
  q2Histo->Write();
  elepHisto->Write();
  angleHisto->Write();
  outputfile.Write();

}
