#include "TFile.h"
#include "TTree.h"
#include "TH1D.h"
#include "TCanvas.h"
#include "TAxis.h"
#include "RooRealVar.h"
#include "RooCategory.h"
#include "RooThresholdCategory.h"
#include "RooDataSet.h"
#include "RooDataHist.h"
#include "RooHistPdf.h"
#include "RooKeysPdf.h"
#include "RooNDKeysPdf.h"
#include "RooAddPdf.h"
#include "RooMCStudy.h"
#include "RooChi2MCSModule.h"

#include <iostream>
#include <string>
using namespace std;

TTree *dataTree;
RooRealVar* lt;
RooRealVar* mm2;
RooCategory* mm2cat;
RooRealVar* q2;
RooCategory* q2cat;
RooRealVar* el;
RooCategory* elcat;
RooRealVar* w;
RooRealVar* MyBkgTag;
RooDataHist* mu_genhist;
RooDataHist* tau_genhist;
RooDataHist* b0_genhist;
RooDataHist* b_genhist;
RooDataHist* comb_genhist;
// RooDataHist* lowmass_genhist;
// RooDataHist* other_genhist;
RooDataHist* mu_multihist;
RooDataHist* tau_multihist;
RooDataHist* b0_multihist;
RooDataHist* b_multihist;
RooDataHist* comb_multihist;
// RooDataHist* lowmass_multihist;
// RooDataHist* other_multihist;
RooDataHist* mu_lthist;
RooDataHist* tau_lthist;
RooDataHist* b0_lthist;
RooDataHist* b_lthist;
RooDataHist* comb_lthist;
// RooDataHist* lowmass_lthist;
// RooDataHist* other_lthist;
RooHistPdf* mu_genpdf;
RooHistPdf* tau_genpdf;
RooHistPdf* b0_genpdf;
RooHistPdf* b_genpdf;
RooHistPdf* comb_genpdf;
// RooHistPdf* lowmass_genpdf;
// RooHistPdf* other_genpdf;
// RooHistPdf* mu_multipdf;
// RooHistPdf* tau_multipdf;
// RooHistPdf* b0_multipdf;
// RooHistPdf* b_multipdf;
// RooHistPdf* comb_multipdf;
// RooHistPdf* lowmass_multipdf;
// RooHistPdf* other_multipdf;
// RooHistPdf* mu_ltpdf;
// RooHistPdf* tau_ltpdf;
// RooHistPdf* b0_ltpdf;
// RooHistPdf* b_ltpdf;
// RooHistPdf* comb_ltpdf;
// RooHistPdf* lowmass_ltpdf;
// RooHistPdf* other_ltpdf;
// RooProdPdf* mu_pdf;
// RooProdPdf* tau_pdf;
// RooProdPdf* b0_pdf;
// RooProdPdf* b_pdf;
// RooProdPdf* comb_pdf;
// RooProdPdf* lowmass_pdf;
// RooProdPdf* other_pdf;
RooRealVar* num_mu;
RooRealVar *Rtau;
RooFormulaVar* num_tau;
RooRealVar* num_b0;
RooRealVar* num_b;
RooRealVar* num_comb;
// RooRealVar* num_lowmass;
// RooRealVar* num_other;
RooAddPdf* model;
RooMCStudy* mcs;
using namespace RooFit;

