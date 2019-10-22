#define RecSelector_cxx
// The class definition in RecSelector.h has been generated automatically
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
// Root > T->Process("RecSelector.C")
// Root > T->Process("RecSelector.C","some options")
// Root > T->Process("RecSelector.C+")
//

#include "RecSelector.h"
#include <TIterator.h>
#include <TStyle.h>
#include <TString.h>
#include <TMath.h>

#include <iostream>
using std::cout;
using std::endl;

#include <algorithm>
#include <map>
#include <string>
#include <cassert>


void RecSelector::Begin(TTree * /*tree*/)
{
  // The Begin() function is called at the start of the query.
  // When running with PROOF Begin() is only called on the client.
  // The tree argument is deprecated (on PROOF 0 is passed).

  // Get Options
  TString option = GetOption();
  TIterator* iterList = fInput->MakeIterator();
  fDataset = iterList->Next()->GetName();

  // Histograms
  KSub_MM_Histo = new TH1F("KSub_MM_Histo","KSub_MM_Histo",100,5450,5800);
  PiSub_MM_Histo = new TH1F("PiSub_MM_Histo","PiSub_MM_Histo",100,5100,5450);
  CDM_MM_Histo = new TH1F("CDM_MM","CDM_MM",100,2996.916,3196.916);
  SS_Angle_Histo = new TH1F("SS_Angle","SS_Angle",100,-50.0,0.0);
  OS_Angle_Histo = new TH1F("OS_Angle","OS_Angle",100,-50.0,0.0);

}

void RecSelector::SlaveBegin(TTree * /*tree*/)
{
  // The SlaveBegin() function is called after the Begin() function.
  // When running with PROOF SlaveBegin() is called on each slave server.
  // The tree argument is deprecated (on PROOF 0 is passed).

  TString option = GetOption();

}

Bool_t RecSelector::Process(Long64_t entry)
{
  // The Process() function is called for each entry in the tree (or possibly
  // keyed object in the case of PROOF) to be processed. The entry argument
  // specifies which entry in the currently loaded tree is to be processed.
  // It can be passed to either RecSelector::GetEntry() or TBranch::GetEntry()
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
  if (not (Jpsi_L0MuonDecision_TOS or Jpsi_L0DiMuonDecision_TOS)) PASSTRIGGER = false;
  if (not (Jpsi_Hlt1DiMuonHighMassDecision_TOS or Jpsi_Hlt1DiMuonLowMassDecision_TOS)) PASSTRIGGER = false;
  if (not (Jpsi_Hlt2DiMuonJPsiHighPTDecision_TOS)) PASSTRIGGER = false;
  if (not PASSTRIGGER) {
    return kTRUE;
  }
  
  // Better BachMu_P
  Double_t bmp2 = ((Bc_PX-Jpsi_PX)*(Bc_PX-Jpsi_PX)
                   + (Bc_PY-Jpsi_PY)*(Bc_PY-Jpsi_PY)
                   + (Bc_PZ-Jpsi_PZ)*(Bc_PZ-Jpsi_PZ));

  // B -> Jpsi K mass window veto
  Double_t MK = 493.677;
  Double_t MuIsK_PE = TMath::Sqrt(MK*MK + bmp2);
  Double_t KSub_MM = TMath::Sqrt((MuIsK_PE+Jpsi_PE)*(MuIsK_PE+Jpsi_PE) - Bc_P*Bc_P);
  KSub_MM_Histo->Fill(KSub_MM);
  
  // B -> Jpsi Pi mass window veto
  Double_t MPI = 139.57018;
  Double_t MuIsPi_PE = TMath::Sqrt(MPI*MPI + bmp2);
  Double_t PiSub_MM = TMath::Sqrt((MuIsPi_PE+Jpsi_PE)*(MuIsPi_PE+Jpsi_PE) - Bc_P*Bc_P);
  PiSub_MM_Histo->Fill(PiSub_MM);

  // Cross DiMuon mass window veto
  Double_t CDM_MM =
    TMath::Sqrt((BachMu_PE+MuM_PE)*(BachMu_PE+MuM_PE)
                -(BachMu_PX+MuM_PX)*(BachMu_PX+MuM_PX)
                -(BachMu_PY+MuM_PY)*(BachMu_PY+MuM_PY)
                -(BachMu_PZ+MuM_PZ)*(BachMu_PZ+MuM_PZ));
  CDM_MM_Histo->Fill(CDM_MM);

  // BachMu / MuP angle
  Double_t SScos = (BachMu_PX*MuP_PX + BachMu_PY*MuP_PY + BachMu_PZ*MuP_PZ)/(BachMu_P*MuP_P);
  Double_t OScos = (BachMu_PX*MuM_PX + BachMu_PY*MuM_PY + BachMu_PZ*MuM_PZ)/(BachMu_P*MuM_P);
  Double_t LogSScos = log(1.0-SScos);
  Double_t LogOScos = log(1.0-OScos);
  cout << "SSCOS = " << LogSScos << endl;
  cout << "OSCOS = " << LogOScos << endl;
  SS_Angle_Histo->Fill(LogSScos);
  OS_Angle_Histo->Fill(LogOScos);
  
  
  return kTRUE;
}

void RecSelector::SlaveTerminate()
{
  // The SlaveTerminate() function is called after all entries or objects
  // have been processed. When running with PROOF SlaveTerminate() is called
  // on each slave server.

}

void RecSelector::Terminate()
{
  // The Terminate() function is the last function to be called during
  // a query. It always runs on the client, it can be used to present
  // the results graphically or save the results to file.
  
  TString outRootname = root_dict[fDataset] + "_HISTOGRAMS.root";
  OutFile = new TFile(outRootname,"RECREATE");

  OutFile->Add(KSub_MM_Histo);
  OutFile->Add(PiSub_MM_Histo);
  OutFile->Add(CDM_MM_Histo);
  OutFile->Add(SS_Angle_Histo);
  OutFile->Add(OS_Angle_Histo);
  
  KSub_MM_Histo->Write();
  PiSub_MM_Histo->Write();
  CDM_MM_Histo->Write();
  SS_Angle_Histo->Write();
  OS_Angle_Histo->Write();

  OutFile->Close();
}

