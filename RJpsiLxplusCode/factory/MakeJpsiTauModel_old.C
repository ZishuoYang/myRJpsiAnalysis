#include "constants.hh"

#include <iostream>

#include "TRandom3.h"
#include "TCanvas.h"
#include "TStopwatch.h"

#include "RooAbsData.h"
#include "RooPoisson.h"
#include "RooRealVar.h"
#include "RooMCStudy.h"
#include "RooMinuit.h"
#include "RooCategory.h"
#include "RooDataSet.h"
#include "RooDataHist.h"
#include "RooFitResult.h"
#include "RooMsgService.h"
#include "RooParamHistFunc.h"
#include "RooHist.h"

#include "RooStats/ModelConfig.h"
#include "RooStats/ToyMCSampler.h"
#include "RooStats/MinNLLTestStat.h"

#include "RooStats/HistFactory/HistFactorySimultaneous.h"
#include "RooStats/HistFactory/Channel.h"
#include "RooStats/HistFactory/MakeModelAndMeasurementsFast.h"
#include "RooStats/HistFactory/Measurement.h"
#include "RooStats/HistFactory/ParamHistFunc.h"
#include "RooStats/HistFactory/HistFactoryModelUtils.h"

//#define UNBLIND

using namespace RooFit;
using namespace RooStats;
using namespace HistFactory;

// Number of samples
const Int_t numChannels = 1; // eventually 2 for 2011 and 2012

// Plot options
const int ncomps = 4;
// Good list -- kRed,kBlue+1,kViolet,kViolet+1,kViolet+2,kGreen,kGreen+1,kOrange+1,kOrange+2,kOrange+3
const int colors[ncomps] = { kRed,kViolet+1,kGreen+1,kOrange+3 };
const TString stackparts[ncomps] = {
  "*sigtau*,*sigmu*,*comb*,*misID*"
  , "*sigmu*,*comb*,*misID*"
  , "*comb*,*misID*"
  , "*misID*"
};

const int ncomps_bl = 4;
// Good list -- kBlue,kGreen+2,kOrange+3,kViolet,kViolet+1,kGreen+1,kGreen+2,kOrange+2,kOrange+1,kOrange+3
const int colors_bl[ncomps_bl] = { kBlue,kViolet,kGreen+2,kOrange+3 };
const TString stackparts_bl[ncomps_bl] = {
  "*sigtau*,*sigmu*,*comb*,*misID*"
  ,"*sigmu*"
  ,"*comb*"
  ,"*misID*"
};

// EXPECTED NUMBERS OF VARIOUS BACKGROUNDS
const double RelLumi = 0.1; // Relative luminosity of fit sample to control sample
const double expMu = 2.5e4;
const double expComb = 3e4;

// FIT OPTIONS
const bool constrainFeeddown = false; // constrain various feeddown modes (from psi2s / chic states) using BFs
const bool dofit = true;
const bool toyMC = true;
const bool slowplots = true; // perform the (slow) plots of mm2, el in q2 bins
const int numToys = 1;
const bool BarlonBeestow = false;
/* Flag to enable Barlow-Beeston procedure for all histograms. 
   Should allow easy comparison of fit errors with and without the technique
   Set the prefix that will appear before all output for this measurement
*/

// PDG CONSTANTS
const double tau_to_mu = 0.1777;
const double tau_to_mu_min = 0.9968;
const double tau_to_mu_max = 1.0032;

const double psi2s_to_jpsi = 0.603;
const double psi2s_to_jpsi_min = 0.9884;
const double psi2s_to_jpsi_max = 1.0116;

// COLLIDER CONSTANTS
const double b0cs = 0;
const double b0cs_min = 0;
const double b0cs_max = 0;

const double bcs = 0;
const double bcs_min = 0;
const double bcs_max = 0;

const double bscs = 0;
const double bscs_min = 0;
const double bscs_max = 0;

void SetNuisanceConstant(ModelConfig* mc, const char* str) {
  ((RooRealVar*)(mc->GetNuisanceParameters()->find(str)))->setConstant(kTRUE);
}

Double_t GetNuisanceVal(ModelConfig* mc, const char* str) {
  return ((RooRealVar*)(mc->GetNuisanceParameters()->find(str)))->getVal();
}