void FitW_LT_MM2Cat_Q2Cat_ELCat ()
{

  const char mm2str[10] = "MissMass2";
  const char ltstr[12] = "ExpLifetime"; // or ExpLifetime
  const char q2str[3] = "Q2";
  const char elstr[13] = "BachMuEnergy";
  const char wstr[7] = "weight";
  const char bkgstr[9] = "MyBkgTag";

  // -------------------------
  // OPENING ROOT FILES
  // -------------------------

  cout << "Opening root files ... " << endl;

  TFile dataFile("Bc_MC.root","READ");
  dataTree = (TTree*)dataFile.Get("DecayTree");
  dataTree->AddFriend("weightTree","Bc_MC_Weights.root");

  // -------------------------
  // CREATEING ROOFIT VARIABLES AND DATASETS
  // -------------------------

  cout << "Creating roofit variables and datasets ... " << endl;

  lt = new RooRealVar (ltstr,"lt",0.0,0.8);
  mm2 = new RooRealVar (mm2str,"mm2",-5,10);
  q2 = new RooRealVar (q2str,"q2",-5,10.4);
  el = new RooRealVar (elstr,"el",120,3000);
  RooThresholdCategory* mm2thrcat = new RooThresholdCategory("mm2thrcat","mm2thrcat",*mm2,"6");
  mm2thrcat->addThreshold(7.0,"6");
  mm2thrcat->addThreshold(5.0,"5");
  mm2thrcat->addThreshold(3.0,"4");
  mm2thrcat->addThreshold(2.0,"3");
  mm2thrcat->addThreshold(-2.0,"2");
  mm2thrcat->addThreshold(-5.0,"1");
  RooThresholdCategory* q2thrcat = new RooThresholdCategory("q2thrcat","q2thrcat",*q2,"VeryHigh");
  q2thrcat->addThreshold(8.5,"VeryHigh");
  q2thrcat->addThreshold(7.0,"High");
  q2thrcat->addThreshold(5.0,"Low");
  q2thrcat->addThreshold(-5.0,"VeryLow");
  RooThresholdCategory* elthrcat = new RooThresholdCategory("elthrcat","elthrcat",*el,"VeryHigh");
  elthrcat->addThreshold(1200,"VeryHigh");
  elthrcat->addThreshold(800,"High");
  elthrcat->addThreshold(500,"Low");
  elthrcat->addThreshold(120,"VeryLow");
  w = new RooRealVar (wstr,"w",0.0,10.0);
  MyBkgTag = new RooRealVar(bkgstr,"tag",0.0);

  RooArgSet vars(*lt,*mm2,*q2,*el,*w,*MyBkgTag);

  RooDataSet* w_data = new RooDataSet("w_data","w_data",vars,Import(*dataTree),WeightVar(*w));
  mm2cat = (RooCategory*)w_data->addColumn(*mm2thrcat);
  q2cat = (RooCategory*)w_data->addColumn(*q2thrcat);
  elcat = (RooCategory*)w_data->addColumn(*elthrcat);

  string mu_cut = "MyBkgTag % 100 == 0";
  string tau_cut = "MyBkgTag % 100 == 1";
  string b0_cut = "MyBkgTag % 1000 == 2";
  string b_cut = "MyBkgTag % 1000 == 102";
  string bunk_cut = "MyBkgTag % 1000 == 202"; // won't use
  string mispid_cut = "MyBkgTag % 100 == 3"; // won't use
  string comb_cut = "MyBkgTag % 100 == 4";
  string pv_cut = "MyBkgTag % 100 == 5"; // won't use
  string other_cut = "(MyBkgTag % 100 == 6) || (MyBkgTag % 100 == -1)"; // won't use
  
  // How many bins are enough?
  mm2->setBins(20);
  lt->setBins(20);

  RooArgSet fvarsset(*lt,*mm2cat,*q2cat,*elcat);
  mu_genhist = new RooDataHist("mu_genhist","mu_genhist",fvarsset);
  mu_genhist->add(*w_data,mu_cut.c_str());
  tau_genhist = new RooDataHist("tau_genhist","tau_genhist",fvarsset);
  tau_genhist->add(*w_data,tau_cut.c_str());
  b0_genhist = new RooDataHist("b0_genhist","b0_genhist",fvarsset);
  b0_genhist->add(*w_data,b0_cut.c_str());
  b_genhist = new RooDataHist("b_genhist","b_genhist",fvarsset);
  b_genhist->add(*w_data,b_cut.c_str());
  comb_genhist = new RooDataHist("comb_genhist","comb_genhist",fvarsset);
  comb_genhist->add(*w_data,comb_cut.c_str());

//   RooArgSet multiset(*mm2,*q2cat,*elcat);   
//   mu_multihist = new RooDataHist("mu_multihist","mu_multihist",multiset);
//   mu_multihist->add(*w_data,mu_cut.c_str());
//   tau_multihist = new RooDataHist("tau_multihist","tau_multihist",multiset);
//   tau_multihist->add(*w_data,tau_cut.c_str());
//   b0_multihist = new RooDataHist("b0_multihist","b0_multihist",multiset);
//   b0_multihist->add(*w_data,b0_cut.c_str());
//   b_multihist = new RooDataHist("b_multihist","b_multihist",multiset);
//   b_multihist->add(*w_data,b_cut.c_str());
//   comb_multihist = new RooDataHist("comb_multihist","comb_multihist",multiset);
//   comb_multihist->add(*w_data,comb_cut.c_str());


//   mu_lthist = new RooDataHist("mu_lthist","mu_lthist",RooArgSet(*lt));
//   mu_lthist->add(*w_data,mu_cut.c_str());
//   tau_lthist = new RooDataHist("tau_lthist","tau_lthist",RooArgSet(*lt));
//   tau_lthist->add(*w_data,tau_cut.c_str());
//   b0_lthist = new RooDataHist("b0_lthist","b0_lthist",RooArgSet(*lt));
//   b0_lthist->add(*w_data,b0_cut.c_str());
//   b_lthist = new RooDataHist("b_lthist","b_lthist",RooArgSet(*lt));
//   b_lthist->add(*w_data,b_cut.c_str());
//   comb_lthist = new RooDataHist("comb_lthist","comb_lthist",RooArgSet(*lt));
//   comb_lthist->add(*w_data,comb_cut.c_str());
  
  // -------------------------
  // CREATING ROOFIT PDFS
  // -------------------------

  cout << "Creating roofit pdfs ... " << endl;
 
  mu_genpdf = new RooHistPdf ("mugen","mu genpdf",fvarsset,*mu_genhist,3);
  tau_genpdf = new RooHistPdf ("taugen","tau genpdf",fvarsset,*tau_genhist,3);
  b0_genpdf = new RooHistPdf ("b0gen","b0 genpdf",fvarsset,*b0_genhist,3);
  b_genpdf = new RooHistPdf ("bgen","b genpdf",fvarsset,*b_genhist,3);
  comb_genpdf = new RooHistPdf ("combgen","comb genpdf",fvarsset,*comb_genhist,3);
  
  num_mu = new RooRealVar ("num_mu","num_mu",0.5E5,1,2E5);
  Rtau = new RooRealVar ("Rtau","Rtau",0.02,1E-10,1.0);
  num_tau = new RooFormulaVar ("num_tau","num_tau","num_mu * Rtau",RooArgList(*num_mu,*Rtau));
  num_b0 = new RooRealVar ("num_b0","num_b0",0.5E4,1,2E5);
  num_b = new RooRealVar ("num_b","num_b",1.25E4,1,2E5);
  num_comb = new RooRealVar ("num_comb","num_comb",1.75E4,1,2E5);

  model = new RooAddPdf ("model","model",
			 RooArgList(*mu_genpdf,*tau_genpdf,*b0_genpdf,*b_genpdf,*comb_genpdf),
			 RooArgList(*num_mu,*num_tau,*num_b0,*num_b,*num_comb));

//   mu_multipdf = new RooHistPdf ("mumulti","mu multipdf",multiset,*mu_multihist,3);
//   tau_multipdf = new RooHistPdf ("taumulti","tau multipdf",multiset,*tau_multihist,3);
//   b0_multipdf = new RooHistPdf ("b0multi","b0 multipdf",multiset,*b0_multihist,3);
//   b_multipdf = new RooHistPdf ("bmulti","b multipdf",multiset,*b_multihist,3);
//   comb_multipdf = new RooHistPdf ("combmulti","comb multipdf",multiset,*comb_multihist,3);
  
//   mu_ltpdf = new RooHistPdf ("mu_ltpdf","mu ltpdf",RooArgSet(*lt),*mu_lthist,3);
//   tau_ltpdf = new RooHistPdf ("tau_ltpdf","tau ltpdf",RooArgSet(*lt),*tau_lthist,3);
//   b0_ltpdf = new RooHistPdf ("b0_ltpdf","b0 ltpdf",RooArgSet(*lt),*b0_lthist,3);
//   b_ltpdf = new RooHistPdf ("b_ltpdf","b ltpdf",RooArgSet(*lt),*b_lthist,3);
//   comb_ltpdf = new RooHistPdf ("comb_ltpdf","comb ltpdf",RooArgSet(*lt),*comb_lthist,3);
  
//   mu_pdf = new RooProdPdf ("mu","mu pdf",RooArgList(*mu_multipdf,*mu_ltpdf));
//   tau_pdf = new RooProdPdf ("tau","tau pdf",RooArgList(*tau_multipdf,*tau_ltpdf));
//   b0_pdf = new RooProdPdf ("b0","b0 pdf",RooArgList(*b0_multipdf,*b0_ltpdf));
//   b_pdf = new RooProdPdf ("b","b pdf",RooArgList(*b_multipdf,*b_ltpdf));
//   comb_pdf = new RooProdPdf ("comb","comb pdf",RooArgList(*comb_multipdf,*comb_ltpdf));

//   model = new RooAddPdf ("model","model",
// 			 RooArgList(*mu_pdf,*tau_pdf,*b0_pdf,*b_pdf,*comb_pdf),
// 			 RooArgList(*num_mu,*num_tau,*num_b0,*num_b,*num_comb));
  

  // -------------------------
  // GENERATING AND FITTING TOY MC
  // -------------------------

  cout << "generating and fitting toy MC ... " << endl;

  /* I'll set the numbers to expected values and generate toy MC
   */

  // Remove FitModel(*model) to make the fit model the one that preserveds
  // the correlations between Lifetime and MissMass2/Q2/BachMuEnergy
  mcs = new RooMCStudy(*model,fvarsset,Binned(true),Extended(true),FitOptions(Save(true),Minos(true),Strategy(2)));
  RooChi2MCSModule chi2mod;
  mcs->addModule(chi2mod);
  
  mcs->generateAndFit(1000,0,true); // number of events taken to be 500?

  return;
}

