//////////////////////////////////////////////////////////
// This class has been automatically generated on
// Tue Jul  2 17:44:22 2013 by ROOT version 5.34/07
// from TTree DecayTree/DecayTree
// found on file: Bc_SIG_Mu.root
//////////////////////////////////////////////////////////

#ifndef RecSelector_h
#define RecSelector_h

#include <TROOT.h>
#include <TChain.h>
#include <TFile.h>
#include <TSelector.h>
#include <TString.h>
#include <TH1F.h>

// Header file for the classes stored in the TTree if any.
#include "BcConstants.h"

// Fixed size dimensions of array or collections stored in the TTree if any.
const Int_t kMaxBc_ENDVERTEX_COV = 1;
const Int_t kMaxBc_OWNPV_COV = 1;
const Int_t kMaxBachMu_OWNPV_COV = 1;
const Int_t kMaxBachMu_ORIVX_COV = 1;
const Int_t kMaxJpsi_ENDVERTEX_COV = 1;
const Int_t kMaxJpsi_OWNPV_COV = 1;
const Int_t kMaxJpsi_ORIVX_COV = 1;
const Int_t kMaxMuM_OWNPV_COV = 1;
const Int_t kMaxMuM_ORIVX_COV = 1;
const Int_t kMaxMuP_OWNPV_COV = 1;
const Int_t kMaxMuP_ORIVX_COV = 1;

class RecSelector : public TSelector {
public :
  TTree          *fChain;   //!pointer to the analyzed TTree or TChain
  TFile          *OutFile;

  // OPTIONS / DATASET
  TString        fDataset;

  // HISTOGRAMS
  TH1F* KSub_MM_Histo;
  TH1F* PiSub_MM_Histo;
  TH1F* CDM_MM_Histo;
  TH1F* SS_Angle_Histo;
  TH1F* OS_Angle_Histo;

