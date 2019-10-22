#define Psi2S_GaussTruth_Selector_cxx
// The class definition in Psi2S_GaussTruth_Selector.h has been generated automatically
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
// Root > T->Process("Psi2S_GaussTruth_Selector.C")
// Root > T->Process("Psi2S_GaussTruth_Selector.C","some options")
// Root > T->Process("Psi2S_GaussTruth_Selector.C+")
//

#include "Psi2S_GaussTruth_Selector.h"
#include <TH2.h>
#include <TStyle.h>
#include <TLorentzVector.h>
#include <TVector3.h>

#include <iostream>

const double Bc_PDG_M = 6277.0;
const double psi2S_PDG_M = 3686.11;
const double Mu_PDG_M = 105.6584;
const double min_SomeMu_PT = 1000;
const double min_BachMu_PT = 300.0; // >99.9% are, because of selection / stripping / tigger
const double max_BachMu_PT = 8000.0; // >99.9% are
const double min_MuMP_PT = 0.0;
const double min_Bc_MM = psi2S_PDG_M + Mu_PDG_M; // can't be below this -- should this be relaxed?
const double max_Bc_MM = Bc_PDG_M; // can't be above this -- should this be relaxed?
const double min_B_MM = 5151; // mu - 3*sigma, found by fitting peak before cut
const double max_B_MM = 5311; // mu + 3*sigma


void Psi2S_GaussTruth_Selector::Begin(TTree * /*tree*/)
{
  // The Begin() function is called at the start of the query.
  // When running with PROOF Begin() is only called on the client.
  // The tree argument is deprecated (on PROOF 0 is passed).

  TString option = GetOption();

  OutFile = new TFile("psi2S_GaussTruth_Cands.root","RECREATE");
  OutChain = new TTree("DecayTree","DecayTree");
  OutChain->Branch("BachMu_MCCTAU",&BachMu_MCCTAU);
  OutChain->Branch("BachMu_MCE",&BachMu_MCE);
  OutChain->Branch("BachMu_MCETA",&BachMu_MCETA);
  OutChain->Branch("BachMu_MCP",&BachMu_MCP);
  OutChain->Branch("BachMu_MCPHI",&BachMu_MCPHI);
  OutChain->Branch("BachMu_MCPT",&BachMu_MCPT);
  OutChain->Branch("BachMu_MCPX",&BachMu_MCPX);
  OutChain->Branch("BachMu_MCPY",&BachMu_MCPY);
  OutChain->Branch("BachMu_MCPZ",&BachMu_MCPZ);
  OutChain->Branch("BachMu_MCTHETA",&BachMu_MCTHETA);
  OutChain->Branch("psi2S_MCCTAU",&psi2S_MCCTAU);
  OutChain->Branch("psi2S_MCE",&psi2S_MCE);
  OutChain->Branch("psi2S_MCETA",&psi2S_MCETA);
  OutChain->Branch("psi2S_MCP",&psi2S_MCP);
  OutChain->Branch("psi2S_MCPHI",&psi2S_MCPHI);
  OutChain->Branch("psi2S_MCPT",&psi2S_MCPT);
  OutChain->Branch("psi2S_MCPX",&psi2S_MCPX);
  OutChain->Branch("psi2S_MCPY",&psi2S_MCPY);
  OutChain->Branch("psi2S_MCPZ",&psi2S_MCPZ);
  OutChain->Branch("psi2S_MCTHETA",&psi2S_MCTHETA);

  // "RECONSTRUCTED" (add the four momenta)
  OutChain->Branch("Y_MCMM",&Y_MCMM);
  OutChain->Branch("Y_MCE",&Y_MCE);
  OutChain->Branch("Y_MCP",&Y_MCP);
  OutChain->Branch("Y_MCPT",&Y_MCPT);
  OutChain->Branch("Y_MCPX",&Y_MCPX);
  OutChain->Branch("Y_MCPY",&Y_MCPY);
  OutChain->Branch("Y_MCPZ",&Y_MCPZ);
  OutChain->Branch("Y_MCETA",&Y_MCETA);
  OutChain->Branch("Y_MCTHETA",&Y_MCTHETA);
  OutChain->Branch("Y_MCPHI",&Y_MCPHI);

  OutChain->Branch("MissMass2",&MissMass2);
  OutChain->Branch("BachMuEnergy",&BachMuEnergy);
  OutChain->Branch("Q2",&Q2);
  OutChain->Branch("Lifetime",&Lifetime);

}

void Psi2S_GaussTruth_Selector::SlaveBegin(TTree * /*tree*/)
{
  // The SlaveBegin() function is called after the Begin() function.
  // When running with PROOF SlaveBegin() is called on each slave server.
  // The tree argument is deprecated (on PROOF 0 is passed).

  TString option = GetOption();

}

