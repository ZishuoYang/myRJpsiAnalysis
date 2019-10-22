#include <TROOT.h>
#include <TChain.h>
#include <TFile.h>
#include <TSelector.h>
#include <TString.h>
#include <TH3F.h>

// MM2 BINS
const double mm2_low = -5;
const double mm2_high = 10;
const int mm2_bins = 30;

// LOGLT BINS
const double loglt_low = -2.25;
const double loglt_high = 1.5;
//const int loglt_bins = 40;
const int loglt_bins = 4;

// Q2 BINS
// pretending this is YM for now
//const double q2_low = 0;
//const double q2_high = 10.11;
//const int q2_bins = 4;
const double q2_low = 3.2;
const double q2_high = 6.5;
const int q2_bins = 30;

// ROOT FILES

const Int_t numMCSamples = 6; // sig, norm, comb mc
const Int_t numDataDrivenSamples = 1; // data driven Mis-ID
const Int_t numDataSamples = 1; // but haven't created it yet

const TString mcfiles[numMCSamples] = {
  "Bc2JpsiMu_MCMU_Cands.root"
  , "Bc2JpsiMu_MCTAU_Cands.root"
  , "Bc2JPsiMu_MCB0BKG_Cands.root"
  , "Bc2JPsiMu_MCBBKG_Cands.root"
  , "Bc2JPsiMu_MCBSBKG_Cands.root"
	, "Bc_BKG_Psi2SFD_Cands.root"
};

const TString datadrivenfiles[numDataDrivenSamples] = {
  "Bc2JpsiMu_DATA2012_MISID_Cands.root"
};

const TString datafiles[numDataSamples] = {
  "Bc2JpsiMu_DATA2012_Cands.root"
};

const TString mccuts[numMCSamples] = {
	"(Bc_BKGCAT == 0 && BachMu_ProbNNmu>0.5) ? exp((1/0.453-1/0.508)*TrueYTAU) : 0"
	,"(Bc_BKGCAT == 10 && BachMu_ProbNNmu>0.5) ? exp((1/0.453-1/0.508)*TrueYTAU) : 0"
  ,"(Bc_BKGCAT > -1 && BachMu_ProbNNmu>0.5) && (abs(Jpsi_MC_MOTHER_ID)==511 || abs(Jpsi_MC_GD_MOTHER_ID)==511 || abs(Jpsi_MC_GD_GD_MOTHER_ID)==511)"
  ,"(Bc_BKGCAT > -1 && BachMu_ProbNNmu>0.5) && (abs(Jpsi_MC_MOTHER_ID)==521 || abs(Jpsi_MC_GD_MOTHER_ID)==521 || abs(Jpsi_MC_GD_GD_MOTHER_ID)==521)"
  ,"(Bc_BKGCAT > -1 && BachMu_ProbNNmu>0.5) && (abs(Jpsi_MC_MOTHER_ID)==531 || abs(Jpsi_MC_GD_MOTHER_ID)==531 || abs(Jpsi_MC_GD_GD_MOTHER_ID)==531)"
	,"(Bc_BKGCAT == 50 && BachMu_ProbNNmu>0.5) ? exp((1/0.453-1/0.508)*TrueLifetime) : 0"
};

const TString datadrivencuts[numDataDrivenSamples] = {
  "(0==0)" // sometimes the PID variables don't work out well
};

const TString datacuts[numDataSamples] = {
	"(BachMu_ProbNNmu>0.5)"
};
  
// Histogram suffixes -- this can go in common options file as well
const TString mchistos[numMCSamples] = {
  "sigmu_2012"
  , "sigtau_2012"
  , "b0comb_2012"
  , "bcomb_2012"
  , "bscomb_2012"
	, "psi2smu_2012"
};

const TString datadrivenhistos[numDataDrivenSamples] = {
  "misID_2012"
};

const TString datahistos[numDataSamples] = {
  "data_2012"
};


// OUTPUT
const TString locTemplates = "histos/BcTemplates.root";
const TString locData = "histos/BcTemplates.root";