  // Declaration of leaf types
  Double_t        Bc_ENDVERTEX_X;
  Double_t        Bc_ENDVERTEX_Y;
  Double_t        Bc_ENDVERTEX_Z;
  Double_t        Bc_ENDVERTEX_XERR;
  Double_t        Bc_ENDVERTEX_YERR;
  Double_t        Bc_ENDVERTEX_ZERR;
  Double_t        Bc_ENDVERTEX_CHI2;
  Int_t           Bc_ENDVERTEX_NDOF;
  Float_t         Bc_ENDVERTEX_COV_[3][3];
  Double_t        Bc_OWNPV_X;
  Double_t        Bc_OWNPV_Y;
  Double_t        Bc_OWNPV_Z;
  Double_t        Bc_OWNPV_XERR;
  Double_t        Bc_OWNPV_YERR;
  Double_t        Bc_OWNPV_ZERR;
  Double_t        Bc_OWNPV_CHI2;
  Int_t           Bc_OWNPV_NDOF;
  Float_t         Bc_OWNPV_COV_[3][3];
  Double_t        Bc_IP_OWNPV;
  Double_t        Bc_IPCHI2_OWNPV;
  Double_t        Bc_FD_OWNPV;
  Double_t        Bc_FDCHI2_OWNPV;
  Double_t        Bc_DIRA_OWNPV;
  Double_t        Bc_P;
  Double_t        Bc_PT;
  Double_t        Bc_PE;
  Double_t        Bc_PX;
  Double_t        Bc_PY;
  Double_t        Bc_PZ;
  Double_t        Bc_MM;
  Double_t        Bc_MMERR;
  Double_t        Bc_M;
  Int_t           Bc_TRUEID;
  Int_t           Bc_MC_MOTHER_ID;
  Int_t           Bc_MC_MOTHER_KEY;
  Int_t           Bc_MC_GD_MOTHER_ID;
  Int_t           Bc_MC_GD_MOTHER_KEY;
  Int_t           Bc_MC_GD_GD_MOTHER_ID;
  Int_t           Bc_MC_GD_GD_MOTHER_KEY;
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
  Int_t           Bc_ID;
  Double_t        Bc_B2JpsiK;
  Double_t        Bc_B2JpsiPi;
  Double_t        Bc_Bc2JpsiMuNu;
  Double_t        Bc_Bc2JpsiTauNu;
  Double_t        Bc_Bc2Psi2SMuNu;
  Double_t        Bc_Bc2Psi2STauNu;
  Double_t        Bc_Bm2CCEta;
  Double_t        Bc_Bm2CCEtaP;
  Double_t        Bc_Bm2CCF0;
  Double_t        Bc_Bm2CCK;
  Double_t        Bc_Bm2CCK1270;
  Double_t        Bc_Bm2CCK1400;
  Double_t        Bc_Bm2CCK892;
  Double_t        Bc_Bm2CCK892Pi;
  Double_t        Bc_Bm2CCK892PiPi;
  Double_t        Bc_Bm2CCKEta;
  Double_t        Bc_Bm2CCKEtaP;
  Double_t        Bc_Bm2CCKOmega;
  Double_t        Bc_Bm2CCKPhi;
  Double_t        Bc_Bm2CCKPi;
  Double_t        Bc_Bm2CCKPiPi;
  Double_t        Bc_Bm2CCKRho;
  Double_t        Bc_Bm2CCOmega;
  Double_t        Bc_Bm2CCPhi;
  Double_t        Bc_Bm2CCPi;
  Double_t        Bc_Bm2CCPiPi;
  Double_t        Bc_Bm2CCRho;
  Double_t        Bc_ChiC0X;
  Double_t        Bc_ChiC1X;
  Double_t        Bc_ChiC2X;
  Double_t        Bc_DOCA;
  Double_t        Bc_DOCACHI2;
  Double_t        Bc_IsABc;
  Double_t        Bc_IsABc_star;
  Double_t        Bc_IsABd;
  Double_t        Bc_IsABd_star;
  Double_t        Bc_IsABs;
  Double_t        Bc_IsABs_star;
  Double_t        Bc_IsABu;
  Double_t        Bc_IsABu_star;
  Double_t        Bc_JpsiX;
  Double_t        Bc_Psi2S2JpsiPiPi;
  Double_t        Bc_Psi2SX;
  Int_t           Bc_BKGCAT;
  Int_t           BachMu_TRACK_Type;
  Int_t           BachMu_TRACK_Key;
  Double_t        BachMu_TRACK_CHI2NDOF;
  Double_t        BachMu_TRACK_PCHI2;
  Double_t        BachMu_TRACK_MatchCHI2;
  Double_t        BachMu_TRACK_GhostProb;
  Double_t        BachMu_TRACK_CloneDist;
  Double_t        BachMu_TRACK_Likelihood;
  Bool_t          BachMu_InMuonAcc;
  Double_t        BachMu_MuonDist2;
  Int_t           BachMu_NShared;
  Double_t        BachMu_MuonLLmu;
  Double_t        BachMu_MuonLLbg;  
  Int_t           BachMu_regionInM2;
  Double_t        BachMu_CombDLLMu;
  Double_t        BachMu_TrueK2Mu;
  Double_t        BachMu_TruePi2Mu;
  Double_t        BachMu_TrueMu;
  Double_t        BachMu_TrueMuFromK;
  Double_t        BachMu_TrueMuFromPi;
  Double_t        BachMu_OWNPV_X;
  Double_t        BachMu_OWNPV_Y;
  Double_t        BachMu_OWNPV_Z;
  Double_t        BachMu_OWNPV_XERR;
  Double_t        BachMu_OWNPV_YERR;
  Double_t        BachMu_OWNPV_ZERR;
  Double_t        BachMu_OWNPV_CHI2;
  Int_t           BachMu_OWNPV_NDOF;
  Float_t         BachMu_OWNPV_COV_[3][3];
  Double_t        BachMu_IP_OWNPV;
  Double_t        BachMu_IPCHI2_OWNPV;
  Double_t        BachMu_ORIVX_X;
  Double_t        BachMu_ORIVX_Y;
  Double_t        BachMu_ORIVX_Z;
  Double_t        BachMu_ORIVX_XERR;
  Double_t        BachMu_ORIVX_YERR;
  Double_t        BachMu_ORIVX_ZERR;
  Double_t        BachMu_ORIVX_CHI2;
  Int_t           BachMu_ORIVX_NDOF;
  Float_t         BachMu_ORIVX_COV_[3][3];
  Double_t        BachMu_P;
  Double_t        BachMu_PT;
  Double_t        BachMu_PE;
  Double_t        BachMu_PX;
  Double_t        BachMu_PY;
  Double_t        BachMu_PZ;
  Double_t        BachMu_M;
  Int_t           BachMu_TRUEID;
  Int_t           BachMu_MC_MOTHER_ID;
  Int_t           BachMu_MC_MOTHER_KEY;
  Int_t           BachMu_MC_GD_MOTHER_ID;
  Int_t           BachMu_MC_GD_MOTHER_KEY;
  Int_t           BachMu_MC_GD_GD_MOTHER_ID;
  Int_t           BachMu_MC_GD_GD_MOTHER_KEY;
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
  Int_t           BachMu_ID;
  Double_t        BachMu_PIDe;
  Double_t        BachMu_PIDmu;
  Double_t        BachMu_PIDK;
  Double_t        BachMu_PIDp;
  Double_t        BachMu_ProbNNe;
  Double_t        BachMu_ProbNNk;
  Double_t        BachMu_ProbNNp;
  Double_t        BachMu_ProbNNpi;
  Double_t        BachMu_ProbNNmu;
  Double_t        BachMu_ProbNNghost;
  Bool_t          BachMu_hasMuon;
  Bool_t          BachMu_isMuon;
  Bool_t          BachMu_hasRich;
  Bool_t          BachMu_hasCalo;
  Double_t        Jpsi_ENDVERTEX_X;
  Double_t        Jpsi_ENDVERTEX_Y;
  Double_t        Jpsi_ENDVERTEX_Z;
  Double_t        Jpsi_ENDVERTEX_XERR;
  Double_t        Jpsi_ENDVERTEX_YERR;
  Double_t        Jpsi_ENDVERTEX_ZERR;
  Double_t        Jpsi_ENDVERTEX_CHI2;
  Int_t           Jpsi_ENDVERTEX_NDOF;
  Float_t         Jpsi_ENDVERTEX_COV_[3][3];
  Double_t        Jpsi_OWNPV_X;
  Double_t        Jpsi_OWNPV_Y;
  Double_t        Jpsi_OWNPV_Z;
  Double_t        Jpsi_OWNPV_XERR;
  Double_t        Jpsi_OWNPV_YERR;
  Double_t        Jpsi_OWNPV_ZERR;
  Double_t        Jpsi_OWNPV_CHI2;
  Int_t           Jpsi_OWNPV_NDOF;
  Float_t         Jpsi_OWNPV_COV_[3][3];
  Double_t        Jpsi_IP_OWNPV;
  Double_t        Jpsi_IPCHI2_OWNPV;
  Double_t        Jpsi_FD_OWNPV;
  Double_t        Jpsi_FDCHI2_OWNPV;
  Double_t        Jpsi_DIRA_OWNPV;
  Double_t        Jpsi_ORIVX_X;
  Double_t        Jpsi_ORIVX_Y;
  Double_t        Jpsi_ORIVX_Z;
  Double_t        Jpsi_ORIVX_XERR;
  Double_t        Jpsi_ORIVX_YERR;
  Double_t        Jpsi_ORIVX_ZERR;
  Double_t        Jpsi_ORIVX_CHI2;
  Int_t           Jpsi_ORIVX_NDOF;
  Float_t         Jpsi_ORIVX_COV_[3][3];
  Double_t        Jpsi_FD_ORIVX;
  Double_t        Jpsi_FDCHI2_ORIVX;
  Double_t        Jpsi_DIRA_ORIVX;
  Double_t        Jpsi_P;
  Double_t        Jpsi_PT;
  Double_t        Jpsi_PE;
  Double_t        Jpsi_PX;
  Double_t        Jpsi_PY;
  Double_t        Jpsi_PZ;
  Double_t        Jpsi_MM;
  Double_t        Jpsi_MMERR;
  Double_t        Jpsi_M;
  Int_t           Jpsi_TRUEID;
  Int_t           Jpsi_MC_MOTHER_ID;
  Int_t           Jpsi_MC_MOTHER_KEY;
  Int_t           Jpsi_MC_GD_MOTHER_ID;
  Int_t           Jpsi_MC_GD_MOTHER_KEY;
  Int_t           Jpsi_MC_GD_GD_MOTHER_ID;
  Int_t           Jpsi_MC_GD_GD_MOTHER_KEY;
  Double_t        Jpsi_TRUEP_E;
  Double_t        Jpsi_TRUEP_X;
  Double_t        Jpsi_TRUEP_Y;
  Double_t        Jpsi_TRUEP_Z;
  Double_t        Jpsi_TRUEPT;
  Double_t        Jpsi_TRUEORIGINVERTEX_X;
  Double_t        Jpsi_TRUEORIGINVERTEX_Y;
  Double_t        Jpsi_TRUEORIGINVERTEX_Z;
  Double_t        Jpsi_TRUEENDVERTEX_X;
  Double_t        Jpsi_TRUEENDVERTEX_Y;
  Double_t        Jpsi_TRUEENDVERTEX_Z;
  Bool_t          Jpsi_TRUEISSTABLE;
  Double_t        Jpsi_TRUETAU;
  Int_t           Jpsi_ID;
  Int_t           Jpsi_BKGCAT;
  Bool_t          Jpsi_L0Global_Dec;
  Bool_t          Jpsi_L0Global_TIS;
  Bool_t          Jpsi_L0Global_TOS;
  Bool_t          Jpsi_Hlt1Global_Dec;
  Bool_t          Jpsi_Hlt1Global_TIS;
  Bool_t          Jpsi_Hlt1Global_TOS;
  Bool_t          Jpsi_Hlt1Phys_Dec;
  Bool_t          Jpsi_Hlt1Phys_TIS;
  Bool_t          Jpsi_Hlt1Phys_TOS;
  Bool_t          Jpsi_Hlt2Global_Dec;
  Bool_t          Jpsi_Hlt2Global_TIS;
  Bool_t          Jpsi_Hlt2Global_TOS;
  Bool_t          Jpsi_Hlt2Phys_Dec;
  Bool_t          Jpsi_Hlt2Phys_TIS;
  Bool_t          Jpsi_Hlt2Phys_TOS;
  Bool_t          Jpsi_L0MuonDecision_Dec;
  Bool_t          Jpsi_L0MuonDecision_TIS;
  Bool_t          Jpsi_L0MuonDecision_TOS;
  Bool_t          Jpsi_L0DiMuonDecision_Dec;
  Bool_t          Jpsi_L0DiMuonDecision_TIS;
  Bool_t          Jpsi_L0DiMuonDecision_TOS;
  Bool_t          Jpsi_Hlt1DiMuonHighMassDecision_Dec;
  Bool_t          Jpsi_Hlt1DiMuonHighMassDecision_TIS;
  Bool_t          Jpsi_Hlt1DiMuonHighMassDecision_TOS;
  Bool_t          Jpsi_Hlt1DiMuonLowMassDecision_Dec;
  Bool_t          Jpsi_Hlt1DiMuonLowMassDecision_TIS;
  Bool_t          Jpsi_Hlt1DiMuonLowMassDecision_TOS;
  Bool_t          Jpsi_Hlt2DiMuonJPsiHighPTDecision_Dec;
  Bool_t          Jpsi_Hlt2DiMuonJPsiHighPTDecision_TIS;
  Bool_t          Jpsi_Hlt2DiMuonJPsiHighPTDecision_TOS;
  Double_t        MuM_OWNPV_X;
  Double_t        MuM_OWNPV_Y;
  Double_t        MuM_OWNPV_Z;
  Double_t        MuM_OWNPV_XERR;
  Double_t        MuM_OWNPV_YERR;
  Double_t        MuM_OWNPV_ZERR;
  Double_t        MuM_OWNPV_CHI2;
  Int_t           MuM_OWNPV_NDOF;
  Float_t         MuM_OWNPV_COV_[3][3];
  Double_t        MuM_IP_OWNPV;
  Double_t        MuM_IPCHI2_OWNPV;
  Double_t        MuM_ORIVX_X;
  Double_t        MuM_ORIVX_Y;
  Double_t        MuM_ORIVX_Z;
  Double_t        MuM_ORIVX_XERR;
  Double_t        MuM_ORIVX_YERR;
  Double_t        MuM_ORIVX_ZERR;
  Double_t        MuM_ORIVX_CHI2;
  Int_t           MuM_ORIVX_NDOF;
  Float_t         MuM_ORIVX_COV_[3][3];
  Double_t        MuM_P;
  Double_t        MuM_PT;
  Double_t        MuM_PE;
  Double_t        MuM_PX;
  Double_t        MuM_PY;
  Double_t        MuM_PZ;
  Double_t        MuM_M;
  Int_t           MuM_TRUEID;
  Int_t           MuM_MC_MOTHER_ID;
  Int_t           MuM_MC_MOTHER_KEY;
  Int_t           MuM_MC_GD_MOTHER_ID;
  Int_t           MuM_MC_GD_MOTHER_KEY;
  Int_t           MuM_MC_GD_GD_MOTHER_ID;
  Int_t           MuM_MC_GD_GD_MOTHER_KEY;
  Double_t        MuM_TRUEP_E;
  Double_t        MuM_TRUEP_X;
  Double_t        MuM_TRUEP_Y;
  Double_t        MuM_TRUEP_Z;
  Double_t        MuM_TRUEPT;
  Double_t        MuM_TRUEORIGINVERTEX_X;
  Double_t        MuM_TRUEORIGINVERTEX_Y;
  Double_t        MuM_TRUEORIGINVERTEX_Z;
  Double_t        MuM_TRUEENDVERTEX_X;
  Double_t        MuM_TRUEENDVERTEX_Y;
  Double_t        MuM_TRUEENDVERTEX_Z;
  Bool_t          MuM_TRUEISSTABLE;
  Double_t        MuM_TRUETAU;
  Int_t           MuM_ID;
  Double_t        MuM_PIDe;
  Double_t        MuM_PIDmu;
  Double_t        MuM_PIDK;
  Double_t        MuM_PIDp;
  Double_t        MuM_ProbNNe;
  Double_t        MuM_ProbNNk;
  Double_t        MuM_ProbNNp;
  Double_t        MuM_ProbNNpi;
  Double_t        MuM_ProbNNmu;
  Double_t        MuM_ProbNNghost;
  Bool_t          MuM_hasMuon;
  Bool_t          MuM_isMuon;
  Bool_t          MuM_hasRich;
  Bool_t          MuM_hasCalo;
  Int_t           MuM_TRACK_Type;
  Int_t           MuM_TRACK_Key;
  Double_t        MuM_TRACK_CHI2NDOF;
  Double_t        MuM_TRACK_PCHI2;
  Double_t        MuM_TRACK_MatchCHI2;
  Double_t        MuM_TRACK_GhostProb;
  Double_t        MuM_TRACK_CloneDist;
  Double_t        MuM_TRACK_Likelihood;
  Double_t        MuP_OWNPV_X;
  Double_t        MuP_OWNPV_Y;
  Double_t        MuP_OWNPV_Z;
  Double_t        MuP_OWNPV_XERR;
  Double_t        MuP_OWNPV_YERR;
  Double_t        MuP_OWNPV_ZERR;
  Double_t        MuP_OWNPV_CHI2;
  Int_t           MuP_OWNPV_NDOF;
  Float_t         MuP_OWNPV_COV_[3][3];
  Double_t        MuP_IP_OWNPV;
  Double_t        MuP_IPCHI2_OWNPV;
  Double_t        MuP_ORIVX_X;
  Double_t        MuP_ORIVX_Y;
  Double_t        MuP_ORIVX_Z;
  Double_t        MuP_ORIVX_XERR;
  Double_t        MuP_ORIVX_YERR;
  Double_t        MuP_ORIVX_ZERR;
  Double_t        MuP_ORIVX_CHI2;
  Int_t           MuP_ORIVX_NDOF;
  Float_t         MuP_ORIVX_COV_[3][3];
  Double_t        MuP_P;
  Double_t        MuP_PT;
  Double_t        MuP_PE;
  Double_t        MuP_PX;
  Double_t        MuP_PY;
  Double_t        MuP_PZ;
  Double_t        MuP_M;
  Int_t           MuP_TRUEID;
  Int_t           MuP_MC_MOTHER_ID;
  Int_t           MuP_MC_MOTHER_KEY;
  Int_t           MuP_MC_GD_MOTHER_ID;
  Int_t           MuP_MC_GD_MOTHER_KEY;
  Int_t           MuP_MC_GD_GD_MOTHER_ID;
  Int_t           MuP_MC_GD_GD_MOTHER_KEY;
  Double_t        MuP_TRUEP_E;
  Double_t        MuP_TRUEP_X;
  Double_t        MuP_TRUEP_Y;
  Double_t        MuP_TRUEP_Z;
  Double_t        MuP_TRUEPT;
  Double_t        MuP_TRUEORIGINVERTEX_X;
  Double_t        MuP_TRUEORIGINVERTEX_Y;
  Double_t        MuP_TRUEORIGINVERTEX_Z;
  Double_t        MuP_TRUEENDVERTEX_X;
  Double_t        MuP_TRUEENDVERTEX_Y;
  Double_t        MuP_TRUEENDVERTEX_Z;
  Bool_t          MuP_TRUEISSTABLE;
  Double_t        MuP_TRUETAU;
  Int_t           MuP_ID;
  Double_t        MuP_PIDe;
  Double_t        MuP_PIDmu;
  Double_t        MuP_PIDK;
  Double_t        MuP_PIDp;
  Double_t        MuP_ProbNNe;
  Double_t        MuP_ProbNNk;
  Double_t        MuP_ProbNNp;
  Double_t        MuP_ProbNNpi;
  Double_t        MuP_ProbNNmu;
  Double_t        MuP_ProbNNghost;
  Bool_t          MuP_hasMuon;
  Bool_t          MuP_isMuon;
  Bool_t          MuP_hasRich;
  Bool_t          MuP_hasCalo;
  Int_t           MuP_TRACK_Type;
  Int_t           MuP_TRACK_Key;
  Double_t        MuP_TRACK_CHI2NDOF;
  Double_t        MuP_TRACK_PCHI2;
  Double_t        MuP_TRACK_MatchCHI2;
  Double_t        MuP_TRACK_GhostProb;
  Double_t        MuP_TRACK_CloneDist;
  Double_t        MuP_TRACK_Likelihood;
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
  Double_t        nTracks;