Bool_t Psi2S_GaussTruth_Selector::Process(Long64_t entry)
{
  // The Process() function is called for each entry in the tree (or possibly
  // keyed object in the case of PROOF) to be processed. The entry argument
  // specifies which entry in the currently loaded tree is to be processed.
  // It can be passed to either Psi2S_GaussTruth_Selector::GetEntry() or TBranch::GetEntry()
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

  // SIMULATED CUTS
  if (!BachMu_ACC) return kTRUE;
  if (!MuP_ACC) return kTRUE;
  if (!MuM_ACC) return kTRUE;
  
  // CUTS THAT REPLICATE TRIGGER / STRIPPING LINE CUTS
  if (std::max(std::max(BachMu_MCPT,MuP_MCPT),MuM_MCPT) < min_SomeMu_PT) return kTRUE;

  // KINEMATIC CUTS
  if (BachMu_MCPT < min_BachMu_PT) return kTRUE;
  if (BachMu_MCPT > max_BachMu_PT) return kTRUE;
  if (MuM_MCPT < min_MuMP_PT) return kTRUE;
  if (MuP_MCPT < min_MuMP_PT) return kTRUE;

  // MAKE THE Y
  TLorentzVector psi2S;
  psi2S.SetXYZT(psi2S_MCPX,
               psi2S_MCPY,
               psi2S_MCPZ,
               psi2S_MCE); 
  TLorentzVector BachMu;
  BachMu.SetXYZT(BachMu_MCPX,
               BachMu_MCPY,
               BachMu_MCPZ,
               BachMu_MCE); 
  TLorentzVector Y = psi2S + BachMu;
  Y_MCMM = Y.M();
  Y_MCE = Y.E();
  Y_MCP = Y.Rho();
  Y_MCPX = Y.Px();
  Y_MCPY = Y.Py();
  Y_MCPZ = Y.Pz();
  Y_MCPT = TMath::Sqrt(Y_MCPX*Y_MCPX + Y_MCPY*Y_MCPY);
  Y_MCETA = Y.Eta();
  Y_MCTHETA = Y.Theta();
  Y_MCPHI = Y.Phi();
  
            
  // CUTS TO CLEAN UP DATASET
//   if (Y_MCMM < min_Bc_MM) return kTRUE;  
//   if (Y_MCMM > max_Bc_MM) return kTRUE;  

  // ESTIMATE THE BC MOMENTUM
  // Pretend that I got the flight direction perfectly
  TLorentzVector Bc;
  Bc.SetXYZT(Bc_MCPX,
            Bc_MCPY,
            Bc_MCPZ,
            Bc_MCE);
  TVector3 Flight = Bc.Vect();
  Flight = Flight.Unit();
  Double_t TanTheta = Flight.Perp()/(Flight.Z());

  // Estimated missing momentum
  double pt_est = (Bc_PDG_M)/(Y_MCMM)*TanTheta*Y_MCPZ;
  TLorentzVector BcP_est;
  BcP_est.SetPtEtaPhiM(pt_est,
                       Flight.Eta(),
                       Flight.Phi(),
                       Bc_PDG_M);
  TVector3 BcEstBoost = BcP_est.BoostVector();
  Momentum = BcP_est.Rho();

  // MISSING MASS SQUARED
  TLorentzVector missMom_est = BcP_est - Y;
  MissMass2 = missMom_est.M2();
  MissMass2 /= 1.0e6;

  // LEPTON ENERGY
  TLorentzVector BachMuP_cm = BachMu;
  BachMuP_cm.Boost(-BcEstBoost);
  BachMuEnergy = BachMuP_cm.Energy();
  BachMuEnergy /= 1.0e3;

  // Q^2
  TLorentzVector Nu_cm = missMom_est; Nu_cm.Boost(-BcEstBoost);
  TLorentzVector BachMuNu_cm = BachMuP_cm + Nu_cm;
  Q2 = BachMuNu_cm.M2();
  Q2 /= 1.0e6;

  OutChain->Fill();
  
  return kTRUE;
}

void Psi2S_GaussTruth_Selector::SlaveTerminate()
{
  // The SlaveTerminate() function is called after all entries or objects
  // have been processed. When running with PROOF SlaveTerminate() is called
  // on each slave server.

}

void Psi2S_GaussTruth_Selector::Terminate()
{
  // The Terminate() function is the last function to be called during
  // a query. It always runs on the client, it can be used to present
  // the results graphically or save the results to file.

  OutFile->Add(OutChain);
  OutChain->Write();
  delete OutChain;
  OutFile->Close();
  //  delete OutFile;

}
