#define Jpsi_GaussTruth_Selector_cxx
// The class definition in Jpsi_GaussTruth_Selector.h has been generated automatically
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
// Root > T->Process("Jpsi_GaussTruth_Selector.C")
// Root > T->Process("Jpsi_GaussTruth_Selector.C","some options")
// Root > T->Process("Jpsi_GaussTruth_Selector.C+")
//

#include "Jpsi_GaussTruth_Selector.h"
#include <TH2.h>
#include <TStyle.h>
#include <TLorentzVector.h>
#include <TVector3.h>

#include <iostream>

const double Bc_PDG_M = 6277.0;
const double Jpsi_PDG_M = 3096.916;
const double Mu_PDG_M = 105.6584;
const double min_SomeMu_PT = 1000;
const double min_BachMu_PT = 300.0; // >99.9% are, because of selection / stripping / tigger
const double max_BachMu_PT = 8000.0; // >99.9% are
const double min_MuMP_PT = 0.0;
const double min_Bc_MM = Jpsi_PDG_M + Mu_PDG_M; // can't be below this -- should this be relaxed?
const double max_Bc_MM = Bc_PDG_M; // can't be above this -- should this be relaxed?
const double min_B_MM = 5151; // mu - 3*sigma, found by fitting peak before cut
const double max_B_MM = 5311; // mu + 3*sigma


void Jpsi_GaussTruth_Selector::Begin(TTree * /*tree*/)
{
  // The Begin() function is called at the start of the query.
  // When running with PROOF Begin() is only called on the client.
  // The tree argument is deprecated (on PROOF 0 is passed).

  TString option = GetOption();

  OutFile = new TFile("Mu_GaussTruth_Cands.root","RECREATE");
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
  OutChain->Branch("Jpsi_MCCTAU",&Jpsi_MCCTAU);
  OutChain->Branch("Jpsi_MCE",&Jpsi_MCE);
  OutChain->Branch("Jpsi_MCETA",&Jpsi_MCETA);
  OutChain->Branch("Jpsi_MCP",&Jpsi_MCP);
  OutChain->Branch("Jpsi_MCPHI",&Jpsi_MCPHI);
  OutChain->Branch("Jpsi_MCPT",&Jpsi_MCPT);
  OutChain->Branch("Jpsi_MCPX",&Jpsi_MCPX);
  OutChain->Branch("Jpsi_MCPY",&Jpsi_MCPY);
  OutChain->Branch("Jpsi_MCPZ",&Jpsi_MCPZ);
  OutChain->Branch("Jpsi_MCTHETA",&Jpsi_MCTHETA);

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
  OutChain->Branch("BcEst_sp_P",&BcEst_sp_P);
  OutChain->Branch("BcEst_sp_PT",&BcEst_sp_PT);
  OutChain->Branch("Bc_sp_P",&Bc_sp_P);
  OutChain->Branch("Bc_sp_PT",&Bc_sp_PT);
  OutChain->Branch("Nu_sp_P",&Nu_sp_P);
  OutChain->Branch("Nu_sp_PT",&Nu_sp_PT);
  OutChain->Branch("sp_Theta",&sp_Theta);

}

void Jpsi_GaussTruth_Selector::SlaveBegin(TTree * /*tree*/)
{
  // The SlaveBegin() function is called after the Begin() function.
  // When running with PROOF SlaveBegin() is called on each slave server.
  // The tree argument is deprecated (on PROOF 0 is passed).

  TString option = GetOption();

}

Bool_t Jpsi_GaussTruth_Selector::Process(Long64_t entry)
{
  // The Process() function is called for each entry in the tree (or possibly
  // keyed object in the case of PROOF) to be processed. The entry argument
  // specifies which entry in the currently loaded tree is to be processed.
  // It can be passed to either Jpsi_GaussTruth_Selector::GetEntry() or TBranch::GetEntry()
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
  TLorentzVector Jpsi;
  Jpsi.SetXYZT(Jpsi_MCPX,
               Jpsi_MCPY,
               Jpsi_MCPZ,
               Jpsi_MCE); 
  TLorentzVector BachMu;
  BachMu.SetXYZT(BachMu_MCPX,
                 BachMu_MCPY,
                 BachMu_MCPZ,
                 BachMu_MCE); 
  TLorentzVector Y = Jpsi + BachMu;
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
  
  TLorentzVector Nu;
  Nu.SetXYZT(NuMu_MCPX,
             NuMu_MCPY,
             NuMu_MCPZ,
             NuMu_MCE);
  
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

  // WHICH NEUTRINO SOLUTION IS IT?
  TVector3 Y_sp_proj3D = (Flight.Dot(Y.Vect()))*Flight;
  TLorentzVector Y_sp_proj;
  //  Y_sp_proj.SetVectM(Y_sp_proj3D,Y_MCMM);
  Y_sp_proj.SetXYZT(Y_sp_proj3D.Px(),
                    Y_sp_proj3D.Py(),
                    Y_sp_proj3D.Pz(),
                    Y_MCE);
  
  TVector3 boost = Y_sp_proj.BoostVector();
  TLorentzVector BcEst_sp = BcP_est; BcEst_sp.Boost(-boost);
  TLorentzVector Bc_sp = Bc; Bc_sp.Boost(-boost);
  TLorentzVector Y_sp = Y; Y_sp.Boost(-boost);
  TLorentzVector Nu_sp = Nu; Nu_sp.Boost(-boost);

  TVector3 Y_dir = Y_sp.Vect(); Y_dir = Y_dir.Unit();
  cout << Y_dir.Dot(Flight) << endl;
  TVector3 Y3 = Y_sp.Vect();
  TVector3 BcEst3 = BcEst_sp.Vect();
  TVector3 Bc3 = Bc_sp.Vect();
  TVector3 Nu3 = Nu_sp.Vect();
  
  
  // Now we want to save the Bc momentum and neutrino properties in this frame
  BcEst_sp_PT = BcEst3.Dot(Y_dir); // should be 0
  BcEst_sp_P = BcEst3.Dot(Flight);
  Bc_sp_PT = Bc3.Dot(Y_dir); // should be 0
  Bc_sp_P = Bc3.Dot(Flight);
  Nu_sp_PT = Nu3.Dot(Y_dir);
  Nu_sp_P = Nu3.Dot(Flight);
  sp_Theta = Bc3.Angle(Nu3);

  OutChain->Fill();
  
  return kTRUE;
}

void Jpsi_GaussTruth_Selector::SlaveTerminate()
{
  // The SlaveTerminate() function is called after all entries or objects
  // have been processed. When running with PROOF SlaveTerminate() is called
  // on each slave server.

}

void Jpsi_GaussTruth_Selector::Terminate()
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