  // List of branches
  TBranch        *b_Bc_ENDVERTEX_X;   //!
  TBranch        *b_Bc_ENDVERTEX_Y;   //!
  TBranch        *b_Bc_ENDVERTEX_Z;   //!
  TBranch        *b_Bc_ENDVERTEX_XERR;   //!
  TBranch        *b_Bc_ENDVERTEX_YERR;   //!
  TBranch        *b_Bc_ENDVERTEX_ZERR;   //!
  TBranch        *b_Bc_ENDVERTEX_CHI2;   //!
  TBranch        *b_Bc_ENDVERTEX_NDOF;   //!
  TBranch        *b_Bc_ENDVERTEX_COV_;   //!
  TBranch        *b_Bc_OWNPV_X;   //!
  TBranch        *b_Bc_OWNPV_Y;   //!
  TBranch        *b_Bc_OWNPV_Z;   //!
  TBranch        *b_Bc_OWNPV_XERR;   //!
  TBranch        *b_Bc_OWNPV_YERR;   //!
  TBranch        *b_Bc_OWNPV_ZERR;   //!
  TBranch        *b_Bc_OWNPV_CHI2;   //!
  TBranch        *b_Bc_OWNPV_NDOF;   //!
  TBranch        *b_Bc_OWNPV_COV_;   //!
  TBranch        *b_Bc_IP_OWNPV;   //!
  TBranch        *b_Bc_IPCHI2_OWNPV;   //!
  TBranch        *b_Bc_FD_OWNPV;   //!
  TBranch        *b_Bc_FDCHI2_OWNPV;   //!
  TBranch        *b_Bc_DIRA_OWNPV;   //!
  TBranch        *b_Bc_P;   //!
  TBranch        *b_Bc_PT;   //!
  TBranch        *b_Bc_PE;   //!
  TBranch        *b_Bc_PX;   //!
  TBranch        *b_Bc_PY;   //!
  TBranch        *b_Bc_PZ;   //!
  TBranch        *b_Bc_MM;   //!
  TBranch        *b_Bc_MMERR;   //!
  TBranch        *b_Bc_M;   //!
  TBranch        *b_Bc_TRUEID;   //!
  TBranch        *b_Bc_MC_MOTHER_ID;   //!
  TBranch        *b_Bc_MC_MOTHER_KEY;   //!
  TBranch        *b_Bc_MC_GD_MOTHER_ID;   //!
  TBranch        *b_Bc_MC_GD_MOTHER_KEY;   //!
  TBranch        *b_Bc_MC_GD_GD_MOTHER_ID;   //!
  TBranch        *b_Bc_MC_GD_GD_MOTHER_KEY;   //!
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
  TBranch        *b_Bc_ID;   //!
  TBranch        *b_Bc_DOCA;
  TBranch        *b_Bc_DOCACHI2;
  TBranch        *b_Bc_B2JpsiK;   //!
  TBranch        *b_Bc_B2JpsiPi;   //!
  TBranch        *b_Bc_Bc2JpsiMuNu;   //!
  TBranch        *b_Bc_Bc2JpsiTauNu;   //!
  TBranch        *b_Bc_Bc2Psi2SMuNu;   //!
  TBranch        *b_Bc_Bc2Psi2STauNu;   //!
  TBranch        *b_Bc_Bm2CCEta;   //!
  TBranch        *b_Bc_Bm2CCEtaP;   //!
  TBranch        *b_Bc_Bm2CCF0;   //!
  TBranch        *b_Bc_Bm2CCK;   //!
  TBranch        *b_Bc_Bm2CCK1270;   //!
  TBranch        *b_Bc_Bm2CCK1400;   //!
  TBranch        *b_Bc_Bm2CCK892;   //!
  TBranch        *b_Bc_Bm2CCK892Pi;   //!
  TBranch        *b_Bc_Bm2CCK892PiPi;   //!
  TBranch        *b_Bc_Bm2CCKEta;   //!
  TBranch        *b_Bc_Bm2CCKEtaP;   //!
  TBranch        *b_Bc_Bm2CCKOmega;   //!
  TBranch        *b_Bc_Bm2CCKPhi;   //!
  TBranch        *b_Bc_Bm2CCKPi;   //!
  TBranch        *b_Bc_Bm2CCKPiPi;   //!
  TBranch        *b_Bc_Bm2CCKRho;   //!
  TBranch        *b_Bc_Bm2CCOmega;   //!
  TBranch        *b_Bc_Bm2CCPhi;   //!
  TBranch        *b_Bc_Bm2CCPi;   //!
  TBranch        *b_Bc_Bm2CCPiPi;   //!
  TBranch        *b_Bc_Bm2CCRho;   //!
  TBranch        *b_Bc_ChiC0X;   //!
  TBranch        *b_Bc_ChiC1X;   //!
  TBranch        *b_Bc_ChiC2X;   //!
  TBranch        *b_Bc_IsABc;   //!
  TBranch        *b_Bc_IsABc_star;   //!
  TBranch        *b_Bc_IsABd;   //!
  TBranch        *b_Bc_IsABd_star;   //!
  TBranch        *b_Bc_IsABs;   //!
  TBranch        *b_Bc_IsABs_star;   //!
  TBranch        *b_Bc_IsABu;   //!
  TBranch        *b_Bc_IsABu_star;   //!
  TBranch        *b_Bc_JpsiX;   //!
  TBranch        *b_Bc_Psi2S2JpsiPiPi;   //!
  TBranch        *b_Bc_Psi2SX;   //!
  TBranch        *b_Bc_BKGCAT;   //!
  TBranch        *b_BachMu_TRACK_Type;   //!
  TBranch        *b_BachMu_TRACK_Key;   //!
  TBranch        *b_BachMu_TRACK_CHI2NDOF;   //!
  TBranch        *b_BachMu_TRACK_PCHI2;   //!
  TBranch        *b_BachMu_TRACK_MatchCHI2;   //!
  TBranch        *b_BachMu_TRACK_GhostProb;   //!
  TBranch        *b_BachMu_TRACK_CloneDist;   //!
  TBranch        *b_BachMu_TRACK_Likelihood;   //!

  TBranch        *b_BachMu_InMuonAcc;
  TBranch        *b_BachMu_MuonDist2;
  TBranch        *b_BachMu_NShared;
  TBranch        *b_BachMu_MuonLLmu;
  TBranch        *b_BachMu_MuonLLbg;  
  TBranch        *b_BachMu_regionInM2;
  TBranch        *b_BachMu_CombDLLMu;