void MakeJpsiTauModel() {
 
  // -------------------------
  // SETUP
  // -------------------------
 
  RooMsgService::instance().setGlobalKillBelow(RooFit::WARNING) ;
  TStopwatch sw;
 
  // -------------------------
  // Histogram inverse normalizations
  // -------------------------
 
  TFile file(locTemplates.Data());
  TH1 *htemp;

  double mcN_sigtau_2012,mcN_sigmu_2012,mcN_b0comb_2012,mcN_bcomb_2012,mcN_bscomb_2012;
  double *mcnorms[numMCSamples]={
    &mcN_sigtau_2012,
    , &mcN_sigmu_2012,
    , &mcN_b0comb_2012
    , &mcN_bcomb_2012
    , &mcN_bscomb_2012
  };

  for (int i =0; i < numMCSamples; i++) {
    file.GetObject("h_"+mchistos[i],htemp);
    assert(htemp!=NULL);
    *(mcnorms[i])=1./htemp->Integral();
    cout << "mcN_" << mchistos[i] << " = " << 1./ *(mcnorms[i]) << endl;
  }
  file.Close();
 
  // -------------------------
  // CREATE HISTFACTORY::MEASUREMENT
  // -------------------------
 
  RooStats::HistFactory::Measurement meas("my_measurement","my measurement");
  meas.SetOutputFilePrefix("results/my_measurement");
  meas.SetExportOnly(kTRUE);
  meas.SetPOI("RawR_jpsi");

  /* Set the lumi for the measurement,***in invfb***
     Only matters for the data-driven pdfs the way I've set it up. 
     rellumi gives the relative luminosity between the
     data used to generate the pdfs and the sample we are fitting
  */
  meas.SetLumi(1.0);
  meas.SetLumiRelErr(0.20);
  
  RooStats::HistFactory::Channel chan_2012("2012");
  chan_2012.SetStatErrorConfig(0.1,"Poisson");
  //  chan_2012.SetData("h_data",locData.Data());

  RooStats::HistFactory::Channel *chans[numChannels] = {&chan_2012};
  RooStats::HistFactory::Sample *samps[numChannels];

  // ------------------------------
  // SETUP SAMPLES
  // -----------------------------

  // Now that data is set up,start creating our samples
  // describing the processes to model the data

  /********************************** Bc -> J/ψ μ ν (NORM) ****************************************/

  RooStats::HistFactory::Sample sigmu_2012("h_sigmu_2012","h_sigmu_2012",locTemplates.Data());
  if (BarlonBeestow)
    sigmu_2012.ActivateStatError();
  samps[0] = &sigmu_2012;
  for (int i = 0; i < numChannels; i++) {
    samps[i]->SetNormalizeByTheory(kFALSE);
    samps[i]->AddNormFactor("mcNorm_sigmu",mcN_sigmu_2012,1e-9,1.); // reset to 1
    samps[i]->AddNormFactor("Nmu",expMu,1e-6,1e6); // expected number
    chans[i]->AddSample(*samps[i]);
  }
 
  /********************************** Bc -> J/ψ τ ν (SIGNAL) ****************************************/

  RooStats::HistFactory::Sample sigtau_2012("h_sigtau_2012","h_sigtau_2012",locTemplates.Data());
  if (BarlonBeestow)
    sigtau_2012.ActivateStatError();
  samps[0] = &sigtau_2012;
  for (int i = 0; i < numChannels; i++) {
    samps[i]->SetNormalizeByTheory(kFALSE);
    samps[i]->AddNormFactor("mcNorm_sigtau",mcN_sigtau_2012,1e-9,1.); // reset to 1
    samps[i]->AddNormFactor("Nmu",expMu,1e-6,1e6); // expected # mu
    samps[i]->AddNormFactor("f_tauFD",tau_to_mu,tau_to_mu,tau_to_mu);
    samps[i]->AddOverallSys("BF_tauFD",tau_to_mu_min,tau_to_mu_max);
    samps[i]->AddNormFactor("RawR_jpsi",0.25,1e-6,0.9); // raw R(J/ψ) -- before BR, efficiency corrections
    chans[i]->AddSample(*samps[i]);
  }

//   /********************************** Bc -> ψ(2S) μ ν (FEEDDOWN) ***********************************************/

//   RooStats::HistFactory::Sample psi2smu_2012("h_psi2smu_2012","h_psi2smu_2012",locTemplates.Data());
//   if (BarlonBeestow)
//     psi2smu_2012.ActivateStatError();
//   samps[0] = &psi2smu_2012;
//   for (int i = 0; i < numChannels; i++) {
//     samps[i]->SetNormalizeByTheory(kFALSE);
//     samps[i]->AddNormFactor("mcNorm_psi2smu_2012",mcN_psi2smu_2012,1e-9,1.); // reset to 1
//     if (!constrainFeeddown) {
//       samps[i]->AddNormFactor("N_psi2smu_2012",1e2,1e-6,1e5);
//     } else {
//       samps[i]->AddNormFactor("Nmu",expMu,1e-6,1e6); // a mostly arbitrary overall normalization for psi2s, chi_c feedown states
//       samps[i]->AddNormFactor("f_psi2s",0,0,0); // branching Bc -> ψ(2S) μ ν relative to Bc -> J/ψ μ ν -- take from Ebert, Kiselev, etc. // find a better name
//       samps[i]->AddOverallSys("BF_psi2s",0.9,1.1); // systematic in in above
//       samps[i]->AddNormFactor("f_psi2sFD",psi2s_to_jpsi,psi2s_to_jpsi,psi2s_to_jpsi); // inclusive ψ(2S) -> J/ψ branching fraction
//       samps[i]->AddNormFactor("BF_psi2sFD",psi2s_to_jpsi_min,psi2s_to_jpsi_max); // PDG error in above
//     }
//     chans[i]->AddSample(*samps[i]); 
//   }

//   /********************************** Bc -> ψ(2S) τ ν (FEEDDOWN) ***********************************************/

//   RooStats::HistFactory::Sample psi2stau_2012("h_psi2stau_2012","h_psi2stau_2012",locTemplates.Data());
//   if (BarlonBeestow)
//     psi2stau_2012.ActivateStatError();
//   samps[0] = &psi2stau_2012;
//   for (int i = 0; i < numChannels; i++) {
//     samps[i]->SetNormalizeByTheory(kFALSE);
//     samps[i]->AddNormFactor("mcNorm_psi2stau_2012",mcN_psi2stau_2012,1e-9,1.); // reset to 1
//     if (!constrainFeeddown) {
//       samps[i]->AddNormFactor("N_psi2smu_2012",1e2,1e-6,1e5);
//     } else {
//       samps[i]->AddNormFactor("Nmu",expMu,1e-6,1e6); // a mostly arbitrary overall normalization for psi2s, chi_c feedown states
//       samps[i]->AddNormFactor("f_psi2s",0,0,0); // branching Bc -> ψ(2S) μ ν relative to Bc -> J/ψ μ ν // find a better name
//       samps[i]->AddOverallSys("BF_psi2s",0.9,1.1); // systematic in in above
//       samps[i]->AddNormFactor("f_psi2sFD",psi2s_to_jpsi,psi2s_to_jpsi,psi2s_to_jpsi); // inclusive ψ(2S) -> J/ψ branching fraction
//       samps[i]->AddNormFactor("BF_psi2sFD",psi2s_to_jpsi_min,psi2s_to_jpsi_max); // PDG error in above
//     }
//     samps[i]->AddNormFactor("f_tauFD",tau_to_mu,tau_to_mu,tau_to_mu);
//     samps[i]->AddOverallSys("BF_tauFD",tau_to_mu_min,tau_to_mu_max);
//     samps[i]->AddNormFactor("RawR_jpsi",0.05,0.,1.); // later have a separate psi2s?
//     chans[i]->AddSample(*samps[i]); 
//   }

  /********************************** Combinatoric B0 BKG (FROM MC, SADLY) *******************************************/

  RooStats::HistFactory::Sample b0comb("h_b0comb_2012","h_b0comb_2012",locTemplates.Data());
  if (BarlonBeestow)
    b0comb.ActivateStatError();
  samps[0] = &b0comb;
  
  for (int i = 0; i < numChannels; i++) {
    samps[i]->SetNormalizeByTheory(kFALSE);
    samps[i]->AddNormFactor("mcNorm_b0comb_2012",mcN_b0comb_2012,1e-9,1.); // reset to 1
    samps[i]->AddNormFactor("Ncomb",expComb,1e-6,1e6); // expected total number of comb. background
    samps[i]->AddNormFactor("f_b0cs",b0cs,b0cs,b0cs);
    samps[i]->AddOverallSys("BF_b0cs",b0cs_min,b0cs_max);
    chans[i]->AddSample(*samps[i]);
  }
 
  /********************************** Combinatoric B BKG (FROM MC, SADLY) *******************************************/

  RooStats::HistFactory::Sample bcomb("h_bcomb_2012","h_bcomb_2012",locTemplates.Data());
  if (BarlonBeestow)
    bcomb.ActivateStatError();
  samps[0] = &bcomb;
  
  for (int i = 0; i < numChannels; i++) {
    samps[i]->SetNormalizeByTheory(kFALSE);
    samps[i]->AddNormFactor("mcNorm_bcomb_2012",mcN_bcomb_2012,1e-9,1.); // reset to 1
    samps[i]->AddNormFactor("Ncomb",expComb,1e-6,1e6); // expected total number of comb. background
    samps[i]->AddNormFactor("f_bcs",bcs,bcs,bcs);
    samps[i]->AddOverallSys("BF_bcs",bcs_min,bcs_max);
    chans[i]->AddSample(*samps[i]);
  }
 
  /********************************** Combinatoric BS BKG (FROM MC, SADLY) *******************************************/

  RooStats::HistFactory::Sample bscomb("h_bscomb_2012","h_bscomb_2012",locTemplates.Data());
  if (BarlonBeestow)
    bscomb.ActivateStatError();
  samps[0] = &bscomb;
  
  for (int i = 0; i < numChannels; i++) {
    samps[i]->SetNormalizeByTheory(kFALSE);
    samps[i]->AddNormFactor("mcNorm_bscomb_2012",mcN_bscomb_2012,1e-9,1.); // reset to 1
    samps[i]->AddNormFactor("Ncomb",expComb,1e-6,1e6); // expected total number of comb. background
    samps[i]->AddNormFactor("f_bscs",bscs,bscs,bscs);
    samps[i]->AddOverallSys("BF_bscs",bscs_min,bscs_max);
    chans[i]->AddSample(*samps[i]);
  }
 
  /********************************** MisID BKG (FROM DATA) *******************************************/

  RooStats::HistFactory::Sample misID("h_misID_2012","h_misID_2012",locTemplates.Data());
  if (BarlonBeestow)
    misID.ActivateStatError();

  misID.SetNormalizeByTheory(kTRUE);
  misID.AddNormFactor("NmisID",RelLumi,1e-6,1e5);
  chan_2012.AddSample(misID);

  /********************************** Sideband BKG (FROM DATA) *******************************************/

//   RooStats::HistFactory::Sample SB("h_SB","h_SB",locTemplates.Data());
//   if (BarlonBeestow)
//     SB.ActivateStatError();
//   SB.SetNormalizeByTheory(kFALSE);
//   SB.AddNormFactor("NSB",RelLumi,1e-3,1e3);
//   chan_2012.AddSample(SB);

  // -------------------------
  // ADD CHANNELS/SAMPLES TO MEASUREMENT
  // -------------------------

  cout << "AT LINE: " << __LINE__ << endl;

  meas.AddChannel(chan_2012);
  meas.CollectHistograms();
  
  cout << "AT LINE: " << __LINE__ << endl;

  // OPTION 1: Let HistFactory do the fit
  // Spoils the blinding!!!
  // RooStats::HistFactory::FitModelAndPlot("my_measurement");
 
  // OPTION 2: Get the model and R(D*) a.k.a. POI from HistFactory manually and steer RooFit myself
  RooWorkspace* w = RooStats::HistFactory::MakeModelAndMeasurementFast(meas);
  RooAbsData *data = (RooAbsData*) w->data("obsData");
  RooAbsData *kindata = data->reduce("channelCat==0");
  
  cout << "AT LINE: " << __LINE__ << endl;

  // MODEL AND POI
  ModelConfig* mc = (ModelConfig*) w->obj("ModelConfig");
  RooSimultaneous* model = (RooSimultaneous*)mc->GetPdf();
  HistFactorySimultaneous* model_hf = new HistFactorySimultaneous( *model );
  RooRealVar* poi = (RooRealVar*) mc->GetParametersOfInterest()->createIterator()->Next();
  std::cout << "Param of Interest: " << poi->GetName() << std::endl; 

  cout << "AT LINE: " << __LINE__ << endl;

  // DATA DIMENSIONS
  RooArgSet *obs = (RooArgSet*) mc->GetObservables();
  RooRealVar *mm2 = (RooRealVar*) obs->find("obs_x_2012");
  mm2->SetTitle("m^{2}_{miss}");
  mm2->setUnit("GeV^{2}");
  RooRealVar *loglt = (RooRealVar*) obs->find("obs_y_2012");
  loglt->SetTitle("ln(τ/ps)");
  loglt->setUnit("");
  RooRealVar *q2 = (RooRealVar*) obs->find("obs_z_2012");
  q2->SetTitle("q^{2}");
  q2->setUnit("MeV^{2}");
  RooCategory *idx = (RooCategory*) obs->find("channelCat");

  cout << "AT LINE: " << __LINE__ << endl;

  // FIX SOME MODEL PARAMS
  for (int i = 0; i < numMCSamples; i++) {
    SetNuisanceConstant(mc,"mcNorm_"+mchistos[i]);
    cout << "mcNorm_"+mchistos[i]+" = " << GetNuisanceVal(mc,"mcNorm_"+mchistos[i]) << endl;
  }
  SetNuisanceConstant(mc,"f_tauFD");
  SetNuisanceConstant(mc,"NmisID");
  SetNuisanceConstant(mc,"Ncomb");
  if (constrainFeeddown) {
    SetNuisanceConstant(mc,"f_psi2s"); // find a better name for that
    SetNuisanceConstant(mc,"f_psi2sFD");
  }
  
  // -------------------------
  // LIST OF STATISTICAL UNCERTAINTIES
  // -------------------------
  
  ParamHistFunc *param_func = NULL;

  // SET 3D GAMMAS (I.E. STAT UNCERTAINTIES)
  RooProdPdf *channelPDF = (RooProdPdf*) w->obj("model_2012");
  RooArgList *gammas = new RooArgList();
  RooStats::HistFactory::getStatUncertaintyFromChannel(channelPDF,param_func,gammas);
  if (param_func != NULL) gammas = (RooArgList*)&(param_func->paramList());

  // -------------------------
  // TOY STUDY
  // -------------------------

  if (toyMC) {
    MinNLLTestStat NLLStat(*model);
    ToyMCSampler *sampler = new ToyMCSampler(NLLStat,1); 
    sampler->SetPdf(*model);
    sampler->SetObservables(*obs);
    sampler->SetParametersForTestStat(*poi);
    sampler->SetGenerateBinned(kTRUE);
    RooArgSet *pars = model_hf->getParameters(data);
    sw.Reset();
    sw.Start();
    data = (RooAbsData*) sampler->GenerateToyData(*pars); 
    sw.Stop();
  }
 
  // -------------------------
  // GET NLL FROM HF MODEL
  // -------------------------

  RooAbsReal* nll_hf = model_hf->createNLL( *data, ConditionalObservables(*gammas) );
  RooMinuit* minuit_hf = new RooMinuit( *nll_hf ) ;
  minuit_hf->optimizeConst(1);
#ifndef UNBLIND
  minuit_hf->setPrintLevel(-1);
#endif
 
  RooFitResult *result;

  // -------------------------
  // PRINT ALL THE THINGS
  // -------------------------

  meas.PrintTree();
  model->Print("v"); 
  channelPDF->Print("v"); 
  cout << "\n\n+++++++\n\n" << endl;

  // -------------------------
  // DO THE FIT
  // -------------------------

  if (dofit) {
    std::cout << "Minimizing the Minuit (Migrad)" << std::endl;
    RooMsgService::instance().setGlobalKillBelow(RooFit::ERROR);

    sw.Reset();
    sw.Start();
    minuit_hf->fit("smh");
    sw.Stop();
    result = minuit_hf->save("Result","Result");
  }

  // -------------------------
  // MAKE PLOTS
  // -------------------------

  // BASIC PLOTS
  RooPlot *mm2_frame = mm2->frame();
  RooPlot *loglt_frame = loglt->frame();
  RooPlot *q2_frame = q2->frame();
  const int nframes = 3;
  RooPlot *drawframes[nframes] = {mm2_frame,loglt_frame,q2_frame};

  // RESIDUALS
  RooPlot *mm2_resid_frame = mm2->frame();
  RooPlot *loglt_resid_frame = loglt->frame();
  RooPlot *q2_resid_frame = q2->frame();

  // BINNED PLOTS
  RooPlot *mm2q2_frame[q2_bins]; // mm2 in bins of q2
  RooPlot *logltq2_frame[q2_bins]; // loglt in bins of q2
  RooPlot *q2frames[2*q2_bins]; // Combination of the two above
  for (int i = 0; i < q2_bins; i++) {
    mm2q2_frame[i] = mm2->frame();
    logltq2_frame[i] = loglt->frame();
    q2frames[i] = mm2q2_frame[i];
    q2frames[i+q2_bins] = logltq2_frame[i];
  }

  /****************************** DO BASIC PLOTS ******************************/


  RooHist *resids[nframes];

  // 3D DATA
  idx->setIndex(0);
  for (int i = 0; i < nframes; i++) {

    // PLOT DATA
    kindata->plotOn(drawframes[i],DataError(RooAbsData::Poisson));

#ifdef UNBLIND // PLOT EVERYTHING
    model->plotOn(drawframes[i],Slice(*idx),ProjWData(*idx,*kindata),LineColor(colors[0]),FillColor(colors[0]),DrawOption("F"));
    resids[i] = drawframes[i]->pullHist();
    if (not BarlonBeestow) {
      for (int j = 1; j < ncomps; j++)
	model->plotOn(drawframes[i],Slice(*idx),ProjWData(*idx,*kindata),Components(stackparts[j]),LineColor(colors[j]),FillColor(colors[j]),DrawOption("F"));
    }
#endif
#ifndef UNBLIND // OR PLOT BLIND
    model->plotOn(drawframes[i],Slice(*idx),ProjWData(*idx,*kindata));
    resids[i] = drawframes[i]->pullHist();
    if (not BarlonBeestow) {
      for (int j = 1; j < ncomps_bl; j++)
	model->plotOn(drawframes[i],Slice(*idx),ProjWData(*idx,*kindata),Components(stackparts_bl[j]),LineColor(colors_bl[j]),LineStyle(kDashed));
    }
#endif

    // PLOT DATA AGAIN, TO PREVENT OVERLAPPING FROM FILL
    kindata->plotOn(drawframes[i],DataError(RooAbsData::Poisson));
  }

  // SET RESIDS
  mm2_resid_frame->addPlotable(resids[0],"P");
  loglt_resid_frame->addPlotable(resids[1],"P");
  q2_resid_frame->addPlotable(resids[2],"P");

  /****************************** DO BINNED PLOTS ******************************/

  // Set up cut strings and range names for all the q2 bins
  char cutstrings[q2_bins][128];
  char rangenames[q2_bins][32];
  for (int i = 0; i < q2_bins; i++) {
    double binlow = q2_low+i*(q2_high-q2_low)/q2_bins;
    double binhigh = q2_low+(i+1)*(q2_high-q2_low)/q2_bins;
    sprintf(cutstrings[i],"obs_z_2012 > %f && obs_z_2012 < %f",q2_low+i*(q2_high-q2_low)/q2_bins,q2_low+(i+1)*(q2_high-q2_low)/q2_bins);
    sprintf(rangenames[i],"q2bin_%d",i);
    q2->setRange(rangenames[i],binlow,binhigh);
  }

  // Project the dataset into these q2 bins
  RooAbsData *q2cutdata[q2_bins];
  if (slowplots == true) {
    for (int i = 0; i < q2_bins; i++) {
      q2cutdata[i] = kindata->reduce(cutstrings[i]);
      kindata->plotOn(mm2q2_frame[i],Cut(cutstrings[i]),DataError(RooAbsData::Poisson));
      kindata->plotOn(logltq2_frame[i],Cut(cutstrings[i]),DataError(RooAbsData::Poisson));
      model->plotOn(mm2q2_frame[i],Slice(*idx),ProjWData(*idx,*q2cutdata[i]),ProjectionRange(rangenames[i])); //,Components(stackparts_bl[0]),LineColor(colors_bl[0]));
      model->plotOn(logltq2_frame[i],Slice(*idx),ProjWData(*idx,*q2cutdata[i]),ProjectionRange(rangenames[i])); //,Components(stackparts_bl[0]),LineColor(colors_bl[0]));

      if (not BarlonBeestow) {
	for (int j = 1; j < ncomps_bl; j++) {
	  model->plotOn(mm2q2_frame[i],Slice(*idx),ProjWData(*idx,*q2cutdata[i]),ProjectionRange(rangenames[i]),Components(stackparts_bl[j]),LineColor(colors_bl[j]),LineStyle(kDashed));
	  model->plotOn(logltq2_frame[i],Slice(*idx),ProjWData(*idx,*q2cutdata[i]),ProjectionRange(rangenames[i]),Components(stackparts_bl[j]),LineColor(colors_bl[j]),LineStyle(kDashed));
	}
      }
    }
  }

  // -------------------------
  // DRAW PLOTS TO CANVAS
  // -------------------------

  // 3D observables
  TCanvas *c_obs = new TCanvas("c_obs","c_obs",600,1200);
  c_obs->Divide(1,3);
  c_obs->cd(1);
  mm2_frame->Draw();
  c_obs->cd(2);
  loglt_frame->Draw();
  c_obs->cd(3);
  q2_frame->Draw();
 
  // RESIDUALS
  TCanvas *c_resids = new TCanvas("c_resids","c_resids",600,1200);
  c_resids->Divide(1,3);
  c_resids->cd(1);
  mm2_resid_frame->Draw();
  c_resids->cd(2);
  loglt_resid_frame->Draw();
  c_resids->cd(3);
  q2_resid_frame->Draw();

  // BINNED PLOTS
  if (slowplots == true) {
    
    TCanvas *c_binned = new TCanvas("c_binned","c_binned",1200,600);
    c_binned->Divide(q2_bins,2);
    
    for (int k = 0 ; k < q2_bins*2; k++) {
      c_binned->cd(k+1);
      q2frames[k]->Draw();
    }
  }

  // -------------------------
  // PRINT OUT SUMMARY INFO
  // -------------------------

  if (toyMC) 
    printf("Stopwatch: Generated test data in %f seconds\n",sw.RealTime());

  if (dofit) {
    printf("Fit ran with status %d\n",result->status());

    printf("Stat error on R(J/ψ) is %f\n",poi->getError());

    result->floatParsFinal().Print();

    RooRealVar *finalNmu = (RooRealVar*)((result->floatParsFinal()).find("Nmu"));
    RooRealVar *finalNcomb = (RooRealVar*)((result->floatParsFinal()).find("Ncomb"));
    RooRealVar *finalNmisID = (RooRealVar*)((result->floatParsFinal()).find("NmisID"));
    RooRealVar *finalBFD1p = (RooRealVar*)((result->floatParsFinal()).find("alpha_BF_tauFD"));
    RooRealVar *finalLumi = (RooRealVar*)((result->floatParsFinal()).find("Lumi"));

#ifdef UNBLIND
    printf("R(J/ψ) (RAW) \t\t\t= %f +/- %f\n",poi->getVal(),poi->getError());
#endif
#ifndef UNBLIND
    printf("R(J/ψ) (RAW) \t\t\t= XXX +/- %f\n",poi->getError());
    if (poi->getVal() > 1e-4 && poi->getVal() < 0.1) {printf("Non-crazy value found!\n");}
#endif
    printf("N(Bc -> J/ψ μ ν) \t\t= %f +/- %f\n",finalNmu->getVal(),finalNmu->getError());
    printf("N(Combinatoric) \t\t= %f +/- %f\n",finalNcomb->getVal(),finalNcomb->getError());
    printf("N(misidentification) \t\t= %f +/- %f\n",finalNmisID->getVal(),finalNmisID->getError());
    printf("Lumi (BKG scaling) \t= %f +/- %f\n",finalLumi->getVal(),finalLumi->getError());
 
    if (dofit) printf("Stopwatch: fit ran in %f seconds\n",sw.RealTime());
  }
 
}