  TBranch        *b_BachMu_TrueK2Mu;   //!
  TBranch        *b_BachMu_TruePi2Mu;   //!
  TBranch        *b_BachMu_TrueMu;   //!
  TBranch        *b_BachMu_TrueMuFromK;   //!
  TBranch        *b_BachMu_TrueMuFromPi;   //!
  TBranch        *b_BachMu_OWNPV_X;   //!
  TBranch        *b_BachMu_OWNPV_Y;   //!
  TBranch        *b_BachMu_OWNPV_Z;   //!
  TBranch        *b_BachMu_OWNPV_XERR;   //!
  TBranch        *b_BachMu_OWNPV_YERR;   //!
  TBranch        *b_BachMu_OWNPV_ZERR;   //!
  TBranch        *b_BachMu_OWNPV_CHI2;   //!
  TBranch        *b_BachMu_OWNPV_NDOF;   //!
  TBranch        *b_BachMu_OWNPV_COV_;   //!
  TBranch        *b_BachMu_IP_OWNPV;   //!
  TBranch        *b_BachMu_IPCHI2_OWNPV;   //!
  TBranch        *b_BachMu_ORIVX_X;   //!
  TBranch        *b_BachMu_ORIVX_Y;   //!
  TBranch        *b_BachMu_ORIVX_Z;   //!
  TBranch        *b_BachMu_ORIVX_XERR;   //!
  TBranch        *b_BachMu_ORIVX_YERR;   //!
  TBranch        *b_BachMu_ORIVX_ZERR;   //!
  TBranch        *b_BachMu_ORIVX_CHI2;   //!
  TBranch        *b_BachMu_ORIVX_NDOF;   //!
  TBranch        *b_BachMu_ORIVX_COV_;   //!
  TBranch        *b_BachMu_P;   //!
  TBranch        *b_BachMu_PT;   //!
  TBranch        *b_BachMu_PE;   //!
  TBranch        *b_BachMu_PX;   //!
  TBranch        *b_BachMu_PY;   //!
  TBranch        *b_BachMu_PZ;   //!
  TBranch        *b_BachMu_M;   //!
  TBranch        *b_BachMu_TRUEID;   //!
  TBranch        *b_BachMu_MC_MOTHER_ID;   //!
  TBranch        *b_BachMu_MC_MOTHER_KEY;   //!
  TBranch        *b_BachMu_MC_GD_MOTHER_ID;   //!
  TBranch        *b_BachMu_MC_GD_MOTHER_KEY;   //!
  TBranch        *b_BachMu_MC_GD_GD_MOTHER_ID;   //!
  TBranch        *b_BachMu_MC_GD_GD_MOTHER_KEY;   //!
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
  TBranch        *b_BachMu_ID;   //!
  TBranch        *b_BachMu_PIDe;   //!
  TBranch        *b_BachMu_PIDmu;   //!
  TBranch        *b_BachMu_PIDK;   //!
  TBranch        *b_BachMu_PIDp;   //!
  TBranch        *b_BachMu_ProbNNe;   //!
  TBranch        *b_BachMu_ProbNNk;   //!
  TBranch        *b_BachMu_ProbNNp;   //!
  TBranch        *b_BachMu_ProbNNpi;   //!
  TBranch        *b_BachMu_ProbNNmu;   //!
  TBranch        *b_BachMu_ProbNNghost;   //!
  TBranch        *b_BachMu_hasMuon;   //!
  TBranch        *b_BachMu_isMuon;   //!
  TBranch        *b_BachMu_hasRich;   //!
  TBranch        *b_BachMu_hasCalo;   //!
  TBranch        *b_Jpsi_ENDVERTEX_X;   //!
  TBranch        *b_Jpsi_ENDVERTEX_Y;   //!
  TBranch        *b_Jpsi_ENDVERTEX_Z;   //!
  TBranch        *b_Jpsi_ENDVERTEX_XERR;   //!
  TBranch        *b_Jpsi_ENDVERTEX_YERR;   //!
  TBranch        *b_Jpsi_ENDVERTEX_ZERR;   //!
  TBranch        *b_Jpsi_ENDVERTEX_CHI2;   //!
  TBranch        *b_Jpsi_ENDVERTEX_NDOF;   //!
  TBranch        *b_Jpsi_ENDVERTEX_COV_;   //!
  TBranch        *b_Jpsi_OWNPV_X;   //!
  TBranch        *b_Jpsi_OWNPV_Y;   //!
  TBranch        *b_Jpsi_OWNPV_Z;   //!
  TBranch        *b_Jpsi_OWNPV_XERR;   //!
  TBranch        *b_Jpsi_OWNPV_YERR;   //!
  TBranch        *b_Jpsi_OWNPV_ZERR;   //!
  TBranch        *b_Jpsi_OWNPV_CHI2;   //!
  TBranch        *b_Jpsi_OWNPV_NDOF;   //!
  TBranch        *b_Jpsi_OWNPV_COV_;   //!
  TBranch        *b_Jpsi_IP_OWNPV;   //!
  TBranch        *b_Jpsi_IPCHI2_OWNPV;   //!
  TBranch        *b_Jpsi_FD_OWNPV;   //!
  TBranch        *b_Jpsi_FDCHI2_OWNPV;   //!
  TBranch        *b_Jpsi_DIRA_OWNPV;   //!
  TBranch        *b_Jpsi_ORIVX_X;   //!
  TBranch        *b_Jpsi_ORIVX_Y;   //!
  TBranch        *b_Jpsi_ORIVX_Z;   //!
  TBranch        *b_Jpsi_ORIVX_XERR;   //!
  TBranch        *b_Jpsi_ORIVX_YERR;   //!
  TBranch        *b_Jpsi_ORIVX_ZERR;   //!
  TBranch        *b_Jpsi_ORIVX_CHI2;   //!
  TBranch        *b_Jpsi_ORIVX_NDOF;   //!
  TBranch        *b_Jpsi_ORIVX_COV_;   //!
  TBranch        *b_Jpsi_FD_ORIVX;   //!
  TBranch        *b_Jpsi_FDCHI2_ORIVX;   //!
  TBranch        *b_Jpsi_DIRA_ORIVX;   //!
  TBranch        *b_Jpsi_P;   //!
  TBranch        *b_Jpsi_PT;   //!
  TBranch        *b_Jpsi_PE;   //!
  TBranch        *b_Jpsi_PX;   //!
  TBranch        *b_Jpsi_PY;   //!
  TBranch        *b_Jpsi_PZ;   //!
  TBranch        *b_Jpsi_MM;   //!
  TBranch        *b_Jpsi_MMERR;   //!
  TBranch        *b_Jpsi_M;   //!
  TBranch        *b_Jpsi_TRUEID;   //!
  TBranch        *b_Jpsi_MC_MOTHER_ID;   //!
  TBranch        *b_Jpsi_MC_MOTHER_KEY;   //!
  TBranch        *b_Jpsi_MC_GD_MOTHER_ID;   //!
  TBranch        *b_Jpsi_MC_GD_MOTHER_KEY;   //!
  TBranch        *b_Jpsi_MC_GD_GD_MOTHER_ID;   //!
  TBranch        *b_Jpsi_MC_GD_GD_MOTHER_KEY;   //!
  TBranch        *b_Jpsi_TRUEP_E;   //!
  TBranch        *b_Jpsi_TRUEP_X;   //!
  TBranch        *b_Jpsi_TRUEP_Y;   //!
  TBranch        *b_Jpsi_TRUEP_Z;   //!
  TBranch        *b_Jpsi_TRUEPT;   //!
  TBranch        *b_Jpsi_TRUEORIGINVERTEX_X;   //!
  TBranch        *b_Jpsi_TRUEORIGINVERTEX_Y;   //!
  TBranch        *b_Jpsi_TRUEORIGINVERTEX_Z;   //!
  TBranch        *b_Jpsi_TRUEENDVERTEX_X;   //!
  TBranch        *b_Jpsi_TRUEENDVERTEX_Y;   //!
  TBranch        *b_Jpsi_TRUEENDVERTEX_Z;   //!
  TBranch        *b_Jpsi_TRUEISSTABLE;   //!
  TBranch        *b_Jpsi_TRUETAU;   //!
  TBranch        *b_Jpsi_ID;   //!
  TBranch        *b_Jpsi_BKGCAT;   //!
  TBranch        *b_Jpsi_L0Global_Dec;
  TBranch        *b_Jpsi_L0Global_TIS;
  TBranch        *b_Jpsi_L0Global_TOS;
  TBranch        *b_Jpsi_Hlt1Global_Dec;
  TBranch        *b_Jpsi_Hlt1Global_TIS;
  TBranch        *b_Jpsi_Hlt1Global_TOS;
  TBranch        *b_Jpsi_Hlt1Phys_Dec;
  TBranch        *b_Jpsi_Hlt1Phys_TIS;
  TBranch        *b_Jpsi_Hlt1Phys_TOS;
  TBranch        *b_Jpsi_Hlt2Global_Dec;
  TBranch        *b_Jpsi_Hlt2Global_TIS;
  TBranch        *b_Jpsi_Hlt2Global_TOS;
  TBranch        *b_Jpsi_Hlt2Phys_Dec;
  TBranch        *b_Jpsi_Hlt2Phys_TIS;
  TBranch        *b_Jpsi_Hlt2Phys_TOS;
  TBranch        *b_Jpsi_L0MuonDecision_Dec;
  TBranch        *b_Jpsi_L0MuonDecision_TIS;
  TBranch        *b_Jpsi_L0MuonDecision_TOS;
  TBranch        *b_Jpsi_L0DiMuonDecision_Dec;
  TBranch        *b_Jpsi_L0DiMuonDecision_TIS;
  TBranch        *b_Jpsi_L0DiMuonDecision_TOS;
  TBranch        *b_Jpsi_Hlt1DiMuonHighMassDecision_Dec;
  TBranch        *b_Jpsi_Hlt1DiMuonHighMassDecision_TIS;
  TBranch        *b_Jpsi_Hlt1DiMuonHighMassDecision_TOS;
  TBranch        *b_Jpsi_Hlt1DiMuonLowMassDecision_Dec;
  TBranch        *b_Jpsi_Hlt1DiMuonLowMassDecision_TIS;
  TBranch        *b_Jpsi_Hlt1DiMuonLowMassDecision_TOS;
  TBranch        *b_Jpsi_Hlt2DiMuonJPsiHighPTDecision_Dec;
  TBranch        *b_Jpsi_Hlt2DiMuonJPsiHighPTDecision_TIS;
  TBranch        *b_Jpsi_Hlt2DiMuonJPsiHighPTDecision_TOS;
  TBranch        *b_MuM_TRACK_Type;   //!
  TBranch        *b_MuM_TRACK_Key;   //!
  TBranch        *b_MuM_TRACK_CHI2NDOF;   //!
  TBranch        *b_MuM_TRACK_PCHI2;   //!
  TBranch        *b_MuM_TRACK_MatchCHI2;   //!
  TBranch        *b_MuM_TRACK_GhostProb;   //!
  TBranch        *b_MuM_TRACK_CloneDist;   //!
  TBranch        *b_MuM_TRACK_Likelihood;   //!
  TBranch        *b_MuM_OWNPV_X;   //!
  TBranch        *b_MuM_OWNPV_Y;   //!
  TBranch        *b_MuM_OWNPV_Z;   //!
  TBranch        *b_MuM_OWNPV_XERR;   //!
  TBranch        *b_MuM_OWNPV_YERR;   //!
  TBranch        *b_MuM_OWNPV_ZERR;   //!
  TBranch        *b_MuM_OWNPV_CHI2;   //!
  TBranch        *b_MuM_OWNPV_NDOF;   //!
  TBranch        *b_MuM_OWNPV_COV_;   //!
  TBranch        *b_MuM_IP_OWNPV;   //!
  TBranch        *b_MuM_IPCHI2_OWNPV;   //!
  TBranch        *b_MuM_ORIVX_X;   //!
  TBranch        *b_MuM_ORIVX_Y;   //!
  TBranch        *b_MuM_ORIVX_Z;   //!
  TBranch        *b_MuM_ORIVX_XERR;   //!
  TBranch        *b_MuM_ORIVX_YERR;   //!
  TBranch        *b_MuM_ORIVX_ZERR;   //!
  TBranch        *b_MuM_ORIVX_CHI2;   //!
  TBranch        *b_MuM_ORIVX_NDOF;   //!
  TBranch        *b_MuM_ORIVX_COV_;   //!
  TBranch        *b_MuM_P;   //!
  TBranch        *b_MuM_PT;   //!
  TBranch        *b_MuM_PE;   //!
  TBranch        *b_MuM_PX;   //!
  TBranch        *b_MuM_PY;   //!
  TBranch        *b_MuM_PZ;   //!
  TBranch        *b_MuM_M;   //!
  TBranch        *b_MuM_TRUEID;   //!
  TBranch        *b_MuM_MC_MOTHER_ID;   //!
  TBranch        *b_MuM_MC_MOTHER_KEY;   //!
  TBranch        *b_MuM_MC_GD_MOTHER_ID;   //!
  TBranch        *b_MuM_MC_GD_MOTHER_KEY;   //!
  TBranch        *b_MuM_MC_GD_GD_MOTHER_ID;   //!
  TBranch        *b_MuM_MC_GD_GD_MOTHER_KEY;   //!
  TBranch        *b_MuM_TRUEP_E;   //!
  TBranch        *b_MuM_TRUEP_X;   //!
  TBranch        *b_MuM_TRUEP_Y;   //!
  TBranch        *b_MuM_TRUEP_Z;   //!
  TBranch        *b_MuM_TRUEPT;   //!
  TBranch        *b_MuM_TRUEORIGINVERTEX_X;   //!
  TBranch        *b_MuM_TRUEORIGINVERTEX_Y;   //!
  TBranch        *b_MuM_TRUEORIGINVERTEX_Z;   //!
  TBranch        *b_MuM_TRUEENDVERTEX_X;   //!
  TBranch        *b_MuM_TRUEENDVERTEX_Y;   //!
  TBranch        *b_MuM_TRUEENDVERTEX_Z;   //!
  TBranch        *b_MuM_TRUEISSTABLE;   //!
  TBranch        *b_MuM_TRUETAU;   //!
  TBranch        *b_MuM_ID;   //!
  TBranch        *b_MuM_PIDe;   //!
  TBranch        *b_MuM_PIDmu;   //!
  TBranch        *b_MuM_PIDK;   //!
  TBranch        *b_MuM_PIDp;   //!
  TBranch        *b_MuM_ProbNNe;   //!
  TBranch        *b_MuM_ProbNNk;   //!
  TBranch        *b_MuM_ProbNNp;   //!
  TBranch        *b_MuM_ProbNNpi;   //!
  TBranch        *b_MuM_ProbNNmu;   //!
  TBranch        *b_MuM_ProbNNghost;   //!
  TBranch        *b_MuM_hasMuon;   //!
  TBranch        *b_MuM_isMuon;   //!
  TBranch        *b_MuM_hasRich;   //!
  TBranch        *b_MuM_hasCalo;   //!
  TBranch        *b_MuP_OWNPV_X;   //!
  TBranch        *b_MuP_OWNPV_Y;   //!
  TBranch        *b_MuP_OWNPV_Z;   //!
  TBranch        *b_MuP_OWNPV_XERR;   //!
  TBranch        *b_MuP_OWNPV_YERR;   //!
  TBranch        *b_MuP_OWNPV_ZERR;   //!
  TBranch        *b_MuP_OWNPV_CHI2;   //!
  TBranch        *b_MuP_OWNPV_NDOF;   //!
  TBranch        *b_MuP_OWNPV_COV_;   //!
  TBranch        *b_MuP_IP_OWNPV;   //!
  TBranch        *b_MuP_IPCHI2_OWNPV;   //!
  TBranch        *b_MuP_ORIVX_X;   //!
  TBranch        *b_MuP_ORIVX_Y;   //!
  TBranch        *b_MuP_ORIVX_Z;   //!
  TBranch        *b_MuP_ORIVX_XERR;   //!
  TBranch        *b_MuP_ORIVX_YERR;   //!
  TBranch        *b_MuP_ORIVX_ZERR;   //!
  TBranch        *b_MuP_ORIVX_CHI2;   //!
  TBranch        *b_MuP_ORIVX_NDOF;   //!
  TBranch        *b_MuP_ORIVX_COV_;   //!
  TBranch        *b_MuP_P;   //!
  TBranch        *b_MuP_PT;   //!
  TBranch        *b_MuP_PE;   //!
  TBranch        *b_MuP_PX;   //!
  TBranch        *b_MuP_PY;   //!
  TBranch        *b_MuP_PZ;   //!
  TBranch        *b_MuP_M;   //!
  TBranch        *b_MuP_TRUEID;   //!
  TBranch        *b_MuP_MC_MOTHER_ID;   //!
  TBranch        *b_MuP_MC_MOTHER_KEY;   //!
  TBranch        *b_MuP_MC_GD_MOTHER_ID;   //!
  TBranch        *b_MuP_MC_GD_MOTHER_KEY;   //!
  TBranch        *b_MuP_MC_GD_GD_MOTHER_ID;   //!
  TBranch        *b_MuP_MC_GD_GD_MOTHER_KEY;   //!
  TBranch        *b_MuP_TRUEP_E;   //!
  TBranch        *b_MuP_TRUEP_X;   //!
  TBranch        *b_MuP_TRUEP_Y;   //!
  TBranch        *b_MuP_TRUEP_Z;   //!
  TBranch        *b_MuP_TRUEPT;   //!
  TBranch        *b_MuP_TRUEORIGINVERTEX_X;   //!
  TBranch        *b_MuP_TRUEORIGINVERTEX_Y;   //!
  TBranch        *b_MuP_TRUEORIGINVERTEX_Z;   //!
  TBranch        *b_MuP_TRUEENDVERTEX_X;   //!
  TBranch        *b_MuP_TRUEENDVERTEX_Y;   //!
  TBranch        *b_MuP_TRUEENDVERTEX_Z;   //!
  TBranch        *b_MuP_TRUEISSTABLE;   //!
  TBranch        *b_MuP_TRUETAU;   //!
  TBranch        *b_MuP_ID;   //!
  TBranch        *b_MuP_PIDe;   //!
  TBranch        *b_MuP_PIDmu;   //!
  TBranch        *b_MuP_PIDK;   //!
  TBranch        *b_MuP_PIDp;   //!
  TBranch        *b_MuP_ProbNNe;   //!
  TBranch        *b_MuP_ProbNNk;   //!
  TBranch        *b_MuP_ProbNNp;   //!
  TBranch        *b_MuP_ProbNNpi;   //!
  TBranch        *b_MuP_ProbNNmu;   //!
  TBranch        *b_MuP_ProbNNghost;   //!
  TBranch        *b_MuP_hasMuon;   //!
  TBranch        *b_MuP_isMuon;   //!
  TBranch        *b_MuP_hasRich;   //!
  TBranch        *b_MuP_hasCalo;   //!
  TBranch        *b_MuP_TRACK_Type;   //!
  TBranch        *b_MuP_TRACK_Key;   //!
  TBranch        *b_MuP_TRACK_CHI2NDOF;   //!
  TBranch        *b_MuP_TRACK_PCHI2;   //!
  TBranch        *b_MuP_TRACK_MatchCHI2;   //!
  TBranch        *b_MuP_TRACK_GhostProb;   //!
  TBranch        *b_MuP_TRACK_CloneDist;   //!
  TBranch        *b_MuP_TRACK_Likelihood;   //!
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
  TBranch        *b_nTracks;   //!


  RecSelector(TTree * /*tree*/ = 0) : fChain(0) { }
  virtual ~RecSelector() { }
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

  //ClassDef(RecSelector,0);
};

#endif

#ifdef RecSelector_cxx
void RecSelector::Init(TTree *tree)
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

  fChain->SetBranchAddress("Bc_ENDVERTEX_X", &Bc_ENDVERTEX_X, &b_Bc_ENDVERTEX_X);
  fChain->SetBranchAddress("Bc_ENDVERTEX_Y", &Bc_ENDVERTEX_Y, &b_Bc_ENDVERTEX_Y);
  fChain->SetBranchAddress("Bc_ENDVERTEX_Z", &Bc_ENDVERTEX_Z, &b_Bc_ENDVERTEX_Z);
  fChain->SetBranchAddress("Bc_ENDVERTEX_XERR", &Bc_ENDVERTEX_XERR, &b_Bc_ENDVERTEX_XERR);
  fChain->SetBranchAddress("Bc_ENDVERTEX_YERR", &Bc_ENDVERTEX_YERR, &b_Bc_ENDVERTEX_YERR);
  fChain->SetBranchAddress("Bc_ENDVERTEX_ZERR", &Bc_ENDVERTEX_ZERR, &b_Bc_ENDVERTEX_ZERR);
  fChain->SetBranchAddress("Bc_ENDVERTEX_CHI2", &Bc_ENDVERTEX_CHI2, &b_Bc_ENDVERTEX_CHI2);
  fChain->SetBranchAddress("Bc_ENDVERTEX_NDOF", &Bc_ENDVERTEX_NDOF, &b_Bc_ENDVERTEX_NDOF);
  fChain->SetBranchAddress("Bc_ENDVERTEX_COV_", Bc_ENDVERTEX_COV_, &b_Bc_ENDVERTEX_COV_);
  fChain->SetBranchAddress("Bc_OWNPV_X", &Bc_OWNPV_X, &b_Bc_OWNPV_X);
  fChain->SetBranchAddress("Bc_OWNPV_Y", &Bc_OWNPV_Y, &b_Bc_OWNPV_Y);
  fChain->SetBranchAddress("Bc_OWNPV_Z", &Bc_OWNPV_Z, &b_Bc_OWNPV_Z);
  fChain->SetBranchAddress("Bc_OWNPV_XERR", &Bc_OWNPV_XERR, &b_Bc_OWNPV_XERR);
  fChain->SetBranchAddress("Bc_OWNPV_YERR", &Bc_OWNPV_YERR, &b_Bc_OWNPV_YERR);
  fChain->SetBranchAddress("Bc_OWNPV_ZERR", &Bc_OWNPV_ZERR, &b_Bc_OWNPV_ZERR);
  fChain->SetBranchAddress("Bc_OWNPV_CHI2", &Bc_OWNPV_CHI2, &b_Bc_OWNPV_CHI2);
  fChain->SetBranchAddress("Bc_OWNPV_NDOF", &Bc_OWNPV_NDOF, &b_Bc_OWNPV_NDOF);
  fChain->SetBranchAddress("Bc_OWNPV_COV_", Bc_OWNPV_COV_, &b_Bc_OWNPV_COV_);
  fChain->SetBranchAddress("Bc_IP_OWNPV", &Bc_IP_OWNPV, &b_Bc_IP_OWNPV);
  fChain->SetBranchAddress("Bc_IPCHI2_OWNPV", &Bc_IPCHI2_OWNPV, &b_Bc_IPCHI2_OWNPV);
  fChain->SetBranchAddress("Bc_FD_OWNPV", &Bc_FD_OWNPV, &b_Bc_FD_OWNPV);
  fChain->SetBranchAddress("Bc_FDCHI2_OWNPV", &Bc_FDCHI2_OWNPV, &b_Bc_FDCHI2_OWNPV);
  fChain->SetBranchAddress("Bc_DIRA_OWNPV", &Bc_DIRA_OWNPV, &b_Bc_DIRA_OWNPV);
  fChain->SetBranchAddress("Bc_P", &Bc_P, &b_Bc_P);
  fChain->SetBranchAddress("Bc_PT", &Bc_PT, &b_Bc_PT);
  fChain->SetBranchAddress("Bc_PE", &Bc_PE, &b_Bc_PE);
  fChain->SetBranchAddress("Bc_PX", &Bc_PX, &b_Bc_PX);
  fChain->SetBranchAddress("Bc_PY", &Bc_PY, &b_Bc_PY);
  fChain->SetBranchAddress("Bc_PZ", &Bc_PZ, &b_Bc_PZ);
  fChain->SetBranchAddress("Bc_MM", &Bc_MM, &b_Bc_MM);
  fChain->SetBranchAddress("Bc_MMERR", &Bc_MMERR, &b_Bc_MMERR);
  fChain->SetBranchAddress("Bc_M", &Bc_M, &b_Bc_M);
  fChain->SetBranchAddress("Bc_ID", &Bc_ID, &b_Bc_ID);
  fChain->SetBranchAddress("Bc_DOCA", &Bc_DOCA, &b_Bc_DOCA);
  fChain->SetBranchAddress("Bc_DOCACHI2", &Bc_DOCACHI2, &b_Bc_DOCACHI2);
  fChain->SetBranchAddress("Jpsi_L0Global_Dec", &Jpsi_L0Global_Dec, &b_Jpsi_L0Global_Dec);
  fChain->SetBranchAddress("Jpsi_L0Global_TIS", &Jpsi_L0Global_TIS, &b_Jpsi_L0Global_TIS);
  fChain->SetBranchAddress("Jpsi_L0Global_TOS", &Jpsi_L0Global_TOS, &b_Jpsi_L0Global_TOS);
  fChain->SetBranchAddress("Jpsi_Hlt1Global_Dec", &Jpsi_Hlt1Global_Dec, &b_Jpsi_Hlt1Global_Dec);
  fChain->SetBranchAddress("Jpsi_Hlt1Global_TIS", &Jpsi_Hlt1Global_TIS, &b_Jpsi_Hlt1Global_TIS);
  fChain->SetBranchAddress("Jpsi_Hlt1Global_TOS", &Jpsi_Hlt1Global_TOS, &b_Jpsi_Hlt1Global_TOS);
  fChain->SetBranchAddress("Jpsi_Hlt1Phys_Dec", &Jpsi_Hlt1Phys_Dec, &b_Jpsi_Hlt1Phys_Dec);
  fChain->SetBranchAddress("Jpsi_Hlt1Phys_TIS", &Jpsi_Hlt1Phys_TIS, &b_Jpsi_Hlt1Phys_TIS);
  fChain->SetBranchAddress("Jpsi_Hlt1Phys_TOS", &Jpsi_Hlt1Phys_TOS, &b_Jpsi_Hlt1Phys_TOS);
  fChain->SetBranchAddress("Jpsi_Hlt2Global_Dec", &Jpsi_Hlt2Global_Dec, &b_Jpsi_Hlt2Global_Dec);
  fChain->SetBranchAddress("Jpsi_Hlt2Global_TIS", &Jpsi_Hlt2Global_TIS, &b_Jpsi_Hlt2Global_TIS);
  fChain->SetBranchAddress("Jpsi_Hlt2Global_TOS", &Jpsi_Hlt2Global_TOS, &b_Jpsi_Hlt2Global_TOS);
  fChain->SetBranchAddress("Jpsi_Hlt2Phys_Dec", &Jpsi_Hlt2Phys_Dec, &b_Jpsi_Hlt2Phys_Dec);
  fChain->SetBranchAddress("Jpsi_Hlt2Phys_TIS", &Jpsi_Hlt2Phys_TIS, &b_Jpsi_Hlt2Phys_TIS);
  fChain->SetBranchAddress("Jpsi_Hlt2Phys_TOS", &Jpsi_Hlt2Phys_TOS, &b_Jpsi_Hlt2Phys_TOS);
  fChain->SetBranchAddress("Jpsi_L0MuonDecision_Dec", &Jpsi_L0MuonDecision_Dec, &b_Jpsi_L0MuonDecision_Dec);
  fChain->SetBranchAddress("Jpsi_L0MuonDecision_TIS", &Jpsi_L0MuonDecision_TIS, &b_Jpsi_L0MuonDecision_TIS);
  fChain->SetBranchAddress("Jpsi_L0MuonDecision_TOS", &Jpsi_L0MuonDecision_TOS, &b_Jpsi_L0MuonDecision_TOS);
  fChain->SetBranchAddress("Jpsi_L0DiMuonDecision_Dec", &Jpsi_L0DiMuonDecision_Dec, &b_Jpsi_L0DiMuonDecision_Dec);
  fChain->SetBranchAddress("Jpsi_L0DiMuonDecision_TIS", &Jpsi_L0DiMuonDecision_TIS, &b_Jpsi_L0DiMuonDecision_TIS);
  fChain->SetBranchAddress("Jpsi_L0DiMuonDecision_TOS", &Jpsi_L0DiMuonDecision_TOS, &b_Jpsi_L0DiMuonDecision_TOS);
  fChain->SetBranchAddress("Jpsi_Hlt1DiMuonHighMassDecision_Dec", &Jpsi_Hlt1DiMuonHighMassDecision_Dec, &b_Jpsi_Hlt1DiMuonHighMassDecision_Dec);
  fChain->SetBranchAddress("Jpsi_Hlt1DiMuonHighMassDecision_TIS", &Jpsi_Hlt1DiMuonHighMassDecision_TIS, &b_Jpsi_Hlt1DiMuonHighMassDecision_TIS);
  fChain->SetBranchAddress("Jpsi_Hlt1DiMuonHighMassDecision_TOS", &Jpsi_Hlt1DiMuonHighMassDecision_TOS, &b_Jpsi_Hlt1DiMuonHighMassDecision_TOS);
  fChain->SetBranchAddress("Jpsi_Hlt1DiMuonLowMassDecision_Dec", &Jpsi_Hlt1DiMuonLowMassDecision_Dec, &b_Jpsi_Hlt1DiMuonLowMassDecision_Dec);
  fChain->SetBranchAddress("Jpsi_Hlt1DiMuonLowMassDecision_TIS", &Jpsi_Hlt1DiMuonLowMassDecision_TIS, &b_Jpsi_Hlt1DiMuonLowMassDecision_TIS);
  fChain->SetBranchAddress("Jpsi_Hlt1DiMuonLowMassDecision_TOS", &Jpsi_Hlt1DiMuonLowMassDecision_TOS, &b_Jpsi_Hlt1DiMuonLowMassDecision_TOS);
  fChain->SetBranchAddress("Jpsi_Hlt2DiMuonJPsiHighPTDecision_Dec", &Jpsi_Hlt2DiMuonJPsiHighPTDecision_Dec, &b_Jpsi_Hlt2DiMuonJPsiHighPTDecision_Dec);
  fChain->SetBranchAddress("Jpsi_Hlt2DiMuonJPsiHighPTDecision_TIS", &Jpsi_Hlt2DiMuonJPsiHighPTDecision_TIS, &b_Jpsi_Hlt2DiMuonJPsiHighPTDecision_TIS);
  fChain->SetBranchAddress("Jpsi_Hlt2DiMuonJPsiHighPTDecision_TOS", &Jpsi_Hlt2DiMuonJPsiHighPTDecision_TOS, &b_Jpsi_Hlt2DiMuonJPsiHighPTDecision_TOS);
  fChain->SetBranchAddress("BachMu_TRACK_Type", &BachMu_TRACK_Type, &b_BachMu_TRACK_Type);
  fChain->SetBranchAddress("BachMu_TRACK_Key", &BachMu_TRACK_Key, &b_BachMu_TRACK_Key);
  fChain->SetBranchAddress("BachMu_TRACK_CHI2NDOF", &BachMu_TRACK_CHI2NDOF, &b_BachMu_TRACK_CHI2NDOF);
  fChain->SetBranchAddress("BachMu_TRACK_PCHI2", &BachMu_TRACK_PCHI2, &b_BachMu_TRACK_PCHI2);
  fChain->SetBranchAddress("BachMu_TRACK_MatchCHI2", &BachMu_TRACK_MatchCHI2, &b_BachMu_TRACK_MatchCHI2);
  fChain->SetBranchAddress("BachMu_TRACK_GhostProb", &BachMu_TRACK_GhostProb, &b_BachMu_TRACK_GhostProb);
  fChain->SetBranchAddress("BachMu_TRACK_CloneDist", &BachMu_TRACK_CloneDist, &b_BachMu_TRACK_CloneDist);
  fChain->SetBranchAddress("BachMu_TRACK_Likelihood", &BachMu_TRACK_Likelihood, &b_BachMu_TRACK_Likelihood);
  fChain->SetBranchAddress("BachMu_InMuonAcc", &BachMu_InMuonAcc, &b_BachMu_InMuonAcc);
  fChain->SetBranchAddress("BachMu_MuonDist2", &BachMu_MuonDist2, &b_BachMu_MuonDist2);
  fChain->SetBranchAddress("BachMu_NShared", &BachMu_NShared, &b_BachMu_NShared);
  fChain->SetBranchAddress("BachMu_MuonLLmu", &BachMu_MuonLLmu, &b_BachMu_MuonLLmu);
  fChain->SetBranchAddress("BachMu_MuonLLbg", &BachMu_MuonLLbg, &b_BachMu_MuonLLbg);
  fChain->SetBranchAddress("BachMu_regionInM2", &BachMu_regionInM2, &b_BachMu_regionInM2);
  fChain->SetBranchAddress("BachMu_CombDLLMu", &BachMu_CombDLLMu, &b_BachMu_CombDLLMu);
  fChain->SetBranchAddress("BachMu_OWNPV_X", &BachMu_OWNPV_X, &b_BachMu_OWNPV_X);
  fChain->SetBranchAddress("BachMu_OWNPV_Y", &BachMu_OWNPV_Y, &b_BachMu_OWNPV_Y);
  fChain->SetBranchAddress("BachMu_OWNPV_Z", &BachMu_OWNPV_Z, &b_BachMu_OWNPV_Z);
  fChain->SetBranchAddress("BachMu_OWNPV_XERR", &BachMu_OWNPV_XERR, &b_BachMu_OWNPV_XERR);
  fChain->SetBranchAddress("BachMu_OWNPV_YERR", &BachMu_OWNPV_YERR, &b_BachMu_OWNPV_YERR);
  fChain->SetBranchAddress("BachMu_OWNPV_ZERR", &BachMu_OWNPV_ZERR, &b_BachMu_OWNPV_ZERR);
  fChain->SetBranchAddress("BachMu_OWNPV_CHI2", &BachMu_OWNPV_CHI2, &b_BachMu_OWNPV_CHI2);
  fChain->SetBranchAddress("BachMu_OWNPV_NDOF", &BachMu_OWNPV_NDOF, &b_BachMu_OWNPV_NDOF);
  fChain->SetBranchAddress("BachMu_OWNPV_COV_", BachMu_OWNPV_COV_, &b_BachMu_OWNPV_COV_);
  fChain->SetBranchAddress("BachMu_IP_OWNPV", &BachMu_IP_OWNPV, &b_BachMu_IP_OWNPV);
  fChain->SetBranchAddress("BachMu_IPCHI2_OWNPV", &BachMu_IPCHI2_OWNPV, &b_BachMu_IPCHI2_OWNPV);
  fChain->SetBranchAddress("BachMu_ORIVX_X", &BachMu_ORIVX_X, &b_BachMu_ORIVX_X);
  fChain->SetBranchAddress("BachMu_ORIVX_Y", &BachMu_ORIVX_Y, &b_BachMu_ORIVX_Y);
  fChain->SetBranchAddress("BachMu_ORIVX_Z", &BachMu_ORIVX_Z, &b_BachMu_ORIVX_Z);
  fChain->SetBranchAddress("BachMu_ORIVX_XERR", &BachMu_ORIVX_XERR, &b_BachMu_ORIVX_XERR);
  fChain->SetBranchAddress("BachMu_ORIVX_YERR", &BachMu_ORIVX_YERR, &b_BachMu_ORIVX_YERR);
  fChain->SetBranchAddress("BachMu_ORIVX_ZERR", &BachMu_ORIVX_ZERR, &b_BachMu_ORIVX_ZERR);
  fChain->SetBranchAddress("BachMu_ORIVX_CHI2", &BachMu_ORIVX_CHI2, &b_BachMu_ORIVX_CHI2);
  fChain->SetBranchAddress("BachMu_ORIVX_NDOF", &BachMu_ORIVX_NDOF, &b_BachMu_ORIVX_NDOF);
  fChain->SetBranchAddress("BachMu_ORIVX_COV_", BachMu_ORIVX_COV_, &b_BachMu_ORIVX_COV_);
  fChain->SetBranchAddress("BachMu_P", &BachMu_P, &b_BachMu_P);
  fChain->SetBranchAddress("BachMu_PT", &BachMu_PT, &b_BachMu_PT);
  fChain->SetBranchAddress("BachMu_PE", &BachMu_PE, &b_BachMu_PE);
  fChain->SetBranchAddress("BachMu_PX", &BachMu_PX, &b_BachMu_PX);
  fChain->SetBranchAddress("BachMu_PY", &BachMu_PY, &b_BachMu_PY);
  fChain->SetBranchAddress("BachMu_PZ", &BachMu_PZ, &b_BachMu_PZ);
  fChain->SetBranchAddress("BachMu_M", &BachMu_M, &b_BachMu_M);
  fChain->SetBranchAddress("BachMu_ID", &BachMu_ID, &b_BachMu_ID);
  fChain->SetBranchAddress("BachMu_PIDe", &BachMu_PIDe, &b_BachMu_PIDe);
  fChain->SetBranchAddress("BachMu_PIDmu", &BachMu_PIDmu, &b_BachMu_PIDmu);
  fChain->SetBranchAddress("BachMu_PIDK", &BachMu_PIDK, &b_BachMu_PIDK);
  fChain->SetBranchAddress("BachMu_PIDp", &BachMu_PIDp, &b_BachMu_PIDp);
  fChain->SetBranchAddress("BachMu_ProbNNe", &BachMu_ProbNNe, &b_BachMu_ProbNNe);
  fChain->SetBranchAddress("BachMu_ProbNNk", &BachMu_ProbNNk, &b_BachMu_ProbNNk);
  fChain->SetBranchAddress("BachMu_ProbNNp", &BachMu_ProbNNp, &b_BachMu_ProbNNp);
  fChain->SetBranchAddress("BachMu_ProbNNpi", &BachMu_ProbNNpi, &b_BachMu_ProbNNpi);
  fChain->SetBranchAddress("BachMu_ProbNNmu", &BachMu_ProbNNmu, &b_BachMu_ProbNNmu);
  fChain->SetBranchAddress("BachMu_ProbNNghost", &BachMu_ProbNNghost, &b_BachMu_ProbNNghost);
  fChain->SetBranchAddress("BachMu_hasMuon", &BachMu_hasMuon, &b_BachMu_hasMuon);
  fChain->SetBranchAddress("BachMu_isMuon", &BachMu_isMuon, &b_BachMu_isMuon);
  fChain->SetBranchAddress("BachMu_hasRich", &BachMu_hasRich, &b_BachMu_hasRich);
  fChain->SetBranchAddress("BachMu_hasCalo", &BachMu_hasCalo, &b_BachMu_hasCalo);
  fChain->SetBranchAddress("Jpsi_ENDVERTEX_X", &Jpsi_ENDVERTEX_X, &b_Jpsi_ENDVERTEX_X);
  fChain->SetBranchAddress("Jpsi_ENDVERTEX_Y", &Jpsi_ENDVERTEX_Y, &b_Jpsi_ENDVERTEX_Y);
  fChain->SetBranchAddress("Jpsi_ENDVERTEX_Z", &Jpsi_ENDVERTEX_Z, &b_Jpsi_ENDVERTEX_Z);
  fChain->SetBranchAddress("Jpsi_ENDVERTEX_XERR", &Jpsi_ENDVERTEX_XERR, &b_Jpsi_ENDVERTEX_XERR);
  fChain->SetBranchAddress("Jpsi_ENDVERTEX_YERR", &Jpsi_ENDVERTEX_YERR, &b_Jpsi_ENDVERTEX_YERR);
  fChain->SetBranchAddress("Jpsi_ENDVERTEX_ZERR", &Jpsi_ENDVERTEX_ZERR, &b_Jpsi_ENDVERTEX_ZERR);
  fChain->SetBranchAddress("Jpsi_ENDVERTEX_CHI2", &Jpsi_ENDVERTEX_CHI2, &b_Jpsi_ENDVERTEX_CHI2);
  fChain->SetBranchAddress("Jpsi_ENDVERTEX_NDOF", &Jpsi_ENDVERTEX_NDOF, &b_Jpsi_ENDVERTEX_NDOF);
  fChain->SetBranchAddress("Jpsi_ENDVERTEX_COV_", Jpsi_ENDVERTEX_COV_, &b_Jpsi_ENDVERTEX_COV_);
  fChain->SetBranchAddress("Jpsi_OWNPV_X", &Jpsi_OWNPV_X, &b_Jpsi_OWNPV_X);
  fChain->SetBranchAddress("Jpsi_OWNPV_Y", &Jpsi_OWNPV_Y, &b_Jpsi_OWNPV_Y);
  fChain->SetBranchAddress("Jpsi_OWNPV_Z", &Jpsi_OWNPV_Z, &b_Jpsi_OWNPV_Z);
  fChain->SetBranchAddress("Jpsi_OWNPV_XERR", &Jpsi_OWNPV_XERR, &b_Jpsi_OWNPV_XERR);
  fChain->SetBranchAddress("Jpsi_OWNPV_YERR", &Jpsi_OWNPV_YERR, &b_Jpsi_OWNPV_YERR);
  fChain->SetBranchAddress("Jpsi_OWNPV_ZERR", &Jpsi_OWNPV_ZERR, &b_Jpsi_OWNPV_ZERR);
  fChain->SetBranchAddress("Jpsi_OWNPV_CHI2", &Jpsi_OWNPV_CHI2, &b_Jpsi_OWNPV_CHI2);
  fChain->SetBranchAddress("Jpsi_OWNPV_NDOF", &Jpsi_OWNPV_NDOF, &b_Jpsi_OWNPV_NDOF);
  fChain->SetBranchAddress("Jpsi_OWNPV_COV_", Jpsi_OWNPV_COV_, &b_Jpsi_OWNPV_COV_);
  fChain->SetBranchAddress("Jpsi_IP_OWNPV", &Jpsi_IP_OWNPV, &b_Jpsi_IP_OWNPV);
  fChain->SetBranchAddress("Jpsi_IPCHI2_OWNPV", &Jpsi_IPCHI2_OWNPV, &b_Jpsi_IPCHI2_OWNPV);
  fChain->SetBranchAddress("Jpsi_FD_OWNPV", &Jpsi_FD_OWNPV, &b_Jpsi_FD_OWNPV);
  fChain->SetBranchAddress("Jpsi_FDCHI2_OWNPV", &Jpsi_FDCHI2_OWNPV, &b_Jpsi_FDCHI2_OWNPV);
  fChain->SetBranchAddress("Jpsi_DIRA_OWNPV", &Jpsi_DIRA_OWNPV, &b_Jpsi_DIRA_OWNPV);
  fChain->SetBranchAddress("Jpsi_ORIVX_X", &Jpsi_ORIVX_X, &b_Jpsi_ORIVX_X);
  fChain->SetBranchAddress("Jpsi_ORIVX_Y", &Jpsi_ORIVX_Y, &b_Jpsi_ORIVX_Y);
  fChain->SetBranchAddress("Jpsi_ORIVX_Z", &Jpsi_ORIVX_Z, &b_Jpsi_ORIVX_Z);
  fChain->SetBranchAddress("Jpsi_ORIVX_XERR", &Jpsi_ORIVX_XERR, &b_Jpsi_ORIVX_XERR);
  fChain->SetBranchAddress("Jpsi_ORIVX_YERR", &Jpsi_ORIVX_YERR, &b_Jpsi_ORIVX_YERR);
  fChain->SetBranchAddress("Jpsi_ORIVX_ZERR", &Jpsi_ORIVX_ZERR, &b_Jpsi_ORIVX_ZERR);
  fChain->SetBranchAddress("Jpsi_ORIVX_CHI2", &Jpsi_ORIVX_CHI2, &b_Jpsi_ORIVX_CHI2);
  fChain->SetBranchAddress("Jpsi_ORIVX_NDOF", &Jpsi_ORIVX_NDOF, &b_Jpsi_ORIVX_NDOF);
  fChain->SetBranchAddress("Jpsi_ORIVX_COV_", Jpsi_ORIVX_COV_, &b_Jpsi_ORIVX_COV_);
  fChain->SetBranchAddress("Jpsi_FD_ORIVX", &Jpsi_FD_ORIVX, &b_Jpsi_FD_ORIVX);
  fChain->SetBranchAddress("Jpsi_FDCHI2_ORIVX", &Jpsi_FDCHI2_ORIVX, &b_Jpsi_FDCHI2_ORIVX);
  fChain->SetBranchAddress("Jpsi_DIRA_ORIVX", &Jpsi_DIRA_ORIVX, &b_Jpsi_DIRA_ORIVX);
  fChain->SetBranchAddress("Jpsi_P", &Jpsi_P, &b_Jpsi_P);
  fChain->SetBranchAddress("Jpsi_PT", &Jpsi_PT, &b_Jpsi_PT);
  fChain->SetBranchAddress("Jpsi_PE", &Jpsi_PE, &b_Jpsi_PE);
  fChain->SetBranchAddress("Jpsi_PX", &Jpsi_PX, &b_Jpsi_PX);
  fChain->SetBranchAddress("Jpsi_PY", &Jpsi_PY, &b_Jpsi_PY);
  fChain->SetBranchAddress("Jpsi_PZ", &Jpsi_PZ, &b_Jpsi_PZ);
  fChain->SetBranchAddress("Jpsi_MM", &Jpsi_MM, &b_Jpsi_MM);
  fChain->SetBranchAddress("Jpsi_MMERR", &Jpsi_MMERR, &b_Jpsi_MMERR);
  fChain->SetBranchAddress("Jpsi_M", &Jpsi_M, &b_Jpsi_M);
  fChain->SetBranchAddress("Jpsi_ID", &Jpsi_ID, &b_Jpsi_ID);
  fChain->SetBranchAddress("MuM_TRACK_Type", &MuM_TRACK_Type, &b_MuM_TRACK_Type);
  fChain->SetBranchAddress("MuM_TRACK_Key", &MuM_TRACK_Key, &b_MuM_TRACK_Key);
  fChain->SetBranchAddress("MuM_TRACK_CHI2NDOF", &MuM_TRACK_CHI2NDOF, &b_MuM_TRACK_CHI2NDOF);
  fChain->SetBranchAddress("MuM_TRACK_PCHI2", &MuM_TRACK_PCHI2, &b_MuM_TRACK_PCHI2);
  fChain->SetBranchAddress("MuM_TRACK_MatchCHI2", &MuM_TRACK_MatchCHI2, &b_MuM_TRACK_MatchCHI2);
  fChain->SetBranchAddress("MuM_TRACK_GhostProb", &MuM_TRACK_GhostProb, &b_MuM_TRACK_GhostProb);
  fChain->SetBranchAddress("MuM_TRACK_CloneDist", &MuM_TRACK_CloneDist, &b_MuM_TRACK_CloneDist);
  fChain->SetBranchAddress("MuM_TRACK_Likelihood", &MuM_TRACK_Likelihood, &b_MuM_TRACK_Likelihood);
  fChain->SetBranchAddress("MuM_OWNPV_X", &MuM_OWNPV_X, &b_MuM_OWNPV_X);
  fChain->SetBranchAddress("MuM_OWNPV_Y", &MuM_OWNPV_Y, &b_MuM_OWNPV_Y);
  fChain->SetBranchAddress("MuM_OWNPV_Z", &MuM_OWNPV_Z, &b_MuM_OWNPV_Z);
  fChain->SetBranchAddress("MuM_OWNPV_XERR", &MuM_OWNPV_XERR, &b_MuM_OWNPV_XERR);
  fChain->SetBranchAddress("MuM_OWNPV_YERR", &MuM_OWNPV_YERR, &b_MuM_OWNPV_YERR);
  fChain->SetBranchAddress("MuM_OWNPV_ZERR", &MuM_OWNPV_ZERR, &b_MuM_OWNPV_ZERR);
  fChain->SetBranchAddress("MuM_OWNPV_CHI2", &MuM_OWNPV_CHI2, &b_MuM_OWNPV_CHI2);
  fChain->SetBranchAddress("MuM_OWNPV_NDOF", &MuM_OWNPV_NDOF, &b_MuM_OWNPV_NDOF);
  fChain->SetBranchAddress("MuM_OWNPV_COV_", MuM_OWNPV_COV_, &b_MuM_OWNPV_COV_);
  fChain->SetBranchAddress("MuM_IP_OWNPV", &MuM_IP_OWNPV, &b_MuM_IP_OWNPV);
  fChain->SetBranchAddress("MuM_IPCHI2_OWNPV", &MuM_IPCHI2_OWNPV, &b_MuM_IPCHI2_OWNPV);
  fChain->SetBranchAddress("MuM_ORIVX_X", &MuM_ORIVX_X, &b_MuM_ORIVX_X);
  fChain->SetBranchAddress("MuM_ORIVX_Y", &MuM_ORIVX_Y, &b_MuM_ORIVX_Y);
  fChain->SetBranchAddress("MuM_ORIVX_Z", &MuM_ORIVX_Z, &b_MuM_ORIVX_Z);
  fChain->SetBranchAddress("MuM_ORIVX_XERR", &MuM_ORIVX_XERR, &b_MuM_ORIVX_XERR);
  fChain->SetBranchAddress("MuM_ORIVX_YERR", &MuM_ORIVX_YERR, &b_MuM_ORIVX_YERR);
  fChain->SetBranchAddress("MuM_ORIVX_ZERR", &MuM_ORIVX_ZERR, &b_MuM_ORIVX_ZERR);
  fChain->SetBranchAddress("MuM_ORIVX_CHI2", &MuM_ORIVX_CHI2, &b_MuM_ORIVX_CHI2);
  fChain->SetBranchAddress("MuM_ORIVX_NDOF", &MuM_ORIVX_NDOF, &b_MuM_ORIVX_NDOF);
  fChain->SetBranchAddress("MuM_ORIVX_COV_", MuM_ORIVX_COV_, &b_MuM_ORIVX_COV_);
  fChain->SetBranchAddress("MuM_P", &MuM_P, &b_MuM_P);
  fChain->SetBranchAddress("MuM_PT", &MuM_PT, &b_MuM_PT);
  fChain->SetBranchAddress("MuM_PE", &MuM_PE, &b_MuM_PE);
  fChain->SetBranchAddress("MuM_PX", &MuM_PX, &b_MuM_PX);
  fChain->SetBranchAddress("MuM_PY", &MuM_PY, &b_MuM_PY);
  fChain->SetBranchAddress("MuM_PZ", &MuM_PZ, &b_MuM_PZ);
  fChain->SetBranchAddress("MuM_M", &MuM_M, &b_MuM_M);
  fChain->SetBranchAddress("MuM_ID", &MuM_ID, &b_MuM_ID);
  fChain->SetBranchAddress("MuM_PIDe", &MuM_PIDe, &b_MuM_PIDe);
  fChain->SetBranchAddress("MuM_PIDmu", &MuM_PIDmu, &b_MuM_PIDmu);
  fChain->SetBranchAddress("MuM_PIDK", &MuM_PIDK, &b_MuM_PIDK);
  fChain->SetBranchAddress("MuM_PIDp", &MuM_PIDp, &b_MuM_PIDp);
  fChain->SetBranchAddress("MuM_ProbNNe", &MuM_ProbNNe, &b_MuM_ProbNNe);
  fChain->SetBranchAddress("MuM_ProbNNk", &MuM_ProbNNk, &b_MuM_ProbNNk);
  fChain->SetBranchAddress("MuM_ProbNNp", &MuM_ProbNNp, &b_MuM_ProbNNp);
  fChain->SetBranchAddress("MuM_ProbNNpi", &MuM_ProbNNpi, &b_MuM_ProbNNpi);
  fChain->SetBranchAddress("MuM_ProbNNmu", &MuM_ProbNNmu, &b_MuM_ProbNNmu);
  fChain->SetBranchAddress("MuM_ProbNNghost", &MuM_ProbNNghost, &b_MuM_ProbNNghost);
  fChain->SetBranchAddress("MuM_hasMuon", &MuM_hasMuon, &b_MuM_hasMuon);
  fChain->SetBranchAddress("MuM_isMuon", &MuM_isMuon, &b_MuM_isMuon);
  fChain->SetBranchAddress("MuM_hasRich", &MuM_hasRich, &b_MuM_hasRich);
  fChain->SetBranchAddress("MuM_hasCalo", &MuM_hasCalo, &b_MuM_hasCalo);
  fChain->SetBranchAddress("MuP_TRACK_Type", &MuP_TRACK_Type, &b_MuP_TRACK_Type);
  fChain->SetBranchAddress("MuP_TRACK_Key", &MuP_TRACK_Key, &b_MuP_TRACK_Key);
  fChain->SetBranchAddress("MuP_TRACK_CHI2NDOF", &MuP_TRACK_CHI2NDOF, &b_MuP_TRACK_CHI2NDOF);
  fChain->SetBranchAddress("MuP_TRACK_PCHI2", &MuP_TRACK_PCHI2, &b_MuP_TRACK_PCHI2);
  fChain->SetBranchAddress("MuP_TRACK_MatchCHI2", &MuP_TRACK_MatchCHI2, &b_MuP_TRACK_MatchCHI2);
  fChain->SetBranchAddress("MuP_TRACK_GhostProb", &MuP_TRACK_GhostProb, &b_MuP_TRACK_GhostProb);
  fChain->SetBranchAddress("MuP_TRACK_CloneDist", &MuP_TRACK_CloneDist, &b_MuP_TRACK_CloneDist);
  fChain->SetBranchAddress("MuP_TRACK_Likelihood", &MuP_TRACK_Likelihood, &b_MuP_TRACK_Likelihood);
  fChain->SetBranchAddress("MuP_OWNPV_X", &MuP_OWNPV_X, &b_MuP_OWNPV_X);
  fChain->SetBranchAddress("MuP_OWNPV_Y", &MuP_OWNPV_Y, &b_MuP_OWNPV_Y);
  fChain->SetBranchAddress("MuP_OWNPV_Z", &MuP_OWNPV_Z, &b_MuP_OWNPV_Z);
  fChain->SetBranchAddress("MuP_OWNPV_XERR", &MuP_OWNPV_XERR, &b_MuP_OWNPV_XERR);
  fChain->SetBranchAddress("MuP_OWNPV_YERR", &MuP_OWNPV_YERR, &b_MuP_OWNPV_YERR);
  fChain->SetBranchAddress("MuP_OWNPV_ZERR", &MuP_OWNPV_ZERR, &b_MuP_OWNPV_ZERR);
  fChain->SetBranchAddress("MuP_OWNPV_CHI2", &MuP_OWNPV_CHI2, &b_MuP_OWNPV_CHI2);
  fChain->SetBranchAddress("MuP_OWNPV_NDOF", &MuP_OWNPV_NDOF, &b_MuP_OWNPV_NDOF);
  fChain->SetBranchAddress("MuP_OWNPV_COV_", MuP_OWNPV_COV_, &b_MuP_OWNPV_COV_);
  fChain->SetBranchAddress("MuP_IP_OWNPV", &MuP_IP_OWNPV, &b_MuP_IP_OWNPV);
  fChain->SetBranchAddress("MuP_IPCHI2_OWNPV", &MuP_IPCHI2_OWNPV, &b_MuP_IPCHI2_OWNPV);
  fChain->SetBranchAddress("MuP_ORIVX_X", &MuP_ORIVX_X, &b_MuP_ORIVX_X);
  fChain->SetBranchAddress("MuP_ORIVX_Y", &MuP_ORIVX_Y, &b_MuP_ORIVX_Y);
  fChain->SetBranchAddress("MuP_ORIVX_Z", &MuP_ORIVX_Z, &b_MuP_ORIVX_Z);
  fChain->SetBranchAddress("MuP_ORIVX_XERR", &MuP_ORIVX_XERR, &b_MuP_ORIVX_XERR);
  fChain->SetBranchAddress("MuP_ORIVX_YERR", &MuP_ORIVX_YERR, &b_MuP_ORIVX_YERR);
  fChain->SetBranchAddress("MuP_ORIVX_ZERR", &MuP_ORIVX_ZERR, &b_MuP_ORIVX_ZERR);
  fChain->SetBranchAddress("MuP_ORIVX_CHI2", &MuP_ORIVX_CHI2, &b_MuP_ORIVX_CHI2);
  fChain->SetBranchAddress("MuP_ORIVX_NDOF", &MuP_ORIVX_NDOF, &b_MuP_ORIVX_NDOF);
  fChain->SetBranchAddress("MuP_ORIVX_COV_", MuP_ORIVX_COV_, &b_MuP_ORIVX_COV_);
  fChain->SetBranchAddress("MuP_P", &MuP_P, &b_MuP_P);
  fChain->SetBranchAddress("MuP_PT", &MuP_PT, &b_MuP_PT);
  fChain->SetBranchAddress("MuP_PE", &MuP_PE, &b_MuP_PE);
  fChain->SetBranchAddress("MuP_PX", &MuP_PX, &b_MuP_PX);
  fChain->SetBranchAddress("MuP_PY", &MuP_PY, &b_MuP_PY);
  fChain->SetBranchAddress("MuP_PZ", &MuP_PZ, &b_MuP_PZ);
  fChain->SetBranchAddress("MuP_M", &MuP_M, &b_MuP_M);
  fChain->SetBranchAddress("MuP_ID", &MuP_ID, &b_MuP_ID);
  fChain->SetBranchAddress("MuP_PIDe", &MuP_PIDe, &b_MuP_PIDe);
  fChain->SetBranchAddress("MuP_PIDmu", &MuP_PIDmu, &b_MuP_PIDmu);
  fChain->SetBranchAddress("MuP_PIDK", &MuP_PIDK, &b_MuP_PIDK);
  fChain->SetBranchAddress("MuP_PIDp", &MuP_PIDp, &b_MuP_PIDp);
  fChain->SetBranchAddress("MuP_ProbNNe", &MuP_ProbNNe, &b_MuP_ProbNNe);
  fChain->SetBranchAddress("MuP_ProbNNk", &MuP_ProbNNk, &b_MuP_ProbNNk);
  fChain->SetBranchAddress("MuP_ProbNNp", &MuP_ProbNNp, &b_MuP_ProbNNp);
  fChain->SetBranchAddress("MuP_ProbNNpi", &MuP_ProbNNpi, &b_MuP_ProbNNpi);
  fChain->SetBranchAddress("MuP_ProbNNmu", &MuP_ProbNNmu, &b_MuP_ProbNNmu);
  fChain->SetBranchAddress("MuP_ProbNNghost", &MuP_ProbNNghost, &b_MuP_ProbNNghost);
  fChain->SetBranchAddress("MuP_hasMuon", &MuP_hasMuon, &b_MuP_hasMuon);
  fChain->SetBranchAddress("MuP_isMuon", &MuP_isMuon, &b_MuP_isMuon);
  fChain->SetBranchAddress("MuP_hasRich", &MuP_hasRich, &b_MuP_hasRich);
  fChain->SetBranchAddress("MuP_hasCalo", &MuP_hasCalo, &b_MuP_hasCalo);
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
  fChain->SetBranchAddress("nTracks", &nTracks, &b_nTracks);
}

Bool_t RecSelector::Notify()
{
  // The Notify() function is called when a new file is opened. This
  // can be either for a new TTree in a TChain or when when a new TTree
  // is started when using PROOF. It is normally not necessary to make changes
  // to the generated code, but the routine can be extended by the
  // user if needed. The return value is currently not used.

  return kTRUE;
}

#endif // #ifdef RecSelector_cxx
